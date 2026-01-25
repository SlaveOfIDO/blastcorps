#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"

u8 D_8039CAF0[0x50 * 0x200];

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
