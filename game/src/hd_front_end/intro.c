#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/hd.h"
#include "../hd_code/yoshi.h"
#include "../hd_code/functions.h"
#include "../hd_code/variables.h"
#include "intro.h"

void func_hd_front_end_801F4E70(s32);  /* extern */
Gfx* func_hd_front_end_801F4FBC(struct Model1 *, s32);

extern u8 nink_ROM_START[];
extern u8 nink_ROM_END[];
extern u8 _64k_ROM_START[];
extern u8 _64k_ROM_END[];
extern u8 copyrightLogo_ROM_START[];
extern s32 D_hd_code_80358078; // current top-level display list length; proposed name: topLevelDlLen
extern void* D_hd_code_8035806C; // static data segment pointer (segment 1); proposed name: staticSegment
extern Mtx  D_hd_front_end_802182D0[];

// <bss>
u16 g_introRotation;
u16 D_hd_front_end_802159D2;
u8 *g_textureNink;
u8 *g_texture64;
u16 g_introMode;
s16 D_hd_front_end_802159DE;
f32 g_introZoom;
f32 g_rotationSpeed;
s32 D_hd_front_end_802159E8;
s32 D_hd_front_end_802159EC;
// </bss>

void introInitialize(s32 introMode) {
  s32 assetNinkSize = (u32)nink_ROM_END - (u32)nink_ROM_START,
      asset64kSize = (u32)_64k_ROM_END - (u32)_64k_ROM_START;

  func_hd_front_end_801F4E70(introMode);
  if (introMode == 2) {
    g_introRotation = 90;
  } else {
    g_introRotation = 0;
  }
  INITIATE_DMA(nink_ROM_START, g_heap, &assetNinkSize, 0xCU, 0U, 1U);
  g_textureNink = g_heap;
  g_heap += assetNinkSize;

  INITIATE_DMA(_64k_ROM_START, g_heap, &asset64kSize, 0xCU, 0U, 1U);
  g_texture64 = g_heap;
  g_heap += asset64kSize;

  g_introMode = introMode;
  g_introZoom = 0.0f;
  g_rotationSpeed = 3.0f;
}

