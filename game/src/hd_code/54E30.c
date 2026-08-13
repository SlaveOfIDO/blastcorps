#include "common.h"
#include "functions.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"
#include "yoshi.h"

void func_hd_code_8029A500();
u64 func_801ECA50(u8);

// <bss>
u64 D_hd_code_803A6AF0;
u64 D_hd_code_803A6AF8;
u8 D_hd_code_803A6B00;
u8 D_hd_code_803A6B01;
u8 D_hd_code_803A6B02;
u8 D_hd_code_803A6B03;
u8 D_hd_code_803A6B04;
// </bss>

void func_hd_code_802995F0(s32 arg0) {
    D_hd_code_803A6B03 = (u8) arg0;
    rmonPrintf("prepare sequence %d\n", arg0);
    switch (D_hd_code_803A6B03) {
    case 1:
        D_hd_code_803A6B02 = 0x26;
        D_hd_code_803A6B01 = 0x28;
        D_hd_code_803A6B00 = 0x28;
        D_hd_code_803A6AF0 = 0x4000;
        D_hd_code_803A6AF8 = 0x4000;
        D_hd_code_803A6B04 = 1;
        return;
    case 3:
        D_hd_code_803A6B02 = 0x26;
        D_hd_code_803A6B01 = 0x2B;
        D_hd_code_803A6B00 = 0x2B;
        D_hd_code_803A6AF0 = 0x4000;
        D_hd_code_803A6AF8 = 0x4000;
        D_hd_code_803A6B04 = 1;
        return;
    case 0:
        D_hd_code_803A6B02 = 0x31;
        D_hd_code_803A6B01 = 0x32;
        D_hd_code_803A6B00 = 0x32;
        D_hd_code_803A6AF0 = 0x4000;
        D_hd_code_803A6AF8 = 0x4000;
        D_hd_code_803A6B04 = 0;
        return;
    case 4:
        D_hd_code_803A6B02 = 0x2F;
        D_hd_code_803A6B01 = 0;
        D_hd_code_803A6B00 = 0;
        D_hd_code_803A6AF0 = 0x4000;
        D_hd_code_803A6AF8 = 0x4000;
        D_hd_code_803A6B04 = 1;
        return;
    case 5:
        D_hd_code_803A6B02 = 0x37;
        D_hd_code_803A6B01 = 0x37;
        D_hd_code_803A6B00 = 0x37;
        if ((players[playerNumber].unk18[D_hd_code_803A6B00] > 0 && players[playerNumber].unk18[D_hd_code_803A6B00] < 6)?1:0) {
            D_hd_code_803A6AF0 = 0x80;
            D_hd_code_803A6AF8 = 0x80;
        } else {
            D_hd_code_803A6AF0 = 0x2000;
            D_hd_code_803A6AF8 = 0x2000;
        }
        D_hd_code_803A6B04 = 1;
        return;
    case 6:
        D_hd_code_803A6B02 = 0x1C;
        D_hd_code_803A6B01 = 0x1C;
        D_hd_code_803A6B00 = 0x1C;
        if ((players[playerNumber].unk18[D_hd_code_803A6B00] > 0 && players[playerNumber].unk18[D_hd_code_803A6B00] < 6)?1:0) {
            D_hd_code_803A6AF0 = 0x80;
            D_hd_code_803A6AF8 = 0x80;
        } else {
            D_hd_code_803A6AF0 = 0x2000;
            D_hd_code_803A6AF8 = 0x2000;
        }
        D_hd_code_803A6B04 = 1;
        return;
    case 7:
        D_hd_code_803A6B02 = 0x35;
        D_hd_code_803A6B01 = 0x35;
        D_hd_code_803A6B00 = 0x35;
        if ((players[playerNumber].unk18[D_hd_code_803A6B00] > 0 && players[playerNumber].unk18[D_hd_code_803A6B00] < 6)?1:0) {
            D_hd_code_803A6AF0 = 0x80;
            D_hd_code_803A6AF8 = 0x80;
        } else {
            D_hd_code_803A6AF0 = 0x2000;
            D_hd_code_803A6AF8 = 0x2000;
        }
        D_hd_code_803A6B04 = 1;
        return;
    case 8:
        D_hd_code_803A6B02 = 7;
        D_hd_code_803A6B01 = 7;
        D_hd_code_803A6B00 = 7;
        if ((players[playerNumber].unk18[D_hd_code_803A6B00] > 0 && players[playerNumber].unk18[D_hd_code_803A6B00] < 6)?1:0) {
            D_hd_code_803A6AF0 = 0x80;
            D_hd_code_803A6AF8 = 0x80;
        } else {
            D_hd_code_803A6AF0 = 0x2000;
            D_hd_code_803A6AF8 = 0x2000;
        }
        D_hd_code_803A6B04 = 1;
        return;
    case 9:
        D_hd_code_803A6B02 = 0x13;
        D_hd_code_803A6B01 = 0x13;
        D_hd_code_803A6B00 = 0x13;
        if ((players[playerNumber].unk18[D_hd_code_803A6B00] > 0 && players[playerNumber].unk18[D_hd_code_803A6B00] < 6)?1:0) {
            D_hd_code_803A6AF0 = 0x80;
            D_hd_code_803A6AF8 = 0x80;
        } else {
            D_hd_code_803A6AF0 = 0x2000;
            D_hd_code_803A6AF8 = 0x2000;
        }
        D_hd_code_803A6B04 = 1;
        return;
    default:
        rmonPrintf("unknown sequence number %d\n", D_hd_code_803A6B03);
        return;
    }
}

