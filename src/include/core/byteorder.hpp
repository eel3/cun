// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Byte order conversion functions.

#ifndef CUN_BYTEORDER_HPP_INCLUDED
#define CUN_BYTEORDER_HPP_INCLUDED

// C++ standard library
#include <bit>
#include <cassert>
#include <climits>
#include <concepts>
#include <cstdint>
#include <type_traits>

namespace cun {

namespace byteorder {

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

static_assert(CHAR_BIT == 8, "cun::byteorder: Assume that `1 byte == 8 bit' environment.");

/// Specifies that a type is `std::bit_cast` ables.
template <typename T1, typename T2>
concept bit_castable =
    (sizeof(T1) == sizeof(T2)) &&
    std::is_trivially_copyable_v<T1> &&
    std::is_trivially_copyable_v<T2>;

/// Specifies that a type is 16bit and can be byte swapping.
template <typename T>
concept byte16_swappable = bit_castable<T, uint16_t>;

/// Specifies that a type is 32bit and can be byte swapping.
template <typename T>
concept byte32_swappable = bit_castable<T, uint32_t>;

/// Specifies that a type is 64bit and can be byte swapping.
template <typename T>
concept byte64_swappable = bit_castable<T, uint64_t>;

/// Specifies that a type can be byte swapping.
template <typename T>
concept byte_swappable =
    byte16_swappable<T> ||
    byte32_swappable<T> ||
    byte64_swappable<T>;

/// Specifies that a type is a 16bit integer can be used by byte swap operation.
template <typename T>
concept byte16_integral = (sizeof(T) == sizeof(uint16_t)) && std::unsigned_integral<T>;

/// Specifies that a type is a 32bit integer can be used by byte swap operation.
template <typename T>
concept byte32_integral = (sizeof(T) == sizeof(uint32_t)) && std::unsigned_integral<T>;

/// Specifies that a type is a 64bit integer can be used by byte swap operation.
template <typename T>
concept byte64_integral = (sizeof(T) == sizeof(uint64_t)) && std::unsigned_integral<T>;

/// Specifies that a type is a integer can be used by byte swap operation.
template <typename T>
concept byte_integral =
    byte16_integral<T> ||
    byte32_integral<T> ||
    byte64_integral<T>;

namespace impl {

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

/// 16bit byte array type.
struct byte16_t {
    uint8_t b[2];
};
static_assert(sizeof(byte16_t) == sizeof(uint16_t));

/// 32bit byte array type.
struct byte32_t {
    uint8_t b[4];
};
static_assert(sizeof(byte32_t) == sizeof(uint32_t));

/// 64bit byte array type.
struct byte64_t {
    uint8_t b[8];
};
static_assert(sizeof(byte64_t) == sizeof(uint64_t));

/* ---------------------------------------------------------------------- */
/* Convert from native endian to big endian: private */
/* ---------------------------------------------------------------------- */

template <byte_integral SrcT>
class to_big final {
private:
    const SrcT m_src;

public:
    constexpr explicit to_big(const SrcT src) :
            m_src(src) {}

    template <byte16_swappable DstT>
    requires (sizeof(DstT) == sizeof(SrcT))
    constexpr operator DstT() const noexcept {
        return std::bit_cast<DstT>(byte16_t { .b = {
            static_cast<uint8_t>((m_src >> 8) & 0xFFU),
            static_cast<uint8_t>( m_src       & 0xFFU),
        }});
    }

    template <byte32_swappable DstT>
    requires (sizeof(DstT) == sizeof(SrcT))
    constexpr operator DstT() const noexcept {
        return std::bit_cast<DstT>(byte32_t { .b = {
            static_cast<uint8_t>((m_src >> 24) & 0xFFU),
            static_cast<uint8_t>((m_src >> 16) & 0xFFU),
            static_cast<uint8_t>((m_src >>  8) & 0xFFU),
            static_cast<uint8_t>( m_src        & 0xFFU),
        }});
    }

