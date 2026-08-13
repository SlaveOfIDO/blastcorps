VERSION  ?= us.v11
export VERSION

# NON_MATCHING - whether to build a matching, identical copy of the ROM
#   1 - enable some alternate, more portable code that does not produce a matching ROM
#   0 - build a matching ROM
NON_MATCHING ?= 0
export NON_MATCHING

CROSS = mips-linux-gnu-
GCC = $(CROSS)gcc
OBJCOPY = $(CROSS)objcopy
PYTHON = python3
TOOLS_DIR := tools

GCC_ASFLAGS := -EB -x assembler-with-cpp -march=vr4300 -mabi=32 -O2 -G 0 -w -nostdinc -c   -mfix4300 -mno-abicalls -DMIPSEB -D_LANGUAGE_ASSEMBLY -D_MIPS_SIM=1 -D_MIPS_SZLONG=32 -mtune=vr4300 -fno-align-labels -fno-align-functions -fno-align-loops -fno-align-jumps -fno-common -fno-zero-initialized-in-bss -mfp32 -ffreestanding -O -mno-shared -fno-PIC
INCLUDE_CFLAGS := -I . -I include -I include/2.0D -I include/2.0D/PR

BUILD_DIR = build
TARGET = $(BUILD_DIR)/blastcorps.$(VERSION)

### Targets

default: all

ifeq ($(NON_MATCHING),1)
all: $(TARGET).z64
else
all: $(TARGET).z64 verify
endif

check: .baserom.$(VERSION).ok

verify: $(TARGET).z64
	echo "$$(cat blastcorps.$(VERSION).sha1)  $(TARGET).z64" | sha1sum --check

extract: check
	splat split blastcorps.$(VERSION).yaml
	mv assets/init.bin init/init.$(VERSION).bin
	mv assets/game.bin game/game.$(VERSION).bin
	$(MAKE) -C init VERSION=$(VERSION) extract
	$(MAKE) -C game VERSION=$(VERSION) extract

.PHONY: init-size game-build reloc init-build game-compress

# links init once with placeholder rzip reloc values, only to learn its
# real compiled size ahead of game's link
init-size:
	$(MAKE) -C init VERSION=$(VERSION) NON_MATCHING=$(NON_MATCHING) RZIP_RELOC_FILE=../tools/rzip_reloc_placeholder.init.txt build/init.$(VERSION).bin

game-build: init-size
	VERSION=$(VERSION) $(PYTHON) $(TOOLS_DIR)/patch_game_rom_base.py
	$(MAKE) -C game VERSION=$(VERSION) NON_MATCHING=$(NON_MATCHING) default

# game/build/game.$(VERSION).elf -> rzip_reloc_auto.init.$(VERSION).txt
reloc: game-build
	$(MAKE) -C game VERSION=$(VERSION) NON_MATCHING=$(NON_MATCHING) reloc

init-build: reloc
	$(MAKE) -C init VERSION=$(VERSION) NON_MATCHING=$(NON_MATCHING) default

game-compress: reloc
	$(MAKE) -C game VERSION=$(VERSION) NON_MATCHING=$(NON_MATCHING) compress

#################
## COMPILATION ##
#################

$(BUILD_DIR)/header.s.o: asm/header.s
	@mkdir -p $(@D)
	$(GCC) $(GCC_ASFLAGS) $(INCLUDE_CFLAGS) -o $@ $<

$(BUILD_DIR)/header.bin: $(BUILD_DIR)/header.s.o
	$(OBJCOPY) -O binary --only-section=.data $< $@

$(TARGET).bin: $(BUILD_DIR)/header.bin init-build game-compress
	cat $(BUILD_DIR)/header.bin assets/boot.bin init/build/init.$(VERSION).bin game/build/game.$(VERSION).compressed.bin > $@

$(TARGET).z64: $(TARGET).bin
	cp $< $@
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
	rm -rf assets
	rm -rf build
	rm -f *auto*.txt
	$(MAKE) -C init clean
	$(MAKE) -C game clean

##########
## FULL ##
##########
full:
	$(MAKE) clean
	$(MAKE) extract
	$(MAKE)

### Settings
.SECONDARY:
.PHONY: all default check verify extract report progress clean full
SHELL = /bin/bash -e -o pipefail
