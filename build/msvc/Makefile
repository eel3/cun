# -*- coding: cp932-dos -*-
# vim:fileencoding=cp932:ff=dos

# ----------------------------------------------------------

root_dir        = ..\..

src_root_dir    = $(root_dir)\src

include_dir           = $(src_root_dir)\include
include_core_dir      = $(include_dir)\core
include_embedded_dir  = $(include_dir)\embedded
include_hosted_dir    = $(include_dir)\hosted

lib_dir           = $(src_root_dir)\lib
lib_core_dir      = $(lib_dir)\core
lib_hosted_dir    = $(lib_dir)\hosted

# ----------------------------------------------------------

vpath           = $(lib_core_dir) $(lib_hosted_dir)

include_dirs    = $(include_core_dir) $(include_hosted_dir) $(vpath)

object_files    = byte_packer_core.obj \
                  byteorder.obj \
                  cstrutil_copy.obj cstrutil_is_ctype.obj cstrutil_to_numeric.obj \
                  misc_basename.obj misc_hex.obj \
                  sleep.obj \
                  strutil_to_numeric.obj \
                  system_tick.obj

target_name     = libcun.lib

lib_files       =

win_ver         = 0x0A00

# ----------------------------------------------------------

!ifdef DEBUG
ccdefs      = /MTd /Zi /D WIN32;_DEBUG;_CONSOLE;WINVER=$(win_ver);_WIN32_WINNT=$(win_ver);_CRT_SECURE_NO_WARNINGS;_WINDOWS;DEBUG
!else
ccdefs      = /MT /D WIN32;NDEBUG;_CONSOLE;WINVER=$(win_ver);_WIN32_WINNT=$(win_ver);_CRT_SECURE_NO_WARNINGS;_WINDOWS
!endif

CXXFLAGS    = /nologo /std:c++20 /EHsc /GL /GS /RTCs /RTCu /W4 $(ccdefs:;= /D ) /I $(include_dirs: = /I )

# ----------------------------------------------------------

phony_targets   = all clean usage

usage: FORCE
	:: usage: $(MAKE) [DEBUG=1] [$(phony_targets: =] [)]

all: $(target_name)

$(target_name): $(object_files)
	lib.exe /NOLOGO /LTCG /OUT:$@ $** $(lib_files)

clean: FORCE
	del /F $(target_name) $(object_files) *.pdb

FORCE:

# ----------------------------------------------------------

{$(lib_core_dir)}.cpp.obj::
	$(CXX) $(CXXFLAGS) /c $<
{$(lib_hosted_dir)}.cpp.obj::
	$(CXX) $(CXXFLAGS) /c $<
