VERSION  ?= us.v11
export VERSION

# NON_MATCHING - whether to build a matching, identical copy of the ROM
#   1 - enable some alternate, more portable code that does not produce a matching ROM
#   0 - build a matching ROM
NON_MATCHING ?= 0
$(eval $(call validate-option,NON_MATCHING,0 1))

ASM_DIR   = asm
ASM_DIRS  = $(shell find $(ASM_DIR)/hd_code -type d) \
            $(shell find $(ASM_DIR)/hd_front_end -type d) \
            $(shell find $(ASM_DIR)/data -type d)

TOOLS_DIR := tools
ASM_PROCESSOR_DIR := $(TOOLS_DIR)/asm-processor

RZIP_RELOC_FILE = rzip_reloc_auto.init.$(VERSION).txt

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
INIT_LD_SCRIPT = init.$(VERSION).ld
LD_SCRIPT = blastcorps.$(VERSION).decompressed.ld
OBJCOPYFLAGS = -O binary
ASFLAGS = -EB -mtune=vr4300 -march=vr4300 -mabi=32 -I include
INIT_LDFLAGS = -T $(INIT_LD_SCRIPT) -Map $(BUILD_DIR)/init.map -T undefined_syms_auto.init.$(VERSION).txt -T undefined_funcs_auto.init.$(VERSION).txt -T undefined_syms.init.$(VERSION).txt -T $(RZIP_RELOC_FILE) --no-check-sections
LDFLAGS = -T $(LD_SCRIPT) -Map $(TARGET).map -T undefined_funcs_auto.$(VERSION).txt -T undefined_syms.$(VERSION).txt -T undefined_syms.hd_code.$(VERSION).txt --no-check-sections
INCLUDE_CFLAGS := -I . -I include -I include/2.0D -I include/2.0D/PR
CFLAGS := -G 0 -Xfullwarn -Xcpluscomm -nostdinc -non_shared -Wab,-r4300_mul -D_LANGUAGE_C -D_FINALROM -DNON_MATCHING=$(NON_MATCHING) -DDEBUG=0 -DTARGET_N64 -DNDEBUG -DF3D_OLD -woff 649,838 $(INCLUDE_CFLAGS)
GCC_ASFLAGS    := -EB -x assembler-with-cpp -march=vr4300 -mabi=32 -O2 -G 0 -w -nostdinc -c   -mfix4300 -mno-abicalls -DMIPSEB -D_LANGUAGE_ASSEMBLY -D_MIPS_SIM=1 -D_MIPS_SZLONG=32 -mtune=vr4300 -fno-align-labels -fno-align-functions -fno-align-loops -fno-align-jumps -fno-common -fno-zero-initialized-in-bss -mfp32 -ffreestanding -O -mno-shared -fno-PIC

### Main
SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/blastcorps.$(VERSION)

### ROM
ROM_SRC_DIR = $(SRC_DIR)

ROM_C_FILES = $(shell find $(ROM_SRC_DIR) -maxdepth 1 -name '*.c')
ROM_C_O_FILES := $(foreach file,$(ROM_C_FILES),$(BUILD_DIR)/$(file).o)

ROM_S_FILES = $(shell find $(ROM_SRC_DIR) -maxdepth 1 -name '*.s' | sed 's|$(SRC_DIR)/||')
ROM_S_O_FILES := $(foreach file,$(ROM_S_FILES),$(BUILD_DIR)/asm/$(file).o)

### Unmatched
UNMATCHED_SRC_DIR = $(ASM_DIR)

# excludes $(ASM_DIR)/init: .init isn't part of the main ROM link (see the
# "init" section below) - its unmatched asm must only feed init's own
# link, not this pool.
UNMATCHED_S_FILES = $(shell find $(UNMATCHED_SRC_DIR) -name '*.s' -not -path '*/nonmatchings/*' -not -path '$(ASM_DIR)/init/*')
UNMATCHED_S_O_FILES := $(foreach file,$(UNMATCHED_S_FILES),$(BUILD_DIR)/$(file).o)

### init
# init needs to be compiled as a seperate component because it is replaced when loading the main game's code
INIT_SRC_DIR   = $(SRC_DIR)/init
INIT_SRC_DIRS  = $(shell find $(INIT_SRC_DIR) -type d)
INIT_C_FILES   = $(shell find $(INIT_SRC_DIR) -name '*.c')
INIT_C_O_FILES := $(foreach file,$(INIT_C_FILES),$(BUILD_DIR)/$(file).o)
INIT_S_FILES   = $(shell find $(INIT_SRC_DIR) -name '*.s')
INIT_S_O_FILES := $(foreach file,$(INIT_S_FILES),$(BUILD_DIR)/$(file).o)

