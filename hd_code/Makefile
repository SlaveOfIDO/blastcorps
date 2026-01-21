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
LD_SCRIPT = hd_code.ld
OBJCOPYFLAGS = -O binary
ASFLAGS = -EB -mtune=vr4300 -march=vr4300 -mabi=32 -I include
LDFLAGS = -T $(LD_SCRIPT) -Map hd_code.map -T undefined_syms_auto.txt -T undefined_funcs_auto.txt -T undefined_syms.txt --no-check-sections
INCLUDE_CFLAGS := -I . -I ../include -I ../include/2.0D
CFLAGS := -G 0 -Xfullwarn -Xcpluscomm -signed -nostdinc -non_shared -Wab,-r4300_mul -D_LANGUAGE_C -D_FINALROM -DTARGET_N64 -DF3D_OLD -woff 649,838 $(INCLUDE_CFLAGS)
GCC_ASFLAGS    := -EB -mtune=vr4300 -march=vr4300 -mabi=32 -O2 -fno-align-labels -fno-align-functions -fno-align-loops -fno-align-jumps -fno-common -fno-zero-initialized-in-bss -mfp32 -c -x assembler-with-cpp -mabi=32 -ffreestanding -mtune=vr4300 -march=vr4300 -mfix4300 -G 0 -O -mno-shared -fno-PIC -mno-abicalls


ASM_DIR   = asm
SRC_DIR   = src

UNMATCHED_SRC_DIR = $(ASM_DIR)
UNMATCHED_S_FILES = $(shell find $(UNMATCHED_SRC_DIR) -name '*.s' -not -path '*/nonmatchings/*')
UNMATCHED_S_O_FILES := $(foreach file,$(UNMATCHED_S_FILES),$(BUILD_DIR)/$(file).o)

HD_CODE_SRC_DIR   = $(SRC_DIR)/hd_code
HD_CODE_SRC_DIRS  = $(shell find $(HD_CODE_SRC_DIR) -type d)

HD_CODE_C_FILES   = $(shell find $(HD_CODE_SRC_DIR) -name '*.c')
HD_CODE_C_O_FILES := $(foreach file,$(HD_CODE_C_FILES),$(BUILD_DIR)/$(file).o)

HD_CODE_S_FILES   = $(shell find $(HD_CODE_SRC_DIR) -name '*.s')
HD_CODE_S_O_FILES := $(foreach file,$(HD_CODE_S_FILES),$(BUILD_DIR)/$(file).o)

# Files requiring pre/post-processing
GLOBAL_ASM_HD_CODE_C_FILES := $(shell $(GREP) GLOBAL_ASM $(HD_CODE_SRC_DIR) </dev/null 2>/dev/null)
GLOBAL_ASM_HD_CODE_C_O_FILES := $(foreach file,$(GLOBAL_ASM_HD_CODE_C_FILES),$(BUILD_DIR)/$(file).o)

#### Assets
BIN_DIRS  = assets assets/hd_code assets/hd_code/os assets/hd_code/io
BIN_FILES = $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.bin))
BIN_O_FILES := $(foreach file,$(BIN_FILES),$(BUILD_DIR)/$(file).o)

MIPS3_C_O_FILES = $(BUILD_DIR)/src/hd_code/libc/ll.c.o

O_FILES := $(UNMATCHED_S_O_FILES) \
		   $(HD_CODE_C_O_FILES) \
		   $(HD_CODE_S_O_FILES) \
		   $(GLOBAL_ASM_HD_CODE_C_O_FILES) \
		   $(BIN_O_FILES)


###################
## DECOMPILATION ##
###################

decompile:
	$(PYTHON) $(TOOLS_DIR)/splat/split.py hd_code.yaml


#################
## COMPILATION ##
#################

## OVERRIDES

build/src/hd_code/libc/ll.c.o: MIPSISET := -mips3 -o32
build/src/hd_code/gu/%.c.o: OPT_FLAGS = -O3

# *.c -> *.c.o (with GLOBAL_ASM macro)
$(GLOBAL_ASM_HD_CODE_C_O_FILES): $(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(PYTHON) $(TOOLS_DIR)/asm-processor/asm_processor.py $(OPT_FLAGS) $< > $(BUILD_DIR)/$<
	$(CC) -c -32 $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $(BUILD_DIR)/$<
	$(PYTHON) $(TOOLS_DIR)/asm-processor/asm_processor.py $(OPT_FLAGS) $< --post-process $@ \
		--assembler "$(AS) $(ASFLAGS)" --asm-prelude $(TOOLS_DIR)/asm-processor/prelude.s

# *.c -> *.c.o (without GLOBAL_ASM macro)
$(MIPS3_C_O_FILES): $(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(CC) -c -32 $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<
	$(TOOLS_DIR)/set_o32abi_bit.py $@
	$(OBJCOPY) $@
	$(OBJCOPY) --strip-unneeded $@


# *.c -> *.c.o (without GLOBAL_ASM macro)
$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<

# *.s -> *.s.o
$(BUILD_DIR)/%.s.o: %.s
	@mkdir -p $(@D)
	@$(GCC) $(GCC_ASFLAGS) $(INCLUDE_CFLAGS) -o $@ $<

#  *.bin -> *.bin.o
$(BUILD_DIR)/%.bin.o: %.bin
	mkdir -p $(@D)
	$(LD) -r -b binary -o $@ $<




# *.o -> *.elf
build/hd_code.elf: $(O_FILES)
	$(LD) $(LDFLAGS) -o $@

# *.elf -> *.bin
build/hd_code.bin: build/hd_code.elf
	$(OBJCOPY) $(OBJCOPYFLAGS) $< $@

# SHA1 check
.baserom.$(VERSION).ok: baserom.$(VERSION).z64
	echo "$$(cat $(BASENAME).$(VERSION).sha1)  $<" | sha1sum --check
	touch $@

compile: build/hd_code.bin verify

verify: build/hd_code.bin
	@echo "$$(cat hd_code.sha1) $<" | sha1sum --check

###########
## CLEAN ##
###########

clean:
	rm -rf asm
	rm -rf assets
	rm -rf build
	rm -f *auto.txt