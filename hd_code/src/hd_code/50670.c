#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"
#include "macros.h"

struct S_8039CA68 {
  s32 unk0;
  s32 unk4;
  s32 unk8;
  s16 unkC;
  s16 unkE;
  s16 unk10;
  s16 unk12;
};

struct S_802FF150 {
  s32 unk0;
  s32 unk4;
  s32 unk8;
  s32 unkC;
  s32 unk10;
  s32 unk14;
  s32 unk18;
  s32 unk1C;
  s8 unk20[8];
  u8 unk28;
}; // Size: 0x2C

// Proposed file name: ghostdigger.c (the original name - the assert in
// func_hd_code_80295AE0 references "ghostdigger.c")
//
// This file is the race "ghost" system: while racing, the player's vehicle
// position/orientation is sampled every frame with a timestamp into a buffer
// (D_8039CA68[1]); if the run beats the saved best time it is copied to the
// ghost buffer (D_8039CA68[0]) at 0x80055400. On later runs the ghost is
// replayed - its transform interpolated to the current race time - and drawn
// as a translucent copy of the vehicle. The buffers live at fixed RAM
// addresses; up to 0xCCC samples. The last function here is an unrelated
// per-region override of the loaded-world-cell list.

s32 func_hd_code_80286038(u16);                       /* extern */
void func_hd_code_80295394(s32*, s32*, s32*, s16*, s16*, s16*); /* extern */
void func_hd_code_802AA6D0(s32, s32, s32, s16, s32, s32, s32, Mtx*); /* extern */
s16 func_hd_code_80295924(s16, s16, f32);           /* extern */
extern s32 D_8039CA78;
extern s32 D_8039CA84;
extern u8 D_8039CA7C;
extern void* D_803BDB00;
extern void* D_803BDB04;
extern void* D_803BDB08;
extern u8 D_8039CA7D;
extern u32 D_8039CA88;
extern u8 D_hd_code_803643D4;
extern u8 D_8039CA7D;
extern s32 D_8039CA70[2];
extern s32 D_8039CA80;
extern u8 D_8039CA8C;
extern s32 D_8039CA78;
extern u8 D_8039CA7C;
extern u8 D_8039CA7D;
extern u8 D_8039CA7E;
extern s32 D_8039CA84;
extern struct S_8039CA68* D_8039CA68[2];
extern s32 D_8039CA80;
extern s16 D_803ED390[3];
extern s8 D_hd_code_8030CD7C;
extern u16 D_803C30A8[];

// <data>
u32 D_hd_code_802FF0D0[19] = {
  0x00004E20, 0x00001B58, 0x00006590, 0x00002AF8,
  0x00002710, 0x00004268, 0x00001B58, 0x00003A98,
  0x000032C8, 0x00004268, 0x00003E80, 0x000088B8,
  0x00000000, 0x00004268, 0x000055F0, 0x000032C8,
  0x00002134, 0x000088B8, 0x000088B8
};

u32 D_hd_code_802FF11C[6][2] = {
  { 0x00552078, 0x005049D8 },
  { 0x005049D8, 0x005049D8 },
  { 0x00553078, 0x005049D8 },
  { 0x0C192078, 0x0C1849D8 },
  { 0x0C1849D8, 0x0C1849D8 },
  { 0x0C193078, 0x0C1849D8 }
};

u32 pad_802FF14C = 0;

struct S_802FF150 D_hd_code_802FF150[1] = {
  { 0x00028A00, 0x00028A00, 0x00032C80, 0x00032C80, 0x00012340, 0x0001B580, 0x00012340, 0x0001B580, { 0x01, 0x02, 0x04, 0x05, 0x08, 0xFF, 0x00, 0x00 }, 0x09 }
};

// </data>

