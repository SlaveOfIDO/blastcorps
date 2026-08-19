#include "common.h"
#include "functions.h"
#include "hd.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"

extern s32 D_hd_code_8036CC68;
extern s32 D_hd_code_8036CC6C;
extern u8* D_hd_code_8036D170;
extern u8 D_hd_code_8036D178;
extern s32 D_hd_code_8036D180;
extern u8 D_hd_code_80367C00;
extern struct S_8036CB60 D_hd_code_8036CB60[];
extern f32 D_hd_code_8036D174;
extern s32 D_hd_code_8036D17C;
extern f32 D_hd_code_8036D184;
extern Vtx D_hd_code_802FBEE0[];
extern Gfx D_hd_code_8036D188[];
extern Mtx D_hd_code_8036D2C8;
extern Mtx D_hd_code_8036D388;
extern Vp D_hd_code_802FBED0;
extern Mtx D_hd_code_8036CC70[][10];
extern s8 D_hd_code_8030C64C;

#define EPSILON (1e-08)

// Proposed file name: mb.c (the original name - the asserts in this file
// reference "mb.c", presumably "motion blur")
//
// This file is the motion blur / after-image effect: each frame the camera
// (eye + look-at) is recorded into an 11-entry ring (D_hd_code_8036CB60), the world
// is rendered from the player camera into a small 120x90 RGBA16 offscreen
// buffer (D_hd_code_8036D170) as a separate RSP task, and that captured image is
// re-projected as translucent curved screen meshes placed at past camera
// orientations (via inverted look-at matrices), producing trailing ghost
// frames with fading alpha. State: D_hd_code_8036D178 (0 = off, 1 = ramping up,
// 3 = hold, 2 = ramping down), D_hd_code_8036D180 = active ghost count,
// D_hd_code_8036D17C = max ghosts, D_hd_code_8036D184 = playback advance per ghost,
// D_hd_code_8036D174 = capture FOV.

void func_hd_code_8027A7DC(Gfx**, s32, s32);
u8 func_hd_code_802796D8(s32, s32*, s32*);
u8 invertTransformMatrix(f32[4][4], f32[4][4]);

// <bss>
struct S_8036CB60 D_hd_code_8036CB60[11];
s32 D_hd_code_8036CC68;
s32 D_hd_code_8036CC6C;
Mtx D_hd_code_8036CC70[2][10];
u8* D_hd_code_8036D170;
f32 D_hd_code_8036D174;
u8 D_hd_code_8036D178;
u8 D_hd_code_8036D179;
u16 D_hd_code_8036D17A;
s32 D_hd_code_8036D17C;
s32 D_hd_code_8036D180;
f32 D_hd_code_8036D184;
Gfx D_hd_code_8036D188[40];
Mtx D_hd_code_8036D2C8;
Mtx D_hd_code_8036D308;
Mtx D_hd_code_8036D348;
Mtx D_hd_code_8036D388;
s32 D_hd_code_8036D3C8;
s32 D_hd_code_8036D3CC;
// </bss>

// <data>
Vp D_hd_code_802FBED0 = { { { 0x00F0, 0x00B4, 0x01FF, 0x0000 }, { 0x00F0, 0x00B4, 0x01FF, 0x0000 } } };
Vtx D_hd_code_802FBEE0[24] = {
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x01C0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0EE0, 0x01C0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0EE0, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x01C0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0EE0, 0x01C0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0EE0, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x01C0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0EE0, 0x01C0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0EE0, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x01C0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0EE0, 0x01C0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0EE0, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x01C0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0EE0, 0x01C0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0EE0, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x01C0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0EE0, 0x01C0 }, { 0xFF, 0xFF, 0xFF, 0x00 } } },
    { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0EE0, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0x00 } } }
};

// Replacement rules for Gfx command 0 - from, 1 - to
u32 D_hd_code_802FC060[3][2] = {
  {0x00552078, 0x00552230},
  {0x005049D8, 0x00504A50},
  {0x00553078, 0x00553078}
};
// </data>

