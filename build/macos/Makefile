# -*- coding: utf-8-unix -*-
# vim:fileencoding=utf-8:ff=unix

# ----------------------------------------------------------

PREFIX         := xcrun 
CXX            := $(PREFIX)$(CXX)
AR             := $(PREFIX)$(AR)
RANLIB         := $(PREFIX)ranlib

CXXFLAGS        =
CPPFLAGS        =
ARFLAGS         = rcS

WARNADD        :=

# ----------------------------------------------------------

SDKROOT        := $(shell xcodebuild -version -sdk macosx | sed -n '/^Path: /s///p')

CPPFLAGS       += -isysroot "$(SDKROOT)"
TARGET_ARCH    := -mmacosx-version-min=10.15 -arch x86_64 -arch arm64

# ----------------------------------------------------------

include ../unix-common/common.mk
