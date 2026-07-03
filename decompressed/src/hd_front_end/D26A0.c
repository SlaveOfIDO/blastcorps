#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/hd.h"
#include "../hd_code/yoshi.h"
#include "../hd_code/functions.h"
#include "../hd_code/variables.h"
#include "structs.h"

u8 func_hd_front_end_801EEDB4(u8, u8, u8);         /* extern */

extern s32 D_hd_code_803649F0;
extern u8  D_hd_code_8036B980[];
extern s32 D_hd_code_8036EA60;
extern s32 D_hd_code_8036EA64;
extern u8  D_hd_code_8036EA68;
extern u8  D_hd_code_8036EA69;
extern u8  D_hd_code_8036EA6A;
extern u8  D_hd_code_8036EA6B;
extern u16 D_hd_code_8036EA6C;
extern s32 D_hd_code_8036EA74;
extern u8  D_hd_code_8036EA78;
extern u8  D_hd_code_8036EA79;
extern u8  D_hd_code_8036EA7A;
extern u8  D_hd_code_8036EA7B;
extern u16 D_hd_code_8036EA7C;
extern s32 D_hd_code_8036EA80;
extern s32 D_hd_code_8036EA84;
extern u8  D_hd_code_8036EA88;
extern u8  D_hd_code_8036EA89;
extern u8  D_hd_code_8036EA8A;
extern u8  D_hd_code_8036EA8B;
extern u16 D_hd_code_8036EA8C;
extern s32 D_hd_code_8036EA90;
extern s32 D_hd_code_8036EA94;
extern u8  D_hd_code_8036EA98;
extern u8  D_hd_code_8036EA99;
extern u8  D_hd_code_8036EA9A;
extern u8  D_hd_code_8036EA9B;
extern u16 D_hd_code_8036EA9C;
extern char D_hd_code_8036B9A8[0x20];


extern u16 D_hd_code_80364EF0[][16];
extern u8  D_hd_code_802E8C44[];
extern struct S_80367C04 D_hd_code_802E8F94[];
u32 func_hd_code_802852EC();                          /* extern */
void func_hd_front_end_801E8DCC(u8 arg0);

