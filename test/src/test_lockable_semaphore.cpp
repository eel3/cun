// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: An inter-thread lockable counting semaphore.

// C++ standard library
#include <chrono>
#include <cstdlib>
#include <thread>

// C++ user library
#include "lockable_semaphore.hpp"
#include "system_tick.hpp"
#include "unittest.hpp"

int main()
{
    // C++ standard library
    using namespace std::literals::chrono_literals;
    using std::jthread;
    using std::this_thread::sleep_for;

    // C++ user library
    namespace system_tick = cun::system_tick;
    using cun::LockableSemaphore;

    auto ut = CUN_UNITTEST_MAKE();

    CUN_UNITTEST_TITLE(ut, "Test code: An inter-thread lockable counting semaphore.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, LockableSemaphore<1> ls);
    CUN_UNITTEST_EXEC(ut, jthread th { []{} });
    CUN_UNITTEST_EXEC(ut, std::chrono::milliseconds::rep t1, t2);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "max()");
    CUN_UNITTEST_EVAL(ut, LockableSemaphore<1>::max() == 1);
    CUN_UNITTEST_EVAL(ut, LockableSemaphore<2>::max() == 2);
    CUN_UNITTEST_EVAL(ut, LockableSemaphore<>::max() == std::numeric_limits<std::ptrdiff_t>::max());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "acquire() / release()");
    CUN_UNITTEST_COMMENT(ut, "Simply acquire and release.");
    CUN_UNITTEST_EXEC(ut, ls.acquire());
    CUN_UNITTEST_EXEC(ut, ls.release());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Wait until released.");
    CUN_UNITTEST_EXEC(ut, t1 = system_tick::millis());
    CUN_UNITTEST_EXEC(ut, th = jthread { [&ls]{ ls.acquire(); sleep_for(100ms); ls.release(); } });
    CUN_UNITTEST_EXEC(ut, sleep_for(50ms));
    CUN_UNITTEST_EXEC(ut, ls.acquire());
    CUN_UNITTEST_EXEC(ut, t2 = system_tick::millis());
    CUN_UNITTEST_EVAL(ut, t2 - t1 >= 100);
    CUN_UNITTEST_EXEC(ut, ls.release());
    CUN_UNITTEST_EXEC(ut, th.join());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "lock() / locked() / unlock()");
    CUN_UNITTEST_EVAL(ut, !ls.locked());
    CUN_UNITTEST_EXEC(ut, ls.lock());
    CUN_UNITTEST_EVAL(ut, ls.locked());
    CUN_UNITTEST_EXEC(ut, ls.unlock());
    CUN_UNITTEST_EVAL(ut, !ls.locked());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Multiple unlocks");
    CUN_UNITTEST_EXEC(ut, ls.unlock());
    CUN_UNITTEST_EVAL(ut, !ls.locked());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "acquire() / lock()");
    CUN_UNITTEST_COMMENT(ut, "Acquired && lock()");
    CUN_UNITTEST_EVAL(ut, !ls.locked());
    CUN_UNITTEST_EXEC(ut, t1 = system_tick::millis());
    CUN_UNITTEST_EXEC(ut, th = jthread { [&ls]{ ls.acquire(); sleep_for(100ms); ls.release(); } });
    CUN_UNITTEST_EXEC(ut, sleep_for(50ms));
    CUN_UNITTEST_EXEC(ut, ls.lock());
    CUN_UNITTEST_EVAL(ut, ls.locked());
    CUN_UNITTEST_EXEC(ut, t2 = system_tick::millis());
    CUN_UNITTEST_EVAL(ut, t2 - t1 >= 100);
    CUN_UNITTEST_EXEC(ut, ls.unlock());
    CUN_UNITTEST_EXEC(ut, th.join());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Locked && acquire()");
    CUN_UNITTEST_EVAL(ut, !ls.locked());
    CUN_UNITTEST_EXEC(ut, t1 = system_tick::millis());
    CUN_UNITTEST_EXEC(ut, th = jthread { [&ls]{ ls.lock(); sleep_for(100ms); ls.unlock(); } });
    CUN_UNITTEST_EXEC(ut, sleep_for(50ms));
    CUN_UNITTEST_EXEC(ut, ls.acquire());
    CUN_UNITTEST_EXEC(ut, t2 = system_tick::millis());
    CUN_UNITTEST_EVAL(ut, t2 - t1 >= 100);
    CUN_UNITTEST_EXEC(ut, ls.release());
    CUN_UNITTEST_EXEC(ut, th.join());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "release()");
    CUN_UNITTEST_EXEC(ut, ls.acquire());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Acquired && invalid argument (1)");
    try {
        CUN_UNITTEST_EXEC(ut, ls.release(-1));
        CUN_UNITTEST_EVAL(ut, false);
    } catch (const std::invalid_argument& e) {
        CUN_UNITTEST_EVAL(ut, true);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Acquired && ineffective argument.");
    CUN_UNITTEST_EXEC(ut, ls.release(0));
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Acquired && invalid argument (2)");
    try {
        CUN_UNITTEST_EXEC(ut, ls.release(2));
        CUN_UNITTEST_EVAL(ut, false);
    } catch (const std::invalid_argument& e) {
        CUN_UNITTEST_EVAL(ut, true);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Acquired && positive testing.");
    CUN_UNITTEST_EXEC(ut, ls.release(1));
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Released && ineffective argument.");
    CUN_UNITTEST_EXEC(ut, ls.release(0));
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Released && invalid argument (2)");
    try {
        CUN_UNITTEST_EXEC(ut, ls.release());
        CUN_UNITTEST_EVAL(ut, false);
    } catch (const std::invalid_argument& e) {
        CUN_UNITTEST_EVAL(ut, true);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "try_acquire()");
    CUN_UNITTEST_COMMENT(ut, "Locked.");
    CUN_UNITTEST_EXEC(ut, ls.lock());
    CUN_UNITTEST_EVAL(ut, ls.locked());
    CUN_UNITTEST_EVAL(ut, !ls.try_acquire());
    CUN_UNITTEST_EXEC(ut, ls.unlock());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Acquired.");
    CUN_UNITTEST_EXEC(ut, ls.acquire());
    CUN_UNITTEST_EVAL(ut, !ls.try_acquire());
    CUN_UNITTEST_EXEC(ut, ls.release());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Positive testing.");
    CUN_UNITTEST_EVAL(ut, ls.try_acquire());
    CUN_UNITTEST_EXEC(ut, ls.release());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "try_lock()");
    CUN_UNITTEST_COMMENT(ut, "Locked (this thread).");
    CUN_UNITTEST_EXEC(ut, ls.lock());
    CUN_UNITTEST_EVAL(ut, ls.locked());
    CUN_UNITTEST_EVAL(ut, !ls.try_lock());
    CUN_UNITTEST_EXEC(ut, ls.unlock());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Locked (another thread).");
    CUN_UNITTEST_EVAL(ut, !ls.locked());
    CUN_UNITTEST_EXEC(ut, th = jthread { [&ls]{ ls.lock(); sleep_for(50ms); ls.unlock(); } });
    CUN_UNITTEST_EXEC(ut, sleep_for(10ms));
    CUN_UNITTEST_EVAL(ut, ls.locked());
    CUN_UNITTEST_EVAL(ut, !ls.try_lock());
    CUN_UNITTEST_EXEC(ut, th.join());
    CUN_UNITTEST_EVAL(ut, !ls.locked());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Acquired.");
    CUN_UNITTEST_EXEC(ut, ls.acquire());
    CUN_UNITTEST_EVAL(ut, !ls.locked());
    CUN_UNITTEST_EVAL(ut, !ls.try_lock());
    CUN_UNITTEST_EXEC(ut, ls.release());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "try_release()");
    CUN_UNITTEST_EXEC(ut, ls.acquire());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Acquired && invalid argument (1)");
    try {
        CUN_UNITTEST_EXEC(ut, ls.try_release(-1));
        CUN_UNITTEST_EVAL(ut, false);
    } catch (const std::invalid_argument& e) {
        CUN_UNITTEST_EVAL(ut, true);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Acquired && ineffective argument.");
    CUN_UNITTEST_EVAL(ut, ls.try_release(0));
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Acquired && invalid argument (2)");
    try {
        CUN_UNITTEST_EXEC(ut, ls.try_release(2));
        CUN_UNITTEST_EVAL(ut, false);
    } catch (const std::invalid_argument& e) {
        CUN_UNITTEST_EVAL(ut, true);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Acquired && positive testing.");
    CUN_UNITTEST_EVAL(ut, ls.try_release(1));
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Released && ineffective argument.");
    CUN_UNITTEST_EVAL(ut, ls.try_release(0));
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Released && locked.");
    CUN_UNITTEST_EXEC(ut, ls.lock());
    CUN_UNITTEST_EVAL(ut, ls.locked());
    CUN_UNITTEST_EVAL(ut, !ls.try_release());
    CUN_UNITTEST_EXEC(ut, ls.unlock());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Released && invalid argument (2)");
    try {
        CUN_UNITTEST_EXEC(ut, ls.try_release());
        CUN_UNITTEST_EVAL(ut, false);
    } catch (const std::invalid_argument& e) {
        CUN_UNITTEST_EVAL(ut, true);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    return EXIT_SUCCESS;
}
