#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/hd.h"
#include "../hd_code/yoshi.h"
#include "../hd_code/functions.h"
#include "../hd_code/variables.h"
#include "structs.h"

void func_hd_front_end_801F4C3C(struct S_8020BD30* arg0, f32 arg1);
void func_hd_front_end_801FD484(f32 *, void *, f32 *, f32 *, f32 *, f32);  /* extern */

typedef struct {
  /* 0x0 */ s32 unk0;
  /* 0x4 */ Gfx *unk4;
} S_80218270;  /* stride 0x8, same layout as D4410.c's S_80218270 */

Gfx* func_hd_front_end_801F3964(Gfx*, struct Model1*, struct S_8020BD30*, f32); /* extern */
Gfx* func_hd_front_end_801F4110(Gfx*, struct Model1*, struct S_8020BD30*, f32); /* extern */
Gfx* func_hd_front_end_801FE238(Gfx*, struct Model1*);                         /* extern */

extern f32 D_hd_front_end_80217B54;
extern f32 D_hd_front_end_80217B58;
extern f32 D_hd_front_end_80217B5C;
extern S_80218270 D_hd_front_end_80218270[];
extern f32 D_hd_front_end_8020BDEC;
extern f32  D_hd_front_end_80217A10[][4][4];
extern s32 D_hd_front_end_80217B50;
extern Mtx D_hd_front_end_80217B70[][4];
extern u8 *D_hd_front_end_80215A7C;
extern u8 *D_hd_front_end_80215A80;
extern Vtx D_hd_front_end_80217690[7][2][4]; // Size: 0x380 / 0x40
extern Mtx D_hd_front_end_80217B70[7][4]; // Size: 0x700 / 0x100
extern u8 *D_hd_front_end_80215A84;
extern f32 D_hd_front_end_8021A918;
extern f32 D_hd_front_end_8021A91C;
extern f32 D_hd_front_end_8021A920;

// <data>
struct S_8020BD30 D_hd_front_end_8020BD30 = { 4476.0f, 0x41DA6666, 27.2999992f, 614.0f, 0x00000000, 0x00000000, 0xC8, 0xC8, 0xC8, 0x00, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
struct S_8020BD30 D_hd_front_end_8020BD6C = { 20000.0f, 0x3F800000, 60193.1992f, 17992.0f, 0x00000000, 0x00000000, 0x28, 0x28, 0xB4, 0x00, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
struct S_8020BD30 D_hd_front_end_8020BDA8 = { 6790.0f, 0x3F800000, 686.900024f, 9117.0f, &D_hd_front_end_8020BD6C, 0x00000000, 0xFF, 0x28, 0x00, 0x00, 72.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
struct S_8020BD30 D_hd_front_end_8020BDE4 = { 12750.0f, 0x3F800000, 365.25f, 5984.0f, &D_hd_front_end_8020BDA8, &D_hd_front_end_8020BD30, 0x00, 0xC8, 0x64, 0x00, 144.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
struct S_8020BD30 D_hd_front_end_8020BE20 = { 12104.0f, 0xC3730000, 224.699997f, 4328.0f, &D_hd_front_end_8020BDE4, 0x00000000, 0xFF, 0x78, 0x00, 0x00, 216.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
struct S_8020BD30 D_hd_front_end_8020BE5C = { 4880.0f, 0x426ACCCD, 88.0f, 2320.0f, &D_hd_front_end_8020BE20, 0x00000000, 0xFF, 0x78, 0x78, 0x00, 288.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
struct S_8020BD30 D_hd_front_end_8020BE98 = { 70000.0f, 0x41CB3333, 0.0f, 0.0f, 0x00000000, &D_hd_front_end_8020BE5C, 0xFF, 0xFF, 0x5A, 0x00, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
// </data>

s32 func_hd_front_end_801F36B0(s32* arg0, s32* arg1) {
  struct S_8020BD30* spC = &D_hd_front_end_8020BD30;
  struct S_8020BD30* sp8 = &D_hd_front_end_8020BD30 + (((s32) (((*arg0 * 0x3C) + (s32)spC) - (s32)spC) / 0x3C) );
  struct S_8020BD30* sp4 = &D_hd_front_end_8020BD30 + (((s32) (((*arg1 * 0x3C) + (s32)spC) - (s32)spC) / 0x3C) );

  return (s32) (sp4->unk38 - sp8->unk38);
}

void func_hd_front_end_801F374C(struct S_8020BD30 *arg0) {
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    Mtx *sp60;
    f32 sp20[4][4];

    while (arg0 != NULL) {
        sp74 = arg0->unk0 / D_hd_front_end_8020BDE4.unk0;
        sp64 = 0.0f;
        sp60 = D_hd_front_end_80217B70[((s32)arg0 - (s32)&D_hd_front_end_8020BD30) / 0x3C];
        if (arg0->unk8 != 0.0f) {
            arg0->unk1C = arg0->unk1C + ((((D_hd_front_end_8020BDE4.unk8 * 360.0) / arg0->unk8) / 1800.0) * 60.0) / 60.0;
        }
        func_hd_front_end_801FD484(&sp64, &arg0->unk1C, &sp70, &sp6C, &sp68, arg0->unkC);
        guTranslateF(sp20, -sp70, -sp6C, -sp68);
        guScale(&sp60[D_hd_code_8035805C + 2], sp74, sp74, sp74);
        guMtxCatF(D_hd_front_end_80217A10[D_hd_front_end_80217B50], sp20, D_hd_front_end_80217A10[D_hd_front_end_80217B50-1]);
        D_hd_front_end_80217B50--;
        guMtxF2L(D_hd_front_end_80217A10[D_hd_front_end_80217B50], &sp60[D_hd_code_8035805C]);
        osWritebackDCache(sp60, 4 * sizeof(Mtx));
        func_hd_front_end_801F4C3C(arg0, sp74);
        func_hd_front_end_801F374C(arg0->unk14);
        D_hd_front_end_80217B50++;
        arg0 = arg0->unk10;
    }
}

Gfx* func_hd_front_end_801F3964(Gfx* gfx, struct Model1* arg1, struct S_8020BD30* arg2, f32 arg3) {
    Gfx* entry = gfx;
    f32 spA0;
    s16 sp9E;
    s16 sp9C;
    u8* sp98;
    Vtx* sp94;
    s32 sp90;

    spA0 = ((f64) arg2->unk0 * 64.0) / (f64) D_hd_front_end_8020BDE4.unk0;
    sp94 = D_hd_front_end_80217690[((s32) arg2 - (s32) &D_hd_front_end_8020BD30) / 0x3C][D_hd_code_8035805C];
    gDPPipeSync(entry++);
    gDPSetPrimColor(entry++, 0xFF, 0xFF, arg2->unk18, arg2->unk19, (*arg2).unk1A, 0xFF);
    gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTextureFilter(entry++, G_TF_BILERP);
    gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | 0xffe0cdf8);
    gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
    gSPTexture(entry++, 0x2000, 0x2000, 0, 0, G_ON);
    gDPSetCombineLERP(entry++, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0);
    switch((((s32) arg2 - (s32) &D_hd_front_end_8020BD30) / 0x3C)) {
        case 1:
        case 4:
            sp98 = D_hd_front_end_80215A80;
            break;
        default:
            sp98 = D_hd_front_end_80215A7C;
            break;
    }

