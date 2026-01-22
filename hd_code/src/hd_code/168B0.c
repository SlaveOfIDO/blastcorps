#include "common.h"
#include "structs.h"

void func_hd_code_802A1040(u16, void*, s32);             /* extern */
void proutSprintf(u8*, const char*, ...);                       /* extern */
void func_hd_code_80275270(u64, s32);                   /* extern */
void func_hd_code_80275390(u64);                      /* extern */
s32 areWeFading();                                /* extern */
void func_hd_code_802AFC28(s32);                       /* extern */
void func_hd_code_802B0D70(s32);                       /* extern */
void func_hd_code_802B2988(s32);                       /* extern */
void func_hd_code_802B40D4(s32);                       /* extern */
void func_hd_code_802B58C8(s32);                       /* extern */
void func_hd_code_802B7308(s32);                       /* extern */
void func_hd_code_802C80A0(s32);                       /* extern */
void func_hd_code_802CB660(s32);                       /* extern */
void func_hd_code_802D2524(s32);                       /* extern */
void func_hd_code_802B2D7C();                          /* extern */
void func_hd_code_802AFFD4();                          /* extern */
void func_hd_code_802B1228();                          /* extern */
void func_hd_code_802D0C68();                          /* extern */
void func_hd_code_802B448C();                          /* extern */
void func_hd_code_802B5CD8();                          /* extern */
void func_hd_code_802C5714();                          /* extern */
void func_hd_code_802C9F54();                          /* extern */
s32 func_hd_code_8025B300(u8*);                     /* extern */
void InitiateDma(void*, void*, s32*, u8, s32, s32);           /* extern */
void func_hd_code_80257490(u8** arg0, s32 arg1);
s8 func_hd_code_80272C5C(s32*, s32, s32, s32, s32, f32);    /* extern */

extern f32 D_hd_code_802E8C84[2];
extern u8 D_80365458[];
extern u8 D_8036698C;
extern u8* D_803669B0;
u8 D_8039CAF0[0x50 * 0x200];
extern u8 D_80365360[];
extern u16 D_803653B0[];
extern u8 D_8036698C;
extern s32 D_803669A0;
extern u16 D_80370C30;
extern s8 D_80370C32;
extern s8 D_80370C33;
extern u64 D_hd_code_80364A90;
extern u8 D_hd_code_802E8BD8;
extern u8 D_hd_code_803643DB;
extern u8 D_hd_code_802E8BD0;
extern s16 D_8036BB1C;
extern s8 D_80364A50;
extern u8 D_hd_code_803643D6;
extern u16 D_80365558[];
extern s32 D_803649E8;
extern u8 D_hd_code_80364456;
extern s32 D_803669B4;
extern s32 D_6A9F10; // attract.raw
extern s32 D_6AD3F0; // 6AD3F0.bin
extern u8 D_8036698C;
extern s32 D_803669A0;
extern u8* D_80358070;
extern u16 D_80366A04;
extern s32 D_80366990;
extern u8 D_803669A8;
extern u8 D_80365580;
extern struct S_803669AC D_80365588[];
extern s32 D_80366990;
extern s32 D_803669A0;
extern struct S_803669AC* D_803669AC;
extern s32 D_hd_code_802E8CB0;
extern struct S_803669AC D_80365588[];
extern s32 D_80366990;
extern s32 D_8036699C;
extern u16 D_803669A4;
extern s8 D_803669A6;
extern s8 D_803669A7;
extern u64 D_80364A98;

void func_hd_code_8025B070(void) {
  s32 sp4;
  for(sp4 = 0; sp4 < 0x50; sp4++) {
    D_80365360[sp4] = 0;
    D_803653B0[sp4] = 0;
  }
}

