#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"

struct S_802AC4C4 {
  s32 unk0;
  s32 unk4;
  s32 unk8;
  s32 unkC;
};

struct S_802FC494 {
  u8 unk0;
  u8 pad1;
  s16 unk2;
  s16 unk4;
  s16 unk6;
  s16 unk8;
  s16 unkA;
  s16 unkC;
  u8 unkE;
  u8 padF;
  s16 unk10;
  s16 unk12;
  s16 unk14;
  u8 unk16; // D_hd_code_802FC4AA
  u8 unk17; // D_hd_code_802FC4AB
  s16 unk18;
  s16 unk1A;
  s16 unk1C;
  s16 unk1E;
  s16 pad20;
}; // Size: 0x22

void func_hd_code_8027DA10(s32, s32, s32);                   /* extern */
void func_hd_code_802C1F30(s32, s32, s32, s32, s32);     /* extern */
f32 func_hd_code_8027DB5C(s32*, s32*, s32);             /* extern */
s16* func_hd_code_802C1EE0(s32);                     /* extern */
f32 func_hd_code_8027DD88(s32, s32, s32*, s32*);    /* extern */
s32 func_hd_code_8027E164(s32, s32, struct S_802AC4C4*, struct S_802AC4C4*);    /* extern */
f32 func_hd_code_8027E228(u8 arg0);
void func_hd_code_802802D4(Vtx*, s32, s32, s32);       /* extern */
void func_hd_code_8028072C(Vtx*, s16, s16, s16, s16, s16, s16); /* extern */
void func_hd_code_802A0CC8(s16, s32);

extern s16 D_8036DCE0[][6];
extern Vtx D_8036DD70[2][12][4];
extern u8 D_8036E370;
extern s32 D_8036E374;
extern u8* D_8036E378;
extern struct S_802FC494 D_hd_code_802FC494[];
extern Vtx* D_8036DCA0[2];
extern Vtx* D_8036DCA8[2];
extern s32 D_8036DCB0;
extern Vtx* D_8036DCB8[2];
extern Vtx* D_8036DCC0[2];
extern Gfx* D_8036DCC8[2];
extern u8 D_8036DCD0;
extern s16 D_8036DCD2;
extern u8 D_8036DCD5;
extern u8 D_8036DCD6;
extern u8 D_8036DCD7;


struct S_802FC3F0 {
  u8 unk0;
  u8 unk1;
  u8 unk2;
  u8 pad3;
  s16 unk4;
  s16 unk6;
  s16 unk8;
  s16 unkA;
  s16 unkC[(0x14 - 0xC) / 2];
  f32 unk14;
  f32 unk18;
  f32 unk1C;
  f32 unk20;
  u8 unk24;
  u8 pad25;
  s16 unk26;
  s32 unk28;
  s32 unk2C;
  u8 unk30;
  u8 unk31;
  u8 pad32;
  u8 pad33;
}; // Size: 0x34

extern struct S_802FC3F0 D_hd_code_802FC3F0[];
extern s32 D_hd_code_803649E8;
extern s32 D_hd_code_802FC51C;

void func_hd_code_8027D810(s32 arg0) {
  switch (arg0) {
    case 0:
      func_hd_code_8027DA10(1, 7, 0x320000);
      break;
    case 4:
      func_hd_code_8027DA10(1, 7, 0xA00000);
      break;
    case 16:
      func_hd_code_8027DA10(1, 7, 0x3C0000);
      func_hd_code_8027DA10(2, 7, 0x3C0000);
      break;
    case 20:
      func_hd_code_8027DA10(1, 7, 0x820000);
      func_hd_code_8027DA10(2, 7, 0x820000);
      break;
    case 15:
      func_hd_code_8027DA10(1, 7, 0x410000);
      func_hd_code_8027DA10(2, 7, 0x410000);
      break;
  }
}

void func_hd_code_8027D8F4(s32 arg0, s32 arg1, s32 arg2) {
  s32 sp34;
  s32 sp30;
  f32 sp2C;
  f32 sp28;
  f32 sp24;

  sp30 = 1;
  sp2C = (6.28318 / (arg1 + 1));
  sp24 = (D_hd_code_802FC51C / 20.0);

  for (sp34 = D_hd_code_802FC51C; sp34 < (arg1 + D_hd_code_802FC51C); sp34++) {
    sp28 = sinf(sp24);
    func_hd_code_802C1F30(arg0, sp30++, 0, -sp28 * arg2, 0);
    sp24 += sp2C;
  }
  D_hd_code_802FC51C++;
}

