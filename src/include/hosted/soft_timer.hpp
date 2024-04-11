// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// A simple software timer.

#ifndef CUN_SOFT_TIMER_HPP_INCLUDED
#define CUN_SOFT_TIMER_HPP_INCLUDED

// C++ standard library
#include <atomic>
#include <chrono>
#include <cstdint>
#include <future>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <utility>

namespace cun {

namespace soft_timer {

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

// C++ standard library
using std::chrono::milliseconds;

/** Repeat count type. */
using size_type = std::int_fast32_t;

/** Repeat forever. */
constexpr size_type FOREVER { -1 };

/** Simple software timer context class. */
template <typename ActionT>
class SoftTimer final {
private:
    const size_type m_max_repeat_times { FOREVER };
    const milliseconds m_period;
    const bool m_run_immediately { false };

    ActionT m_action;

    std::atomic_bool m_expired { false };
    mutable std::mutex m_mutex;
    std::promise<void> m_pr_fin;
    size_type m_repeat_times { 0 };
    std::thread m_thread;
    bool m_working { false };

    static void check_period(const milliseconds& period) {
        if (period <= milliseconds::zero()) {
            throw std::invalid_argument("SoftTimer: period must be greater than 0");
            /*NOTREACHED*/
        }
    }

    static void check_repeat_times(const size_type repeat_times) {
        if (repeat_times == 0) {
            throw std::invalid_argument("SoftTimer: repeat times must not be 0");
            /*NOTREACHED*/
        }
    }

    void main_loop(std::promise<void>& pr_init,
                   std::future<void>& fu_fin,
                   std::chrono::steady_clock::time_point next_action_time) noexcept {
        m_expired = false;
        m_repeat_times = 0;

        pr_init.set_value();

        while (fu_fin.wait_until(next_action_time) == std::future_status::timeout) {
            next_action_time += m_period;

            if (m_expired) {
                continue;
            }

            try {
                m_action();
            } catch (...) {
                /*EMPTY*/
            }

            if (m_max_repeat_times >= 0) {
                m_repeat_times++;
                if (m_repeat_times >= m_max_repeat_times) {
                    m_expired = true;
                }
            }
        }
    }

public:
    SoftTimer() = delete;

    SoftTimer(const milliseconds& period, ActionT action) :
        m_period { period },
        m_action { action }
    {
        check_period(period);
    }

    SoftTimer(const milliseconds& period, const size_type repeat_times, ActionT action) :
        m_max_repeat_times { repeat_times >= 0 ? repeat_times : FOREVER },
        m_period { period },
        m_action { action }
    {
        check_period(period);
        check_repeat_times(repeat_times);
    }

    SoftTimer(const milliseconds& period, const size_type repeat_times, const bool run_immediately, ActionT action) :
        m_max_repeat_times { repeat_times >= 0 ? repeat_times : FOREVER },
        m_period { period },
        m_run_immediately { run_immediately },
        m_action { action }
    {
        check_period(period);
        check_repeat_times(repeat_times);
    }

    virtual ~SoftTimer() {
        (void) stop();
    }

    SoftTimer(const SoftTimer& other) :
        m_max_repeat_times { other.m_max_repeat_times },
        m_period { other.m_period },
        m_run_immediately { other.m_run_immediately },
        m_action { other.m_action }
    {
        std::lock_guard<std::mutex> lck { other.m_mutex };

        if (other.m_working) {
            throw std::invalid_argument("SoftTimer: cannot copy working timer");
        }
    }

    SoftTimer(SoftTimer&& other) :
        m_max_repeat_times { other.m_max_repeat_times },
        m_period { other.m_period },
        m_run_immediately { other.m_run_immediately },
        m_action { std::move(other.m_action) }
    {
        std::lock_guard<std::mutex> lck { other.m_mutex };

        if (other.m_working) {
            throw std::invalid_argument("SoftTimer: cannot move working timer");
        }
    }

    bool expired() const {
        std::lock_guard<std::mutex> lck { m_mutex };
        return m_working && m_expired;
    }

    bool restart() {
        (void) stop();
        return start();
    }

    bool start() {
        std::lock_guard<std::mutex> lck { m_mutex };
        if (m_working) {
            return false;
        }

        auto next_action_time = std::chrono::steady_clock::now();
        if (!m_run_immediately) {
            next_action_time += m_period;
        }

        std::promise<void> pr_init;
        auto fu_init = pr_init.get_future();

        m_pr_fin = std::promise<void> {};
        auto fu_fin = m_pr_fin.get_future();

        m_thread = std::thread { [this,
                                  pr = std::move(pr_init),
                                  fu = std::move(fu_fin),
                                  &next_action_time]() mutable {
            main_loop(pr, fu, next_action_time);
        }};
        fu_init.get();

        m_working = true;

        return true;
    };

