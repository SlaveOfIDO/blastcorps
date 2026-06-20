#include "common.h"
#include "functions.h"
#include "hd.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"
#include "yoshi.h"

struct S_8039B070 {
  s32 unk0;
  s32 unk4;
  s32 unk8;
  s16 unkC;
  u8 unkE;
  s16 unk10;
  s16 unk12;
  s32 unk14;
  u8 unk18;
  u8 unk19;
  s16 unk1A;
  s16 unk1C;
  s16 unk1E;
  s16 unk20;
  u8 unk22;
  u8 unk23;
  u8 unk24;
  s16 unk26;
  s16 unk28;
  s16 unk2A;
  s32 unk2C;
  s32 unk30;
  s32 unk34;
  s32 unk38;
  Vtx* unk3C;
  ALSoundState* unk40; // Sound 1
  s32 unk44; // Sound 2
};

struct S_802FDB98 {
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
}; // Size: 0x18

// Proposed file name: tnt.c
//
// This file is the explosive/TNT object system: timed or trigger-detonated
// boxes (the crates the player has to set off, the depots that chain-react,
// and the missile-detonator targets). Each object (S_8039B070) has a fuse
// timer (unk10/unk12), a detonation/destroyed state, a glowing/pulsing
// texture (the prim color in unk20 oscillates), proximity collision against
// the player and the missile (unk1E = blast radius), and chained explosions.
// Templates come from D_hd_code_802FDB98; live objects from D_hd_code_8039B070.
// At the end of the file are two boot-time controller-detection helpers
// (splat grouped them here by address).

void func_hd_code_8028DA5C(Vtx*, u8);                   /* extern */
struct S_8039B070* func_hd_code_8028DE94();
void func_hd_code_802CDA10(s32, s32, s32);
void sndDeactivate(s32);
void func_hd_code_8028DD64(u8);                       /* extern */
void func_hd_code_802CDAE8(s16, s16);                  /* extern */
void func_hd_code_802AACD4(u8, s32, s32, s16*, s16*);

extern s32 D_hd_code_803A73F0;
extern s32 D_hd_code_803A73F4;
extern s32 D_hd_code_803A73F8;
extern s16 D_hd_code_802FDB70[];
extern struct S_8039B070 D_hd_code_8039B070[];
extern s32 D_hd_code_8039B610;
extern s32 D_hd_code_8039B614;
extern s32 D_hd_code_8039B618;
extern s32 D_hd_code_8039B61C;
extern s8 D_hd_code_8039B620;
extern struct S_802FDB98 D_hd_code_802FDB98[];

struct S_Tnt {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 unk6;
    u8 unk7;
    s16 unk8;
    s16 unkA;
}; // Size: 0xC

// <data>
s16 D_hd_code_802FDB70[20] = {
  0x0000, 0x0087, 0x0069, 0x0096,
  0x0096, 0x0087, 0x0000, 0x0096,
  0x00C8, 0x07D0, 0x00AF, 0x0000,
  0x0000, 0x00C3, 0x00BE, 0x00B9,
  0x0069, 0x0000, 0x0000, 0x0000
};

struct S_802FDB98 D_hd_code_802FDB98[2] = {
  { 0xFFF1, 0x000F, 0x0000, 0x001E, 0xFFF1, 0x000F, 0x0706, 0x0707, 0x0706, 0x0707, 0x0340, 0x03A0 },
  { 0xFFF1, 0x000F, 0x0000, 0x001E, 0xFFF1, 0x000F, 0x0706, 0x0707, 0x03EA, 0x03EB, 0x0340, 0x03A0 }
};
// </data>

