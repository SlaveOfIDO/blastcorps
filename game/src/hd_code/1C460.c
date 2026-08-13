#include "common.h"
#include "functions.h"
#include "gu/guint.h"
#include "snd.h"
#include "structs.h"
#include "variables.h"
// Proposed file name: music.c
//
// This file is the music/sequence player module: it manages MIDI sequence
// playback via the compressed sequence player (ALCSPlayer), a "tune stack"
// for interrupting music with jingles and resuming where it left off
// (including seq position, tempo and channel state), volume fades,
// per-level track selection, and SFX dispatch.

// BSS Begin
struct S_80367400 D_hd_code_80366C30[4]; // tune stack: saved seq location/tempo/channel state + tune id per frame; proposed name: tuneStack
struct S_80367400* D_hd_code_80367400; // tune stack pointer (current frame); proposed name: tuneStackPtr
s32 D_hd_code_80367408[0x42]; // per-sequence data length (rounded up to even), one per tune in seq file; proposed name: tuneDataLengths
void* D_hd_code_80367510; // sequence data buffer the current tune is DMA'd into; proposed name: seqDataBuffer
ALSeqFile *D_hd_code_80367514; // sequence file header (66 tunes); proposed name: seqFile
ALCSeq D_hd_code_80367518[2]; // double-buffered compressed sequences (index = D_hd_code_802E8D84); proposed name: seqDoubleBuffer
u8 D_hd_code_80367708; // currently playing tune id; proposed name: currentTune
f32 D_hd_code_8036770C; // current/target music volume scale (fade target); proposed name: musicVolTarget
f32 D_hd_code_80367710; // per-level volume scale applied when (re)starting a tune; proposed name: levelMusicVol
f32 D_hd_code_80367714; // volume scale to resume at after a pop; proposed name: popResumeVol
ALHeap D_hd_code_80367718; // audio heap; proposed name: audioHeap
u8 D_hd_code_80367728; // pop state machine: 2 = waiting for stop, 1 = waiting for play to restore state, 0 = idle; proposed name: tunePopState
u8 D_hd_code_80367729; // push state machine: 1 = waiting to snapshot state, 2 = waiting for stop, 0 = idle; proposed name: tunePushState
u8 D_hd_code_8036772A; // volume fade in progress flag; proposed name: musicFadeActive
s32 D_hd_code_8036772C; // saved tempo to restore once player is playing; proposed name: savedTempo
s8 D_hd_code_80367730; // set when tune stack is at the bottom (nothing pushed); proposed name: tuneStackEmpty
ALCSPlayer* D_hd_code_80367734; // the compressed MIDI sequence player; proposed name: seqPlayer
ALBank* D_hd_code_80367738; // SFX instrument bank; proposed name: sfxBank
ALBank* D_hd_code_8036773C; // music instrument bank; proposed name: musicBank
s32 D_hd_code_80367740; // saved timer/frame counter (set alongside results music); proposed name: resultsMusicStartFrame
// BSS End