    bool stop() {
        std::lock_guard<std::mutex> lck { m_mutex };
        if (!m_working) {
            return true;
        }

        m_pr_fin.set_value();
        m_thread.join();

        m_working = false;

        return true;
    };
};

/* ---------------------------------------------------------------------- */
/* Factory function (stack) */
/* ---------------------------------------------------------------------- */

/** Simple software timer factory function (stack). */
template <typename ActionT>
constexpr auto create(const milliseconds& period, ActionT action)
{
    return std::move(cun::soft_timer::SoftTimer<ActionT>(period, action));
}

/** Simple software timer factory function (stack). */
template <typename ActionT>
constexpr auto create(const milliseconds& period, const size_type repeat_times, ActionT action)
{
    return std::move(cun::soft_timer::SoftTimer<ActionT>(period, repeat_times, action));
}

/** Simple software timer factory function (stack). */
template <typename ActionT>
constexpr auto create(const milliseconds& period, const size_type repeat_times, const bool run_immediately, ActionT action)
{
    return std::move(cun::soft_timer::SoftTimer<ActionT>(period, repeat_times, run_immediately, action));
}

/* ---------------------------------------------------------------------- */
/* Factory function (heap) */
/* ---------------------------------------------------------------------- */

/** Simple software timer factory function (heap). */
template <typename ActionT>
constexpr auto alloc_create(const milliseconds& period, ActionT action)
{
    return new cun::soft_timer::SoftTimer<ActionT>(period, action);
}

/** Simple software timer factory function (heap). */
template <typename ActionT>
constexpr auto alloc_create(const milliseconds& period, const size_type repeat_times, ActionT action)
{
    return new cun::soft_timer::SoftTimer<ActionT>(period, repeat_times, action);
}

/** Simple software timer factory function (heap). */
template <typename ActionT>
constexpr auto alloc_create(const milliseconds& period, const size_type repeat_times, const bool run_immediately, ActionT action)
{
    return new cun::soft_timer::SoftTimer<ActionT>(period, repeat_times, run_immediately, action);
}

/* ---------------------------------------------------------------------- */
/* Factory function (shared_ptr) */
/* ---------------------------------------------------------------------- */

/** Simple software timer factory function (shared_ptr). */
template <typename ActionT>
constexpr auto shared_create(const milliseconds& period, ActionT action)
{
    return std::make_shared<cun::soft_timer::SoftTimer<ActionT>>(period, action);
}

/** Simple software timer factory function (shared_ptr). */
template <typename ActionT>
constexpr auto shared_create(const milliseconds& period, const size_type repeat_times, ActionT action)
{
    return std::make_shared<cun::soft_timer::SoftTimer<ActionT>>(period, repeat_times, action);
}

/** Simple software timer factory function (shared_ptr). */
template <typename ActionT>
constexpr auto shared_create(const milliseconds& period, const size_type repeat_times, const bool run_immediately, ActionT action)
{
    return std::make_shared<cun::soft_timer::SoftTimer<ActionT>>(period, repeat_times, run_immediately, action);
}

/* ---------------------------------------------------------------------- */
/* Factory function (unique_ptr) */
/* ---------------------------------------------------------------------- */

/** Simple software timer factory function (unique_ptr). */
template <typename ActionT>
constexpr auto unique_create(const milliseconds& period, ActionT action)
{
    return std::make_unique<cun::soft_timer::SoftTimer<ActionT>>(period, action);
}

/** Simple software timer factory function (unique_ptr). */
template <typename ActionT>
constexpr auto unique_create(const milliseconds& period, const size_type repeat_times, ActionT action)
{
    return std::make_unique<cun::soft_timer::SoftTimer<ActionT>>(period, repeat_times, action);
}

/** Simple software timer factory function (unique_ptr). */
template <typename ActionT>
constexpr auto unique_create(const milliseconds& period, const size_type repeat_times, const bool run_immediately, ActionT action)
{
    return std::make_unique<cun::soft_timer::SoftTimer<ActionT>>(period, repeat_times, run_immediately, action);
}

} // namespace soft_timer

} // namespace cun

#endif // ndef CUN_SOFT_TIMER_HPP_INCLUDED