// Build the live TNT list from the level's placements [arg0, arg1): copy
// position (snapping y to the ground), type, fuse length and chain target,
// load the type's four textures, and build the 8-vertex box geometry
// (already named: LoadLevelTnt)
void LoadLevelTnt(struct S_Tnt* arg0, s32 arg1) {
    D_hd_code_8039B610 = 0;
    D_hd_code_8039B614 = 0;
    D_hd_code_8039B618 = 0;
    D_hd_code_8039B61C = 0;
    D_hd_code_8039B620 = 0;
    while ((s32)arg0 != arg1) {

        D_hd_code_8039B070[D_hd_code_8039B610].unk0 = arg0->unk0 << 5;
        D_hd_code_8039B070[D_hd_code_8039B610].unk4 = arg0->unk2 << 5;
        D_hd_code_8039B070[D_hd_code_8039B610].unk8 = arg0->unk4 << 5;
        D_hd_code_8039B070[D_hd_code_8039B610].unk4 = func_hd_code_802CE6F8(D_hd_code_8039B070[D_hd_code_8039B610].unk0, D_hd_code_8039B070[D_hd_code_8039B610].unk8, D_hd_code_8039B070[D_hd_code_8039B610].unk4);
        D_hd_code_8039B070[D_hd_code_8039B610].unk23 = D_hd_code_803F932C;
        D_hd_code_8039B070[D_hd_code_8039B610].unkE = arg0->unk6;
        D_hd_code_8039B070[D_hd_code_8039B610].unk10 = arg0->unk7 * 0x3C;
        D_hd_code_8039B070[D_hd_code_8039B610].unk12 = (s16) D_hd_code_8039B070[D_hd_code_8039B610].unk10;
        D_hd_code_8039B070[D_hd_code_8039B610].unk2C = func_hd_code_802A0CC8(D_hd_code_802FDB98[D_hd_code_8039B070[D_hd_code_8039B610].unkE].unkC, 0);
        D_hd_code_8039B070[D_hd_code_8039B610].unk30 = func_hd_code_802A0CC8(D_hd_code_802FDB98[D_hd_code_8039B070[D_hd_code_8039B610].unkE].unkE, 0);
        D_hd_code_8039B070[D_hd_code_8039B610].unk34 = func_hd_code_802A0CC8(D_hd_code_802FDB98[D_hd_code_8039B070[D_hd_code_8039B610].unkE].unk10, 0);
        D_hd_code_8039B070[D_hd_code_8039B610].unk38 = func_hd_code_802A0CC8(D_hd_code_802FDB98[D_hd_code_8039B070[D_hd_code_8039B610].unkE].unk12, 0);
        D_hd_code_8039B070[D_hd_code_8039B610].unkC = 0;
        D_hd_code_8039B070[D_hd_code_8039B610].unk14 = 0;
        D_hd_code_8039B070[D_hd_code_8039B610].unk1E = 0;
        D_hd_code_8039B070[D_hd_code_8039B610].unk19 = 0;
        D_hd_code_8039B070[D_hd_code_8039B610].unk1A = arg0->unk8;
        D_hd_code_8039B070[D_hd_code_8039B610].unk1C = arg0->unkA;
        D_hd_code_8039B070[D_hd_code_8039B610].unk20 = 0;
        D_hd_code_8039B070[D_hd_code_8039B610].unk22 = 0;
        D_hd_code_8039B070[D_hd_code_8039B610].unk24 = 0;
        D_hd_code_8039B070[D_hd_code_8039B610].unk26 = 0;
        D_hd_code_8039B070[D_hd_code_8039B610].unk28 = 0;
        D_hd_code_8039B070[D_hd_code_8039B610].unk2A = 0;
        D_hd_code_8039B070[D_hd_code_8039B610].unk18 = 1;
        D_hd_code_8039B070[D_hd_code_8039B610].unk3C = (Vtx*)D_hd_code_80358070;
        D_hd_code_80358070 += 8 * sizeof(Vtx);
        func_hd_code_8028DA5C(D_hd_code_8039B070[D_hd_code_8039B610].unk3C, D_hd_code_8039B070[D_hd_code_8039B610].unkE);
        D_hd_code_8039B610 += 1;
        arg0++;

    }
}

