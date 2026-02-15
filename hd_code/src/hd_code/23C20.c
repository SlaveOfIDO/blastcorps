#include "common.h"
#include "variables.h"
#include "functions.h"
#include "structs.h"

f32 func_hd_code_80268D84(f32, f32, f32, f32, f32, f32, f32); /* extern */
extern u8 D_8036B8C0;
extern s32 D_8036B908;
extern u8 D_8036B90C;

extern f32 D_8036B8C8[4][4];
struct S_802F3C24 {
  s32 unk0;
  f32 unk4;
  f32 unk8;
};
extern struct S_802F3C24 D_hd_code_802F3C24[];

struct S_802F3C2C {
  u8 unk0;
  s32 pad4;
  s32 pad8;
}; // size: 0xC
extern struct S_802F3C2C D_hd_code_802F3C2C[];

struct S_802F3C48 {
  s32 unk0;
  u8 unk4;
  u8 pad5;
  s16 unk6;
  s16 unk8;
  s16 unkA;
  u8 unkC;
  u8 padD[3];
}; // size: 0x10
extern struct S_802F3C48 D_hd_code_802F3C48[];


f32 func_hd_code_8026A184(f32, f32, f32, f32, f32, f32, f32); /* extern */
void func_hd_code_8026A2E8(f32, f32*);                 /* extern */
extern s32 D_80364A94;
extern s32 D_8036B950;
extern u8 D_8036B954;
extern u8 D_8036B955;
extern u8 D_8036B958[];
extern u8 D_8036B95C;
extern u8 D_8036B960[4];
extern s8 D_8036B964;
extern u8 D_8036B966;
extern s16 D_803FCD6A;
extern s16 D_803FCD6C;
extern s16 D_803FCD6E;
extern u8 D_803FCD70;
extern u8 D_803FCD75;
struct S_802F41F0 {
  s32 unk0;
  u8 unk4;
  u8 pad5;
  s16 unk6;
  f32 unk8;
  s16 unkC;
  s16 unkE;
  u8 unk10;
  u8 unk11;
  u8 unk12;
  u8 unk13;
}; // size: 0x14
extern struct S_802F41F0 D_hd_code_802F41E8[]; // +0x8

struct S_802F4224 {
  s32 unk0;
  u8 unk4;
  u8 unk5;
  s16 unk6;
  s16 unk8;
  s16 unkA;
  s16 unkC;
  s16 unkE;
  s16 unk10;
  u8 unk12;
  u8 unk13;
  u8 unk14;
  u8 pad15;
  u8 pad16;
  u8 pad17;
}; // size: 0x18
extern struct S_802F4224 D_hd_code_802F4224[];
extern s32 D_hd_code_80303AF4;
extern s32 D_hd_code_80303B00;
extern s32 D_hd_code_80303B10;
extern s32 D_hd_code_80303B24;
s32 func_hd_code_8026A6F0(s32, s32, s32, s32, s32, s32); /* extern */
s32 func_hd_code_802AB3C0(s32);                     /* extern */
extern u8 D_8036B970;
extern u8 D_8036B971;
extern u8 D_8036B978;
extern u8 D_8036B979;
extern u8 D_8036C7CC;
extern u8 D_803EFECB;
extern f32 D_8036B910[4][4];
extern s32 D_803FCD60;
extern u8 D_803ED826;
struct S_802F3C10 {
  u8 unk0;
  u8 unk1;
  s16 unk2;
  s16 unk4;
  s16 unk6;
  s16 unk8;
  s16 unkA;
  s16 unkC;
  s16 unkE;
  s16 unk10;
  s16 unk12;
};
extern struct S_802F3C10 D_hd_code_802F3C10[];


