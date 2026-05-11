#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"
#include "macros.h"

struct S_8036EC30 {
  s16 *unk0;
  s16 *unk4;
  s16 *unk8;
  s32 unkC;
  s16 unk10;
  s16 unk12;
  u8 unk14;
  u8 unk15;
  u8 unk16;
  u8 unk17;
  s8 unk18;
  u8 unk19;
  u8 unk1A;
  u8 unk1B;
  u8 unk1C;
  u8 unk1D;
  u8 unk1E;
  u8 unk1F;
  u8 unk20;
  u8 pad21;
  u8 unk22;
  u8 pad23;
}; // Size: 0x24+

struct S_8036EC38
{
  u8 unk0;
  u8 pad1;
  u8 pad2;
  u8 pad3;
  s32 unk4;
  s32 unk8;
  s32 unkC;
  s16 unk10;
  s16 unk12;
  s16 unk14;
  u8 unk16;
  u8 unk17;
  s16 unk18;
  s16 unk1A;
  s16 unk1C;
  s16 pad1E;
}; // Size: 0x20

extern struct S_8036EC38 D_8036EC38[50];
extern u8 D_80370B8C;
extern u8 D_80370B8D;
extern u8* D_80370B90;
extern struct S_8036EC30* D_8036EC30;
extern s32 D_80370B78;
extern s32 D_80370B7C;
extern s32 D_80370B80;
extern u8 D_80370B84;
extern s32 D_80370B88;
extern s32 D_80370BB0;
extern s32 D_80370BB4;
extern struct S_8036EC30* D_hd_code_802C4A20[];
extern Vtx D_hd_code_802FDA80[4];

void func_hd_code_80288220(void) {
  s32 sp4;

  for(sp4 = 0; sp4 < 50; sp4++) {
    D_8036EC38[sp4].unk0 = 0;
  }

  D_80370B8C = 0;
  D_80370B8D = 0;
  D_80370B90 = D_hd_code_80358070;
  D_hd_code_80358070 += 0x1400;
}

s32 func_hd_code_80288284(u8 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 pad4;
    s32 sp8;

    if (((u8) D_80370B8C == 0) && ((u8) D_80370B8D == 0)) {
        D_80370B78 = arg1;
        D_80370B7C = arg2;
        D_80370B80 = arg3;
        D_80370B88 = arg4;
        D_8036EC30 = D_hd_code_802C4A20[arg0];
        D_80370B84 = 0;
        D_hd_code_802FDA80[0].v.ob[0] = (s16) -D_8036EC30->unkC;
        D_hd_code_802FDA80[0].v.ob[1] = (s16) D_8036EC30->unkC;
        D_hd_code_802FDA80[0].v.tc[0] = 0;
        D_hd_code_802FDA80[0].v.tc[1] = 0;
        D_hd_code_802FDA80[0].v.cn[0] = D_8036EC30->unk1D;
        D_hd_code_802FDA80[0].v.cn[1] = D_8036EC30->unk1E;
        D_hd_code_802FDA80[0].v.cn[2] = D_8036EC30->unk1F;
        D_hd_code_802FDA80[0].v.cn[3] = D_8036EC30->unk20;

        D_hd_code_802FDA80[1].v.ob[0] = (s16) D_8036EC30->unkC;
        D_hd_code_802FDA80[1].v.ob[1] = (s16) D_8036EC30->unkC;
        D_hd_code_802FDA80[1].v.tc[0] = 0;
        D_hd_code_802FDA80[1].v.tc[1] = D_8036EC30->unk17 << 5;
        D_hd_code_802FDA80[1].v.cn[0] = D_8036EC30->unk1D;
        D_hd_code_802FDA80[1].v.cn[1] = D_8036EC30->unk1E;
        D_hd_code_802FDA80[1].v.cn[2] = D_8036EC30->unk1F;
        D_hd_code_802FDA80[1].v.cn[3] = D_8036EC30->unk20;

        D_hd_code_802FDA80[2].v.ob[0] = (s16) D_8036EC30->unkC;
        D_hd_code_802FDA80[2].v.ob[1] = (s16) -D_8036EC30->unkC;
        D_hd_code_802FDA80[2].v.tc[0] = D_8036EC30->unk16 << 5;
        D_hd_code_802FDA80[2].v.tc[1] = D_8036EC30->unk17 << 5;
        D_hd_code_802FDA80[2].v.cn[0] = D_8036EC30->unk1D;
        D_hd_code_802FDA80[2].v.cn[1] = D_8036EC30->unk1E;
        D_hd_code_802FDA80[2].v.cn[2] = D_8036EC30->unk1F;
        D_hd_code_802FDA80[2].v.cn[3] = D_8036EC30->unk20;

        D_hd_code_802FDA80[3].v.ob[0] = (s16) -D_8036EC30->unkC;
        D_hd_code_802FDA80[3].v.ob[1] = (s16) -D_8036EC30->unkC;
        D_hd_code_802FDA80[3].v.tc[0] = 0;
        D_hd_code_802FDA80[3].v.tc[1] = D_8036EC30->unk17 << 5;
        D_hd_code_802FDA80[3].v.cn[0] = D_8036EC30->unk1D;
        D_hd_code_802FDA80[3].v.cn[1] = D_8036EC30->unk1E;
        D_hd_code_802FDA80[3].v.cn[2] = D_8036EC30->unk1F;
        D_hd_code_802FDA80[3].v.cn[3] = D_8036EC30->unk20;

        switch (D_8036EC30->unk22) {
        case 0:
            sp8 = 4;
            break;
        case 1:
            sp8 = 8;
            break;
        case 2:
            sp8 = 16;
            break;
        case 3:
            sp8 = 32;
            break;
        }
        D_80370BB4 = (s32) (D_8036EC30->unk16 * D_8036EC30->unk17 * sp8) / 8;
        D_80370BB0 = 0;
        D_80370B8C = 1;
        return 1;
    }
    return 0;
}

