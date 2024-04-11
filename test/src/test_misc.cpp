// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: Miscellaneous.

// C++ standard library
#include <cstdlib>
#include <cstring>
#include <string>
#include <utility>

// C++ user library
#include "misc.h"
#include "misc.hpp"
#include "unittest.hpp"

namespace {

// C++ standard library
using std::string;

// C++ user library
using namespace cun::misc;
using cun::UnitTest;

void test_BZERO(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Miscellaneous - CUN_BZERO.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "before");
    CUN_UNITTEST_EXEC(ut, char array[] = "test");
    CUN_UNITTEST_EVAL(ut, array[0] == 't');
    CUN_UNITTEST_EVAL(ut, array[1] == 'e');
    CUN_UNITTEST_EVAL(ut, array[2] == 's');
    CUN_UNITTEST_EVAL(ut, array[3] == 't');
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "after");
    CUN_UNITTEST_EXEC(ut, CUN_BZERO(&array[1], 2));
    CUN_UNITTEST_EVAL(ut, array[0] == 't');
    CUN_UNITTEST_EVAL(ut, array[1] == '\x00');
    CUN_UNITTEST_EVAL(ut, array[2] == '\x00');
    CUN_UNITTEST_EVAL(ut, array[3] == 't');
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_CSTREQ(UnitTest& ut)
{
    using std::strcpy;

    CUN_UNITTEST_TITLE(ut, "Test code: Miscellaneous - CUN_CSTREQ.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_COMMENT(ut, "Variables for the testing.");
    CUN_UNITTEST_EXEC(ut, const char *s1);
    CUN_UNITTEST_EXEC(ut, const char *s2);
    CUN_UNITTEST_EXEC(ut, char buf1[16] {});
    CUN_UNITTEST_EXEC(ut, char buf2[16] {});
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "compare a same pointer");
    CUN_UNITTEST_EXEC(ut, s1 = "string");
    CUN_UNITTEST_EXEC(ut, s2 = s1);
    CUN_UNITTEST_EVAL(ut, CUN_CSTREQ(s1, s2));
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "compare a first character");
    CUN_UNITTEST_EXEC(ut, s1 = "abc");
    CUN_UNITTEST_EXEC(ut, s2 = "Abc");
    CUN_UNITTEST_EVAL(ut, !CUN_CSTREQ(s1, s2));
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "compare rest characters");
    CUN_UNITTEST_EXEC(ut, s1 = "abc");
    CUN_UNITTEST_EXEC(ut, s2 = "aBc");
    CUN_UNITTEST_EVAL(ut, !CUN_CSTREQ(s1, s2));
    CUN_UNITTEST_EXEC(ut, s1 = "abc");
    CUN_UNITTEST_EXEC(ut, s2 = "abC");
    CUN_UNITTEST_EVAL(ut, !CUN_CSTREQ(s1, s2));
    CUN_UNITTEST_EXEC(ut, (void) strcpy(buf1, "abc"));
    CUN_UNITTEST_EXEC(ut, (void) strcpy(buf2, "abc"));
    CUN_UNITTEST_EVAL(ut, CUN_CSTREQ(buf1, buf2));
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "compare a zero-length string");
    CUN_UNITTEST_EXEC(ut, buf1[0] = '\0');
    CUN_UNITTEST_EXEC(ut, buf2[0] = '\0');
    CUN_UNITTEST_EVAL(ut, CUN_CSTREQ(buf1, buf2));
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "compare a null pointer");
    CUN_UNITTEST_EXEC(ut, s1 = nullptr);
    CUN_UNITTEST_EXEC(ut, s2 = nullptr);
    CUN_UNITTEST_EVAL(ut, CUN_CSTREQ(s1, s2));
    CUN_UNITTEST_EXEC(ut, s1 = nullptr);
    CUN_UNITTEST_EXEC(ut, s2 = buf2);
    CUN_UNITTEST_EVAL(ut, !CUN_CSTREQ(s1, s2));
    CUN_UNITTEST_EXEC(ut, s1 = buf1);
    CUN_UNITTEST_EXEC(ut, s2 = nullptr);
    CUN_UNITTEST_EVAL(ut, !CUN_CSTREQ(s1, s2));
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_NELEMS(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Miscellaneous - CUN_NELEMS.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "char array[1]");
    CUN_UNITTEST_EXEC(ut, char array_1[1]);
    CUN_UNITTEST_EVAL(ut, CUN_NELEMS(array_1) == 1);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "int array[3]");
    CUN_UNITTEST_EXEC(ut, int array_3[3]);
    CUN_UNITTEST_EVAL(ut, CUN_NELEMS(array_3) == 3);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "int *p - return invalid size");
    CUN_UNITTEST_EXEC(ut, auto *p = array_3);
    CUN_UNITTEST_EVAL(ut, CUN_NELEMS(p) != 3);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_nelems(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Miscellaneous - nelems.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "char array[1]");
    CUN_UNITTEST_EXEC(ut, char array_1[1]);
    CUN_UNITTEST_EVAL(ut, nelems(array_1) == 1);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "int array[3]");
    CUN_UNITTEST_EXEC(ut, int array_3[3]);
    CUN_UNITTEST_EVAL(ut, nelems(array_3) == 3);
    CUN_UNITTEST_NL(ut);

