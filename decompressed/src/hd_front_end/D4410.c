#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/hd.h"
#include "../hd_code/yoshi.h"
#include "../hd_code/functions.h"
#include "../hd_code/variables.h"
#include "structs.h"

#pragma intrinsic(sqrtf)

typedef struct {
  u8 pad0[0x20];
  /* 0x20 */ f32 unk20;
  /* 0x24 */ f32 unk24;
  /* 0x28 */ f32 unk28;
  /* 0x2C */ f32 unk2C;
  /* 0x30 */ f32 unk30;
  /* 0x34 */ f32 unk34;
  s32 pad38;
} S_8020BD30;  /* stride 0x3C */

typedef struct {
  /* 0x0 */ s32 unk0;
  /* 0x4 */ Gfx *unk4;
} S_80218270;  /* stride 0x8 */

float sqrtf(float);
void func_hd_front_end_801F0570(void);
u8 func_hd_code_80264BA4(u8);
s32 func_hd_front_end_801FE760(s32);
void func_hd_front_end_801FCE74(u8 *, s32, f32, f32, s32, s32, f32, s32);
s32 func_hd_front_end_801F1DA8(s32);
void func_hd_front_end_801FDCA4(Vtx *, s32, s32);
void func_hd_code_802595E0(S_80218270 *, s32, s32, void *);
void func_hd_front_end_801F374C(void *);
void func_hd_front_end_801F4878(s32 *, struct Model1 *);
void func_hd_front_end_801F36B0(void);

extern s32 D_hd_front_end_80217290[];   /* grid X */
extern s32 D_hd_front_end_80217390[];   /* grid Y */
extern s32 D_hd_front_end_80217490[];   /* grid S */
extern s32 D_hd_front_end_80217590[];   /* grid T */
extern Vtx D_hd_front_end_80215A88[];
extern u8 D_66C900[];
extern u8 D_68B550[];
extern u8 *D_hd_front_end_80215A70[];
extern u8 *D_hd_front_end_80215A7C;
extern u8 *D_hd_front_end_80215A80;
extern u8 *D_hd_front_end_80215A84;
extern s32 D_hd_front_end_8021728C;
extern void *D_hd_front_end_8020BC88;
extern s32 D_hd_front_end_8020BD08[9];
extern u16 D_hd_front_end_80217288;
extern S_8020BD30 D_hd_front_end_8020BD30[];
extern s32 D_hd_front_end_8020BE98;
extern u8   D_hd_front_end_80217A10[];
extern s32  D_hd_front_end_80217B50;
extern f32  D_hd_front_end_80217B54;
extern f32  D_hd_front_end_80217B58;
extern f32  D_hd_front_end_80217B5C;
extern f32  D_hd_front_end_80217B60;
extern f32  D_hd_front_end_80217B64;
extern f32  D_hd_front_end_80217B68;
extern s32  D_hd_front_end_80217B6C;
extern S_80218270 D_hd_front_end_80218270[];
extern s16  D_hd_front_end_802182A8;

