// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// A time measuring class.

#ifndef CUN_TIME_MEASURING_HPP_INCLUDED
#define CUN_TIME_MEASURING_HPP_INCLUDED

// C++ standard library
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <string>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

inline namespace time_measuring {

/** A time measuring base class. */
template <
    std::size_t MAX_LOG,
    typename UNIT,
    typename CLOCK
>
class TimeMeasuring {
    static_assert(MAX_LOG > 0, "TimeMeasuring: 0 size log buffer is not allowed.");

public:
    using duration = typename CLOCK::duration;
    using size_type = std::size_t;

    struct report_type final {
        size_type num_data;
        UNIT min;
        UNIT max;
        UNIT mean;
        UNIT stdev;
    };

protected:
    const std::string m_tag;

    duration m_data[MAX_LOG];
    size_type m_num_log { 0 };
    size_type m_wp { 0 };

public:
    TimeMeasuring() : TimeMeasuring("") {};

    explicit TimeMeasuring(const std::string& tag) : m_tag { tag } {}
    explicit TimeMeasuring(std::string&& tag) : m_tag { tag } {}

    const char *c_tag() const noexcept {
        return m_tag.c_str();
    }

    virtual void clear() noexcept {
        this->m_num_log = 0;
        this->m_wp = 0;
    }

    bool empty() const noexcept {
        return size() == 0;
    }

    bool make_report(report_type& report) const noexcept {
        using std::chrono::duration_cast;

        if (empty()) {
            return false;
        }

        report.num_data = m_num_log;

        auto min = duration::max();
        auto max = duration::min();
        auto total = duration::zero();

        for (size_type i = 0; i < m_num_log; i++) {
            const auto& n = m_data[i];
            min = std::min(min, n);
            max = std::max(max, n);
            total += n;
        }
        report.min = duration_cast<UNIT>(min);
        report.max = duration_cast<UNIT>(max);
        const auto mean = total / m_num_log;
        report.mean = duration_cast<UNIT>(mean);

        total = duration::zero();
        for (size_type i = 0; i < m_num_log; i++) {
            const auto n = m_data[i] - mean;
            total += n * n.count();
        }
        const auto variance = total / m_num_log;
        const auto stdev = sqrt(static_cast<double>(variance.count()));
        report.stdev = duration_cast<UNIT>(duration { static_cast<typename duration::rep>(stdev) });

        return true;
    }

    size_type max_size() const noexcept {
        return MAX_LOG;
    }

    size_type size() const noexcept {
        return m_num_log;
    }

    const std::string& tag() const noexcept {
        return m_tag;
    }
};

/** An elapsed time measuring class. */
template <
    std::size_t MAX_LOG,
    typename UNIT = std::chrono::microseconds,
    typename CLOCK = std::chrono::steady_clock
>
class ElapsedTime final : public TimeMeasuring<MAX_LOG, UNIT, CLOCK> {
private:
    using super = TimeMeasuring<MAX_LOG, UNIT, CLOCK>;
    using time_point = typename CLOCK::time_point;

    time_point m_begin_time;
    bool m_being_measured { false };

public:
    using super::TimeMeasuring;

    virtual void clear() noexcept override {
        super::clear();
        m_being_measured = false;
    }

    void notify_begin() noexcept {
        m_begin_time = CLOCK::now();
        this->m_being_measured = true;
    }

    void notify_end() noexcept {
        if (!this->m_being_measured) {
            return;
        }

        this->m_data[this->m_wp++] = CLOCK::now() - m_begin_time;
        if (this->m_wp >= MAX_LOG) {
            this->m_wp = 0;
        }
        if (this->m_num_log < MAX_LOG) {
            this->m_num_log++;
        }

        this->m_being_measured = false;
    }
};

/** A time interval measuring class. */
template <
    std::size_t MAX_LOG,
    typename UNIT = std::chrono::microseconds,
    typename CLOCK = std::chrono::steady_clock
>
class TimeInterval final : public TimeMeasuring<MAX_LOG, UNIT, CLOCK> {
private:
    using super = TimeMeasuring<MAX_LOG, UNIT, CLOCK>;
    using time_point = typename CLOCK::time_point;

    time_point m_begin_time;
    bool m_being_measured { false };

public:
    using super::TimeMeasuring;

    virtual void clear() noexcept override {
        super::clear();
        m_being_measured = false;
    }

    void emit() {
        if (!this->m_being_measured) {
            m_begin_time = CLOCK::now();
            this->m_being_measured = true;
        } else {
            const auto current_time = CLOCK::now();
            this->m_data[this->m_wp++] = current_time - m_begin_time;
            m_begin_time = current_time;
            if (this->m_wp >= MAX_LOG) {
                this->m_wp = 0;
            }
            if (this->m_num_log < MAX_LOG) {
                this->m_num_log++;
            }
        }
    }
};

} // inline namespace time_measuring

} // namespace cun

#endif // ndef CUN_TIME_MEASURING_HPP_INCLUDED
