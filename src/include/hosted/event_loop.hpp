// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// An event loop toolbox.

#ifndef EVENT_LOOP_HPP_INCLUDED
#define EVENT_LOOP_HPP_INCLUDED

// C++ standard library
#include <any>
#include <cassert>
#include <concepts>
#include <functional>
#include <future>
#include <map>
#include <optional>
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

/** A concept for return value traits. */
template <typename T>
concept RVTraits = requires {
    typename T::type;
    { T::ok() } -> std::same_as<typename T::type>;
    { T::ng() } -> std::same_as<typename T::type>;
    { T::event_not_found() } -> std::same_as<typename T::type>;
};

/** A traits for return values (base). */
template <typename T>
struct ReturnTraits;

/** A traits for return values: bool. */
template<>
struct ReturnTraits<bool> {
    using type = bool;
    static type ok() noexcept { return true; }
    static type ng() noexcept { return false; }
    static type event_not_found() noexcept { return false; }
};

/** Event loop toolbox class. */
template <
    typename EventTypeT,
    ContextPtr ContextPtrT = void *,
    RVTraits RVTraitsT = ReturnTraits<bool>
>
class EventLoop {
public:
    using return_type = typename RVTraitsT::type;
    using event_proc = std::function<return_type (ContextPtrT, std::any&, std::any&)>;
    using event_entry = std::map<EventTypeT, event_proc>;

private:
    using promise_type = std::promise<return_type>;
    using mail_type = std::tuple<EventTypeT, std::optional<promise_type>, std::any, std::any>;

    ContextPtrT m_context;
    Mailbox<mail_type> m_mailbox;
    event_entry m_event_entry;
    std::jthread m_thread;

    void main_loop(const std::stop_token& stoken) noexcept {
        using std::get;

        for (;;) {
            mail_type mail;

            (void) m_mailbox.pop(mail, stoken);
            if (stoken.stop_requested()) {
                break;
            }
            const auto request = get<0>(mail);

            auto retval = RVTraitsT::event_not_found();
            auto p = m_event_entry.find(request);
            if (p != m_event_entry.end()) {
                retval = p->second(m_context, get<2>(mail), get<3>(mail));
            }

            if (auto pr = std::move(get<1>(mail)); pr) {
                pr->set_value(retval);
            }
        }
    }

    return_type send_event(const EventTypeT type, std::any&& args, std::any&& results) noexcept {
        try {
            if (m_thread.get_stop_token().stop_requested()) {
                return RVTraitsT::ng();
            }

            promise_type pr;
            auto fu = pr.get_future();
            auto mail = std::make_tuple(type, std::make_optional(std::move(pr)),
                                        std::move(args), std::move(results));
            m_mailbox.emplace(std::move(mail));
            return fu.get();
        } catch (...) {
            return RVTraitsT::ng();
        }
    }

    return_type post_event(const EventTypeT type, std::any&& args) noexcept {
        try {
            if (m_thread.get_stop_token().stop_requested()) {
                return RVTraitsT::ng();
            }

            auto mail = std::make_tuple(type, std::optional<promise_type> {},
                                        std::move(args), std::any {});
            m_mailbox.emplace(std::move(mail));
            return RVTraitsT::ok();
        } catch (...) {
            return RVTraitsT::ng();
        }
    }

public:
    explicit EventLoop(event_entry&& event_entry = {},
                       ContextPtrT context = nullptr) :
            m_context { context },
            m_event_entry { std::move(event_entry) } {
        m_thread = std::jthread { [this](auto stoken){ main_loop(stoken); } };
    }

    explicit EventLoop(const event_entry& event_entry,
                       ContextPtrT context = nullptr) :
            m_context { context },
            m_event_entry { event_entry } {
        m_thread = std::jthread { [this](auto stoken){ main_loop(stoken); } };
    }

    virtual ~EventLoop() {
        m_thread.request_stop();
        m_thread.join();
    }

    template <typename ArgsT, typename ResultsT>
    return_type send_event(const EventTypeT type, ArgsT&& args, ResultsT&& results) noexcept {
        return send_event(type,
                          std::make_any<std::decay_t<ArgsT>>(std::forward<ArgsT>(args)),
                          std::make_any<std::decay_t<ResultsT>>(std::forward<ResultsT>(results)));
    }

    template <typename ArgsT>
    return_type send_event(const EventTypeT type, ArgsT&& args) noexcept {
        return send_event(type,
                          std::make_any<std::decay_t<ArgsT>>(std::forward<ArgsT>(args)),
                          std::any {});
    }

    return_type send_event(const EventTypeT type) noexcept {
        return send_event(type, std::any {}, std::any {});
    }

    template <typename ArgsT>
    return_type post_event(const EventTypeT type, ArgsT&& args) noexcept {
        return post_event(type,
                          std::make_any<std::decay_t<ArgsT>>(std::forward<ArgsT>(args)));
    }

    return_type post_event(const EventTypeT type) noexcept {
        return post_event(type, std::any {});
    }
};

} // inline namespace event_loop

} // namespace cun

#endif // ndef EVENT_LOOP_HPP_INCLUDED
