// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "message.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
// @@protoc_insertion_point(includes)

namespace TuriCreate {
namespace Annotation {
namespace Specification {
class ParcelDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<Parcel> {
  public:
  const ::TuriCreate::Annotation::Specification::Annotations* annotations_;
  const ::TuriCreate::Annotation::Specification::Data* data_;
  const ::TuriCreate::Annotation::Specification::MetaData* metadata_;
  const ::TuriCreate::Annotation::Specification::ProgressMeta* progress_;
  const ::TuriCreate::Annotation::Specification::Similarity* similarity_;
} _Parcel_default_instance_;
class ClientRequestDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<ClientRequest> {
  public:
  const ::TuriCreate::Annotation::Specification::DataGetter* getter_;
  const ::TuriCreate::Annotation::Specification::Annotations* annotations_;
} _ClientRequest_default_instance_;

namespace protobuf_message_2eproto {

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTableField
    const TableStruct::entries[] = {
  {0, 0, 0, ::google::protobuf::internal::kInvalidMask, 0, 0},
};

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::AuxillaryParseTableField
    const TableStruct::aux[] = {
  ::google::protobuf::internal::AuxillaryParseTableField(),
};
PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTable const
    TableStruct::schema[] = {
  { NULL, NULL, 0, -1, -1, false },
  { NULL, NULL, 0, -1, -1, false },
};


void TableStruct::Shutdown() {
  _Parcel_default_instance_.Shutdown();
  _ClientRequest_default_instance_.Shutdown();
}

void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  ::TuriCreate::Annotation::Specification::protobuf_annotate_2eproto::InitDefaults();
  ::TuriCreate::Annotation::Specification::protobuf_data_2eproto::InitDefaults();
  ::TuriCreate::Annotation::Specification::protobuf_meta_2eproto::InitDefaults();
  ::TuriCreate::Annotation::Specification::protobuf_progress_2eproto::InitDefaults();
  ::TuriCreate::Annotation::Specification::protobuf_similarity_2eproto::InitDefaults();
  _Parcel_default_instance_.DefaultConstruct();
  _ClientRequest_default_instance_.DefaultConstruct();
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
void AddDescriptorsImpl() {
  InitDefaults();
  ::TuriCreate::Annotation::Specification::protobuf_annotate_2eproto::AddDescriptors();
  ::TuriCreate::Annotation::Specification::protobuf_data_2eproto::AddDescriptors();
  ::TuriCreate::Annotation::Specification::protobuf_meta_2eproto::AddDescriptors();
  ::TuriCreate::Annotation::Specification::protobuf_progress_2eproto::AddDescriptors();
  ::TuriCreate::Annotation::Specification::protobuf_similarity_2eproto::AddDescriptors();
  ::google::protobuf::internal::OnShutdown(&TableStruct::Shutdown);
}

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
#endif  // GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER

}  // namespace protobuf_message_2eproto


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Parcel::kAnnotationsFieldNumber;
const int Parcel::kDataFieldNumber;
const int Parcel::kMetadataFieldNumber;
const int Parcel::kProgressFieldNumber;
const int Parcel::kSimilarityFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Parcel::Parcel()
  : ::google::protobuf::MessageLite(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_message_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:TuriCreate.Annotation.Specification.Parcel)
}
Parcel::Parcel(const Parcel& from)
  : ::google::protobuf::MessageLite(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  clear_has_Message();
  switch (from.Message_case()) {
    case kAnnotations: {
      mutable_annotations()->::TuriCreate::Annotation::Specification::Annotations::MergeFrom(from.annotations());
      break;
    }
    case kData: {
      mutable_data()->::TuriCreate::Annotation::Specification::Data::MergeFrom(from.data());
      break;
    }
    case kMetadata: {
      mutable_metadata()->::TuriCreate::Annotation::Specification::MetaData::MergeFrom(from.metadata());
      break;
    }
    case kProgress: {
      mutable_progress()->::TuriCreate::Annotation::Specification::ProgressMeta::MergeFrom(from.progress());
      break;
    }
    case kSimilarity: {
      mutable_similarity()->::TuriCreate::Annotation::Specification::Similarity::MergeFrom(from.similarity());
      break;
    }
    case MESSAGE_NOT_SET: {
      break;
    }
  }
  // @@protoc_insertion_point(copy_constructor:TuriCreate.Annotation.Specification.Parcel)
}

void Parcel::SharedCtor() {
  clear_has_Message();
  _cached_size_ = 0;
}

Parcel::~Parcel() {
  // @@protoc_insertion_point(destructor:TuriCreate.Annotation.Specification.Parcel)
  SharedDtor();
}

void Parcel::SharedDtor() {
  if (has_Message()) {
    clear_Message();
  }
}

void Parcel::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const Parcel& Parcel::default_instance() {
  protobuf_message_2eproto::InitDefaults();
  return *internal_default_instance();
}

Parcel* Parcel::New(::google::protobuf::Arena* arena) const {
  Parcel* n = new Parcel;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Parcel::clear_Message() {
// @@protoc_insertion_point(one_of_clear_start:TuriCreate.Annotation.Specification.Parcel)
  switch (Message_case()) {
    case kAnnotations: {
      delete Message_.annotations_;
      break;
    }
    case kData: {
      delete Message_.data_;
      break;
    }
    case kMetadata: {
      delete Message_.metadata_;
      break;
    }
    case kProgress: {
      delete Message_.progress_;
      break;
    }
    case kSimilarity: {
      delete Message_.similarity_;
      break;
    }
    case MESSAGE_NOT_SET: {
      break;
    }
  }
  _oneof_case_[0] = MESSAGE_NOT_SET;
}


void Parcel::Clear() {
// @@protoc_insertion_point(message_clear_start:TuriCreate.Annotation.Specification.Parcel)
  clear_Message();
}

bool Parcel::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:TuriCreate.Annotation.Specification.Parcel)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // .TuriCreate.Annotation.Specification.Annotations annotations = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_annotations()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // .TuriCreate.Annotation.Specification.Data data = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_data()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // .TuriCreate.Annotation.Specification.MetaData metadata = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(26u)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_metadata()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // .TuriCreate.Annotation.Specification.ProgressMeta progress = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(34u)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_progress()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // .TuriCreate.Annotation.Specification.Similarity similarity = 5;
      case 5: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(42u)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_similarity()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:TuriCreate.Annotation.Specification.Parcel)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:TuriCreate.Annotation.Specification.Parcel)
  return false;
