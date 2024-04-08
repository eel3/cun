ChangeLog
=========

[0.0.0.2024040801] - 2024-04-08
-------------------------------

### Fixed

* Unit test: Sleep utility: Fix a possible failing test.

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