void func_hd_code_802683E0(void) {
  s32 sp3C;
  u8 sp3B;
  u8 sp3A;
  struct UnknownStruct_803644BC* sp34;

  sp3C = 0;
  sp3B = 0;

  if (D_hd_code_80364456 != 0 || D_803ED826 != 0) {
    return;
  }

  while(!sp3B && (sp3C <= 0)) {
    if (D_hd_code_802F3C10[sp3C].unk0 == levelno) {
      sp34 = D_80364460;
      sp3A = 0;
      while((sp3A == 0) && (D_803649D0 != sp34)) {
        if (D_hd_code_802F3C10[sp3C].unk1 == sp34->unk5C) {
          sp3A = 1;
        } else {
          sp34++;
        }
      }
      if ((sp3A != 0) && (((func_hd_code_802AC4C4((s32) sp34->unk64 >> 5, (s32) sp34->unk6C >> 5, (s32) D_hd_code_802F3C10[sp3C].unk2, (s32) D_hd_code_802F3C10[sp3C].unk4, (s32) D_hd_code_802F3C10[sp3C].unk6, (s32) D_hd_code_802F3C10[sp3C].unk8, (s32) D_hd_code_802F3C10[sp3C].unkA, (s32) D_hd_code_802F3C10[sp3C].unkC) != 0)) || ((func_hd_code_802AC4C4((s32) sp34->unk64 >> 5, (s32) sp34->unk6C >> 5, (s32) D_hd_code_802F3C10[sp3C].unk2, (s32) D_hd_code_802F3C10[sp3C].unk4, (s32) D_hd_code_802F3C10[sp3C].unkA, (s32) D_hd_code_802F3C10[sp3C].unkC, (s32) D_hd_code_802F3C10[sp3C].unkE, (s32) D_hd_code_802F3C10[sp3C].unk10) != 0)))) {
        if (func_hd_code_8026A6F0(sp34->unk64, sp34->unk68, sp34->unk6C, D_hd_code_803643E0, D_hd_code_803643E4, D_hd_code_803643E8) < D_hd_code_802F3C10[sp3C].unk12) {
          D_803649ED = D_hd_code_802F3C10[sp3C].unk1;
          sp3B = 1;
        }
      }
    }
    sp3C += 1;
  }
}

void func_hd_code_80268664(s32 arg0) {
  f32 sp4;
  f32 temp_f4;

  D_8036B8B0 = 0;
  D_8036B8C0 = 0;
  loop_1:
      if (D_hd_code_802F3C24[D_8036B8C0].unk0 == arg0) {
        D_8036B8B0 = 1;
      } else {
        D_8036B8C0 += 1;
      }
  if (((s32) D_8036B8C0 < 3) && (D_8036B8B0 == 0)) {
    goto loop_1;
  }
  if (D_8036B8B0 != 0) {
    sp4 = D_hd_code_802F3C24[D_8036B8C0].unk4;
    D_8036B8C8[0][0] = -sp4;
    D_8036B8C8[0][1] = (sp4 * 2.0);
    D_8036B8C8[0][2] = -sp4;
    D_8036B8C8[0][3] = 0.0f;
    D_8036B8C8[1][0] = (2.0 - sp4);
    D_8036B8C8[1][1] = (sp4 - 3.0);
    D_8036B8C8[1][2] = 0.0f;
    D_8036B8C8[1][3] = 1.0f;
    D_8036B8C8[2][0] = (sp4 - 2.0);
    D_8036B8C8[2][1] = (3.0 - (sp4 * 2.0));
    D_8036B8C8[2][2] = sp4;
    D_8036B8C8[2][3] = 0.0f;
    D_8036B8C8[3][0] = sp4;
    D_8036B8C8[3][1] = -sp4;
    D_8036B8C8[3][2] = 0.0f;
    D_8036B8C8[3][3] = 0.0f;
    D_8036B908 = 0;
    D_8036B90C = 1;
  }
}