#undef DO_
}

void Parcel::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:TuriCreate.Annotation.Specification.Parcel)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .TuriCreate.Annotation.Specification.Annotations annotations = 1;
  if (has_annotations()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      1, *Message_.annotations_, output);
  }

  // .TuriCreate.Annotation.Specification.Data data = 2;
  if (has_data()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      2, *Message_.data_, output);
  }

  // .TuriCreate.Annotation.Specification.MetaData metadata = 3;
  if (has_metadata()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      3, *Message_.metadata_, output);
  }

  // .TuriCreate.Annotation.Specification.ProgressMeta progress = 4;
  if (has_progress()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      4, *Message_.progress_, output);
  }

  // .TuriCreate.Annotation.Specification.Similarity similarity = 5;
  if (has_similarity()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      5, *Message_.similarity_, output);
  }

  // @@protoc_insertion_point(serialize_end:TuriCreate.Annotation.Specification.Parcel)
}

size_t Parcel::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:TuriCreate.Annotation.Specification.Parcel)
  size_t total_size = 0;

  switch (Message_case()) {
    // .TuriCreate.Annotation.Specification.Annotations annotations = 1;
    case kAnnotations: {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          *Message_.annotations_);
      break;
    }
    // .TuriCreate.Annotation.Specification.Data data = 2;
    case kData: {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          *Message_.data_);
      break;
    }
    // .TuriCreate.Annotation.Specification.MetaData metadata = 3;
    case kMetadata: {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          *Message_.metadata_);
      break;
    }
    // .TuriCreate.Annotation.Specification.ProgressMeta progress = 4;
    case kProgress: {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          *Message_.progress_);
      break;
    }
    // .TuriCreate.Annotation.Specification.Similarity similarity = 5;
    case kSimilarity: {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          *Message_.similarity_);
      break;
    }
    case MESSAGE_NOT_SET: {
      break;
    }
  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Parcel::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const Parcel*>(&from));
}

