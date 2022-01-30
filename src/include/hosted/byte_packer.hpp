// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Byte data pack/unpack functions.

#ifndef CUN_BYTE_PACKER_HPP_INCLUDED
#define CUN_BYTE_PACKER_HPP_INCLUDED

// C++ standard library
#include <array>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

// C++ user library
#include "binary_writer.hpp"

// For this library
#include "byte_packer_core.hpp"

namespace cun {

namespace byte_packer {

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

template <
    template<typename T, typename Allocator = std::allocator<T>> class ContainerT
>
bool pack(ContainerT<std::uint8_t>& buf,
          const char * const fmt, ...) noexcept
{
    bool ok;

    std::va_list args;
    va_start(args, fmt);

    try {
        cun::ContainerByteWriter<ContainerT> writer(buf);
        ok = cun::byte_packer::pack(writer, fmt, args);
    } catch (...) {
        ok = false;
    }

    va_end(args);

    return ok;
}

template <std::size_t N>
bool pack(std::array<std::uint8_t, N>& buf,
          std::size_t& nwritten,
          const char * const fmt, ...) noexcept
{
    cun::ArrayByteWriter<N> writer(buf);
    std::va_list args;

    va_start(args, fmt);
    const auto ok = cun::byte_packer::pack(writer, fmt, args);
    va_end(args);

    if (ok) {
        nwritten = writer.size();
    }

    return ok;
}

inline bool pack(std::ostream& out,
                 std::size_t& nwritten,
                 const char * const fmt, ...) noexcept
{
    bool ok;

    std::va_list args;
    va_start(args, fmt);

    try {
        cun::StreamByteWriter writer(out);
        ok = cun::byte_packer::pack(writer, fmt, args);
        if (ok) {
            nwritten = writer.size();
        }
    } catch (...) {
        ok = false;
    }

    va_end(args);

    return ok;
}

inline bool pack(std::string& buf,
                 const char * const fmt, ...) noexcept
{
    bool ok;

    std::va_list args;
    va_start(args, fmt);

    try {
        cun::StringByteWriter writer(buf);
        ok = cun::byte_packer::pack(writer, fmt, args);
    } catch (...) {
        ok = false;
    }

    va_end(args);

    return ok;
}

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

template <typename... Args>
bool unpack(const std::vector<std::uint8_t>& buf,
            std::size_t& nread,
            const char * const fmt,
            Args ... args) noexcept
{
    return cun::byte_packer::unpack(buf.data(), buf.size(), nread, fmt, args ...);
}

template <std::size_t N, typename... Args>
bool unpack(const std::array<std::uint8_t, N>& buf,
            std::size_t& nread,
            const char * const fmt,
            Args ... args) noexcept
{
    static_assert(N > 0, "std::array<std::uint8_t, 0> is not allowed.");

    return cun::byte_packer::unpack(buf.data(), buf.size(), nread, fmt, args ...);
}

template <typename... Args>
bool unpack(const std::string& buf,
            std::size_t& nread,
            const char * const fmt,
            Args ... args) noexcept
{
    return cun::byte_packer::unpack(reinterpret_cast<const std::uint8_t *>(buf.data()), buf.size(), nread, fmt, args ...);
}

} // namespace byte_packer

} // namespace cun

#endif // ndef CUN_BYTE_PACKER_HPP_INCLUDED
