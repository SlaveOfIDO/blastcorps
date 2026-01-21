BASENAME  = blastcorps
VERSION  := us.v11

ASM_DIR   = asm
ASM_DIRS  = $(shell find $(ASM_DIR)/init -type d) $(shell find $(ASM_DIR)/hd_code -type d) $(shell find $(ASM_DIR)/data -type d) # only include init and data here

TOOLS_DIR := ./tools
ASM_PROCESSOR_DIR := $(TOOLS_DIR)/asm-processor

BLASTCORP_EXTRACTED := blastcorps/init.$(VERSION).bin blastcorps/hd_code.$(VERSION).bin blastcorps/hd_front_end.$(VERSION).bin

TOOLS_DIR := tools

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
LD_SCRIPT = $(BASENAME).$(VERSION).decompressed.ld
OBJCOPYFLAGS = -O binary
ASFLAGS = -EB -mtune=vr4300 -march=vr4300 -mabi=32 -I include
LDFLAGS = -T $(LD_SCRIPT) -Map $(TARGET).map -T undefined_syms_auto.init.$(VERSION).txt -T undefined_funcs_auto.init.$(VERSION).txt -T undefined_syms.init.$(VERSION).txt --no-check-sections
INCLUDE_CFLAGS := -I . -I include -I include/2.0I -I include/2.0I/PR
CFLAGS := -G 0 -Xfullwarn -Xcpluscomm -signed -nostdinc -non_shared -Wab,-r4300_mul -D_LANGUAGE_C -D_FINALROM -woff 649,838 $(INCLUDE_CFLAGS)
GCC_ASFLAGS    := -EB -mtune=vr4300 -march=vr4300 -mabi=32 -O2 -fno-align-labels -fno-align-functions -fno-align-loops -fno-align-jumps -fno-common -fno-zero-initialized-in-bss -mfp32 -c -x assembler-with-cpp -mabi=32 -ffreestanding -mtune=vr4300 -march=vr4300 -mfix4300 -G 0 -O -mno-shared -fno-PIC -mno-abicalls

### Main

SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/$(BASENAME).$(VERSION)

### ROM
ROM_SRC_DIR = $(SRC_DIR)

ROM_C_FILES = $(shell find $(ROM_SRC_DIR) -maxdepth 1 -name '*.c')
ROM_C_O_FILES := $(foreach file,$(ROM_C_FILES),$(BUILD_DIR)/$(file).o)

ROM_S_FILES = $(shell find $(ROM_SRC_DIR) -maxdepth 1 -name '*.s' | sed 's|$(SRC_DIR)/||')
ROM_S_O_FILES := $(foreach file,$(ROM_S_FILES),$(BUILD_DIR)/asm/$(file).o)

### Unmatched
UNMATCHED_SRC_DIR = $(ASM_DIR)

UNMATCHED_S_FILES = $(shell find $(UNMATCHED_SRC_DIR) -name '*.s' -not -path '*/nonmatchings/*')
UNMATCHED_S_O_FILES := $(foreach file,$(UNMATCHED_S_FILES),$(BUILD_DIR)/$(file).o)


### Init

INIT_SRC_DIR   = $(SRC_DIR)/init
INIT_SRC_DIRS  = $(shell find $(INIT_SRC_DIR) -type d)

INIT_C_FILES   = $(shell find $(INIT_SRC_DIR) -name '*.c')
INIT_C_O_FILES := $(foreach file,$(INIT_C_FILES),$(BUILD_DIR)/$(file).o)

INIT_S_FILES   = $(shell find $(INIT_SRC_DIR) -name '*.s')
INIT_S_O_FILES := $(foreach file,$(INIT_S_FILES),$(BUILD_DIR)/$(file).o)

MIPS3_INIT_C_O_FILES = $(BUILD_DIR)/src/init/libc/ll.c.o
# Files requiring pre/post-processing
GLOBAL_ASM_INIT_C_FILES := $(shell $(GREP) GLOBAL_ASM $(INIT_SRC_DIR) </dev/null 2>/dev/null)
GLOBAL_ASM_INIT_C_O_FILES := $(foreach file,$(GLOBAL_ASM_INIT_C_FILES),$(BUILD_DIR)/$(file).o)

### HD Code


HD_CODE_SRC_DIR   = $(SRC_DIR)/hd_code
HD_CODE_SRC_DIRS  = $(shell find $(HD_CODE_SRC_DIR) -type d)

HD_CODE_C_FILES   = $(shell find $(HD_CODE_SRC_DIR) -name '*.c')
HD_CODE_C_O_FILES := $(foreach file,$(HD_CODE_C_FILES),$(BUILD_DIR)/$(file).o)

HD_CODE_S_FILES   = $(shell find $(HD_CODE_SRC_DIR) -name '*.s')
HD_CODE_S_O_FILES := $(foreach file,$(HD_CODE_S_FILES),$(BUILD_DIR)/$(file).o)

