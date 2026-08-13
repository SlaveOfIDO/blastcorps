#!/usr/bin/env python3
"""Shared loader for rzip.config.json, used by decompress_rom.py and compress_rom.py.

The config maps a version key (us.v11, us.v10, eu, jp) to the list of gzip
compressed overlays in that ROM. The version is selected via the VERSION
environment variable. Fields ending in "Address" or "Size" are hex strings.
"""

import json
import os
import subprocess
import sys
from typing import Optional

CONFIG_FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)), "rzip.config.json")

NEXT_AVAILABLE_FREE_SPACE = 0x800000
NM = "mips-linux-gnu-nm"


def readSymbol(elfPath, symbolName) -> Optional[int]:
    """Reads an absolute symbol's value straight out of a linked ELF via nm,
    or None if the ELF or symbol doesn't exist (yet). Masked to 32 bits:
    nm sign-extends addresses with bit 31 set (e.g. VRAM addresses) out to
    16 hex digits, since it formats values at the BFD target's word size,
    not this o32 MIPS binary's actual 32-bit address space."""
    if not os.path.exists(elfPath):
        return None
    try:
        output = subprocess.check_output([NM, elfPath], text=True)
    except (subprocess.CalledProcessError, OSError):
        return None
    for line in output.splitlines():
        parts = line.split()
        if len(parts) == 3 and parts[2] == symbolName:
            return int(parts[0], 16) & 0xFFFFFFFF
    return None


def loadOverlays():
    with open(CONFIG_FILE, "r") as fh:
        configs = json.load(fh)

    version = os.environ.get("VERSION")
    if version is None:
        sys.exit(f"Error: VERSION environment variable is not set. Available versions: {', '.join(configs)}")
    if version not in configs:
        sys.exit(f"Error: Unknown VERSION '{version}'. Available versions: {', '.join(configs)}")

    overlays = configs[version]
    for overlay in overlays:
        for key, value in overlay.items():
            if key.endswith("Address") or key.endswith("Size"):
                overlay[key] = int(value, 16)
    return version, overlays


def align16(position):
    return (position + 0xF) & ~0xF


def readOverlayLayout(elfPath, name):
    """name's real decompressed start position and total (code+data) size,
    read straight out of a linked ELF's own <name>_ROM_START/_ROM_END
    symbols, or None if either is missing (elf doesn't exist yet, or
    predates this overlay being linked).

    Deliberately NOT using <name>_TEXT_START/_DATA_START/_DATA_END to find
    where "code" ends and "data" begins: those don't mark a clean boundary
    in this .ld script (splat interleaves .data from one object file among
    other objects' .text, by original address order), so they don't
    correspond to the code/data split rzip.config.json's
    codeDecompressedSize actually describes. ROM_START/ROM_END don't have
    that problem - they're just the section's real overall bounds."""
    romStart = readSymbol(elfPath, f"{name}_ROM_START")
    romEnd = readSymbol(elfPath, f"{name}_ROM_END")
    if romStart is None or romEnd is None:
        return None
    return {"decompressedCodeROMAddress": romStart, "realTotalDecompressedSize": romEnd - romStart}


def computeDecompressedROMAddresses(overlays, elfPath=None):
    """Mirror the layout written by decompress_rom.py: segments appended at
    NEXT_AVAILABLE_FREE_SPACE, each aligned to 0x10 bytes, using
    rzip.config.json's hardcoded original sizes - the correct layout only
    when nothing has compiled to a different size than the original ROM's
    (a matching build).

    If elfPath is given and a previous link exists, each overlay's real
    start position and total size are instead read back out of its own
    linker-tracked ROM_START/ROM_END symbols (see readOverlayLayout),
    overriding the accumulated guess. This matters even for overlays whose
    own ROM position hasn't drifted: accumulating hd_code's hardcoded size
    to find hd_front_end's position has no way to see that hd_code's own
    compiled size (not just its position) drifted under NON_MATCHING,
    which silently shifts where hd_front_end's real decompressed bytes are
    read from.

    codeDecompressedSize (the code/data gzip-member split point) is left
    as rzip.config.json's original fixed byte count in both cases: the
    runtime inflate loop doesn't care where that split falls, since each
    gzip member is self-describing and decompressing them in order
    reproduces the overlay's full content regardless - so keeping the
    original split point is what keeps a matching build's compressed
    bytes byte-identical to retail. Only dataDecompressedSize (the
    remainder) is adjusted to absorb any real drift in the overlay's total
    size, wherever in the content that drift actually happened."""
    position = NEXT_AVAILABLE_FREE_SPACE
    for x in overlays:
        real = readOverlayLayout(elfPath, x["name"]) if elfPath else None
        if real is not None:
            x["decompressedCodeROMAddress"] = real["decompressedCodeROMAddress"]
            x["decompressedDataROMAddress"] = x["decompressedCodeROMAddress"] + x["codeDecompressedSize"]
            x["dataDecompressedSize"] = real["realTotalDecompressedSize"] - x["codeDecompressedSize"]
            continue
        position = align16(position)
        x["decompressedCodeROMAddress"] = position
        position += x["codeDecompressedSize"]
        position = align16(position)
        x["decompressedDataROMAddress"] = position
        position += x["dataDecompressedSize"]
