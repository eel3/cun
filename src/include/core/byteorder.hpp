// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Byte order conversion functions.

#ifndef CUN_BYTEORDER_HPP_INCLUDED
#define CUN_BYTEORDER_HPP_INCLUDED

// C++ standard library
#include <cassert>
#include <cstdint>

namespace cun {

namespace byteorder {

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

union union16_t {
    uint8_t b[2];
    int16_t i;
    uint16_t u;
};

union union32_t {
    uint8_t b[4];
    float f;
    int32_t i;
    uint32_t u;
};

union union64_t {
    uint8_t b[8];
    double f;
    int64_t i;
    uint64_t u;
};

/* ---------------------------------------------------------------------- */
/* Convert from native endian to big endian */
/* ---------------------------------------------------------------------- */

constexpr union16_t to_big(const union16_t src) noexcept
{
    return { .b = {
        static_cast<uint8_t>((src.u >> 8) & 0xFFU),
        static_cast<uint8_t>( src.u       & 0xFFU),
    }};
}

constexpr union32_t to_big(const union32_t src) noexcept
{
    return { .b = {
        static_cast<uint8_t>((src.u >> 24) & 0xFFU),
        static_cast<uint8_t>((src.u >> 16) & 0xFFU),
        static_cast<uint8_t>((src.u >>  8) & 0xFFU),
        static_cast<uint8_t>( src.u        & 0xFFU),
    }};
}

constexpr union64_t to_big(const union64_t src) noexcept
{
    return { .b = {
        static_cast<uint8_t>((src.u >> 56) & 0xFFU),
        static_cast<uint8_t>((src.u >> 48) & 0xFFU),
        static_cast<uint8_t>((src.u >> 40) & 0xFFU),
        static_cast<uint8_t>((src.u >> 32) & 0xFFU),
        static_cast<uint8_t>((src.u >> 24) & 0xFFU),
        static_cast<uint8_t>((src.u >> 16) & 0xFFU),
        static_cast<uint8_t>((src.u >>  8) & 0xFFU),
        static_cast<uint8_t>( src.u        & 0xFFU),
    }};
}

constexpr int16_t to_big(const int16_t src) noexcept
{
    return to_big(union16_t { .i = src }).i;
}

constexpr uint16_t to_big(const uint16_t src) noexcept
{
    return to_big(union16_t { .u = src }).u;
}

constexpr int32_t to_big(const int32_t src) noexcept
{
    return to_big(union32_t { .i = src }).i;
}

constexpr uint32_t to_big(const uint32_t src) noexcept
{
    return to_big(union32_t { .u = src }).u;
}

constexpr float to_big(const float src) noexcept
{
    return to_big(union32_t { .f = src }).f;
}

constexpr int64_t to_big(const int64_t src) noexcept
{
    return to_big(union64_t { .i = src }).i;
}

constexpr uint64_t to_big(const uint64_t src) noexcept
{
    return to_big(union64_t { .u = src }).u;
}

constexpr double to_big(const double src) noexcept
{
    return to_big(union64_t { .f = src }).f;
}

/* ---------------------------------------------------------------------- */
/* Convert from big endian to native endian */
/* ---------------------------------------------------------------------- */

constexpr union16_t from_big(const union16_t src) noexcept
{
    return { .u = static_cast<uint16_t>(
        (static_cast<uint16_t>(src.b[0]) << 8) |
        (static_cast<uint16_t>(src.b[1])     )
    )};
}

constexpr union32_t from_big(const union32_t src) noexcept
{
    return { .u =
        (static_cast<uint32_t>(src.b[0]) << 24) |
        (static_cast<uint32_t>(src.b[1]) << 16) |
        (static_cast<uint32_t>(src.b[2]) <<  8) |
        (static_cast<uint32_t>(src.b[3])      )
    };
}

constexpr union64_t from_big(const union64_t src) noexcept
{
    return { .u =
        (static_cast<uint64_t>(src.b[0]) << 56) |
        (static_cast<uint64_t>(src.b[1]) << 48) |
        (static_cast<uint64_t>(src.b[2]) << 40) |
        (static_cast<uint64_t>(src.b[3]) << 32) |
        (static_cast<uint64_t>(src.b[4]) << 24) |
        (static_cast<uint64_t>(src.b[5]) << 16) |
        (static_cast<uint64_t>(src.b[6]) <<  8) |
        (static_cast<uint64_t>(src.b[7])      )
    };
}

constexpr int16_t from_big(const int16_t src) noexcept
{
    return from_big(union16_t { .i = src }).i;
}

constexpr uint16_t from_big(const uint16_t src) noexcept
{
    return from_big(union16_t { .u = src }).u;
}

constexpr int32_t from_big(const int32_t src) noexcept
{
    return from_big(union32_t { .i = src }).i;
}

constexpr uint32_t from_big(const uint32_t src) noexcept
{
    return from_big(union32_t { .u = src }).u;
}

constexpr float from_big(const float src) noexcept
{
    return from_big(union32_t { .f = src }).f;
}

constexpr int64_t from_big(const int64_t src) noexcept
{
    return from_big(union64_t { .i = src }).i;
}

constexpr uint64_t from_big(const uint64_t src) noexcept
{
    return from_big(union64_t { .u = src }).u;
}

constexpr double from_big(const double src) noexcept
{
    return from_big(union64_t { .f = src }).f;
}

/* ---------------------------------------------------------------------- */
/* Packing to big endian */
/* ---------------------------------------------------------------------- */

constexpr void pack_to_big(const union16_t src, uint8_t * const dst) noexcept
{
    assert(dst != nullptr);

    dst[0] = static_cast<uint8_t>((src.u >> 8) & 0xFFU);
    dst[1] = static_cast<uint8_t>( src.u       & 0xFFU);
}

constexpr void pack_to_big(const union32_t src, uint8_t * const dst) noexcept
{
    assert(dst != nullptr);

    dst[0] = static_cast<uint8_t>((src.u >> 24) & 0xFFU);
    dst[1] = static_cast<uint8_t>((src.u >> 16) & 0xFFU);
    dst[2] = static_cast<uint8_t>((src.u >>  8) & 0xFFU);
    dst[3] = static_cast<uint8_t>( src.u        & 0xFFU);
}

constexpr void pack_to_big(const union64_t src, uint8_t * const dst) noexcept
{
    assert(dst != nullptr);

    dst[0] = static_cast<uint8_t>((src.u >> 56) & 0xFFU);
    dst[1] = static_cast<uint8_t>((src.u >> 48) & 0xFFU);
    dst[2] = static_cast<uint8_t>((src.u >> 40) & 0xFFU);
    dst[3] = static_cast<uint8_t>((src.u >> 32) & 0xFFU);
    dst[4] = static_cast<uint8_t>((src.u >> 24) & 0xFFU);
    dst[5] = static_cast<uint8_t>((src.u >> 16) & 0xFFU);
    dst[6] = static_cast<uint8_t>((src.u >>  8) & 0xFFU);
    dst[7] = static_cast<uint8_t>( src.u        & 0xFFU);
}

constexpr void pack_to_big(const int16_t src, uint8_t * const dst) noexcept
{
    pack_to_big(union16_t { .i = src }, dst);
}

constexpr void pack_to_big(const uint16_t src, uint8_t * const dst) noexcept
{
    pack_to_big(union16_t { .u = src }, dst);
}

constexpr void pack_to_big(const int32_t src, uint8_t * const dst) noexcept
{
    pack_to_big(union32_t { .i = src }, dst);
}

constexpr void pack_to_big(const uint32_t src, uint8_t * const dst) noexcept
{
    pack_to_big(union32_t { .u = src }, dst);
}

constexpr void pack_to_big(const float src, uint8_t * const dst) noexcept
{
    pack_to_big(union32_t { .f = src }, dst);
}

constexpr void pack_to_big(const int64_t src, uint8_t * const dst) noexcept
{
    pack_to_big(union64_t { .i = src }, dst);
}

constexpr void pack_to_big(const uint64_t src, uint8_t * const dst) noexcept
{
    pack_to_big(union64_t { .u = src }, dst);
}

constexpr void pack_to_big(const double src, uint8_t * const dst) noexcept
{
    pack_to_big(union64_t { .f = src }, dst);
}

/* ---------------------------------------------------------------------- */
/* Unpacking from big endian */
/* ---------------------------------------------------------------------- */

class unpack_from_big final {
private:
    const uint8_t * const m_src;

public:
    constexpr explicit unpack_from_big(const uint8_t * const src) :
            m_src(src) {
        assert(src != nullptr);
    }

