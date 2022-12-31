// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// std::string utility functions.

#ifndef CUN_STRUTIL_HPP_INCLUDED
#define CUN_STRUTIL_HPP_INCLUDED

// C++ standard library
#include <array>
#include <cstddef>
#include <numeric>
#include <string>

namespace cun {

namespace strutil {

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

extern long tol_strict(const std::string& s, const int base = 10);

extern bool tol_safe(const std::string& s,
                     long& retval,
                     std::size_t * const idx = nullptr,
                     const int base = 10) noexcept;

extern bool tol_safe_strict(const std::string& s,
                            long& retval,
                            const int base = 10) noexcept;

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

template <typename CharT>
using StringT = std::basic_string<CharT>;

template <
    class CharT,
    template <typename T, typename Allocator = std::allocator<T>> class ContainerT
>
StringT<CharT> join(const ContainerT<StringT<CharT>>& container, const CharT *sep = nullptr)
{
    if (container.empty()) {
        return "";
    }

    if (sep == nullptr) {
        sep = "";
    }

    auto p = container.cbegin();
    ++p;

    return std::accumulate(p, container.cend(), *container.cbegin(), [sep](auto& acc, auto& s){
        return acc + sep + s;
    });
}

template <
    class CharT,
    template <typename T, typename Allocator = std::allocator<T>> class ContainerT
>
StringT<CharT> join(const ContainerT<StringT<CharT>>& container, StringT<CharT>& sep)
{
    return join(container, sep.c_str());
}

template <typename CharT, std::size_t N>
StringT<CharT> join(const std::array<StringT<CharT>, N>& container, const CharT *sep = nullptr)
{
    if (container.empty()) {
        return "";
    }

    if (sep == nullptr) {
        sep = "";
    }

    auto p = container.cbegin();
    ++p;

    return std::accumulate(p, container.cend(), *container.cbegin(), [sep](auto& acc, auto& s){
        return acc + sep + s;
    });
}

template <typename CharT, std::size_t N>
StringT<CharT> join(const std::array<StringT<CharT>, N>& container, const StringT<CharT>& sep)
{
    return join(container, sep.c_str());
}

} // namespace strutil

} // namespace cun

#endif // ndef CUN_STRUTIL_HPP_INCLUDED