void func_hd_code_802688C4(s32 arg0) {
    s32 sp54;
    s32 sp50;
    u8 sp4C[4];
    u8 sp48[4];
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    s32 pad2C[4];
    u8 sp2B;

    if (D_8036B8B0 != 0) {
        sp48[0] = D_8036B90C - 1;
        sp48[1] = D_8036B90C;
        sp48[2] = D_8036B90C + 1;
        sp48[3]=  D_8036B90C + 2;
        for(sp54 = 0; sp54 < 4; sp54++) {
            sp50 = 0;
            sp2B = 0;
            while(((sp50 < 0x5A) && (sp2B == 0))) {
                if (D_hd_code_802F3C48[sp50].unk0 == arg0 && D_hd_code_802F3C48[sp50].unk4 == sp48[sp54]) {
                    sp2B = 1;
                } else {
                    sp50 += 1;
                }
            }
            if (sp2B == 0) {
                func_hd_code_8029A7E4("\n --- ASSERTION FAULT - %s - %s, line %d\n\n", "found", "utils2.c", 0xB5);
            }
            sp4C[sp54] = sp50;
        }
        sp44 = (f32) ((f64) (f32) D_8036B908 / 1000.0);
        sp40 = sp44 * sp44;
        sp3C = sp40 * sp44;
        D_8036B8B4 = (s32) func_hd_code_80268D84(D_hd_code_802F3C48[sp4C[0]].unk6 << 5, D_hd_code_802F3C48[sp4C[1]].unk6 << 5, D_hd_code_802F3C48[sp4C[2]].unk6 << 5, D_hd_code_802F3C48[sp4C[3]].unk6 << 5, sp44, sp40, sp3C);
        D_8036B8B8 = (s32) func_hd_code_80268D84(D_hd_code_802F3C48[sp4C[0]].unk8 << 5, D_hd_code_802F3C48[sp4C[1]].unk8 << 5, D_hd_code_802F3C48[sp4C[2]].unk8 << 5, D_hd_code_802F3C48[sp4C[3]].unk8 << 5, sp44, sp40, sp3C);
        D_8036B8BC = (s32) func_hd_code_80268D84(D_hd_code_802F3C48[sp4C[0]].unkA << 5, D_hd_code_802F3C48[sp4C[1]].unkA << 5, D_hd_code_802F3C48[sp4C[2]].unkA << 5, D_hd_code_802F3C48[sp4C[3]].unkA << 5, sp44, sp40, sp3C);
        if ((D_hd_code_803643D7 == 0) && (D_hd_code_803643D6 == 0) && (areWeFading() == 0)) {
            D_8036B908 += (f32)D_hd_code_802F3C2C[D_8036B8C0].unk0 * ((D_hd_code_802F3C48[sp4C[2]].unkC - D_hd_code_802F3C48[sp4C[1]].unkC) * sp44 + D_hd_code_802F3C48[sp4C[1]].unkC);
        }
        if (D_8036B908 >= 0x3E8) {
            D_8036B908 = 0;
            D_8036B90C += 1;
        }
    }
}

f32 func_hd_code_80268D84(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
  s32 spC;
  s32 sp8;
  s32 sp4;
  s32 sp0;

  spC = D_8036B8C8[0][0] * arg0 + D_8036B8C8[1][0] * arg1 + D_8036B8C8[2][0] * arg2 + D_8036B8C8[3][0] * arg3;
  sp8 = D_8036B8C8[0][1] * arg0 + D_8036B8C8[1][1] * arg1 + D_8036B8C8[2][1] * arg2 + D_8036B8C8[3][1] * arg3;
  sp4 = D_8036B8C8[0][2] * arg0 + D_8036B8C8[1][2] * arg1 + D_8036B8C8[2][2] * arg2 + D_8036B8C8[3][2] * arg3;
  sp0 = D_8036B8C8[0][3] * arg0 + D_8036B8C8[1][3] * arg1 + D_8036B8C8[2][3] * arg2 + D_8036B8C8[3][3] * arg3;

  return spC * arg6 + arg5 * sp8 + arg4 * sp4 + sp0;
}


