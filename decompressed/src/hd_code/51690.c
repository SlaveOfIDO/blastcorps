#include "common.h"
#include "functions.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"

extern u8* D_hd_code_8039CA90; // wrong type
extern u8* D_hd_code_8039CA94; // wrong type
extern u8* D_hd_code_8039CA98;
extern void* D_hd_code_8039CA9C;
extern s32 D_6A8DA0;
Gfx* func_hd_code_8029700C(Gfx*, s16, s16);         /* extern */

// Proposed file name: controller_display.c
//
// This file draws the on-screen N64 controller graphic that visualizes the
// inputs being played back during the attract-mode demos: the controller
// body (from controllertextures.raw), highlighted buttons (A/B/C/Start/Z/R
// each in their own color when held), the analog stick offset, and the
// Z/R trigger and D-pad textures. The displayed input comes from the
// playback button/stick state (D_hd_code_80370C30/32/33).

// Allocate and DMA the controller display textures from ROM
// (controllertextures.raw) into level memory, carving out the body, stick,
// trigger and D-pad sub-textures
// Proposed name: InitControllerDisplay
void func_hd_code_80295E50(void) {
  s32 sp24;

  D_hd_code_8039CA90 = D_hd_code_80358070;
  D_hd_code_8039CA94 = D_hd_code_80358070 + 0x3200;
  D_hd_code_8039CA98 = D_hd_code_8039CA94 + 0xF0;
  D_hd_code_8039CA9C = D_hd_code_8039CA98 + 0x180;
  sp24 = (u32)&D_6A9F10 - (u32)&D_6A8DA0; // controllertextures.raw
  InitiateDma((u8* ) &D_6A8DA0, D_hd_code_80358070, &sp24, 0xAU, 0U, 1U);
  D_hd_code_80358070 += sp24;
  D_hd_code_8039CAA0 = 0;
  D_hd_code_8039CAA2 = 1;
}

