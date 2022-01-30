// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// A logger implementation (Unix syslog).

#ifndef CUN_LOGGER_HPP_INCLUDED
#define CUN_LOGGER_HPP_INCLUDED

// C++ standard library
#include <cassert>
#include <sstream>

// Unix system call and library
#include <syslog.h>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

/** A logger class. */
class Logger final {
private:
    const int m_facility { LOG_LOCAL7 };
    bool m_opened { false };

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

        syslog(pri1, fmt2.str().c_str(), pri2, args ...);
    }

public:
    Logger() = default;
    explicit Logger(const int facility) : m_facility(facility) {}

    bool open(const char * const tag) noexcept {
        if (m_opened) {
            return true;
        }

        openlog(tag, LOG_PID | LOG_NDELAY, m_facility);
        m_opened = true;
        return true;
    }

    void close() noexcept {
        if (!m_opened) {
            return;
        }

        closelog();
        m_opened = false;
    }

    template <typename... Args>
    void verbose(const char * const fmt, Args ... args) const {
        debug_print(LOG_DEBUG, "verbose", fmt, args ...);
    }

    template <typename... Args>
    void debug(const char * const fmt, Args ... args) const {
        debug_print(LOG_DEBUG, "debug", fmt, args ...);
    }

    template <typename... Args>
    void info(const char * const fmt, Args ... args) const {
        debug_print(LOG_INFO, "info", fmt, args ...);
    }

    template <typename... Args>
    void notice(const char * const fmt, Args ... args) const {
        debug_print(LOG_NOTICE, "notice", fmt, args ...);
    }

    template <typename... Args>
    void warn(const char * const fmt, Args ... args) const {
        debug_print(LOG_WARNING, "warning", fmt, args ...);
    }

    template <typename... Args>
    void error(const char * const fmt, Args ... args) const {
        debug_print(LOG_ERR, "error", fmt, args ...);
    }

    template <typename... Args>
    void fatal(const char * const fmt, Args ... args) const {
        debug_print(LOG_CRIT, "fatal", fmt, args ...);
    }
};

} // namespace cun

#endif // ndef CUN_LOGGER_HPP_INCLUDED