// Data
// Per-tune base volume, one entry per sequence in the seq file
// Proposed name: tuneVolumes
s16 D_hd_code_802E8D00[66] = {
  0x6590,
  0x6FB8,
  0x6FB8,
  0x6FB8,
  0x6590,
  0x6FB8,
  0x6590,
  0x6590,
  0x6FB8,
  0x55F0,
  0x6590,
  0x6FB8,
  0x6590,
  0x6590,
  0x6590,
  0x7FFF,
  0x7530,
  0x6590,
  0x6FB8,
  0x6590,
  0x6FB8,
  0x6590,
  0x6FB8,
  0x6FB8,
  0x6590,
  0x6FB8,
  0x6590,
  0x6590,
  0x7FFF,
  0x6590,
  0x6590,
  0x6590,
  0x6FB8,
  0x6590,
  0x7FFF,
  0x7530,
  0x6590,
  0x6590,
  0x5B68,
  0x6590,
  0x6590,
  0x6FB8,
  0x7FFF,
  0x6FB8,
  0x6FB8,
  0x7530,
  0x7FFF,
  0x6590,
  0x6FB8,
  0x6FB8,
  0x6590,
  0x6590,
  0x7530,
  0x7530,
  0x6590,
  0x6590,
  0x6590,
  0x7530,
  0x6FB8,
  0x6FB8,
  0x6590,
  0x6590,
  0x6FB8,
  0x6590,
  0x7FFF,
  0x6FB8
};
u8 D_hd_code_802E8D84 = 0; // Can be either 0 or 1; double-buffer index into D_hd_code_80367518, toggled each tune start; proposed name: seqBufIdx
f32 D_hd_code_802E8D88 = 1.0f; // master music volume multiplier; proposed name: musicMasterVol
// Per-level default tune id, indexed by levelno
// Proposed name: levelTunes
u8 D_hd_code_802E8D8C[60] = {
  0x08,
  0x01,
  0x05,
  0x0B,
  0x11,
  0x02,
  0x29,
  0x10,
  0x12,
  0x08,
  0x0B,
  0x1F,
  0x08,
  0x06,
  0x06,
  0x06,
  0x2A,
  0x05,
  0x08,
  0x2A,
  0x1F,
  0x1F,
  0x10,
  0x10,
  0x10,
  0x07,
  0x0B,
  0x1F,
  0x29,
  0x22,
  0x12,
  0x07,
  0x02,
  0x01,
  0x23,
  0x05,
  0x22,
  0x12,
  0x26,
  0x05,
  0x15,
  0x07,
  0x1F,
  0x15,
  0x04,
  0x15,
  0x04,
  0x15,
  0x02,
  0x0D,
  0x12,
  0x07,
  0x15,
  0x04,
  0x2A,
  0x0B,
  0x10,
  0x0B,
  0x04,
  0x22
};

// Per-level push/jingle tune id, indexed by levelno (0 = none)
// Proposed name: levelJingles
u8 D_hd_code_802E8DC8[60] = {
  0x14,
  0x20,
  0x17,
  0x16,
  0x1B,
  0x19,
  0x00,
  0x00,
  0x00,
  0x14,
  0x16,
  0x00,
  0x14,
  0x1E,
  0x1E,
  0x1E,
  0x1C,
  0x17,
  0x14,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x16,
  0x00,
  0x00,
  0x1C,
  0x00,
  0x00,
  0x00,
  0x20,
  0x00,
  0x17,
  0x00,
  0x00,
  0x00,
  0x00,
  0x09,
  0x00,
  0x00,
  0x00,
  0x1A,
  0x00,
  0x1A,
  0x24,
  0x19,
  0x0D,
  0x20,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x16,
  0x1A,
  0x00
};

// Per-level tune id set (used by func_hd_code_80260E2C, likely results/end-of-level music), indexed by levelno
// Proposed name: levelResultsTunes
u8 D_hd_code_802E8E04[60] = {
  0x2B,
  0x35,
  0x31,
  0x2C,
  0x38,
  0x30,
  0x32,
  0x34,
  0x35,
  0x2B,
  0x2C,
  0x2F,
  0x2B,
  0x32,
  0x32,
  0x32,
  0x2E,
  0x31,
  0x2B,
  0x2E,
  0x2F,
  0x2F,
  0x34,
  0x34,
  0x34,
  0x36,
  0x2C,
  0x2F,
  0x32,
  0x2E,
  0x35,
  0x36,
  0x30,
  0x35,
  0x2D,
  0x31,
  0x2E,
  0x35,
  0x26,
  0x31,
  0x37,
  0x36,
  0x2F,
  0x37,
  0x33,
  0x37,
  0x33,
  0x37,
  0x30,
  0x0D,
  0x35,
  0x36,
  0x37,
  0x33,
  0x2E,
  0x2C,
  0x34,
  0x2C,
  0x33,
  0x2E
};