void func_hd_front_end_801F0570(void) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    s32 pad[2];

    sp1C = 250.0f;
    sp18 = ((sp1C * 2.0) / 7.0);
    for (sp28 = 0; sp28 < 8; sp28++) {
        for (sp2C = 0; sp2C < 8; sp2C++) {
            D_hd_front_end_80217290[sp2C + sp28 * 8] = (s32) ((f32) sp2C * sp18 - sp1C);
            D_hd_front_end_80217390[sp2C + sp28 * 8] = (s32) ((f32) sp28 * sp18 - sp1C);
            D_hd_front_end_80217490[sp2C + sp28 * 8] = (sp2C << 5) << 5;
            D_hd_front_end_80217590[sp2C + sp28 * 8] = (sp28 << 5) << 5;
        }
    }
    /* Face 0: +Z */
    for (sp24 = 0; sp24 < 0x40; sp24++) {
        sp10 = D_hd_front_end_80217290[sp24];
        spC = D_hd_front_end_80217390[sp24];
        sp8 = 250.0f;
        sp14 = sqrtf(sp10 * sp10 + spC * spC + sp8 * sp8);
        D_hd_front_end_80215A88[sp24].n.ob[0] = (s16) (s32) ((f64) (sp10 / sp14) * 250.0);
        D_hd_front_end_80215A88[sp24].n.ob[1] = (s16) (s32) ((f64) (spC / sp14) * 250.0);
        D_hd_front_end_80215A88[sp24].n.ob[2] = (s16) (s32) ((f64) (sp8 / sp14) * 250.0);
        D_hd_front_end_80215A88[sp24].n.tc[0] = (s16) D_hd_front_end_80217490[sp24];
        D_hd_front_end_80215A88[sp24].n.tc[1] = (s16) D_hd_front_end_80217590[sp24];
        D_hd_front_end_80215A88[sp24].n.n[0] = (s8) (s32) (sp10 / sp14 * 127.0f);
        D_hd_front_end_80215A88[sp24].n.n[1] = (s8) (s32) (spC / sp14 * 127.0f);
        D_hd_front_end_80215A88[sp24].n.n[2] = (s8) (s32) (sp8 / sp14 * 127.0f);
        D_hd_front_end_80215A88[sp24].n.a = 0xFF;
    }
    /* Face 1: -Z */
    sp20 = 0x40;
    for (sp24 = 0; sp24 < 0x40; sp24++) {
        sp10 = (f32) D_hd_front_end_80217290[sp24];
        spC = (f32) D_hd_front_end_80217390[sp24];
        sp8 = 250.0f;
        sp14 = sqrtf(sp10 * sp10 + spC * spC + sp8 * sp8);
        D_hd_front_end_80215A88[sp20 + sp24].n.ob[0] = (s16) (s32) ((f64) (sp10 / sp14) * 250.0);
        D_hd_front_end_80215A88[sp20 + sp24].n.ob[1] = (s16) (s32) ((f64) (spC / sp14) * 250.0);
        D_hd_front_end_80215A88[sp20 + sp24].n.ob[2] = (s16) (s32) ((f64) (-sp8 / sp14) * 250.0);
        D_hd_front_end_80215A88[sp20 + sp24].n.tc[0] = (s16) D_hd_front_end_80217490[sp24];
        D_hd_front_end_80215A88[sp20 + sp24].n.tc[1] = (s16) D_hd_front_end_80217590[sp24];
        D_hd_front_end_80215A88[sp20 + sp24].n.n[0] = (s8) (s32) (sp10 / sp14 * 127.0f);
        D_hd_front_end_80215A88[sp20 + sp24].n.n[1] = (s8) (s32) (spC / sp14 * 127.0f);
        D_hd_front_end_80215A88[sp20 + sp24].n.n[2] = (s8) (s32) (-sp8 / sp14 * 127.0f);
        D_hd_front_end_80215A88[sp20 + sp24].n.a = 0xFF;
    }
    /* Face 2: +Y */
    sp20 = 0x80;
    for (sp24 = 0; sp24 < 0x40; sp24++) {
        sp10 = (f32) D_hd_front_end_80217290[sp24];
        spC = (f32) D_hd_front_end_80217390[sp24];
        sp8 = 250.0f;
        sp14 = sqrtf(sp10 * sp10 + spC * spC + sp8 * sp8);
        D_hd_front_end_80215A88[sp20 + sp24].n.ob[0] = (s16) (s32) ((f64) (sp10 / sp14) * 250.0);
        D_hd_front_end_80215A88[sp20 + sp24].n.ob[1] = (s16) (s32) ((f64) (sp8 / sp14) * 250.0);
        D_hd_front_end_80215A88[sp20 + sp24].n.ob[2] = (s16) (s32) ((f64) (spC / sp14) * 250.0);
        D_hd_front_end_80215A88[sp20 + sp24].n.tc[0] = (s16) D_hd_front_end_80217490[sp24];
        D_hd_front_end_80215A88[sp20 + sp24].n.tc[1] = (s16) D_hd_front_end_80217590[sp24];
        D_hd_front_end_80215A88[sp20 + sp24].n.n[0] = (s8) (s32) (sp10 / sp14 * 127.0f);
        D_hd_front_end_80215A88[sp20 + sp24].n.n[1] = (s8) (s32) (sp8 / sp14 * 127.0f);
        D_hd_front_end_80215A88[sp20 + sp24].n.n[2] = (s8) (s32) (spC / sp14 * 127.0f);
        D_hd_front_end_80215A88[sp20 + sp24].n.a = 0xFF;
    }
    /* Face 3: -Y */
    sp20 = 0xC0;
    for (sp24 = 0; sp24 < 0x40; sp24++) {
        sp10 = (f32) D_hd_front_end_80217290[sp24];
        spC = (f32) D_hd_front_end_80217390[sp24];
        sp8 = 250.0f;
        sp14 = sqrtf(sp10 * sp10 + spC * spC + sp8 * sp8);
        D_hd_front_end_80215A88[sp20 + sp24].n.ob[0] = (s16) (s32) ((f64) (sp10 / sp14) * 250.0);
        D_hd_front_end_80215A88[sp20 + sp24].n.ob[1] = (s16) (s32) ((f64) (-sp8 / sp14) * 250.0);
        D_hd_front_end_80215A88[sp20 + sp24].n.ob[2] = (s16) (s32) ((f64) (spC / sp14) * 250.0);
        D_hd_front_end_80215A88[sp20 + sp24].n.tc[0] = (s16) D_hd_front_end_80217490[sp24];
        D_hd_front_end_80215A88[sp20 + sp24].n.tc[1] = (s16) D_hd_front_end_80217590[sp24];
        D_hd_front_end_80215A88[sp20 + sp24].n.n[0] = (s8) (s32) (sp10 / sp14 * 127.0f);
        D_hd_front_end_80215A88[sp20 + sp24].n.n[1] = (s8) (s32) (-sp8 / sp14 * 127.0f);
        D_hd_front_end_80215A88[sp20 + sp24].n.n[2] = (s8) (s32) (spC / sp14 * 127.0f);
        D_hd_front_end_80215A88[sp20 + sp24].n.a = 0xFF;
    }
    /* Face 4: +X */
    sp20 = 0x100;
    for (sp24 = 0; sp24 < 0x40; sp24++) {
        sp10 = (f32) D_hd_front_end_80217290[sp24];
        spC = (f32) D_hd_front_end_80217390[sp24];
        sp8 = 250.0f;
        sp14 = sqrtf(sp10 * sp10 + spC * spC + sp8 * sp8);
        D_hd_front_end_80215A88[sp20 + sp24].n.ob[0] = (s16) (s32) ((f64) (sp8 / sp14) * 250.0);
        D_hd_front_end_80215A88[sp20 + sp24].n.ob[1] = (s16) (s32) ((f64) (sp10 / sp14) * 250.0);
        D_hd_front_end_80215A88[sp20 + sp24].n.ob[2] = (s16) (s32) ((f64) (spC / sp14) * 250.0);
        D_hd_front_end_80215A88[sp20 + sp24].n.tc[0] = (s16) D_hd_front_end_80217490[sp24];
        D_hd_front_end_80215A88[sp20 + sp24].n.tc[1] = (s16) D_hd_front_end_80217590[sp24];
        D_hd_front_end_80215A88[sp20 + sp24].n.n[0] = (s8) (s32) (sp8 / sp14 * 127.0f);
        D_hd_front_end_80215A88[sp20 + sp24].n.n[1] = (s8) (s32) (sp10 / sp14 * 127.0f);
        D_hd_front_end_80215A88[sp20 + sp24].n.n[2] = (s8) (s32) (spC / sp14 * 127.0f);
        D_hd_front_end_80215A88[sp20 + sp24].n.a = 0xFF;
    }
    /* Face 5: -X */
    sp20 = 0x140;
    for (sp24 = 0; sp24 < 0x40; sp24++) {
        sp10 = (f32) D_hd_front_end_80217290[sp24];
        spC = (f32) D_hd_front_end_80217390[sp24];
        sp8 = 250.0f;
        sp14 = sqrtf(sp10 * sp10 + spC * spC + sp8 * sp8);
        D_hd_front_end_80215A88[sp20 + sp24].n.ob[0] = (s16) (s32) ((f64) (-sp8 / sp14) * 250.0);
        D_hd_front_end_80215A88[sp20 + sp24].n.ob[1] = (s16) (s32) ((f64) (sp10 / sp14) * 250.0);
        D_hd_front_end_80215A88[sp20 + sp24].n.ob[2] = (s16) (s32) ((f64) (spC / sp14) * 250.0);
        D_hd_front_end_80215A88[sp20 + sp24].n.tc[0] = (s16) D_hd_front_end_80217490[sp24];
        D_hd_front_end_80215A88[sp20 + sp24].n.tc[1] = (s16) D_hd_front_end_80217590[sp24];
        D_hd_front_end_80215A88[sp20 + sp24].n.n[0] = (s8) (s32) (-sp8 / sp14 * 127.0f);
        D_hd_front_end_80215A88[sp20 + sp24].n.n[1] = (s8) (s32) (sp10 / sp14 * 127.0f);
        D_hd_front_end_80215A88[sp20 + sp24].n.n[2] = (s8) (s32) (spC / sp14 * 127.0f);
        D_hd_front_end_80215A88[sp20 + sp24].n.a = 0xFF;
    }
}