void func_hd_code_8027DA10(s32 arg0, s32 arg1, s32 arg2) {
  f32 sp64;
  f32 sp60;
  f32 sp5C;
  s32 sp58;
  s16* sp54;
  s32 pad40[5];
  s32 sp30[4];
  s32 sp20[4];

  sp54 = func_hd_code_802C1EE0(arg0);
  for(sp58 = 0; sp58 < 4; sp58++) {
    sp30[sp58] = sp54[sp58 * 2] << 5;
    sp20[sp58] = sp54[sp58 * 2 + 1] << 5;
  }

  sp64 = func_hd_code_8027DB5C(sp30, sp20, arg2);
  sp5C = (f32) (3.14159 / (f64) (arg1 + 1));

  for(sp58 = 0; sp58 < arg1; sp58++) {
    sp60 = sinf((f32) (sp58 + 1) * sp5C);
    func_hd_code_802C1F30(arg0, sp58 + 1, 0, (s32) (-sp60 * sp64), 0);
  }
}

f32 func_hd_code_8027DB5C(s32* arg0, s32* arg1, s32 arg2) {
  s32 sp2C;
  f32 sp28;
  f32 sp24;
  f32 sp20;
  f32 sp1C;
  s32 sp18;

  sp2C = 0;
  sp28 = 0.0f;
  while (&D_hd_code_80364460[sp2C] != D_hd_code_803649D0) {
    sp18 = D_hd_code_80364460[sp2C].unk5C;
    if ((sp18 != 0xFE) && ((sp18 != 0) || (D_hd_code_803649E8 == 0))) {
      if (func_hd_code_8027E164(D_hd_code_80364460[sp2C].unk64, D_hd_code_80364460[sp2C].unk6C, arg0, arg1) != 0) {
        if (D_hd_code_80364460[sp2C].unk70 != 0) {
          sp1C = func_hd_code_8027DD88(D_hd_code_80364460[sp2C].unk64, D_hd_code_80364460[sp2C].unk6C, arg0, arg1);
          if (sp1C <= 0.5) {
            sp1C = (f32) (sp1C * 2.0);
          } else {
            sp1C = (f32) ((1.0 - (f64) sp1C) * 2.0);
          }
          sp20 = func_hd_code_8027E228(D_hd_code_80364460[sp2C].unk5C);
          sp24 = sp1C * sp20;
          if (sp28 < sp24) {
            sp28 = sp24;
          }
        }
      }
    }
    sp2C += 1;
  }
  return (f32) arg2 * sp28;
}

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_8027DD88.s")

s32 func_hd_code_8027E164(s32 arg0, s32 arg1, struct S_802AC4C4* arg2, struct S_802AC4C4* arg3) {
  if (func_hd_code_802AC4C4(arg0, arg1, arg2->unk0, arg3->unk0, arg2->unk4, arg3->unk4, arg2->unk8, arg3->unk8) != 0) {
    return 1;
  }
  if (func_hd_code_802AC4C4(arg0, arg1, arg2->unk0, arg3->unk0, arg2->unk8, arg3->unk8, arg2->unkC, arg3->unkC) != 0) {
    return 1;
  }
  return 0;
}

f32 func_hd_code_8027E228(u8 arg0) {
  switch (arg0) {
    case 0x0:
      return 0.3f;
    case 0x1:
      return 0.8f;
    case 0x5:
      return 0.8f;
    case 0x4:
      return 0.8f;
    case 0x2:
      return 0.8f;
    case 0x10:
      return 0.4f;
    case 0x3:
      return 0.8f;
    case 0x8:
      return 0.6f;
    case 0xA:
      return 0.6f;
    case 0xD:
      return 0.8f;
    case 0xE:
      return 0.6f;
    case 0xF:
      return 0.6f;

    case 0x9:
      return 0.0f;
    case 0xFF:
      return 0.8f;
    default:
      rmonPrintf("DIGGER WEIGHT NOT SET\n");
  }
}

