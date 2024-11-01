/*
 * -*- coding: utf-8-with-signature-dos -*-
 * vim:fileencoding=utf-8:ff=dos
 *
 * C-string utility functions (ISO C interface).
 */

#ifndef CUN_CSTRUTIL_H_INCLUDED
#define CUN_CSTRUTIL_H_INCLUDED

/* C standard library */
#include <stdbool.h>
#include <stddef.h>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif /* def __cplusplus */

extern bool cun_cstrutil_is_alpha(const int c);
extern bool cun_cstrutil_is_blank(const int c);
extern bool cun_cstrutil_is_space(const int c);

extern bool cun_cstrutil_tol(const char * const s,
                             long * const retval,
                             char **endp,
                             const int base);

extern bool cun_cstrutil_tol_strict(const char * const s,
                                    long * const retval,
                                    const int base);

extern char *cun_cstrutil_copy(char * const buf,
                               const size_t bufsize,
                               const char * const src);

#ifdef __cplusplus
} /* extern "C" */
#endif /* def __cplusplus */

#endif /* ndef CUN_CSTRUTIL_H_INCLUDED */
