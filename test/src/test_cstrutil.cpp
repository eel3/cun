// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: C-string utility.

// C++ standard library
#include <cstdlib>

// C++ user library
#include "cstrutil.hpp"
#include "unittest.hpp"

namespace {

// C++ user library
using namespace cun;
using namespace cstrutil;

void test_is_alpha(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: C-string utility - is_alpha.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_is_blank(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: C-string utility - is_blank.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_is_space(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: C-string utility - is_space.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_tol(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: C-string utility - tol.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_tol_strict(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: C-string utility - tol_strict.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_copy(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: C-string utility - copy.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

} // namespace

int main()
{
    auto ut = CUN_UNITTEST_MAKE();

    test_is_alpha(ut);
    test_is_blank(ut);
    test_is_space(ut);
    test_tol(ut);
    test_tol_strict(ut);
    test_copy(ut);

    return EXIT_SUCCESS;
}
