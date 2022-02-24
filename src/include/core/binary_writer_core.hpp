// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// A binary data writer.

#ifndef CUN_BINARY_WRITER_CORE_HPP_INCLUDED
#define CUN_BINARY_WRITER_CORE_HPP_INCLUDED

// C++ standard library
#include <cstdint>
#include <cstring>
#include <type_traits>

// C++ user library
#include "data_writer.hpp"

namespace cun {

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

/** A binary data writer basic class. */
template <typename T>
class BinaryWriter : public cun::IDataWriter<T> {
public:
    using size_type = typename cun::IDataWriter<T>::size_type;
    using value_type = typename cun::IDataWriter<T>::value_type;

private:
    value_type *m_buf { nullptr };
    size_type m_bufsize { 0 };
    size_type m_size { 0 };

    template <typename U = T>
    std::enable_if_t<std::is_trivially_copyable<value_type>::value && std::is_same<U, T>::value, bool>
    do_push(const value_type *data, size_type n) noexcept {
        (void) std::memcpy(m_buf, data, sizeof(*data) * n);
        m_size += n;
        return true;
    }

    template <typename U = T>
    std::enable_if_t<!std::is_trivially_copyable<value_type>::value && std::is_same<U, T>::value, bool>
    do_push(const value_type *data, size_type n) {
        for (; n > 0; ++data, --n) {
            m_buf[m_size++] = *data;
        }
        return true;
    }

    bool have_no_buffer() const noexcept {
        return (m_buf == nullptr) || (m_bufsize == 0);
    }

    size_type size_of_free() const noexcept {
        return m_bufsize - m_size;
    }

public:
    BinaryWriter() = delete;
    BinaryWriter(value_type *buf, size_type n) noexcept :
        m_buf { buf },
        m_bufsize { n } {}
    virtual ~BinaryWriter() = default;
    BinaryWriter(const BinaryWriter&) = delete;
    BinaryWriter(BinaryWriter&&) = delete;
    BinaryWriter& operator=(const BinaryWriter&) = delete;
    BinaryWriter& operator=(BinaryWriter&&) = delete;

    virtual size_type byte_size() const noexcept override {
        return sizeof(value_type) * m_size;
    }

    virtual bool can_push(const size_type npush) const noexcept override {
        if (npush == 0) {
            return true;
        } else if (have_no_buffer()) {
            return false;
        } else {
            return npush <= size_of_free();
        }
        /*NOTREACHED*/
    };

    virtual void clear() noexcept override {
        m_size = 0;
    }

    virtual const value_type *data() const noexcept override {
        return (have_no_buffer() || empty()) ? nullptr : m_buf;
    }

    virtual bool empty() const noexcept override {
        return m_size == 0;
    }

    virtual size_type max_size() const noexcept override {
        return have_no_buffer() ? 0 : m_bufsize;
    }

    virtual bool push(const value_type& data) override {
        if (!can_push(1)) {
            return false;
        }

        m_buf[m_size++] = data;
        return true;
    }

    bool push(const value_type *data, const size_type n) override {
        if (n == 0) {
            return true;
        } else if (data == nullptr) {
            return false;
        } else if (!can_push(n)) {
            return false;
        } else {
            return do_push(data, n);
        }
        /*NOTREACHED*/
    }

    virtual size_type size() const noexcept override {
        return m_size;
    }
};

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

/** A binary data writer class containing a fixed buffer array. */
template <typename T, typename cun::BinaryWriter<T>::size_type N>
class BufferedBinaryWriter final : public cun::BinaryWriter<T> {
public:
    using size_type = typename cun::BinaryWriter<T>::size_type;
    using value_type = typename cun::BinaryWriter<T>::value_type;

private:
    value_type m_buf[N];

public:
    BufferedBinaryWriter() noexcept : cun::BinaryWriter<T>(m_buf, N) {}
    virtual ~BufferedBinaryWriter() = default;
    BufferedBinaryWriter(const BufferedBinaryWriter&) = delete;
    BufferedBinaryWriter(BufferedBinaryWriter&&) = delete;
    BufferedBinaryWriter& operator=(const BufferedBinaryWriter&) = delete;
    BufferedBinaryWriter& operator=(BufferedBinaryWriter&&) = delete;
};

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

/** A byte data writer interface class. */
using IByteWriter = cun::IDataWriter<std::uint8_t>;

/** A byte data writer class. */
using ByteWriter = cun::BinaryWriter<std::uint8_t>;

/** A byte data writer class containing a fixed buffer array. */
template <cun::ByteWriter::size_type N>
using BufferedByteWriter = cun::BufferedBinaryWriter<cun::ByteWriter::value_type, N>;

} // namespace cun

#endif // ndef CUN_BINARY_WRITER_CORE_HPP_INCLUDED
