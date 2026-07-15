#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/hd.h"
#include "../hd_code/yoshi.h"
#include "../hd_code/functions.h"
#include "../hd_code/variables.h"
#include "../hd_code/io/controller.h"
#include "structs.h"


void func_hd_code_80262008(u8 arg0, f32 arg1);
s32 func_hd_code_802753F8(void);
void func_hd_code_802862DC(void);
void func_hd_front_end_801E8C40(u8 arg0);
Gfx *func_hd_front_end_801E9718(Gfx *gfx, struct Model1 *arg1, s32 arg2); /* extern */
Gfx* func_hd_front_end_801EAA7C(Gfx*, struct Model1*, s32*); /* extern */
Gfx* func_hd_front_end_801EC770(Gfx*, struct Model1*, s32*); /* extern */
Gfx* func_hd_front_end_801ED800(s32, struct Model1*, u8, s32*); /* extern */
Gfx* func_hd_front_end_801F51C8(struct Model1*, Gfx*); /* extern */
s32 func_hd_front_end_801F73FC();                   /* extern */
void func_hd_front_end_801F803C(void);
Gfx* func_hd_front_end_801F8440(struct Model1*, Gfx*); /* extern */
Gfx* func_hd_front_end_80201364(struct Model1*, Gfx*); /* extern */
extern s32 D_hd_code_80364A64;
extern s8 D_hd_code_80364A71;
extern u8 D_hd_code_80364AE9;
extern u16 D_hd_code_8036BB16;
extern s16 D_hd_code_8036BB1A;
extern s16 D_hd_code_8036BB1E;
extern u8 D_hd_code_8039C541;
extern s8 D_hd_front_end_80210550;
extern s32 D_hd_front_end_80219F58;
extern u64 D_hd_front_end_8021A830;
extern u8 D_hd_front_end_8021AB70;
extern u8 D_hd_front_end_8021AB72[];
extern u16 D_hd_front_end_8021AB74;
extern u16 D_hd_front_end_8021AB76;
extern ALSoundState D_hd_front_end_8021AB7C;
extern u8 D_hd_code_80365060[];
extern OSMesgQueue D_hd_code_80315180;
extern s16 D_hd_code_8036BB20;
extern u8 D_hd_front_end_802154B0;
extern s32 D_hd_code_80358078; // current top-level display list length; proposed name: topLevelDlLen
extern void* D_hd_code_8035806C; // static data segment pointer (segment 1); proposed name: staticSegment

