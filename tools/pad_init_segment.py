#!/usr/bin/env python3
"""Pad the .init segment's ROM footprint in the splat-generated linker
script back up to the size the original ROM's segment layout expects.

splat's generated blastcorps.$(VERSION).decompressed.ld places every
segment after .init sequentially, driven by __romPos (a running ROM byte
offset), rather than pinning each one to a fixed address. That's harmless
for a byte-matching build, but AVOID_ASM=1 recompiles some still-
nonmatching functions with plain C instead of linking their matching
handwritten .s files, and the compiled size doesn't necessarily match the
original. When .init comes out smaller, every segment/symbol placed after
it (blast_offsets, blast_textures, the hd_code/hd_front_end gzip overlays,
...) shifts earlier - but compress_rom.py/rzip.config.json still target the
ORIGINAL fixed ROM addresses when writing the recompressed overlays back
into the final .z64. That mismatches the DMA source addresses compiled
into init/*.c (_787FD0_ROM_START etc, both derived from __romPos), which
then read garbage instead of the real compressed data.

Forcing __romPos back up to at least the original boundary right after
.init keeps every downstream __romPos-derived symbol lined up with where
compress_rom.py actually puts things. This only helps when .init comes out
SMALLER than budget - if it ever needs more space than the original ROM
gave it, this is a no-op and the same mismatch reappears (shifted forward
instead of backward).

splat regenerates the .ld file on every `splat split`, so this can't be a
one-off hand-edit to the .ld itself; `make extract` re-applies it via this
script after every extraction instead.
"""
import os
import sys
from pathlib import Path

import yaml

REPO_ROOT = Path(__file__).resolve().parent.parent


def find_init_padding_target(version: str) -> int:
    yaml_path = REPO_ROOT / f"blastcorps.{version}.yaml"
    with open(yaml_path) as fh:
        config = yaml.safe_load(fh)

    segments = config["segments"]
    init_index = next(
        (i for i, seg in enumerate(segments) if isinstance(seg, dict) and seg.get("name") == "init"),
        None,
    )
    if init_index is None:
        sys.exit(f"Error: couldn't find the 'init' segment in {yaml_path}")
    if init_index + 1 >= len(segments):
        sys.exit(f"Error: 'init' is the last segment in {yaml_path}, nothing follows it to pad up to")

    next_seg = segments[init_index + 1]
    start = next_seg[0] if isinstance(next_seg, list) else next_seg["start"]
    return start if isinstance(start, int) else int(start, 0)


def patch_ld(version: str, target: int) -> None:
    ld_path = REPO_ROOT / f"blastcorps.{version}.decompressed.ld"
    text = ld_path.read_text()

    marker = "__romPos = MAX(__romPos, "
    if marker in text:
        print(f"{ld_path.name}: init padding already present, leaving as-is")
        return

    anchor = "    init_ROM_END = __romPos;"
    if anchor not in text:
        sys.exit(f"Error: couldn't find '{anchor.strip()}' in {ld_path} - has splat's output format changed?")

    patch = (
        "    # Inserted by tools/pad_init_segment.py (see that file for why):\n"
        "    # keep every __romPos-derived symbol after .init lined up with\n"
        "    # the original ROM layout even if .init's compiled size shrinks.\n"
        f"    __romPos = MAX(__romPos, {hex(target)});\n"
    )
    text = text.replace(anchor, patch + anchor, 1)
    ld_path.write_text(text)
    print(f"{ld_path.name}: padded .init's ROM footprint up to {hex(target)}")


if __name__ == "__main__":
    version = os.environ.get("VERSION")
    if not version:
        sys.exit("Error: VERSION environment variable is not set")
    target = find_init_padding_target(version)
    patch_ld(version, target)