// Copy the display list [arg0, arg1) into freshly allocated level memory,
// rewriting every render-mode setting through a 3-entry translation table
// (opaque -> translucent equivalents) - used to make a ghost/translucent
// version of a model's display list
// Proposed name: CloneDisplayListXlu
void func_hd_code_80278BF0(Gfx* arg0, Gfx* arg1, Gfx** arg2) {
  Gfx* entry;
  s8 sp3B;
  u32 sp34;
  u8 found;
  s32 sp2C;
  u32 sp28;

  *arg2 = (Gfx* ) D_hd_code_80358070;
  entry = *arg2;
  D_hd_code_80358070 += (arg1 - arg0 - 2) * 8;
  while (arg0 != arg1) {
    sp3B = arg0->words.w0 >> 24;
    switch (sp3B) {
      case G_ENDDL:
        arg0++;
        break;
      case G_SETOTHERMODE_L:
        sp34 = (arg0->words.w0 >> 8) & 0xFFFF;
        if (sp34 == G_MDSFT_RENDERMODE) {
          entry->words.w0 = arg0->words.w0;
          sp28 = arg0->words.w1;
          sp2C = 0;
          found = 0;
          while(!found && sp2C < 3) {
            if (D_hd_code_802FC060[sp2C][0] == sp28) {
              found = 1;
            } else {
              sp2C += 1;
            }
          }
          if (!found) {
            rmonPrintf("\n --- ASSERTION FAULT - %s - %s, line %d\n\n", "found", "mb.c", 0x9D);
          }
          entry->words.w1 = D_hd_code_802FC060[sp2C][1];
          entry++, arg0++;
        } else {
          (entry++)->words = (arg0++)->words;
        }
        break;
      default:
        (entry++)->words = (arg0++)->words;
        break;
    }
  }
  gSPEndDisplayList(entry++);
}

// Allocate the 120x90 capture buffer (0x5460 bytes) from the level
// allocator and reset all motion blur state
// Proposed name: InitMotionBlur
void func_hd_code_80278E3C(void) {

  func_hd_code_80257490(D_hd_code_80358070, 0x40);
  D_hd_code_8036D170 = D_hd_code_80358070;

  D_hd_code_80358070 += 0x5460;
  func_hd_code_80257490(D_hd_code_80358070, 8);
  D_hd_code_8036D178 = 0;
  D_hd_code_8036CC68 = 0;
  D_hd_code_8036CC6C = 0;
  D_hd_code_8036D180 = 0;
  D_hd_code_80367C00 = 0;
}

