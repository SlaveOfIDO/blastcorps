#!/usr/bin/env python3
"""Fix %gp_rel(...)/%hi(...)/%lo(...) macros spimdisasm leaves on $gp in
handwritten asm files.

Handwritten functions repurpose $gp as an ordinary scratch register --
used as a base for a run of addi/lb/lh/sb/sh accesses, as a plain temp
holding arbitrary values, even saved/restored across calls like any other
callee-clobbered register. It is never the real linker _gp: this project's
handwritten .s files are all compiled with -mno-abicalls -fno-PIC
-mno-shared -G 0 (see decompressed/Makefile's GCC_ASFLAGS/CFLAGS), which
rules out the compiler ever legitimately emitting GOT-relative or
small-data-relative code involving $gp. So every use of $gp here is
fair game, with no need to track whether it "looks like" a repurposed base.

spimdisasm doesn't know this and, whenever it sees `lui $gp, %hi(SYMBOL)` /
`addiu $gp, $gp, %lo(SYMBOL)`, treats $gp the normal way from then on:
offsets off of it get rendered as `%gp_rel(OTHER_SYMBOL)($gp)`, as if
OTHER_SYMBOL were meant to be relocated relative to a real small-data
section. That's not something we can actually assemble here, so it has to
be rewritten to a plain hex immediate. The same problem shows up in a few
shapes:

    lui   $gp, %hi(D_hd_code_803ED760)
    addiu $gp, $gp, %lo(D_hd_code_803ED760)      # $gp used as a scratch base
    sh    $t1, %gp_rel(D_hd_code_803ED7B2)($gp)  # offset off that base
    lw    $gp, %lo(D_hd_code_803ED760)($gp)      # dereference through it

Rather than recomputing the offset from symbol names (OTHER_SYMBOL's
address minus the address $gp was last loaded with), this script decodes
the actual instruction word already printed in the line's leading comment
-- that word is the final, linked machine code from the ROM, so its 16-bit
immediate field *is* the correct value, independent of whatever address
spimdisasm's heuristics happened to name the symbols with. This matters in
practice: spimdisasm has been observed to mislabel the %hi/%lo pair that
establishes a local $gp base (off by a few hundred bytes), which silently
produced wrong offsets under a name-arithmetic approach despite looking
plausible.
"""

import re
from pathlib import Path

try:
    import rabbitizer
except ImportError as exc:  # pragma: no cover
    raise SystemExit(
        "fix_gp_rel.py requires the 'rabbitizer' package to decode instruction "
        "words. It's already used by spimdisasm in this project's venv; if it's "
        "missing here, install it with `pip install rabbitizer` (not done "
        "automatically by this script)."
    ) from exc

REPO_ROOT = Path(__file__).resolve().parent.parent
SEARCH_ROOT = REPO_ROOT / "decompressed" / "src"

# Comment splat/spimdisasm print before every instruction:
#   /* <rom offset> <vram> <instruction word> */
WORD_RE = re.compile(r"/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s*\*/")
MNEMONIC_RE = re.compile(r"\*/\s*(\S+)")

# `lui $gp, %hi(SYM)`.
GP_HI_RE = re.compile(r"(lui\s+\$gp,\s*)%hi\([^()]+\)")
# `addiu $gp, $gp, %lo(SYM)` (the initial base load) or a later handwritten
# `addi $gp, $gp, %lo(SYM)` adjustment -- $gp redefined in terms of itself.
GP_LOCAL_RE = re.compile(r"(\$gp,\s*\$gp,\s*)%lo\([^()]+\)")
# `%gp_rel(SYM)($gp)` (or the bare 3-operand `addi $rd, $gp, %gp_rel(SYM)`
# form, with no trailing `($gp)`) -- an offset off of $gp.
GP_REL_RE = re.compile(r"%gp_rel\(([^()]+)\)(\(\$gp\))?")
# `%lo(SYM)($gp)` as a load/store offset, e.g. dereferencing through $gp
# right after computing it (`lw $gp, %lo(SYM)($gp)`) -- as opposed to the
# `$gp, $gp, %lo(SYM)` base-establishment shape GP_LOCAL_RE handles.
GP_LO_OFFSET_RE = re.compile(r"%lo\(([^()]+)\)(\(\$gp\))")


