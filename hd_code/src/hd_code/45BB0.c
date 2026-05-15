#include "common.h"
#include "functions.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"
#include "yoshi.h"

void func_hd_code_8028ADF0(u8, u8, OSContPad*, s8*, s8*); /* extern */
void func_hd_code_8028B190(s8*, s8*);                  /* extern */
void func_hd_code_8028B734(s8*, s8*, u8);              /* extern */

extern OSContPad D_80370BD8;
extern u8 D_80370C15;
extern u8 D_80370C16;
extern u8 D_80370C17;
extern u8 D_80370C18;
extern u8 D_80370C19;
extern u8 D_80370C1A;
extern u8 D_80370C1B;
extern u8 D_80370C1F;
extern u8 D_80370C20;
extern s8 D_80370C23;
extern u8 D_80370C25;
extern u8 D_80370C26;
extern s8 D_80370C2C;
extern s8 D_80370C2E;
extern s8 D_80370C2F;
extern s8 D_80370C34;
extern s32 D_80370C40;
extern s8 D_80370C75;
extern s8 D_803ED40A;
extern s16 D_803F7C34;
extern u8 D_803F7C3F;
extern OSContStatus D_80370BC8;
extern void* D_80370BF0;
extern u8 D_80370C10;
extern u8 D_80370C35;
extern s32 D_80370BC0;
extern char* D_hd_code_802FDB18[3]; // Strings from asm files
extern u32 D_hd_code_802FDB24[];

u8 func_hd_code_8028A370(void) {
  u32 pad;
  u8 sp1B;

  osCreateMesgQueue(&D_80370BF8, &D_80370BF0, 1);
  osSetEventMesg(5U, &D_80370BF8, NULL);
  osContInit(&D_80370BF8, &sp1B, &D_80370BC8);
  osContSetCh(1U);
  D_80370C10 = 0;
  D_80370C35 = 0;
  return sp1B;
}

void func_hd_code_8028A3E4(void) {
  if (!D_8039C4B0) {
    func_hd_code_8028A42C();
    osContStartReadData(&D_80370BF8);
    D_80370C10 = 1;
  }
}

void func_hd_code_8028A42C(void) {
  if (D_80370C10 != 0) {
    osRecvMesg(&D_80370BF8, NULL, 1);
    D_80370C10 = 0;
  }
}

