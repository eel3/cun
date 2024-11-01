# -*- coding: cp932-dos -*-
# vim:fileencoding=cp932:ff=dos

# ----------------------------------------------------------

root_dir        = ..\..\..

cun_dir         = $(root_dir)\build\msvc

src_root_dir    = $(root_dir)\src

include_dir           = $(src_root_dir)\include
include_core_dir      = $(include_dir)\core
include_embedded_dir  = $(include_dir)\embedded
include_hosted_dir    = $(include_dir)\hosted

machdep_logger_dir    = $(src_root_dir)\machdep\logger\windows

test_dir        = $(root_dir)\test\src

# ----------------------------------------------------------

vpath             = $(test_dir)

include_dirs      = $(include_core_dir) $(include_hosted_dir) $(machdep_logger_dir) $(vpath)

target_name       = test_binary_writer.exe \
                    test_byte_packer.exe \
                    test_circular_buffer.exe \
                    test_cstrutil.exe \
                    test_event_loop.exe \
                    test_logger.exe \
                    test_mailbox.exe \
                    test_misc.exe \
                    test_mockable.exe \
                    test_mockout.exe \
                    test_repeat_call.exe \
                    test_sequtil.exe \
                    test_sleep.exe \
                    test_soft_timer.exe \
                    test_strutil.exe \
                    test_system_tick.exe

lib_object_files  = 

object_files      = $(lib_object_files) $(target_name:.exe=.obj)

libcun_file       = $(cun_dir)\libcun.lib

lib_files         =

win_ver           = 0x0A00

testlog_file      = unittest.log

# ----------------------------------------------------------

!ifdef DEBUG
ccdefs      = /MTd /Zi /D WIN32;_DEBUG;_CONSOLE;WINVER=$(win_ver);_WIN32_WINNT=$(win_ver);_CRT_SECURE_NO_WARNINGS;_WINDOWS;DEBUG
!else
ccdefs      = /MT /D WIN32;NDEBUG;_CONSOLE;WINVER=$(win_ver);_WIN32_WINNT=$(win_ver);_CRT_SECURE_NO_WARNINGS;_WINDOWS
!endif

CXXFLAGS    = /nologo /std:c++17 /EHsc /GL /GS /RTCs /RTCu /W4 $(ccdefs:;= /D ) /I $(include_dirs: = /I )

#-----------------------------------------------------------

make_cun    = cd "$(cun_dir)" & $(MAKE) /NOLOGO

# ----------------------------------------------------------

phony_targets   = all clean mostlyclean run usage

usage: FORCE
	:: usage: $(MAKE) [DEBUG=1] [$(phony_targets: =] [)]

run: all
	@( for %%I in ($(target_name)) do @( echo %%I & %%I ) ) >$(testlog_file)
	@findstr /n "^NG\>" $(testlog_file) || echo All tests passed.

all: $(target_name)

$(target_name): $$(@B).obj $(lib_object_files) $(libcun_file)
	link.exe /NOLOGO /LTCG /OUT:$@ /SUBSYSTEM:CONSOLE $** $(lib_files)

$(libcun_file):
	$(make_cun) all

clean: mostlyclean
	$(make_cun) clean

mostlyclean: FORCE
	del /F $(target_name) $(object_files) *.pdb $(testlog_file)

FORCE:

# ----------------------------------------------------------

{$(test_dir)}.cpp.obj::
	$(CXX) $(CXXFLAGS) /c $<
