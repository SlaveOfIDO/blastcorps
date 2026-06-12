#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"

// Proposed file name: radar.c
//
// This file draws the HUD navigation aids that track the runaway missile
// carrier: a 3D arrow in the corner of the screen pointing toward the
// carrier (color-coded by distance, blinking when close), and the circular
// radar/minimap with blips for the objective and the carrier, a rotating
// direction needle and a radar sweep line. D_803F7670/D_803F7678 hold the
// carrier's world x/z; D_803F7660 == 0x98967F (9999999) is the sentinel for
// "no carrier on this level". D_hd_code_80367BD6 is the overall HUD alpha.

f32 func_hd_code_80284ADC(s16, s16, s16, s16);      /* extern */

extern Mtx D_8036E5E0[]; // per-frame matrices for the rotated radar needle; proposed name: radarNeedleMtx
extern u16 D_hd_code_802FC5B0[]; // Texture, IA16, radar background layer 1; proposed name: radarTex1
extern u16 D_hd_code_802FC6B0[]; // Texture, IA16, radar background layer 2 (zoomable detail); proposed name: radarTex2
extern u8 D_hd_code_802FD6B0[8 * 32];  // Texture, IA8 8x32, radar sweep line; proposed name: radarSweepTex
extern Vtx D_hd_code_802FD7B0[4]; // radar disc quad; proposed name: radarDiscVtx
extern Vtx D_hd_code_802FD7F0[4]; // radar sweep line quad; proposed name: radarSweepVtx
extern Vtx D_hd_code_802FD830[2][12]; // double-buffered radar markers: [0..3] objective blip, [4..7] carrier blip, [8..11] needle; proposed name: radarMarkerVtx
extern f32 D_hd_code_802FD9B0; // radar sweep rotation angle in degrees, +4 per frame; proposed name: radarSweepAngle
extern s32 D_803F7660; // carrier-related value; 0x98967F (9999999) = no carrier on this level
extern u16 D_hd_code_802FCEB0[32 * 32]; // Texture data, RGBA16, carrier arrow surface; proposed name: carrierArrowTex
extern Vtx D_hd_code_802FD9B8[10]; // 3D carrier arrow model (9 triangles); proposed name: carrierArrowVtx

