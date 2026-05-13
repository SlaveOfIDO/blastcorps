#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"
#include "macros.h"

s32 func_hd_code_802A0CC8(s16, s32);

extern u8 D_803EE3B1;
extern u8 *D_8036EC00; // Texture
extern Vtx* D_8036EC04;
extern Mtx* D_8036EC08;
extern Mtx* D_8036EC0C;
extern s16 D_8036EC10;
extern u8 D_hd_code_80364A68;
extern u8* D_8036EC14;
extern Vtx* D_8036EC18;
extern s16 D_8036EC1C;
extern u8 D_hd_code_80364A6A;
extern u8* D_8036EC20;
extern Vtx* D_8036EC24;
extern s16 D_8036EC28;
extern u8 D_hd_code_80364A6C;

void func_hd_code_80286A00(void) {
  D_hd_code_80364A68 = 1;

  // Load texture
  D_8036EC00 = D_hd_code_80358070;
  func_hd_code_802A0CC8(0x760, 0);

  D_8036EC08 = (Mtx*)D_hd_code_80358070;
  D_hd_code_80358070 += 2 * sizeof(Mtx);

  D_8036EC0C = (Mtx*)D_hd_code_80358070;
  D_hd_code_80358070 += 0x80;

  D_8036EC04 = (Vtx*)D_hd_code_80358070;
  D_hd_code_80358070 += 8 * sizeof(Vtx);
  D_8036EC04[0].v.ob[0] = 0x26;
  D_8036EC04[0].v.ob[1] = 0x7B;
  D_8036EC04[0].v.ob[2] = -5;
  D_8036EC04[0].v.tc[0] = 0;
  D_8036EC04[0].v.tc[1] = 0x4E0;

  D_8036EC04[1].v.ob[0] = 0x4D;
  D_8036EC04[1].v.ob[1] = 0x7B;
  D_8036EC04[1].v.ob[2] = -5;
  D_8036EC04[1].v.tc[0] = 0x4E0;
  D_8036EC04[1].v.tc[1] = 0x4E0;

  D_8036EC04[2].v.ob[0] = 0x4D;
  D_8036EC04[2].v.ob[1] = 0xAD;
  D_8036EC04[2].v.ob[2] = -5;
  D_8036EC04[2].v.tc[0] = 0x4E0;
  D_8036EC04[2].v.tc[1] = 0;

  D_8036EC04[3].v.ob[0] = 0x26;
  D_8036EC04[3].v.ob[1] = 0xAD;
  D_8036EC04[3].v.ob[2] = -5;
  D_8036EC04[3].v.tc[0] = 0;
  D_8036EC04[3].v.tc[1] = 0;

  D_8036EC04[4].v.ob[0] = -1;
  D_8036EC04[4].v.ob[1] = 0;
  D_8036EC04[4].v.ob[2] = -5;

  D_8036EC04[5].v.ob[0] = 1;
  D_8036EC04[5].v.ob[1] = 0;
  D_8036EC04[5].v.ob[2] = -5;

  D_8036EC04[6].v.ob[0] = -1;
  D_8036EC04[6].v.ob[1] = -17;
  D_8036EC04[6].v.ob[2] = -5;

  D_8036EC04[7].v.ob[0] = 1;
  D_8036EC04[7].v.ob[1] = -17;
  D_8036EC04[7].v.ob[2] = -5;

  D_8036EC10 = 0;
}