#if 0
    CUN_UNITTEST_NAME(ut, "int *p - cannot compile");
    CUN_UNITTEST_EXEC(ut, auto *p = array_3);
    CUN_UNITTEST_EVAL(ut, nelems(p) != 3);
    CUN_UNITTEST_NL(ut);
#endif

    CUN_UNITTEST_RESET(ut);
}

void test_max(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Miscellaneous - max.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "compare integer");
    CUN_UNITTEST_EVAL(ut, cun::max( 2,  1) ==  2);
    CUN_UNITTEST_EVAL(ut, cun::max( 1,  1) ==  1);
    CUN_UNITTEST_EVAL(ut, cun::max( 0,  1) ==  1);
    CUN_UNITTEST_EVAL(ut, cun::max(-1,  1) ==  1);
    CUN_UNITTEST_EVAL(ut, cun::max(-1,  0) ==  0);
    CUN_UNITTEST_EVAL(ut, cun::max(-1, -1) == -1);
    CUN_UNITTEST_EVAL(ut, cun::max(-1, -2) == -1);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "compare std::string");
    CUN_UNITTEST_EVAL(ut, cun::max(string(""),  string(""))  == "");
    CUN_UNITTEST_EVAL(ut, cun::max(string("a"), string("b")) == "b");
    CUN_UNITTEST_EVAL(ut, cun::max(string("c"), string("b")) == "c");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_min(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Miscellaneous - min.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "compare integer");
    CUN_UNITTEST_EVAL(ut, cun::min( 2,  1) ==  1);
    CUN_UNITTEST_EVAL(ut, cun::min( 1,  1) ==  1);
    CUN_UNITTEST_EVAL(ut, cun::min( 0,  1) ==  0);
    CUN_UNITTEST_EVAL(ut, cun::min(-1,  1) == -1);
    CUN_UNITTEST_EVAL(ut, cun::min(-1,  0) == -1);
    CUN_UNITTEST_EVAL(ut, cun::min(-1, -1) == -1);
    CUN_UNITTEST_EVAL(ut, cun::min(-1, -2) == -2);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "compare std::string");
    CUN_UNITTEST_EVAL(ut, cun::min(string(""),  string(""))  == "");
    CUN_UNITTEST_EVAL(ut, cun::min(string("a"), string("b")) == "a");
    CUN_UNITTEST_EVAL(ut, cun::min(string("c"), string("b")) == "b");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_within_range(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Miscellaneous - within_range.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "low == high");
    CUN_UNITTEST_EVAL(ut, !within_range(1, 2, 2));
    CUN_UNITTEST_EVAL(ut,  within_range(2, 2, 2));
    CUN_UNITTEST_EVAL(ut, !within_range(3, 2, 2));
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "low < high");
    CUN_UNITTEST_EVAL(ut, !within_range(1, 2, 3));
    CUN_UNITTEST_EVAL(ut,  within_range(2, 2, 3));
    CUN_UNITTEST_EVAL(ut,  within_range(3, 2, 3));
    CUN_UNITTEST_EVAL(ut, !within_range(4, 2, 3));
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "std::pair version");
    CUN_UNITTEST_EXEC(ut, const auto range = std::make_pair(2, 3));
    CUN_UNITTEST_EVAL(ut, !within_range(1, range));
    CUN_UNITTEST_EVAL(ut,  within_range(2, range));
    CUN_UNITTEST_EVAL(ut,  within_range(3, range));
    CUN_UNITTEST_EVAL(ut, !within_range(4, range));
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_clamp(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Miscellaneous - clamp.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "low == high");
    CUN_UNITTEST_EVAL(ut, cun::clamp(1, 2, 2) == 2);
    CUN_UNITTEST_EVAL(ut, cun::clamp(2, 2, 2) == 2);
    CUN_UNITTEST_EVAL(ut, cun::clamp(3, 2, 2) == 2);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "low < high");
    CUN_UNITTEST_EVAL(ut, cun::clamp(1, 2, 3) == 2);
    CUN_UNITTEST_EVAL(ut, cun::clamp(2, 2, 3) == 2);
    CUN_UNITTEST_EVAL(ut, cun::clamp(3, 2, 3) == 3);
    CUN_UNITTEST_EVAL(ut, cun::clamp(4, 2, 3) == 3);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_clamp_ex(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Miscellaneous - clamp_ex.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "low == high");
    CUN_UNITTEST_EVAL(ut, clamp_ex(1, 2, 2, 0) == 0);
    CUN_UNITTEST_EVAL(ut, clamp_ex(2, 2, 2, 0) == 2);
    CUN_UNITTEST_EVAL(ut, clamp_ex(3, 2, 2, 0) == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "low < high");
    CUN_UNITTEST_EVAL(ut, clamp_ex(1, 2, 3, 0) == 0);
    CUN_UNITTEST_EVAL(ut, clamp_ex(2, 2, 3, 0) == 2);
    CUN_UNITTEST_EVAL(ut, clamp_ex(3, 2, 3, 0) == 3);
    CUN_UNITTEST_EVAL(ut, clamp_ex(4, 2, 3, 0) == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_remap_range(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Miscellaneous - remap_range.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "same range, minimum width");
    CUN_UNITTEST_EVAL(ut, remap_range(0, 0, 0, 0, 0) == 0);
    CUN_UNITTEST_EVAL(ut, remap_range(1, 1, 1, 1, 1) == 1);
    CUN_UNITTEST_EVAL(ut, remap_range(-1, -1, -1, -1, -1) == -1);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "different range, minimum width");
    CUN_UNITTEST_EVAL(ut, remap_range(0, 0, 0, 2, 2) == 2);
    CUN_UNITTEST_EVAL(ut, remap_range(0, 0, 0, -2, -2) == -2);
    CUN_UNITTEST_EVAL(ut, remap_range(2, 2, 2, -2, -2) == -2);
    CUN_UNITTEST_EVAL(ut, remap_range(-2, -2, -2, 2, 2) == 2);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "same range");
    CUN_UNITTEST_EVAL(ut, remap_range(1, 1, 10, 1, 10) == 1);
    CUN_UNITTEST_EVAL(ut, remap_range(10, 1, 10, 1, 10) == 10);
    CUN_UNITTEST_EVAL(ut, remap_range(-10, -10, -1, -10, -1) == -10);
    CUN_UNITTEST_EVAL(ut, remap_range(-1, -10, -1, -10, -1) == -1);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "different range, same width (1)");
    CUN_UNITTEST_EVAL(ut, remap_range(1, 1, 10, 6, 15) == 6);
    CUN_UNITTEST_EVAL(ut, remap_range(10, 1, 10, 6, 15) == 15);
    CUN_UNITTEST_EVAL(ut, remap_range(1, 1, 10, 11, 20) == 11);
    CUN_UNITTEST_EVAL(ut, remap_range(10, 1, 10, 11, 20) == 20);
    CUN_UNITTEST_EVAL(ut, remap_range(-10, -10, -1, -15, -6) == -15);
    CUN_UNITTEST_EVAL(ut, remap_range(-1, -10, -1, -15, -6) == -6);
    CUN_UNITTEST_EVAL(ut, remap_range(-10, -10, -1, -20, -11) == -20);
    CUN_UNITTEST_EVAL(ut, remap_range(-1, -10, -1, -20, -11) == -11);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "different range, different width");
    CUN_UNITTEST_EVAL(ut, remap_range(1, 1, 10, 1, 20) == 1);
    CUN_UNITTEST_EVAL(ut, remap_range(5, 1, 10, 1, 20) == 9);
    CUN_UNITTEST_EVAL(ut, remap_range(6, 1, 10, 1, 20) == 11);
    CUN_UNITTEST_EVAL(ut, remap_range(10, 1, 10, 1, 20) == 20);
    CUN_UNITTEST_EVAL(ut, remap_range(1, 1, 10, 11, 30) == 11);
    CUN_UNITTEST_EVAL(ut, remap_range(5, 1, 10, 11, 30) == 19);
    CUN_UNITTEST_EVAL(ut, remap_range(6, 1, 10, 11, 30) == 21);
    CUN_UNITTEST_EVAL(ut, remap_range(10, 1, 10, 11, 30) == 30);
    CUN_UNITTEST_EVAL(ut, remap_range(-10, -10, -1, -20, -1) == -20);
    CUN_UNITTEST_EVAL(ut, remap_range(-6, -10, -1, -20, -1) == -12);
    CUN_UNITTEST_EVAL(ut, remap_range(-5, -10, -1, -20, -1) == -10);
    CUN_UNITTEST_EVAL(ut, remap_range(-1, -10, -1, -20, -1) == -1);
    CUN_UNITTEST_EVAL(ut, remap_range(-10, -10, -1, -30, -11) == -30);
    CUN_UNITTEST_EVAL(ut, remap_range(-6, -10, -1, -30, -11) == -22);
    CUN_UNITTEST_EVAL(ut, remap_range(-5, -10, -1, -30, -11) == -20);
    CUN_UNITTEST_EVAL(ut, remap_range(-1, -10, -1, -30, -11) == -11);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "std::pair version");
    CUN_UNITTEST_EVAL(ut, remap_range(0, std::make_pair(0, 0), std::make_pair(0, 0)) == 0);
    CUN_UNITTEST_EVAL(ut, remap_range(2, std::make_pair(2, 2), std::make_pair(-2, -2)) == -2);
    CUN_UNITTEST_EVAL(ut, remap_range(1, std::make_pair(1, 10), std::make_pair(1, 10)) == 1);
    CUN_UNITTEST_EVAL(ut, remap_range(10, std::make_pair(1, 10), std::make_pair(11, 20)) == 20);
    CUN_UNITTEST_EVAL(ut, remap_range(1, std::make_pair(1, 10), std::make_pair(1, 20)) == 1);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_basename(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Miscellaneous - basename.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "nullptr");
    CUN_UNITTEST_EVAL(ut, cun::basename(nullptr) == ".");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "empty (zero size) string");
    CUN_UNITTEST_EVAL(ut, cun::basename("") == ".");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("")) == ".");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "only separator");
    CUN_UNITTEST_EVAL(ut, cun::basename("/") == "/");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("/")) == "/");
    CUN_UNITTEST_EVAL(ut, cun::basename("//") == "/");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("//")) == "/");
    CUN_UNITTEST_NL(ut);