INIT_ASM_DIR = $(ASM_DIR)/init
INIT_ASM_DIRS = $(shell find $(INIT_ASM_DIR) -type d)
INIT_UNMATCHED_S_FILES = $(shell find $(INIT_ASM_DIR) -name '*.s' -not -path '*/nonmatchings/*')
INIT_UNMATCHED_S_O_FILES := $(foreach file,$(INIT_UNMATCHED_S_FILES),$(BUILD_DIR)/$(file).o)

MIPS3_INIT_C_O_FILES = $(BUILD_DIR)/src/init/libc/ll.c.o
GLOBAL_ASM_INIT_C_FILES := $(shell $(GREP) GLOBAL_ASM $(INIT_SRC_DIR) </dev/null 2>/dev/null)
GLOBAL_ASM_INIT_C_O_FILES := $(foreach file,$(GLOBAL_ASM_INIT_C_FILES),$(BUILD_DIR)/$(file).o)

INIT_O_FILES := $(INIT_UNMATCHED_S_O_FILES) \
                 $(INIT_C_O_FILES) \
                 $(INIT_S_O_FILES) \
                 $(GLOBAL_ASM_INIT_C_O_FILES)

### hd_code / hd_front_end
HD_CODE_SRC_DIR   = $(SRC_DIR)/hd_code
HD_CODE_SRC_DIRS  = $(shell find $(HD_CODE_SRC_DIR) -type d)
HD_CODE_C_FILES   = $(shell find $(HD_CODE_SRC_DIR) -name '*.c')
HD_CODE_C_O_FILES := $(foreach file,$(HD_CODE_C_FILES),$(BUILD_DIR)/$(file).o)
HD_CODE_S_FILES   = $(shell find $(HD_CODE_SRC_DIR) -name '*.s')
HD_CODE_S_O_FILES := $(foreach file,$(HD_CODE_S_FILES),$(BUILD_DIR)/$(file).o)

HD_FRONT_END_SRC_DIR   = $(SRC_DIR)/hd_front_end
HD_FRONT_END_SRC_DIRS  = $(shell find $(HD_FRONT_END_SRC_DIR) -type d)
HD_FRONT_END_C_FILES   = $(shell find $(HD_FRONT_END_SRC_DIR) -name '*.c')
HD_FRONT_END_C_O_FILES := $(foreach file,$(HD_FRONT_END_C_FILES),$(BUILD_DIR)/$(file).o)
HD_FRONT_END_S_FILES   = $(shell find $(HD_FRONT_END_SRC_DIR) -name '*.s')
HD_FRONT_END_S_O_FILES := $(foreach file,$(HD_FRONT_END_S_FILES),$(BUILD_DIR)/$(file).o)

MIPS3_HD_C_O_FILES = $(BUILD_DIR)/src/hd_code/libc/ll.c.o \
                     $(BUILD_DIR)/src/hd_code/libc/llcvt.c.o

GLOBAL_ASM_HD_CODE_C_FILES := $(shell $(GREP) GLOBAL_ASM $(HD_CODE_SRC_DIR) </dev/null 2>/dev/null)
GLOBAL_ASM_HD_CODE_C_O_FILES := $(foreach file,$(GLOBAL_ASM_HD_CODE_C_FILES),$(BUILD_DIR)/$(file).o)

GLOBAL_ASM_HD_FRONT_END_C_FILES := $(shell $(GREP) GLOBAL_ASM $(HD_FRONT_END_SRC_DIR) </dev/null 2>/dev/null)
GLOBAL_ASM_HD_FRONT_END_C_O_FILES := $(foreach file,$(GLOBAL_ASM_HD_FRONT_END_C_FILES),$(BUILD_DIR)/$(file).o)

GLOBAL_ASM_HD_C_O_FILES := $(GLOBAL_ASM_HD_CODE_C_O_FILES) $(GLOBAL_ASM_HD_FRONT_END_C_O_FILES)

#### Assets
BIN_DIRS  = assets assets/hd_code assets/hd_code/os assets/hd_code/io assets/hd_front_end
BIN_FILES = $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.bin))
BIN_O_FILES := $(foreach file,$(BIN_FILES),$(BUILD_DIR)/$(file).o)

### Aggregated
O_FILES := $(UNMATCHED_S_O_FILES) \
           $(ROM_C_O_FILES) \
		   $(ROM_S_O_FILES) \
		   $(HD_CODE_C_O_FILES) \
		   $(HD_CODE_S_O_FILES) \
		   $(HD_FRONT_END_C_O_FILES) \
		   $(HD_FRONT_END_S_O_FILES) \
		   $(BIN_O_FILES)


