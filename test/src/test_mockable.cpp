// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: Mockable.

// C++ standard library
#include <cstdlib>
#include <cstring>

// C++ user library
#include "unittest.hpp"

// C user library
extern "C" {
#include "misc.h"
#include "mockable.h"
}

int main()
{
    auto ut = CUN_UNITTEST_MAKE();

    CUN_UNITTEST_TITLE(ut, "Test code: Mockable.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "CUN_MOCKABLE");
    CUN_UNITTEST_EVAL(ut, std::strcmp(CUN_XSTR(CUN_MOCKABLE(fun)), "fun") == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "CUN_RENAMABLE");
    CUN_UNITTEST_EVAL(ut, std::strcmp(CUN_XSTR(CUN_RENAMABLE(fun)), "fun") == 0);
    CUN_UNITTEST_NL(ut);

    return EXIT_SUCCESS;
}
