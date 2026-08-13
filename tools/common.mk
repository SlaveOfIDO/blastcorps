# Shared toolchain and compiler flags for the init/ and game/ Makefiles.
# Included as `include ../tools/common.mk` - every path here is written
# relative to that (init/ and game/ are both one level under the content
# root). Requires NON_MATCHING to already be set by the includer.

CROSS = mips-linux-gnu-
AS = $(CROSS)as
LD = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy
PYTHON = python3
CC = ../tools/ido5.3_recomp/cc
GCC = $(CROSS)gcc
GREP = grep -rl

OPT_FLAGS := -O1
MIPSISET := -mips2 -o32
OBJCOPYFLAGS = -O binary
ASFLAGS = -EB -mtune=vr4300 -march=vr4300 -mabi=32 -I ../include
INCLUDE_CFLAGS := -I . -I ../include -I ../include/2.0D -I ../include/2.0D/PR
CFLAGS := -G 0 -Xfullwarn -Xcpluscomm -nostdinc -non_shared -Wab,-r4300_mul -D_LANGUAGE_C -D_FINALROM -DNON_MATCHING=$(NON_MATCHING) -DDEBUG=0 -DTARGET_N64 -DNDEBUG -DF3D_OLD -woff 649,838 $(INCLUDE_CFLAGS)
GCC_ASFLAGS := -EB -x assembler-with-cpp -march=vr4300 -mabi=32 -O2 -G 0 -w -nostdinc -c -mfix4300 -mno-abicalls -DMIPSEB -D_LANGUAGE_ASSEMBLY -D_MIPS_SIM=1 -D_MIPS_SZLONG=32 -mtune=vr4300 -fno-align-labels -fno-align-functions -fno-align-loops -fno-align-jumps -fno-common -fno-zero-initialized-in-bss -mfp32 -ffreestanding -O -mno-shared -fno-PIC
GCC_CFLAGS := -EB -march=vr4300 -mabi=32 -mtune=vr4300 -mfix4300 -mno-abicalls -mno-shared -fno-PIC -mfp32 -ffreestanding -fno-common -fno-merge-constants -G 0 -Os -D_LANGUAGE_C -D_FINALROM -DNON_MATCHING=$(NON_MATCHING) -DDEBUG=0 -DTARGET_N64 -DNDEBUG -DF3D_OLD $(INCLUDE_CFLAGS)

BUILD_DIR = build
TOOLS_DIR = ../tools
