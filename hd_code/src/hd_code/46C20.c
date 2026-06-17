#include "common.h"
#include "functions.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"

void func_801F57B0();
void func_hd_code_802C4070(void**, void**, u32, u8);
extern void** D_hd_code_802FDB30;
extern void** D_hd_code_802FDB34;
extern OSIoMesg D_80370C58;
extern OSMesgQueue D_hd_code_803150A0;

// Proposed file name: dma.c
//
// This file contains the cartridge DMA primitive used everywhere to stream
// data from ROM (with optional gzip / texture decompression on the way in),
// and the loader that pulls the front-end menu overlay into RAM the first
// time it is needed.

// <data>
void** D_hd_code_802FDB30 = (void**)0x803FFFF8;
void** D_hd_code_802FDB34 = (void**)0x803FFFFC;
// </data>

// Load the front-end menu overlay into its fixed RAM region (0x801E7000) on
// first use: blank the screen, invalidate the caches, DMA the overlay from
// ROM, zero the remaining space, and run its init (func_801F57B0)
// Proposed name: LoadFrontEndOverlay
void func_hd_code_8028B3E0(void) {
  s32 sp24;

  sp24 = (s32)*D_hd_code_802FDB34 - (s32)*D_hd_code_802FDB30;
  osViBlack(1U);
  if (frontEndPresent == 0) {
    osInvalDCache((void* )0x801E7000, 0x37D00);
    osInvalICache((void* )0x801E7000, 0x37D00);
    InitiateDma(*D_hd_code_802FDB30, (void* )0x801E7000, &sp24, 0xDU, 0xA, 1);
    bzero(sp24 + 0x801E7000, 0x37D00 - sp24);
    frontEndPresent = 1;
    func_801F57B0();
    rmonPrintf("got front end\n");
  }
}

// The cartridge DMA primitive (already named). arg0 = ROM source, arg1 =
// RAM dest, *arg2 = byte count, arg3/arg4 = decompression-mode flags
// (nonzero routes the data through a scratch buffer at 0x8021ED00 and then a
// decompressor), arg5 = decompressor select: 1 = gzip (func_hd_code_8025C230),
// 2 = texture codec (func_hd_code_802C4070). Transfers in 0x4000-byte chunks
// plus the remainder; when decompressing, writes the decompressed size back
// to *arg2.
void InitiateDma(u8* arg0, u8* arg1, s32* arg2, u8 arg3, u8 arg4, u8 arg5) {
  u32 sp44;
  u32 sp40;
  void* sp3C;
  void* sp38;
  u8* sp34;

  sp38 = arg1;
  if (arg3 || arg4) {
    sp3C = (void* )0x8021ED00;
  } else {
    sp3C = arg1;
  }
  osInvalDCache(sp3C, *arg2);
  sp34 = (u8*)sp3C;
  for(sp44 = 0; sp44 < (u32) ((u32) *arg2 >> 0xE); sp44++) {
    osPiStartDma(&D_80370C58, 0, OS_READ, (u32) arg0, sp34, 0x4000U, &D_hd_code_803150A0);
    osRecvMesg(&D_hd_code_803150A0, NULL, 1);
    arg0 += 0x4000;
    sp34 += 0x4000;
  }

  sp40 = *arg2 - (((u32) *arg2 >> 0xE) << 0xE);
  if (sp40 != 0) {
    osPiStartDma(&D_80370C58, 0, OS_READ, (u32) arg0, sp34, sp40, &D_hd_code_803150A0);
    osRecvMesg(&D_hd_code_803150A0, NULL, 1);
  }
  switch (arg5) {                            /* irregular */
    case 1:
      if (arg3) {
        func_hd_code_8025C230(&sp3C, &arg1, 0x8004B400);
      }
      if (arg4) {
        func_hd_code_8025C230(&sp3C, &arg1, 0x8004B400);
      }
      break;
    case 2:
      if (arg3) {
        func_hd_code_802C4070(&sp3C, &arg1, 0x8004B400, arg3);
      }
      if (arg4) {
        func_hd_code_802C4070(&sp3C, &arg1, 0x8004B400, arg4);
      }
      break;
  }
  if (arg3 || arg4) {
    *arg2 = (s32)arg1 - (s32)sp38;
  }
}

