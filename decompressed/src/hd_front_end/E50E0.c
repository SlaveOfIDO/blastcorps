#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/hd.h"
#include "../hd_code/yoshi.h"
#include "../hd_code/functions.h"
#include "../hd_code/variables.h"
#include "../hd_code/io/controller.h"
#include "structs.h"

extern u8 D_hd_front_end_8020E3E8[];
extern u8* D_hd_front_end_8020E430[];
extern u8* D_hd_front_end_8021AB90[4];
extern s8 D_hd_front_end_8021ABA0;
s32 func_hd_front_end_801E96F8(void);               /* extern */
extern u32 D_hd_code_802FAD50[];
extern s16 D_hd_front_end_8020E3E0[];
extern s32 D_hd_front_end_8021ABA4;
extern ALSoundState D_hd_front_end_8021ABA8;
extern u8 D_hd_front_end_8021ABA1;
extern u8 D_hd_front_end_8021ABA2;
extern s32 D_6A32B0;
extern u8 D_68B550[];

void func_hd_front_end_80201240(s32 arg0) {
  s32 sp24;
  s32 sp20;

  sp24 = (s32)&D_6A32B0 - (s32)D_68B550;
  InitiateDma(D_68B550, D_hd_code_80358070, &sp24, 0xD, 0, 1);
  for (sp20 = 0; sp20 < 4; sp20++) {
    D_hd_front_end_8021AB90[sp20] = &D_hd_code_80358070[sp20 * 160 * 120 * 2];
  }
  D_hd_code_80358070 = &D_hd_code_80358070[sp24];
  D_hd_front_end_8021ABA0 = arg0;
  D_hd_front_end_8021ABA2 = 0;
  D_hd_front_end_8021ABA1 = 0;
  D_hd_front_end_8020C070[0xAF].unkC = &D_hd_front_end_8020E3E8[arg0 * 0x12];
  D_hd_front_end_8020C070[0xAF].unk10 = D_hd_front_end_8020E430[arg0];
}

