#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"
#include "macros.h"

// Proposed file name: recording.c (the original name - the assert in
// func_hd_code_8025BEF8 references "recording.c")
//
// This file is the controller input recording/replay system, used both for
// the instant replay after a mission and for the attract-mode demos baked
// into the ROM. Input frames are run-length encoded as
// {buttons hi, buttons lo, repeat count, stick x, stick y} entries.

// Data Begin
char D_hd_code_802E8CB0[16] = "\t \0\0\0\0\0\0\0\0\0\0\0\0\0\0"; // texture id 0x0920 for the blinking replay HUD sprite; proposed name: replaySpriteTexId
s32 D_hd_code_802E8CC0 = 8;
s32 D_hd_code_802E8CC4 = 0;
// Data end

// BSS Begin
u8 D_hd_code_80365580; // replay HUD sprite slot; proposed name: replaySprite
struct S_803669AC D_hd_code_80365588[0x400]; // input recording buffer (run-length encoded); proposed name: inputRecordBuf
s32 pad_80366988;
u8 D_hd_code_8036698C; // vehicle id the demo/recording starts in; proposed name: demoVehicle
s32 D_hd_code_80366990; // recording write index; proposed name: recordWriteIdx
s32 D_hd_code_80366994; // playback read index; proposed name: playbackReadIdx
s32 D_hd_code_80366998; // playback length in entries; proposed name: playbackLength
s32 D_hd_code_8036699C; // run length of the entry currently being recorded; proposed name: recordRunLen
s32 D_hd_code_803669A0; // remaining repeats of the current playback entry; proposed name: playbackRunLeft
u16 D_hd_code_803669A4; // last recorded button state; proposed name: lastButtons
s8 D_hd_code_803669A6; // last recorded stick x; proposed name: lastStickX
s8 D_hd_code_803669A7; // last recorded stick y; proposed name: lastStickY
u8 D_hd_code_803669A8; // recording reset flag (skip the next delta check); proposed name: recordReset
struct S_803669AC* D_hd_code_803669AC; // playback entries (demo data or the record buffer); proposed name: playbackEntries
u8* D_hd_code_803669B0; // demo initial vehicle state blob; proposed name: demoVehicleState
s32 D_hd_code_803669B4; // demo loaded, vehicle state not yet applied; proposed name: demoPending
// BSS end

// Load attract-mode demo arg0: DMA the demo blob from ROM, skip to the
// requested demo (each is a 0x140E-byte record plus a variable-size vehicle
// state blob), and read out the playback length, level number (*arg1),
// starting vehicle id, the input entries and the vehicle state pointer.
// Proposed name: LoadDemo
void func_hd_code_8025B9D0(s32 arg0, s32* arg1) {
  s32 sp34;
  s32* sp30;
  s32 sp2C;
  s32 sp28;
  u16 sp26;
  u8* sp20;

  sp30 = &D_6A9F10;
  sp2C = (s32)&D_6AD3F0 - (s32)&D_6A9F10;
  sp20 = (u8*)D_hd_code_80358070;
  InitiateDma(&D_6A9F10, D_hd_code_80358070, &sp2C, 9U, 0, 1);
  D_hd_code_80358070 += sp2C;
  func_hd_code_80257490((u8** ) &D_hd_code_80358070, 0x10);
  for (sp34 = 0; sp34 < arg0; sp34++) {
    sp28 = (s32) *((s16*)&sp20[0x140C]);
    sp20 = sp20 + sp28 + 0x140E;
  }
  D_hd_code_80366A04 = *((u16*) &sp20[0]);
  sp26 = *((u16*)&sp20[2]);
  D_hd_code_80366998 = *((u16*)&sp20[8]);
  *arg1 = (s32) sp20[0xA];
  D_hd_code_8036698C = sp20[0xB];
  D_hd_code_803669AC = (struct S_803669AC *)&sp20[0xC];
  sp28 = *((s16*)&sp20[0x140C]);
  sp20 += 0x140E;
  func_hd_code_80257490((u8** ) &sp20, 2);
  D_hd_code_803669B0 = sp20;
  D_hd_code_80366994 = 0;
  D_hd_code_803669A0 = (s32) D_hd_code_803669AC->unk2;
  D_hd_code_803669B4 = 1;
}

// Start recording inputs from scratch
// Proposed name: StartRecording
void func_hd_code_8025BB38(void) {
  D_hd_code_80366990 = 0;
  D_hd_code_803669A8 = 1;
}

