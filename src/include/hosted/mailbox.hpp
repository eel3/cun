// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// An inter-thread communication mailbox.

#ifndef CUN_MAILBOX_HPP_INCLUDED
#define CUN_MAILBOX_HPP_INCLUDED

// C++ standard library
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <utility>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

inline namespace mailbox {

/** Inter-thread communication mailbox class. */
template <typename T>
class Mailbox final {
public:
    using size_type = typename std::queue<T>::size_type;
    using value_type = T;

private:
    mutable std::mutex m_mutex;
    std::condition_variable m_cond;
    std::queue<value_type> m_queue;

public:
    void clear() {
        std::lock_guard<std::mutex> lck(m_mutex);
        std::queue<value_type> empty;
        std::swap(m_queue, empty);
    }

    bool empty() const noexcept {
        std::lock_guard<std::mutex> lck(m_mutex);
        return m_queue.empty();
    }

    value_type pop() {
        value_type val;
        pop(val);
        return val;
    }

    void pop(value_type& val) {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_cond.wait(lck, [this]{ return !m_queue.empty(); });
        val = std::move(m_queue.front());
        m_queue.pop();
    }

    bool pop(value_type& val, const std::chrono::milliseconds::rep& timeout) {
        std::unique_lock<std::mutex> lck(m_mutex);
        const auto have_some =
            m_cond.wait_for(lck, std::chrono::milliseconds { timeout }, [this]{
                return !m_queue.empty();
            });
        if (have_some) {
            val = std::move(m_queue.front());
            m_queue.pop();
        }
        return have_some;
    }

    void push(const value_type& val) {
        std::lock_guard<std::mutex> lck(m_mutex);
        m_queue.push(val);
        m_cond.notify_one();
    }

    void push(value_type&& val) {
        std::lock_guard<std::mutex> lck(m_mutex);
        m_queue.push(std::move(val));
        m_cond.notify_one();
    }

    template <typename... Args>
    void emplace(Args&& ... args) {
        std::lock_guard<std::mutex> lck(m_mutex);
        m_queue.emplace(std::forward<Args>(args) ...);
        m_cond.notify_one();
    }

    size_type size() const noexcept {
        std::lock_guard<std::mutex> lck(m_mutex);
        return m_queue.size();
    }

    bool try_pop(value_type& val) {
        std::lock_guard<std::mutex> lck(m_mutex);
        if (m_queue.empty()) {
            return false;
        };
        val = std::move(m_queue.front());
        m_queue.pop();
        return true;
    }
};

} // inline namespace mailbox

} // namespace cun

#endif // ndef CUN_MAILBOX_HPP_INCLUDED