// Per-level alternate tune id set (used by func_hd_code_80260E80, overlaps with D_hd_code_802E8E04), indexed by levelno
// Proposed name: levelResultsTunesAlt
u8 D_hd_code_802E8E40[60] = {
  0x41,
  0x39,
  0x3E,
  0x3B,
  0x3D,
  0x3A,
  0x32,
  0x34,
  0x35,
  0x41,
  0x3B,
  0x2F,
  0x41,
  0x32,
  0x32,
  0x32,
  0x40,
  0x3E,
  0x41,
  0x2E,
  0x2F,
  0x2F,
  0x34,
  0x34,
  0x34,
  0x36,
  0x3B,
  0x2F,
  0x32,
  0x40,
  0x35,
  0x36,
  0x30,
  0x39,
  0x2D,
  0x31,
  0x2E,
  0x35,
  0x26,
  0x31,
  0x3F,
  0x36,
  0x2F,
  0x37,
  0x3C,
  0x3F,
  0x33,
  0x37,
  0x3A,
  0x0D,
  0x39,
  0x36,
  0x37,
  0x33,
  0x2E,
  0x2C,
  0x34,
  0x3B,
  0x3C,
  0x2E
};

// Effect id -> bank sound number map for func_hd_code_802619D0 (0 = no sound)
// Proposed name: effectSfxMap
u16 D_hd_code_802E8E7C[28] = {
  0x0012,
  0x0011,
  0x0017,
  0x0018,
  0x0010,
  0x000A,
  0x0016,
  0x0040,
  0x0045,
  0x0043,
  0x003E,
  0x0044,
  0x0011,
  0x0011,
  0x0011,
  0x0011,
  0x0011,
  0x0011,
  0x0011,
  0x0011,
  0x0011,
  0x0000,
  0x0018,
  0x0043,
  0x0043,
  0x0043,
  0x0043,
  0x0043
};

// Randomized sound id pools: 5 groups of up to 5 sound ids, -1 terminated (see func_hd_code_8026205C)
// Proposed name: randomSfxPools
struct S_802E8EB4 D_hd_code_802E8EB4[5] = {
  {0x00000067, 0x000000D9, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000},
  {0x00000059, 0x000000E1, 0x000000E2, 0x000000E3, 0x00000065, 0xFFFFFFFF},
  {0x0000007A, 0x000000C3, 0x000000C2, 0xFFFFFFFF, 0x00000000, 0x00000000},
  {0x0000005D, 0x000000E0, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000},
  {0x00000056, 0x000000DB, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000}
};

// Start playing a tune: toggles the sequence double-buffer, stops the player,
// DMAs the sequence data into RAM, attaches it to the player and plays it.
// Volume = per-tune base volume * arg1 * master volume.
// Proposed name: PlayTune
void func_hd_code_80260C20(u8 arg0, f32 arg1) {
  void* sp24;

  D_hd_code_802E8D84 ^= 1;
  alCSPStop(D_hd_code_80367734);

  D_hd_code_8036772A = 0;
  D_hd_code_8036770C = arg1;
  D_hd_code_80367708 = arg0;
  sp24 = D_hd_code_80367514->seqArray[arg0].offset;


  InitiateDma(sp24, D_hd_code_80367510, &D_hd_code_80367408[arg0], 0U, 0, 0);
  alCSeqNew(&D_hd_code_80367518[D_hd_code_802E8D84], D_hd_code_80367510);
  alCSPSetSeq(D_hd_code_80367734, &D_hd_code_80367518[D_hd_code_802E8D84]);
  alCSPPlay(D_hd_code_80367734);
  alCSPSetVol(D_hd_code_80367734, D_hd_code_802E8D00[D_hd_code_80367708] * D_hd_code_8036770C * D_hd_code_802E8D88);
}

// Set the master music volume multiplier and apply it immediately
// Proposed name: SetMusicMasterVolume
void func_hd_code_80260D7C(f32 arg0) {
  D_hd_code_802E8D88 = arg0;
  alCSPSetVol(D_hd_code_80367734, (s32) ((f32) D_hd_code_802E8D00[D_hd_code_80367708] * D_hd_code_8036770C * arg0));
}

