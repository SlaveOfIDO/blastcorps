#include "common.h"
#include "functions.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"

struct S_8039C718 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 unk10;
    u8 unk11;
    s32 unk14;
    s32 unk18;
};

struct S_8039C800 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 pad24;
    u8 unk26;
    u8 unk27;
}; // Size: 0x28

struct S_802FDC08
{
  /* 0x000 */ Gfx unk0[40];
  /* 0x140 */ Vtx unk140[20];
  /* 0x280 */ s16 unk280;
  /* 0x282 */ u8 unk282;
  /* 0x283 */ u8 unk283;
  /* 0x284 */ s16 unk284;
  /* 0x286 */ s16 unk286;
  /* 0x288 */ s32 unk288;
  /* 0x28C */ u32 pad28C;
}; // Size: 0x290


struct S_8039C720 {
  s16 unk0;
  s16 unk2;
  s32 unk4;
  u8 pad8;
  u8 unk9;
  u8 padA;
  u8 padB;
  u8 padC[0x1C - 0xC];
}; // Size: 0x1C

struct S_8039C724 {
  s32 unk0;
  u8 pad4[0x18];
};

struct S_SquareBlockData1 {
  s16 unk0;
  s16 unk2;
  s16 unk4;
  s16 unk6;
}; // Size: 0x8

struct S_SquareBlockData2 {
  s16 unk0;
  s16 unk2;
  s16 unk4;
  u8 unk6;
  u8 unk7;
  s16 unk8;
}; // Size: 0xA


// Proposed file name: blocks.c
//
// This file is the pushable-block puzzle system: square blocks the player
// shoves around the level (D_hd_code_8039C550, loaded from the level) that home in on
// and drop into matching sockets/holes (D_hd_code_8039C718), bouncing to a rest and
// then triggering the socket's effect (e.g. raising a platform via
// func_hd_code_802CEA68 / func_hd_code_80291724). Block templates come from
// D_hd_code_802FDC08, sockets can also spawn a trigger marker
// (D_hd_code_8039C800). Blocks can also ride moveable platforms.

void func_hd_code_80291724(s32);                        /* extern */
void func_hd_code_802CEA68(s32, s32);                  /* extern */
void func_hd_code_802CE9A4();                          /* extern */
void func_hd_code_802CE9C8(void*, u8, u8);             /* extern */

extern struct S_8039C720 D_hd_code_8039C720[];
extern s32 D_hd_code_8039C710;
extern struct S_8039C718 D_hd_code_8039C718[];
extern s32 D_hd_code_8039C7F8;
extern struct S_8039C800 D_hd_code_8039C800[];
extern u8 D_hd_code_8039C940;
extern s32 D_hd_code_8039C944;
extern s32 D_hd_code_8039C948;
extern s32 D_hd_code_8039C94C;
extern s8 D_hd_code_8039C950;
extern s32 D_hd_code_8039C954;
extern s32 D_hd_code_8039C958;
extern s32 D_hd_code_8039C95C;
extern s32 D_hd_code_803FB8B0;

// <data>
s16 D_hd_code_802FDBE0[20] = {
  0x0000, 0x0087, 0x0069, 0x0096,
  0x0096, 0x0087, 0x0000, 0x0096,
  0x00C8, 0x07D0, 0x00AF, 0x0000,
  0x0000, 0x00C3, 0x00BE, 0x00B9,
  0x0069, 0x0000, 0x0000, 0x0000
};

