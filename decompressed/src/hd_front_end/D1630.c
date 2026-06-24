#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/hd.h"
#include "../hd_code/yoshi.h"
#include "../hd_code/functions.h"
#include "../hd_code/variables.h"
void func_hd_front_end_801F4E70(s32);  /* extern */

extern s32 D_hd_front_end_80215960;
extern s32 D_hd_front_end_80215964;
extern f32 D_hd_front_end_80215968;
extern f32 D_hd_front_end_8021596C;
extern s16 D_hd_front_end_80215974;
extern s16 D_hd_front_end_80215976;
extern s32 D_hd_front_end_80215978;

void func_hd_front_end_801ED790(void) {
  func_hd_front_end_801F4E70(0);
  D_hd_front_end_80215960 = 0;
  D_hd_front_end_80215964 = 0;
  D_hd_front_end_80215968 = D_hd_front_end_8021596C = 0.0f;
  D_hd_front_end_80215976 = 0;
  D_hd_front_end_80215974 = 0;
  D_hd_front_end_80215978 = players[playerNumber].unkC;
}

typedef struct {
    /* 0x0 */ u8 *unk0;
    /* 0x4 */ s32 unk4;
} UnknownData802081C0;  /* 0x8 */

s32 func_hd_front_end_801F4FBC(struct Model1 *, s32);  /* extern */

extern UnknownData802081C0 D_hd_front_end_802081C0[];
extern u8   D_hd_front_end_802082B8[];
extern s8  *D_hd_front_end_802084B0;
extern s8  *D_hd_front_end_802084B4;
extern u16 *D_hd_front_end_802084B8;
extern u16 *D_hd_front_end_802084BC;
extern s8   D_hd_front_end_802084C0;
extern s32  D_hd_front_end_80215960;
extern s32  D_hd_front_end_80215964;
extern f32  D_hd_front_end_80215968;
extern f32  D_hd_front_end_8021596C;
extern u32  D_hd_front_end_80215970;
extern s16  D_hd_front_end_80215974;
extern s16  D_hd_front_end_80215976;
extern s32  D_hd_front_end_80215978;
extern u8   D_hd_front_end_80215980[];
extern u8   D_hd_front_end_80215998[];
extern s16  D_hd_front_end_802159B0;
extern Mtx  D_hd_front_end_802182D0[];

