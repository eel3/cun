// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: A time measuring class.

// C++ standard library
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <thread>

// C++ user library
#define private public
#define protected public
#include "time_measuring.hpp"
#undef protected
#undef private
#include "unittest.hpp"

namespace {

// C++ standard library
using namespace std::literals::chrono_literals;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;

// C++ user library
using namespace cun::time_measuring;
using cun::UnitTest;

void test_ElapsedTime(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: A time measuring class - ElapsedTime.");
    CUN_UNITTEST_NL(ut);

#if 0
    CUN_UNITTEST_NAME(ut, "Compile error");
    {
        CUN_UNITTEST_EXEC(ut, ElapsedTime<0> tm);
    }
    CUN_UNITTEST_NL(ut);
#endif

    CUN_UNITTEST_NAME(ut, "Minimul log size");
    {
        CUN_UNITTEST_EXEC(ut, constexpr auto TAG { "Minimul log size" });
        CUN_UNITTEST_EXEC(ut, ElapsedTime<1, milliseconds> tm { TAG });
        CUN_UNITTEST_EXEC(ut, ElapsedTime<1, milliseconds>::report_type report);
        CUN_UNITTEST_NL(ut);

        CUN_UNITTEST_COMMENT(ut, "Initial values");
        CUN_UNITTEST_EVAL(ut, std::strcmp(tm.c_tag(), TAG) == 0);
        CUN_UNITTEST_EVAL(ut, tm.empty());
        CUN_UNITTEST_EVAL(ut, tm.max_size() == 1);
        CUN_UNITTEST_EVAL(ut, tm.size() == 0);
        CUN_UNITTEST_EVAL(ut, tm.tag() == TAG);
        CUN_UNITTEST_EVAL(ut, !tm.make_report(report));
        CUN_UNITTEST_NL(ut);

        CUN_UNITTEST_COMMENT(ut, "Elapsed time (1)");
        CUN_UNITTEST_EXEC(ut, tm.notify_begin());
        CUN_UNITTEST_EVAL(ut, tm.empty());
        CUN_UNITTEST_EXEC(ut, sleep_for(100ms));
        CUN_UNITTEST_EXEC(ut, tm.notify_end());
        CUN_UNITTEST_EVAL(ut, !tm.empty());
        CUN_UNITTEST_EVAL(ut, tm.size() == 1);
        CUN_UNITTEST_EVAL(ut, tm.m_data[0] >= duration_cast<ElapsedTime<1, milliseconds>::duration>(100ms));
        CUN_UNITTEST_NL(ut);

        CUN_UNITTEST_COMMENT(ut, "Elapsed time (2)");
        CUN_UNITTEST_EXEC(ut, tm.notify_begin());
        CUN_UNITTEST_EXEC(ut, sleep_for(200ms));
        CUN_UNITTEST_EXEC(ut, tm.notify_end());
        CUN_UNITTEST_EVAL(ut, !tm.empty());
        CUN_UNITTEST_EVAL(ut, tm.size() == 1);
        CUN_UNITTEST_EVAL(ut, tm.m_data[0] >= duration_cast<ElapsedTime<1, milliseconds>::duration>(200ms));
        CUN_UNITTEST_NL(ut);

        CUN_UNITTEST_COMMENT(ut, "Make report");
        CUN_UNITTEST_EXEC(ut, tm.m_data[0] = duration_cast<ElapsedTime<1, milliseconds>::duration>(100ms));
        CUN_UNITTEST_EVAL(ut, tm.make_report(report));
        CUN_UNITTEST_EVAL(ut, report.num_data == 1);
        CUN_UNITTEST_EVAL(ut, report.min == 100ms);
        CUN_UNITTEST_EVAL(ut, report.max == 100ms);
        CUN_UNITTEST_EVAL(ut, report.mean == 100ms);
        CUN_UNITTEST_EVAL(ut, report.stdev == 0ms);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "Typical OK pattern");
    {
        CUN_UNITTEST_EXEC(ut, constexpr auto TAG { "Typical OK pattern" });
        CUN_UNITTEST_EXEC(ut, ElapsedTime<2, milliseconds> tm { TAG });
        CUN_UNITTEST_EXEC(ut, ElapsedTime<2, milliseconds>::report_type report);
        CUN_UNITTEST_NL(ut);

        CUN_UNITTEST_COMMENT(ut, "Initial values");
        CUN_UNITTEST_EVAL(ut, std::strcmp(tm.c_tag(), TAG) == 0);
        CUN_UNITTEST_EVAL(ut, tm.empty());
        CUN_UNITTEST_EVAL(ut, tm.max_size() == 2);
        CUN_UNITTEST_EVAL(ut, tm.size() == 0);
        CUN_UNITTEST_EVAL(ut, tm.tag() == TAG);
        CUN_UNITTEST_NL(ut);

        CUN_UNITTEST_COMMENT(ut, "Elapsed time");
        CUN_UNITTEST_EXEC(ut, tm.notify_begin());
        CUN_UNITTEST_EXEC(ut, sleep_for(100ms));
        CUN_UNITTEST_EXEC(ut, tm.notify_end());
        CUN_UNITTEST_EXEC(ut, tm.notify_begin());
        CUN_UNITTEST_EXEC(ut, sleep_for(200ms));
        CUN_UNITTEST_EXEC(ut, tm.notify_end());
        CUN_UNITTEST_EVAL(ut, !tm.empty());
        CUN_UNITTEST_EVAL(ut, tm.size() == 2);
        CUN_UNITTEST_EVAL(ut, tm.m_data[0] >= duration_cast<ElapsedTime<1, milliseconds>::duration>(100ms));
        CUN_UNITTEST_EVAL(ut, tm.m_data[1] >= duration_cast<ElapsedTime<1, milliseconds>::duration>(200ms));
        CUN_UNITTEST_EXEC(ut, tm.notify_begin());
        CUN_UNITTEST_EXEC(ut, sleep_for(300ms));
        CUN_UNITTEST_EXEC(ut, tm.notify_begin());
        CUN_UNITTEST_EXEC(ut, sleep_for(200ms));
        CUN_UNITTEST_EXEC(ut, tm.notify_end());
        CUN_UNITTEST_EXEC(ut, tm.notify_end());
        CUN_UNITTEST_EVAL(ut, tm.size() == 2);
        CUN_UNITTEST_EVAL(ut, tm.m_data[0] <= duration_cast<ElapsedTime<1, milliseconds>::duration>(250ms));
        CUN_UNITTEST_EVAL(ut, tm.m_data[1] >= duration_cast<ElapsedTime<1, milliseconds>::duration>(200ms));
        CUN_UNITTEST_NL(ut);

        CUN_UNITTEST_COMMENT(ut, "Make report");
        CUN_UNITTEST_EXEC(ut, tm.m_data[0] = duration_cast<ElapsedTime<1, milliseconds>::duration>(100ms));
        CUN_UNITTEST_EXEC(ut, tm.m_data[1] = duration_cast<ElapsedTime<1, milliseconds>::duration>(200ms));
        CUN_UNITTEST_EVAL(ut, tm.make_report(report));
        CUN_UNITTEST_EVAL(ut, report.num_data == 2);
        CUN_UNITTEST_EVAL(ut, report.min == 100ms);
        CUN_UNITTEST_EVAL(ut, report.max == 200ms);
        CUN_UNITTEST_EVAL(ut, report.mean == 150ms);
        CUN_UNITTEST_EVAL(ut, report.stdev == 50ms);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_TimeInterval(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: A time measuring class - TimeInterval.");
    CUN_UNITTEST_NL(ut);

#if 0
    CUN_UNITTEST_NAME(ut, "Compile error");
    {
        CUN_UNITTEST_EXEC(ut, TimeInterval<0> ti);
    }
    CUN_UNITTEST_NL(ut);
#endif

    CUN_UNITTEST_NAME(ut, "Minimul log size");
    {
        CUN_UNITTEST_EXEC(ut, constexpr auto TAG { "Minimul log size" });
        CUN_UNITTEST_EXEC(ut, TimeInterval<1, milliseconds> ti { TAG });
        CUN_UNITTEST_EXEC(ut, TimeInterval<1, milliseconds>::report_type report);
        CUN_UNITTEST_NL(ut);

        CUN_UNITTEST_COMMENT(ut, "Initial values");
        CUN_UNITTEST_EVAL(ut, std::strcmp(ti.c_tag(), TAG) == 0);
        CUN_UNITTEST_EVAL(ut, ti.empty());
        CUN_UNITTEST_EVAL(ut, ti.max_size() == 1);
        CUN_UNITTEST_EVAL(ut, ti.size() == 0);
        CUN_UNITTEST_EVAL(ut, ti.tag() == TAG);
        CUN_UNITTEST_EVAL(ut, !ti.make_report(report));
        CUN_UNITTEST_NL(ut);

        CUN_UNITTEST_COMMENT(ut, "Time interval (1)");
        CUN_UNITTEST_EXEC(ut, ti.emit());
        CUN_UNITTEST_EVAL(ut, ti.empty());
        CUN_UNITTEST_EXEC(ut, sleep_for(100ms));
        CUN_UNITTEST_EXEC(ut, ti.emit());
        CUN_UNITTEST_EVAL(ut, !ti.empty());
        CUN_UNITTEST_EVAL(ut, ti.size() == 1);
        CUN_UNITTEST_EVAL(ut, ti.m_data[0] >= duration_cast<ElapsedTime<1, milliseconds>::duration>(100ms));
        CUN_UNITTEST_NL(ut);

        CUN_UNITTEST_COMMENT(ut, "Time interval (2)");
        CUN_UNITTEST_EXEC(ut, sleep_for(200ms));
        CUN_UNITTEST_EXEC(ut, ti.emit());
        CUN_UNITTEST_EVAL(ut, !ti.empty());
        CUN_UNITTEST_EVAL(ut, ti.size() == 1);
        CUN_UNITTEST_EVAL(ut, ti.m_data[0] >= duration_cast<ElapsedTime<1, milliseconds>::duration>(200ms));
        CUN_UNITTEST_NL(ut);

        CUN_UNITTEST_COMMENT(ut, "Make report");
        CUN_UNITTEST_EXEC(ut, ti.m_data[0] = duration_cast<ElapsedTime<1, milliseconds>::duration>(100ms));
        CUN_UNITTEST_EVAL(ut, ti.make_report(report));
        CUN_UNITTEST_EVAL(ut, report.num_data == 1);
        CUN_UNITTEST_EVAL(ut, report.min == 100ms);
        CUN_UNITTEST_EVAL(ut, report.max == 100ms);
        CUN_UNITTEST_EVAL(ut, report.mean == 100ms);
        CUN_UNITTEST_EVAL(ut, report.stdev == 0ms);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "Typical OK pattern");
    {
        CUN_UNITTEST_EXEC(ut, constexpr auto TAG { "Typical OK pattern" });
        CUN_UNITTEST_EXEC(ut, TimeInterval<2, milliseconds> ti { TAG });
        CUN_UNITTEST_EXEC(ut, TimeInterval<2, milliseconds>::report_type report);

        CUN_UNITTEST_COMMENT(ut, "Initial values");
        CUN_UNITTEST_EVAL(ut, std::strcmp(ti.c_tag(), TAG) == 0);
        CUN_UNITTEST_EVAL(ut, ti.empty());
        CUN_UNITTEST_EVAL(ut, ti.max_size() == 2);
        CUN_UNITTEST_EVAL(ut, ti.size() == 0);
        CUN_UNITTEST_EVAL(ut, ti.tag() == TAG);
        CUN_UNITTEST_NL(ut);

        CUN_UNITTEST_COMMENT(ut, "Elapsed time");
        CUN_UNITTEST_EXEC(ut, ti.emit());
        CUN_UNITTEST_EXEC(ut, sleep_for(100ms));
        CUN_UNITTEST_EXEC(ut, ti.emit());
        CUN_UNITTEST_EXEC(ut, sleep_for(200ms));
        CUN_UNITTEST_EXEC(ut, ti.emit());
        CUN_UNITTEST_EVAL(ut, !ti.empty());
        CUN_UNITTEST_EVAL(ut, ti.size() == 2);
        CUN_UNITTEST_EVAL(ut, ti.m_data[0] >= duration_cast<ElapsedTime<1, milliseconds>::duration>(100ms));
        CUN_UNITTEST_EVAL(ut, ti.m_data[1] >= duration_cast<ElapsedTime<1, milliseconds>::duration>(200ms));
        CUN_UNITTEST_EXEC(ut, sleep_for(300ms));
        CUN_UNITTEST_EXEC(ut, ti.emit());
        CUN_UNITTEST_EVAL(ut, ti.size() == 2);
        CUN_UNITTEST_EVAL(ut, ti.m_data[0] >= duration_cast<ElapsedTime<1, milliseconds>::duration>(300ms));
        CUN_UNITTEST_EVAL(ut, ti.m_data[1] >= duration_cast<ElapsedTime<1, milliseconds>::duration>(200ms));
        CUN_UNITTEST_NL(ut);

        CUN_UNITTEST_COMMENT(ut, "Make report");
        CUN_UNITTEST_EXEC(ut, ti.m_data[0] = duration_cast<ElapsedTime<1, milliseconds>::duration>(100ms));
        CUN_UNITTEST_EXEC(ut, ti.m_data[1] = duration_cast<ElapsedTime<1, milliseconds>::duration>(200ms));
        CUN_UNITTEST_EVAL(ut, ti.make_report(report));
        CUN_UNITTEST_EVAL(ut, report.num_data == 2);
        CUN_UNITTEST_EVAL(ut, report.min == 100ms);
        CUN_UNITTEST_EVAL(ut, report.max == 200ms);
        CUN_UNITTEST_EVAL(ut, report.mean == 150ms);
        CUN_UNITTEST_EVAL(ut, report.stdev == 50ms);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

} // namespace

int main()
{
    auto ut = CUN_UNITTEST_MAKE();

    test_ElapsedTime(ut);
    test_TimeInterval(ut);

    return EXIT_SUCCESS;
}