u8 func_hd_front_end_801EE800(s8 *arg0, u8 arg1, u8 arg2) {
    UnknownData8024C414 *sp3C;
    struct S_80367C04 *sp38;
    u32 sp34;
    u8 sp33;
    s32 pad;

    sp3C = &players[playerNumber];
    sp38 = &D_hd_code_802E8F94[levelno];
    rmonPrintf("new ip=%8d : tc=%5d : bd=%2d : cr=%2d : rt=%3d : coin=%1d : bdn=%1d\n", D_hd_code_8036EA70, D_hd_code_8036EA74, D_hd_code_8036EA78, D_hd_code_8036EA79, D_hd_code_8036EA7C, D_hd_code_8036EA7A, D_hd_code_8036EA7B);
    rmonPrintf("old ip=%8d : tc=%5d : bd=%2d : cr=%2d : rt=%3d : coin=%1d : bdn=%1d\n", D_hd_code_8036EA60, D_hd_code_8036EA64, D_hd_code_8036EA68, D_hd_code_8036EA69, D_hd_code_8036EA6C, D_hd_code_8036EA6A, D_hd_code_8036EA6B);
    rmonPrintf("res ip=%8d : tc=%5d : bd=%2d : cr=%2d : rt=%3d : coin=%1d : bdn=%1d\n", D_hd_code_8036EA80, D_hd_code_8036EA84, D_hd_code_8036EA88, D_hd_code_8036EA89, D_hd_code_8036EA8C, D_hd_code_8036EA8A, D_hd_code_8036EA8B);
    rmonPrintf("rs2 ip=%8d : tc=%5d : bd=%2d : cr=%2d : rt=%3d : coin=%1d : bdn=%1d\n", D_hd_code_8036EA90, D_hd_code_8036EA94, D_hd_code_8036EA98, D_hd_code_8036EA99, D_hd_code_8036EA9C, D_hd_code_8036EA9A, D_hd_code_8036EA9B);
    rmonPrintf("units %d\n", sp3C->unkA);
    if (D_hd_code_802E8F94[levelno].unk0 == 1) {
        sp34 = func_hd_code_802852EC();
        if (arg2 != 0) {
            if (arg1 != 0) {
                if (sp34 >= 0x64U) {
                    D_hd_code_8036EA7A = 3;
                } else if (sp34 >= 0x5AU) {
                    D_hd_code_8036EA7A = 2;
                } else if (sp34 >= 0x46U) {
                    D_hd_code_8036EA7A = 1;
                } else {
                    D_hd_code_8036EA7A = 5;
                }
                if (D_hd_code_803643D5 != 0) {
                    rmonPrintf("Units up 3\n");
                    sp3C->unkA += 3;
                }
                D_hd_code_8036EA7B = 1;
            } else {
                D_hd_code_8036EA7A = 0;
            }
        }
        sp33 = D_hd_code_8036EA7A;
    } else {
        sp33 = func_hd_front_end_801EEDB4(levelno, arg1, arg2);
    }
    proutSprintf(D_hd_code_8036B980, "%s", D_hd_front_end_8020D810[levelno].name);
    *arg0 = 0;
    if ((arg1 != 0) && (arg2 != 0)) {
        if ((levelno == 0x31) || (levelno == 0x2F) || (levelno == 0x26)) {
            rmonPrintf(ASSERT_MESSAGE, "!DUMMY_LEVELS(levelno)", "stats.c", 0x5E);
        }
        if (D_hd_code_802E8F94[levelno].unk0 == 1) {
            sp3C->unk14 = D_hd_code_803649F0;
        }
        if (sp3C->unkA < 0x168) {
            rmonPrintf("UNITS UP %d\n", (D_hd_code_8036EA7A % 5) - (D_hd_code_8036EA6A % 5));
            sp3C->unkA += (D_hd_code_8036EA7A % 5) - (D_hd_code_8036EA6A % 5);
        }
        if (sp3C->unkA == 0x162) {
            sp3C->unkA += 6;
        }
        if ((sp3C->unkA / 12) > sp3C->unkC) {
            *arg0 = 1;
            sp3C->unkC++;
        }
        if (!(D_hd_code_802E8F94[levelno].unk0 & 0x81)) {
            sp3C->unk92[levelno] = D_hd_code_8036EA7B;
        }
        D_hd_code_80364EF0[playerNumber][D_hd_code_802E8C44[D_hd_code_8036EA7B]] = D_hd_code_8036EA74;
        if ((D_hd_code_803643D5 != 0) && (D_hd_code_802E8F94[levelno].unk0 == 1)) {
            D_hd_code_80364EF0[playerNumber][D_hd_code_802E8C44[0]] = D_hd_code_8036EA74;
        }
        sp3C->unk18[levelno] = sp33;
        func_hd_front_end_801E8DCC(playerNumber);
    }
    return sp33;
}

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D26A0/D_hd_front_end_8020EF48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D26A0/D_hd_front_end_8020EF58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D26A0/D_hd_front_end_8020EF68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D26A0/D_hd_front_end_8020EF78.s")

s32 func_hd_code_80286038(s32);                     /* extern */
void func_hd_code_80295A20(s32);                    /* extern */
u8 func_hd_front_end_801EF2BC(u16 arg0, u8 arg1, u8 arg2);         /* extern */

