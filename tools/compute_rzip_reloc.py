#!/usr/bin/env python3
"""Computes hd_code/hd_front_end's real, absolute ROM layout for their
recompressed (rzip) overlay - the position src/init/1A30.c's NON_MATCHING=1
path DMA-reads from at runtime - and writes the rzip_*_START/_END and
hd_code_BSS_END linker symbols (../rzip_reloc_auto.init.<version>.txt) for
init's link to -T in.

Run from game/ (like decompress_game.py/compress_game.py), after game has
been built against its patched linker script (see
tools/patch_game_rom_base.py and the root Makefile's game-build target),
so build/game.<version>.elf's _ROM_START/_ROM_END symbols are already
absolute ROM addresses - exactly what init links against - rather than
relative to game's own start.

Unlike the old monolithic build, game itself only ever links once: its
own internal layout (VRAM addresses, and ROM positions relative to its
own start) doesn't depend on init's size at all, only the *absolute* base
those relative positions are read out at does - and that's resolved by
patching the linker script before this one link, not by re-linking game
after the fact.
"""

from typing import BinaryIO
import io
import os
import struct
import subprocess
import sys

from rzip_config import loadOverlays, computeDecompressedROMAddresses, align16, readSymbol, computeGameRomBase, ORIGINAL_GAME_ROM_START

GZIP = "../tools/gzip-1.2.4/gzip"
RELOC_SYM_PREFIX = "rzip"


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


def compressOverlays(fr: BinaryIO, overlays):
    for x in overlays:
        x["codeCompressedSize"] = compressSegmentData(fr, x["codeName"], x["decompressedCodeROMAddress"], x["codeDecompressedSize"], x["codeTimestamp"])
        x["dataCompressedSize"] = compressSegmentData(fr, x["dataName"], x["decompressedDataROMAddress"], x["dataDecompressedSize"], x["dataTimestamp"])


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


def writeRelocFile(version, overlays, endAddress, hdCodeBssEnd):
    path = f"../rzip_reloc_auto.init.{version}.txt"
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
elfPath = f"build/game.{version}.elf"
# this build's real, absolute ROM base for game - see
# tools/patch_game_rom_base.py, which patched game's linker script to
# this same value before it was linked
gameRomBase = computeGameRomBase(f"../init/build/init.{version}.bin")

print(f"Computing rzip reloc layout for version '{version}'")
os.makedirs("build", exist_ok=True)

# each overlay's real decompressed position (absolute ROM address, since
# game's linker script was seeded at gameRomBase) and size, straight out
# of game's own linked ELF. Rebased back to file-relative for reading out
# of game's own build/game.<version>.bin below.
computeDecompressedROMAddresses(overlays, elfPath=elfPath)
for x in overlays:
    x["decompressedCodeROMAddress"] -= gameRomBase
    x["decompressedDataROMAddress"] -= gameRomBase

# the compressed overlay layout starts wherever game's own link actually
# placed the yaml's placeholder segment for it, named after its declared,
# *original*-ROM-relative hex address (see game.<version>.yaml's "game"
# bin entries, rebased from rzip.config.json's original absolute address
# during extraction - not this build's actual gameRomBase, which may
# differ from the original ROM's 0x4CE0 boundary if init's size has
# drifted) - see readTrueStartAddress in the old compute_rzip_reloc.py
# this was ported from. Its *value* comes out as an absolute ROM address
# for this build (gameRomBase), which is what layoutCompressedOverlays
# below should pack starting from - init links against absolute
# addresses.
firstOverlayGameRelativeStart = overlays[0]["codeROMAddress"] - ORIGINAL_GAME_ROM_START
startAddress = readSymbol(elfPath, f"_{firstOverlayGameRelativeStart:X}_ROM_START")
if startAddress is None:
    sys.exit(f"error: could not find _{firstOverlayGameRelativeStart:X}_ROM_START in {elfPath}")

with open(f"build/game.{version}.bin", "rb") as fh:
    print("[1/2] Compressing overlays...")
    compressOverlays(fh, overlays)

print("[2/2] Laying out compressed overlays...")
endAddress = layoutCompressedOverlays(overlays, startAddress)
hdCodeBssEnd = readSymbol(elfPath, "hd_code_BSS_END")
if hdCodeBssEnd is None:
    sys.exit(f"error: could not find hd_code_BSS_END in {elfPath}")
writeRelocFile(version, overlays, endAddress, hdCodeBssEnd)
