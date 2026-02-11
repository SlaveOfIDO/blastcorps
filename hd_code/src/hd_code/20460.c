#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"

struct S_80367D60 {
  s16 unk0;
  s16 unk2;
  s16 unk4;
  s16 unk6;
  s16 unk8;
  s16 unkA;
  s16 unkC;
  s16 unkE;
  s16 unk10;
  u8 unk12;
  u8 unk13;
  u8 unk14;
  u8 unk15;
  s16 unk16;
  s16 unk18;
  u8 unk1A;
  u8 unk1B;
  u8 unk1C;
  u8 pad1D[0x20-0x1D];
  f32 unk20;
};

s32 func_hd_code_80265A0C(s32);                     /* extern */
void func_hd_code_80265B7C(s32);                       /* extern */
s32 func_hd_code_80267614(struct S_80367D60*);                   /* extern */
void func_hd_code_8026A5CC(void*, void*, u32);              /* extern */
s32 func_hd_code_8026A8E0(s16, s16);                /* extern */
void sndCreatePostEvent(ALSoundState *state, s16 eventType, s32 arg2);
s16 func_hd_code_802D9830(s32);                     /* extern */
s16 func_hd_code_802D98A0(s32);                     /* extern */
void func_hd_code_8026513C();                          /* extern */
void func_hd_code_80265428();                          /* extern */
void func_hd_code_80265E48();                          /* extern */

extern struct S_80367D60 D_80367D60[0x14];
extern struct S_80367D60 D_80367D60[0x14];
extern s32 D_803EF310;
extern s32 D_803EF318;
extern u8 D_803EF32E;
extern s16 D_80368034;
extern s16 D_80368036;
extern s8 D_803EF32C;
extern s32 D_80368030;
extern s32 D_80368038;
extern s32 D_8036803C;
extern s32 D_803EF308;
extern s32 D_803EF30C;
extern u8 D_803EF32D;
extern u16 D_803C30A8[];
extern s32 D_80368040;
extern u32 D_8036B968;
extern s32 D_80368044;
extern s32 D_80368048;

// Data
Vtx D_hd_code_802E9FB0[4] = {
  { 6, 20, 6, 0, 0, 992, 0xFF, 0xFF, 0xFF, 0xFF },
  {-6, 20, -6, 0, 608, 992, 0xFF, 0xFF, 0xFF, 0xFF  },
  {-6, 0, -6, 0, 0x0260, 0,  0xFF, 0xFF, 0xFF, 0xFF  },
{ 6, 0, 6, 0, 0, 0,   0xFF, 0xFF, 0xFF, 0xFF }
};
#include "20460_textures.h"


void func_hd_code_80264C20(s32 arg0) {
  s32 sp1C;

  for(sp1C = 0; sp1C < 0x14; sp1C++) {
    D_80367D60[sp1C].unk15 = 0;
  }

  D_8036B968 = osGetCount();
  D_80368038 = 0x05F5E0FF;
  if (arg0 != 0) {
    D_8036EA79 = (u8) D_80368040;
    return;
  }
  D_8036EA79 = 0;
  return;
}

