// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: A simple software timer.

// C++ standard library
#include <atomic>
#include <chrono>
#include <cstdlib>
#include <stdexcept>

// C++ user library
#include "soft_timer.hpp"
#include "system_tick.hpp"
#include "unittest.hpp"

int main()
{
    // C++ standard library
    using namespace std::literals::chrono_literals;
    using std::chrono::milliseconds;
    using std::this_thread::sleep_for;

    // C++ user library
    using namespace cun::soft_timer;
    namespace system_tick = cun::system_tick;

    auto ut = CUN_UNITTEST_MAKE();

    CUN_UNITTEST_TITLE(ut, "Test code: A simple software timer.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "constructor parameter check (1)");
    try {
        CUN_UNITTEST_EXEC(ut, auto timer = create(-1ms, []{}));
        CUN_UNITTEST_EVAL(ut, false);
    } catch (const std::invalid_argument& e) {
        CUN_UNITTEST_EVAL(ut, true);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    try {
        CUN_UNITTEST_EXEC(ut, auto timer = create(0ms, []{}));
        CUN_UNITTEST_EVAL(ut, false);
    } catch (const std::invalid_argument& e) {
        CUN_UNITTEST_EVAL(ut, true);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    try {
        CUN_UNITTEST_EXEC(ut, auto timer = create(1ms, []{}));
        CUN_UNITTEST_EVAL(ut, true);
    } catch (const std::exception& e) {
        CUN_UNITTEST_EVAL(ut, false);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "constructor parameter check (2)");
    try {
        CUN_UNITTEST_EXEC(ut, auto timer = create(-1ms, 1, []{}));
        CUN_UNITTEST_EVAL(ut, false);
    } catch (const std::invalid_argument& e) {
        CUN_UNITTEST_EVAL(ut, true);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    try {
        CUN_UNITTEST_EXEC(ut, auto timer = create(0ms, 1, []{}));
        CUN_UNITTEST_EVAL(ut, false);
    } catch (const std::invalid_argument& e) {
        CUN_UNITTEST_EVAL(ut, true);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    try {
        CUN_UNITTEST_EXEC(ut, auto timer = create(1ms, 0, []{}));
        CUN_UNITTEST_EVAL(ut, false);
    } catch (const std::exception& e) {
        CUN_UNITTEST_EVAL(ut, true);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    try {
        CUN_UNITTEST_EXEC(ut, auto timer = create(1ms, 1, []{}));
        CUN_UNITTEST_EVAL(ut, true);
    } catch (const std::exception& e) {
        CUN_UNITTEST_EVAL(ut, false);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    try {
        CUN_UNITTEST_EXEC(ut, auto timer = create(1ms, FOREVER, []{}));
        CUN_UNITTEST_EVAL(ut, true);
    } catch (const std::exception& e) {
        CUN_UNITTEST_EVAL(ut, false);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "constructor parameter check (3)");
    try {
        CUN_UNITTEST_EXEC(ut, auto timer = create(-1ms, 1, true, []{}));
        CUN_UNITTEST_EVAL(ut, false);
    } catch (const std::invalid_argument& e) {
        CUN_UNITTEST_EVAL(ut, true);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    try {
        CUN_UNITTEST_EXEC(ut, auto timer = create(0ms, 1, true, []{}));
        CUN_UNITTEST_EVAL(ut, false);
    } catch (const std::invalid_argument& e) {
        CUN_UNITTEST_EVAL(ut, true);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    try {
        CUN_UNITTEST_EXEC(ut, auto timer = create(1ms, 0, true, []{}));
        CUN_UNITTEST_EVAL(ut, false);
    } catch (const std::exception& e) {
        CUN_UNITTEST_EVAL(ut, true);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    try {
        CUN_UNITTEST_EXEC(ut, auto timer = create(1ms, 1, true, []{}));
        CUN_UNITTEST_EVAL(ut, true);
    } catch (const std::exception& e) {
        CUN_UNITTEST_EVAL(ut, false);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    try {
        CUN_UNITTEST_EXEC(ut, auto timer = create(1ms, FOREVER, true, []{}));
        CUN_UNITTEST_EVAL(ut, true);
    } catch (const std::exception& e) {
        CUN_UNITTEST_EVAL(ut, false);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "typical usage (repeat forever)");
    {
        CUN_UNITTEST_EXEC(ut, std::atomic_uint count { 0 });
        CUN_UNITTEST_EXEC(ut, auto timer = create(10ms, [&count]{ ++count; }));
        CUN_UNITTEST_EVAL(ut, !timer.expired());
        CUN_UNITTEST_EVAL(ut, timer.start());
        CUN_UNITTEST_EXEC(ut, while (count < 5) sleep_for(10ms));
        CUN_UNITTEST_EVAL(ut, !timer.expired());
        CUN_UNITTEST_EVAL(ut, count >= 5);
        CUN_UNITTEST_EVAL(ut, timer.stop());
        CUN_UNITTEST_EVAL(ut, !timer.expired());
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, std::atomic_uint count { 0 });
        CUN_UNITTEST_EXEC(ut, auto timer = create(10ms, FOREVER, [&count]{ ++count; }));
        CUN_UNITTEST_EVAL(ut, !timer.expired());
        CUN_UNITTEST_EVAL(ut, timer.start());
        CUN_UNITTEST_EXEC(ut, while (count < 5) sleep_for(10ms));
        CUN_UNITTEST_EVAL(ut, !timer.expired());
        CUN_UNITTEST_EVAL(ut, count >= 5);
        CUN_UNITTEST_EVAL(ut, timer.stop());
        CUN_UNITTEST_EVAL(ut, !timer.expired());
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, std::atomic_uint count { 0 });
        CUN_UNITTEST_EXEC(ut, auto timer = create(10ms, FOREVER, true, [&count]{ ++count; }));
        CUN_UNITTEST_EVAL(ut, !timer.expired());
        CUN_UNITTEST_EVAL(ut, timer.start());
        CUN_UNITTEST_EXEC(ut, while (count < 5) sleep_for(10ms));
        CUN_UNITTEST_EVAL(ut, !timer.expired());
        CUN_UNITTEST_EVAL(ut, count >= 5);
        CUN_UNITTEST_EVAL(ut, timer.stop());
        CUN_UNITTEST_EVAL(ut, !timer.expired());
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "typical usage (with max repeat count)");
    {
        CUN_UNITTEST_EXEC(ut, std::atomic_uint count { 0 });
        CUN_UNITTEST_EXEC(ut, auto timer = create(10ms, 3, [&count]{ ++count; }));
        CUN_UNITTEST_EVAL(ut, !timer.expired());
        CUN_UNITTEST_EVAL(ut, timer.start());
        CUN_UNITTEST_EXEC(ut, while (!timer.expired()) sleep_for(10ms));
        CUN_UNITTEST_EVAL(ut, timer.expired());
        CUN_UNITTEST_EXEC(ut, sleep_for(100ms));
        CUN_UNITTEST_EVAL(ut, count == 3);
        CUN_UNITTEST_EVAL(ut, timer.stop());
        CUN_UNITTEST_EVAL(ut, !timer.expired());
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, std::atomic_uint count { 0 });
        CUN_UNITTEST_EXEC(ut, auto timer = create(10ms, 3, true, [&count]{ ++count; }));
        CUN_UNITTEST_EVAL(ut, !timer.expired());
        CUN_UNITTEST_EVAL(ut, timer.start());
        CUN_UNITTEST_EXEC(ut, while (!timer.expired()) sleep_for(10ms));
        CUN_UNITTEST_EVAL(ut, timer.expired());
        CUN_UNITTEST_EXEC(ut, sleep_for(100ms));
        CUN_UNITTEST_EVAL(ut, count == 3);
        CUN_UNITTEST_EVAL(ut, timer.stop());
        CUN_UNITTEST_EVAL(ut, !timer.expired());
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "run immediately");
    {
        CUN_UNITTEST_EXEC(ut, milliseconds::rep t1, t2);
        CUN_UNITTEST_EXEC(ut, auto timer = create(100ms, 1, false, [&t2]{ t2 = system_tick::millis(); }));
        CUN_UNITTEST_EXEC(ut, t1 = system_tick::millis());
        CUN_UNITTEST_EVAL(ut, timer.start());
        CUN_UNITTEST_EXEC(ut, while (!timer.expired()) sleep_for(10ms));
        CUN_UNITTEST_EVAL(ut, timer.stop());
        CUN_UNITTEST_EXEC(ut, const auto elapsed = t2 - t1);
        CUN_UNITTEST_EVAL(ut, elapsed >= 100 && elapsed < 150);
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, milliseconds::rep t1, t2);
        CUN_UNITTEST_EXEC(ut, auto timer = create(100ms, 1, true, [&t2]{ t2 = system_tick::millis(); }));
        CUN_UNITTEST_EXEC(ut, t1 = system_tick::millis());
        CUN_UNITTEST_EVAL(ut, timer.start());
        CUN_UNITTEST_EXEC(ut, while (!timer.expired()) sleep_for(10ms));
        CUN_UNITTEST_EVAL(ut, timer.stop());
        CUN_UNITTEST_EXEC(ut, const auto elapsed = t2 - t1);
        CUN_UNITTEST_EVAL(ut, elapsed >= 0 && elapsed < 50);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "stop then start timer");
    {
        CUN_UNITTEST_EXEC(ut, std::atomic_uint count { 0 });
        CUN_UNITTEST_EXEC(ut, auto timer = create(10ms, [&count]{ ++count; }));
        CUN_UNITTEST_EVAL(ut, timer.start());
        CUN_UNITTEST_EXEC(ut, while (count < 5) sleep_for(10ms));
        CUN_UNITTEST_EVAL(ut, timer.stop());
        CUN_UNITTEST_EVAL(ut, count >= 5);
        CUN_UNITTEST_EXEC(ut, count = 0);
        CUN_UNITTEST_EVAL(ut, timer.start());
        CUN_UNITTEST_EXEC(ut, while (count < 5) sleep_for(10ms));
        CUN_UNITTEST_EVAL(ut, timer.stop());
        CUN_UNITTEST_EVAL(ut, count >= 5);
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, std::atomic_uint count { 0 });
        CUN_UNITTEST_EXEC(ut, auto timer = create(10ms, 3, [&count]{ ++count; }));
        CUN_UNITTEST_EVAL(ut, timer.start());
        CUN_UNITTEST_EXEC(ut, while (!timer.expired()) sleep_for(10ms));
        CUN_UNITTEST_EVAL(ut, count == 3);
        CUN_UNITTEST_EVAL(ut, timer.stop());
        CUN_UNITTEST_EXEC(ut, count = 0);
        CUN_UNITTEST_EVAL(ut, timer.start());
        CUN_UNITTEST_EXEC(ut, while (!timer.expired()) sleep_for(10ms));
        CUN_UNITTEST_EVAL(ut, timer.stop());
        CUN_UNITTEST_EVAL(ut, count == 3);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "restart timer");
    {
        CUN_UNITTEST_EXEC(ut, std::atomic_uint count { 0 });
        CUN_UNITTEST_EXEC(ut, auto timer = create(10ms, 3, [&count]{ ++count; }));
        CUN_UNITTEST_EVAL(ut, timer.start());
        CUN_UNITTEST_EXEC(ut, while (!timer.expired()) sleep_for(10ms));
        CUN_UNITTEST_EVAL(ut, count == 3);
        CUN_UNITTEST_EXEC(ut, count = 0);
        CUN_UNITTEST_EVAL(ut, timer.restart());
        CUN_UNITTEST_EXEC(ut, while (!timer.expired()) sleep_for(10ms));
        CUN_UNITTEST_EVAL(ut, timer.stop());
        CUN_UNITTEST_EVAL(ut, count == 3);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "start twice, stop twice");
    {
        CUN_UNITTEST_EXEC(ut, auto timer = create(10ms, []{}));
        CUN_UNITTEST_EVAL(ut, timer.start());
        CUN_UNITTEST_EVAL(ut, !timer.start());
        CUN_UNITTEST_EVAL(ut, timer.stop());
        CUN_UNITTEST_EVAL(ut, timer.stop());
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "destructor test (delete an object without stopping)");
    {
        CUN_UNITTEST_EXEC(ut, auto timer = create(10ms, []{}));
        CUN_UNITTEST_EVAL(ut, timer.start());
        CUN_UNITTEST_EXEC(ut, sleep_for(100ms));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "heap version");
    try {
        CUN_UNITTEST_EXEC(ut, auto timer = alloc_create(10ms, []{}));
        CUN_UNITTEST_EVAL(ut, !timer->expired());
        CUN_UNITTEST_EVAL(ut, timer->start());
        CUN_UNITTEST_EXEC(ut, delete timer);
    } catch (...) {
        /*EMPTY*/
    }
    CUN_UNITTEST_NL(ut);
    try {
        CUN_UNITTEST_EXEC(ut, auto timer = alloc_create(10ms, 3, []{}));
        CUN_UNITTEST_EVAL(ut, !timer->expired());
        CUN_UNITTEST_EVAL(ut, timer->start());
        CUN_UNITTEST_EXEC(ut, delete timer);
    } catch (...) {
        /*EMPTY*/
    }
    CUN_UNITTEST_NL(ut);
    try {
        CUN_UNITTEST_EXEC(ut, auto timer = alloc_create(10ms, 3, true, []{}));
        CUN_UNITTEST_EVAL(ut, !timer->expired());
        CUN_UNITTEST_EVAL(ut, timer->start());
        CUN_UNITTEST_EXEC(ut, delete timer);
    } catch (...) {
        /*EMPTY*/
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "shared_ptr version");
    try {
        CUN_UNITTEST_EXEC(ut, auto timer = shared_create(10ms, []{}));
        CUN_UNITTEST_EVAL(ut, !timer->expired());
        CUN_UNITTEST_EVAL(ut, timer->start());
    } catch (...) {
        /*EMPTY*/
    }
    CUN_UNITTEST_NL(ut);
    try {
        CUN_UNITTEST_EXEC(ut, auto timer = shared_create(10ms, 3, []{}));
        CUN_UNITTEST_EVAL(ut, !timer->expired());
        CUN_UNITTEST_EVAL(ut, timer->start());
    } catch (...) {
        /*EMPTY*/
    }
    CUN_UNITTEST_NL(ut);
    try {
        CUN_UNITTEST_EXEC(ut, auto timer = shared_create(10ms, 3, true, []{}));
        CUN_UNITTEST_EVAL(ut, !timer->expired());
        CUN_UNITTEST_EVAL(ut, timer->start());
    } catch (...) {
        /*EMPTY*/
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "unique_ptr version");
    try {
        CUN_UNITTEST_EXEC(ut, auto timer = unique_create(10ms, []{}));
        CUN_UNITTEST_EVAL(ut, !timer->expired());
        CUN_UNITTEST_EVAL(ut, timer->start());
    } catch (...) {
        /*EMPTY*/
    }
    CUN_UNITTEST_NL(ut);
    try {
        CUN_UNITTEST_EXEC(ut, auto timer = unique_create(10ms, 3, []{}));
        CUN_UNITTEST_EVAL(ut, !timer->expired());
        CUN_UNITTEST_EVAL(ut, timer->start());
    } catch (...) {
        /*EMPTY*/
    }
    CUN_UNITTEST_NL(ut);
    try {
        CUN_UNITTEST_EXEC(ut, auto timer = unique_create(10ms, 3, true, []{}));
        CUN_UNITTEST_EVAL(ut, !timer->expired());
        CUN_UNITTEST_EVAL(ut, timer->start());
    } catch (...) {
        /*EMPTY*/
    }
    CUN_UNITTEST_NL(ut);

    return EXIT_SUCCESS;
}
