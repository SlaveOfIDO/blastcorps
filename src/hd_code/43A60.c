#include "common.h"
#include "functions.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"

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
  u8 unk21;
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

struct S_80288DF0 {
  u8 unk0;
  s32 unk4;
}; // Size: 0x8

// Proposed file name: particles.c
//
// This file is the generic particle-burst effect system used for explosions,
// dust, debris and similar. A burst spawns from a per-effect template
// (S_8036EC30 in D_hd_code_802C4A20: animation frame-id lists, sprite
// dimensions/format, particle count, spawn count per frame, life span,
// spread/speed ranges, gravity, bounce floor, colors). Up to 50 live
// particles (D_hd_code_8036EC38) are simulated with velocity + gravity + a ground
// bounce, each playing through its frame animation, and drawn as
// camera-facing billboards. Frame textures are demand-loaded and cached
// (D_hd_code_80370B90 / D_hd_code_80370B98), and particles are depth-sorted before drawing.

void func_hd_code_80289EF4(Gfx**);                     /* extern */
u32 func_hd_code_8028A0A0(s16);
void func_hd_code_8028A1D0(struct S_80288DF0*, s32);                   /* extern */

extern Mtx D_hd_code_8036F278[][50];
extern struct S_8036EC38 D_hd_code_8036EC38[50];
extern u8 D_hd_code_80370B8C;
extern u8 D_hd_code_80370B8D;
extern u8* D_hd_code_80370B90;
extern struct S_8036EC30* D_hd_code_8036EC30;
extern s32 D_hd_code_80370B78;
extern s32 D_hd_code_80370B7C;
extern s32 D_hd_code_80370B80;
extern u8 D_hd_code_80370B84;
extern s32 D_hd_code_80370B88;
extern s32 D_hd_code_80370BB0;
extern s32 D_hd_code_80370BB4;
extern struct S_8036EC30* D_hd_code_802C4A20[];
extern Vtx D_hd_code_802FDA80[4];
extern s16 D_hd_code_80370B98[];
extern s32 D_hd_code_80370BB0;
extern s32 D_hd_code_80370BB4;

// Init the particle system at level start: clear all 50 particle slots and
// allocate the frame-texture cache buffer
// Proposed name: InitParticles
void func_hd_code_80288220(void) {
  s32 sp4;

  for(sp4 = 0; sp4 < 50; sp4++) {
    D_hd_code_8036EC38[sp4].unk0 = 0;
  }

  D_hd_code_80370B8C = 0;
  D_hd_code_80370B8D = 0;
  D_hd_code_80370B90 = D_hd_code_80358070;
  D_hd_code_80358070 += 0x1400;
}

