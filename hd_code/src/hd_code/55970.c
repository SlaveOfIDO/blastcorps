#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"
#include "macros.h"
#include "yoshi.h"

extern u8* D_48FA70;
extern u8* D_48FE90;
extern u8* D_803A6B10;
extern s16 D_803A6B14;

void func_hd_code_8029A130(void) {
  s32 sp24;

  sp24 = (u32)&D_48FE90 - (u32)&D_48FA70;
  InitiateDma(&D_48FA70, D_hd_code_80358070, &sp24, 0xCU, 0U, 1U);
  D_803A6B10 = D_hd_code_80358070;
  D_hd_code_80358070 += sp24;
  D_803A6B14 = 0;
}


Gfx* func_hd_code_8029A1A8(s32 arg0, Gfx* gfx) {
  Gfx* entry = gfx;

  gDPPipeSync(entry++);
  gSPTexture(entry++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
  gDPSetTexturePersp(entry++, G_TP_NONE);
  gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
  gDPSetCombineMode(entry++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

  if ((D_803A6B14 + 0x40) >= 0x100) {
    D_803A6B14 = 0xFF;
  } else {
    D_803A6B14 += 0x40;
  }
  gDPSetPrimColor(entry++, 0, 0, 255, 255, 255, D_803A6B14);
  gDPLoadTextureBlock(entry++, D_803A6B10, G_IM_FMT_IA, G_IM_SIZ_8b, 256, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
  gSPTextureRectangle(entry++, qu102(32), qu102(208), qu102(288), qu102(224), G_TX_RENDERTILE, 0, 0, qs510(1), qs510(1));
  gDPPipeSync(entry++);
  gDPSetTexturePersp(entry++, G_TP_PERSP);

  return entry;
}

