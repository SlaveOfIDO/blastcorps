#!/usr/bin/env python3
"""Compresses hd_code/hd_front_end (gzip, matching the original ROM's
format) straight out of the just-linked ROM and splices them into the
final .z64, then fills the freed-up space with 0xFF and drops the appended
decompressed overlay data used only for building.

hd_code/hd_front_end compile as a normal part of the main ROM link now (see
blastcorps.us.v11.yaml) - their real, current compiled bytes are already
sitting in build/blastcorps.<version>.bin by the time this runs, at each
overlay's own real, linker-tracked position (see
computeDecompressedROMAddresses), so there's no need for a separate
pre-link step to learn them first.
"""

from typing import BinaryIO
import io
import re
import shutil
import struct
import subprocess

from rzip_config import loadOverlays, computeDecompressedROMAddresses, align16

GZIP = "tools/gzip-1.2.4/gzip"
ROM_SIZE = 0x800000


def readStartAddress(version, name):
    """Reads the same rzip_<NAME>_TEXT_START that init was linked against,
    straight out of rzip_reloc_auto.init.<version>.txt, instead of
    re-deriving it independently - so this can never disagree with what
    src/init/1A30.c's DMA actually reads from (see
    compute_rzip_reloc.py's readTrueStartAddress for why the address in
    rzip.config.json alone isn't always right)."""
    path = f"rzip_reloc_auto.init.{version}.txt"
    symbol = f"rzip_{name.upper()}_TEXT_START"
    with open(path) as f:
        for line in f:
            m = re.match(rf"{symbol}\s*=\s*(0x[0-9a-fA-F]+)\s*;", line)
            if m:
                return int(m.group(1), 16)
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
# reads each overlay's real decompressedCodeROMAddress/
# decompressedDataROMAddress/*DecompressedSize straight out of the just-linked
# ELF's own symbols - this main ROM ELF always exists by the time
# compress_rom.py runs, so these are always the real, current values, already
# correct file offsets into build/blastcorps.<version>.bin (see
# computeDecompressedROMAddresses)
computeDecompressedROMAddresses(overlays, elfPath=f"build/blastcorps.{version}.elf")
# must match whatever init was actually linked against, which may not be
# rzip.config.json's codeROMAddress (see readStartAddress)
startAddress = readStartAddress(version, overlays[0]["name"])

source_file = f"build/blastcorps.{version}.bin"
destination_file = f"build/blastcorps.{version}.z64"
print(f"Compressing ROM for version '{version}'")

# Make a copy of the built ROM to be used as the compressed ROM
shutil.copyfile(source_file, destination_file)

# Open the compressed ROM
with open(destination_file, "r+b") as fh:
    print("[1/3] Compressing overlays...")
    compressOverlays(fh, overlays)

    print("[2/3] Writing compressed overlays...")
    endAddress = writeCompressedOverlays(fh, overlays, startAddress)

    if endAddress < ROM_SIZE:
        print(f"    - Filling {hex(endAddress)}-{hex(ROM_SIZE)} with 0xFF")
        fh.seek(endAddress, io.SEEK_SET)
        fh.write(b"\xFF" * (ROM_SIZE - endAddress))
    else:
        print(f"    - Compressed overlays extend to {hex(endAddress)}, not filling")

    fh.seek(0, io.SEEK_SET)
    whole_rom = fh.read(ROM_SIZE)

print("[3/3] Removing decompressed overlays...")
with open(destination_file, "wb") as f:
    f.write(whole_rom)