// Start the motion blur: arg0 = ghost frame count (max 10), arg1 = playback
// advance per ghost (max 1.0), arg2 scales the capture FOV (atan of
// arg2 / distance between the two latest camera samples). Builds the curved
// screen mesh - 6 horizontal strips at radius 100 spanning the FOV - that
// the captured image is projected onto.
// Proposed name: StartMotionBlur
void func_hd_code_80278EB0(s32 arg0, f32 arg1, s32 arg2) {
    f32 spB0[4][4];
    f32 sp70[4][4];
    f32 sp64[3];
    f32 sp58[3];
    f32 sp54;
    s32 sp50;
    s32 sp4C;
    f32 sp48;
    f32 sp44;
    u8 sp43;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 pad;
    s32 sp2C;

    sp4C = 0;
    if (arg0 >= 0xB) {
        arg0 = 0xA;
    }
    if (arg1 > 1.0f) {
        arg1 = 1.0f;
    }
    D_hd_code_8036D17C = arg0;
    D_hd_code_8036D184 = arg1;
    D_hd_code_8036D180 = 0;
    D_hd_code_8036D178 = 1;
    sp43 = func_hd_code_802796D8(1, &sp3C, &sp38);
    if (sp43 != 0) {
        sp34 = func_hd_code_8026A6F0(D_hd_code_8036CB60[sp3C].unk0, D_hd_code_8036CB60[sp3C].unk4, D_hd_code_8036CB60[sp3C].unk8, D_hd_code_8036CB60[sp3C].unkC, D_hd_code_8036CB60[sp3C].unk10, D_hd_code_8036CB60[sp3C].unk14);
        if ((f64) sp34 < 1.0) {
            sp34 = 1;
        }
        arg2 <<= 16;
        sp2C = func_hd_code_802ACF3C(arg2 / sp34);
        D_hd_code_8036D174 = (f32) (((f64) (f32) sp2C / 65536.0) * 360.0);
    } else {
        D_hd_code_8036D174 = 25.0f;
    }
    sp54 = (D_hd_code_8036D174 / 2.0);
    sp48 = (D_hd_code_8036D174 / 6.0);
    sp44 = sp54 * 1.3333334f;
    for(sp50 = 0; sp50 < 6; sp50++) {
        guAlignF(spB0, sp54, 1.0f, 0.0f, 0.0f);
        guMtxXFMF(spB0, 0.0f, 0.0f, -100.0f, &sp64[0], &sp64[1], &sp64[2]);
        guAlignF(sp70, sp44, 0.0f, 1.0f, 0.0f);
        guMtxXFMF(sp70, sp64[0], sp64[1], sp64[2], &sp58[0], &sp58[1], &sp58[2]);
        D_hd_code_802FBEE0[sp4C].v.ob[0] = sp58[0];
        D_hd_code_802FBEE0[sp4C].v.ob[1] = sp58[1];
        D_hd_code_802FBEE0[sp4C].v.ob[2] = sp58[2];
        guAlignF(sp70, -sp44, 0.0f, 1.0f, 0.0f);
        guMtxXFMF(sp70, sp64[0], sp64[1], sp64[2], &sp58[0], &sp58[1], &sp58[2]);
        D_hd_code_802FBEE0[sp4C + 3].v.ob[0] = sp58[0];
        D_hd_code_802FBEE0[sp4C + 3].v.ob[1] = sp58[1];
        D_hd_code_802FBEE0[sp4C + 3].v.ob[2] = sp58[2];
        guAlignF(spB0, sp54 - sp48, 1.0f, 0.0f, 0.0f);
        guMtxXFMF(spB0, 0.0f, 0.0f, -100.0f, &sp64[0], &sp64[1], &sp64[2]);
        guAlignF(sp70, sp44, 0.0f, 1.0f, 0.0f);
        guMtxXFMF(sp70, sp64[0], sp64[1], sp64[2], &sp58[0], &sp58[1], &sp58[2]);
        D_hd_code_802FBEE0[sp4C + 1].v.ob[0] = sp58[0];
        D_hd_code_802FBEE0[sp4C + 1].v.ob[1] = sp58[1];
        D_hd_code_802FBEE0[sp4C + 1].v.ob[2] = sp58[2];
        guAlignF(sp70, -sp44, 0.0f, 1.0f, 0.0f);
        guMtxXFMF(sp70, sp64[0], sp64[1], sp64[2],  &sp58[0], &sp58[1], &sp58[2]);
        D_hd_code_802FBEE0[sp4C + 2].v.ob[0] = sp58[0];
        D_hd_code_802FBEE0[sp4C + 2].v.ob[1] = sp58[1];
        D_hd_code_802FBEE0[sp4C + 2].v.ob[2] = sp58[2];
        sp4C += 4;
        sp54 -= sp48;
    }
}

// Request the motion blur to ramp down (immediate stop if barely started)
// Proposed name: StopMotionBlur
void func_hd_code_802794A4(void) {
  if (D_hd_code_80367C00 == 0) {
    if (D_hd_code_8036D180 < 2) {
      D_hd_code_8036D178 = 0;
      return;
    }
    D_hd_code_8036D178 = 2;
  }
}

// Kill the motion blur immediately
// Proposed name: KillMotionBlur
void func_hd_code_802794E4(void) {
  D_hd_code_8036D178 = 0;
}

// Is the motion blur active?
// Proposed name: IsMotionBlurActive
u8 func_hd_code_802794F0() {
  return !(D_hd_code_8036D178 == 0);
}

// Record this frame's camera sample into the ring: (arg0..arg2) = look-at
// point (<< 5 fixed point), (arg3..arg5) = eye position (<< 16 fixed point)
// Proposed name: RecordCameraSample
void func_hd_code_80279514(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
  D_hd_code_8036CB60[D_hd_code_8036CC68].unk0 = (f32) arg3 / 65536.0;
  D_hd_code_8036CB60[D_hd_code_8036CC68].unk4 = (f32) arg4 / 65536.0;
  D_hd_code_8036CB60[D_hd_code_8036CC68].unk8 = (f32) arg5 / 65536.0;
  D_hd_code_8036CB60[D_hd_code_8036CC68].unkC = arg0 / 32.0f;
  D_hd_code_8036CB60[D_hd_code_8036CC68].unk10 = arg1 / 32.0f;
  D_hd_code_8036CB60[D_hd_code_8036CC68].unk14 = arg2 / 32.0f;

  D_hd_code_8036CC68++;
  if (D_hd_code_8036CC68 == 0xB) {
    D_hd_code_8036CC68 = 0;
  }

  if (D_hd_code_8036CC68 == D_hd_code_8036CC6C) {
    D_hd_code_8036CC6C++;
    if (D_hd_code_8036CC6C == 0xB) {
      D_hd_code_8036CC6C = 0;
    }
  }
}

