// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Utility functions.

#ifndef CUN_MISC_HPP_INCLUDED
#define CUN_MISC_HPP_INCLUDED

// C++ standard library
#include <string>
#include <utility>

// For this library
#include "misc_core.hpp"

namespace cun {

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

} // namespace cun

#endif // ndef CUN_MISC_HPP_INCLUDED
