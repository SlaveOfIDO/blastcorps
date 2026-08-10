#!/usr/bin/env python3
"""Recompute and patch the N64 ROM header CRC1/CRC2 checksum in place.

Uses the CIC-NUS-6102 checksum algorithm (verified against baserom.us.v10,
baserom.us.v11, baserom.eu and baserom.jp), which is what Blast Corps boots
with. A NON_MATCHING build changes bytes inside the checksummed range, so the
checksum baked in by the original game no longer matches and real hardware /
accurate emulators refuse to boot the ROM.
"""

import argparse

CHECKSUM_START = 0x1000
CHECKSUM_LENGTH = 0x100000
SEED_6102 = 0xF8CA4DDC
MASK = 0xFFFFFFFF


def rol(value, bits):
    bits &= 0x1F
    value &= MASK
    return ((value << bits) | (value >> (32 - bits))) & MASK


def calc_checksum(data, seed=SEED_6102):
    t1 = t2 = t3 = t4 = t5 = t6 = seed
    for i in range(CHECKSUM_START, CHECKSUM_START + CHECKSUM_LENGTH, 4):
        d = int.from_bytes(data[i:i + 4], "big")
        if (t6 + d) & MASK < t6:
            t4 = (t4 + 1) & MASK
        t6 = (t6 + d) & MASK
        t3 ^= d
        r = rol(d, d & 0x1F)
        t5 = (t5 + r) & MASK
        if t2 > d:
            t2 ^= r
        else:
            t2 = (t2 ^ (t6 ^ d)) & MASK
        t1 = (t1 + (t5 ^ d)) & MASK

    crc1 = (t6 ^ t4 ^ t3) & MASK
    crc2 = (t5 ^ t2 ^ t1) & MASK
    return crc1, crc2


def fix_checksum(path):
    with open(path, "r+b") as f:
        data = f.read(CHECKSUM_START + CHECKSUM_LENGTH)
        if len(data) < CHECKSUM_START + CHECKSUM_LENGTH:
            raise ValueError(f"{path} is smaller than expected for checksumming")

        crc1, crc2 = calc_checksum(data)

        f.seek(0x10)
        f.write(crc1.to_bytes(4, "big"))
        f.write(crc2.to_bytes(4, "big"))

    print(f"Patched checksum for {path}: CRC1={crc1:08X} CRC2={crc2:08X}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("rom", help="Path to the built .z64 ROM to patch in place")
    args = parser.parse_args()
    fix_checksum(args.rom)
