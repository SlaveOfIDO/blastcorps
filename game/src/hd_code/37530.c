#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"

s32 func_hd_code_8027BCF0(s16 arg0, s16 arg1, s16 arg2);
void func_hd_code_8027D350(s16 x1, s16 y1, s16 z1, s16 x2, s16 y2, s16 z2, Vtx* arg6, s32 arg7);
void func_hd_code_8027D5AC();                          /* extern */

struct S_802FC368_sub {
  s16 unk0;
  s16 unk2;
  s16 unk4;
  s16 unk6;
  s16 unk8;
  s16 unkA;
  s16 unkC;
  s16 unkE;
}; // size: 0x10

struct S_802FC368 {
  struct S_802FC368_sub *unk0; // first
  struct S_802FC368_sub *unk4; // last
  u8 unk8;
}; // Size: 0xC

struct S_8036D3D0 {
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
  s16 unk14;
  s16 unk16;
  u8 unk18;
  u8 unk19;
  u8 unk1A;
  u8 unk1B;
}; // Size: 0x1C


// Proposed file name: tracks.c
//
// This file is the tire track / skid mark system. Each frame a driving
// vehicle records a track segment - both wheels' edge points, rotated by the
// vehicle heading - into an 80-entry ring buffer (D_hd_code_8036D3D0); consecutive
// segments connect into triangle strips (a frame gap or the per-vehicle
// strip length limit starts a new strip), drawn as black translucent
// geometry with per-vertex alpha. Long strips get a culling bounding box
// (gSPCullDisplayList). When the ring is nearly full the oldest segments
// fade out and are retired. Per-level "no track" zones (D_hd_code_802FC360,
// e.g. water) suppress recording.
// Segment fields: unk0..unkA = left track edge points, unkC..unk16 = right
// track edge points, unk18/19 = left/right alpha, unk1A = strip-break flag,
// unk1B = single-track flag.

extern struct S_802FC368 D_hd_code_802FC360[11]; // per-level no-track zone lists {first, last, level}; proposed name: noTrackZones
extern struct S_8036D3D0 D_hd_code_8036D3D0[0x50]; // track segment ring buffer; proposed name: trackSegments

extern u8 D_hd_code_8036DC90; // ring tail (oldest); proposed name: trackTail
extern u8 D_hd_code_8036DC91; // ring head (write position); proposed name: trackHead
extern u8 D_hd_code_8036DC92; // segments in the current strip; proposed name: trackStripLen
extern u32 D_hd_code_8036DC94; // frame of the last recorded segment (gap = new strip); proposed name: trackLastFrame


// <data>
struct S_802FC368_sub D_hd_code_802FC080[4] = {
  { 0x10CC, 0x1294, 0x10CC, 0x1249, 0x0CAF, 0x1249, 0x00C3, 0x00D2 },
  { 0x10CC, 0x1294, 0x0CAF, 0x1249, 0x0CAF, 0x1294, 0x00C3, 0x00D2 },
  { 0x14C9, 0x1F10, 0x1441, 0x1F10, 0x14C9, 0x1BE7, 0x00C3, 0x00D2 },
  { 0x1441, 0x1F10, 0x14C9, 0x1BE7, 0x1441, 0x1BE7, 0x00C3, 0x00D2 }
};

struct S_802FC368_sub D_hd_code_802FC0C0[4] = {
  { 0x0F48, 0x0C6B, 0x10F6, 0x0C71, 0x0F48, 0x0D06, 0x005F, 0x0069 },
  { 0x10F6, 0x0C71, 0x0F48, 0x0D06, 0x10F6, 0x0D06, 0x005F, 0x0069 },
  { 0x0E18, 0x0D00, 0x0E18, 0x0D7C, 0x0A46, 0x0CB9, 0x005F, 0x0069 },
  { 0x0E18, 0x0D7C, 0x0A46, 0x0CB9, 0x0A46, 0x0DC6, 0x005F, 0x0069 }
};