// Fill the 8 corner vertices of a TNT box of type arg1 from the type's
// min/max extents, with box-mapped texcoords
// Proposed name: BuildTntBox
void func_hd_code_8028DA5C(Vtx* arg0, u8 arg1) {
  arg0[0].v.ob[0] = D_hd_code_802FDB98[arg1].unk2;
  arg0[0].v.ob[1] = D_hd_code_802FDB98[arg1].unk4;
  arg0[0].v.ob[2] = D_hd_code_802FDB98[arg1].unk8;
  arg0[0].v.tc[1] = 0;
  arg0[0].v.tc[0] = 0;

  arg0[1].v.ob[0] = D_hd_code_802FDB98[arg1].unk2;
  arg0[1].v.ob[1] = D_hd_code_802FDB98[arg1].unk6;
  arg0[1].v.ob[2] = D_hd_code_802FDB98[arg1].unk8;
  arg0[1].v.tc[1] = 0x3E0;
  arg0[1].v.tc[0] = 0;

  arg0[2].v.ob[0] = D_hd_code_802FDB98[arg1].unk2;
  arg0[2].v.ob[1] = D_hd_code_802FDB98[arg1].unk6;
  arg0[2].v.ob[2] = D_hd_code_802FDB98[arg1].unkA;
  arg0[2].v.tc[0] = 0x3E0,
  arg0[2].v.tc[1] = 0x3E0;

  arg0[3].v.ob[0] = D_hd_code_802FDB98[arg1].unk2;
  arg0[3].v.ob[1] = D_hd_code_802FDB98[arg1].unk4;
  arg0[3].v.ob[2] = D_hd_code_802FDB98[arg1].unkA;
  arg0[3].v.tc[0] = 0x3E0;
  arg0[3].v.tc[1] = 0;

  arg0[4].v.ob[0] = D_hd_code_802FDB98[arg1].unk0;
  arg0[4].v.ob[1] = D_hd_code_802FDB98[arg1].unk4;
  arg0[4].v.ob[2] = D_hd_code_802FDB98[arg1].unk8;
  arg0[4].v.tc[0] = 0x3E0;
  arg0[4].v.tc[1] = 0;

  arg0[5].v.ob[0] = D_hd_code_802FDB98[arg1].unk0;
  arg0[5].v.ob[1] = D_hd_code_802FDB98[arg1].unk6;
  arg0[5].v.ob[2] = D_hd_code_802FDB98[arg1].unk8;
  arg0[5].v.tc[0] = 0x3E0,
  arg0[5].v.tc[1] = 0x3E0;

  arg0[6].v.ob[0] = D_hd_code_802FDB98[arg1].unk0;
  arg0[6].v.ob[1] = D_hd_code_802FDB98[arg1].unk6;
  arg0[6].v.ob[2] = D_hd_code_802FDB98[arg1].unkA;
  arg0[6].v.tc[1] = 0x3E0;
  arg0[6].v.tc[0] = 0;

  arg0[7].v.ob[0] = D_hd_code_802FDB98[arg1].unk0;
  arg0[7].v.ob[1] = D_hd_code_802FDB98[arg1].unk4;
  arg0[7].v.ob[2] = D_hd_code_802FDB98[arg1].unkA;
  arg0[7].v.tc[1] = 0;
  arg0[7].v.tc[0] = 0;
}

// Detonate TNT object arg0: spawn the explosion at its position, start its
// short destroyed timer, set the camera shake, stop its looping sounds and
// play the boom (and re-arm the warning beep on another live object)
// Proposed name: DetonateTnt
void func_hd_code_8028DD64(u8 arg0) {
  struct S_8039B070* sp1C;

  func_hd_code_802CDA10(D_hd_code_8039B070[arg0].unk0, D_hd_code_8039B070[arg0].unk4, D_hd_code_8039B070[arg0].unk8);
  D_hd_code_8039B070[arg0].unk19 = 5;
  D_hd_code_8039B070[arg0].unk18 = 0;
  D_hd_code_802E8BE4 = 0xA;
  D_hd_code_802E8BE8 = 0x190;
  if (D_hd_code_8039B070[arg0].unk40 != 0) {
    sndDeactivate(D_hd_code_8039B070[arg0].unk40);
    sp1C = func_hd_code_8028DE94();
    if (sp1C != 0) {
      sndPlaySfx(D_hd_code_80367738, 0x73, &sp1C->unk40); // TODO: pointer to pointer seems wrong here
    }
  }
  if (D_hd_code_8039B070[arg0].unk44 != 0) {
    sndDeactivate(D_hd_code_8039B070[arg0].unk44);
  }
  sndPlaySfx(D_hd_code_80367738, 0x10, NULL);
}

// Find a live, already-triggered TNT object (used to move the warning beep
// to another active fuse); returns NULL if none
// Proposed name: FindTriggeredTnt
struct S_8039B070* func_hd_code_8028DE94(void) {
  s32 sp4;

