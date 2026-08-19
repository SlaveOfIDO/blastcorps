#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/hd.h"
#include "../hd_code/yoshi.h"
#include "../hd_code/functions.h"
#include "../hd_code/variables.h"
#include "../hd_code/io/controller.h"
#include "structs.h"


void func_hd_code_802595E0(struct S_8020C070*, s32, s32, s32 (*)(void*, void*)); /* extern */
s32 func_hd_front_end_801EF2BC(u16, s32, u8);       /* extern */
s32 func_hd_front_end_801F7F74(u8);                /* extern */
void func_hd_front_end_801F8228(void);              /* extern */
void func_hd_front_end_801F8354(u8);               /* extern */
void func_hd_front_end_801FDE50(void);              /* extern */
s32 func_hd_front_end_801F7FF4(struct S_8020C070* arg0, struct S_8020C070* arg1);
s32 func_hd_front_end_801F81B4(u8);
void func_hd_front_end_801F8228(void);
void func_hd_front_end_801E8EB8(u8, s32);                /* extern */
Gfx* func_hd_code_80274868(Gfx*);                     /* extern */
s32 func_hd_code_80272ED8(s32, s32, u8, s32, u32, s32, f32); /* extern */
s32 func_hd_code_80274AA4(s32);                     /* extern */

extern u8 D_hd_front_end_8021A8F0;
extern u8 D_hd_code_80365060[];
extern u16 D_hd_code_80364EF0[][16];

// <bss>
u8 D_hd_front_end_80219FD0[64][0x20];
u8 D_hd_front_end_8021A7D0[24];
u8 D_hd_front_end_8021A7E8[64];
u32 D_hd_front_end_8021A828;
u32 D_hd_front_end_8021A82C;
u64 D_hd_front_end_8021A830;
s32 D_hd_front_end_8021A838;
s32 D_hd_front_end_8021A83C;
// </bss>

// <data>
char D_hd_front_end_8020D800[4][4] = {
  "1ST",
  "2ND",
  "3RD",
  "4TH"
};
// </data>

void func_hd_front_end_801F7850(void) {
    UnknownData8024C414* sp7C;
    struct S_802F8BDC* sp78;
    struct S_8020C070* sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    u8 sp48[0x20];
    u8 sp28[0x20];

    sp7C = &players[playerNumber];
    sp78 = &D_hd_code_802F8BDC[0x16];
    D_hd_code_8036BB24 = (struct S_8020C070*) D_hd_code_80358070;
    D_hd_code_80358070 += 0x71C;

    for (sp6C = 0; sp6C < 4; sp6C++) {
        if ((D_hd_code_80365060[sp6C] == 1) && (saveIt[sp6C] == 0) &&
            (((players[sp6C].unk18[levelno] > 0) && (players[sp6C].unk18[levelno] < 6))?1:0) != 0) {
            osSendMesg(&D_hd_front_end_80219EF8,
                       (void*) ((levelno << 8) | 8 | (sp6C << 0x10) | 0x01000000), 1);
            osRecvMesg(&D_hd_front_end_80219F50, NULL, 1);
        } else {
            func_hd_front_end_801F8354(sp6C);
        }
    }


    for (sp70 = 0, sp68 = 0; sp70 < 0x10; sp70++) {
        if ((func_hd_front_end_801F7F74(sp70) != 0) &&
            (D_hd_code_80364EF0[D_hd_code_80364AEA][D_hd_code_802E8C44[sp70]] > 0)) {
            for (sp6C = 0; sp6C < 4; sp6C++) {
                sp74 = &D_hd_code_8036BB24[(sp68 * 4) + sp6C];
                sp7C = &players[sp6C];
                if ((D_hd_code_80365060[sp6C] == 1) &&
                    (D_hd_code_80364EF0[sp6C][D_hd_code_802E8C44[sp70]] > 0) &&
                    ((D_hd_code_802E8F94[levelno].unk0 != 0x80) || (sp7C->unk91 >= 0xB))) {
                    func_hd_code_80264A34(sp48, D_hd_code_80364EF0[sp6C][D_hd_code_802E8C44[sp70]], 0);
                    sprintf(D_hd_front_end_80219FD0[(sp68 * 4) + sp6C], "%-7.7s %s", sp7C, sp48);
                    sp74->unkC = D_hd_front_end_80219FD0[(sp68 * 4) + sp6C];
                    sp74->unk10 = NULL;
                    sp74->unk14 = (func_hd_front_end_801EF2BC(
                        D_hd_code_80364EF0[sp6C][D_hd_code_802E8C44[sp70]],
                        levelno, players[sp6C].unk91) % 5) + 0x12;
                    sp74->unk18 = sp6C;
                } else {
                    sp74->unkC = NULL;
                    sp74->unk10 = NULL;
                    sp74->unk14 = 0;
                    sp74->unk18 = 4;
                }
                sp74->unk0 = 0x1400;
                sp74->unk2 = 0x24;
                sp74->unk6 = 0x10;
                sp74->unk8 = 0x11;
                sp74->unk16 = D_hd_code_80364EF0[sp6C][D_hd_code_802E8C44[sp70]];
                sp74->unk1A = sp70;
            }
            func_hd_code_802595E0(&D_hd_code_8036BB24[sp68 * 4], 4, 0x1C,
                                  &func_hd_front_end_801F7FF4);
            for (sp6C = 0; sp6C < 4; sp6C++) {
                sp74 = &D_hd_code_8036BB24[(sp68 * 4) + sp6C];
                sp74->unk4 = sp6C * 0x11;
                if (sp6C == 2) {
                    sp74->unk0 |= 1;
                }
                if (sp74->unkC != NULL) {
                    bcopy(sp74->unkC, sp28, func_hd_code_8025B300(sp74->unkC) + 1);
                    sprintf(sp74->unkC, "%s %s", D_hd_front_end_8020D800[sp6C], sp28);
                }
            }
            sp68 += 1;
        }
    }
    func_hd_code_802595E0(D_hd_code_8036BB24, sp68, 0x70, &func_hd_front_end_801F7FF4);

    for (sp70 = 0; sp70 < (sp68 * 4); sp70++) {
        sp74 = &D_hd_code_8036BB24[sp70];
        D_hd_front_end_8021A7E8[sp70] = sp74->unk18;
        if (!(sp70 & 3)) {
            D_hd_front_end_8021A7D0[sp70 / 4] = sp74->unk1A;
        }
        sp74->unk16 = 0x1E;
        sp74->unk4 += (sp70 / 4) * 0x64;
    }

    if (D_hd_code_802E8F94[levelno].unk0 == 0x80) {
        sp74 = &D_hd_code_8036BB24[sp70];
        sp74->unkC = NULL;
        sp74->unk10 = NULL;
        sp74->unk0 = 0x400;
        sp74->unk2 = -0x20;
        sp74->unk4 = 0x28;
        sp74->unk14 = 0xD;
        sp74->unk1A = 0;
        sp74->unk16 = sp74->unk1A;
        sp78->unk10 = (sp68 * 4) + 1;
    } else {
        sp78->unk10 = sp68 * 4;
    }
    sp78->unk18 = 2;
    D_hd_front_end_8021A828 = sp68 * 4;
    func_hd_front_end_801F8228();
    func_hd_front_end_801FDE50();
}

