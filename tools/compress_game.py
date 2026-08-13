#!/usr/bin/env python3
"""Compresses hd_code/hd_front_end (gzip, matching the original ROM's
format) straight out of game's just-linked bin and splices them back in,
then fills the freed-up space with 0xFF and truncates off the appended
decompressed overlay data used only for building - mirrors
decompress_game.py's inverse.

Run from game/, after game has been built against its patched linker
script (see tools/patch_game_rom_base.py and the root Makefile's
game-build target) and ../rzip_reloc_auto.init.<version>.txt has been
computed (see compute_rzip_reloc.py) - this needs that file's addresses
to know where to place the recompressed overlay.

Produces build/game.<version>.compressed.bin, sized to exactly match
game's real ROM size for this build (0x800000 - this build's gameRomBase,
which shrinks or grows opposite to init's own real size) - ready for the
root Makefile to concatenate after header+boot+init.bin.
"""

from typing import BinaryIO
import io
import os
import re
import shutil
import struct
import subprocess

from rzip_config import loadOverlays, computeDecompressedROMAddresses, align16, computeGameRomBase, NEXT_AVAILABLE_FREE_SPACE

GZIP = "../tools/gzip-1.2.4/gzip"


def readStartAddress(version, name, gameRomBase):
    """Reads the same rzip_<NAME>_TEXT_START that init was linked against,
    straight out of ../rzip_reloc_auto.init.<version>.txt, instead of
    re-deriving it independently - so this can never disagree with what
    src/init/1A30.c's DMA actually reads from. Rebased from the absolute
    ROM address written there back to game-relative, since this operates
    on game's own bin, not the full ROM."""
    path = f"../rzip_reloc_auto.init.{version}.txt"
    symbol = f"rzip_{name.upper()}_TEXT_START"
    with open(path) as f:
        for line in f:
            m = re.match(rf"{symbol}\s*=\s*(0x[0-9a-fA-F]+)\s*;", line)
            if m:
                return int(m.group(1), 16) - gameRomBase
    raise ValueError(f"{symbol} not found in {path}")


def compressSegmentData(fr: BinaryIO, name, offset, decompressedSize, timestamp) -> bytes:
    fr.seek(offset, io.SEEK_SET)
    print(f"    - Read {name} decompressed from {hex(offset)}")
    decompressedData = fr.read(decompressedSize)

    with open("build/" + name, "wb") as f:
        f.write(decompressedData)

    # compress data with tools/gzip-1.2.4/gzip by starting subprocess
    compressedData = subprocess.check_output([GZIP, "-f", "-c", "build/" + name])

    # restore the original timestamp in the gzip header MTIME field
    compressedData = compressedData[:4] + struct.pack("<I", timestamp) + compressedData[8:]

    with open("build/" + name + ".gz", "wb") as f:
        f.write(compressedData)

    return compressedData


def compressOverlays(fr: BinaryIO, overlays):
    for x in overlays:
        x["codeCompressedData"] = compressSegmentData(
            fr, x["codeName"], x["decompressedCodeROMAddress"], x["codeDecompressedSize"], x["codeTimestamp"]
        )
        x["dataCompressedData"] = compressSegmentData(
            fr, x["dataName"], x["decompressedDataROMAddress"], x["dataDecompressedSize"], x["dataTimestamp"]
        )


def writeCompressedOverlays(fr: BinaryIO, overlays, startAddress):
    """Pack the compressed code/data of every overlay back-to-back into fr,
    starting at startAddress, aligning to 0x10 after each overlay's
    code+data pair (data immediately follows code within a pair, no gap).
    Returns the final (aligned) end-of-layout position."""
    position = align16(startAddress)
    for x in overlays:
        fr.seek(position, io.SEEK_SET)
        fr.write(x["codeCompressedData"])
        position += len(x["codeCompressedData"])

        fr.seek(position, io.SEEK_SET)
        fr.write(x["dataCompressedData"])
        position += len(x["dataCompressedData"])

        position = align16(position)
    return position


version, overlays = loadOverlays()
elfPath = f"build/game.{version}.elf"
# this build's real, absolute ROM base for game - see
# tools/patch_game_rom_base.py, which patched game's linker script to
# this same value before it was linked
gameRomBase = computeGameRomBase(f"../init/build/init.{version}.bin")
gameRomSize = NEXT_AVAILABLE_FREE_SPACE - gameRomBase

# reads each overlay's real decompressedCodeROMAddress/
# decompressedDataROMAddress/*DecompressedSize straight out of game's own
# just-linked ELF's symbols. These come out absolute (game's linker
# script was seeded at gameRomBase), so rebase back to file-relative
# before using them to read out of game's own build/game.<version>.bin
# below.
computeDecompressedROMAddresses(overlays, elfPath=elfPath)
for x in overlays:
    x["decompressedCodeROMAddress"] -= gameRomBase
    x["decompressedDataROMAddress"] -= gameRomBase
startAddress = readStartAddress(version, overlays[0]["name"], gameRomBase)

source_file = f"build/game.{version}.bin"
destination_file = f"build/game.{version}.compressed.bin"
print(f"Compressing game segment for version '{version}'")

os.makedirs("build", exist_ok=True)

# Make a copy of the built game bin to be used as the compressed one
shutil.copyfile(source_file, destination_file)

# Open the compressed game bin
with open(destination_file, "r+b") as fh:
    print("[1/3] Compressing overlays...")
    compressOverlays(fh, overlays)

    print("[2/3] Writing compressed overlays...")
    endAddress = writeCompressedOverlays(fh, overlays, startAddress)

    if endAddress < gameRomSize:
        print(f"    - Filling {hex(endAddress)}-{hex(gameRomSize)} with 0xFF")
        fh.seek(endAddress, io.SEEK_SET)
        fh.write(b"\xFF" * (gameRomSize - endAddress))
    else:
        print(f"    - Compressed overlays extend to {hex(endAddress)}, not filling")

    fh.seek(0, io.SEEK_SET)
    game_bytes = fh.read(gameRomSize)

print("[3/3] Removing decompressed overlays...")
with open(destination_file, "wb") as f:
    f.write(game_bytes)
