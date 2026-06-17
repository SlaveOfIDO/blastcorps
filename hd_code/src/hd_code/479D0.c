#include "common.h"
#include "functions.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"

struct S_8039AF00 {
  s16 unk0;
  s16 unk2;
  s16 unk4;
  u8 unk6;
  u8 unk7; // is transparent
  s16 unk8; // alpha
  s16 padA;
  u8* unkC; // texture data
  u8* unk10; // texture data
  Vtx* unk14; // 8 vertices
}; // Size: 0x18

struct S_802FDB40 {
  s16 unk0;
  s16 unk2;
  s16 unk4;
  s16 unk6;
  s16 unk8;
  s16 unkA;
  s16 unkC;
  s16 unkE;
  s16 unk10;
  s16 unk12;
  u8 unk14;
}; // Size: 0x16


struct S_AmmoData {
  s16 unk0;
  s16 unk2;
  s16 unk4;
  s16 unk6;

}; // Size: unknown

// Proposed file name: crates.c
//
// This file is the collectible crate system: 3D textured boxes placed in a
// level that the player collects by driving close, incrementing a vehicle
// ammo/charge counter (D_803F8B72 or D_803EDC00, the counters shown by the
// vehicle gauges in 42240.c) and fading out. Each crate type's geometry,
// textures, pickup radius and which counter it feeds come from the
// D_hd_code_802FDB40 template table; live crates live in D_8039AF00.

void func_hd_code_8028C41C(Vtx* arg0, u8 arg1, s16 x, s16 y, s16 z);

extern struct S_8039AF00 D_8039AF00[];
extern s32 D_8039B068;

// <data>
struct S_802FDB40 D_hd_code_802FDB40[2] = {
  { 0xFFF6, 0x000A, 0x0000, 0x0014, 0xFFF6, 0x000A, 0x0995, 0x0995, 0x0280, 0x0064, 0x0A  },
  { 0xFFF6, 0x000A, 0x0000, 0x0014, 0xFFF6, 0x000A, 0x0997, 0x0997, 0x0280, 0x0064, 0x01 }
};
// </data>

// Build the live crate list from the level's crate placements [arg0, arg1):
// copy position and type, load the two textures for that type, allocate and
// fill the 8-vertex box geometry
// (already partially named: LoadLevelAmmo)
void LoadLevelAmmo(struct S_AmmoData* arg0, s32 arg1) {
  D_8039B068 = 0;
  while ((s32)arg0 != arg1) {
    D_8039AF00[D_8039B068].unk0 = arg0->unk0;
    D_8039AF00[D_8039B068].unk2 = arg0->unk2;
    D_8039AF00[D_8039B068].unk4 = arg0->unk4;
    D_8039AF00[D_8039B068].unk6 = arg0->unk6;
    D_8039AF00[D_8039B068].unk7 = 0;
    D_8039AF00[D_8039B068].unk8 = 0xFF;
    D_8039AF00[D_8039B068].unkC = func_hd_code_802A0CC8(D_hd_code_802FDB40[D_8039AF00[D_8039B068].unk6].unkC, 0);
    D_8039AF00[D_8039B068].unk10 = func_hd_code_802A0CC8(D_hd_code_802FDB40[D_8039AF00[D_8039B068].unk6].unkE, 0);
    D_8039AF00[D_8039B068].unk14 = (Vtx*)D_hd_code_80358070;
    D_hd_code_80358070 += 0x80;
    func_hd_code_8028C41C(D_8039AF00[D_8039B068].unk14,
                          D_8039AF00[D_8039B068].unk6,
                          D_8039AF00[D_8039B068].unk0,
                          D_8039AF00[D_8039B068].unk2,
                          (s32) D_8039AF00[D_8039B068].unk4);
    D_8039B068 += 1;
    arg0++;
  }
}

