// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// A binary data writer.

#ifndef CUN_BINARY_WRITER_HPP_INCLUDED
#define CUN_BINARY_WRITER_HPP_INCLUDED

// C++ standard library
#include <algorithm>
#include <array>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>

// C++ user library
#include "data_writer.hpp"

// For this library
#include "binary_writer_core.hpp"

namespace cun {

inline namespace binary_writer {

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

/** A binary data writer class writing data to a std::array. */
template <typename T, typename cun::BinaryWriter<T>::size_type N>
class ArrayBinaryWriter final : public cun::BinaryWriter<T> {
public:
    using size_type = typename cun::BinaryWriter<T>::size_type;
    using value_type = typename cun::BinaryWriter<T>::value_type;

    ArrayBinaryWriter() = delete;
    explicit ArrayBinaryWriter(std::array<T, N>& buf) noexcept : cun::BinaryWriter<T>(buf.data(), N) {
        static_assert(N > 0, "ArrayBinaryWriter: std::array<T, 0> is not allowed.");
    }
    virtual ~ArrayBinaryWriter() = default;
    ArrayBinaryWriter(const ArrayBinaryWriter&) = delete;
    ArrayBinaryWriter(ArrayBinaryWriter&&) = delete;
    ArrayBinaryWriter& operator=(const ArrayBinaryWriter&) = delete;
    ArrayBinaryWriter& operator=(ArrayBinaryWriter&&) = delete;
};

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

/** A binary data writer class writing data to a std::deque/list/vector. */
template <
    class T,
    template <typename U = T, typename Allocator = std::allocator<U>> class ContainerT
>
class ContainerBinaryWriter final : public cun::IDataWriter<T> {
public:
    using size_type = typename cun::IDataWriter<T>::size_type;
    using value_type = typename cun::IDataWriter<T>::value_type;

private:
    ContainerT<T>& m_buf;

    size_type size_of_free() const noexcept {
        return m_buf.max_size() - m_buf.size();
    }

public:
    ContainerBinaryWriter() = delete;
    explicit ContainerBinaryWriter(ContainerT<T>& buf) noexcept : m_buf { buf } {}
    virtual ~ContainerBinaryWriter() = default;
    ContainerBinaryWriter(const ContainerBinaryWriter&) = delete;
    ContainerBinaryWriter(ContainerBinaryWriter&&) = delete;
    ContainerBinaryWriter& operator=(const ContainerBinaryWriter&) = delete;
    ContainerBinaryWriter& operator=(ContainerBinaryWriter&&) = delete;

    virtual size_type byte_size() const noexcept override {
        return sizeof(value_type) * m_buf.size();
    }

    virtual bool can_push(const size_type npush) const noexcept override {
        return npush <= size_of_free();
    };

    virtual void clear() noexcept override {
        m_buf.clear();
    }

    virtual const value_type *data() const noexcept override {
        return nullptr;
    }

    virtual bool empty() const noexcept override {
        return m_buf.empty();
    }

    virtual size_type max_size() const noexcept override {
        return m_buf.max_size();
    }

    virtual bool push(const value_type& data) override {
        if (!can_push(1)) {
            return false;
        }

        m_buf.emplace_back(data);
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
            (void) std::copy_n(data, n, std::back_inserter(m_buf));
            return true;
        }
        /*NOTREACHED*/
    }

    virtual size_type size() const noexcept override {
        return m_buf.size();
    }
};

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

/** A binary data writer class writing data to a std::ostream. */
template <typename T>
class StreamBinaryWriter final : public cun::IDataWriter<T> {
public:
    using size_type = typename cun::IDataWriter<T>::size_type;
    using value_type = typename cun::IDataWriter<T>::value_type;

private:
    std::ostream& m_buf;
    size_type m_size { 0 };

public:
    StreamBinaryWriter() = delete;
    explicit StreamBinaryWriter(std::ostream& buf) noexcept : m_buf { buf } {}
    virtual ~StreamBinaryWriter() = default;
    StreamBinaryWriter(const StreamBinaryWriter&) = delete;
    StreamBinaryWriter(StreamBinaryWriter&&) = delete;
    StreamBinaryWriter& operator=(const StreamBinaryWriter&) = delete;
    StreamBinaryWriter& operator=(StreamBinaryWriter&&) = delete;

    virtual size_type byte_size() const noexcept override {
        return sizeof(value_type) * m_size;
    }