void func_hd_code_8027E344(s32 arg0) {
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    u8 sp1F;

    sp2C = 0;
    sp28 = 0;
    sp24 = 0;
    sp1F = 0;
    D_8036DCD6 = 0;
    while ((sp1F == 0) && ((s32) D_8036DCD6 < 3)) {
        if (D_hd_code_802FC3F0[D_8036DCD6].unk0 == arg0) {
            sp1F = 1;
        } else {
            D_8036DCD6 += 1;
        }
    }

    if (sp1F == 0) {
        D_8036DCD4 = 0;
        return;
    }
    D_8036DCD4 = 1;
    D_8036DCA0[0] = (Vtx*)D_hd_code_80358070;
    D_hd_code_80358070 += ((D_hd_code_802FC3F0[D_8036DCD6].unk1 + 1) * (D_hd_code_802FC3F0[D_8036DCD6].unk2 + 1)) * sizeof(Vtx);
    D_8036DCA0[1] = (Vtx*) D_hd_code_80358070;
    D_hd_code_80358070 += ((D_hd_code_802FC3F0[D_8036DCD6].unk1 + 1) * (D_hd_code_802FC3F0[D_8036DCD6].unk2 + 1)) * sizeof(Vtx);
    D_8036DCA8[0] = (Vtx*)D_hd_code_80358070;
    D_hd_code_80358070 += 0x12C0;
    D_8036DCA8[1] = (Vtx*)D_hd_code_80358070;
    D_hd_code_80358070 += 0x12C0;
    sp20 = D_hd_code_802FC3F0[D_8036DCD6].unk1 * D_hd_code_802FC3F0[D_8036DCD6].unk2 * 2 * 8;

    sp20 += ((((s32) D_hd_code_802FC3F0[D_8036DCD6].unk1 / 8) + 1) * D_hd_code_802FC3F0[D_8036DCD6].unk2 * 8);
    sp20 += 0x1C20;
    D_8036DCC8[0] = (Gfx*)D_hd_code_80358070;
    D_hd_code_80358070 = &D_hd_code_80358070[sp20];
    D_8036DCC8[1] = (Gfx*)D_hd_code_80358070;
    D_hd_code_80358070 = &D_hd_code_80358070[sp20];
    D_8036DCD7 = D_hd_code_802FC3F0[D_8036DCD6].unk31;
    D_8036DCD5 = D_hd_code_802FC3F0[D_8036DCD6].unk24;
    if (D_8036DCD5 != 0) {
        D_8036DCB8[0] = (Vtx*)D_hd_code_80358070;
        func_hd_code_802A0CC8(D_hd_code_802FC3F0[D_8036DCD6].unk26, 0); // unk26?
    } else {
        for(sp34 = 0; sp34 < 3; sp34++) {
            D_8036DCB8[sp34] = (Vtx*)D_hd_code_80358070;
            func_hd_code_802A0CC8(D_hd_code_802FC3F0[2].unkC[sp34+20], 0); // Or other offset?
        }
    }
    D_8036DCD0 = 0;
    D_8036DCD2 = 0;

    sp44 = (s32) (D_hd_code_802FC3F0[D_8036DCD6].unk8 - D_hd_code_802FC3F0[D_8036DCD6].unk4) / (s32) D_hd_code_802FC3F0[D_8036DCD6].unk1;
    sp40 = (s32) (D_hd_code_802FC3F0[D_8036DCD6].unkA - D_hd_code_802FC3F0[D_8036DCD6].unk6) / (s32) D_hd_code_802FC3F0[D_8036DCD6].unk2;
    sp3C = (s32) D_hd_code_802FC3F0[D_8036DCD6].unk4;
    sp38 = (s32) D_hd_code_802FC3F0[D_8036DCD6].unk6;

    for(sp34 = 0; sp34 <= D_hd_code_802FC3F0[D_8036DCD6].unk2; sp34++) {
        sp24 = 0;
        for(sp30 = 0; sp30 <= D_hd_code_802FC3F0[D_8036DCD6].unk1; sp30++) {
            D_8036DCA0[0][sp2C].v.ob[0] = (s16) sp3C;
            D_8036DCA0[0][sp2C].v.ob[2] = (s16) sp38;
            D_8036DCA0[1][sp2C].v.ob[0] = (s16) sp3C;
            D_8036DCA0[1][sp2C].v.ob[2] = (s16) sp38;

            D_8036DCA0[0][sp2C].v.tc[0] = (s16) (sp28 << 5);
            D_8036DCA0[0][sp2C].v.tc[1] = (s16) (sp24 << 5);
            D_8036DCA0[1][sp2C].v.tc[0] = (s16) (sp28 << 5);
            D_8036DCA0[1][sp2C].v.tc[1] = (s16) (sp24 << 5);
            sp24 ^= 0x1F;
            sp2C += 1;
            sp3C += sp44;
        }
        sp28 ^= 0x1F;
        sp3C = D_hd_code_802FC3F0[D_8036DCD6].unk4;
        sp38 += sp40;
    }
    D_8036DCB0 = 0;
}

