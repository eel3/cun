// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Utility functions.

#ifndef CUN_MISC_CORE_HPP_INCLUDED
#define CUN_MISC_CORE_HPP_INCLUDED

// C++ standard library
#include <cassert>
#include <cstddef>
#include <type_traits>

namespace cun {

inline namespace misc {

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

template <typename T, std::size_t N>
constexpr std::size_t nelems(const T (&)[N]) noexcept
{
    return N;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

template <typename T>
constexpr const T& max(const T& x, const T& y) noexcept
{
    return (x > y) ? x : y;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

template <typename T>
constexpr const T& min(const T& x, const T& y) noexcept
{
    return (x < y) ? x : y;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

template <typename T>
constexpr bool within_range(const T& n, const T& low, const T& high) noexcept
{
    assert(low <= high);

    return (n >= low) && (n <= high);
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

template <typename T>
constexpr const T& clamp(const T& n, const T& low, const T& high) noexcept
{
    assert(low <= high);

    return cun::min(cun::max(n, low), high);
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

template <typename T>
constexpr const T& clamp_ex(const T& n,
                            const T& low,
                            const T& high,
                            const T& substitute) noexcept
{
    assert(low <= high);

    return cun::within_range(n, low, high) ? n : substitute;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

template <typename T>
constexpr const T remap_range(const T& n,
                              const T& in_low,
                              const T& in_high,
                              const T& out_low,
                              const T& out_high) noexcept
{
    static_assert(std::is_arithmetic<T>(), "cun::remap_range: T must be a arithmetic type.");

    assert((in_low <= in_high) &&
           cun::within_range(n, in_low, in_high) &&
           (out_low <= out_high));

    constexpr T MINSCALE = static_cast<T>(1);

    const auto in_scale =
        in_high == in_low ? MINSCALE : in_high - in_low;
    const auto out_scale =
        out_high == out_low ? MINSCALE : out_high - out_low;

    return (n - in_low) * out_scale / in_scale + out_low;
}

} // inline namespace misc

} // namespace cun

#endif // ndef CUN_MISC_CORE_HPP_INCLUDED