// Draw the 3D arrow pointing at the missile carrier. (arg2, arg3, arg4) and
// (arg5, arg6, arg7) are two world positions (>> 5 fixed point): the first is
// used for the arrow's direction to the carrier, the second for the distance
// that picks its color - green when more than 1500 units away, fading to red
// within 500. Within 250 units the arrow blinks. The arrow is a 10-vertex
// lit, env-mapped (G_TEXTURE_GEN) model drawn in perspective at the bottom
// left of the screen, rotated by the carrier bearing (atan via
// func_hd_code_802AD7D4 quadrant lookup) relative to the camera yaw
// (D_hd_code_80364452). Not drawn when there is no carrier.
// Proposed name: DrawCarrierArrow
void func_hd_code_80282C80(Gfx** gfx, struct Model1* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    Gfx* entry = *gfx;
    f32 sp130;
    f32 sp12C;
    u8 sp12B;
    u8 sp12A;
    s16 sp128;
    f32 spE8[4][4];
    f32 spA8[4][4];
    s32 spA4;
    s32 spA0;
    u8 sp9F;

    arg2 >>= 5;
    arg3 >>= 5;
    arg4 >>= 5;
    arg5 >>= 5;
    arg6 >>= 5;
    arg7 >>= 5;

    spA4 = D_803F7670 >> 5;
    spA0 = D_803F7678 >> 5;
    sp130 = sqrtf((((spA4 - arg2) * (spA4 - arg2)) + ((spA0 - arg4) * (spA0 - arg4))));
    if (sp130 < 1.0) {
        sp130 = 1.0f;
    }
    if ((spA4 >= arg2) && (spA0 >= arg4)) {
        sp12C = (func_hd_code_802AD7D4((s32) (((spA4 - arg2) / sp130) * 65536.0)) >> 4);
    }
    if ((spA4 >= arg2) && (spA0 < arg4)) {
        sp12C = ((func_hd_code_802AD7D4((s32) (((arg4 - spA0) / sp130) * 65536.0)) >> 4) + 0x400);
    }
    if ((spA4 < arg2) && (spA0 < arg4)) {
        sp12C = ((func_hd_code_802AD7D4((s32) (((arg2 - spA4) / sp130) * 65536.0)) >> 4) + 0x800);
    }
    if ((spA4 < arg2) && (spA0 >= arg4)) {
        sp12C = ((func_hd_code_802AD7D4((s32) (((spA0 - arg4) / sp130) * 65536.0)) >> 4) + 0xC00);
    }
    sp12C = (sp12C * 0.08791208791208792);
    sp12C = ((360.0 - sp12C) - 45.0);
    sp12C = (sp12C + (((D_hd_code_80364452 * 360.0) / 4095.0) - 135.0));
    sp130 = sqrtf((((arg5 - spA4) * (arg5 - spA4)) + ((arg7 - spA0) * (arg7 - spA0))));
    if (sp130 > 1500.0f) {
        sp12A = 0xFF;
        sp12B = 0;
    } else if (sp130 < 500.0f) {
        sp12B = 0xFF;
        sp12A = 0;
    } else {
        sp128 = (s16) (s32) (((sp130 - 500.0f) / 1000.0f) * 511.0f);
        if ((s16) sp128 < 0x100) {
            sp12A = sp128,
            sp12B = 0xFF;
        } else {
            sp12A = 0xFF,
            sp12B = 0x1FE - sp128;
        }
    }
    if (sp130 < 250.0f) {
        sp9F = 1;
    } else {
        sp9F = 0;
    }
    if ((((D_hd_code_803156C4 % 30U) >= 0x10U) || (sp9F == 0)) && (D_803F7660 != 0x98967F)) {
        guAlignF(spE8, 20.0f, 1.0f, 0.0f, 0.0f);
        guAlignF(spA8, -sp12C, 0.0f, 0.0f, 1.0f);
        guMtxCatF(spE8, spA8, spE8);
        guTranslateF(spA8, -150.0f, -230.0f, -800.0f);
        guMtxCatF(spE8, spA8, spE8);
        guMtxF2L(spE8, (Mtx* ) arg1->unk1580);
        gSPMatrix(entry++, (u32) &D_2000000.projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPPerspNormalize(entry++, D_hd_code_8035807C);

        gSPMatrix(entry++, D_2000000.unk1580, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
        gSPSetGeometryMode(entry++, G_SHADE | G_CULL_FRONT | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH);
        gDPPipeSync(entry++);
        gDPSetCycleType(entry++, G_CYC_1CYCLE);

        if (D_hd_code_80367BD6 == 0xFF) {
            gDPSetRenderMode(entry++, G_RM_RA_OPA_SURF, G_RM_RA_OPA_SURF2);
        } else {
            gDPSetRenderMode(entry++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
        }
        gDPSetCombineMode(entry++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

        gDPSetPrimColor(entry++, 0, 0, sp12B, sp12A, 0, D_hd_code_80367BD6);
        gSPTexture(entry++, qu016(0.03028), qu016(0.03028), 0, G_TX_RENDERTILE, G_ON);
        gDPLoadTextureBlock(entry++, (u32) (&D_hd_code_802FCEB0) + 0x80000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPVertex(entry++, osVirtualToPhysical(D_hd_code_802FD9B8), 10, 0);
        gSP1Triangle(entry++, 0, 1, 2, 0);
        gSP1Triangle(entry++, 0, 2, 3, 0);
        gSP1Triangle(entry++, 3, 1, 0, 0);
        gSP1Triangle(entry++, 1, 4, 2, 0);
        gSP1Triangle(entry++, 4, 5, 2, 0);
        gSP1Triangle(entry++, 5, 3, 2, 0);
        gSP1Triangle(entry++, 6, 7, 8, 0);
        gSP1Triangle(entry++, 9, 6, 8, 0);
        gSP1Triangle(entry++, 7, 9, 8, 0);
        gDPPipeSync(entry++);
    }
    *gfx = entry;
}

// Draw the radar/minimap centered at screen (58, 195). arg2 = frame double-
// buffer index, (arg3, arg4) = player world x/z, (arg5, arg6) = objective
// world x/z. The distance between them picks one of three zoom levels (range
// scale 1200/2400/4800 units, with matching texture shift); D_hd_code_803643DB
// == 0 forces the closest zoom and hides blips and sweep. Draws the radar
// disc from two blended IA16 texture layers (2-cycle combine), then two
// 3x3-pixel blips rotated into radar space by the camera yaw and clipped to
// the radar's screen box - the objective blip (blinking at the closest zoom)
// and the carrier blip - then a needle quad rotated toward
// (D_803F767C, D_803F7680), and finally the rotating sweep line.
// Proposed name: DrawRadar
void func_hd_code_8028376C(Gfx** gfx, struct Model1* arg1, u8 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    Gfx* entry;
    s32 sp218;
    u8 sp217;
    s32 sp210;
    s16 sp20E;
    s16 sp20C;
    s16 sp20A;
    s16 sp208;
    Mtx sp1C8;
    f32 sp188[4][4];
    f32 sp148[4][4];
    f32 sp144;
    f32 sp140;
    f32 sp13C;
    f32 sp138;

    entry = *gfx;
    sp218 = func_hd_code_8026A610(arg3, arg4, arg5, arg6);
    if (sp218 < 0x55F0) {
        sp217 = 0xA;
        sp210 = 0x4B0;
    }
    if ((sp218 >= 0x55F0) && (sp218 < 0xABE0)) {
        sp217 = 0;
        sp210 = 0x960;
    }
    if (sp218 >= 0xABE0) {
        sp217 = 0xF;
        sp210 = 0x12C0;
    }
    if (D_hd_code_803643DB == 0) {
        sp217 = 0xA;
        sp210 = 0x4B0;
    }
    guAlignF(sp188, (360.0 - (D_hd_code_80364414 - 180.0)), 0.0f, 1.0f, 0.0f);
    guMtxXFMF(sp188, ((arg3 - arg5) / sp210), 0.0f, ((arg4 - arg6) / sp210), &sp144, &sp140, &sp13C);
    sp20E = (58.0f + sp144);
    sp20C = (195.0f + sp13C);
    D_hd_code_802FD830[arg2][0].v.ob[0] = sp20E - 2;
    D_hd_code_802FD830[arg2][0].v.ob[1] = sp20C - 2;
    D_hd_code_802FD830[arg2][1].v.ob[0] = sp20E - 2;
    D_hd_code_802FD830[arg2][1].v.ob[1] = sp20C + 1;
    D_hd_code_802FD830[arg2][2].v.ob[0] = sp20E + 1;
    D_hd_code_802FD830[arg2][2].v.ob[1] = sp20C + 1;
    D_hd_code_802FD830[arg2][3].v.ob[0] = sp20E + 1;
    D_hd_code_802FD830[arg2][3].v.ob[1] = sp20C - 2;
    func_hd_code_802C1B9C();
    guMtxXFMF(sp188, ((arg3 - D_803F7670) / sp210), 0.0f, ((arg4 - D_803F7678) / sp210), &sp144, &sp140, &sp13C);
    sp20A = (58.0f + sp144);
    sp208 = (195.0f + sp13C);
    D_hd_code_802FD830[arg2][4].v.ob[0] = sp20A - 2;

    D_hd_code_802FD830[arg2][4].v.ob[1] = sp208 - 2;
    D_hd_code_802FD830[arg2][5].v.ob[0] = sp20A - 2;
    D_hd_code_802FD830[arg2][5].v.ob[1] = sp208 + 1;
    D_hd_code_802FD830[arg2][6].v.ob[0] = sp20A + 1;
    D_hd_code_802FD830[arg2][6].v.ob[1] = sp208 + 1;
    D_hd_code_802FD830[arg2][7].v.ob[0] = sp20A + 1;
    D_hd_code_802FD830[arg2][7].v.ob[1] = sp208 - 2;
    gSPMatrix(entry++, (u32) &D_2000000.mtx1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(entry++, (u32) &D_2000000.modelview, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
    gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
    gDPPipeSync(entry++);
    gDPSetTextureLOD(entry++, G_TL_TILE);
    gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);
    gDPSetTextureImage(entry++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, (u32) (&D_hd_code_802FC5B0) + 0x80000000);
    gDPSetTile(entry++, G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
    gDPLoadSync(entry++);
    gDPLoadBlock(entry++, G_TX_LOADTILE, 0, 0, 127, 1024);
    gDPSetTextureImage(entry++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, (u32) (&D_hd_code_802FC6B0) + 0x80000000);
    gDPTileSync(entry++);
    gDPSetTile(entry++, G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0x0100, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
    gDPLoadSync(entry++);
    gDPLoadBlock(entry++, G_TX_LOADTILE, 0, 0, 1023, 512);
    gDPSetTile(entry++, G_IM_FMT_IA, G_IM_SIZ_8b, 2, 0x0000, G_TX_RENDERTILE, 0, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 4, G_TX_NOLOD);
    gDPSetTileSize(entry++, G_TX_RENDERTILE, qu102(0.5), qu102(0.5), qu102(15.5), qu102(15.5));


    gDPSetTile(entry++, G_IM_FMT_IA, G_IM_SIZ_4b, 4, 0x0100, 1, 0, G_TX_MIRROR | G_TX_WRAP, 6, sp217, G_TX_MIRROR | G_TX_WRAP, 6, sp217);
    //spEC->words.w0 = 0xF5600900;
    //    spEC->words.w1 = ((sp217 & 0xF) << 0xA) | 0x01058000 | 0x100 | 0x60 | sp217 & 0xF;

    gDPSetTileSize(entry++, 1, qu102(0.5), qu102(0.5), qu102(63), qu102(63));
    gDPSetCycleType(entry++, G_CYC_2CYCLE);
    gDPSetRenderMode(entry++, G_RM_PASS, G_RM_CLD_SURF2);
    gDPSetCombineLERP(entry++, PRIMITIVE, SHADE, TEXEL1_ALPHA, SHADE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
    gDPSetPrimColor(entry++, 0, 0, 255, 255, 255, D_hd_code_80367BD6 < 0x3F ? D_hd_code_80367BD6 : 0x3F);
    gSPVertex(entry++, osVirtualToPhysical(&D_hd_code_802FD7B0), 4, 0);
    gSP1Triangle(entry++, 0, 1, 2, 0);
    gSP1Triangle(entry++, 0, 2, 3, 0);
    gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_OFF);
    gDPPipeSync(entry++);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    gDPSetCombineLERP(entry++, 0, 0, 0, SHADE, 0, 0, 0, PRIMITIVE, 0, 0, 0, SHADE, 0, 0, 0, PRIMITIVE);
    gDPSetPrimColor(entry++, 0, 0, 0, 0, 0, D_hd_code_80367BD6);

    if (D_hd_code_803643DB != 0) {
        gDPSetRenderMode(entry++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);

        if ((((u32) ((u32) D_hd_code_803156C4 % 40U) >= 0x15U) || (sp217 != 0xA)) && (sp20E >= 0x22) && (sp20E < 0x53) && (sp20C >= 0xAB) && (sp20C < 0xDC)) {
            gSPVertex(entry++, osVirtualToPhysical(&D_hd_code_802FD830[arg2][0]), 4, 0);
            gSP1Triangle(entry++, 0, 1, 2, 0);
            gSP1Triangle(entry++, 0, 2, 3, 0);
        }
        if ((sp20A >= 0x22) && (sp20A < 0x53) && (sp208 >= 0xB0) && (sp208 < 0xD7) && (D_803F7660 != 0x98967F)) {
            gSPVertex(entry++, osVirtualToPhysical(&D_hd_code_802FD830[arg2][4]), 4, 0);
            gSP1Triangle(entry++, 0, 1, 2, 0);
            gSP1Triangle(entry++, 0, 2, 3, 0);
        }
    }
    sp138 = func_hd_code_80284ADC(arg3 >> 5, arg4 >> 5, D_803F767C, D_803F7680);
    guAlignF(sp188, -((360.0 - (D_hd_code_80364414 - 180.0)) + (sp138 + 180.0)), 0.0f, 0.0f, 1.0f);
    guTranslateF((f32 (*)[4]) &sp148[0], 58.0f, 195.0f, 0.0f);
    guMtxCatF(sp188, (f32 (*)[4]) &sp148[0], sp188);
    guMtxF2L(sp188, &D_8036E5E0[arg2]);
    gDPPipeSync(entry++);

    if (D_hd_code_80367BD6 == 0xFF) {
       gDPSetRenderMode(entry++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
    } else {
       gDPSetRenderMode(entry++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    }
    gSPMatrix(entry++, osVirtualToPhysical(&D_8036E5E0[arg2]), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPVertex(entry++, osVirtualToPhysical(&D_hd_code_802FD830[arg2][8]), 4, 0);
    gSP1Triangle(entry++, 0, 1, 2, 0);
    gSP1Triangle(entry++, 0, 2, 3, 0);
    gSPPopMatrix(entry++, G_MTX_MODELVIEW);

    if (D_hd_code_803643DB != 0) {
        gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);
        gDPPipeSync(entry++);
        gDPSetCycleType(entry++, G_CYC_1CYCLE);
        gDPSetRenderMode(entry++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
        gDPSetCombineLERP(entry++, 0, 0, 0, SHADE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, SHADE, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor(entry++, 0, 0, 0, 0, 0, MIN(0x7F, D_hd_code_80367BD6));
        gDPLoadTextureBlock(entry++, (u32) (&D_hd_code_802FD6B0) + 0x80000000, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        guAlign(&arg1->unk2C0[0xC], D_hd_code_802FD9B0, 0.0f, 0.0f, 1.0f);
        guTranslate(&sp1C8, 58.0f, 195.0f, 0.0f);
        guMtxCatL(&arg1->unk2C0[0xC], &sp1C8, &arg1->unk2C0[0xC]);
        D_hd_code_802FD9B0 = (D_hd_code_802FD9B0 + 4.0);
        gSPMatrix(entry++, (u32) &D_2000000.unk2C0[0xC], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPVertex(entry++, osVirtualToPhysical(&D_hd_code_802FD7F0), 4, 0);
        gSP1Triangle(entry++, 0, 1, 2, 0);
        gSP1Triangle(entry++, 1, 2, 3, 0);
    }
    gDPPipeSync(entry++);

    *gfx = entry;
}

// Return the bearing in degrees (0..360) from point (arg0, arg1) to point
// (arg2, arg3), using the quadrant-corrected atan lookup
// func_hd_code_802AD7D4 (which works in 1/65536 revolutions)
// Proposed name: GetAngleToPoint
f32 func_hd_code_80284ADC(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
  f32 sp1C = sqrtf((((arg2 - arg0) * (arg2 - arg0)) + ((arg3 - arg1) * (arg3 - arg1))));

  if (sp1C < 1.0) {
    return 0.0f;
  }

  if ((arg2 >= arg0) && (arg3 >= arg1)) {
    return  (((f64) func_hd_code_802AD7D4((s32) (((f64) (arg2 - arg0) * 65535.9) / (f64) sp1C)) / 65536.0) * 360.0);
  }
  else if ((arg2 >= arg0) && (arg3 < arg1)) {
    return  (((f64) (func_hd_code_802AD7D4((s32) (((f64) (arg1 - arg3) * 65535.9) / (f64) sp1C)) + 0x4000) / 65536.0) * 360.0);
  }
  else if ((arg2 < arg0) && (arg3 < arg1)) {
    return  (((f64) (func_hd_code_802AD7D4((s32) (((f64) (arg0 - arg2) * 65535.9) / (f64) sp1C)) + 0x8000) / 65536.0) * 360.0);
  }
  else if ((arg2 < arg0) && (arg3 >= arg1)) {
    return (((f64) (func_hd_code_802AD7D4((s32) (((f64) (arg3 - arg1) * 65535.9) / (f64) sp1C)) + 0xC000) / 65536.0) * 360.0);
  }
}