struct S_802FC368_sub D_hd_code_802FC100[2] = {
  { 0x0D68, 0x1077, 0x0E2F, 0x0FF3, 0x0E1E, 0x0E8A, 0x0190, 0x01FE },
  { 0x0D68, 0x1077, 0x0E1E, 0x0E8A, 0x0D58, 0x0F10, 0x0190, 0x01FE }
};

struct S_802FC368_sub D_hd_code_802FC120[4] = {
  { 0x1A53, 0x0DAC, 0x193A, 0x0DB9, 0x1A4E, 0x126B, 0x00AA, 0x00CD },
  { 0x193A, 0x0DB9, 0x1A4E, 0x126B, 0x1940, 0x1259, 0x00AA, 0x00CD },
  { 0x233D, 0x1EC9, 0x2350, 0x1F5E, 0x1F2D, 0x1EE3, 0x0028, 0x00BE },
  { 0x233D, 0x1EC9, 0x1F2D, 0x1EE3, 0x1F5E, 0x1E27, 0x0028, 0x00BE }
};

struct S_802FC368_sub D_hd_code_802FC160[2] = {
  { 0x0996, 0x0525, 0x0AEA, 0x0525, 0x0AEA, 0x05A7, 0x0118, 0x013E },
  { 0x0996, 0x0525, 0x0AEA, 0x05A7, 0x0996, 0x05A7, 0x0118, 0x013E }
};

struct S_802FC368_sub D_hd_code_802FC180[6] = {
  { 0x0E55, 0x0E27, 0x0E50, 0x0D9B, 0x0DB7, 0x0D8A, 0x015E, 0x01C2 },
  { 0x0E55, 0x0E27, 0x0DB7, 0x0D8A, 0x0DBD, 0x0E3C, 0x015E, 0x01C2 },
  { 0x0E48, 0x143B, 0x0E5F, 0x139D, 0x0DAD, 0x1383, 0x015E, 0x01C2 },
  { 0x0E48, 0x143B, 0x0DAD, 0x1383, 0x0DB7, 0x1451, 0x015E, 0x01C2 },
  { 0x0E52, 0x1A52, 0x0E54, 0x19AA, 0x0DB7, 0x199C, 0x015E, 0x01C2 },
  { 0x0E52, 0x1A52, 0x0DB7, 0x199C, 0x0DBB, 0x1A69, 0x015E, 0x01C2 }
};

struct S_802FC368_sub D_hd_code_802FC1E0[8] = {
  { 0x045C, 0x01C2, 0x071B, 0x01C2, 0x071B, 0x02DA, 0x0050, 0x00C8 },
  { 0x045C, 0x01C2, 0x071B, 0x02DA, 0x045C, 0x02DA, 0x0050, 0x00C8 },
  { 0x045C, 0x05BE, 0x071B, 0x05BE, 0x071B, 0x06B8, 0x0050, 0x00C8 },
  { 0x045C, 0x05BE, 0x071B, 0x06B8, 0x045C, 0x06B8, 0x0050, 0x00C8 },
  { 0x045C, 0x078A, 0x071B, 0x078A, 0x071B, 0x08A5, 0x0050, 0x00C8 },
  { 0x045C, 0x078A, 0x071B, 0x08A5, 0x045C, 0x08A5, 0x0050, 0x00C8 },
  { 0x045C, 0x0A73, 0x071B, 0x0A73, 0x071B, 0x0B59, 0x0050, 0x00C8 },
  { 0x045C, 0x0A73, 0x071B, 0x0B59, 0x045C, 0x0B59, 0x0050, 0x00C8 }
};

struct S_802FC368_sub D_hd_code_802FC260[2] = {
  { 0x06EE, 0x07DA, 0x06E9, 0x08BF, 0x0882, 0x089C, 0x000A, 0x00C8 },
  { 0x06EE, 0x07DA, 0x0882, 0x089C, 0x0882, 0x07EC, 0x000A, 0x00C8 }
};