#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/23C20/func_hd_code_80268EE8.s")

void func_hd_code_80268F54(void) {
  u8 sp7;
  f32 sp0;

  sp7 = 0;
  if ((D_80364A98 == 0x800)) {
    D_8036B966 = 0;
  } else {
    D_8036B966 = 1;
  }
  D_8036B955 = 0;
  while (sp7 == 0) {
    if ((D_hd_code_802F41E8[D_8036B955].unk0 == levelno) && (D_hd_code_802F41E8[D_8036B955].unk4 == D_8036B966)) {
      sp7 = 1;
    } else {
      D_8036B955 += 1;
    }
  }
  sp0 = D_hd_code_802F41E8[D_8036B955].unk8;
  D_8036B910[0][0] = -sp0;
  D_8036B910[0][1] = sp0 * 2.0;
  D_8036B910[0][2] = -sp0;
  D_8036B910[0][3] = 0.0f;
  D_8036B910[1][0] = 2.0 - sp0;
  D_8036B910[1][1] = sp0 - 3.0;
  D_8036B910[1][2] = 0.0f;
  D_8036B910[1][3] = 1.0f;
  D_8036B910[2][0] = sp0 - 2.0;
  D_8036B910[2][1] = 3.0 - sp0 * 2.0;
  D_8036B910[2][2] = sp0;
  D_8036B910[2][3] = 0.0f;
  D_8036B910[3][0] = sp0;
  D_8036B910[3][1] = -sp0;
  D_8036B910[3][2] = 0.0f;
  D_8036B910[3][3] = 0.0f;
  D_803FCD60 = D_hd_code_802F41E8[D_8036B955].unkC << 5;
  D_8036B950 = 0;
  D_8036B954 = 1;
  D_8036B958[0] = 0;
  D_8036B958[1] = 0;
  D_8036B958[2] = 0;
  D_8036B958[3] = 0;
  D_8036B95C = 0;
  D_8036B964 = 0;
  D_8036B965 = 0;
}

