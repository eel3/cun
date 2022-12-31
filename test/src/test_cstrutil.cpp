// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: C-string utility.

// C++ standard library
#include <climits>
#include <cstdlib>
#include <cstring>

// C++ user library
#include "cstrutil.hpp"
#include "unittest.hpp"

namespace {

// C++ user library
using namespace cun;
using namespace cstrutil;

void test_is_alpha(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: C-string utility - is_alpha.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, const char *p, *q);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "uppercase alphabet");
    CUN_UNITTEST_EXEC(ut, p = "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    CUN_UNITTEST_EXEC(ut, q = p + std::strlen(p));
    for (; p < q; p++) {
        CUN_UNITTEST_EVAL(ut, is_alpha(static_cast<unsigned char>(*p)));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "lowercase alphabet");
    CUN_UNITTEST_EXEC(ut, p = "abcdefghijklmnopqrstuvwxyz");
    CUN_UNITTEST_EXEC(ut, q = p + std::strlen(p));
    for (; p < q; p++) {
        CUN_UNITTEST_EVAL(ut, is_alpha(static_cast<unsigned char>(*p)));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "not alphabet");
    CUN_UNITTEST_EXEC(ut, p = "\t\n\r !0123456789@[`{~\x7F");
    CUN_UNITTEST_EXEC(ut, q = p + std::strlen(p));
    for (; p < q; p++) {
        CUN_UNITTEST_EVAL(ut, !is_alpha(static_cast<unsigned char>(*p)));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_is_blank(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: C-string utility - is_blank.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, const char *p, *q);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "blank character");
    CUN_UNITTEST_EXEC(ut, p = "\t ");
    CUN_UNITTEST_EXEC(ut, q = p + std::strlen(p));
    for (; p < q; p++) {
        CUN_UNITTEST_EVAL(ut, is_blank(static_cast<unsigned char>(*p)));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "not blank character");
    CUN_UNITTEST_EXEC(ut, p = "\b\n\v\f\r\x1F!");
    CUN_UNITTEST_EXEC(ut, q = p + std::strlen(p));
    for (; p < q; p++) {
        CUN_UNITTEST_EVAL(ut, !is_blank(static_cast<unsigned char>(*p)));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_is_space(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: C-string utility - is_space.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, const char *p, *q);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "space character");
    CUN_UNITTEST_EXEC(ut, p = "\t\n\v\f\r ");
    CUN_UNITTEST_EXEC(ut, q = p + std::strlen(p));
    for (; p < q; p++) {
        CUN_UNITTEST_EVAL(ut, is_space(static_cast<unsigned char>(*p)));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "not space character");
    CUN_UNITTEST_EXEC(ut, p = "\b\x0E\x1F!");
    CUN_UNITTEST_EXEC(ut, q = p + std::strlen(p));
    for (; p < q; p++) {
        CUN_UNITTEST_EVAL(ut, !is_space(static_cast<unsigned char>(*p)));
    }
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_tol(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: C-string utility - tol.");
    CUN_UNITTEST_NL(ut);

#if LONG_MIN == (-2147483647L - 1)
    CUN_UNITTEST_EXEC(ut, constexpr auto OK_MIN_NUMBER { "-2147483648" });
    CUN_UNITTEST_EXEC(ut, constexpr auto NG_MIN_NUMBER { "-2147483649" });
#endif
#if LONG_MAX == 2147483647L
    CUN_UNITTEST_EXEC(ut, constexpr auto OK_MAX_NUMBER { "2147483647" });
    CUN_UNITTEST_EXEC(ut, constexpr auto NG_MAX_NUMBER { "2147483648" });
#endif

#if LONG_MIN == (-9223372036854775807L - 1)
    CUN_UNITTEST_EXEC(ut, constexpr auto OK_MIN_NUMBER { "-9223372036854775808" });
    CUN_UNITTEST_EXEC(ut, constexpr auto NG_MIN_NUMBER { "-9223372036854775809" });
#endif
#if LONG_MAX == 9223372036854775807L
    CUN_UNITTEST_EXEC(ut, constexpr auto OK_MAX_NUMBER { "9223372036854775807" });
    CUN_UNITTEST_EXEC(ut, constexpr auto NG_MAX_NUMBER { "9223372036854775808" });
#endif

    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, long retval);
    CUN_UNITTEST_EXEC(ut, char *endp);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "invalid argument");
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EXEC(ut, endp = nullptr);
    CUN_UNITTEST_EVAL(ut, !cun_cstrutil_tol(nullptr, &retval, &endp, 0));
    CUN_UNITTEST_EVAL(ut, retval == 0);
    CUN_UNITTEST_EVAL(ut, !cun_cstrutil_tol("1", nullptr, &endp, 0));
    CUN_UNITTEST_EVAL(ut, !cun_cstrutil_tol("1", &retval, &endp, -1));
    CUN_UNITTEST_EVAL(ut, retval == 0);
    CUN_UNITTEST_EVAL(ut, !cun_cstrutil_tol("1", &retval, &endp, 1));
    CUN_UNITTEST_EVAL(ut, retval == 0);
    CUN_UNITTEST_EVAL(ut, !cun_cstrutil_tol("1", &retval, &endp, 37));
    CUN_UNITTEST_EVAL(ut, retval == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "not number");
    CUN_UNITTEST_EXEC(ut, retval = ~0);
    CUN_UNITTEST_EXEC(ut, endp = nullptr);
    CUN_UNITTEST_EVAL(ut, !cun_cstrutil_tol("", &retval, &endp, 0));
    CUN_UNITTEST_EVAL(ut, retval == ~0);
    CUN_UNITTEST_EVAL(ut, !cun_cstrutil_tol(" ", &retval, &endp, 0));
    CUN_UNITTEST_EVAL(ut, retval == ~0);
    CUN_UNITTEST_EVAL(ut, !cun_cstrutil_tol("A", &retval, &endp, 0));
    CUN_UNITTEST_EVAL(ut, retval == ~0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "typical OK pattern");
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EXEC(ut, endp = nullptr);
    CUN_UNITTEST_EVAL(ut, cun_cstrutil_tol("1", &retval, &endp, 0));
    CUN_UNITTEST_EVAL(ut, retval == 1);
    CUN_UNITTEST_EVAL(ut, *endp == '\0');
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EXEC(ut, endp = nullptr);
    CUN_UNITTEST_EVAL(ut, cun_cstrutil_tol("1024byte", &retval, &endp, 0));
    CUN_UNITTEST_EVAL(ut, retval == 1024);
    CUN_UNITTEST_EVAL(ut, *endp == 'b');
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "huge number");
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, !cun_cstrutil_tol(NG_MIN_NUMBER, &retval, nullptr, 0));
    CUN_UNITTEST_EVAL(ut, retval == 0);
    CUN_UNITTEST_EVAL(ut, cun_cstrutil_tol(OK_MIN_NUMBER, &retval, nullptr, 0));
    CUN_UNITTEST_EVAL(ut, retval == LONG_MIN);
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, !cun_cstrutil_tol(NG_MAX_NUMBER, &retval, nullptr, 0));
    CUN_UNITTEST_EVAL(ut, retval == 0);
    CUN_UNITTEST_EVAL(ut, cun_cstrutil_tol(OK_MAX_NUMBER, &retval, nullptr, 0));
    CUN_UNITTEST_EVAL(ut, retval == LONG_MAX);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "base test");
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, cun_cstrutil_tol("10", &retval, nullptr, 0));
    CUN_UNITTEST_EVAL(ut, retval == 10);
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, cun_cstrutil_tol("10", &retval, nullptr, 2));
    CUN_UNITTEST_EVAL(ut, retval == 2);
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, cun_cstrutil_tol("10", &retval, nullptr, 8));
    CUN_UNITTEST_EVAL(ut, retval == 8);
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, cun_cstrutil_tol("10", &retval, nullptr, 10));
    CUN_UNITTEST_EVAL(ut, retval == 10);
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, cun_cstrutil_tol("A", &retval, nullptr, 16));
    CUN_UNITTEST_EVAL(ut, retval == 10);
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, cun_cstrutil_tol("f", &retval, nullptr, 16));
    CUN_UNITTEST_EVAL(ut, retval == 15);
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, cun_cstrutil_tol("Z", &retval, nullptr, 36));
    CUN_UNITTEST_EVAL(ut, retval == 35);
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, cun_cstrutil_tol("010", &retval, nullptr, 0));
    CUN_UNITTEST_EVAL(ut, retval == 8);
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, cun_cstrutil_tol("0x7F", &retval, nullptr, 0));
    CUN_UNITTEST_EVAL(ut, retval == 127);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "C++ version");
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, tol("10", retval));
    CUN_UNITTEST_EVAL(ut, retval == 10);
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EXEC(ut, endp = nullptr);
    CUN_UNITTEST_EVAL(ut, tol("10", retval, &endp));
    CUN_UNITTEST_EVAL(ut, retval == 10);
    CUN_UNITTEST_EVAL(ut, *endp == '\0');
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, tol("10", retval, nullptr, 16));
    CUN_UNITTEST_EVAL(ut, retval == 16);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_tol_strict(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: C-string utility - tol_strict.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, long retval);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "not number");
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, !cun_cstrutil_tol_strict("byte", &retval, 0));
    CUN_UNITTEST_EVAL(ut, retval == 0);
    CUN_UNITTEST_EVAL(ut, !cun_cstrutil_tol_strict("1byte", &retval, 0));
    CUN_UNITTEST_EVAL(ut, retval == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "typical OK pattern");
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, cun_cstrutil_tol_strict("1", &retval, 0));
    CUN_UNITTEST_EVAL(ut, retval == 1);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "C++ version");
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, tol_strict("10", retval));
    CUN_UNITTEST_EVAL(ut, retval == 10);
    CUN_UNITTEST_EXEC(ut, retval = 0);
    CUN_UNITTEST_EVAL(ut, tol_strict("10", retval, 16));
    CUN_UNITTEST_EVAL(ut, retval == 16);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

