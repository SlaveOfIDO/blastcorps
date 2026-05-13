#include "common.h"
#include "variables.h"
#include "functions.h"
#include "structs.h"
#include "aliases.h"

void func_hd_code_802A0B00(u16, u8*);
void func_hd_code_802A0EE0(u16, u8*);
Gfx* func_hd_code_802742D8(Gfx* gfx, u8 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, f32 arg7, u8 arg8);

// BSS Begin
u8* D_hd_code_8036BFE0[64][2];
u8 D_hd_code_8036C1E0[64];
u8 D_hd_code_8036C220[64];
f32 D_hd_code_8036C260[64];
u8 D_hd_code_8036C360;
u8* D_hd_code_8036C368[2][64][2];
// BSS End

extern u8 D_803B9888;

void func_hd_code_80272C50() {
  D_hd_code_8036C360 = 0;
}

u8 func_hd_code_80272C5C(u16* arg0, u16* arg1, u8 arg2, u8 arg3, u8 arg4, f32 arg5) {
  u8* sp3C;
  s32 sp38;
  s32 sp34;
  s32 sp30;
  s32 sp2C;
  s32 sp28;

  sp28 = D_hd_code_8036C360;
  if (D_803B9888 == 0) {
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
      D_hd_code_8036BFE0[sp38][sp34] = D_hd_code_80358070;
      func_hd_code_802A0B00(arg0[arg3 * sp2C + sp34], sp3C);
    }

    D_hd_code_8036C1E0[sp38] = arg3;
    D_hd_code_8036C220[sp38] = arg4;
    if (arg4 & 4) {
      for(sp34 = 0; sp34 < 2; sp34++) {
        for(sp30 = 0; sp30 < 2; sp30++) {
          D_hd_code_8036C368[sp34][sp38][sp30] = D_hd_code_80358070;
          D_hd_code_80358070 += 0x80;
        }
      }
    }
    D_hd_code_8036C260[sp38] = arg5;
  }

  D_hd_code_8036C360 = sp38;
  return sp28;
}