// Start a particle burst of template arg0 at world (arg1, arg2, arg3) with
// floor y arg4: select the template, build the base billboard quad from its
// sprite size/colors, reset the texture cache and arm the spawner. Returns 0
// if a burst is already active.
// Proposed name: StartParticleBurst
s32 func_hd_code_80288284(u8 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 pad4;
    s32 sp8;

    if (((u8) D_hd_code_80370B8C == 0) && ((u8) D_hd_code_80370B8D == 0)) {
        D_hd_code_80370B78 = arg1;
        D_hd_code_80370B7C = arg2;
        D_hd_code_80370B80 = arg3;
        D_hd_code_80370B88 = arg4;
        D_hd_code_8036EC30 = D_hd_code_802C4A20[arg0];
        D_hd_code_80370B84 = 0;
        D_hd_code_802FDA80[0].v.ob[0] = (s16) -D_hd_code_8036EC30->unkC;
        D_hd_code_802FDA80[0].v.ob[1] = (s16) D_hd_code_8036EC30->unkC;
        D_hd_code_802FDA80[0].v.tc[0] = 0;
        D_hd_code_802FDA80[0].v.tc[1] = 0;
        D_hd_code_802FDA80[0].v.cn[0] = D_hd_code_8036EC30->unk1D;
        D_hd_code_802FDA80[0].v.cn[1] = D_hd_code_8036EC30->unk1E;
        D_hd_code_802FDA80[0].v.cn[2] = D_hd_code_8036EC30->unk1F;
        D_hd_code_802FDA80[0].v.cn[3] = D_hd_code_8036EC30->unk20;

        D_hd_code_802FDA80[1].v.ob[0] = (s16) D_hd_code_8036EC30->unkC;
        D_hd_code_802FDA80[1].v.ob[1] = (s16) D_hd_code_8036EC30->unkC;
        D_hd_code_802FDA80[1].v.tc[0] = 0;
        D_hd_code_802FDA80[1].v.tc[1] = D_hd_code_8036EC30->unk17 << 5;
        D_hd_code_802FDA80[1].v.cn[0] = D_hd_code_8036EC30->unk1D;
        D_hd_code_802FDA80[1].v.cn[1] = D_hd_code_8036EC30->unk1E;
        D_hd_code_802FDA80[1].v.cn[2] = D_hd_code_8036EC30->unk1F;
        D_hd_code_802FDA80[1].v.cn[3] = D_hd_code_8036EC30->unk20;

        D_hd_code_802FDA80[2].v.ob[0] = (s16) D_hd_code_8036EC30->unkC;
        D_hd_code_802FDA80[2].v.ob[1] = (s16) -D_hd_code_8036EC30->unkC;
        D_hd_code_802FDA80[2].v.tc[0] = D_hd_code_8036EC30->unk16 << 5;
        D_hd_code_802FDA80[2].v.tc[1] = D_hd_code_8036EC30->unk17 << 5;
        D_hd_code_802FDA80[2].v.cn[0] = D_hd_code_8036EC30->unk1D;
        D_hd_code_802FDA80[2].v.cn[1] = D_hd_code_8036EC30->unk1E;
        D_hd_code_802FDA80[2].v.cn[2] = D_hd_code_8036EC30->unk1F;
        D_hd_code_802FDA80[2].v.cn[3] = D_hd_code_8036EC30->unk20;

        D_hd_code_802FDA80[3].v.ob[0] = (s16) -D_hd_code_8036EC30->unkC;
        D_hd_code_802FDA80[3].v.ob[1] = (s16) -D_hd_code_8036EC30->unkC;
        D_hd_code_802FDA80[3].v.tc[0] = 0;
        D_hd_code_802FDA80[3].v.tc[1] = D_hd_code_8036EC30->unk17 << 5;
        D_hd_code_802FDA80[3].v.cn[0] = D_hd_code_8036EC30->unk1D;
        D_hd_code_802FDA80[3].v.cn[1] = D_hd_code_8036EC30->unk1E;
        D_hd_code_802FDA80[3].v.cn[2] = D_hd_code_8036EC30->unk1F;
        D_hd_code_802FDA80[3].v.cn[3] = D_hd_code_8036EC30->unk20;

        switch (D_hd_code_8036EC30->unk22) {
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
        D_hd_code_80370BB4 = (s32) (D_hd_code_8036EC30->unk16 * D_hd_code_8036EC30->unk17 * sp8) / 8;
        D_hd_code_80370BB0 = 0;
        D_hd_code_80370B8C = 1;
        return 1;
    }
    return 0;
}

// Per-frame particle update: while the burst is active, spawn this frame's
// batch of new particles (random direction/elevation/spin/lifetime from the
// template), advance every live particle through its animation phases
// (spawn -> loop -> die frame lists), integrate position with gravity, bounce
// off the floor, and retire expired particles. Sets a short cooldown when the
// last particle dies.
// Proposed name: UpdateParticles
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
    if (D_hd_code_80370B8C == 0) {
        if (D_hd_code_80370B8D != 0) {
            D_hd_code_80370B8D = D_hd_code_80370B8D - 1;
        }
    } else {
        D_hd_code_80370B8C = 0;
        if (D_hd_code_80370B84 < D_hd_code_8036EC30->unk1A) {
            while ((sp97 == 0) && (sp9C < D_hd_code_8036EC30->unk19)) {
                sp96 = 0;
                while ((sp96 == 0) && (sp98 < 0x32)) {
                    if (D_hd_code_8036EC38[sp98].unk0 == 0) {
                        sp96 = 1;
                    } else {
                        sp98 += 1;
                    }
                }
                if (sp96 != 0) {
                    D_hd_code_8036EC38[sp98].unk0 = 1;
                    D_hd_code_8036EC38[sp98].unk4 = D_hd_code_80370B78;
                    D_hd_code_8036EC38[sp98].unk8 = D_hd_code_80370B7C;
                    D_hd_code_8036EC38[sp98].unkC = D_hd_code_80370B80;
                    sp38 = func_hd_code_8026A828(0, D_hd_code_8036EC30->unk1B);
                    guAlignF(&sp54[0], (f32) sp38, 0.0f, 0.0f, 1.0f);
                    guMtxXFMF(&sp54[0], 0.0f, (f32) (func_hd_code_8026A828(-D_hd_code_8036EC30->unk12, D_hd_code_8036EC30->unk12) + D_hd_code_8036EC30->unk10) / 32.0f, 0.0f, &sp50, &sp4C, &sp48);
                    sp38 = func_hd_code_8026A828(0, 0x167);
                    guAlignF(&sp54[0], (f32) sp38, 0.0f, 1.0f, 0.0f);
                    guMtxXFMF(&sp54[0], sp50, sp4C, sp48, &sp44, &sp40, &sp3C);
                    D_hd_code_8036EC38[sp98].unk10 = (s16) (sp44 * 32.0f);
                    D_hd_code_8036EC38[sp98].unk12 = (s16) (sp40 * 32.0f);
                    D_hd_code_8036EC38[sp98].unk14 = (s16) (sp3C * 32.0f);
                    D_hd_code_8036EC38[sp98].unk16 = 0;
                    D_hd_code_8036EC38[sp98].unk18 = 0;
                    D_hd_code_8036EC38[sp98].unk1A = 0;
                    D_hd_code_8036EC38[sp98].unk1C = 0;
                    D_hd_code_8036EC38[sp98].unk17 = func_hd_code_8026A828(-D_hd_code_8036EC30->unk15, D_hd_code_8036EC30->unk15) + D_hd_code_8036EC30->unk14;
                    sp98 += 1;
                } else {
                    sp97 = 1;
                }
                sp9C += 1;
            }
            D_hd_code_80370B84 += 1;
        }

        for(sp9C = 0; sp9C < 0x32; sp9C++) {
            if (D_hd_code_8036EC38[sp9C].unk0 != 0) {
                D_hd_code_80370B8C = 1;
                switch (D_hd_code_8036EC38[sp9C].unk16) {                  /* irregular */
                case 0:
                    sp36 = *D_hd_code_8036EC30->unk0;
                    if (D_hd_code_8036EC38[sp9C].unk18 == sp36) {
                        D_hd_code_8036EC38[sp9C].unk16 = 1;
                        D_hd_code_8036EC38[sp9C].unk18 = 0;
                    }
                    break;
                case 1:
                    sp36 = *D_hd_code_8036EC30->unk4;
                    if (D_hd_code_8036EC38[sp9C].unk18 == sp36) {
                        D_hd_code_8036EC38[sp9C].unk18 = 0;
                    }
                    break;
                case 3:
                    sp36 = *D_hd_code_8036EC30->unk8;
                    if (D_hd_code_8036EC38[sp9C].unk18 == sp36) {
                        D_hd_code_8036EC38[sp9C].unk0 = 0;
                    }
                    break;
                }

                if (D_hd_code_8036EC38[sp9C].unk1C == D_hd_code_8036EC38[sp9C].unk17) {
                    D_hd_code_8036EC38[sp9C].unk16 = 3;
                    D_hd_code_8036EC38[sp9C].unk18 = 0;
                }
            }
        }

        for(sp9C = 0; sp9C < 0x32; sp9C++) {
            if (D_hd_code_8036EC38[sp9C].unk0 != 0) {
                D_hd_code_8036EC38[sp9C].unk4 += D_hd_code_8036EC38[sp9C].unk10;
                D_hd_code_8036EC38[sp9C].unkC += D_hd_code_8036EC38[sp9C].unk14;
                sp94 = D_hd_code_8036EC38[sp9C].unk12 + (D_hd_code_8036EC38[sp9C].unk1A * D_hd_code_8036EC30->unk18);
                D_hd_code_8036EC38[sp9C].unk8 += sp94;
                if (D_hd_code_8036EC38[sp9C].unk8 < D_hd_code_80370B88) {
                    D_hd_code_8036EC38[sp9C].unk8 = D_hd_code_80370B88;
                    D_hd_code_8036EC38[sp9C].unk12 = -((sp94 * 16) / D_hd_code_8036EC30->unk1C);
                    D_hd_code_8036EC38[sp9C].unk1A = 0;
                }
            }
            D_hd_code_8036EC38[sp9C].unk1A += 1;
            D_hd_code_8036EC38[sp9C].unk18 += 1;
            D_hd_code_8036EC38[sp9C].unk1C += 1;
        }

        if (D_hd_code_80370B8C == 0) {
            D_hd_code_80370B8D = 3;
        }
    }
}

