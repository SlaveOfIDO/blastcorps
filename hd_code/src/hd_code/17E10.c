#include "common.h"
#include "structs.h"
#include "variables.h"
#include "functions.h"
#include <PR/gbi.h>
#include <PR/mbi.h>

void func_hd_code_8025C5D0(void) {
    switch (D_hd_code_802E8BEC) {
    case 0:
        if ((D_hd_code_80364A90 == 2)) {
            if (D_hd_code_80358060 == 0x96) {
                func_hd_code_8026AF6C(0x803EU);
            }
            if (D_hd_code_80358060 == 0x190) {
                func_hd_code_8026AF6C(0x8025U);
            }
            if (D_hd_code_80358060 == 0x2BC) {
                func_hd_code_8026AF6C(0x8026U);
            }
        } else {
            if (D_hd_code_80358060 == 0x64) {
                func_hd_code_8026AF6C(0x8027U);
            }
            if (D_hd_code_80358060 == 0x12C) {
                func_hd_code_8026AF6C(0x8028U);
            }
            if (D_hd_code_80358060 == 0x1F4) {
                func_hd_code_8026AF6C(0x8029U);
            }
            if (D_hd_code_80358060 == 0x2BC) {
                func_hd_code_8026AF6C(0x802AU);
            }
        }
        break;
    case 1:
        if (D_hd_code_80358060 == 0xB4) {
            func_hd_code_8026AF6C(0x802BU);
        }
        if (D_hd_code_80358060 == 0x1D6) {
            func_hd_code_8026AF6C(0x802CU);
        }
        break;
    case 2:
        if (D_hd_code_80358060 == 0xB4) {
            func_hd_code_8026AF6C(0x802DU);
        }
        break;
    case 3:
        if (D_hd_code_80358060 == 0xB4) {
            func_hd_code_8026AF6C(0x802EU);
        }
        break;
    case 4:
        if (D_hd_code_80358060 == 0xB4) {
            func_hd_code_8026AF6C(0x802FU);
        }
        break;
    case 5:
        if (D_hd_code_80358060 == 0xB4) {
            func_hd_code_8026AF6C(0x8030U);
        }
        break;
    case 6:
        if (D_hd_code_80358060 == 0xB4) {
            func_hd_code_8026AF6C(0x8031U);
        }
        if (D_hd_code_80358060 == 0x1D6) {
            func_hd_code_8026AF6C(0x8032U);
        }
        break;
    case 7:
        if (D_hd_code_80358060 == 0xB4) {
            func_hd_code_8026AF6C(0x8033U);
        }
        break;
    case 8:
        if (D_hd_code_80358060 == 0xB4) {
            func_hd_code_8026AF6C(0x8034U);
        }
        break;
    }
    if (D_hd_code_80358060 == 0x82) {
        D_80366A18 = 1;
    }
}

