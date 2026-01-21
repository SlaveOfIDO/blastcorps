#!/usr/bin/env python3

from typing import BinaryIO
import gzip
import io
import shutil
import subprocess

source_file = 'build/blastcorps.us.v11.bin'
destination_file = 'build/blastcorps.us.v11.z64'

overlays = [
    {
        "name": "hd_code",
        "codeName": "hd_code_text.raw",
        "codeTimestamp": "124D0433",
        "codeROMAddress": 0x787FD0,
        "decompressedCodeROMAddress": 0x800000,

        "dataName": "hd_code_data.raw",
        "dataTimestamp": "134D0433",
        "dataROMAddress": 0x7D73B4,
        "dataCompressedSize": 0xC713, # - 8 for length without gzip footer
        "decompressedDataROMAddress": 0x8A4410,
        "dataDecompressedSize": 0x26A90, # - 8 for length without gzip footer
        # Note: These byte arrays should not contain the gzip footer
        # codeCompressedData: [], // Will be written to ROM
        # dataCompressedData: [], // Will be written to ROM directly after .code, regardless of the original .data address
    }
]

def readAndCompressOverlays(fr : BinaryIO):
    for x in overlays:
        # read in code segment
        fr.seek(x["decompressedCodeROMAddress"], io.SEEK_SET)
        print(f"    - Read {x['name']}.code decompressed from {hex(fr.tell())}")
        x["codeDecompressedData"] = fr.read(x['decompressedDataROMAddress'] - x['decompressedCodeROMAddress'])

        # write data to temporary file
        with open("build/" + x["codeName"], "wb") as f:
            f.write(x["codeDecompressedData"])

        # compress data with tools/gzip-1.2.4/gzip by starting subprocess
        x["codeCompressedData"] = subprocess.check_output(["tools/gzip-1.2.4/gzip", "-f", "-c", "build/" + x["codeName"]])

        # write codeCompressedData to codeROMAddress
        fr.seek(x["codeROMAddress"], io.SEEK_SET)
        fr.write(x["codeCompressedData"])
        fr.seek(x["codeROMAddress"]+4, io.SEEK_SET)
        fr.write(bytes.fromhex(x["codeTimestamp"]))






        # read in data segment
        fr.seek(x["decompressedDataROMAddress"], io.SEEK_SET)
        print(f"    - Read {x['name']}.data decompressed from {hex(fr.tell())}")
        x["dataDecompressedData"] = fr.read(x['dataDecompressedSize'])

        # write data to temporary file
        with open("build/" + x["dataName"], "wb") as f:
            f.write(x["dataDecompressedData"])

        # compress data with tools/gzip-1.2.4/gzip by starting subprocess
        x["dataCompressedData"] = subprocess.check_output(["tools/gzip-1.2.4/gzip", "-f", "-c", "build/" + x["dataName"]])

        # write codeCompressedData to codeROMAddress
        fr.seek(x["dataROMAddress"], io.SEEK_SET)
        fr.write(x["dataCompressedData"])
        fr.seek(x["dataROMAddress"]+4, io.SEEK_SET)
        fr.write(bytes.fromhex(x["dataTimestamp"]))



# Make a copy of the baseROM to be used as the decompressed baseROM
shutil.copyfile(source_file, destination_file)

whole_rom = None

# Open the decompressed ROM
with open(destination_file, "r+b") as fh:
    # Decompress all code and data segments
    print("[1/2] Compressing overlays...")
    readAndCompressOverlays(fh)

    fh.seek(0, io.SEEK_SET)
    whole_rom = fh.read(0x800000)

print("[2/2] Removing decompressed overlays...")
with open(destination_file, "wb") as f:
    f.write(whole_rom)

