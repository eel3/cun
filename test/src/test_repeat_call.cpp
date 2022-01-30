// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: Repeat call function utility.

// C++ standard library
#include <cstdlib>

// C++ user library
#include "repeat_call.hpp"
#include "unittest.hpp"

int main()
{
    using namespace cun::repeat_call;

    auto ut = CUN_UNITTEST_MAKE();

    CUN_UNITTEST_TITLE(ut, "Test code: Repeat call function utility.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, auto caller = create(0, []{}));
    CUN_UNITTEST_EXEC(ut, (void) caller);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    return EXIT_SUCCESS;
}