// One-time ghost init: point the ghost and record buffers at their fixed RAM
// addresses and reset the best time
// Proposed name: InitGhost
void func_hd_code_80294E30(void) {
  D_8039CA68[0] = (struct S_8039CA68*)0x80055400;
  D_8039CA68[1] = (struct S_8039CA68*)0x80065400;
  D_8039CA88 = func_hd_code_80286038(0xFFFF) - 1;
  D_8039CA7D = 0;
}

// Start recording a new run: reset the sample count and enable recording
// Proposed name: StartGhostRecord
void func_hd_code_80294E88(void) {
  D_8039CA70[1] = 0;
  D_8039CA80 = -1;
  D_8039CA62 = 1;
  D_8039CA8C = 0;
}

// Start playing back the saved ghost (if one exists): reset the playback
// cursor and enable drawing
// Proposed name: StartGhostPlayback
void func_hd_code_80294EB8(void) {
  if (D_8039CA7D != 0) {
    D_8039CA61 = 1;
    D_8039CA84 = -1;
    D_8039CA78 = 0;
    D_8039CA7E = D_8039CA7C;
  }
}

// Record one ghost sample this frame: the player's position, orientation and
// the elapsed race time (warns and stops on buffer overrun)
// Proposed name: RecordGhostSample
void func_hd_code_80294F00(void) {
  if (D_hd_code_80364A90 & 0x104) {
    if (D_8039CA80 == -1) {
      D_8039CA80 = D_hd_code_803156C0;
    }
    if ((u32) D_8039CA70[1] < 0xCCCU) {
      D_8039CA68[1][D_8039CA70[1]].unk0 = D_hd_code_803643E0;
      D_8039CA68[1][D_8039CA70[1]].unk4 = D_hd_code_803643E4;
      D_8039CA68[1][D_8039CA70[1]].unk8 = D_hd_code_803643E8;
      D_8039CA68[1][D_8039CA70[1]].unkC = D_803ED390[0];
      D_8039CA68[1][D_8039CA70[1]].unkE = D_803ED390[1];
      D_8039CA68[1][D_8039CA70[1]].unk10 = D_803ED390[2];
      D_8039CA68[1][D_8039CA70[1]].unk12 = (D_hd_code_803156C0 - D_8039CA80);
      D_8039CA70[1]++;
      return;
    }
    D_8039CA8C = 1;
    rmonPrintf("OVERRUN GHOST DIGGER ARRAY\n");
  }
}

