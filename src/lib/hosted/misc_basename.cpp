// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Utility functions - basename.

// C++ standard library
#include <string>

// For this library
#include "misc.hpp"

namespace {

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

using std::string;

const string DOT { "." };
const string SEP { "/" };

#if defined(_WIN32) || defined(_WIN64)
    const string WSEP { "\\" };
    const string SEPS { SEP + WSEP };
#else /* defined(_WIN32) || defined(_WIN64) */
    const string SEPS { SEP };
#endif /* defined(_WIN32) || defined(_WIN64) */

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

inline string trim_right(const string& s, const string& chars = "\t\n\v\f\r ")
{
    auto rpos = s.find_last_not_of(chars);

    return (rpos == string::npos) ? "" : s.substr(0, rpos + 1);
}

} // namespace

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

std::string basename(const std::string& s)
{
    if (s.empty()) {
        return DOT;
    }

    const auto path = trim_right(s, SEPS);
    if (path.empty()) {
        return std::string { s.back() };
    }

    auto pos = path.find_last_of(SEPS);
    return (pos == std::string::npos) ? path : path.substr(pos + 1);
}

std::string basename(const char * const s)
{
    return (s == nullptr) ? DOT : cun::basename(std::string { s });
}

} // namespace cun
