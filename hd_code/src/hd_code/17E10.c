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

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_8025C878.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_8025CE74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_8025D0B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_8025D184.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_8025D2B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_8025E1E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_8025E2CC.s")

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
            func_hd_code_802609D0();
            func_hd_code_802C1DD0(D_hd_code_802E8F94[levelno].unk0 == 0x20 || D_hd_code_802E8F94[levelno].unk0 == 0x80);
            switch (levelno) {                      /* switch 1; irregular */
            case 49:                                /* switch 1 */
                func_hd_code_80260650(D_80367738, 0x31U, NULL);
                func_hd_code_80261570(0.0f);
                break;
            case 50:                                /* switch 1 */
                D_8036BB1A = -1;
                func_hd_code_8026AF6C(0xA00EU);
                func_hd_code_80261570(0.0f);
                break;
            default:                                /* switch 1 */
                func_hd_code_80260650(D_80367738, 0x31U, NULL);
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
                    func_hd_code_80260650(D_80367738, 0x32U, NULL);
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
                    func_hd_code_80260650(D_80367738, 0x32U, NULL);
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


#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_8025EDF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_8025F044.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_8025F0F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_8026005C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_802600D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_80260148.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_80260210.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_80260300.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_802604FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_80260618.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_80260634.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_80260650.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_802608C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_80260934.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_802609D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_802609F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_80260A10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_80260A30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_80260AB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_80260B24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/17E10/func_hd_code_80260B40.s")
