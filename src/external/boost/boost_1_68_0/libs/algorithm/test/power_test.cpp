/*
   Copyright (c) Marshall Clow 2014.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    For more information, see http://www.boost.org
*/

#include <iostream>
#include <functional>

#include <boost/config.hpp>
#include <boost/algorithm/algorithm.hpp>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

namespace ba = boost::algorithm;

void test_power ()
{
    BOOST_CHECK ( ba::power(0, 0) == 1);
    BOOST_CHECK ( ba::power(5, 0) == 1);
    BOOST_CHECK ( ba::power(1, 1) == 1);
    BOOST_CHECK ( ba::power(1, 4) == 1);
    BOOST_CHECK ( ba::power(3, 2) == 9);
    BOOST_CHECK ( ba::power(2, 3) == 8);
    BOOST_CHECK ( ba::power(3, 3) == 27);
    BOOST_CHECK ( ba::power(2, 30) == 0x40000000);
    BOOST_CHECK ( ba::power(5L, 10) == 3125*3125);
    BOOST_CHECK ( ba::power(18, 3) == 18*18*18);

    BOOST_CHECK ( ba::power(3,2) == ba::power(3,2, std::multiplies<int>()));
    BOOST_CHECK ( ba::power(3,2, std::plus<int>()) == 6);
}


void test_power_constexpr ()
{
    BOOST_CXX14_CONSTEXPR bool check_zero_power1 =
        ba::power(0, 0) == 1;
    BOOST_CHECK(check_zero_power1);
    BOOST_CXX14_CONSTEXPR bool check_zero_power2 =
        ba::power(5, 0) == 1;
    BOOST_CHECK(check_zero_power2);
    BOOST_CXX14_CONSTEXPR bool check_one_base1 =
        ba::power(1, 1) == 1;
    BOOST_CHECK(check_one_base1);
    BOOST_CXX14_CONSTEXPR bool check_one_base2 =
        ba::power(1, 4) == 1;
    BOOST_CHECK(check_one_base2);
    BOOST_CXX14_CONSTEXPR bool check_power1 =
        ba::power(3, 2) == 9;
    BOOST_CHECK(check_power1);
    BOOST_CXX14_CONSTEXPR bool check_power2 =
        ba::power(2, 3) == 8;
    BOOST_CHECK(check_power2);
    BOOST_CXX14_CONSTEXPR bool check_power3 =
        ba::power(3, 3) == 27;
    BOOST_CHECK(check_power3);
    BOOST_CXX14_CONSTEXPR bool check_power4 =
        ba::power(2, 30) == 0x40000000;
    BOOST_CHECK(check_power4);
    BOOST_CXX14_CONSTEXPR bool check_power5 =
        ba::power(5L, 10) == 3125*3125;
    BOOST_CHECK(check_power5);
    BOOST_CXX14_CONSTEXPR bool check_power6 =
        ba::power(18, 3) == 18*18*18;
    BOOST_CHECK(check_power6);

    BOOST_CXX14_CONSTEXPR bool check_multiple =
        ba::power(3, 2, std::multiplies<int>()) == ba::power(3, 2);
    BOOST_CHECK(check_multiple);
    BOOST_CXX14_CONSTEXPR bool check_plus =
        ba::power(3, 2, std::plus<int>()) == 6;
    BOOST_CHECK(check_plus);
}


BOOST_AUTO_TEST_CASE( test_main ) {
  test_power ();
  test_power_constexpr ();
}