// Draw the live particles (frame buffer arg1): resolve each particle's
// current animation frame texture (cached/loaded via func_hd_code_8028A0A0),
// depth-sort the particles, then for each draw a billboard quad rotated to
// face the camera (pitch from the camera-to-particle vector, yaw from the
// camera heading), batching identical textures.
// Proposed name: DrawParticles
void func_hd_code_80288DF0(Gfx** gfx, u8 arg1) {
    s32 sp2FC;
    s32 sp2F8;
    Gfx* entry = *gfx;
    f32 sp2B4[4][4];
    f32 sp274[4][4];
    s32 sp270;
    s32 sp26C;
    s32 sp268;
    s32 sp264;
    s32 sp260;
    s32 sp25C;
    struct S_80288DF0 spCC[50];
    s32 spC8 = 0;
    s32 spC4 = -1;

    if (D_hd_code_80370B8C == 0) {
        return;
    }

    func_hd_code_80289EF4(&entry);
    for(sp2FC = 0; sp2FC < 50; sp2FC++) {
        if (D_hd_code_8036EC38[sp2FC].unk0 != 0) {
            switch (D_hd_code_8036EC38[sp2FC].unk16) {
            case 0:
                sp25C = D_hd_code_8036EC30->unk0[D_hd_code_8036EC38[sp2FC].unk18];
                break;
            case 1:
                sp25C = D_hd_code_8036EC30->unk4[D_hd_code_8036EC38[sp2FC].unk18];
                break;
            case 3:
                sp25C = D_hd_code_8036EC30->unk8[D_hd_code_8036EC38[sp2FC].unk18];
                break;
            }
            spCC[spC8].unk0 = sp2FC;
            spCC[spC8].unk4 = func_hd_code_8028A0A0(sp25C);
            spC8 += 1;
        }
    }
    func_hd_code_8028A1D0(spCC, spC8);
    for(sp2F8 = 0; sp2F8 < spC8; sp2F8++) {
        sp2FC =  spCC[sp2F8].unk0;
        if (spCC[sp2F8].unk4 != spC4) {
            spC4 = spCC[sp2F8].unk4;

            gDPPipeSync(entry++);

            switch (D_hd_code_8036EC30->unk22) {
            case G_IM_SIZ_4b:
                rare_gDPLoadTextureBlock_4b(entry++,
                                            OS_PHYSICAL_TO_K0(spC4),
                                            D_hd_code_8036EC30->unk21,
                                            D_hd_code_8036EC30->unk16,
                                            D_hd_code_8036EC30->unk17,
                                            0,
                                           G_TX_NOMIRROR | G_TX_CLAMP,
                                           G_TX_NOMIRROR | G_TX_CLAMP,
                                           G_TX_NOMASK,
                                           G_TX_NOMASK,
                                           G_TX_NOLOD,
                                           G_TX_NOLOD);
                break;
            case G_IM_SIZ_8b:
                gDPLoadTextureBlock(entry++,
                                    OS_PHYSICAL_TO_K0(spC4),
                                    D_hd_code_8036EC30->unk21,
                                    G_IM_SIZ_8b,
                                    D_hd_code_8036EC30->unk16,
                                    D_hd_code_8036EC30->unk17,
                                    0,
                                   G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMASK,
                                   G_TX_NOMASK,
                                   G_TX_NOLOD,
                                   G_TX_NOLOD);
                break;
            case G_IM_SIZ_16b:
                gDPLoadTextureBlock(entry++,
                                    OS_PHYSICAL_TO_K0(spC4),
                                    D_hd_code_8036EC30->unk21,
                                    G_IM_SIZ_16b,
                                    D_hd_code_8036EC30->unk16,
                                    D_hd_code_8036EC30->unk17,
                                    0,
                                    G_TX_NOMIRROR | G_TX_CLAMP,
                                    G_TX_NOMIRROR | G_TX_CLAMP,
                                    G_TX_NOMASK,
                                    G_TX_NOMASK,
                                    G_TX_NOLOD,
                                    G_TX_NOLOD);
                break;
            case G_IM_SIZ_32b:
                gDPLoadTextureBlock(entry++,
                                    OS_PHYSICAL_TO_K0(spC4),
                                    D_hd_code_8036EC30->unk21,
                                    G_IM_SIZ_32b,
                                    D_hd_code_8036EC30->unk16,
                                    D_hd_code_8036EC30->unk17,
                                    0,
                                    G_TX_NOMIRROR | G_TX_CLAMP,
                                    G_TX_NOMIRROR | G_TX_CLAMP,
                                    G_TX_NOMASK,
                                    G_TX_NOMASK,
                                    G_TX_NOLOD,
                                    G_TX_NOLOD);
                break;
            }
        }
        sp270 = func_hd_code_8026A6F0(
            D_hd_code_803643F8 >> 11,
            D_hd_code_803643FC >> 11,
            D_hd_code_80364400 >> 11,
            D_hd_code_8036EC38[sp2FC].unk4,
            D_hd_code_8036EC38[sp2FC].unk8,
            D_hd_code_8036EC38[sp2FC].unkC);
        if (sp270 == 0) {
            sp270 = 1;
        }
        sp26C = (D_hd_code_803643FC >> 11) - D_hd_code_8036EC38[sp2FC].unk8;
        sp26C <<= 16;
        sp264 = sp26C / sp270;
        if (sp264 < 0) {
            sp260 = -sp264;
        } else {
            sp260 = sp264;
        }
        sp268 = func_hd_code_802AD7D4(sp260);
        if (sp264 > 0) {
            sp268 = -sp268;
        }
        guAlignF(sp2B4, ((f32) sp268 / 65536.0) * 360.0, 1.0f, 0.0f, 0.0f);
        guAlignF(sp274, ((f32) D_hd_code_80364452 / 4095.0) * 360.0, 0.0f, 1.0f, 0.0f);
        guMtxCatF(sp2B4, sp274, sp2B4);
        guTranslateF(sp274, D_hd_code_8036EC38[sp2FC].unk4 / 32.0f, D_hd_code_8036EC38[sp2FC].unk8 / 32.0f, D_hd_code_8036EC38[sp2FC].unkC / 32.0f);
        guMtxCatF(sp2B4, sp274, sp2B4);
        guMtxF2L(sp2B4, &D_hd_code_8036F278[arg1][sp2FC]);
        gSPMatrix(entry++, osVirtualToPhysical(&D_hd_code_8036F278[arg1][sp2FC]), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
        gSPVertex(entry++, osVirtualToPhysical(D_hd_code_802FDA80), 4, 0);
        gSP1Triangle(entry++, 0, 1, 2, 0);
        gSP1Triangle(entry++, 0, 2, 3, 0);
        gSPPopMatrix(entry++, G_MTX_MODELVIEW);

    }

    *gfx = entry;

}


// Set up the RDP for particle drawing: z-buffered translucent, smooth
// shaded, combine mode by the template's texture format
// Proposed name: BeginParticleDraw
void func_hd_code_80289EF4(Gfx** gfx) {
  Gfx* entry = *gfx;

  gDPPipeSync(entry++);
  gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
  gSPSetGeometryMode(entry++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH);
  gDPSetRenderMode(entry++, G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2);

  switch (D_hd_code_8036EC30->unk21) {
    case G_IM_FMT_RGBA:
      gDPSetCombineMode(entry++, G_CC_MODULATEIA, G_CC_MODULATEIA);
      break;
    case G_IM_FMT_IA:
      gDPSetCombineMode(entry++, G_CC_MODULATEIA, G_CC_MODULATEIA);
      break;
    case G_IM_FMT_I:
      gDPSetCombineMode(entry++, G_CC_MODULATEI, G_CC_MODULATEI);
      break;
  }
  gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);

  *gfx = entry;
}