    template <typename T>
    constexpr operator T() const noexcept;
};

template<> constexpr unpack_from_big::operator union16_t() const noexcept {
    return { .u = static_cast<uint16_t>(
        (static_cast<uint16_t>(m_src[0]) << 8) |
        (static_cast<uint16_t>(m_src[1])     )
    )};
}

template<> constexpr unpack_from_big::operator union32_t() const noexcept {
    return { .u =
        (static_cast<uint32_t>(m_src[0]) << 24) |
        (static_cast<uint32_t>(m_src[1]) << 16) |
        (static_cast<uint32_t>(m_src[2]) <<  8) |
        (static_cast<uint32_t>(m_src[3])      )
    };
}

template<> constexpr unpack_from_big::operator union64_t() const noexcept {
    return { .u =
        (static_cast<uint64_t>(m_src[0]) << 56) |
        (static_cast<uint64_t>(m_src[1]) << 48) |
        (static_cast<uint64_t>(m_src[2]) << 40) |
        (static_cast<uint64_t>(m_src[3]) << 32) |
        (static_cast<uint64_t>(m_src[4]) << 24) |
        (static_cast<uint64_t>(m_src[5]) << 16) |
        (static_cast<uint64_t>(m_src[6]) <<  8) |
        (static_cast<uint64_t>(m_src[7])      )
    };
}

template<> constexpr unpack_from_big::operator int16_t() const noexcept {
    return static_cast<union16_t>(*this).i;
}

template<> constexpr unpack_from_big::operator uint16_t() const noexcept {
    return static_cast<union16_t>(*this).u;
}

template<> constexpr unpack_from_big::operator int32_t() const noexcept {
    return static_cast<union32_t>(*this).i;
}

template<> constexpr unpack_from_big::operator uint32_t() const noexcept {
    return static_cast<union32_t>(*this).u;
}

template<> constexpr unpack_from_big::operator float() const noexcept {
    return static_cast<union32_t>(*this).f;
}

template<> constexpr unpack_from_big::operator int64_t() const noexcept {
    return static_cast<union64_t>(*this).i;
}

template<> constexpr unpack_from_big::operator uint64_t() const noexcept {
    return static_cast<union64_t>(*this).u;
}

template<> constexpr unpack_from_big::operator double() const noexcept {
    return static_cast<union64_t>(*this).f;
}

/* ---------------------------------------------------------------------- */
/* Convert from native endian to little endian */
/* ---------------------------------------------------------------------- */

constexpr union16_t to_little(const union16_t src) noexcept
{
    return { .b = {
        static_cast<uint8_t>( src.u       & 0xFFU),
        static_cast<uint8_t>((src.u >> 8) & 0xFFU),
    }};
}

constexpr union32_t to_little(const union32_t src) noexcept
{
    return { .b = {
        static_cast<uint8_t>( src.u        & 0xFFU),
        static_cast<uint8_t>((src.u >>  8) & 0xFFU),
        static_cast<uint8_t>((src.u >> 16) & 0xFFU),
        static_cast<uint8_t>((src.u >> 24) & 0xFFU),
    }};
}

constexpr union64_t to_little(const union64_t src) noexcept
{
    return { .b = {
        static_cast<uint8_t>( src.u        & 0xFFU),
        static_cast<uint8_t>((src.u >>  8) & 0xFFU),
        static_cast<uint8_t>((src.u >> 16) & 0xFFU),
        static_cast<uint8_t>((src.u >> 24) & 0xFFU),
        static_cast<uint8_t>((src.u >> 32) & 0xFFU),
        static_cast<uint8_t>((src.u >> 40) & 0xFFU),
        static_cast<uint8_t>((src.u >> 48) & 0xFFU),
        static_cast<uint8_t>((src.u >> 56) & 0xFFU),
    }};
}

constexpr int16_t to_little(const int16_t src) noexcept
{
    return to_little(union16_t { .i = src }).i;
}

constexpr uint16_t to_little(const uint16_t src) noexcept
{
    return to_little(union16_t { .u = src }).u;
}

constexpr int32_t to_little(const int32_t src) noexcept
{
    return to_little(union32_t { .i = src }).i;
}

constexpr uint32_t to_little(const uint32_t src) noexcept
{
    return to_little(union32_t { .u = src }).u;
}

constexpr float to_little(const float src) noexcept
{
    return to_little(union32_t { .f = src }).f;
}

constexpr int64_t to_little(const int64_t src) noexcept
{
    return to_little(union64_t { .i = src }).i;
}

constexpr uint64_t to_little(const uint64_t src) noexcept
{
    return to_little(union64_t { .u = src }).u;
}

constexpr double to_little(const double src) noexcept
{
    return to_little(union64_t { .f = src }).f;
}

/* ---------------------------------------------------------------------- */
/* Convert from little endian to native endian */
/* ---------------------------------------------------------------------- */

constexpr union16_t from_little(const union16_t src) noexcept
{
    return { .u = static_cast<uint16_t>(
        (static_cast<uint16_t>(src.b[1]) << 8) |
        (static_cast<uint16_t>(src.b[0])     )
    )};
}

constexpr union32_t from_little(const union32_t src) noexcept
{
    return { .u =
        (static_cast<uint32_t>(src.b[3]) << 24) |
        (static_cast<uint32_t>(src.b[2]) << 16) |
        (static_cast<uint32_t>(src.b[1]) <<  8) |
        (static_cast<uint32_t>(src.b[0])      )
    };
}

constexpr union64_t from_little(const union64_t src) noexcept
{
    return { .u =
        (static_cast<uint64_t>(src.b[7]) << 56) |
        (static_cast<uint64_t>(src.b[6]) << 48) |
        (static_cast<uint64_t>(src.b[5]) << 40) |
        (static_cast<uint64_t>(src.b[4]) << 32) |
        (static_cast<uint64_t>(src.b[3]) << 24) |
        (static_cast<uint64_t>(src.b[2]) << 16) |
        (static_cast<uint64_t>(src.b[1]) <<  8) |
        (static_cast<uint64_t>(src.b[0])      )
    };
}

constexpr int16_t from_little(const int16_t src) noexcept
{
    return from_little(union16_t { .i = src }).i;
}

constexpr uint16_t from_little(const uint16_t src) noexcept
{
    return from_little(union16_t { .u = src }).u;
}

constexpr int32_t from_little(const int32_t src) noexcept
{
    return from_little(union32_t { .i = src }).i;
}

constexpr uint32_t from_little(const uint32_t src) noexcept
{
    return from_little(union32_t { .u = src }).u;
}

constexpr float from_little(const float src) noexcept
{
    return from_little(union32_t { .f = src }).f;
}

constexpr int64_t from_little(const int64_t src) noexcept
{
    return from_little(union64_t { .i = src }).i;
}

constexpr uint64_t from_little(const uint64_t src) noexcept
{
    return from_little(union64_t { .u = src }).u;
}

constexpr double from_little(const double src) noexcept
{
    return from_little(union64_t { .f = src }).f;
}

/* ---------------------------------------------------------------------- */
/* Packing to little endian */
/* ---------------------------------------------------------------------- */

constexpr void pack_to_little(const union16_t src, uint8_t * const dst) noexcept
{
    assert(dst != nullptr);

    dst[0] = static_cast<uint8_t>( src.u       & 0xFFU);
    dst[1] = static_cast<uint8_t>((src.u >> 8) & 0xFFU);
}

constexpr void pack_to_little(const union32_t src, uint8_t * const dst) noexcept
{
    assert(dst != nullptr);

    dst[0] = static_cast<uint8_t>( src.u        & 0xFFU);
    dst[1] = static_cast<uint8_t>((src.u >>  8) & 0xFFU);
    dst[2] = static_cast<uint8_t>((src.u >> 16) & 0xFFU);
    dst[3] = static_cast<uint8_t>((src.u >> 24) & 0xFFU);
}

constexpr void pack_to_little(const union64_t src, uint8_t * const dst) noexcept
{
    assert(dst != nullptr);

    dst[0] = static_cast<uint8_t>( src.u        & 0xFFU);
    dst[1] = static_cast<uint8_t>((src.u >>  8) & 0xFFU);
    dst[2] = static_cast<uint8_t>((src.u >> 16) & 0xFFU);
    dst[3] = static_cast<uint8_t>((src.u >> 24) & 0xFFU);
    dst[4] = static_cast<uint8_t>((src.u >> 32) & 0xFFU);
    dst[5] = static_cast<uint8_t>((src.u >> 40) & 0xFFU);
    dst[6] = static_cast<uint8_t>((src.u >> 48) & 0xFFU);
    dst[7] = static_cast<uint8_t>((src.u >> 56) & 0xFFU);
}

constexpr void pack_to_little(const int16_t src, uint8_t * const dst)
{
    pack_to_little(union16_t { .i = src }, dst);
}

constexpr void pack_to_little(const uint16_t src, uint8_t * const dst)
{
    pack_to_little(union16_t { .u = src }, dst);
}

constexpr void pack_to_little(const int32_t src, uint8_t * const dst)
{
    pack_to_little(union32_t { .i = src }, dst);
}

constexpr void pack_to_little(const uint32_t src, uint8_t * const dst)
{
    pack_to_little(union32_t { .u = src }, dst);
}

constexpr void pack_to_little(const float src, uint8_t * const dst)
{
    pack_to_little(union32_t { .f = src }, dst);
}

constexpr void pack_to_little(const int64_t src, uint8_t * const dst)
{
    pack_to_little(union64_t { .i = src }, dst);
}

constexpr void pack_to_little(const uint64_t src, uint8_t * const dst)
{
    pack_to_little(union64_t { .u = src }, dst);
}

constexpr void pack_to_little(const double src, uint8_t * const dst)
{
    pack_to_little(union64_t { .f = src }, dst);
}

/* ---------------------------------------------------------------------- */
/* Unpacking from little endian */
/* ---------------------------------------------------------------------- */

class unpack_from_little final {
private:
    const uint8_t * const m_src;

public:
    constexpr explicit unpack_from_little(const uint8_t * const src) :
            m_src(src) {
        assert(src != nullptr);
    }

