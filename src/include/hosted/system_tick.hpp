// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// System tick utility.

#ifndef CUN_SYSTEM_TICK_HPP_INCLUDED
#define CUN_SYSTEM_TICK_HPP_INCLUDED

// C++ standard library
#include <chrono>

/* ---------------------------------------------------------------------- */
/*  */
/* ---------------------------------------------------------------------- */

namespace cun {

namespace system_tick {

extern std::chrono::milliseconds::rep millis() noexcept;
extern std::chrono::microseconds::rep micros() noexcept;
extern std::chrono::nanoseconds::rep nanos() noexcept;

} // namespace system_tick

} // namespace cun

#endif // ndef CUN_SYSTEM_TICK_HPP_INCLUDED