Gfx *func_hd_front_end_801F1568(void) {
    u16 (*spAC)[49][420];
    s32 spA8;
    s32 padA4;
    s32 padA0;
    s32 sp9C;
    s32 sp98;
    s32 sp94;
    s32 sp90;
    s32 sp8C;
    s32 sp88;
    s32 sp84;
    s32 sp80;
    s32 sp7C;
    s32 sp78;
    s32 sp74;
    s32 sp70;
    s32 sp6C;
    Gfx *entry;
    Gfx *sp64;

    spAC = (u16 (*)[49][420])D_hd_code_80358070;
    spA8 = (s32) &D_68B550 - (s32) &D_66C900;
    InitiateDma(D_66C900, D_hd_code_80358070, &spA8, 0xDU, 0U, 1U);
    D_hd_code_80358070 += spA8;
    D_hd_front_end_8021728C = D_hd_code_80358070 - 0x6600;
    for (sp9C = 0; sp9C < 3; sp9C++) {
        D_hd_front_end_80215A70[sp9C] = (D_hd_code_80358070 - ((-sp9C * 0x800 + 0x1800) << 1)) - 0x3000;
    }
    D_hd_front_end_80215A7C = D_hd_code_80358070 - 0x3000;
    D_hd_front_end_80215A80 = D_hd_code_80358070 - 0x2000;
    D_hd_front_end_80215A84 = D_hd_code_80358070 - 0x1000;
    entry = (Gfx *) D_hd_code_80358070;
    sp64 = (Gfx*)D_hd_code_80358070;
    func_hd_front_end_801F0570();

    gSPTexture(entry++, qu016(0.5), qu016(0.5), 4, G_TX_RENDERTILE, G_ON);

    for (sp90 = 0; sp90 < 6; sp90++) {
        sp8C = sp90 << 6;
        gSPVertex(entry++, &D_hd_front_end_80215A88[sp8C], 8, 0);
        sp88 = 8;
        for (sp9C = 0; sp9C < 7; sp9C++) {
            gSPVertex(entry++, &D_hd_front_end_80215A88[sp8C + sp9C * 8 + 8], 8, sp88);
            for (sp98 = 0; sp98 < 7; sp98++) {
                sp94 = sp9C * 7 + sp98;


                for (sp84 = 0, sp7C = 0, sp80 = 0; sp84 < 5; sp84++, sp7C += sp78, sp80 += sp6C + 3) {
                    sp74 = (0x10 >> sp84) + 1;
                    sp70 = (sp74 + 3) >> 2;
                    sp78 = sp74 * sp70;
                    sp6C = sp74 * sp74;
                    gDPSetTextureImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, sp74, &spAC[sp90][sp94][sp80]);
                    gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, sp70, sp7C, 7, 0, 0, 0, 0, 0, 0, 0);
                    gDPLoadTile(entry++, 7, 0, 0, (sp74 * 4), (sp74 * 4));
                    gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, sp70, sp7C, sp84, 0, 0, 0, sp84, 0, 0, sp84);
                    gDPSetTileSize(entry++, sp84, ((sp98 * 0x10) << 2) >> sp84, ((sp9C * 0x10) << 2) >> sp84, ((sp98 * 0x10 + 0x10) << 2) >> sp84, ((sp9C * 0x10 + 0x10) << 2) >> sp84);

                }
                if ((sp90 == 1) || (sp90 == 2) || (sp90 == 5)) {
                    if (sp88 == 8) {
                        gSP1Triangle(entry++, sp98, sp98 + 8, sp98 + 9, 0);
                        gSP1Triangle(entry++, sp98, sp98 + 9, sp98 + 1, 0);
                    } else {
                        gSP1Triangle(entry++, sp98 + 8, sp98, sp98 + 1, 0);
                        gSP1Triangle(entry++, sp98 + 8, sp98 + 1, sp98 + 9, 0);
                    }
                } else if (sp88 == 8) {
                    gSP1Triangle(entry++, sp98, sp98 + 9, sp98 + 8, 0);
                    gSP1Triangle(entry++, sp98, sp98 + 1, sp98 + 9, 0);
                } else {
                    gSP1Triangle(entry++, sp98 + 8, sp98 + 1, sp98, 0);
                    gSP1Triangle(entry++, sp98 + 8, sp98 + 9, sp98 + 1, 0);
                }
            }
            sp88 ^= 8;
        }
    }

    gSPEndDisplayList(entry++);

    D_hd_code_80358070 += ((s32) entry - (s32) sp64 >> 3) * 8;
    return sp64;
}

