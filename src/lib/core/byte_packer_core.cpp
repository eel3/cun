// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Byte data pack/unpack functions.

// C++ standard library
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>

// C++ user library
#include "binary_writer_core.hpp"

// For this library
#include "byte_packer.h"
#include "byte_packer_core.hpp"

namespace cun {

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace byte_packer {

bool pack(cun::IByteWriter& writer,
          const char * const fmt,
          std::va_list args)
{
#define CAN_WRITE(size) \
    do { \
        if (!writer.can_push(size)) { \
            return false; \
        } \
    } while (/*CONSTCOND*/ 0)

    assert(fmt != nullptr);

    for (auto p = fmt; *p != '\0'; p++) {
        std::size_t len;
        const char *a;
        const uint8_t *c;
        std::uint16_t s;
        std::uint32_t i;
        std::uint64_t l;

        len = 0;

        switch (*p) {
        case 'a':   // C-string (packing with NUL)
            len = 1;
            /*FALLTHROUGH*/
        case 'A':   // C-string (packing without NUL)
            a = va_arg(args, const char *);
            len += std::strlen(a);
            CAN_WRITE(len);
            writer.push(reinterpret_cast<const uint8_t *>(a), len);
            break;
        case 'C':   // uint8_t array
            c = va_arg(args, const std::uint8_t *);
            len = va_arg(args, std::size_t);
            CAN_WRITE(len);
            writer.push(c, len);
            break;
        case 'c':   // uint8_t
            CAN_WRITE(1);
            writer.push(static_cast<std::uint8_t>(va_arg(args, unsigned int)));
            break;
        case 's':   // uint16_t, BE (network byte order)
            CAN_WRITE(2);
            s = static_cast<std::uint16_t>(va_arg(args, unsigned int));
            writer.push(static_cast<std::uint8_t>((s >> 8) & 0xFF));
            writer.push(static_cast<std::uint8_t>( s       & 0xFF));
            break;
        case 'S':   // uint16_t, LE
            CAN_WRITE(2);
            s = static_cast<std::uint16_t>(va_arg(args, unsigned int));
            writer.push(static_cast<std::uint8_t>( s       & 0xFF));
            writer.push(static_cast<std::uint8_t>((s >> 8) & 0xFF));
            break;
        case 'i':   // uint32_t, BE (network byte order)
            CAN_WRITE(4);
            i = va_arg(args, std::uint32_t);
            writer.push(static_cast<std::uint8_t>((i >> 24) & 0xFF));
            writer.push(static_cast<std::uint8_t>((i >> 16) & 0xFF));
            writer.push(static_cast<std::uint8_t>((i >>  8) & 0xFF));
            writer.push(static_cast<std::uint8_t>( i        & 0xFF));
            break;
        case 'I':   // uint32_t, LE
            CAN_WRITE(4);
            i = va_arg(args, std::uint32_t);
            writer.push(static_cast<std::uint8_t>( i        & 0xFF));
            writer.push(static_cast<std::uint8_t>((i >>  8) & 0xFF));
            writer.push(static_cast<std::uint8_t>((i >> 16) & 0xFF));
            writer.push(static_cast<std::uint8_t>((i >> 24) & 0xFF));
            break;
        case 'l':   // uint64_t, BE (network byte order)
            CAN_WRITE(8);
            l = va_arg(args, std::uint64_t);
            writer.push(static_cast<std::uint8_t>((l >> 56) & 0xFF));
            writer.push(static_cast<std::uint8_t>((l >> 48) & 0xFF));
            writer.push(static_cast<std::uint8_t>((l >> 40) & 0xFF));
            writer.push(static_cast<std::uint8_t>((l >> 32) & 0xFF));
            writer.push(static_cast<std::uint8_t>((l >> 24) & 0xFF));
            writer.push(static_cast<std::uint8_t>((l >> 16) & 0xFF));
            writer.push(static_cast<std::uint8_t>((l >>  8) & 0xFF));
            writer.push(static_cast<std::uint8_t>( l        & 0xFF));
            break;
        case 'L':   // uint64_t, LE
            CAN_WRITE(8);
            l = va_arg(args, std::uint64_t);
            writer.push(static_cast<std::uint8_t>( l        & 0xFF));
            writer.push(static_cast<std::uint8_t>((l >>  8) & 0xFF));
            writer.push(static_cast<std::uint8_t>((l >> 16) & 0xFF));
            writer.push(static_cast<std::uint8_t>((l >> 24) & 0xFF));
            writer.push(static_cast<std::uint8_t>((l >> 32) & 0xFF));
            writer.push(static_cast<std::uint8_t>((l >> 40) & 0xFF));
            writer.push(static_cast<std::uint8_t>((l >> 48) & 0xFF));
            writer.push(static_cast<std::uint8_t>((l >> 56) & 0xFF));
            break;
        default:    // Unknown format character
            return false;
        }
    }

    return true;

#undef CAN_WRITE
}

} // namespace byte_packer

} // namespace cun