// Get the master music volume multiplier
// Proposed name: GetMusicMasterVolume
f32 func_hd_code_80260DF0(void) {
  return D_hd_code_802E8D88;
}

// Push the current level's jingle tune (from D_hd_code_802E8DC8) onto the tune stack
// Proposed name: PushLevelJingle
void func_hd_code_80260DFC(void) {
  func_hd_code_80260EE0(D_hd_code_802E8DC8[levelno]);
}

// Save the current timer and tempo, then hard-play the current level's tune
// from D_hd_code_802E8E04 (likely results/end-of-level music)
// Proposed name: PlayLevelResultsTune
void func_hd_code_80260E2C(void) {
  D_hd_code_80367740 = (s32) sc.unk803156C4;
  D_hd_code_8036772C = alCSPGetTempo(D_hd_code_80367734);
  func_hd_code_80261FB0(D_hd_code_802E8E04[levelno]);
}

// Save the current timer, then hard-play the current level's tune from the
// alternate set D_hd_code_802E8E40
// Proposed name: PlayLevelResultsTuneAlt
void func_hd_code_80260E80(void) {
  D_hd_code_80367740 = (s32) sc.unk803156C4;
  func_hd_code_80261FB0(D_hd_code_802E8E40[levelno]);
}

// Wrapper for func_hd_code_80260DFC (push current level's jingle tune)
// Proposed name: PushLevelJingleWrapper
void func_hd_code_80260EC0(void) {
  func_hd_code_80260DFC();
}

// Push tune: save the current tune id into the stack frame, set the new tune
// and arm the push state machine (func_hd_code_80261284 does the actual work)
// Proposed name: PushTune
void func_hd_code_80260EE0(u8 arg0) {
  if (D_hd_code_80367728 != 0) {
    rmonPrintf("OH DEAR - pushing tune but we're still popping!\n");
    return;
  }
  rmonPrintf("push tune %d\n", (u8) arg0);
  D_hd_code_80367400->unk1F0 = D_hd_code_80367708;
  D_hd_code_80367708 = arg0;
  D_hd_code_80367730 = 0;
  D_hd_code_80367729 = 1;
}

// Pop tune: restore the previous tune id from the stack, stop the player and
// arm the pop state machine (func_hd_code_80261068 resumes playback).
// arg0 is the volume scale to resume at. No-op if the stack is empty.
// Proposed name: PopTune
void func_hd_code_80260F60(f32 arg0) {
  rmonPrintf("1 pop tune");
  if (&D_hd_code_80366C30[0] == D_hd_code_80367400) {
    return;
  }

  D_hd_code_80367400 = D_hd_code_80367400 - 1;
  if (&D_hd_code_80366C30[0] == D_hd_code_80367400) {
    D_hd_code_80367730 = 1;
  }
  rmonPrintf("2 pop tune %d\n", D_hd_code_80367400->unk1F0);
  D_hd_code_80367708 = D_hd_code_80367400->unk1F0;
  alCSPStop(D_hd_code_80367734);
  D_hd_code_80367728 = 2;
  D_hd_code_80367714 = arg0;
}

// Pop tune, resuming silent (volume 0)
// Proposed name: PopTuneSilent
void func_hd_code_8026101C(void) {
  func_hd_code_80260F60(0);
}

// Pop tune, resuming at full volume
// Proposed name: PopTuneFullVolume
void func_hd_code_80261040(void) {
  func_hd_code_80260F60(1.0f);
}

