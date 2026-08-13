#!/usr/bin/env python3
"""Generates a small, standalone linker script for a preliminary
hd_code/hd_front_end-only link, by slicing the .hd_code/.hd_front_end
SECTIONS out of the real, already-generated main linker script.

This exists to learn hd_code/hd_front_end's actual compiled size/content
before init/ links (init/'s NON_MATCHING=1 code references the compressed
overlay's real ROM position directly - see compute_rzip_reloc.py). Slicing
from the real .ld instead of maintaining a second yaml/splat config for
this means there's exactly one place hd_code/hd_front_end's structure is
declared (blastcorps.us.v11.yaml) - nothing here can drift out of sync
with it.

Relies on splat always resetting __romPos to 0 at the top of any SECTIONS
block it writes, regardless of the yaml's declared "start:" address - so
lifting the .hd_code/.hd_front_end blocks out of the real script (where
__romPos has already accumulated to 0x800000 by the time it reaches them)
and wrapping them in a fresh SECTIONS block makes hd_code_ROM_START come
out as 0 again, exactly like a dedicated from-scratch splat config would.
"""
import sys

START_MARKER = "hd_code_ROM_START = __romPos;"
END_MARKER = "hd_front_end_VRAM_END = .;"


def main():
    if len(sys.argv) != 3:
        sys.exit(f"usage: {sys.argv[0]} <main.ld> <output.ld>")
    main_ld_path, out_path = sys.argv[1], sys.argv[2]

    lines = open(main_ld_path).read().splitlines()

    start = next((i for i, l in enumerate(lines) if START_MARKER in l), None)
    end = next((i for i, l in enumerate(lines) if END_MARKER in l), None)
    if start is None or end is None:
        sys.exit(f"error: could not find hd_code/hd_front_end block markers in {main_ld_path}")

    body = lines[start:end + 1]

    with open(out_path, "w") as f:
        f.write("SECTIONS\n{\n    __romPos = 0;\n")
        f.write("\n".join(body))
        f.write("\n}\n")

    print(f"    - Wrote {out_path}")


if __name__ == "__main__":
    main()
