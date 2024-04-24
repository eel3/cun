// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Repeat call function utility.

#ifndef CUN_REPEAT_CALL_CORE_HPP_INCLUDED
#define CUN_REPEAT_CALL_CORE_HPP_INCLUDED

// C++ standard library
#include <cstdint>
#include <type_traits>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

namespace repeat_call {

/** std::forward alternative. */
template <typename T>
constexpr T&& forward(std::remove_reference_t<T>& t) noexcept
{
    return static_cast<T&&>(t);
}

/** Repeat count type. */
using size_type = std::int_fast32_t;

/** Repeat forever. */
constexpr size_type FOREVER { -1 };

/** Repeat call context class. */
template <typename ActionT>
class Context final {
private:
    const size_type MAX_REPEAT_TIMES { FOREVER };

    bool m_working { true };
    size_type m_repeat_times { 0 };

    ActionT m_action;

public:
    Context() = delete;

    Context(const size_type repeat_times, ActionT&& action) :
        MAX_REPEAT_TIMES { repeat_times },
        m_working { repeat_times != 0 },
        m_action { action } {}

    bool expired() const noexcept {
        return !m_working;
    }

    bool resume() {
        if (!m_working) {
            return false;
        }

        if (m_action()) {
            m_repeat_times++;
            if ((MAX_REPEAT_TIMES >= 0) && (m_repeat_times >= MAX_REPEAT_TIMES)) {
                m_working = false;
            }
        } else {
            m_working = false;
        }
        return true;
    }
};

/** Repeat call factory function (stack). */
template <typename ActionT>
constexpr auto create(const size_type repeat_times, ActionT&& action)
{
    return cun::repeat_call::Context<ActionT>(repeat_times, forward<ActionT>(action));
}

} // namespace repeat_call

} // namespace cun

#endif // ndef CUN_REPEAT_CALL_CORE_HPP_INCLUDED
