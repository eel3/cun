/*
 * -*- coding: utf-8-with-signature-dos -*-
 * vim:fileencoding=utf-8:ff=dos
 *
 * Mock out helpers for unit test (ISO C interface).
 */

#ifndef CUN_MOCKABLE_H_INCLUDED
#define CUN_MOCKABLE_H_INCLUDED

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#ifndef CUN_MOCKABLE
#define CUN_MOCKABLE(sym) sym
#endif /* ndef CUN_MOCKABLE */

#ifndef CUN_STUBREADY
#define CUN_STUBREADY(sym) sym
#endif /* ndef CUN_STUBREADY */

#ifndef CUN_REALNAME
#define CUN_REALNAME(sym) sym
#endif /* ndef CUN_REALNAME */

#endif /* ndef CUN_MOCKABLE_H_INCLUDED */
