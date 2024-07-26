ChangeLog
=========

[0.0.0.2024072601] - 2024-07-26
-------------------------------

### Changed

* Library: Sleep utility: Use pass by value instead of pass by reference.

[0.0.0.2024042401] - 2024-04-24
-------------------------------

### Changed

* Library: Miscellaneous: Use universal reference in some functions.
* Library: Repeat call function utility: Remove the default constructor.
* Library: Repeat call function utility: Use universal reference in factory functions and the constructor.
* Library: Sequence utility: Use universal reference in some functions.
* Library: Software timer: Use universal reference in factory functions and constructors.

[0.0.0.2024041301] - 2024-04-13
-------------------------------

### Changed

* Build: Update C++ language standard from C++14 to C++17.
* Build: Windows: Make sure to specify C++ language standard.
* Library: Miscellaneous: max: Fix algorithm when comparing equal values.
* Library: Miscellaneous: min: Fix algorithm when comparing equal values.

[0.0.0.2024041201] - 2024-04-12
-------------------------------

### Changed

* Library: Mailbox: pop: Make it possible to set a flexible timeout value.
* Library: Miscellaneous: wait_until: Make it possible to specify a polling interval.
* Library: Miscellaneous: wait_while: Make it possible to specify a polling interval.
* Library: Software timer: Make it possible to set a flexible timer interval value.
* Unit test: Use chrono_literals.
* Unit test: Software timer: Use std::this_thread::sleep_for instead of cun::sleep::millis.

[0.0.0.2024041101] - 2024-04-11
-------------------------------

### Changed

* Library: Add an inline namespace to some utilities.
* Library: Software timer: Improve a first timing the timer is triggered.
* Unit test: Change coding style of importing symbols in namespaces.

[0.0.0.2024040801] - 2024-04-08
-------------------------------

### Added

* Library: Miscellaneous: wait_until: The first implementation.
* Library: Miscellaneous: wait_while: The first implementation.
* Library: Software timer: The first implementation.

### Changed

* Unit test: Circular buffer: Change test name.
* Unit test: Mailbox: Change test name.
* Unit test: String utility: tol_strict: Use CUN_UNITTEST_EXEC instead of CUN_UNITTEST_ECHO.

### Fixed

* Unit test: Sleep utility: Fix a possible failing test.
* Unit test: System tick utility: Fix a possible failing test.

[0.0.0.2024040101] - 2024-04-01
-------------------------------

### Changed

* Library: Sleep utility: Use pass by reference instead of pass by value.

[0.0.0.2024033101] - 2024-03-31
-------------------------------

### Added

* Library: Sleep utility: The first implementation.
* Library: System tick utility: Add new APIs.

### Changed

* Library: System tick utility: Improve code style.

[0.0.0.2023011801] - 2023-01-18
-------------------------------

### Changed

* Unit test: Mailbox: Improve some test cases.
* Unit test: System tick utility: Improve test cases.

[0.0.0.2023011601] - 2023-01-16
-------------------------------

### Added

* Library: System tick utility: The first implementation.

[0.0.0.2023011101] - 2023-01-11
-------------------------------

### Added

* Unit test: Sequence utility

### Changed

* Unit test: Repeat call function utility: Improve code style.

[0.0.0.2023010601] - 2023-01-06
-------------------------------

### Added

* Library: Repeat call function utility: shared_create: The first implementation.
* Library: Repeat call function utility: unique_create: The first implementation.
* Unit test: Mailbox
* Unit test: Repeat call function utility

### Changed

* Library: Repeat call function utility: Improve header file organization.
* Unit test: Miscellaneous: basename: Improve the order of test.

### Fixed

* Library: Repeat call function utility: Fix a possible Context::expired() return wrong value.
* Library: Repeat call function utility: s/builder/factory/g.

[0.0.0.2022123101] - 2022-12-31
-------------------------------

### Added

* Unit test: String utility

### Changed

* Library: String utility: Improve API.

### Fixed

* Library: String utility: join: Fix an inappropriate addition of separator.
* Unit test: C-string utility: Use CUN_UNITTEST_NAME instead of CUN_UNITTEST_COMMENT.

[0.0.0.2022122901] - 2022-12-29
-------------------------------

### Added

* Unit test: C-string utility

### Fixed

* Library: C-string utility: cun_cstrutil_tol: Fix potential null pointer access error.

[0.0.0.2022122801] - 2022-12-28
-------------------------------

### Added

* Unit test: Miscellaneous

### Fixed

* Library: Miscellaneous: remap_range: Fix potential division by zero error.
* Library: Miscellaneous: basename: Fix behavior when an argument contain only separator charactors.

[0.0.0.2022112701] - 2022-11-27
-------------------------------

### Changed

* Library: Event loop toolbox: Improve API.

[0.0.0.2022111201] - 2022-11-12
-------------------------------

### Changed

* Library: Event loop toolbox: Rename event types.

[0.0.0.2022111101] - 2022-11-11
-------------------------------

### Added

* Library: Event loop toolbox: The first implementation.

[0.0.0.2022071001] - 2022-07-10
-------------------------------

### Changed

* Build: Linux: Suppress compiler warnings.
* Library: Add noexcept specifier to some constructors.
* Library: Remove unnecessary whitespace.
* Library: Mailbox: Use std::queue&lt;T&gt;::size_type insted of std::size_t.
* Library: Mailbox: Add move semantics support.

### Fixed

* Library: Circular buffer: Add maximum buffer size limit check.
* Library: Logger/C++ Standard Library: Use _WIN32 and _WIN64 instead of WIN32 and WIN64.

[0.0.0.2022013101] - 2022-01-31
-------------------------------

### Added

* The first implementation of CUN.
