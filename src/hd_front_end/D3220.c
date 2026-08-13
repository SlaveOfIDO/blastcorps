#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/hd.h"
#include "../hd_code/yoshi.h"
#include "../hd_code/functions.h"
#include "../hd_code/variables.h"

void func_hd_front_end_801F4E70(s32);  /* extern */
s32 func_hd_front_end_801F4FBC(struct Model1 *, s32);  /* extern */

extern u8 nink_ROM_START[];
extern u8 nink_ROM_END[];
extern u8 _64k_ROM_START[];
extern u8 _64k_ROM_END[];
extern u8 copyrightLogo_ROM_START[];
extern u16 D_hd_front_end_802159D0;
extern u8 *D_hd_front_end_802159D4;
extern u8 *D_hd_front_end_802159D8;
extern s16 D_hd_front_end_802159DC;
extern f32 D_hd_front_end_802159E0;
extern f32 D_hd_front_end_802159E4;
extern s32 D_hd_code_80358078; // current top-level display list length; proposed name: topLevelDlLen
extern void* D_hd_code_8035806C; // static data segment pointer (segment 1); proposed name: staticSegment
extern Mtx  D_hd_front_end_802182D0[];

void func_hd_front_end_801EF380(s32 arg0) {
  s32 assetNinkSize = (u32)nink_ROM_END - (u32)nink_ROM_START,
      asset64kSize = (u32)_64k_ROM_END - (u32)_64k_ROM_START;

  func_hd_front_end_801F4E70(arg0);
  if (arg0 == 2) {
    D_hd_front_end_802159D0 = 0x5A;
  } else {
    D_hd_front_end_802159D0 = 0;
  }
  InitiateDma(nink_ROM_START, D_hd_code_80358070, &assetNinkSize, 0xCU, 0U, 1U);
  D_hd_front_end_802159D4 = D_hd_code_80358070;
  D_hd_code_80358070 += assetNinkSize;
  InitiateDma(_64k_ROM_START, D_hd_code_80358070, &asset64kSize, 0xCU, 0U, 1U);
  D_hd_front_end_802159D8 = D_hd_code_80358070;
  D_hd_code_80358070 += asset64kSize;
  D_hd_front_end_802159DC = arg0;
  D_hd_front_end_802159E0 = 0.0f;
  D_hd_front_end_802159E4 = 3.0f;
}