void func_hd_code_8028A470(void) {
    OSContPad* sp44;
    s32 pad;
    s32 sp3C;

    sp44 = &D_80370BD8;
    if (D_hd_code_80358064 != 0) {
        if ((D_8039C4B0 == 0) && (D_80370C10 != 0)) {
            osRecvMesg(&D_80370BF8, NULL, 1);
            osContGetReadData(sp44);
            if (sp44->errno != 0) {
                rmonPrintf("pad read error - zeroing data\n");
                sp44->stick_x = sp44->stick_y = sp44->button = 0;
            }
            D_80370C10 = 0;
        }
        D_80370C2A = D_80370C28;
        D_80370C28 = sp44->button;
        if (D_80370C38 != 0) {
            if (sp44->button & 0x4000) {
                sp44->button = sp44->button & ~0x4000;
            } else {
                D_80370C38 = 0;
            }
        }
        if ((u32) D_hd_code_80358060 < 6U) {
            if (D_hd_code_80358060 == 5) {
                D_80370C2A |= 0xD000;
            } else {
                D_80370C28 &= 0xFFFF2FFF;
            }
        }
        D_80370C13 = D_80370C11;
        D_80370C14 = D_80370C12;
        D_80370C11 = sp44->stick_x;
        D_80370C12 = sp44->stick_y;
        D_80370C24 = D_80370C1E;
        D_80370C25 = D_80370C1F;
        D_80370C26 = D_80370C20;
        D_80370C27 = D_80370C21;

        switch(D_hd_code_80364A90) {
            case 0x100000000000:
            case 0x400:
            case 0x40:
            case 0x2:
                if ((levelno != 0x26) && (levelno != 0x31)) {
                    do {
                        func_hd_code_8025BEF8();
                        if (D_80370C30 & 0x40) {
                            D_80370C40 = 0;
                        } else if (D_80370C30 & 0x80) {
                            D_80370C40 = 1;
                        }
                    } while (D_80370C30 & 0xC0);
                }
                sp44->button = D_80370C30;
                sp44->stick_x = D_80370C32;
                sp44->stick_y = D_80370C33;
                sp44->button &= ~8;
                break;
            case 0x100:
            case 0x4:
                if ((D_hd_code_802E8BD0 == 0) || ((D_hd_code_80364A90 == 0x2000))) {
                    func_hd_code_8025BBE8(sp44->button & ~0x1000, sp44->stick_x, sp44->stick_y);
                }
                break;
            case 0x800:
            case 0x1000:
            case 0x04000000:
            case 0x200:
            case 0x8:
            case 0x1:
                sp44->button = 0;
                sp44->stick_x = 0;
                sp44->stick_y = 0;
                break;
        }

        D_80370C34 = 0;
        if ((D_hd_code_80364A90 & 0x2000100000002546)) {
            D_803ED40A = 0;
            D_803F7C34 = 0;
            if ((D_hd_code_80364A90 & 0x440)) {
                sp3C = D_80370C40;
            } else if (players[playerNumber].unkF0 & (1 << D_hd_code_80364456)) {
                sp3C = 1;
            } else {
                sp3C = 0;
            }
            if (((D_hd_code_80364A90 == 2)) || ((D_hd_code_80364A90 == 0x100000000000))) {
                sp3C = 0;
            }
            D_80370C35 = (u8) sp3C;
            if (D_hd_code_802E8BD0 != 0) {
                func_hd_code_8028ADF0(1, 0, sp44, &sp44->stick_x, &sp44->stick_y);
            } else {
                switch (sp3C) {                     /* switch 1; irregular */
                case 0:                             /* switch 1 */
                    switch (D_hd_code_80364456) {   /* switch 2; irregular */
                    case 9:                         /* switch 2 */
                        if (D_803F7C3F != 0) {
                            D_80370C34 = 1;
                        }
                        /* fallthrough */
                    case 0:                         /* switch 2 */
                    case 2:                         /* switch 2 */
                    case 16:                        /* switch 2 */
                        func_hd_code_8028B734(&sp44->stick_x, &sp44->stick_y, D_hd_code_80364456);
                        func_hd_code_8028B190(&sp44->stick_x, &sp44->stick_y);
                        break;
                    default:                        /* switch 2 */
                        D_80370C75 = 0;
                        func_hd_code_8028ADF0(0, 0, sp44, &sp44->stick_x, &sp44->stick_y);
                        break;
                    }
                    break;
                case 1:                             /* switch 1 */
                    if (D_hd_code_80364456 == 9) {
                        D_80370C75 = 0;
                        func_hd_code_8028ADF0(1, 1, sp44, &sp44->stick_x, &sp44->stick_y);
                    } else {
                        D_80370C75 = 0;
                        func_hd_code_8028ADF0(1, 0, sp44, &sp44->stick_x, &sp44->stick_y);
                    }
                    break;
                }
            }
        }
    } else {
        sp44->button = 0;
        sp44->stick_x = 0;
        sp44->stick_y = 0;
    }
    if (sp44->button & 0x200) {
        D_80370C15 = 1;
    } else {
        D_80370C15 = 0;
    }
    if (sp44->button & 0x100) {
        D_80370C16 = 1;
    } else {
        D_80370C16 = 0;
    }
    if (sp44->button & 0x800) {
        D_80370C17 = 1;
    } else {
        D_80370C17 = 0;
    }
    if (sp44->button & 0x400) {
        D_80370C18 = 1;
    } else {
        D_80370C18 = 0;
    }
    if (sp44->button & 0x1000) {
        D_80370C19 = 1;
    } else {
        D_80370C19 = 0;
    }
    if (sp44->button & 0x20) {
        D_80370C1A = 1;
    } else {
        D_80370C1A = 0;
    }
    if (sp44->button & 0x10) {
        D_80370C1B = 1;
    } else {
        D_80370C1B = 0;
    }
    if (sp44->button & 0x8000) {
        D_80370C1C = 1;
    } else {
        D_80370C1C = 0;
    }
    if (sp44->button & 0x4000) {
        D_80370C1D = 1;
    } else {
        D_80370C1D = 0;
    }
    if (sp44->button & 2) {
        D_80370C1E = 1;
    } else {
        D_80370C1E = 0;
    }
    if (sp44->button & 4) {
        D_80370C1F = 1;
    } else {
        D_80370C1F = 0;
    }
    if (sp44->button & 8) {
        D_80370C20 = 1;
    } else {
        D_80370C20 = 0;
    }
    if (sp44->button & 1) {
        D_80370C21 = 1;
    } else {
        D_80370C21 = 0;
    }
    if (sp44->button & 0x2000) {
        D_80370C22 = 1;
    } else {
        D_80370C22 = 0;
    }

    D_80370C23 = D_80370C1D != 0 || D_80370C22 != 0;
    D_80370C2E = D_80370C2C;
    D_80370C2F = D_80370C2D;
    D_80370C2C = sp44->stick_x;
    D_80370C2D = sp44->stick_y;
}

void func_hd_code_8028AFA4(u16, s8*, s8*);             /* extern */
void func_hd_code_8028B0E8(OSContPad*, s8, s8);        /* extern */

void func_hd_code_8028ADF0(u8 arg0, u8 arg1, OSContPad* arg2, s8* arg3, s8* arg4) {
  if ((arg0 == 0) && (D_hd_code_802E8BD0 == 0)) {
    *arg4 = 0;
  }
  if (arg1 == 0) {
    func_hd_code_8028AFA4(arg2->button, arg3, arg4);
  }
  func_hd_code_8028B190(arg3, arg4);
  if (arg1 == 0) {
    func_hd_code_8028B0E8(arg2, *arg3, *arg4);
  }
}

