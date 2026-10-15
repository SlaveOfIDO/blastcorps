#!/usr/bin/env python3

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
