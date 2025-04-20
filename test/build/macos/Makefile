# -*- coding: utf-8-unix -*-
# vim:fileencoding=utf-8:ff=unix

# ----------------------------------------------------------

CUN_TARGET     := macos

CUN_MACHDEP_LOGGER := unix

# ----------------------------------------------------------

PREFIX         := xcrun 
CXX            := $(PREFIX)$(CXX)

CXXFLAGS        =
CPPFLAGS        =
LDFLAGS         =
LDLIBS         := -lm -lc++

WARNADD        := -Wno-sizeof-pointer-div

# ----------------------------------------------------------

SDKROOT        := $(shell xcodebuild -version -sdk macosx | sed -n '/^Path: /s///p')

CPPFLAGS       += -isysroot "$(SDKROOT)"
TARGET_ARCH    := -mmacosx-version-min=10.15 -arch x86_64 -arch arm64

# ----------------------------------------------------------

include ../unix-common/common.mk
