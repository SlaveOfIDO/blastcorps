#include "common.h"
#include "variables.h"
#include "functions.h"
#include "structs.h"

void func_hd_code_802A0B00(u16, u8*);                  /* extern */
void func_hd_code_802A0EE0(u16, u8*);                  /* extern */

extern u8* D_8036BFE0[][2];
extern u8 D_8036C1E0[];
extern u8 D_8036C220[];
extern f32 D_8036C260[];
extern u8 D_8036C360;
extern u8* D_8036C368[][64][2];

void func_hd_code_80272C50(void) {
  D_8036C360 = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/2E490/func_hd_code_80272C5C.s")
/*
u8 func_hd_code_80272C5C(u16* arg0, u16* arg1, u8 arg2, u8 arg3, u8 arg4, f32 arg5) {
  u8* sp3C;
  s32 sp38;
  s32 sp34;
  s32 sp30;
  s32 sp2C;
  s32 sp28;

  sp28 = D_8036C360;
  if (D_hd_code_803B9888 == 0) {
    func_hd_code_802A0700();
  }
  sp2C = 0;
  for(sp38 = sp28; sp38 < arg2 + sp28; sp38++, sp2C += (arg1 != 0) ? 0 : 1) {
    if (arg1 != 0) {
      func_hd_code_80257490(&D_hd_code_80358070, 0x10);
      func_hd_code_802A0EE0(arg1[sp38 - sp28], sp3C = D_hd_code_80358070);
      D_hd_code_80358070 += 0x80;
    } else {
      func_hd_code_80257490(&D_hd_code_80358070, 0x10);
      sp3C = NULL;
    }
    for(sp34 = 0; sp34 < arg3; sp34++) {
      D_8036BFE0[sp38][sp34] = D_hd_code_80358070;
      func_hd_code_802A0B00(arg0[arg3 * sp2C + sp34], sp3C);
    }

    D_8036C1E0[sp38] = (u8) arg3;
    D_8036C220[sp38] = (u8) arg4;
    if ((u8) arg4 & 4) {
      for(sp34 = 0; sp34 < 2; sp34++) {
        for(sp30 = 0; sp30 < 2; sp30++) {
          D_8036C368[sp34][sp38][sp30] = D_hd_code_80358070;
          D_hd_code_80358070 += 0x80;
        }
      }
    }
    D_8036C260[sp38] = arg5;
  }

  D_8036C360 = sp38;
  return sp28;
}
*/
#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/2E490/func_hd_code_80272ED8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/2E490/func_hd_code_802742D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/2E490/func_hd_code_80274868.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/2E490/func_hd_code_80274998.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/2E490/func_hd_code_80274AA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/2E490/func_hd_code_80274B08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/2E490/func_hd_code_80274B40.s")
