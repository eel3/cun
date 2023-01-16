// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// System tick utility.

// C++ standard library
#include <chrono>

// For this library
#include "system_tick.hpp"

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace {

template <typename T>
typename T::rep get_tick() noexcept
{
    const auto tp = std::chrono::steady_clock::now();
    const auto duration = std::chrono::duration_cast<T>(tp.time_since_epoch());

    return duration.count();
}

} // namespace

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

namespace system_tick {

std::chrono::milliseconds::rep millis() noexcept
{
    return get_tick<std::chrono::milliseconds>();
}

std::chrono::microseconds::rep micros() noexcept
{
    return get_tick<std::chrono::microseconds>();
}

std::chrono::nanoseconds::rep nanos() noexcept
{
    return get_tick<std::chrono::nanoseconds>();
}

} // namespace system_tick

} // namespace cun
