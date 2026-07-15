#include "common.h"
#include "functions.h"
#include "hd.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"
#include "yoshi.h"

#define LEVEL_SAVE_SIZE 0x40

void func_hd_code_802C4BF0(u8*);
u32 create_status(u8*, u8);
s32 func_hd_code_8026AD30(s16);
u32 func_hd_code_802852EC();                          /* extern */

extern u16 D_hd_code_80364EF0[][0x10];
extern s32 D_hd_code_80364A9C;
extern s32 D_hd_code_80358064;
extern u8 D_hd_code_8036EB94[4];
extern u8 D_hd_code_8036EB9C[4];

// Proposed file name: stats_perm.c (the original name - the asserts in
// func_hd_code_80285814 reference "stats_perm.c")
//
// This file handles the per-level statistics: the four scored objectives -
// buildings destroyed (D_hd_code_8036EA78 / target D_hd_code_8036EB92), RDUs found
// (D_hd_code_8036EA7C / D_hd_code_8036EB90), points/communication points (D_hd_code_8036EA79 /
// D_hd_code_8036EB93), and the time/par - their percentages and the results-screen
// text/highlights, the per-level medal save bits, and the controller-pak
// save record. Mirror snapshots of the stats block (D_hd_code_8036EA60/80/90) hold
// the values at level start / last checkpoint for comparison.

// Load the level's target stats for the current player at level start:
// the par time (from the medal-tier table D_hd_code_80364EF0), the current
// medal, and whether the level is already completed (D_hd_code_8036EB98)
// Proposed name: LoadLevelStats
void func_hd_code_80285190(void) {
  s32 sp4;

  D_hd_code_8036EA7B = players[playerNumber].unk92[levelno];
  D_hd_code_8036EA74 = (s32) D_hd_code_80364EF0[playerNumber][D_hd_code_802E8C44[D_hd_code_802E8F94[levelno].unk0 == 1 ? 1 : D_hd_code_8036EA7B]];
  D_hd_code_8036EA7A = (u8) ((s32) players[playerNumber].unk18[levelno] % 8);

  for(sp4 = 0; sp4 < 4; sp4++) {
    D_hd_code_8036EB94[sp4] = 0;
  }

  if (players[playerNumber].unk18[levelno] > 0 && players[playerNumber].unk18[levelno] < 6) {
    D_hd_code_8036EB98 = 1;
    return;
  }
  D_hd_code_8036EB98 = 0;
}

// Build the results-screen stat lines and highlights: format the four
// objective rows ("count (percent%)", money, time), and set each row's
// window flags - highlighting (flag 4) the objectives that improved over the
// saved snapshot. Returns the overall completion percentage (average of the
// scored objectives; 2 of 3 when there's no controller pak).
// Proposed name: BuildStatsScreen
u32 func_hd_code_802852EC(void) {
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    u32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    u8 sp24[0x20];

    sp48 = 0;
    sp44 = 0;
    if (D_hd_code_8036EB92 != 0) {
        sp5C = (D_hd_code_8036EA78 * 0x64) / D_hd_code_8036EB92;
    } else {
        sp5C = 0x64;
    }
    if (D_hd_code_8036EB93 != 0) {
        sp58 = (D_hd_code_8036EA79 * 0x64) / D_hd_code_8036EB93;
    } else {
        sp58 = 0x64;
    }
    if (D_hd_code_8036EB90 != 0) {
        sp54 = (D_hd_code_8036EA7C * 0x64) / D_hd_code_8036EB90;
    } else {
        sp54 = 0x64;
    }
    proutSprintf(D_hd_code_8036B9A8, "***%2d (%d%c)*", D_hd_code_8036EA78, sp5C, 0x25);
    proutSprintf(D_hd_code_8036B9A8 + 0x20, "***$%d*", D_hd_code_8036EA70);
    proutSprintf(D_hd_code_8036B9A8 + 0x40, "***%2d (%d%c)*", D_hd_code_8036EA79, sp58, 0x25);
    proutSprintf(D_hd_code_8036B9A8 + 0x60, "***%2d (%d%c)*", D_hd_code_8036EA7C, sp54, 0x25);
    func_hd_code_80264A34(sp24, D_hd_code_8036EA74, 0);
    proutSprintf(D_hd_code_8036B9A8 + 0x80, "***%s*", &sp24);
    for(sp50 = 0x12; sp50 < 0x17;sp50++) {
        D_hd_code_802F5804[sp50].unk0 = 0x400;
    }

    for(sp50 = 0xE; sp50 < 0x12; sp50++) {
        D_hd_front_end_8020C070[sp50].unk0 = 0x400;
    }

    if ((D_hd_code_80364A98 == 0x40)) {
        sp48 = 0x100;
    }
    if (D_hd_code_80364A90 & 0x30C) {
        sp44 = 0x100;
    }
    if (D_hd_code_8036EA78 > D_hd_code_8036EA68) {
        sp4C = sp44 | 4;
    } else {
        sp4C = 0;
    }
    D_hd_front_end_8020C070[0xE].unk0 |= sp4C | 0x80;
    D_hd_code_802F5804[0x12].unk0 |= sp4C | sp48 | 0x80;
    if ((u32) D_hd_code_8036EA70 > (u32) D_hd_code_8036EA60) {
        sp4C = sp44 | 4;
    } else {
        sp4C = 0;
    }
    D_hd_front_end_8020C070[0xF].unk0 |= sp4C | 0x80;
    D_hd_code_802F5804[0x13].unk0 |= sp4C | sp48 | 0x80;
    if (D_hd_code_8036EA79 > D_hd_code_8036EA69) {
        sp4C = sp44 | 4;
    } else {
        sp4C = 0;
    }
    D_hd_front_end_8020C070[0x10].unk0 |= sp4C | 0x80;
    D_hd_code_802F5804[0x14].unk0 |= sp4C | sp48 | 0x80;
    if (D_hd_code_8036EA7C > D_hd_code_8036EA6C) {
        sp4C = sp44 | 4;
    } else {
        sp4C = 0;
    }
    D_hd_front_end_8020C070[0x11].unk0 |= sp4C | 0x80;
    D_hd_code_802F5804[0x15].unk0 |= sp4C | sp48 | 0x80;
    D_hd_code_802F5804[0x16].unk0 |= sp48 | 0x80;
    if (D_hd_code_802E8BF8 != 0) {
        return (sp5C + sp54) / 2U;
    }
    return (sp5C + sp58 + sp54) / 3U;
}