    template <byte64_swappable DstT>
    requires (sizeof(DstT) == sizeof(SrcT))
    constexpr operator DstT() const noexcept {
        return std::bit_cast<DstT>(byte64_t { .b = {
            static_cast<uint8_t>((m_src >> 56) & 0xFFU),
            static_cast<uint8_t>((m_src >> 48) & 0xFFU),
            static_cast<uint8_t>((m_src >> 40) & 0xFFU),
            static_cast<uint8_t>((m_src >> 32) & 0xFFU),
            static_cast<uint8_t>((m_src >> 24) & 0xFFU),
            static_cast<uint8_t>((m_src >> 16) & 0xFFU),
            static_cast<uint8_t>((m_src >>  8) & 0xFFU),
            static_cast<uint8_t>( m_src        & 0xFFU),
        }});
    }
};

/* ---------------------------------------------------------------------- */
/* Convert from big endian to native endian: private */
/* ---------------------------------------------------------------------- */

template <byte16_swappable T>
constexpr uint16_t from_big(const T src) noexcept
{
    const auto byte = std::bit_cast<byte16_t>(src);

    return static_cast<uint16_t>(
        (static_cast<uint16_t>(byte.b[0]) << 8) |
        (static_cast<uint16_t>(byte.b[1])     )
    );
}

template <byte32_swappable T>
constexpr uint32_t from_big(const T src) noexcept
{
    const auto byte = std::bit_cast<byte32_t>(src);

    return static_cast<uint32_t>(
        (static_cast<uint32_t>(byte.b[0]) << 24) |
        (static_cast<uint32_t>(byte.b[1]) << 16) |
        (static_cast<uint32_t>(byte.b[2]) <<  8) |
        (static_cast<uint32_t>(byte.b[3])      )
    );
}

template <byte64_swappable T>
constexpr uint64_t from_big(const T src) noexcept
{
    const auto byte = std::bit_cast<byte64_t>(src);

    return static_cast<uint64_t>(
        (static_cast<uint64_t>(byte.b[0]) << 56) |
        (static_cast<uint64_t>(byte.b[1]) << 48) |
        (static_cast<uint64_t>(byte.b[2]) << 40) |
        (static_cast<uint64_t>(byte.b[3]) << 32) |
        (static_cast<uint64_t>(byte.b[4]) << 24) |
        (static_cast<uint64_t>(byte.b[5]) << 16) |
        (static_cast<uint64_t>(byte.b[6]) <<  8) |
        (static_cast<uint64_t>(byte.b[7])      )
    );
}

/* ---------------------------------------------------------------------- */
/* Convert from native endian to little endian: private */
/* ---------------------------------------------------------------------- */

template <byte_integral SrcT>
class to_little final {
private:
    const SrcT m_src;

public:
    constexpr explicit to_little(const SrcT src) :
            m_src(src) {}

    template <byte16_swappable DstT>
    requires (sizeof(DstT) == sizeof(SrcT))
    constexpr operator DstT() const noexcept {
        return std::bit_cast<DstT>(byte16_t { .b = {
            static_cast<uint8_t>( m_src       & 0xFFU),
            static_cast<uint8_t>((m_src >> 8) & 0xFFU),
        }});
    }

    template <byte32_swappable DstT>
    requires (sizeof(DstT) == sizeof(SrcT))
    constexpr operator DstT() const noexcept {
        return std::bit_cast<DstT>(byte32_t { .b = {
            static_cast<uint8_t>( m_src        & 0xFFU),
            static_cast<uint8_t>((m_src >>  8) & 0xFFU),
            static_cast<uint8_t>((m_src >> 16) & 0xFFU),
            static_cast<uint8_t>((m_src >> 24) & 0xFFU),
        }});
    }

