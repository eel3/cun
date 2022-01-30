// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// C-string utility functions.

#ifndef CUN_CSTRUTIL_HPP_INCLUDED
#define CUN_CSTRUTIL_HPP_INCLUDED

// C++ standard library
#include <cstddef>

// For this library
#include "cstrutil.h"

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

namespace cstrutil {

inline bool is_alpha(const int c) noexcept
{
    return cun_cstrutil_is_alpha(c);
}

inline bool is_blank(const int c) noexcept
{
    return cun_cstrutil_is_blank(c);
}

inline bool is_space(const int c) noexcept
{
    return cun_cstrutil_is_space(c);
}

inline bool tol(const char * const s,
                long& retval,
                char **endp = nullptr,
                const int base = 10) noexcept
{
    return cun_cstrutil_tol(s, &retval, endp, base);
}

inline bool tol_strict(const char * const s,
                       long& retval,
                       const int base = 10) noexcept
{
    return cun_cstrutil_tol_strict(s, &retval, base);
}

inline char *copy(char * const buf,
                  const std::size_t bufsize,
                  const char * const src) noexcept
{
    return cun_cstrutil_copy(buf, bufsize, src);
}

} // namespace cstrutil

} // namespace cun

#endif // ndef CUN_CSTRUTIL_HPP_INCLUDED
