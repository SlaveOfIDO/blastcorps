#include "common.h"
#include "functions.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"

// <bss>
u8 D_hd_code_80365580;
struct S_803669AC D_hd_code_80365588[0x400];
s32 pad_80366988;
u8 D_hd_code_8036698C;
s32 D_hd_code_80366990;
s32 D_hd_code_80366994;
s32 D_hd_code_80366998;
s32 D_hd_code_8036699C;
s32 D_hd_code_803669A0;
u16 D_hd_code_803669A4;
s8 g_previousStickX;
s8 g_previousStickY;
u8 D_hd_code_803669A8;
struct S_803669AC* D_hd_code_803669AC;
u8* D_hd_code_803669B0;
s32 D_hd_code_803669B4;
// </bss>

// <data>
char D_hd_code_802E8CB0[16] = "\t \0\0\0\0\0\0\0\0\0\0\0\0\0\0";
s32 D_hd_code_802E8CC0 = 8;
s32 D_hd_code_802E8CC4 = 0;
// </data>

void func_hd_code_8025B9D0(s32 arg0, s32* arg1) {
  s32 sp34;
  s32* sp30;
  s32 sp2C;
  s32 sp28;
  u16 sp26;
  u8* sp20;

  sp30 = &attract_ROM_START;
  sp2C = (s32)&attract2_ROM_START - (s32)&attract_ROM_START;
  sp20 = g_heap;
  INITIATE_DMA(&attract_ROM_START, g_heap, &sp2C, 9U, 0, 1);
  g_heap += sp2C;
  hdAlignPointer(&g_heap, 0x10);
  for (sp34 = 0; sp34 < arg0; sp34++) {
    sp28 = (s32) * ((s16*)&sp20[0x140C]);
    sp20 = sp20 + sp28 + 0x140E;
  }
  D_hd_code_80366A04 = *((u16*)&sp20[0]);
  sp26 = *((u16*)&sp20[2]);
  D_hd_code_80366998 = *((u16*)&sp20[8]);
  *arg1 = (s32)sp20[0xA];
  D_hd_code_8036698C = sp20[0xB];
  D_hd_code_803669AC = (struct S_803669AC*)&sp20[0xC];
  sp28 = *((s16*)&sp20[0x140C]);
  sp20 += 0x140E;
  hdAlignPointer(&sp20, 2);
  D_hd_code_803669B0 = sp20;
  D_hd_code_80366994 = 0;
  D_hd_code_803669A0 = (s32)D_hd_code_803669AC->unk2;
  D_hd_code_803669B4 = 1;
}

void func_hd_code_8025BB38(void) {
  D_hd_code_80366990 = 0;
  D_hd_code_803669A8 = 1;
}

void func_hd_code_8025BB50(void) {
  D_hd_code_80366998 = D_hd_code_80366990;
  D_hd_code_80366994 = 0;
  D_hd_code_803669AC = D_hd_code_80365588;
  D_hd_code_80365580 = func_hd_code_80272C5C(D_hd_code_802E8CB0, 0, 1, 1, 1, 1.0f);
  D_hd_code_803669A0 = (s32)D_hd_code_803669AC[D_hd_code_80366994].unk2;
}

void func_hd_code_8025BBE8(u16 arg0, s8 stickX, s8 stickY) {
  if (D_hd_code_803669A8 == 0) {
    if (arg0 != D_hd_code_803669A4 || stickX != g_previousStickX || stickY != g_previousStickY ||
        D_hd_code_8036699C == 0xFF || g_nextGameState != 0) {
      if (D_hd_code_80366990 < 0x400) {
        D_hd_code_80365588[D_hd_code_80366990].unk0 = D_hd_code_803669A4 >> 8;
        D_hd_code_80365588[D_hd_code_80366990].unk1 = D_hd_code_803669A4 & 0xFF;
        D_hd_code_80365588[D_hd_code_80366990].unk3 = g_previousStickX;
        D_hd_code_80365588[D_hd_code_80366990].unk4 = g_previousStickY;
        D_hd_code_80365588[D_hd_code_80366990].unk2 = D_hd_code_8036699C;
        D_hd_code_80366990 += 1;
        D_hd_code_8036699C = 0;
      }
    } else {
      D_hd_code_8036699C += 1;
    }
  } else {
    D_hd_code_8036699C = 0;
  }
  D_hd_code_803669A4 = arg0;
  g_previousStickX = stickX;
  g_previousStickY = stickY;
  D_hd_code_803669A8 = 0;
}