void func_hd_code_80269258(void) {
    s32 sp6C;
    s32 sp68;
    u8 sp64[4];
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    u8 sp3B;
    u8 sp3A;

    D_8036B960[0] = D_8036B954 - 1;
    D_8036B960[1] = D_8036B954;
    D_8036B960[2] = D_8036B954 + 1;
    D_8036B960[3] = D_8036B954 + 2;
    for(sp6C = 0; sp6C < 4; sp6C++) {
        sp68 = 0;
        sp3B = 0;
        while ((sp68 < 0x31) && (sp3B == 0)) {
            if ((D_hd_code_802F4224[sp68].unk0 == levelno) && (D_hd_code_802F4224[sp68].unk4 == D_8036B966) && (D_hd_code_802F4224[sp68].unk5 == D_8036B960[sp6C]) && (D_hd_code_802F4224[sp68].unk13 == D_8036B95C)) {
                sp3B = 1;
            } else {
                sp68 += 1;
            }
        }

        if (!sp3B) {
            sp68 = 0;
            while ((sp68 < 0x31) && (sp3B == 0)) {
                if ((D_hd_code_802F4224[sp68].unk0 == levelno) && (D_hd_code_802F4224[sp68].unk4 == D_8036B966) && (D_hd_code_802F4224[sp68].unk5 == D_8036B960[sp6C]) && (D_hd_code_802F4224[sp68].unk13 == D_8036B958[sp6C])) {
                    sp3B = 1;
                } else {
                    sp68 += 1;
                }
            }
        }
        if (sp3B == 0) {
            func_hd_code_8029A7E4("\n --- ASSERTION FAULT - %s - %s, line %d\n\n", "found", "utils2.c", 0x183);
        }
        sp64[sp6C] = sp68;
    }
    sp60 = (f32) ((f64) (f32) D_8036B950 / 1000.0);
    sp5C = sp60 * sp60;
    sp58 = sp5C * sp60;
    sp54 = (f32) D_hd_code_802F4224[sp64[0]].unkC;
    sp50 = (f32) D_hd_code_802F4224[sp64[1]].unkC;
    sp4C = (f32) D_hd_code_802F4224[sp64[2]].unkC;
    sp48 = (f32) D_hd_code_802F4224[sp64[3]].unkC;
    func_hd_code_8026A2E8(sp54, &sp50);
    func_hd_code_8026A2E8(sp50, &sp4C);
    func_hd_code_8026A2E8(sp4C, &sp48);
    sp44 = func_hd_code_8026A184(sp54, sp50, sp4C, sp48, sp60, sp5C, sp58);
    D_803FCD6A = (s16) (s32) (((f64) sp44 / 360.0) * 4095.0);
    sp54 = (f32) D_hd_code_802F4224[sp64[0]].unkE;
    sp50 = (f32) D_hd_code_802F4224[sp64[1]].unkE;
    sp4C = (f32) D_hd_code_802F4224[sp64[2]].unkE;
    sp48 = (f32) D_hd_code_802F4224[sp64[3]].unkE;
    func_hd_code_8026A2E8(sp54, &sp50);
    func_hd_code_8026A2E8(sp50, &sp4C);
    func_hd_code_8026A2E8(sp4C, &sp48);
    sp40 = func_hd_code_8026A184(sp54, sp50, sp4C, sp48, sp60, sp5C, sp58);
    D_803FCD6C = (s16) (s32) (((f64) sp40 / 360.0) * 4095.0);
    sp54 = (f32) D_hd_code_802F4224[sp64[0]].unk10;
    sp50 = (f32) D_hd_code_802F4224[sp64[1]].unk10;
    sp4C = (f32) D_hd_code_802F4224[sp64[2]].unk10;
    sp48 = (f32) D_hd_code_802F4224[sp64[3]].unk10;
    func_hd_code_8026A2E8(sp54, &sp50);
    func_hd_code_8026A2E8(sp50, &sp4C);
    func_hd_code_8026A2E8(sp4C, &sp48);
    sp3C = func_hd_code_8026A184(sp54, sp50, sp4C, sp48, sp60, sp5C, sp58);
    D_803FCD6E = (s16) (s32) (((f64) sp3C / 360.0) * 4095.0);
    D_803FCD48 = (s32) func_hd_code_8026A184((f32) ( D_hd_code_802F4224[sp64[0]].unk6 << 5), (f32) ( D_hd_code_802F4224[sp64[1]].unk6 << 5), (f32) ( D_hd_code_802F4224[sp64[2]].unk6 << 5), (f32) ( D_hd_code_802F4224[sp64[3]].unk6 << 5), sp60, sp5C, sp58);
    D_803FCD4C = (s32) func_hd_code_8026A184((f32) ( D_hd_code_802F4224[sp64[0]].unk8 << 5), (f32) ( D_hd_code_802F4224[sp64[1]].unk8 << 5), (f32) ( D_hd_code_802F4224[sp64[2]].unk8 << 5), (f32) ( D_hd_code_802F4224[sp64[3]].unk8 << 5), sp60, sp5C, sp58);
    D_803FCD50 = (s32) func_hd_code_8026A184((f32) ( D_hd_code_802F4224[sp64[0]].unkA << 5), (f32) ( D_hd_code_802F4224[sp64[1]].unkA << 5), (f32) ( D_hd_code_802F4224[sp64[2]].unkA << 5), (f32) ( D_hd_code_802F4224[sp64[3]].unkA << 5), sp60, sp5C, sp58);
    if (D_hd_code_802F41E8[D_8036B955].unkE != -1) {
        if (D_803FCD4C < D_hd_code_802F41E8[D_8036B955].unkE << 5) {
            D_803FCD4C = D_hd_code_802F41E8[D_8036B955].unkE << 5;
        }
    }
    D_803FCD70 = 0;
    if ((D_hd_code_803643D7 == 0) && (D_hd_code_803643D6 == 0) && (areWeFading() == 0)) {
        D_8036B950 += (D_hd_code_802F41E8[D_8036B955].unk10 * (((D_hd_code_802F4224[sp64[2]].unk12 - D_hd_code_802F4224[sp64[1]].unk12) * sp60) + D_hd_code_802F4224[sp64[1]].unk12));
    }
    if (D_8036B950 >= 0x3E8) {
        D_8036B950 = 0;
        D_8036B954 += 1;
        switch (D_8036B95C) {                       /* switch 1; irregular */
        case 0:                                     /* switch 1 */
            sp3A = D_hd_code_802F41E8[D_8036B955].unk11;
            break;
        case 1:                                     /* switch 1 */
            sp3A = D_hd_code_802F41E8[D_8036B955].unk12;
            break;
        case 2:                                     /* switch 1 */
            sp3A = D_hd_code_802F41E8[D_8036B955].unk13;
            break;
        }
        if ((s32) D_8036B954 >= (s32) sp3A) {
            switch (D_8036B95C) {                   /* switch 2; irregular */
            case 0:                                 /* switch 2 */
                if (D_803FCD75 == 1) {
                    func_hd_code_80275270(0x200000000000, 0x3F000000);
                } else {
                    D_803643DA = 1;
                    D_hd_code_802E8BD8 = 1;
                }
                break;
            case 1:                                 /* switch 2 */
                D_803643D9 = 1;
                D_hd_code_802E8BD8 = 1;
                break;
            }
        }
        switch (D_hd_code_802F4224[sp64[2]].unk14) {                          /* switch 3 */
        case 0:
            break;
        case 1:                                     /* switch 3 */
            if (D_80364AA8 == 0x80) {
                D_8036B95C = 1;
                return;
            }
            func_hd_code_802C1DD0(0);
            if ((s32) D_8036EA78 < (s32) D_8036EB92) {
                D_8036B964 = 1;
                D_8036B95C = 1;
            }
            D_8036B965 = 1;
            D_80364A84 = 1;
            return;
        case 2:                                     /* switch 3 */
        case 3:                                     /* switch 3 */
        case 11:                                    /* switch 3 */
        case 12:                                    /* switch 3 */
        case 13:                                    /* switch 3 */
            D_803FCD70 = D_hd_code_802F4224[sp64[2]].unk14;
            return;
        case 5:                                     /* switch 3 */
            D_hd_code_802F5804[0x2A].unkC = "LANDING ABORTED!";
            D_hd_code_802F5804[0x2A].unk10 = &D_hd_code_80303AF4;
            D_hd_code_802F8BDC[0x17].unk12 = 0xDA;
            if (D_hd_code_80364A90 & 0x104) {
                func_hd_code_8026AF6C(0x8017U);
                return;
            }
            break;
        case 6:                                     /* switch 3 */
            D_hd_code_802F5804[0x2A].unkC = "DITCHING IN SEA!";
            D_hd_code_802F5804[0x2A].unk10 = &D_hd_code_80303B00;
            D_hd_code_802F8BDC[0x17].unk12 = 0x77;
            if (D_hd_code_80364A90 & 0x104) {
                func_hd_code_8026AF6C(0x8017U);
                return;
            }
            break;
        case 4:                                     /* switch 3 */
            D_hd_code_802F5804[0x2A].unkC = "ON FINAL APPROACH!";
            D_hd_code_802F5804[0x2A].unk10 = &D_hd_code_80303B10;
            D_hd_code_802F8BDC[0x17].unk12 = 0xD7;
            if (D_hd_code_80364A90 & 0x104) {
                func_hd_code_8026AF6C(0x8017U);
                return;
            }
            break;
        case 7:                                     /* switch 3 */
            D_hd_code_802F5804[0x2A].unkC = "SUCCESSFUL LANDING!";
            D_hd_code_802F5804[0x2A].unk10 = &D_hd_code_80303B24;
            D_hd_code_802F8BDC[0x17].unk12 = 0x82;
            if (D_hd_code_80364A90 & 0x104) {
                func_hd_code_8026AF6C(0x8017U);
                return;
            }
            break;
        case 8:                                     /* switch 3 */
            D_hd_code_802F5804[0x2A].unkC = "3000 FT!";
            D_hd_code_802F5804[0x2A].unk10 = NULL;
            D_hd_code_802F8BDC[0x17].unk12 = 0xD5;
            if (D_hd_code_80364A90 & 0x104) {
                func_hd_code_8026AF6C(0x8017U);
                return;
            }
            break;
        case 9:                                     /* switch 3 */
            D_hd_code_802F5804[0x2A].unkC = "2000 FT!";
            D_hd_code_802F5804[0x2A].unk10 = NULL;
            D_hd_code_802F8BDC[0x17].unk12 = 0xD3;
            if (D_hd_code_80364A90 & 0x104) {
                func_hd_code_8026AF6C(0x8017U);
                return;
            }
            break;
        case 10:                                    /* switch 3 */
            D_hd_code_802F5804[0x2A].unkC = "1000 FT!";
            D_hd_code_802F5804[0x2A].unk10 = NULL;
            D_hd_code_802F8BDC[0x17].unk12 = 0xD1;
            if (D_hd_code_80364A90 & 0x104) {
                func_hd_code_8026AF6C(0x8017U);
                func_hd_code_80260DFC();
            }
            break;
        }
    }
}

