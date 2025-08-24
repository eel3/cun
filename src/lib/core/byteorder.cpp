// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Byte order conversion functions (ISO C interface).

// For this library
#include "byteorder.h"
#include "byteorder.hpp"

using namespace cun::byteorder;

extern "C" {

/* ---------------------------------------------------------------------- */
/* Convert from native endian to big endian */
/* ---------------------------------------------------------------------- */

int16_t cun_byteorder_to_big_i16(const int16_t src)
{
    return to_big(src);
}

uint16_t cun_byteorder_to_big_u16(const uint16_t src)
{
    return to_big(src);
}

int32_t cun_byteorder_to_big_i32(const int32_t src)
{
    return to_big(src);
}

uint32_t cun_byteorder_to_big_u32(const uint32_t src)
{
    return to_big(src);
}

float cun_byteorder_to_big_f32(const float src)
{
    return to_big(src);
}

int64_t cun_byteorder_to_big_i64(const int64_t src)
{
    return to_big(src);
}

uint64_t cun_byteorder_to_big_u64(const uint64_t src)
{
    return to_big(src);
}

double cun_byteorder_to_big_f64(const double src)
{
    return to_big(src);
}


/* ---------------------------------------------------------------------- */
/* Convert from big endian to native endian */
/* ---------------------------------------------------------------------- */

int16_t cun_byteorder_from_big_i16(const int16_t src)
{
    return from_big(src);
}

uint16_t cun_byteorder_from_big_u16(const uint16_t src)
{
    return from_big(src);
}

int32_t cun_byteorder_from_big_i32(const int32_t src)
{
    return from_big(src);
}

uint32_t cun_byteorder_from_big_u32(const uint32_t src)
{
    return from_big(src);
}

float cun_byteorder_from_big_f32(const float src)
{
    return from_big(src);
}

int64_t cun_byteorder_from_big_i64(const int64_t src)
{
    return from_big(src);
}

uint64_t cun_byteorder_from_big_u64(const uint64_t src)
{
    return from_big(src);
}

double cun_byteorder_from_big_f64(const double src)
{
    return from_big(src);
}

/* ---------------------------------------------------------------------- */
/* Packing to big endian */
/* ---------------------------------------------------------------------- */

void cun_byteorder_pack_big_i16(const int16_t src, uint8_t * const dst)
{
    pack_to_big(src, dst);
}

void cun_byteorder_pack_big_u16(const uint16_t src, uint8_t * const dst)
{
    pack_to_big(src, dst);
}

void cun_byteorder_pack_big_i32(const int32_t src, uint8_t * const dst)
{
    pack_to_big(src, dst);
}

void cun_byteorder_pack_big_u32(const uint32_t src, uint8_t * const dst)
{
    pack_to_big(src, dst);
}

void cun_byteorder_pack_big_f32(const float src, uint8_t * const dst)
{
    pack_to_big(src, dst);
}

void cun_byteorder_pack_big_i64(const int64_t src, uint8_t * const dst)
{
    pack_to_big(src, dst);
}

void cun_byteorder_pack_big_u64(const uint64_t src, uint8_t * const dst)
{
    pack_to_big(src, dst);
}

void cun_byteorder_pack_big_f64(const double src, uint8_t * const dst)
{
    pack_to_big(src, dst);
}

/* ---------------------------------------------------------------------- */
/* Unpacking from big endian */
/* ---------------------------------------------------------------------- */

int16_t cun_byteorder_unpack_big_i16(const uint8_t * const src)
{
    return static_cast<int16_t>(unpack_from_big(src));
}

uint16_t cun_byteorder_unpack_big_u16(const uint8_t * const src)
{
    return static_cast<uint16_t>(unpack_from_big(src));
}

int32_t cun_byteorder_unpack_big_i32(const uint8_t * const src)
{
    return static_cast<int32_t>(unpack_from_big(src));
}

uint32_t cun_byteorder_unpack_big_u32(const uint8_t * const src)
{
    return static_cast<uint32_t>(unpack_from_big(src));
}

float cun_byteorder_unpack_big_f32(const uint8_t * const src)
{
    return static_cast<float>(unpack_from_big(src));
}

int64_t cun_byteorder_unpack_big_i64(const uint8_t * const src)
{
    return static_cast<int64_t>(unpack_from_big(src));
}

uint64_t cun_byteorder_unpack_big_u64(const uint8_t * const src)
{
    return static_cast<uint64_t>(unpack_from_big(src));
}

double cun_byteorder_unpack_big_f64(const uint8_t * const src)
{
    return static_cast<double>(unpack_from_big(src));
}

/* ---------------------------------------------------------------------- */
/* Convert from native endian to little endian */
/* ---------------------------------------------------------------------- */

int16_t cun_byteorder_to_little_i16(const int16_t src)
{
    return to_little(src);
}

uint16_t cun_byteorder_to_little_u16(const uint16_t src)
{
    return to_little(src);
}

int32_t cun_byteorder_to_little_i32(const int32_t src)
{
    return to_little(src);
}

uint32_t cun_byteorder_to_little_u32(const uint32_t src)
{
    return to_little(src);
}

float cun_byteorder_to_little_f32(const float src)
{
    return to_little(src);
}

int64_t cun_byteorder_to_little_i64(const int64_t src)
{
    return to_little(src);
}

uint64_t cun_byteorder_to_little_u64(const uint64_t src)
{
    return to_little(src);
}

double cun_byteorder_to_little_f64(const double src)
{
    return to_little(src);
}

/* ---------------------------------------------------------------------- */
/* Convert from little endian to native endian */
/* ---------------------------------------------------------------------- */

int16_t cun_byteorder_from_little_i16(const int16_t src)
{
    return from_little(src);
}

uint16_t cun_byteorder_from_little_u16(const uint16_t src)
{
    return from_little(src);
}

int32_t cun_byteorder_from_little_i32(const int32_t src)
{
    return from_little(src);
}

uint32_t cun_byteorder_from_little_u32(const uint32_t src)
{
    return from_little(src);
}

float cun_byteorder_from_little_f32(const float src)
{
    return from_little(src);
}

int64_t cun_byteorder_from_little_i64(const int64_t src)
{
    return from_little(src);
}

uint64_t cun_byteorder_from_little_u64(const uint64_t src)
{
    return from_little(src);
}

double cun_byteorder_from_little_f64(const double src)
{
    return from_little(src);
}

/* ---------------------------------------------------------------------- */
/* Packing to little endian */
/* ---------------------------------------------------------------------- */

void cun_byteorder_pack_little_i16(const int16_t src, uint8_t * const dst)
{
    pack_to_little(src, dst);
}

void cun_byteorder_pack_little_u16(const uint16_t src, uint8_t * const dst)
{
    pack_to_little(src, dst);
}

void cun_byteorder_pack_little_i32(const int32_t src, uint8_t * const dst)
{
    pack_to_little(src, dst);
}

void cun_byteorder_pack_little_u32(const uint32_t src, uint8_t * const dst)
{
    pack_to_little(src, dst);
}

void cun_byteorder_pack_little_f32(const float src, uint8_t * const dst)
{
    pack_to_little(src, dst);
}

void cun_byteorder_pack_little_i64(const int64_t src, uint8_t * const dst)
{
    pack_to_little(src, dst);
}

void cun_byteorder_pack_little_u64(const uint64_t src, uint8_t * const dst)
{
    pack_to_little(src, dst);
}

void cun_byteorder_pack_little_f64(const double src, uint8_t * const dst)
{
    pack_to_little(src, dst);
}

/* ---------------------------------------------------------------------- */
/* Unpacking from little endian */
/* ---------------------------------------------------------------------- */

int16_t cun_byteorder_unpack_little_i16(const uint8_t * const src)
{
    return static_cast<int16_t>(unpack_from_little(src));
}

uint16_t cun_byteorder_unpack_little_u16(const uint8_t * const src)
{
    return static_cast<uint16_t>(unpack_from_little(src));
}

int32_t cun_byteorder_unpack_little_i32(const uint8_t * const src)
{
    return static_cast<int32_t>(unpack_from_little(src));
}

uint32_t cun_byteorder_unpack_little_u32(const uint8_t * const src)
{
    return static_cast<uint32_t>(unpack_from_little(src));
}

float cun_byteorder_unpack_little_f32(const uint8_t * const src)
{
    return static_cast<float>(unpack_from_little(src));
}

int64_t cun_byteorder_unpack_little_i64(const uint8_t * const src)
{
    return static_cast<int64_t>(unpack_from_little(src));
}

uint64_t cun_byteorder_unpack_little_u64(const uint8_t * const src)
{
    return static_cast<uint64_t>(unpack_from_little(src));
}

double cun_byteorder_unpack_little_f64(const uint8_t * const src)
{
    return static_cast<double>(unpack_from_little(src));
}

} // extern "C"
