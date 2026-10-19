#!/usr/bin/env python3

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

    compressedData = subprocess.check_output([GZIP, "-f", "-c", "build/" + name])

    # restore the original timestamp in the gzip header MTIME field
    compressedData = compressedData[:4] + struct.pack("<I", timestamp) + compressedData[8:]

    return len(compressedData)


def compressOverlays(fr: BinaryIO, overlays):
    for x in overlays:
        x["codeCompressedSize"] = compressSegmentData(fr, x["codeName"], x["decompressedCodeROMAddress"], x["codeDecompressedSize"], x["codeTimestamp"])
        x["dataCompressedSize"] = compressSegmentData(fr, x["dataName"], x["decompressedDataROMAddress"], x["dataDecompressedSize"], x["dataTimestamp"])


def layoutCompressedOverlays(overlays, startAddress):
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
gameRomBase = computeGameRomBase(f"../init/build/init.{version}.bin")

print(f"Computing rzip reloc layout for version '{version}'")
os.makedirs("build", exist_ok=True)

computeDecompressedROMAddresses(overlays, elfPath=elfPath)
for x in overlays:
    x["decompressedCodeROMAddress"] -= gameRomBase
    x["decompressedDataROMAddress"] -= gameRomBase

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
