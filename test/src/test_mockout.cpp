﻿// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: Mockout.

// C++ standard library
#include <cstdlib>
#include <cstring>

// C++ user library
#include "unittest.hpp"

// C user library
extern "C" {
#include "misc.h"
#include "mockout.h"
#include "mockable.h"
}

int main()
{
    auto ut = CUN_UNITTEST_MAKE();

    CUN_UNITTEST_TITLE(ut, "Test code: Mockout.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "CUN_ADD_PREFIX");
    CUN_UNITTEST_EVAL(ut, std::strcmp(CUN_XSTR(CUN_ADD_PREFIX(prefix_, symbol)), "prefix_symbol") == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "CUN_MOCKOUT");
    CUN_UNITTEST_EVAL(ut, std::strcmp(CUN_XSTR(CUN_MOCKOUT(mock_, name)), "mock_name") == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "CUN_RENAME");
    CUN_UNITTEST_EVAL(ut, std::strcmp(CUN_XSTR(CUN_RENAME(renamed_, name)), "renamed_name") == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "CUN_MOCKABLE");
    CUN_UNITTEST_EVAL(ut, std::strcmp(CUN_XSTR(CUN_MOCKABLE(fun)), "mock_fun") == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "CUN_RENAMABLE");
    CUN_UNITTEST_EVAL(ut, std::strcmp(CUN_XSTR(CUN_RENAMABLE(fun)), "real_fun") == 0);
    CUN_UNITTEST_NL(ut);

    return EXIT_SUCCESS;
}
