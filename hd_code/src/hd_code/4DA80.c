#include "common.h"
#include "functions.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"


struct S_8039C960 {
  s32 unk0;
  s32 unk4;
  s32 unk8;
  s32 unkC;
  s16 unk10;
  s16 unk12;
  s16 unk14;
  s16 unk16;
  u8 unk18;
  s16 unk1A;
  s32 unk1C;
  s32 unk20;
  s32 unk24;
  u8 unk28;
  u8 unk29;
  u8 pad2A;
  u8 pad2B;
}; // Size: 0x2C

struct S_802FE3C0 {
  u8 pad0[0x5A0];
  s16 unk5A0;
  s16 pad5A2;
  s32 unk5A4;
  u8 unk5A8;
  u8 unk5A9;
  u8 pad5AA[0x5AC - 0x5AA];
  s32 unk5AC;
  u8 unk5B0;
  u8 pad5B1;
  u8 pad5B2;
  u8 pad5B3;
  s32 pad5B4;
}; // Size: 0x5B8

// Proposed file name: projectiles.c
//
// This file is the ballistic projectile system (up to 4 in flight at once,
// D_8039C960): an object is launched with a speed toward a target, flies a
// gravity arc, and detonates on hitting terrain, a building or the world
// edge - colliding objects can damage buildings (D_hd_code_803643D9) and
// spawn explosions. Used for thrown/fired objects like boulders. Projectile
// templates (collision model, explosion ids) come from D_hd_code_802FE3C0.

void func_hd_code_80292DDC(s32);

extern struct S_8039C960 D_8039C960[4];
extern u16 D_803BE716;
extern struct S_802FE3C0 D_hd_code_802FE3C0[];

// Clear all projectile slots at level init
// Proposed name: InitProjectiles
void func_hd_code_80292240(void) {
  s32 sp4;

  for(sp4 = 0; sp4 < 4; sp4++) {
    D_8039C960[sp4].unk28 = 0;
  }
}

// Launch a projectile of type arg7 from (arg1, arg2, arg3) toward
// (arg4, arg5, arg6) at speed arg0 (arg8 = collision flag): claim a free
// slot, set the velocity from the normalized direction, and store the
// initial yaw (quadrant atan). Returns 0 if no slot is free.
// Proposed name: LaunchProjectile
s32 func_hd_code_80292288(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s16 arg8) {
  s32 sp2C;
  u8 sp2B;
  f32 sp24;
  f32 sp20;
  f32 sp1C;
  f32 sp18;

  sp2C = 0;
  sp2B = 0;
  while((sp2B == 0) && (sp2C < 4)) {
    if (D_8039C960[sp2C].unk28 != 0) {
      sp2C += 1;
    } else {
      sp2B = 1;
    }
  }

  if (sp2B == 0) {
    return 0;
  }
  D_8039C960[sp2C].unk28 = 1;
  D_8039C960[sp2C].unk18 = arg7;
  D_8039C960[sp2C].unk1A = arg8;
  D_8039C960[sp2C].unk0 = arg4;
  D_8039C960[sp2C].unk4 = arg5;
  D_8039C960[sp2C].unk8 = arg6;
  D_8039C960[sp2C].unk1C = arg5;
  D_8039C960[sp2C].unk24 = 0;
  D_8039C960[sp2C].unk29 = 0xFF;
  sp24 = (arg4 - arg1),
  sp20 = (arg5 - arg2),
  sp1C = (arg6 - arg3);
  guNormalize(&sp24, &sp20, &sp1C);
  D_8039C960[sp2C].unk10 = (arg0 * sp24);
  D_8039C960[sp2C].unk12 = (arg0 * sp1C);
  D_8039C960[sp2C].unk20 = (arg0 * sp20);
  sp18 = sqrtf((((arg4 - arg1) * (arg4 - arg1)) + ((arg6 - arg3) * (arg6 - arg3))));
  if (sp18 < 1.0) {
    sp18 = 1.0f;
  }
  if ((arg4 >= arg1) && (arg6 >= arg3)) {
    D_8039C960[sp2C].unk14 = func_hd_code_802AD7D4((((arg4 - arg1) * 65535.0) / sp18)) >> 4;
  }
  if ((arg4 >= arg1) && (arg6 < arg3)) {
    D_8039C960[sp2C].unk14 = (func_hd_code_802AD7D4((((arg3 - arg6) * 65535.0) / sp18)) >> 4) + 0x400;
  }
  if ((arg4 < arg1) && (arg6 < arg3)) {
    D_8039C960[sp2C].unk14 = (func_hd_code_802AD7D4((((arg1 - arg4) * 65535.0) / sp18)) >> 4) + 0x800;
  }
  if ((arg4 < arg1) && (arg6 >= arg3)) {
    D_8039C960[sp2C].unk14 = (func_hd_code_802AD7D4((((arg6 - arg3) * 65535.0) / sp18)) >> 4) + 0xC00;
  }
  return 1;
}

