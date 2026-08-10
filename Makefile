VERSION  ?= us.v11
export VERSION

# NON_MATCHING - whether to build a matching, identical copy of the ROM
#   1 - enable some alternate, more portable code that does not produce a matching ROM
#   0 - build a matching ROM
NON_MATCHING ?= 0
$(eval $(call validate-option,NON_MATCHING,0 1))

ASM_DIR   = asm
ASM_DIRS  = $(shell find $(ASM_DIR)/init -type d) $(shell find $(ASM_DIR)/hd_code -type d) $(shell find $(ASM_DIR)/data -type d) # only include init and data here

TOOLS_DIR := tools
ASM_PROCESSOR_DIR := $(TOOLS_DIR)/asm-processor

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
LD_SCRIPT = blastcorps.$(VERSION).decompressed.ld
OBJCOPYFLAGS = -O binary
ASFLAGS = -EB -mtune=vr4300 -march=vr4300 -mabi=32 -I include
RZIP_RELOC_FILE = rzip_reloc_auto.init.$(VERSION).txt
LDFLAGS = -T $(LD_SCRIPT) -Map $(TARGET).map -T undefined_syms_auto.init.$(VERSION).txt -T undefined_funcs_auto.init.$(VERSION).txt -T undefined_syms.init.$(VERSION).txt -T decompressed/exported_symbols.auto.txt -T $(RZIP_RELOC_FILE) --no-check-sections
INCLUDE_CFLAGS := -I . -I include -I include/2.0D -I include/2.0D/PR
CFLAGS := -G 0 -Xfullwarn -Xcpluscomm -signed -nostdinc -non_shared -Wab,-r4300_mul -D_LANGUAGE_C -D_FINALROM -DNON_MATCHING=$(NON_MATCHING) -DDEBUG=0 -woff 649,838 $(INCLUDE_CFLAGS)
GCC_ASFLAGS    := -EB -x assembler-with-cpp -march=vr4300 -mabi=32 -O2 -G 0 -w -nostdinc -c   -mfix4300 -mno-abicalls -DMIPSEB -D_LANGUAGE_ASSEMBLY -D_MIPS_SIM=1 -D_MIPS_SZLONG=32

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
		   $(BIN_O_FILES)


### Optimisation Overrides

build/src/init/libc/ll.c.o: MIPSISET := -mips3 -o32

### Targets


default: all

ifeq ($(NON_MATCHING),1)
all: dirs $(TARGET).z64
else
all: dirs $(TARGET).z64 verify
endif

dirs:
	$(foreach dir,$(INIT_SRC_DIRS) $(ASM_DIRS) $(BIN_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))

check: .baserom.$(VERSION).ok

verify: $(TARGET).z64
	echo "$$(cat blastcorps.$(VERSION).sha1)  $(TARGET).z64" | sha1sum --check

extract: check decompressed.$(VERSION).z64
	splat split blastcorps.$(VERSION).yaml
	VERSION=$(VERSION) $(PYTHON) $(TOOLS_DIR)/pad_init_segment.py

	cp assets/decompressed.$(VERSION).bin decompressed/decompressed.$(VERSION).bin

decompressed.$(VERSION).z64: baserom.$(VERSION).z64
	VERSION=$(VERSION) $(PYTHON) $(TOOLS_DIR)/decompress_rom.py

#################
## COMPILATION ##
#################

# *.c -> *.c.o (with GLOBAL_ASM macro)
$(GLOBAL_ASM_C_O_FILES): $(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(PYTHON) $(TOOLS_DIR)/asm-processor/build.py $(CC) -- $(AS) $(ASFLAGS) -- -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<

# 1A30.c.o (without asm processor)
ifeq ($(NON_MATCHING),1)
$(BUILD_DIR)/src/init/1A30.c.o: src/init/1A30.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<
endif

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
	@mkdir -p $(@D)
	$(GCC) $(GCC_ASFLAGS) $(INCLUDE_CFLAGS) -o $@ $<

#  *.bin -> *.bin.o
$(BUILD_DIR)/%.bin.o: %.bin
	$(LD) -r -b binary -o $@ $<

#  assets/decompressed.us.v11.bin -> assets/decompressed.us.v11.bin.o
$(BUILD_DIR)/assets/decompressed.$(VERSION).bin.o: decompressed/build/decompressed.bin
	echo "Copying decompressed binary"
	cp decompressed/build/decompressed.bin assets/decompressed.$(VERSION).bin
	$(LD) -r -b binary -o $@ $<

# computed ahead of linking (from the already-built decompressed overlay
# content) so the linker sees this build's addresses, not a stale previous
# build's. .PHONY (always reruns) rather than tracked via the file's mtime:
# make has a sharp edge where a missing prerequisite of an *already-existing*
# target is silently treated as "up to date" once that target exists on
# disk, which would make the addresses go stale again after the first build.
.PHONY: $(RZIP_RELOC_FILE)
$(RZIP_RELOC_FILE): decompressed/build/decompressed.bin
	VERSION=$(VERSION) $(PYTHON) $(TOOLS_DIR)/compute_rzip_reloc.py

# *.o -> *.elf
$(TARGET).elf: $(O_FILES) $(RZIP_RELOC_FILE)
	$(LD) $(LDFLAGS) -o $@

# *.elf -> *.bin
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) $(OBJCOPYFLAGS) $< $@

# *.bin -> *.z64
$(TARGET).z64: $(TARGET).bin $(RZIP_RELOC_FILE)
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
	rm -f *auto.txt
	rm -f decompressed/decompressed.bin

##########
## FULL ##
##########
full-decompressed:
	make -C decompressed clean
	make -C decompressed extract
	make -C decompressed
full:
	make clean
	make extract
	make full-decompressed
	make


### Settings
.SECONDARY:
.PHONY: all clean default
SHELL = /bin/bash -e -o pipefail
