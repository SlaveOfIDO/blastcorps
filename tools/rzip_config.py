#!/usr/bin/env python3
"""Shared loader for rzip.config.json, used by decompress_rom.py and compress_rom.py.

The config maps a version key (us.v11, us.v10, eu, jp) to the list of gzip
compressed overlays in that ROM. The version is selected via the VERSION
environment variable. Fields ending in "Address" or "Size" are hex strings.
"""

import json
import os
import sys

CONFIG_FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)), "rzip.config.json")

NEXT_AVAILABLE_FREE_SPACE = 0x800000


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


def computeDecompressedROMAddresses(overlays):
    """Mirror the layout written by decompress_rom.py: segments appended at
    NEXT_AVAILABLE_FREE_SPACE, each aligned to 0x10 bytes."""
    position = NEXT_AVAILABLE_FREE_SPACE
    for x in overlays:
        position = align16(position)
        x["decompressedCodeROMAddress"] = position
        position += x["codeDecompressedSize"]
        position = align16(position)
        x["decompressedDataROMAddress"] = position
        position += x["dataDecompressedSize"]
