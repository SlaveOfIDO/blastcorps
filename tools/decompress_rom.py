#!/usr/bin/env python3

from typing import BinaryIO
import gzip
import io
import shutil

from rzip_config import loadOverlays, NEXT_AVAILABLE_FREE_SPACE


def readAndDecompressOverlays(fr : BinaryIO, overlays):
    for x in overlays:
        x["codeCompressedSize"] = x["dataROMAddress"] - x["codeROMAddress"]
        fr.seek(x["codeROMAddress"], io.SEEK_SET)
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
    fr.seek(NEXT_AVAILABLE_FREE_SPACE, io.SEEK_SET)
    for x in overlays:
        decompressedCodeStart = alignHex10(fr)
        fr.write(x["codeDecompressedData"])
        print(f"    - Wrote {x['name']}.code to {hex(decompressedCodeStart)}")
        decompressedDataStart = alignHex10(fr)
        fr.write(x["dataDecompressedData"])
        print(f"    - Wrote {x['name']}.data to {hex(decompressedDataStart)}")


version, overlays = loadOverlays()
source_file = f"baserom.{version}.z64"
destination_file = f"baserom.{version}.decompressed.z64"
print(f"Decompressing ROM for version '{version}'")

# Make a copy of the baseROM to be used as the decompressed baseROM
shutil.copyfile(source_file, destination_file)

# Open the decompressed ROM
with open(destination_file, "r+b") as fh:
    # Decompress all code and data segments
    print("[1 / 2] Decompressing overlays...")
    readAndDecompressOverlays(fh, overlays)

    # Concatenate the decompressed segments onto the end of the ROM file, align by 0x10 bytes
    print("[2 / 2] Writing decompressed overlays...")
    writeDecompressedOverlaysToROM(fh, overlays)
    print("Decompressed ROM created.")
