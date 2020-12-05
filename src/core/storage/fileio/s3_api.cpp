/* Copyright © 2017 Apple Inc. All rights reserved.
 *
 * Use of this source code is governed by a BSD-3-clause license that can
 * be found in the LICENSE.txt file or at
 * https://opensource.org/licenses/BSD-3-Clause
 */
#ifndef TC_DISABLE_REMOTEFS

#ifndef _WIN32
#include <arpa/inet.h>
#else
#include <ws2tcpip.h>
#endif
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/regex.hpp>
#include <boost/tokenizer.hpp>
#include <chrono>
#include <core/logging/assertions.hpp>
#include <core/logging/logger.hpp>
#include <core/random/random.hpp>
#include <core/storage/fileio/fs_utils.hpp>
#include <core/storage/fileio/general_fstream.hpp>
#include <core/storage/fileio/get_s3_endpoint.hpp>
#include <core/storage/fileio/s3_api.hpp>
#include <core/system/cppipc/server/cancel_ops.hpp>
#include <fstream>
#include <future>
#include <memory>
#include <regex>
#include <string>
#include <thread>

/* aws */
#include <aws/core/Aws.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/core/http/HttpResponse.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/Delete.h>
#include <aws/s3/model/DeleteObjectRequest.h>
#include <aws/s3/model/DeleteObjectsRequest.h>
#include <aws/s3/model/ListObjectsV2Request.h>
#include <aws/s3/model/ListObjectsV2Result.h>

using namespace Aws;
using namespace Aws::S3;
using namespace turi::fileio;

