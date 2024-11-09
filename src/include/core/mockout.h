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

#define CUN_MOCKOUT(prefix, sym) CUN_ADD_PREFIX(prefix, sym)
#define CUN_STUBILIZE(prefix, sym) CUN_ADD_PREFIX(prefix, sym)
#define CUN_RENAME(prefix, sym) CUN_ADD_PREFIX(prefix, sym)

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#ifndef CUN_MOCKABLE
#define CUN_MOCKABLE(sym) CUN_MOCKOUT(mock_, sym)
#endif /* ndef CUN_MOCKABLE */

#ifndef CUN_STUBREADY
#define CUN_STUBREADY(sym) CUN_STUBILIZE(stub_, sym)
#endif /* ndef CUN_STUBREADY */

#ifndef CUN_REALNAME
#define CUN_REALNAME(sym) CUN_RENAME(real_, sym)
#endif /* ndef CUN_REALNAME */

#endif /* ndef CUN_MOCKOUT_H_INCLUDED */