struct S_802FC368_sub D_hd_code_802FC280[8] = {
  { 0x1703, 0x0ABC, 0x178C, 0x0ADE, 0x17F4, 0x098C, 0x012C, 0x015E },
  { 0x1703, 0x0ABC, 0x17F4, 0x098C, 0x1782, 0x0975, 0x012C, 0x015E },
  { 0x1450, 0x1584, 0x14C3, 0x1584, 0x137E, 0x1A6F, 0x012C, 0x015E },
  { 0x1450, 0x1584, 0x137E, 0x1A6F, 0x12EB, 0x1A4C, 0x012C, 0x015E },
  { 0x122E, 0x0C83, 0x12F2, 0x0C8B, 0x12F2, 0x0EAC, 0x012C, 0x015E },
  { 0x122E, 0x0C83, 0x12F2, 0x0EAC, 0x122E, 0x0EAC, 0x012C, 0x015E },
  { 0x122E, 0x1554, 0x12F2, 0x1554, 0x12F2, 0x1A72, 0x012C, 0x015E },
  { 0x122E, 0x1554, 0x12F2, 0x1A72, 0x122E, 0x1A72, 0x012C, 0x015E }
};

struct S_802FC368_sub D_hd_code_802FC300[2] = {
  { 0x09F3, 0x0F0C, 0x0972, 0x0FE1, 0x0BC4, 0x111F, 0x012C, 0x01C2 },
  { 0x09F3, 0x0F0C, 0x0BC4, 0x111F, 0x0C21, 0x10B0, 0x012C, 0x01C2 }
};

struct S_802FC368_sub D_hd_code_802FC320[4] = {
  { 0x081A, 0x0FA7, 0x0954, 0x10AC, 0x0874, 0x1304, 0x0000, 0x012C },
  { 0x081A, 0x0FA7, 0x0874, 0x1304, 0x068C, 0x116A, 0x0000, 0x012C },
  { 0x0AF2, 0x11F9, 0x0C3A, 0x12FB, 0x0ACB, 0x14E6, 0x0000, 0x012C },
  { 0x0AF2, 0x11F9, 0x0ACB, 0x14E6, 0x08EF, 0x1370, 0x0000, 0x012C }
};
struct S_802FC368 D_hd_code_802FC360[11] = {
  { D_hd_code_802FC080, D_hd_code_802FC0C0, 0x1D },
  { D_hd_code_802FC0C0, D_hd_code_802FC100, 0x09 },
  { D_hd_code_802FC100, D_hd_code_802FC120, 0x02 },
  { D_hd_code_802FC120, D_hd_code_802FC160, 0x10 },
  { D_hd_code_802FC160, D_hd_code_802FC180, 0x11 },
  { D_hd_code_802FC180, D_hd_code_802FC1E0, 0x0C },
  { D_hd_code_802FC1E0, D_hd_code_802FC260, 0x12 },
  { D_hd_code_802FC260, D_hd_code_802FC280, 0x00 },
  { D_hd_code_802FC280, D_hd_code_802FC300, 0x0D },
  { D_hd_code_802FC300, D_hd_code_802FC320, 0x04 },
  { D_hd_code_802FC320, D_hd_code_802FC360, 0x07 }
};
// </data>

// Is (arg0, arg1, arg2) inside one of this level's no-track zones (y range +
// point-in-triangle tests)?
// Proposed name: IsInNoTrackZone
s32 func_hd_code_8027BCF0(s16 arg0, s16 arg1, s16 arg2) {
  s32 index = 0;
  u8 found = 0;

  while(index <= 10 && !found) {
    if (D_hd_code_802FC360[index].unk8 == levelno) {
      found = 1;
    } else {
      index++;
    }
  }

  if (!found) {
    return 0;
  } else {
    struct S_802FC368_sub *current = D_hd_code_802FC360[index].unk0;
    struct S_802FC368_sub *last = D_hd_code_802FC360[index].unk4;

    while (current != last) {
      if (arg1 >= current->unkC &&
          arg1 <= current->unkE &&
          func_hd_code_802AC4C4(arg0, arg2, current->unk0, current->unk2, current->unk4, current->unk6, current->unk8, current->unkA)) {
        return 1;
      }
      current++;
    }
  }
  return 0;
}

