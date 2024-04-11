// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// A logger implementation (Android NDK).

#ifndef CUN_LOGGER_HPP_INCLUDED
#define CUN_LOGGER_HPP_INCLUDED

// C++ standard library
#include <cassert>
#include <sstream>
#include <string>

// Android system call and library
#include <android/log.h>

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
    void debug_print(const int pri1,
                     const char * const pri2,
                     const char * const fmt,
                     Args ... args) const {
        assert((pri2 != nullptr) && (fmt != nullptr));

        if (!m_opened) {
            return;
        }

        std::ostringstream fmt2;
        fmt2 << "<%s> " << fmt;

        (void) __android_log_print(pri1, m_tag.c_str(), fmt2.str().c_str(), pri2, args ...);
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
        debug_print(ANDROID_LOG_VERBOSE, "verbose", fmt, args ...);
    }

    template <typename... Args>
    void debug(const char * const fmt, Args ... args) const {
        debug_print(ANDROID_LOG_DEBUG, "debug", fmt, args ...);
    }

    template <typename... Args>
    void info(const char * const fmt, Args ... args) const {
        debug_print(ANDROID_LOG_INFO, "info", fmt, args ...);
    }

    template <typename... Args>
    void notice(const char * const fmt, Args ... args) const {
        debug_print(ANDROID_LOG_INFO, "notice", fmt, args ...);
    }

    template <typename... Args>
    void warn(const char * const fmt, Args ... args) const {
        debug_print(ANDROID_LOG_WARN, "warning", fmt, args ...);
    }

    template <typename... Args>
    void error(const char * const fmt, Args ... args) const {
        debug_print(ANDROID_LOG_ERROR, "error", fmt, args ...);
    }

    template <typename... Args>
    void fatal(const char * const fmt, Args ... args) const {
        debug_print(ANDROID_LOG_FATAL, "fatal", fmt, args ...);
    }
};

} // inline namespace logger

} // namespace cun

#endif // ndef CUN_LOGGER_HPP_INCLUDED