    if ((f64) arg2->unk38 > 1.0) {
        spA0 = (f32) (((f64) spA0 * 10000.0) / (f64) arg2->unk38);
    }
    sp90 = spA0;
    func_hd_code_8027690C(arg1, 0.0f, 0.0f, 0.0f, &sp9E, &sp9C,
                          &D_hd_front_end_80217B70[((s32) arg2 - (s32) &D_hd_front_end_8020BD30) / 0x3C][D_hd_code_8035805C],
                          &D_hd_front_end_80217B70[((s32) arg2 - (s32) &D_hd_front_end_8020BD30) / 0x3C][D_hd_code_8035805C + 2],
                          &arg1->unk1280, 4.0f);
    if ((f64) (ABS(sp9E)) + (spA0 / 2.0) < 4096.0 && (f64) (ABS(sp9C)) + (spA0 / 2.0) < 4096.0) {
        gDPSetTextureImage(entry++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, sp98);
        gDPSetTile(entry++, G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, 7, 0, 1, 6, 0, 2, 0, 0);
        gDPLoadSync(entry++);
        gDPLoadBlock(entry++, 7, 0, 0, 2047, 256);
        gDPPipeSync(entry++);
        gDPSetTile(entry++, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0, 0, 0, 1, 6, 0, 2, 0, 0);
        gDPSetTileSize(entry++, 0, 0, 0, 252, 252);
        sp94[0].v.ob[0] = (s16) (sp9E - (sp90 / 2));
        sp94[0].v.ob[1] = (s16) (sp9C - (sp90 / 2));
        sp94[0].v.ob[2] = -0xA;
        sp94[0].v.tc[0] = 0;
        sp94[0].v.tc[1] = 0;
        sp94[1].v.ob[0] = (s16) (sp9E - (sp90 / 2));
        sp94[1].v.ob[1] = (s16) (sp9C + (sp90 / 2));
        sp94[1].v.ob[2] = -0xA;
        sp94[1].v.tc[0] = 0;
        sp94[1].v.tc[1] = 0x3F00;
        sp94[2].v.ob[0] = (s16) (sp9E + (sp90 / 2));
        sp94[2].v.ob[1] = (s16) (sp9C + (sp90 / 2));
        sp94[2].v.ob[2] = -0xA;
        sp94[2].v.tc[0] = 0x3F00;
        sp94[2].v.tc[1] = 0x3F00;
        sp94[3].v.ob[0] = (s16) (sp9E + (sp90 / 2));
        sp94[3].v.ob[1] = (s16) (sp9C - (sp90 / 2));
        sp94[3].v.ob[2] = -0xA;
        sp94[3].v.tc[0] = 0x3F00;
        sp94[3].v.tc[1] = 0;
        gSPVertex(entry++, sp94, 4, 0);
        gSP1Triangle(entry++, 0, 1, 2, 0);
        gSP1Triangle(entry++, 0, 3, 2, 0);
        gDPPipeSync(entry++);
    }
    gDPPipeSync(entry++);
    osWritebackDCache(sp94, 0x40);
    return entry;
}

Gfx* func_hd_front_end_801F4110(Gfx* gfx, struct Model1* arg1, struct S_8020BD30* arg2, f32 arg3) {
    Gfx* entry = gfx;
    f32 spA0;
    s16 sp9E;
    s16 sp9C;
    Vtx* sp98;
    s32 sp94;

    spA0 = (f32) (((f64) arg2->unk0 * 64.0) / (f64) D_hd_front_end_8020BDE4.unk0);
    sp98 = D_hd_front_end_80217690[((s32) arg2 - (s32) &D_hd_front_end_8020BD30) / 0x3C][D_hd_code_8035805C];
    gDPPipeSync(entry++);
    gDPSetPrimColor(entry++, 255, 255, arg2->unk18, arg2->unk19, (*arg2).unk1A, 255);
    gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTextureFilter(entry++, G_TF_BILERP);
    gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | 0xffe0cdf8);
    gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
    gSPTexture(entry++, 0x1000, 0x1000, 0, 0, G_ON);
    gDPSetCombineLERP(entry++, 0, 0, 0, TEXEL0, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, TEXEL0, 0);
    if ((f64) arg2->unk38 > 1.0) {
        spA0 = (f32) (((f64) spA0 * 10000.0) / (f64) arg2->unk38);
    }
    sp94 = spA0;
    func_hd_code_8027690C(arg1, 0.0f, 0.0f, 0.0f, &sp9E, &sp9C,
                          &D_hd_front_end_80217B70[((s32) arg2 - (s32) &D_hd_front_end_8020BD30) / 0x3C][D_hd_code_8035805C],
                          &D_hd_front_end_80217B70[((s32) arg2 - (s32) &D_hd_front_end_8020BD30) / 0x3C][D_hd_code_8035805C + 2],
                          &arg1->unk1280, 4.0f);
    if ((f64) (ABS(sp9E)) + (spA0 / 2.0) < 4096.0 && (f64) (ABS(sp9C)) + (spA0 / 2.0) < 4096.0) {
        gDPSetTextureImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 1, D_hd_front_end_80215A84);
        gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0, 0, 7, 0, 2, 0, 0, 2, 0, 0);
        gDPLoadSync(entry++);
        gDPLoadBlock(entry++, 7, 0, 0, 1023, 128);
        gDPPipeSync(entry++);
        gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, 0, 0, 2, 0, 0, 2, 0, 0);
        gDPSetTileSize(entry++, 0, 0, 0, 124, 124);
        sp98[0].v.ob[0] = (s16) (sp9E - (sp94 / 2));
        sp98[0].v.ob[1] = (s16) (sp9C - (sp94 / 2));
        sp98[0].v.ob[2] = -0xA;
        sp98[0].v.tc[0] = 0;
        sp98[0].v.tc[1] = 0;
        sp98[1].v.ob[0] = (s16) (sp9E - (sp94 / 2));
        sp98[1].v.ob[1] = (s16) (sp9C + (sp94 / 2));
        sp98[1].v.ob[2] = -0xA;
        sp98[1].v.tc[0] = 0;
        sp98[1].v.tc[1] = 0x3E00;
        sp98[2].v.ob[0] = (s16) (sp9E + (sp94 / 2));
        sp98[2].v.ob[1] = (s16) (sp9C + (sp94 / 2));
        sp98[2].v.ob[2] = -0xA;
        sp98[2].v.tc[0] = 0x3E00;
        sp98[2].v.tc[1] = 0x3E00;
        sp98[3].v.ob[0] = (s16) (sp9E + (sp94 / 2));
        sp98[3].v.ob[1] = (s16) (sp9C - (sp94 / 2));
        sp98[3].v.ob[2] = -0xA;
        sp98[3].v.tc[0] = 0x3E00;
        sp98[3].v.tc[1] = 0;
        gSPVertex(entry++, sp98, 4, 0);
        gSP1Triangle(entry++, 0, 1, 2, 0);
        gSP1Triangle(entry++, 0, 3, 2, 0);
        gDPPipeSync(entry++);
    }
    gDPPipeSync(entry++);
    osWritebackDCache(sp98, 0x40);
    return entry;
}

void func_hd_front_end_801F4878(Gfx* gfx, struct Model1* arg1) {
    Gfx* entry = gfx;
    s32 sp68;
    struct S_8020BD30* sp64;
    struct S_8020BD30* sp60;
    Mtx* sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;

    for (sp68 = 0; sp68 < 7; sp68++) {
        sp64 = &D_hd_front_end_8020BD30;
        sp60 = &sp64[((s32)&sp64[sp68] - (s32)sp64) / 0x3C];
        sp5C = D_hd_front_end_80217B70[sp68];
        sp58 = sp60->unk0 / D_hd_front_end_8020BDE4.unk0;
        sp54 = sp60->unk20 - D_hd_front_end_80217B54;
        sp50 = sp60->unk24 - D_hd_front_end_80217B58;
        sp4C = sp60->unk28 - D_hd_front_end_80217B5C;
        sp60->unk38 = sqrtf((sp54 * sp54) + (sp50 * sp50) + (sp4C * sp4C));
        D_hd_front_end_80218270[((s32) sp60 - (s32) &D_hd_front_end_8020BD30) / 0x3C].unk0 = ((s32) sp60 - (s32) &D_hd_front_end_8020BD30) / 0x3C;
        D_hd_front_end_80218270[((s32) sp60 - (s32) &D_hd_front_end_8020BD30) / 0x3C].unk4 = entry;
        switch (sp68) {
        case 3:
            gSPMatrix(entry++, &arg1->projection, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
            gSPMatrix(entry++, &arg1->projection2, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
            gSPMatrix(entry++, &sp5C[D_hd_code_8035805C], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
            gSPMatrix(entry++, &sp5C[D_hd_code_8035805C + 2], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
            gSPMatrix(entry++, &arg1->unk1280, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
            entry = func_hd_front_end_801FE238(entry, arg1);
            break;
        case 6:
            gSPMatrix(entry++, &arg1->mtx2, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
            gSPMatrix(entry++, &arg1->modelview, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
            entry = func_hd_front_end_801F4110(entry, arg1, sp60, sp58);
            break;
        default:
            gSPMatrix(entry++, &arg1->mtx2, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
            gSPMatrix(entry++, &arg1->modelview, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
            entry = func_hd_front_end_801F3964(entry, arg1, sp60, sp58);
            break;
        }
        gSPEndDisplayList(entry++);
    }
}

void func_hd_front_end_801F4C3C(struct S_8020BD30* arg0, f32 arg1) {
  f32 sp2C;
  f32 sp28 = 0.0f;
  f32 sp24 = 0.0f;

  if (((s32) arg0 - (s32) &D_hd_front_end_8020BD30) / 0x3C != 6) {
    sp2C = D_hd_front_end_80217A10[D_hd_front_end_80217B50][3][3];
    arg0->unk20 = (f32) (D_hd_front_end_80217A10[D_hd_front_end_80217B50][3][0] / sp2C);
    arg0->unk24 = (f32) (D_hd_front_end_80217A10[D_hd_front_end_80217B50][3][1] / sp2C);
    arg0->unk28 = (f32) (D_hd_front_end_80217A10[D_hd_front_end_80217B50][3][2] / sp2C);
  }
  if (((s32) arg0 - (s32) &D_hd_front_end_8020BD30) / 0x3C == 3) {
    do { func_hd_front_end_801FD484(&D_hd_front_end_8021A920, &D_hd_front_end_8021A91C, &arg0->unk2C,
        &arg0->unk30,
        &arg0->unk34, arg1 * D_hd_front_end_8021A918); }while(0); // TODO: fake match
    arg0->unk2C += arg0->unk20;
    arg0->unk30 += arg0->unk24;
    arg0->unk34 += arg0->unk28;

  } else {
    func_hd_front_end_801FD484(&sp28, &sp24, &arg0->unk2C, &arg0->unk30, &arg0->unk34, arg1 * D_hd_front_end_8021A918);
    arg0->unk2C += arg0->unk20;
    arg0->unk30 += arg0->unk24;
    arg0->unk34 += arg0->unk28;
  }
}

void func_hd_front_end_801F4E1C(s32* arg0, s32* arg1) {
  s32* spC = arg0;
  s32* sp8 = arg1;
  u32 sp4;

  for(sp4 = 0; sp4 < 16; sp4++) {
    sp8[sp4]= spC[sp4];
  }
}

