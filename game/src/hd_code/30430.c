#include "common.h"
#include "functions.h"
#include "hd.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"
#include "yoshi.h"

// <bss>
u16 D_hd_code_8036C770;
f32 D_hd_code_8036C774;
u64 D_hd_code_8036C778;
s32 D_hd_code_8036C780;
u8 D_hd_code_8036C784;
// </bss>

// <data>
struct S_802FA8B0 D_hd_code_802FA8B0[2] = {
  { { { { { 0x0000, 0x0000, 0xFFF6 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } },
      { { { 0x013F, 0x0000, 0xFFF6 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } },
      { { { 0x013F, 0x00EF, 0xFFF6 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } },
      { { { 0x0000, 0x00EF, 0xFFF6 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } } } },
  { { { { { 0x0000, 0x0000, 0xFFF6 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } },
      { { { 0x013F, 0x0000, 0xFFF6 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } },
      { { { 0x013F, 0x00EF, 0xFFF6 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } },
      { { { 0x0000, 0x00EF, 0xFFF6 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } } } }
};
f32 D_hd_code_802FA930 = 8.0f;
// </data>

Gfx* func_hd_code_80274BF0(void* arg0, Gfx* gfx) {
  Gfx* entry;

  entry = gfx;
  if (g_frameCount == 0) {
    if ((g_currentGameState & 0x4055800100040000) || (((g_currentGameState & 0x1801)) && (g_currentLevel == 0x32))) {
      D_hd_code_8036C784 = 0xFF;
      if ((g_currentGameState & 0x51800100040000)) {
        D_hd_code_8036C770 = func_hd_code_8026B10C();
        yoshiShow(0U);
      }
      D_hd_code_8036C780 = D_hd_code_803156C4;
    } else {
      D_hd_code_8036C784 = 0;
    }
  }
  if ((D_hd_code_8036C778 != 0)) {
    D_hd_code_8036C784 = MIN(255.0f, ((D_hd_code_803156C4 - D_hd_code_8036C780) * D_hd_code_8036C774));
    if (D_hd_code_8036C784 == 0xFF) {
      g_nextGameState = D_hd_code_8036C778;
      D_hd_code_8036C778 = 0;
    }
  } else if (D_hd_code_8036C784 != 0) {
    D_hd_code_8036C784 = MAX(0.0f, 255.0f - ((D_hd_code_803156C4 - D_hd_code_8036C780) * D_hd_code_802FA930));
    if (D_hd_code_8036C784 == 0) {
      yoshiShow(D_hd_code_8036C770);
      D_hd_code_8036C770 = 0;
    }
  }
  if (D_hd_code_8036C784 != 0) {
    gDPPipeSync(entry++);
    gDPSetRenderMode(entry++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
    gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_OFF);
    gDPSetPrimColor(entry++, 0, 0, 0, 0, 0, D_hd_code_8036C784);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    gDPSetCombineMode(entry++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPFillRectangle(entry++, 0, 0, 319, 239);

    osWritebackDCache(&D_hd_code_802FA8B0[D_hd_code_8035805C], 0x40);
  }
  return entry;
}

void fadeTo(u64 targetGameState, f32 duration) {
  if ((D_hd_code_8036C778 != 0)) {
    rmonPrintf(ASSERT_MESSAGE, "!postFadeLoop_done", "fade.c", 0x64);
  }
  if ((D_hd_code_8036C778 == 0)) {
    D_hd_code_8036C778 = targetGameState;
    D_hd_code_8036C774 = 4.25 / duration;
    D_hd_code_8036C780 = D_hd_code_803156C4;
    if (!(targetGameState & 0x40000000080004C2) && !(g_currentGameState & 0x4000000000040000)) {
      func_hd_code_80261570(0.0f);
    }
  }
}

void fadeToFast(u64 targetGameState) {
  fadeTo(targetGameState, 0.25f);
}

s32 areWeFading(void) {
  return D_hd_code_8036C778 != 0 ? 1 : 0;
}

s32 func_hd_code_802753F8(void) {
  return D_hd_code_8036C770 != 0 ? 1 : 0;
}
