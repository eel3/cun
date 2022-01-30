// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Byte data pack/unpack functions.

#ifndef CUN_BYTE_PACKER_CORE_HPP_INCLUDED
#define CUN_BYTE_PACKER_CORE_HPP_INCLUDED

// C++ standard library
#include <cstdarg>
#include <cstddef>
#include <cstdint>

// C++ user library
#include "binary_writer_core.hpp"

// For this library
#include "byte_packer.h"

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

namespace byte_packer {

extern bool pack(cun::IByteWriter& writer,
                 const char * const fmt,
                 std::va_list args);

template <typename... Args>
bool pack(std::uint8_t * const buf,
          std::size_t bufsize,
          std::size_t& nwritten,
          const char * const fmt,
          Args ... args) noexcept
{
    return cun_byte_packer_Pack(buf, bufsize, &nwritten, fmt, args ...);
}

template <typename... Args>
bool unpack(const std::uint8_t * const buf,
            std::size_t bufsize,
            std::size_t& nread,
            const char * const fmt,
            Args ... args) noexcept
{
    return cun_byte_packer_Unpack(buf, bufsize, &nread, fmt, args ...);
}

} // namespace byte_packer

} // namespace cun

#endif // ndef CUN_BYTE_PACKER_CORE_HPP_INCLUDED