### Optimisation Overrides
build/src/init/libc/ll.c.o: MIPSISET := -mips3 -o32
build/src/hd_code/libc/ll.c.o: MIPSISET := -mips3 -o32
build/src/hd_code/libc/llcvt.c.o: MIPSISET := -mips3 -o32
build/src/hd_code/libc/string.c.o: OPT_FLAGS = -O2
build/src/hd_code/libc/ldiv.c.o: OPT_FLAGS = -O2
build/src/hd_code/gu/%.c.o: OPT_FLAGS = -O3
build/src/hd_code/audio/%.c.o: OPT_FLAGS = -O3

### Targets

default: all

ifeq ($(NON_MATCHING),1)
all: dirs $(TARGET).z64
else
all: dirs $(TARGET).z64 verify
endif

dirs:
	$(foreach dir,$(INIT_SRC_DIRS) $(INIT_ASM_DIRS) $(HD_CODE_SRC_DIRS) $(HD_FRONT_END_SRC_DIRS) $(ASM_DIRS) $(BIN_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))

check: .baserom.$(VERSION).ok

verify: $(TARGET).z64
	echo "$$(cat blastcorps.$(VERSION).sha1)  $(TARGET).z64" | sha1sum --check

extract: check decompressed.$(VERSION).z64
	splat split blastcorps.$(VERSION).yaml
	splat split init.$(VERSION).yaml

decompressed.$(VERSION).z64: baserom.$(VERSION).z64
	VERSION=$(VERSION) $(PYTHON) $(TOOLS_DIR)/decompress_rom.py

#################
## COMPILATION ##
#################

# *.c -> *.c.o (without GLOBAL_ASM macro)
$(BUILD_DIR)/%.c.o: %.c
	$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<

# *.s -> *.s.o
$(BUILD_DIR)/%.s.o: %.s
	@mkdir -p $(@D)
	$(GCC) $(GCC_ASFLAGS) $(INCLUDE_CFLAGS) -o $@ $<