s32 func_hd_code_8025C878(Gfx* arg0, void* arg1, u8 arg2, s32* arg3) {
    s32 sp6C;
    u32 sp68;
    Gfx* entry;
    s32 sp60;

    sp68 = D_803156C4;
    entry = arg0;
    if ((D_hd_code_802E8BF0 != 0) && D_hd_code_80364A90 & 2) {
        if (arg2 != 0) {
            sp6C = D_80366BA4;
        } else {
            sp6C = D_80366BA4 + 0x3C0;
        }
        D_80366BA8 = 0;
        if (D_hd_code_80358060 == 0) {
            D_80366A10 = 0;
            D_80366A11 = 0;
        }
        if (D_hd_code_80358060 > D_80366A04) {
            if (sp68 < (u32) (D_80366BBC + 0x78)) {
                gDPPipeSync(entry++);
                gSPMatrix(entry++, &D_2000000.mtx1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
                gSPMatrix(entry++, &D_2000000.modelview, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gDPSetRenderMode(entry++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
                gDPSetCombineMode(entry++, G_CC_SHADE, G_CC_SHADE);
                gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
                gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_OFF);
                gSPVertex(entry++, (u32)&D_hd_code_802FA8B0[arg2] + 0x80000000, 4, 0);
                gSP1Triangle(entry++, 0, 1, 2, 0);
                gSP1Triangle(entry++, 0, 2, 3, 0);

                sp60 = 0;
                do {
                    D_hd_code_802FA8B0[arg2].v[sp60].v.cn[0] = 0;
                    D_hd_code_802FA8B0[arg2].v[sp60].v.cn[1] = 0;
                    D_hd_code_802FA8B0[arg2].v[sp60].v.cn[2] = 0;
                    D_hd_code_802FA8B0[arg2].v[sp60].v.cn[3] = (sp68 - D_80366BBC) * 2.125;
                } while (++sp60 < 4);
                func_hd_code_8025E1E0(&entry);
            } else {
                gDPPipeSync(entry++);
                gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
                gDPSetRenderMode(entry++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
                gDPSetCycleType(entry++, G_CYC_FILL);
                gDPSetFillColor(entry++, 0x00010001);
                gDPFillRectangle(entry++, 0, 0, 319, 239);
                gDPPipeSync(entry++);
                gDPSetCycleType(entry++, G_CYC_1CYCLE);
                func_hd_code_8025E1E0(&entry);
            }
        } else {
            if (D_80366A04 == D_hd_code_80358060) {
                D_80366BBC = sp68;
            }
            func_hd_code_8025E1E0(&entry);
        }
    } else {
        entry = func_hd_code_8025D2B4(entry, arg1, arg3);
    }
    *arg3 += (s32) (entry - arg0);
    return entry;
}

void func_hd_code_8025CE74(void) {
  D_80366BA0 = (struct S_802FA8B0*)D_80358070;
  D_80358070 += 0x40;
  D_80366BA0->v[0].v.ob[0] = 0;
  D_80366BA0->v[0].v.ob[1] = 0;
  D_80366BA0->v[0].v.ob[2] = 0;
  D_80366BA0->v[0].v.flag = 0;
  D_80366BA0->v[0].v.tc[0] = 0;
  D_80366BA0->v[0].v.tc[1] = 0x9E0;
  D_80366BA0->v[0].v.cn[0] = 0;
  D_80366BA0->v[0].v.cn[1] = 0;
  D_80366BA0->v[0].v.cn[2] = 0;
  D_80366BA0->v[0].v.cn[3] = 0;

  D_80366BA0->v[1].v.ob[0] = 0x14;
  D_80366BA0->v[1].v.ob[1] = 0;
  D_80366BA0->v[1].v.ob[2] = 0;
  D_80366BA0->v[1].v.flag  = 0;
  D_80366BA0->v[1].v.tc[0] = 0x280;
  D_80366BA0->v[1].v.tc[1] = 0x9E0;
  D_80366BA0->v[1].v.cn[0] = 0;
  D_80366BA0->v[1].v.cn[1] = 0;
  D_80366BA0->v[1].v.cn[2] = 0;
  D_80366BA0->v[1].v.cn[3] = 0;

  D_80366BA0->v[2].v.ob[0] = 0x14;
  D_80366BA0->v[2].v.ob[1] = 0x4F;
  D_80366BA0->v[2].v.ob[2] = 0;
  D_80366BA0->v[2].v.flag  = 0;
  D_80366BA0->v[2].v.tc[0] = 0x280;
  D_80366BA0->v[2].v.tc[1] = 0;
  D_80366BA0->v[2].v.cn[0] = 0;
  D_80366BA0->v[2].v.cn[1] = 0;
  D_80366BA0->v[2].v.cn[2] = 0;
  D_80366BA0->v[2].v.cn[3] = 0;

  D_80366BA0->v[3].v.ob[0] = 0;
  D_80366BA0->v[3].v.ob[1] = 0x4F;
  D_80366BA0->v[3].v.ob[2] = 0;
  D_80366BA0->v[3].v.flag  = 0;
  D_80366BA0->v[3].v.tc[0] = 0;
  D_80366BA0->v[3].v.tc[1] = 0;
  D_80366BA0->v[3].v.cn[0] = 0;
  D_80366BA0->v[3].v.cn[1] = 0;
  D_80366BA0->v[3].v.cn[2] = 0;
  D_80366BA0->v[3].v.cn[3] = 0;

  D_80366BA4 = (s32) D_80358070;
  D_80358070 += 0x780;
}

void func_hd_code_8025D0B0(u8 arg0) {
  s32* sp34;
  s32 sp30;

  switch(arg0) {
    case 1:
      sp34 = &D_489E70; // titlepicture_usa
      sp30 = (s32)&D_48F5A0 - (s32)&D_489E70;
      break;
    case 0:
      sp34 = &D_487050; // titlelogo_usa
      sp30 = (s32)&D_489E70 - (s32)&D_487050;
      break;
  }

  InitiateDma(sp34, D_80358070, &sp30, 0xCU, 0, 1);
  D_80366BB0[arg0] = (s32) D_80358070 & 0x1FFFFFFF;
  D_80358070 = &D_80358070[sp30];
}

void func_hd_code_8025D184(void) {
  if ((D_80364A98 & 2)) {
    func_hd_code_8025D0B0(1);
    func_hd_code_8025D0B0(0);
    D_80366A16 = 0xFF;
    D_80366A12 = 0;
    D_80366A00 = 0xA5;
    D_80366A02 = 0xD;
    return;
  }
  if ((D_80364A98 & 0x40000)) {
    D_80366A16 = 0;
    D_80366A12 = 4;
    D_80366A02 = 0x2A;
    return;
  }
  if ((D_80364A98 & 0x10000)) {
    D_80366A16 = 0;
    D_80366A12 = 3;
    return;
  }
  func_hd_code_8025D0B0(1);
  func_hd_code_8025D0B0(0);
  D_80366A12 = 3;
  D_80366A14 = 0;
  D_80366A00 = 0x10;
}

s32 func_hd_code_8025D2B4(Gfx* arg0, void* arg1, s32* arg2) {
    Gfx* entry;
    s32 spC0;
    s32 spBC;
    s32 spB8;
    s16 spB6;
    entry = arg0;
    if ((D_hd_code_80364A90 & 0x08040E2110418002)) {
        D_80366A14 = D_80366A14 + 10;
        if (D_80366A14 >= 0x100) {
            D_80366A14 = 0xFF;
        }
    } else if ((D_hd_code_80364A90 & 0x0188004203160000)) {
        D_80366A14 = D_80366A14 - 10;
        if (D_80366A14 <= 0) {
            D_80366A14 = 0;
        }
    }
    switch (D_80366A12) {                           /* irregular */
    case 0:
        if (D_hd_code_80358060 == 0x3C) {
            D_80366A12 = 1;
        }
        break;
    case 1:
        D_80366A16 = D_80366A16 - 8;
        if (D_80366A16 < 0) {
            D_80366A16 = 0;
            D_80366A12 = 2;
        }
        break;
    case 2:
        D_80366A00 = D_80366A00 - 0xA;
        if (D_80366A00 < 0x11) {
            D_80366A00 = 0x10;
            D_80366A12 = 3;
        }
        break;
    case 4:
        if (D_8036BB1C == 2) {
            if ((D_80366A16 + 4) >= 0x81) {
                D_80366A16 = 0x80;
            } else {
                D_80366A16 += 4;
            }
        } else if ((D_hd_code_80364A90 == 0x200000)) {
            if ((D_80366A16 - 6) < 0) {
                D_80366A16 = 0;
            } else {
                D_80366A16 -= 6;
            }
        }
        break;
    }
    gDPPipeSync(entry++);
    gSPTexture(entry++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
    gDPSetTexturePersp(entry++, G_TP_NONE);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineLERP(entry++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);

    if ((D_hd_code_80364A90 == 2) && (D_8036BB1C != 1)) {
        spB6 = D_80366A00 - ((s32) (0xFF - D_8039CAA0) / 4);
        if ((spB6 + 0x3F) == D_80366A00) {
            spB6 = -0x64;
        }
    } else {
        spB6 = D_80366A00;
    }
    switch(D_80366A12) {
        case 0:
        case 1: // 9253
        case 4: {
            gDPSetPrimColor(entry++, 0, 0, 0x00, 0x00, 0x00, D_80366A16);
            spB8 = 0x52;
            for(spC0 = 0; spC0 < 0x96; spC0 += 0x1F) {
                for(spBC = 0; spBC < 0x96; spBC += 0x1F) {
                    gDPSetTextureImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 156, D_80366BB0[1]);
                    gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, ((s32) (((spC0 - spC0) * 2) + 0x47) >> 3), 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
                    gDPLoadSync(entry++);
                    gDPLoadTile(entry++, G_TX_LOADTILE, spC0 << 2, spBC << 2, (spC0 + 0x1F) << 2, (spBC + 0x1F) << 2);
                    gDPPipeSync(entry++);
                    gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, ((s32) (((spC0 - spC0) * 2) + 0x47) >> 3), 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
                    gDPSetTileSize(entry++, 0, spC0 * 4, spBC * 4, (spC0 + 0x1F) << 2, (spBC + 0x1F) << 2);
                    gSPTextureRectangle(entry++,
                                        (spC0 + spB8) << 2,
                                        (spBC + D_80366A02) << 2,
                                        (spC0 + spB8 + 0x1F) << 2,
                                        (spBC + D_80366A02 + 0x1F) << 2,
                                        0,
                                        spC0 << 5,
                                        spBC << 5,
                                        qs510(1),
                                        qs510(1));
                }
            }
            if (D_80366A12 == 4) {
                break;
            }
        }
    default: {
        gDPPipeSync(entry++);
        gDPSetCombineLERP(entry++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor(entry++, 0, 0, 0x00, 0x00, 0x00, ((s16) D_80366A14 / 2));

        spB8 = 0x14;
        for(spC0 = 0; spC0 < 0x110; spC0 += 0x1F) {
            gDPSetTextureImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 280, D_80366BB0[0]); // correct
            gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, (((spC0 - spC0) * 2) + 0x47) >> 3, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
            gDPLoadSync(entry++);
            gDPLoadTile(entry++, G_TX_LOADTILE, spC0 << 2, 0, (spC0 + 0x1F) << 2, qu102(63));
            gDPPipeSync(entry++);
            gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, (((spC0 - spC0) * 2) + 0x47) >> 3, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
            gDPSetTileSize(entry++, G_TX_RENDERTILE, spC0 << 2, 0, (spC0 + 0x1F) << 2, qu102(63));
            gDPPipeSync(entry++);
            gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetCombineLERP(entry++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
            gDPSetPrimColor(entry++, 0, 0, 0, 0, 0, ((s16) D_80366A14 / 2));

            /* (pkt, xl, yl, xh, yh, tile, s, t, dsdx, dtdy) */
            gSPTextureRectangle(entry++, MAX((spC0 + spB8) << 2, 0), MAX((spB6 + 6) << 2, 0), MAX((spC0 + spB8 + 0x1F) << 2, 0), MAX((spB6 + 0x45) << 2, 0), 0, ((spC0 << 5) - (MIN((((spC0 + spB8) << 2) << 10) >> 7, 0))), -MIN((((spB6 + 6) << 2) << 10) >> 7, 0), qs510(1), qs510(1));
            gDPPipeSync(entry++);

            if ((D_80366A14 == 0xFF) && ((D_hd_code_80364A90 & 0xC9FD0FE79BFF80B0))) {
                gDPSetRenderMode(entry++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
            }
            gDPSetCombineLERP(entry++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
            gDPSetPrimColor(entry++, 0, 0, 0, 0, 0, D_80366A14);
            gSPTextureRectangle(entry++, MAX((spC0 + spB8) << 2, 0), MAX((spB6) << 2, 0), MAX((spC0 + spB8 + 0x1F) << 2, 0), MAX((spB6 + 0x3F) << 2, 0), 0, ((spC0 << 5) - (MIN((((spC0 + spB8) << 2) << 10) >> 7, 0))), -MIN((((spB6) << 2) << 10) >> 7, 0), qs510(1), qs510(1));
        }
    }
    }
    gDPPipeSync(entry++);
    gDPSetTexturePersp(entry++, G_TP_PERSP);

    *arg2 += (s32) (entry - arg0);
    return entry;
}

void func_hd_code_8025E1E0(Gfx** arg0) {
  Gfx* entry = *arg0;

  gSPMatrix(entry++, &D_2000000.projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
  gSPMatrix(entry++, &D_2000000.projection2, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
  gSPMatrix(entry++, &D_2000000.modelview, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

  func_hd_code_8024FC2C(&entry, 0U);
  func_hd_code_8024FC2C(&entry, 1U);
  func_hd_code_8024FC2C(&entry, 2U);
  *arg0 = entry;
}

void func_hd_code_8025E2CC(Gfx** arg0, struct Model1* arg1, u8 arg2) {
    Gfx* sp24;

    sp24 = *arg0;
    if ((D_hd_code_803643D7 != 0) && (areWeFading() == 0)) {
        if (D_80366BC0.unk0 == 0) {
            func_hd_code_802C1DD0(D_hd_code_802E8F94[levelno].unk0 == 0x20 || D_hd_code_802E8F94[levelno].unk0 == 0x80);
            D_80366BB8 = 0;
            if ((D_80364AF0[playerNumber].unk18[levelno] > 0 && D_80364AF0[playerNumber].unk18[levelno] < 6)?1:0 != 0) {
                sndDeactivateAllSfxByFlag_11();
                sndDeactivateAllSfxByFlag_3();
                D_80366BC0.unk2 = 5;
                D_80366BC4.unk0 = 0;
                if (D_80364AA8 != 1) {
                    func_hd_code_80260E2C();
                    D_80366BC4.unk0 = 1;
                }
            } else {
                switch (levelno) {                  /* irregular */
                case 40:
                    sndDeactivateAllSfxByFlag_3();
                    func_hd_code_80260DFC();
                    D_80366BC0.unk2 = 0x1E;
                    D_80366BC4.unk0 = 0;
                    break;
                case 50:
                    sndDeactivateAllSfxByFlag_3();
                    func_hd_code_80260EE0(0x25);
                    D_80366BC0.unk2 = 0x23;
                    D_80366BC4.unk0 = 0;
                    break;
                default:
                    sndDeactivateAllSfxByFlag_3();
                    D_80366BC0.unk2 = 5;
                    func_hd_code_80260E2C();
                    D_80366BC4.unk0 = 1;
                    break;
                }
            }
            func_hd_code_8026AF6C(D_80366BC0.unk2 | 0x8000 | 0x2000);
            D_8036BB1A = -1;
            if (D_80366BC0.unk2 == 5) {
                sndPlaySfx(D_80367738, func_hd_code_8026205C(2), NULL);
            }
        }
        D_80366BC0.unk0 = D_hd_code_803643D7;
        if (D_80366BB8 == 0) {
            if ((D_8036BB1C == 8) && (D_8036BB18 == D_80366BC0.unk2)) {
                D_80366BB8 = D_803156C4;
                func_hd_code_80278318();
                func_hd_code_80277EDC(2, 1, 2, func_hd_code_8026205C(3));
            }
        } else if ((func_hd_code_802D4E10(D_80367734) != 0) && ((D_80366BC4.unk0 == 0) || ((u32) (D_803156C4 - D_80367740) < 0x1E1U))) {
            if (D_80366BC4.unk0 == 0) {
                if (D_803156C4 - D_80366BB8 > D_hd_code_802E8CD0[(D_80364AA8 & 0x81)?1:0]) {
                    goto block_32;
                }
            }
        } else {
block_32:
            func_hd_code_80275270(0x08000000, 0x3F400000);
            D_80366BB8 = 0;
            D_80366BC0.unk0 = 0;
        }
    }
    *arg0 = sp24;
}

void func_hd_code_8025E67C(Gfx** arg0, struct Model1* arg1, u8 arg2) {
    Gfx* entry;
    u32 sp60;
    u32 sp5C;
    u32 sp58;
    u32 pad54;
    u32 sp50;

    entry = *arg0;
    sp60 = D_803156C4;
    if (D_hd_code_803643D6 != 0) {
        if (D_803643D8 == 0) {
            sndDeactivateAllSfxByFlag_1();
            func_hd_code_802C1DD0(D_hd_code_802E8F94[levelno].unk0 == 0x20 || D_hd_code_802E8F94[levelno].unk0 == 0x80);
            switch (levelno) {                      /* switch 1; irregular */
            case 49:                                /* switch 1 */
                sndPlaySfx(D_80367738, 0x31U, NULL);
                func_hd_code_80261570(0.0f);
                break;
            case 50:                                /* switch 1 */
                D_8036BB1A = -1;
                func_hd_code_8026AF6C(0xA00EU);
                func_hd_code_80261570(0.0f);
                break;
            default:                                /* switch 1 */
                sndPlaySfx(D_80367738, 0x31U, NULL);
                D_hd_code_802E8BD8 = 1;
                if ((D_8036BB18 != -1) || (func_hd_code_8026B10C() != 0)) {
                    func_hd_code_8026AF6C(0x4000U);
                }
                D_8036BB1A = -1;
                func_hd_code_80261570(0.0f);
                break;
            }
            D_80366BB8 = sp60;
            D_80366BC4.unk1 = 0U;
        }
        sp5C = sp60 - D_80366BB8;
        if (sp5C >= 0xB4U) {
            switch (levelno) {                      /* switch 2; irregular */
            case 49:                                /* switch 2 */
                if (D_80366BC4.unk1 == 0) {
                    sndPlaySfx(D_80367738, 0x32U, NULL);
                    D_80366BC4.unk1 = 1U;
                }
                break;
            case 50:                                /* switch 2 */
                if ((D_8036BB1C == 1) && (areWeFading() == 0)) {
                    if ((((s32)  D_80364AF0[playerNumber].unk18[levelno] > 0) && ((s32) D_80364AF0[playerNumber].unk18[levelno] < 6)?1:0) != 0) {
                        func_hd_code_80275390(0x08000000);
                    } else {
                        func_hd_code_80275390(0x40);
                    }
                }
                break;
            default:                                /* switch 2 */
                if (D_80366BC4.unk1 == 0) {
                    sndPlaySfx(D_80367738, 0x32U, NULL);
                    D_80366BC4.unk1 = 1U;
                }

                gSPMatrix(entry++, &D_2000000.mtx1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
                gSPMatrix(entry++, &D_2000000.modelview, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gDPPipeSync(entry++);
                gDPSetRenderMode(entry++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
                gDPSetCombineMode(entry++, G_CC_SHADE, G_CC_SHADE);
                gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
                gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_OFF);
                gSPVertex(entry++, (s32)&D_hd_code_802FA8B0[arg2] + 0x80000000, 4, 0);
                gSP1Triangle(entry++, 0, 1, 2, 0);
                gSP1Triangle(entry++, 0, 2, 3, 0);
                gDPPipeSync(entry++);

                if (!areWeFading()) {
                    if ((sp60 - D_80366BB8) - 0xB4 < 0x5AU) {
                        sp50 = (u32) (((sp60 - D_80366BB8) - 0xB4) * 2.8333333333333335);
                        for(sp5C = 0; sp5C < 4U; sp5C++) {
                            for(sp58 = 0; sp58 < 4U; sp58++) {
                                *(&D_hd_code_802FA8BC + ((arg2 << 6) + (sp5C * 0x10) + sp58)) = sp50;
                            }
                        }
                    } else if ((u32) ((sp60 - D_80366BB8) - 0x10E) >= 0x2EU) {
                        if ((D_hd_code_80364A90 == 0x100000000000)) {
                            D_80364A98 = 0x200000000000;
                        } else {
                            if ((((s32) D_80364AF0[playerNumber].unk18[levelno] > 0) && ((s32)  D_80364AF0[playerNumber].unk18[levelno] < 6))?1:0 != 0) {
                                func_hd_code_80275390(0x08000000);
                            } else {
                                func_hd_code_80275390(0x40);
                            }
                        }
                    } else {
                        for(sp5C = 0; sp5C < 4U; sp5C++) {
                            for(sp58 = 0; sp58 < 4U; sp58++) {
                                *(&D_hd_code_802FA8BC + ((arg2 << 6) + (sp5C * 0x10) + sp58)) = 0xFF;
                            }
                        }
                    }
                }
                break;
            }
        }
    }
    *arg0 = entry;
}