s32 func_hd_front_end_801F1DA8(s32 arg0) {
  struct LevelData *sp2C;
  s32 sp28;
  s32 sp24;

  if (func_hd_front_end_801FE760(arg0) != 0) {
    return 0;
  }
  if (func_hd_code_80264BA4(arg0) != 3) {
    return 0;
  }

  if ((((players[playerNumber].unk18[arg0] > 0) && (players[playerNumber].unk18[arg0] < 6)?1:0) != 0) || (arg0 == 0)) {
    return 1;
  }
  for (sp28 = 0; sp28 < 0x3C; sp28++) {
    if (((players[playerNumber].unk18[sp28] > 0) && (players[playerNumber].unk18[sp28] < 6)?1:0) != 0) {
      sp2C = &D_hd_front_end_8020D810[sp28];

      for(sp24 = 0; sp24 < 8 && sp2C->unk1C[sp24] != -1;sp24++) {
        if (sp2C->unk1C[sp24] == arg0) {
          return 1;
        }
      }

      for (sp24 = 0;sp24 < 4 && sp2C->unk18[sp24] != -1;sp24++) {
        if ((sp2C->unk18[sp24] == arg0) && (players[playerNumber].unk54[sp28] & (1 << sp24))) {
          return 1;
        }
      }
    }
  }
  return 0;
}

