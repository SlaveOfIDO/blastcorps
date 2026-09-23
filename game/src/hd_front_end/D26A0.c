#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/hd.h"
#include "../hd_code/yoshi.h"
#include "../hd_code/functions.h"
#include "../hd_code/variables.h"
#include "../hd_code/stats_perm.h"
#include "structs.h"

u8 func_hd_front_end_801EEDB4(u8, u8, u8);         /* extern */

extern s32 D_hd_code_803649F0;
extern char D_hd_code_8036B9A8[0x20];


extern u16 D_hd_code_80364EF0[][16];
extern u8  D_hd_code_802E8C44[];
extern struct S_80367C04 D_hd_code_802E8F94[];
u32 func_hd_code_802852EC();                          /* extern */
void func_hd_front_end_801E8DCC(u8 arg0);

s32 func_hd_code_80286038(s32);                     /* extern */
void func_hd_code_80295A20(s32);                    /* extern */
u8 func_hd_front_end_801EF2BC(u16 arg0, u8 arg1, u8 arg2);         /* extern */

extern u16 D_hd_code_80364EF0[][16];
extern u8  D_hd_code_802E8C44[];
extern struct S_80367C04 D_hd_code_802E8F94[];
extern struct S_80367BCC D_hd_code_802F49F4[];
extern struct S_8020C070 D_hd_front_end_8020C070[];

extern u16 D_hd_code_80303B3C[];
extern u16 D_hd_code_80303B48[];
extern u16 D_hd_code_80303B58[];
extern u16 D_hd_code_80303B68[];

u8 func_hd_front_end_801EE800(s8 *arg0, u8 arg1, u8 arg2) {
    UnknownData8024C414 *sp3C;
    struct S_80367C04 *sp38;
    u32 sp34;
    u8 sp33;
    s32 pad;

    sp3C = &players[playerNumber];
    sp38 = &D_hd_code_802E8F94[g_currentLevel];
    rmonPrintf("new ip=%8d : tc=%5d : bd=%2d : cr=%2d : rt=%3d : coin=%1d : bdn=%1d\n", g_statsNew.money, g_statsNew.timeCode, g_statsNew.buildingsDestroyed, g_statsNew.civiliansRescued, g_statsNew.rdusFound, g_statsNew.coin, g_statsNew.bdn);
    rmonPrintf("old ip=%8d : tc=%5d : bd=%2d : cr=%2d : rt=%3d : coin=%1d : bdn=%1d\n", g_statsOld.money, g_statsOld.timeCode, g_statsOld.buildingsDestroyed, g_statsOld.civiliansRescued, g_statsOld.rdusFound, g_statsOld.coin, g_statsOld.bdn);
    rmonPrintf("res ip=%8d : tc=%5d : bd=%2d : cr=%2d : rt=%3d : coin=%1d : bdn=%1d\n", g_statsRes.money, g_statsRes.timeCode, g_statsRes.buildingsDestroyed, g_statsRes.civiliansRescued, g_statsRes.rdusFound, g_statsRes.coin, g_statsRes.bdn);
    rmonPrintf("rs2 ip=%8d : tc=%5d : bd=%2d : cr=%2d : rt=%3d : coin=%1d : bdn=%1d\n", g_statsRes2.money, g_statsRes2.timeCode, g_statsRes2.buildingsDestroyed, g_statsRes2.civiliansRescued, g_statsRes2.rdusFound, g_statsRes2.coin, g_statsRes2.bdn);
    rmonPrintf("units %d\n", sp3C->unkA);
    if (D_hd_code_802E8F94[g_currentLevel].unk0 == 1) {
        sp34 = func_hd_code_802852EC();
        if (arg2 != 0) {
            if (arg1 != 0) {
                if (sp34 >= 0x64U) {
                    g_statsNew.coin = 3;
                } else if (sp34 >= 0x5AU) {
                    g_statsNew.coin = 2;
                } else if (sp34 >= 0x46U) {
                    g_statsNew.coin = 1;
                } else {
                    g_statsNew.coin = 5;
                }
                if (D_hd_code_803643D5 != 0) {
                    rmonPrintf("Units up 3\n");
                    sp3C->unkA += 3;
                }
                g_statsNew.bdn = 1;
            } else {
                g_statsNew.coin = 0;
            }
        }
        sp33 = g_statsNew.coin;
    } else {
        sp33 = func_hd_front_end_801EEDB4(g_currentLevel, arg1, arg2);
    }
    sprintf(D_hd_code_8036B980, "%s", D_hd_front_end_8020D810[g_currentLevel].name);
    *arg0 = 0;
    if ((arg1 != 0) && (arg2 != 0)) {
        if ((g_currentLevel == 0x31) || (g_currentLevel == 0x2F) || (g_currentLevel == 0x26)) {
            rmonPrintf(ASSERT_MESSAGE, "!DUMMY_LEVELS(levelno)", "stats.c", 0x5E);
        }
        if (D_hd_code_802E8F94[g_currentLevel].unk0 == 1) {
            sp3C->unk14 = D_hd_code_803649F0;
        }
        if (sp3C->unkA < 0x168) {
            rmonPrintf("UNITS UP %d\n", (g_statsNew.coin % 5) - (g_statsOld.coin % 5));
            sp3C->unkA += (g_statsNew.coin % 5) - (g_statsOld.coin % 5);
        }
        if (sp3C->unkA == 0x162) {
            sp3C->unkA += 6;
        }
        if ((sp3C->unkA / 12) > sp3C->unkC) {
            *arg0 = 1;
            sp3C->unkC++;
        }
        if (!(D_hd_code_802E8F94[g_currentLevel].unk0 & 0x81)) {
            sp3C->unk92[g_currentLevel] = g_statsNew.bdn;
        }
        D_hd_code_80364EF0[playerNumber][D_hd_code_802E8C44[g_statsNew.bdn]] = g_statsNew.timeCode;
        if ((D_hd_code_803643D5 != 0) && (D_hd_code_802E8F94[g_currentLevel].unk0 == 1)) {
            D_hd_code_80364EF0[playerNumber][D_hd_code_802E8C44[0]] = g_statsNew.timeCode;
        }
        sp3C->unk18[g_currentLevel] = sp33;
        func_hd_front_end_801E8DCC(playerNumber);
    }
    return sp33;
}


