// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Unit test utility.

#ifndef CUN_UNITTEST_HPP_INCLUDED
#define CUN_UNITTEST_HPP_INCLUDED

// C++ standard library
#include <cassert>
#include <cstdint>
#include <iostream>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

/** Utility class for unit testing. */
class UnitTest final {
private:
    static constexpr auto LINE =
        "// ------------------------------------------------------ //";
    static constexpr auto COMMENT = "// ";

    static constexpr auto NONE = "    ";
    static constexpr auto SOME = "--- ";
    static constexpr auto OK   = "OK  ";
    static constexpr auto NG   = "NG  ";

    std::ostream& m_out;
    std::uint32_t m_count { 0 };

public:
    UnitTest() noexcept : m_out { std::cout } {}
    explicit UnitTest(std::ostream& out) noexcept : m_out { out } {}

    void comment(const char * const s = "") const {
        assert(s != nullptr);
        m_out << NONE << COMMENT << s << std::endl;
    }

    void echo(const char * const s = "") const {
        assert(s != nullptr);
        m_out << NONE << s << std::endl;
    }

    void name(const char * const s = "") {
        assert(s != nullptr);
        m_out << SOME << "Test No. " << ++m_count << " : " << s << std::endl;
    }

    void nl() const {
        m_out << std::endl;
    }

    void reset() noexcept {
        m_count = 0;
    }

    void testlog(const char * const expr) const {
        assert(expr != nullptr);
        m_out << NONE << expr << std::endl;
    }

    void testlog(const char * const expr, const int eval) const {
        assert(expr != nullptr);
        m_out << (eval ? OK : NG) << expr << std::endl;
    }

    void title(const char * const s = "") const {
        assert(s != nullptr);
        using std::endl;
        m_out << LINE << endl
              << COMMENT << s << endl
              << LINE << endl;
    }
};

} // namespace cun

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#define CUN_UNITTEST_COMMENT(ut, s) \
    ut.comment(s)

#define CUN_UNITTEST_ECHO(ut, s) \
    ut.echo(s)

#define CUN_UNITTEST_EVAL(ut, ...) \
    ut.testlog(#__VA_ARGS__, (__VA_ARGS__)) 

#define CUN_UNITTEST_EXEC(ut, ...) \
    ut.testlog(#__VA_ARGS__); __VA_ARGS__

#define CUN_UNITTEST_MAKE(...) \
    cun::UnitTest(__VA_ARGS__)

#define CUN_UNITTEST_NAME(ut, s) \
    ut.name(s)

#define CUN_UNITTEST_NL(ut) \
    ut.nl()

#define CUN_UNITTEST_RESET(ut) \
    ut.reset()

#define CUN_UNITTEST_TITLE(ut, s) \
    ut.title(s)

#endif // ndef CUN_UNITTEST_HPP_INCLUDED
