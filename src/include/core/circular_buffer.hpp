// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// A circular buffer.

#ifndef CUN_CIRCULAR_BUFFER_HPP_INCLUDED
#define CUN_CIRCULAR_BUFFER_HPP_INCLUDED

// C++ standard library
#include <atomic>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <type_traits>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

inline namespace circular_buffer {

/** A circular buffer class. */
template <typename T, std::size_t N, typename IndexT = std::atomic_size_t>
class CircularBuffer final {
    static_assert(N > 0, "CircularBuffer: 0 size buffer is not allowed.");
    static_assert(N < SIZE_MAX, "CircularBuffer: buffer size must be less than SIZE_MAX.");

public:
    using size_type = std::size_t;
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;

private:
    static constexpr size_type MAX_SIZE { N };
    static constexpr size_type BUF_SIZE { MAX_SIZE + 1 };

    IndexT m_rp { 0 };
    IndexT m_wp { 0 };
    value_type m_buf[BUF_SIZE];

    template <typename U = T>
    static std::enable_if_t<std::is_trivially_copyable<value_type>::value && std::is_same<U, T>::value, void>
    copy(value_type *dst, const value_type *src, size_type n) noexcept {
        (void) std::memcpy(dst, src, sizeof(value_type) * n);
    }

    template <typename U = T>
    static std::enable_if_t<!std::is_trivially_copyable<value_type>::value && std::is_same<U, T>::value, void>
    copy(value_type *dst, const value_type *src, size_type n) {
        for (; n > 0; ++dst, ++src, --n) {
            *dst = *src;
        }
    }

    static size_type prev_index(const size_type p) noexcept {
        return (p == 0) ? MAX_SIZE : p - 1;
    }

    static size_type size_of_free(const size_type rp, const size_type wp) noexcept {
        return (rp <= wp) ? (BUF_SIZE - wp + rp - 1) : (rp - wp - 1);
    }

    static size_type size_of_used(const size_type rp, const size_type wp) noexcept {
        return (rp <= wp) ? (wp - rp) : (BUF_SIZE - rp + wp);
    }

public:
    reference back() {
        assert(!empty());

        return m_buf[prev_index(m_wp)];
    }

    const_reference back() const {
        assert(!empty());

        return m_buf[prev_index(m_wp)];
    }

    void clear() noexcept {
        m_rp = 0;
        m_wp = 0;
    }

    bool empty() const noexcept {
        return size() == 0;
    }

    reference front() {
        assert(!empty());

        return m_buf[m_rp];
    }

    const_reference front() const {
        assert(!empty());

        return m_buf[m_rp];
    }

    size_type max_size() const noexcept {
        return MAX_SIZE;
    }

    bool pop(value_type& val) {
        return pop(&val, 1) == 1;
    }

    size_type pop(value_type * const buf, const size_type n) {
        if ((buf == nullptr) || (n == 0)) {
            return 0;
        }

        size_type rp = m_rp;
        size_type wp = m_wp;

        size_type ndata = size_of_used(rp, wp);
        if (ndata > n) {
            ndata = n;
        }

        size_type ncopied { 0 };

        if (wp < rp) {
            auto remain = BUF_SIZE - rp;

            if (remain <= ndata) {
                copy(buf, &m_buf[rp], remain);
                ndata -= remain;
                ncopied = remain;
                rp = 0;
            }
        }

        if (ndata > 0) {
            copy(&buf[ncopied], &m_buf[rp], ndata);
            ncopied += ndata;
            rp += ndata;
        }

        m_rp = rp;

        return ncopied;
    }

    bool push(const value_type& val) {
        return push(&val, 1) == 1;
    }

    size_type push(const value_type * const data, const size_type n) {
        if ((data == nullptr) || (n == 0)) {
            return 0;
        }

        size_type rp = m_rp;
        size_type wp = m_wp;

        auto nfree = size_of_free(rp, wp);
        if (nfree == 0) {
            return 0;
        }

        auto nwrite = (n <= nfree) ? n : nfree;

        size_type nwritten { 0 };

        if ((rp <= wp) && (rp != 0)) {
            auto remain = BUF_SIZE - wp;

            if (remain <= nwrite) {
                copy(&m_buf[wp], data, remain);
                nwrite -= remain;
                nwritten = remain;
                wp = 0;
            }
        }

        if (nwrite > 0) {
            copy(&m_buf[wp], &data[nwritten], nwrite);
            nwritten += nwrite;
            wp += nwrite;
        }

        m_wp = wp;

        return nwritten;
    }

    size_type size() const noexcept {
        return size_of_used(m_rp, m_wp);
    }
};

} // inline namespace circular_buffer

} // namespace cun

#endif // ndef CUN_CIRCULAR_BUFFER_HPP_INCLUDED
