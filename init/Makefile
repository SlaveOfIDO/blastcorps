VERSION ?= us.v11
export VERSION

# NON_MATCHING - whether to build a matching, identical copy of init
#   1 - enable some alternate, more portable code that does not produce a matching build
#   0 - build a matching init
NON_MATCHING ?= 0

# C files that can be built with gcc
MODERN_BUILD_C_FILES := src/init/1A30.c \
                        src/init/rarezip.c \
                        src/init/inflate.c

include ../tools/common.mk

RZIP_RELOC_FILE ?= ../rzip_reloc_auto.init.$(VERSION).txt
INIT_LD_SCRIPT = init.$(VERSION).ld
INIT_LDFLAGS = -T $(INIT_LD_SCRIPT) -Map $(BUILD_DIR)/init.map -T undefined_syms_auto.init.$(VERSION).txt -T undefined_funcs_auto.init.$(VERSION).txt -T undefined_syms.init.$(VERSION).txt -T $(RZIP_RELOC_FILE) --no-check-sections

TARGET = $(BUILD_DIR)/init.$(VERSION)

SRC_DIR = src/init
SRC_DIRS = $(shell find $(SRC_DIR) -type d)
C_FILES = $(shell find $(SRC_DIR) -name '*.c')
C_O_FILES := $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file).o)
S_FILES = $(shell find $(SRC_DIR) -name '*.s')
S_O_FILES := $(foreach file,$(S_FILES),$(BUILD_DIR)/$(file).o)

# covers both asm/init (code) and asm/data/init (non-matching .data/.rodata
# for init/*, e.g. asm/data/init/os/exceptasm.data.s)
ASM_DIR = asm
ASM_DIRS = $(shell find $(ASM_DIR) -type d)
UNMATCHED_S_FILES = $(shell find $(ASM_DIR) -name '*.s' -not -path '*/nonmatchings/*')
UNMATCHED_S_O_FILES := $(foreach file,$(UNMATCHED_S_FILES),$(BUILD_DIR)/$(file).o)

MODERN_BUILD_C_O_FILES := $(foreach file,$(MODERN_BUILD_C_FILES),$(BUILD_DIR)/$(file).o)

MIPS3_C_O_FILES = $(BUILD_DIR)/src/init/libc/ll.c.o
GLOBAL_ASM_C_FILES := $(shell $(GREP) GLOBAL_ASM $(SRC_DIR) </dev/null 2>/dev/null)
GLOBAL_ASM_C_O_FILES := $(foreach file,$(GLOBAL_ASM_C_FILES),$(BUILD_DIR)/$(file).o)

O_FILES := $(UNMATCHED_S_O_FILES) \
           $(C_O_FILES) \
           $(S_O_FILES) \
           $(GLOBAL_ASM_C_O_FILES)

### Optimisation Overrides
build/src/init/libc/ll.c.o: MIPSISET := -mips3 -o32

### Targets

default: $(TARGET).bin
ifeq ($(NON_MATCHING),0)
	echo "$$(cat init.$(VERSION).sha1) $(TARGET).bin" | sha1sum --check
endif

extract:
	splat split init.$(VERSION).yaml

dirs:
	$(foreach dir,$(SRC_DIRS) $(ASM_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))

#################
## COMPILATION ##
#################

# *.c -> *.c.o (without GLOBAL_ASM macro)
$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<

# *.s -> *.s.o
$(BUILD_DIR)/%.s.o: %.s
	@mkdir -p $(@D)
	$(GCC) $(GCC_ASFLAGS) $(INCLUDE_CFLAGS) -o $@ $<

# *.c -> *.c.o (with GLOBAL_ASM macro)
$(GLOBAL_ASM_C_O_FILES): $(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(PYTHON) $(TOOLS_DIR)/asm-processor/build.py $(CC) -- $(AS) $(ASFLAGS) -- -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<

ifeq ($(NON_MATCHING),1)
$(MODERN_BUILD_C_O_FILES): $(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(GCC) -c $(GCC_CFLAGS) -o $@ $<
endif

# *.c -> *.c.o (without GLOBAL_ASM macro, mips3)
$(MIPS3_C_O_FILES): $(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(CC) -c -32 $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<
	$(TOOLS_DIR)/set_o32abi_bit.py $@
	$(OBJCOPY) $@
	$(OBJCOPY) --strip-unneeded $@

# init/*.o -> init.elf
$(TARGET).elf: $(O_FILES) $(RZIP_RELOC_FILE)
	$(LD) $(INIT_LDFLAGS) -o $@

# init.elf -> init.bin
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) $(OBJCOPYFLAGS) $< $@

###########
## CLEAN ##
###########

clean:
	rm -rf asm
	rm -rf build

### Settings
.SECONDARY:
.PHONY: default extract dirs clean
SHELL = /bin/bash -e -o pipefail
