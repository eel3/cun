# -*- coding: utf-8-unix -*-
# vim:fileencoding=utf-8:ff=unix

# ----------------------------------------------------------

root-dir       := ../..

src-root-dir   := $(root-dir)/src

include-dir          := $(src-root-dir)/include
include-core-dir     := $(include-dir)/core
include-embedded-dir := $(include-dir)/embedded
include-hosted-dir   := $(include-dir)/hosted

lib-dir          := $(src-root-dir)/lib
lib-core-dir     := $(lib-dir)/core
lib-hosted-dir   := $(lib-dir)/hosted

# ----------------------------------------------------------

VPATH          := $(lib-core-dir) $(lib-hosted-dir)

include-dirs   := $(addprefix -I ,$(include-core-dir) $(include-hosted-dir) $(VPATH) .)

object-files   := byte_packer_core.o \
                  cstrutil_copy.o cstrutil_is_ctype.o cstrutil_to_numeric.o \
                  misc_basename.o misc_hex.o \
                  sleep.o \
                  strutil_to_numeric.o \
                  system_tick.o

depend-files   := $(subst .o,.d,$(object-files))

target-name    := libcun.a

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

RANLIB         ?= ranlib

OPTIM          +=

WARN_COMMON    ?= -pedantic -Wall -Wextra
WARN_CXX       ?=

CXXWARN        ?= -std=c++20 $(WARN_COMMON) $(WARN_CXX)

CXXFLAGS       += $(OPTIM) $(CXXWARN) $(WARNADD)
CPPFLAGS       += $(include-dirs)
ARFLAGS        ?= rcS

# ----------------------------------------------------------

phony-targets  := all clean usage

.PHONY: $(phony-targets)

usage:
	# usage: $(MAKE) [DEBUG=1] [PROFILE=1] $(patsubst %,[%],$(phony-targets))

all: $(target-name)

$(target-name): $(target-name)($(sort $(object-files)))
	$(RANLIB) $@

clean:
	$(RM) $(target-name) $(object-files) $(depend-files) $(cov-files)

# ----------------------------------------------------------

ifneq "$(MAKECMDGOALS)" ""
ifneq "$(MAKECMDGOALS)" "clean"
ifneq "$(MAKECMDGOALS)" "usage"
  -include $(depend-files)
endif
endif
endif

# $(call make-depend,source-file,object-file,depend-file,cc,flags)
make-depend = $4 -MM -MF $3 -MP -MT $2 $5 $(CPPFLAGS) $1

%.o: %.cpp
	$(call make-depend,$<,$@,$(subst .o,.d,$@),$(CXX),$(CXXFLAGS))
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<
