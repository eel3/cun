// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// A logger implementation (Standard error).

#ifndef CUN_LOGGER_HPP_INCLUDED
#define CUN_LOGGER_HPP_INCLUDED

#if defined(_WIN32) || defined(_WIN64)
#   if !defined(__MINGW32__) && !defined(__MINGW64__)
#       ifndef _CRT_SECURE_NO_WARNINGS
#           define _CRT_SECURE_NO_WARNINGS
#       endif /* ndef _CRT_SECURE_NO_WARNINGS */
#   endif /* !defined(__MINGW32__) && !defined(__MINGW64__) */
#endif /* defined(_WIN32) || defined(_WIN64) */

// C++ standard library
#include <cassert>
#include <chrono>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

inline namespace logger {

/** A logger class. */
class Logger final {
private:
    bool m_opened { false };
    std::FILE * const m_out { stderr };
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
        {
            using std::chrono::system_clock;

            const auto now = system_clock::to_time_t(system_clock::now());
            const auto tmp = std::localtime(&now);
            fmt2 << std::put_time(tmp, "%Y-%m-%dT%H:%M:%S%z: ");
        }
        fmt2 << "%s: <%s> " << fmt << std::endl;

        (void) std::fprintf(m_out, fmt2.str().c_str(), m_tag.c_str(), pri, args ...);
    }

public:
    Logger() = default;
    explicit Logger(std::FILE * const out) : m_out(out) {
        if (out == nullptr) {
            throw std::invalid_argument("nullptr is not allowed.");
        }
        /*NOTREACHED*/
    }

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