    template <typename T>
    constexpr operator T() const noexcept;
};

template<> constexpr unpack_from_little::operator union16_t() const noexcept {
    return { .u = static_cast<uint16_t>(
        (static_cast<uint16_t>(m_src[1]) << 8) |
        (static_cast<uint16_t>(m_src[0])     )
    )};
}

template<> constexpr unpack_from_little::operator union32_t() const noexcept {
    return { .u =
        (static_cast<uint32_t>(m_src[3]) << 24) |
        (static_cast<uint32_t>(m_src[2]) << 16) |
        (static_cast<uint32_t>(m_src[1]) <<  8) |
        (static_cast<uint32_t>(m_src[0])      )
    };
}

template<> constexpr unpack_from_little::operator union64_t() const noexcept {
    return { .u =
        (static_cast<uint64_t>(m_src[7]) << 56) |
        (static_cast<uint64_t>(m_src[6]) << 48) |
        (static_cast<uint64_t>(m_src[5]) << 40) |
        (static_cast<uint64_t>(m_src[4]) << 32) |
        (static_cast<uint32_t>(m_src[3]) << 24) |
        (static_cast<uint32_t>(m_src[2]) << 16) |
        (static_cast<uint32_t>(m_src[1]) <<  8) |
        (static_cast<uint32_t>(m_src[0])      )
    };
}

template<> constexpr unpack_from_little::operator int16_t() const noexcept {
    return static_cast<union16_t>(*this).i;
}

template<> constexpr unpack_from_little::operator uint16_t() const noexcept {
    return static_cast<union16_t>(*this).u;
}

template<> constexpr unpack_from_little::operator int32_t() const noexcept {
    return static_cast<union32_t>(*this).i;
}

template<> constexpr unpack_from_little::operator uint32_t() const noexcept {
    return static_cast<union32_t>(*this).u;
}

template<> constexpr unpack_from_little::operator float() const noexcept {
    return static_cast<union32_t>(*this).f;
}

template<> constexpr unpack_from_little::operator int64_t() const noexcept {
    return static_cast<union64_t>(*this).i;
}

template<> constexpr unpack_from_little::operator uint64_t() const noexcept {
    return static_cast<union64_t>(*this).u;
}

template<> constexpr unpack_from_little::operator double() const noexcept {
    return static_cast<union64_t>(*this).f;
}

} // namespace byteorder

} // namespace cun

#endif // ndef CUN_BYTEORDER_HPP_INCLUDED
