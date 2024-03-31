// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: System tick utility.

// C++ standard library
#include <chrono>
#include <cstdlib>
#include <thread>

// C++ user library
#include "system_tick.hpp"
#include "unittest.hpp"

int main()
{
    using std::this_thread::sleep_for;
    using namespace cun::system_tick;

    auto ut = CUN_UNITTEST_MAKE();

    CUN_UNITTEST_TITLE(ut, "Test code: System tick utility.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, constexpr std::chrono::milliseconds timeout { 100 });
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "secs");
    {
        CUN_UNITTEST_EXEC(ut, const auto t1 = secs());
        CUN_UNITTEST_EXEC(ut, sleep_for(std::chrono::seconds { 1 }));
        CUN_UNITTEST_EXEC(ut, const auto t2 = secs());
        CUN_UNITTEST_EXEC(ut, const auto elapsed = t2 - t1);
        CUN_UNITTEST_EVAL(ut, elapsed >= 1 && elapsed < 2);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "millis");
    {
        CUN_UNITTEST_EXEC(ut, const auto t1 = millis());
        CUN_UNITTEST_EXEC(ut, sleep_for(timeout));
        CUN_UNITTEST_EXEC(ut, const auto t2 = millis());
        CUN_UNITTEST_EXEC(ut, const auto elapsed = t2 - t1);
        CUN_UNITTEST_EVAL(ut, elapsed >= 100 && elapsed < 120);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "micros");
    {
        CUN_UNITTEST_EXEC(ut, const auto t1 = micros());
        CUN_UNITTEST_EXEC(ut, sleep_for(timeout));
        CUN_UNITTEST_EXEC(ut, const auto t2 = micros());
        CUN_UNITTEST_EXEC(ut, const auto elapsed = t2 - t1);
        CUN_UNITTEST_EVAL(ut, elapsed >= 100000 && elapsed < 120000);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "nanos");
    {
        CUN_UNITTEST_EXEC(ut, const auto t1 = nanos());
        CUN_UNITTEST_EXEC(ut, sleep_for(timeout));
        CUN_UNITTEST_EXEC(ut, const auto t2 = nanos());
        CUN_UNITTEST_EXEC(ut, const auto elapsed = t2 - t1);
        CUN_UNITTEST_EVAL(ut, elapsed >= 100000000 && elapsed < 120000000);
    }
    CUN_UNITTEST_NL(ut);

    return EXIT_SUCCESS;
}