Gfx *func_hd_front_end_801F2000(void) {
    Vtx *sp84 = (Vtx *) D_hd_code_80358070;
    u8 *sp80 = D_hd_code_80358070;
    Gfx *sp7C;
    Gfx *entry;
    s32 sp74;
    s32 sp70;


    D_hd_code_80358070 += 0x300;
    sp7C = entry = (Gfx*)D_hd_code_80358070;

    gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | 0xFFE0CDF8);
    gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH | G_CULL_BACK);
    gSPTexture(entry++, 0x8000, 0x8000, 5, 0, G_ON);
    gDPSetTextureLOD(entry++, G_TL_LOD);
    gDPSetCycleType(entry++, G_CYC_2CYCLE);
    gDPSetRenderMode(entry++, G_RM_OPA_SURF, G_RM_XLU_SURF2);
    for (sp70 = 0; sp70 < 2; sp70++) {
        gDPPipeSync(entry++);
        if (sp70 != 0) {
            gDPSetCombineLERP(entry++, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, COMBINED, 0, PRIMITIVE_ALPHA, 0, COMBINED, 0, PRIMITIVE, 0);
        } else {
            gSPDisplayList(entry++, &D_hd_front_end_8020BC88);
            gDPSetCombineLERP(entry++, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, 0, 0, 0, PRIMITIVE, COMBINED, 0, ENVIRONMENT, 0);
        }
        for (sp74 = 0; sp74 < 0x3C; sp74++) {
            s32 sp44;
            s32 sp40;

            for (sp44 = 0, sp40 = 0; sp44 < 6 && sp40 == 0; sp44++) {
                if (D_hd_code_802E8F38[sp44].unk0 == sp74) {
                    sp40 = 1;
                }
            }
            if ((sp40 != 0) && (players[playerNumber].unk90 & (1 << (sp44 + 0x1F)))) {
                func_hd_front_end_801FCE74(sp84, sp74, (f32) (sp70 * 1.5 + 2.5), (f32) (sp70 * 1.5 + 4.0), 0x20, 0x20, 2.25f, 1);
                gSPVertex(entry++, sp84, 4, 0);
                gSP1Triangle(entry++, 0, 1, 2, 0);
                gSP1Triangle(entry++, 2, 3, 0, 0);
                sp84 += 4;
            }
        }
    }
    gDPPipeSync(entry++);
    gSPEndDisplayList(entry++);
    D_hd_code_80358070 = (u8*)entry;
    osWritebackDCache(sp80, 0x300);
    return sp7C;
}

