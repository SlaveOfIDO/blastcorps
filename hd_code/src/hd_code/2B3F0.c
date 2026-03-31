#include "common.h"
#include "variables.h"
#include "functions.h"
#include "structs.h"

void func_hd_code_8026A5CC(void*, void*, u32);              /* extern */
s32 func_hd_code_8026AD30(s16);                         /* extern */
void func_hd_code_802AC544(s16, s16, s16);             /* extern */
s32 func_hd_code_80270A54(struct Struct8036BED8*);  /* extern */

extern Vtx D_hd_code_802F99C0[];
extern u8 D_hd_code_802F9A00[]; // This is a 16 x 16 32 bits texture image
extern u8* D_hd_code_802F9E00[]; // This is a 16 x 16 32 bits texture image
extern s32 D_hd_code_802FA200[];
extern s32 D_hd_code_802FA250;
extern s32 D_hd_code_802FA258;
extern s32 D_hd_code_802FA25C;
extern s32 D_hd_code_802FA260;
extern s32 D_hd_code_802FA264;
extern s32 D_hd_code_802FA26C;

// BSS Begin
u16 D_8036BBB0[0x192];
s32 D_8036BED4;
struct Struct8036BED8 *D_8036BED8;
f32 D_8036BEDC;
u8  D_8036BEE0;
// BSS End

extern s32 D_803BE70C;
extern s32 D_803BE710;
extern s16 D_803BE714;
extern u16 D_803C30A8[];

void LoadLevelRdus(struct vec3s* arg0, struct vec3s* arg1) {
  s32 pad1;

  D_8036EB90 = 0;
  D_8036EA7C = 0;
  if (D_hd_code_80364A90 != 0x40) {
    D_8036BED4 = *D_8036BBB0 = 0;
  }
  D_8036BED8 = D_hd_code_80358070;
  D_8036BEE0 = 0;
  D_8036BEDC = 999999.0f;
  while (arg0 != arg1) {
    D_8036BED8[D_8036EB90].x = arg0->x;
    D_8036BED8[D_8036EB90].y = arg0->y;
    D_8036BED8[D_8036EB90].z = arg0->z;
    D_8036BED8[D_8036EB90].unk6 = 0;
    D_8036BED8[D_8036EB90].unk7 = ((arg0->z / (D_803BE710 >> 5)) * D_803BE714) + (arg0->x / (D_803BE70C >> 5));

    func_hd_code_8026A5CC(D_8036BED8[D_8036EB90].unk8[0], &D_hd_code_802F99C0, 0x40U);
    func_hd_code_8026A5CC(D_8036BED8[D_8036EB90].unk8[1], &D_hd_code_802F99C0, 0x40U);
    D_8036EB90++;
    arg0++;
  }
  D_hd_code_80358070 += D_8036EB90 * 0x88;
}

u8 func_hd_code_8026FE6C(s32 arg0) {
  return D_8036BED8[arg0].unk6;
}

void func_hd_code_8026FE8C(s32 arg0) {
  D_8036BED8[arg0].unk6 = 1;
  D_8036EA7C += 1;
}

void func_hd_code_8026FEC4(void) {
  s32 sp34;
  s32 pad30;
  s32 sp2C;
  u8 sp2B;
  u8 sp2A;

  sp2A = 0;
  sp2B = (((s32) D_hd_code_803643E8 / (s32) D_803BE710) * D_803BE714) + ((s32) D_hd_code_803643E0 / (s32) D_803BE70C);

  for(sp34 = 0;sp34 < (s32) D_8036EB90; sp34++) {
    if (((u8) D_8036BED8[sp34].unk7 == sp2B) && ((u8) D_8036BED8[sp34].unk6 == 0)) {
      sp2C = func_hd_code_8026A6F0((s32) D_hd_code_803643E0 >> 5, (s32) D_hd_code_803643E4 >> 5, (s32) D_hd_code_803643E8 >> 5, (s32) D_8036BED8[sp34].x, (s32) D_8036BED8[sp34].y, (s32) D_8036BED8[sp34].z);
      if (sp2C < D_hd_code_802FA200[D_hd_code_80364456]) {
        D_8036EA7C++;
        if ((D_8036EA7C >= 4) && D_hd_code_802E8BD0 == 0) {
          func_hd_code_8026AD30(0x46);
        }
        if (D_hd_code_80364A90 != 0x40) {
          D_8036BBB0[D_8036BED4] = D_8036BBB0[D_8036BED4+1] = sp34;
          D_8036BED4++;
        }
        func_hd_code_802AC544(D_8036BED8[sp34].x, D_8036BED8[sp34].y + 5, D_8036BED8[sp34].z);
        D_8036BED8[sp34].unk6 = 1;
        if (sp2A == 0) {
          sp2A = 1;
          if (D_hd_code_80364AA8 == 0x40) {
            sndPlaySfx(D_hd_code_80367738, 0x3B, NULL);
          } else {
            sndPlaySfx(D_hd_code_80367738, 0x27, NULL);
          }
        }
      }
    }
  }
}