void func_hd_front_end_801EF4AC(void) {
    struct Model1* sp12C;
    Gfx* entry;
    s32 sp124;
    s32 sp120;
    s32 sp11C;
    s16 sp11A;


    sp12C = &D_hd_code_803156F8[D_hd_code_8035805C ^ 1];
    entry = sp12C->dp;
    func_hd_code_8028A470();
    func_hd_code_80284E54(D_hd_code_803156F8[D_hd_code_8035805C].dp, D_hd_code_80358078, 1U, 1, 0x4D2, 0);
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


    if ((u16) D_hd_front_end_802159DC == 1) {
        if ((u32) ((u32) (D_hd_code_80358060 * 0xB9) / 20U) >= 0xBAU) {
            sp11A = 0xB9;
        } else {
            sp11A = (s16) ((u32) (D_hd_code_80358060 * 0xB9) / 20U);
        }
    } else {
        sp11A = 0;
    }

    gDPSetFillColor(entry++, (GPACK_RGBA5551(sp11A, sp11A, sp11A, 1) << 16) | GPACK_RGBA5551(sp11A, sp11A, sp11A, 1));
    gDPFillRectangle(entry++, 0, 0, 319, 239);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);

    func_hd_code_8028A3E4();
    if (D_hd_code_80358060 == 0xFA) {
        if (D_hd_code_80364A90 == 0x10) {
            D_hd_code_80364A98 = 0x20;
        } else {
            D_hd_code_80364A98 = 0x0400000000000000;
            if (D_hd_code_802FA268 != 0) {
                sndPlaySfx((struct ALBankAlt_s* ) D_hd_code_80367738, 0x68, NULL);
            }
        }
    }
    if ((u32) D_hd_code_80358060 < 2U) {
        guPerspective(&sp12C->unk1240, &D_hd_code_8035807C, 45.0f, 1.3333334f, 40.0f, 8000.0f, 0.25f);
        if ((u16) D_hd_front_end_802159DC == 1) {
            guTranslate(&sp12C->unk1280, 0.0f, -130.0f, 0.0f);
            guAlign(&sp12C->unk12C0, 35.0f, 0.1f, 0.0f, 0.0f);
        } else {
            guTranslate(&sp12C->unk1280, 0.0f, 0.0f, 0.0f);
            guAlign(&sp12C->unk12C0, -10.0f, 0.1f, 0.0f, 0.0f);
        }
    }
    if ((u32) D_hd_code_80358060 >= 0x14U) {
        if ((D_hd_code_80358060 == 0x14) && ((u16) D_hd_front_end_802159DC == 1)) {
            sndPlaySfx((struct ALBankAlt_s* ) D_hd_code_80367738, 0xBA, NULL);
        } else if ((D_hd_code_80358060 == 0x14) && ((u16) D_hd_front_end_802159DC == 2)) {
            sndPlaySfx((struct ALBankAlt_s* ) D_hd_code_80367738, 0xBD, NULL);
        }
        if ((u32) D_hd_code_80358060 < 0x50U) {
            D_hd_front_end_802159E0 = (f32) ((((0x50 - D_hd_code_80358060) * 7600.0) / 60.0) + 400.0);
        }
        if ((D_hd_code_80358060 == 0x4B) && ((u16) D_hd_front_end_802159DC == 2)) {
            sndPlaySfx((struct ALBankAlt_s* ) D_hd_code_80367738, 0xB8, NULL);
        } else if ((D_hd_code_80358060 == 0x4B) && ((u16) D_hd_front_end_802159DC == 1)) {
            sndPlaySfx((struct ALBankAlt_s* ) D_hd_code_80367738, 0xBB, NULL);
        }
        guLookAtReflect(&sp12C->projection2, &sp12C->lookAt, 1.0f, 0.0f, D_hd_front_end_802159E0, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
        D_hd_front_end_802159D0 =  (u32) ((f32) (u16) D_hd_front_end_802159D0 + D_hd_front_end_802159E4);
        guAlign(&D_hd_front_end_802182D0[D_hd_code_8035805C], (f32) ((s32) (D_hd_front_end_802159D0) % 360), 0.0f, 1.0f, 0.0f);
        guScale(&sp12C->unk1300, 1.5f, 1.5f, 1.5f);

        gDPSetRenderMode(entry++, G_RM_AA_ZB_OPA_INTER, G_RM_NOOP2);

        entry = func_hd_front_end_801F4FBC(sp12C, (s32) entry);
    }
    if (((u32) D_hd_code_80358060 >= 0x51U) && ((u16) D_hd_front_end_802159DC == 1)) {
        gDPPipeSync(entry++);
        gSPTexture(entry++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
        gDPSetTexturePersp(entry++, G_TP_NONE);
        gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(entry++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(entry++, 0, 0, 0x28, 0x00, 0xFF, MIN((D_hd_code_80358060 * 6) - 0x1E0, 0xFF));

        sp120 = 0x1A,
        sp11C = 0x2A;
        for(sp124 = 0; sp124 < 0x100; sp124+=0x20) {
            gDPSetTextureImage(entry++, G_IM_FMT_IA, G_IM_SIZ_8b, 256, (u32) D_hd_front_end_802159D4);
            gDPSetTile(entry++, G_IM_FMT_IA, G_IM_SIZ_8b, ((sp124 - sp124) + 0x27) >> 3, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
            gDPLoadSync(entry++);
            gDPLoadTile(entry++, G_TX_LOADTILE, (sp124 * 4), 0, ((sp124 + 0x1F) << 2), qu102(31));
            gDPPipeSync(entry++);
            gDPSetTile(entry++, G_IM_FMT_IA, G_IM_SIZ_8b, ((s32) ((sp124 - sp124) + 0x27) >> 3), 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
            gDPSetTileSize(entry++, G_TX_RENDERTILE, (sp124 * 4), 0, ((sp124 + 0x1F) << 2), qu102(31));
            gSPTextureRectangle(entry++,
                                ((sp124 + sp120) << 2),
                                (sp11C << 2),
                                ((sp124 + sp120 + 0x20) << 2),
                                ((sp11C + 0x20) << 2),
                                G_TX_RENDERTILE,
                                (sp124 << 5),
                                0,
                                qs510(1), qs510(1));

            /*
            spA0->words.w0 = ((((sp124 + sp120 + 0x20) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((sp11C + 0x20) * 4) & 0xFFF);
            spA0->words.w1 = ((((sp124 + sp120) * 4) & 0xFFF) << 0xC) | ((sp11C * 4) & 0xFFF);
            sp9C = entry;
            entry += 8;
            sp9C->words.w0 = 0xB3000000;
            sp9C->words.w1 = ((sp124 << 5) & 0xFFFF) << 0x10;
            sp98 = entry;
            entry += 8;
            sp98->words.w0 = 0xB2000000;
            sp98->words.w1 = 0x04000400;      */
        }


        gDPPipeSync(entry++);
        gDPSetPrimColor(entry++, 0, 0, 0xFF, 0x00, 0x28, MIN((D_hd_code_80358060 * 4) - 0x140, 0xFF));
        gDPSetTextureImage(entry++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, (u32) D_hd_front_end_802159D8);
        gDPSetTile(entry++, G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
        gDPLoadSync(entry++);
        gDPLoadBlock(entry++, G_TX_LOADTILE, 0, 0, 479, 410);
        gDPPipeSync(entry++);
        gDPSetTile(entry++, G_IM_FMT_IA, G_IM_SIZ_8b, 5, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
        gDPSetTileSize(entry++, G_TX_RENDERTILE, 0, 0, qu102(39), qu102(23));
        gSPTextureRectangle(entry++, qu102(256), qu102(20), qu102(296), qu102(44), G_TX_RENDERTILE, 0, 0, qs510(1), qs510(1));
        gDPSetTexturePersp(entry++, G_TP_PERSP);

    }
    if ((u32) D_hd_code_80358060 >= 0xDDU) {
        gDPPipeSync(entry++);
        gDPSetCycleType(entry++, G_CYC_1CYCLE);
        gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(entry++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetPrimColor(entry++, 0, 0, 0, 0, 0, ((u32) ((D_hd_code_80358060 * 0xFF) + 0xFFFF24DC) / 30U));
        gDPFillRectangle(entry++, 0, 0, 319, 239);
    }
    gDPFullSync(entry++);
    gSPEndDisplayList(entry++);

    D_hd_code_80358078 = (s32) (((u32)entry - (u32)sp12C) - 0x48B0) >> 3;
}
