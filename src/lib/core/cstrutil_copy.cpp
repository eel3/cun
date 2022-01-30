// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// C-string utility functions - copy.

// C++ standard library
#include <cstring>

// For this library
#include "cstrutil.h"

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

extern "C" {

char *cun_cstrutil_copy(char * const buf,
                        const size_t bufsize,
                        const char * const src)
{
    if ((buf != nullptr) && (bufsize > 0) && (src != nullptr)) {
        buf[0] = '\0';
        (void) std::strncat(buf, src, bufsize - 1);
    }

    return buf;
}

} // extern "C"
