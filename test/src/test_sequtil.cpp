// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: Sequence utility.

// C++ standard library
#include <array>
#include <cctype>
#include <cstdlib>
#include <string>

// C++ user library
#include "sequtil.hpp"
#include "unittest.hpp"

namespace {

// C++ standard library
using std::array;
using std::isspace;
using std::string;

// C++ user library
using namespace cun;
using namespace sequtil;

struct Action final {
    int accumulator { 0 };
    int counter { 0 };

    void operator()(const int& n) noexcept {
        accumulator += n;
        counter++;
    }

    void reset() noexcept {
        accumulator = 0;
        counter = 0;
    }
};

void test_all_of(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - all_of.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, const auto pred = [](const int& n) { return (n % 2) == 0; });
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "empty sequence");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 0> a {});
        CUN_UNITTEST_EVAL(ut, all_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "none of");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 1> a { 1 });
        CUN_UNITTEST_EVAL(ut, !all_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { 1, 3 });
        CUN_UNITTEST_EVAL(ut, !all_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 1, 3, 5 });
        CUN_UNITTEST_EVAL(ut, !all_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "any of");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { 1, 2 });
        CUN_UNITTEST_EVAL(ut, !all_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 1, 2, 3 });
        CUN_UNITTEST_EVAL(ut, !all_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 2, 3, 4 });
        CUN_UNITTEST_EVAL(ut, !all_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "all of");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 1> a { 2 });
        CUN_UNITTEST_EVAL(ut, all_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { 2, 4 });
        CUN_UNITTEST_EVAL(ut, all_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 2, 4, 6 });
        CUN_UNITTEST_EVAL(ut, all_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_any_of(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - any_of.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, const auto pred = [](const int& n) { return (n % 2) == 0; });
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "empty sequence");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 0> a {});
        CUN_UNITTEST_EVAL(ut, !any_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "none of");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 1> a { 1 });
        CUN_UNITTEST_EVAL(ut, !any_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { 1, 3 });
        CUN_UNITTEST_EVAL(ut, !any_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 1, 3, 5 });
        CUN_UNITTEST_EVAL(ut, !any_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "any of");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { 1, 2 });
        CUN_UNITTEST_EVAL(ut, any_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 1, 2, 3 });
        CUN_UNITTEST_EVAL(ut, any_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 2, 3, 4 });
        CUN_UNITTEST_EVAL(ut, any_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "all of");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 1> a { 2 });
        CUN_UNITTEST_EVAL(ut, any_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { 2, 4 });
        CUN_UNITTEST_EVAL(ut, any_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 2, 4, 6 });
        CUN_UNITTEST_EVAL(ut, any_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_none_of(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - none_of.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, const auto pred = [](const int& n) { return (n % 2) == 0; });
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "empty sequence");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 0> a {});
        CUN_UNITTEST_EVAL(ut, none_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "none of");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 1> a { 1 });
        CUN_UNITTEST_EVAL(ut, none_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { 1, 3 });
        CUN_UNITTEST_EVAL(ut, none_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 1, 3, 5 });
        CUN_UNITTEST_EVAL(ut, none_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "any of");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { 1, 2 });
        CUN_UNITTEST_EVAL(ut, !none_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 1, 2, 3 });
        CUN_UNITTEST_EVAL(ut, !none_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 2, 3, 4 });
        CUN_UNITTEST_EVAL(ut, !none_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "all of");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 1> a { 2 });
        CUN_UNITTEST_EVAL(ut, !none_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { 2, 4 });
        CUN_UNITTEST_EVAL(ut, !none_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 2, 4, 6 });
        CUN_UNITTEST_EVAL(ut, !none_of(a, pred));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_for_each(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - for_each.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, Action action);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "empty sequence");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 0> a {});
        CUN_UNITTEST_EXEC(ut, action.reset());
        CUN_UNITTEST_EXEC(ut, auto result = for_each(a, action));
        CUN_UNITTEST_EVAL(ut, result.accumulator == 0);
        CUN_UNITTEST_EVAL(ut, result.counter == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "size 1");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 1> a { 0 });
        CUN_UNITTEST_EXEC(ut, action.reset());
        CUN_UNITTEST_EXEC(ut, auto result = for_each(a, action));
        CUN_UNITTEST_EVAL(ut, result.accumulator == 0);
        CUN_UNITTEST_EVAL(ut, result.counter == 1);
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 1> a { 1 });
        CUN_UNITTEST_EXEC(ut, action.reset());
        CUN_UNITTEST_EXEC(ut, auto result = for_each(a, action));
        CUN_UNITTEST_EVAL(ut, result.accumulator == 1);
        CUN_UNITTEST_EVAL(ut, result.counter == 1);
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 1> a { -1 });
        CUN_UNITTEST_EXEC(ut, action.reset());
        CUN_UNITTEST_EXEC(ut, auto result = for_each(a, action));
        CUN_UNITTEST_EVAL(ut, result.accumulator == -1);
        CUN_UNITTEST_EVAL(ut, result.counter == 1);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "size 2");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { 1, 2 });
        CUN_UNITTEST_EXEC(ut, action.reset());
        CUN_UNITTEST_EXEC(ut, auto result = for_each(a, action));
        CUN_UNITTEST_EVAL(ut, result.accumulator == 3);
        CUN_UNITTEST_EVAL(ut, result.counter == 2);
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { -1, -2 });
        CUN_UNITTEST_EXEC(ut, action.reset());
        CUN_UNITTEST_EXEC(ut, auto result = for_each(a, action));
        CUN_UNITTEST_EVAL(ut, result.accumulator == -3);
        CUN_UNITTEST_EVAL(ut, result.counter == 2);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_contain(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - contain.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, constexpr int value { 2 });
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "empty sequence");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 0> a {});
        CUN_UNITTEST_EVAL(ut, !contain(a, value));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "none of");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 1> a { 1 });
        CUN_UNITTEST_EVAL(ut, !contain(a, value));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { 1, 3 });
        CUN_UNITTEST_EVAL(ut, !contain(a, value));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 1, 3, 5 });
        CUN_UNITTEST_EVAL(ut, !contain(a, value));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "any of");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { 1, 2 });
        CUN_UNITTEST_EVAL(ut, contain(a, value));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 1, 2, 3 });
        CUN_UNITTEST_EVAL(ut, contain(a, value));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 2, 3, 4 });
        CUN_UNITTEST_EVAL(ut, contain(a, value));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "all of");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 1> a { 2 });
        CUN_UNITTEST_EVAL(ut, contain(a, value));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { 2, 2 });
        CUN_UNITTEST_EVAL(ut, contain(a, value));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 2, 2, 2 });
        CUN_UNITTEST_EVAL(ut, contain(a, value));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_not_contain(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - not_contain.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, constexpr int value { 2 });
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "empty sequence");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 0> a {});
        CUN_UNITTEST_EVAL(ut, not_contain(a, value));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "none of");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 1> a { 1 });
        CUN_UNITTEST_EVAL(ut, not_contain(a, value));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { 1, 3 });
        CUN_UNITTEST_EVAL(ut, not_contain(a, value));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 1, 3, 5 });
        CUN_UNITTEST_EVAL(ut, not_contain(a, value));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "any of");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { 1, 2 });
        CUN_UNITTEST_EVAL(ut, !not_contain(a, value));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 1, 2, 3 });
        CUN_UNITTEST_EVAL(ut, !not_contain(a, value));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 2, 3, 4 });
        CUN_UNITTEST_EVAL(ut, !not_contain(a, value));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "all of");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 1> a { 2 });
        CUN_UNITTEST_EVAL(ut, !not_contain(a, value));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { 2, 2 });
        CUN_UNITTEST_EVAL(ut, !not_contain(a, value));
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 2, 2, 2 });
        CUN_UNITTEST_EVAL(ut, !not_contain(a, value));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_for_each_if(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - for_each_if.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, const auto pred = [](const int& n) { return (n % 2) == 0; });
    CUN_UNITTEST_EXEC(ut, Action action);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "empty sequence");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 0> a {});
        CUN_UNITTEST_EXEC(ut, action.reset());
        CUN_UNITTEST_EXEC(ut, auto result = for_each_if(a, pred, action));
        CUN_UNITTEST_EVAL(ut, result.accumulator == 0);
        CUN_UNITTEST_EVAL(ut, result.counter == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "none of");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 1> a { 1 });
        CUN_UNITTEST_EXEC(ut, action.reset());
        CUN_UNITTEST_EXEC(ut, auto result = for_each_if(a, pred, action));
        CUN_UNITTEST_EVAL(ut, result.accumulator == 0);
        CUN_UNITTEST_EVAL(ut, result.counter == 0);
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { 1, 3 });
        CUN_UNITTEST_EXEC(ut, action.reset());
        CUN_UNITTEST_EXEC(ut, auto result = for_each_if(a, pred, action));
        CUN_UNITTEST_EVAL(ut, result.accumulator == 0);
        CUN_UNITTEST_EVAL(ut, result.counter == 0);
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 1, 3, 5 });
        CUN_UNITTEST_EXEC(ut, action.reset());
        CUN_UNITTEST_EXEC(ut, auto result = for_each_if(a, pred, action));
        CUN_UNITTEST_EVAL(ut, result.accumulator == 0);
        CUN_UNITTEST_EVAL(ut, result.counter == 0);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "any of");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { 1, 2 });
        CUN_UNITTEST_EXEC(ut, action.reset());
        CUN_UNITTEST_EXEC(ut, auto result = for_each_if(a, pred, action));
        CUN_UNITTEST_EVAL(ut, result.accumulator == 2);
        CUN_UNITTEST_EVAL(ut, result.counter == 1);
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 1, 2, 3 });
        CUN_UNITTEST_EXEC(ut, action.reset());
        CUN_UNITTEST_EXEC(ut, auto result = for_each_if(a, pred, action));
        CUN_UNITTEST_EVAL(ut, result.accumulator == 2);
        CUN_UNITTEST_EVAL(ut, result.counter == 1);
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 2, 3, 4 });
        CUN_UNITTEST_EXEC(ut, action.reset());
        CUN_UNITTEST_EXEC(ut, auto result = for_each_if(a, pred, action));
        CUN_UNITTEST_EVAL(ut, result.accumulator == 6);
        CUN_UNITTEST_EVAL(ut, result.counter == 2);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "all of");
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 1> a { 2 });
        CUN_UNITTEST_EXEC(ut, action.reset());
        CUN_UNITTEST_EXEC(ut, auto result = for_each_if(a, pred, action));
        CUN_UNITTEST_EVAL(ut, result.accumulator == 2);
        CUN_UNITTEST_EVAL(ut, result.counter == 1);
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 2> a { 2, 4 });
        CUN_UNITTEST_EXEC(ut, action.reset());
        CUN_UNITTEST_EXEC(ut, auto result = for_each_if(a, pred, action));
        CUN_UNITTEST_EVAL(ut, result.accumulator == 6);
        CUN_UNITTEST_EVAL(ut, result.counter == 2);
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, const array<int, 3> a { 2, 4, 6 });
        CUN_UNITTEST_EXEC(ut, action.reset());
        CUN_UNITTEST_EXEC(ut, auto result = for_each_if(a, pred, action));
        CUN_UNITTEST_EVAL(ut, result.accumulator == 12);
        CUN_UNITTEST_EVAL(ut, result.counter == 3);
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_trim_front_if(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - trim_front_if.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, const auto pred = [](const char& c) { return isspace(static_cast<unsigned char>(c)); });
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "empty sequence");
    {
        CUN_UNITTEST_EXEC(ut, string s {});
        CUN_UNITTEST_EXEC(ut, trim_front_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "none of");
    {
        CUN_UNITTEST_EXEC(ut, string s { "ab" });
        CUN_UNITTEST_EXEC(ut, trim_front_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "ab");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "any of");
    {
        CUN_UNITTEST_EXEC(ut, string s { " ab" });
        CUN_UNITTEST_EXEC(ut, trim_front_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "ab");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { "a b" });
        CUN_UNITTEST_EXEC(ut, trim_front_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "a b");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { "ab " });
        CUN_UNITTEST_EXEC(ut, trim_front_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "ab ");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { " a b " });
        CUN_UNITTEST_EXEC(ut, trim_front_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "a b ");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "all of");
    {
        CUN_UNITTEST_EXEC(ut, string s { " " });
        CUN_UNITTEST_EXEC(ut, trim_front_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { "  " });
        CUN_UNITTEST_EXEC(ut, trim_front_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_trim_back_if(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - trim_back_if.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, const auto pred = [](const char& c) { return isspace(static_cast<unsigned char>(c)); });
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "empty sequence");
    {
        CUN_UNITTEST_EXEC(ut, string s {});
        CUN_UNITTEST_EXEC(ut, trim_back_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "none of");
    {
        CUN_UNITTEST_EXEC(ut, string s { "ab" });
        CUN_UNITTEST_EXEC(ut, trim_back_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "ab");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "any of");
    {
        CUN_UNITTEST_EXEC(ut, string s { " ab" });
        CUN_UNITTEST_EXEC(ut, trim_back_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == " ab");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { "a b" });
        CUN_UNITTEST_EXEC(ut, trim_back_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "a b");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { "ab " });
        CUN_UNITTEST_EXEC(ut, trim_back_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "ab");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { " a b " });
        CUN_UNITTEST_EXEC(ut, trim_back_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == " a b");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "all of");
    {
        CUN_UNITTEST_EXEC(ut, string s { " " });
        CUN_UNITTEST_EXEC(ut, trim_back_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { "  " });
        CUN_UNITTEST_EXEC(ut, trim_back_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_trim_if(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - trim_if.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, const auto pred = [](const char& c) { return isspace(static_cast<unsigned char>(c)); });
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "empty sequence");
    {
        CUN_UNITTEST_EXEC(ut, string s {});
        CUN_UNITTEST_EXEC(ut, trim_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "none of");
    {
        CUN_UNITTEST_EXEC(ut, string s { "ab" });
        CUN_UNITTEST_EXEC(ut, trim_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "ab");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "any of");
    {
        CUN_UNITTEST_EXEC(ut, string s { " ab" });
        CUN_UNITTEST_EXEC(ut, trim_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "ab");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { "a b" });
        CUN_UNITTEST_EXEC(ut, trim_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "a b");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { "ab " });
        CUN_UNITTEST_EXEC(ut, trim_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "ab");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { " a b " });
        CUN_UNITTEST_EXEC(ut, trim_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "a b");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "all of");
    {
        CUN_UNITTEST_EXEC(ut, string s { " " });
        CUN_UNITTEST_EXEC(ut, trim_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { "  " });
        CUN_UNITTEST_EXEC(ut, trim_if(s, pred));
        CUN_UNITTEST_EVAL(ut, s == "");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_trim_front(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - trim_front.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, constexpr char value { ' ' });
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "empty sequence");
    {
        CUN_UNITTEST_EXEC(ut, string s {});
        CUN_UNITTEST_EXEC(ut, trim_front(s, value));
        CUN_UNITTEST_EVAL(ut, s == "");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "none of");
    {
        CUN_UNITTEST_EXEC(ut, string s { "ab" });
        CUN_UNITTEST_EXEC(ut, trim_front(s, value));
        CUN_UNITTEST_EVAL(ut, s == "ab");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "any of");
    {
        CUN_UNITTEST_EXEC(ut, string s { " ab" });
        CUN_UNITTEST_EXEC(ut, trim_front(s, value));
        CUN_UNITTEST_EVAL(ut, s == "ab");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { "a b" });
        CUN_UNITTEST_EXEC(ut, trim_front(s, value));
        CUN_UNITTEST_EVAL(ut, s == "a b");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { "ab " });
        CUN_UNITTEST_EXEC(ut, trim_front(s, value));
        CUN_UNITTEST_EVAL(ut, s == "ab ");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { " a b " });
        CUN_UNITTEST_EXEC(ut, trim_front(s, value));
        CUN_UNITTEST_EVAL(ut, s == "a b ");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "all of");
    {
        CUN_UNITTEST_EXEC(ut, string s { " " });
        CUN_UNITTEST_EXEC(ut, trim_front(s, value));
        CUN_UNITTEST_EVAL(ut, s == "");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { "  " });
        CUN_UNITTEST_EXEC(ut, trim_front(s, value));
        CUN_UNITTEST_EVAL(ut, s == "");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_trim_back(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - trim_back.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, constexpr char value { ' ' });
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "empty sequence");
    {
        CUN_UNITTEST_EXEC(ut, string s {});
        CUN_UNITTEST_EXEC(ut, trim_back(s, value));
        CUN_UNITTEST_EVAL(ut, s == "");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "none of");
    {
        CUN_UNITTEST_EXEC(ut, string s { "ab" });
        CUN_UNITTEST_EXEC(ut, trim_back(s, value));
        CUN_UNITTEST_EVAL(ut, s == "ab");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "any of");
    {
        CUN_UNITTEST_EXEC(ut, string s { " ab" });
        CUN_UNITTEST_EXEC(ut, trim_back(s, value));
        CUN_UNITTEST_EVAL(ut, s == " ab");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { "a b" });
        CUN_UNITTEST_EXEC(ut, trim_back(s, value));
        CUN_UNITTEST_EVAL(ut, s == "a b");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { "ab " });
        CUN_UNITTEST_EXEC(ut, trim_back(s, value));
        CUN_UNITTEST_EVAL(ut, s == "ab");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { " a b " });
        CUN_UNITTEST_EXEC(ut, trim_back(s, value));
        CUN_UNITTEST_EVAL(ut, s == " a b");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "all of");
    {
        CUN_UNITTEST_EXEC(ut, string s { " " });
        CUN_UNITTEST_EXEC(ut, trim_back(s, value));
        CUN_UNITTEST_EVAL(ut, s == "");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { "  " });
        CUN_UNITTEST_EXEC(ut, trim_back(s, value));
        CUN_UNITTEST_EVAL(ut, s == "");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_trim(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Sequence utility - trim.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, constexpr char value { ' ' });
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "empty sequence");
    {
        CUN_UNITTEST_EXEC(ut, string s {});
        CUN_UNITTEST_EXEC(ut, trim(s, value));
        CUN_UNITTEST_EVAL(ut, s == "");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "none of");
    {
        CUN_UNITTEST_EXEC(ut, string s { "ab" });
        CUN_UNITTEST_EXEC(ut, trim(s, value));
        CUN_UNITTEST_EVAL(ut, s == "ab");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "any of");
    {
        CUN_UNITTEST_EXEC(ut, string s { " ab" });
        CUN_UNITTEST_EXEC(ut, trim(s, value));
        CUN_UNITTEST_EVAL(ut, s == "ab");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { "a b" });
        CUN_UNITTEST_EXEC(ut, trim(s, value));
        CUN_UNITTEST_EVAL(ut, s == "a b");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { "ab " });
        CUN_UNITTEST_EXEC(ut, trim(s, value));
        CUN_UNITTEST_EVAL(ut, s == "ab");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { " a b " });
        CUN_UNITTEST_EXEC(ut, trim(s, value));
        CUN_UNITTEST_EVAL(ut, s == "a b");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "all of");
    {
        CUN_UNITTEST_EXEC(ut, string s { " " });
        CUN_UNITTEST_EXEC(ut, trim(s, value));
        CUN_UNITTEST_EVAL(ut, s == "");
    }
    CUN_UNITTEST_NL(ut);
    {
        CUN_UNITTEST_EXEC(ut, string s { "  " });
        CUN_UNITTEST_EXEC(ut, trim(s, value));
        CUN_UNITTEST_EVAL(ut, s == "");
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

} // namespace

int main()
{
    auto ut = CUN_UNITTEST_MAKE();

    test_all_of(ut);
    test_any_of(ut);
    test_none_of(ut);
    test_for_each(ut);
    test_contain(ut);
    test_not_contain(ut);
    test_for_each_if(ut);
    test_trim_front_if(ut);
    test_trim_back_if(ut);
    test_trim_if(ut);
    test_trim_front(ut);
    test_trim_back(ut);
    test_trim(ut);

    return EXIT_SUCCESS;
}
