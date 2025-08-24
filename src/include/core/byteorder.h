/*
 * -*- coding: utf-8-with-signature-dos -*-
 * vim:fileencoding=utf-8:ff=dos
 *
 * Byte order conversion functions (ISO C interface).
 */

#ifndef CUN_BYTEORDER_H_INCLUDED
#define CUN_BYTEORDER_H_INCLUDED

/* C standard library */
#include <stdint.h>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif /* def __cplusplus */

extern int16_t  cun_byteorder_to_big_i16(const int16_t  src);
extern uint16_t cun_byteorder_to_big_u16(const uint16_t src);
extern int32_t  cun_byteorder_to_big_i32(const int32_t  src);
extern uint32_t cun_byteorder_to_big_u32(const uint32_t src);
extern float    cun_byteorder_to_big_f32(const float    src);
extern int64_t  cun_byteorder_to_big_i64(const int64_t  src);
extern uint64_t cun_byteorder_to_big_u64(const uint64_t src);
extern double   cun_byteorder_to_big_f64(const double   src);

extern int16_t  cun_byteorder_from_big_i16(const int16_t  src);
extern uint16_t cun_byteorder_from_big_u16(const uint16_t src);
extern int32_t  cun_byteorder_from_big_i32(const int32_t  src);
extern uint32_t cun_byteorder_from_big_u32(const uint32_t src);
extern float    cun_byteorder_from_big_f32(const float    src);
extern int64_t  cun_byteorder_from_big_i64(const int64_t  src);
extern uint64_t cun_byteorder_from_big_u64(const uint64_t src);
extern double   cun_byteorder_from_big_f64(const double   src);

extern void cun_byteorder_pack_big_i16(const int16_t  src, uint8_t * const dst);
extern void cun_byteorder_pack_big_u16(const uint16_t src, uint8_t * const dst);
extern void cun_byteorder_pack_big_i32(const int32_t  src, uint8_t * const dst);
extern void cun_byteorder_pack_big_u32(const uint32_t src, uint8_t * const dst);
extern void cun_byteorder_pack_big_f32(const float    src, uint8_t * const dst);
extern void cun_byteorder_pack_big_i64(const int64_t  src, uint8_t * const dst);
extern void cun_byteorder_pack_big_u64(const uint64_t src, uint8_t * const dst);
extern void cun_byteorder_pack_big_f64(const double   src, uint8_t * const dst);

extern int16_t  cun_byteorder_unpack_big_i16(const uint8_t * const src);
extern uint16_t cun_byteorder_unpack_big_u16(const uint8_t * const src);
extern int32_t  cun_byteorder_unpack_big_i32(const uint8_t * const src);
extern uint32_t cun_byteorder_unpack_big_u32(const uint8_t * const src);
extern float    cun_byteorder_unpack_big_f32(const uint8_t * const src);
extern int64_t  cun_byteorder_unpack_big_i64(const uint8_t * const src);
extern uint64_t cun_byteorder_unpack_big_u64(const uint8_t * const src);
extern double   cun_byteorder_unpack_big_f64(const uint8_t * const src);

extern int16_t  cun_byteorder_to_little_i16(const int16_t  src);
extern uint16_t cun_byteorder_to_little_u16(const uint16_t src);
extern int32_t  cun_byteorder_to_little_i32(const int32_t  src);
extern uint32_t cun_byteorder_to_little_u32(const uint32_t src);
extern float    cun_byteorder_to_little_f32(const float    src);
extern int64_t  cun_byteorder_to_little_i64(const int64_t  src);
extern uint64_t cun_byteorder_to_little_u64(const uint64_t src);
extern double   cun_byteorder_to_little_f64(const double   src);

extern int16_t  cun_byteorder_from_little_i16(const int16_t  src);
extern uint16_t cun_byteorder_from_little_u16(const uint16_t src);
extern int32_t  cun_byteorder_from_little_i32(const int32_t  src);
extern uint32_t cun_byteorder_from_little_u32(const uint32_t src);
extern float    cun_byteorder_from_little_f32(const float    src);
extern int64_t  cun_byteorder_from_little_i64(const int64_t  src);
extern uint64_t cun_byteorder_from_little_u64(const uint64_t src);
extern double   cun_byteorder_from_little_f64(const double   src);

extern void cun_byteorder_pack_little_i16(const int16_t  src, uint8_t * const dst);
extern void cun_byteorder_pack_little_u16(const uint16_t src, uint8_t * const dst);
extern void cun_byteorder_pack_little_i32(const int32_t  src, uint8_t * const dst);
extern void cun_byteorder_pack_little_u32(const uint32_t src, uint8_t * const dst);
extern void cun_byteorder_pack_little_f32(const float    src, uint8_t * const dst);
extern void cun_byteorder_pack_little_i64(const int64_t  src, uint8_t * const dst);
extern void cun_byteorder_pack_little_u64(const uint64_t src, uint8_t * const dst);
extern void cun_byteorder_pack_little_f64(const double   src, uint8_t * const dst);

extern int16_t  cun_byteorder_unpack_little_i16(const uint8_t * const src);
extern uint16_t cun_byteorder_unpack_little_u16(const uint8_t * const src);
extern int32_t  cun_byteorder_unpack_little_i32(const uint8_t * const src);
extern uint32_t cun_byteorder_unpack_little_u32(const uint8_t * const src);
extern float    cun_byteorder_unpack_little_f32(const uint8_t * const src);
extern int64_t  cun_byteorder_unpack_little_i64(const uint8_t * const src);
extern uint64_t cun_byteorder_unpack_little_u64(const uint8_t * const src);
extern double   cun_byteorder_unpack_little_f64(const uint8_t * const src);

#ifdef __cplusplus
} /* extern "C" */
#endif /* def __cplusplus */

#endif /* ndef CUN_BYTEORDER_H_INCLUDED */