void func_hd_code_8027E9B8(u8 arg0) {
  s32 sp34;
  s32 sp30;
  s32 sp2C;
  s32 sp28;

  if (((u8) D_8036DCD4 != 0) && (D_hd_code_802E8BD0 == 0)) {
    D_8036DCB0 += 1;
    D_8036DCD2 += 0xF;
    if (D_8036DCD2 >= 0xFF) {
      D_8036DCD2 = 0;
      D_8036DCD0++;
      if (D_8036DCD0 >= 3) {
        D_8036DCD0 = 0;
      }
    }
  }
  if ((u8) D_8036DCD4 != 0) {
    sp2C = (s32) (D_hd_code_802FC3F0[D_8036DCD6].unk8 - D_hd_code_802FC3F0[D_8036DCD6].unk4) / (s32) D_hd_code_802FC3F0[D_8036DCD6].unk1;
    for(sp34 = 0; sp34 <= D_hd_code_802FC3F0[D_8036DCD6].unk1; sp34++) {
      for(sp30 = 0; sp30 <= D_hd_code_802FC3F0[D_8036DCD6].unk2; sp30++) {
        D_8036DCA0[arg0][sp34 + (sp30 * (D_hd_code_802FC3F0[D_8036DCD6].unk2 + 1))].v.ob[1] = D_hd_code_802FC3F0[D_8036DCD6].unkC[1] *
            sinf((((sp34 + 1) * sp2C) / D_hd_code_802FC3F0[D_8036DCD6].unk1C) + (D_8036DCB0 / D_hd_code_802FC3F0[D_8036DCD6].unk14)) + D_hd_code_802FC3F0[D_8036DCD6].unkC[0];
      }
    }

    sp28 = (s32) (D_hd_code_802FC3F0[D_8036DCD6].unkA - D_hd_code_802FC3F0[D_8036DCD6].unk6) / (s32) D_hd_code_802FC3F0[D_8036DCD6].unk2;
    for(sp34 = 0; sp34 <= D_hd_code_802FC3F0[D_8036DCD6].unk2; sp34++) {
      for(sp30 = 0; sp30 <= D_hd_code_802FC3F0[D_8036DCD6].unk1; sp30++) {
        D_8036DCA0[arg0][sp30 + (sp34 * (D_hd_code_802FC3F0[D_8036DCD6].unk2 + 1))].v.ob[1] +=
            D_hd_code_802FC3F0[D_8036DCD6].unkC[2] *
              sinf((((sp34 + 1) * sp28) / D_hd_code_802FC3F0[D_8036DCD6].unk20) + (D_8036DCB0 / D_hd_code_802FC3F0[D_8036DCD6].unk18));
      }
    }
  }
}

u8 func_hd_code_8027EED8(s16 arg0, s16 arg1, s16* arg2) {
  f32 pad2C;
  f32 sp28;
  f32 sp24;

  if (!D_8036DCD4) {
    return 0;
  }

  if (arg0 < D_hd_code_802FC3F0[D_8036DCD6].unk4
   || arg0 > D_hd_code_802FC3F0[D_8036DCD6].unk8
   || arg1 < D_hd_code_802FC3F0[D_8036DCD6].unk6
   || arg1 > D_hd_code_802FC3F0[D_8036DCD6].unkA) {
    *arg2 = D_hd_code_802FC3F0[D_8036DCD6].unkC[0];
    return 0;
   }

  sp28 = (D_hd_code_802FC3F0[D_8036DCD6].unk8 - D_hd_code_802FC3F0[D_8036DCD6].unk4) / (f32) D_hd_code_802FC3F0[D_8036DCD6].unk1;
  sp24 = (arg0 - D_hd_code_802FC3F0[D_8036DCD6].unk4) / sp28;
  *arg2 = D_hd_code_802FC3F0[D_8036DCD6].unkC[1] * sinf(((sp24 + 1.0f) * sp28) / D_hd_code_802FC3F0[D_8036DCD6].unk1C + D_8036DCB0 / D_hd_code_802FC3F0[D_8036DCD6].unk14) + D_hd_code_802FC3F0[D_8036DCD6].unkC[0];

  sp28 = (f32) (D_hd_code_802FC3F0[D_8036DCD6].unkA - D_hd_code_802FC3F0[D_8036DCD6].unk6) / (f32) D_hd_code_802FC3F0[D_8036DCD6].unk2;
  sp24 = (f32) (arg1 - D_hd_code_802FC3F0[D_8036DCD6].unk6) / sp28;
  *arg2 += D_hd_code_802FC3F0[D_8036DCD6].unkC[2] * sinf(((sp24 + 1.0f) * sp28) / D_hd_code_802FC3F0[D_8036DCD6].unk20 + D_8036DCB0 / D_hd_code_802FC3F0[D_8036DCD6].unk18);
  return 1;
}