# Files requiring pre/post-processing
GLOBAL_ASM_HD_CODE_C_FILES := $(shell $(GREP) GLOBAL_ASM $(HD_CODE_SRC_DIR) </dev/null 2>/dev/null)
GLOBAL_ASM_HD_CODE_C_O_FILES := $(foreach file,$(GLOBAL_ASM_HD_CODE_C_FILES),$(BUILD_DIR)/$(file).o)


### Combined
GLOBAL_ASM_C_O_FILES := $(GLOBAL_ASM_INIT_C_O_FILES) \
                        $(GLOBAL_ASM_HD_CODE_C_O_FILES)

#### Assets
BIN_DIRS  = assets assets/init assets/hd_code
BIN_FILES = $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.bin))
BIN_O_FILES := $(foreach file,$(BIN_FILES),$(BUILD_DIR)/$(file).o)

### Aggregated
O_FILES := $(UNMATCHED_S_O_FILES) \
           $(ROM_C_O_FILES) \
		   $(ROM_S_O_FILES) \
		   $(INIT_C_O_FILES) \
		   $(INIT_S_O_FILES) \
		   $(GLOBAL_ASM_INIT_C_O_FILES) \
		   $(HD_CODE_C_O_FILES) \
		   $(HD_CODE_S_O_FILES) \
		   $(GLOBAL_ASM_HD_CODE_C_O_FILES) \
		   $(BIN_O_FILES)


### Optimisation Overrides

build/src/init/libc/ll.c.o: MIPSISET := -mips3 -o32

### Targets


default: all

all: dirs $(TARGET).z64 verify

dirs:
	$(foreach dir,$(INIT_SRC_DIRS) $(HD_CODE_SRC_DIRS) $(ASM_DIRS) $(BIN_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))

check: .baserom.$(VERSION).ok

verify: $(TARGET).z64
	echo "$$(cat $(BASENAME).$(VERSION).sha1)  $(TARGET).z64" | sha1sum --check

extract: check decompressed.$(VERSION).z64
	$(PYTHON) $(TOOLS_DIR)/splat/split.py $(BASENAME).$(VERSION).yaml

decompressed.$(VERSION).z64: baserom.$(VERSION).z64
	$(PYTHON) $(TOOLS_DIR)/decompress_rom.py baserom.$(VERSION).z64

#################
## COMPILATION ##
#################

# *.c -> *.c.o (with GLOBAL_ASM macro)
$(GLOBAL_ASM_C_O_FILES): $(BUILD_DIR)/%.c.o: %.c
	$(PYTHON) $(ASM_PROCESSOR_DIR)/asm_processor.py $(OPT_FLAGS) $< > $(BUILD_DIR)/$<
	$(CC) -c -32 $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $(BUILD_DIR)/$<
	$(PYTHON) $(ASM_PROCESSOR_DIR)/asm_processor.py $(OPT_FLAGS) $< --post-process $@ \
		--assembler "$(AS) $(ASFLAGS)" --asm-prelude $(ASM_PROCESSOR_DIR)/prelude.s

# *.c -> *.c.o (without GLOBAL_ASM macro)
$(MIPS3_INIT_C_O_FILES): $(BUILD_DIR)/%.c.o: %.c
	$(CC) -c -32 $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<
	tools/set_o32abi_bit.py $@
	$(OBJCOPY) $@
	$(OBJCOPY) --strip-unneeded $@


# *.c -> *.c.o (without GLOBAL_ASM macro)
$(BUILD_DIR)/%.c.o: %.c
	$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<

# *.s -> *.s.o
$(BUILD_DIR)/%.s.o: %.s
	$(GCC) $(GCC_ASFLAGS) $(INCLUDE_CFLAGS) -o $@ $<

#  *.bin -> *.bin.o
$(BUILD_DIR)/%.bin.o: %.bin
	$(LD) -r -b binary -o $@ $<

# *.o -> *.elf
$(TARGET).elf: $(O_FILES)
	$(LD) $(LDFLAGS) -o $@

# *.elf -> *.bin
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) $(OBJCOPYFLAGS) $< $@

# *.bin -> *.z64
$(TARGET).z64: $(TARGET).bin
	$(PYTHON) $(TOOLS_DIR)/compress_rom.py $(TARGET).bin

# SHA1 check
.baserom.$(VERSION).ok: baserom.$(VERSION).z64
	echo "$$(cat $(BASENAME).$(VERSION).sha1)  $<" | sha1sum --check
	touch $@


###########
## CLEAN ##
###########

clean:
	rm -rf asm
	rm -rf assets
	rm -rf build
	rm -f *auto.txt
	rm -rf $(BLASTCORP_EXTRACTED)

### Settings
.SECONDARY:
.PHONY: all clean default
SHELL = /bin/bash -e -o pipefail
