#!/usr/bin/env python3
"""Computes the packed ROM layout for the compressed overlays and writes the
rzip_*_START/_END linker symbols (rzip_reloc_auto.init.<version>.txt).

This runs *before* the main ROM is linked, reading the decompressed overlay
content straight out of decompressed/build/decompressed.bin (already built
by the decompressed sub-project) instead of the not-yet-linked main ROM, so
the linker always sees the addresses for the current build rather than a
previous one.

The compressed segments themselves are cached under build/ (as
<name>.gz), along with a build/rzip_layout.json sidecar recording where each
one belongs in the final ROM, for compress_rom.py to pick up after the link.
"""

from typing import BinaryIO
import io
import json
import os
import struct
import subprocess

from rzip_config import loadOverlays, computeDecompressedROMAddresses, align16, NEXT_AVAILABLE_FREE_SPACE

GZIP = "tools/gzip-1.2.4/gzip"
RELOC_SYM_PREFIX = "rzip"
DECOMPRESSED_BIN = "decompressed/build/decompressed.bin"
LAYOUT_SIDECAR = "build/rzip_layout.json"


def compressSegmentData(fr : BinaryIO, name, offset, decompressedSize, timestamp):
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

    return len(compressedData)


def compressOverlays(fr : BinaryIO, overlays):
    for x in overlays:
        codeOffset = x["decompressedCodeROMAddress"] - NEXT_AVAILABLE_FREE_SPACE
        dataOffset = x["decompressedDataROMAddress"] - NEXT_AVAILABLE_FREE_SPACE
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


def writeRelocFile(version, overlays, endAddress):
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
    print(f"    - Wrote {path}")


def writeLayoutSidecar(overlays, endAddress):
    layout = {
        "endAddress": endAddress,
        "overlays": [
            {"codeName": x["codeName"], "dataName": x["dataName"],
             "codeROMAddress": x["codeROMAddress"], "dataROMAddress": x["dataROMAddress"]}
            for x in overlays
        ],
    }
    os.makedirs("build", exist_ok=True)
    with open(LAYOUT_SIDECAR, "w") as f:
        json.dump(layout, f, indent=2)


version, overlays = loadOverlays()
computeDecompressedROMAddresses(overlays)
# the original ROM address of the first overlay's code is used as the start
# of the repacked compressed layout for this version
startAddress = overlays[0]["codeROMAddress"]

print(f"Computing rzip reloc layout for version '{version}'")
os.makedirs("build", exist_ok=True)

with open(DECOMPRESSED_BIN, "rb") as fh:
    print("[1/2] Compressing overlays...")
    compressOverlays(fh, overlays)

print("[2/2] Laying out compressed overlays...")
endAddress = layoutCompressedOverlays(overlays, startAddress)
writeRelocFile(version, overlays, endAddress)
writeLayoutSidecar(overlays, endAddress)