void func_hd_code_8025BD98() {
  switch (D_hd_code_8036698C) {
    case 3:
      func_hd_code_802B40D4(D_hd_code_803669B0);
      func_hd_code_802B2D7C();
      break;
    case 0:
      func_hd_code_802AFC28(D_hd_code_803669B0);
      break;
    case 1:
      func_hd_code_802B0D70(D_hd_code_803669B0);
      func_hd_code_802AFFD4();
      break;
    case 2:
      func_hd_code_802B2988(D_hd_code_803669B0);
      func_hd_code_802B1228();
      break;
    case 16:
      func_hd_code_802D2524(D_hd_code_803669B0);
      func_hd_code_802D0C68();
      break;
    case 4:
      func_hd_code_802B58C8(D_hd_code_803669B0);
      func_hd_code_802B448C();
      break;
    case 5:
      func_hd_code_802B7308(D_hd_code_803669B0);
      func_hd_code_802B5CD8();
      break;
    case 9:
      func_hd_code_802C80A0(D_hd_code_803669B0);
      func_hd_code_802C5714();
      break;
    case 10:
      func_hd_code_802CB660(D_hd_code_803669B0);
      func_hd_code_802C9F54();
      break;
  }
  if (D_hd_code_8036698C != 0) {
    D_hd_code_803649E8 = 1;
  }
  g_currentVehicleType = D_hd_code_8036698C;
  D_hd_code_803669B4 = 0;
}

void func_hd_code_8025BEF8(void) {
  u64 pad;
  if (D_hd_code_80366994 > D_hd_code_80366998 ||
      ((D_hd_code_803643DB != 0) && (D_hd_code_803643D6 != 0) && ((g_currentGameState & 0x440)))) {
    if ((D_hd_code_8036BB1C != 1) || (((g_currentGameState & 0x440)) && ((u8)D_hd_code_80364A50 == 0))) {
      if (!g_gamePaused) {
        D_hd_code_802E8BD8 = 1;
      }
    } else if (areWeFading() == 0) {
      switch (g_currentGameState) {
        case 0x2:
          fadeTo(2, 0.25f);
          break;
        case 0x100000000000:
          rmonPrintf("sequence playback over\n");
          fadeToFast(0x0000200000000000);
          break;
        case 0x40:
        case 0x400:
          D_hd_code_802E8BD8 = 1;
          if (g_currentGameState == 0x400) {
            fadeTo(0x40, 1.25f);
            break;
          }
          fadeTo(0x40, 0.5f);
          break;
        default:
          rmonPrintf(ASSERT_MESSAGE, "1==0", "recording.c", 0x184);
          break;
      }
      return;
    }
  } else {
    D_hd_code_80370C30 =
        (D_hd_code_803669AC[D_hd_code_80366994].unk0 << 8) + D_hd_code_803669AC[D_hd_code_80366994].unk1;
    D_hd_code_80370C32 = D_hd_code_803669AC[D_hd_code_80366994].unk3;
    D_hd_code_80370C33 = D_hd_code_803669AC[D_hd_code_80366994].unk4;
    D_hd_code_803669A0--;
    if (D_hd_code_803669A0 < 0) {
      D_hd_code_80366994++;
      D_hd_code_803669A0 = D_hd_code_803669AC[D_hd_code_80366994].unk2;
    }
    if (((g_currentGameState & 0x100000000002)) && (D_hd_code_8036698C != 9)) {
      if ((D_hd_code_80370C30 & 0xC000) == 0x8000) {
        D_hd_code_80370C30 = D_hd_code_80370C30 & 0xFFFF7FFF;
        D_hd_code_80370C30 = D_hd_code_80370C30 | 0x4000;
      }
      if ((D_hd_code_80370C30 & 0xC000) == 0x4000) {
        D_hd_code_80370C30 = D_hd_code_80370C30 & ~0x4000;
        D_hd_code_80370C30 = D_hd_code_80370C30 | 0x8000;
      }
    }
  }
}