def format_offset(offset: int) -> str:
    return f"-0x{-offset:X}" if offset < 0 else f"0x{offset:X}"


def decode_instruction(line: str) -> "rabbitizer.Instruction":
    word_match = WORD_RE.search(line)
    if not word_match:
        raise ValueError(f"no instruction word comment found on line: {line!r}")
    return rabbitizer.Instruction(int(word_match.group(1), 16))


def decode_checked(path: Path, line: str, expected_mnemonics=None) -> "rabbitizer.Instruction":
    instr = decode_instruction(line)
    mnemonic_match = MNEMONIC_RE.search(line)
    written_mnemonic = mnemonic_match.group(1) if mnemonic_match else None
    decoded_mnemonic = instr.getOpcodeName()
    if written_mnemonic != decoded_mnemonic:
        raise ValueError(
            f"{path}: decoded mnemonic '{decoded_mnemonic}' doesn't match "
            f"written mnemonic '{written_mnemonic}': {line!r}"
        )
    if expected_mnemonics is not None and decoded_mnemonic not in expected_mnemonics:
        raise ValueError(
            f"{path}: expected one of {expected_mnemonics}, decoded "
            f"'{decoded_mnemonic}': {line!r}"
        )
    return instr


def fix_file(path: Path) -> int:
    lines = path.read_text().splitlines(keepends=True)

    fixed = 0

    def replace_gp_offset(match: re.Match, line: str) -> str:
        nonlocal fixed
        instr = decode_checked(path, line)
        offset = instr.getProcessedImmediate()
        gp_suffix = match.group(2)
        fixed += 1
        return f"{format_offset(offset)}{gp_suffix or ''}"

    def replace_gp_hi(match: re.Match, line: str) -> str:
        nonlocal fixed
        instr = decode_checked(path, line, {"lui"})
        fixed += 1
        return f"{match.group(1)}0x{instr.getImmediate():X}"

    def replace_gp_lo(match: re.Match, line: str) -> str:
        nonlocal fixed
        instr = decode_checked(path, line, {"addiu", "addi"})
        fixed += 1
        return f"{match.group(1)}0x{instr.getImmediate():X}"

    for i, line in enumerate(lines):
        new_line = line
        if "%gp_rel(" in new_line:
            new_line = GP_REL_RE.sub(lambda m: replace_gp_offset(m, line), new_line)
        if "%hi(" in new_line:
            new_line = GP_HI_RE.sub(lambda m: replace_gp_hi(m, line), new_line)
        if "%lo(" in new_line:
            new_line = GP_LOCAL_RE.sub(lambda m: replace_gp_lo(m, line), new_line)
            new_line = GP_LO_OFFSET_RE.sub(lambda m: replace_gp_offset(m, line), new_line)
        lines[i] = new_line

    path.write_text("".join(lines))
    return fixed


def needs_fix(text: str) -> bool:
    return (
        "%gp_rel(" in text
        or GP_LOCAL_RE.search(text) is not None
        or GP_HI_RE.search(text) is not None
        or GP_LO_OFFSET_RE.search(text) is not None
    )


def find_files_to_fix(root: Path):
    for path in sorted(root.rglob("*.s")):
        if needs_fix(path.read_text()):
            yield path


def main() -> None:
    for path in find_files_to_fix(SEARCH_ROOT):
        fixed = fix_file(path)
        print(f"{path.relative_to(REPO_ROOT)}: fixed {fixed} reference(s)")


if __name__ == "__main__":
    main()
