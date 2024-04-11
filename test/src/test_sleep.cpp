// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: Sleep utility.

// C++ standard library
#include <cstdlib>

// C++ user library
#include "sleep.hpp"
#include "system_tick.hpp"
#include "unittest.hpp"

int main()
{
    namespace sleep = cun::sleep;
    namespace system_tick = cun::system_tick;

    auto ut = CUN_UNITTEST_MAKE();

    CUN_UNITTEST_TITLE(ut, "Test code: Sleep utility.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "secs");
    {
        CUN_UNITTEST_EXEC(ut, const auto t1 = system_tick::millis());
        CUN_UNITTEST_EXEC(ut, sleep::secs(1));
        CUN_UNITTEST_EXEC(ut, const auto t2 = system_tick::millis());
        CUN_UNITTEST_EXEC(ut, const auto elapsed = t2 - t1);
        CUN_UNITTEST_EVAL(ut, elapsed >= 1000 && elapsed < 1050);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "millis");
    {
        CUN_UNITTEST_EXEC(ut, const auto t1 = system_tick::millis());
        CUN_UNITTEST_EXEC(ut, sleep::millis(100));
        CUN_UNITTEST_EXEC(ut, const auto t2 = system_tick::millis());
        CUN_UNITTEST_EXEC(ut, const auto elapsed = t2 - t1);
        CUN_UNITTEST_EVAL(ut, elapsed >= 100 && elapsed < 150);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "micros");
    {
        CUN_UNITTEST_EXEC(ut, const auto t1 = system_tick::micros());
        CUN_UNITTEST_EXEC(ut, sleep::micros(100000));
        CUN_UNITTEST_EXEC(ut, const auto t2 = system_tick::micros());
        CUN_UNITTEST_EXEC(ut, const auto elapsed = t2 - t1);
        CUN_UNITTEST_EVAL(ut, elapsed >= 100000 && elapsed < 150000);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "nanos");
    {
        CUN_UNITTEST_EXEC(ut, const auto t1 = system_tick::nanos());
        CUN_UNITTEST_EXEC(ut, sleep::nanos(100000000));
        CUN_UNITTEST_EXEC(ut, const auto t2 = system_tick::nanos());
        CUN_UNITTEST_EXEC(ut, const auto elapsed = t2 - t1);
        CUN_UNITTEST_EVAL(ut, elapsed >= 100000000 && elapsed < 150000000);
    }
    CUN_UNITTEST_NL(ut);

    return EXIT_SUCCESS;
}