// Get the ring indices arg0 steps back: *arg1 = that sample, *arg2 = the one
// before it. Returns 0 if the ring doesn't go back that far.
// Proposed name: GetCameraSample
u8 func_hd_code_802796D8(s32 arg0, s32* arg1, s32* arg2) {
  s32 sp4 = D_hd_code_8036CC68;

  while (arg0--) {
    if (sp4) {
      sp4 -= 1;
    } else {
      sp4 = 10;
    }
    if (sp4 == D_hd_code_8036CC6C) {
      return 0;
    }
  }

  *arg1 = sp4;
  if (sp4) {
    sp4 -= 1;
  } else {
    sp4 = 10;
  }

  *arg2 = sp4;

  return 1;
}

// Render the world display list arg6 (segments arg7/arg8, env alpha arg9)
// from the camera given by look-at (arg0..arg2, << 5) and eye (arg3..arg5,
// << 16) into the 120x90 offscreen capture buffer, with the blur FOV,
// submitted as its own RSP task. Called every frame from the game loop while
// the blur is active.
// Proposed name: RenderBlurFrame
void func_hd_code_80279778(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    Gfx* entry;
    u16 spDA;
    s32 padD4;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    s32 pad9C[8]; // Perhaps sp94 of type Mtx?
    f32 sp98;
    f32 sp94;

    if ((u8) D_hd_code_8036D178 != 0) {
        entry = D_hd_code_8036D188;
        gSPViewport(entry++, (s32) &D_hd_code_802FBED0 & 0x1FFFFFFF);
        gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
        gSPSegment(entry++, 0x00, 0x00000000);
        gSPSegment(entry++, 0x06, arg7 & 0x1FFFFFFF);
        gSPSegment(entry++, 0x07, arg8 & 0x1FFFFFFF);
        gDPPipeSync(entry++);
        gDPSetScissor(entry++, G_SC_NON_INTERLACE, 0, 0, 120, 90);
        gDPSetColorDither(entry++, G_CD_DISABLE);
        gDPSetCycleType(entry++, G_CYC_FILL);
        gSPClearGeometryMode(entry++, G_ZBUFFER);
        gDPSetDepthImage(entry++, D_hd_code_80358058);
        gDPSetColorImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 120, D_hd_code_80358058);
        gDPSetFillColor(entry++, 0xFFFCFFFC);
        gDPFillRectangle(entry++, 0, 0, 119, 89);
        gDPPipeSync(entry++);

        gDPSetColorImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 120, (u32)D_hd_code_8036D170 & 0x1FFFFFFF);
        gDPSetFillColor(entry++, 0x00000000);
        gDPFillRectangle(entry++, 0, 0, 119, 89);
        gDPPipeSync(entry++);

        guPerspective(&D_hd_code_8036D2C8, &spDA, D_hd_code_8036D174, 1.3333334f, 100.0f, 5000.0f, 1.0f);
        gSPMatrix(entry++, (s32) &D_hd_code_8036D2C8 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPPerspNormalize(entry++, spDA);

        spD0 = (f32) arg0 / 32.0f;
        spCC = (f32) arg1 / 32.0f;
        spC8 = (f32) arg2 / 32.0f;
        spC4 = (f32) ((f64) (f32) arg3 / 65536.0);
        spC0 = (f32) ((f64) (f32) arg4 / 65536.0);
        spBC = (f32) ((f64) (f32) arg5 / 65536.0);
        sp98 = spC4 - spD0;
        if (sp98 < 0.0) {
            sp98 = (f32) (0.0 - (f64) sp98);
        }
        sp94 = spBC - spC8;
        if (sp94 < 0.0) {
            sp94 = (f32) (0.0 - (f64) sp94);
        }
        if ((sp98 > 0.5) || (sp94 > 0.5)) {
            guLookAt((s32) &D_hd_code_8036D388, spC4, spC0, spBC, spD0, spCC, spC8, 0.0f, 1.0f, 0.0f);
        } else {
            guLookAt((s32) &D_hd_code_8036D388, (f32) ((f64) spC4 + 2.0), spC0, (f32) ((f64) spBC + 2.0), spD0, spCC, spC8, 0.0f, 1.0f, 0.0f);
        }
        gSPMatrix(entry++, (s32) &D_hd_code_8036D388 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetEnvColor(entry++, 0, 0, 0, arg9);
        gSPDisplayList(entry++, arg6 & 0x1FFFFFFF);
        gSPEndDisplayList(entry++);
        func_hd_code_80284E54(D_hd_code_8036D188, (s32) ((u32)entry - (u32)&D_hd_code_8036D188) >> 3, 2, 0, 0x54D, 0);
    }
}