// Reset the tire track ring at level init
// Proposed name: ResetTireTracks
void func_hd_code_8027BE4C(void) {
  s32 pad;

  D_hd_code_8036DC90 = 0;
  D_hd_code_8036DC91 = 0;
  D_hd_code_8036DC92 = 0;
  D_hd_code_8036DC94 = -1;
}

// Record one tire track segment: arg0 = strip length limit, arg1 = ground y,
// (arg2, arg3)/(arg4, arg5) = left/right wheel offsets from the vehicle at
// (arg6, arg7), arg8 = heading (0..4095), arg9 = track half width,
// arg10/arg11 = the two edge alphas, arg12 = single-track flag. Rotates the
// wheel offsets by the heading, computes the 4 edge points, starts a new
// strip after a frame gap and splits strips at the length limit. Skipped
// inside no-track zones.
// Proposed name: AddTireTrackSegment
void func_hd_code_8027BE7C(u8 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s32 arg6, s32 arg7, s16 arg8, u8 arg9, u8 arg10, u8 arg11, u8 arg12) {
    f32 sp50[4][4];
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    s16 sp32;
    s16 sp30;
    s16 sp2E;
    s16 sp2C;

    if (func_hd_code_8027BCF0(arg6 >> 5, arg1 >> 5, arg7 >> 5) == 0) {
        guAlignF(sp50, ((f32) arg8 / 4095.0) * 360.0, 0.0f, 1.0f, 0.0f);
        guMtxXFMF(sp50, arg2, 0.0f, arg3, &sp4C, &sp3C, &sp48);
        guMtxXFMF(sp50, arg4, 0.0f, arg5, &sp44, &sp3C, &sp40);

        sp32 = (s32) (sp4C + arg6) >> 5;
        sp30 = (s32) (sp48 + arg7) >> 5;
        sp2E = (s32) (sp44 + arg6) >> 5;
        sp2C = (s32) (sp40 + arg7) >> 5;
        arg1 >>= 5;

        guMtxXFMF(sp50, arg9, 0.0f, 0.0f, &sp38, &sp3C, &sp34);
        if (((D_hd_code_8036DC94 + 1) != D_hd_code_80358060) || (D_hd_code_8036DC94 == -1U)) {
            D_hd_code_8036D3D0[D_hd_code_8036DC91].unk1A = 1;

            D_hd_code_8036DC91++;
            if (D_hd_code_8036DC91 == 0x50) {
                D_hd_code_8036DC91 = 0;
            }
            if (D_hd_code_8036DC91 == D_hd_code_8036DC90) {
                D_hd_code_8036DC90++;
                if (D_hd_code_8036DC90 == 0x50) {
                    D_hd_code_8036DC90 = 0;
                }
            }
        }

        D_hd_code_8036D3D0[D_hd_code_8036DC91].unk1B = arg12;

        D_hd_code_8036D3D0[D_hd_code_8036DC91].unk0 = sp32 + (s16)sp38;
        D_hd_code_8036D3D0[D_hd_code_8036DC91].unk2 = arg1;
        D_hd_code_8036D3D0[D_hd_code_8036DC91].unk4 = sp30 + (s16)sp34;
        D_hd_code_8036D3D0[D_hd_code_8036DC91].unk6 = sp32 - (s16)sp38;
        D_hd_code_8036D3D0[D_hd_code_8036DC91].unk8 = arg1;
        D_hd_code_8036D3D0[D_hd_code_8036DC91].unkA = sp30 - (s16)sp34;
        D_hd_code_8036D3D0[D_hd_code_8036DC91].unkC = sp2E + (s16)sp38;
        D_hd_code_8036D3D0[D_hd_code_8036DC91].unkE = arg1;
        D_hd_code_8036D3D0[D_hd_code_8036DC91].unk10 = sp2C + (s16)sp34;
        D_hd_code_8036D3D0[D_hd_code_8036DC91].unk12 = sp2E - (s16)sp38;
        D_hd_code_8036D3D0[D_hd_code_8036DC91].unk14 = arg1;
        D_hd_code_8036D3D0[D_hd_code_8036DC91].unk16 = sp2C - (s16)sp34;
        D_hd_code_8036D3D0[D_hd_code_8036DC91].unk18 = arg10;
        D_hd_code_8036D3D0[D_hd_code_8036DC91].unk19 = arg11;

        D_hd_code_8036DC92++;
        if (D_hd_code_8036DC92 >= arg0) {
            D_hd_code_8036DC92 = 0;
            D_hd_code_8036D3D0[D_hd_code_8036DC91].unk1A = 0;
            D_hd_code_8036DC91++;
            if (D_hd_code_8036DC91 == 0x50) {
                D_hd_code_8036DC91 = 0;
            }
            if (D_hd_code_8036DC91 == D_hd_code_8036DC90) {
                D_hd_code_8036DC90++;
                if (D_hd_code_8036DC90 == 0x50) {
                    D_hd_code_8036DC90 = 0;
                }
            }
        }
        D_hd_code_8036DC94 = D_hd_code_80358060;
    }
}