void func_hd_front_end_801FE990(void) {
    s32 spDC;
    Gfx* entry;
    OSMesg spD4;

    if (D_hd_code_80364A90 & 0x80010000000ULL) {
        if (D_hd_front_end_8021AB7C.link.next == NULL) {
            sndPlaySfx((struct ALBankAlt_s*) D_hd_code_80367738, 0x73, &D_hd_front_end_8021AB7C);
        }
        if (D_hd_code_8036BB1C == 2) {
            osRecvMesg(&D_hd_front_end_80219F50, &spD4, 1);
            if (D_hd_front_end_80219F58 != 0) {
                rmonPrintf(ASSERT_MESSAGE, "MQ_IS_EMPTY(&pakToGameMessageQ)", "back_loop.c", 0x3E);
            }
            D_hd_front_end_8021AB70 = !(spD4);
            if (D_hd_code_80364A90 == 0x10000000ULL) {
                if (D_hd_front_end_8021AB70 != 0) {
                    func_hd_front_end_801EA278();
                }
                D_hd_code_80364A98 = 0x8000;
            } else {
                D_hd_code_80364A98 = 0x2000000000;
            }
            sndDeactivate((s32) D_hd_front_end_8021AB7C.link.next);
            func_hd_code_8026AF6C(0x4000);
        }
    }
    if (D_hd_code_8036BB16 != 0) {
        rmonPrintf("yoshiSelection in back_loop is %d %d\n", D_hd_code_8036BB16, func_hd_code_8026F92C(D_hd_code_80364A90));

        switch (D_hd_code_80364A90) {
        case 0x10000ULL:
            if (D_hd_code_8036BB16 == 0xFFFF) {
                D_hd_code_80364A98 = 0x8000000000000000;
                func_hd_front_end_801E8EB8(4, 1);
            } else if ((D_hd_code_802F8BDC[0xA].unk18 - 2) < 4) {
                D_hd_code_80364A98 = 0x02000000;
            } else if (D_hd_front_end_802154B0 == 4) {
                D_hd_front_end_8021AB70 = 0;
                D_hd_code_8039C541 = 1;
                D_hd_code_80364A98 = 0x8000;
            } else {
                D_hd_code_80364A98 = 0x800000;
            }
            break;
        case 0x100000000ULL:
            if ((D_hd_code_8036BB16 != 0xFFFF) && (func_hd_front_end_801F73FC() != 0)) {
                D_hd_front_end_8021AB74 = D_hd_code_8036BB16;
                D_hd_code_80364A98 = 0x4000000000;
            }
            break;
        case 0x400000ULL:
            if (D_hd_code_8036BB16 == 0xFFFF) {
                func_hd_front_end_801E8EB8(4, 1);
                D_hd_code_80364A98 = 0x200000;
            } else {
                playerNumber = D_hd_code_8036BB16 - 2;
                if (playerNumber < 4) {
                    D_hd_code_80364A98 = 0x100000;
                } else {
                    D_hd_code_80364A98 = 0x200000;
                }
            }
            break;
        case 0x80000ULL:
            if (D_hd_code_8036BB16 == 0xC) {
                func_hd_front_end_801EA108(playerNumber, 0, 0);
            }
            func_hd_front_end_801E8EB8(4, 1);
            D_hd_code_80364A98 = 0x800000;
            break;
        case 0x8000000000ULL:
            if (D_hd_code_8036BB16 == 0xC) {
                osSendMesg(&D_hd_front_end_80219EF8, (void*) (((s16) D_hd_front_end_8021AB74 << 0x10) | 5), 1);
            }
            D_hd_code_80364A98 = 0x10000000000;
            break;
        case 0x80ULL:
        case 0x8000000ULL:
            if (D_hd_code_8036BB16 == 0xFFFF) {
                D_hd_code_80364A98 = 0x4000;
            } else {
                spDC = ((D_hd_code_802F8BDC[D_hd_code_8036BB18].unk10 + D_hd_code_802F8BDC[D_hd_code_8036BB18].unkE) - D_hd_code_8036BB16) - 1;
                switch (spDC) {                         /* irregular */
                case 0:
                    D_hd_code_80364A98 = 0x4000;
                    break;
                case 1:
                    D_hd_code_80364A98 = 0x40;
                    break;
                case 2:
                    if (!(D_hd_code_80364AA8 & 0x81)) {
                        if ((D_hd_code_80364AA8 == 2) && (D_hd_code_80364A90 == 0x8000000ULL)) {
                            D_hd_code_8039CA60 = 1;
                        }
                        D_hd_code_80364A98 = 0x20000000;
                    } else {
                        D_hd_code_80364A98 = 0x2000;
                    }
                    break;
                case 3:
                    D_hd_code_80364A98 = 0x40000000000;
                    break;
                }
            }
            break;

        case 0x40000000000ULL:
            if (D_hd_code_8036BB16 == 0xFFFF) {
                playerNumber = D_hd_code_80364AE9;
            }
            if ((playerNumber == D_hd_code_80364AE9) || (playerNumber == D_hd_code_80364AEA) || (D_hd_code_8036BB16 == 0xFFFF)) {
                D_hd_code_80364A98 = D_hd_front_end_8021A830;
            } else {
                D_hd_code_80364A98 = 0x0100000000000000;
            }
            break;
        case 0x4000000000000ULL:
            func_hd_front_end_801E8C40(4);
            D_hd_code_80364A98 = 0x8000000000000;
            break;
        case 0x1000000000000ULL: /* 0x1000000000000, unk4 == 0x10000 */
            func_hd_code_80275390(0x20000000000000ULL);
            break;
        case 0x40000000000000ULL: /* unk4 == 0x400000 */
            if (D_hd_code_8036BB16 == 0xC) {
                func_hd_front_end_801EA108(playerNumber, 0, 1);
            }
            break;
        case 0x100000000000000ULL: /* unk4 == 0x01000000 */
            func_hd_front_end_801E8EB8(4, 1);
            break;
        case 0x4000000000000000ULL: /* unk4 == 0x40000000 */
            if (D_hd_code_8036BB16 == 0xC) {
                func_hd_code_80275270(0x0400000000000000ULL, 0.5f);
            } else {
                func_hd_code_80275270(0x4000ULL, 0.5f);
            }
            break;

        default:
            rmonPrintf("backdrop illegal yoshi selection\n");
            break;
        }

        D_hd_front_end_8021AB76 = D_hd_code_8036BB16;
        D_hd_code_8036BB16 = 0;
    }
    nextdma = 0;
    no_palette_dmas = 0;
    func_hd_code_802A5720();
    func_hd_code_80284E54(D_hd_code_803156F8[D_hd_code_8035805C].dp, D_hd_code_80358078, 1, 1, 0x4D2, 0);
    D_hd_code_8035805C ^= 1;

    entry = D_hd_code_803156F8[D_hd_code_8035805C].dp;
    gSPSegment(entry++, 0, 0x00000000);
    gSPSegment(entry++, 2, osVirtualToPhysical(&D_hd_code_803156F8[D_hd_code_8035805C]));
    gSPSegment(entry++, 1, osVirtualToPhysical(D_hd_code_8035806C));
    gSPDisplayList(entry++, D_1000038);
    gSPDisplayList(entry++, D_1000010);
    // TODO: clip macro
    gMoveWd(entry++, G_MW_CLIP, 0x0004, 0x00000003);
    gMoveWd(entry++, G_MW_CLIP, 0x000c, 0x00000003);
    gMoveWd(entry++, G_MW_CLIP, 0x0014, 0x0000fffd);
    gMoveWd(entry++, G_MW_CLIP, 0x001c, 0x0000fffd);
    gDPSetCycleType(entry++, G_CYC_FILL);
    if (D_hd_code_80364A90 & (0x88000080ULL)) {
        gDPSetDepthImage(entry++, D_hd_code_80358058);
        gDPSetColorImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, D_hd_code_80358058);
        gDPSetFillColor(entry++, 0xfffcfffc);
        gDPFillRectangle(entry++, 220, 110, 300, 160);
    } else if (D_hd_code_80364A90 & (0x40000000ULL)) {
        gDPSetDepthImage(entry++, D_hd_code_80358058);
        gDPSetColorImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, D_hd_code_80358058);
        gDPSetFillColor(entry++, 0xfffcfffc);
        gDPFillRectangle(entry++, 0, 0, 319, 239);
    }
    gDPSetColorImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, D_hd_code_80358050[D_hd_code_8035805C]);
    func_hd_code_80259450();
    entry = func_hd_front_end_80200BE0(entry, &D_hd_code_803156F8[D_hd_code_8035805C], &D_hd_code_80358078);
    gDPPipeSync(entry++);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    if (D_hd_code_80364A90 & 0xC000000000000ULL) {
        entry = func_hd_code_8026BBD0(entry, &D_hd_code_803156F8[D_hd_code_8035805C], &D_hd_code_80358078);
    }
    if (D_hd_code_80364A90 == 0x4000000000000ULL) {
        if (D_hd_code_80358060 == 0) {
            func_hd_code_80262008(0x27, 0);
            func_hd_code_80260EE0(0xF);
        }
        if ((D_hd_code_8036BB1E == 0) && (playerNumber == 4)) {
            playerNumber = D_hd_code_80364AEA;
            func_hd_front_end_801E8DCC(D_hd_code_80364AEA);
            D_hd_code_802F8BDC[0x38].unk8 |= 0x20;
        }
    }
    if (D_hd_code_80364A90 & ((0x818D04001AFB8080ULL))) {
        entry = func_hd_front_end_801E9718(entry, &D_hd_code_803156F8[D_hd_code_8035805C], 0xC2);
    }
    if (D_hd_code_80364A90 & ((0x898C0FE313F78002ULL))) {
        entry = func_hd_code_8025C878(entry, &D_hd_code_803156F8[D_hd_code_8035805C], D_hd_code_8035805C, &D_hd_code_80358078);
    }
    if (D_hd_code_80364A90 & 0x410000ULL) {
        u8 sp7F = playerNumber;
        playerNumber = D_hd_code_802F8BDC[0xA].unk18 - 2;
        if (playerNumber != sp7F) {
            if (sp7F == 4) {
                func_hd_front_end_801E8EB8(playerNumber, 0);
            } else {
                func_hd_front_end_801E8EB8(playerNumber, 1);
            }
        }
    }
    func_hd_code_8028A3E4();
    if (D_hd_code_80364A90 & (0x40000000ULL)) {
        entry = func_hd_front_end_801ED800(entry, &D_hd_code_803156F8[D_hd_code_8035805C], D_hd_code_8035805C, &D_hd_code_80358078);
    }
    if (D_hd_code_80364A90 == 0x1000000000000ULL) {
        entry = func_hd_front_end_80201364(D_hd_code_803156F8, entry);
    }
    entry = func_hd_code_8024C404(entry, &D_hd_code_803156F8[D_hd_code_8035805C], &D_hd_code_80358078);
    if (D_hd_code_80364A90 & (0x88000080ULL)) {
        entry = func_hd_front_end_801EC770(entry, &D_hd_code_803156F8[D_hd_code_8035805C], &D_hd_code_80358078);
        if ((D_hd_code_80364A71 != -1) && (D_hd_code_8036BB1C == 2)) {
            entry = func_hd_front_end_801F51C8(&D_hd_code_803156F8[D_hd_code_8035805C], entry);
            gSPClearGeometryMode(entry++, G_ZBUFFER);
        }
    }
    if (D_hd_code_80364A90 == (0x80000000ULL)) {
        if (D_hd_code_80364A64 != 0) {
            D_hd_code_80364A64 -= 1;
        } else if ((D_hd_code_8036BB1E != 2) && (D_hd_code_8036BB1C == 2)) {
            func_hd_code_8026AF6C(0x4000);
            sndPlaySfx((struct ALBankAlt_s*) D_hd_code_80367738, 0x1C, NULL);
        }
    }
    func_hd_code_8028A470();
    if (D_hd_code_80364A90 == 0x800000000000ULL) {
        func_hd_code_802862DC();
    }
    if ((D_hd_code_80364A90 & (0x88000080ULL)) && ((D_hd_code_803156C4 % 20) >= 6) && (D_hd_code_80364A71 != -1) && (D_hd_code_8036BB1C == 2)) {
        s32 sp74;
        s32 sp70;

        sp74 = 0x118,
        sp70 = 0x8C;
        proutSprintf(D_hd_front_end_8021AB72, "%d", D_hd_code_80364A71);
        func_hd_code_80259CCC(&D_hd_code_803156F8[D_hd_code_8035805C], D_hd_front_end_8021AB72, NULL, 1, 0, sp74, sp70, 0x1A, 0x16, 1, 0, 0, 0, (s32) D_hd_code_8036BB20);
        func_hd_code_80259DC8(&D_hd_code_803156F8[D_hd_code_8035805C], D_hd_front_end_8021AB72, 0, 1, 0, sp74 + 2, sp70 + 2, 0x12, 0x12, 1, 0xFF, 0xFF, 0, (s32) D_hd_code_8036BB20, 0xFF, 0, 0, (s32) D_hd_code_8036BB20);
    }
    if (D_hd_code_80364A90 & 0x40000000000ULL) {
        func_hd_front_end_801F803C();
        entry = func_hd_front_end_801F8440(&D_hd_code_803156F8[D_hd_code_8035805C], entry);
    }
    func_hd_code_80259C24(&entry, &D_hd_code_803156F8[D_hd_code_8035805C]);
    entry = func_hd_code_80274BF0(&D_hd_code_803156F8[D_hd_code_8035805C], entry);
    if (!(D_hd_code_80364A90 & 0xC000000000000ULL)) {
        entry = func_hd_code_8026BBD0(entry, &D_hd_code_803156F8[D_hd_code_8035805C], &D_hd_code_80358078);
    }
    if ((D_hd_code_8036BB1C != 1) && (D_hd_code_8036BB18 == 0xB)) {
        entry = func_hd_front_end_801EAA7C(entry, &D_hd_code_803156F8[D_hd_code_8035805C], &D_hd_code_80358078);
    }
    gDPFullSync(entry++);
    gSPEndDisplayList(entry++);
    D_hd_code_80358078 = (s32) (((s32)entry - (s32)&D_hd_code_803156F8[D_hd_code_8035805C]) - 0x48B0) >> 3;
    for (spDC = 0; spDC < nextdma; spDC++) {
        osRecvMesg(&D_hd_code_80315180, NULL, 1);
    }
    for (spDC = 0; spDC < (nextdma - no_palette_dmas); spDC++) {
        func_hd_code_802A57AC();
    }
    if ((D_hd_code_80364A90 & ((0x81D9836583B28000ULL))) && (D_hd_code_8036BB1C == 1) && (func_hd_code_802753F8() == 0) && (areWeFading() == 0) && (D_hd_code_80364A98 == 0) && (D_hd_code_8036BB1A == -1)) {
        switch (D_hd_code_80364A90) {               /* irregular */
        case 0x20000ULL:
            D_hd_code_80364A98 = 0x40000;
            break;
        case 0x200000ULL:
            D_hd_code_80364A98 = 0x10000;
            break;
        case 0x10000000000ULL:
            D_hd_code_80364A98 = 0x100000000;
            return;
        case 0x100000ULL:
            D_hd_code_80364A98 = 0x80000;
            D_hd_front_end_8020C070[9].unkC = D_hd_front_end_8020C070[playerNumber + 2].unkC;
            D_hd_front_end_8020C070[9].unk10 = NULL;

            D_hd_front_end_8020C070[9].unk6 = D_hd_front_end_8020C070[9].unk8 = 0x14;

            func_hd_code_8026AF6C(0x800C);
            break;
        case 0x4000000000ULL:
            D_hd_code_80364A98 = 0x8000000000;
            D_hd_front_end_8020C070[9].unkC = D_hd_front_end_8020C070[(s16) D_hd_front_end_8021AB74].unkC;
            D_hd_front_end_8020C070[9].unk10 = D_hd_front_end_8020C070[(s16) D_hd_front_end_8021AB74].unk10;
            D_hd_front_end_8020C070[9].unk6 = D_hd_front_end_8020C070[9].unk8 = 0xF;
            func_hd_code_8026AF6C(0x800C);
            return;
         case 0x800000ULL:
            D_hd_code_80364A98 = 0x400000;
            break;
        case 0x2000000ULL:
            D_hd_code_80364AE9 = playerNumber;
            D_hd_code_80364AEA = playerNumber;
            if (D_hd_code_80365060[playerNumber] == 1) {
                func_hd_code_80275390(0x4000ULL);
                return;
            }
            D_hd_code_80364A98 = 0x20000;
            return;
        case 0x8000000000000000ULL:
            func_hd_code_80275390(0x0400000000000000ULL);
            return;
        case 0x1000000ULL:
            osSendMesg(&D_hd_front_end_80219EF8, (void*) ((playerNumber << 0x10) | 7), 1);
            osSendMesg(&D_hd_front_end_80219EF8, (void*) ((playerNumber << 0x10) | 0x15 | 0x01000000), 1);
            func_hd_code_802995F0(4);
            func_hd_code_80275390(0x100000000000ULL);
            return;
        case 0x80000000ULL:
            D_hd_code_80364A98 = 0x40000000;
            return;
        case 0x8000ULL:
            if (D_hd_code_8039C541 != 0) {
                func_hd_code_80275390(0x20000000000000ULL);
                return;
            }
            if (D_hd_front_end_8021AB70 != 0) {
                D_hd_code_80364A98 = 0x10000;
                return;
            }
            D_hd_code_80364A98 = 0x10000000;
            break;
        case 0x2000000000ULL:
            if (D_hd_front_end_8021AB70 != 0) {
                D_hd_code_80364A98 = 0x100000000;
                return;
            }
            D_hd_code_80364A98 = 0x80000000000;
            return;
        case 0x100000000ULL:
        case 0x40000000000000ULL:
            func_hd_code_80275270(0x10ULL, 0.5f);
            return;
        case 0x800000000000ULL:
            func_hd_code_80275270(0x2000000000000ULL, 0.75f);
            func_hd_code_80261570(0.0f);
            return;
        case 0x1000000000000ULL: // Unknown case number. Please check
            func_hd_code_80275270(0x2ULL, 0.5f);
            return;
        case 0x8000000000000ULL:
            playerNumber = D_hd_code_80364AEA;
            func_hd_code_80275270(0x4000ULL, 0.6f);
            return;
        case 0x80000000000000ULL:
            if ((playerNumber == D_hd_code_80364AE9) || (playerNumber == D_hd_code_80364AEA)) {
                D_hd_code_80364A98 = D_hd_front_end_8021A830;
                return;
            }
            D_hd_code_80364A98 = 0x0100000000000000;
            return;
        case 0x100000000000000ULL:
            if ((s16) D_hd_front_end_8021AB76 != 0xC) {
                D_hd_code_80364A98 = 0x0200000000000000;
                return;
            }
            func_hd_code_80275390(D_hd_front_end_8021A830); /* see note */
            return;
        default:
            rmonPrintf("illegal yoshi wait game mode %d\n", func_hd_code_8026F92C(D_hd_code_80364A90));
            break;
        }
    }
}


