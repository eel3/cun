// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Utility functions - basename.

// C++ standard library
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>

// For this library
#include "misc.hpp"

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

inline namespace misc {

void hex_dump(FILE *out, const void *obj, const std::size_t size) noexcept
{
    if ((out == nullptr) || (obj == nullptr) || (size == 0)) {
        return;
    }

    auto p = static_cast<const uint8_t *>(obj);
    auto end = p + size;
    for (; p < end; p++) {
        (void) std::fprintf(out, "%02x", *p);
    }
}

void hex_dump(std::ostream& out, const void *obj, const std::size_t size)
{
    if ((obj == nullptr) || (size == 0)) {
        return;
    }

    auto p = static_cast<const uint8_t *>(obj);
    auto end = p + size;
    for (; p < end; p++) {
        out << std::hex << std::setw(2)  << std::setfill('0') << static_cast<uint32_t>(*p);
    }
}

std::string to_hex_string(const void *obj, const std::size_t size)
{
    std::ostringstream oss;

    hex_dump(oss, obj, size);

    return oss.str();
}

} // inline namespace misc

} // namespace cun
