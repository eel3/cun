# -*- coding: utf-8-unix -*-
# vim:fileencoding=utf-8:ff=unix

# ----------------------------------------------------------

root-dir       := ../../..

cun-dir         = $(root-dir)/build/$(CUN_TARGET)

src-root-dir   := $(root-dir)/src

include-dir          := $(src-root-dir)/include
include-core-dir     := $(include-dir)/core
include-embedded-dir := $(include-dir)/embedded
include-hosted-dir   := $(include-dir)/hosted

machdep-logger-dir   := $(src-root-dir)/machdep/logger/$(CUN_MACHDEP_LOGGER)

test-dir       := $(root-dir)/test/src

# ----------------------------------------------------------

VPATH            := $(test-dir)

include-dirs     := $(addprefix -I ,$(include-core-dir) $(include-hosted-dir) $(machdep-logger-dir) $(VPATH) .)

target-name      := test_binary_writer \
                    test_byte_packer \
                    test_circular_buffer \
                    test_cstrutil \
                    test_event_loop \
                    test_logger \
                    test_mailbox \
                    test_misc \
                    test_repeat_call \
                    test_sequtil \
                    test_sleep \
                    test_soft_timer \
                    test_strutil \
                    test_system_tick

lib-object-files := 

object-files     := $(lib-object-files) $(addsuffix .o,$(target-name))

depend-files     := $(subst .o,.d,$(object-files))

libcun-file      := $(cun-dir)/libcun.a

testlog-file     := unittest.log

# ----------------------------------------------------------

ifeq "$(strip $(DEBUG))" ""
  CPPFLAGS     += -DNDEBUG
  OPTIM        += -O2
else
  CPPFLAGS     += -DDEBUG
  OPTIM        += -g
endif

ifneq "$(strip $(PROFILE))" ""
  OPTIM        += --coverage
  cov-files     = $(subst .o,.gcno,$(object-files)) $(subst .o,.gcda,$(object-files)) $(wildcard *.gcov)
endif

OPTIM          +=

WARN_COMMON    ?= -pedantic -Wall -Wextra
WARN_CXX       ?=

CXXWARN        ?= -std=c++17 $(WARN_COMMON) $(WARN_CXX)

CXXFLAGS       += $(OPTIM) $(CXXWARN) $(WARNADD)
CPPFLAGS       += $(include-dirs)
LDFLAGS        += $(OPTIM)

#-----------------------------------------------------------

# $(call make-cun,arguments)
make-cun        = cd "$(cun-dir)"; $(MAKE) $1

# ----------------------------------------------------------

phony-targets  := all clean mostlyclean run usage

.PHONY: $(phony-targets)

usage:
	# usage: $(MAKE) [DEBUG=1] [PROFILE=1] $(patsubst %,[%],$(phony-targets))

run: all
	@for i in $(target-name); do echo $$i; "./$$i"; done | tee $(testlog-file) | grep -n '^NG' || echo All tests passed.

all: $(target-name)

.SECONDEXPANSION:
$(target-name): $$@.o $(lib-object-files) $(libcun-file)

$(libcun-file):
	$(call make-cun,all)

clean: mostlyclean
	$(call make-cun,clean)

mostlyclean:
	$(RM) $(target-name) $(object-files) $(depend-files) $(cov-files) $(testlog-file)

# ----------------------------------------------------------

ifneq "$(MAKECMDGOALS)" ""
ifneq "$(MAKECMDGOALS)" "clean"
ifneq "$(MAKECMDGOALS)" "mostlyclean"
ifneq "$(MAKECMDGOALS)" "usage"
  -include $(depend-files)
endif
endif
endif
endif

# $(call make-depend,source-file,object-file,depend-file,cc,flags)
make-depend = $4 -MM -MF $3 -MP -MT $2 $5 $(CPPFLAGS) $1

%.o: %.cpp
	$(call make-depend,$<,$@,$(subst .o,.d,$@),$(CXX),$(CXXFLAGS))
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<