// Switch to replaying the inputs just recorded (instant replay): point
// playback at the record buffer and load the blinking replay HUD sprite
// Proposed name: StartReplay
void func_hd_code_8025BB50(void) {
  D_hd_code_80366998 = D_hd_code_80366990;
  D_hd_code_80366994 = 0;
  D_hd_code_803669AC = D_hd_code_80365588;
  D_hd_code_80365580 = func_hd_code_80272C5C(D_hd_code_802E8CB0, 0, 1, 1, 1, 1.0f);
  D_hd_code_803669A0 = (s32) D_hd_code_803669AC[D_hd_code_80366994].unk2;
}

// Record one frame of input (buttons, stick x/y), run-length encoded:
// identical consecutive frames just bump the repeat counter; a new entry is
// flushed when the input changes (capacity 0x400 entries)
// Proposed name: RecordInputFrame
void func_hd_code_8025BBE8(u16 arg0, s8 arg1, s8 arg2) {
  if (D_hd_code_803669A8 == 0) {
    if (arg0 != D_hd_code_803669A4 || ((s8) arg1 != D_hd_code_803669A6) || ((s8) arg2 != D_hd_code_803669A7) || (D_hd_code_8036699C == 0xFF) || (D_hd_code_80364A98 != 0) ) {
      if (D_hd_code_80366990 < 0x400) {
        D_hd_code_80365588[D_hd_code_80366990].unk0 = D_hd_code_803669A4 >> 8;
        D_hd_code_80365588[D_hd_code_80366990].unk1 = D_hd_code_803669A4 & 0xFF;
        D_hd_code_80365588[D_hd_code_80366990].unk3 = D_hd_code_803669A6;
        D_hd_code_80365588[D_hd_code_80366990].unk4 = D_hd_code_803669A7;
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
  D_hd_code_803669A6 = (s8) arg1;
  D_hd_code_803669A7 = (s8) arg2;
  D_hd_code_803669A8 = 0;
}

// Apply the demo's initial vehicle state: per-vehicle state-restore dispatch
// with the demo's state blob, then the matching vehicle init, and set it as
// the current vehicle
// Proposed name: ApplyDemoVehicleState
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
  D_hd_code_80364456 = D_hd_code_8036698C;
  D_hd_code_803669B4 = 0;
}

// Playback: feed the current recorded entry into the controller input
// variables (D_hd_code_80370C30/32/33), advancing through run-length
// entries. When playback runs out, either pause the game (instant replay
// end) or fade to the appropriate next state (attract demo cycling, race
// results, "sequence playback over"). During attract/race playback the A
// and B button bits are swapped - the demos were apparently recorded with a
// different mapping.
// Proposed name: PlaybackInputFrame
void func_hd_code_8025BEF8(void) {
    u64 pad;
    if (D_hd_code_80366994 > D_hd_code_80366998  || ((D_hd_code_803643DB != 0) && (D_hd_code_803643D6 != 0) && ((D_hd_code_80364A90 & 0x440)))) {
        if ((D_hd_code_8036BB1C != 1) || (((D_hd_code_80364A90 & 0x440)) && ((u8) D_hd_code_80364A50 == 0))) {
            if (D_hd_code_802E8BD0 == 0) {
                D_hd_code_802E8BD8 = 1;
            }
        } else if (areWeFading() == 0) {
            switch(D_hd_code_80364A90) {
                case 0x2:
                    func_hd_code_80275270(2, 0.25f);
                    break;
                case 0x100000000000:
                    rmonPrintf("sequence playback over\n");
                    func_hd_code_80275390(0x0000200000000000);
                    break;
                case 0x40:
                case 0x400:
                    D_hd_code_802E8BD8 = 1;
                    if(D_hd_code_80364A90 == 0x400) {
                        func_hd_code_80275270(0x40, 1.25f);
                        break;
                    }
                    func_hd_code_80275270(0x40, 0.5f);
                    break;
                default:
                    rmonPrintf(ASSERT_MESSAGE, "1==0", "recording.c", 0x184);
                    break;
            }
            return;
        }
    } else {
        D_hd_code_80370C30 = (D_hd_code_803669AC[D_hd_code_80366994].unk0 << 8) + D_hd_code_803669AC[D_hd_code_80366994].unk1;
        D_hd_code_80370C32 = D_hd_code_803669AC[D_hd_code_80366994].unk3;
        D_hd_code_80370C33 = D_hd_code_803669AC[D_hd_code_80366994].unk4;
        D_hd_code_803669A0--;
        if (D_hd_code_803669A0 < 0) {
            D_hd_code_80366994++;
            D_hd_code_803669A0 = D_hd_code_803669AC[D_hd_code_80366994].unk2;
        }
        if (((D_hd_code_80364A90 & 0x100000000002)) && (D_hd_code_8036698C != 9)) {
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