void Parcel::MergeFrom(const Parcel& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:TuriCreate.Annotation.Specification.Parcel)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  switch (from.Message_case()) {
    case kAnnotations: {
      mutable_annotations()->::TuriCreate::Annotation::Specification::Annotations::MergeFrom(from.annotations());
      break;
    }
    case kData: {
      mutable_data()->::TuriCreate::Annotation::Specification::Data::MergeFrom(from.data());
      break;
    }
    case kMetadata: {
      mutable_metadata()->::TuriCreate::Annotation::Specification::MetaData::MergeFrom(from.metadata());
      break;
    }
    case kProgress: {
      mutable_progress()->::TuriCreate::Annotation::Specification::ProgressMeta::MergeFrom(from.progress());
      break;
    }
    case kSimilarity: {
      mutable_similarity()->::TuriCreate::Annotation::Specification::Similarity::MergeFrom(from.similarity());
      break;
    }
    case MESSAGE_NOT_SET: {
      break;
    }
  }
}

void Parcel::CopyFrom(const Parcel& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:TuriCreate.Annotation.Specification.Parcel)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Parcel::IsInitialized() const {
  return true;
}

void Parcel::Swap(Parcel* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Parcel::InternalSwap(Parcel* other) {
  std::swap(Message_, other->Message_);
  std::swap(_oneof_case_[0], other->_oneof_case_[0]);
  std::swap(_cached_size_, other->_cached_size_);
}

::std::string Parcel::GetTypeName() const {
  return "TuriCreate.Annotation.Specification.Parcel";
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Parcel

// .TuriCreate.Annotation.Specification.Annotations annotations = 1;
bool Parcel::has_annotations() const {
  return Message_case() == kAnnotations;
}
void Parcel::set_has_annotations() {
  _oneof_case_[0] = kAnnotations;
}
void Parcel::clear_annotations() {
  if (has_annotations()) {
    delete Message_.annotations_;
    clear_has_Message();
  }
}
 const ::TuriCreate::Annotation::Specification::Annotations& Parcel::annotations() const {
  // @@protoc_insertion_point(field_get:TuriCreate.Annotation.Specification.Parcel.annotations)
  return has_annotations()
      ? *Message_.annotations_
      : ::TuriCreate::Annotation::Specification::Annotations::default_instance();
}
::TuriCreate::Annotation::Specification::Annotations* Parcel::mutable_annotations() {
  if (!has_annotations()) {
    clear_Message();
    set_has_annotations();
    Message_.annotations_ = new ::TuriCreate::Annotation::Specification::Annotations;
  }
  // @@protoc_insertion_point(field_mutable:TuriCreate.Annotation.Specification.Parcel.annotations)
  return Message_.annotations_;
}
::TuriCreate::Annotation::Specification::Annotations* Parcel::release_annotations() {
  // @@protoc_insertion_point(field_release:TuriCreate.Annotation.Specification.Parcel.annotations)
  if (has_annotations()) {
    clear_has_Message();
    ::TuriCreate::Annotation::Specification::Annotations* temp = Message_.annotations_;
    Message_.annotations_ = NULL;
    return temp;
  } else {
    return NULL;
  }
}
void Parcel::set_allocated_annotations(::TuriCreate::Annotation::Specification::Annotations* annotations) {
  clear_Message();
  if (annotations) {
    set_has_annotations();
    Message_.annotations_ = annotations;
  }
  // @@protoc_insertion_point(field_set_allocated:TuriCreate.Annotation.Specification.Parcel.annotations)
}

// .TuriCreate.Annotation.Specification.Data data = 2;
bool Parcel::has_data() const {
  return Message_case() == kData;
}
void Parcel::set_has_data() {
  _oneof_case_[0] = kData;
}
void Parcel::clear_data() {
  if (has_data()) {
    delete Message_.data_;
    clear_has_Message();
  }
}
 const ::TuriCreate::Annotation::Specification::Data& Parcel::data() const {
  // @@protoc_insertion_point(field_get:TuriCreate.Annotation.Specification.Parcel.data)
  return has_data()
      ? *Message_.data_
      : ::TuriCreate::Annotation::Specification::Data::default_instance();
}
::TuriCreate::Annotation::Specification::Data* Parcel::mutable_data() {
  if (!has_data()) {
    clear_Message();
    set_has_data();
    Message_.data_ = new ::TuriCreate::Annotation::Specification::Data;
  }
  // @@protoc_insertion_point(field_mutable:TuriCreate.Annotation.Specification.Parcel.data)
  return Message_.data_;
}
::TuriCreate::Annotation::Specification::Data* Parcel::release_data() {
  // @@protoc_insertion_point(field_release:TuriCreate.Annotation.Specification.Parcel.data)
  if (has_data()) {
    clear_has_Message();
    ::TuriCreate::Annotation::Specification::Data* temp = Message_.data_;
    Message_.data_ = NULL;
    return temp;
  } else {
    return NULL;
  }
}
void Parcel::set_allocated_data(::TuriCreate::Annotation::Specification::Data* data) {
  clear_Message();
  if (data) {
    set_has_data();
    Message_.data_ = data;
  }
  // @@protoc_insertion_point(field_set_allocated:TuriCreate.Annotation.Specification.Parcel.data)
}

// .TuriCreate.Annotation.Specification.MetaData metadata = 3;
bool Parcel::has_metadata() const {
  return Message_case() == kMetadata;
}
void Parcel::set_has_metadata() {
  _oneof_case_[0] = kMetadata;
}
void Parcel::clear_metadata() {
  if (has_metadata()) {
    delete Message_.metadata_;
    clear_has_Message();
  }
}
 const ::TuriCreate::Annotation::Specification::MetaData& Parcel::metadata() const {
  // @@protoc_insertion_point(field_get:TuriCreate.Annotation.Specification.Parcel.metadata)
  return has_metadata()
      ? *Message_.metadata_
      : ::TuriCreate::Annotation::Specification::MetaData::default_instance();
}
::TuriCreate::Annotation::Specification::MetaData* Parcel::mutable_metadata() {
  if (!has_metadata()) {
    clear_Message();
    set_has_metadata();
    Message_.metadata_ = new ::TuriCreate::Annotation::Specification::MetaData;
  }
  // @@protoc_insertion_point(field_mutable:TuriCreate.Annotation.Specification.Parcel.metadata)
  return Message_.metadata_;
}
::TuriCreate::Annotation::Specification::MetaData* Parcel::release_metadata() {
  // @@protoc_insertion_point(field_release:TuriCreate.Annotation.Specification.Parcel.metadata)
  if (has_metadata()) {
    clear_has_Message();
    ::TuriCreate::Annotation::Specification::MetaData* temp = Message_.metadata_;
    Message_.metadata_ = NULL;
    return temp;
  } else {
    return NULL;
  }
}
void Parcel::set_allocated_metadata(::TuriCreate::Annotation::Specification::MetaData* metadata) {
  clear_Message();
  if (metadata) {
    set_has_metadata();
    Message_.metadata_ = metadata;
  }
  // @@protoc_insertion_point(field_set_allocated:TuriCreate.Annotation.Specification.Parcel.metadata)
}

// .TuriCreate.Annotation.Specification.ProgressMeta progress = 4;
bool Parcel::has_progress() const {
  return Message_case() == kProgress;
}
void Parcel::set_has_progress() {
  _oneof_case_[0] = kProgress;
}
void Parcel::clear_progress() {
  if (has_progress()) {
    delete Message_.progress_;
    clear_has_Message();
  }
}
 const ::TuriCreate::Annotation::Specification::ProgressMeta& Parcel::progress() const {
  // @@protoc_insertion_point(field_get:TuriCreate.Annotation.Specification.Parcel.progress)
  return has_progress()
      ? *Message_.progress_
      : ::TuriCreate::Annotation::Specification::ProgressMeta::default_instance();
}
::TuriCreate::Annotation::Specification::ProgressMeta* Parcel::mutable_progress() {
  if (!has_progress()) {
    clear_Message();
    set_has_progress();
    Message_.progress_ = new ::TuriCreate::Annotation::Specification::ProgressMeta;
  }
  // @@protoc_insertion_point(field_mutable:TuriCreate.Annotation.Specification.Parcel.progress)
  return Message_.progress_;
}
::TuriCreate::Annotation::Specification::ProgressMeta* Parcel::release_progress() {
  // @@protoc_insertion_point(field_release:TuriCreate.Annotation.Specification.Parcel.progress)
  if (has_progress()) {
    clear_has_Message();
    ::TuriCreate::Annotation::Specification::ProgressMeta* temp = Message_.progress_;
    Message_.progress_ = NULL;
    return temp;
  } else {
    return NULL;
  }
}
void Parcel::set_allocated_progress(::TuriCreate::Annotation::Specification::ProgressMeta* progress) {
  clear_Message();
  if (progress) {
    set_has_progress();
    Message_.progress_ = progress;
  }
  // @@protoc_insertion_point(field_set_allocated:TuriCreate.Annotation.Specification.Parcel.progress)
}

// .TuriCreate.Annotation.Specification.Similarity similarity = 5;
bool Parcel::has_similarity() const {
  return Message_case() == kSimilarity;
}
void Parcel::set_has_similarity() {
  _oneof_case_[0] = kSimilarity;
}
void Parcel::clear_similarity() {
  if (has_similarity()) {
    delete Message_.similarity_;
    clear_has_Message();
  }
}
 const ::TuriCreate::Annotation::Specification::Similarity& Parcel::similarity() const {
  // @@protoc_insertion_point(field_get:TuriCreate.Annotation.Specification.Parcel.similarity)
  return has_similarity()
      ? *Message_.similarity_
      : ::TuriCreate::Annotation::Specification::Similarity::default_instance();
}
::TuriCreate::Annotation::Specification::Similarity* Parcel::mutable_similarity() {
  if (!has_similarity()) {
    clear_Message();
    set_has_similarity();
    Message_.similarity_ = new ::TuriCreate::Annotation::Specification::Similarity;
  }
  // @@protoc_insertion_point(field_mutable:TuriCreate.Annotation.Specification.Parcel.similarity)
  return Message_.similarity_;
}
::TuriCreate::Annotation::Specification::Similarity* Parcel::release_similarity() {
  // @@protoc_insertion_point(field_release:TuriCreate.Annotation.Specification.Parcel.similarity)
  if (has_similarity()) {
    clear_has_Message();
    ::TuriCreate::Annotation::Specification::Similarity* temp = Message_.similarity_;
    Message_.similarity_ = NULL;
    return temp;
  } else {
    return NULL;
  }
}
void Parcel::set_allocated_similarity(::TuriCreate::Annotation::Specification::Similarity* similarity) {
  clear_Message();
  if (similarity) {
    set_has_similarity();
    Message_.similarity_ = similarity;
  }
  // @@protoc_insertion_point(field_set_allocated:TuriCreate.Annotation.Specification.Parcel.similarity)
}

bool Parcel::has_Message() const {
  return Message_case() != MESSAGE_NOT_SET;
}
void Parcel::clear_has_Message() {
  _oneof_case_[0] = MESSAGE_NOT_SET;
}
Parcel::MessageCase Parcel::Message_case() const {
  return Parcel::MessageCase(_oneof_case_[0]);
}
#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ClientRequest::kGetterFieldNumber;
const int ClientRequest::kAnnotationsFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

ClientRequest::ClientRequest()
  : ::google::protobuf::MessageLite(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_message_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:TuriCreate.Annotation.Specification.ClientRequest)
}
ClientRequest::ClientRequest(const ClientRequest& from)
  : ::google::protobuf::MessageLite(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  clear_has_Type();
  switch (from.Type_case()) {
    case kGetter: {
      mutable_getter()->::TuriCreate::Annotation::Specification::DataGetter::MergeFrom(from.getter());
      break;
    }
    case kAnnotations: {
      mutable_annotations()->::TuriCreate::Annotation::Specification::Annotations::MergeFrom(from.annotations());
      break;
    }
    case TYPE_NOT_SET: {
      break;
    }
  }
  // @@protoc_insertion_point(copy_constructor:TuriCreate.Annotation.Specification.ClientRequest)
}

void ClientRequest::SharedCtor() {
  clear_has_Type();
  _cached_size_ = 0;
}

ClientRequest::~ClientRequest() {
  // @@protoc_insertion_point(destructor:TuriCreate.Annotation.Specification.ClientRequest)
  SharedDtor();
}

void ClientRequest::SharedDtor() {
  if (has_Type()) {
    clear_Type();
  }
}

void ClientRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ClientRequest& ClientRequest::default_instance() {
  protobuf_message_2eproto::InitDefaults();
  return *internal_default_instance();
}

ClientRequest* ClientRequest::New(::google::protobuf::Arena* arena) const {
  ClientRequest* n = new ClientRequest;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void ClientRequest::clear_Type() {
// @@protoc_insertion_point(one_of_clear_start:TuriCreate.Annotation.Specification.ClientRequest)
  switch (Type_case()) {
    case kGetter: {
      delete Type_.getter_;
      break;
    }
    case kAnnotations: {
      delete Type_.annotations_;
      break;
    }
    case TYPE_NOT_SET: {
      break;
    }
  }
  _oneof_case_[0] = TYPE_NOT_SET;
}


void ClientRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:TuriCreate.Annotation.Specification.ClientRequest)
  clear_Type();
}