  for (sp4 = 0; sp4 < D_hd_code_8039B610; sp4++) {
    if (D_hd_code_8039B070[sp4].unk18 != 0 && D_hd_code_8039B070[sp4].unk14 != 0) {
      return &D_hd_code_8039B070[sp4];
    }
  }

  return 0;
}

// Per-frame TNT update (arg0 = current vehicle). For each object: handle the
// post-detonation explosion delay (firing the chain target), count down a
// triggered fuse (detonating at 0), pulse the glow color, run collision
// against the player/missile to trigger or destroy it, compute the blast
// radius pushing the player, register it with the collision system, and
// manage its warning/burning looping sounds.
// Proposed name: UpdateTnt
void func_hd_code_8028DF14(u8 arg0) {
    s32 sp4C;
    u8 sp4B;
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s16 sp3A;
    s16 sp38;
    u8 sp37;
    f32 sp30;
    s16 sp2E;
    u8 sp2D;

    for(sp4C = 0; sp4C < D_hd_code_8039B610; sp4C++) {
        if (D_hd_code_8039B070[sp4C].unk19 != 0) {
            D_hd_code_8039B070[sp4C].unk19 = D_hd_code_8039B070[sp4C].unk19 - 1;
            if (D_hd_code_8039B070[sp4C].unk19 == 0) {
                D_hd_code_803A73F0 = D_hd_code_8039B070[sp4C].unk0;
                D_hd_code_803A73F4 = D_hd_code_8039B070[sp4C].unk4;
                D_hd_code_803A73F8 = D_hd_code_8039B070[sp4C].unk8;
                if (D_hd_code_8039B070[sp4C].unk1A != 0) {
                    func_hd_code_802CDAE8(D_hd_code_8039B070[sp4C].unk1C, D_hd_code_8039B070[sp4C].unk1A);
                }
            }
        }
        if (D_hd_code_8039B070[sp4C].unk18 != 0) {
            if (D_hd_code_8039B070[sp4C].unk14 != 0) {
                if (D_hd_code_8039B070[sp4C].unk10 != 0) {
                    D_hd_code_8039B070[sp4C].unk10 = D_hd_code_8039B070[sp4C].unk10 - 1;
                    if (D_hd_code_8039B070[sp4C].unk10 <= 0) {
                        func_hd_code_8028DD64(sp4C);
                    }
                }
            }
            if (D_hd_code_8039B070[sp4C].unk14 != 0) {
                if (D_hd_code_8039B070[sp4C].unk12 != 0) {
                    sp30 = (f32) D_hd_code_8039B070[sp4C].unk10 / (f32) D_hd_code_8039B070[sp4C].unk12;
                    sp30 = (f32) (1.0 - (f64) sp30);
                    sp30 = (f32) ((f64) sp30 * 50.0);
                    if (D_hd_code_8039B070[sp4C].unk22 != 0) {
                        D_hd_code_8039B070[sp4C].unk20 -= (s16) (s32) sp30;
                        if (D_hd_code_8039B070[sp4C].unk20 < 0) {
                            D_hd_code_8039B070[sp4C].unk20 = -D_hd_code_8039B070[sp4C].unk20;
                            D_hd_code_8039B070[sp4C].unk22 = 0;
                        }
                    } else {
                        D_hd_code_8039B070[sp4C].unk20 += (s16) (s32) sp30;
                        if (D_hd_code_8039B070[sp4C].unk20 >= 0x100) {
                            D_hd_code_8039B070[sp4C].unk20 = 0x1FE - D_hd_code_8039B070[sp4C].unk20;
                            D_hd_code_8039B070[sp4C].unk22 = 1;
                        }
                    }
                }
            }
            if (arg0 == 0) {
                D_hd_code_8039B070[sp4C].unk1E = 0;
            }
            if ((D_hd_code_8039B070[sp4C].unk1E != 0) && (func_hd_code_802CE958(sp4C + 0x100) == 0)) {
                func_hd_code_802CE65C(D_hd_code_8039B070[sp4C].unk0, D_hd_code_8039B070[sp4C].unk8, D_hd_code_8039B070[sp4C].unk1E, D_hd_code_8039B070[sp4C].unkC);
                D_hd_code_8039B070[sp4C].unk0 = D_hd_code_803F9320;
                D_hd_code_8039B070[sp4C].unk8 = D_hd_code_803F9324;
                D_hd_code_8039B070[sp4C].unk4 = func_hd_code_802CE6F8(D_hd_code_8039B070[sp4C].unk0, D_hd_code_8039B070[sp4C].unk8, D_hd_code_8039B070[sp4C].unk4);
                D_hd_code_8039B070[sp4C].unk23 = D_hd_code_803F932C;
            }
            func_hd_code_802CE4F0(D_hd_code_8039B070[sp4C].unk0, D_hd_code_8039B070[sp4C].unk4, D_hd_code_8039B070[sp4C].unk8);
            sp4B = func_hd_code_802CDF94(D_hd_code_802FDB98[D_hd_code_8039B070[sp4C].unkE].unk14);
            if (sp4B != 0) {
                if (D_hd_code_803F932D != 0) {
                    D_hd_code_803643D9 = 1;
                    func_hd_code_8028DD64(sp4C);
                }
                if (D_hd_code_803F932E != 0) {
                    D_hd_code_803ED40C = 1;
                }
                if ((D_hd_code_8039B070[sp4C].unk14 == 0) && (arg0 != 0)) {
                    if (func_hd_code_8028DE94() == 0) {
                        sndPlaySfx(D_hd_code_80367738, 0x73, (ALSoundState* ) &D_hd_code_8039B070[sp4C].unk40);
                    }
                    D_hd_code_8039B070[sp4C].unk14 = D_hd_code_80358060;
                }
                if ((u8) D_hd_code_8039B620 == arg0) {
                    sp44 = D_hd_code_803643E0 - D_hd_code_8039B614,
                    sp40 = D_hd_code_803643E4 - D_hd_code_8039B618,
                    sp3C = D_hd_code_803643E8 - D_hd_code_8039B61C;
                    D_hd_code_8039B070[sp4C].unk1E = (s16) (s32) (sqrtf((f32) ((sp44 * sp44) + (sp40 * sp40) + (sp3C * sp3C))) + 8.0f);
                    if ((D_hd_code_8039B070[sp4C].unk1E > D_hd_code_802FDB70[arg0]) && (levelno != 0x22)) {
                        D_hd_code_8039B070[sp4C].unk1E = D_hd_code_802FDB70[arg0];
                    }
                } else {
                    D_hd_code_8039B070[sp4C].unk1E = 0;
                }
            }
            if (D_hd_code_8039B070[sp4C].unk1E != 0) {
                sp37 = 0;
                sp3A = D_hd_code_803A7410,
                sp38 = D_hd_code_803A7412;

                func_hd_code_802CE5BC(D_hd_code_8039B070[sp4C].unk0, D_hd_code_8039B070[sp4C].unk4, D_hd_code_8039B070[sp4C].unk8, (s32) D_hd_code_802FDB98[D_hd_code_8039B070[sp4C].unkE].unk14, 0xC9, 0);
                if ((sp3A != D_hd_code_803A7410) || (sp38 != D_hd_code_803A7412)) {
                    sp37 = 1;
                }
                if (D_hd_code_8039B070[sp4C].unk1A != 0) {
                    sp2E = 0;
                } else {
                    sp2E = D_hd_code_8039B070[sp4C].unk1C;
                }
                if (func_hd_code_802CDB70(D_hd_code_802FDB98[D_hd_code_8039B070[sp4C].unkE].unk16, sp2E) != 0) {
                    func_hd_code_8028DD64(sp4C);
                }
            } else {
                sp37 = 0;
            }
            sp2D = 0;
            if ((D_hd_code_803A7410 != 0) || (D_hd_code_803A7412 != 0xFFF)) {
                if (func_hd_code_8029B930() < 0x64) {
                    sp2D = 1;
                } else {
                    if (sp37 != 0) {
                        D_hd_code_8039B070[sp4C].unkC = func_hd_code_802CE3B8(D_hd_code_8039B070[sp4C].unkC);

                    } else {
                        D_hd_code_8039B070[sp4C].unkC = func_hd_code_802A6F6C();
                    }
                }
            }
            if (((sp2D != 0) || (arg0 == 0)) && (D_hd_code_8039B070[sp4C].unk18 != 0)) {
                func_hd_code_802CE880(sp4C + 0x100, D_hd_code_8039B070[sp4C].unk0, D_hd_code_8039B070[sp4C].unk4, D_hd_code_8039B070[sp4C].unk8, (s32) D_hd_code_802FDB98[D_hd_code_8039B070[sp4C].unkE].unk14);
                D_hd_code_8039B070[sp4C].unk1E = 0;
            } else {
                func_hd_code_802CE90C(sp4C + 0x100);
            }
            if (D_hd_code_8039B070[sp4C].unk1E > 0) {
                D_hd_code_8039B070[sp4C].unk1E -= (levelno != 0x2B ? 8 : 4);
            } else {
                D_hd_code_8039B070[sp4C].unk1E = 0;
            }
            if ((D_hd_code_8039B070[sp4C].unk1E > 0) && (D_hd_code_8039B070[sp4C].unk44 == 0) && (D_hd_code_8039B070[sp4C].unk18 != 0)) {
                sndPlaySfx(D_hd_code_80367738, 7, (ALSoundState* ) &D_hd_code_8039B070[sp4C].unk44);
                if (D_hd_code_80364456 == 4) {
                    func_hd_code_8026AD30(0x54);
                }
            }
            if ((D_hd_code_8039B070[sp4C].unk44 != 0) && (D_hd_code_8039B070[sp4C].unk1E == 0)) {
                sndDeactivate(D_hd_code_8039B070[sp4C].unk44);
            }
        }
    }
    D_hd_code_8039B614 = D_hd_code_803643E0;
    D_hd_code_8039B618 = D_hd_code_803643E4;
    D_hd_code_8039B61C = D_hd_code_803643E8;
    D_hd_code_8039B620 = (s8) arg0;
}

