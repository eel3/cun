// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Sleep utility.

// C++ standard library
#include <thread>

// For this library
#include "sleep.hpp"

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace {

template <typename T>
void delay(const typename T::rep& r) noexcept
{
    try {
        std::this_thread::sleep_for(T { r });
    } catch (...) {
        /*EMPTY*/
    }
}

} // namespace

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

namespace sleep {

using std::chrono::seconds;
using std::chrono::milliseconds;
using std::chrono::microseconds;
using std::chrono::nanoseconds;

void secs(const seconds::rep r) noexcept
{
    delay<seconds>(r);
}

void millis(milliseconds::rep r) noexcept
{
    delay<milliseconds>(r);
}

void micros(const microseconds::rep r) noexcept
{
    delay<microseconds>(r);
}

void nanos(const nanoseconds::rep r) noexcept
{
    delay<nanoseconds>(r);
}

} // namespace sleep

} // namespace cun