// Draw the motion blur ghosts: ramp the ghost count up/down per the state,
// then for each ghost interpolate a past camera from the ring, invert its
// look-at matrix to place the curved screen mesh in world space facing that
// camera, and draw the captured image on it in 120x15 strips with linearly
// fading alpha (noise dither for the translucency).
// Proposed name: DrawMotionBlur
void func_hd_code_80279EE8(Gfx** gfx, s32* arg1, u8 arg2) {
    Gfx* entry = *gfx;
    u8 sp14B;
    s32 sp144;
    s32 sp140;
    f32 sp100[4][4];
    f32 spC0[4][4];
    s32 spBC;
    u8 spBB;
    u8 spBA;
    s32 spB4;
    s32 spB0;
    s32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;

    sp144 = 0;
    sp140 = 0;
    spB4 = 1;
    spA8 = 0.0f;
    switch (D_hd_code_8036D178) {
    case 1:
        D_hd_code_8036D180++;
        if (D_hd_code_8036D180 == D_hd_code_8036D17C) {
            D_hd_code_8036D178 = 3;
        }
        break;
    case 2:
        D_hd_code_8036D180--;
        if (D_hd_code_8036D180 == 0) {
            D_hd_code_8036D178 = 0;
        }
        break;
    }
    if (D_hd_code_8036D178 != 0) {
        gDPPipeSync(entry++);
        gDPSetColorDither(entry++, G_CD_NOISE);
        gDPSetAlphaDither(entry++, G_AD_NOTPATTERN);
        gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
        gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
        gDPSetCycleType(entry++, G_CYC_1CYCLE);
        gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(entry++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetTextureFilter(entry++, G_TF_BILERP);
        gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);


        spBA = 0x1E / (s32) (D_hd_code_8036D17C - 1);
        spBB = 0x28 - ((spBA) * (D_hd_code_8036D17C - D_hd_code_8036D180));
        for (spBC = 0; spBC < D_hd_code_8036D180; spBC++) {
            gDPSetPrimColor(entry++, 0, 0, 0xFF, 0xFF, 0xFF, spBB);

            sp14B = func_hd_code_802796D8(spB4, &spB0, &spAC);
            if (sp14B == 0) {
                break;
            }
            spA4 = ((D_hd_code_8036CB60[spAC].unkC - D_hd_code_8036CB60[spB0].unkC) * spA8) + D_hd_code_8036CB60[spB0].unkC;
            spA0 = ((D_hd_code_8036CB60[spAC].unk10 - D_hd_code_8036CB60[spB0].unk10) * spA8) + D_hd_code_8036CB60[spB0].unk10;
            sp9C = ((D_hd_code_8036CB60[spAC].unk14 - D_hd_code_8036CB60[spB0].unk14) * spA8) + D_hd_code_8036CB60[spB0].unk14;
            sp98 = ((D_hd_code_8036CB60[spAC].unk0 - D_hd_code_8036CB60[spB0].unk0) * spA8) + D_hd_code_8036CB60[spB0].unk0;
            sp94 = ((D_hd_code_8036CB60[spAC].unk4 - D_hd_code_8036CB60[spB0].unk4) * spA8) + D_hd_code_8036CB60[spB0].unk4;
            sp90 = (D_hd_code_8036CB60[spAC].unk8 - D_hd_code_8036CB60[spB0].unk8) * spA8 + D_hd_code_8036CB60[spB0].unk8;

            spA8 += D_hd_code_8036D184;
            if (spA8 >= 1.0) {
                spB4 += 1;
                spA8 = 0.0f;
            }

            sp8C = sp98 - spA4;
            if (sp8C < 0.0) {
                sp8C = (0.0 - sp8C);
            }

            sp88 = sp90 - sp9C;
            if (sp88 < 0.0) {
                sp88 = (f32) (0.0 - sp88);
            }
            if (((f64) sp8C > 0.5) || ((f64) sp88 > 0.5)) {
                guLookAtF(sp100, sp98, sp94, sp90, spA4, spA0, sp9C, 0.0f, 1.0f, 0.0f);
            } else {
                guLookAtF(sp100, (f32) ((f64) sp98 + 2.0), sp94, (f32) ((f64) sp90 + 2.0), spA4, spA0, sp9C, 0.0f, 1.0f, 0.0f);
            }
            sp14B = invertTransformMatrix(spC0, sp100);
            if (sp14B == 0) {
                rmonPrintf(ASSERT_MESSAGE, "flag", "mb.c", 0x223);
            }
            guMtxF2L(spC0, &D_hd_code_8036CC70[arg2][spBC]);
            gSPMatrix(entry++, (s32) &D_hd_code_8036CC70[arg2][spBC] & 0x1FFFFFFF, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            gSPVertex(entry++, (s32) D_hd_code_802FBEE0 & 0x1FFFFFFF, 16, 0);

            sp140 = 0;
            sp144 = 0;
            func_hd_code_8027A7DC(&entry, 0, 0);

            sp144 += 0xE10,
            sp140 += 4;
            func_hd_code_8027A7DC(&entry, sp144, sp140);

            sp144 += 0xE10,
            sp140 += 4;
            func_hd_code_8027A7DC(&entry, sp144, sp140);

            sp144 += 0xE10,
            sp140 += 4;
            func_hd_code_8027A7DC(&entry, sp144, sp140);

            sp144 += 0xE10,
            sp140 += 4;
            gSPVertex(entry++, (s32) (D_hd_code_802FBEE0 + 16) & 0x1FFFFFFF, 8, 0);

            sp140 = 0;
            func_hd_code_8027A7DC(&entry, sp144, 0);

            sp144 += 0xE10,
            sp140 += 4;
            func_hd_code_8027A7DC(&entry, sp144, sp140);

            sp144 += 0xE10,
            sp140 += 4;
            gSPPopMatrix(entry++, G_MTX_MODELVIEW);

            spBB -= spBA;
        }
        gDPPipeSync(entry++);
        gDPSetColorDither(entry++, G_CD_MAGICSQ);
        gDPPipeSync(entry++);

        *gfx = entry;
    }
}

// Draw one 120x15 strip of the captured blur frame (arg1 = byte offset into
// the capture buffer, arg2 = base vertex index)
// Proposed name: DrawBlurStrip
void func_hd_code_8027A7DC(Gfx** gfx, s32 arg1, s32 arg2) {
  Gfx* entry = *gfx;
  s32 pad;

  gDPLoadTextureBlock(entry++, OS_PHYSICAL_TO_K0(&D_hd_code_8036D170[arg1]), G_IM_FMT_RGBA, G_IM_SIZ_16b, 120, 15, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
  gSP1Triangle(entry++, arg2, arg2 + 1, arg2 + 2, 0);
  gSP1Triangle(entry++, arg2, arg2 + 2, arg2 + 3, 0);
  *gfx = entry;

}

// Undo the pivoting row swaps after the 3x3 inversion
// Proposed name: UnpivotInverse3
void func_hd_code_8027AA04(f32 arg0[][3], s32 arg1, s32 arg2, s32 arg3) {
  s32 spC;
  s32 sp8;
  f32 sp4;

  if (arg1 != 0) {
    if (arg2 == 0) {
      for(spC = 0; spC < 3; spC++) {
        sp4 = arg0[arg2][spC];
        arg0[arg2][spC] = arg0[arg1][spC];
        arg0[arg1][spC] = sp4;
      }

      sp8 = arg2;
      arg2 = arg1;
      arg1 = sp8;
    } else {
      for(spC = 0; spC < 3; spC++) {
        sp4 = arg0[arg3][spC];
        arg0[arg3][spC] = arg0[arg1][spC];
        arg0[arg1][spC] = sp4;
      }

      sp8 = arg3;
      arg3 = arg1;
      arg1 = sp8;
    }
  }
  if (arg2 != 1) {
    for(spC = 0; spC < 3; spC++) {
      sp4 = arg0[arg3][spC];
      arg0[arg3][spC] = arg0[arg2][spC];
      arg0[arg2][spC] = sp4;
    }

    sp8 = arg3;
    arg3 = arg2;
    arg2 = sp8;
  }
}

// Gauss-Jordan elimination steps 2 and 3 of the 3x3 inversion (after the
// first pivot column arg2 is done); returns 0 if singular
// Proposed name: InvertMtx3Tail
s32 func_hd_code_8027AC00(f32 arg0[3][3], f32 arg1[][3], s32 arg2) {
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;

    if (arg2 == 0) {
        sp2C = 1,
        sp28 = 2;
    } else {
        if (arg2 == 1) {
            sp2C = 0,
            sp28 = 2;
        } else {
            sp2C = 0,
            sp28 = 1;
        }
    }
    sp1C = arg0[sp2C][1];
    if (sp1C < 0.0f) {
        sp1C = -sp1C;
    }

    sp18 = arg0[sp28][1];
    if (sp18 < 0.0f) {
        sp18 = -sp18;
    }
    if (sp1C > sp18) {
        sp34 = sp2C;
    } else {
        sp34 = sp28;
    }
    if (sp34 == sp2C) {
        sp30 = sp28;
    } else {
        sp30 = sp2C;
    }
    if ((arg0[sp34][1] < EPSILON) && (arg0[sp34][1] > -EPSILON)) {
        return 0;
    }
    sp20 = (1.0 / (f64) arg0[sp34][1]);
    arg0[sp34][1] = 1.0f;
    arg0[sp34][2] = (arg0[sp34][2] * sp20);
    arg1[sp34][sp34] = sp20;
    arg1[sp34][arg2] *= sp20;

    for(sp24 = 0; sp24 < 3; sp24++) {
        if (sp24 != sp34) {
            sp20 = -arg0[sp24][1];
            arg0[sp24][1] = 0.0f;

            arg0[sp24][2] += sp20 * arg0[sp34][2];
            arg1[sp24][sp34] = arg1[sp34][sp34] * sp20;
            arg1[sp24][arg2] += sp20 * arg1[sp34][arg2];
        }
    }

    if ((arg0[sp30][2] < EPSILON) && (arg0[sp30][2] > -EPSILON)) {
        return 0;
    }
    sp20 = (1.0 / arg0[sp30][2]);
    arg0[sp30][2] = 1.0f;
    arg1[sp30][sp30] = sp20;
    arg1[sp30][arg2] *= sp20;
    arg1[sp30][sp34] *= sp20;
    for(sp24 = 0; sp24 < 3; sp24++) {
        if (sp24 != sp30) {
            sp20 = -arg0[sp24][2];
            arg0[sp24][2] = 0.0f;

            arg1[sp24][arg2] += sp20 * arg1[sp30][arg2];
            arg1[sp24][sp34] += sp20 * arg1[sp30][sp34];
            arg1[sp24][sp30] += sp20 * arg1[sp30][sp30];
        }
    }

    func_hd_code_8027AA04(arg1, arg2, sp34, sp30);
    return 1;
}

// Invert a 3x3 matrix in place by Gauss-Jordan elimination with partial
// pivoting, writing the inverse to arg1; returns 0 if singular
// Proposed name: InvertMtx3
s32 func_hd_code_8027B200(f32 arg0[3][3], f32 arg1[3][3]) {
  s32 sp5C;
  s32 sp58;
  f32 sp54;
  f32 sp50;
  f32 sp4C;
  f32 sp48;

  arg1[0][0] = arg1[1][1] = arg1[2][2] = 1.0f;
  arg1[0][1] = arg1[0][2] = arg1[1][0] = arg1[1][2] = arg1[2][0] = arg1[2][1] = 0.0f;

  sp50 = arg0[0][0];
  if (sp50 < 0.0f) {
    sp50 = -sp50;
  }

  sp4C = arg0[1][0];
  if (sp4C < 0.0f) {
    sp4C = -sp4C;
  }

  sp48 = arg0[2][0];
  if (sp48 < 0.0f) {
    sp48 = -sp48;
  }

  if (sp50 > sp4C) {
    if (sp50 > sp48) {
      sp58 = 0;
    } else {
      sp58 = 2;
    }
  } else if (sp4C > sp48) {
    sp58 = 1;
  } else {
    sp58 = 2;
  }

  if ((arg0[sp58][0] < EPSILON) && (arg0[sp58][0] > -EPSILON)) {
    return 0;
  }
  sp54 = 1.0 / arg0[sp58][0];
  arg0[sp58][0] = 1.0f;
  arg0[sp58][1] *= sp54;
  arg0[sp58][2] *= sp54;

  arg1[sp58][sp58] = sp54;

  for(sp5C = 0; sp5C < 3; sp5C++) {
    if (sp5C != sp58) {
      sp54 = -arg0[sp5C][0];

      arg0[sp5C][0] = 0.0f;
      arg0[sp5C][1] += sp54 * arg0[sp58][1];
      arg0[sp5C][2] += sp54 * arg0[sp58][2];

      arg1[sp5C][sp58] = sp54 * arg1[sp58][sp58];
    }
  }
  if (func_hd_code_8027AC00(arg0, arg1, sp58) == 0) {
    return 0;
  }
  return 1;
}

// Reduce the projective part of a 4x4 matrix before inversion (extracts the
// translation column and w scale, pivoting if w is ~0); returns 0 on failure
// Proposed name: ReduceMtx4Projective
s32 func_hd_code_8027B5D0(f32 arg0[4][4], f32 arg1[4], f32* arg2, s32* arg3) {
  s32 sp14;
  s32 sp10;
  f32 spC;
  f32 sp8;

  *arg3 = -1;

  if ((arg0[3][3] > 0.0f ? arg0[3][3] : -arg0[3][3]) < EPSILON) {
    sp8 = 0.0f;
    for(sp14 = 0; sp14 < 4; sp14++) {
      if (arg0[sp14][3] > sp8) {
        *arg3 = sp14;
        sp8 = arg0[*arg3][3];
      } else if (arg0[sp14][3] < -sp8) {
        *arg3 = sp14;
        sp8 = -arg0[*arg3][3];
      }
    }
    if (*arg3 < 0) {
      return 0;
    }
    for(sp10 = 0; sp10 < 4; sp10++) {
      spC = arg0[3][sp10];
      arg0[3][sp10] = arg0[*arg3][sp10];
      arg0[*arg3][sp10] = spC;
    }
  }

  arg1[0] = -arg0[0][3];
  arg1[1] = -arg0[1][3];
  arg1[2] = -arg0[2][3];
  *arg2 = 1.0 / arg0[3][3];

  arg0[0][3] = arg0[1][3] = arg0[2][3] = 0.0f;

  arg0[3][3] = 1.0f;

  arg0[3][0] *= *arg2;
  arg0[3][1] *= *arg2;
  arg0[3][2] *= *arg2;
  for(sp14 = 0; sp14 < 3; sp14++) {
    arg0[0][sp14] += arg1[0] * arg0[3][sp14];
    arg0[1][sp14] += arg1[1] * arg0[3][sp14];
    arg0[2][sp14] += arg1[2] * arg0[3][sp14];
  }

  return 1;
}

u8 invertTransformMatrix(f32 arg0[4][4], f32 arg1[4][4]) {
  f32 spA8[4][4];
  s32 i;
  s32 j;
  s32 sp9C;
  f32 sp78[3][3];
  f32 sp54[3][3];
  f32 sp50;
  f32 sp4C;
  f32 sp3C[4];
  f32 sp2C[4];
  s32 sp28;

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      spA8[i][j] = arg1[i][j];
      arg0[i][j] = 0.0f;
    }
  }
  arg0[0][0] = 1.0f;
  arg0[1][1] = 1.0f;
  arg0[2][2] = 1.0f;
  arg0[3][3] = 1.0f;

  sp9C = spA8[0][3] == 0.0 && spA8[1][3] == 0.0 && spA8[2][3] == 0.0 && spA8[3][3] == 1.0;
  if ((sp9C == 0) && (func_hd_code_8027B5D0(spA8, sp3C, &sp50, &sp28) == 0)) {
    return 0;
  }
  sp2C[0] = spA8[3][0];
  sp2C[1] = spA8[3][1];
  sp2C[2] = spA8[3][2];

  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      sp78[i][j] = spA8[i][j];
    }
  }
  if (func_hd_code_8027B200(sp78, sp54) == 0) {
    return 0;
  }

  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      arg0[i][j] = sp54[i][j];
    }
  }

  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      arg0[3][i] -= (sp2C[j] * sp54[j][i]);
    }
  }
  if (sp9C == 0) {
    for (i = 0; i < 4; i++) {
      arg0[i][3] += (sp3C[0] * arg0[i][0]) + (sp3C[1] * arg0[i][1]) + (sp3C[2] * arg0[i][2]);
      arg0[i][3] *= sp50;
    }
    if (sp28 >= 0) {
      for (i = 0; i < 4; i++) {
        sp4C = arg0[i][3];
        arg0[i][3] = arg0[i][sp28];
        arg0[i][sp28] = sp4C;
      }
    }
  }
  return 1;
}