#if defined(_WIN32) || defined(_WIN64)
    CUN_UNITTEST_EVAL(ut, cun::basename("\\") == "\\");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("\\")) == "\\");
    CUN_UNITTEST_EVAL(ut, cun::basename("\\\\") == "\\");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("\\\\")) == "\\");
    CUN_UNITTEST_EVAL(ut, cun::basename("/\\") == "\\");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("/\\")) == "\\");
    CUN_UNITTEST_EVAL(ut, cun::basename("\\/") == "/");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("\\/")) == "/");
    CUN_UNITTEST_NL(ut);
#endif /* defined(_WIN32) || defined(_WIN64) */

    CUN_UNITTEST_NAME(ut, "no separator");
    CUN_UNITTEST_EVAL(ut, cun::basename("a") == "a");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("a")) == "a");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "start with separator");
    CUN_UNITTEST_EVAL(ut, cun::basename("/a") == "a");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("/a")) == "a");
    CUN_UNITTEST_EVAL(ut, cun::basename("//a") == "a");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("//a")) == "a");
    CUN_UNITTEST_NL(ut);

#if defined(_WIN32) || defined(_WIN64)
    CUN_UNITTEST_EVAL(ut, cun::basename("\\a") == "a");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("\\a")) == "a");
    CUN_UNITTEST_EVAL(ut, cun::basename("\\\\a") == "a");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("\\\\a")) == "a");
    CUN_UNITTEST_NL(ut);
