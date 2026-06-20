VERSION  := us.v11

### VARS


TOOLS_DIR := ../tools
BUILD_DIR = build

CROSS = mips-linux-gnu-
AS = $(CROSS)as
CPP = cpp
LD = $(CROSS)ld
OBJDUMP = $(CROSS)objdump
OBJCOPY = $(CROSS)objcopy
PYTHON = python3
GZIP = gzip
CC      = $(TOOLS_DIR)/ido5.3_recomp/cc
GCC = $(CROSS)gcc
GREP    = grep -rl

OPT_FLAGS := -O1
MIPSISET := -mips2 -o32
LD_SCRIPT = decompressed.$(VERSION).ld
OBJCOPYFLAGS = -O binary
ASFLAGS = -EB -mtune=vr4300 -march=vr4300 -mabi=32 -I include
LDFLAGS = -T $(LD_SCRIPT) -Map decompressed.map -T undefined_syms_auto.txt -T undefined_funcs_auto.txt -T undefined_syms.txt --no-check-sections
INCLUDE_CFLAGS := -I . -I ../include -I ../include/2.0D
CFLAGS := -c -G 0 -Xfullwarn -Xcpluscomm -signed -nostdinc -non_shared -Wab,-r4300_mul -D_LANGUAGE_C -D_FINALROM -DTARGET_N64 -DF3D_OLD -woff 649,838 $(INCLUDE_CFLAGS)
GCC_ASFLAGS    := -EB -mtune=vr4300 -march=vr4300 -mabi=32 -O2 -fno-align-labels -fno-align-functions -fno-align-loops -fno-align-jumps -fno-common -fno-zero-initialized-in-bss -mfp32 -c -x assembler-with-cpp -mabi=32 -ffreestanding -mtune=vr4300 -march=vr4300 -mfix4300 -G 0 -O -mno-shared -fno-PIC -mno-abicalls


ASM_DIR   = asm
SRC_DIR   = src

UNMATCHED_SRC_DIR = $(ASM_DIR)
UNMATCHED_DECOMPRESSED_S_FILES = $(shell find $(UNMATCHED_SRC_DIR) -name '*.s' -not -path '*/nonmatchings/*')
UNMATCHED_DECOMPRESSED_S_O_FILES := $(foreach file,$(UNMATCHED_DECOMPRESSED_S_FILES),$(BUILD_DIR)/$(file).o)

DECOMPRESSED_SRC_DIR   = $(SRC_DIR)
DECOMPRESSED_SRC_DIRS  = $(shell find $(DECOMPRESSED_SRC_DIR) -type d)

DECOMPRESSED_C_FILES   = $(shell find $(DECOMPRESSED_SRC_DIR) -name '*.c')
DECOMPRESSED_C_O_FILES := $(foreach file,$(DECOMPRESSED_C_FILES),$(BUILD_DIR)/$(file).o)

DECOMPRESSED_S_FILES   = $(shell find $(DECOMPRESSED_SRC_DIR) -name '*.s')
DECOMPRESSED_S_O_FILES := $(foreach file,$(DECOMPRESSED_S_FILES),$(BUILD_DIR)/$(file).o)

# Files requiring pre/post-processing
GLOBAL_ASM_DECOMPRESSED_C_FILES := $(shell $(GREP) GLOBAL_ASM $(DECOMPRESSED_SRC_DIR) </dev/null 2>/dev/null)
GLOBAL_ASM_DECOMPRESSED_C_O_FILES := $(foreach file,$(GLOBAL_ASM_DECOMPRESSED_C_FILES),$(BUILD_DIR)/$(file).o)

#### Assets
BIN_DIRS  = assets assets/hd_code assets/hd_code/os assets/hd_code/io
BIN_FILES = $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.bin))
BIN_O_FILES := $(foreach file,$(BIN_FILES),$(BUILD_DIR)/$(file).o)

MIPS3_C_O_FILES = $(BUILD_DIR)/src/hd_code/libc/ll.c.o

DECOMPRESSED_O_FILES := $(UNMATCHED_DECOMPRESSED_S_O_FILES) \
		   $(DECOMPRESSED_C_O_FILES) \
		   $(DECOMPRESSED_S_O_FILES) \
		   $(GLOBAL_ASM_DECOMPRESSED_C_O_FILES) \
		   $(BIN_O_FILES)

####################
## DEFAULT TARGET ##
####################

default: all

all: verify

################
## EXTRACTION ##
################

extract:
	splat split decompressed.$(VERSION).yaml


#################
## COMPILATION ##
#################

## OVERRIDES

build/src/hd_code/libc/ll.c.o: MIPSISET := -mips3 -o32
build/src/hd_code/gu/%.c.o: OPT_FLAGS = -O3
build/src/hd_code/audio/%.c.o: OPT_FLAGS = -O3

# *.c -> *.c.o (with GLOBAL_ASM macro)
$(GLOBAL_ASM_DECOMPRESSED_C_O_FILES): $(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(PYTHON) $(TOOLS_DIR)/asm-processor/build.py $(CC) -- $(AS) $(ASFLAGS) -- $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<

# *.c -> *.c.o (without GLOBAL_ASM macro)
$(MIPS3_C_O_FILES): $(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(CC) -32 $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<
	$(TOOLS_DIR)/set_o32abi_bit.py $@
	$(OBJCOPY) $@
	$(OBJCOPY) --strip-unneeded $@


# *.c -> *.c.o (without GLOBAL_ASM macro)
$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<

# *.s -> *.s.o
$(BUILD_DIR)/%.s.o: %.s
	@mkdir -p $(@D)
	@$(GCC) $(GCC_ASFLAGS) $(INCLUDE_CFLAGS) -o $@ $<

#  *.bin -> *.bin.o
$(BUILD_DIR)/%.bin.o: %.bin
	@mkdir -p $(@D)
	$(LD) -r -b binary -o $@ $<




# *.o -> *.elf
build/decompressed.elf: $(DECOMPRESSED_O_FILES)
	$(LD) $(LDFLAGS) -o $@

# *.elf -> *.bin
build/decompressed.bin: build/decompressed.elf
	$(OBJCOPY) $(OBJCOPYFLAGS) $< $@

verify: build/decompressed.bin
	@echo "$$(cat decompressed.$(VERSION).sha1) $<" | sha1sum --check


###########
## CLEAN ##
###########

clean:
	rm -rf asm
	rm -rf assets
	rm -rf build
	rm -f *auto.txt