f32 func_hd_code_8026A184(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
  s32 spC;
  s32 sp8;
  s32 sp4;
  s32 sp0;

  spC = D_8036B910[0][0] * arg0 + D_8036B910[1][0] * arg1 + D_8036B910[2][0] * arg2 + D_8036B910[3][0] * arg3;
  sp8 = D_8036B910[0][1] * arg0 + D_8036B910[1][1] * arg1 + D_8036B910[2][1] * arg2 + D_8036B910[3][1] * arg3;
  sp4 = D_8036B910[0][2] * arg0 + D_8036B910[1][2] * arg1 + D_8036B910[2][2] * arg2 + D_8036B910[3][2] * arg3;
  sp0 = D_8036B910[0][3] * arg0 + D_8036B910[1][3] * arg1 + D_8036B910[2][3] * arg2 + D_8036B910[3][3] * arg3;

  return spC * arg6 + arg5 * sp8 + arg4 * sp4 + sp0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/23C20/func_hd_code_8026A2E8.s")

void func_hd_code_8026A378(s32 arg0, s8* arg1) {
  s32 sp4;
  u8 sp3;
  u8 sp2;
  u8 sp1;

  sp4 = 100000000;
  sp2 = 0;
  sp1 = 0;

  while (sp4) {
    sp3 = arg0 / sp4;
    if (sp1 || sp3) {
      *(arg1++) = sp3 + 0x30;

      sp1 = sp2 = 1;
    }
    arg0 -= sp3 * sp4;
    sp4 /= 10;
  }

  if (!sp2) {
    *(arg1++) = 0x30;
  }

  *arg1 = 0;
}

void func_hd_code_8026A454(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, Mtx* arg5) {
  f32 sp60[4][4];
  f32 sp20[4][4];

  func_hd_code_802D4F20(sp60, -arg0, -arg1, -arg2);
  guAlignF(sp20, (f32) arg3 / 11.375, 0.0f, 0.0f, 1.0f);
  guMtxCatF(sp60, sp20, sp60);
  guAlignF(sp20, (f32) arg4 / 11.375, 0.0f, 1.0f, 0.0f);
  guMtxCatF(sp60, sp20, sp60);
  func_hd_code_802D4F20(sp20, arg0, arg1, arg2);
  guMtxCatF(sp60, sp20, sp60);
  guMtxF2L(sp60, arg5);
}


#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/23C20/func_hd_code_8026A5CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/23C20/func_hd_code_8026A610.s")

f32 func_hd_code_802DA58C(s64);                /* extern */

s32 func_hd_code_8026A6F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
  s64 sp38;
  s64 sp30;
  s64 sp28;

  sp38 = arg0 - arg3,
  sp30 = arg1 - arg4,
  sp28 = arg2 - arg5;

  sp38 = sp38 * sp38;
  sp30 = sp30 * sp30;
  sp28 = sp28 * sp28;
  return sqrtf(func_hd_code_802DA58C(sp38 + sp30 + sp28));
}

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/23C20/func_hd_code_8026A828.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/23C20/func_hd_code_8026A8BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/23C20/func_hd_code_8026A8E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/23C20/func_hd_code_8026A974.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/23C20/func_hd_code_8026A988.s")