Gfx* func_hd_front_end_801F2428(void) {
    struct LevelData* spEC;
    Vtx* spE8 = (Vtx*)D_hd_code_80358070;
    Gfx* entry;
    Gfx* spE0;
    s32 spDC;
    s32 spD8;
    s32 spD4 = 0;
    s32 spD0 = 0;
    s32 spCC;
    u8 spCB;
    s8 spCA;
    u8 spC9;
    f32 spC4;
    s32 spA0[9] = D_hd_front_end_8020BD08;
    s32 sp9C;
    s32 sp98 = 0;
    u8 sp97;
    u8 sp96;
    u8 sp95;
    u8 sp94;

    D_hd_code_80358070 += 0x1E00;
    entry = (Gfx*)D_hd_code_80358070;
    spE0 = entry;

    gDPPipeSync(entry++);

    gDPSetTextureLOD(entry++, G_TL_LOD);
    gDPSetCycleType(entry++, G_CYC_2CYCLE);
    gDPSetRenderMode(entry++, G_RM_OPA_SURF, G_RM_XLU_SURF2);
    gSPTexture(entry++, 0x8000, 0x8000, 5, 0, G_ON);
    for(spCA = 8; spCA >= 0; spCA--) {
        sp9C = spA0[spCA];
        if (sp9C != sp98) {
            gSPDisplayList(entry++, sp9C);
        }
        sp98 = sp9C;
        gDPPipeSync(entry++);
        switch (spCA) {
        case 0:
        case 8:
            gDPSetCombineLERP(entry++, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, 0, 0, 0, SHADE, COMBINED, 0, ENVIRONMENT, 0);
            sp94 = 0xFF;
            sp95 = 0;
            sp96 = 0;
            sp97 = 0;
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            gDPSetCombineLERP(entry++, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, COMBINED, 0, PRIMITIVE_ALPHA, 0, COMBINED, 0, PRIMITIVE, 0);
            sp94 = 0xFF;
            sp95 = 0;
            sp96 = 0;
            sp97 = 0;
            break;
        case 5:
            gDPSetCombineLERP(entry++, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, 0, 0, 0, SHADE, COMBINED, 0, PRIMITIVE, 0);
            sp95 = sp96  = sp97 = 0x50, sp94 = 0xFF;
            break;
        case 6:
            gDPSetCombineLERP(entry++, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, 0, 0, 0, SHADE, COMBINED, 0, PRIMITIVE, 0);
            sp97 = 0xFF,
            sp94 = 0xFF,
            sp95 = 0;
            sp96 = 0;
            break;
        case 7:
            gDPSetCombineLERP(entry++, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, 0, 0, 0, SHADE, COMBINED, 0, PRIMITIVE, 0);
            sp96 = 0xFF,
            sp94 = 0xFF;
            sp95 = 0;
            sp97 = 0;
            break;
        }

        for(spDC = 0; spDC < 0x3C; spDC++) {
            spC9 = ((spCA == 6) || (spCA == 7)) && (((players[playerNumber].unk18[spDC] > 0) && (players[playerNumber].unk18[spDC] < 6))?1:0)!=0 && players[playerNumber].unk18[spDC] != 4;
            if ((players->unk18[(playerNumber << 8) + spDC] == spCA) || (spC9 != 0)) {
                spEC = &D_hd_front_end_8020D810[spDC];
                if (func_hd_front_end_801F1DA8(spDC) != 0) {
                    if (spC9 != 0) {
                        for(spD8 = 0, spCB = 0;((spD8 < 4) && (spEC->unk18[spD8] != -1) && (spCB == 0));spD8++) {
                            if (!(players->unk54[(playerNumber << 8) + spDC] & (1 << spD8))) {
                                spCB = 1;
                            }
                        }
                        if (!(((spCB == 0) || (spCA != 6)) && ((spCB != 0) || (spCA != 7)))) {
                            continue;
                        }
                    }
                    if (D_hd_code_802E8F94[spDC].unk0 & 0x81) {
                        spC4 = 1.75f;
                    } else {
                        spC4 = 1.0f;
                    }
                    if (spC9 != 0) {
                        spC4 = (f32) ((f64) spC4 + 0.3);
                    }
                    func_hd_front_end_801FCE74(&spE8[spD4], spDC, 0.0f, 0.0f, 0x20, 0x20, spC4, 0);
                    for(spD8 = 0; spD8 < 4; spD8++) {
                        spE8[spD4 + spD8].v.cn[0] = sp97;
                        spE8[spD4 + spD8].v.cn[1] = sp96;
                        spE8[spD4 + spD8].v.cn[2] = sp95;
                        spE8[spD4 + spD8].v.cn[3] = sp94;
                    }
                    spD4 += 4;
                    spCC = spD4 - spD0;
                    if (!(spCC & 0xF)) {
                        Vtx* sp60 = ((spD4 - 16)) + spE8;
                        gSPVertex(entry++, sp60, 16, 0);
                        for(spD8 = 0; spD8 < 16; spD8 += 4) {
                            gSP1Triangle(entry++, spD8, spD8 + 1, spD8 + 2, 0);
                            gSP1Triangle(entry++, spD8 + 2, spD8 + 3, spD8, 0);
                        }
                    }
                }
            }
        }
        spCC = spD4 - spD0;
        if (spCC % 16) {
            Vtx* sp50 = ((spD4 - (spCC % 16))) + spE8;
            gSPVertex(entry++, sp50, spCC % 16, 0)
            for(spD8 = 0; spD8 < (spCC % 16); spD8+=4) {
                    gSP1Triangle(entry++, spD8, spD8 + 1, spD8 + 2, 0);
                    gSP1Triangle(entry++, spD8 + 2, spD8 + 3, spD8, 0);
            }
            spD0 = spD4;
        }
    }
    gDPPipeSync(entry++);
    gSPEndDisplayList(entry++);
    D_hd_code_80358070 = (u8*)entry;
    osWritebackDCache(spE8, 0x1E00);
    return spE0;
}