s32 func_hd_front_end_801F7F74(u8 arg0) {
  if (D_hd_code_802E8F94[levelno].unk0 == 0x80) {
    return arg0 == 0;
  }
  return (players[D_hd_code_80364AEA].unk10 & (1 << arg0))?1:0;
}

s32 func_hd_front_end_801F7FF4(struct S_8020C070* arg0, struct S_8020C070* arg1) {
  if ((arg0->unkC != NULL) && (arg1->unkC != NULL)) {
    return arg0->unk16 - arg1->unk16;
  }
  if (arg0->unkC != NULL) {
    return -1;
  }
  return 1;
}

void func_hd_front_end_801F803C(void) {
  s32 sp1C;
  s32 sp18;

  if ((D_hd_code_80370C28 & 0x2010) && !(D_hd_code_80370C2A & 0x2010)) {
    for (sp1C = (playerNumber + 1) % 4, sp18 = 0; sp18 < 4 && (D_hd_code_80365060[sp1C % 4] != 1 || !func_hd_front_end_801F81B4(sp1C % 4)); sp18++, sp1C = (sp1C + 1) % 4) {
    }
    if (playerNumber != sp1C) {
      sndPlaySfx((struct ALBankAlt_s*) D_hd_code_80367738, 0x1D, NULL);
      playerNumber = sp1C;
      func_hd_front_end_801E8EB8(sp1C & 0xFF, 1);
      func_hd_front_end_801F8228();
      return;
    }
    sndPlaySfx((struct ALBankAlt_s*) D_hd_code_80367738, 0xD0, NULL);
  }
}

s32 func_hd_front_end_801F81B4(u8 arg0) {
  u32 sp4;
  u32 sp0;

  sp4 = D_hd_front_end_8021A828;
  for (sp0 = 0; sp0 < sp4 && D_hd_front_end_8021A7E8[sp0] != arg0; sp0++) {
  }
  return sp0 != sp4;
}

void func_hd_front_end_801F8228(void) {
  struct S_8020C070* sp4;
  u32 sp0;

  for (sp0 = 0; sp0 < D_hd_front_end_8021A828; sp0++) {
    sp4 = &D_hd_code_8036BB24[sp0];
    if (D_hd_front_end_8021A7E8[sp0] == playerNumber) {
      sp4->unk0 |= 4;
    } else {
      sp4->unk0 &= ~4;
    }
    if (D_hd_front_end_8021A7E8[sp0] == D_hd_code_80364AEA) {
      sp4->unk19 = 6;
      sp4->unk18 = sp4->unk19;
    } else if (D_hd_front_end_8021A7E8[sp0] == playerNumber) {
      sp4->unk19 = 2;
      sp4->unk18 = sp4->unk19;
    } else {
      sp4->unk19 = 7;
      sp4->unk18 = sp4->unk19;
    }
  }
}

void func_hd_front_end_801F8354(u8 arg0) {
  s32 sp24;

  if (!frontEndPresent) {
    rmonPrintf(ASSERT_MESSAGE, "frontEndPresent", "bestTimes.c", 0x117);
  }
  if ((players[arg0].unk18[levelno] > 0) && (players[arg0].unk18[levelno] < 6)?1:0) {
    return;
  }
  for (sp24 = 0; sp24 < 0x10; sp24++) {
    D_hd_code_80364EF0[arg0][D_hd_code_802E8C44[sp24]] = 0;
  }
}

Gfx* func_hd_front_end_801F8440(s32 arg0, Gfx* arg1) {
  Gfx* sp2C;
  s16 sp2A;

  sp2A = 0;
  sp2C = arg1;
  if (D_hd_code_802E8F94[levelno].unk0 != 0x80) {
    sp2C = func_hd_code_80274868(arg1);
    sp2C = func_hd_code_80272ED8(sp2C,
               D_hd_front_end_8021A7D0[D_hd_code_802F8BDC[0x16].unk18 / 4] + D_hd_front_end_8021A8F0,
               0x18 - sp2A, 0x64, 0xFF - (sp2A * 2), 1, 1.0f);
    sp2C = func_hd_code_80274AA4(sp2C);
  }
  return sp2C;
}