extern char* D_hd_front_end_802084D0[];
extern s32 D_hd_front_end_802084E0[];
extern u16 D_hd_code_80364EF0[][16];
extern u8  D_hd_code_802E8C44[];
extern struct S_80367C04 D_hd_code_802E8F94[];
extern struct S_80367BCC D_hd_code_802F49F4[];
extern struct S_8020C070 D_hd_front_end_8020C070[];

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
    if ((D_hd_code_80364A98 == 0x08000000) && (arg1 != 0) && (sp5C->unk0 == 2)) {
        func_hd_code_80295A20(func_hd_code_80286038(D_hd_code_8036EA74));
    }
    if ((arg2 != 0) && (arg1 != 0)) {
        if (D_hd_code_802E8F94[(u8) arg0].unk0 == 0x80) {
            D_hd_code_8036EA7B = 0;
        } else if ((u32) D_hd_code_8036EA74 <= (u32) D_hd_code_8036EA64) {
            D_hd_code_8036EA7B = D_hd_code_803643D4;
        } else if (D_hd_code_8036EA74 != 0xFFFF) {
            sp32 = D_hd_code_80364EF0[playerNumber][D_hd_code_802E8C44[D_hd_code_803643D4]];
            if ((sp32 == 0) || ((u32) D_hd_code_8036EA74 < sp32)) {
                D_hd_code_80364EF0[playerNumber][D_hd_code_802E8C44[D_hd_code_803643D4]] = D_hd_code_8036EA74;
            }
        }
    }
    if (((u32) D_hd_code_8036EA74 <= (u32) D_hd_code_8036EA64) && (arg1 != 0)) {
        D_hd_code_8036EA7A = func_hd_front_end_801EF2BC(D_hd_code_8036EA74, (u8) arg0, players[playerNumber].unk91);
    } else {
        D_hd_code_8036EA74 = D_hd_code_8036EA64;
    }
    if (((u32) D_hd_code_8036EA74 < (u32) D_hd_code_8036EA64) && (D_hd_code_803643D5 == 0)) {
        sp6C = 0x484;
        if (arg2 != 0) {
            sp6C = 0x584;
        }
    } else {
        sp6C = 0x480;
    }
    func_hd_code_80264A34(sp34, D_hd_code_8036EA74, 0);
    proutSprintf(D_hd_code_8036B9A8 + 0x80, "****%s*", &sp34);
    if (arg1 != 0) {
        sp54 = &D_hd_front_end_8020C070[0x19];
        D_hd_front_end_8020C070[0x19].unk0 = sp6C;
        rmonPrintf("getting icon %d\n", D_hd_code_8036EA7B);
        sp54->unk14 = D_hd_code_8036EA7B + 0x22;
        sp58 = &D_hd_code_802F49F4[sp54->unk14];
        sp54->unk1A = func_hd_code_80272C5C(&sp58->unk6, 0, sp58->unk4, sp58->unk2C, sp58->unk2D | 4, 1.0f);
        if (playerNumber != D_hd_code_80364AEA) {
            sp64 = 3;
        } else if (((D_hd_code_80364A98 == 0x80)) || (D_hd_code_803643D5 != 0)) {
            sp64 = 1;
        } else if ((u32) D_hd_code_8036EA74 < (u32) D_hd_code_8036EA64) {
            sp64 = 0;
        } else {
            sp64 = 2;
        }
        D_hd_front_end_8020C070[0x18].unkC = D_hd_front_end_802084D0[sp64];
        D_hd_front_end_8020C070[0x18].unk10 = D_hd_front_end_802084E0[sp64];
    }
    return D_hd_code_8036EA7A;
}

s8 func_hd_front_end_801EF1E0(void) {
  struct LevelData *spC;
  s32 sp8;
  s32 sp4;

  spC = &D_hd_front_end_8020D810[levelno];
  if (spC->unk18[0] == -1) {
    return -1;
  }


  for(sp8 = 0, sp4 = 0; ((spC->unk18[sp8] != -1) && (sp8 < 2)); sp8++) {
    if (players[playerNumber].unk54[levelno] & (1 << sp8)) {
      sp4++;
    }
  }
  return sp4;
}
u8 func_hd_front_end_801EF2BC(u16 arg0, u8 arg1, u8 arg2) {
  u8 sp7;
  struct S_80367C04 *sp0;

  sp0 = &D_hd_code_802E8F94[arg1];
  if ((sp0->unk30 >= arg0) && (arg2 >= 0xC)) {
    sp7 = 4;
  } else if (sp0->unk32 >= arg0) {
    sp7 = 3;
  } else if (sp0->unk34 >= arg0) {
    sp7 = 2;
  } else if (sp0->unk36 >= arg0) {
    sp7 = 1;
  } else {
    sp7 = 5;
  }
  return sp7;
}