namespace turi {
namespace {

/**
 * Check the string is a valid s3 bucket name using the following criteria from
 * http://docs.aws.amazon.com/AmazonS3/latest/dev/BucketRestrictions.html:
 *
 * 1 Bucket names must be at least 3 and no more than 63 characters long.
 * 2 Bucket names must be a series of one or more labels.
 * 3 Adjacent labels are separated by a single period (.).
 * 4 Bucket names can contain lowercase letters, numbers, and hyphens.
 * 5 Each label must start and end with a lowercase letter or a number.
 * 6 Bucket names must not be formatted as an IP address (e.g., 192.168.5.4).
 *
 * Amendment 1:
 *   Uppercase letters are in fact fine... And it is in fact case sensitive.
 *   Our test bucket Turi-Datasets breaks a couple of the rules above.
 *   Tweaked to accept capital letters.
 *
 * Amendment 2:
 *   underscores are fine too
 */
bool bucket_name_valid(const std::string& bucket_name) {
  // rule 1
  if (bucket_name.size() < 3 || bucket_name.size() > 63) {
    return false;
  }

  // rule 2, 3
  typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
  boost::char_separator<char> sep(".");
  tokenizer labels(bucket_name, sep);
  tokenizer::iterator iter = labels.begin();
  if (iter == labels.end()) {
    return false;
  }

  // rule 4, 5
  auto label_valid = [](const std::string& label) {
    if (label.empty()) return false;
    using namespace std::regex_constants;

    auto alnum = [=](char x) {
      return (x <= 'Z' && x >= 'A') || (x <= 'z' && x >= 'a') ||
             (x <= '9' && x >= '0');
    };
    auto alnum_underscore_or_hypen = [=](char x) {
      return x == '-' || x == '_' || alnum(x);
    };

    // begin
    if (!alnum(*label.begin())) return false;
    // end
    if (!alnum(*(label.end() - 1))) return false;
    // everything in between
    for (size_t i = 1; i < label.size() - 1; ++i) {
      if (!alnum_underscore_or_hypen(label[i])) return false;
    }
    return true;
  };
  while (iter != labels.end()) {
    if (!label_valid(*iter)) return false;
    ++iter;
  }

  // rule 6, to validate, let's try creating an ip address from the bucket name.
  struct sockaddr_in sa;
  int result = inet_pton(AF_INET, bucket_name.c_str(), &(sa.sin_addr));
  if (result != 0) return false;

  return true;
}

}  // anonymous namespace

/*
 * @param: parsed_url output parameter, its state will be modified
 */
S3Client init_aws_sdk_with_turi_env(s3url& parsed_url) {
  // s3 client config
  // DefaultCredentialProviderChain
  Aws::Client::ClientConfiguration clientConfiguration;

  // a little bit too long, anyway
  clientConfiguration.requestTimeoutMs = 5 * 60000;
  clientConfiguration.connectTimeoutMs = 20000;

  if (turi::fileio::insecure_ssl_cert_checks()) {
    clientConfiguration.verifySSL = false;
  }

  if (!parsed_url.endpoint.empty()) {
    clientConfiguration.endpointOverride = parsed_url.endpoint.c_str();
  } else {
    auto env_var = get_endpoint_from_env();
    if (env_var) {
      clientConfiguration.endpointOverride = env_var->c_str();
      parsed_url.sdk_endpoint = env_var->c_str();
    }
  }

  // TODO: add proxy support
  // clientConfiguration.proxyHost = proxy.c_str();

  // set path or file for ssl certs
  if (!get_alternative_ssl_cert_file().empty()) {
    auto fstaus = get_file_status(get_alternative_ssl_cert_file());
    ASSERT_TRUE(fstaus.second.empty());
    if (fstaus.first == file_status::REGULAR_FILE) {
      clientConfiguration.caFile = get_alternative_ssl_cert_file().c_str();
    } else {
      std::stringstream ss;
      ss << "Invalid file for alternative SSL certificate. Value of "
            "TURI_FILEIO_ALTERNATIVE_SSL_CERT_FILE must be a regular file. "
         << get_alternative_ssl_cert_file() << " is not a regular file.";
      log_and_throw(ss.str());
    }
  }

  if (!get_alternative_ssl_cert_dir().empty()) {
    auto fstaus = get_file_status(get_alternative_ssl_cert_dir());
    ASSERT_TRUE(fstaus.second.empty());
    if (fstaus.first == file_status::DIRECTORY) {
      clientConfiguration.caPath = get_alternative_ssl_cert_dir().c_str();
    } else {
      std::stringstream ss;
      ss << "Invalid file for alternative SSL certificate. Value of "
            "TURI_FILEIO_ALTERNATIVE_SSL_CERT_DIR must be a valid directory. "
         << get_alternative_ssl_cert_dir() << " is not a regular directory.";
      log_and_throw(ss.str());
    }
  }

  std::string region = fileio::get_region_name_from_endpoint(
      clientConfiguration.endpointOverride.c_str());

  if (!region.empty()) {
    clientConfiguration.region = region.c_str();
  } else {
    auto env_var = get_auth_region_from_env();
    if (env_var) {
      clientConfiguration.region = env_var->c_str();
      parsed_url.sdk_region = env_var->c_str();
    }
  }

  if (parsed_url.secret_key.empty()) {
    return S3Client(clientConfiguration,
                    /* default value */
                    Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never,
                    /* use virtual address */ false);
  } else {
    // credentials
    Aws::Auth::AWSCredentials credentials(parsed_url.access_key_id.c_str(),
                                          parsed_url.secret_key.c_str());
    return S3Client(credentials, clientConfiguration,
                    /* default value */
                    Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never,
                    /* use virtual address */ false);
  }
}

const std::vector<std::string> S3Operation::_enum_to_str = {
    "DeleteObjects", "ListObjects", "HeadObjects"};

/**
 * This splits a URL of the form
 * s3://[access_key_id]:[secret_key]:[endpoint/][bucket]/[object_name]
 * into several pieces.
 *
 * Returns true on success, false on failure.
 */
bool parse_s3url(const std::string& s3_url, s3url& ret, std::string& err_msg) {
  // must begin with s3://
  auto url = s3_url;
  if (fileio::get_protocol(url) != "s3") {
    err_msg = url + " doesn't start with 's3://'";
    return false;
  }
  // strip the s3://
  url = url.substr(5);
  err_msg.clear();

  // Extract the access key ID and secret key
  std::stringstream ss;
  size_t splitpos = url.find(':');
  if (splitpos == std::string::npos) {
    ss << "Cannot find AWS_ACCESS_KEY_ID in the s3 url." << __FILE__ << " at "
       << __LINE__;
    err_msg = ss.str();
    logstream(LOG_WARNING) << err_msg << std::endl;
    return false;
  } else {
    ret.access_key_id = url.substr(0, splitpos);
    url = url.substr(splitpos + 1);
  }
  // Extract the secret key
  splitpos = url.find(':');
  if (splitpos == std::string::npos) {
    ss << "Cannot find SECRET_AWS_ACCESS_KEY in the s3 url." << __LINE__
       << " at " << __FILE__;
    err_msg = ss.str();
    logstream(LOG_WARNING) << err_msg << std::endl;
    return false;
  } else {
    ret.secret_key = url.substr(0, splitpos);
    url = url.substr(splitpos + 1);
  }

  boost::trim(url);

  if (url.empty()) {
    ss << "missing endpoint or bucket or object key in "
       << "s3://" << __FILE__ << " at" << __LINE__;
    err_msg = ss.str();
    return false;
  }

  // this is a bad design
  auto original_url = sanitize_url(url);

  // The rest is parsed using boost::tokenizer
  typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
  /*
   * keep extra token separators
   * since s3 is not like the UNIX director that redundant '/' will
   * be removed, e.g.,
   * s3://key/gui///// is not same as s3://key/gui/.
   * However in linux,
   * dir//// is same as dir/ or dir
   * */
  boost::char_separator<char> sep("/", 0, boost::keep_empty_tokens);
  tokenizer tokens(url, sep);
  tokenizer::iterator iter = tokens.begin();

  if (iter == tokens.end()) {
    ss << "missing endpoint or bucket or object key in " << url << __FILE__
       << "at" << __LINE__;
    err_msg = ss.str();
    return false;
  }

  // Parse endpoints; since we support private cloud settings
  // url can be tricky; region (.*)com is not sufficient
  if (std::regex_match(*iter, std::regex("(.*)\\.(com|net)"))) {
    std::string endpoint = *iter;

    std::vector<std::string> subs;
    boost::algorithm::split(subs, endpoint, [](char c) { return c == '.'; });
    bool is_valid = std::all_of(
        std::begin(subs), std::end(subs), [](const std::string& name) {
          return boost::regex_match(name, boost::regex("[[:w:]]+"));
        });

    if (!is_valid) {
      ss << "endpoint name: " << endpoint << " contains invalid chars: " << url
         << " " << __FILE__ << " at" << __LINE__;
      err_msg = ss.str();
      return false;
    }

    ret.endpoint = std::move(endpoint);
    ++iter;
  }

  // Parse bucket name
  if (iter == tokens.end()) {
    ss << "missing bucket name in " << '\'' << original_url << '\'' << " in "
       << __FILE__ << " at " << __LINE__;
    err_msg = ss.str();
    return false;
  }
  if (!bucket_name_valid(*iter)) {
    ss << '\'' << original_url << '\'' << " has invalid bucket name: " << *iter;
    err_msg = ss.str();
    logstream(LOG_WARNING) << err_msg << std::endl;
    return false;
  }
  ret.bucket = *iter;
  ++iter;

  // The rest part is the object key
  if (iter == tokens.end()) {
    // no object key
    return true;
  }

  ret.object_name = *iter;
  ++iter;
  while (iter != tokens.end()) {
    ret.object_name += "/" + *iter;
    ++iter;
  }

  // std::cout << "Access Key: " << ret.access_key_id << "\n"
  //           << "Secret Key: " << ret.secret_key<< "\n"
  //           << "Bucket: " << ret.bucket<< "\n"
  //           << "Object: " << ret.object_name<< "\n"
  //           << "Endpoint: " << ret.endpoint << "\n";
  return true;
}

// The options we pass to aws cli for s3 commands
// "us-east-1" is the us-standard and it works with buckets from all regions
// "acl" grants the bucket owner full permission regardless of the uploader's
// account
static const std::string S3_COMMAND_OPTION =
    "--region us-east-1 --acl bucket-owner-full-control";

std::string validate_input_file(const std::string& local_file) {
  // Try to open the input file
  std::shared_ptr<turi::general_ifstream> fin(
      new turi::general_ifstream(local_file.c_str(),
                                 false));  // gzip_compressed.
                                           // We avoid decompressing the file
                                           // on transfer. i.e. if the file is
                                           // compressed/uncompressed to begin
                                           // with, lets  keep it that way.

  // file cannot be opened
  if (!fin->good()) {
    return std::string("File ") + local_file + " cannot be opened.";
  }

  // get the file size. Return failure on failure.
  size_t file_size = fin->file_size();
  if (file_size == (size_t)(-1)) {
    return std::string("Size of file ") + local_file + " cannot be obtained.";
  }
  return "";
}

std::string validate_output_file(const std::string& local_file) {
  // Try to open the output file
  std::shared_ptr<turi::general_ofstream> fout(
      new turi::general_ofstream(local_file.c_str(),
                                 false));  // gzip_compressed.
                                           // We avoid recompressing the file
                                           // on transfer. i.e. if the file is
                                           // compressed/uncompressed to begin
                                           // with, lets  keep it that way.
  // file cannot be opened
  if (!fout->good()) {
    // return a failure immediately.
    return std::string("File ") + local_file + " cannot be opened.";
  }
  return "";
}

/**
 * Adding single quote around the path, and escape all single quotes inside the
 * path.
 */
std::string quote_and_escape_path(const std::string& path) {
  // s3 keys are at most 1024 bytes,
  // we make the buffer three times bigger
  // and it should be enough to conver the length of escaped path
  // s3://bucket_name/key
  const size_t BUF_SIZE = 1024 * 3;
  char* buf = new char[BUF_SIZE];
  size_t current_pos = 0;
  buf[current_pos++] = '\"';  // begin quote
  for (const auto& c : path) {
    if (c == '\'') {
      buf[current_pos++] = '\\';  // escape quote
      if (current_pos >= BUF_SIZE) {
        delete[] buf;
        throw("Invalid path: exceed length limit");
      }
    }
    buf[current_pos++] = c;
    if (current_pos >= BUF_SIZE) {
      delete[] buf;
      throw("Invalid path: exceed length limit");
    }
  }
  buf[current_pos++] = '\"';  // end quote
  std::string ret(buf, current_pos);
  delete[] buf;
  return ret;
}

list_objects_response list_objects_impl(const s3url& parsed_url,
                                        std::string proxy,
                                        std::string endpoint) {
  // do not modify the parsed_url because string_from_s3url() will
  // be called on it to retrieve its original url (prefix) in is_directory.

  // let init_aws_sdk to be aware of the endpoint to override
  auto temp_url = parsed_url;

  if (temp_url.endpoint.empty()) {
    temp_url.endpoint = endpoint;
  }

  if (!temp_url.sdk_proxy || temp_url.sdk_proxy->empty()) {
    temp_url.sdk_proxy = proxy;
  }

  S3Client client = init_aws_sdk_with_turi_env(temp_url);

  list_objects_response ret;

  Aws::S3::Model::ListObjectsV2Request request;
  request.WithBucket(parsed_url.bucket.c_str());
  request.WithPrefix(parsed_url.object_name.c_str());
  request.WithDelimiter("/");  // seperate objects from directories

  bool moreResults = false;
  bool success = false;
  int backoff = 50;  // ms
  int n_retry = 0;

  do {
    n_retry = 0;
    do {
      auto outcome = client.ListObjectsV2(request);

      success = outcome.IsSuccess();

      if (success) {
        auto result = outcome.GetResult();
        // now iterate through found objects - these are files
        Aws::Vector<Aws::S3::Model::Object> objects;
        objects = result.GetContents();
        for (auto const& o : objects) {
          ret.objects.push_back(std::string(o.GetKey().c_str()));
          std::stringstream stream;
          stream << o.GetLastModified().Millis();
          ret.objects_last_modified.push_back(stream.str());
          ret.objects_size.push_back(o.GetSize());
        }

        // now iterate through common prefixes - these are directories
        Aws::Vector<Aws::S3::Model::CommonPrefix> prefixes;
        prefixes = result.GetCommonPrefixes();
        for (auto const& p : prefixes) {
          std::string key = std::string(p.GetPrefix().c_str());
          // strip the ending "/" on a directory
          if (boost::ends_with(key, "/")) key = key.substr(0, key.length() - 1);
          ret.directories.push_back(key);
        }

        // more results to retrieve
        moreResults = result.GetIsTruncated();
        if (moreResults) {
          // add to the request object with continuation token
          request.WithContinuationToken(result.GetContinuationToken());
        }

        // jump out the retry loop
        break;

      } else {
        auto error = outcome.GetError();
        /*
         * Unlike CoreErrors, S3Error Never retries on S3 errors.
         * Retry can be based on HTTP code or HTTP body.
         *
         * 1. if SDK uses HTTP code, e.g., ShouldRetry return true on 429.
         * We don't need to retry on our own since SDK already made decision to
         * retry based on HTTP code.
         *
         * 2. if SDK doesn't use HTTP code but HTTP body, we check HTTP on our
         * own if SDK doesn't think it should retry based on messages in HTTP
         * body. Check https://guihao-liang.github.io/2020-04-12-aws-s3-retry/
         *
         * */
        if (!error.ShouldRetry()) {
          // SDK didn't retry for us, check retry on our own decisions
          // especially for non-standard AWS error reply
          if (error.GetErrorType() == Aws::S3::S3Errors::UNKNOWN &&
              error.GetResponseCode() ==
                  Aws::Http::HttpResponseCode::TOO_MANY_REQUESTS) {
            n_retry++;
          } else {
            // it's standard AWS error, let's stop retry immediately
            // and report accordingly to user
            n_retry = 3;
          }

          if (n_retry >= 3) {
            // amend the error msg on the last retry failure
            std::stringstream ss;
            reportS3ErrorDetailed(ss, temp_url, S3Operation::List, outcome)
                << std::endl;
            ret.error = ss.str();
            logstream(LOG_DEBUG)
                << "list_objects_impl failed:" << ret.error << std::endl;
          } else {
            // continue retry
            std::this_thread::sleep_for(std::chrono::milliseconds(backoff));
            backoff *= 2;
          }

        } else {
          // error.ShouldRetry() == true
          // AWS SDK already retried 3 times
          std::stringstream ss;
          reportS3ErrorDetailed(ss, temp_url, S3Operation::List, outcome)
              << std::endl;
          ret.error = ss.str();
          logstream(LOG_DEBUG)
              << "list_objects_impl failed:" << ret.error << std::endl;
          // no need to retry, just jump out all while loop
          break;
        }
      }
    } while (n_retry < 3);  // finished retry

  } while (moreResults && success);

  for (auto& dir : ret.directories) {
    s3url dirurl = parsed_url;
    dirurl.object_name = dir;
    // this is not necessary to override what returned by s3
    dir = dirurl.string_from_s3url();
  }
  for (auto& object : ret.objects) {
    s3url objurl = parsed_url;
    objurl.object_name = object;
    object = objurl.string_from_s3url();
  }

  return ret;
}

/// returns an error string on failure. Empty string on success
std::string delete_object_impl(const s3url& parsed_url, std::string proxy,
                               std::string endpoint) {
  // do not modify the parsed_url because string_from_s3url() will
  // be called on it to retrieve its original url (prefix) in is_directory.

  // let init_aws_sdk to be aware of the endpoint to override
  auto temp_url = parsed_url;

  if (temp_url.endpoint.empty()) {
    temp_url.endpoint = endpoint;
  }

  if (!temp_url.sdk_proxy || temp_url.sdk_proxy->empty()) {
    temp_url.sdk_proxy = proxy;
  }

  S3Client client = init_aws_sdk_with_turi_env(temp_url);

  std::string ret;

  Aws::S3::Model::DeleteObjectRequest request;
  request.WithBucket(parsed_url.bucket.c_str());
  request.WithKey(parsed_url.object_name.c_str());

  auto outcome = client.DeleteObject(request);
  if (!outcome.IsSuccess()) {
    std::stringstream ss;
    reportS3ErrorDetailed(ss, temp_url, S3Operation::Delete, outcome)
        << std::endl;
    ret = ss.str();
  }

  return ret;
}

/// returns an error string on failure. Empty string on success
std::string delete_prefix_impl(const s3url& parsed_url, std::string proxy,
                               std::string endpoint) {
  // do not modify the parsed_url because string_from_s3url() will
  // be called on it to retrieve its original url (prefix) in is_directory.

  // let init_aws_sdk to be aware of the endpoint to override
  auto temp_url = parsed_url;

  if (temp_url.endpoint.empty()) {
    temp_url.endpoint = endpoint;
  }

  if (!temp_url.sdk_proxy || temp_url.sdk_proxy->empty()) {
    temp_url.sdk_proxy = proxy;
  }

  S3Client client = init_aws_sdk_with_turi_env(temp_url);

  std::string ret;

  Aws::S3::Model::ListObjectsV2Request request;
  request.WithBucket(parsed_url.bucket.c_str());
  request.WithPrefix(parsed_url.object_name.c_str());

  // keep retrieving objects until no more objects match query
  bool moreResults = false;
  Aws::S3::Model::Delete deleteObjects;
  do {
    auto outcome = client.ListObjectsV2(request);
    if (outcome.IsSuccess()) {
      auto result = outcome.GetResult();

      // now iterate through found objects and construct DeleteObjects request
      // with them
      auto objects = result.GetContents();
      for (auto const& o : objects) {
        Aws::S3::Model::ObjectIdentifier key;
        deleteObjects.AddObjects(key.WithKey(o.GetKey()));
      }

      // more results to retrieve
      moreResults = result.GetIsTruncated();
      if (moreResults) {
        // add to the request object with continuation token
        request.WithContinuationToken(result.GetContinuationToken());
      }

    } else {
      std::stringstream ss;
      reportS3ErrorDetailed(ss, temp_url, S3Operation::List, outcome)
          << std::endl;
      ret = ss.str();
    }

  } while (moreResults);

  if (deleteObjects.GetObjects().size() > 0) {
    Aws::S3::Model::DeleteObjectsRequest delRequest;
    delRequest.WithBucket(parsed_url.bucket.c_str());
    delRequest.WithDelete(deleteObjects);

    auto outcome = client.DeleteObjects(delRequest);
    if (!outcome.IsSuccess()) {
      std::stringstream ss;
      reportS3ErrorDetailed(ss, parsed_url, S3Operation::Delete, outcome)
          << std::endl;
      ret = ss.str();
    }
  }

  return ret;
}

list_objects_response list_objects(std::string url, std::string proxy) {
  s3url parsed_url;
  list_objects_response ret;
  std::string err_msg;

  // in order not to reach the rate limit

  bool success = parse_s3url(url, parsed_url, err_msg);

  if (!success) {
    ret.error = err_msg;
    return ret;
  }

  logstream(LOG_DEBUG) << "list_obejcts: " << url << std::endl;

  size_t current_endpoint = 0;
  // try all endpoints
  auto endpoints = get_s3_endpoints();
  do {
    ret = list_objects_impl(parsed_url, proxy, endpoints[current_endpoint]);
    ++current_endpoint;
  } while (boost::algorithm::icontains(ret.error, "PermanentRedirect") &&
           current_endpoint < endpoints.size());

  return ret;
}

std::pair<file_status, list_objects_response> is_directory(std::string url,
                                                           std::string proxy) {
  s3url parsed_url;
  list_objects_response ret;
  std::string err_msg;
  bool success = parse_s3url(url, parsed_url, err_msg);
  if (!success) {
    ret.error = std::move(err_msg);
    return {file_status::MISSING, ret};
  }

  /* if there are no “/”‘s it is just a top level bucket
   * list_objects_impl will remove the ending ‘/’
   * e.g., dir/ -> dir
   * in turicreate convention, dir should not have ‘/’,
   * refer to dir_archive::init_for_read
   */
  // remove credentials
  url = parsed_url.string_from_s3url();
  logstream(LOG_DEBUG) << "compare on url: " << url << std::endl;
  if (url.length() > 5 && url.back() == '/') url.pop_back();

  list_objects_response response = list_objects(url, proxy);
  // an error occured
  if (!response.error.empty()) {
    return {file_status::MISSING, response};
  }

  // its a top level bucket name
  if (parsed_url.object_name.empty()) {
    return {file_status::DIRECTORY, response};
  }

  // is a directory
  for (auto dir : response.directories) {
    if (dir == url) {
      return {file_status::DIRECTORY, response};
    }
  }

  // is an object
  for (auto& object : response.objects) {
    if (object == url) {
      return {file_status::REGULAR_FILE, response};
    }
  }

  // is not found
  // s3 would be slient with list-objects if prefix doesn't exist
  if (response.error.empty()) {
    std::stringstream ss;
    ss << sanitize_url(url)
       << " has no objects or diretoires. Consider create the prefix and try "
          "again";

    response.error = ss.str();
  }

  return {file_status::MISSING, response};
}

list_objects_response list_directory(std::string url, std::string proxy) {
  s3url parsed_url;
  list_objects_response ret;
  std::string err_msg;
  bool success = parse_s3url(url, parsed_url, err_msg);
  if (!success) {
    ret.error = err_msg;
    return ret;
  }
  // normalize the URL so it doesn't matter if you put strange "/"s at the end
  url = parsed_url.string_from_s3url();
  auto isdir = is_directory(url, proxy);
  // if not found.
  if (isdir.first == file_status::MISSING) return isdir.second;
  // if its a directory
  if (isdir.first == file_status::DIRECTORY) {
    // if there are no "/"'s it is a top level bucket and we don't need
    // to mess with prefixes to get the contents
    if (!parsed_url.object_name.empty()) {
      parsed_url.object_name = parsed_url.object_name + "/";
    }
    size_t current_endpoint = 0;

    // try all endpoints
    auto endpoints = get_s3_endpoints();
    do {
      ret = list_objects_impl(parsed_url, proxy, endpoints[current_endpoint]);
      ++current_endpoint;
    } while (boost::algorithm::icontains(ret.error, "PermanentRedirect") &&
             current_endpoint < endpoints.size());
  } else {
    ret.objects.push_back(url);
  }

  return ret;
}

std::string delete_object(std::string url, std::string proxy) {
  s3url parsed_url;
  std::string err_msg;

  bool success = parse_s3url(url, parsed_url, err_msg);
  if (!success) {
    return err_msg;
  }
  // try all endpoints
  size_t current_endpoint = 0;
  auto endpoints = get_s3_endpoints();
  do {
    err_msg =
        delete_object_impl(parsed_url, proxy, endpoints[current_endpoint]);
    ++current_endpoint;
  } while (boost::algorithm::icontains(err_msg, "PermanentRedirect") &&
           current_endpoint < endpoints.size());

  return err_msg;
}

std::string delete_prefix(std::string url, std::string proxy) {
  s3url parsed_url;
  std::string err_msg;
  bool success = parse_s3url(url, parsed_url, err_msg);
  if (!success) {
    return err_msg;
  }
  // try all endpoints
  size_t current_endpoint = 0;
  auto endpoints = get_s3_endpoints();
  do {
    err_msg =
        delete_prefix_impl(parsed_url, proxy, endpoints[current_endpoint]);
    ++current_endpoint;
  } while (boost::algorithm::icontains(err_msg, "PermanentRedirect") &&
           current_endpoint < endpoints.size());

  return err_msg;
}

std::string sanitize_s3_url_aggressive(std::string url) {
  // must begin with s3://
  if (fileio::get_protocol(url) != "s3") {
    return url;
  }
  // strip the s3://
  url = url.substr(5);

  // strip the secret key and the access key following the usual rules.
  size_t splitpos = url.find(':');
  if (splitpos != std::string::npos) url = url.substr(splitpos + 1);
  splitpos = url.find(':');
  if (splitpos != std::string::npos) url = url.substr(splitpos + 1);

  // now, a user error is possible where ":" shows up inside the
  // secret key / access key thus leaking part of a key in the logs.
  // so we also perform a more aggressive truncation.
  // find the first "/" and delete everything up to the last ":"
  // before the first "/"
  size_t bucketend = url.find('/');
  if (bucketend == std::string::npos) bucketend = url.length();
  size_t last_colon = url.find_last_of(':', bucketend);
  if (last_colon != std::string::npos) url = url.substr(last_colon + 1);
  return "s3://" + url;
}

std::string sanitize_s3_url(const std::string& url) {
  s3url parsed_url;
  std::string err_msg;
  auto ret = parse_s3url(url, parsed_url, err_msg);
  DASSERT_EQ(ret, err_msg.empty());
  if (ret) {
    if (parsed_url.endpoint.empty())
      return "s3://" + parsed_url.bucket + "/" + parsed_url.object_name;
    else
      return "s3://" + parsed_url.endpoint + "/" + parsed_url.bucket + "/" +
             parsed_url.object_name;
  } else {
    return sanitize_s3_url_aggressive(url);
  };
}

std::string get_s3_file_last_modified(const std::string& url) {
  list_objects_response response = list_objects(url);
  if (response.error.empty() && response.objects_last_modified.size() == 1) {
    return response.objects_last_modified[0];
  } else if (!response.error.empty()) {
    logstream(LOG_WARNING) << "List object error: " << response.error << " "
                           << __FILE__ << " at " << __LINE__ << std::endl;
    throw(response.error);
  }
  return "";
}

}  // namespace turi

#endif
