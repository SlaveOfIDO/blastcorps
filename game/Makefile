VERSION ?= us.v11
export VERSION

# NON_MATCHING - whether to build a matching, identical copy of game
#   1 - enable some alternate, more portable code that does not produce a matching build
#   0 - build a matching game
NON_MATCHING ?= 0

include ../tools/common.mk

LD_SCRIPT = game.$(VERSION).ld
LDFLAGS = -T $(LD_SCRIPT) -Map $(TARGET).map -T undefined_funcs_auto.$(VERSION).txt -T undefined_syms.$(VERSION).txt -T undefined_syms.hd_code.$(VERSION).txt --no-check-sections

TARGET = $(BUILD_DIR)/game.$(VERSION)

### hd_code / hd_front_end
HD_CODE_SRC_DIR   = src/hd_code
HD_CODE_SRC_DIRS  = $(shell find $(HD_CODE_SRC_DIR) -type d)
HD_CODE_C_FILES   = $(shell find $(HD_CODE_SRC_DIR) -name '*.c')
HD_CODE_C_O_FILES := $(foreach file,$(HD_CODE_C_FILES),$(BUILD_DIR)/$(file).o)
HD_CODE_S_FILES   = $(shell find $(HD_CODE_SRC_DIR) -name '*.s')
HD_CODE_S_O_FILES := $(foreach file,$(HD_CODE_S_FILES),$(BUILD_DIR)/$(file).o)

HD_FRONT_END_SRC_DIR   = src/hd_front_end
HD_FRONT_END_SRC_DIRS  = $(shell find $(HD_FRONT_END_SRC_DIR) -type d)
HD_FRONT_END_C_FILES   = $(shell find $(HD_FRONT_END_SRC_DIR) -name '*.c')
HD_FRONT_END_C_O_FILES := $(foreach file,$(HD_FRONT_END_C_FILES),$(BUILD_DIR)/$(file).o)
HD_FRONT_END_S_FILES   = $(shell find $(HD_FRONT_END_SRC_DIR) -name '*.s')
HD_FRONT_END_S_O_FILES := $(foreach file,$(HD_FRONT_END_S_FILES),$(BUILD_DIR)/$(file).o)

MIPS3_C_O_FILES = $(BUILD_DIR)/src/hd_code/libc/ll.c.o \
                   $(BUILD_DIR)/src/hd_code/libc/llcvt.c.o

GLOBAL_ASM_HD_CODE_C_FILES := $(shell $(GREP) GLOBAL_ASM $(HD_CODE_SRC_DIR) </dev/null 2>/dev/null)
GLOBAL_ASM_HD_CODE_C_O_FILES := $(foreach file,$(GLOBAL_ASM_HD_CODE_C_FILES),$(BUILD_DIR)/$(file).o)

GLOBAL_ASM_HD_FRONT_END_C_FILES := $(shell $(GREP) GLOBAL_ASM $(HD_FRONT_END_SRC_DIR) </dev/null 2>/dev/null)
GLOBAL_ASM_HD_FRONT_END_C_O_FILES := $(foreach file,$(GLOBAL_ASM_HD_FRONT_END_C_FILES),$(BUILD_DIR)/$(file).o)

GLOBAL_ASM_C_O_FILES := $(GLOBAL_ASM_HD_CODE_C_O_FILES) $(GLOBAL_ASM_HD_FRONT_END_C_O_FILES)

### Unmatched
ASM_DIR = asm
ASM_DIRS = $(shell find $(ASM_DIR) -type d)
UNMATCHED_S_FILES = $(shell find $(ASM_DIR) -name '*.s' -not -path '*/nonmatchings/*')
UNMATCHED_S_O_FILES := $(foreach file,$(UNMATCHED_S_FILES),$(BUILD_DIR)/$(file).o)

#### Assets
BIN_DIRS  = assets assets/hd_code assets/hd_code/os assets/hd_code/io assets/hd_front_end
BIN_FILES = $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.bin))
BIN_O_FILES := $(foreach file,$(BIN_FILES),$(BUILD_DIR)/$(file).o)

### Aggregated
O_FILES := $(UNMATCHED_S_O_FILES) \
           $(HD_CODE_C_O_FILES) \
           $(HD_CODE_S_O_FILES) \
           $(HD_FRONT_END_C_O_FILES) \
           $(HD_FRONT_END_S_O_FILES) \
           $(BIN_O_FILES)