struct S_802FDC08 D_hd_code_802FDC08[3] = {
  {
    {
      gsSPVertex(0x002FDD48, 8, 0),
      gsSP1Triangle(0, 1, 2, 0),
      gsSP1Triangle(0, 2, 3, 0),
      gsSP1Triangle(4, 1, 0, 0),
      gsSP1Triangle(1, 4, 5, 0),
      gsSP1Triangle(7, 5, 4, 0),
      gsSP1Triangle(5, 7, 6, 0),
      gsSP1Triangle(7, 3, 2, 0),
      gsSP1Triangle(6, 7, 2, 0),
      gsSPModifyVertex(5, G_MWO_POINT_ST, 0x00000000),
      gsSPModifyVertex(6, G_MWO_POINT_ST, 0x07E00000),
      gsSP1Triangle(5, 2, 1, 0),
      gsSP1Triangle(2, 5, 6, 0),
      gsSPEndDisplayList(),
  },
{
    { { { 0x001E, 0x0000, 0xFFE2 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } },
    { { { 0x001E, 0x001E, 0xFFE2 }, 0x0000, { 0x0000, 0x03E0 }, { 0x00, 0x00, 0x00, 0x00 } } },
    { { { 0x001E, 0x001E, 0x001E }, 0x0000, { 0x07E0, 0x03E0 }, { 0x00, 0x00, 0x00, 0x00 } } },
    { { { 0x001E, 0x0000, 0x001E }, 0x0000, { 0x07E0, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } },
    { { { 0xFFE2, 0x0000, 0xFFE2 }, 0x0000, { 0x07E0, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } },
    { { { 0xFFE2, 0x001E, 0xFFE2 }, 0x0000, { 0x07E0, 0x03E0 }, { 0x00, 0x00, 0x00, 0x00 } } },
    { { { 0xFFE2, 0x001E, 0x001E }, 0x0000, { 0x0000, 0x03E0 }, { 0x00, 0x00, 0x00, 0x00 } } },
    { { { 0xFFE2, 0x0000, 0x001E }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } }
},
    0x048C, 0x40, 0x20,
    0x0640, 0x001E,
    0x000003C0,
    0x00000000
  },
  {
      {
        gsSPVertex(0x002FDFD8, 8, 0),
        gsSP1Triangle(2, 1, 0, 0),
        gsSP1Triangle(3, 2, 0, 0),
        gsSP1Triangle(0, 1, 4, 0),
        gsSP1Triangle(5, 4, 1, 0),
        gsSP1Triangle(4, 5, 7, 0),
        gsSP1Triangle(6, 7, 5, 0),
        gsSP1Triangle(2, 3, 7, 0),
        gsSP1Triangle(2, 7, 6, 0),
        gsSPModifyVertex(5, G_MWO_POINT_ST, 0x00000000),
        gsSPModifyVertex(6, G_MWO_POINT_ST, 0x07E00000),
        gsSP1Triangle(1, 2, 5, 0),
        gsSP1Triangle(6, 5, 2, 0),
        gsSPEndDisplayList(),
    },
    {
        { { { 0x002A, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } },
        { { { 0x002A, 0x001E, 0x0000 }, 0x0000, { 0x0000, 0x03E0 }, { 0x00, 0x00, 0x00, 0x00 } } },
        { { { 0x0000, 0x001E, 0xFFD6 }, 0x0000, { 0x07E0, 0x03E0 }, { 0x00, 0x00, 0x00, 0x00 } } },
        { { { 0x0000, 0x0000, 0xFFD6 }, 0x0000, { 0x07E0, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } },
        { { { 0x0000, 0x0000, 0x002A }, 0x0000, { 0x07E0, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } },
        { { { 0x0000, 0x001E, 0x002A }, 0x0000, { 0x07E0, 0x03E0 }, { 0x00, 0x00, 0x00, 0x00 } } },
        { { { 0xFFD6, 0x001E, 0x0000 }, 0x0000, { 0x0000, 0x03E0 }, { 0x00, 0x00, 0x00, 0x00 } } },
        { { { 0xFFD6, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } }
    },
    0x048C, 0x40, 0x20,
0x0640, 0x001E,
0x000003C0,
0x00000000
  },
  {
      {
        gsSPVertex(0x002FDFD8, 8, 0),
        gsSP1Triangle(2, 1, 0, 0),
        gsSP1Triangle(3, 2, 0, 0),
        gsSP1Triangle(0, 1, 4, 0),
        gsSP1Triangle(5, 4, 1, 0),
        gsSP1Triangle(4, 5, 7, 0),
        gsSP1Triangle(6, 7, 5, 0),
        gsSP1Triangle(2, 3, 7, 0),
        gsSP1Triangle(2, 7, 6, 0),
        gsSPModifyVertex(5, G_MWO_POINT_ST, 0x00000000),
        gsSPModifyVertex(6, G_MWO_POINT_ST, 0x07E00000),
        gsSP1Triangle(1, 2, 5, 0),
        gsSP1Triangle(6, 5, 2, 0),
        gsSPEndDisplayList(),
    },
    {
        { { { 0x002A, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } },
        { { { 0x002A, 0x001E, 0x0000 }, 0x0000, { 0x0000, 0x03E0 }, { 0x00, 0x00, 0x00, 0x00 } } },
        { { { 0x0000, 0x001E, 0xFFD6 }, 0x0000, { 0x07E0, 0x03E0 }, { 0x00, 0x00, 0x00, 0x00 } } },
        { { { 0x0000, 0x0000, 0xFFD6 }, 0x0000, { 0x07E0, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } },
        { { { 0x0000, 0x0000, 0x002A }, 0x0000, { 0x07E0, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } },
        { { { 0x0000, 0x001E, 0x002A }, 0x0000, { 0x07E0, 0x03E0 }, { 0x00, 0x00, 0x00, 0x00 } } },
        { { { 0xFFD6, 0x001E, 0x0000 }, 0x0000, { 0x0000, 0x03E0 }, { 0x00, 0x00, 0x00, 0x00 } } },
        { { { 0xFFD6, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } },
    },
    0x048C, 0x40, 0x20,
    0x0500, 0x0028,
    0x000003C0,
    0x00000000
  }
};
// </data>

// Build the level's blocks and sockets from the placement blob [arg0, arg1):
// a count-prefixed array of blocks (position, type, snapped ground height,
// loaded texture) followed by a count-prefixed array of sockets (position,
// type, attached collision data); sockets that drive a trigger also get a
// marker entry in D_hd_code_8039C800
// (already named: LoadLevelSquareBlocks)
void LoadLevelSquareBlocks(u8* arg0, s32 arg1) {
    s32 sp1C;

    D_hd_code_8039C710 = 0;
    D_hd_code_8039C7F8 = 0;
    D_hd_code_8039C940 = 0;
    D_hd_code_8039C944 = 0;
    D_hd_code_8039C948 = 0;
    D_hd_code_8039C94C = 0;
    D_hd_code_8039C954 = 0;
    D_hd_code_8039C958 = 0;
    D_hd_code_8039C95C = 0;
    D_hd_code_8039C950 = 0;
    D_hd_code_803ED40C = 0;
    func_hd_code_802CE9A4();
    if ((s32)arg0 != arg1) {
        D_hd_code_8039C710 = *(s16*)arg0;
        arg0 += 2;
        for(sp1C = 0; sp1C < D_hd_code_8039C710; sp1C++) {
            D_hd_code_8039C550[sp1C].unk0 = ((struct S_SquareBlockData1*)arg0)->unk0 << 5;
            D_hd_code_8039C550[sp1C].unk4 = ((struct S_SquareBlockData1*)arg0)->unk2 << 5;
            D_hd_code_8039C550[sp1C].unk8 = ((struct S_SquareBlockData1*)arg0)->unk4 << 5;
            D_hd_code_8039C550[sp1C].unk10 = ((struct S_SquareBlockData1*)arg0)->unk6;
            arg0 += sizeof(struct S_SquareBlockData1);
            D_hd_code_8039C550[sp1C].unk4 = func_hd_code_802CE6F8(D_hd_code_8039C550[sp1C].unk0, D_hd_code_8039C550[sp1C].unk8, D_hd_code_8039C550[sp1C].unk4);
            D_hd_code_8039C550[sp1C].unkE = 0;
            D_hd_code_8039C550[sp1C].unkC = 0;
            D_hd_code_8039C550[sp1C].unk11 = 0;
            D_hd_code_8039C550[sp1C].unk12 = 0;
            D_hd_code_8039C550[sp1C].unk20 = 0;
            D_hd_code_8039C550[sp1C].unk14 = 0;
            D_hd_code_8039C550[sp1C].unk18 = 0;
            D_hd_code_8039C550[sp1C].unk29 = 0;
            D_hd_code_8039C550[sp1C].unk30 = func_hd_code_802A0CC8(D_hd_code_802FDC08[D_hd_code_8039C550[sp1C].unk10].unk280, 0);
        }

        D_hd_code_8039C7F8 = *(s16*)arg0;
        arg0 += 2;

        for(sp1C = 0; sp1C < D_hd_code_8039C7F8; sp1C++) {
            D_hd_code_8039C718[sp1C].unk0 = ((struct S_SquareBlockData2*)arg0)->unk0 << 5;
            D_hd_code_8039C718[sp1C].unk4 = ((struct S_SquareBlockData2*)arg0)->unk2 << 5;
            D_hd_code_8039C718[sp1C].unk8 = ((struct S_SquareBlockData2*)arg0)->unk4 << 5;
            D_hd_code_8039C718[sp1C].unk10 = ((struct S_SquareBlockData2*)arg0)->unk6;
            D_hd_code_8039C718[sp1C].unkC = (s32) (D_hd_code_8039C718[sp1C].unk4 - D_hd_code_802FDC08[D_hd_code_8039C718[sp1C].unk10].unk288);
            D_hd_code_8039C718[sp1C].unk11 = 0;
            D_hd_code_8039C718[sp1C].unk14 = D_hd_code_803FB8B0;
            func_hd_code_802CE9C8(arg0 + 10, ((struct S_SquareBlockData2*)arg0)->unk7, D_hd_code_8039C718[sp1C].unk10);
            D_hd_code_8039C718[sp1C].unk18 = D_hd_code_803FB8B0;
            if (((struct S_SquareBlockData2*)arg0)->unk8 != 0) {
                D_hd_code_8039C800[D_hd_code_8039C940].unk0 = D_hd_code_8039C718[sp1C].unk0;
                D_hd_code_8039C800[D_hd_code_8039C940].unk4 = D_hd_code_8039C718[sp1C].unk4;
                D_hd_code_8039C800[D_hd_code_8039C940].unk8 = D_hd_code_8039C718[sp1C].unk8;
                D_hd_code_8039C800[D_hd_code_8039C940].unkE = (s16) ((s32) D_hd_code_8039C718[sp1C].unk4 >> 5);
                D_hd_code_8039C800[D_hd_code_8039C940].unk14 = (s16) ((s32) D_hd_code_8039C718[sp1C].unk4 >> 5);
                D_hd_code_8039C800[D_hd_code_8039C940].unk1A = (s16) ((s32) D_hd_code_8039C718[sp1C].unk4 >> 5);
                D_hd_code_8039C800[D_hd_code_8039C940].unk20 = (s16) ((s32) D_hd_code_8039C718[sp1C].unk4 >> 5);
                D_hd_code_8039C800[D_hd_code_8039C940].unkC = ((s32) D_hd_code_8039C718[sp1C].unk0 >> 5) - 0x28;
                D_hd_code_8039C800[D_hd_code_8039C940].unk10 = ((s32) D_hd_code_8039C718[sp1C].unk8 >> 5) - 0x28;
                D_hd_code_8039C800[D_hd_code_8039C940].unk12 = ((s32) D_hd_code_8039C718[sp1C].unk0 >> 5) + 0x28;
                D_hd_code_8039C800[D_hd_code_8039C940].unk16 = ((s32) D_hd_code_8039C718[sp1C].unk8 >> 5) - 0x28;
                D_hd_code_8039C800[D_hd_code_8039C940].unk18 = ((s32) D_hd_code_8039C718[sp1C].unk0 >> 5) - 0x28;
                D_hd_code_8039C800[D_hd_code_8039C940].unk1C = ((s32) D_hd_code_8039C718[sp1C].unk8 >> 5) + 0x28;
                D_hd_code_8039C800[D_hd_code_8039C940].unk1E = ((s32) D_hd_code_8039C718[sp1C].unk0 >> 5) + 0x28;
                D_hd_code_8039C800[D_hd_code_8039C940].unk22 = ((s32) D_hd_code_8039C718[sp1C].unk8 >> 5) + 0x28;
                D_hd_code_8039C800[D_hd_code_8039C940].unk26 = 0;
                D_hd_code_8039C800[D_hd_code_8039C940].unk27 = sp1C;
                D_hd_code_8039C940 += 1;
            }
            arg0 = 10 + ((struct S_SquareBlockData2*)arg0)->unk7 * 0x16 + arg0;
        }
    }
}

// Per-frame block update (arg0 = current vehicle). For each block not yet
// homing or settled: clear its push velocity, move it by any pending push
// while re-snapping to the ground, check whether the player/missile is close
// enough to shove it (accumulating a push speed capped per vehicle), and -
// when it lines up over a matching-type socket within range - latch onto
// that socket. Homing blocks slide toward the socket center, then drop with a
// damped bounce; on settling they fire the socket's trigger. Also manages the
// rolling/landing sounds.
// Proposed name: UpdateBlocks
void func_hd_code_802906C0(u8 arg0) {
    s32 sp74;
    s32 sp70;
    u8 sp6F;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    s16 sp5E;
    s16 sp5C;
    u8 sp5B;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    u8 sp43;
    u8 sp42;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    u8 sp33;

    for (sp74 = 0; sp74 < D_hd_code_8039C710; sp74++) {
        if ((D_hd_code_8039C550[sp74].unk11 == 0) && (D_hd_code_8039C550[sp74].unk12 == 0)) {
            if (arg0 == 0) {
                D_hd_code_8039C550[sp74].unkC = 0;
            }
            if ((D_hd_code_8039C550[sp74].unkC != 0) && (func_hd_code_802CE958(sp74) == 0)) {
                func_hd_code_802CE65C(D_hd_code_8039C550[sp74].unk0, D_hd_code_8039C550[sp74].unk8, D_hd_code_8039C550[sp74].unkC, D_hd_code_8039C550[sp74].unkE);
                D_hd_code_8039C550[sp74].unk0 = D_hd_code_803F9320;
                D_hd_code_8039C550[sp74].unk8 = D_hd_code_803F9324;
                D_hd_code_8039C550[sp74].unk4 = func_hd_code_802CE6F8(D_hd_code_8039C550[sp74].unk0, D_hd_code_8039C550[sp74].unk8, D_hd_code_8039C550[sp74].unk4);
                D_hd_code_8039C550[sp74].unk28 = D_hd_code_803F932C;

                sp42 = 0;
                sp70 = 0;
                while(sp70 < D_hd_code_8039C7F8 && !sp42) {
                    if ((D_hd_code_8039C550[sp74].unk10 == D_hd_code_8039C718[sp70].unk10) && (D_hd_code_8039C550[sp74].unk28 == 0) && (D_hd_code_8039C718[sp70].unk11 == 0)) {
                        sp68 = (s32) (D_hd_code_8039C550[sp74].unk0 - D_hd_code_8039C718[sp70].unk0) >> 5;
                        sp64 = (s32) (D_hd_code_8039C550[sp74].unk4 - D_hd_code_8039C718[sp70].unk4) >> 5;
                        sp60 = (s32) (D_hd_code_8039C550[sp74].unk8 - D_hd_code_8039C718[sp70].unk8) >> 5;
                        sp54 = (s32) sqrtf((f32) ((sp68 * sp68) + (sp64 * sp64) + (sp60 * sp60)));
                        if (sp54 <= D_hd_code_802FDC08[D_hd_code_8039C550[sp74].unk10].unk286) {
                            D_hd_code_8039C550[sp74].unk24 = func_hd_code_8026A610(D_hd_code_8039C550[sp74].unk0, D_hd_code_8039C550[sp74].unk8, D_hd_code_8039C718[sp70].unk0, D_hd_code_8039C718[sp70].unk8);
                            D_hd_code_8039C550[sp74].unk1C = D_hd_code_8039C550[sp74].unk4;
                            D_hd_code_8039C550[sp74].unk12 = 1;
                            D_hd_code_8039C550[sp74].unk13 = sp70;
                            D_hd_code_8039C718[sp70].unk11 = 1;
                            sp42 = 1;
                        }
                    }
                    sp70++;
                }
            }
            func_hd_code_802CE4F0(D_hd_code_8039C550[sp74].unk0, D_hd_code_8039C550[sp74].unk4, D_hd_code_8039C550[sp74].unk8);
            sp6F = func_hd_code_802CDF94(D_hd_code_802FDC08[D_hd_code_8039C550[sp74].unk10].unk284);
            if (sp6F != 0) {
                if ((D_hd_code_803F932D == 0) && (D_hd_code_803F932E != 0)) {
                    D_hd_code_803ED40C = 1;
                }
                sp33 = D_hd_code_8036443C != 0 || arg0 == 9;
                if ((((u8) D_hd_code_8039C950 == arg0) && (sp33 != 0)) || (D_hd_code_803F932D != 0)) {
                    if (D_hd_code_803F932D == 0) {
                        sp68 = D_hd_code_803643E0 - D_hd_code_8039C944,
                        sp64 = D_hd_code_803643E4 - D_hd_code_8039C948,
                        sp60 = D_hd_code_803643E8 - D_hd_code_8039C94C;
                    } else {
                        sp68 = D_hd_code_803EF6DC - D_hd_code_8039C954,
                        sp64 = D_hd_code_803EF6E0 - D_hd_code_8039C958,
                        sp60 = D_hd_code_803EF6E4 - D_hd_code_8039C95C;
                    }
                    D_hd_code_8039C550[sp74].unkC = (s16) (s32) (sqrtf((f32) ((sp68 * sp68) + (sp64 * sp64) + (sp60 * sp60))) + 10.0f);
                    if (D_hd_code_8039C550[sp74].unkC > D_hd_code_802FDBE0[arg0]) {
                        D_hd_code_8039C550[sp74].unkC = D_hd_code_802FDBE0[arg0];
                    }
                } else {
                    D_hd_code_8039C550[sp74].unkC = 0;
                }
            }

            if (D_hd_code_8039C550[sp74].unkC != 0) {
                sp5B = 0;
                sp5E = D_hd_code_803A7410,
                sp5C = D_hd_code_803A7412;
                func_hd_code_802CE5BC(D_hd_code_8039C550[sp74].unk0, D_hd_code_8039C550[sp74].unk4, D_hd_code_8039C550[sp74].unk8, (s32) D_hd_code_802FDC08[D_hd_code_8039C550[sp74].unk10].unk284, 0xC8, (s32) D_hd_code_8039C550[sp74].unk10);
                func_hd_code_802CDB70(D_hd_code_802FDC08[D_hd_code_8039C550[sp74].unk10].unk284, 0);
                if ((sp5E != D_hd_code_803A7410) || (sp5C != D_hd_code_803A7412)) {
                    sp5B = 1;
                }
            } else {
                sp5B = 0;
            }
            sp43 = 0;
            if ((D_hd_code_803A7410 != 0) || (D_hd_code_803A7412 != 0xFFF)) {
                if (func_hd_code_8029B930() < 0x12C) {
                    sp43 = 1;
                } else {
                    if (sp5B != 0) {
                        D_hd_code_8039C550[sp74].unkE = func_hd_code_802CE3B8(D_hd_code_8039C550[sp74].unkE);
                    } else {
                        D_hd_code_8039C550[sp74].unkE = func_hd_code_802A6F6C();
                    }
                }
            }
            if (((sp43 != 0) || (arg0 == 0)) && ((D_hd_code_8039C550[sp74].unk12 == 0))) {
                func_hd_code_802CE880(sp74, D_hd_code_8039C550[sp74].unk0, D_hd_code_8039C550[sp74].unk4, D_hd_code_8039C550[sp74].unk8, (s32) D_hd_code_802FDC08[D_hd_code_8039C550[sp74].unk10].unk284);
                D_hd_code_8039C550[sp74].unkC = 0;
            } else {
                func_hd_code_802CE90C(sp74);
            }

            if (D_hd_code_8039C550[sp74].unkC > 0) {
                D_hd_code_8039C550[sp74].unkC = D_hd_code_8039C550[sp74].unkC - 8;
            } else {
                D_hd_code_8039C550[sp74].unkC = 0;
            }
        }
        if (D_hd_code_8039C550[sp74].unk12 != 0) {
            sp3C = D_hd_code_8039C718[D_hd_code_8039C550[sp74].unk13].unk0;
            sp38 = D_hd_code_8039C718[D_hd_code_8039C550[sp74].unk13].unk8;

            if ((D_hd_code_8039C550[sp74].unk0 != sp3C) || (D_hd_code_8039C550[sp74].unk8 != sp38)) {
                sp54 = func_hd_code_8026A610(D_hd_code_8039C550[sp74].unk0, D_hd_code_8039C550[sp74].unk8, sp3C, sp38);
                if (sp54 != 0) {
                    sp68 = sp3C - D_hd_code_8039C550[sp74].unk0;
                    if (sp68 > 0) {
                        sp50 = sp68;
                    } else {
                        sp50 = -sp68;
                    }

                    sp50 <<= 10;
                    sp50 /= sp54;
                    sp50 *= D_hd_code_8039C550[sp74].unkC;
                    sp50 >>= 10;

                    if (sp68 < 0) {
                        sp50 = -sp50;
                    }
                    D_hd_code_8039C550[sp74].unk0 += sp50;
                    sp60 = sp38 - D_hd_code_8039C550[sp74].unk8;
                    if (sp60 > 0) {
                        sp50 = sp60;
                    } else {
                        sp50 = -sp60;
                    }

                    sp50 <<= 10;
                    sp50 /= sp54;
                    sp50 *= D_hd_code_8039C550[sp74].unkC;
                    sp50 >>= 10;

                    if (sp60 < 0) {
                        sp50 = -sp50;
                    }
                    D_hd_code_8039C550[sp74].unk8 += sp50;
                    sp54 = func_hd_code_8026A610(D_hd_code_8039C550[sp74].unk0, D_hd_code_8039C550[sp74].unk8, sp3C, sp38);
                    if (sp54 >= D_hd_code_8039C550[sp74].unk24) {
                        D_hd_code_8039C550[sp74].unk0 = sp3C;
                        D_hd_code_8039C550[sp74].unk8 = sp38;
                    } else {
                        D_hd_code_8039C550[sp74].unk24 = sp54;
                    }
                }
            } else {
                if (D_hd_code_8039C550[sp74].unk4 == D_hd_code_8039C550[sp74].unk1C) {
                    sndPlaySfx(D_hd_code_80367738, 0x64, NULL);
                }
                sp34 = D_hd_code_8039C720[D_hd_code_8039C550[sp74].unk13].unk4;
                sp4C = (D_hd_code_8039C550[sp74].unk14 * D_hd_code_8039C550[sp74].unk18) + ((D_hd_code_8039C550[sp74].unk18 * (-4)) * D_hd_code_8039C550[sp74].unk18);
                D_hd_code_8039C550[sp74].unk4 = D_hd_code_8039C550[sp74].unk1C + sp4C;
                if (D_hd_code_8039C550[sp74].unk4 < sp34) {
                    D_hd_code_8039C550[sp74].unk4 = sp34;
                    sp48 = (D_hd_code_8039C550[sp74].unk14 * (D_hd_code_8039C550[sp74].unk18 - 1)) + (((D_hd_code_8039C550[sp74].unk18 * (-4)) + 4) * (D_hd_code_8039C550[sp74].unk18 - 1));
                    sp44 = sp4C - sp48;
                    if (sp44 < 0) {
                        sp44 = -sp44;
                    }
                    if (sp44 < 0x14) {
                        D_hd_code_8039C550[sp74].unk12 = 0;
                        D_hd_code_8039C550[sp74].unk11 = 1;
                        func_hd_code_802CEA68(D_hd_code_8039C718[D_hd_code_8039C550[sp74].unk13].unk14, D_hd_code_8039C718[D_hd_code_8039C550[sp74].unk13].unk18);
                        func_hd_code_80291724(D_hd_code_8039C550[sp74].unk13);
                    } else {
                        D_hd_code_8039C550[sp74].unk14 = sp44 >> 1;
                        D_hd_code_8039C550[sp74].unk18 = 0;
                        D_hd_code_8039C550[sp74].unk1C = sp34;
                        sndPlaySfx(D_hd_code_80367738, 0xC, NULL);
                    }
                } else {
                    D_hd_code_8039C550[sp74].unk18 += 1;
                }
            }
        }
        if ((D_hd_code_8039C550[sp74].unkC != 0) && (D_hd_code_8039C550[sp74].unk12 == 0) && (D_hd_code_8039C550[sp74].unk11 == 0) && (D_hd_code_8039C550[sp74].unk34 == 0)) {
            sndPlaySfx(D_hd_code_80367738, 7, (ALSoundState* ) &D_hd_code_8039C550[sp74].unk34);
        }
        if ((D_hd_code_8039C550[sp74].unk34 != 0) && ((D_hd_code_8039C550[sp74].unkC == 0) || (D_hd_code_8039C550[sp74].unk12 != 0) || (D_hd_code_8039C550[sp74].unk11 != 0))) {
            sndDeactivate(D_hd_code_8039C550[sp74].unk34);
        }
    }
    D_hd_code_8039C944 = D_hd_code_803643E0;
    D_hd_code_8039C948 = D_hd_code_803643E4;
    D_hd_code_8039C94C = D_hd_code_803643E8;
    D_hd_code_8039C950 = (s8) arg0;
    D_hd_code_8039C954 = D_hd_code_803EF6DC;
    D_hd_code_8039C958 = D_hd_code_803EF6E0;
    D_hd_code_8039C95C = D_hd_code_803EF6E4;
}

// Mark the trigger marker belonging to socket arg0 as activated (block
// dropped in)
// Proposed name: ActivateBlockTrigger
void func_hd_code_80291724(s32 arg0) {
  u8 sp7 = 0;
  s32 sp0 = 0;

  while (sp7 == 0 && sp0 < D_hd_code_8039C940) {
    if (D_hd_code_8039C800[sp0].unk27 == arg0) {
      D_hd_code_8039C800[sp0].unk26 = 1;
      sp7 = 1;
    } else {
      sp0 += 1;
    }
  }
}

// Draw the blocks: each block's per-type display list (D_hd_code_802FDC08)
// translated to its position, decal-textured
// Proposed name: DrawBlocks
void func_hd_code_802917B0(Gfx** gfx, struct Model1* arg1) {
  Gfx* entry = *gfx;
  s32 sp80;

  if (D_hd_code_8039C710 > 0) {
    gDPPipeSync(entry++);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    gDPSetRenderMode(entry++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gDPSetCombineMode(entry++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
    gSPSetGeometryMode(entry++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);
  }

  for(sp80 = 0; sp80 < D_hd_code_8039C710; sp80++) {
    guTranslate(&arg1->unkB00[sp80], (f32) D_hd_code_8039C550[sp80].unk0 / 32.0f, (f32) D_hd_code_8039C550[sp80].unk4 / 32.0f, (f32) D_hd_code_8039C550[sp80].unk8 / 32.0f);
    gSPMatrix(entry++, (u32) &D_2000000.unkB00[sp80], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);

    gDPLoadTextureBlock(entry++, OS_PHYSICAL_TO_K0(D_hd_code_8039C550[sp80].unk30), G_IM_FMT_RGBA, G_IM_SIZ_16b, D_hd_code_802FDC08[D_hd_code_8039C550[sp80].unk10].unk282, D_hd_code_802FDC08[D_hd_code_8039C550[sp80].unk10].unk283, /* pal = */0,  G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPDisplayList(entry++, osVirtualToPhysical(D_hd_code_802FDC08[D_hd_code_8039C550[sp80].unk10].unk0));
    gSPPopMatrix(entry++, G_MTX_MODELVIEW);
  }
  gDPPipeSync(entry++);

  *gfx = entry;
}

void func_hd_code_802AACD4(u8, s32, s32, s16*, s16*);

// Begin tracking blocks resting on moveable geometry group arg0 (record
// their offset within the platform so they ride along)
// Proposed name: AttachBlocksToPlatform
void func_hd_code_80291ED8(u8 arg0) {
  s32 i;

  for (i = 0; i < D_hd_code_8039C710; i++) {
    if (D_hd_code_8039C550[i].unk28 == arg0) {
      D_hd_code_8039C550[i].unkC = 0;
      D_hd_code_8039C550[i].unk29 = 1;
      func_hd_code_802AACD4(arg0, D_hd_code_8039C550[i].unk0, D_hd_code_8039C550[i].unk8, &D_hd_code_8039C550[i].unk2A, &D_hd_code_8039C550[i].unk2C);
    }
  }
}

// Move the platform-attached blocks along with moveable geometry group arg0,
// re-snapping their ground height
// Proposed name: MoveBlocksWithPlatform
void func_hd_code_80291FAC(u8 arg0) {
  s32 sp24;

  for(sp24 = 0; sp24 < D_hd_code_8039C710; sp24++) {
    if (D_hd_code_8039C550[sp24].unk29 != 0) {
      func_hd_code_802AAE1C(arg0, D_hd_code_8039C550[sp24].unk2A, D_hd_code_8039C550[sp24].unk2C, &D_hd_code_8039C550[sp24], &D_hd_code_8039C550[sp24].unk8);
      D_hd_code_8039C550[sp24].unk4 = func_hd_code_802CE6F8(D_hd_code_8039C550[sp24].unk0, D_hd_code_8039C550[sp24].unk8, D_hd_code_8039C550[sp24].unk4);
    }
  }
}

// Clear the platform-attached flag on all blocks
// Proposed name: DetachAllBlocks
void func_hd_code_80292084(void) {
  s32 sp4;

  for(sp4 = 0; sp4 < D_hd_code_8039C710; sp4++) {
    D_hd_code_8039C550[sp4].unk29 = 0;
  }
}

// Collision query: set D_hd_code_803A7424 if the sphere at (arg0, arg1, arg2) with
// extra radius arg3 overlaps any non-settled, non-attached block
// Proposed name: TestSphereAgainstBlocks
void func_hd_code_802920DC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
  s32 sp24;
  s32 sp20;

  arg0 = arg0 >> 5,
  arg1 = arg1 >> 5,
  arg2 = arg2 >> 5,
  arg3 = arg3 >> 5;

  for(sp24 = 0; sp24 < D_hd_code_8039C710; sp24++) {
    if ((D_hd_code_8039C550[sp24].unk11 == 0) && (D_hd_code_8039C550[sp24].unk29 == 0)) {
      sp20 = func_hd_code_8026A6F0(arg0, arg1, arg2, D_hd_code_8039C550[sp24].unk0 >> 5, D_hd_code_8039C550[sp24].unk4 >> 5, D_hd_code_8039C550[sp24].unk8 >> 5);
      if (sp20 <= ((D_hd_code_802FDC08[D_hd_code_8039C550[sp24].unk10].unk284 >> 5) + arg3)) {
        D_hd_code_803A7424 = 1;
      }
    }
  }
}