void func_hd_code_80299C0C(void) {
  levelno = D_hd_code_803A6B02;
}

void func_hd_code_80299C20(void) {
  switch (levelno) {
    case 0x2F:
      D_hd_code_802E8BEC = 0;
      D_hd_code_802E8BF0 = 0;
      func_hd_code_8025B9D0(0, &levelno);
      break;
    case 0x37:
      D_hd_code_802E8BEC = 9;
      D_hd_code_802E8BF0 = 0;
      func_hd_code_8025B9D0(9, &levelno);
      D_hd_code_803643D4 = 5;
      func_hd_code_8026AF6C(0x8041U);
      func_hd_code_80295E50();
      break;
    case 0x1C:
      D_hd_code_802E8BEC = 0xA;
      D_hd_code_802E8BF0 = 0;
      func_hd_code_8025B9D0(0xA, &levelno);
      D_hd_code_803643D4 = 1;
      func_hd_code_8026AF6C(0x8042U);
      func_hd_code_80295E50();
      break;
    case 0x35:
      D_hd_code_802E8BEC = 0xB;
      D_hd_code_802E8BF0 = 0;
      func_hd_code_8025B9D0(0xB, &levelno);
      D_hd_code_803643D4 = 2;
      func_hd_code_8026AF6C(0x8043U);
      func_hd_code_80295E50();
      break;
    case 0x7:
      D_hd_code_802E8BEC = 0xC;
      D_hd_code_802E8BF0 = 0;
      func_hd_code_8025B9D0(0xC, &levelno);
      D_hd_code_803643D4 = 3;
      func_hd_code_8026AF6C(0x8044U);
      func_hd_code_80295E50();
      break;
    case 0x13:
      D_hd_code_802E8BEC = 0xD;
      D_hd_code_802E8BF0 = 0;
      func_hd_code_8025B9D0(0xD, &levelno);
      D_hd_code_803643D4 = 9;
      func_hd_code_8026AF6C(0x8045U);
      func_hd_code_80295E50();
      break;
    case 0x31:
      func_hd_code_8029A500();
      break;
    case 0x26:
      func_hd_code_8025BB50();
      break;
  }
}

void func_hd_code_80299E10(s32 arg0) {
  sndDeactivateAllSfxByFlag_1();

  switch (levelno) {
    case 0x26:
    case 0x2F:
    case 0x31:
      players[playerNumber].unk18[levelno] = 5;
      break;
    case 0x37:
      players[playerNumber].unk92[0x5C] |= 1;
      break;
    case 0x1C:
      players[playerNumber].unk92[0x5C] |= 2;
      break;
    case 0x35:
      players[playerNumber].unk92[0x5C] |= 4;
      break;
    case 0x7:
      players[playerNumber].unk92[0x5C] |= 8;
      break;
    case 0x13:
      players[playerNumber].unk92[0x5C] |= 0x10;
      break;
  }
  if (arg0 != 0) {
    sndPlaySfx(D_hd_code_80367738, 0x1E, NULL);
    D_hd_code_80364A98 = D_hd_code_803A6AF0;
    levelno = D_hd_code_803A6B00;
  } else {
    D_hd_code_80364A98 = D_hd_code_803A6AF8;
    levelno = D_hd_code_803A6B01;
  }
  rmonPrintf("finishing sequence and going to level %d\n", levelno);
}

u64 func_hd_code_80299FE8(u8 arg0) {
  u64 sp28;

  switch (arg0) {
    case 0x26:
      sp28 = 0x100000000000;
      func_hd_code_802995F0(1);
      break;
    case 0x37:
      sp28 = 0x100000000000;
      func_hd_code_802995F0(5);
      break;
    case 0x1C:
      sp28 = 0x100000000000;
      func_hd_code_802995F0(6);
      break;
    case 0x35:
      sp28 = 0x100000000000;
      func_hd_code_802995F0(7);
      break;
    case 0x7:
      sp28 = 0x100000000000;
      func_hd_code_802995F0(8);
      break;
    case 0x13:
      sp28 = 0x100000000000;
      func_hd_code_802995F0(9);
      break;
    default:
      sp28 = func_801ECA50(arg0);
      break;
  }
  rmonPrintf("get loop done for world %d\n", func_hd_code_8026F92C(sp28));
  return sp28;
}