// Draw all tire tracks: fade the oldest segments, then walk the ring strip
// by strip building vertex runs (left track edges, then the right track
// appended unless single-track), black prim color modulated by the
// per-vertex shade alpha. Strips with enough vertices get an 8-corner
// bounding box and gSPCullDisplayList so off-screen tracks are skipped. The
// strip geometry goes into a sub-display list buffer called from the main
// list.
// Proposed name: DrawTireTracks
void func_hd_code_8027C4C8(Gfx** gfx, struct Model1* arg1) {
    Gfx* entry;
    u8 sp9B;
    u8 sp9A;
    u8 sp99;
    u8 sp98;
    u8 sp97;
    Gfx* sp90;
    s32 sp8C;
    s32 sp88;
    s32 sp84;
    s16 sp82;
    s16 sp80;
    s16 sp7E;
    s16 sp7C;
    s16 sp7A;
    s16 sp78;
    u8 sp77;
    u8 sp76;
    s32 sp70;
    s32 sp6C;
    u8 sp6B;


    entry = *gfx;
    sp97 = 0;
    sp9B = D_hd_code_8036DC90;
    sp90 = arg1->unk3C30;
    sp8C = 0;
    sp88 = 0;

    func_hd_code_8027D5AC();
    gDPPipeSync(entry++);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    gDPSetRenderMode(entry++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
    gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
    gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_OFF);
    gDPSetCombineLERP(entry++, 0, 0, 0, PRIMITIVE, 0, 0, 0, SHADE, 0, 0, 0, PRIMITIVE, 0, 0, 0, SHADE);
    gDPSetPrimColor(entry++, 0, 0, 0x00, 0x00, 0x00, 0x00);

    while (sp97 == 0) {
        sp9A = sp9B;
        sp6B = D_hd_code_8036D3D0[sp9B].unk1B;
        if ((sp9B != D_hd_code_8036DC91) && (D_hd_code_8036D3D0[sp9B].unk1A == 0)) {
loop_3:
            sp9B++;
            if (sp9B == 0x50) {
                sp9B = 0;
            }
            if ((sp9B != D_hd_code_8036DC91) && D_hd_code_8036D3D0[sp9B].unk1A == 0) {
                goto loop_3;
            }
        }
        sp99 = sp9B;
        if (sp9B == D_hd_code_8036DC91) {
            sp97 = 1;
        }
        if (sp9A != sp99) {
            gSPDisplayList(entry++, &D_2000000.unk3C30[sp8C]);

            sp82 = 0x7FFF,
            sp80 = 0x7FFF,
            sp7E = 0x7FFF;
            sp7C = -0x8000,
            sp7A = -0x8000,
            sp78 = -0x8000;

            sp84 = sp88;
            sp98 = sp9A;
            if (sp9A != sp99) {
                do {
                    arg1->unk2000[sp84].n.ob[0] = (s16) D_hd_code_8036D3D0[sp98].unk0;
                    arg1->unk2000[sp84].n.ob[1] = (s16) D_hd_code_8036D3D0[sp98].unk2;
                    arg1->unk2000[sp84].n.ob[2] = (s16) D_hd_code_8036D3D0[sp98].unk4;
                    arg1->unk2000[sp84].n.a = (u8) D_hd_code_8036D3D0[sp98].unk18;
                    sp84++;

                    arg1->unk2000[sp84].n.ob[0] = (s16) D_hd_code_8036D3D0[sp98].unk6;
                    arg1->unk2000[sp84].n.ob[1] = (s16) D_hd_code_8036D3D0[sp98].unk8;
                    arg1->unk2000[sp84].n.ob[2] = (s16) D_hd_code_8036D3D0[sp98].unkA;
                    arg1->unk2000[sp84].n.a = (u8) D_hd_code_8036D3D0[sp98].unk18;
                    sp84++;

                    if (D_hd_code_8036D3D0[sp98].unk0 < sp82) {
                        sp82 = D_hd_code_8036D3D0[sp98].unk0;
                    }

                    if (D_hd_code_8036D3D0[sp98].unk2 < sp80) {
                        sp80 = D_hd_code_8036D3D0[sp98].unk2;
                    }

                    if (D_hd_code_8036D3D0[sp98].unk4 < sp7E) {
                        sp7E = D_hd_code_8036D3D0[sp98].unk4;
                    }

                    if (D_hd_code_8036D3D0[sp98].unk0 > sp7C) {
                        sp7C = D_hd_code_8036D3D0[sp98].unk0;
                    }

                    if (D_hd_code_8036D3D0[sp98].unk2 > sp7A) {
                        sp7A = D_hd_code_8036D3D0[sp98].unk2;
                    }

                    if (D_hd_code_8036D3D0[sp98].unk4 > sp78) {
                        sp78 = D_hd_code_8036D3D0[sp98].unk4;
                    }

                    if (D_hd_code_8036D3D0[sp98].unk6 < sp82) {
                        sp82 = D_hd_code_8036D3D0[sp98].unk6;
                    }

                    if (D_hd_code_8036D3D0[sp98].unk8 < sp80) {
                        sp80 = D_hd_code_8036D3D0[sp98].unk8;
                    }

                    if (D_hd_code_8036D3D0[sp98].unkA < sp7E) {
                        sp7E = D_hd_code_8036D3D0[sp98].unkA;
                    }

                    if (D_hd_code_8036D3D0[sp98].unk6 > sp7C) {
                        sp7C = D_hd_code_8036D3D0[sp98].unk6;
                    }

                    if (D_hd_code_8036D3D0[sp98].unk8 > sp7A) {
                        sp7A = D_hd_code_8036D3D0[sp98].unk8;
                    }

                    if (D_hd_code_8036D3D0[sp98].unkA > sp78) {
                        sp78 = D_hd_code_8036D3D0[sp98].unkA;
                    }

                    sp98++;
                    if (sp98 == 0x50) {
                        sp98 = 0;
                    }
                } while (sp98 != sp99);
            }
            if (sp6B == 0) {
                sp98 = sp9A;
                if (sp9A != sp99) {
                    do {
                        arg1->unk2000[sp84].n.ob[0] = (s16) D_hd_code_8036D3D0[sp98].unkC;
                        arg1->unk2000[sp84].n.ob[1] = (s16) D_hd_code_8036D3D0[sp98].unkE;
                        arg1->unk2000[sp84].n.ob[2] = (s16) D_hd_code_8036D3D0[sp98].unk10;
                        arg1->unk2000[sp84].n.a = (u8) D_hd_code_8036D3D0[sp98].unk19;
                        sp84++;

                        arg1->unk2000[sp84].n.ob[0] = (s16) D_hd_code_8036D3D0[sp98].unk12;
                        arg1->unk2000[sp84].n.ob[1] = (s16) D_hd_code_8036D3D0[sp98].unk14;
                        arg1->unk2000[sp84].n.ob[2] = (s16) D_hd_code_8036D3D0[sp98].unk16;
                        arg1->unk2000[sp84].n.a = (u8) D_hd_code_8036D3D0[sp98].unk19;
                        sp84++;
                        if (D_hd_code_8036D3D0[sp98].unkC < sp82) {
                            sp82 = D_hd_code_8036D3D0[sp98].unkC;
                        }

                        if (D_hd_code_8036D3D0[sp98].unkE < sp80) {
                            sp80 = D_hd_code_8036D3D0[sp98].unkE;
                        }

                        if (D_hd_code_8036D3D0[sp98].unk10 < sp7E) {
                            sp7E = D_hd_code_8036D3D0[sp98].unk10;
                        }

                        if (D_hd_code_8036D3D0[sp98].unk12 > sp7C) {
                            sp7C = D_hd_code_8036D3D0[sp98].unk12;
                        }

                        if (D_hd_code_8036D3D0[sp98].unk14 > sp7A) {
                            sp7A = D_hd_code_8036D3D0[sp98].unk14;
                        }

                        if (D_hd_code_8036D3D0[sp98].unk16 > sp78) {
                            sp78 = D_hd_code_8036D3D0[sp98].unk16;
                        }

                        if (D_hd_code_8036D3D0[sp98].unkC < sp82) {
                            sp82 = D_hd_code_8036D3D0[sp98].unkC;
                        }

                        if (D_hd_code_8036D3D0[sp98].unkE < sp80) {
                            sp80 = D_hd_code_8036D3D0[sp98].unkE;
                        }

                        if (D_hd_code_8036D3D0[sp98].unk10 < sp7E) {
                            sp7E = D_hd_code_8036D3D0[sp98].unk10;
                        }

                        if (D_hd_code_8036D3D0[sp98].unk12 > sp7C) {
                            sp7C = D_hd_code_8036D3D0[sp98].unk12;
                        }

                        if (D_hd_code_8036D3D0[sp98].unk14 > sp7A) {
                            sp7A = D_hd_code_8036D3D0[sp98].unk14;
                        }

                        if (D_hd_code_8036D3D0[sp98].unk16 > sp78) {
                            sp78 = D_hd_code_8036D3D0[sp98].unk16;
                        }
                        sp98++;
                        if (sp98 == 0x50) {
                            sp98 = 0;
                        }
                    } while (sp98 != sp99);
                }
            }
            sp70 = sp84 - sp88;
            if (sp6B != 0) {
                sp6C = 0;
            } else {
                sp6C = sp70 >> 1;
            }
            if (sp70 >= 0x29) {
                func_hd_code_8027D350(sp82, sp80, sp7E, sp7C, sp7A, sp78, arg1->unk2000, sp84);

                gSPVertex(sp90++,&D_2000000.unk2000[sp84], 8, 0);
                gSPCullDisplayList(sp90++, 0, 7);

                sp8C += 2;
                sp84 += 8;
            }
            while (sp70 >= 3) {
                if (sp70 > 16) {
                    sp76 = 16;
                } else {
                    sp76 = (u8) sp70;
                }

                gSPVertex(sp90++, &D_2000000.unk2000[sp88], sp76, 0);
//                sp38->unk0 = (s32) (((((sp76 - 1) * 0x10) & 0xFF) << 0x10) | 0x04000000 | ((sp76 * 0x10) & 0xFFFF));
                //sp38->unk4 = (void* ) ((sp88 * 0x10) + 0x2000 + &D_2000000);

                sp77 = 0;
                sp88 = sp88 - 2 + sp76;
                sp8C++;
                while ((sp76 - 2) > sp77) {
                    if (sp6C != 2) {
                        gSP1Triangle(sp90++, sp77, sp77 + 1, sp77 + 2, 0);
                        gSP1Triangle(sp90++, sp77 + 1, sp77 + 2, sp77 + 3, 0);

                        sp8C += 2;
                        sp6C -= 2;
                        sp77 += 2;
                    } else {
                        sp6C = 0;
                        sp77 += 4;
                    }
                }
                sp70 = (sp70 - sp76) + 2;
            }
            sp88 = sp84;
            gSPEndDisplayList(sp90++);
            sp8C += 1;
        }
        sp9B++;
        if (sp9B == 0x50) {
            sp9B = 0;
        }
    }
    gDPPipeSync(entry++);

    *gfx = entry;
}