// Per-frame projectile update: advance each live projectile along its arc
// (x/z linear, y under -12 gravity), update its pitch, and detonate it
// (func_hd_code_80292DDC) when it leaves the map, drops below ground, or hits
// a building/the terrain - damaging the struck building and spawning the
// per-template trail/impact explosions. Also fades the projectile's tint.
// Proposed name: UpdateProjectiles
void func_hd_code_80292830(void) {
    s32 sp34;
    s16 sp32;
    s16 sp30;
    s16 sp2E;
    s32 sp28;
    s32 sp24;

    sp28 = (u16) D_803BE714 * D_803BE70C;
    sp24 = D_803BE716 * D_803BE710;
    for(sp34 = 0; sp34 < 4; sp34++) {
        if (D_8039C960[sp34].unk28 != 0) {
            D_8039C960[sp34].unk0 += D_8039C960[sp34].unk10;
            D_8039C960[sp34].unk8 += D_8039C960[sp34].unk12;
            D_8039C960[sp34].unk4 = (D_8039C960[sp34].unk1C + (D_8039C960[sp34].unk20 * D_8039C960[sp34].unk24)) + (((-12.0) * D_8039C960[sp34].unk24) * D_8039C960[sp34].unk24);
            sp32 = D_8039C960[sp34].unkC - D_8039C960[sp34].unk4;
            if (sp32 >= 0x400) {
                sp32 = 0x3FF;
            }
            if (sp32 < -0x3FF) {
                sp32 = -0x3FF;
            }
            D_8039C960[sp34].unk16 = sp32;
            if ((D_8039C960[sp34].unk0 >= sp28) || ((!(D_8039C960[sp34].unk8 < sp24))) || (D_8039C960[sp34].unk0 < 0) || (D_8039C960[sp34].unk8 < 0) || (D_8039C960[sp34].unk4 < 0)) {
                func_hd_code_80292DDC(sp34);
            } else {
                func_hd_code_802CE4F0(D_8039C960[sp34].unk0, D_8039C960[sp34].unk4, D_8039C960[sp34].unk8);
                func_hd_code_802CDF94(D_hd_code_802FE3C0[D_8039C960[sp34].unk18].unk5A0);
                if (D_803F932D != 0) {
                    D_hd_code_803643D9 = 1;
                }

                sp30 = D_803A7410,
                sp2E = D_803A7412;

                func_hd_code_802CE5BC(D_8039C960[sp34].unk0, D_8039C960[sp34].unk4, D_8039C960[sp34].unk8, (s32) D_hd_code_802FE3C0[D_8039C960[sp34].unk18].unk5A0, 0xCA, 0);
                func_hd_code_802CDB70(D_hd_code_802FE3C0[D_8039C960[sp34].unk18].unk5A0, D_8039C960[sp34].unk1A);
                if ((sp30 != D_803A7410) || (sp2E != D_803A7412)) {
                    func_hd_code_80292DDC(sp34);
                }
                if (D_8039C960[sp34].unk4 < func_hd_code_802CE6F8(D_8039C960[sp34].unk0, D_8039C960[sp34].unk8, D_8039C960[sp34].unk4)) {
                    func_hd_code_80292DDC(sp34);
                }

                if (D_hd_code_802FE3C0[D_8039C960[sp34].unk18].unk5A9 != 0) {
                    func_hd_code_802AC61C(D_8039C960[sp34].unk0, D_8039C960[sp34].unk4, D_8039C960[sp34].unk8, D_hd_code_802FE3C0[D_8039C960[sp34].unk18].unk5B0, D_hd_code_802FE3C0[D_8039C960[sp34].unk18].unk5AC);
                }

                D_8039C960[sp34].unkC = D_8039C960[sp34].unk4;
                D_8039C960[sp34].unk29 -= 0x19;
                if ((s32) D_8039C960[sp34].unk29 < 0x64) {
                    D_8039C960[sp34].unk29 = 0xFF;
                }
                D_8039C960[sp34].unk24 += 1;
            }
        }
    }
}