void func_hd_code_8027F1F8(Gfx** gfx, u8 arg1, s32 arg2) {
    Gfx* entry;
    s32 sp130;
    s32 sp12C;
    s32 pad128;
    s32 sp124;
    s32 sp120;
    s32 sp11C;
    s32 sp118;
    u8 sp117;
    s32 sp110;
    s32 sp10C;
    u8 sp10B;
    s16 sp108;
    s16 sp106;
    s16 sp104;
    s16 sp102;
    s16 sp100;
    s16 spFE;
    Gfx* entry2;
    Vtx* spF4;
    s32 spF0;

    entry = *gfx;
    sp117 = 0;
    entry2 = D_8036DCC8[arg1];
    spF4 = D_8036DCA8[arg1];
    if (((u8) D_8036DCD4 == 0) || ((u8) arg2 != D_8036DCD7)) {
        return;
    }
    gDPPipeSync(entry++);
    if (D_8036DCD5 != 0) {
        gDPSetCycleType(entry++, G_CYC_1CYCLE);
        gDPSetRenderMode(entry++, G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2);
        gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
        gSPSetGeometryMode(entry++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH);
        gSPTexture(entry++, 1984, 1984, 0, G_TX_RENDERTILE, G_ON);
        gDPSetCombineLERP(entry++, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE);
        gDPSetPrimColor(entry++, 0, 0, 0x00, 0x00, 0x00, 0xAA);
        gDPLoadTextureBlock(entry++, (u32) (*D_8036DCB8) + 0x80000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    } else {
        gDPSetCycleType(entry++, G_CYC_2CYCLE);
        gDPSetRenderMode(entry++, D_hd_code_802FC3F0[D_8036DCD6].unk28, D_hd_code_802FC3F0[D_8036DCD6].unk2C);
        gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
        if (D_hd_code_802FC3F0[D_8036DCD6].unk30 != 0) {
            gSPSetGeometryMode(entry++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
        } else {
            gSPSetGeometryMode(entry++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
        }
        gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);
        gDPSetCombineLERP(entry++, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, 0, 0, 0, 0, 0, 0, 0, COMBINED, 0, 0, 0, PRIMITIVE);
        gDPSetTextureLOD(entry++, G_TL_TILE);

        if (D_8036DCD0 == 2) {
            sp10B = 0;
        } else {
            sp10B = D_8036DCD0 + 1;
        }
        gDPSetTextureImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, (u32) (D_8036DCB8[D_8036DCD0]) + 0x80000000);
        gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
        gDPLoadSync(entry++);
        gDPLoadBlock(entry++, G_TX_LOADTILE, 0, 0, 1023, 256);
        gDPSetTextureImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, (u32) (D_8036DCB8[sp10B]) + 0x80000000);
        gDPTileSync(entry++);
        gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0x0100, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
        gDPLoadSync(entry++);
        gDPLoadBlock(entry++, G_TX_LOADTILE, 0, 0, 1023, 256);
        gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD);
        gDPSetTileSize(entry++, G_TX_RENDERTILE, qu102(0.5), qu102(0.5), qu102(31.5), qu102(31.5));
        gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0x0100, 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOLOD);
        gDPSetTileSize(entry++, 1, qu102(0.5), qu102(0.5), qu102(31.5), qu102(31.5));
        gDPSetPrimColor(entry++, 0, D_8036DCD2, 0x00, 0x00, 0x00, 0xAA);
    }
    sp124 = (D_hd_code_802FC3F0[D_8036DCD6].unk1 + 1) * (D_hd_code_802FC3F0[D_8036DCD6].unk2 + 1);
    sp130 = 0;
    sp12C = D_hd_code_802FC3F0[D_8036DCD6].unk1 + 1;
    sp11C = 0;
    spF0 = 0;
    while (sp117 == 0) {
        if ((D_hd_code_802FC3F0[D_8036DCD6].unk1 - sp11C) + 1 >= 9) {
            sp120 = 8;
        } else {
            sp120 = (D_hd_code_802FC3F0[D_8036DCD6].unk1 - sp11C) + 1;
        }
        if (spF0 == 0) {
            gSPDisplayList(entry++, osVirtualToPhysical(entry2));

            gSPVertex(entry2++, osVirtualToPhysical(spF4), 8, 0);
            gSPCullDisplayList(entry2++, 0, 7);

            sp108 = 0x7FFF,
            sp104 = 0x7FFF,
            sp100 = 0x7FFF;

            sp106 = -0x8000,
            sp102 = -0x8000,
            spFE = -0x8000;
        }

        gSPVertex(entry2++, osVirtualToPhysical(&D_8036DCA0[arg1][sp130]), sp120, 0);
        gSPVertex(entry2++, osVirtualToPhysical(&D_8036DCA0[arg1][sp12C]), sp120, 8);

        for(sp110 = 0; (sp110 < sp120); sp110++) {
            if (D_8036DCA0[arg1][sp130 + sp110].v.ob[0] < sp108) {
                sp108 = D_8036DCA0[arg1][sp130 + sp110].v.ob[0];
            }
            if (D_8036DCA0[arg1][sp130 + sp110].v.ob[1] < sp104) {
                sp104 = D_8036DCA0[arg1][sp130 + sp110].v.ob[1];
            }
            if (D_8036DCA0[arg1][sp130 + sp110].v.ob[2] < sp100) {
                sp100 = D_8036DCA0[arg1][sp130 + sp110].v.ob[2];
            }

            if (D_8036DCA0[arg1][sp130 + sp110].v.ob[0] > sp106) {
                sp106 = D_8036DCA0[arg1][sp130 + sp110].v.ob[0];
            }
            if (D_8036DCA0[arg1][sp130 + sp110].v.ob[1] > sp102) {
                sp102 = D_8036DCA0[arg1][sp130 + sp110].v.ob[1];
            }
            if (D_8036DCA0[arg1][sp130 + sp110].v.ob[2] > spFE) {
                spFE = D_8036DCA0[arg1][sp130 + sp110].v.ob[2];
            }
        }

        for(sp110 = 0; sp110 < sp120; sp110++) {
            if (D_8036DCA0[arg1][sp12C + sp110].v.ob[0] < sp108) {
                sp108 = D_8036DCA0[arg1][sp12C + sp110].v.ob[0];
            }
            if (D_8036DCA0[arg1][sp12C + sp110].v.ob[1] < sp104) {
                sp104 = D_8036DCA0[arg1][sp12C + sp110].v.ob[1];
            }
            if (D_8036DCA0[arg1][sp12C + sp110].v.ob[2] < sp100) {
                sp100 = D_8036DCA0[arg1][sp12C + sp110].v.ob[2];
            }
            if (D_8036DCA0[arg1][sp12C + sp110].v.ob[0] > sp106) {
                sp106 = D_8036DCA0[arg1][sp12C + sp110].v.ob[0];
            }
            if (D_8036DCA0[arg1][sp12C + sp110].v.ob[1] > sp102) {
                sp102 = D_8036DCA0[arg1][sp12C + sp110].v.ob[1];
            }
            if (D_8036DCA0[arg1][sp12C + sp110].v.ob[2] > spFE) {
                spFE = D_8036DCA0[arg1][sp12C + sp110].v.ob[2];
            }
        }


        sp118 = 0;
        for(sp110 = 0; sp110 < sp120 - 1; sp110++) {
            gSP1Triangle(entry2++, sp118 + 1, sp118, sp118 + 8, 0);

            if (D_8036DCD5 != 0) {
                func_hd_code_802802D4(D_8036DCA0[arg1], sp130 + sp118, sp130 + sp118 + 1, sp12C + sp118);
            }
            gSP1Triangle(entry2++, sp118 + 8, sp118 + 9, sp118 + 1, 0);

            if (D_8036DCD5 != 0) {
                func_hd_code_802802D4(D_8036DCA0[arg1], sp12C + sp118, sp12C + sp118 + 1, sp130 + sp118 + 1);
            }
            sp118 += 1;
        }

        sp10C = sp120 - 1;
        sp11C += sp10C;

        sp130 += sp10C, sp12C += sp10C;
        if (sp11C == D_hd_code_802FC3F0[D_8036DCD6].unk1) {
            sp11C = 0;
            sp130++, sp12C++;

        }
        spF0 += (sp120 * 2);
        if (spF0 >= 0x20) {
            gSPEndDisplayList(entry2++);
            func_hd_code_8028072C(spF4, sp108, sp104, sp100, (s32) sp106, (s32) sp102, (s32) spFE);
            spF0 = 0;
            spF4 += 8;
        }
        if (sp12C == sp124) {
            sp117 = 1;
        }
    }

    if (spF0 != 0) {
        gSPEndDisplayList(entry2++);
        func_hd_code_8028072C(spF4, sp108, sp104, sp100, (s32) sp106, (s32) sp102, (s32) spFE);
        spF4 += 8;
    }
    gDPPipeSync(entry++);
    gDPSetTextureLOD(entry++, G_TL_LOD);
    gDPPipeSync(entry++);

    *gfx = entry;
}

