// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Repeat call function utility.

#ifndef CUN_REPEAT_CALL_HPP_INCLUDED
#define CUN_REPEAT_CALL_HPP_INCLUDED

// C++ standard library
#include <memory>

// For this library
#include "repeat_call_core.hpp"

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

namespace repeat_call {

/** Repeat call factory function (heap). */
template <typename ActionT>
constexpr auto alloc_create(const size_type repeat_times, ActionT&& action)
{
    return new cun::repeat_call::Context<ActionT>(repeat_times, forward<ActionT>(action));
}

/** Repeat call factory function (shared_ptr). */
template <typename ActionT>
constexpr auto shared_create(const size_type repeat_times, ActionT&& action)
{
    return std::make_shared<cun::repeat_call::Context<ActionT>>(repeat_times, forward<ActionT>(action));
}

/** Repeat call factory function (unique_ptr). */
template <typename ActionT>
constexpr auto unique_create(const size_type repeat_times, ActionT&& action)
{
    return std::make_unique<cun::repeat_call::Context<ActionT>>(repeat_times, forward<ActionT>(action));
}

} // namespace repeat_call

} // namespace cun

#endif // ndef CUN_REPEAT_CALL_HPP_INCLUDED