void func_hd_code_8028AE88(void) {
  D_80370C27 = 0;
  D_80370C26 = 0;
  D_80370C25 = 0;
  D_80370C24 = 0;
  D_80370C2D = 0;
  D_80370C2C = 0;
  D_80370C23 = 0;
  D_80370C22 = 0;
  D_80370C21 = 0;
  D_80370C20 = 0;
  D_80370C1F = 0;
  D_80370C1E = D_80370C1F;
  D_80370C1D = D_80370C1E;
  D_80370C1C = D_80370C1D;
  D_80370C1B = D_80370C1C;
  D_80370C1A = D_80370C1B;
  D_80370C19 = D_80370C1A;
  D_80370C18 = D_80370C19;
  D_80370C17 = D_80370C18;
  D_80370C16 = D_80370C17;
  D_80370C15 = D_80370C16;
  D_80370C2A = 0;
  D_80370C28 = 0;
  D_80370BC0 = 0;
  D_80370C38 = 0;
}

void func_hd_code_8028AFA4(u16 arg0, s8* arg1, s8* arg2) {
  if (arg0 & 0x200) {
    *arg1 = -0x50;
  }
  if (arg0 & 0x100) {
    *arg1 = 0x50;
  }
  if (arg0 & 0x4000) {
    *arg2 = -0x50;
  }
  if (arg0 & 0x8000) {
    *arg2 = 0x50;
  }
}

void func_hd_code_8028B000(s8* arg0, s8* arg1) {
  switch (D_hd_code_80364456) {
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
      if ((*arg0 < 0x33) && (*arg0 >= -0x32)) {
        *arg0 = 0;
      } else {
        if (*arg0 >= 0x33) {
          *arg0 = 0x50;
        }
        if (*arg0 < -0x32) {
          *arg0 = -0x50;
        }
      }
      if ((*arg1 < 0x33) && (*arg1 >= -0x32)) {
        *arg1 = 0;
        return;
      }
      if (*arg1 >= 0x33) {
        *arg1 = 0x50;
      }
      if (*arg1 < -0x32) {
        *arg1 = -0x50;
      }
    default:
      return;
  }
}

void func_hd_code_8028B0E8(OSContPad* arg0, s8 arg1, s8 arg2) {
  if (!(arg0->button & 0x200) && (arg1 < -0x32)) {
    arg0->button |= 0x200;
  }
  if (!(arg0->button & 0x100) && (arg1 >= 0x33)) {
    arg0->button |= 0x100;
  }
  if (!(arg0->button & 0x8000) && (arg2 >= 0x33)) {
    arg0->button |= 0x8000;
  }
  if (!(arg0->button & 0x4000) && (arg2 < -0x32)) {
    arg0->button |= 0x4000;
  }
}


void func_hd_code_8028B190(s8* arg0, s8* arg1) {
  if ((*arg0 < 0xA) && (*arg0 >= -9)) {
    *arg0 = 0;
  }
  if (*arg0 >= 0x51) {
    *arg0 = 0x50;
  }
  if (*arg0 < -0x50) {
    *arg0 = -0x50;
  }
  if ((*arg1 < 0xA) && (*arg1 >= -9)) {
    *arg1 = 0;
  }
  if (*arg1 >= 0x51) {
    *arg1 = 0x50;
  }
  if (*arg1 < -0x50) {
    *arg1 = -0x50;
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/45BB0/D_hd_code_8030CBF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/45BB0/D_hd_code_8030CC04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/45BB0/D_hd_code_8030CC18.s")

void func_hd_code_8028B240(void) {
  char* sp24[3] = D_hd_code_802FDB18;
  char* sp20 = "CONTROL METHOD:";
  s32 found = 0;
  s32 sp18 = 0;

  while(sp18 < 3 && !found) {
    if (D_hd_code_802FDB24[sp18] & (1 << D_hd_code_80364456)) {
      found = 1;
    } else {
      sp18 += 1;
    }

  }
  if (!found) {
    rmonPrintf(ASSERT_MESSAGE, "found", "controller.c", 0x203);
  }
  D_hd_code_802F5804[0x1A5].unkC = sp20;
  D_hd_code_802F5804[0x1A5].unk10 = NULL;
  D_hd_code_802F5804[0x1A6].unkC = sp24[sp18];
  D_hd_code_802F5804[0x1A6].unk6 = 0x13;
  if ((players[playerNumber].unkF0 ^ 0x10205) & (1 << D_hd_code_80364456)) {
    D_hd_code_802F8BDC[0x58].unk18 = 0x1A8;
  } else {
    D_hd_code_802F8BDC[0x58].unk18 = 0x1A7;
  }
  func_hd_code_8026AF6C(0x8058U);
}
