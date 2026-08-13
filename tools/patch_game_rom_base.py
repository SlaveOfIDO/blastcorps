#!/usr/bin/env python3
"""Patches game's generated linker script (game/game.<version>.ld) to seed
its ROM position counter (__romPos) at game's real, absolute ROM base for
this build - init's declared start (0x1000) plus init's real compiled
size - instead of splat's default 0, so every _ROM_START/_ROM_END symbol
game's link produces comes out as an absolute ROM address (matching what
code like hd.c's DMA source computations expect), not relative to game's
own start.

Run from the content root, after init has been linked once with
tools/rzip_reloc_placeholder.init.txt purely to learn its real size (see
the root Makefile's init-size target) - that link's real size doesn't
depend on the placeholder values at all (see that file's own comment), so
it's already correct without knowing anything about game.

Idempotent: leaves the file (and its mtime) untouched if the computed
base already matches what's there, so an unrelated rebuild doesn't force
a needless relink of game.
"""

import os
import re
import sys

from rzip_config import computeGameRomBase

version = os.environ.get("VERSION")
if version is None:
    sys.exit("Error: VERSION environment variable is not set.")

init_bin_path = f"init/build/init.{version}.bin"
game_rom_base = computeGameRomBase(init_bin_path)

ld_path = f"game/game.{version}.ld"
with open(ld_path) as f:
    content = f.read()

current = re.search(r"__romPos = (\S+);", content)
if current is None:
    sys.exit(f"error: could not find '__romPos = ...;' in {ld_path}")

if int(current.group(1), 0) == game_rom_base:
    print(f"{ld_path}: __romPos already {hex(game_rom_base)}, leaving untouched")
else:
    patched = content[:current.start(1)] + hex(game_rom_base) + content[current.end(1):]
    with open(ld_path, "w") as f:
        f.write(patched)
    print(f"Patched {ld_path}: __romPos = {hex(game_rom_base)} (init size {hex(os.path.getsize(init_bin_path))})")