bool ClientRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:TuriCreate.Annotation.Specification.ClientRequest)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // .TuriCreate.Annotation.Specification.DataGetter getter = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_getter()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // .TuriCreate.Annotation.Specification.Annotations annotations = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_annotations()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:TuriCreate.Annotation.Specification.ClientRequest)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:TuriCreate.Annotation.Specification.ClientRequest)
  return false;
#undef DO_
}

void ClientRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:TuriCreate.Annotation.Specification.ClientRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .TuriCreate.Annotation.Specification.DataGetter getter = 1;
  if (has_getter()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      1, *Type_.getter_, output);
  }

  // .TuriCreate.Annotation.Specification.Annotations annotations = 2;
  if (has_annotations()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessage(
      2, *Type_.annotations_, output);
  }

  // @@protoc_insertion_point(serialize_end:TuriCreate.Annotation.Specification.ClientRequest)
}

size_t ClientRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:TuriCreate.Annotation.Specification.ClientRequest)
  size_t total_size = 0;

  switch (Type_case()) {
    // .TuriCreate.Annotation.Specification.DataGetter getter = 1;
    case kGetter: {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          *Type_.getter_);
      break;
    }
    // .TuriCreate.Annotation.Specification.Annotations annotations = 2;
    case kAnnotations: {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          *Type_.annotations_);
      break;
    }
    case TYPE_NOT_SET: {
      break;
    }
  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ClientRequest::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const ClientRequest*>(&from));
}

