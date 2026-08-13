#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/hd.h"
#include "../hd_code/yoshi.h"
#include "../hd_code/functions.h"
#include "../hd_code/variables.h"
#include "../hd_code/io/controller.h"
#include "structs.h"

void func_hd_front_end_80200714(u8);                   /* extern */

extern u8 D_hd_front_end_8021AB84;
extern s32 attract3_ROM_START;
extern s32 attract4_ROM_START;
extern s32 usa_star_ROM_START;
extern u8* D_hd_front_end_8021AB80;
extern u8 D_hd_front_end_8021AB84;

void func_hd_front_end_802006F0(void) {
  func_hd_front_end_80200714(D_hd_front_end_8021AB84);
}

void func_hd_front_end_80200714(u8 arg0) {
  s32* sp34;
  s32* sp30;                                      /* compiler-managed */
  u32 sp2C;
  u16* sp28;
  u32 sp24;
  u8 sp23;
  u8 sp22;
  u8 sp21;
  u8 sp20;

  D_hd_front_end_8021AB80 = D_hd_code_80358070;
  D_hd_front_end_8021AB84 = arg0;
  switch (arg0) {                                 /* switch 1 */
    case 1:
    case 2:
    case 3:
      sp34 = &attract2_ROM_START;
      sp30 = &attract3_ROM_START;
      break;
    case 4:
    case 7:
    case 8:
      sp34 = &attract3_ROM_START;
      sp30 = &attract4_ROM_START;
      break;
    case 5:
    case 6:
    case 9:
      sp34 = &attract4_ROM_START;
      sp30 = &usa_star_ROM_START;
      break;
    default:
      return;
  }

  sp2C = (u32)sp30 - (u32)sp34;
  InitiateDma((u8*) sp34, D_hd_code_80358070, &sp2C, 0xD, 0, 2);
  sp28 = (u16*) D_hd_code_80358070;
  for (sp24 = 0; sp24 < sp2C >> 1; sp24++) {
    sp23 = sp28[sp24] >> 0xB;
    sp22 = (sp28[sp24] >> 6) & 0x1F;
    sp21 = (sp28[sp24] >> 1) & 0x1F;
    switch (arg0) {                     /* switch 2 */
      case 3:
      case 7:
      case 9:
        sp23 = MIN(31.0, (f32)sp23 * 1.25);
        sp22 = sp21 < 3 ? sp21 : 3;
        sp21 = sp21 / 4;
        break;
      case 2:
      case 6:
      case 8:
        sp22 = sp21 < 2 ? sp21 : 2;
        sp20 = sp23;
        sp23 = sp21 / 3;
        sp21 = (f32) sp20 * 0.8125;
        break;
    }
    sp28[sp24] = (sp23 << 0xB) | (sp22 << 6) | (sp21 * 2) | 1;
  }

  D_hd_code_80358070 = &D_hd_code_80358070[sp2C];
}

void func_hd_front_end_80200BD4(u8* arg0) {
  D_hd_front_end_8021AB80 = arg0;
}

Gfx* func_hd_front_end_80200BE0(Gfx* gfx, struct Model1* arg1, s32* arg2) {
    Gfx* entry;
    s32 sp70;
    s32 sp6C;
    u8 sp6B;

    entry = gfx;
    gDPPipeSync(entry++);
    gSPTexture(entry++, 0, 0, 0, 0, G_OFF);
    gDPSetTexturePersp(entry++, G_TP_NONE);
    if (D_hd_code_80364A90 & 0xC000000000000ULL) {
        gDPSetCycleType(entry++, G_CYC_1CYCLE);
        gDPSetRenderMode(entry++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        gDPSetCombineLERP(entry++, TEXEL0, 0, PRIMITIVE_ALPHA, 0, 0, 0, 0, 1, TEXEL0, 0, PRIMITIVE_ALPHA, 0, 0, 0, 0, 1);
        switch(D_hd_code_80364A90) {
            case 0x4000000000000ULL:
            case 0x8000000000000ULL:
                sp6B = 0x60;
                break;
            default:
                sp6B = 0xFF;
                break;
        }
        gDPSetPrimColor(entry++, 0, 0, 0, 0, 0, sp6B);
    } else {
        gDPSetCycleType(entry++, G_CYC_COPY);
        gDPSetRenderMode(entry++, G_RM_NOOP, G_RM_NOOP2);
    }
    for (sp70 = 0; sp70 < 0x140; sp70 += 0x40) {
        for (sp6C = 0; sp6C < 0xF0; sp6C += 0x10) {
            gDPSetTextureImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, D_hd_front_end_8021AB80);
            gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, ((sp70 - sp70) * 2 + 0x87) >> 3, 0, 7, 0, 2, 0, 0, 2, 0, 0);
            gDPLoadSync(entry++);
            gDPLoadTile(entry++, 7, (sp70 << 2), (sp6C << 2), ((sp70 + 0x3F) << 2), ((sp6C + 0xF) << 2));
            gDPPipeSync(entry++);
            gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, ((sp70 - sp70) * 2 + 0x87) >> 3, 0, 0, 0, 2, 0, 0, 2, 0, 0);
            gDPSetTileSize(entry++, 0, (sp70 << 2), (sp6C << 2), ((sp70 + 0x3F) << 2), ((sp6C + 0xF) << 2));
            if (D_hd_code_80364A90 & 0xC000000000000ULL) {
                gSPTextureRectangle(entry++, (sp70 << 2), (sp6C << 2), ((sp70 + 0x40) << 2), ((sp6C + 0x10) << 2), 0, (sp70 << 5), (sp6C << 5), 0x400, 0x400);
            } else {
                gSPTextureRectangle(entry++, (sp70 << 2), (sp6C << 2), ((sp70 + 0x3F) << 2), ((sp6C + 0xF) << 2), 0, (sp70 << 5), (sp6C << 5), 0x1000, 0x400);
            }
        }
    }
    gDPSetTexturePersp(entry++, G_TP_PERSP);
    *arg2 += ((s32)entry - (s32)gfx) >> 3;
    return entry;
}