// Draw the TNT boxes: each live box is drawn with its four textures (two
// per face pair, 2-cycle LOD-blended), positioned and spun by its yaw, with
// the pulsing prim color for the glow
// Proposed name: DrawTnt
void func_hd_code_8028E9E4(Gfx** gfx, struct Model1* arg1) {
    Gfx* entry;
    s32 sp1A0;
    f32 sp160[4][4];
    f32 sp120[4][4];

    entry = *gfx;
    if (D_hd_code_8039B610 > 0) {
        gDPPipeSync(entry++);
        gDPSetCycleType(entry++, G_CYC_2CYCLE);
        gDPSetRenderMode(entry++, G_RM_PASS, G_RM_AA_ZB_OPA_SURF2);
        gDPSetCombineLERP(entry++, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, SHADE);
        gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
        gSPSetGeometryMode(entry++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
        gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);
        gDPSetTextureLOD(entry++, G_TL_TILE);
    }
    for(sp1A0 = 0; sp1A0 < D_hd_code_8039B610; sp1A0++) {
        if (D_hd_code_8039B070[sp1A0].unk18 != 0) {
            guAlignF(sp160, (f32) (((f64) (f32) D_hd_code_8039B070[sp1A0].unk2A / 4095.0) * 360.0), 0.0f, 1.0f, 0.0f);
            guTranslateF(sp120, (f32) D_hd_code_8039B070[sp1A0].unk0 / 32.0f, (f32) D_hd_code_8039B070[sp1A0].unk4 / 32.0f, (f32) D_hd_code_8039B070[sp1A0].unk8 / 32.0f);
            guMtxCatF(sp160, sp120, sp160);
            guMtxF2L(sp160, &arg1->unk600[sp1A0]);
            gSPMatrix(entry++, (u32) &D_2000000.unk600[sp1A0], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);

            gSPVertex(entry++, osVirtualToPhysical(D_hd_code_8039B070[sp1A0].unk3C), 8, 0);
            gDPPipeSync(entry++);
            gDPSetTextureImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, D_hd_code_8039B070[sp1A0].unk2C + 0x80000000);
            gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
            gDPLoadSync(entry++);
            gDPLoadBlock(entry++, G_TX_LOADTILE, 0, 0, 1023, 256);
            gDPSetTextureImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, D_hd_code_8039B070[sp1A0].unk30 + 0x80000000);
            gDPTileSync(entry++);
            gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0100, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
            gDPLoadSync(entry++);
            gDPLoadBlock(entry++, G_TX_LOADTILE, 0, 0, 1023, 256);
            gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD);
            gDPSetTileSize(entry++, G_TX_RENDERTILE, qu102(0.5), qu102(0.5), qu102(31.5), qu102(31.5));
            gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0x0100, 1, 0, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD);
            gDPSetTileSize(entry++, 1, qu102(0.5), qu102(0.5), qu102(31.5), qu102(31.5));
            gDPSetPrimColor(entry++, 0, D_hd_code_8039B070[sp1A0].unk20, 0x00, 0x00, 0x00, 0x00);

            gSP1Triangle(entry++, 6, 3, 2, 0);
            gSP1Triangle(entry++, 6, 7, 3, 0);
            gSP1Triangle(entry++, 4, 1, 0, 0);
            gSP1Triangle(entry++, 1, 4, 5, 0);

            gSPModifyVertex(entry++, 0, 20, 0x03E00000);
            gSPModifyVertex(entry++, 1, 20, 0x03E003E0);
            gSPModifyVertex(entry++, 2, 20, 0x3E0);
            gSPModifyVertex(entry++, 3, 20, 0);

            gSP1Triangle(entry++, 0, 1, 2, 0);
            gSP1Triangle(entry++, 0, 2, 3, 0);

            gSPModifyVertex(entry++, 7, 20, 0x03E00000);
            gSPModifyVertex(entry++, 6, 20, 0x03E003E0);
            gSPModifyVertex(entry++, 5, 20, 0x3E0);
            gSPModifyVertex(entry++, 4, 20, 0);

            gSP1Triangle(entry++, 7, 5, 4, 0);
            gSP1Triangle(entry++, 7, 6, 5, 0);
            gDPSetTextureImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, D_hd_code_8039B070[sp1A0].unk34 + 0x80000000);
            gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
            gDPLoadSync(entry++);
            gDPLoadBlock(entry++, G_TX_LOADTILE, 0, 0, 1023, 256);
            gDPSetTextureImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, D_hd_code_8039B070[sp1A0].unk38 + 0x80000000);
            gDPTileSync(entry++);
            gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0100, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
            gDPLoadSync(entry++);
            gDPLoadBlock(entry++, G_TX_LOADTILE, 0, 0, 1023, 256);
            gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD);
            gDPSetTileSize(entry++, G_TX_RENDERTILE, qu102(0.5), qu102(0.5), qu102(31.5), qu102(31.5));
            gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0x0100, 1, 0, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 5, G_TX_NOLOD);
            gDPSetTileSize(entry++, 1, qu102(0.5), qu102(0.5), qu102(31.5), qu102(31.5));

            gSPModifyVertex(entry++, 2, 20, 0);
            gSPModifyVertex(entry++, 1, 20, 0x03E00000);
            gSPModifyVertex(entry++, 5, 20, 0x03E003E0);
            gSPModifyVertex(entry++, 6, 20, 0x3E0);

            gSP1Triangle(entry++, 5, 2, 1, 0);
            gSP1Triangle(entry++, 2, 5, 6, 0);
            gSPPopMatrix(entry++, G_MTX_MODELVIEW);
        }
    }
    gDPSetTextureLOD(entry++, G_TL_LOD);
    gDPPipeSync(entry++);

    *gfx = entry;
}

