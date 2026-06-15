#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"
#include "macros.h"
#include "yoshi.h"

u8 func_hd_code_80297F74();                         /* extern */
extern u8 D_8039CAD0;
extern u8 D_hd_code_802FF180[6];
extern char* D_hd_code_802FF188[][20][2];
extern u8 D_hd_code_802FF5E8[];
struct S_8036BB24 {
    u16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u8* unkC;
    char* unk10;
    u8 unk14;
    u8 pad15;
    s16 unk16;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
}; // Size: 0x1C
extern struct S_8036BB24* D_hd_code_8036BB24; // 21 elements

void func_hd_code_802979E0(u8 arg0) {
    struct S_802F8BDC* sp4C;
    struct S_8036BB24* sp48;
    struct S_80367BCC* sp44;
    u8 sp43;
    u8 sp42;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    u8 sp2F;


    sp4C = &D_hd_code_802F8BDC[0x15];
    sp43 = func_hd_code_80297F74();
    sp42 = 0;
    if ((sp43 == 1) && (func_hd_code_80297EF8((s32) (u8) arg0) == 0)) {
        sp43 -= 1;
    }
    if (sp43 == 0) {
        D_8039CAD0 = 6;
    } else {
        sp2F = 0;
        sp3C = (s32) D_8039CAB6;
        while((sp3C < (D_8039CAB6 + 6)) && (sp2F == 0)) {
            if ((func_hd_code_80297EF8(D_hd_code_802FF180[sp3C % 6]) == 0) && (D_hd_code_802FF180[sp3C % 6] != (u8) arg0)) {
                sp2F = 1;
            } else {
                sp3C += 1;
            }
        }
        D_8039CAD0 = (u8) (sp3C % 6);
    }
    D_hd_code_8036BB24 = (struct S_8036BB24*)D_hd_code_80358070;
    D_hd_code_80358070 += 0x24C;




    for (sp3C = 0,  sp34 = 0, sp30 = 0, sp2F = 0; (sp3C < 0x14) && (sp2F == 0); sp3C++) {
        char* sp24 = D_hd_code_802FF188[D_8039CAD0][sp3C][0];
        char* sp28 = D_hd_code_802FF188[D_8039CAD0][sp3C][1];
        sp48 = &D_hd_code_8036BB24[sp3C];
        if (sp24 != NULL) {
            sp30 += 1;
            sp48->unk0 = 0x1020;
            if (D_hd_code_802FF5E8[(D_8039CAD0 * 5) + sp34] == sp3C) {
                sp48->unk0 |= 1;
                sp34 += 1;
            }
            sp48->unk4 = (s16) (sp3C * 0x10);
            sp48->unk6 = 0x10;
            sp48->unk8 = 0x10;
            sp48->unkC = sp24;
            sp48->unk10 = sp28;
            sp48->unk14 = 0U;
            sp48->unk16 = 0;
            sp48->unk18 = 7;
            sp48->unk19 = 7;
            sp48->unk1A = 0U;
        } else {
            sp2F = 1;
        }
    }

    sp48 = &D_hd_code_8036BB24[sp30];
    sp48->unkC = 0;
    sp48->unk10 = 0;
    sp48->unk0 = 0x400;
    sp48->unk2 = -0x20;
    sp48->unk4 = 0x26;
    sp48->unk14 = 0x18U;
    sp48->unk1A = 0;
    sp48->unk16 = (s16) sp48->unk1A;
    sp44 = &D_hd_code_802F49F4[sp48->unk14];
    sp48->unk1A = func_hd_code_80272C5C(sp44->unk6, 0, sp44->unk4, sp44->unk2C, sp44->unk2D | 4, 1.0f);
    sp4C->unk10 = sp30 + 1;
    sp4C->unk18 = D_hd_code_802FF5E8[D_8039CAD0 * 5];
    if (func_hd_code_80297EF8((s32) (u8) arg0) == 0) {
        sp43 -= 1;
    }
    for(sp3C = 0; sp3C < sp4C->unk10 && sp42 == 0; sp3C++) {
        sp48 = &D_hd_code_8036BB24[sp3C];
        sp38 = 0;
        while ((sp38 < func_hd_code_8025B300(sp48->unkC)) && (sp42 == 0)) {
            if (((s32) sp48->unkC[sp38] >= 0x30) && ((s32) sp48->unkC[sp38] < 0x36)) {
                sp48->unkC[sp38] = sp43 + 0x30;
                sp42 = 1;
            }
            sp38 += 1;
        }
    }
}

void func_hd_code_80297ECC(void) {
  D_hd_code_802F8BDC[0x15].unk18 = D_hd_code_802FF5E8[D_8039CAD0 * 5];
}

u8 func_hd_code_80297EF8(u8 arg0) {
  u8 sp27;
  u8 sp26;

  sp26 = func_hd_code_8029766C(arg0, &sp27);
  return sp26 && (players[playerNumber].unk90 & (1 << sp27)) ? 1 : 0;
}

u8 func_hd_code_80297F74(void) {
  s32 sp4;
  s32 sp0 = 6;

  for(sp4 = 0; sp4 < 6; sp4++) {
    if (players[playerNumber].unk90 & (1 << sp4)) {
      sp0--;
    }
  }

  return sp0;
}