    template <byte64_swappable DstT>
    requires (sizeof(DstT) == sizeof(SrcT))
    constexpr operator DstT() const noexcept {
        return std::bit_cast<DstT>(byte64_t { .b = {
            static_cast<uint8_t>( m_src        & 0xFFU),
            static_cast<uint8_t>((m_src >>  8) & 0xFFU),
            static_cast<uint8_t>((m_src >> 16) & 0xFFU),
            static_cast<uint8_t>((m_src >> 24) & 0xFFU),
            static_cast<uint8_t>((m_src >> 32) & 0xFFU),
            static_cast<uint8_t>((m_src >> 40) & 0xFFU),
            static_cast<uint8_t>((m_src >> 48) & 0xFFU),
            static_cast<uint8_t>((m_src >> 56) & 0xFFU),
        }});
    }
};

/* ---------------------------------------------------------------------- */
/* Convert from little endian to native endian: private */
/* ---------------------------------------------------------------------- */

template <byte16_swappable T>
constexpr uint16_t from_little(const T src) noexcept
{
    const auto byte = std::bit_cast<byte16_t>(src);

    return static_cast<uint16_t>(
        (static_cast<uint16_t>(byte.b[1]) << 8) |
        (static_cast<uint16_t>(byte.b[0])     )
    );
}

template <byte32_swappable T>
constexpr uint32_t from_little(const T src) noexcept
{
    const auto byte = std::bit_cast<byte32_t>(src);

    return static_cast<uint32_t>(
        (static_cast<uint32_t>(byte.b[3]) << 24) |
        (static_cast<uint32_t>(byte.b[2]) << 16) |
        (static_cast<uint32_t>(byte.b[1]) <<  8) |
        (static_cast<uint32_t>(byte.b[0])      )
    );
}

template <byte64_swappable T>
constexpr uint64_t from_little(const T src) noexcept
{
    const auto byte = std::bit_cast<byte64_t>(src);

    return static_cast<uint64_t>(
        (static_cast<uint64_t>(byte.b[7]) << 56) |
        (static_cast<uint64_t>(byte.b[6]) << 48) |
        (static_cast<uint64_t>(byte.b[5]) << 40) |
        (static_cast<uint64_t>(byte.b[4]) << 32) |
        (static_cast<uint64_t>(byte.b[3]) << 24) |
        (static_cast<uint64_t>(byte.b[2]) << 16) |
        (static_cast<uint64_t>(byte.b[1]) <<  8) |
        (static_cast<uint64_t>(byte.b[0])      )
    );
}

} // namespace impl

/* ---------------------------------------------------------------------- */
/* Convert from native endian to big endian: public */
/* ---------------------------------------------------------------------- */

template <byte_integral T>
constexpr T to_big(const T src) noexcept
{
    return impl::to_big(src);
}

template <byte16_swappable T>
requires (!byte16_integral<T>)
constexpr T to_big(const T src) noexcept
{
    return impl::to_big(std::bit_cast<uint16_t>(src));
}

template <byte32_swappable T>
requires (!byte32_integral<T>)
constexpr T to_big(const T src) noexcept
{
    return impl::to_big(std::bit_cast<uint32_t>(src));
}

template <byte64_swappable T>
requires (!byte64_integral<T>)
constexpr T to_big(const T src) noexcept
{
    return impl::to_big(std::bit_cast<uint64_t>(src));
}

/* ---------------------------------------------------------------------- */
/* Convert from big endian to native endian: public */
/* ---------------------------------------------------------------------- */

template <byte_integral T>
constexpr T from_big(const T src) noexcept
{
    return impl::from_big(src);
}

template <byte_swappable T>
requires (!byte_integral<T>)
constexpr T from_big(const T src) noexcept
{
    return std::bit_cast<T>(impl::from_big(src));
}

/* ---------------------------------------------------------------------- */
/* Packing to big endian */
/* ---------------------------------------------------------------------- */

template <byte16_integral T>
constexpr void pack_to_big(const T src, uint8_t * const dst) noexcept
{
    assert(dst != nullptr);

    dst[0] = static_cast<uint8_t>((src >> 8) & 0xFFU);
    dst[1] = static_cast<uint8_t>( src       & 0xFFU);
}

template <byte16_swappable T>
requires (!byte16_integral<T>)
constexpr void pack_to_big(const T src, uint8_t * const dst) noexcept
{
    pack_to_big(std::bit_cast<uint16_t>(src), dst);
}

template <byte32_integral T>
constexpr void pack_to_big(const T src, uint8_t * const dst) noexcept
{
    assert(dst != nullptr);

    dst[0] = static_cast<uint8_t>((src >> 24) & 0xFFU);
    dst[1] = static_cast<uint8_t>((src >> 16) & 0xFFU);
    dst[2] = static_cast<uint8_t>((src >>  8) & 0xFFU);
    dst[3] = static_cast<uint8_t>( src        & 0xFFU);
}

template <byte32_swappable T>
requires (!byte32_integral<T>)
constexpr void pack_to_big(const T src, uint8_t * const dst) noexcept
{
    pack_to_big(std::bit_cast<uint32_t>(src), dst);
}

template <byte64_integral T>
constexpr void pack_to_big(const T src, uint8_t * const dst) noexcept
{
    assert(dst != nullptr);

    dst[0] = static_cast<uint8_t>((src >> 56) & 0xFFU);
    dst[1] = static_cast<uint8_t>((src >> 48) & 0xFFU);
    dst[2] = static_cast<uint8_t>((src >> 40) & 0xFFU);
    dst[3] = static_cast<uint8_t>((src >> 32) & 0xFFU);
    dst[4] = static_cast<uint8_t>((src >> 24) & 0xFFU);
    dst[5] = static_cast<uint8_t>((src >> 16) & 0xFFU);
    dst[6] = static_cast<uint8_t>((src >>  8) & 0xFFU);
    dst[7] = static_cast<uint8_t>( src        & 0xFFU);
}

template <byte64_swappable T>
requires (!byte64_integral<T>)
constexpr void pack_to_big(const T src, uint8_t * const dst) noexcept
{
    pack_to_big(std::bit_cast<uint64_t>(src), dst);
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

    template <byte16_integral T>
    constexpr operator T() const noexcept {
        return static_cast<T>(
            (static_cast<T>(m_src[0]) << 8) |
            (static_cast<T>(m_src[1])     )
        );
    }

    template <byte16_swappable T>
    requires (!byte16_integral<T>)
    constexpr operator T() const noexcept {
        return std::bit_cast<T>(static_cast<uint16_t>(*this));
    }

    template <byte32_integral T>
    constexpr operator T() const noexcept {
        return static_cast<T>(
            (static_cast<T>(m_src[0]) << 24) |
            (static_cast<T>(m_src[1]) << 16) |
            (static_cast<T>(m_src[2]) <<  8) |
            (static_cast<T>(m_src[3])      )
        );
    }

    template <byte32_swappable T>
    requires (!byte32_integral<T>)
    constexpr operator T() const noexcept {
        return std::bit_cast<T>(static_cast<uint32_t>(*this));
    }

    template <byte64_integral T>
    constexpr operator T() const noexcept {
        return static_cast<T>(
            (static_cast<T>(m_src[0]) << 56) |
            (static_cast<T>(m_src[1]) << 48) |
            (static_cast<T>(m_src[2]) << 40) |
            (static_cast<T>(m_src[3]) << 32) |
            (static_cast<T>(m_src[4]) << 24) |
            (static_cast<T>(m_src[5]) << 16) |
            (static_cast<T>(m_src[6]) <<  8) |
            (static_cast<T>(m_src[7])      )
        );
    }

    template <byte64_swappable T>
    requires (!byte64_integral<T>)
    constexpr operator T() const noexcept {
        return std::bit_cast<T>(static_cast<uint64_t>(*this));
    }
};

/* ---------------------------------------------------------------------- */
/* Convert from native endian to little endian: public */
/* ---------------------------------------------------------------------- */

template <byte_integral T>
constexpr T to_little(const T src) noexcept
{
    return impl::to_little(src);
}

template <byte16_swappable T>
requires (!byte16_integral<T>)
constexpr T to_little(const T src) noexcept
{
    return impl::to_little(std::bit_cast<uint16_t>(src));
}

template <byte32_swappable T>
requires (!byte32_integral<T>)
constexpr T to_little(const T src) noexcept
{
    return impl::to_little(std::bit_cast<uint32_t>(src));
}

template <byte64_swappable T>
requires (!byte64_integral<T>)
constexpr T to_little(const T src) noexcept
{
    return impl::to_little(std::bit_cast<uint64_t>(src));
}

/* ---------------------------------------------------------------------- */
/* Convert from little endian to native endian: public */
/* ---------------------------------------------------------------------- */

template <byte_integral T>
constexpr T from_little(const T src) noexcept
{
    return impl::from_little(src);
}

template <byte_swappable T>
requires (!byte_integral<T>)
constexpr T from_little(const T src) noexcept
{
    return std::bit_cast<T>(impl::from_little(src));
}

/* ---------------------------------------------------------------------- */
/* Packing to little endian */
/* ---------------------------------------------------------------------- */

template <byte16_integral T>
constexpr void pack_to_little(const T src, uint8_t * const dst) noexcept
{
    assert(dst != nullptr);

    dst[0] = static_cast<uint8_t>( src       & 0xFFU);
    dst[1] = static_cast<uint8_t>((src >> 8) & 0xFFU);
}

template <byte16_swappable T>
requires (!byte16_integral<T>)
constexpr void pack_to_little(const T src, uint8_t * const dst) noexcept
{
    pack_to_little(std::bit_cast<uint16_t>(src), dst);
}

template <byte32_integral T>
constexpr void pack_to_little(const T src, uint8_t * const dst) noexcept
{
    assert(dst != nullptr);

    dst[0] = static_cast<uint8_t>( src        & 0xFFU);
    dst[1] = static_cast<uint8_t>((src >>  8) & 0xFFU);
    dst[2] = static_cast<uint8_t>((src >> 16) & 0xFFU);
    dst[3] = static_cast<uint8_t>((src >> 24) & 0xFFU);
}

template <byte32_swappable T>
requires (!byte32_integral<T>)
constexpr void pack_to_little(const T src, uint8_t * const dst) noexcept
{
    pack_to_little(std::bit_cast<uint32_t>(src), dst);
}

template <byte64_integral T>
constexpr void pack_to_little(const T src, uint8_t * const dst) noexcept
{
    assert(dst != nullptr);

    dst[0] = static_cast<uint8_t>( src        & 0xFFU);
    dst[1] = static_cast<uint8_t>((src >>  8) & 0xFFU);
    dst[2] = static_cast<uint8_t>((src >> 16) & 0xFFU);
    dst[3] = static_cast<uint8_t>((src >> 24) & 0xFFU);
    dst[4] = static_cast<uint8_t>((src >> 32) & 0xFFU);
    dst[5] = static_cast<uint8_t>((src >> 40) & 0xFFU);
    dst[6] = static_cast<uint8_t>((src >> 48) & 0xFFU);
    dst[7] = static_cast<uint8_t>((src >> 56) & 0xFFU);
}

template <byte64_swappable T>
requires (!byte64_integral<T>)
constexpr void pack_to_little(const T src, uint8_t * const dst) noexcept
{
    pack_to_little(std::bit_cast<uint64_t>(src), dst);
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


    template <byte16_integral T>
    constexpr operator T() const noexcept {
        return static_cast<T>(
            (static_cast<T>(m_src[1]) << 8) |
            (static_cast<T>(m_src[0])     )
        );
    }

    template <byte16_swappable T>
    requires (!byte16_integral<T>)
    constexpr operator T() const noexcept {
        return std::bit_cast<T>(static_cast<uint16_t>(*this));
    }

    template <byte32_integral T>
    constexpr operator T() const noexcept {
        return static_cast<T>(
            (static_cast<T>(m_src[3]) << 24) |
            (static_cast<T>(m_src[2]) << 16) |
            (static_cast<T>(m_src[1]) <<  8) |
            (static_cast<T>(m_src[0])      )
        );
    }

    template <byte32_swappable T>
    requires (!byte32_integral<T>)
    constexpr operator T() const noexcept {
        return std::bit_cast<T>(static_cast<uint32_t>(*this));
    }

    template <byte64_integral T>
    constexpr operator T() const noexcept {
        return static_cast<T>(
            (static_cast<T>(m_src[7]) << 56) |
            (static_cast<T>(m_src[6]) << 48) |
            (static_cast<T>(m_src[5]) << 40) |
            (static_cast<T>(m_src[4]) << 32) |
            (static_cast<T>(m_src[3]) << 24) |
            (static_cast<T>(m_src[2]) << 16) |
            (static_cast<T>(m_src[1]) <<  8) |
            (static_cast<T>(m_src[0])      )
        );
    }

    template <byte64_swappable T>
    requires (!byte64_integral<T>)
    constexpr operator T() const noexcept {
        return std::bit_cast<T>(static_cast<uint64_t>(*this));
    }
};

} // namespace byteorder

} // namespace cun

#endif // ndef CUN_BYTEORDER_HPP_INCLUDED
