// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: Sequence utility.

// C++ standard library
#include <cstdlib>

// C++ user library
#include "sequtil.hpp"
#include "unittest.hpp"

namespace {

// C++ user library
using namespace cun;
using namespace sequtil;

void test_all_of(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - all_of.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_any_of(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - any_of.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_none_of(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - none_of.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_for_each(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - for_each.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_contain(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - contain.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_not_contain(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - not_contain.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_for_each_if(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - for_each_if.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_trim_front_if(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - trim_front_if.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_trim_back_if(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - trim_back_if.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_trim_if(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - trim_if.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_trim_front(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - trim_front.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_trim_back(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - trim_back.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_trim(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - trim.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

} // namespace

int main()
{
    auto ut = CUN_UNITTEST_MAKE();

    test_all_of(ut);
    test_any_of(ut);
    test_none_of(ut);
    test_for_each(ut);
    test_contain(ut);
    test_not_contain(ut);
    test_for_each_if(ut);
    test_trim_front_if(ut);
    test_trim_back_if(ut);
    test_trim_if(ut);
    test_trim_front(ut);
    test_trim_back(ut);
    test_trim(ut);

    return EXIT_SUCCESS;
}