// Write the 8 corner vertices of the bounding box (x1..z2) into the vertex
// array at arg7, for gSPCullDisplayList
// Proposed name: WriteCullBox
void func_hd_code_8027D350(s16 x1, s16 y1, s16 z1, s16 x2, s16 y2, s16 z2, Vtx* arg6, s32 arg7) {
  arg6[arg7].v.ob[0] = x1;
  arg6[arg7].v.ob[1] = y1;
  arg6[arg7].v.ob[2] = z1;
  arg7++;

  arg6[arg7].v.ob[0] = x1;
  arg6[arg7].v.ob[1] = y2;
  arg6[arg7].v.ob[2] = z1;
  arg7++;

  arg6[arg7].v.ob[0] = x2;
  arg6[arg7].v.ob[1] = y1;
  arg6[arg7].v.ob[2] = z1;
  arg7++;

  arg6[arg7].v.ob[0] = x2;
  arg6[arg7].v.ob[1] = y2;
  arg6[arg7].v.ob[2] = z1;
  arg7++;

  arg6[arg7].v.ob[0] = x1;
  arg6[arg7].v.ob[1] = y1;
  arg6[arg7].v.ob[2] = z2;
  arg7++;

  arg6[arg7].v.ob[0] = x1;
  arg6[arg7].v.ob[1] = y2;
  arg6[arg7].v.ob[2] = z2;
  arg7++;

  arg6[arg7].v.ob[0] = x2;
  arg6[arg7].v.ob[1] = y1;
  arg6[arg7].v.ob[2] = z2;
  arg7++;

  arg6[arg7].v.ob[0] = x2;
  arg6[arg7].v.ob[1] = y2;
  arg6[arg7].v.ob[2] = z2;
}

