#!/usr/bin/env python3
"""Computes hd_code/hd_front_end's real compressed ROM layout ahead of
linking init/ (src/1A30.c's NON_MATCHING=1 path references the compressed
overlay's ROM position directly), and writes the rzip_*_START/_END and
hd_code_BSS_END linker symbols (rzip_reloc_auto.init.<version>.txt) for
init's link to -T in.

Reads real, current compiled content out of build/hd_code_prelim.bin - a
preliminary link of just hd_code/hd_front_end (see
tools/gen_hd_code_prelim_ld.py and the root Makefile), built from the same
.o files that go into the real ROM link - rather than hardcoding it, so
this stays correct even if hd_code/hd_front_end's compiled size ever
drifts from the original ROM's.

That preliminary link is still only an approximation, though: linked on
its own, without the rest of the ROM's symbols available, a handful of
relocations can resolve to slightly different bytes than they do in the
real link (see chooseDecompressedSource) - enough to shift the compressed
size by a few bytes. So once a previous run's main ROM ELF exists, this
switches to reading the real, final compiled bytes straight out of it
instead (same idea as readTrueStartAddress below), and only falls back to
the preliminary link's approximation for the very first pass, before the
real ROM has been linked even once yet.

The *starting* ROM address for this layout is a different problem: the main
.decompressed.ld script places every segment back-to-back by a running
__romPos counter, so hd_code's real starting position also depends on the
compiled size of everything before it in the ROM (init, mainly) - which
isn't fixed for a NON_MATCHING build. rzip.config.json's codeROMAddress is
only the *original* ROM's position, correct exclusively when nothing
upstream has drifted in size (a matching build). If a previous run's main
ROM ELF (build/blastcorps.<version>.elf) exists, this reads that segment's
own linker-computed position back out of it (see readTrueStartAddress)
instead of trusting the config, so a drifted build corrects itself. See the
Makefile's $(TARGET).z64 rule for how this converges within one `make`
invocation.

hd_code_BSS_END - the *VRAM* end of hd_code (used by src/init/1A30.c to
know how far to zero after DMA+inflate) - is the same class of problem:
unlike hd_code_VRAM/hd_front_end_VRAM (fixed load addresses regardless of
compiled size), it's the end of hd_code's own content, which obviously
does depend on compiled size. It used to be hardcoded in
undefined_syms.init.<version>.txt; now it's read back out of a previous
main ROM ELF the same way as the rzip_* addresses above (see
readHdCodeBssEnd), for the same reason.

hd_code/hd_front_end's *final* compressed bytes (what actually ends up in
the ROM) come from compress_rom.py, which runs after the real link and
reads their content straight out of the final binary - this script's own
compressed output is only used for sizing/positions, not the bytes
actually shipped.
"""

from typing import BinaryIO, Optional
import io
import os
import struct
import subprocess

from rzip_config import loadOverlays, computeDecompressedROMAddresses, align16, readSymbol, NEXT_AVAILABLE_FREE_SPACE

GZIP = "tools/gzip-1.2.4/gzip"
RELOC_SYM_PREFIX = "rzip"
DECOMPRESSED_BIN = "build/hd_code_prelim.bin"
# bootstrap fallback for hd_code_BSS_END, for the very first pass before any
# main ROM ELF exists to read the real value back out of - originally the
# only value, hardcoded in undefined_syms.init.<version>.txt
HD_CODE_BSS_END_FALLBACK = 0x80400000


def compressSegmentData(fr: BinaryIO, name, offset, decompressedSize, timestamp) -> int:
    fr.seek(offset, io.SEEK_SET)
    print(f"    - Read {name} decompressed from {hex(offset)}")
    decompressedData = fr.read(decompressedSize)

    with open("build/" + name, "wb") as f:
        f.write(decompressedData)

    # compress data with tools/gzip-1.2.4/gzip by starting subprocess
    compressedData = subprocess.check_output([GZIP, "-f", "-c", "build/" + name])

    # restore the original timestamp in the gzip header MTIME field
    compressedData = compressedData[:4] + struct.pack("<I", timestamp) + compressedData[8:]

    return len(compressedData)


def compressOverlays(fr: BinaryIO, overlays, shift):
    for x in overlays:
        codeOffset = x["decompressedCodeROMAddress"] + shift
        dataOffset = x["decompressedDataROMAddress"] + shift
        x["codeCompressedSize"] = compressSegmentData(fr, x["codeName"], codeOffset, x["codeDecompressedSize"], x["codeTimestamp"])
        x["dataCompressedSize"] = compressSegmentData(fr, x["dataName"], dataOffset, x["dataDecompressedSize"], x["dataTimestamp"])


def layoutCompressedOverlays(overlays, startAddress):
    """Pack the compressed code/data of every overlay back-to-back, starting
    at startAddress, aligning to 0x10 after each overlay's code+data pair.
    Returns the final (aligned) end-of-layout position."""
    position = align16(startAddress)
    for x in overlays:
        x["codeROMAddress"] = position
        position += x["codeCompressedSize"]
        x["codeROMEndAddress"] = position

        x["dataROMAddress"] = position
        position += x["dataCompressedSize"]
        x["dataROMEndAddress"] = position

        position = align16(position)
    return position