// Begin tracking TNT objects sitting on moveable geometry group arg0 (so
// they ride along with it): record their offset within the platform
// Proposed name: AttachTntToPlatform
void func_hd_code_8028F6B4(u8 arg0) {
  s32 sp24;

  for(sp24 = 0; sp24 < D_hd_code_8039B610; sp24++) {
    if ((D_hd_code_8039B070[sp24].unk18 != 0) && (D_hd_code_8039B070[sp24].unk23 == arg0)) {
      D_hd_code_8039B070[sp24].unk1E = 0;
      D_hd_code_8039B070[sp24].unk24 = 1;
      func_hd_code_802AACD4(arg0, D_hd_code_8039B070[sp24].unk0, D_hd_code_8039B070[sp24].unk8, &D_hd_code_8039B070[sp24].unk26, &D_hd_code_8039B070[sp24].unk28);
    }
  }
}

// Move the platform-attached TNT objects along with moveable geometry group
// arg0 each frame, re-snapping their ground height and re-checking collision
// Proposed name: MoveTntWithPlatform
void func_hd_code_8028F794(u8 arg0) {
  s32 sp24;
  s16 sp22;

  for(sp24 = 0; sp24 < D_hd_code_8039B610; sp24++) {
    if ((D_hd_code_8039B070[sp24].unk18 != 0) && (D_hd_code_8039B070[sp24].unk24 != 0)) {
      func_hd_code_802AAE1C(arg0, D_hd_code_8039B070[sp24].unk26, D_hd_code_8039B070[sp24].unk28, &D_hd_code_8039B070[sp24], &D_hd_code_8039B070[sp24].unk8);
      D_hd_code_8039B070[sp24].unk4 = func_hd_code_802CE6F8(D_hd_code_8039B070[sp24].unk0, D_hd_code_8039B070[sp24].unk8, D_hd_code_8039B070[sp24].unk4);
      if (D_hd_code_8039B070[sp24].unk1A != 0) {
        sp22 = 0;
      } else {
        sp22 = D_hd_code_8039B070[sp24].unk1C;
      }
      func_hd_code_802CE4F0(D_hd_code_8039B070[sp24].unk0, D_hd_code_8039B070[sp24].unk4, D_hd_code_8039B070[sp24].unk8);
      if (func_hd_code_802CDB70(D_hd_code_802FDB98[D_hd_code_8039B070[sp24].unkE].unk14, sp22) != 0) {
        func_hd_code_8028DD64(sp24);
      }
    }
  }
}