void func_hd_code_802802D4(Vtx* arg0, s32 arg1, s32 arg2, s32 arg3) {
  f32 sp44[3];
  f32 sp38[3];
  f32 pad2C[3];
  f32 sp28;
  f32 sp24;
  f32 sp20;
  f32 sp1C;
  f32 sp18;


  sp44[0] = arg0[arg3].v.ob[0] - arg0[arg1].v.ob[0];
  sp44[1] = arg0[arg3].v.ob[1] - arg0[arg1].v.ob[1];
  sp44[2] = arg0[arg3].v.ob[2] - arg0[arg1].v.ob[2];

  sp38[0] = arg0[arg2].v.ob[0] - arg0[arg1].v.ob[0];
  sp38[1] = arg0[arg2].v.ob[1] - arg0[arg1].v.ob[1];
  sp38[2] = arg0[arg2].v.ob[2] - arg0[arg1].v.ob[2];

  sp24 = (sp44[1] * sp38[2]) - (sp44[2] * sp38[1]);
  sp20 = (sp44[2] * sp38[0]) - (sp44[0] * sp38[2]);
  sp1C = (sp44[0] * sp38[1]) - (sp44[1] * sp38[0]);

  sp18 = sqrtf((sp24 * sp24) + (sp20 * sp20) + (sp1C * sp1C));
  if (sp18 < 1.0) {
    sp18 = 1.0f;
  }
  sp28 = 120.0 / sp18;
  sp24 *= sp28;
  sp20 *= sp28;
  sp1C *= sp28;
  arg0[arg1].v.cn[0] = (s8)sp24;
  arg0[arg1].v.cn[1] = (s8)sp20;
  arg0[arg1].v.cn[2] = (s8)sp1C;
  arg0[arg1].v.cn[3] = 0;
  arg0[arg2].v.cn[0] = (s8)sp24;
  arg0[arg2].v.cn[1] = (s8)sp20;
  arg0[arg2].v.cn[2] = (s8)sp1C;
  arg0[arg2].v.cn[3] = 0;
  arg0[arg3].v.cn[0] = (s8)sp24;
  arg0[arg3].v.cn[1] = (s8)sp20;
  arg0[arg3].v.cn[2] = (s8)sp1C;
  arg0[arg3].v.cn[3] = 0;
}

