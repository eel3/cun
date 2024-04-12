// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: Mailbox.

// C++ standard library
#include <chrono>
#include <cstdlib>
#include <string>

// C++ user library
#include "mailbox.hpp"
#include "system_tick.hpp"
#include "unittest.hpp"

int main()
{
    // C++ standard library
    using namespace std::literals::chrono_literals;
    using std::string;

    // C++ user library
    namespace system_tick = cun::system_tick;
    using cun::Mailbox;

    auto ut = CUN_UNITTEST_MAKE();

    CUN_UNITTEST_TITLE(ut, "Test code: Mailbox.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, Mailbox<string> mbox);
    CUN_UNITTEST_EXEC(ut, string val);
    CUN_UNITTEST_EXEC(ut, std::chrono::milliseconds::rep t1, t2);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "default parameter check");
    CUN_UNITTEST_EVAL(ut, mbox.empty());
    CUN_UNITTEST_EVAL(ut, mbox.size() == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EVAL(ut, val.empty());
    CUN_UNITTEST_EXEC(ut, t1 = system_tick::millis());
    CUN_UNITTEST_EVAL(ut, !mbox.pop(val, 100ms));
    CUN_UNITTEST_EXEC(ut, t2 = system_tick::millis());
    CUN_UNITTEST_EVAL(ut, t2 - t1 >= 100);
    CUN_UNITTEST_EVAL(ut, val.empty());
    CUN_UNITTEST_EVAL(ut, !mbox.try_pop(val));
    CUN_UNITTEST_EVAL(ut, val.empty());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "push data");
    CUN_UNITTEST_EXEC(ut, string s1 { "1" });
    CUN_UNITTEST_EXEC(ut, mbox.push(s1));
    CUN_UNITTEST_EVAL(ut, !mbox.empty());
    CUN_UNITTEST_EVAL(ut, mbox.size() == 1);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, mbox.push(string { "2" }));
    CUN_UNITTEST_EVAL(ut, mbox.size() == 2);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, string s3 { "3" });
    CUN_UNITTEST_EXEC(ut, mbox.emplace(s3));
    CUN_UNITTEST_EXEC(ut, mbox.emplace(string { "4" }));
    CUN_UNITTEST_EVAL(ut, mbox.size() == 4);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "pop data: have some mails");
    CUN_UNITTEST_EXEC(ut, val = mbox.pop());
    CUN_UNITTEST_EVAL(ut, mbox.size() == 3);
    CUN_UNITTEST_EVAL(ut, val == "1");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, mbox.pop(val));
    CUN_UNITTEST_EVAL(ut, mbox.size() == 2);
    CUN_UNITTEST_EVAL(ut, val == "2");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, t1 = system_tick::millis());
    CUN_UNITTEST_EVAL(ut, mbox.pop(val, 100ms));
    CUN_UNITTEST_EXEC(ut, t2 = system_tick::millis());
    CUN_UNITTEST_EVAL(ut, t2 - t1 < 100);
    CUN_UNITTEST_EVAL(ut, mbox.size() == 1);
    CUN_UNITTEST_EVAL(ut, val == "3");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EVAL(ut, mbox.try_pop(val));
    CUN_UNITTEST_EVAL(ut, mbox.empty());
    CUN_UNITTEST_EVAL(ut, val == "4");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "pop data: have no mail");
    CUN_UNITTEST_EXEC(ut, val.clear());
    CUN_UNITTEST_EVAL(ut, val.empty());
    CUN_UNITTEST_EXEC(ut, t1 = system_tick::millis());
    CUN_UNITTEST_EVAL(ut, !mbox.pop(val, 100ms));
    CUN_UNITTEST_EXEC(ut, t2 = system_tick::millis());
    CUN_UNITTEST_EVAL(ut, t2 - t1 >= 100);
    CUN_UNITTEST_EVAL(ut, val.empty());
    CUN_UNITTEST_EVAL(ut, !mbox.try_pop(val));
    CUN_UNITTEST_EVAL(ut, val.empty());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "clear data");
    CUN_UNITTEST_EXEC(ut, mbox.push("A"));
    CUN_UNITTEST_EXEC(ut, mbox.push("B"));
    CUN_UNITTEST_EXEC(ut, mbox.push("C"));
    CUN_UNITTEST_EVAL(ut, !mbox.empty());
    CUN_UNITTEST_EVAL(ut, mbox.size() == 3);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, mbox.clear());
    CUN_UNITTEST_EVAL(ut, mbox.empty());
    CUN_UNITTEST_EVAL(ut, mbox.size() == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, val.clear());
    CUN_UNITTEST_EVAL(ut, val.empty());
    CUN_UNITTEST_EXEC(ut, t1 = system_tick::millis());
    CUN_UNITTEST_EVAL(ut, !mbox.pop(val, 100ms));
    CUN_UNITTEST_EXEC(ut, t2 = system_tick::millis());
    CUN_UNITTEST_EVAL(ut, t2 - t1 >= 100);
    CUN_UNITTEST_EVAL(ut, val.empty());
    CUN_UNITTEST_EVAL(ut, !mbox.try_pop(val));
    CUN_UNITTEST_EVAL(ut, val.empty());
    CUN_UNITTEST_NL(ut);

    return EXIT_SUCCESS;
}
