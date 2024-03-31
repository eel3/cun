// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Sleep utility.

#ifndef CUN_SLEEP_HPP_INCLUDED
#define CUN_SLEEP_HPP_INCLUDED

// C++ standard library
#include <chrono>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

namespace sleep {

extern void secs(const std::chrono::seconds::rep r) noexcept;
extern void millis(const std::chrono::milliseconds::rep r) noexcept;
extern void micros(const std::chrono::microseconds::rep r) noexcept;
extern void nanos(const std::chrono::nanoseconds::rep r) noexcept;

} // namespace sleep

} // namespace cun

#endif // ndef CUN_SLEEP_HPP_INCLUDED