# *.c -> *.c.o (with GLOBAL_ASM macro)
$(GLOBAL_ASM_INIT_C_O_FILES): $(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(PYTHON) $(TOOLS_DIR)/asm-processor/build.py $(CC) -- $(AS) $(ASFLAGS) -- -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<

# 1A30.c.o (without asm processor)
ifeq ($(NON_MATCHING),1)
$(BUILD_DIR)/src/init/1A30.c.o: src/init/1A30.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<
endif

# *.c -> *.c.o (without GLOBAL_ASM macro, mips3)
$(MIPS3_INIT_C_O_FILES): $(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(CC) -c -32 $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<
	$(TOOLS_DIR)/set_o32abi_bit.py $@
	$(OBJCOPY) $@
	$(OBJCOPY) --strip-unneeded $@

# *.c -> *.c.o (with GLOBAL_ASM macro)
$(GLOBAL_ASM_HD_C_O_FILES): $(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(PYTHON) $(TOOLS_DIR)/asm-processor/build.py $(CC) -- $(AS) $(ASFLAGS) -- -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<

# *.c -> *.c.o (without GLOBAL_ASM macro, mips3)
$(MIPS3_HD_C_O_FILES): $(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(CC) -c -32 $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<
	$(TOOLS_DIR)/set_o32abi_bit.py $@
	$(OBJCOPY) $@
	$(OBJCOPY) --strip-unneeded $@

# *.c -> *.c.o (catch-all)
$(BUILD_DIR)/src/hd_code/%.c.o: src/hd_code/%.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<

$(BUILD_DIR)/src/hd_front_end/%.c.o: src/hd_front_end/%.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<

# *.s -> *.s.o
$(BUILD_DIR)/src/hd_code/%.s.o: src/hd_code/%.s
	@mkdir -p $(@D)
	@$(GCC) $(GCC_ASFLAGS) $(INCLUDE_CFLAGS) -o $@ $<

$(BUILD_DIR)/src/hd_front_end/%.s.o: src/hd_front_end/%.s
	@mkdir -p $(@D)
	@$(GCC) $(GCC_ASFLAGS) $(INCLUDE_CFLAGS) -o $@ $<

# hd_code/hd_front_end's non-matching-functions asm (asm/hd_code, asm/data)
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
	$(LD) -r -b binary -o $@ $<

#  assets/init.bin -> assets/init.bin.o
$(BUILD_DIR)/assets/init.bin.o: $(BUILD_DIR)/init.bin
	echo "Copying init binary"
	cp $(BUILD_DIR)/init.bin assets/init.bin
	$(LD) -r -b binary -o $@ $<

# Preliminary hd_code/hd_front_end-only link: needed so init's own link
# (below) can -T in real, freshly-computed rzip_reloc values instead of
# hardcoding them (src/1A30.c's NON_MATCHING=1 path references the
# compressed overlay's ROM position directly). Reuses the SAME hd_code/
# hd_front_end .o files that go into the real ROM link - nothing is
# compiled twice. The linker script is sliced straight out of the real,
# already-generated $(LD_SCRIPT) (see tools/gen_hd_code_prelim_ld.py) rather
# than maintained separately, so there's exactly one place hd_code/
# hd_front_end's structure is declared.
$(BUILD_DIR)/hd_code_prelim.ld: $(LD_SCRIPT)
	$(PYTHON) $(TOOLS_DIR)/gen_hd_code_prelim_ld.py $< $@

HD_PRELIM_LDFLAGS = -T $(BUILD_DIR)/hd_code_prelim.ld -Map $(BUILD_DIR)/hd_code_prelim.map -T undefined_syms_auto.$(VERSION).txt -T undefined_funcs_auto.$(VERSION).txt -T undefined_syms.hd_code.$(VERSION).txt --no-check-sections

$(BUILD_DIR)/hd_code_prelim.elf: $(HD_CODE_C_O_FILES) $(HD_CODE_S_O_FILES) $(HD_FRONT_END_C_O_FILES) $(HD_FRONT_END_S_O_FILES) $(UNMATCHED_S_O_FILES) $(BUILD_DIR)/hd_code_prelim.ld
	$(LD) $(HD_PRELIM_LDFLAGS) -o $@

$(BUILD_DIR)/hd_code_prelim.bin: $(BUILD_DIR)/hd_code_prelim.elf
	$(OBJCOPY) $(OBJCOPYFLAGS) $< $@

# computed ahead of linking init (from the preliminary hd_code/hd_front_end
# layout above) so the linker sees this build's addresses, not a stale
# previous build's. .PHONY (always reruns) rather than tracked via the
# file's mtime: make has a sharp edge where a missing prerequisite of an
# *already-existing* target is silently treated as "up to date" once that
# target exists on disk, which would make the addresses go stale again
# after the first build.
.PHONY: $(RZIP_RELOC_FILE)
$(RZIP_RELOC_FILE): $(BUILD_DIR)/hd_code_prelim.bin
	VERSION=$(VERSION) $(PYTHON) $(TOOLS_DIR)/compute_rzip_reloc.py

# init/*.o -> init.elf
$(BUILD_DIR)/init.elf: $(INIT_O_FILES) $(RZIP_RELOC_FILE)
	$(LD) $(INIT_LDFLAGS) -o $@

# init.bin -> init.elf
$(BUILD_DIR)/init.bin: $(BUILD_DIR)/init.elf
	$(OBJCOPY) $(OBJCOPYFLAGS) $< $@
ifeq ($(NON_MATCHING),0)
	echo "$$(cat init.$(VERSION).sha1) $@" | sha1sum --check
endif

# *.o -> *.elf
$(TARGET).elf: $(O_FILES)
	$(LD) $(LDFLAGS) -o $@

# *.elf -> *.bin
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) $(OBJCOPYFLAGS) $< $@

# *.bin -> *.z64
#
# hd_code's real ROM position depends on this build's own compiled size of
# everything before it in the ROM (init, mainly) - not knowable until after
# a real link of $(TARGET).elf above. So that first link is only a "probe":
# purely so compute_rzip_reloc.py (run again, from scratch, by this
# recursive $(MAKE)) can read its own linker-computed position for the
# hd_code placeholder back out of it and regenerate rzip_reloc_auto with
# the real value instead of rzip.config.json's original-ROM guess. Nothing
# downstream of the probe link depends on these symbols' *values* (only
# their existence), so sizes - and therefore the corrected position - can't
# change again on this second pass, and it converges in exactly one
# recursion. See compute_rzip_reloc.py's readTrueStartAddress.
$(TARGET).z64: $(TARGET).bin
	$(MAKE) VERSION=$(VERSION) NON_MATCHING=$(NON_MATCHING) $(TARGET).bin
	VERSION=$(VERSION) $(PYTHON) $(TOOLS_DIR)/compress_rom.py
ifeq ($(NON_MATCHING),1)
	$(PYTHON) $(TOOLS_DIR)/fix_checksum.py $@
endif

# SHA1 check
.baserom.$(VERSION).ok: baserom.$(VERSION).z64
	echo "$$(cat blastcorps.$(VERSION).sha1)  $<" | sha1sum --check
	touch $@

############
## REPORT ##
############

report:
	$(PYTHON) $(TOOLS_DIR)/generate_objdiff.py
	objdiff-cli report generate -o report.json --format json-pretty

progress: report
	$(PYTHON) $(TOOLS_DIR)/progress.py

###########
## CLEAN ##
###########

clean:
	rm -rf asm
	rm -rf assets
	rm -rf build
	rm -f *auto*.txt

##########
## FULL ##
##########
full:
	make clean
	make extract
	make

### Settings
.SECONDARY:
.PHONY: all clean default
SHELL = /bin/bash -e -o pipefail
