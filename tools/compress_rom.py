#!/usr/bin/env python3

from typing import BinaryIO
import io
import shutil
import struct
import subprocess

from rzip_config import loadOverlays, computeDecompressedROMAddresses

ROM_SIZE = 0x800000
GZIP = "tools/gzip-1.2.4/gzip"


def compressSegment(fr : BinaryIO, name, decompressedROMAddress, decompressedSize, romAddress, timestamp):
    # read in decompressed segment
    fr.seek(decompressedROMAddress, io.SEEK_SET)
    print(f"    - Read {name} decompressed from {hex(fr.tell())}")
    decompressedData = fr.read(decompressedSize)

    # write data to temporary file
    with open("build/" + name, "wb") as f:
        f.write(decompressedData)

    # compress data with tools/gzip-1.2.4/gzip by starting subprocess
    compressedData = subprocess.check_output([GZIP, "-f", "-c", "build/" + name])

    # write compressed data to its ROM address, then restore the original
    # timestamp in the gzip header MTIME field
    fr.seek(romAddress, io.SEEK_SET)
    fr.write(compressedData)
    fr.seek(romAddress + 4, io.SEEK_SET)
    fr.write(struct.pack("<I", timestamp))


def readAndCompressOverlays(fr : BinaryIO, overlays):
    for x in overlays:
        compressSegment(fr, x["codeName"], x["decompressedCodeROMAddress"], x["codeDecompressedSize"],
                        x["codeROMAddress"], x["codeTimestamp"])
        compressSegment(fr, x["dataName"], x["decompressedDataROMAddress"], x["dataDecompressedSize"],
                        x["dataROMAddress"], x["dataTimestamp"])


version, overlays = loadOverlays()
computeDecompressedROMAddresses(overlays)
source_file = f"build/blastcorps.{version}.bin"
destination_file = f"build/blastcorps.{version}.z64"
print(f"Compressing ROM for version '{version}'")

# Make a copy of the built ROM to be used as the compressed ROM
shutil.copyfile(source_file, destination_file)

whole_rom = None

# Open the compressed ROM
with open(destination_file, "r+b") as fh:
    # Compress all code and data segments
    print("[1/2] Compressing overlays...")
    readAndCompressOverlays(fh, overlays)

    fh.seek(0, io.SEEK_SET)
    whole_rom = fh.read(ROM_SIZE)

print("[2/2] Removing decompressed overlays...")
with open(destination_file, "wb") as f:
    f.write(whole_rom)