// Fill the 8 corner vertices of a crate box of type arg1 at (x, y, z), using
// the type's min/max extents and box-mapped texcoords
// Proposed name: BuildCrateBox
void func_hd_code_8028C41C(Vtx* arg0, u8 arg1, s16 x, s16 y, s16 z) {
  arg0[0].v.ob[0] = D_hd_code_802FDB40[arg1].unk2 + x;
  arg0[0].v.ob[1] = D_hd_code_802FDB40[arg1].unk4 + y;
  arg0[0].v.ob[2] = D_hd_code_802FDB40[arg1].unk8 + z;
  arg0[0].v.tc[1] = 0;
  arg0[0].v.tc[0] = 0;
  arg0[1].v.ob[0] = D_hd_code_802FDB40[arg1].unk2 + x;
  arg0[1].v.ob[1] = D_hd_code_802FDB40[arg1].unk6 + y;
  arg0[1].v.ob[2] = D_hd_code_802FDB40[arg1].unk8 + z;
  arg0[1].v.tc[1] = 0x1E0;
  arg0[1].v.tc[0] = 0;
  arg0[2].v.ob[0] = D_hd_code_802FDB40[arg1].unk2 + x;
  arg0[2].v.ob[1] = D_hd_code_802FDB40[arg1].unk6 + y;
  arg0[2].v.ob[2] = D_hd_code_802FDB40[arg1].unkA + z;
  arg0[2].v.tc[0] = 0x1E0,
  arg0[2].v.tc[1] = 0x1E0;
  arg0[3].v.ob[0] = D_hd_code_802FDB40[arg1].unk2 + x;
  arg0[3].v.ob[1] = D_hd_code_802FDB40[arg1].unk4 + y;
  arg0[3].v.ob[2] = D_hd_code_802FDB40[arg1].unkA + z;
  arg0[3].v.tc[0] = 0x1E0;
  arg0[3].v.tc[1] = 0;
  arg0[4].v.ob[0] = D_hd_code_802FDB40[arg1].unk0 + x;
  arg0[4].v.ob[1] = D_hd_code_802FDB40[arg1].unk4 + y;
  arg0[4].v.ob[2] = D_hd_code_802FDB40[arg1].unk8 + z;
  arg0[4].v.tc[0] = 0x1E0;
  arg0[4].v.tc[1] = 0;
  arg0[5].v.ob[0] = D_hd_code_802FDB40[arg1].unk0 + x;
  arg0[5].v.ob[1] = D_hd_code_802FDB40[arg1].unk6 + y;
  arg0[5].v.ob[2] = D_hd_code_802FDB40[arg1].unk8 + z;
  arg0[5].v.tc[0] = 0x1E0,
  arg0[5].v.tc[1] = 0x1E0;
  arg0[6].v.ob[0] = D_hd_code_802FDB40[arg1].unk0 + x;
  arg0[6].v.ob[1] = D_hd_code_802FDB40[arg1].unk6 + y;
  arg0[6].v.ob[2] = D_hd_code_802FDB40[arg1].unkA + z;
  arg0[6].v.tc[1] = 0x1E0;
  arg0[6].v.tc[0] = 0;
  arg0[7].v.ob[0] = D_hd_code_802FDB40[arg1].unk0 + x;
  arg0[7].v.ob[1] = D_hd_code_802FDB40[arg1].unk4 + y;
  arg0[7].v.ob[2] = D_hd_code_802FDB40[arg1].unkA + z;
  arg0[7].v.tc[1] = 0;
  arg0[7].v.tc[0] = 0;
}

// Per-frame crate update (arg0 = current vehicle): for each uncollected
// crate, register it with the collision system - or, if it is meant for the
// current vehicle and the player is within its pickup radius, collect it
// (play sfx 0x70, bump the matching counter by 10, start its fade-out).
// Collected crates fade their alpha out.
// Proposed name: UpdateCrates
void func_hd_code_8028C874(u8 arg0) {
  s32 i;
  s32 distance;

  for(i = 0; i < D_8039B068; i++) {
    if ((u8) D_8039AF00[i].unk7 == 0) {
      if (D_hd_code_802FDB40[D_8039AF00[i].unk6].unk14 == arg0) {
        func_hd_code_802CE90C(i + 0x10000);
        distance = func_hd_code_8026A6F0(
            (s32) D_hd_code_803643E0 >> 5,
            (s32) D_hd_code_803643E4 >> 5,
            (s32) D_hd_code_803643E8 >> 5,
            (s32) D_8039AF00[i].unk0,
            (s32) D_8039AF00[i].unk2,
            (s32) D_8039AF00[i].unk4);

        if (distance <= D_hd_code_802FDB40[D_8039AF00[i].unk6].unk12) {
          D_8039AF00[i].unk7 = 1;
          sndPlaySfx(D_hd_code_80367738, 0x70, NULL);
          switch (D_8039AF00[i].unk6) {
            case 0:
              D_803F8B72 += 10;
              break;
            case 1:
              D_803EDC00 += 10;
              break;
          }
        }
      } else {
        func_hd_code_802CE880(i + 0x10000,
                              D_8039AF00[i].unk0 << 5,
                              D_8039AF00[i].unk2 << 5,
                              D_8039AF00[i].unk4 << 5,
                              D_hd_code_802FDB40[D_8039AF00[i].unk6].unk10);
      }
    } else {
      D_8039AF00[i].unk8 -= 20;
      if (D_8039AF00[i].unk8 < 0) {
        D_8039AF00[i].unk8 = 0;
      }
    }
  }
}