Gfx* func_hd_front_end_80201364(s32 arg0, Gfx* gfx) {
    Gfx* entry = gfx;
    s32 spC0;
    s32 spBC;
    s32 spB8;
    s32 spB4;

    gDPPipeSync(entry++);
    gSPTexture(entry++, 0, 0, 0, 0, G_OFF);
    gDPSetTexturePersp(entry++, G_TP_NONE);
    gDPSetCycleType(entry++, G_CYC_2CYCLE);
    gDPSetCombineLERP(entry++, NOISE, 0, PRIMITIVE_ALPHA, 0, 0, 0, 0, ENVIRONMENT, TEXEL1, 0, ENV_ALPHA, COMBINED, 0, 0, 0, ENVIRONMENT);
    switch (D_hd_code_8036BB1C) {                   /* switch 1; irregular */
    case 1:
    case 4:
        D_hd_front_end_8021ABA4 = 0;
        break;
    case 2:
        switch (D_hd_front_end_8021ABA4) {          /* switch 2; irregular */
        case 0:
            if (((u8) D_hd_front_end_8021ABA1 + 3) >= 0x100) {
                D_hd_front_end_8021ABA1 = -1;
            } else {
                D_hd_front_end_8021ABA1 = (u8) D_hd_front_end_8021ABA1 + 3;
            }
            if (D_hd_front_end_8021ABA1 < 0x80) {
                D_hd_front_end_8021ABA2 = D_hd_front_end_8021ABA1;
            } else {
                D_hd_front_end_8021ABA2 = 0xFF - (u8) D_hd_front_end_8021ABA1;
            }
            if ((u8) D_hd_front_end_8021ABA1 == 0xFF) {
                D_hd_front_end_8021ABA4 = 1;
                sndPlaySfx((struct ALBankAlt_s*) D_hd_code_80367738, D_hd_front_end_8020E3E0[(u8) D_hd_front_end_8021ABA0], NULL);
            }
            break;
        case 1:
            D_hd_front_end_8021ABA2 = 0;
            D_hd_front_end_8021ABA1 = -1;
            if (func_hd_code_8026A828(0, 0x28) == 0) {
                D_hd_front_end_8021ABA4 = 2;
            }
            break;
        case 2:
            if ((func_hd_code_8026A828(0, 0x1E) == 0) || ((u8) D_hd_front_end_8021ABA2 == 0xFF)) {
                D_hd_front_end_8021ABA4 = 3;
            }
            if (((u8) D_hd_front_end_8021ABA2 + 0x18) >= 0x100) {
                D_hd_front_end_8021ABA2 = -1;
            } else {
                D_hd_front_end_8021ABA2 = (u8) D_hd_front_end_8021ABA2 + 0x18;
            }
            D_hd_front_end_8021ABA1 = 0xFF - (u8) D_hd_front_end_8021ABA2;
            break;
        case 3:
            if (func_hd_code_8026A828(0, 0x32) == 0) {
                D_hd_front_end_8021ABA4 = 2;
            }
            if (((u8) D_hd_front_end_8021ABA2 - 0x20) < 0) {
                D_hd_front_end_8021ABA2 = 0;
            } else {
                D_hd_front_end_8021ABA2 = (u8) D_hd_front_end_8021ABA2 - 0x20;
            }
            D_hd_front_end_8021ABA1 = 0xFF - (u8) D_hd_front_end_8021ABA2;
            if ((u8) D_hd_front_end_8021ABA2 == 0) {
                D_hd_front_end_8021ABA4 = 1;
            }
            break;
        }
        if (func_hd_front_end_801E96F8() != 0) {
            func_hd_code_8026AF6C(0x4000);
        }
        break;
    case 8:
        if (((u8) D_hd_front_end_8021ABA1 - 6) < 0) {
            D_hd_front_end_8021ABA1 = 0;
        } else {
            D_hd_front_end_8021ABA1 = (u8) D_hd_front_end_8021ABA1 - 6;
        }
        if ((u8) D_hd_front_end_8021ABA1 < 0x80) {
            D_hd_front_end_8021ABA2 = D_hd_front_end_8021ABA1;
        } else {
            D_hd_front_end_8021ABA2 = 0xFF - (u8) D_hd_front_end_8021ABA1;
        }
        break;
    }
    if (((u8) D_hd_front_end_8021ABA2 >= 0x3D) && (D_hd_front_end_8021ABA8.link.next == NULL)) {
        sndPlaySfx((struct ALBankAlt_s*) D_hd_code_80367738, 0x69, &D_hd_front_end_8021ABA8);
    }
    gDPSetPrimColor(entry++, 0, 0, 0, 0, 0, D_hd_front_end_8021ABA2);
    gDPSetEnvColor(entry++, 0, 0, 0, D_hd_front_end_8021ABA1);
    gDPSetRenderMode(entry++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    spB8 = 0x50;
    for (spC0 = 0; spC0 < 0xA0; spC0 += 0x20) {
        spB4 = 0x20;
        for (spBC = 0; spBC < 0x78; spBC += 8) {
            gDPSetTextureImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 160, D_hd_front_end_8021AB90[(u8) D_hd_front_end_8021ABA0]);
            gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, (((spC0 - spC0) << 1) + 0x47) >> 3, 0, 7, 0, 2, 0, 0, 2, 0, 0);
            gDPLoadSync(entry++);
            gDPLoadTile(entry++, 7, (spC0 << 2), (spBC << 2), ((spC0 + 0x1F) << 2), ((spBC + 7) << 2));
            gDPPipeSync(entry++);
            gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, (((spC0 - spC0) << 1) + 0x47) >> 3, 0, 0, 0, 2, 0, 0, 2, 0, 0);
            gDPSetTileSize(entry++, 0, (spC0 << 2), (spBC << 2), ((spC0 + 0x1F) << 2), ((spBC + 7) << 2));
            gSPTextureRectangle(entry++, ((spC0 + spB8) << 2), ((spBC + spB4) << 2), ((spC0 + spB8 + 0x20) << 2), ((spBC + spB4 + 8) << 2), 0, (spC0 << 5), (spBC << 5), 0x400, 0x400);
        }
    }
    gDPPipeSync(entry++);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor(entry++, 0, 0, 200, 200, 200, 255);
    gDPSetCombineLERP(entry++, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, 0, TEXEL0, 0, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, 0, TEXEL0, 0);
    gDPSetTextureImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 1, (u32)D_hd_code_802FAD50 + 0x80000000);
    gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0, 0, 7, 0, 1, 5, 0, 3, 0, 0);
    gDPLoadSync(entry++);
    gDPLoadBlock(entry++, 7, 0, 0, 1023, 128);
    gDPPipeSync(entry++);
    gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, 0, 0, 1, 5, 0, 3, 0, 0);
    gDPSetTileSize(entry++, 0, 0, 0, 124, 124);
    gSPTextureRectangle(entry++, ((spB8 - 0x10) << 2), ((spB4 - 0x18) << 2), ((spB8 + 0xB8) << 2), ((spB4 + 0x90) << 2), 0, 0, 0x400, 0xA3, 0xC3);
    gDPPipeSync(entry++);
    gDPSetTexturePersp(entry++, G_TP_PERSP);
    return entry;
}