#endif /* defined(_WIN32) || defined(_WIN64) */

    CUN_UNITTEST_NAME(ut, "end with separator");
    CUN_UNITTEST_EVAL(ut, cun::basename("a/") == "a");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("a/")) == "a");
    CUN_UNITTEST_EVAL(ut, cun::basename("a//") == "a");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("a//")) == "a");
    CUN_UNITTEST_NL(ut);

#if defined(_WIN32) || defined(_WIN64)
    CUN_UNITTEST_EVAL(ut, cun::basename("a\\") == "a");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("a\\")) == "a");
    CUN_UNITTEST_EVAL(ut, cun::basename("a\\\\") == "a");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("a\\\\")) == "a");
    CUN_UNITTEST_NL(ut);
#endif /* defined(_WIN32) || defined(_WIN64) */

    CUN_UNITTEST_NAME(ut, "multiple separators");
    CUN_UNITTEST_EVAL(ut, cun::basename("/a/b") == "b");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("/a/b")) == "b");
    CUN_UNITTEST_EVAL(ut, cun::basename("a/b") == "b");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("a/b")) == "b");
    CUN_UNITTEST_EVAL(ut, cun::basename("/a/b/") == "b");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("/a/b/")) == "b");
    CUN_UNITTEST_EVAL(ut, cun::basename("a/b/") == "b");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("a/b/")) == "b");
    CUN_UNITTEST_NL(ut);

