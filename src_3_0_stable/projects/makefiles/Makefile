#############################################################################
# Subtitles Mod Makefile for GNU Make
#############################################################################

OS ?= $(shell uname)

#############################################################################
# SETUP DIRECTORIES
#############################################################################

# It must be top-level in order to get the right path; do not include or call it from any other
ifeq ("$(MAKELEVEL)", "0")
	MAKEFILE_DIR := $(shell dirname "$(wordlist 1,$(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))")
	ifeq ("$(MAKEFILE_DIR)", "")
		MAKEFILE_DIR := $(CURDIR)
	endif
else
	# Try as a last resort path
	MAKEFILE_DIR := $(CURDIR)
endif

# Get active build configuration
ifeq ("$(BUILD_CFG)", "")
	BUILD_CFG := release
endif
ifneq ("$(BUILD_CFG)", "release")
	BUILD_CFG := debug
endif

# The first two paths must be relative to Makefile's
BUILD_SRC_DIR       := ../..
BUILD_OBJ_DIR       := $(BUILD_CFG)
BUILD_DST_DIR       := $(BUILD_SRC_DIR)/../../GoldSrc Engine

CL_BASE_SRC_DIR     := $(BUILD_SRC_DIR)/cl_dll
COMMON_SRC_DIR      := $(BUILD_SRC_DIR)/common
SV_BASE_SRC_DIR     := $(BUILD_SRC_DIR)/dlls
ENGINE_SRC_DIR      := $(BUILD_SRC_DIR)/engine
EXTERNAL_SRC_DIR    := $(BUILD_SRC_DIR)/external
GAME_SHARED_SRC_DIR := $(BUILD_SRC_DIR)/game_shared
LIBS_BASE_DIR       := $(BUILD_SRC_DIR)/lib
PM_SHARED_SRC_DIR   := $(BUILD_SRC_DIR)/pm_shared
PUBLIC_SRC_DIR      := $(BUILD_SRC_DIR)/public
SM_BASE_SRC_DIR     := $(BUILD_SRC_DIR)/subs_mod
UTILS_SRC_DIR       := $(BUILD_SRC_DIR)/utils
UTILS_VGUI_SRC_DIR  := $(UTILS_SRC_DIR)/vgui

ifeq ("$(OS)", "Linux")
	LIBS_BASE_DIR := $(LIBS_BASE_DIR)/linux
else
ifeq ("$(OS)", "Darwin")
	LIBS_BASE_DIR := $(LIBS_BASE_DIR)/osx
endif
endif

BACKUP_SUFFIX := .bak

#############################################################################
# ARCHITECTURE FLAGS
#############################################################################

ifeq ("$(BUILD_CFG)", "release")
	ARCH_CFLAGS_I486  := -m32 -O3 -gdwarf-2 -g2
	ARCH_CFLAGS_I686  := -m32 -O3 -gdwarf-2 -g2
	ARCH_CFLAGS_AMD   := -m32 -O3 -gdwarf-2 -g2
	ARCH_CFLAGS_AMD64 := -m64 -O3 -gdwarf-2 -g2
else
	ARCH_CFLAGS_I486  := -m32 -gdwarf-2 -g2
	ARCH_CFLAGS_I686  := -m32 -gdwarf-2 -g2
	ARCH_CFLAGS_AMD   := -m32 -gdwarf-2 -g2
	ARCH_CFLAGS_AMD64 := -m64 -gdwarf-2 -g2
endif

ifeq ("$(OS)", "Linux")
	ARCH_CFLAGS_I486 += -march=pentium-m -mfpmath=387
	ARCH_CFLAGS_I686 += -march=pentium-m -mfpmath=387
	ARCH_CFLAGS_AMD  += -march=k6 -mfpmath=387
else
ifeq ("$(OS)", "Darwin")
	ARCH_CFLAGS_I486 += -march=pentium-m -mfpmath=387
	ARCH_CFLAGS_I686 += -march=pentium-m -mfpmath=387
	ARCH_CFLAGS_AMD  += -mfpmath=387
endif
endif

ARCH       := i386
ARCH_FLAGS := $(ARCH_CFLAGS_I686)

#############################################################################
# CONFIGURING TOOLS
#############################################################################

CMN_FLAGS := $(ARCH_FLAGS)
LDFLAGS   := $(LDFLAGS)
LDLIBS    := $(LDLIBS) -lstdc++ -lpthread -lm

ifeq ("$(OS)", "Linux")
	CC      := $(shell which gcc)
	CXX     := $(shell which g++)
	LDFLAGS += -L"$(shell $(CXX) $(CMN_FLAGS) -print-file-name=libstdc++.so | xargs dirname)" -Wl,--as-needed
	LDLIBS  += -ldl