void func_hd_code_80264CB4(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, s32 arg5) {
  s32 pad24;
  s32 sp20;
  s32 sp1C;
  u8 sp1B;
  s16 sp18;


  sp1C = 0;
  sp20 = 0;
  D_8036EA79 += arg5;
  if ((arg5 != 0) && (D_hd_code_802E8BD0 == 0)) {
    func_hd_code_8026AD30(0x48U);
  }
  if (arg3 >= 0xC9) {
    arg3 = 0xC8;
  }
  while (sp20 < arg5 && sp1C < 0x14) {
    if (sp20 == 2) {
      sndPlaySfx((struct ALBankAlt_s* ) D_80367738, 0x24, NULL);
    }
    sp1B = 0;
    while(sp1C < 0x14 && sp1B == 0) {
      if (D_80367D60[sp1C].unk15 == 0) {
        sp1B = 1;
      } else {
        sp1C += 1;
      }
    }
    if (sp1B != 0) {
      D_80367D60[sp1C].unk0 = arg0;
      D_80367D60[sp1C].unk4 = arg2;
      D_80367D60[sp1C].unk2 = arg1;
      sp18 = arg3 / 5; // perhaps no sp
      D_80367D60[sp1C].unkA = (arg0 - arg3) + func_hd_code_8026A8E0(-sp18, sp18);
      D_80367D60[sp1C].unkC =   (arg2 + arg3) + func_hd_code_8026A8E0(-sp18, sp18);
      D_80367D60[sp1C].unk10 = (arg3 * 3) / 2;
      D_80367D60[sp1C].unkE = arg3;

      D_80367D60[sp1C].unk6 =  (D_80367D60[sp1C].unkA + func_hd_code_8026A8E0(-arg3, arg3));
      D_80367D60[sp1C].unk8 =  (D_80367D60[sp1C].unkC + func_hd_code_8026A8E0(-arg3, arg3));
      D_80367D60[sp1C].unk13 = 0;
      D_80367D60[sp1C].unk14 = 0;
      D_80367D60[sp1C].unk16 = func_hd_code_8026A8E0(-0x1F4, 0x1F4);
      D_80367D60[sp1C].unk12 = arg4;
      D_80367D60[sp1C].unk1C = 0;
      D_80367D60[sp1C].unk15 = 5;
      D_80367D60[sp1C].unk18 = 0xFA0;
      D_80367D60[sp1C].unk20 = 1e8f;
      D_80367D60[sp1C].unk1B = 0;
    }
    sp1C++;
    sp20++;
  }
}

void func_hd_code_8026510C(void) {
  func_hd_code_80265428();
  func_hd_code_8026513C();
  func_hd_code_80265E48();
}

void func_hd_code_8026513C(void) {
  s16 sp2E;
  s16 sp2C;
  s16 sp2A;
  s16 sp28;
  f32 sp24;
  s16 sp22;
  s16 sp20;
  s32 sp1C;

  for(sp1C = 0; sp1C < 0x14; sp1C++) {
    if (D_80367D60[sp1C].unk15 == 5) {
      sp2E = D_80367D60[sp1C].unk6 - D_80367D60[sp1C].unk0;
      if (sp2E >= 0) {
        sp2A = sp2E;
      } else {
        sp2A = -sp2E;
      }
      sp2C = D_80367D60[sp1C].unk8 - D_80367D60[sp1C].unk4;
      if (sp2C >= 0) {
        sp28 = sp2C;
      } else {
        sp28 = -sp2C;
      }
      sp24 = func_hd_code_8026A610(D_80367D60[sp1C].unk6, D_80367D60[sp1C].unk8, D_80367D60[sp1C].unk0, D_80367D60[sp1C].unk4);
      if ((sp24 < 1.0) || D_80367D60[sp1C].unk20 < sp24) {
        D_80367D60[sp1C].unk15 = 1;
      } else {
        D_80367D60[sp1C].unk20 = sp24;
        sp22 = ((sp2A / sp24) * 5.0f);
        sp20 = ((sp28 / sp24) * 5.0f);
        if (sp2E >= 0) {
          D_80367D60[sp1C].unk0 += sp22;
        } else {
          D_80367D60[sp1C].unk0 -= sp22;
        }
        if (sp2C >= 0) {
          D_80367D60[sp1C].unk4 += sp20;
        } else {
          D_80367D60[sp1C].unk4 -= sp20;
        }
      }
    }
  }
}

