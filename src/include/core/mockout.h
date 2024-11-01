/*
 * -*- coding: utf-8-with-signature-dos -*-
 * vim:fileencoding=utf-8:ff=dos
 *
 * Mock out helpers for unit test (ISO C interface).
 */

#ifndef CUN_MOCKOUT_H_INCLUDED
#define CUN_MOCKOUT_H_INCLUDED

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#define CUN_ADD_PREFIX(prefix, sym) prefix##sym

#define CUN_MOCKOUT(prefix, fun) CUN_ADD_PREFIX(prefix, fun)
#define CUN_RENAME(prefix, fun) CUN_ADD_PREFIX(prefix, fun)

#define CUN_MOCKABLE(fun) CUN_MOCKOUT(mock_, fun)
#define CUN_RENAMABLE(fun) CUN_RENAME(real_, fun)

#endif /* ndef CUN_MOCKOUT_H_INCLUDED */
