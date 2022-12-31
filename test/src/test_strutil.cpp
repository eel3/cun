// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: String utility.

// C++ standard library
#include <array>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <vector>

// C++ user library
#include "strutil.hpp"
#include "unittest.hpp"

namespace {

// C++ standard library
using std::array;
using std::string;
using std::vector;

// C++ user library
using namespace cun;
using namespace strutil;

void test_tol_strict(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: String utility - tol_strict.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "typical NG pattern");
    try {
        CUN_UNITTEST_ECHO(ut, "const auto n = tol_strict(\"1024byte\")");
        const auto n = tol_strict("1024byte");
        CUN_UNITTEST_EVAL(ut, n == 1024);
    } catch (const std::invalid_argument& e) {
        CUN_UNITTEST_EVAL(ut, true);
        CUN_UNITTEST_ECHO(ut, e.what());
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "typical OK pattern");
    CUN_UNITTEST_EVAL(ut, tol_strict("1024") == 1024);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_tol_safe(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: String utility - tol_safe.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, long retval);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "typical NG pattern");
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, !tol_safe("A", retval));
    CUN_UNITTEST_EVAL(ut, retval == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "typical OK pattern");
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, tol_safe("1024", retval));
    CUN_UNITTEST_EVAL(ut, retval == 1024);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_tol_safe_strict(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: String utility - tol_safe_strict.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, long retval);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "typical NG pattern");
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, !tol_safe_strict("1024byte", retval));
    CUN_UNITTEST_EVAL(ut, retval == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "typical OK pattern");
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, tol_safe_strict("1024", retval));
    CUN_UNITTEST_EVAL(ut, retval == 1024);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_join_container(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: String utility - join (ContainerT).");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, string sep { " : " });
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "empty container");
    {
        CUN_UNITTEST_EXEC(ut, vector<string> v);
        CUN_UNITTEST_EVAL(ut, v.empty());
        CUN_UNITTEST_EVAL(ut, join(v) == "");
        CUN_UNITTEST_EVAL(ut, join(v, static_cast<char *>(nullptr)) == "");
        CUN_UNITTEST_EVAL(ut, join(v, ", ") == "");
        CUN_UNITTEST_EVAL(ut, join(v, sep) == "");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "number of elements == 1");
    {
        CUN_UNITTEST_EXEC(ut, vector<string> v { "a" });
        CUN_UNITTEST_EVAL(ut, v.size() == 1);
        CUN_UNITTEST_EVAL(ut, join(v) == "a");
        CUN_UNITTEST_EVAL(ut, join(v, static_cast<char *>(nullptr)) == "a");
        CUN_UNITTEST_EVAL(ut, join(v, ", ") == "a");
        CUN_UNITTEST_EVAL(ut, join(v, sep) == "a");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "number of elements >= 2");
    {
        CUN_UNITTEST_EXEC(ut, vector<string> v { "a", "b" });
        CUN_UNITTEST_EVAL(ut, v.size() >= 2);
        CUN_UNITTEST_EVAL(ut, join(v) == "ab");
        CUN_UNITTEST_EVAL(ut, join(v, static_cast<char *>(nullptr)) == "ab");
        CUN_UNITTEST_EVAL(ut, join(v, ", ") == "a, b");
        CUN_UNITTEST_EVAL(ut, join(v, sep) == "a : b");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_join_array(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: String utility - join (std::array).");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, string sep { " : " });
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "empty container");
    {
        CUN_UNITTEST_EXEC(ut, array<string, 0> a);
        CUN_UNITTEST_EVAL(ut, a.empty());
        CUN_UNITTEST_EVAL(ut, join(a) == "");
        CUN_UNITTEST_EVAL(ut, join(a, static_cast<char *>(nullptr)) == "");
        CUN_UNITTEST_EVAL(ut, join(a, ", ") == "");
        CUN_UNITTEST_EVAL(ut, join(a, sep) == "");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "number of elements == 1");
    {
        CUN_UNITTEST_EXEC(ut, array<string, 1> a { "a" });
        CUN_UNITTEST_EVAL(ut, a.size() == 1);
        CUN_UNITTEST_EVAL(ut, join(a) == "a");
        CUN_UNITTEST_EVAL(ut, join(a, static_cast<char *>(nullptr)) == "a");
        CUN_UNITTEST_EVAL(ut, join(a, ", ") == "a");
        CUN_UNITTEST_EVAL(ut, join(a, sep) == "a");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "number of elements >= 2");
    {
        CUN_UNITTEST_EXEC(ut, array<string, 2> a { "a", "b" });
        CUN_UNITTEST_EVAL(ut, a.size() >= 2);
        CUN_UNITTEST_EVAL(ut, join(a) == "ab");
        CUN_UNITTEST_EVAL(ut, join(a, static_cast<char *>(nullptr)) == "ab");
        CUN_UNITTEST_EVAL(ut, join(a, ", ") == "a, b");
        CUN_UNITTEST_EVAL(ut, join(a, sep) == "a : b");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

} // namespace

int main()
{
    auto ut = CUN_UNITTEST_MAKE();

    test_tol_strict(ut);
    test_tol_safe(ut);
    test_tol_safe_strict(ut);
    test_join_container(ut);
    test_join_array(ut);

    return EXIT_SUCCESS;
}