// <data>
char* D_hd_front_end_802084D0[4] = {
  "YOUR NEW BEST!",
  "BEST TO DATE",
  "YOUR BEST STAYS",
  "GUEST BEST IS"
};
u16* D_hd_front_end_802084E0[] = {
  D_hd_code_80303B3C,
  D_hd_code_80303B48,
  D_hd_code_80303B58,
  D_hd_code_80303B68
};
// </data>


u8 func_hd_front_end_801EEDB4(u8 arg0, u8 arg1, u8 arg2) {
    s32 sp6C;
    s32 pad68;
    s32 sp64;
    UnknownData8024C414 *sp60;
    struct S_80367C04 *sp5C;
    struct S_80367BCC *sp58;
    struct S_8020C070 *sp54;
    u8 sp34[0x20];
    u16 sp32;


    sp60 = &players[playerNumber];
    sp5C = &D_hd_code_802E8F94[(u8) arg0];
    if ((g_nextGameState == 0x08000000) && (arg1 != 0) && (sp5C->unk0 == 2)) {
        func_hd_code_80295A20(func_hd_code_80286038(g_statsNew.timeCode));
    }
    if ((arg2 != 0) && (arg1 != 0)) {
        if (D_hd_code_802E8F94[(u8) arg0].unk0 == 0x80) {
            g_statsNew.bdn = 0;
        } else if ((u32) g_statsNew.timeCode <= (u32) g_statsOld.timeCode) {
            g_statsNew.bdn = D_hd_code_803643D4;
        } else if (g_statsNew.timeCode != 0xFFFF) {
            sp32 = D_hd_code_80364EF0[playerNumber][D_hd_code_802E8C44[D_hd_code_803643D4]];
            if ((sp32 == 0) || ((u32) g_statsNew.timeCode < sp32)) {
                D_hd_code_80364EF0[playerNumber][D_hd_code_802E8C44[D_hd_code_803643D4]] = g_statsNew.timeCode;
            }
        }
    }
    if (((u32) g_statsNew.timeCode <= (u32) g_statsOld.timeCode) && (arg1 != 0)) {
        g_statsNew.coin = func_hd_front_end_801EF2BC(g_statsNew.timeCode, (u8) arg0, players[playerNumber].unk91);
    } else {
        g_statsNew.timeCode = g_statsOld.timeCode;
    }
    if (((u32) g_statsNew.timeCode < (u32) g_statsOld.timeCode) && (D_hd_code_803643D5 == 0)) {
        sp6C = 0x484;
        if (arg2 != 0) {
            sp6C = 0x584;
        }
    } else {
        sp6C = 0x480;
    }
    func_hd_code_80264A34(sp34, g_statsNew.timeCode, 0);
    sprintf(D_hd_code_8036B9A8 + 0x80, "****%s*", &sp34);
    if (arg1 != 0) {
        sp54 = &D_hd_front_end_8020C070[0x19];
        D_hd_front_end_8020C070[0x19].unk0 = sp6C;
        rmonPrintf("getting icon %d\n", g_statsNew.bdn);
        sp54->unk14 = g_statsNew.bdn + 0x22;
        sp58 = &D_hd_code_802F49F4[sp54->unk14];
        sp54->unk1A = func_hd_code_80272C5C(&sp58->unk6, 0, sp58->unk4, sp58->unk2C, sp58->unk2D | 4, 1.0f);
        if (playerNumber != D_hd_code_80364AEA) {
            sp64 = 3;
        } else if (((g_nextGameState == 0x80)) || (D_hd_code_803643D5 != 0)) {
            sp64 = 1;
        } else if ((u32) g_statsNew.timeCode < (u32) g_statsOld.timeCode) {
            sp64 = 0;
        } else {
            sp64 = 2;
        }
        D_hd_front_end_8020C070[0x18].unkC = D_hd_front_end_802084D0[sp64];
        D_hd_front_end_8020C070[0x18].unk10 = D_hd_front_end_802084E0[sp64];
    }
    return g_statsNew.coin;
}

s8 func_hd_front_end_801EF1E0(void) {
  struct LevelData *spC;
  s32 sp8;
  s32 sp4;

  spC = &D_hd_front_end_8020D810[g_currentLevel];
  if (spC->unk18[0] == -1) {
    return -1;
  }


  for(sp8 = 0, sp4 = 0; ((spC->unk18[sp8] != -1) && (sp8 < 2)); sp8++) {
    if (players[playerNumber].unk54[g_currentLevel] & (1 << sp8)) {
      sp4++;
    }
  }
  return sp4;
}

u8 func_hd_front_end_801EF2BC(u16 arg0, u8 arg1, u8 arg2) {
  u8 sp7;
  struct S_80367C04 *sp0;

  sp0 = &D_hd_code_802E8F94[arg1];
  if ((sp0->unk30[0] >= arg0) && (arg2 >= 0xC)) {
    sp7 = 4;
  } else if (sp0->unk30[1] >= arg0) {
    sp7 = 3;
  } else if (sp0->unk30[2] >= arg0) {
    sp7 = 2;
  } else if (sp0->unk30[3] >= arg0) {
    sp7 = 1;
  } else {
    sp7 = 5;
  }
  return sp7;
}
