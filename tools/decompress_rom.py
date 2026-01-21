#!/usr/bin/env python3

from typing import BinaryIO
import gzip
import io
import shutil

next_available_free_space = 0x800000
source_file = 'baserom.us.v11.z64'
destination_file = 'baserom.us.v11.decompressed.z64'

overlays = [
    {
        "name": "hd_code",
        "codeName": "hd_code_text.raw",
        "codeROMAddress": 0x787FD0,

        "dataName": "hd_code_data.raw",
        "dataROMAddress": 0x7D73B4,
        "dataCompressedSize": 0xC713, # - 8 for length without gzip footer
        # Note: These byte arrays should not contain the gzip footer
        # codeCompressedData: [], // Will be written to ROM
        # dataCompressedData: [], // Will be written to ROM directly after .code, regardless of the original .data address
    }
]

def readAndDecompressOverlays(fr : BinaryIO):
    for x in overlays:
        x["codeCompressedSize"] = x["dataROMAddress"] - x["codeROMAddress"]
        fr.seek(x["codeROMAddress"], io.SEEK_SET)
        print(f"    - Read {x['name']}.code compressed from {hex(fr.tell())}")
        x["codeCompressedData"] = fr.read(x['codeCompressedSize'])
        x["codeDecompressedData"] = gzip.decompress(x["codeCompressedData"])
        print(f"    - Read {x['name']}.data compressed from {hex(fr.tell())}")
        x["dataCompressedData"] = fr.read(x['dataCompressedSize'])
        x["dataDecompressedData"] = gzip.decompress(x["dataCompressedData"])

        with open("expected/" + x["codeName"] + ".expected", "wb") as f:
            f.write(x["codeDecompressedData"])
        with open("expected/" + x["dataName"] + ".expected", "wb") as f:
            f.write(x["dataDecompressedData"])
        

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

def writeDecompressedOverlaysToROM(fr : BinaryIO):
    fr.seek(next_available_free_space, io.SEEK_SET)
    for x in overlays:
        decompressedCodeStart = alignHex10(fr)
        fr.write(x["codeDecompressedData"])
        print(f"    - Wrote {x['name']}.code to {hex(decompressedCodeStart)}")
        decompressedDataStart = alignHex10(fr)
        fr.write(x["dataDecompressedData"])
        print(f"    - Wrote {x['name']}.data to {hex(decompressedDataStart)}")

# Make a copy of the baseROM to be used as the decompressed baseROM
shutil.copyfile(source_file, destination_file)

# Open the decompressed ROM
with open(destination_file, "r+b") as fh:
    # Decompress all code and data segments
    print("[1 / 2] Decompressing overlays...")
    readAndDecompressOverlays(fh)

    # Concatenate the decompressed segments onto the end of the ROM file, align by 0x10 bytes
    print("[2 / 2] Writing decompressed overlays...")
    writeDecompressedOverlaysToROM(fh)
    print("Decompressed ROM created.")