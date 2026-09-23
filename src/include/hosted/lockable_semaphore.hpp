// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// An inter-thread lockable counting semaphore.

#ifndef CUN_LOCKABLE_SEMAPHORE_HPP_INCLUDED
#define CUN_LOCKABLE_SEMAPHORE_HPP_INCLUDED

// C++ standard library
#include <condition_variable>
#include <cstddef>
#include <limits>
#include <mutex>
#include <stdexcept>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

inline namespace lockable_semaphore {

/** Inter-thread lockable counting semaphore class. */
template <std::ptrdiff_t MAX = std::numeric_limits<std::ptrdiff_t>::max()>
class LockableSemaphore final {
    static_assert(MAX >= 1, "LockableSemaphore: The least maximum value must be greater than or equal to 1.");

private:
    std::condition_variable m_cond;
    std::ptrdiff_t m_count { 0 };
    std::mutex m_mutex;
    std::unique_lock<std::mutex> m_lock { m_mutex, std::defer_lock };

public:
    static constexpr std::ptrdiff_t max() noexcept { return MAX; }

    void acquire() {
        std::unique_lock<std::mutex> lck { m_mutex };
        m_cond.wait(lck, [this]{ return m_count < MAX; });
        m_count++;
        m_cond.notify_all();
    }

    void lock() {
        m_lock.lock();
        m_cond.wait(m_lock, [this]{ return m_count <= 0; });
    }

    bool locked() const noexcept {
        return m_lock.owns_lock();
    }

    void release(std::ptrdiff_t update = 1) {
        if (update < 0) {
            throw std::invalid_argument("argument must be greater or equal to 0");
        }
        if (update == 0) {
            return;
        }

        std::lock_guard<std::mutex> lck { m_mutex };

        if (update > m_count) {
            throw std::invalid_argument("argument is too big");
        }
        m_count -= update;
        m_cond.notify_all();
    }

    bool try_acquire() {
        std::unique_lock<std::mutex> lck { m_mutex, std::try_to_lock };
        if (!lck) {
            return false;
        }
        if (m_count >= MAX) {
            return false;
        }
        m_count++;
        m_cond.notify_all();
        return true;
    }

    bool try_lock() {
        try {
            if (!m_lock.try_lock()) {
                return false;
            }
        } catch (...) {
            return false;
        }
        if (m_count > 0) {
            m_lock.unlock();
            return false;
        }
        return true;
    }

    bool try_release(std::ptrdiff_t update = 1) {
        if (update < 0) {
            throw std::invalid_argument("argument must be greater or equal to 0");
        }
        if (update == 0) {
            return true;
        }

        std::unique_lock<std::mutex> lck { m_mutex, std::try_to_lock };
        if (!lck) {
            return false;
        }

        if (update > m_count) {
            throw std::invalid_argument("argument is too big");
        }
        m_count -= update;
        m_cond.notify_all();
        return true;
    }

    void unlock() {
        try {
            m_lock.unlock();
        } catch (...) {
            /*EMPTY*/
        }
    }
};

} // inline namespace lockable_semaphore

} // namespace cun

#endif // ndef CUN_LOCKABLE_SEMAPHORE_HPP_INCLUDED