// When the ring is nearly full (71+ segments), fade the oldest segment's
// alphas toward zero and advance the tail once both reach 0 (checking the
// next entry too so retirement keeps pace)
// Proposed name: FadeOldTireTracks
void func_hd_code_8027D5AC(void) {
  s32 sp4;
  u8 sp3;

  if (D_hd_code_8036DC91 >= D_hd_code_8036DC90) {
    sp4 = D_hd_code_8036DC91 - D_hd_code_8036DC90;
  } else {
    sp4 = (D_hd_code_8036DC91 - D_hd_code_8036DC90) + 0x50;
  }
  if (sp4 >= 0x47) {
    if (D_hd_code_8036D3D0[D_hd_code_8036DC90].unk18 <= 0) {
      D_hd_code_8036D3D0[D_hd_code_8036DC90].unk18 = 0;
    } else {
      D_hd_code_8036D3D0[D_hd_code_8036DC90].unk18 -= 1;
    }

    if (D_hd_code_8036D3D0[D_hd_code_8036DC90].unk19 <= 0) {
      D_hd_code_8036D3D0[D_hd_code_8036DC90].unk19 = 0;
    } else {
      D_hd_code_8036D3D0[D_hd_code_8036DC90].unk19 -= 1;
    }

    if ((D_hd_code_8036D3D0[D_hd_code_8036DC90].unk18 == 0) && (D_hd_code_8036D3D0[D_hd_code_8036DC90].unk19 == 0)) {
      sp3 = D_hd_code_8036DC90 + 1;
      if (sp3 == 0x50) {
        sp3 = 0;
      }

      if (D_hd_code_8036D3D0[sp3].unk18 <= 0) {
        D_hd_code_8036D3D0[sp3].unk18 = 0;
      } else {
        D_hd_code_8036D3D0[sp3].unk18 -= 1;
      }

      if (D_hd_code_8036D3D0[sp3].unk19 <= 0) {
        D_hd_code_8036D3D0[sp3].unk19 = 0;
      } else {
        D_hd_code_8036D3D0[sp3].unk19 -= 1;
      }

      if ((D_hd_code_8036D3D0[sp3].unk18 == 0) && (D_hd_code_8036D3D0[sp3].unk19 == 0)) {
        D_hd_code_8036DC90 = sp3;
      }
    }
  }
}
