# VEXcode mkenv.mk 2022_06_26_01

# macros to help with paths that include spaces
sp = $() $()
qs = $(subst ?, ,$1)
sq = $(subst $(sp),?,$1)

# default platform and build location
PLATFORM  = vexiq2
BUILD     = build

# version for clang headers
ifneq ("$(origin HEADERS)", "command line")
HEADERS = 18
endif

# Project name passed from app
ifeq ("$(origin P)", "command line")
PROJECT  := $(P)
else
PROJECT  := $(call qs,$(notdir $(call sq,${CURDIR})))
endif

# check if the PROJECT name contains any whitespace
ifneq (1,$(words $(PROJECT)))
$(error Project name cannot contain whitespace: $(PROJECT))
endif

# SDK path passed from app
# if not set then environmental variabled used
ifeq ("$(origin T)", "command line")
VEX_SDK_PATH = $(T)
endif
# backup if still not set
VEX_SDK_PATH ?= ${HOME}/sdk

# printf_float flag name passed from app
ifeq ("$(origin PRINTF_FLOAT)", "command line")
PRINTF_FLAG = -u_printf_float
endif

# Verbose flag passed from app
ifeq ("$(origin V)", "command line")
BUILD_VERBOSE=$(V)
endif

# allow verbose to be set by makefile if not set by app
ifndef VERBOSE
BUILD_VERBOSE ?= 0
else
BUILD_VERBOSE ?= $(VERBOSE)
endif

# use verbose flag
ifeq ($(BUILD_VERBOSE),0)
Q = @
else
Q =
endif

# compile and link tools
CC      = clang
CXX     = clang
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size
LINK    = arm-none-eabi-ld
ARCH    = arm-none-eabi-ar
ECHO    = @echo
DEFINES = -DVexIQ2

# platform specific macros, OS is env variable on windows
ifeq ($(OS),Windows_NT)
$(info windows build for platform $(PLATFORM))
SHELL = cmd.exe
MKDIR = md "$(@D)" 2> nul || :
RMDIR = rmdir /S /Q
CLEAN = $(RMDIR) $(BUILD) 2> nul || :
else
# which flavor of linux
UNAME := $(shell sh -c 'uname -sm 2>/dev/null || Unknown')
$(info unix build for platform $(PLATFORM) on $(UNAME))
MKDIR = mkdir -p "$(@D)" 2> /dev/null || :
RMDIR = rm -rf
CLEAN = $(RMDIR) $(BUILD) 2> /dev/null || :
endif

# toolchain include and lib locations
TOOL_INC  = -I"$(VEX_SDK_PATH)/$(PLATFORM)/clang/$(HEADERS)/include" -I"$(VEX_SDK_PATH)/$(PLATFORM)/gcc/include/c++/13.2.1" -I"$(VEX_SDK_PATH)/$(PLATFORM)/gcc/include/c++/13.2.1/arm-none-eabi/thumb/v7e-m+dp/hard" -I"$(VEX_SDK_PATH)/$(PLATFORM)/gcc/include"
TOOL_LIB  = -L"$(VEX_SDK_PATH)/$(PLATFORM)/gcc/lib"

# compiler flags
CFLAGS_CL = -target thumbv7-none-eabi -fshort-enums -Wno-unknown-attributes -U__INT32_TYPE__ -U__UINT32_TYPE__ -D__INT32_TYPE__=long -D__UINT32_TYPE__='unsigned long' 
CFLAGS_V7 = -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS    = ${CFLAGS_CL} ${CFLAGS_V7} -Os -Wall -Werror=return-type -std=gnu23 $(DEFINES)
CXX_FLAGS = ${CFLAGS_CL} ${CFLAGS_V7} -Os -Wall -Werror=return-type -fno-rtti -fno-threadsafe-statics -fno-exceptions -std=gnu++23 -ffunction-sections -fdata-sections $(DEFINES)

# linker flags
LNK_FLAGS = -z noexecstack --no-warn-rwx-segments -nostdlib $(PRINTF_FLAG) -T "$(VEX_SDK_PATH)/$(PLATFORM)/lscript.ld" -Map="$(BUILD)/$(PROJECT).map" --gc-section -L"$(VEX_SDK_PATH)/$(PLATFORM)" ${TOOL_LIB}

# future statuc library
PROJECTLIB = lib$(PROJECT)
ARCH_FLAGS = rcs

# libraries
LIBS =  --start-group -lviq2rt -lc_nano -lstdc++_nano -lm -lgcc --end-group

# include file paths
INC += $(addprefix -I, ${INC_F})
INC += -I"$(VEX_SDK_PATH)/$(PLATFORM)/include"
INC += ${TOOL_INC}