    virtual bool can_push(const size_type) const noexcept override {
        return !m_buf.fail();
    };

    virtual void clear() noexcept override {
        m_size = 0;
    }

    virtual const value_type *data() const noexcept override {
        return nullptr;
    }

    virtual bool empty() const noexcept override {
        return m_size == 0;
    }

    virtual size_type max_size() const noexcept override {
        return 0;
    }

    virtual bool push(const value_type& data) override {
        if (!can_push(1)) {
            return false;
        }

        (void) m_buf.write(reinterpret_cast<const char *>(&data),
                           static_cast<std::streamsize>(sizeof(data)));
        m_size++;
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
            (void) m_buf.write(reinterpret_cast<const char *>(data),
                               static_cast<std::streamsize>(sizeof(data) * n));
            m_size += n;
            return true;
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

/** A binary data writer class writing data to a std::string. */
template <typename T>
class StringBinaryWriter final : public cun::IDataWriter<T> {
public:
    using size_type = typename cun::IDataWriter<T>::size_type;
    using value_type = typename cun::IDataWriter<T>::value_type;

private:
    std::string& m_buf;

    size_type byte_size_of_free() const noexcept {
        return m_buf.max_size() - m_buf.size();
    }

    size_type size_of_free() const noexcept {
        return byte_size_of_free() / sizeof(value_type);
    }

public:
    StringBinaryWriter() = delete;
    explicit StringBinaryWriter(std::string& buf) noexcept : m_buf { buf } {}
    virtual ~StringBinaryWriter() = default;
    StringBinaryWriter(const StringBinaryWriter&) = delete;
    StringBinaryWriter(StringBinaryWriter&&) = delete;
    StringBinaryWriter& operator=(const StringBinaryWriter&) = delete;
    StringBinaryWriter& operator=(StringBinaryWriter&&) = delete;

    virtual size_type byte_size() const noexcept override {
        return m_buf.size();
    }

    virtual bool can_push(const size_type npush) const noexcept override {
        return npush <= size_of_free();
    };

    virtual void clear() noexcept override {
        m_buf.clear();
    }

    virtual const value_type *data() const noexcept override {
        return empty() ? nullptr : reinterpret_cast<const value_type *>(m_buf.data());
    }

    virtual bool empty() const noexcept override {
        return m_buf.empty();
    }

    virtual size_type max_size() const noexcept override {
        return m_buf.max_size() / sizeof(value_type);
    }

    virtual bool push(const value_type& data) override {
        if (!can_push(1)) {
            return false;
        }

        (void) m_buf.append(reinterpret_cast<const char *>(&data), sizeof(data));
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
            (void) m_buf.append(reinterpret_cast<const char *>(data), sizeof(data) * n);
            return true;
        }
        /*NOTREACHED*/
    }

    virtual size_type size() const noexcept override {
        return m_buf.size() / sizeof(value_type);
    }
};

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

/** A byte data writer class writing data to a std::array. */
template <cun::ByteWriter::size_type N>
using ArrayByteWriter = cun::ArrayBinaryWriter<cun::ByteWriter::value_type, N>;

/** A byte data writer class writing data to a std::deque/list/vector. */
template <
    template <typename T, typename Allocator = std::allocator<T>> class ContainerT
>
using ContainerByteWriter = cun::ContainerBinaryWriter<cun::ByteWriter::value_type, ContainerT>;
/** A byte data writer class writing data to a std::deque */
using DequeByteWriter = cun::ContainerBinaryWriter<cun::ByteWriter::value_type, std::deque>;
/** A byte data writer class writing data to a std::list. */
using ListByteWriter = cun::ContainerBinaryWriter<cun::ByteWriter::value_type, std::list>;
/** A byte data writer class writing data to a std::vector. */
using VectorByteWriter = cun::ContainerBinaryWriter<cun::ByteWriter::value_type, std::vector>;

/** A byte data writer class writing data to a std::ostream. */
using StreamByteWriter = cun::StreamBinaryWriter<cun::ByteWriter::value_type>;

/** A byte data writer class writing data to a std::string. */
using StringByteWriter = cun::StringBinaryWriter<cun::ByteWriter::value_type>;

} // inline namespace binary_writer

} // namespace cun

#endif // ndef CUN_BINARY_WRITER_HPP_INCLUDED
