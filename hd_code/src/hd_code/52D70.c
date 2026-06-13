#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"
#include "macros.h"

u8 func_hd_code_8029766C(u8, u8*);                  /* extern */
extern s16 D_8039CAB0;
extern s16 D_8039CAB2;
extern s16 D_8039CAB4;
extern u8 D_8039CAB6;
extern u8 D_8039CAB8;
extern Mtx* D_8039CAC4;
extern u8 D_8039CAC8;
extern Gfx* D_8039CABC;
extern void* D_8039CAC0;


void func_hd_code_80297530(u8 arg0) {
  u8 sp1F;
  u8 sp1E;

  sp1F = 0;
  if (D_hd_code_80364A98 == 0x2000) {
    sp1F = func_hd_code_8029766C(arg0, &sp1E);
  } else {
    sp1F = 0;
  }
  D_8039CAC8 = players[playerNumber].unk90;
  if (sp1F != 0) {
    D_8039CAB7 = 1;
    D_8039CAB0 = D_hd_code_802E8F38[sp1E].unk2;
    D_8039CAB2 = D_hd_code_802E8F38[sp1E].unk4;
    D_8039CAB4 = D_hd_code_802E8F38[sp1E].unk6;
    D_8039CAB6 = sp1E;
    D_8039CAB8 = 0;
    D_8039CAC4 = (Mtx*)D_hd_code_80358070;
    D_hd_code_80358070 += 2 * sizeof(Mtx);
    guTranslate(&D_8039CAC4[0], 0.0f, 0.0f, 0.0f);
    guTranslate(&D_8039CAC4[1], 0.0f, 0.0f, 0.0f);
    return;
  }
  D_8039CAB7 = 0;
}

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

void func_hd_code_802976E8(Gfx** gfx) {
  Gfx* entry = *gfx;

  if (D_8039CAB7 != 0) {
    gSPSegment(entry++, 0x06, osVirtualToPhysical(D_8039CAC0));
    gSPSegment(entry++, 0x07, osVirtualToPhysical(D_8039CAC4));
    gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
    gSPDisplayList(entry++, osVirtualToPhysical(D_8039CABC));
    gDPPipeSync(entry++);

  }
  *gfx = entry;
}

void func_hd_code_80297804(s32 arg0, s32 arg1, s32 arg2) {
  if ((D_8039CAB7 != 0) && (players[playerNumber].unk91 < 5)) {
    if (D_8039CAB8 != 0) {
      if (func_hd_code_8026A6F0(arg0 >> 5, arg1 >> 5, arg2 >> 5, (s32) D_8039CAB0, (s32) D_8039CAB2, (s32) D_8039CAB4) >= 0x8D) {
        D_8039CAB8 = 0;
      }
    } else if (func_hd_code_8026A6F0(arg0 >> 5, arg1 >> 5, arg2 >> 5, (s32) D_8039CAB0, (s32) D_8039CAB2, (s32) D_8039CAB4) < 0x50) {
      D_8039CAB8 = 1;
      D_8039CAC8 |= 1 << D_8039CAB6;
      D_hd_code_80364A98 = 0x1000000000;
    }
  }
}

void func_hd_code_80297960(void) {
  if ((D_hd_code_802FA268 != 0) && (D_80370C28 & 0x2000) && (D_8039CAB7 != 0)) {
    D_8039CAC8 |= 1 << D_8039CAB6;
  }
  players[playerNumber].unk90 = D_8039CAC8;
}