Gfx *func_hd_front_end_801F2E20(void) {
    Vtx *spCC = D_hd_code_803156F8[0].unk15C0;
    Vtx *spC8 = D_hd_code_803156F8[1].unk15C0;
    Mtx *spC4 = (Mtx*)D_hd_code_80358070;
    Gfx *entry;
    Gfx *spBC;
    s32 spB8;
    s32 spB4;
    s32 padB0;
    s32 padAC;
    s32 padA8;
    s32 padA4;
    s32 spA0;
    s32 pad9C;
    s32 pad98;
    s32 pad94;
    s32 pad90;
    s32 pad8C;
    s32 pad88;
    s32 pad84;

    D_hd_code_80358070 += 0x80;
    entry = (Gfx*)D_hd_code_80358070;
    spBC = (Gfx*)D_hd_code_80358070;

    guPerspective(&spC4[0], &D_hd_front_end_80217288, 45.0f, 1.3333334f, 100.0f, 25000.0f, 1.0f);
    guLookAt(&spC4[1], 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    gSPPerspNormalize(entry++, D_hd_front_end_80217288);
    gSPMatrix(entry++, &spC4[0], G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(entry++, &spC4[1], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPTexture(entry++, 0x8000, 0x8000, 0, 0, G_ON);

    spA0 = 0;
    for (spB8 = 0; spB8 < 0x200; spB8 += 0x10) {
        gSPVertex(entry++, &D_2000000.unk15C0[spB8], 16, 0);
        gDPPipeSync(entry++);
        for (spB4 = 0; spB4 < 0x10; spB4 += 4) {
            if (((spB8 + spB4) >> 2) % 43 == 0) {
                gDPSetTextureImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, (spA0 << 8) * 2 + D_hd_front_end_8021728C);
                gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, 2, 0, 0, 2, 0, 0);
                gDPLoadSync(entry++);
                gDPLoadBlock(entry++, 7, 0, 0, 255, 512);
                gDPPipeSync(entry++);
                gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, 0, 0, 2, 0, 0, 2, 0, 0);
                gDPSetTileSize(entry++, 0, 0, 0, 60, 60);
                spA0++;
            }
            func_hd_front_end_801FDCA4(spCC, (spB8 + spB4) / 4, func_hd_code_8026A828(0, 0x61A8));
            spCC[spB8 + spB4 + 0].v.tc[0] = 0;
            spCC[spB8 + spB4 + 0].v.tc[1] = 0;
            spCC[spB8 + spB4 + 1].v.tc[0] = 0;
            spCC[spB8 + spB4 + 1].v.tc[1] = 0x3C0;
            spCC[spB8 + spB4 + 2].v.tc[0] = 0x3C0;
            spCC[spB8 + spB4 + 2].v.tc[1] = 0x3C0;
            spCC[spB8 + spB4 + 3].v.tc[0] = 0x3C0;
            spCC[spB8 + spB4 + 3].v.tc[1] = 0;
            gSP1Triangle(entry++, spB4, spB4 + 1, spB4 + 2, 0);
            gSP1Triangle(entry++, spB4, spB4 + 2, spB4 + 3, 0);
        }
    }
    for (spB8 = 0; spB8 < 0x2000U; spB8++) {
        *((u8 *) spC8 + spB8) = *((u8 *) spCC + spB8);
    }
    gDPPipeSync(entry++);
    gSPEndDisplayList(entry++);
    D_hd_code_80358070 += ((s32) ((s32)entry - (s32)spBC) >> 3) * 8;
    osWritebackDCache(spCC, 0x2000);
    return spBC;
}

