#include "common.h"
#include "functions.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"
#include "yoshi.h"

struct S_80304A90 {
  s32 unk0;
  u8 unk4;
  u8 unk5;
  u8 unk6[0x30 - 0x8];
}; // Size: 0x30

extern struct S_80304A90 D_hd_code_80304A90[];
extern s16 D_hd_code_8036BB1C;
extern s32 D_hd_code_803A6B20;
extern s32 D_hd_code_803A6B24;

void func_hd_code_8029A500(void) {
  D_hd_code_803A6B20 = -0xEF;
  D_hd_code_803A6B24 = 0;
}

s32 func_hd_code_8029A518(struct Model1* arg0, s32 arg1) {
    s32 sp64;
    struct S_80304A90* sp60;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;

    sp54 = 0;
    sp64 = arg1;
    for(sp5C = 0; sp5C < 0x52; sp5C++) {
        sp60 = &D_hd_code_80304A90[sp5C];
        if (sp60->unk0 & 1) {
            sp50 = 0xA0;
        } else if (sp60->unk0 & 4) {
            sp50 = 0x6A;
        } else if (sp60->unk0 & 8) {
            sp50 = 0xD5;
        } else {
            sp50 = 0;
        }
        if ((sp54 - D_hd_code_803A6B20 >= -0x31) && (sp54 - D_hd_code_803A6B20 < 0xF0)) {
            func_hd_code_80259DC8(
                arg0,
                sp60->unk6,
                0,
                0,
                sp50,
                sp58,
                sp54 - D_hd_code_803A6B20,
                sp60->unk5,
                sp60->unk5,
                1,
                D_hd_code_802F47B0[sp60->unk4][0],
                D_hd_code_802F47B0[sp60->unk4][1],
                D_hd_code_802F47B0[sp60->unk4][2],
                D_hd_code_802F47B0[sp60->unk4][3],
                D_hd_code_802F47B0[sp60->unk4][4],
                D_hd_code_802F47B0[sp60->unk4][5],
                D_hd_code_802F47B0[sp60->unk4][6],
                D_hd_code_802F47B0[sp60->unk4][7]
            );
        }
        if (sp60->unk0 & 0x20) {
            sp54 += 0x26;
        }
        if (sp60->unk0 & 0x10) {
            sp54 += 0x16;
        }
        if (sp60->unk0 & 0x40) {
            sp54 += 0x11;
        }
    }
    if (D_hd_code_80358060 == 0x64) {
        func_hd_code_8026AF6C(0x8036U);
    }
    if ((u32) D_hd_code_80358060 >= 0x18CU) {
        D_hd_code_803A6B20 += 1;
    }
    if (D_hd_code_803643D6 != 0) {
        D_hd_code_803A6B24 += 1;
    }
    if (D_hd_code_803A6B24 == 0x7D) {
        func_hd_code_8026AF6C(0x8037U);
        func_hd_code_80260EE0(0x25);
    }
    if ((D_hd_code_803A6B24 >= 0x7E) && (D_hd_code_8036BB1C == 1) && (areWeFading() == 0)) {
        func_hd_code_80275270(0x200000000000, 0.75f);
    }
    return sp64;
}

