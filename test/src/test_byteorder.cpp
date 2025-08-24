// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: Byte order conversion functions.

// C++ standard library
#include <cstdlib>
#include <cstring>

// C++ user library
#include "byteorder.h"
#include "byteorder.hpp"
#include "unittest.hpp"

namespace {

// C++ user library
using namespace cun::byteorder;
using cun::UnitTest;

template <typename UnionT>
struct test_data_t final {
    UnionT native;
    UnionT be;
    UnionT le;
};

constexpr test_data_t<union16_t> TEST_DATA_16 {
    .native = { .u = static_cast<uint16_t>(0xAA'BBu) },
    .be = { .b = {
        static_cast<uint8_t>(0xAAu),
        static_cast<uint8_t>(0xBBu),
    }},
    .le = { .b = {
        static_cast<uint8_t>(0xBBu),
        static_cast<uint8_t>(0xAAu),
    }},
};

constexpr test_data_t<union32_t> TEST_DATA_32 {
    .native = { .u = static_cast<uint32_t>(0xAA'BB'CC'DDul) },
    .be = { .b = {
        static_cast<uint8_t>(0xAAu),
        static_cast<uint8_t>(0xBBu),
        static_cast<uint8_t>(0xCCu),
        static_cast<uint8_t>(0xDDu),
    }},
    .le = { .b = {
        static_cast<uint8_t>(0xDDu),
        static_cast<uint8_t>(0xCCu),
        static_cast<uint8_t>(0xBBu),
        static_cast<uint8_t>(0xAAu),
    }},
};

constexpr test_data_t<union64_t> TEST_DATA_64 {
    .native = { .u = static_cast<uint64_t>(0x01'23'45'67'89'AB'CD'EFull) },
    .be = { .b = {
        static_cast<uint8_t>(0x01u),
        static_cast<uint8_t>(0x23u),
        static_cast<uint8_t>(0x45u),
        static_cast<uint8_t>(0x67u),
        static_cast<uint8_t>(0x89u),
        static_cast<uint8_t>(0xABu),
        static_cast<uint8_t>(0xCDu),
        static_cast<uint8_t>(0xEFu),
    }},
    .le = { .b = {
        static_cast<uint8_t>(0xEFu),
        static_cast<uint8_t>(0xCDu),
        static_cast<uint8_t>(0xABu),
        static_cast<uint8_t>(0x89u),
        static_cast<uint8_t>(0x67u),
        static_cast<uint8_t>(0x45u),
        static_cast<uint8_t>(0x23u),
        static_cast<uint8_t>(0x01u),
    }},
};

void test_union_t(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Byte order conversion functions - union??_t.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EVAL(ut, sizeof(union16_t) == 2);
    CUN_UNITTEST_EVAL(ut, sizeof(union32_t) == 4);
    CUN_UNITTEST_EVAL(ut, sizeof(union64_t) == 8);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_to_big(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Byte order conversion functions - to_big.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "Core functions.");
    CUN_UNITTEST_EVAL(ut, to_big(TEST_DATA_16.native).u == TEST_DATA_16.be.u);
    CUN_UNITTEST_EVAL(ut, to_big(TEST_DATA_32.native).u == TEST_DATA_32.be.u);
    CUN_UNITTEST_EVAL(ut, to_big(TEST_DATA_64.native).u == TEST_DATA_64.be.u);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "16bit primitive data types.");
    CUN_UNITTEST_EVAL(ut, to_big(TEST_DATA_16.native.i) == TEST_DATA_16.be.i);
    CUN_UNITTEST_EVAL(ut, to_big(TEST_DATA_16.native.u) == TEST_DATA_16.be.u);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "32bit primitive data types.");
    CUN_UNITTEST_EVAL(ut, to_big(TEST_DATA_32.native.i) == TEST_DATA_32.be.i);
    CUN_UNITTEST_EVAL(ut, to_big(TEST_DATA_32.native.u) == TEST_DATA_32.be.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = to_big(TEST_DATA_32.native.f));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_32.be.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "64bit primitive data types.");
    CUN_UNITTEST_EVAL(ut, to_big(TEST_DATA_64.native.i) == TEST_DATA_64.be.i);
    CUN_UNITTEST_EVAL(ut, to_big(TEST_DATA_64.native.u) == TEST_DATA_64.be.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = to_big(TEST_DATA_64.native.f));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_64.be.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_from_big(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Byte order conversion functions - from_big.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "Core functions.");
    CUN_UNITTEST_EVAL(ut, from_big(TEST_DATA_16.be).u == TEST_DATA_16.native.u);
    CUN_UNITTEST_EVAL(ut, from_big(TEST_DATA_32.be).u == TEST_DATA_32.native.u);
    CUN_UNITTEST_EVAL(ut, from_big(TEST_DATA_64.be).u == TEST_DATA_64.native.u);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "16bit primitive data types.");
    CUN_UNITTEST_EVAL(ut, from_big(TEST_DATA_16.be.i) == TEST_DATA_16.native.i);
    CUN_UNITTEST_EVAL(ut, from_big(TEST_DATA_16.be.u) == TEST_DATA_16.native.u);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "32bit primitive data types.");
    CUN_UNITTEST_EVAL(ut, from_big(TEST_DATA_32.be.i) == TEST_DATA_32.native.i);
    CUN_UNITTEST_EVAL(ut, from_big(TEST_DATA_32.be.u) == TEST_DATA_32.native.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = from_big(TEST_DATA_32.be.f));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_32.native.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "64bit primitive data types.");
    CUN_UNITTEST_EVAL(ut, from_big(TEST_DATA_64.be.i) == TEST_DATA_64.native.i);
    CUN_UNITTEST_EVAL(ut, from_big(TEST_DATA_64.be.u) == TEST_DATA_64.native.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = from_big(TEST_DATA_64.be.f));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_64.native.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_pack_to_big(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Byte order conversion functions - pack_to_big.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, union16_t retval_16);
    CUN_UNITTEST_EXEC(ut, union32_t retval_32);
    CUN_UNITTEST_EXEC(ut, union64_t retval_64);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "Core functions.");
    CUN_UNITTEST_EXEC(ut, pack_to_big(TEST_DATA_16.native, retval_16.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_16.b, TEST_DATA_16.be.b, sizeof(retval_16.b)) == 0);
    CUN_UNITTEST_EXEC(ut, pack_to_big(TEST_DATA_32.native, retval_32.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_32.b, TEST_DATA_32.be.b, sizeof(retval_32.b)) == 0);
    CUN_UNITTEST_EXEC(ut, pack_to_big(TEST_DATA_64.native, retval_64.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_64.b, TEST_DATA_64.be.b, sizeof(retval_64.b)) == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "16bit primitive data types.");
    CUN_UNITTEST_EXEC(ut, pack_to_big(TEST_DATA_16.native.i, retval_16.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_16.b, TEST_DATA_16.be.b, sizeof(retval_16.b)) == 0);
    CUN_UNITTEST_EXEC(ut, pack_to_big(TEST_DATA_16.native.u, retval_16.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_16.b, TEST_DATA_16.be.b, sizeof(retval_16.b)) == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "32bit primitive data types.");
    CUN_UNITTEST_EXEC(ut, pack_to_big(TEST_DATA_32.native.i, retval_32.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_32.b, TEST_DATA_32.be.b, sizeof(retval_32.b)) == 0);
    CUN_UNITTEST_EXEC(ut, pack_to_big(TEST_DATA_32.native.u, retval_32.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_32.b, TEST_DATA_32.be.b, sizeof(retval_32.b)) == 0);
    CUN_UNITTEST_EXEC(ut, pack_to_big(TEST_DATA_32.native.f, retval_32.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_32.b, TEST_DATA_32.be.b, sizeof(retval_32.b)) == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "64bit primitive data types.");
    CUN_UNITTEST_EXEC(ut, pack_to_big(TEST_DATA_64.native.i, retval_64.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_64.b, TEST_DATA_64.be.b, sizeof(retval_64.b)) == 0);
    CUN_UNITTEST_EXEC(ut, pack_to_big(TEST_DATA_64.native.u, retval_64.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_64.b, TEST_DATA_64.be.b, sizeof(retval_64.b)) == 0);
    CUN_UNITTEST_EXEC(ut, pack_to_big(TEST_DATA_64.native.f, retval_64.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_64.b, TEST_DATA_64.be.b, sizeof(retval_64.b)) == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_unpack_from_big(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Byte order conversion functions - unpack_from_big.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "Core functions.");
    CUN_UNITTEST_EVAL(ut, static_cast<union16_t>(unpack_from_big(TEST_DATA_16.be.b)).u == TEST_DATA_16.native.u);
    CUN_UNITTEST_EVAL(ut, static_cast<union32_t>(unpack_from_big(TEST_DATA_32.be.b)).u == TEST_DATA_32.native.u);
    CUN_UNITTEST_EVAL(ut, static_cast<union64_t>(unpack_from_big(TEST_DATA_64.be.b)).u == TEST_DATA_64.native.u);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "16bit primitive data types.");
    CUN_UNITTEST_EVAL(ut, static_cast<int16_t>(unpack_from_big(TEST_DATA_16.be.b)) == TEST_DATA_16.native.i);
    CUN_UNITTEST_EVAL(ut, static_cast<uint16_t>(unpack_from_big(TEST_DATA_16.be.b)) == TEST_DATA_16.native.u);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "32bit primitive data types.");
    CUN_UNITTEST_EVAL(ut, static_cast<int32_t>(unpack_from_big(TEST_DATA_32.be.b)) == TEST_DATA_32.native.i);
    CUN_UNITTEST_EVAL(ut, static_cast<uint32_t>(unpack_from_big(TEST_DATA_32.be.b)) == TEST_DATA_32.native.u);
    {
        CUN_UNITTEST_EXEC(ut, const float f = unpack_from_big(TEST_DATA_32.be.b));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_32.native.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "64bit primitive data types.");
    CUN_UNITTEST_EVAL(ut, static_cast<int64_t>(unpack_from_big(TEST_DATA_64.be.b)) == TEST_DATA_64.native.i);
    CUN_UNITTEST_EVAL(ut, static_cast<uint64_t>(unpack_from_big(TEST_DATA_64.be.b)) == TEST_DATA_64.native.u);
    {
        CUN_UNITTEST_EXEC(ut, const double f = unpack_from_big(TEST_DATA_64.be.b));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_64.native.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_to_little(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Byte order conversion functions - to_little.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "Core functions.");
    CUN_UNITTEST_EVAL(ut, to_little(TEST_DATA_16.native).u == TEST_DATA_16.le.u);
    CUN_UNITTEST_EVAL(ut, to_little(TEST_DATA_32.native).u == TEST_DATA_32.le.u);
    CUN_UNITTEST_EVAL(ut, to_little(TEST_DATA_64.native).u == TEST_DATA_64.le.u);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "16bit primitive data types.");
    CUN_UNITTEST_EVAL(ut, to_little(TEST_DATA_16.native.i) == TEST_DATA_16.le.i);
    CUN_UNITTEST_EVAL(ut, to_little(TEST_DATA_16.native.u) == TEST_DATA_16.le.u);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "32bit primitive data types.");
    CUN_UNITTEST_EVAL(ut, to_little(TEST_DATA_32.native.i) == TEST_DATA_32.le.i);
    CUN_UNITTEST_EVAL(ut, to_little(TEST_DATA_32.native.u) == TEST_DATA_32.le.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = to_little(TEST_DATA_32.native.f));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_32.le.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "64bit primitive data types.");
    CUN_UNITTEST_EVAL(ut, to_little(TEST_DATA_64.native.i) == TEST_DATA_64.le.i);
    CUN_UNITTEST_EVAL(ut, to_little(TEST_DATA_64.native.u) == TEST_DATA_64.le.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = to_little(TEST_DATA_64.native.f));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_64.le.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_from_little(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Byte order conversion functions - from_little.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "Core functions.");
    CUN_UNITTEST_EVAL(ut, from_little(TEST_DATA_16.le).u == TEST_DATA_16.native.u);
    CUN_UNITTEST_EVAL(ut, from_little(TEST_DATA_32.le).u == TEST_DATA_32.native.u);
    CUN_UNITTEST_EVAL(ut, from_little(TEST_DATA_64.le).u == TEST_DATA_64.native.u);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "16bit primitive data types.");
    CUN_UNITTEST_EVAL(ut, from_little(TEST_DATA_16.le.i) == TEST_DATA_16.native.i);
    CUN_UNITTEST_EVAL(ut, from_little(TEST_DATA_16.le.u) == TEST_DATA_16.native.u);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "32bit primitive data types.");
    CUN_UNITTEST_EVAL(ut, from_little(TEST_DATA_32.le.i) == TEST_DATA_32.native.i);
    CUN_UNITTEST_EVAL(ut, from_little(TEST_DATA_32.le.u) == TEST_DATA_32.native.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = from_little(TEST_DATA_32.le.f));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_32.native.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "64bit primitive data types.");
    CUN_UNITTEST_EVAL(ut, from_little(TEST_DATA_64.le.i) == TEST_DATA_64.native.i);
    CUN_UNITTEST_EVAL(ut, from_little(TEST_DATA_64.le.u) == TEST_DATA_64.native.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = from_little(TEST_DATA_64.le.f));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_64.native.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_pack_to_little(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Byte order conversion functions - pack_to_little.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, union16_t retval_16);
    CUN_UNITTEST_EXEC(ut, union32_t retval_32);
    CUN_UNITTEST_EXEC(ut, union64_t retval_64);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "Core functions.");
    CUN_UNITTEST_EXEC(ut, pack_to_little(TEST_DATA_16.native, retval_16.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_16.b, TEST_DATA_16.le.b, sizeof(retval_16.b)) == 0);
    CUN_UNITTEST_EXEC(ut, pack_to_little(TEST_DATA_32.native, retval_32.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_32.b, TEST_DATA_32.le.b, sizeof(retval_32.b)) == 0);
    CUN_UNITTEST_EXEC(ut, pack_to_little(TEST_DATA_64.native, retval_64.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_64.b, TEST_DATA_64.le.b, sizeof(retval_64.b)) == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "16bit primitive data types.");
    CUN_UNITTEST_EXEC(ut, pack_to_little(TEST_DATA_16.native.i, retval_16.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_16.b, TEST_DATA_16.le.b, sizeof(retval_16.b)) == 0);
    CUN_UNITTEST_EXEC(ut, pack_to_little(TEST_DATA_16.native.u, retval_16.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_16.b, TEST_DATA_16.le.b, sizeof(retval_16.b)) == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "32bit primitive data types.");
    CUN_UNITTEST_EXEC(ut, pack_to_little(TEST_DATA_32.native.i, retval_32.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_32.b, TEST_DATA_32.le.b, sizeof(retval_32.b)) == 0);
    CUN_UNITTEST_EXEC(ut, pack_to_little(TEST_DATA_32.native.u, retval_32.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_32.b, TEST_DATA_32.le.b, sizeof(retval_32.b)) == 0);
    CUN_UNITTEST_EXEC(ut, pack_to_little(TEST_DATA_32.native.f, retval_32.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_32.b, TEST_DATA_32.le.b, sizeof(retval_32.b)) == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "64bit primitive data types.");
    CUN_UNITTEST_EXEC(ut, pack_to_little(TEST_DATA_64.native.i, retval_64.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_64.b, TEST_DATA_64.le.b, sizeof(retval_64.b)) == 0);
    CUN_UNITTEST_EXEC(ut, pack_to_little(TEST_DATA_64.native.u, retval_64.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_64.b, TEST_DATA_64.le.b, sizeof(retval_64.b)) == 0);
    CUN_UNITTEST_EXEC(ut, pack_to_little(TEST_DATA_64.native.f, retval_64.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_64.b, TEST_DATA_64.le.b, sizeof(retval_64.b)) == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_unpack_from_little(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Byte order conversion functions - unpack_from_little.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "Core functions.");
    CUN_UNITTEST_EVAL(ut, static_cast<union16_t>(unpack_from_little(TEST_DATA_16.le.b)).u == TEST_DATA_16.native.u);
    CUN_UNITTEST_EVAL(ut, static_cast<union32_t>(unpack_from_little(TEST_DATA_32.le.b)).u == TEST_DATA_32.native.u);
    CUN_UNITTEST_EVAL(ut, static_cast<union64_t>(unpack_from_little(TEST_DATA_64.le.b)).u == TEST_DATA_64.native.u);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "16bit primitive data types.");
    CUN_UNITTEST_EVAL(ut, static_cast<int16_t>(unpack_from_little(TEST_DATA_16.le.b)) == TEST_DATA_16.native.i);
    CUN_UNITTEST_EVAL(ut, static_cast<uint16_t>(unpack_from_little(TEST_DATA_16.le.b)) == TEST_DATA_16.native.u);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "32bit primitive data types.");
    CUN_UNITTEST_EVAL(ut, static_cast<int32_t>(unpack_from_little(TEST_DATA_32.le.b)) == TEST_DATA_32.native.i);
    CUN_UNITTEST_EVAL(ut, static_cast<uint32_t>(unpack_from_little(TEST_DATA_32.le.b)) == TEST_DATA_32.native.u);
    {
        CUN_UNITTEST_EXEC(ut, const float f = unpack_from_little(TEST_DATA_32.le.b));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_32.native.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "64bit primitive data types.");
    CUN_UNITTEST_EVAL(ut, static_cast<int64_t>(unpack_from_little(TEST_DATA_64.le.b)) == TEST_DATA_64.native.i);
    CUN_UNITTEST_EVAL(ut, static_cast<uint64_t>(unpack_from_little(TEST_DATA_64.le.b)) == TEST_DATA_64.native.u);
    {
        CUN_UNITTEST_EXEC(ut, const double f = unpack_from_little(TEST_DATA_64.le.b));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_64.native.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_c_api(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Byte order conversion functions - ISO C interface.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, union16_t retval_16);
    CUN_UNITTEST_EXEC(ut, union32_t retval_32);
    CUN_UNITTEST_EXEC(ut, union64_t retval_64);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "Convert from native endian to big endian.");
    CUN_UNITTEST_EVAL(ut, cun_byteorder_to_big_i16(TEST_DATA_16.native.i) == TEST_DATA_16.be.i);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_to_big_u16(TEST_DATA_16.native.u) == TEST_DATA_16.be.u);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_to_big_i32(TEST_DATA_32.native.i) == TEST_DATA_32.be.i);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_to_big_u32(TEST_DATA_32.native.u) == TEST_DATA_32.be.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = cun_byteorder_to_big_f32(TEST_DATA_32.native.f));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_32.be.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_EVAL(ut, cun_byteorder_to_big_i64(TEST_DATA_64.native.i) == TEST_DATA_64.be.i);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_to_big_u64(TEST_DATA_64.native.u) == TEST_DATA_64.be.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = cun_byteorder_to_big_f64(TEST_DATA_64.native.f));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_64.be.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "Convert from big endian to native endian.");
    CUN_UNITTEST_EVAL(ut, cun_byteorder_from_big_i16(TEST_DATA_16.be.i) == TEST_DATA_16.native.i);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_from_big_u16(TEST_DATA_16.be.u) == TEST_DATA_16.native.u);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_from_big_i32(TEST_DATA_32.be.i) == TEST_DATA_32.native.i);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_from_big_u32(TEST_DATA_32.be.u) == TEST_DATA_32.native.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = cun_byteorder_from_big_f32(TEST_DATA_32.be.f));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_32.native.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_EVAL(ut, cun_byteorder_from_big_i64(TEST_DATA_64.be.i) == TEST_DATA_64.native.i);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_from_big_u64(TEST_DATA_64.be.u) == TEST_DATA_64.native.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = cun_byteorder_from_big_f64(TEST_DATA_64.be.f));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_64.native.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "Packing to big endian.");
    CUN_UNITTEST_EXEC(ut, cun_byteorder_pack_big_i16(TEST_DATA_16.native.i, retval_16.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_16.b, TEST_DATA_16.be.b, sizeof(retval_16.b)) == 0);
    CUN_UNITTEST_EXEC(ut, cun_byteorder_pack_big_u16(TEST_DATA_16.native.u, retval_16.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_16.b, TEST_DATA_16.be.b, sizeof(retval_16.b)) == 0);
    CUN_UNITTEST_EXEC(ut, cun_byteorder_pack_big_i32(TEST_DATA_32.native.i, retval_32.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_32.b, TEST_DATA_32.be.b, sizeof(retval_32.b)) == 0);
    CUN_UNITTEST_EXEC(ut, cun_byteorder_pack_big_u32(TEST_DATA_32.native.u, retval_32.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_32.b, TEST_DATA_32.be.b, sizeof(retval_32.b)) == 0);
    CUN_UNITTEST_EXEC(ut, cun_byteorder_pack_big_f32(TEST_DATA_32.native.f, retval_32.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_32.b, TEST_DATA_32.be.b, sizeof(retval_32.b)) == 0);
    CUN_UNITTEST_EXEC(ut, cun_byteorder_pack_big_i64(TEST_DATA_64.native.i, retval_64.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_64.b, TEST_DATA_64.be.b, sizeof(retval_64.b)) == 0);
    CUN_UNITTEST_EXEC(ut, cun_byteorder_pack_big_u64(TEST_DATA_64.native.u, retval_64.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_64.b, TEST_DATA_64.be.b, sizeof(retval_64.b)) == 0);
    CUN_UNITTEST_EXEC(ut, cun_byteorder_pack_big_f64(TEST_DATA_64.native.f, retval_64.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_64.b, TEST_DATA_64.be.b, sizeof(retval_64.b)) == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "Unpacking from big endian.");
    CUN_UNITTEST_EVAL(ut, cun_byteorder_unpack_big_i16(TEST_DATA_16.be.b) == TEST_DATA_16.native.i);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_unpack_big_u16(TEST_DATA_16.be.b) == TEST_DATA_16.native.u);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_unpack_big_i32(TEST_DATA_32.be.b) == TEST_DATA_32.native.i);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_unpack_big_u32(TEST_DATA_32.be.b) == TEST_DATA_32.native.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = cun_byteorder_unpack_big_f32(TEST_DATA_32.be.b));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_32.native.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_EVAL(ut, cun_byteorder_unpack_big_i64(TEST_DATA_64.be.b) == TEST_DATA_64.native.i);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_unpack_big_u64(TEST_DATA_64.be.b) == TEST_DATA_64.native.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = cun_byteorder_unpack_big_f64(TEST_DATA_64.be.b));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_64.native.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "Convert from native endian to little endian.");
    CUN_UNITTEST_EVAL(ut, cun_byteorder_to_little_i16(TEST_DATA_16.native.i) == TEST_DATA_16.le.i);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_to_little_u16(TEST_DATA_16.native.u) == TEST_DATA_16.le.u);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_to_little_i32(TEST_DATA_32.native.i) == TEST_DATA_32.le.i);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_to_little_u32(TEST_DATA_32.native.u) == TEST_DATA_32.le.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = cun_byteorder_to_little_f32(TEST_DATA_32.native.f));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_32.le.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_EVAL(ut, cun_byteorder_to_little_i64(TEST_DATA_64.native.i) == TEST_DATA_64.le.i);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_to_little_u64(TEST_DATA_64.native.u) == TEST_DATA_64.le.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = cun_byteorder_to_little_f64(TEST_DATA_64.native.f));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_64.le.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "Convert from little endian to native endian.");
    CUN_UNITTEST_EVAL(ut, cun_byteorder_from_little_i16(TEST_DATA_16.le.i) == TEST_DATA_16.native.i);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_from_little_u16(TEST_DATA_16.le.u) == TEST_DATA_16.native.u);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_from_little_i32(TEST_DATA_32.le.i) == TEST_DATA_32.native.i);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_from_little_u32(TEST_DATA_32.le.u) == TEST_DATA_32.native.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = cun_byteorder_from_little_f32(TEST_DATA_32.le.f));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_32.native.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_EVAL(ut, cun_byteorder_from_little_i64(TEST_DATA_64.le.i) == TEST_DATA_64.native.i);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_from_little_u64(TEST_DATA_64.le.u) == TEST_DATA_64.native.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = cun_byteorder_from_little_f64(TEST_DATA_64.le.f));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_64.native.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "Packing to little endian.");
    CUN_UNITTEST_EXEC(ut, cun_byteorder_pack_little_i16(TEST_DATA_16.native.i, retval_16.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_16.b, TEST_DATA_16.le.b, sizeof(retval_16.b)) == 0);
    CUN_UNITTEST_EXEC(ut, cun_byteorder_pack_little_u16(TEST_DATA_16.native.u, retval_16.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_16.b, TEST_DATA_16.le.b, sizeof(retval_16.b)) == 0);
    CUN_UNITTEST_EXEC(ut, cun_byteorder_pack_little_i32(TEST_DATA_32.native.i, retval_32.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_32.b, TEST_DATA_32.le.b, sizeof(retval_32.b)) == 0);
    CUN_UNITTEST_EXEC(ut, cun_byteorder_pack_little_u32(TEST_DATA_32.native.u, retval_32.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_32.b, TEST_DATA_32.le.b, sizeof(retval_32.b)) == 0);
    CUN_UNITTEST_EXEC(ut, cun_byteorder_pack_little_f32(TEST_DATA_32.native.f, retval_32.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_32.b, TEST_DATA_32.le.b, sizeof(retval_32.b)) == 0);
    CUN_UNITTEST_EXEC(ut, cun_byteorder_pack_little_i64(TEST_DATA_64.native.i, retval_64.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_64.b, TEST_DATA_64.le.b, sizeof(retval_64.b)) == 0);
    CUN_UNITTEST_EXEC(ut, cun_byteorder_pack_little_u64(TEST_DATA_64.native.u, retval_64.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_64.b, TEST_DATA_64.le.b, sizeof(retval_64.b)) == 0);
    CUN_UNITTEST_EXEC(ut, cun_byteorder_pack_little_f64(TEST_DATA_64.native.f, retval_64.b));
    CUN_UNITTEST_EVAL(ut, std::memcmp(retval_64.b, TEST_DATA_64.le.b, sizeof(retval_64.b)) == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "Unpacking from little endian.");
    CUN_UNITTEST_EVAL(ut, cun_byteorder_unpack_little_i16(TEST_DATA_16.le.b) == TEST_DATA_16.native.i);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_unpack_little_u16(TEST_DATA_16.le.b) == TEST_DATA_16.native.u);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_unpack_little_i32(TEST_DATA_32.le.b) == TEST_DATA_32.native.i);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_unpack_little_u32(TEST_DATA_32.le.b) == TEST_DATA_32.native.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = cun_byteorder_unpack_little_f32(TEST_DATA_32.le.b));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_32.native.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_EVAL(ut, cun_byteorder_unpack_little_i64(TEST_DATA_64.le.b) == TEST_DATA_64.native.i);
    CUN_UNITTEST_EVAL(ut, cun_byteorder_unpack_little_u64(TEST_DATA_64.le.b) == TEST_DATA_64.native.u);
    {
        CUN_UNITTEST_EXEC(ut, const auto f = cun_byteorder_unpack_little_f64(TEST_DATA_64.le.b));
        CUN_UNITTEST_EVAL(ut, std::memcmp(&f, &TEST_DATA_64.native.f, sizeof(f)) == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

} // namespace

int main()
{
    auto ut = CUN_UNITTEST_MAKE();

    test_union_t(ut);

    test_to_big(ut);
    test_from_big(ut);

    test_pack_to_big(ut);
    test_unpack_from_big(ut);

    test_to_little(ut);
    test_from_little(ut);

    test_pack_to_little(ut);
    test_unpack_from_little(ut);

    test_c_api(ut);

    return EXIT_SUCCESS;
}