void func_hd_code_80265428(void) {
    s32 sp34;
    s32 pad30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;

    for(sp34 = 0; sp34 < 0x14; sp34++) {
        if (((D_80367D60[sp34].unk15 == 1) || (D_80367D60[sp34].unk15 == 4) || (D_80367D60[sp34].unk15 == 2)) && (func_hd_code_80265A0C(sp34) != 0)) {
            func_hd_code_80265B7C(sp34);

            sp2C = D_80367D60[sp34].unk0 + D_80368034;
            sp28 = D_80367D60[sp34].unk4 + D_80368036;
            sp24 = D_80367D60[sp34].unk0 - D_80368034;
            sp20 = D_80367D60[sp34].unk4 - D_80368036;

            if (sp2C < (D_80367D60[sp34].unkA - D_80367D60[sp34].unkE)) {
                sp2C = D_80367D60[sp34].unkA - D_80367D60[sp34].unkE;
            }
            if (sp28 < D_80367D60[sp34].unkC - D_80367D60[sp34].unkE) {
                sp28 = D_80367D60[sp34].unkC - D_80367D60[sp34].unkE;
            }
            if (sp2C >= D_80367D60[sp34].unkA + D_80367D60[sp34].unkE) {
                sp2C = D_80367D60[sp34].unkA + D_80367D60[sp34].unkE - 1;
            }
            if (sp28 >= D_80367D60[sp34].unkC + D_80367D60[sp34].unkE) {
                sp28 = D_80367D60[sp34].unkC + D_80367D60[sp34].unkE - 1;
            }
            if (sp24 < D_80367D60[sp34].unkA - D_80367D60[sp34].unkE) {
                sp24 = D_80367D60[sp34].unkA - D_80367D60[sp34].unkE;
            }
            if (sp20 < D_80367D60[sp34].unkC - D_80367D60[sp34].unkE) {
                sp20 = D_80367D60[sp34].unkC - D_80367D60[sp34].unkE;
            }
            if (sp24 >= D_80367D60[sp34].unkA + D_80367D60[sp34].unkE) {
                sp24 = D_80367D60[sp34].unkA + D_80367D60[sp34].unkE - 1;
            }
            if (sp20 >= D_80367D60[sp34].unkC + D_80367D60[sp34].unkE) {
                sp20 = D_80367D60[sp34].unkC + D_80367D60[sp34].unkE - 1;
            }

            sp1C = func_hd_code_8026A610(D_hd_code_803643E0 >> 5, D_hd_code_803643E8 >> 5, sp2C, sp28);
            sp18 = func_hd_code_8026A610(D_hd_code_803643E0 >> 5, D_hd_code_803643E8 >> 5, sp24, sp20);

            if (D_80367D60[sp34].unk1B != 0) {
                if (D_80367D60[sp34].unk1A != 0) {
                    sp18 = 0;
                } else {
                    sp1C = 0;
                }
                D_80367D60[sp34].unk1B -= 1;
            }
            if (sp1C < sp18) {
                D_80367D60[sp34].unk0 = (s16) sp24;
                D_80367D60[sp34].unk4 = (s16) sp20;
                D_80367D60[sp34].unk18 += 0x800;

                if (D_80367D60[sp34].unk18 >= 0x1000) {
                    D_80367D60[sp34].unk18 = D_80367D60[sp34].unk18 - 0xFFF;
                }
                if (D_80367D60[sp34].unk1A != 0) {
                    D_80367D60[sp34].unk1B = 5;
                }

                D_80367D60[sp34].unk1A = 0;
            } else {
                D_80367D60[sp34].unk0 = (s16) sp2C;
                D_80367D60[sp34].unk4 = (s16) sp28;
                if (D_80367D60[sp34].unk1A == 0) {
                    D_80367D60[sp34].unk1B = 5;
                }
                D_80367D60[sp34].unk1A = 1;
            }
            if ((sp34 == 1) && D_80367D60[sp34].unk15 != 4) {
                sndPlaySfx((struct ALBankAlt_s* ) D_80367738, 0x24, NULL);
            }
            if (D_80367D60[sp34].unk15 == 2) {
                D_803EF32C = 6;
            }
            D_80367D60[sp34].unk15 = 4;
        } else {
            if (D_80367D60[sp34].unk15 == 4) {
                D_80367D60[sp34].unk15 = 1;
            }
        }
    }
}