else
ifeq ("$(OS)", "Darwin")
	DEVELOPER_DIR := $(shell /usr/bin/xcode-select -print-path)

	ifeq ("$(findstring 10.7, $(shell sw_vers -productVersion))", "")
		COMPILER_BIN_DIR := $(DEVELOPER_DIR)/usr/bin
		SDK_DIR          := $(DEVELOPER_DIR)/SDKs
	else
		COMPILER_BIN_DIR := $(DEVELOPER_DIR)/Toolchains/XcodeDefault.xctoolchain/usr/bin
		SDK_DIR          := $(DEVELOPER_DIR)/Platforms/MacOSX.platform/Developer/SDKs
	endif

	# FIXME: make SDK root auto-detection?
	SDKROOT ?= $(SDK_DIR)/MacOSX10.8.sdk

	CMN_FLAGS += -arch $(ARCH) \
                 -march=prescott \
                 -gdwarf-2 \
                 -g2 \
                 -momit-leaf-frame-pointer \
                 -mtune=core2 \
                 -isysroot "$(SDKROOT)" \
                 -mmacosx-version-min=10.5 \
                 -fasm-blocks \
                 -Qunused-arguments \
                 -Wno-typedef-redefinition

	CC  := $(COMPILER_BIN_DIR)/clang
	CXX := $(COMPILER_BIN_DIR)/clang++
endif
endif

CFLAGS   := $(CFLAGS)
CXXFLAGS := $(CXXFLAGS)
LDFLAGS  += $(CMN_FLAGS)
LINK     := $(CC)

ifneq ("$(BUILD_CFG)", "release")
	LDFLAGS   += -Wl,-i
	CMN_FLAGS += -D_DEBUG \
                 -Wno-write-strings
	CXXFLAGS  += -Wno-conversion-null \
                 -Wno-invalid-offsetof
else
	CMN_FLAGS += -DNDEBUG \
                 -fpermissive \
                 -fexpensive-optimizations \
                 -w
endif

ifeq ("$(OS)", "Linux")
	CMN_FLAGS += -DPOSIX -D_POSIX \
                 -DLINUX -D_LINUX
else
ifeq ("$(OS)", "Darwin")
	CMN_FLAGS += -DPOSIX -D_POSIX \
                 -DLINUX -D_LINUX \
                 -DOSX -D_OSX \
                 -fvisibility=hidden
endif
endif

CMN_FLAGS += -DGNUC \
             -Dstricmp=strcasecmp \
             -D_strnicmp=strncasecmp \
             -Dstrnicmp=strncasecmp \
             -D_snprintf=snprintf \
             -D_alloca=alloca \
             -D_vsnprintf=vsnprintf \
             -fno-strict-aliasing \
             -fno-exceptions \
             -fno-common \
             -Werror=return-type

CFLAGS    += $(CMN_FLAGS)
CXXFLAGS  += $(CMN_FLAGS)

ifeq ("$(OS)", "Linux")
	# Who wants to programmer hell?..
	ESCAPED_ORIGIN := \$$$$ORIGIN

	SHLIBEXT     := so
	SHLIBCFLAGS  :=
	SHLIBLDFLAGS := -shared -gdwarf-2 -g2 -Wl,--no-undefined,-z,origin,-rpath,"$(ESCAPED_ORIGIN)"
else
ifeq ("$(OS)", "Darwin")
	SHLIBEXT     := dylib
	SHLIBCFLAGS  :=
	SHLIBLDFLAGS := -dynamiclib -gdwarf-2 -g2 -Wl,-no-undefined,-rpath,"@loader_path/."
endif
endif

SHLIBCXXFLAGS := $(SHLIBCFLAGS)
SHLIBLDFLAGS  += -Wl,-rpath-link,"$(LIBS_BASE_DIR)" -L"$(LIBS_BASE_DIR)"
MAKE_FLAGS    := -j 8

#############################################################################
# SETUP AND BUILD
#############################################################################

SM_HL_CL_MAKE := $(MAKE) -f Makefile.sm_hl_cl $(MAKE_FLAGS)
SM_HL_SV_MAKE := $(MAKE) -f Makefile.sm_hl_sv $(MAKE_FLAGS)

TARGETS := sm_hl_cl_build \
           sm_hl_sv_build

.EXPORT_ALL_VARIABLES:

all:     targets
clean:   sm_hl_sv_clean sm_hl_cl_clean dirs_clean
targets: $(TARGETS)
os_chk:  $(OS)

# Check if running OS is supported by Makefile
Linux:
Darwin:

sm_hl_cl_build: os_chk
	$(SM_HL_CL_MAKE) -C "$(MAKEFILE_DIR)" all

sm_hl_cl_clean: os_chk
	$(SM_HL_CL_MAKE) -C "$(MAKEFILE_DIR)" clean

sm_hl_sv_build: os_chk
	$(SM_HL_SV_MAKE) -C "$(MAKEFILE_DIR)" all

sm_hl_sv_clean: os_chk
	$(SM_HL_SV_MAKE) -C "$(MAKEFILE_DIR)" clean

dirs_clean:     os_chk
	-rm -rf "$(MAKEFILE_DIR)/$(BUILD_OBJ_DIR)"

#############################################################################
