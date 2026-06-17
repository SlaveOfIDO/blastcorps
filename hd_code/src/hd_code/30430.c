#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"
#include "macros.h"

// Proposed file name: fade.c (the original name - the assert in
// func_hd_code_80275270 references "fade.c")
//
// This file is the screen fade system: fading to black before a game state
// transition (the new state is applied once fully black) and fading back in
// when a state starts, drawn as a full-screen black rectangle.

extern u16 D_8036C770; // message window id hidden during the fade, restored after fade-in; proposed name: fadeSavedWindow
extern f32 D_8036C774; // fade-out alpha step per frame; proposed name: fadeOutSpeed
u64 D_8036C778; // game state to enter once the fade-out completes (0 = not fading out); proposed name: fadeTargetState
extern s32 D_8036C780; // frame the fade started; proposed name: fadeStartFrame
extern u8 D_8036C784; // current fade overlay alpha; proposed name: fadeAlpha
extern u32 D_hd_code_803156C4;
extern u8 D_hd_code_8035805C;
extern u32 D_hd_code_80358060;
extern u64 D_hd_code_80364A90;
extern u64 D_hd_code_80364A98;
extern s32 levelno;

// <data>
struct S_802FA8B0 D_hd_code_802FA8B0[2] = {
    { { { { { 0x0000, 0x0000, 0xFFF6 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } }, { { { 0x013F, 0x0000, 0xFFF6 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } }, { { { 0x013F, 0x00EF, 0xFFF6 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } }, { { { 0x0000, 0x00EF, 0xFFF6 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } } } },
    { { { { { 0x0000, 0x0000, 0xFFF6 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } }, { { { 0x013F, 0x0000, 0xFFF6 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } }, { { { 0x013F, 0x00EF, 0xFFF6 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } }, { { { 0x0000, 0x00EF, 0xFFF6 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x00, 0x00, 0x00 } } } } }
};
f32 D_hd_code_802FA930 = 8.0f; // fade-in alpha step per frame; proposed name: fadeInSpeed
// </data>

// Per-frame fade update + draw: on frame 0 of certain game states start
// fully black (hiding any open message window for later restore); while
// fading out, ramp the alpha up and apply the pending game state once fully
// black; while fading in, ramp it down and restore the saved window at zero.
// Draws the overlay as a full-screen black rectangle.
// Proposed name: UpdateDrawFade
Gfx* func_hd_code_80274BF0(void* arg0, Gfx* gfx) {
    Gfx* entry;

    entry = gfx;
    if (D_hd_code_80358060 == 0) {
        if ((D_hd_code_80364A90 & 0x4055800100040000) || (((D_hd_code_80364A90 & 0x1801)) && (levelno == 0x32))) {
            D_8036C784 = 0xFF;
            if ((D_hd_code_80364A90 & 0x51800100040000)) {
                D_8036C770 = func_hd_code_8026B10C();
                func_hd_code_8026AF6C(0U);
            }
            D_8036C780 = D_hd_code_803156C4;
        } else {
            D_8036C784 = 0;
        }
    }
    if ((D_8036C778 != 0)) {
        D_8036C784 = MIN(255.0f, ((D_hd_code_803156C4 - D_8036C780) * D_8036C774));
        if (D_8036C784 == 0xFF) {
            D_hd_code_80364A98 = D_8036C778;
            D_8036C778 = 0;
        }
    } else if (D_8036C784 != 0) {
        D_8036C784 = MAX(0.0f, 255.0f - ((D_hd_code_803156C4 - D_8036C780) * D_hd_code_802FA930));
        if (D_8036C784 == 0) {
            func_hd_code_8026AF6C(D_8036C770);
            D_8036C770 = 0;
        }
    }
    if (D_8036C784 != 0) {
        gDPPipeSync(entry++);
        gDPSetRenderMode(entry++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
        gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_OFF);
        gDPSetPrimColor(entry++, 0, 0, 0, 0, 0, D_8036C784);
        gDPSetCycleType(entry++, G_CYC_1CYCLE);
        gDPSetCombineMode(entry++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPFillRectangle(entry++, 0, 0, 319, 239);

        osWritebackDCache(&D_hd_code_802FA8B0[D_hd_code_8035805C], 0x40);
    }
    return entry;
}

// Start a fade-out into game state arg0 over arg2 seconds (255 alpha /
// (arg2 * 60 frames)); most targets also fade the music to silence
// Proposed name: StartFadeTo
void func_hd_code_80275270(u64 arg0, f32 arg2) {
  if ((D_8036C778 != 0)) {
    rmonPrintf(ASSERT_MESSAGE, "!postFadeLoop_done", "fade.c", 0x64);
  }
  if ((D_8036C778 == 0)) {
    D_8036C778 = arg0;
    D_8036C774 = 4.25 / arg2;
    D_8036C780 = D_hd_code_803156C4;
    if (!(arg0 & 0x40000000080004C2) && !(D_hd_code_80364A90 & 0x4000000000040000)) {
      func_hd_code_80261570(0.0f);
    }
  }
}

// Fade out into game state arg0 quickly (0.25 seconds)
// Proposed name: StartFadeToFast
void func_hd_code_80275390(u64 arg0) {
  func_hd_code_80275270(arg0, 0.25f);
}

s32 areWeFading(void) {
  return D_8036C778 != 0 ? 1 : 0;
}

// Return 1 if a message window is saved for restore after the fade
// Proposed name: HasFadeSavedWindow
s32 func_hd_code_802753F8(void) {
  return D_8036C770 != 0 ? 1 : 0;
}