void introRender(void) {
    struct Model1* sp12C;
    Gfx* entry;
    s32 sp124;
    s32 sp120;
    s32 sp11C;
    s16 sp11A;


    sp12C = &D_hd_code_803156F8[D_hd_code_8035805C ^ 1];
    entry = sp12C->dp;
    controllerUpdateInput();
    gfxSubmitTask(D_hd_code_803156F8[D_hd_code_8035805C].dp, D_hd_code_80358078, 1U, 1, 0x4D2, 0);
    D_hd_code_8035805C ^= 1;


    gSPSegment(entry++, 0x00, 0x00000000);
    gSPSegment(entry++, 0x02, osVirtualToPhysical(sp12C));
    gSPSegment(entry++, 0x01, osVirtualToPhysical(D_hd_code_8035806C));
    gSPDisplayList(entry++, (u32) D_1000038);
    gSPDisplayList(entry++, (u32) D_1000010);
    gDPSetCycleType(entry++, G_CYC_FILL);
    gDPSetDepthImage(entry++, D_hd_code_80358058);
    gDPSetColorImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, D_hd_code_80358058);
    gDPSetFillColor(entry++, 0xFFFCFFFC);
    gDPFillRectangle(entry++, 0, 0, 319, 239);
    gDPSetColorImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, D_hd_code_80358050[D_hd_code_8035805C]);
    gDPPipeSync(entry++);


    if (g_introMode == 1) {
        if (g_frameCount * 185 / 20 > 185) {
            sp11A = 185;
        } else {
            sp11A = (s16) (g_frameCount * 185 / 20);
        }
    } else {
        sp11A = 0;
    }

    gDPSetFillColor(entry++, (GPACK_RGBA5551(sp11A, sp11A, sp11A, 1) << 16) | GPACK_RGBA5551(sp11A, sp11A, sp11A, 1));
    gDPFillRectangle(entry++, 0, 0, 319, 239);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);

    func_hd_code_8028A3E4();
    if (g_frameCount == 0xFA) {
        if (g_currentGameState == 0x10) {
            g_nextGameState = 0x20;
        } else {
            g_nextGameState = 0x0400000000000000;
            if (D_hd_code_802FA268 != 0) {
                sndPlaySfx(D_hd_code_80367738, 0x68, NULL);
            }
        }
    }
    if (g_frameCount < 2U) {
        guPerspective(&sp12C->unk1240, &D_hd_code_8035807C, 45.0f, 1.3333334f, 40.0f, 8000.0f, 0.25f);
        if (g_introMode == 1) {
            guTranslate(&sp12C->unk1280, 0.0f, -130.0f, 0.0f);
            guAlign(&sp12C->unk12C0, 35.0f, 0.1f, 0.0f, 0.0f);
        } else {
            guTranslate(&sp12C->unk1280, 0.0f, 0.0f, 0.0f);
            guAlign(&sp12C->unk12C0, -10.0f, 0.1f, 0.0f, 0.0f);
        }
    }
    if (g_frameCount >= 0x14U) {
        if (g_frameCount == 0x14 && g_introMode == 1) {
            sndPlaySfx(D_hd_code_80367738, 0xBA, NULL);
        } else if (g_frameCount == 0x14 && g_introMode == 2) {
            sndPlaySfx(D_hd_code_80367738, 0xBD, NULL);
        }
        if (g_frameCount < 0x50U) {
            g_introZoom = ((0x50 - g_frameCount) * 7600.0 / 60.0 + 400.0);
        }
        if (g_frameCount == 0x4B && g_introMode == 2) {
            sndPlaySfx(D_hd_code_80367738, 0xB8, NULL);
        } else if (g_frameCount == 0x4B && g_introMode == 1) {
            sndPlaySfx(D_hd_code_80367738, 0xBB, NULL);
        }
        guLookAtReflect(&sp12C->projection2, &sp12C->lookAt, 1.0f, 0.0f, g_introZoom, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        g_introRotation =  (u32) ((f32) g_introRotation + g_rotationSpeed);
        guAlign(&D_hd_front_end_802182D0[D_hd_code_8035805C], (f32) ((s32) g_introRotation % 360), 0.0f, 1.0f, 0.0f);
        guScale(&sp12C->unk1300, 1.5f, 1.5f, 1.5f);
#ifdef TARGET_PORT
        // Requested diagnostic (docs/PORT_PLAN.md "Phase 5" - the Nintendo
        // logo 3D model itself still not appearing): this "scale" isn't a
        // literal guScale(0..1) - the grow-in effect is a camera dolly,
        // guLookAtReflect's zEye (D_hd_front_end_802159E0) shrinking from
        // 8000 down to 400 over frame counter (D_hd_code_80358060) 0x14-0x50,
        // combined with the Y-axis rotation angle (D_hd_front_end_802159D0,
        // via guAlign just above). Logging both plus the frame counter
        // driving them every frame this branch runs, to see whether zEye
        // is actually reaching a sane, decreasing value or getting stuck.
        rmonPrintf("[port] nink logo: frame=%d zEye=%f rotY=%d\n", (int)g_frameCount,
                   (double)g_introZoom, (int)((s32)(g_introRotation) % 360));
#endif

        gDPSetRenderMode(entry++, G_RM_AA_ZB_OPA_INTER, G_RM_NOOP2);

        entry = func_hd_front_end_801F4FBC(sp12C, (s32) entry);
    }
    if (g_frameCount > 80 && g_introMode == INTRO_MODE_NINTENDO) {
        gDPPipeSync(entry++);
        gSPTexture(entry++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
        gDPSetTexturePersp(entry++, G_TP_NONE);
        gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(entry++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(entry++, 0, 0, 0x28, 0x00, 0xFF, MIN((g_frameCount * 6) - 0x1E0, 0xFF));

        sp120 = 26,
        sp11C = 42;
        for(sp124 = 0; sp124 < 0x100; sp124+=0x20) {
            gDPSetTextureImage(entry++, G_IM_FMT_IA, G_IM_SIZ_8b, 256, g_textureNink);
            gDPSetTile(entry++, G_IM_FMT_IA, G_IM_SIZ_8b, (sp124 - sp124 + 0x27) >> 3, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
            gDPLoadSync(entry++);
            gDPLoadTile(entry++, G_TX_LOADTILE, sp124 * 4, 0, (sp124 + 0x1F) << 2, qu102(31));
            gDPPipeSync(entry++);
            gDPSetTile(entry++, G_IM_FMT_IA, G_IM_SIZ_8b, (sp124 - sp124 + 0x27 >> 3), 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
            gDPSetTileSize(entry++, G_TX_RENDERTILE, sp124 * 4, 0, (sp124 + 0x1F) << 2, qu102(31));
            gSPTextureRectangle(entry++,
                                (sp124 + sp120) << 2,
                                sp11C << 2,
                                (sp124 + sp120 + 0x20) << 2,
                                (sp11C + 0x20) << 2,
                                G_TX_RENDERTILE,
                                (sp124 << 5),
                                0,
                                qs510(1), qs510(1));
        }


        gDPPipeSync(entry++);
        gDPSetPrimColor(entry++, 0, 0, 0xFF, 0x00, 0x28, MIN((g_frameCount * 4) - 0x140, 0xFF));
        gDPSetTextureImage(entry++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, (u32) g_texture64);
        gDPSetTile(entry++, G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
        gDPLoadSync(entry++);
        gDPLoadBlock(entry++, G_TX_LOADTILE, 0, 0, 479, 410);
        gDPPipeSync(entry++);
        gDPSetTile(entry++, G_IM_FMT_IA, G_IM_SIZ_8b, 5, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
        gDPSetTileSize(entry++, G_TX_RENDERTILE, 0, 0, qu102(39), qu102(23));
        gSPTextureRectangle(entry++, qu102(256), qu102(20), qu102(296), qu102(44), G_TX_RENDERTILE, 0, 0, qs510(1), qs510(1));
        gDPSetTexturePersp(entry++, G_TP_PERSP);

    }
    if (g_frameCount > 220) {
        gDPPipeSync(entry++);
        gDPSetCycleType(entry++, G_CYC_1CYCLE);
        gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(entry++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetPrimColor(entry++, 0, 0, 0, 0, 0, (g_frameCount * 0xFF + 0xFFFF24DC)/ 30U);
        gDPFillRectangle(entry++, 0, 0, 319, 239);
    }
    gDPFullSync(entry++);
    gSPEndDisplayList(entry++);

    D_hd_code_80358078 = (s32) ((u32)entry - (u32)sp12C - 0x48B0) >> 3;
}
