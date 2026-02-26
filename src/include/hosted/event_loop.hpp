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
#include <thread>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>

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
    typename UserEventT,
    ContextPtr ContextPtrT = void *,
    typename ReturnT = bool,
    ReturnT OK = true,
    ReturnT ERROR = false
>
class EventLoop {
public:
    using event_proc = std::function<ReturnT (ContextPtrT, std::any&, std::any&)>;
    using event_entry = std::map<UserEventT, event_proc>;

private:
    enum class InternalEvent {
        destroy
    };
    using event_type = std::variant<InternalEvent, UserEventT>;
    using mail_type = std::tuple<event_type, std::promise<ReturnT>, std::any, std::any>;

    ContextPtrT m_context;
    Mailbox<mail_type> m_mailbox;
    event_entry m_event_entry;
    std::thread m_thread;

    void main_loop() noexcept {
        using std::get;

        for (;;) {
            mail_type mail;

            m_mailbox.pop(mail);
            const auto event = get<0>(mail);
            if (std::holds_alternative<InternalEvent>(event)) {
                assert(get<InternalEvent>(event) == InternalEvent::destroy);
                break;
            }

            assert(std::holds_alternative<UserEventT>(event));
            const auto request = get<UserEventT>(event);

            auto retval = ERROR;
            auto p = m_event_entry.find(request);
            if (p != m_event_entry.end()) {
                retval = p->second(m_context, get<2>(mail), get<3>(mail));
            }

            auto pr = std::move(get<1>(mail));
            pr.set_value(retval);
        }
    }

    ReturnT send_event(event_type&& type, std::any&& args, std::any&& results) noexcept {
        try {
            std::promise<ReturnT> pr;
            auto fu = pr.get_future();
            auto mail = std::make_tuple(type, std::move(pr), args, results);
            m_mailbox.emplace(std::move(mail));
            return fu.get();
        } catch (...) {
            return ERROR;
        }
    }

    ReturnT post_event(event_type&& type, std::any&& args) noexcept {
        try {
            std::promise<ReturnT> pr;
            auto mail = std::make_tuple(type, std::move(pr), args, std::any {});
            m_mailbox.emplace(std::move(mail));
            return OK;
        } catch (...) {
            return ERROR;
        }
    }

public:
    EventLoop(event_entry event_entry = {},
              ContextPtrT context = nullptr) :
        m_context { context },
        m_event_entry { event_entry } {
        m_thread = std::thread { [this]{ main_loop(); } };
    }

    virtual ~EventLoop() {
        (void) post_event(event_type { InternalEvent::destroy }, std::any {});
        m_thread.join();
    }

    template <typename ArgsT, typename ResultsT>
    ReturnT send_event(const UserEventT type, ArgsT&& args, ResultsT&& results) noexcept {
        return send_event(event_type { type },
                          std::make_any<ArgsT>(std::forward<ArgsT>(args)),
                          std::make_any<ResultsT>(std::forward<ResultsT>(results)));
    }

    template <typename ArgsT>
    ReturnT send_event(const UserEventT type, ArgsT&& args) noexcept {
        return send_event(event_type { type },
                          std::make_any<ArgsT>(std::forward<ArgsT>(args)),
                          std::any {});
    }

    ReturnT send_event(const UserEventT type) noexcept {
        return send_event(event_type { type }, std::any {}, std::any {});
    }

    template <typename ArgsT>
    ReturnT post_event(const UserEventT type, ArgsT&& args) noexcept {
        return post_event(event_type { type }, std::make_any<ArgsT>(std::forward<ArgsT>(args)));
    }

    ReturnT post_event(const UserEventT type) noexcept {
        return post_event(event_type { type }, std::any {});
    }
};

} // inline namespace event_loop

} // namespace cun

#endif // ndef EVENT_LOOP_HPP_INCLUDED