void func_hd_code_8028072C(Vtx* arg0, s16 x1, s16 y1, s16 z1, s16 x2, s16 y2, s16 z2) {
  arg0[0].v.ob[0] = x1;
  arg0[0].v.ob[1] = y1;
  arg0[0].v.ob[2] = z1;

  arg0[1].v.ob[0] = x1;
  arg0[1].v.ob[1] = y2;
  arg0[1].v.ob[2] = z1;

  arg0[2].v.ob[0] = x2;
  arg0[2].v.ob[1] = y1;
  arg0[2].v.ob[2] = z1;

  arg0[3].v.ob[0] = x2;
  arg0[3].v.ob[1] = y2;
  arg0[3].v.ob[2] = z1;

  arg0[4].v.ob[0] = x1;
  arg0[4].v.ob[1] = y1;
  arg0[4].v.ob[2] = z2;

  arg0[5].v.ob[0] = x1;
  arg0[5].v.ob[1] = y2;
  arg0[5].v.ob[2] = z2;

  arg0[6].v.ob[0] = x2;
  arg0[6].v.ob[1] = y1;
  arg0[6].v.ob[2] = z2;

  arg0[7].v.ob[0] = x2;
  arg0[7].v.ob[1] = y2;
  arg0[7].v.ob[2] = z2;
}