Gfx* func_hd_code_80272ED8(Gfx* arg0, u8 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, f32 arg6) {
    s32 sp104;
    Gfx* entry;
    u8 spFF;
    s32 spF8;
    s32 spF4;
    s32 spF0;
    s32 spEC;

    entry = arg0;

    spFF = arg4;
    arg6 *= D_hd_code_8036C260[arg1];
    spEC = D_hd_code_8036C1E0[arg1];
    if ((arg5 & 8) && ((u32) ((u32) D_hd_code_803156C4 % 20U) < 7U)) {
        spFF = (u32)arg4 >> 1;
    }
    gDPPipeSync(entry++);
    if (D_hd_code_8036C220[arg1] & 4) {
        if (arg6 > 1.0) {
            gDPSetTextureFilter(entry++, G_TF_BILERP);
        } else {
            gDPSetTextureFilter(entry++, G_TF_POINT);
        }
    }

    for (sp104 = 0; sp104 < (spEC - ((D_hd_code_8036C220[arg1] & 8)?1:0)); sp104++) {
        if (D_hd_code_8036C220[arg1] & 2) {
            gDPLoadTextureBlock(entry++, D_hd_code_8036BFE0[arg1][sp104], G_IM_FMT_RGBA,
                                G_IM_SIZ_32b, spEC * 32, 32,
                                0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, spEC + 4, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureBlock(entry++, D_hd_code_8036BFE0[arg1][sp104], G_IM_FMT_RGBA,
                                G_IM_SIZ_16b, spEC * 32, 32,
                                0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, spEC + 4, G_TX_NOLOD, G_TX_NOLOD);

        }
        if (arg5 != 0) {
            gDPPipeSync(entry++);
            if (arg5 & 4) {
                gDPSetPrimColor(entry++, 0, 0, arg4, arg4, arg4, 0xFF);
            } else {
                gDPSetPrimColor(entry++, 0, 0, 0, 0, 0, arg4 / 2);
            }
            spF0 = (s32) ((f32) spEC + (2.0f * arg6));

            gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetCombineLERP(entry++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);

            if (D_hd_code_8036C220[arg1] & 4) {
                entry = func_hd_code_802742D8(entry, arg1, arg2, arg3, sp104, spEC, spF0, arg6, 1);
            } else {
                spF8 = (arg2 - spF0) * 4;
                spF4 = (s32) ((f32) ((arg3 + spF0) * 4) + ((f32) ((sp104 << 5) * 4) * arg6));

                gSPTextureRectangle(entry++,
                                    MAX(spF8, 0),
                                    MAX(spF4, 0),
                                    MAX((arg2 << 2) + ((spEC * 32 - spF0 - 1) << 2) * arg6, 0),
                                    MAX(((arg3 + spF0) * 4) + ((((sp104 << 5)) + 32) << 2) * arg6, 0),
                                    0,
                                    -MIN(((s32) ((s32) (1024.0f / arg6) * spF8) >> 7), 0),
                                    (((D_hd_code_8036C220[arg1] & 1)?((spEC << 5) << 5):(0)) - MIN((s32) ((s32) (1024.0f / arg6) * spF4) >> 7,0)),
                                    (s32)(1024.0f / arg6),
                                    (s32)(1024.0f / arg6));
            }
        }
        if (!(arg5 & 6)) {
            if (!(arg5 & 1)) {
                spF0 = (s32) ((f32) spEC + (2.0f * arg6));
            } else {
                spF0 = 0;
            }

            gDPPipeSync(entry++);
            gDPSetPrimColor(entry++, 0, 0, 0xFF, 0x00, 0x00, spFF);


            if ((D_hd_code_8036C220[arg1] & 2) || (spFF != 0xFF) || (!(D_hd_code_80364A90 & 0xC9FD0FE79BFF80B0))) {
                gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            } else {
                gDPSetRenderMode(entry++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
            }
            gDPSetCombineLERP(entry++, TEXEL0, 0, PRIMITIVE_ALPHA, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE_ALPHA, 0, TEXEL0, 0, PRIMITIVE, 0);

            if (D_hd_code_8036C220[arg1] & 4) {
                entry = func_hd_code_802742D8(entry, arg1, arg2, arg3, sp104, spEC, spF0, arg6, 0);
            } else {
                spF8 = (arg2 - spF0) * 4;
                spF4 = (s32) ((f32) ((arg3 + spF0) * 4) + ((f32) ((sp104 << 5) * 4) * arg6));

                gSPTextureRectangle(entry++,
                                    MAX(spF8, 0),
                                    MAX(spF4, 0),
                                    MAX((f32) (arg2 * 4) + ((f32) ((((spEC << 5) - spF0) - 1) << 2) * arg6), 0),
                                    MAX((f32) ((arg3 + spF0) * 4) + ((f32) (((sp104 << 5) + 0x20) << 2) * arg6), 0),
                                    0,
                                    -MIN(((s32) ((s32) (1024.0f / arg6) * spF8) >> 7), 0),
                                    (((D_hd_code_8036C220[arg1] & 1)?((spEC << 5) << 5):(0)) - MIN((s32) ((s32) (1024.0f / arg6) * spF4) >> 7,0)),
                                    (s32)(1024.0f / arg6),
                                    (s32)(1024.0f / arg6));
            }
        }
    }

    gDPPipeSync(entry++);

    return entry;
}

Gfx* func_hd_code_802742D8(Gfx* gfx, u8 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, f32 arg7, u8 arg8) {
    s16* sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;

    sp34 = D_hd_code_8036C368[D_hd_code_8035805C][arg1][arg8];
    sp30 = arg2 - arg6;
    sp2C = arg3 + arg6;
    if (D_hd_code_8036C220[arg1] & 1) {
        sp28 = 0;
    } else {
        sp28 = arg5 << 5;
    }
    if (arg4 != 0) {
        sp34 = sp34 + 0x20;
        sp34[0x0] = sp30;
        sp34[0x1] = ((sp2C + (64.0f * arg7)) - 1.0f);
        sp34[0x2] = -0xA;
        sp34[0x4] = 0;
        sp34[0x5] = (sp28 << 5);

        sp34[0x8] = ((sp30 + ((arg5 << 5) * arg7)) - 1.0f);
        sp34[0x9] = ((sp2C + (64.0f * arg7)) - 1.0f);
        sp34[0xA] = -0xA;
        sp34[0xC] = (((arg5 << 5) - 1) << 5);
        sp34[0xD] = (sp28 << 5);

        sp34[0x10] = ((sp30 + ((arg5 << 5) * arg7)) - 1.0f);
        sp34[0x11] = ((sp2C + (32.0f * arg7)) - 1.0f);
        sp34[0x12] = -0xA;
        sp34[0x14] = (((arg5 << 5) - 1) << 5);
        sp34[0x15] = ((sp28 + 0x1F) << 5);

        sp34[0x18] = sp30;
        sp34[0x19] = ((sp2C + (32.0f * arg7)) - 1.0f);
        sp34[0x1A] = -0xA;
        sp34[0x1C] = 0;
        sp34[0x1D] = ((sp28 + 0x1F) << 5);
    } else {
        sp34[0x0] = sp30;
        sp34[0x1] = sp2C;
        sp34[0x2] = -0xA;
        sp34[0x4] = 0;
        sp34[0x5] = ((sp28 + 0x1F) << 5);

        sp34[0x8] = ((sp30 + ((arg5 << 5) * arg7)) - 1.0f);
        sp34[0x9] = sp2C;
        sp34[0xA] = -0xA;
        sp34[0xC] = (((arg5 << 5) - 1) << 5);
        sp34[0xD] = ((sp28 + 0x1F) << 5);

        sp34[0x10] = ((sp30 + ((arg5 << 5) * arg7)) - 1.0f);
        sp34[0x11] = ((sp2C + (32.0f * arg7)) - 1.0f);
        sp34[0x12] = -0xA;
        sp34[0x14] = (((arg5 << 5) - 1) << 5);
        sp34[0x15] = (sp28 << 5);

        sp34[0x18] = sp30;
        sp34[0x19]= ((sp2C + (32.0f * arg7)) - 1.0f);
        sp34[0x1A] = -0xA;
        sp34[0x1C] = 0;
        sp34[0x1D] = (sp28 << 5);
    }

    gSPVertex(gfx++, sp34, 4, 0);
    osWritebackDCache(sp34, 0x40);
    gSP1Triangle(gfx++, 0, 3, 2, 0);
    gSP1Triangle(gfx++, 0, 2, 1, 0);

    return gfx;
}

Gfx* func_hd_code_80274868(Gfx* gfx) {
  Gfx* entry = gfx;

  gDPPipeSync(entry++);
  gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
  gSPTexture(entry++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
  gDPSetTexturePersp(entry++, G_TP_NONE);
  gDPSetCycleType(entry++, G_CYC_1CYCLE);
  gDPSetRenderMode(entry++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
  gDPSetTextureFilter(entry++, G_TF_BILERP);

  return entry;
}

Gfx* func_hd_code_80274998(Gfx* gfx) {
  Gfx* entry = gfx;

  gDPPipeSync(entry++);
  gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
  gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
  gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);
  gDPSetCycleType(entry++, G_CYC_1CYCLE);
  gDPSetRenderMode(entry++, G_RM_OPA_SURF, G_RM_OPA_SURF2);

  return entry;
}

Gfx* func_hd_code_80274AA4(Gfx* gfx) {
  Gfx *entry = gfx;

  gDPPipeSync(entry++);
  gDPSetTexturePersp(entry++, G_TP_PERSP);

  return entry;
}

Gfx* func_hd_code_80274B08(Gfx* gfx) {
  Gfx* entry = gfx;

  gDPPipeSync(entry++);

  return entry;
}

void func_hd_code_80274B40(Gfx** gfx, struct Model1* arg1, u8 arg2, s16 arg3, s32 arg4) {
  Gfx* entry = *gfx;

  if (D_hd_code_803156C4 % 40U < 0x1CU) {
    entry = func_hd_code_80274868(entry);
    entry = func_hd_code_80272ED8(entry, (s32) arg2, arg3, (s32) (s16) arg4, 0xFFU, 1, 1.0f);
    entry = func_hd_code_80274AA4(entry);
  }
  *gfx = entry;
}
