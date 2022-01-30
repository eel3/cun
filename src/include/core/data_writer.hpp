// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// A data writer interface.

#ifndef CUN_DATA_WRITER_HPP_INCLUDED
#define CUN_DATA_WRITER_HPP_INCLUDED

// C++ standard library
#include <cstddef>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

/** A data writer interface class. */
template <typename T>
class IDataWriter {
public:
    using size_type = std::size_t;
    using value_type = T;

    IDataWriter() = default;
    virtual ~IDataWriter() = default;
    IDataWriter(const IDataWriter&) = delete;
    IDataWriter(IDataWriter&&) = delete;
    IDataWriter& operator=(const IDataWriter&) = delete;
    IDataWriter& operator=(IDataWriter&&) = delete;

    virtual size_type byte_size() const noexcept = 0;
    virtual bool can_push(const size_type npush) const noexcept = 0;
    virtual void clear() = 0;
    virtual const value_type *data() const noexcept = 0;
    virtual bool empty() const noexcept = 0;
    virtual size_type max_size() const noexcept = 0;
    virtual bool push(const value_type& data) = 0;
    virtual bool push(const value_type *data, const size_type n) = 0;
    virtual size_type size() const noexcept = 0;
};

} // namespace cun

#endif // ndef CUN_DATA_WRITER_HPP_INCLUDED
