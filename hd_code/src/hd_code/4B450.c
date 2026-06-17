#include "common.h"
#include "functions.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"
#include "yoshi.h"

u8 func_hd_code_8028FCD4(OSMesgQueue*, u8*);       /* extern */

// <data>
u8 D_hd_code_802FDBD0 = 0;
u8 D_hd_code_802FDBD4 = 0;
// </data>

// Boot-time controller check: read controller 1 once and record whether
// Start is held (D_hd_code_802FDBD0) and whether it's held with no pak
// present (D_hd_code_802FDBD4) - used to pick the initial boot mode
// Proposed name: CheckBootButtons
void func_hd_code_8028FC10(void) {
  u8 sp3F;
  u8 sp3E;
  OSContPad sp24[4]; // 4 = MAX_CONTROLLERS?

  sp3E = 0;
  osContStartReadData(&D_80370BF8);
  osRecvMesg(&D_80370BF8, NULL, 1);
  osContGetReadData(sp24);
  if (sp24[0].button & CONT_START) {
    sp3E = 1;
  }
  if ((func_hd_code_8028FCD4(&D_80370BF8, &sp3F) == 0) && (sp3F & 1)) {
    D_hd_code_802FDBD0 = sp3E;
  }
  D_hd_code_802FDBD4 = sp3E != 0 && D_hd_code_802FDBD0 == 0;
}

// Query which of the 4 controller ports have a connected, error-free
// controller (bitmask into *arg1); returns controller 0's error code
// Proposed name: QueryControllers
u8 func_hd_code_8028FCD4(OSMesgQueue* arg0, u8* arg1) {
  OSContStatus sp20[4];
  s32 sp1C;

  *arg1 = 0;
  osContStartQuery(arg0);
  while (arg0->validCount == 0) {}
  osRecvMesg(arg0, NULL, 0);
  osContGetQuery(sp20);

  for(sp1C = 0; sp1C < 4; sp1C++) {
    if ((sp20[sp1C].status & 1) && (sp20[sp1C].errno == 0)) {
      *arg1 |= 1 << sp1C;
    }
  }

  return sp20[0].errno;
}
