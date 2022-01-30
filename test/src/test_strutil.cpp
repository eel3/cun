// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: String utility.

// C++ standard library
#include <cstdlib>

// C++ user library
#include "strutil.hpp"
#include "unittest.hpp"

namespace {

// C++ user library
using namespace cun;
using namespace strutil;

void test_tol_strict(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: String utility - tol_strict.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_tol_safe(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: String utility - tol_safe.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_tol_safe_strict(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: String utility - tol_safe_strict.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_join_container(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: String utility - join (ContainerT).");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_join_array(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: String utility - join (std::array).");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

} // namespace

int main()
{
    auto ut = CUN_UNITTEST_MAKE();

    test_tol_strict(ut);
    test_tol_safe(ut);
    test_tol_safe_strict(ut);
    test_join_container(ut);
    test_join_array(ut);

    return EXIT_SUCCESS;
}
