ChangeLog
=========

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