// Pop state machine update (called per frame): once the player has stopped,
// restart the saved tune; once it's playing again, restore the saved sequence
// position, tempo and channel state from the stack frame, then fade volume
// back to 1.0 if it was popped quiet.
// Proposed name: UpdateTunePop
void func_hd_code_80261068(void) {
  u32 sp114;
  ALCSeqMarker sp28;

  switch(D_hd_code_80367728) {
    case 2:
      if (alCSPGetState(D_hd_code_80367734) == 0) {
        func_hd_code_80260C20(D_hd_code_80367708, D_hd_code_80367714);
        D_hd_code_80367728 = 1;
      }
      break;

    case 1:
      alCSeqGetLoc(&D_hd_code_80367518[D_hd_code_802E8D84], &sp28);
      if ((alCSPGetState(D_hd_code_80367734) == 1) && (sp28.lastTicks != 0)) {
        alCSeqSetLoc(&D_hd_code_80367518[D_hd_code_802E8D84], &D_hd_code_80367400->unk0[0x40]);
        alCSPSetTempo(D_hd_code_80367734, D_hd_code_80367400->unk1EC);
        // Reads 4 channels 4 * 0x10
        for(sp114 = 0; sp114 < 0x40U; sp114++) {
          // Raw data transfer
          *(((u32*)D_hd_code_80367734->chanState) + sp114) = D_hd_code_80367400->unk0[sp114];
        }
        D_hd_code_80367728 = 0;
        if ((f64) D_hd_code_80367714 != 1.0) {
          func_hd_code_80261570(1.0f);
        }
      }
      break;

  }
}

// Auto-pop: if no push/pop is in progress and the current tune has finished
// playing on its own, automatically pop back to the previous tune
// Proposed name: AutoPopTune
void func_hd_code_802611F0(void) {
  ALCSeqMarker sp1C;

  alCSeqGetLoc(&D_hd_code_80367518[D_hd_code_802E8D84], &sp1C);
  if ((D_hd_code_80367729 == 0) && (D_hd_code_80367728 == 0) && (alCSPGetState(D_hd_code_80367734) == 0) && (sp1C.lastTicks != 0)) {
    rmonPrintf("auto popping\n");
    func_hd_code_8026101C();
  }
}

// Push state machine update (called per frame): once the player is playing,
// snapshot the sequence location, tempo and channel state into the current
// stack frame, stop the player and advance the stack pointer; once stopped,
// start the pushed tune.
// Proposed name: UpdateTunePush
void func_hd_code_80261284(void) {
  u32 sp24;

  switch (D_hd_code_80367729) {                           /* irregular */
    case 1:
      if (alCSPGetState(D_hd_code_80367734) == 1) {
        alCSeqGetLoc(&D_hd_code_80367518[D_hd_code_802E8D84], &D_hd_code_80367400->unk0[0x40]);
        D_hd_code_80367400->unk1EC = alCSPGetTempo(D_hd_code_80367734);
        for(sp24 = 0; sp24 < 0x40U; sp24++) {
          D_hd_code_80367400->unk0[sp24] = *(((u32*)D_hd_code_80367734->chanState)+sp24);

        }
        alCSPStop(D_hd_code_80367734);
        D_hd_code_80367400++;
        D_hd_code_80367729 = 2;
        return;
      }
      return;
    case 2:
      if (alCSPGetState(D_hd_code_80367734) == 0) {
        func_hd_code_80260C20(D_hd_code_80367708, 1.0f);
        D_hd_code_80367729 = 0;
      }
      break;
  }
}

// Volume fade update (called per frame): exponentially interpolate the player
// volume toward the target at 7.5% per step, snapping and clearing the fade
// flag once within 10 units
// Proposed name: UpdateMusicFade
void func_hd_code_802613C8(void) {
  f32 sp2C;
  f32 sp28;
  s16 sp26;

  sp2C = alCSPGetVol(D_hd_code_80367734);
  sp28 = D_hd_code_802E8D00[D_hd_code_80367708] * D_hd_code_802E8D88;
  sp26 = sp2C + (sp28 * D_hd_code_8036770C - sp2C) * 0.075;
  if ((ABS(sp26 - sp28 * D_hd_code_8036770C)) < 10.0f) {
    sp26 = sp28 * D_hd_code_8036770C;
    D_hd_code_8036772A = 0;
  }
  alCSPSetVol(D_hd_code_80367734, (s32) sp26);
}