// Get the physical address of frame texture arg0, loading it into the next
// cache slot (and recording its id) if not already cached this burst
// Proposed name: GetParticleFrameTexture
u32 func_hd_code_8028A0A0(s16 arg0) {
  u8 sp27 = 0;
  s32 sp20 = 0;
  u8* sp1C;

  while(!sp27 && sp20 < D_hd_code_80370BB0) {
    if (D_hd_code_80370B98[sp20] == arg0) {
      sp27 = 1;
    } else {
      sp20++;
    }
  }

  if (sp27 != 0) {
    return osVirtualToPhysical(&D_hd_code_80370B90[sp20 * D_hd_code_80370BB4]);
  }

  sp1C = &D_hd_code_80370B90[D_hd_code_80370BB0 * D_hd_code_80370BB4];
  D_hd_code_80370B98[D_hd_code_80370BB0] = arg0;
  D_hd_code_80370BB0++;

  func_hd_code_802A1040(arg0, sp1C, 0);
  return osVirtualToPhysical(sp1C);
}

// Shell-sort the particle draw list arg0 (arg1 entries) by texture address
// so same-texture particles batch together
// Proposed name: SortParticlesByTexture
void func_hd_code_8028A1D0(struct S_80288DF0* arg0, s32 arg1) {
  s32 sp14;
  s32 sp10;
  s32 spC;
  struct S_80288DF0 sp4;

  for (spC = 1; spC <= (arg1 / 9); spC = (spC * 3) + 1){}

  for (;spC > 0; spC /= 3) {
    for(sp14 = spC; sp14 < arg1; sp14++) {
      sp4.unk0 = arg0[sp14].unk0;
      sp4.unk4 = arg0[sp14].unk4;
      sp10 = sp14;

      while (sp10 >= spC && arg0[sp10 - spC].unk4 > sp4.unk4) {
        arg0[sp10].unk0 = arg0[sp10 - spC].unk0;
        arg0[sp10].unk4 = arg0[sp10 - spC].unk4;
        sp10 -= spC;
      }

      arg0[sp10].unk0 = sp4.unk0;
      arg0[sp10].unk4 = sp4.unk4;
    }
  }
}