void test_copy(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: C-string utility - copy.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, char buf[8]);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "invalid argument");
    CUN_UNITTEST_EXEC(ut, buf[0] = '\xFF');
    CUN_UNITTEST_EVAL(ut, copy(nullptr, sizeof(buf), "test") == nullptr);
    CUN_UNITTEST_EVAL(ut, copy(buf, 0, "test") == buf);
    CUN_UNITTEST_EVAL(ut, buf[0] == '\xFF');
    CUN_UNITTEST_EVAL(ut, copy(buf, sizeof(buf), nullptr) == buf);
    CUN_UNITTEST_EVAL(ut, buf[0] == '\xFF');
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "minimum buffer size");
    CUN_UNITTEST_EXEC(ut, buf[0] = '\xFF');
    CUN_UNITTEST_EVAL(ut, copy(buf, 1, "test") == buf);
    CUN_UNITTEST_EVAL(ut, buf[0] == '\0');
    CUN_UNITTEST_EXEC(ut, std::memset(buf, '\xFF', sizeof(buf)));
    CUN_UNITTEST_EVAL(ut, copy(buf, 2, "test") == buf);
    CUN_UNITTEST_EVAL(ut, std::strcmp(buf, "t") == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "maximum buffer size");
    CUN_UNITTEST_EXEC(ut, std::memset(buf, '\xFF', sizeof(buf)));
    CUN_UNITTEST_EVAL(ut, copy(buf, 4, "test") == buf);
    CUN_UNITTEST_EVAL(ut, std::strcmp(buf, "tes") == 0);
    CUN_UNITTEST_EVAL(ut, std::strcmp(buf, "test") < 0);
    CUN_UNITTEST_EXEC(ut, std::memset(buf, '\xFF', sizeof(buf)));
    CUN_UNITTEST_EVAL(ut, copy(buf, 5, "test") == buf);
    CUN_UNITTEST_EVAL(ut, std::strcmp(buf, "test") == 0);
    CUN_UNITTEST_EXEC(ut, std::memset(buf, '\xFF', sizeof(buf)));
    CUN_UNITTEST_EVAL(ut, copy(buf, 6, "test") == buf);
    CUN_UNITTEST_EVAL(ut, std::strcmp(buf, "test") == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "minimum source string");
    CUN_UNITTEST_EXEC(ut, std::memset(buf, '\xFF', sizeof(buf)));
    CUN_UNITTEST_EVAL(ut, copy(buf, sizeof(buf), "") == buf);
    CUN_UNITTEST_EVAL(ut, std::strcmp(buf, "") == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "maximum source string");
    CUN_UNITTEST_EXEC(ut, std::memset(buf, '\xFF', sizeof(buf)));
    CUN_UNITTEST_EVAL(ut, copy(buf, sizeof(buf), "DEADBE") == buf);
    CUN_UNITTEST_EVAL(ut, std::strcmp(buf, "DEADBE") == 0);
    CUN_UNITTEST_EXEC(ut, std::memset(buf, '\xFF', sizeof(buf)));
    CUN_UNITTEST_EVAL(ut, copy(buf, sizeof(buf), "DEADBEE") == buf);
    CUN_UNITTEST_EVAL(ut, std::strcmp(buf, "DEADBEE") == 0);
    CUN_UNITTEST_EXEC(ut, std::memset(buf, '\xFF', sizeof(buf)));
    CUN_UNITTEST_EVAL(ut, copy(buf, sizeof(buf), "DEADBEEF") == buf);
    CUN_UNITTEST_EVAL(ut, std::strcmp(buf, "DEADBEE") == 0);
    CUN_UNITTEST_EVAL(ut, std::strcmp(buf, "DEADBEEF") < 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

} // namespace

int main()
{
    auto ut = CUN_UNITTEST_MAKE();

    test_is_alpha(ut);
    test_is_blank(ut);
    test_is_space(ut);
    test_tol(ut);
    test_tol_strict(ut);
    test_copy(ut);

    return EXIT_SUCCESS;
}