// Deferred tempo restore: once the player reaches the playing state, apply the
// tempo saved in D_hd_code_8036772C
// Proposed name: RestoreSavedTempo
void func_hd_code_80261528(void) {
  if (D_hd_code_80367734->state == 1) {
    alCSPSetTempo(D_hd_code_80367734, D_hd_code_8036772C);
    D_hd_code_8036772C = 0;
  }
}

// Set a fade target volume scale and flag a fade as active
// (func_hd_code_802613C8 performs the fade)
// Proposed name: FadeMusicTo
void func_hd_code_80261570(f32 arg0) {
  D_hd_code_8036770C = arg0;
  D_hd_code_8036772A = 1;
}

// Audio system init: set up the audio heap, DMA the music and SFX instrument
// bank files from ROM, load the sequence file header and record each
// sequence's length, create the audio manager and compressed sequence player,
// init the SFX player and start the audio thread.
// Proposed name: InitAudio
void func_hd_code_80261588(void) {
    ALSeqpSfxConfig sp84;
    s32 sp80;
    s32 sp7C;
    s32 sp78;
    ALHeap* sp74;
    s8 pad73;
    s8 pad72;
    s8 pad71;
    s8 sp70;
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s8 pad63;
    s8 pad62;
    s8 pad61;
    s8 sp60;
    s32 sp5C;
    ALHeap* sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    ALBankFile* sp40;
    ALBankFile* sp3C;
    s32 sp38;
    s32 sp34;
    u32 sp30;
    s32 pad2C;
    s32 pad28;
    s32 sp24;
    s32 sp20;

    alHeapInit(&D_hd_code_80367718, &D_hd_code_80370C80, 0x2A280);
    sp38 = sp34 = (s32)&snd_unk1_ROM_START - (s32)&snd_bank0_ROM_START;
    InitiateDma(&snd_bank0_ROM_START, (void* )0x8004B400, &sp38, 0xDU, 0, 2);
    sp3C = alHeapAlloc(&D_hd_code_80367718, 1, sp38);
    InitiateDma(&snd_bank0_ROM_START, sp3C, &sp34, 0xDU, 0, 2);
    alBnkfNew(sp3C, &snd_unk1_ROM_START);
    D_hd_code_8036773C = sp3C->bankArray[0];
    sp38 = sp34 = (s32)&snd_unk2_ROM_START - (s32)&snd_bank1_ROM_START;

    InitiateDma(&snd_bank1_ROM_START, (void* )0x8004B400, &sp38, 0xDU, 0, 2);
    sp40 = alHeapAlloc(&D_hd_code_80367718, 1, sp38);
    InitiateDma(&snd_bank1_ROM_START, sp40, &sp34, 0xDU, 0, 2);
    alBnkfNew(sp40, &snd_unk2_ROM_START);
    D_hd_code_80367738 = sp40->bankArray[0];
    D_hd_code_80367514 = alHeapAlloc(&D_hd_code_80367718, 1, 4);
    sp20 = 4;
    InitiateDma(&snd_seqfile_ROM_START, D_hd_code_80367514, &sp20, 0U, 0, 0);
    sp24 = (D_hd_code_80367514->seqCount * 8) + 4;
    D_hd_code_80367514 = alHeapAlloc(&D_hd_code_80367718, 1, 0x214);
    InitiateDma(&snd_seqfile_ROM_START, D_hd_code_80367514, &sp24, 0U, 0, 0);
    alSeqFileNew(D_hd_code_80367514, &snd_seqfile_ROM_START);
    D_hd_code_80367510 = alHeapAlloc(&D_hd_code_80367718, 1, 0x21AE);
    for(sp30 = 0; sp30 < 0x42U; sp30++) {
        D_hd_code_80367408[sp30] = D_hd_code_80367514->seqArray[sp30].len;
        if (D_hd_code_80367408[sp30] & 1) {
            D_hd_code_80367408[sp30]++;
        }
    }
    // TODO: find matching struct. probably ALSynConfig
    sp44 = 0;
    sp48 = 0x18;
    sp4C = 0x80;
    sp50 = 1;
    sp54 = 0;
    sp60 = 6;
    sp5C = 0;
    sp58 = &D_hd_code_80367718;
    amCreateAudioManager(&sp44, 0xC);
    // TODO: find matching struct
    sp68 = 0x18;
    sp6C = 0x20;
    sp70 = 0x10;
    sp74 = &D_hd_code_80367718;
    sp78 = 0;
    sp7C = 0;
    sp80 = 0;
    D_hd_code_80367734 = alHeapAlloc(&D_hd_code_80367718, 1, 0x7C);
    alCSPNew(D_hd_code_80367734, &sp68);
    alCSPSetBank(D_hd_code_80367734, D_hd_code_8036773C);
    sp84.maxEvents = 0x40;
    sp84.maybeSndStateCount = 0x20;
    sp84.maybeMaxSounds = 8;
    sp84.slotCount = 8;
    sp84.heap = &D_hd_code_80367718;
    sndNewPlayerInit(&sp84);
    rmonPrintf("%d bytes audio heap left over\n", D_hd_code_80367718.len - ((s32)D_hd_code_80367718.cur - (s32)D_hd_code_80367718.base));
    D_hd_code_8036772A = 0;
    D_hd_code_80367728 = 0;
    D_hd_code_80367710 = D_hd_code_8036770C = 1.0f;
    D_hd_code_80367730 = 1;
    D_hd_code_80367400 = &D_hd_code_80366C30[0];
    amStartAudioThread();
}