// Detonate projectile arg0: free its slot, spawn the impact explosion, set
// the camera shake and play the boom (sfx 0x10)
// Proposed name: DetonateProjectile
void func_hd_code_80292DDC(s32 arg0) {
  D_8039C960[arg0].unk28 = 0;
  func_hd_code_802AC61C(D_8039C960[arg0].unk0, D_8039C960[arg0].unk4, D_8039C960[arg0].unk8, D_hd_code_802FE3C0[D_8039C960[arg0].unk18].unk5A8, D_hd_code_802FE3C0[D_8039C960[arg0].unk18].unk5A4);
  D_hd_code_802E8BE4 = 0xA;
  D_hd_code_802E8BE8 = 0x190;
  sndPlaySfx(D_hd_code_80367738, 0x10, NULL);
}

// Draw the in-flight projectiles (after their first couple frames): each
// scaled, oriented to its pitch/yaw, tinted by its fade value, drawn from its
// per-type display list
// Proposed name: DrawProjectiles
void func_hd_code_80292EB8(Gfx** gfx, struct Model1* arg1) {
  Gfx* entry;
  s32 spD8;
  f32 sp98[4][4];
  f32 sp58[4][4];

  entry = *gfx;

  gDPPipeSync(entry++);
  gDPSetCycleType(entry++, G_CYC_1CYCLE);
  gDPSetRenderMode(entry++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
  gDPSetCombineMode(entry++, G_CC_SHADE, G_CC_SHADE);
  gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
  gSPSetGeometryMode(entry++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH);
  gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_OFF);

  for(spD8 = 0; spD8 < 4; spD8++) {
    if ((D_8039C960[spD8].unk28 != 0) && (D_8039C960[spD8].unk24 >= 2)) {
      guScaleF(sp98, 0.5f, 0.5f, 0.35f);
      guAlignF(sp58, (f32) (((f64) D_8039C960[spD8].unk16 / 4095.0) * 360.0), 1.0f, 0.0f, 0.0f);
      guMtxCatF(sp98, sp58, sp98);
      guAlignF(sp58, (f32) (((f64) D_8039C960[spD8].unk14 / 4095.0) * 360.0), 0.0f, 1.0f, 0.0f);
      guMtxCatF(sp98, sp58, sp98);
      guTranslateF(sp58, (f32) D_8039C960[spD8].unk0 / 32.0f, (f32) D_8039C960[spD8].unk4 / 32.0f, (f32) D_8039C960[spD8].unk8 / 32.0f);
      guMtxCatF(sp98, sp58, sp98);
      guMtxF2L(sp98, &arg1->unkD00[spD8]);


      gSPMatrix(entry++, &D_2000000.unkD00[spD8], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
      gDPPipeSync(entry++);
      gDPSetPrimColor(entry++, 0, 0, D_8039C960[spD8].unk29, 0, 0, 0xFF);
      gSPDisplayList(entry++, osVirtualToPhysical(&D_hd_code_802FE3C0[D_8039C960[spD8].unk18]));
      gSPPopMatrix(entry++, G_MTX_MODELVIEW);
    }
  }

  gDPPipeSync(entry++);
  *gfx = entry;
}