s32 func_hd_front_end_801ED800(s32 arg0, struct Model1 *arg1, u8 arg2, s32 *arg3) {
    s32 sp74;
    s32 sp70;
    s32 sp6C;
    UnknownData8024C414 *sp68;
    s32 sp64;
    s32 pad60;

    sp74 = arg0;
    if ((D_hd_code_80370C28 & 0x8000) && !(D_hd_code_80370C2A & 0x8000) && (D_hd_code_802FA268 != 0)) {
        D_hd_front_end_80215960 = 2;
        D_hd_front_end_80215964 = 3;
    }
    switch (D_hd_front_end_80215960) {              /* switch 1; irregular */
    case 3:
        break;
    case 0:
        D_hd_front_end_8021596C = (((f64) sins((u32) ((u32) 60U * (0x4000U * (D_hd_code_80358060)) / 60U) / 90U) * 2.85) / 32767.0);
        if ((f64) D_hd_front_end_8021596C >= 2.84) {
            D_hd_front_end_8021596C = 2.84f;
            D_hd_front_end_80215960 = 1;
            D_hd_front_end_80215970 = 0x91;
        }
        break;
    case 1:
        if (D_hd_front_end_80215970-- == 0) {
            D_hd_front_end_80215960 = 2;
        }
        break;
    case 2:
        D_hd_front_end_8021596C = (f32) ((f64) D_hd_front_end_8021596C * 0.9);
        break;
    }
    switch (D_hd_front_end_80215964) {              /* switch 2; irregular */
    case 0:
        if (D_hd_code_80358060 == 0x32) {
            D_hd_front_end_80215964 = 1;
            D_hd_front_end_80215974 = 0;
            D_hd_front_end_80215976 = 0;
        }
        break;
    case 1:
        if ((D_hd_front_end_80215974 + 0x10) >= 0x100) {
            D_hd_front_end_80215974 = 0xFF;
        } else {
            D_hd_front_end_80215974 += 0x10;
        }
        if (D_hd_code_80358060 == 0xC8) {
            D_hd_front_end_80215964 = 2;
        }
        break;
    case 2:
        if ((D_hd_front_end_80215974 - 0x20) < 0) {
            D_hd_front_end_80215974 = 0;
        } else {
            D_hd_front_end_80215974 -= 0x20;
        }
        if ((D_hd_front_end_80215976 + 0x10) >= 0x100) {
            D_hd_front_end_80215976 = 0xFF;
        } else {
            D_hd_front_end_80215976 += 0x10;
        }
        if (D_hd_code_80358060 == 0x122) {
            D_hd_front_end_80215964 = 3;
        }
        break;
    case 3:
        if ((D_hd_front_end_80215976 - 0x20) < 0) {
            D_hd_front_end_80215976 = 0;
        } else {
            D_hd_front_end_80215976 -= 0x20;
        }
        if (D_hd_front_end_80215976 == 0) {
            D_hd_code_80364A98 = 0x08000000;
        }
        break;
    }
    if ((D_hd_front_end_80215974 > 0) || (D_hd_front_end_80215976 > 0)) {
        sp68 = &players[playerNumber];
        func_hd_code_80259CCC(arg1, D_hd_front_end_802084B0, D_hd_front_end_802084B8, 0U, 0x9C, 0, 0x18, 0x1A, 0x1A, 1, 0, 0, 0, D_hd_front_end_80215974 / 2);
        func_hd_code_80259CCC(arg1, D_hd_front_end_802084B4, D_hd_front_end_802084BC, 0U, 0x9D, 0, 0xCB, 0x16, 0x16, 1, 0, 0, 0, D_hd_front_end_80215974 / 2);
        sp70 = 0;
        sp6C = 0;
        while (sp6C < D_hd_front_end_802082B8[D_hd_front_end_80215978]) {
            if ((D_hd_front_end_80215980[sp70] = D_hd_front_end_802081C0[D_hd_front_end_80215978].unk0[sp70]) == ' ') {
                sp6C++;
            }
            sp70++;
        }
        D_hd_front_end_80215980[sp70 - 1] = 0;
        sp6C = sp70;
        for(;D_hd_front_end_802081C0[D_hd_front_end_80215978].unk0[sp70] != 0;sp70++) {
            D_hd_front_end_80215998[sp70 - sp6C] = D_hd_front_end_802081C0[D_hd_front_end_80215978].unk0[sp70];
        }
        D_hd_front_end_80215998[sp70 - sp6C] = 0;
        if ((func_hd_code_8025B300(D_hd_front_end_80215980) >= 0xE) || (func_hd_code_8025B300(D_hd_front_end_80215998) >= 0xE)) {
            sp64 = 0x1D;
        } else {
            sp64 = 0x21;
        }
        func_hd_code_80259CCC(arg1, (s8 *) D_hd_front_end_80215980, NULL, 0U, 0x9D, 0, 0x58, sp64, sp64, 1, 0, 0, 0, D_hd_front_end_80215976 / 2);
        func_hd_code_80259CCC(arg1, (s8 *) D_hd_front_end_80215998, NULL, 0U, 0x9D, 0, 0x76, sp64, sp64, 1, 0, 0, 0, D_hd_front_end_80215976 / 2);
        D_hd_front_end_802159B0 += D_hd_front_end_802084C0 * 0xF;
        if (D_hd_front_end_802159B0 >= 0x100) {
            D_hd_front_end_802159B0 -= 0x1E;
            D_hd_front_end_802084C0 = -D_hd_front_end_802084C0;
        }
        if (D_hd_front_end_802159B0 < 0) {
            D_hd_front_end_802159B0 += 0x1E;
            D_hd_front_end_802084C0 = -D_hd_front_end_802084C0;
        }
        func_hd_code_80259DC8(arg1, (s32) D_hd_front_end_802084B0, (s32) D_hd_front_end_802084B8, 0, 0xA0, 0, 0x14, 0x1A, 0x1A, 1, 0xFF, 0xFF - D_hd_front_end_802159B0, 0, D_hd_front_end_80215974, 0xFF, D_hd_front_end_802159B0, 0, D_hd_front_end_80215974);
        func_hd_code_80259DC8(arg1, (s32) D_hd_front_end_802084B4, (s32) D_hd_front_end_802084BC, 0, 0xA0, 0, 0xC8, 0x16, 0x16, 1, 0xFF, 0xFF - D_hd_front_end_802159B0, 0, D_hd_front_end_80215974, 0xFF, D_hd_front_end_802159B0, 0, D_hd_front_end_80215974);
        func_hd_code_80259DC8(arg1, (s32) D_hd_front_end_80215980, 0, 0, 0xA0, 0, 0x55, sp64, sp64, 1, 0xFF, 0xFF - D_hd_front_end_802159B0, 0, D_hd_front_end_80215976, 0xFF, D_hd_front_end_802159B0, 0, D_hd_front_end_80215976);
        func_hd_code_80259DC8(arg1, (s32) D_hd_front_end_80215998, 0, 0, 0xA0, 0, 0x73, sp64, sp64, 1, 0xFF, 0xFF - D_hd_front_end_802159B0, 0, D_hd_front_end_80215976, 0xFF, D_hd_front_end_802159B0, 0, D_hd_front_end_80215976);
    }
    D_hd_front_end_80215968 = (f32) ((f64) D_hd_front_end_80215968 + (12.0 - (f64) (D_hd_front_end_8021596C * 2.0f)));
    if ((f64) D_hd_front_end_80215968 > 360.0) {
        D_hd_front_end_80215968 = (f32) ((f64) D_hd_front_end_80215968 - 360.0);
    }
    if ((u32) D_hd_code_80358060 < 2U) {
        guPerspective(&arg1->unk1240, &D_hd_code_8035807C, 45.0f, 1.3333334f, 40.0f, 4000.0f, 1.0f);
        guLookAtReflect(&arg1->projection2, &arg1->lookAt, 5.0f, 7.0f, 400.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        guMtxIdent(&arg1->unk1280);
        guMtxIdent(&arg1->unk12C0);
    }
    guScale(&arg1->unk1300, D_hd_front_end_8021596C / 8.0f, D_hd_front_end_8021596C / 8.0f, D_hd_front_end_8021596C / 8.0f);
    guAlign(&D_hd_front_end_802182D0[arg2], D_hd_front_end_80215968, 1.0f, 1.0f, 1.0f);
    if ((f64) D_hd_front_end_8021596C > 0.2) {
        sp74 = func_hd_front_end_801F4FBC(arg1, sp74);
    }
    *arg3 += (sp74 - arg0) >> 3;
    return sp74;
}

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D1630/D_hd_front_end_8020ED40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D1630/D_hd_front_end_8020ED50.s")