// Play a one-shot sound effect: maps the logical effect id through
// D_hd_code_802E8E7C to a bank sound number (0 = no sound)
// Proposed name: PlaySoundEffect
void func_hd_code_802619D0(u32 effectId) {
  if (effectId >= 0x1CU) {
    rmonPrintf("effect id %d out of range!\n", effectId);
    return;
  }

  if (D_hd_code_802E8E7C[effectId] != 0) {
    sndPlaySfx(D_hd_code_80367738, D_hd_code_802E8E7C[effectId], 0);
  }
}

// Main music chooser. arg0 is a one-hot level bitmask (1 << levelno; u64 since
// there are 60 levels), which is why the cases are powers of two. Deactivates
// certain SFX, applies per-level SFX ducking, then selects the tune for that
// level: special-case levels get fixed tunes, some just fade the music out,
// ordinary levels use D_hd_code_802E8D8C[levelno]. Returns the new tune id
// (after starting a fade-out) if it differs from the current one, else 0.
// Proposed name: ChooseLevelMusic
u8 func_hd_code_80261A44(u64 arg0) {
    u8 sp27;
    u8 sp26;

    sp26 = 0;
    sp27 = D_hd_code_80367708;
    if (arg0 != 4) {
        sndDeactivateAllSfxByFlag_3();
    }
    sndDeactivateAllSfxByFlag_11();
    func_hd_code_80261E9C(arg0);
    if ((D_hd_code_80364A90 & 0xC9FD8FE7FBFFC0B0)) {
        func_hd_code_80260A30(0);
        func_hd_code_80260A30(5);
    }
    D_hd_code_80367710 = 1.0f;

    switch(arg0) {
        case 0x2:
            sp27 = 0x11;
            break;
        case 0x40:
            sp27 = 0xA;
            break;
        case 0x800:
        case 0x1000:
            sp27 = 3;
            break;
        case 0x10000:
            sp27 = 0x21;
            break;
        case 0x40000000000000:
        case 0x100000000:
        case 0x200000000:
        case 0x20000:
        case 0x40000:
            sp27 = 0x21;
            break;
        case 0x80000000:
            func_hd_code_80261570(0.0f);
            break;
        case 0x08000000:
            sp27 = 0xE;
            break;

        case 0x4000: // correct
        case 0x80: // correct
            if (func_hd_code_80264BA4(levelno) == 3) {
                sp27 = 0xC;
            } else {
                sp27 = 0x13;
            }
            break;
        case 0x40000000:
            sp27 = 0xF;
            break;
        case 0x2000:
            if (D_hd_code_802E8F94[levelno].unk0 != 1) {
                func_hd_code_80261570(0.0f);
                break;
            }
        case 0x4:
            sp27 = D_hd_code_802E8D8C[levelno];
            sp26 = 1;
            break;
        case 0x20000000:
            sp27 = 0x1D;
            break;
        case 0x100000000000:
            sp27 = D_hd_code_802E8D8C[levelno];
            sp26 = 1;
            if (levelno == 0x26) {
                D_hd_code_80367710 = 0.7f;
            }
            break;
        case 0x4000000000000:
            func_hd_code_80261570(0.0f);
            break;

        case 0x10000000000000:
            sp27 = 0x28;
            break;

        case 0x4000000000000000:
            break;
        case 0x800000000000:
            func_hd_code_80261570(0.0f);
            break;
    }

    if ((sp27 != D_hd_code_80367708) || (sp26 != 0)) {
        func_hd_code_80261570(0.0f);
        return sp27;
    }
    return 0U;
}