void* func_hd_code_8025B0B8(u16 arg0) {
  s32 sp1C;
  u8 found;

  found = 0;
  sp1C = 0;
  while((sp1C < 0x50) && !found) {
    if (D_803653B0[sp1C] == arg0) {
      found = 1;
    } else {
      sp1C++;
    }
  }
  if (!found) {
    sp1C = 0;
    while ((sp1C < 0x50) && !found) {
      if (D_803653B0[sp1C] == 0) {
        func_hd_code_802A1040(arg0, &D_8039CAF0[sp1C * 0x200], 0);
        D_803653B0[sp1C] = arg0;
        found = 1;
      } else {
        sp1C++;
      }
    }
  }
  if (!found) {
    sp1C = 0;
    while (sp1C < 0x50 && !found) {
      if (D_80365360[sp1C] == 0) {
        func_hd_code_802A1040(arg0, &D_8039CAF0[sp1C * 0x200], 0);
        D_803653B0[sp1C] = arg0;
        found = 1;
      } else {
        sp1C++;
      }
    }
  }
  if (!found) {
    func_hd_code_8029A7E4("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "found", "font.c", 0x51);
  }
  if (found) {
    D_80365360[sp1C] = 3;
  }
  return &D_8039CAF0[sp1C * 0x200];
}

void func_hd_code_8025B2B8(void) {
  s32 i;
  for (i = 0; i < 0x50; i++) {
    if (D_80365360[i] != 0) {
      D_80365360[i]--;
    }
  }
}

s32 func_hd_code_8025B300(u8* arg0) {
  s32 sp4;
  s32 sp0;

  sp4 = 0;
  sp0 = 0;
  if ((arg0 != NULL) && (*arg0 != 0)) {
    do {
      if (arg0[sp4] == 0x2A) {
        sp0++;
      }
    } while (arg0[++sp4] != 0);
  }
  return sp4 - sp0;
}

s32 func_hd_code_8025B370(u16* arg0) {
  s32 sp4;
  s32 sp0;

  sp4 = 0;
  sp0 = 0;
  if ((arg0 != NULL) && arg0[0] != 0xFFE) {
    do {
      if (arg0[sp4] == 0x1000) {
        sp0++;
      }
    } while (arg0[++sp4] != 0xFFE);
  }
  return sp4 - sp0;
}

s32 func_hd_code_8025B3F0(u8* arg0, u8* arg1) {
  s32 sp2C;
  s32 sp28;

  if ((sp28 = func_hd_code_8025B300(arg0)) != func_hd_code_8025B300(arg1)) {
    return 1;
  }
  for(sp2C = 0; sp2C < sp28; sp2C++) {
    if (arg0[sp2C] != arg1[sp2C]) {
      return 1;
    }
  }
  return 0;
}

s16 func_hd_code_8025B498(u16 arg0, u16 arg1, u8* arg2, s32 arg3) {
  volatile s32 sp2C = 0;
  volatile s16 sp2A = ((s16) arg0) - ((arg1 * (1.0f + (((func_hd_code_8025B300(arg2)) - 1) * D_hd_code_802E8C84[0]))) / 2.0);
  return sp2A;
}

u8* func_hd_code_8025B558(u16* arg0) {
  s32 sp4;

  sp4 = 0;
  while(arg0[sp4] != 0 && sp4 < 0xFF) {
    D_80365458[sp4++] = (u8) arg0[sp4];
  }
  D_80365458[sp4] = 0;
  return D_80365458;
}

u16* func_hd_code_8025B5D4(u16 *arg0, u16 *arg1, u16* arg2, s32 arg3) {
  u8 sp34[10];
  s32 sp30;
  s32 sp2C;
  s32 sp28;

  sp30 = 0;
  sp2C = 0;
  do {
    switch (arg1[sp30]) {                          /* irregular */
      case 0x1003:
        for (sp28 = 0; arg2[sp28] != 0xFFE; sp28++, sp2C++) {
          arg0[sp2C] = arg2[sp28];
        }
        break;
      case 0x1004:
        proutSprintf(sp34, "%d", arg3);
        for(sp28 = 0; sp34[sp28] != 0; sp28++, sp2C++) {
          arg0[sp2C] = sp34[sp28] - 0x20;
        }
        break;
      default:
        arg0[sp2C] = arg1[sp30];
        sp2C++;
        break;
    }
    sp30 += 1;
  } while (arg1[sp30] != 0x0FFE);

  arg0[sp2C] = 0xFFE;

  return arg0;
}

u16* func_hd_code_8025B7AC(u8* arg0) {
  s32 sp1C;
  for (sp1C = 0; sp1C < func_hd_code_8025B300(arg0); sp1C++) {
    switch (arg0[sp1C]) {
      case 0x20:
        D_80365558[sp1C] = 0x1002;
        break;
      case 0x2E:
        D_80365558[sp1C] = 0x3C;
        break;
      case 0x31:
      case 0x32:
      case 0x33:
      case 0x34:
        D_80365558[sp1C] = arg0[sp1C] - 0x20;
        break;
      default:
        D_80365558[sp1C] = arg0[sp1C] - 0x27;
        break;
      case 0x2F:
        D_80365558[sp1C] = 0x3D;
        break;
      case 0x3A:
        D_80365558[sp1C] = 0x3E;
        break;
    }
  }
  D_80365558[sp1C] = 0xFFE;

  return D_80365558;
}

void func_hd_code_8025B918(u16* arg0, u16* arg1) {
  s32 sp1C;
  s32 sp18;

  sp1C = 0,
  sp18 = func_hd_code_8025B370(arg0);
  while (sp1C < func_hd_code_8025B370(arg1)) {
    arg0[sp18] = arg1[sp1C];

    sp1C++,
    sp18++;
  }
  arg0[sp18] = 0x0FFE;
}
