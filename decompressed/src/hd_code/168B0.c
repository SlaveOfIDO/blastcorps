#include "common.h"
#include "functions.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"

// Proposed file name: font.c (the original name - the assert in
// func_hd_code_8025B0B8 references "font.c")
//
// This file is the glyph texture cache used by the text renderer (14B30.c),
// plus string helpers for the u16 code strings ("str16") used by the text
// system: code 0xFFE terminates, 0x1002 is a space, 0x1003/0x1004 are
// insert-string/insert-number placeholders. The cache holds up to 0x50
// glyph textures of 0x200 bytes in D_hd_code_8039CAF0; each use refreshes a
// 3-frame TTL and expired slots can be evicted.

// BSS Begin
u8 D_hd_code_80365360[0x50]; // per-slot TTL, decremented each frame; 0 = evictable; proposed name: glyphSlotAge
u16 D_hd_code_803653B0[0x54]; // per-slot loaded glyph texture id (0 = empty); proposed name: glyphSlotId
u8 D_hd_code_80365458[0x100]; // static buffer for str16 -> ASCII conversion; proposed name: asciiConvBuf
u16 D_hd_code_80365558[0x14]; // static buffer for ASCII -> str16 conversion; proposed name: str16ConvBuf
// BSS End

// Clear the glyph cache
// Proposed name: InitFontCache
void func_hd_code_8025B070(void) {
  s32 sp4;
  for(sp4 = 0; sp4 < 0x50; sp4++) {
    D_hd_code_80365360[sp4] = 0;
    D_hd_code_803653B0[sp4] = 0;
  }
}

// Get the texture for glyph id arg0: return the cached slot if present,
// otherwise load it (func_hd_code_802A1040) into an empty slot, or failing
// that into an expired one. Refreshes the slot's TTL to 3 frames.
// Proposed name: GetGlyphTexture
void* func_hd_code_8025B0B8(u16 arg0) {
  s32 sp1C;
  u8 found;

  found = 0;
  sp1C = 0;
  while((sp1C < 0x50) && !found) {
    if (D_hd_code_803653B0[sp1C] == arg0) {
      found = 1;
    } else {
      sp1C++;
    }
  }
  if (!found) {
    sp1C = 0;
    while ((sp1C < 0x50) && !found) {
      if (D_hd_code_803653B0[sp1C] == 0) {
        func_hd_code_802A1040(arg0, &D_hd_code_8039CAF0[sp1C * 0x200], 0);
        D_hd_code_803653B0[sp1C] = arg0;
        found = 1;
      } else {
        sp1C++;
      }
    }
  }
  if (!found) {
    sp1C = 0;
    while (sp1C < 0x50 && !found) {
      if (D_hd_code_80365360[sp1C] == 0) {
        func_hd_code_802A1040(arg0, &D_hd_code_8039CAF0[sp1C * 0x200], 0);
        D_hd_code_803653B0[sp1C] = arg0;
        found = 1;
      } else {
        sp1C++;
      }
    }
  }
  if (!found) {
    rmonPrintf(ASSERT_MESSAGE, "found", "font.c", 0x51);
  }
  if (found) {
    D_hd_code_80365360[sp1C] = 3;
  }
  return &D_hd_code_8039CAF0[sp1C * 0x200];
}

// Age the glyph cache by one frame (called from the main loop)
// Proposed name: AgeFontCache
void func_hd_code_8025B2B8(void) {
  s32 i;
  for (i = 0; i < 0x50; i++) {
    if (D_hd_code_80365360[i] != 0) {
      D_hd_code_80365360[i]--;
    }
  }
}

// Visible length of an ASCII string (excluding '*' full-advance markers)
// Proposed name: StrVisibleLen
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

// Visible length of a str16 (0xFFE terminated, excluding 0x1000 markers)
// Proposed name: Str16VisibleLen
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

// Return 1 if the two ASCII strings differ
// Proposed name: StrDiffer
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

// Compute the left x that centers string arg2 at x = arg0, given character
// width arg1 and the proportional advance factor
// Proposed name: GetCenteredTextX
s16 func_hd_code_8025B498(u16 arg0, u16 arg1, u8* arg2, s32 arg3) {
  volatile s32 sp2C = 0;
  volatile s16 sp2A = ((s16) arg0) - ((arg1 * (1.0f + (((func_hd_code_8025B300(arg2)) - 1) * D_hd_code_802E8C84[0]))) / 2.0);
  return sp2A;
}

// Convert a 0-terminated u16 string to ASCII in the static buffer
// Proposed name: Str16ToAscii
u8* func_hd_code_8025B558(u16* arg0) {
  s32 sp4;

  sp4 = 0;
  while(arg0[sp4] != 0 && sp4 < 0xFF) {
    D_hd_code_80365458[sp4++] = (u8) arg0[sp4];
  }
  D_hd_code_80365458[sp4] = 0;
  return D_hd_code_80365458;
}

// Build a str16 into arg0 from template arg1, expanding placeholder 0x1003
// to the str16 arg2 and 0x1004 to the decimal number arg3
// Proposed name: FormatStr16
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
        sprintf(sp34, "%d", arg3);
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

// Convert an ASCII string (digits, '.', '/', ':', spaces, letters) to str16
// glyph codes in the static buffer
// Proposed name: AsciiToStr16
u16* func_hd_code_8025B7AC(u8* arg0) {
  s32 sp1C;
  for (sp1C = 0; sp1C < func_hd_code_8025B300(arg0); sp1C++) {
    switch (arg0[sp1C]) {
      case 0x20:
        D_hd_code_80365558[sp1C] = 0x1002;
        break;
      case 0x2E:
        D_hd_code_80365558[sp1C] = 0x3C;
        break;
      case 0x31:
      case 0x32:
      case 0x33:
      case 0x34:
        D_hd_code_80365558[sp1C] = arg0[sp1C] - 0x20;
        break;
      default:
        D_hd_code_80365558[sp1C] = arg0[sp1C] - 0x27;
        break;
      case 0x2F:
        D_hd_code_80365558[sp1C] = 0x3D;
        break;
      case 0x3A:
        D_hd_code_80365558[sp1C] = 0x3E;
        break;
    }
  }
  D_hd_code_80365558[sp1C] = 0xFFE;

  return D_hd_code_80365558;
}

// Append str16 arg1 to str16 arg0
// Proposed name: Str16Concat
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