// Draw the crates: each visible box is drawn with its main texture on the
// four side faces (UV-remapped per face via gSPModifyVertex) and a second
// texture on the top, opaque while live and translucent (by alpha) while
// fading out
// Proposed name: DrawCrates
void func_hd_code_8028CB30(Gfx** gfx, s32* arg1) {
    Gfx* entry = *gfx;
    s32 spE0;
    u8 spDF = 0;

    gDPPipeSync(entry++);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    gDPSetCombineLERP(entry++, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE);
    gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
    gSPSetGeometryMode(entry++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);


    for(spE0 = 0; spE0 < D_8039B068; spE0++) {
        if (((u8) D_8039AF00[spE0].unk7 == 0) || (D_8039AF00[spE0].unk8 != 0)) {
            gDPPipeSync(entry++);

            if ((D_8039AF00[spE0].unk7 == 0) && ((spDF == 0) || (spDF == 2))) {
                gDPSetRenderMode(entry++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
                spDF = 1;
            }
            if ((D_8039AF00[spE0].unk7 != 0) && ((spDF == 0) || (spDF == 1))) {
                gDPSetRenderMode(entry++, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
                spDF = 2;
            }
            gDPSetPrimColor(entry++, 0, 0, 0, 0, 0, D_8039AF00[spE0].unk8);

            gSPVertex(entry++, osVirtualToPhysical(D_8039AF00[spE0].unk14), 8, 0);

            gDPSetTextureImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, D_8039AF00[spE0].unkC + 0x80000000);

            gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
            gDPLoadSync(entry++);
            gDPLoadBlock(entry++, G_TX_LOADTILE, 0, 0, 255, 512);
            gDPPipeSync(entry++);
            gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
            gDPSetTileSize(entry++, G_TX_RENDERTILE, 0, 0, qu102(15), qu102(15));
            gSP1Triangle(entry++, 6, 3, 2, 0);
            gSP1Triangle(entry++, 6, 7, 3, 0);
            gSP1Triangle(entry++, 4, 1, 0, 0);
            gSP1Triangle(entry++, 1, 4, 5, 0);

            gSPModifyVertex(entry++, 0, 20, 0x01E00000);
            gSPModifyVertex(entry++, 1, 20, 0x01E001E0);
            gSPModifyVertex(entry++, 2, 20, 0x1E0);
            gSPModifyVertex(entry++, 3, 20, 0);

            gSP1Triangle(entry++, 0, 1, 2, 0);
            gSP1Triangle(entry++, 0, 2, 3, 0);

            gSPModifyVertex(entry++, 7, 20, 0x01E00000);
            gSPModifyVertex(entry++, 6, 20, 0x01E001E0);
            gSPModifyVertex(entry++, 5, 20, 0x1E0);
            gSPModifyVertex(entry++, 4, 20, 0);

            gSP1Triangle(entry++, 7, 5, 4, 0);
            gSP1Triangle(entry++, 7, 6, 5, 0);

            gDPLoadTextureBlock(entry++, D_8039AF00[spE0].unk10 + 0x80000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

            gSPModifyVertex(entry++, 2, 20, 0);
            gSPModifyVertex(entry++, 1, 20, 0x01E00000);
            gSPModifyVertex(entry++, 5, 20, 0x01E001E0);
            gSPModifyVertex(entry++, 6, 20, 0x1E0);

            gSP1Triangle(entry++, 5, 2, 1, 0);
            gSP1Triangle(entry++, 2, 5, 6, 0);
        }
    }

    gDPPipeSync(entry++);
    *gfx = entry;
}

