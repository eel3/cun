// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// A logger implementation (debugger on Windows).

#ifndef CUN_LOGGER_HPP_INCLUDED
#define CUN_LOGGER_HPP_INCLUDED

// C++ standard library
#include <cassert>
#include <cstdio>
#include <sstream>
#include <string>
#include <vector>

// Windows API and library
#include <windows.h>
#include <debugapi.h>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

inline namespace logger {

/** A logger class. */
class Logger final {
private:
    bool m_opened { false };
    std::string m_tag { "" };

    template <typename... Args>
    void debug_print(const char * const pri,
                     const char * const fmt,
                     Args ... args) const {
        assert((pri != nullptr) && (fmt != nullptr));

        if (!m_opened) {
            return;
        }

        std::ostringstream fmt2;
        fmt2 << "%s: <%s> " << fmt;

        const auto len = _scprintf(fmt2.str().c_str(), m_tag.c_str(), pri, args ...) + 1;
        assert(len > 0);
        std::vector<char> buf(static_cast<size_t>(len), '\0');
        (void) sprintf_s(buf.data(), static_cast<size_t>(len), fmt2.str().c_str(), m_tag.c_str(), pri, args ...);

        OutputDebugStringA(buf.data());
    }

public:
    bool open(const char * const tag) noexcept {
        if (m_opened) {
            return true;
        }

        if (tag == nullptr) {
            m_tag.clear();
        } else {
            m_tag = tag;
        }

        m_opened = true;
        return true;
    }

    void close() noexcept {
        m_opened = false;
    }

    template <typename... Args>
    void verbose(const char * const fmt, Args ... args) const {
        debug_print("verbose", fmt, args ...);
    }

    template <typename... Args>
    void debug(const char * const fmt, Args ... args) const {
        debug_print("debug", fmt, args ...);
    }

    template <typename... Args>
    void info(const char * const fmt, Args ... args) const {
        debug_print("info", fmt, args ...);
    }

    template <typename... Args>
    void notice(const char * const fmt, Args ... args) const {
        debug_print("notice", fmt, args ...);
    }

    template <typename... Args>
    void warn(const char * const fmt, Args ... args) const {
        debug_print("warning", fmt, args ...);
    }

    template <typename... Args>
    void error(const char * const fmt, Args ... args) const {
        debug_print("error", fmt, args ...);
    }

    template <typename... Args>
    void fatal(const char * const fmt, Args ... args) const {
        debug_print("fatal", fmt, args ...);
    }
};

} // inline namespace logger

} // namespace cun

#endif // ndef CUN_LOGGER_HPP_INCLUDED
