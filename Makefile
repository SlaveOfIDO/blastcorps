VERSION  := us.v11

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
LDFLAGS = -T $(LD_SCRIPT) -Map $(TARGET).map -T undefined_syms_auto.init.$(VERSION).txt -T undefined_funcs_auto.init.$(VERSION).txt -T undefined_syms.init.$(VERSION).txt --no-check-sections
INCLUDE_CFLAGS := -I . -I include -I include/2.0D -I include/2.0D/PR
CFLAGS := -G 0 -Xfullwarn -Xcpluscomm -signed -nostdinc -non_shared -Wab,-r4300_mul -D_LANGUAGE_C -D_FINALROM -woff 649,838 $(INCLUDE_CFLAGS)
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

all: dirs $(TARGET).z64 verify

dirs:
	$(foreach dir,$(INIT_SRC_DIRS) $(ASM_DIRS) $(BIN_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))

check: .baserom.$(VERSION).ok

verify: $(TARGET).z64
	echo "$$(cat blastcorps.$(VERSION).sha1)  $(TARGET).z64" | sha1sum --check

extract: check decompressed.$(VERSION).z64
	splat split blastcorps.$(VERSION).yaml
	cp assets/hd_code.$(VERSION).bin hd_code/hd_code.bin
	cp assets/hd_front_end.$(VERSION).bin hd_front_end/hd_front_end.bin

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
	@mkdir -p $(@D)
	$(GCC) $(GCC_ASFLAGS) $(INCLUDE_CFLAGS) -o $@ $<

#  *.bin -> *.bin.o
$(BUILD_DIR)/%.bin.o: %.bin
	$(LD) -r -b binary -o $@ $<

#  assets/hd_code.us.v11.bin -> assets/hd_code.us.v11.bin.o
$(BUILD_DIR)/assets/hd_code.$(VERSION).bin.o: assets/hd_code.$(VERSION).bin
	echo "Copying hd_code binary"
	cp hd_code/hd_code.bin assets/hd_code.$(VERSION).bin
	$(LD) -r -b binary -o $@ $<

#  assets/hd_front_end.us.v11.bin -> assets/hd_front_end.us.v11.bin.o
$(BUILD_DIR)/assets/hd_front_end.$(VERSION).bin.o: assets/hd_front_end.$(VERSION).bin
	echo "Copying hd_front_end binary"
	cp hd_front_end/hd_front_end.bin assets/hd_front_end.$(VERSION).bin
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
	rm -f hd_code/hd_code.bin
	rm -f hd_front_end/hd_front_end.bin

### Settings
.SECONDARY:
.PHONY: all clean default
SHELL = /bin/bash -e -o pipefail
