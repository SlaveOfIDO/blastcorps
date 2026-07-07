#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/hd.h"
#include "../hd_code/yoshi.h"
#include "../hd_code/functions.h"
#include "../hd_code/variables.h"
#include "structs.h"

void func_hd_code_802A08B4(u8*, u8*);               /* extern */
void func_hd_front_end_80202100(s32, u8**, s32*, s32*);                           /* extern */
void func_hd_front_end_80202270(u8*, s32*, struct S_80211AC0*);                   /* extern */
void func_hd_front_end_802022EC(struct S_80211AC0*, s32, s32, s32, f32, s32, s32); /* extern */

extern u8 D_6E8980; // usa_star.raw
extern u8 D_6EA850; // ninlogo.raw
extern u8 D_6EAB90; // reflectlogo.raw
extern u8 D_6EC4C0;
extern s32 D_hd_front_end_802182C0;
extern u8* D_hd_front_end_802182C4;
extern u8* D_hd_front_end_802182C8;
extern u8* D_hd_front_end_802182CC;
extern s16 D_hd_code_8036BB20;
extern u8* D_hd_front_end_80218350;
extern s32 D_hd_front_end_80218358[2];
extern s32 D_hd_front_end_80218360[2];
extern s32 D_hd_front_end_80218368[2];
extern Mtx D_hd_front_end_80218370;
extern Mtx D_hd_front_end_802183B0;
extern Mtx D_hd_front_end_802183F0;
extern struct S_80211AC0 D_hd_front_end_80218430;
extern u32 D_hd_front_end_80218730;
extern u16 D_hd_front_end_80218734;
extern Mtx  D_hd_front_end_802182D0[];

typedef struct {
  u8 pad0[0x14];
  s32 unk14;
  u8 pad18[0x4];
  s32 unk1C;
  s32 unk20;
} S_DmaAssetHdr;  /* asset header: unk14/unk1C/unk20 are self-relative byte offsets */

void func_hd_front_end_801F4E70(s32 arg0) {
  S_DmaAssetHdr* sp34;
  u8* sp30;

  func_hd_code_802A0700();
  switch ((u8) arg0) {                            /* irregular */
    case 0:
      D_hd_front_end_802182C4 = &D_6E8980;
      D_hd_front_end_802182C0 = &D_6EA850 - &D_6E8980;
      break;
    case 1:
      D_hd_front_end_802182C4 = &D_6EA850;
      D_hd_front_end_802182C0 = &D_6EAB90 - &D_6EA850;
      break;
    case 2:
      D_hd_front_end_802182C4 = &D_6EAB90;
      D_hd_front_end_802182C0 = &D_6EC4C0 - &D_6EAB90;
      break;
  }
  InitiateDma(D_hd_front_end_802182C4, D_hd_code_80358070, &D_hd_front_end_802182C0, 0xCU, 0xAU, 1U);
  sp34 = (S_DmaAssetHdr *) D_hd_code_80358070;
  D_hd_code_80358070 = &D_hd_code_80358070[D_hd_front_end_802182C0];
  D_hd_front_end_802182C8 = sp34->unk1C + (u8 *) sp34;
  sp30 = sp34->unk20 + (u8 *) sp34;
  D_hd_front_end_802182CC = sp34->unk14 + (u8 *) sp34;
  func_hd_code_802A08B4(D_hd_front_end_802182C8, sp30);
}

