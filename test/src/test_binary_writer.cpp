// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: Binary data writer && Byte data writer.

// C++ standard library
#include <array>
#include <cstdlib>
#include <deque>
#include <list>
#include <sstream>
#include <string>
#include <vector>

// C++ user library
#include "binary_writer.hpp"
#include "unittest.hpp"

namespace {

// C++ standard library
using std::uint8_t;

// C++ user library
using namespace cun;

void test_ByteWriter(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Binary data writer && Byte data writer - ByteWriter.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, uint8_t buf[16]);
    CUN_UNITTEST_EXEC(ut, ByteWriter writer(buf, 16));
    CUN_UNITTEST_EXEC(ut, (void) writer);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_BufferedByteWriter(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Binary data writer && Byte data writer - BufferedByteWriter.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, BufferedByteWriter<16> writer);
    CUN_UNITTEST_EXEC(ut, (void) writer);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_ArrayByteWriter(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Binary data writer && Byte data writer - ArrayByteWriter.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, std::array<uint8_t, 16> buf);
    CUN_UNITTEST_EXEC(ut, ArrayByteWriter<16> writer(buf));
    CUN_UNITTEST_EXEC(ut, (void) writer);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_DequeByteWriter(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Binary data writer && Byte data writer - DequeByteWriter.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, std::deque<uint8_t> buf);
    CUN_UNITTEST_EXEC(ut, DequeByteWriter writer(buf));
    CUN_UNITTEST_EXEC(ut, (void) writer);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_ListByteWriter(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Binary data writer && Byte data writer - ListByteWriter.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, std::list<uint8_t> buf);
    CUN_UNITTEST_EXEC(ut, ListByteWriter writer(buf));
    CUN_UNITTEST_EXEC(ut, (void) writer);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_VectorByteWriter(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Binary data writer && Byte data writer - VectorByteWriter.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, std::vector<uint8_t> buf);
    CUN_UNITTEST_EXEC(ut, VectorByteWriter writer(buf));
    CUN_UNITTEST_EXEC(ut, (void) writer);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_StreamByteWriter(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Binary data writer && Byte data writer - StreamByteWriter.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, std::ostringstream buf);
    CUN_UNITTEST_EXEC(ut, StreamByteWriter writer(buf));
    CUN_UNITTEST_EXEC(ut, (void) writer);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_StringByteWriter(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Binary data writer && Byte data writer - StringByteWriter.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, std::string buf);
    CUN_UNITTEST_EXEC(ut, StringByteWriter writer(buf));
    CUN_UNITTEST_EXEC(ut, (void) writer);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

} // namespace

int main()
{
    auto ut = CUN_UNITTEST_MAKE();

    test_ByteWriter(ut);
    test_BufferedByteWriter(ut);

    test_ArrayByteWriter(ut);
    test_DequeByteWriter(ut);
    test_ListByteWriter(ut);
    test_VectorByteWriter(ut);
    test_StreamByteWriter(ut);
    test_StringByteWriter(ut);

    return EXIT_SUCCESS;
}
