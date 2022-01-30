// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// std::string utility functions - stoXXX wrappers.

// C++ standard library
#include <stdexcept>

// For this library
#include "strutil.hpp"

namespace cun {

namespace strutil {

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

long tol_strict(const std::string& s, const int base)
{
    std::size_t idx { 0 };

    const auto n = std::stol(s, &idx, base);
    if (idx != s.size()) {
        throw std::invalid_argument(s);
        /*NOTREACHED*/
    }

    return n;
}

bool tol_safe(const std::string& s,
              long& retval,
              std::size_t * const idx,
              const int base) noexcept
{
    try {
        retval = std::stol(s, idx, base);
        return true;
    } catch (...) {
        return false;
    }
    /*NOTREACHED*/
}

bool tol_safe_strict(const std::string& s,
                     long& retval,
                     const int base) noexcept
{
    try {
        retval = cun::strutil::tol_strict(s, base);
        return true;
    } catch (...) {
        return false;
    }
    /*NOTREACHED*/
}

} // namespace strutil

} // namespace cun