// Switch to the player selected on the world map: re-init the level, and if
// it's a completed demolition level with a valid save record, recreate the
// pak status block and restore the destroyed-buildings state. Returns 1 if
// the saved state was applied. Snapshots the stats into all mirror copies.
// Proposed name: SwitchToSelectedPlayer
u8 func_hd_code_80285814(void) {
  u8 sp27;
  u8 coin;

  sp27 = 0;
  if (!frontEndPresent) {
    rmonPrintf(ASSERT_MESSAGE, "frontEndPresent", "stats_perm.c", 0x8C);
  }
  frontEndPresent = 1;
  func_hd_code_80255DC8();
  if ((D_hd_code_80364A90 == 0x4000)) {
    osRecvMesg(&D_hd_front_end_80219F50, NULL, 1);
  }
  if ((players[playerNumber].unk18[levelno] > 0 && players[playerNumber].unk18[levelno] < 6)?1:0) {
    if (D_hd_code_802E8F94[levelno].unk0 == 1) {
      if (*(u64*)pakBuffer == 0x1234567887654321) {
        func_hd_code_80256A34(NULL);
        rmonPrintf("Creating status ...\n");
        coin = players[playerNumber].unk18[levelno];
        if (coin == 5) {
          coin = 4;
        }
        if (!(create_status(pakBuffer, coin) <= LEVEL_SAVE_SIZE-4)) {
          rmonPrintf(ASSERT_MESSAGE, "create_status(pakBuffer,coin)<=LEVEL_SAVE_SIZE-4", "stats_perm.c", 0xA1);
        }
        func_hd_code_802C4BF0(pakBuffer);
        func_hd_code_802C1DD0(0);
        func_hd_code_80264C20((s32) pakBuffer);
        sp27 = 1;
      } else {
        func_hd_code_80256A34((s32* ) pakBuffer);
      }
    } else {
      func_hd_code_80256A34(NULL);
    }
  } else {
    func_hd_code_80256A34(NULL);
  }
  func_hd_code_80285A78((s32* ) &D_hd_code_8036EA70, &D_hd_code_8036EA60);
  func_hd_code_80285A78((s32* ) &D_hd_code_8036EA70, &D_hd_code_8036EA80);
  func_hd_code_80285A78((s32* ) &D_hd_code_8036EA70, &D_hd_code_8036EA90);
  return sp27;
}

// Copy a 16-byte stats block from arg0 to arg1 (snapshot/restore)
// Proposed name: CopyStatsBlock
void func_hd_code_80285A78(u8* arg0, u8* arg1) {
  u32 sp4;

  for(sp4 = 0; sp4 < 16; sp4++) {
    arg1[sp4] = arg0[sp4];
  }
}

// Mark sub-objective arg0 (one of the high save bits) as achieved on this
// level and flag the save as dirty
// Proposed name: SetObjectiveBit
void func_hd_code_80285AB0(u8 arg0) {
  D_hd_code_80364A87 |= 2;
  players[playerNumber].unk54[levelno] |= (1 << (arg0 + 0x1F));
}

// Has sub-objective arg0 been achieved on this level?
// Proposed name: GetObjectiveBit
s32 func_hd_code_80285B10(u8 arg0) {
  return (players[playerNumber].unk54[levelno] & (1 << (arg0 + 0x1F))) ? 1 : 0;
}