extern "C" {

bool cun_byte_packer_Pack(uint8_t * const buf,
                          size_t bufsize,
                          size_t * const nwritten,
                          const char * const fmt, ...)
{
    assert((buf != nullptr) && (nwritten != nullptr) && (fmt != nullptr));

    cun::ByteWriter writer(buf, bufsize);
    std::va_list args;

    va_start(args, fmt);
    const auto ok = cun::byte_packer::pack(writer, fmt, args);
    va_end(args);

    if (ok) {
        *nwritten = writer.size();
    }

    return ok;
}

bool cun_byte_packer_Unpack(const uint8_t * const buf,
                            size_t bufsize,
                            size_t * const nread,
                            const char * const fmt, ...)
{
#define CAN_READ(size) \
    do { \
        if (bufsize < size) { \
            va_end(args); \
            return false; \
        } \
        bufsize -= size; \
    } while (/*CONSTCOND*/ 0)

    assert((buf != nullptr) && (nread != nullptr) && (fmt != nullptr));

    auto bp = buf;

    std::va_list args;
    va_start(args, fmt);

    for (auto p = fmt; *p != '\0'; p++) {
        std::size_t len;
        char *a;
        std::uint8_t *c;
        std::uint16_t *s;
        std::uint32_t *i;
        std::uint64_t *l;

        switch (*p) {
        case 'a':   // C-string (packed with NUL)
            a = va_arg(args, char *);
            len = va_arg(args, std::size_t);
            if (len > 0) {
                *a = '\0';
                (void) std::strncat(a, reinterpret_cast<const char *>(bp), len - 1);
            }
            bp += std::strlen(reinterpret_cast<const char *>(bp)) + 1;
            break;
        case 'A':   // C-string (packed without NUL)
            a = va_arg(args, char *);
            len = va_arg(args, std::size_t);
            CAN_READ(len);
            (void) std::memcpy(a, bp, len);
            a[len] = '\0';
            bp += len;
            break;
        case 'C':   // uint8_t array
            c = va_arg(args, std::uint8_t *);
            len = va_arg(args, std::size_t);
            CAN_READ(len);
            (void) std::memcpy(c, bp, len);
            bp += len;
            break;
        case 'c':   // uint8_t
            CAN_READ(1);
            c = va_arg(args, std::uint8_t *);
            *c = *bp++;
            break;
        case 's':   // uint16_t, BE (network byte order)
            CAN_READ(2);
            s = va_arg(args, std::uint16_t *);
            *s  = static_cast<std::uint16_t>(*bp++) << 8;
            *s |= static_cast<std::uint16_t>(*bp++);
            break;
        case 'S':   // uint16_t, LE
            CAN_READ(2);
            s = va_arg(args, std::uint16_t *);
            *s  = static_cast<std::uint16_t>(*bp++);
            *s |= static_cast<std::uint16_t>(*bp++) << 8;
            break;
        case 'i':   // uint32_t, BE (network byte order)
            CAN_READ(4);
            i = va_arg(args, std::uint32_t *);
            *i  = static_cast<std::uint32_t>(*bp++) << 24;
            *i |= static_cast<std::uint32_t>(*bp++) << 16;
            *i |= static_cast<std::uint32_t>(*bp++) <<  8;
            *i |= static_cast<std::uint32_t>(*bp++);
            break;
        case 'I':   // uint32_t, LE
            CAN_READ(4);
            i = va_arg(args, std::uint32_t *);
            *i  = static_cast<std::uint32_t>(*bp++);
            *i |= static_cast<std::uint32_t>(*bp++) <<  8;
            *i |= static_cast<std::uint32_t>(*bp++) << 16;
            *i |= static_cast<std::uint32_t>(*bp++) << 24;
            break;
        case 'l':   // uint64_t, BE (network byte order)
            CAN_READ(8);
            l = va_arg(args, std::uint64_t *);
            *l  = static_cast<std::uint64_t>(*bp++) << 56;
            *l |= static_cast<std::uint64_t>(*bp++) << 48;
            *l |= static_cast<std::uint64_t>(*bp++) << 40;
            *l |= static_cast<std::uint64_t>(*bp++) << 32;
            *l |= static_cast<std::uint64_t>(*bp++) << 24;
            *l |= static_cast<std::uint64_t>(*bp++) << 16;
            *l |= static_cast<std::uint64_t>(*bp++) <<  8;
            *l |= static_cast<std::uint64_t>(*bp++);
            break;
        case 'L':   // uint64_t, LE
            CAN_READ(8);
            l = va_arg(args, std::uint64_t *);
            *l  = static_cast<std::uint64_t>(*bp++);
            *l |= static_cast<std::uint64_t>(*bp++) <<  8;
            *l |= static_cast<std::uint64_t>(*bp++) << 16;
            *l |= static_cast<std::uint64_t>(*bp++) << 24;
            *l |= static_cast<std::uint64_t>(*bp++) << 32;
            *l |= static_cast<std::uint64_t>(*bp++) << 40;
            *l |= static_cast<std::uint64_t>(*bp++) << 48;
            *l |= static_cast<std::uint64_t>(*bp++) << 56;
            break;
        default:    // Unknown format character
            va_end(args);
            return false;
        }
    }

    va_end(args);

    *nread = bp - buf;

    return true;

#undef CAN_READ
}

} // extern "C"
