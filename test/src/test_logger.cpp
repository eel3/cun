// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: Logger.

// C++ standard library
#include <cstdlib>

// C++ user library
#include "logger.hpp"
#include "unittest.hpp"

int main()
{
    using cun::Logger;

    auto ut = CUN_UNITTEST_MAKE();

    CUN_UNITTEST_TITLE(ut, "Test code: Logger.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, auto logger = Logger {});
    CUN_UNITTEST_EXEC(ut, logger.open("TAG"));
    CUN_UNITTEST_EXEC(ut, logger.debug("a"));
    CUN_UNITTEST_EXEC(ut, logger.debug("%d", 1));

    CUN_UNITTEST_NL(ut);
    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    return EXIT_SUCCESS;
}