// Per-level SFX ducking: set SFX slot 0/5 volumes based on the level bitmask
// (full volume 0x7FFF for levels not listed)
// Proposed name: SetLevelSfxVolumes
void func_hd_code_80261E9C(u64 arg0) {
  switch(arg0) {
    case 0x2:
      sndSetSfxSlotVolume(0, 0x5DC0);
      sndSetSfxSlotVolume(5, 0x5DC0);
      break;
    case 0x20000000:
      sndSetSfxSlotVolume(0, 0x61A8);
      break;
    case 0x40:
      sndSetSfxSlotVolume(0, 0x4E20);
      sndSetSfxSlotVolume(5, 0x4E20);
      break;
    case 0x800:
    case 0x1000:
      sndSetSfxSlotVolume(0, 0x6D60);
      sndSetSfxSlotVolume(5, 0x6D60);
      break;
    default:
      sndSetSfxSlotVolume(0, 0x7FFF);
      sndSetSfxSlotVolume(5, 0x7FFF);
      break;
  }
}

// Hard reset and play: clear push/pop state, reset the tune stack to the
// bottom and start the tune at the stored per-level volume
// Proposed name: ResetAndPlayTune
void func_hd_code_80261FB0(u8 arg0) {
  D_hd_code_80367728 = 0;
  D_hd_code_80367729 = 0;
  D_hd_code_80367400 = &D_hd_code_80366C30[0];
  D_hd_code_80367730 = 1;
  func_hd_code_80260C20(arg0, D_hd_code_80367710);
}

// Reset the tune stack and play a tune at an explicit volume (does not clear
// the push/pop state flags, unlike func_hd_code_80261FB0)
// Proposed name: ResetAndPlayTuneVol
void func_hd_code_80262008(u8 arg0, f32 arg1) {
  D_hd_code_80367400 = &D_hd_code_80366C30[0];
  D_hd_code_80367730 = 1;
  func_hd_code_80260C20(arg0, arg1);
}

// Get the currently playing tune id
// Proposed name: GetCurrentTune
u8 func_hd_code_80262050()
{
  return D_hd_code_80367708;
}

// Random sound variation picker: count the valid (-1 terminated) entries in
// group arg0 of D_hd_code_802E8EB4 and return one chosen pseudo-randomly via
// the CPU cycle counter
// Proposed name: PickRandomSfx
s32 func_hd_code_8026205C(s32 arg0) {
  u32 sp2C;
  s32 sp28;

  for(sp2C = 0, sp28 = 0;sp28 < 5 && D_hd_code_802E8EB4[arg0].unk0[sp28] != -1; sp28++, sp2C++);

  return D_hd_code_802E8EB4[arg0].unk0[osGetCount() % sp2C];
}
