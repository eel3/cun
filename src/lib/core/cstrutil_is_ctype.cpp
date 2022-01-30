// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// C-string utility functions - ctype for ASCII code ("C" locale).

// C++ standard library
#include <cassert>
#include <cstring>

// For this library
#include "cstrutil.h"

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace {

inline bool cstrutil_is_ctype(const int c, const char * const c_table) noexcept
{
    return (c != '\0') && (std::strchr(c_table, c) != nullptr);
}

} // namespace

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

extern "C" {

bool cun_cstrutil_is_alpha(const int c)
{
    return cstrutil_is_ctype(c, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
}

bool cun_cstrutil_is_blank(const int c)
{
    return cstrutil_is_ctype(c, "\t ");
}

bool cun_cstrutil_is_space(const int c)
{
    return cstrutil_is_ctype(c, "\t\n\v\f\r ");
}

} // extern "C"
