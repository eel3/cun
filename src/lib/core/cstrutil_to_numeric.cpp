// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// C-string utility functions - string to numeric.

// C++ standard library
#include <cerrno>
#include <climits>
#include <cstdlib>

// For this library
#include "cstrutil.h"

extern "C" {

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

bool cun_cstrutil_tol(const char * const s,
                      long * const retval,
                      char **endp,
                      const int base)
{
    if ((s == nullptr)
        || (retval == nullptr)
        || ((base != 0) && ((base < 2) || (base > 36)))) {
        return false;
    }

    char *ep { nullptr };

    errno = 0;
    const auto n = std::strtol(s, &ep, base);
    if ((n == 0) && (const_cast<const char *>(ep) == s)) {
        return false;
    }
    if (((n == LONG_MAX) || (n == LONG_MIN)) && (errno == ERANGE)) {
        return false;
    }

    *retval = n;
    if (endp != nullptr) {
        *endp = ep;
    }

    return true;
}

bool cun_cstrutil_tol_strict(const char * const s,
                             long * const retval,
                             const int base)
{
    long n { 0 };
    char *ep { nullptr };

    const auto ok = cun_cstrutil_tol(s, &n, &ep, base);
    if (!ok || (*ep != '\0')) {
        return false;
    }

    *retval = n;

    return true;
}

} // extern "C"
