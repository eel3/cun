// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: Circular buffer.

// C++ standard library
#include <cstdint>
#include <cstdlib>

// C++ user library
#include "circular_buffer.hpp"
#include "unittest.hpp"

int main()
{
    // C++ standard library
    using std::uint8_t;

    // C++ user library
    using cun::CircularBuffer;

    auto ut = CUN_UNITTEST_MAKE();

    CUN_UNITTEST_TITLE(ut, "Test code: Circular buffer.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "default parameter check");
    CUN_UNITTEST_EXEC(ut, CircularBuffer<uint8_t, 1> cb1);
    CUN_UNITTEST_EVAL(ut, cb1.empty());
    CUN_UNITTEST_EVAL(ut, cb1.free_size() == 1);
    CUN_UNITTEST_EVAL(ut, !cb1.full());
    CUN_UNITTEST_EVAL(ut, cb1.max_size() == 1);
    CUN_UNITTEST_EVAL(ut, cb1.size() == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "push data: part.1");
    CUN_UNITTEST_EVAL(ut, cb1.push(1));
    CUN_UNITTEST_EVAL(ut, !cb1.empty());
    CUN_UNITTEST_EVAL(ut, cb1.free_size() == 0);
    CUN_UNITTEST_EVAL(ut, cb1.full());
    CUN_UNITTEST_EVAL(ut, cb1.size() == 1);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "pop data");
    CUN_UNITTEST_EXEC(ut, uint8_t val = 0);
    CUN_UNITTEST_EVAL(ut, cb1.pop(val));
    CUN_UNITTEST_EVAL(ut, val == 1);
    CUN_UNITTEST_EVAL(ut, cb1.empty());
    CUN_UNITTEST_EVAL(ut, cb1.free_size() == 1);
    CUN_UNITTEST_EVAL(ut, !cb1.full());
    CUN_UNITTEST_EVAL(ut, cb1.size() == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "push data: part.2");
    CUN_UNITTEST_EVAL(ut, cb1.push(2));
    CUN_UNITTEST_EVAL(ut, !cb1.push(3));
    CUN_UNITTEST_EVAL(ut, cb1.front() == 2);
    CUN_UNITTEST_EVAL(ut, cb1.back() == 2);
    CUN_UNITTEST_EVAL(ut, !cb1.empty());
    CUN_UNITTEST_EVAL(ut, cb1.free_size() == 0);
    CUN_UNITTEST_EVAL(ut, cb1.full());
    CUN_UNITTEST_EVAL(ut, cb1.size() == 1);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "drop data");
    CUN_UNITTEST_EVAL(ut, cb1.drop());
    CUN_UNITTEST_EVAL(ut, cb1.empty());
    CUN_UNITTEST_EVAL(ut, cb1.free_size() == 1);
    CUN_UNITTEST_EVAL(ut, !cb1.full());
    CUN_UNITTEST_EVAL(ut, cb1.size() == 0);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_NAME(ut, "clear all data");
    CUN_UNITTEST_EVAL(ut, cb1.push(4));
    CUN_UNITTEST_EVAL(ut, !cb1.empty());
    CUN_UNITTEST_EVAL(ut, cb1.free_size() == 0);
    CUN_UNITTEST_EVAL(ut, cb1.full());
    CUN_UNITTEST_EVAL(ut, cb1.size() == 1);
    CUN_UNITTEST_EXEC(ut, cb1.clear());
    CUN_UNITTEST_EVAL(ut, cb1.empty());
    CUN_UNITTEST_EVAL(ut, cb1.free_size() == 1);
    CUN_UNITTEST_EVAL(ut, !cb1.full());
    CUN_UNITTEST_EVAL(ut, cb1.size() == 0);
    CUN_UNITTEST_NL(ut);

    return EXIT_SUCCESS;
}