void func_hd_code_802701A8(Gfx** arg0, s32 *arg1) {
    Gfx* entry;
    s32 sp110;
    s32 sp10C;
    f32 spCC[4][4];
    f32 spBC[4];
    f32 spAC[4];
    f32 sp9C[4];

    entry = *arg0;

    gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
    gSPSetGeometryMode(entry++, G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH);
    gDPPipeSync(entry++);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    gDPSetRenderMode(entry++, G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2);
    gDPSetCombineMode(entry++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);


    if (D_hd_code_80364414 != D_8036BEDC) {
        D_8036BEE0 = (u8) D_8036BEE0 ^ 1;
        guAlignF(spCC, (D_hd_code_80364414 - 135.0), 0.0f, 1.0f, 0.0f);

        for(sp110 = 0; sp110 < 4; sp110++) {
            guMtxXFMF(spCC,
                      (f32) D_hd_code_802F99C0[sp110].v.ob[0],
                      (f32) D_hd_code_802F99C0[sp110].v.ob[1],
                      (f32) D_hd_code_802F99C0[sp110].v.ob[2],
                      &spBC[sp110],
                      &spAC[sp110],
                      &sp9C[sp110]
                     );
        }

        for(sp110 = 0; sp110 < D_8036EB90; sp110++) {
            for(sp10C = 0; sp10C < 4; sp10C++) {
                D_8036BED8[sp110].unk8[D_8036BEE0][sp10C].v.ob[0] = (s16)spBC[sp10C] + D_8036BED8[sp110].x;
                D_8036BED8[sp110].unk8[D_8036BEE0][sp10C].v.ob[1] = (s16)spAC[sp10C] + D_8036BED8[sp110].y;
                D_8036BED8[sp110].unk8[D_8036BEE0][sp10C].v.ob[2] = (s16)sp9C[sp10C] + D_8036BED8[sp110].z;
            }
        }
    }


    gDPLoadTextureBlock(entry++, osVirtualToPhysical(&D_hd_code_802F9A00), G_IM_FMT_RGBA, G_IM_SIZ_32b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    for(sp110 = 0; sp110 < D_8036EB90; sp110++) {
        if (((u8) D_8036BED8[sp110].unk6 == 0) && (func_hd_code_80270A54(&D_8036BED8[sp110]) != 0)) {
            gSPVertex(entry++, &D_8036BED8[sp110].unk8[D_8036BEE0], 4, 0);
            gSP1Triangle(entry++, 0, 1, 2, 0);
            gSP1Triangle(entry++, 0, 2, 3, 0);
        }
    }
    gDPPipeSync(entry++);


    gDPLoadTextureBlock(entry++, osVirtualToPhysical(&D_hd_code_802F9E00), G_IM_FMT_RGBA, G_IM_SIZ_32b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    for(sp110 = 0; sp110 < D_8036EB90; sp110++) {
        if (((u8) D_8036BED8[sp110].unk6 != 0) && (func_hd_code_80270A54(&D_8036BED8[sp110]) != 0)) {
            gSPVertex(entry++, (u32) (&D_8036BED8[sp110].unk8[D_8036BEE0]), 4, 0);
            gSP1Triangle(entry++, 0, 1, 2, 0);
            gSP1Triangle(entry++, 0, 2, 3, 0);
        }
    }
    gDPPipeSync(entry++);

    *arg0 = entry;
    D_8036BEDC = D_hd_code_80364414;
}

s32 func_hd_code_80270A54(struct Struct8036BED8* arg0) {
  s32 spC;
  u8 spB;

  spC = 0;
  spB = arg0->unk7;
  while (D_803C30A8[spC] != 0xFFFF) {
    if (D_803C30A8[spC++] == spB) {
      return 1;
    }
  }
  return 0;
}

void func_hd_code_80270AE0(u8* arg0) {
  s32 sp94;
  u8* sp10[0x21];
  u8** spC;
  s32 pad8;
  u8* sp4;

  sp94 = 1;
  spC = sp10;
  if ((arg0 != NULL) && (*arg0 != 0)) {

    sp4 = arg0;
    while (*sp4 != 0) {
      while ((*sp4 != 0) && (*sp4 == 0x20)) {
        *sp4++ = 0U;
      }

      if (*sp4 != 0) {
        sp10[sp94] = sp4;
        sp94++;
      }

      while ((*sp4 != 0) && (*sp4 != 0x20)) {
        sp4++;
      }
    }

    while ((sp94 >= 2) && (spC[1][0] == 0x2D)) {
      switch (spC[1][1]) {
        case 0x64:
          D_hd_code_802FA254 = 1;
          break;
        case 0x76:
          D_hd_code_802FA250 = 1;
          break;
        case 0x73:
          D_hd_code_802FA258 = 1;
          break;
        case 0x6A:
          D_hd_code_802FA25C = 1;
          break;
        case 0x6D:
          D_hd_code_802FA260 = 1;
          break;
        case 0x6C:
          D_hd_code_802FA264 = 1;
          break;
        case 0x63:
          D_hd_code_802FA268 = 1;
          break;
        case 0x43:
          D_hd_code_802FA26C = 1;
          D_hd_code_802FA268 = 1;
          break;
      }
      sp94 -= 1;
      spC++;
    }
  }
}