Gfx *func_hd_front_end_801F3450(Gfx *gfx, struct Model1 *arg1) {
    Gfx *entry = gfx;
    S_8020BD30 *sp48 = D_hd_front_end_8020BD30;
    S_8020BD30 *sp44 = &D_hd_front_end_8020BD30[(((s32)D_hd_front_end_80217B6C * 0x3C + (s32)sp48) - (s32)sp48)  / 0x3C];
    u8 sp43;
    s32 sp3C;

    gSPPerspNormalize(entry++, D_hd_code_8035807C);
    D_hd_front_end_80217B50 = 4;
    guMtxIdentF((Mtx *) &D_hd_front_end_80217A10[0x100]);
    func_hd_front_end_801F374C(&D_hd_front_end_8020BE98);
    if (D_hd_front_end_802182A8 != 1) {
        D_hd_front_end_80217B54 = sp44->unk2C;
        D_hd_front_end_80217B58 = sp44->unk30;
        D_hd_front_end_80217B5C = sp44->unk34;
        D_hd_front_end_80217B60 = sp44->unk20;
        D_hd_front_end_80217B64 = sp44->unk24;
        D_hd_front_end_80217B68 = sp44->unk28;
    }
    guLookAt(&arg1->projection2, D_hd_front_end_80217B54 + 1.0f, D_hd_front_end_80217B58, D_hd_front_end_80217B5C, D_hd_front_end_80217B60, D_hd_front_end_80217B64, D_hd_front_end_80217B68, 0.0f, 1.0f, 0.0f);
    func_hd_front_end_801F4878(&arg1->unkACB0, arg1);
    func_hd_code_802595E0(D_hd_front_end_80218270, 7, 8, &func_hd_front_end_801F36B0);
    for (sp3C = 0, sp43 = 0; sp3C < 7; sp3C++) {
        if ((sp43 == 0) || (D_hd_front_end_80217B6C != 3)) {
            gSPDisplayList(entry++, D_hd_front_end_80218270[sp3C].unk4);
        }
        if (D_hd_front_end_80218270[sp3C].unk0 == 3) {
            sp43 = 1;
        }
    }
    return entry;
}
