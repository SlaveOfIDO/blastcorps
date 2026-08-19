#include "common.h"
#include "functions.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"
#include "yoshi.h"

extern u8* copyrightLogo_ROM_START;
extern u8* scientist_ROM_START;
extern u8* D_hd_code_803A6B10;
extern s16 D_hd_code_803A6B14;

// <bss>
u8* D_hd_code_803A6B10;
s16 D_hd_code_803A6B14;
s16 D_hd_code_803A6B16;
s32 D_hd_code_803A6B18;
s32 D_hd_code_803A6B1C;
// </bss>

void func_hd_code_8029A130(void) {
  s32 sp24;

  sp24 = (u32)&scientist_ROM_START - (u32)&copyrightLogo_ROM_START;
  InitiateDma(&copyrightLogo_ROM_START, D_hd_code_80358070, &sp24, 0xCU, 0U, 1U);
  D_hd_code_803A6B10 = D_hd_code_80358070;
  D_hd_code_80358070 += sp24;
  D_hd_code_803A6B14 = 0;
}


Gfx* func_hd_code_8029A1A8(s32 arg0, Gfx* gfx) {
  Gfx* entry = gfx;

  gDPPipeSync(entry++);
  gSPTexture(entry++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
  gDPSetTexturePersp(entry++, G_TP_NONE);
  gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
  gDPSetCombineMode(entry++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

  if ((D_hd_code_803A6B14 + 0x40) >= 0x100) {
    D_hd_code_803A6B14 = 0xFF;
  } else {
    D_hd_code_803A6B14 += 0x40;
  }
  gDPSetPrimColor(entry++, 0, 0, 255, 255, 255, D_hd_code_803A6B14);
  gDPLoadTextureBlock(entry++, D_hd_code_803A6B10, G_IM_FMT_IA, G_IM_SIZ_8b, 256, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
  gSPTextureRectangle(entry++, qu102(32), qu102(208), qu102(288), qu102(224), G_TX_RENDERTILE, 0, 0, qs510(1), qs510(1));
  gDPPipeSync(entry++);
  gDPSetTexturePersp(entry++, G_TP_PERSP);

  return entry;
}

