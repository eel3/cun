CUN: C++ Utility for Niche use cases
====================================

Miscellaneous C++ utility classes and functions for niche use cases.

License
-------

zlib License.

Target environments
-------------------

Windows, Linux, macOS.

CUN is written in ISO C++14, and so probably works fine on other OS.

Set up
------

TBD.

List of utilities
-----------------

### Binary data writer && Byte data writer

An abstraction layer of binary data writing.

#### Dependencies

* Data writer interface

#### Files

* core
    * binary_writer_core.hpp
* embedded
    * binary_writer.hpp
* hosted
    * binary_writer.hpp

### Byte packer / unpacker

Binary data pack / unpack functions.

#### Dependencies

* Binary data writer && Byte data writer

#### Files

* core
    * byte_packer_core.cpp
    * byte_packer_core.hpp
    * byte_packer.h
* embedded
    * byte_packer.hpp
* hosted
    * byte_packer.hpp

### Circular buffer

A circular buffer class without implicit dynamic memory allocation.

#### Dependencies

None.

#### Files

* core
    * circular_buffer.hpp

### C-string utility

Utility functions for C-style string.

#### Dependencies

None.

#### Files

* core
    * cstrutil.h
    * cstrutil.hpp
    * cstrutil_copy.cpp
    * cstrutil_is_ctype.cpp
    * cstrutil_to_numeric.cpp

### Data writer interface

An abstraction interface of data writing.

#### Dependencies

None.

#### Files

* core
    * data_writer.hpp

### Event loop toolbox

An event loop toolbox.

#### Dependencies

* Mailbox

#### Files

* hosted
    * event_loop.hpp

### Logger

A logger class.

#### Dependencies

None.

#### Files

* machdep
    * logger.hpp

### Mailbox

An inter-thread communication mailbox class.

#### Dependencies

None.

#### Files

* hosted
    * mailbox.hpp

### Miscellaneous

Miscellaneous utility functions.

#### Dependencies

None.

#### Files

* core
    * misc.h
    * misc_core.hpp
* embedded
    * misc.hpp
* hosted
    * misc.hpp
    * misc_basename.cpp

### Repeat call function utility

A state machine class to repeat function call.

#### Dependencies

None.

#### Files

* core
    * repeat_call_core.hpp
* embedded
    * repeat_call.hpp
* hosted
    * repeat_call.hpp

### Sequence utility

Utility functions for sequence class.

#### Dependencies

None.

#### Files

* hosted
    * sequtil.hpp

### Sleep utility

Utility functions to sleep / delay current thread.

#### Dependencies

None.

#### Files

* hosted
    * sleep.cpp
    * sleep.hpp

### Software timer

A simple software timer.

#### Dependencies

None.

#### Files

* hosted
    * soft_timer.hpp

### String utility

Utility functions for std::string.

#### Dependencies

None.

#### Files

* hosted
    * strutil.hpp
    * strutil_to_numeric.cpp

### System tick utility

Utility functions for system tick.

#### Dependencies

None.

#### Files

* hosted
    * system_tick.cpp
    * system_tick.hpp

### Unit test utility

Utility functions for unit test.

#### Dependencies

None.

#### Files

* hosted
    * unittest.hpp