Gfx* func_hd_front_end_801F4FBC(struct Model1* arg0, Gfx* gfx) {
  Gfx* entry = gfx;
  gSPSegment(entry++, 6, D_hd_front_end_802182CC);
  gSPSegment(entry++, 7, &D_hd_front_end_802182D0[D_hd_code_8035805C]);
  gSPPerspNormalize(entry++, D_hd_code_8035807C);
  gSPLookAtX(entry++, &arg0->lookAt);
  gSPLookAtY(entry++, &arg0->lookAt.l[1]);
  gSPMatrix(entry++, &arg0->unk1240, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
  gSPMatrix(entry++, &arg0->projection2, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
  gSPMatrix(entry++, &arg0->unk12C0, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
  gSPMatrix(entry++, &arg0->unk1280, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
  gSPMatrix(entry++, &arg0->unk1300, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
  gSPDisplayList(entry++, D_hd_front_end_802182C8);
  return entry;
}

Gfx* func_hd_front_end_801F51C8(struct Model1* arg0, Gfx* gfx) {
    Gfx* entry = gfx;
    void* sp68;

    gSPPerspNormalize(entry++, D_hd_front_end_80218734);
    gSPLookAt(entry++, &arg0->lookAt);
    gSPMatrix(entry++, &arg0->unk240, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(entry++, &arg0->projection2, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gDPSetEnvColor(entry++, 0, 0, 0, D_hd_code_8036BB20);
    {
        s32 sp4C = *(s32 *) (D_hd_front_end_80218350 + *(s32 *) (D_hd_front_end_80218350 + 0x18) + 4);
        Mtx* sp48 = D_hd_front_end_80218358[D_hd_code_8035805C] + sp4C;

        func_hd_front_end_802021FC(&D_hd_front_end_80218430, D_hd_front_end_80218358[D_hd_code_8035805C], D_hd_front_end_80218358[D_hd_code_8035805C ^ 1]);
        D_hd_front_end_80218730 = D_hd_front_end_80218730 + 3;
        guAlign(sp48, (f32) (D_hd_front_end_80218730 % 360U), 0.0f, 1.0f, 0.0f);
        osWritebackDCache(sp48, 0x40);
    }
    sp68 = D_hd_front_end_80218350 + *(s32 *) (D_hd_front_end_80218350 + 0x14);
    gSPSegment(entry++, 6, sp68);
    gSPSegment(entry++, 7, D_hd_front_end_80218358[D_hd_code_8035805C]);
    gSPMatrix(entry++, &D_hd_front_end_802183F0, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(entry++, &D_hd_front_end_80218370, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPMatrix(entry++, &D_hd_front_end_802183B0, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPDisplayList(entry++, D_hd_front_end_80218360[D_hd_code_8035805C]);
    gSPMatrix(entry++, &D_hd_front_end_802183F0, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(entry++, &D_hd_front_end_80218370, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPMatrix(entry++, &D_hd_front_end_802183B0, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPDisplayList(entry++, D_hd_front_end_80218368[D_hd_code_8035805C]);
    return entry;
}

void func_hd_front_end_801F55D8(void) {
  s32 sp3C;
  struct Model1* sp38;

  func_hd_front_end_80202100(0x96, &D_hd_front_end_80218350, D_hd_front_end_80218358, D_hd_front_end_80218360);
  guTranslate(&D_hd_front_end_80218370, 150.0f, -45.0f, 0.0f);
  guScale(&D_hd_front_end_802183B0, 1.5f, 1.5f, 1.5f);
  func_hd_front_end_80202270(D_hd_front_end_80218350, D_hd_front_end_80218358, &D_hd_front_end_80218430);
  func_hd_front_end_802022EC(&D_hd_front_end_80218430, 1, 0, 0, 0.0f, 2, 0);
  func_hd_front_end_802022EC(&D_hd_front_end_80218430, 2, 0, 0, 0.0f, 1, 1);
  guAlign(&D_hd_front_end_802183F0, 20.0f, 1.0f, 0.0f, 0.0f);
  for (sp3C = 0; sp3C < 2; sp3C++) {
    sp38 = &D_hd_code_803156F8[sp3C];
    guPerspective(&sp38->unk240, &D_hd_front_end_80218734, 45.0f, 1.3333334f, 40.0f, 4000.0f, 1.0f);
    guLookAtReflect(&sp38->projection2, &sp38->lookAt, 0.0f, 1.0f, 400.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  }
}