void func_hd_code_802886A0(void) {
    s32 sp9C;
    s32 sp98;
    u8 sp97;
    u8 sp96;
    s16 sp94;
    f32 sp54[4][4];
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    s32 sp38;
    s16 sp36;

    sp9C = 0;
    sp98 = 0;
    sp97 = 0;
    if (D_80370B8C == 0) {
        if (D_80370B8D != 0) {
            D_80370B8D = D_80370B8D - 1;
        }
    } else {
        D_80370B8C = 0;
        if (D_80370B84 < D_8036EC30->unk1A) {
            while ((sp97 == 0) && (sp9C < D_8036EC30->unk19)) {
                sp96 = 0;
                while ((sp96 == 0) && (sp98 < 0x32)) {
                    if (D_8036EC38[sp98].unk0 == 0) {
                        sp96 = 1;
                    } else {
                        sp98 += 1;
                    }
                }
                if (sp96 != 0) {
                    D_8036EC38[sp98].unk0 = 1;
                    D_8036EC38[sp98].unk4 = D_80370B78;
                    D_8036EC38[sp98].unk8 = D_80370B7C;
                    D_8036EC38[sp98].unkC = D_80370B80;
                    sp38 = func_hd_code_8026A828(0, D_8036EC30->unk1B);
                    guAlignF(&sp54[0], (f32) sp38, 0.0f, 0.0f, 1.0f);
                    guMtxXFMF(&sp54[0], 0.0f, (f32) (func_hd_code_8026A828(-D_8036EC30->unk12, D_8036EC30->unk12) + D_8036EC30->unk10) / 32.0f, 0.0f, &sp50, &sp4C, &sp48);
                    sp38 = func_hd_code_8026A828(0, 0x167);
                    guAlignF(&sp54[0], (f32) sp38, 0.0f, 1.0f, 0.0f);
                    guMtxXFMF(&sp54[0], sp50, sp4C, sp48, &sp44, &sp40, &sp3C);
                    D_8036EC38[sp98].unk10 = (s16) (sp44 * 32.0f);
                    D_8036EC38[sp98].unk12 = (s16) (sp40 * 32.0f);
                    D_8036EC38[sp98].unk14 = (s16) (sp3C * 32.0f);
                    D_8036EC38[sp98].unk16 = 0;
                    D_8036EC38[sp98].unk18 = 0;
                    D_8036EC38[sp98].unk1A = 0;
                    D_8036EC38[sp98].unk1C = 0;
                    D_8036EC38[sp98].unk17 = func_hd_code_8026A828(-D_8036EC30->unk15, D_8036EC30->unk15) + D_8036EC30->unk14;
                    sp98 += 1;
                } else {
                    sp97 = 1;
                }
                sp9C += 1;
            }
            D_80370B84 += 1;
        }

        for(sp9C = 0; sp9C < 0x32; sp9C++) {
            if (D_8036EC38[sp9C].unk0 != 0) {
                D_80370B8C = 1;
                switch (D_8036EC38[sp9C].unk16) {                  /* irregular */
                case 0:
                    sp36 = *D_8036EC30->unk0;
                    if (D_8036EC38[sp9C].unk18 == sp36) {
                        D_8036EC38[sp9C].unk16 = 1;
                        D_8036EC38[sp9C].unk18 = 0;
                    }
                    break;
                case 1:
                    sp36 = *D_8036EC30->unk4;
                    if (D_8036EC38[sp9C].unk18 == sp36) {
                        D_8036EC38[sp9C].unk18 = 0;
                    }
                    break;
                case 3:
                    sp36 = *D_8036EC30->unk8;
                    if (D_8036EC38[sp9C].unk18 == sp36) {
                        D_8036EC38[sp9C].unk0 = 0;
                    }
                    break;
                }

                if (D_8036EC38[sp9C].unk1C == D_8036EC38[sp9C].unk17) {
                    D_8036EC38[sp9C].unk16 = 3;
                    D_8036EC38[sp9C].unk18 = 0;
                }
            }
        }

        for(sp9C = 0; sp9C < 0x32; sp9C++) {
            if (D_8036EC38[sp9C].unk0 != 0) {
                D_8036EC38[sp9C].unk4 += D_8036EC38[sp9C].unk10;
                D_8036EC38[sp9C].unkC += D_8036EC38[sp9C].unk14;
                sp94 = D_8036EC38[sp9C].unk12 + (D_8036EC38[sp9C].unk1A * D_8036EC30->unk18);
                D_8036EC38[sp9C].unk8 += sp94;
                if (D_8036EC38[sp9C].unk8 < D_80370B88) {
                    D_8036EC38[sp9C].unk8 = D_80370B88;
                    D_8036EC38[sp9C].unk12 = -((sp94 * 16) / D_8036EC30->unk1C);
                    D_8036EC38[sp9C].unk1A = 0;
                }
            }
            D_8036EC38[sp9C].unk1A += 1;
            D_8036EC38[sp9C].unk18 += 1;
            D_8036EC38[sp9C].unk1C += 1;
        }

        if (D_80370B8C == 0) {
            D_80370B8D = 3;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/43A60/func_hd_code_80288DF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/43A60/func_hd_code_80289EF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/43A60/func_hd_code_8028A0A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/43A60/func_hd_code_8028A1D0.s")