// Demolition-level checkpoint: when a completed non-demolition objective is
// re-cleared, save the result, fade to the results state and mark the level
// done
// Proposed name: TriggerLevelCheckpoint
void func_hd_code_80285B68(s32 arg0) {
  if (D_hd_code_80364A90 & 0x104) {
    if (((players[playerNumber].unk18[levelno] > 0 && players[playerNumber].unk18[levelno] < 6)?1:0) && (D_hd_code_802E8F94[levelno].unk0 != 1) && (playerNumber == D_hd_code_80364AEA)) {
      func_hd_code_802CF5B0();
      D_hd_code_802E8BD8 = 1;
      func_hd_code_80275270(0x4000, 1.25f);
      saveIt[playerNumber] = levelno + 1;
      D_hd_code_8036EB99 = 1;
    }
  }
}

// Show the "level complete" message window (0x47)
// Proposed name: ShowLevelCompleteMessage
void func_hd_code_80285CA0() {
  func_hd_code_8026AD30(0x47);
}

// Check each scored objective for newly hitting 100% this frame and fire the
// matching "all X found/destroyed" announcement window (0x39-0x3B), plus a
// special fanfare (0x3C + sfx 0xC6) when all three are complete at once
// Proposed name: CheckObjectivesComplete
void func_hd_code_80285CC0() {
  s32 sp34;
  s32 sp30;
  s32 sp2C;

  sp34 = -1;
  sp30 = 0;
  for(sp2C = 0; sp2C < 4; sp2C++) {
    D_hd_code_8036EB9C[sp2C] = D_hd_code_8036EB94[sp2C];
    if (D_hd_code_8036EB94[sp2C] == 0) {
      switch (sp2C) {                         /* irregular */
        case 0:
          ;
          if (D_hd_code_8036EB94[sp2C] = (D_hd_code_8036EA7C == D_hd_code_8036EB90)) {
            sp34 = 0x39;
          }
          break;
        case 1:
          if (D_hd_code_8036EB94[sp2C] = (D_hd_code_8036EA79 == D_hd_code_8036EB93)) {
            sp34 = 0x3A;
          }
          break;
        case 2:
          func_hd_code_802C1DD0(0);
          if (D_hd_code_8036EB94[sp2C] = (D_hd_code_8036EA78 == D_hd_code_8036EB92)) {
            sp34 = 0x3B;
          }
          break;
        case 3:

          if (D_hd_code_8036EB94[sp2C] = D_hd_code_8036EB94[0] && D_hd_code_8036EB94[2] && D_hd_code_8036EB94[1]) {
            sp34 = 0x3C;
            sp30 = 0xC6;
          }
          break;
      }
    }
  }

  if (D_hd_code_80358064 != 0) {
    if ((sp34 != -1) && !(func_hd_code_8026B10C() & 0x8000)) {
      func_hd_code_8026AF6C(sp34 | 0x8000);
    }
    if (sp30 != 0) {
      sndPlaySfx(D_hd_code_80367738, (s16) sp30, NULL);
    }
  }
}

// Show the time-bonus / par result window: temporarily add the elapsed-time
// bonus into the stats, rebuild the screen, then open window 0x06 with the
// time row highlighted (arg0 = level start frame)
// Proposed name: ShowTimeBonus
void func_hd_code_80285EF4(s32 arg0) {
  s32 sp1C;

  sp1C = func_hd_code_8028604C(D_hd_code_803156C0 - arg0);
  func_hd_code_802C1DD0(0);
  D_hd_code_8036EA74 += sp1C;
  func_hd_code_802852EC();
  D_hd_code_8036EA74 -= sp1C;
  func_hd_code_80285A78((s32* ) &D_hd_code_8036EA70, &D_hd_code_8036EA60);
  D_hd_code_802F5804[0x18].unk0 &= ~1;
  D_hd_code_802F5804[0x18].unk0 |= 0x800;
  D_hd_code_802F5804[0x17].unk0 &= ~1;
  D_hd_code_802F5804[0x17].unk0 |= 0x800;
  D_hd_code_802F5804[0x11].unk0 |= 1;
  D_hd_code_802F5804[0x11].unk0 &= ~0x800;
  D_hd_code_802F8BDC[6].unk18 = 0x11;
  D_hd_code_802F8BDC[6].unk8 |= 0x80;
  func_hd_code_8026AF6C(0x8006U);
  D_hd_code_802F8BDC[6].unkC = 0;
  D_hd_code_802E8BD8 = 1;
}

// Convert a time value in the stat units back to frames (x6)
// Proposed name: TimeUnitsToFrames
s32 func_hd_code_80286038(u16 arg0) {
  return arg0  * 6;
}

// Convert frames to the stat time units (frames / 6, capped), used by the
// timer/par calculations
// Proposed name: FramesToTimeUnits
u16 func_hd_code_8028604C(s32 arg0) {
  return MIN(0xEA5F, arg0 / 6U);
}

// Has level lvl been completed (medal 1..5)?
// Proposed name: IsLevelCompleted
u8 func_hd_code_80286090(s32 lvl) {
  return (players[playerNumber].unk18[lvl] > 0 && players[playerNumber].unk18[lvl] < 6)?1:0;
}