#if defined(_WIN32) || defined(_WIN64)
    CUN_UNITTEST_EVAL(ut, cun::basename("\\a\\b") == "b");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("\\a\\b")) == "b");
    CUN_UNITTEST_EVAL(ut, cun::basename("a\\b") == "b");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("a\\b")) == "b");
    CUN_UNITTEST_EVAL(ut, cun::basename("\\a\\b\\") == "b");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("\\a\\b\\")) == "b");
    CUN_UNITTEST_EVAL(ut, cun::basename("a\\b\\") == "b");
    CUN_UNITTEST_EVAL(ut, cun::basename(string("a\\b\\")) == "b");
    CUN_UNITTEST_NL(ut);
#endif /* defined(_WIN32) || defined(_WIN64) */

    CUN_UNITTEST_RESET(ut);
}

void test_wait_until(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Miscellaneous - wait_until.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, int count);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "try 1 times");
    CUN_UNITTEST_EXEC(ut, count = 0);
    CUN_UNITTEST_EXEC(ut, wait_until([&count]{ ++count; return true; }));
    CUN_UNITTEST_EVAL(ut, count == 1);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "try 2 times");
    CUN_UNITTEST_EXEC(ut, count = 0);
    CUN_UNITTEST_EXEC(ut, wait_until([&count]{ ++count; return count >= 2; }));
    CUN_UNITTEST_EVAL(ut, count == 2);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "try 10 times");
    CUN_UNITTEST_EXEC(ut, count = 0);
    CUN_UNITTEST_EXEC(ut, wait_until([&count]{ ++count; return count >= 10; }));
    CUN_UNITTEST_EVAL(ut, count == 10);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_wait_while(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Miscellaneous - wait_while.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, int count);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "try 1 times");
    CUN_UNITTEST_EXEC(ut, count = 0);
    CUN_UNITTEST_EXEC(ut, wait_while([&count]{ ++count; return false; }));
    CUN_UNITTEST_EVAL(ut, count == 1);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "try 2 times");
    CUN_UNITTEST_EXEC(ut, count = 0);
    CUN_UNITTEST_EXEC(ut, wait_while([&count]{ ++count; return count < 2; }));
    CUN_UNITTEST_EVAL(ut, count == 2);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "try 10 times");
    CUN_UNITTEST_EXEC(ut, count = 0);
    CUN_UNITTEST_EXEC(ut, wait_while([&count]{ ++count; return count < 10; }));
    CUN_UNITTEST_EVAL(ut, count == 10);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

} // namespace

int main()
{
    auto ut = CUN_UNITTEST_MAKE();

    test_BZERO(ut);
    test_CSTREQ(ut);
    test_NELEMS(ut);
    test_nelems(ut);
    test_max(ut);
    test_min(ut);
    test_within_range(ut);
    test_clamp(ut);
    test_clamp_ex(ut);
    test_remap_range(ut);
    test_basename(ut);
    test_wait_until(ut);
    test_wait_while(ut);

    return EXIT_SUCCESS;
}