def readTrueStartAddress(version, configStartAddress) -> Optional[int]:
    """splat names the placeholder segment for an address-only entry (no
    name given) after its declared hex address, e.g. the main yaml's
    `- [0x787FD0, bin]` becomes output section `._787FD0`, with a
    `_787FD0_ROM_START` symbol holding wherever __romPos actually put it
    for *this* link - which is what we want, however this build's earlier
    segments (init, mainly) actually came out sized."""
    elfPath = f"build/blastcorps.{version}.elf"
    symbolName = f"_{configStartAddress:X}_ROM_START"
    trueAddress = readSymbol(elfPath, symbolName)
    if trueAddress is None:
        print(f"    - No prior {elfPath} to confirm the real start address from; using rzip.config.json's {hex(configStartAddress)}")
        return None
    if trueAddress != configStartAddress:
        print(f"    - {elfPath} says the real start address is {hex(trueAddress)}, not rzip.config.json's {hex(configStartAddress)} (earlier ROM content has drifted in size) - using {hex(trueAddress)}")
    return trueAddress


def readHdCodeBssEnd(version) -> int:
    """hd_code_BSS_END is the VRAM address right after hd_code's own
    text+data+bss - depends on hd_code's total compiled size, so like
    the rzip_* addresses above it's read back out of a previous main ROM
    link if one exists, falling back to the original hardcoded value only
    for the very first pass."""
    elfPath = f"build/blastcorps.{version}.elf"
    trueEnd = readSymbol(elfPath, "hd_code_BSS_END")
    if trueEnd is None:
        print(f"    - No prior {elfPath} to confirm hd_code_BSS_END from; using {hex(HD_CODE_BSS_END_FALLBACK)}")
        return HD_CODE_BSS_END_FALLBACK
    if trueEnd != HD_CODE_BSS_END_FALLBACK:
        print(f"    - {elfPath} says hd_code_BSS_END is {hex(trueEnd)}, not {hex(HD_CODE_BSS_END_FALLBACK)} (hd_code's compiled size has drifted) - using {hex(trueEnd)}")
    return trueEnd


def chooseDecompressedSource(version, name):
    """Picks where to read hd_code/hd_front_end's decompressed content from
    for sizing: the real main ROM binary, at wherever this build's own link
    actually put it (most accurate - see the module docstring), if one
    exists yet; otherwise the preliminary hd_code/hd_front_end-only link
    (always at offset 0 - see gen_hd_code_prelim_ld.py), for the very first
    pass. Returns (path, shift). When reading from the real ROM binary,
    computeDecompressedROMAddresses (given the same elfPath) has already
    read each overlay's real, absolute decompressedCodeROMAddress/
    decompressedDataROMAddress straight out of its own linker-tracked
    symbols, which are already correct file offsets into that binary - so
    shift is just 0. The preliminary link's own hd_code_ROM_START is
    always exactly 0 (no per-overlay symbols to read yet, so
    computeDecompressedROMAddresses falls back to accumulating from
    NEXT_AVAILABLE_FREE_SPACE) - shift rebases that back to 0."""
    elfPath = f"build/blastcorps.{version}.elf"
    binPath = f"build/blastcorps.{version}.bin"
    trueBase = readSymbol(elfPath, f"{name}_ROM_START")
    if trueBase is not None and os.path.exists(binPath):
        return binPath, 0
    return DECOMPRESSED_BIN, -NEXT_AVAILABLE_FREE_SPACE


def writeRelocFile(version, overlays, endAddress, hdCodeBssEnd):
    path = f"rzip_reloc_auto.init.{version}.txt"
    with open(path, "w") as f:
        for x in overlays:
            name = x["name"].upper()
            f.write(f"{RELOC_SYM_PREFIX}_{name}_TEXT_START = {hex(x['codeROMAddress'])};\n")
            f.write(f"{RELOC_SYM_PREFIX}_{name}_TEXT_END = {hex(x['codeROMEndAddress'])};\n")
            f.write(f"{RELOC_SYM_PREFIX}_{name}_DATA_START = {hex(x['dataROMAddress'])};\n")
            f.write(f"{RELOC_SYM_PREFIX}_{name}_DATA_END = {hex(x['dataROMEndAddress'])};\n")
        # end of the whole packed layout, i.e. where the 0xFF padding starts
        f.write(f"{RELOC_SYM_PREFIX}_LAYOUT_END = {hex(endAddress)};\n")
        f.write(f"hd_code_BSS_END = {hex(hdCodeBssEnd)};\n")
    print(f"    - Wrote {path}")


version, overlays = loadOverlays()
computeDecompressedROMAddresses(overlays, elfPath=f"build/blastcorps.{version}.elf")
# the original ROM address of the first overlay's code is used as the start
# of the repacked compressed layout for this version, unless a previous
# build of the real ROM shows this build's actual position has drifted
# from it (see readTrueStartAddress)
startAddress = readTrueStartAddress(version, overlays[0]["codeROMAddress"])
if startAddress is None:
    startAddress = overlays[0]["codeROMAddress"]

print(f"Computing rzip reloc layout for version '{version}'")
os.makedirs("build", exist_ok=True)

decompressedSourcePath, decompressedSourceBase = chooseDecompressedSource(version, overlays[0]["name"])
print(f"    - Reading decompressed content from {decompressedSourcePath}")
with open(decompressedSourcePath, "rb") as fh:
    print("[1/2] Compressing overlays...")
    compressOverlays(fh, overlays, decompressedSourceBase)

print("[2/2] Laying out compressed overlays...")
endAddress = layoutCompressedOverlays(overlays, startAddress)
hdCodeBssEnd = readHdCodeBssEnd(version)
writeRelocFile(version, overlays, endAddress, hdCodeBssEnd)
