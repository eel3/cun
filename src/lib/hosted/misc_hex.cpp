// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Utility functions - basename.

// C++ standard library
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <ostream>

// For this library
#include "misc.hpp"

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

inline namespace misc {

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

} // inline namespace misc

} // namespace cun
