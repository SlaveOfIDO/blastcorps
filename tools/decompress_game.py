#!/usr/bin/env python3

from typing import BinaryIO
import gzip
import io
import shutil

from rzip_config import loadOverlays, NEXT_AVAILABLE_FREE_SPACE

# game.{version}.bin is a raw slice of the ROM starting at the "game" segment
# (see blastcorps.{version}.yaml), not the ROM itself - every ROM address
# from rzip.config.json/NEXT_AVAILABLE_FREE_SPACE needs to be shifted down
# by this segment's start to land in the right place in that slice.
GAME_ROM_START = 0x4CE0


def readAndDecompressOverlays(fr : BinaryIO, overlays):
    for x in overlays:
        x["codeCompressedSize"] = x["dataROMAddress"] - x["codeROMAddress"]
        fr.seek(x["codeROMAddress"] - GAME_ROM_START, io.SEEK_SET)
        print(f"    - Read {x['name']}.code compressed from {hex(fr.tell())}")
        x["codeCompressedData"] = fr.read(x['codeCompressedSize'])
        x["codeDecompressedData"] = gzip.decompress(x["codeCompressedData"])
        print(f"    - Read {x['name']}.data compressed from {hex(fr.tell())}")
        x["dataCompressedData"] = fr.read(x['dataCompressedSize'])
        x["dataDecompressedData"] = gzip.decompress(x["dataCompressedData"])


def alignHex10(fr: BinaryIO):
    # Get the current position
    current_position = fr.tell()

    # Calculate the offset to the desired alignment
    alignment = 0x10
    offset = alignment - (current_position % alignment)

    # Adjust the position by seeking with the offset
    if abs(offset) < alignment:
        fr.seek(offset, io.SEEK_CUR)

    return fr.tell()

def writeDecompressedOverlaysToROM(fr : BinaryIO, overlays):
    fr.seek(NEXT_AVAILABLE_FREE_SPACE - GAME_ROM_START, io.SEEK_SET)
    for x in overlays:
        decompressedCodeStart = alignHex10(fr)
        fr.write(x["codeDecompressedData"])
        print(f"    - Wrote {x['name']}.code to {hex(decompressedCodeStart)}")
        decompressedDataStart = alignHex10(fr)
        fr.write(x["dataDecompressedData"])
        print(f"    - Wrote {x['name']}.data to {hex(decompressedDataStart)}")


version, overlays = loadOverlays()
source_file = f"game.{version}.bin"
destination_file = f"game.{version}.decompressed.bin"
print(f"Decompressing game segment for version '{version}'")

# Make a copy of the game bin to be used as the decompressed game bin
shutil.copyfile(source_file, destination_file)

# Open the decompressed game bin
with open(destination_file, "r+b") as fh:
    # Decompress all code and data segments
    print("[1 / 2] Decompressing overlays...")
    readAndDecompressOverlays(fh, overlays)

    # Concatenate the decompressed segments onto the end of the file, align by 0x10 bytes
    print("[2 / 2] Writing decompressed overlays...")
    writeDecompressedOverlaysToROM(fh, overlays)
    print("Decompressed game segment created.")