// Clear the platform-attached flag on all TNT objects
// Proposed name: DetachAllTnt
void func_hd_code_8028F93C(void) {
  s32 sp4;

  for(sp4 = 0; sp4 < D_hd_code_8039B610; sp4++) {
    D_hd_code_8039B070[sp4].unk24 = 0;
  }
}

// Set D_hd_code_803A7424 if point (arg0, arg1, arg2) is within any live TNT's radius
// (collision query used by other systems)
// Proposed name: TestPointAgainstTnt
void func_hd_code_8028F994(s32 arg0, s32 arg1, s32 arg2) {
  s32 sp24;

  arg0 = arg0 >> 5,
  arg1 = arg1 >> 5,
  arg2 = arg2 >> 5;
  for(sp24 = 0; sp24 < D_hd_code_8039B610; sp24++) {
    if (D_hd_code_8039B070[sp24].unk18 != 0) {
      s32 sp20 = func_hd_code_8026A6F0(arg0, arg1, arg2, (s32) D_hd_code_8039B070[sp24].unk0 >> 5, (s32) D_hd_code_8039B070[sp24].unk4 >> 5, (s32) D_hd_code_8039B070[sp24].unk8 >> 5);
      if (sp20 <= D_hd_code_802FDB98[D_hd_code_8039B070[sp24].unkE].unk14 >> 5) {
        D_hd_code_803A7424 = 1;
      }
    }
  }
}

// As above but with an extra radius margin arg3, and ignoring
// platform-attached objects
// Proposed name: TestSphereAgainstTnt
void func_hd_code_8028FAC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
  s32 sp24;
  s32 sp20;

  arg0 = arg0 >> 5,
  arg1 = arg1 >> 5,
  arg2 = arg2 >> 5,
  arg3 = arg3 >> 5;

  for(sp24 = 0; sp24 < D_hd_code_8039B610; sp24++) {
    if ((D_hd_code_8039B070[sp24].unk18 != 0) && (D_hd_code_8039B070[sp24].unk24 == 0)) {
      sp20 = func_hd_code_8026A6F0(arg0, arg1, arg2, (s32) D_hd_code_8039B070[sp24].unk0 >> 5, (s32) D_hd_code_8039B070[sp24].unk4 >> 5, (s32) D_hd_code_8039B070[sp24].unk8 >> 5);
      if (sp20 <= ((s16) D_hd_code_802FDB98[D_hd_code_8039B070[sp24].unkE].unk14 >> 5) + arg3) {
        D_hd_code_803A7424 = 1;
      }
    }
  }
}

