// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Utility functions.

#ifndef CUN_MISC_HPP_INCLUDED
#define CUN_MISC_HPP_INCLUDED

// C++ standard library
#include <chrono>
#include <string>
#include <thread>
#include <utility>

// For this library
#include "misc_core.hpp"

namespace cun {

inline namespace misc {

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

extern std::string basename(const std::string& s);
extern std::string basename(const char * const s);

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

template <typename T>
constexpr bool within_range(const T& n, const std::pair<T, T>& range) noexcept
{
    return cun::within_range(n, range.first, range.second);
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

template <typename T>
constexpr const T remap_range(const T& n,
                              const std::pair<T, T>& in_range,
                              const std::pair<T, T>& out_range) noexcept
{
    return cun::remap_range(n, in_range.first, in_range.second, out_range.first, out_range.second);
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

template <typename RepT, typename PeriodT, typename PredicateT>
constexpr void wait_until(const std::chrono::duration<RepT, PeriodT>& poll_interval, PredicateT pred)
{
    while (!pred()) {
        std::this_thread::sleep_for(poll_interval);
    }
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

template <typename PredicateT>
constexpr void wait_while(PredicateT pred)
{
    while (pred()) {
        std::this_thread::sleep_for(std::chrono::milliseconds { 1 });
    }
}

} // inline namespace misc

} // namespace cun

#endif // ndef CUN_MISC_HPP_INCLUDED
