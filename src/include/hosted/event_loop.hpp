// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// An event loop toolbox.

#ifndef EVENT_LOOP_HPP_INCLUDED
#define EVENT_LOOP_HPP_INCLUDED

// C++ standard library
#include <concepts>
#include <functional>
#include <future>
#include <map>
#include <thread>
#include <tuple>
#include <type_traits>
#include <utility>

// C++ user library
#include "mailbox.hpp"

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

inline namespace event_loop {

/** A concept for pointer like objects. */
template <typename T>
concept PointerLike = requires(T p) {
    *p;
    p.operator->();
    { p == nullptr } -> std::convertible_to<bool>;
    { p != nullptr } -> std::convertible_to<bool>;
    { static_cast<bool>(p) } -> std::same_as<bool>;
};

/** A concept for EventLoop's context pointers. */
template <typename T>
concept ContextPtr =
    std::is_pointer_v<T> ||
    PointerLike<T>;

/** Event loop toolbox class. */
template <
    typename EventTypeT,
    ContextPtr ContextPtrT = void *,
    typename ReturnT = bool,
    ReturnT ERROR = false,
    EventTypeT ON_DESTROY = EventTypeT::on_destroy_event_loop
>
class EventLoop {
public:
    using event_proc = std::function<ReturnT (ContextPtrT, void *, void *)>;

private:
    using mail_type = std::tuple<EventTypeT, std::promise<ReturnT>, void *, void *>;

    ContextPtrT m_context;
    Mailbox<mail_type> m_mailbox;
    std::map<EventTypeT, event_proc> m_event_entry;
    std::thread m_thread;

    void main_loop() noexcept {
        using std::get;

        for (;;) {
            mail_type mail;

            m_mailbox.pop(mail);
            const auto request = get<0>(mail);

            auto retval = ERROR;
            auto p = m_event_entry.find(request);
            if (p != m_event_entry.end()) {
                retval = p->second(m_context, get<2>(mail), get<3>(mail));
            }

            auto pr = std::move(get<1>(mail));
            pr.set_value(retval);

            if (request == ON_DESTROY) {
                break;
            }
        }
    }

    static mail_type to_mail(const EventTypeT type,
                             std::promise<ReturnT> pr,
                             void *args = nullptr,
                             void *results = nullptr) noexcept {
        return std::make_tuple(type, std::move(pr), args, results);
    }

public:
    EventLoop(std::map<EventTypeT, event_proc> event_entry = {},
              ContextPtrT context = nullptr) :
        m_context { context },
        m_event_entry { event_entry } {
        m_thread = std::thread { [this]{ main_loop(); } };
    }

    virtual ~EventLoop() {
        (void) post_event(ON_DESTROY);
        m_thread.join();
    }

    ReturnT send_event(const EventTypeT type,
                       void *args = nullptr,
                       void *results = nullptr) noexcept {
        try {
            std::promise<ReturnT> pr;
            auto fu = pr.get_future();
            auto mail = to_mail(type, std::move(pr), args, results);
            m_mailbox.emplace(std::move(mail));
            return fu.get();
        } catch (...) {
            return false;
        }
    }

    ReturnT post_event(const EventTypeT type,
                       void *args = nullptr) noexcept {
        try {
            std::promise<ReturnT> pr;
            auto mail = to_mail(type, std::move(pr), args);
            m_mailbox.emplace(std::move(mail));
            return true;
        } catch (...) {
            return false;
        }
    }
};

} // inline namespace event_loop

} // namespace cun

#endif // ndef EVENT_LOOP_HPP_INCLUDED