void func_hd_code_8026A9B4(void) {
    struct UnknownStruct_803644BC* sp3C;
    u8 sp3B;
    s32 sp34;
    s32 sp30;

    sp34 = 0xF423F;
    if ((u8) D_803A7430 == 0xF) {
        func_hd_code_8026AD30(0x50U);
    }
    if (levelno == 0x12) {
        if ((D_hd_code_803643E0 >> 5 < 0x578) && (func_hd_code_8026A610(D_hd_code_803643E0 >> 5, (s32) D_hd_code_803643E8 >> 5, 0x531, 0x1061) < 0x82)) {
            func_hd_code_8026AD30(0x51U);
        }
    }
    if (D_hd_code_80364456 != D_8036B979) {
        D_8036B978 = D_8036B979;
    }
    if (D_hd_code_80364456 != 0) {
        D_8036B979 = D_hd_code_80364456;
    }
    sp3C = D_80364460;
    sp3B = 0;
    while((sp3B == 0) && (D_803649D0 != sp3C)) {
        if ((sp3C->unk5C != D_8036B978) && (sp3C->unk5C != D_hd_code_80364456) && (D_hd_code_80364456 != 0) && (sp3C->unk5C != 0) && (sp3C->unk5C != 0xFE) && (sp3C->unk5C != 0xFF) && (sp3C->unk5C != 7) && (sp3C->unk5C != 6)) {
            sp30 = func_hd_code_8026A6F0((s32) D_hd_code_803643E0 >> 5, (s32) D_hd_code_803643E4 >> 5, (s32) D_hd_code_803643E8 >> 5, (s32) sp3C->unk64 >> 5, (s32) sp3C->unk68 >> 5, (s32) sp3C->unk6C >> 5);
            if (sp30 < sp34) {
                sp34 = sp30;
            }
            if ((sp30 < 0x64) && (D_8036B970 == 0) && ((func_hd_code_802AB3C0(sp3C->unk5C) == 0) || (D_803EFECB == 0))) {
                func_hd_code_8026AD30(0x4CU);
                D_8036B970 = 1;
                sp3B = 1;
            }
        }
        sp3C++;
    }
    if ((D_8036B970 != 0) && (sp34 >= 0x191)) {
        D_8036B970 = 0;
    }
    if ((levelno == 0) && ((s32) D_8036C7CC >= 2)) {
        func_hd_code_8026AD30(0x4DU);
    }
    if ((levelno == 0) && (D_hd_code_80364456 == 7) && (((s32) D_hd_code_803643E0 >> 5) >= 0x899)) {
        func_hd_code_8026AD30(0x53U);
    }
    if (D_8036B971 != 0) {
        if (((D_80364AF0[playerNumber].unk18[levelno] > 0 && D_80364AF0[playerNumber].unk18[levelno] < 6)?1:0) == 0 && (D_8036EB98 == 0)) {
            if (func_hd_code_8026AD30(0x4EU) == 0) {
                func_hd_code_8026AD30(0x4FU);
            }
            D_8036B971 = 0;
        }
    }
}





