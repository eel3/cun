// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// An object pool.

#ifndef CUN_OBJECT_POOL_HPP_INCLUDED
#define CUN_OBJECT_POOL_HPP_INCLUDED

// C++ standard library
#include <atomic>
#include <cstddef>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

inline namespace object_pool {

/** A reference class of an object within a pool. */
template <typename T>
class ObjectRef {
public:
    T value {};

    ObjectRef() = default;
    virtual ~ObjectRef() = default;

    ObjectRef(const ObjectRef&) = delete;
    ObjectRef(ObjectRef&&) = delete;
    ObjectRef& operator=(const ObjectRef&) = delete;
    ObjectRef& operator=(ObjectRef&&) = delete;

    virtual bool empty() const noexcept = 0;

    virtual void release() noexcept = 0;
};

/** An object pool class. */
template <typename T, std::size_t N>
class ObjectPool final {
    static_assert(N > 0, "ObjectPool: 0 size pool is not allowed.");

public:
    using size_type = std::size_t;
    using value_type = ObjectRef<T>;
    using pointer = value_type *;

private:
    class Holder final : public value_type {
    private:
        std::atomic_bool m_in_use { false };

    public:
        Holder() = default;
        virtual ~Holder() = default;

        Holder(const Holder&) = delete;
        Holder(Holder&&) = delete;
        Holder& operator=(const Holder&) = delete;
        Holder& operator=(Holder&&) = delete;

        virtual bool empty() const noexcept override {
            return !m_in_use;
        }

        virtual void release() noexcept override {
            m_in_use = false;
        }

        void acquire() noexcept {
            m_in_use = true;
        }
    };

    Holder m_pool[N];

    size_type size_of_free() const noexcept {
        size_type n { 0 };
        for (const auto& p : m_pool) {
            if (p.empty()) {
                n++;
            }
        }
        return n;
    }

    size_type size_of_used() const noexcept {
        return N - size_of_free();
    }

public:
    void clear() noexcept {
        for (auto&& p : m_pool) {
            p.release();
        }
    }

    bool empty() const noexcept {
        return size_of_used() == 0;
    }

    bool full() const noexcept {
        return size_of_free() == 0;
    }

    pointer get() noexcept {
        for (auto&& p : m_pool) {
            if (p.empty()) {
                p.acquire();
                return &p;
            }
        }
        return nullptr;
    }

    size_type max_size() const noexcept {
        return N;
    }

    size_type size() const noexcept {
        return size_of_used();
    }
};

} // inline namespace object_pool

} // namespace cun

#endif // ndef CUN_OBJECT_POOL_HPP_INCLUDED