s32 func_hd_code_80265A0C(s32 arg0) {
  s16 sp6;
  s16 sp4;
  s16 sp2;
  s16 sp0;

  sp2 = D_80367D60[arg0].unkA - D_80367D60[arg0].unk10;
  sp0 = D_80367D60[arg0].unkC - D_80367D60[arg0].unk10;

  sp6 = D_hd_code_803643E0 >> 5,
  sp4 = D_hd_code_803643E8 >> 5;

  if (((s16) sp6 < sp2) || ((s16) sp4 < sp0)) {
    return 0;
  }

  sp2 = D_80367D60[arg0].unkA + D_80367D60[arg0].unk10;
  sp0 = D_80367D60[arg0].unkC + D_80367D60[arg0].unk10;
  if ((sp6 >= sp2) || (sp4 >= sp0)) {
    return 0;
  }
  return 1;
}

void func_hd_code_80265B7C(s32 arg0) {
  s16 sp26;
  s16 sp24;
  s16 sp22;
  s16 sp20;
  s16 sp1E;
  s16 sp1C;
  s32 sp18;

  sp18 = (s16) D_hd_code_8036443C / 40;;
  if (sp18 < 0) {
    sp18 = -sp18;
  }
  if ((D_hd_code_8036443C != 0) && (sp18 == 0)) {
    sp18 = 2;
  }
  sp26 = D_80367D60[arg0].unk16 + D_hd_code_8036443E + 0x400;
  if (sp26 >= 0x1000) {
    sp26 -= 0xFFF;
  }
  D_80367D60[arg0].unk18 = sp26;
  sp24 = (s16) (sp26 % 1024);
  sp22 = func_hd_code_802D9830((s32) ((s16) sp24 * 0xFFFF) / 4095);
  sp20 = func_hd_code_802D98A0((s32) (sp24 * 0xFFFF) / 4095);
  if ((s32) D_80367D60[arg0].unk1C < sp18) {
    D_80367D60[arg0].unk1C++;
  }
  if (D_80367D60[arg0].unk1C > sp18) {
    D_80367D60[arg0].unk1C--;
  }
  sp1E = (s32) (D_80367D60[arg0].unk1C * sp22) >> 0xF;
  sp1C = (s32) (D_80367D60[arg0].unk1C * sp20) >> 0xF;
  if (sp26 < 0x400) {
    D_80368034 = (s16) sp1E;
    D_80368036 = (s16) sp1C;
  }
  if ((sp26 >= 0x400) && (sp26 < 0x800)) {
    D_80368034 = sp1C;
    D_80368036 = -sp1E;
  }
  if ((sp26 >= 0x800) && (sp26 < 0xC00)) {
    D_80368034 = -sp1E;
    D_80368036 = -sp1C;
  }
  if (sp26 >= 0xC00) {
    D_80368034 = -sp1C;
    D_80368036 = sp1E;
  }
}

void func_hd_code_80265E48(void) {
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    u8 sp2F;
    u8 sp2E;
    s32 sp28;

    sp40 = -1,
    sp3C = 0x05F5E0FF,
    sp38 = -1;

    sp34 = 0;
    sp2E = 0;

    if (D_803EF32D != 0) {
        sp44 = 0;
        sp2F = 0;
        while(!sp2F) {
            if (D_80367D60[sp44].unk15 == 2) {
                D_80367D60[sp44].unk15 = 3;
                D_80367D60[sp44].unk13 = 0;
                sp2F = 1;
            } else {
                sp44 += 1;
            }
        };
        D_803EF32D = 0;
        D_80368038 = 0x05F5E0FF;
    } else {
        D_80368038 -= 1;
        if (D_80368038 == 0) {
            D_803EF32C = 6;
            D_80367D60[D_8036803C].unk15 = 1;
            sp2E = 1;
        }
    }
    if ((u8) D_803EF32C == 0) {
        for(sp44 = 0; sp44 < 0x14; sp44++) {
            if (D_80367D60[sp44].unk15 == 3) {
                D_80367D60[sp44].unk15 = 0;
            }
        }

        for(sp44 = 0; sp44 < 0x14; sp44++) {
            if (D_80367D60[sp44].unk15 == 1) {
                sp30 = func_hd_code_8026A610(
                    D_803EF2EC,
                    D_803EF2F4,
                    D_80367D60[sp44].unk0 << 5,
                    D_80367D60[sp44].unk4 << 5);
                if (sp30 < sp3C) {
                    sp40 = sp44;
                    sp3C = sp30;
                }
                if (sp30 > sp34) {
                    sp38 = sp44;
                    sp34 = sp30;
                }
            }
        }
        if (sp40 == -1) {
            return;
        }

        sp44 = sp2E ? sp38 : sp40;

        D_803EF308 = D_80367D60[sp44].unk0 << 5;
        D_803EF30C = D_80367D60[sp44].unk4 << 5;
        D_80368030 = D_80367D60[sp44].unk2 << 5;
        D_80367D60[sp44].unk15 = 2;
        D_80368038 = 0x258;
        D_803EF32C = 1;

        D_8036803C = sp44;

        sp28 = MIN(0x7FFF, 0x88B8 - (func_hd_code_8026A610(D_hd_code_803643E0, D_hd_code_803643E8, D_803EF308, D_803EF30C) * 2));

        if (sp28 >= 0xFA1) {
            sndCreatePostEvent(sndPlaySfx((struct ALBankAlt_s* ) D_80367738, 0x25, NULL), 8, sp28);
        }

    }
}

