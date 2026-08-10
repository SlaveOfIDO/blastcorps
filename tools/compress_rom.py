#!/usr/bin/env python3
"""Injects the compressed overlays (computed ahead of linking by
compute_rzip_reloc.py, see build/rzip_layout.json) into the final linked
ROM, fills the freed-up space with 0xFF, and drops the appended decompressed
overlay data used only for building.
"""

from typing import BinaryIO
import io
import json
import shutil

from rzip_config import loadOverlays

ROM_SIZE = 0x800000
LAYOUT_SIDECAR = "build/rzip_layout.json"


def writeCompressedOverlays(fr : BinaryIO, layout):
    for x in layout["overlays"]:
        with open("build/" + x["codeName"] + ".gz", "rb") as f:
            codeCompressedData = f.read()
        with open("build/" + x["dataName"] + ".gz", "rb") as f:
            dataCompressedData = f.read()

        fr.seek(x["codeROMAddress"], io.SEEK_SET)
        fr.write(codeCompressedData)
        fr.seek(x["dataROMAddress"], io.SEEK_SET)
        fr.write(dataCompressedData)


version, _ = loadOverlays()

with open(LAYOUT_SIDECAR) as f:
    layout = json.load(f)

source_file = f"build/blastcorps.{version}.bin"
destination_file = f"build/blastcorps.{version}.z64"
print(f"Compressing ROM for version '{version}'")

# Make a copy of the built ROM to be used as the compressed ROM
shutil.copyfile(source_file, destination_file)

# Open the compressed ROM
with open(destination_file, "r+b") as fh:
    print("[1/2] Writing compressed overlays...")
    writeCompressedOverlays(fh, layout)

    endAddress = layout["endAddress"]
    if endAddress < ROM_SIZE:
        print(f"    - Filling {hex(endAddress)}-{hex(ROM_SIZE)} with 0xFF")
        fh.seek(endAddress, io.SEEK_SET)
        fh.write(b"\xFF" * (ROM_SIZE - endAddress))
    else:
        print(f"    - Compressed overlays extend to {hex(endAddress)}, not filling")

    fh.seek(0, io.SEEK_SET)
    whole_rom = fh.read(ROM_SIZE)

print("[2/2] Removing decompressed overlays...")
with open(destination_file, "wb") as f:
    f.write(whole_rom)
