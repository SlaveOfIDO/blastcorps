#!/usr/bin/env python3

import json
import os

directories = [["init", ""], ["decompressed", "decompressed"]]

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

                # hd_code/src/hd_code/00000.s|c -> hd_code/build/src/hd_code/00000.s|c.o
                # src/init/rarezip.s|c -> build/src/init/rarezip.s|c.o
                base_path = source_path.replace(src_path.replace('asm', 'src'), os.path.join(directory, "build/src"), 1) + '.o'
                if not os.path.exists(base_path):
                    base_path = None
                # hd_code/src/hd_code/00000.c -> hd_code/build/asm/hd_code/00000.s.o
                # src/init/rarezip.c -> build/asm/init/rarezip.s.o
                target_path = asm_path.replace(src_path, os.path.join(directory, "build/asm"), 1).replace(".s", ".s.o")

                # Categorize by which segment the file belongs to, falling
                # back to the top-level directory category (e.g. "init").
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
                data["units"].append(unit)

with open("objdiff.json", "w") as f:
    json.dump(data, f, indent=4)