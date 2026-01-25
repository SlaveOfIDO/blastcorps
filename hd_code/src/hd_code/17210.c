#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"

s32 D_80366994;
s32 D_80366998;

void func_hd_code_8025B9D0(s32 arg0, s32* arg1) {
  s32 sp34;
  s32* sp30;
  s32 sp2C;
  s32 sp28;
  u16 sp26;
  u8* sp20;

  sp30 = &D_6A9F10;
  sp2C = (s32)&D_6AD3F0 - (s32)&D_6A9F10;
  sp20 = (u8*)D_80358070;
  InitiateDma(&D_6A9F10, D_80358070, &sp2C, 9U, 0, 1);
  D_80358070 += sp2C;
  func_hd_code_80257490((u8** ) &D_80358070, 0x10);
  for (sp34 = 0; sp34 < arg0; sp34++) {
    sp28 = (s32) *((s16*)&sp20[0x140C]);
    sp20 = sp20 + sp28 + 0x140E;
  }
  D_80366A04 = *((u16*) &sp20[0]);
  sp26 = *((u16*)&sp20[2]);
  D_80366998 = *((u16*)&sp20[8]);
  *arg1 = (s32) sp20[0xA];
  D_8036698C = sp20[0xB];
  D_803669AC = (struct S_803669AC *)&sp20[0xC];
  sp28 = *((s16*)&sp20[0x140C]);
  sp20 += 0x140E;
  func_hd_code_80257490((u8** ) &sp20, 2);
  D_803669B0 = sp20;
  D_80366994 = 0;
  D_803669A0 = (s32) D_803669AC->unk2;
  D_803669B4 = 1;
}

void func_hd_code_8025BB38(void) {
  D_80366990 = 0;
  D_803669A8 = 1;
}

void func_hd_code_8025BB50(void) {
  D_80366998 = D_80366990;
  D_80366994 = 0;
  D_803669AC = D_80365588;
  D_80365580 = func_hd_code_80272C5C(&D_hd_code_802E8CB0, 0, 1, 1, 1, 1.0f);
  D_803669A0 = (s32) D_803669AC[D_80366994].unk2;
}

void func_hd_code_8025BBE8(u16 arg0, s8 arg1, s8 arg2) {
  if (D_803669A8 == 0) {
    if (arg0 != D_803669A4 || ((s8) arg1 != D_803669A6) || ((s8) arg2 != D_803669A7) || (D_8036699C == 0xFF) || (D_80364A98 != 0) ) {
      if (D_80366990 < 0x400) {
        D_80365588[D_80366990].unk0 = D_803669A4 >> 8;
        D_80365588[D_80366990].unk1 = D_803669A4 & 0xFF;
        D_80365588[D_80366990].unk3 = D_803669A6;
        D_80365588[D_80366990].unk4 = D_803669A7;
        D_80365588[D_80366990].unk2 = D_8036699C;
        D_80366990 += 1;
        D_8036699C = 0;
      }
    } else {
      D_8036699C += 1;
    }
  } else {
    D_8036699C = 0;
  }
  D_803669A4 = arg0;
  D_803669A6 = (s8) arg1;
  D_803669A7 = (s8) arg2;
  D_803669A8 = 0;
}

void func_hd_code_8025BD98() {
  switch (D_8036698C) {
    case 3:
      func_hd_code_802B40D4(D_803669B0);
      func_hd_code_802B2D7C();
      break;
    case 0:
      func_hd_code_802AFC28(D_803669B0);
      break;
    case 1:
      func_hd_code_802B0D70(D_803669B0);
      func_hd_code_802AFFD4();
      break;
    case 2:
      func_hd_code_802B2988(D_803669B0);
      func_hd_code_802B1228();
      break;
    case 16:
      func_hd_code_802D2524(D_803669B0);
      func_hd_code_802D0C68();
      break;
    case 4:
      func_hd_code_802B58C8(D_803669B0);
      func_hd_code_802B448C();
      break;
    case 5:
      func_hd_code_802B7308(D_803669B0);
      func_hd_code_802B5CD8();
      break;
    case 9:
      func_hd_code_802C80A0(D_803669B0);
      func_hd_code_802C5714();
      break;
    case 10:
      func_hd_code_802CB660(D_803669B0);
      func_hd_code_802C9F54();
      break;
  }
  if (D_8036698C != 0) {
    D_803649E8 = 1;
  }
  D_hd_code_80364456 = D_8036698C;
  D_803669B4 = 0;
}

void func_hd_code_8025BEF8(void) {
    u64 pad;
    if (D_80366994 > D_80366998  || ((D_hd_code_803643DB != 0) && (D_hd_code_803643D6 != 0) && ((D_hd_code_80364A90 & 0x440)))) {
        if ((D_8036BB1C != 1) || (((D_hd_code_80364A90 & 0x440)) && ((u8) D_80364A50 == 0))) {
            if (D_hd_code_802E8BD0 == 0) {
                D_hd_code_802E8BD8 = 1;
            }
        } else if (areWeFading() == 0) {
            switch(D_hd_code_80364A90) {
                case 0x2:
                    func_hd_code_80275270(2, 0x3E800000);
                    break;
                case 0x100000000000:
                    func_hd_code_8029A7E4("sequence playback over\n");
                    func_hd_code_80275390(0x0000200000000000);
                    break;
                case 0x40:
                case 0x400:
                    D_hd_code_802E8BD8 = 1;
                    if(D_hd_code_80364A90 == 0x400) {
                        func_hd_code_80275270(0x40, 0x3FA00000);
                        break;
                    }
                    func_hd_code_80275270(0x40, 0x3F000000);
                    break;
                default:
                    func_hd_code_8029A7E4("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "1==0", "recording.c", 0x184);
                    break;
            }
            return;
        }
    } else {
        D_80370C30 = (D_803669AC[D_80366994].unk0 << 8) + D_803669AC[D_80366994].unk1;
        D_80370C32 = D_803669AC[D_80366994].unk3;
        D_80370C33 = D_803669AC[D_80366994].unk4;
        D_803669A0--;
        if (D_803669A0 < 0) {
            D_80366994++;
            D_803669A0 = D_803669AC[D_80366994].unk2;
        }
        if (((D_hd_code_80364A90 & 0x100000000002)) && (D_8036698C != 9)) {
            if ((D_80370C30 & 0xC000) == 0x8000) {
                D_80370C30 = D_80370C30 & 0xFFFF7FFF;
                D_80370C30 = D_80370C30 | 0x4000;
            }
            if ((D_80370C30 & 0xC000) == 0x4000) {
                D_80370C30 = D_80370C30 & ~0x4000;
                D_80370C30 = D_80370C30 | 0x8000;
            }
        }
    }
}
