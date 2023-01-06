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

    CUN_UNITTEST_EXEC(ut, auto num_called = 0);
    CUN_UNITTEST_EXEC(ut, auto return_value = true);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "repeat 0");
    CUN_UNITTEST_EXEC(ut, auto c1 = create(0, []{ return false; }));
    CUN_UNITTEST_EVAL(ut, c1.expired());
    CUN_UNITTEST_EVAL(ut, !c1.resume());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "repeat 1");
    CUN_UNITTEST_EXEC(ut, auto c2 = create(1, [&]{ num_called++; return return_value; }));
    CUN_UNITTEST_EVAL(ut, !c2.expired());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, num_called = 0);
    CUN_UNITTEST_EXEC(ut, return_value = true);
    CUN_UNITTEST_EVAL(ut, c2.resume());
    CUN_UNITTEST_EVAL(ut, num_called == 1);
    CUN_UNITTEST_EVAL(ut, c2.expired());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EVAL(ut, !c2.resume());
    CUN_UNITTEST_EVAL(ut, num_called == 1);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "repeat 2: OK, OK");
    CUN_UNITTEST_EXEC(ut, auto c3 = create(2, [&]{ num_called++; return return_value; }));
    CUN_UNITTEST_EVAL(ut, !c3.expired());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, num_called = 0);
    CUN_UNITTEST_EXEC(ut, return_value = true);
    CUN_UNITTEST_EVAL(ut, c3.resume());
    CUN_UNITTEST_EVAL(ut, num_called == 1);
    CUN_UNITTEST_EVAL(ut, !c3.expired());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EVAL(ut, c3.resume());
    CUN_UNITTEST_EVAL(ut, num_called == 2);
    CUN_UNITTEST_EVAL(ut, c3.expired());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EVAL(ut, !c3.resume());
    CUN_UNITTEST_EVAL(ut, num_called == 2);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "repeat 2: OK, NG");
    CUN_UNITTEST_EXEC(ut, auto c4 = create(2, [&]{ num_called++; return return_value; }));
    CUN_UNITTEST_EVAL(ut, !c4.expired());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, num_called = 0);
    CUN_UNITTEST_EXEC(ut, return_value = true);
    CUN_UNITTEST_EVAL(ut, c4.resume());
    CUN_UNITTEST_EVAL(ut, num_called == 1);
    CUN_UNITTEST_EVAL(ut, !c4.expired());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, return_value = false);
    CUN_UNITTEST_EVAL(ut, c4.resume());
    CUN_UNITTEST_EVAL(ut, num_called == 2);
    CUN_UNITTEST_EVAL(ut, c4.expired());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EVAL(ut, !c4.resume());
    CUN_UNITTEST_EVAL(ut, num_called == 2);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "repeat 2: NG, OK");
    CUN_UNITTEST_EXEC(ut, auto c5 = create(2, [&]{ num_called++; return return_value; }));
    CUN_UNITTEST_EVAL(ut, !c5.expired());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, num_called = 0);
    CUN_UNITTEST_EXEC(ut, return_value = false);
    CUN_UNITTEST_EVAL(ut, c5.resume());
    CUN_UNITTEST_EVAL(ut, num_called == 1);
    CUN_UNITTEST_EVAL(ut, c5.expired());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, return_value = true);
    CUN_UNITTEST_EVAL(ut, !c5.resume());
    CUN_UNITTEST_EVAL(ut, num_called == 1);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "repeat forever");
    CUN_UNITTEST_EXEC(ut, auto c6 = create(FOREVER, [&]{ num_called++; return return_value; }));
    CUN_UNITTEST_EVAL(ut, !c6.expired());
    CUN_UNITTEST_EXEC(ut, num_called = 0);
    CUN_UNITTEST_EXEC(ut, return_value = true);
    CUN_UNITTEST_NL(ut);

    for (auto i = 1; i <= 3; i++) {
        CUN_UNITTEST_EVAL(ut, c6.resume());
        CUN_UNITTEST_EVAL(ut, num_called == i);
        CUN_UNITTEST_EVAL(ut, !c6.expired());
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, return_value = false);
    CUN_UNITTEST_EVAL(ut, c6.resume());
    CUN_UNITTEST_EVAL(ut, num_called == 4);
    CUN_UNITTEST_EVAL(ut, c6.expired());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EVAL(ut, !c6.resume());
    CUN_UNITTEST_EVAL(ut, num_called == 4);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "heap version");
    try {
        CUN_UNITTEST_EXEC(ut, auto cp = alloc_create(0, []{ return false; }));
        CUN_UNITTEST_EVAL(ut, cp->expired());
        CUN_UNITTEST_EVAL(ut, !cp->resume());
        CUN_UNITTEST_EXEC(ut, delete cp);
    } catch (...) {
        /*EMPTY*/
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "shared_ptr version");
    try {
        CUN_UNITTEST_EXEC(ut, auto cp = shared_create(0, []{ return false; }));
        CUN_UNITTEST_EVAL(ut, cp->expired());
        CUN_UNITTEST_EVAL(ut, !cp->resume());
    } catch (...) {
        /*EMPTY*/
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "unique_ptr version");
    try {
        CUN_UNITTEST_EXEC(ut, auto cp = unique_create(0, []{ return false; }));
        CUN_UNITTEST_EVAL(ut, cp->expired());
        CUN_UNITTEST_EVAL(ut, !cp->resume());
    } catch (...) {
        /*EMPTY*/
    }
    CUN_UNITTEST_NL(ut);

    return EXIT_SUCCESS;
}
