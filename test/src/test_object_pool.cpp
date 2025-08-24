// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: Object pool.

// C++ standard library
#include <cstdint>
#include <cstdlib>

// C++ user library
#include "object_pool.hpp"
#include "unittest.hpp"

int main()
{
    // C++ standard library
    using std::uint8_t;

    // C++ user library
    using namespace cun::object_pool;

    auto ut = CUN_UNITTEST_MAKE();

    CUN_UNITTEST_TITLE(ut, "Test code: Object pool.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "default parameter check");
    CUN_UNITTEST_EXEC(ut, ObjectPool<int32_t, 2> pool);
    CUN_UNITTEST_EVAL(ut, pool.empty());
    CUN_UNITTEST_EVAL(ut, !pool.full());
    CUN_UNITTEST_EVAL(ut, pool.max_size() == 2);
    CUN_UNITTEST_EVAL(ut, pool.size() == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "get an object reference from the pool (1)");
    CUN_UNITTEST_EXEC(ut, auto ref1 = pool.get());
    CUN_UNITTEST_EVAL(ut, ref1 != nullptr);
    CUN_UNITTEST_EVAL(ut, !ref1->empty());
    CUN_UNITTEST_EVAL(ut, !pool.empty());
    CUN_UNITTEST_EVAL(ut, !pool.full());
    CUN_UNITTEST_EVAL(ut, pool.size() == 1);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "get an object reference from the pool (2)");
    CUN_UNITTEST_EXEC(ut, auto ref2 = pool.get());
    CUN_UNITTEST_EVAL(ut, ref2 != nullptr);
    CUN_UNITTEST_EVAL(ut, !ref2->empty());
    CUN_UNITTEST_EVAL(ut, !pool.empty());
    CUN_UNITTEST_EVAL(ut, pool.full());
    CUN_UNITTEST_EVAL(ut, pool.size() == 2);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "the pool is full");
    CUN_UNITTEST_EXEC(ut, auto ref3 = pool.get());
    CUN_UNITTEST_EVAL(ut, ref3 == nullptr);
    CUN_UNITTEST_EVAL(ut, !pool.empty());
    CUN_UNITTEST_EVAL(ut, pool.full());
    CUN_UNITTEST_EVAL(ut, pool.size() == 2);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "release an object reference");
    CUN_UNITTEST_EXEC(ut, ref1->release());
    CUN_UNITTEST_EVAL(ut, ref1->empty());
    CUN_UNITTEST_EVAL(ut, !ref2->empty());
    CUN_UNITTEST_EVAL(ut, !pool.empty());
    CUN_UNITTEST_EVAL(ut, !pool.full());
    CUN_UNITTEST_EVAL(ut, pool.size() == 1);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "force clear the pool");
    CUN_UNITTEST_EXEC(ut, pool.clear());
    CUN_UNITTEST_EVAL(ut, ref1->empty());
    CUN_UNITTEST_EVAL(ut, ref2->empty());
    CUN_UNITTEST_EVAL(ut, pool.empty());
    CUN_UNITTEST_EVAL(ut, !pool.full());
    CUN_UNITTEST_EVAL(ut, pool.size() == 0);
    CUN_UNITTEST_NL(ut);

    return EXIT_SUCCESS;
}