void func_hd_code_802807D8(u8 arg0) {
    s32 sp34;
    s32 sp30;
    s16 sp2E;
    s16 sp2C;
    s16 sp2A;
    s16 sp28;
    s16 sp26;
    s32 sp20;
    u8 sp1F;

    D_8036E374 = 0;
    sp20 = 0;
    sp1F = 0;
    D_8036E370 = 0;
    while((sp1F == 0) && ((s32) D_8036E370 < 4)) {
        if (D_hd_code_802FC494[D_8036E370].unk0 == (u8) arg0) {
            sp1F = 1;
        } else {
            D_8036E370 += 1;
        }
    }

    if (sp1F != 0) {
        D_8036E374 = (s32) D_hd_code_802FC494[D_8036E370].unkE;
        D_8036E378 = D_hd_code_80358070;
        func_hd_code_802A0CC8(D_hd_code_802FC494[D_8036E370].unk14, 0);
        for(sp34 = 0; sp34 < D_8036E374; sp34++) {
            sp2E = func_hd_code_8026A828(D_hd_code_802FC494[D_8036E370].unk2, D_hd_code_802FC494[D_8036E370].unk6);
            sp2C = func_hd_code_8026A828(D_hd_code_802FC494[D_8036E370].unkA, D_hd_code_802FC494[D_8036E370].unkC);
            sp2A = func_hd_code_8026A828(D_hd_code_802FC494[D_8036E370].unk4, D_hd_code_802FC494[D_8036E370].unk8);
            sp28 = func_hd_code_8026A828(D_hd_code_802FC494[D_8036E370].unk18, D_hd_code_802FC494[D_8036E370].unk1A);
            sp26 = func_hd_code_8026A828(D_hd_code_802FC494[D_8036E370].unk1C, D_hd_code_802FC494[D_8036E370].unk1E);
            sp28 = sp28 >> 1,
            sp26 = sp26 >> 1;
            D_8036DCE0[sp34][3] = sp28;
            D_8036DCE0[sp34][4] = sp26;
            D_8036DCE0[sp34][1] = sp2E;
            D_8036DCE0[sp34][2] = sp2A;
            D_8036DCE0[sp34][0] = func_hd_code_8026A828(D_hd_code_802FC494[D_8036E370].unk10, D_hd_code_802FC494[D_8036E370].unk12);
            D_8036DCE0[sp34][5] = func_hd_code_8026A828(0, 0xFFF);
            for(sp30 = 0; sp30 < 2; sp30++) {
                D_8036DD70[sp30][sp34][0].v.ob[0] = sp2E - sp28;
                D_8036DD70[sp30][sp34][0].v.ob[1] = sp2C;
                D_8036DD70[sp30][sp34][0].v.ob[2] = sp2A - sp26;
                D_8036DD70[sp30][sp34][0].v.tc[0] = 0;
                D_8036DD70[sp30][sp34][0].v.tc[1] = 0;

                D_8036DD70[sp30][sp34][1].v.ob[0] = sp2E + sp28;
                D_8036DD70[sp30][sp34][1].v.ob[1] = sp2C;
                D_8036DD70[sp30][sp34][1].v.ob[2] = sp2A - sp26;
                D_8036DD70[sp30][sp34][1].v.tc[0] = D_hd_code_802FC494[D_8036E370].unk16 << 5;
                D_8036DD70[sp30][sp34][1].v.tc[1] = 0;

                D_8036DD70[sp30][sp34][2].v.ob[0] = sp2E + sp28;
                D_8036DD70[sp30][sp34][2].v.ob[1] = sp2C;
                D_8036DD70[sp30][sp34][2].v.ob[2] = sp2A + sp26;
                D_8036DD70[sp30][sp34][2].v.tc[0] = D_hd_code_802FC494[D_8036E370].unk16 << 5;
                D_8036DD70[sp30][sp34][2].v.tc[1] = D_hd_code_802FC494[D_8036E370].unk17 << 5;

                D_8036DD70[sp30][sp34][3].v.ob[0] = sp2E - sp28;
                D_8036DD70[sp30][sp34][3].v.ob[1] = sp2C;
                D_8036DD70[sp30][sp34][3].v.ob[2] = sp2A + sp26;
                D_8036DD70[sp30][sp34][3].v.tc[0] = 0;
                D_8036DD70[sp30][sp34][3].v.tc[1] = D_hd_code_802FC494[D_8036E370].unk17 << 5;
            }
        }
    }
}


#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_80280F34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_80281A70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_80281CE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_80281E44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_802821D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_80282224.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_80282728.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/39050/func_hd_code_8028273C.s")
