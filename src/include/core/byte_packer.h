// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Byte data pack/unpack functions (ISO C interface).

#ifndef CUN_BYTE_PACKER_H_INCLUDED
#define CUN_BYTE_PACKER_H_INCLUDED

// C standard library
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif /* def __cplusplus */

extern bool cun_byte_packer_Pack(uint8_t * const buf,
                                 size_t bufsize,
                                 size_t * const nwritten,
                                 const char * const fmt, ...);


extern bool cun_byte_packer_Unpack(const uint8_t * const buf,
                                   size_t bufsize,
                                   size_t * const nread,
                                   const char * const fmt, ...);

#ifdef __cplusplus
} /* extern "C" */
#endif /* def __cplusplus */

#endif // ndef CUN_BYTE_PACKER_H_INCLUDED
