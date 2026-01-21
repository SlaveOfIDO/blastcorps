#include "common.h"

extern u8 D_80365360[];
extern u16 D_803653B0[];

void func_hd_code_8025B070(void) {
  s32 sp4;
  for(sp4 = 0; sp4 < 0x50; sp4++) {
    D_80365360[sp4] = 0;
    D_803653B0[sp4] = 0;
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/168B0/func_hd_code_8025B0B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/168B0/func_hd_code_8025B2B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/168B0/func_hd_code_8025B300.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/168B0/func_hd_code_8025B370.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/168B0/func_hd_code_8025B3F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/168B0/func_hd_code_8025B498.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/168B0/func_hd_code_8025B558.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/168B0/func_hd_code_8025B5D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/168B0/func_hd_code_8025B7AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/168B0/func_hd_code_8025B918.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/168B0/func_hd_code_8025B9D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/168B0/func_hd_code_8025BB38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/168B0/func_hd_code_8025BB50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/168B0/func_hd_code_8025BBE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/168B0/func_hd_code_8025BD98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/168B0/func_hd_code_8025BEF8.s")
