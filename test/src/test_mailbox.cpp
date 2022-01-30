// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: Mailbox.

// C++ standard library
#include <cstdlib>

// C++ user library
#include "mailbox.hpp"
#include "unittest.hpp"

int main()
{
    using cun::Mailbox;

    auto ut = CUN_UNITTEST_MAKE();

    CUN_UNITTEST_TITLE(ut, "Test code: Mailbox.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, Mailbox<int> mbox);
    CUN_UNITTEST_EXEC(ut, (void) mbox);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "TODO: write test code.");
    CUN_UNITTEST_NL(ut);

    return EXIT_SUCCESS;
}