void func_hd_code_802661EC(void) {
  D_803EF308 = D_803EF6DC;
  D_803EF30C = D_803EF6E4;
  D_80368044 = D_hd_code_803643E0;
  D_80368048 = D_hd_code_803643E8;
  D_803EF32C = 1;
  D_80368038 = 0x7D0;
}

void func_hd_code_80266248(Gfx** arg0, struct Model1* arg1) {
    Gfx* entry;
    s32 sp168;
    s32 sp164;
    s32 sp160;
    s32 sp15C;
    u8 sp15B;
    u8 sp15A;
    u8* sp154;
    u32 sp150;
    u8 sp14F;
    f32 sp10C[4][4];
    f32 spFC[4];
    f32 spEC[4];
    f32 spDC[4];
    s16 spDA;

    entry = *arg0;
    sp168 = 0;
    guAlignF(sp10C, D_hd_code_80364414 - 135.0, 0.0f, 1.0f, 0.0f);
    for(sp160 = 0; sp160 < 4; sp160++) {
        guMtxXFMF(
            sp10C,
            D_hd_code_802E9FB0[sp160].v.ob[0],
            D_hd_code_802E9FB0[sp160].v.ob[1],
            D_hd_code_802E9FB0[sp160].v.ob[2],
            &spFC[sp160], &spEC[sp160], &spDC[sp160]);
    }
    gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
    gSPSetGeometryMode(entry++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH);
    gDPPipeSync(entry++);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    gDPSetRenderMode(entry++, G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2);
    gDPSetCombineMode(entry++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);

    for(sp164 = 0; sp164 < 0x14; sp164++) {
        if ((func_hd_code_80267614(&D_80367D60[sp164]) != 0) && (((D_80367D60[sp164].unk15 == 1)) || (D_80367D60[sp164].unk15 == 2) || ((D_80367D60[sp164].unk15 == 4) && (D_80367D60[sp164].unk1C == 0)))) {
            D_80367D60[sp164].unk14++;
            if (D_80367D60[sp164].unk14 >= 6) {
                D_80367D60[sp164].unk13++;
                D_80367D60[sp164].unk14 = 0;
            }
            if (D_80367D60[sp164].unk13 >= 6) {
                D_80367D60[sp164].unk13 = 0U;
            }

            switch (D_80367D60[sp164].unk13) {
            case 0:
                sp154 = D_hd_code_802EA4F0;
                break;
            case 1:
                sp154 = D_hd_code_802EA9F0;
                break;
            case 2:
                sp154 = D_hd_code_802EAEF0;
                break;
            case 3:
                sp154 = D_hd_code_802EB3F0;
                break;
            case 4:
                sp154 = D_hd_code_802EB8F0;
                break;
            case 5:
                sp154 = D_hd_code_802EBDF0;
                break;
            }

            sp150 = osVirtualToPhysical(sp154);
            gDPPipeSync(entry++);
            gDPLoadTextureBlock(entry++, sp150, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

            func_hd_code_8026A5CC(&arg1->unk1900[sp168], &D_hd_code_802E9FB0, 0x40);
            for(sp15C = 0; sp15C < 4; sp15C++) {
                arg1->unk1900[sp168 + sp15C].v.ob[0] = spFC[sp15C] + D_80367D60[sp164].unk0;
                arg1->unk1900[sp168 + sp15C].v.ob[1] = spEC[sp15C] + D_80367D60[sp164].unk2;
                arg1->unk1900[sp168 + sp15C].v.ob[2] = spDC[sp15C] + D_80367D60[sp164].unk4;
            }

            gSPVertex(entry++, &D_2000000.unk1900[sp168], 4, 0);
            sp168 += 4;
            gSP1Triangle(entry++, 0, 1, 2, 0);
            gSP1Triangle(entry++, 0, 2, 3, 0);
        }
    }

    for(sp164 = 0; sp164 < 0x14; sp164++) {
        if ((((D_80367D60[sp164].unk15 == 4) && (D_80367D60[sp164].unk1C != 0)) || (D_80367D60[sp164].unk15 == 5)) && (func_hd_code_80267614(&D_80367D60[sp164]) != 0)) {
            D_80367D60[sp164].unk14 += D_80367D60[sp164].unk1C;
            if (D_80367D60[sp164].unk14 >= 0xB) {
                D_80367D60[sp164].unk13++;
                D_80367D60[sp164].unk14 = 0;
            }
            if (D_80367D60[sp164].unk13 >= 8) {
                D_80367D60[sp164].unk13 = 0U;
            }
            sp15A = D_80367D60[sp164].unk13;
            sp14F = 0;
            spDA = D_80367D60[sp164].unk18 - (((D_hd_code_80364414 - 135.0) / 360.0) * 4095.0);
            if (spDA < 0) {
                spDA = spDA + 0xFFF;
            }
            if (spDA >= 0xC00) {
                switch (sp15A) {
                case 0:
                    sp154 = D_hd_code_802EEAF0;
                    break;
                case 1:
                    sp154 = D_hd_code_802EEFF0;
                    break;
                case 2:
                    sp154 = D_hd_code_802EF4F0;
                    break;
                case 3:
                    sp154 = D_hd_code_802EF9F0;
                    break;
                case 4:
                    sp154 = D_hd_code_802EFEF0;
                    break;
                case 5:
                    sp154 = D_hd_code_802F03F0;
                    break;
                case 6:
                    sp154 = D_hd_code_802F08F0;
                    break;
                case 7:
                    sp154 = D_hd_code_802F0DF0;
                    break;
                }
            }
            if ((spDA >= 0x800) && (spDA < 0xC00)) {
                sp14F = 1;
                switch (sp15A) {
                case 0:
                    sp154 = D_hd_code_802F12F0;
                    break;
                case 1:
                    sp154 = D_hd_code_802F17F0;
                    break;
                case 2:
                    sp154 = D_hd_code_802F1CF0;
                    break;
                case 3:
                    sp154 = D_hd_code_802F21F0;
                    break;
                case 4:
                    sp154 = D_hd_code_802F26F0;
                    break;
                case 5:
                    sp154 = D_hd_code_802F2BF0;
                    break;
                case 6:
                    sp154 = D_hd_code_802F30F0;
                    break;
                case 7:
                    sp154 = D_hd_code_802F35F0;
                    break;
                }
            }
            if ((spDA >= 0x400) && (spDA < 0x800)) {
                switch (sp15A) {
                case 0:
                    sp154 = D_hd_code_802EC2F0;
                    break;
                case 1:
                    sp154 = D_hd_code_802EC7F0;
                    break;
                case 2:
                    sp154 = D_hd_code_802ECCF0;
                    break;
                case 3:
                    sp154 = D_hd_code_802ED1F0;
                    break;
                case 4:
                    sp154 = D_hd_code_802ED6F0;
                    break;
                case 5:
                    sp154 = D_hd_code_802EDBF0;
                    break;
                case 6:
                    sp154 = D_hd_code_802EE0F0;
                    break;
                case 7:
                    sp154 = D_hd_code_802EE5F0;
                    break;
                }
            }
            if (spDA < 0x400) {
                switch (sp15A) {
                case 0:
                    sp154 = D_hd_code_802F12F0;
                    break;
                case 1:
                    sp154 = D_hd_code_802F17F0;
                    break;
                case 2:
                    sp154 = D_hd_code_802F1CF0;
                    break;
                case 3:
                    sp154 = D_hd_code_802F21F0;
                    break;
                case 4:
                    sp154 = D_hd_code_802F26F0;
                    break;
                case 5:
                    sp154 = D_hd_code_802F2BF0;
                    break;
                case 6:
                    sp154 = D_hd_code_802F30F0;
                    break;
                case 7:
                    sp154 = D_hd_code_802F35F0;
                    break;
                }
            }
            sp150 = osVirtualToPhysical(sp154);
            gDPPipeSync(entry++);
            gDPLoadTextureBlock(entry++, sp150, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

            func_hd_code_8026A5CC(&arg1->unk1900[sp168], &D_hd_code_802E9FB0, 0x40);
            if (sp14F != 0) {
                arg1->unk1900[sp168].v.tc[0] = 0x260;
                arg1->unk1900[sp168+1].v.tc[0] = 0;
                arg1->unk1900[sp168+2].v.tc[0] = 0;
                arg1->unk1900[sp168+3].v.tc[0] = 0x260;
            }
            for(sp15C = 0; sp15C < 4; sp15C++) {
                arg1->unk1900[sp168 + sp15C].v.ob[0] = spFC[sp15C] + D_80367D60[sp164].unk0;
                arg1->unk1900[sp168 + sp15C].v.ob[1] = spEC[sp15C] + D_80367D60[sp164].unk2;
                arg1->unk1900[sp168 + sp15C].v.ob[2] = spDC[sp15C] + D_80367D60[sp164].unk4;
            }
            gSPVertex(entry++, &D_2000000.unk1900[sp168], 4, 0);
            sp168 += 4;
            gSP1Triangle(entry++, 0, 1, 2, 0);
            gSP1Triangle(entry++, 0, 2, 3, 0);
        }
    }

    if (D_803EF32E == 0) {
        sp164 = 0;
        sp15B = 0;
        while(sp164 < 0x14 && sp15B == 0) {
            if (D_80367D60[sp164].unk15 == 3) {
                sp15B = 1;
                gDPPipeSync(entry++);
                gDPLoadTextureBlock(entry++, osVirtualToPhysical(&D_hd_code_802E9FF0), G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

                func_hd_code_8026A5CC(&arg1->unk1900[sp168], &D_hd_code_802E9FB0, 0x40);
                for(sp15C = 0; sp15C < 4; sp15C++) {
                    arg1->unk1900[sp168 + sp15C].v.ob[0] = spFC[sp15C];
                    arg1->unk1900[sp168 + sp15C].v.ob[1] = spEC[sp15C];
                    arg1->unk1900[sp168 + sp15C].v.ob[2] = spDC[sp15C];
                }
                func_hd_code_802D4F68(&arg1->unk200, D_803EF310 / 32.0f, D_803EF314 / 32.0f, D_803EF318 / 32.0f);
                gSPMatrix(entry++, &D_2000000.unk200, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
                gSPVertex(entry++, &D_2000000.unk1900[sp168], 4, 0);
                sp168 += 4;
                gSP1Triangle(entry++, 0, 1, 2, 0);
                gSP1Triangle(entry++, 0, 2, 3, 0);
                gSPPopMatrix(entry++, G_MTX_MODELVIEW);

            } else {
                sp164 += 1;
            }
        }
    }
    gDPPipeSync(entry++);
    *arg0 = entry;
}

s32 func_hd_code_80267614(struct S_80367D60* arg0) {
  s32 spC;
  u8 spB;

  spC = 0;
  spB = arg0->unk12;
  while(D_803C30A8[spC] != 0xFFFF) {
    if (D_803C30A8[spC++] == spB) {
      return 1;
    }
  }
  return 0;
}