void func_hd_code_80286C60(Gfx** gfx, s32* arg1, u8 arg2, u8 arg3) {
    Gfx* entry = *gfx;

    if (arg3 != 3 && D_8036EC10 == 0) {
        return;
    }

    if (arg3 == 3 && D_8036EC10 < 0xFF) {
        D_8036EC10 += 0xA;
        if (D_8036EC10 > 0xFF) {
            D_8036EC10 = 0xFF;
        }
    }

    if (arg3 != 3 && D_8036EC10 != 0) {
        D_8036EC10 -= 0xA;
        if (D_8036EC10 < 0) {
            D_8036EC10 = 0;
        }
    }
    gSPMatrix(entry++, &D_2000000.mtx1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(entry++, &D_2000000.modelview, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(entry++);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
    gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
    gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);
    gDPSetPrimColor(entry++, 0, 0, 255, 255, 255, MIN(D_8036EC10, D_hd_code_80367BD6));
    gDPSetCombineMode(entry++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPLoadTextureBlock(entry++, (u32)D_8036EC00 + 0x80000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 40, 40, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPVertex(entry++, (u32)D_8036EC04 + 0x80000000, 4, 0);
    gSP1Triangle(entry++, 0, 1, 2, 0);
    gSP1Triangle(entry++, 0, 2, 3, 0);
    gDPPipeSync(entry++);
    gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_OFF);
    gDPSetRenderMode(entry++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetCombineMode(entry++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);

    guTranslate(&D_8036EC0C[arg2], 56.0f, 151.0f, 0.0f);
    gSPMatrix(entry++, (u32) (&D_8036EC0C[arg2]) + 0x80000000, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    guAlign(&D_8036EC08[arg2], ((D_803EE3B1 / 100.0f) * 180.0) + 270.0, 0.0f, 0.0f, 1.0f);
    gSPMatrix(entry++, (u32) (&D_8036EC08[arg2]) + 0x80000000, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPVertex(entry++, (u32) (&D_8036EC04[4]) + 0x80000000, 4, 0);
    gSP1Triangle(entry++, 0, 1, 2, 0);
    gSP1Triangle(entry++, 1, 2, 3, 0);
    gSPPopMatrix(entry++, G_MTX_MODELVIEW);
    gDPPipeSync(entry++);

    *gfx = entry;
}

void func_hd_code_802873AC(void) {
  D_hd_code_80364A6A = 1;
  D_8036EC14 = D_hd_code_80358070;
  func_hd_code_802A0CC8(0x996, 0);
  D_8036EC18 = (Vtx* ) D_hd_code_80358070;
  D_hd_code_80358070 += 4 * sizeof(Vtx);

  D_8036EC18[0].v.ob[0] = 0x22;
  D_8036EC18[0].v.ob[1] = 0x87;
  D_8036EC18[0].v.ob[2] = -5;
  D_8036EC18[0].v.tc[0] = 0;
  D_8036EC18[0].v.tc[1] = 0x3E0;

  D_8036EC18[1].v.ob[0] = 0x40;
  D_8036EC18[1].v.ob[1] = 0x87;
  D_8036EC18[1].v.ob[2] = -5;
  D_8036EC18[1].v.tc[0] = 0x3E0;
  D_8036EC18[1].v.tc[1] = 0x3E0;

  D_8036EC18[2].v.ob[0] = 0x40;
  D_8036EC18[2].v.ob[1] = 0xA5;
  D_8036EC18[2].v.ob[2] = -5;
  D_8036EC18[2].v.tc[0] = 0x3E0;
  D_8036EC18[2].v.tc[1] = 0;

  D_8036EC18[3].v.ob[0] = 0x22;
  D_8036EC18[3].v.ob[1] = 0xA5;
  D_8036EC18[3].v.ob[2] = -5;
  D_8036EC18[3].v.tc[0] = 0;
  D_8036EC18[3].v.tc[1] = 0;

  D_8036EC1C = 0;
}

void func_hd_code_80287530(Gfx** gfx, struct Model1* arg1, u8 arg2, u8 arg3) {
  Gfx* entry = *gfx;
  s8 spB8[20];

  if (arg3 != 0xA && D_8036EC1C == 0) {
    return;
  }

  if ((arg3 == 0xA) && (D_8036EC1C < 0xFF)) {
    D_8036EC1C += 0xA;
    if (D_8036EC1C >= 0x100) {
      D_8036EC1C = 0xFF;
    }
  }
  if ((arg3 != 0xA) && (D_8036EC1C != 0)) {
    D_8036EC1C -= 0xA;
    if (D_8036EC1C < 0) {
      D_8036EC1C = 0;
    }
  }
  gSPMatrix(entry++, (u32) &D_2000000.mtx1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
  gSPMatrix(entry++, (u32) &D_2000000.modelview, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
  gDPPipeSync(entry++);
  gDPSetCycleType(entry++, G_CYC_1CYCLE);
  gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
  gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
  gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
  gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);
  gDPSetPrimColor(entry++, 0, 0, 255, 255, 255, MIN(D_8036EC1C, D_hd_code_80367BD6));

  gDPSetCombineMode(entry++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
  gDPLoadTextureBlock(entry++, (u32) (D_8036EC14) + 0x80000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
  gSPVertex(entry++, (u32) (D_8036EC18) + 0x80000000, 4, 0);
  gSP1Triangle(entry++, 0, 1, 2, 0);
  gSP1Triangle(entry++, 0, 2, 3, 0);
  gDPPipeSync(entry++);

  func_hd_code_8026A378(D_803F8B72, spB8);
  func_hd_code_80259DC8(arg1, (s32) &spB8, 0, 1, 0, 0x40, 0x91, 0xF, 0xF, 1, 0xFF, 0xFF, 0, MIN(D_8036EC1C, D_hd_code_80367BD6), 0xFF, 0, 0, MIN(D_8036EC1C, D_hd_code_80367BD6));
  gDPPipeSync(entry++);

  *gfx = entry;
}

void func_hd_code_80287AE4(void) {
  D_hd_code_80364A6C = 1;

  D_8036EC20 = D_hd_code_80358070;
  func_hd_code_802A0CC8(0x998, 0);
  D_8036EC24 = (Vtx* ) D_hd_code_80358070;
  D_hd_code_80358070 += 4 * sizeof(Vtx);

  D_8036EC24[0].v.ob[0] = 0x22;
  D_8036EC24[0].v.ob[1] = 0x91;
  D_8036EC24[0].v.ob[2] = -5;
  D_8036EC24[0].v.tc[0] = 0;
  D_8036EC24[0].v.tc[1] = 0x3E0;

  D_8036EC24[1].v.ob[0] = 0x40;
  D_8036EC24[1].v.ob[1] = 0x91;
  D_8036EC24[1].v.ob[2] = -5;
  D_8036EC24[1].v.tc[0] = 0x3E0;
  D_8036EC24[1].v.tc[1] = 0x3E0;

  D_8036EC24[2].v.ob[0] = 0x40;
  D_8036EC24[2].v.ob[1] = 0xAF;
  D_8036EC24[2].v.ob[2] = -5;
  D_8036EC24[2].v.tc[0] = 0x3E0;
  D_8036EC24[2].v.tc[1] = 0;

  D_8036EC24[3].v.ob[0] = 0x22;
  D_8036EC24[3].v.ob[1] = 0xAF;
  D_8036EC24[3].v.ob[2] = -5;
  D_8036EC24[3].v.tc[0] = 0;
  D_8036EC24[3].v.tc[1] = 0;

  D_8036EC28 = 0;
}

void func_hd_code_80287C68(Gfx** gfx, struct Model1* arg1, u8 arg2, u8 arg3) {
  Gfx* entry = *gfx;
  s8 spB8[20];

  if (arg3 != 1 && D_8036EC28 == 0) {
    return;
  }

  if ((arg3 == 1) && (D_8036EC28 < 0xFF)) {
    D_8036EC28 += 0xA;
    if (D_8036EC28 >= 0x100) {
      D_8036EC28 = 0xFF;
    }
  }
  if ((arg3 != 1) && (D_8036EC28 != 0)) {
    D_8036EC28 -= 0xA;
    if (D_8036EC28 < 0) {
      D_8036EC28 = 0;
    }
  }
  gSPMatrix(entry++, (u32) &D_2000000.mtx1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
  gSPMatrix(entry++, (u32) &D_2000000.modelview, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
  gDPPipeSync(entry++);
  gDPSetCycleType(entry++, G_CYC_1CYCLE);
  gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
  gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
  gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
  gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);
  gDPSetPrimColor(entry++, 0, 0, 255, 255, 255, MIN(D_8036EC28, D_hd_code_80367BD6));

  gDPSetCombineMode(entry++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
  gDPLoadTextureBlock(entry++, (u32) (D_8036EC20) + 0x80000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
  gSPVertex(entry++, (u32) (D_8036EC24) + 0x80000000, 4, 0);
  gSP1Triangle(entry++, 0, 1, 2, 0);
  gSP1Triangle(entry++, 0, 2, 3, 0);
  gDPPipeSync(entry++);

  func_hd_code_8026A378((s32) D_803EDC00, spB8);
  func_hd_code_80259DC8(arg1, (s32) &spB8, 0, 1, 0, 0x44, 0x97, 0xF, 0xF, 1, 0xFF, 0xFF, 0, MIN(D_8036EC28, D_hd_code_80367BD6), 0xFF, 0, 0, MIN(D_8036EC28, D_hd_code_80367BD6));
  gDPPipeSync(entry++);

  *gfx = entry;
}
