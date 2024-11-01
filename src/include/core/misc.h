/*
 * -*- coding: utf-8-with-signature-dos -*-
 * vim:fileencoding=utf-8:ff=dos
 *
 * Utility functions (ISO C interface).
 */

#ifndef CUN_MISC_H_INCLUDED
#define CUN_MISC_H_INCLUDED

/* C standard library */
#include <string.h>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#define CUN_BZERO(p, size) \
    ((void) memset((p), 0, (size)))

#define CUN_CSTREQ(s1, s2) \
    (((s1) == (s2)) || \
     (((s1) != NULL) && \
      ((s2) != NULL) && \
      (((s1)[0] == (s2)[0]) && (strcmp((s1), (s2)) == 0))))

#define CUN_NELEMS(ary) \
    (sizeof(ary) / sizeof((ary)[0]))

#define CUN_STR(x)  #x

#define CUN_XSTR(x) CUN_STR(x)

#endif /* ndef CUN_MISC_H_INCLUDED */
