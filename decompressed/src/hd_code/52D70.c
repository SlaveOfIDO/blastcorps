#include "common.h"
#include "functions.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"

extern s16 D_hd_code_8039CAB0;
extern s16 D_hd_code_8039CAB2;
extern s16 D_hd_code_8039CAB4;
extern u8 D_hd_code_8039CAB8;
extern Mtx* D_hd_code_8039CAC4;
extern u8 D_hd_code_8039CAC8;
extern Gfx* D_hd_code_8039CABC;
extern void* D_hd_code_8039CAC0;

// Proposed file name: academy_marker.c
//
// This file handles the academy-test location marker: on the six special
// academy levels (positions in D_hd_code_802E8F38, the same table used by the
// campaign code in 41930.c) a marker is placed that the player must drive to.
// Reaching it sets the matching bit in the player's academy-passed mask
// (unk90) and triggers the completion state. D_hd_code_8039CAB7 = marker active,
// D_hd_code_8039CAB8 = player currently inside it.

// Set up the academy marker when entering an academy level: if the level has
// an entry in D_hd_code_802E8F38, record its position and allocate its
// matrices; otherwise disable the marker
// Proposed name: InitAcademyMarker
void func_hd_code_80297530(u8 arg0) {
  u8 sp1F;
  u8 sp1E;

  sp1F = 0;
  if (D_hd_code_80364A98 == 0x2000) {
    sp1F = func_hd_code_8029766C(arg0, &sp1E);
  } else {
    sp1F = 0;
  }
  D_hd_code_8039CAC8 = players[playerNumber].unk90;
  if (sp1F != 0) {
    D_hd_code_8039CAB7 = 1;
    D_hd_code_8039CAB0 = D_hd_code_802E8F38[sp1E].unk2;
    D_hd_code_8039CAB2 = D_hd_code_802E8F38[sp1E].unk4;
    D_hd_code_8039CAB4 = D_hd_code_802E8F38[sp1E].unk6;
    D_hd_code_8039CAB6 = sp1E;
    D_hd_code_8039CAB8 = 0;
    D_hd_code_8039CAC4 = (Mtx*)D_hd_code_80358070;
    D_hd_code_80358070 += 2 * sizeof(Mtx);
    guTranslate(&D_hd_code_8039CAC4[0], 0.0f, 0.0f, 0.0f);
    guTranslate(&D_hd_code_8039CAC4[1], 0.0f, 0.0f, 0.0f);
    return;
  }
  D_hd_code_8039CAB7 = 0;
}

// Look up level arg0 in the academy position table; returns 1 and the index
// (*arg1) if found
// Proposed name: FindAcademyLevel
u8 func_hd_code_8029766C(u8 arg0, u8* arg1) {
  u8 sp7;
  s32 sp0;

  sp7 = 0;
  sp0 = 0;
  while ((sp7 == 0) && (sp0 < 6)) {
    if (D_hd_code_802E8F38[sp0].unk0 == (arg0 )) {
      sp7 = 1;
    } else {
      sp0 += 1;
    }
  }
  if (arg1 != NULL) {
    *arg1 = sp0;
  }
  return sp7;
}

// Draw the academy marker's display list (when active)
// Proposed name: DrawAcademyMarker
void func_hd_code_802976E8(Gfx** gfx) {
  Gfx* entry = *gfx;

  if (D_hd_code_8039CAB7 != 0) {
    gSPSegment(entry++, 0x06, osVirtualToPhysical(D_hd_code_8039CAC0));
    gSPSegment(entry++, 0x07, osVirtualToPhysical(D_hd_code_8039CAC4));
    gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
    gSPDisplayList(entry++, osVirtualToPhysical(D_hd_code_8039CABC));
    gDPPipeSync(entry++);

  }
  *gfx = entry;
}

// Per-frame academy marker proximity check: when the player at
// (arg0, arg1, arg2) drives within 0x50 units of the marker, mark this
// academy test passed (set its bit, trigger state 0x1000000000); requires
// leaving a 0x8D radius before it can re-trigger
// Proposed name: CheckAcademyMarker
void func_hd_code_80297804(s32 arg0, s32 arg1, s32 arg2) {
  if ((D_hd_code_8039CAB7 != 0) && (players[playerNumber].unk91 < 5)) {
    if (D_hd_code_8039CAB8 != 0) {
      if (func_hd_code_8026A6F0(arg0 >> 5, arg1 >> 5, arg2 >> 5, (s32) D_hd_code_8039CAB0, (s32) D_hd_code_8039CAB2, (s32) D_hd_code_8039CAB4) >= 0x8D) {
        D_hd_code_8039CAB8 = 0;
      }
    } else if (func_hd_code_8026A6F0(arg0 >> 5, arg1 >> 5, arg2 >> 5, (s32) D_hd_code_8039CAB0, (s32) D_hd_code_8039CAB2, (s32) D_hd_code_8039CAB4) < 0x50) {
      D_hd_code_8039CAB8 = 1;
      D_hd_code_8039CAC8 |= 1 << D_hd_code_8039CAB6;
      D_hd_code_80364A98 = 0x1000000000;
    }
  }
}

// Commit the academy-passed mask back to the player's save (also lets the
// "give all coins" debug flag + Z mark it passed)
// Proposed name: SaveAcademyProgress
void func_hd_code_80297960(void) {
  if ((D_hd_code_802FA268 != 0) && (D_hd_code_80370C28 & 0x2000) && (D_hd_code_8039CAB7 != 0)) {
    D_hd_code_8039CAC8 |= 1 << D_hd_code_8039CAB6;
  }
  players[playerNumber].unk90 = D_hd_code_8039CAC8;
}