// Draw the ghost vehicle: sample its interpolated transform for the current
// race time (func_hd_code_80295394), build its matrix and draw the vehicle's
// display list translucently (prim alpha 0x64)
// Proposed name: DrawGhost
void func_hd_code_80295120(Gfx** gfx, struct Model1* arg1) {
  Gfx* entry = *gfx;
  s32 sp60;
  s32 sp5C;
  s32 sp58;
  s16 sp56;
  s16 sp54;
  s16 sp52;

  if (D_8039CA61 != 0) {
    func_hd_code_80295394(&sp60, &sp5C, &sp58, &sp56, &sp54, &sp52);
    func_hd_code_802AA6D0(sp60, sp5C, sp58, sp56, (s32) sp54, (s32) sp52, D_hd_code_802FF0D0[D_8039CA7C], &arg1->unk14C0);

    gSPSegment(entry++, 0x06, osVirtualToPhysical(D_803BDB04));
    gSPSegment(entry++, 0x07, osVirtualToPhysical(D_803BDB00));
    gSPMatrix(entry++, (u32) &D_2000000.unk14C0, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gDPPipeSync(entry++);
    gDPSetEnvColor(entry++, 0x00, 0x00, 0x00, 0xFF);
    gDPSetPrimColor(entry++, 0, 0, 0xFF, 0xFF, 0xFF, 0x64);
    gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
    gSPDisplayList(entry++, osVirtualToPhysical(D_803BDB08));
    gSPMatrix(entry++, (u32) &D_2000000.modelview, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(entry++);
  }
  *gfx = entry;
}

// Sample the ghost's position (arg0..2) and orientation (arg3..5) at the
// current race time, linearly interpolating between the two bracketing
// recorded samples (angles wrapped via func_hd_code_80295924)
// Proposed name: SampleGhost
void func_hd_code_80295394(s32* arg0, s32* arg1, s32* arg2, s16* arg3, s16* arg4, s16* arg5) {
    u8 sp2F;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    f32 sp18;

    sp28 = D_hd_code_803156C0 - D_8039CA84;
    if (D_hd_code_80364A90 == 0x2000) {
        *arg0 = D_8039CA68[0][0].unk0;
        *arg1 = D_8039CA68[0][0].unk4;
        *arg2 = D_8039CA68[0][0].unk8;
        *arg3 = D_8039CA68[0][0].unkC;
        *arg4 = D_8039CA68[0][0].unkE;
        *arg5 = D_8039CA68[0][0].unk10;
        D_8039CA84 = D_hd_code_803156C0;
        return;
    }
    sp2F = 0;
    while ((D_8039CA78 < D_8039CA70[0] - 2) && !sp2F) {
        if (sp28 >= D_8039CA68[0][D_8039CA78].unk12 && sp28 < D_8039CA68[0][D_8039CA78+1].unk12) {
            sp2F = 1;
        } else {
            D_8039CA78 += 1;
        }
    }
    sp2F = 0;
    sp24 = D_8039CA78 + 1;
    while ((sp24 < (D_8039CA70[0] - 2)) && (sp2F == 0)) {
        if (sp28 <= D_8039CA68[0][sp24].unk12) {
            sp2F = 1;
        } else {
            sp24 += 1;
        }
    }
    sp20 = D_8039CA68[0][sp24].unk12 - D_8039CA68[0][D_8039CA78].unk12;
    if (sp24 >= (D_8039CA70[0] - 2)) {
        sp1C = D_8039CA68[0][sp24].unk12 - D_8039CA68[0][D_8039CA78].unk12;
    } else {
        sp1C = sp28 - D_8039CA68[0][D_8039CA78].unk12;
    }
    sp18 = sp1C / (f32) sp20;
    *arg0 = (D_8039CA68[0][sp24].unk0 - D_8039CA68[0][D_8039CA78].unk0) * sp18 + D_8039CA68[0][D_8039CA78].unk0;
    *arg1 = (D_8039CA68[0][sp24].unk4 - D_8039CA68[0][D_8039CA78].unk4) * sp18 + D_8039CA68[0][D_8039CA78].unk4;
    *arg2 = (D_8039CA68[0][sp24].unk8 - D_8039CA68[0][D_8039CA78].unk8) * sp18 + D_8039CA68[0][D_8039CA78].unk8;
    *arg3 = func_hd_code_80295924(D_8039CA68[0][D_8039CA78].unkC, D_8039CA68[0][sp24].unkC, sp18);
    *arg4 = func_hd_code_80295924(D_8039CA68[0][D_8039CA78].unkE, D_8039CA68[0][sp24].unkE, sp18);
    *arg5 = func_hd_code_80295924(D_8039CA68[0][D_8039CA78].unk10, D_8039CA68[0][sp24].unk10, sp18);
}

// Interpolate between two angles (0..4095) by arg2, taking the shorter way
// around and wrapping the result
// Proposed name: LerpAngle
s16 func_hd_code_80295924(s16 arg0, s16 arg1, f32 arg2) {
  s16 sp6 = arg1 - arg0;

  if (sp6 >= -0x800) {
    if (sp6 >= 0x801) {
      sp6 -= 0xFFF;
    }
  } else {
    sp6 += 0xFFF;
  }

  arg2 *= sp6;
  arg2 += arg0;

  if (arg2 < 0.0) {
    arg2 += 4095.0;
  }

  if (arg2 > 4095.0) {
    arg2 -= 4095.0;
  }

  return arg2;
}

// If this run's time arg0 beats the saved ghost time, copy the recorded run
// into the ghost buffer and store the new best time
// Proposed name: SaveGhostIfBest
void func_hd_code_80295A20(u32 arg0) {
  u8* spC;
  u8* sp8;
  s32 sp4;

  if (D_8039CA88 >= arg0) {
    if (D_8039CA8C == 0) {
      D_8039CA7D = 1;
    } else {
      D_8039CA7D = 0;
    }

    spC = (u8*)&D_8039CA68[0][0];
    sp8 = (u8*)D_8039CA68[1];
    for(sp4 = 0; sp4 < 0x10000; sp4++) {
      spC[sp4] = sp8[sp4];
    }

    D_8039CA7C = D_hd_code_803643D4;
    D_8039CA70[0] = D_8039CA70[1];
    D_8039CA88 = arg0;
  }
}

// Patch the vehicle display list [gfx, arg1) for ghost rendering: force the
// combine to modulate-by-prim and translate each render mode through a
// 6-entry table to its translucent equivalent
// Proposed name: PatchGhostDisplayList
void func_hd_code_80295AE0(Gfx* gfx, Gfx* arg1) {
  s8 sp3F;
  s32 sp38;
  u8 sp37;
  s32 sp30;
  u32 sp2C;

  while (gfx != arg1) {
    sp3F = gfx->words.w0 >> 0x18;
    switch(sp3F) {
      case (s8)G_SETCOMBINE:
        gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        break;
      case G_SETOTHERMODE_L:
        sp38 = (u16)(gfx->words.w0 >> 8);
        if (sp38 == G_MDSFT_RENDERMODE) {
          sp2C = gfx->words.w1;
          sp30 = 0;
          sp37 = 0;

          while ((sp37 == 0) && (sp30 < 6)) {
            if (D_hd_code_802FF11C[sp30][0] == sp2C) {
              sp37 = 1;
            } else {
              sp30 += 1;
            }
          }

          if (sp37 == 0) {
            rmonPrintf(ASSERT_MESSAGE, "found", "ghostdigger.c", 0x152);
          }
          gfx->words.w1 = D_hd_code_802FF11C[sp30][1];
        }
        gfx++;
        break;
      default:
        gfx++;
        break;
    }
  }
}

// Override the loaded-world-cell list (D_803C30A8) when the player at
// (arg1, arg2) is inside a special region of level arg0 (table
// D_hd_code_802FF150) - forces a custom set of world cells to be considered
// loaded there
// Proposed name: ApplyRegionCellOverride
void func_hd_code_80295C70(u8 arg0, s32 arg1, s32 arg2) {
  s32 sp2C;
  s32 sp28;

  for(sp2C = 0; sp2C < 1; sp2C++) {
    if (D_hd_code_802FF150[sp2C].unk28 == arg0
        && (func_hd_code_802AC4C4(arg1, arg2, D_hd_code_802FF150[sp2C].unk0, D_hd_code_802FF150[sp2C].unk10, D_hd_code_802FF150[sp2C].unk4, D_hd_code_802FF150[sp2C].unk14, D_hd_code_802FF150[sp2C].unk8, D_hd_code_802FF150[sp2C].unk18) != 0
            || (func_hd_code_802AC4C4(arg1, arg2, D_hd_code_802FF150[sp2C].unk0, D_hd_code_802FF150[sp2C].unk10, D_hd_code_802FF150[sp2C].unk8, D_hd_code_802FF150[sp2C].unk18, D_hd_code_802FF150[sp2C].unkC, D_hd_code_802FF150[sp2C].unk1C) != 0))) {
      sp28 = 0;
      while (D_hd_code_802FF150[sp2C].unk20[sp28] != -1) {
        D_803C30A8[sp28] = D_hd_code_802FF150[sp2C].unk20[sp28];
        sp28++;
      }
      D_803C30A8[sp28] = 0xFFFF;
    }
  }
}