// Draw the controller display at screen (arg2, arg3) with alpha arg4: a drop
// shadow then the body image, the Z/R trigger and D-pad textures when held,
// each pressed face button as a colored overlay (blue A, green B, red Start,
// gray C-buttons), and the analog stick nub offset by the stick position.
// Proposed name: DrawControllerDisplay
Gfx* func_hd_code_80295EFC(s32 arg0, Gfx* gfx, s16 arg2, s16 arg3, u8 arg4) {
    Gfx* entry = gfx;
    s32 sp118;

    gDPPipeSync(entry++);
    gSPTexture(entry++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
    gDPSetTexturePersp(entry++, G_TP_NONE);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_NOOP2);
    gDPSetCombineLERP(entry++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(entry++, 0, 0, 0, 0, 0, arg4 / 2);


    entry = func_hd_code_8029700C(entry, arg2 - 4, arg3 + 4);

    gDPPipeSync(entry++);
    gDPSetCombineLERP(entry++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(entry++, 0, 0, 0, 0, 0, arg4);

    entry = func_hd_code_8029700C(entry, arg2, arg3);
    if (D_hd_code_80370C30 & 0x30) {
        gDPLoadTextureBlock(entry++, D_hd_code_8039CA98, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 6, 0, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_CLAMP, 5, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        if (D_hd_code_80370C30 & 0x10) {
            gSPTextureRectangle(entry++,
                                MAX((arg2 + 0x30) << 2, 0),
                                MAX((arg3 + 8) << 2, 0),
                                MAX((arg2 + 0x4F) << 2, 0),
                                MAX((arg3 + 0xD) << 2, 0),
                                G_TX_RENDERTILE,
                                -MIN((((arg2 + 0x30) << 2) << 0xA) >> 7, 0),
                                -MIN((((arg3 + 8) << 2) << 0xA) >> 7,0),
                                qs510(1),
                                qs510(1)
                               );
        }
        if (D_hd_code_80370C30 & 0x20) {
            gSPTextureRectangle(entry++,
                                MAX((arg2) << 2, 0),
                                MAX((arg3 + 8) << 2, 0),
                                MAX((arg2 + 0x1F ) << 2, 0),
                                MAX((arg3 + 0xD) << 2, 0),
                                G_TX_RENDERTILE,
                                0x400-MIN((((arg2) << 2) << 0xA) >> 7, 0),
                                -MIN((((arg3 + 8) << 2) << 0xA) >> 7,0),
                                qs510(1),
                                qs510(1)
                               );
        }
    }
    if (D_hd_code_80370C30 & 0x2000) {
        gDPLoadTextureBlock(entry++, D_hd_code_8039CA9C, G_IM_FMT_RGBA, G_IM_SIZ_16b, 24, 24, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        gSPTextureRectangle(entry++,
                                MAX((arg2 + 9) << 2, 0),
                                MAX((arg3 + 0x33) << 2, 0),
                                MAX((arg2 + 0x20 ) << 2, 0),
                                MAX((arg3 + 0x4A) << 2, 0),
                                G_TX_RENDERTILE,
                                -MIN((((arg2 + 9) << 2) << 0xA) >> 7, 0),
                                -MIN((((arg3 + 0x33) << 2) << 0xA) >> 7,0),
                                qs510(1),
                                qs510(1)
                               );
    }

    gDPPipeSync(entry++);
    gDPSetCombineMode(entry++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPLoadTextureBlock(entry++, D_hd_code_8039CA94, G_IM_FMT_IA, G_IM_SIZ_16b, 12, 10, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    {
        u8 sp6F;
        u16 sp6C;
        u16 sp6A;

        for(sp118 = 0; sp118 < 16; sp118++) {
            sp6F = 1;
            if (D_hd_code_80370C30 & (1 << sp118)) {
                gDPPipeSync(entry++);

                switch (1 << sp118) {
                case 0x8000:
                    gDPSetPrimColor(entry++, 0, 0, 0x0, 0x0, 0xFF, arg4);
                    sp6C = 0x39,
                    sp6A = 0x1E;
                    break;
                case 0x4000:
                    gDPSetPrimColor(entry++, 0, 0, 0x0, 0xFF, 0, arg4);
                    sp6C = 0x34,
                    sp6A = 0x19;
                    break;
                case 0x1000:
                    gDPSetPrimColor(entry++, 0, 0, 0xFF, 0, 0, arg4);
                    sp6C = 0x23,
                    sp6A = 0x1B;
                    break;
                case 0x200:
                    gDPSetPrimColor(entry++, 0, 0, 0x50, 0x50, 0x50, arg4);
                    sp6C = 4,
                    sp6A = 0x16;
                    break;
                case 0x100:
                    gDPSetPrimColor(entry++, 0, 0, 0x50, 0x50, 0x50, arg4);
                    sp6C = 0x10,
                    sp6A = 0x16;
                    break;
                default:
                    sp6F = 0;
                    break;
                }

                if (sp6F != 0) {
                    gSPTextureRectangle(entry++,
                                    MAX((arg2 + sp6C) << 2, 0),
                                    MAX((arg3 + sp6A) << 2, 0),
                                    MAX((arg2 + sp6C + 0xB ) << 2, 0),
                                    MAX((arg3 + sp6A + 9) << 2, 0),
                                    G_TX_RENDERTILE,
                                    -MIN((((arg2 + sp6C) << 2) << 0xA) >> 7, 0),
                                    -MIN((((arg3 + sp6A) << 2) << 0xA) >> 7,0),
                                    qs510(1),
                                    qs510(1)
                                   );


                }
            }
        }

        gDPPipeSync(entry++);
        gDPSetPrimColor(entry++, 0, 0, 0xDC, 0xDC, 0xDC, arg4);

        gSPTextureRectangle(entry++,
                                    MAX((arg2 + D_hd_code_80370C32 / 18 + 0x23) << 2, 0),
                                    MAX((arg3 - D_hd_code_80370C33 / 18 + 0x28) << 2, 0),
                                    MAX((arg2 + D_hd_code_80370C32 / 18 + 0x2E) << 2, 0),
                                    MAX((arg3 - D_hd_code_80370C33 / 18 + 0x31) << 2, 0),
                                    G_TX_RENDERTILE,
                                    -MIN((((arg2 + D_hd_code_80370C32 / 18 + 0x23) << 2) << 0xA) >> 7, 0),
                                    -MIN((((arg3 - D_hd_code_80370C33 / 18 + 0x28) << 2) << 0xA) >> 7,0),
                                    qs510(1),
                                    qs510(1)
                                   );

        gDPPipeSync(entry++);
        gDPSetTexturePersp(entry++, G_TP_PERSP);

    }



    return entry;
}

// Draw the 80x80 controller body image at (arg1, arg2) in 31-pixel tiles
// (the texture is too big for one TMEM load)
// Proposed name: DrawControllerBody
Gfx* func_hd_code_8029700C(Gfx* arg0, s16 arg1, s16 arg2) {
  s32 sp44;
  s32 sp40;

  for (sp44 = 0; sp44 < 0x50; sp44 += 0x1F) {
    for (sp40 = 0; sp40 < 0x50; sp40 += 0x1F) {
      gDPLoadTextureTile(arg0++,
         /* timg */ D_hd_code_8039CA90,
         /* fmt */ G_IM_FMT_RGBA,
         /* siz */ G_IM_SIZ_16b,
         /* width */ 80,
         /* height */ 0,
         /* uls */ sp44,
         /* ult */ sp40,
         /* lrs */ MIN(0x4F, sp44 + 0x1F),
         /* lrt */ MIN(0x4F, sp40 + 0x1F),
         /* pal */ 0,
         /* cms */ 2,
         /* cmt */ 2,
         /* masks */ 0,
         /* maskt */ 0,
         /* shifts */ 0,
         /* shiftt */ 0
      );

      rare_gSPScisTextureRectangle(arg0++,
          /* xl */ (arg1 + sp44) << 2,
          /* yl */ (arg2 + sp40) << 2,
          /* xh */ (MIN(0x4F, sp44 + 0x1F) + arg1) << 2,
          /* yh */ (MIN(0x4F, sp40 + 0x1F) + arg2) << 2,
          /* tile */ 0,
          /* s */ (sp44 << 5),
          /* t */ (sp40 << 5),
          /* dsdx */ 0x400,
          /* dtdy */ 0x400
      );
    }
  }
  return arg0;
}