### Optimisation Overrides
build/src/hd_code/libc/ll.c.o: MIPSISET := -mips3 -o32
build/src/hd_code/libc/llcvt.c.o: MIPSISET := -mips3 -o32
build/src/hd_code/libc/string.c.o: OPT_FLAGS = -O2
build/src/hd_code/libc/ldiv.c.o: OPT_FLAGS = -O2
build/src/hd_code/gu/%.c.o: OPT_FLAGS = -O3
build/src/hd_code/audio/%.c.o: OPT_FLAGS = -O3

### Targets

default: $(TARGET).bin

extract:
	splat split game.$(VERSION).yaml

dirs:
	$(foreach dir,$(HD_CODE_SRC_DIRS) $(HD_FRONT_END_SRC_DIRS) $(ASM_DIRS) $(BIN_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))

# game/build/game.<version>.elf -> ../rzip_reloc_auto.init.<version>.txt
reloc: $(TARGET).elf
	VERSION=$(VERSION) $(PYTHON) $(TOOLS_DIR)/compute_rzip_reloc.py

# game/build/game.<version>.bin + ../rzip_reloc_auto.init.<version>.txt -> game/build/game.<version>.compressed.bin
compress: $(TARGET).bin
	VERSION=$(VERSION) $(PYTHON) $(TOOLS_DIR)/compress_game.py

#################
## COMPILATION ##
#################

# *.c -> *.c.o (without GLOBAL_ASM macro, catch-all)
$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<

# *.s -> *.s.o
$(BUILD_DIR)/src/hd_code/%.s.o: src/hd_code/%.s
	@mkdir -p $(@D)
	@$(GCC) $(GCC_ASFLAGS) $(INCLUDE_CFLAGS) -o $@ $<

$(BUILD_DIR)/src/hd_front_end/%.s.o: src/hd_front_end/%.s
	@mkdir -p $(@D)
	@$(GCC) $(GCC_ASFLAGS) $(INCLUDE_CFLAGS) -o $@ $<

# *.c -> *.c.o (with GLOBAL_ASM macro)
$(GLOBAL_ASM_C_O_FILES): $(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(PYTHON) $(TOOLS_DIR)/asm-processor/build.py $(CC) -- $(AS) $(ASFLAGS) -- -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<

# *.c -> *.c.o (without GLOBAL_ASM macro, mips3)
$(MIPS3_C_O_FILES): $(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(CC) -c -32 $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<
	$(TOOLS_DIR)/set_o32abi_bit.py $@
	$(OBJCOPY) $@
	$(OBJCOPY) --strip-unneeded $@

# hd_code/hd_front_end's non-matching-functions asm (asm/hd_code, asm/hd_front_end, asm/data)
$(BUILD_DIR)/asm/hd_code/%.s.o: asm/hd_code/%.s
	@mkdir -p $(@D)
	@$(GCC) $(GCC_ASFLAGS) $(INCLUDE_CFLAGS) -o $@ $<

$(BUILD_DIR)/asm/hd_front_end/%.s.o: asm/hd_front_end/%.s
	@mkdir -p $(@D)
	@$(GCC) $(GCC_ASFLAGS) $(INCLUDE_CFLAGS) -o $@ $<

$(BUILD_DIR)/asm/data/hd_code/%.s.o: asm/data/hd_code/%.s
	@mkdir -p $(@D)
	@$(GCC) $(GCC_ASFLAGS) $(INCLUDE_CFLAGS) -o $@ $<

$(BUILD_DIR)/asm/data/hd_front_end/%.s.o: asm/data/hd_front_end/%.s
	@mkdir -p $(@D)
	@$(GCC) $(GCC_ASFLAGS) $(INCLUDE_CFLAGS) -o $@ $<

#  *.bin -> *.bin.o
$(BUILD_DIR)/%.bin.o: %.bin
	@mkdir -p $(@D)
	$(LD) -r -b binary -o $@ $<

# *.o -> game.elf
# LD_SCRIPT is an explicit prerequisite (not just referenced inside
# LDFLAGS) because tools/patch_game_rom_base.py rewrites it in place
# before every real link, and that rewrite needs to trigger a relink.
$(TARGET).elf: $(O_FILES) $(LD_SCRIPT)
	$(LD) $(LDFLAGS) -o $@

# game.elf -> game.bin
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) $(OBJCOPYFLAGS) $< $@

###########
## CLEAN ##
###########

clean:
	rm -rf asm
	rm -rf assets
	rm -rf build

### Settings
.SECONDARY:
.PHONY: default extract dirs reloc compress clean
SHELL = /bin/bash -e -o pipefail