void ClientRequest::MergeFrom(const ClientRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:TuriCreate.Annotation.Specification.ClientRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  switch (from.Type_case()) {
    case kGetter: {
      mutable_getter()->::TuriCreate::Annotation::Specification::DataGetter::MergeFrom(from.getter());
      break;
    }
    case kAnnotations: {
      mutable_annotations()->::TuriCreate::Annotation::Specification::Annotations::MergeFrom(from.annotations());
      break;
    }
    case TYPE_NOT_SET: {
      break;
    }
  }
}

void ClientRequest::CopyFrom(const ClientRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:TuriCreate.Annotation.Specification.ClientRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ClientRequest::IsInitialized() const {
  return true;
}

void ClientRequest::Swap(ClientRequest* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ClientRequest::InternalSwap(ClientRequest* other) {
  std::swap(Type_, other->Type_);
  std::swap(_oneof_case_[0], other->_oneof_case_[0]);
  std::swap(_cached_size_, other->_cached_size_);
}

::std::string ClientRequest::GetTypeName() const {
  return "TuriCreate.Annotation.Specification.ClientRequest";
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// ClientRequest

// .TuriCreate.Annotation.Specification.DataGetter getter = 1;
bool ClientRequest::has_getter() const {
  return Type_case() == kGetter;
}
void ClientRequest::set_has_getter() {
  _oneof_case_[0] = kGetter;
}
void ClientRequest::clear_getter() {
  if (has_getter()) {
    delete Type_.getter_;
    clear_has_Type();
  }
}
 const ::TuriCreate::Annotation::Specification::DataGetter& ClientRequest::getter() const {
  // @@protoc_insertion_point(field_get:TuriCreate.Annotation.Specification.ClientRequest.getter)
  return has_getter()
      ? *Type_.getter_
      : ::TuriCreate::Annotation::Specification::DataGetter::default_instance();
}
::TuriCreate::Annotation::Specification::DataGetter* ClientRequest::mutable_getter() {
  if (!has_getter()) {
    clear_Type();
    set_has_getter();
    Type_.getter_ = new ::TuriCreate::Annotation::Specification::DataGetter;
  }
  // @@protoc_insertion_point(field_mutable:TuriCreate.Annotation.Specification.ClientRequest.getter)
  return Type_.getter_;
}
::TuriCreate::Annotation::Specification::DataGetter* ClientRequest::release_getter() {
  // @@protoc_insertion_point(field_release:TuriCreate.Annotation.Specification.ClientRequest.getter)
  if (has_getter()) {
    clear_has_Type();
    ::TuriCreate::Annotation::Specification::DataGetter* temp = Type_.getter_;
    Type_.getter_ = NULL;
    return temp;
  } else {
    return NULL;
  }
}
void ClientRequest::set_allocated_getter(::TuriCreate::Annotation::Specification::DataGetter* getter) {
  clear_Type();
  if (getter) {
    set_has_getter();
    Type_.getter_ = getter;
  }
  // @@protoc_insertion_point(field_set_allocated:TuriCreate.Annotation.Specification.ClientRequest.getter)
}

// .TuriCreate.Annotation.Specification.Annotations annotations = 2;
bool ClientRequest::has_annotations() const {
  return Type_case() == kAnnotations;
}
void ClientRequest::set_has_annotations() {
  _oneof_case_[0] = kAnnotations;
}
void ClientRequest::clear_annotations() {
  if (has_annotations()) {
    delete Type_.annotations_;
    clear_has_Type();
  }
}
 const ::TuriCreate::Annotation::Specification::Annotations& ClientRequest::annotations() const {
  // @@protoc_insertion_point(field_get:TuriCreate.Annotation.Specification.ClientRequest.annotations)
  return has_annotations()
      ? *Type_.annotations_
      : ::TuriCreate::Annotation::Specification::Annotations::default_instance();
}
::TuriCreate::Annotation::Specification::Annotations* ClientRequest::mutable_annotations() {
  if (!has_annotations()) {
    clear_Type();
    set_has_annotations();
    Type_.annotations_ = new ::TuriCreate::Annotation::Specification::Annotations;
  }
  // @@protoc_insertion_point(field_mutable:TuriCreate.Annotation.Specification.ClientRequest.annotations)
  return Type_.annotations_;
}
::TuriCreate::Annotation::Specification::Annotations* ClientRequest::release_annotations() {
  // @@protoc_insertion_point(field_release:TuriCreate.Annotation.Specification.ClientRequest.annotations)
  if (has_annotations()) {
    clear_has_Type();
    ::TuriCreate::Annotation::Specification::Annotations* temp = Type_.annotations_;
    Type_.annotations_ = NULL;
    return temp;
  } else {
    return NULL;
  }
}
void ClientRequest::set_allocated_annotations(::TuriCreate::Annotation::Specification::Annotations* annotations) {
  clear_Type();
  if (annotations) {
    set_has_annotations();
    Type_.annotations_ = annotations;
  }
  // @@protoc_insertion_point(field_set_allocated:TuriCreate.Annotation.Specification.ClientRequest.annotations)
}

bool ClientRequest::has_Type() const {
  return Type_case() != TYPE_NOT_SET;
}
void ClientRequest::clear_has_Type() {
  _oneof_case_[0] = TYPE_NOT_SET;
}
ClientRequest::TypeCase ClientRequest::Type_case() const {
  return ClientRequest::TypeCase(_oneof_case_[0]);
}
#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace Specification
}  // namespace Annotation
}  // namespace TuriCreate

// @@protoc_insertion_point(global_scope)
