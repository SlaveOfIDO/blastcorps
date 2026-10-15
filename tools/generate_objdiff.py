#!/usr/bin/env python3

import json
import os

directories = [["init", "init"], ["game", "game"]]

EXCLUDED_UNITS = {
    "game/src/data/hd_code/f3d",
    "game/src/data/hd_code/asp",
    "game/src/data/hd_code/rspboot",
    "game/src/hd_code/68810",
    "game/src/data/hd_code/68810.data",
    "game/src/hd_code/gu/cosf",
    "game/src/hd_code/gu/sinf",
}

FORCE_COMPLETE_UNITS = {
    "game/src/hd_code/audio/csplayer",
    "game/src/hd_code/audio/seqplayer",
    "game/src/hd_code/libc/xprintf",
    "game/src/hd_code/libc/xldtob",
    "game/src/hd_code/audio/reverb",
    "game/src/hd_code/audio/load",
    "game/src/hd_code/audio/env",
    "game/src/hd_code/debug/kdebugserver",
    "game/src/hd_code/io/vimgr",
    "game/src/hd_code/audio/cseq",
    "game/src/hd_code/io/sptask",
    "game/src/hd_code/audio/bnkf",
    "game/src/hd_code/io/contreaddata",
    "game/src/hd_code/audio/seq",
    "game/src/hd_code/audio/drvrNew",
    "game/src/hd_code/io/sptaskyielded",
    "game/src/hd_code/libc/sprintf",
    "game/src/hd_code/audio/synthesizer",
    "game/src/hd_code/audio/cspgetstate",
}


def has_global_asm_pragma(source_path):
    if not source_path.endswith(".c") or not os.path.exists(source_path):
        return False
    with open(source_path) as f:
        return "#pragma GLOBAL_ASM" in f.read()

data = {
    "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
    "units": []
}


for category, directory in directories:
    src_path = os.path.join(directory, "asm") # hd_code/asm
    for root, dirs, files in os.walk(src_path):
        for file in files:
            asm_path = os.path.join(root, file) # hd_code/asm/hd_code/00000.s
            if file.endswith(".s") and not file.endswith("rsp.s") and "nonmatchings" not in asm_path:

                source_path = asm_path.replace('asm', 'src').replace('.s', '.c') # hd_code/src/hd_code/00000.c
                if not os.path.exists(source_path):
                    source_path = asm_path.replace('asm', 'src') # hd_code/src/hd_code/00000.s
                name = os.path.splitext(source_path)[0] # hd_code/src/hd_code/00000
                if name in EXCLUDED_UNITS or has_global_asm_pragma(source_path):
                    continue

                # hd_code/src/hd_code/00000.s|c -> hd_code/build/src/hd_code/00000.s|c.o
                # src/init/rarezip.s|c -> build/src/init/rarezip.s|c.o
                base_path = source_path.replace(src_path.replace('asm', 'src'), os.path.join(directory, "build/src"), 1) + '.o'
                if not os.path.exists(base_path):
                    base_path = None
                # hd_code/src/hd_code/00000.c -> hd_code/build/asm/hd_code/00000.s.o
                # src/init/rarezip.c -> build/asm/init/rarezip.s.o
                target_path = asm_path.replace(src_path, os.path.join(directory, "build/asm"), 1).replace(".s", ".s.o")

                if "hd_front_end" in asm_path:
                    progress_category = "hd_front_end"
                elif "hd_code" in asm_path:
                    progress_category = "hd_code"
                else:
                    progress_category = category

                unit = {
                    "name": name,
                    "base_path": base_path,
                    "target_path": target_path,
                    "metadata": {
                        "source_path": source_path,
                        "progress_categories": [ progress_category ]
                    }
                }
                if name in FORCE_COMPLETE_UNITS:
                    unit["complete"] = True
                data["units"].append(unit)

with open("objdiff.json", "w") as f:
    json.dump(data, f, indent=4)