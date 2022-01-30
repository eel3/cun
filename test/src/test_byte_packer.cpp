// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: Byte packer / unpacker.

// C++ standard library
#include <cstdlib>

// C++ user library
#include "byte_packer.hpp"
#include "unittest.hpp"

namespace {

// C++ user library
using namespace cun;
using namespace byte_packer;

void test_pack_carray(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Byte packer / unpacker - pack (C-array).");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_unpack_carray(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Byte packer / unpacker - unpack (C-array).");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_pack_container(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Byte packer / unpacker - pack (ContainerT).");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_pack_array(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Byte packer / unpacker - pack (std::array).");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_pack_ostream(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Byte packer / unpacker - pack (std::ostream).");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_pack_string(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Byte packer / unpacker - pack (std::string).");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_unpack_vector(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Byte packer / unpacker - unpack (std::vector).");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_unpack_array(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Byte packer / unpacker - unpack (std::array).");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_unpack_string(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Byte packer / unpacker - unpack (std::string).");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

} // namespace

int main()
{
    auto ut = CUN_UNITTEST_MAKE();

    test_pack_carray(ut);
    test_unpack_carray(ut);

    test_pack_container(ut);
    test_pack_array(ut);
    test_pack_ostream(ut);
    test_pack_string(ut);

    test_unpack_vector(ut);
    test_unpack_array(ut);
    test_unpack_string(ut);

    return EXIT_SUCCESS;
}
