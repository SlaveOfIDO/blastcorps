#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"

void func_hd_code_8027DA10(s32, s32, s32);                   /* extern */
void func_hd_code_802C1F30(s32, s32, s32, s32, s32);     /* extern */
f32 func_hd_code_8027DB5C(s32*, s32*, s32);             /* extern */
s16* func_hd_code_802C1EE0(s32);                     /* extern */
f32 func_hd_code_8027DD88(s32, s32, s32*, s32*);    /* extern */
s32 func_hd_code_8027E164(s32, s32, s32*, s32*);    /* extern */
f32 func_hd_code_8027E228(s32);                     /* extern */

extern s32 D_hd_code_803649E8;
extern s32 D_hd_code_802FC51C;

void func_hd_code_8027D810(s32 arg0) {
  switch (arg0) {
    case 0:
      func_hd_code_8027DA10(1, 7, 0x320000);
      break;
    case 4:
      func_hd_code_8027DA10(1, 7, 0xA00000);
      break;
    case 16:
      func_hd_code_8027DA10(1, 7, 0x3C0000);
      func_hd_code_8027DA10(2, 7, 0x3C0000);
      break;
    case 20:
      func_hd_code_8027DA10(1, 7, 0x820000);
      func_hd_code_8027DA10(2, 7, 0x820000);
      break;
    case 15:
      func_hd_code_8027DA10(1, 7, 0x410000);
      func_hd_code_8027DA10(2, 7, 0x410000);
      break;
  }
}

void func_hd_code_8027D8F4(s32 arg0, s32 arg1, s32 arg2) {
  s32 sp34;
  s32 sp30;
  f32 sp2C;
  f32 sp28;
  f32 sp24;

  sp30 = 1;
  sp2C = (6.28318 / (arg1 + 1));
  sp24 = (D_hd_code_802FC51C / 20.0);

  for (sp34 = D_hd_code_802FC51C; sp34 < (arg1 + D_hd_code_802FC51C); sp34++) {
    sp28 = sinf(sp24);
    func_hd_code_802C1F30(arg0, sp30++, 0, -sp28 * arg2, 0);
    sp24 += sp2C;
  }
  D_hd_code_802FC51C++;
}

void func_hd_code_8027DA10(s32 arg0, s32 arg1, s32 arg2) {
  f32 sp64;
  f32 sp60;
  f32 sp5C;
  s32 sp58;
  s16* sp54;
  s32 pad40[5];
  s32 sp30[4];
  s32 sp20[4];

  sp54 = func_hd_code_802C1EE0(arg0);
  for(sp58 = 0; sp58 < 4; sp58++) {
    sp30[sp58] = sp54[sp58 * 2] << 5;
    sp20[sp58] = sp54[sp58 * 2 + 1] << 5;
  }

  sp64 = func_hd_code_8027DB5C(sp30, sp20, arg2);
  sp5C = (f32) (3.14159 / (f64) (arg1 + 1));

  for(sp58 = 0; sp58 < arg1; sp58++) {
    sp60 = sinf((f32) (sp58 + 1) * sp5C);
    func_hd_code_802C1F30(arg0, sp58 + 1, 0, (s32) (-sp60 * sp64), 0);
  }
}

f32 func_hd_code_8027DB5C(s32* arg0, s32* arg1, s32 arg2) {
  s32 sp2C;
  f32 sp28;
  f32 sp24;
  f32 sp20;
  f32 sp1C;
  s32 sp18;

  sp2C = 0;
  sp28 = 0.0f;
  while (&D_hd_code_80364460[sp2C] != D_hd_code_803649D0) {
    sp18 = D_hd_code_80364460[sp2C].unk5C;
    if ((sp18 != 0xFE) && ((sp18 != 0) || (D_hd_code_803649E8 == 0))) {
      if (func_hd_code_8027E164(D_hd_code_80364460[sp2C].unk64, D_hd_code_80364460[sp2C].unk6C, arg0, arg1) != 0) {
        if (D_hd_code_80364460[sp2C].unk70 != 0) {
          sp1C = func_hd_code_8027DD88(D_hd_code_80364460[sp2C].unk64, D_hd_code_80364460[sp2C].unk6C, arg0, arg1);
          if (sp1C <= 0.5) {
            sp1C = (f32) (sp1C * 2.0);
          } else {
            sp1C = (f32) ((1.0 - (f64) sp1C) * 2.0);
          }
          sp20 = func_hd_code_8027E228(D_hd_code_80364460[sp2C].unk5C);
          sp24 = sp1C * sp20;
          if (sp28 < sp24) {
            sp28 = sp24;
          }
        }
      }
    }
    sp2C += 1;
  }
  return (f32) arg2 * sp28;
}

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_8027DD88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_8027E164.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_8027E228.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_8027E344.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_8027E9B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_8027EED8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_8027F1F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_802802D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_8028072C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_802807D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_80280F34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_80281A70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_80281CE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_80281E44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_802821D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_80282224.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_80282728.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_8028273C.s")
