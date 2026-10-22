#include "common.h"
#include "functions.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"
#include "yoshi.h"
#include "../levels.h"
#include "../vehicles.h"

void func_hd_code_8028ADF0(u8, u8, OSContPad*, s8*, s8*); /* extern */
void func_hd_code_8028B190(s8*, s8*);                     /* extern */
void func_hd_code_8028B734(s8*, s8*, u8);                 /* extern */
void func_hd_code_8028AFA4(u16, s8*, s8*);                /* extern */
void func_hd_code_8028B0E8(OSContPad*, s8, s8);           /* extern */

extern u8 g_upButtonPressed;
extern u8 g_downButtonPressed;
extern u8 g_startButtonPressed;
extern u8 g_lButtonPressed;
extern u8 g_rButtonPressed;
extern u8 g_cDownButtonPressed;
extern u8 g_cUpButtonPressed;
extern s8 D_hd_code_80370C23;
extern u8 D_hd_code_80370C25;
extern u8 D_hd_code_80370C26;
extern s8 D_hd_code_80370C2E;
extern s8 D_hd_code_80370C2F;
extern s8 D_hd_code_80370C34;
extern s32 D_hd_code_80370C40;
extern s8 D_hd_code_80370C75;
extern s8 D_hd_code_803ED40A;
extern s16 D_hd_code_803F7C34;
extern u8 D_hd_code_803F7C3F;
extern OSContStatus D_hd_code_80370BC8;
extern void* D_hd_code_80370BF0;
extern u8 D_hd_code_80370C10;
extern u8 D_hd_code_80370C35;
extern s32 D_hd_code_80370BC0;

// <bss>
s32 D_hd_code_80370BC0;
s32 D_hd_code_80370BC4;
OSContStatus D_hd_code_80370BC8;
s32 D_hd_code_80370BCC;
s32 D_hd_code_80370BD0;
s32 D_hd_code_80370BD4;
OSContPad D_hd_code_80370BD8;
s32 D_hd_code_80370BE0;
s32 D_hd_code_80370BE4;
s32 D_hd_code_80370BE8;
s32 D_hd_code_80370BEC;
void* D_hd_code_80370BF0;
s32 D_hd_code_80370BF4;
OSMesgQueue D_hd_code_80370BF8;
u8 D_hd_code_80370C10;
s8 D_hd_code_80370C11;
s8 D_hd_code_80370C12;
s8 D_hd_code_80370C13;
s8 D_hd_code_80370C14;
u8 g_leftButtonPressed;
u8 g_rightButtonPressed;
u8 g_upButtonPressed;
u8 g_downButtonPressed;
u8 g_startButtonPressed;
u8 g_lButtonPressed;
u8 g_rButtonPressed;
u8 g_aButtonPressed;
u8 g_bButtonPressed;
u8 g_cLeftButtonPressed;
u8 g_cDownButtonPressed;
u8 g_cUpButtonPressed;
u8 g_cRightButtonPressed;
u8 g_zButtonPressed;
s8 D_hd_code_80370C23;
u8 D_hd_code_80370C24;
u8 D_hd_code_80370C25;
u8 D_hd_code_80370C26;
u8 D_hd_code_80370C27;
u16 g_currentButtons;
u16 g_previousButtons;
s8 g_stickX;
s8 g_stickY;
s8 D_hd_code_80370C2E;
s8 D_hd_code_80370C2F;
u16 D_hd_code_80370C30;
s8 D_hd_code_80370C32;
s8 D_hd_code_80370C33;
s8 D_hd_code_80370C34;
u8 D_hd_code_80370C35;
u8 D_hd_code_80370C36;
u8 D_hd_code_80370C37;
s32 D_hd_code_80370C38;
s32 D_hd_code_80370C3C;
s32 D_hd_code_80370C40;
s32 D_hd_code_80370C44;
s32 D_hd_code_80370C48;
s32 D_hd_code_80370C4C;
u8 frontEndPresent;
u8 D_hd_code_80370C51;
u8 D_hd_code_80370C52;
u8 D_hd_code_80370C53;
s32 D_hd_code_80370C54;
s32 D_hd_code_80370C58;
s32 D_hd_code_80370C5C;
s32 D_hd_code_80370C60;
s32 D_hd_code_80370C64;
s32 D_hd_code_80370C68;
s32 D_hd_code_80370C6C;
// </bss>

// <data>
s32 D_hd_code_802FDB10 = 0;  // unused
s8 D_hd_code_802FDB14 = 0;
// </data>

u8 func_hd_code_8028A370(void) {
  u32 pad;
  u8 sp1B;

  osCreateMesgQueue(&D_hd_code_80370BF8, &D_hd_code_80370BF0, 1);
  osSetEventMesg(OS_EVENT_SI, &D_hd_code_80370BF8, NULL);
  osContInit(&D_hd_code_80370BF8, &sp1B, &D_hd_code_80370BC8);
  osContSetCh(1U);
  D_hd_code_80370C10 = 0;
  D_hd_code_80370C35 = 0;
  return sp1B;
}

void func_hd_code_8028A3E4(void) {
  if (!g_pakBusy) {
    func_hd_code_8028A42C();
    osContStartReadData(&D_hd_code_80370BF8);
    D_hd_code_80370C10 = 1;
  }
}

void func_hd_code_8028A42C(void) {
  if (D_hd_code_80370C10 != 0) {
    osRecvMesg(&D_hd_code_80370BF8, NULL, 1);
    D_hd_code_80370C10 = 0;
  }
}

void controllerUpdateInput(void) {
  OSContPad* sp44;
  s32 pad;
  s32 sp3C;

  sp44 = &D_hd_code_80370BD8;
  if (D_hd_code_80358064 != 0) {
    if ((g_pakBusy == 0) && (D_hd_code_80370C10 != 0)) {
      osRecvMesg(&D_hd_code_80370BF8, NULL, 1);
      osContGetReadData(sp44);
      if (sp44->errno != 0) {
        rmonPrintf("pad read error - zeroing data\n");
        sp44->stick_x = sp44->stick_y = sp44->button = 0;
      }
      D_hd_code_80370C10 = 0;
    }
    g_previousButtons = g_currentButtons;
    g_currentButtons = sp44->button;
    if (D_hd_code_80370C38 != 0) {
      if (sp44->button & B_BUTTON) {
        sp44->button = sp44->button & ~B_BUTTON;
      } else {
        D_hd_code_80370C38 = 0;
      }
    }
    if ((u32)g_frameCount < 6U) {
      if (g_frameCount == 5) {
        g_previousButtons |= (A_BUTTON | B_BUTTON | START_BUTTON);
      } else {
        g_currentButtons &= ~(A_BUTTON | B_BUTTON | START_BUTTON);
      }
    }
    D_hd_code_80370C13 = D_hd_code_80370C11;
    D_hd_code_80370C14 = D_hd_code_80370C12;
    D_hd_code_80370C11 = sp44->stick_x;
    D_hd_code_80370C12 = sp44->stick_y;
    D_hd_code_80370C24 = g_cLeftButtonPressed;
    D_hd_code_80370C25 = g_cDownButtonPressed;
    D_hd_code_80370C26 = g_cUpButtonPressed;
    D_hd_code_80370C27 = g_cRightButtonPressed;

    switch (g_currentGameState) {
      case 0x100000000000:
      case 0x400:
      case 0x40:
      case 0x2:
        if (g_currentLevel != LEVEL_SHUTTLE_ISLAND && g_currentLevel != LEVEL_END_SEQUENCE) {
          do {
            func_hd_code_8025BEF8();
            if (D_hd_code_80370C30 & 0x40) {
              D_hd_code_80370C40 = 0;
            } else if (D_hd_code_80370C30 & 0x80) {
              D_hd_code_80370C40 = 1;
            }
          } while (D_hd_code_80370C30 & 0xC0);
        }
        sp44->button = D_hd_code_80370C30;
        sp44->stick_x = D_hd_code_80370C32;
        sp44->stick_y = D_hd_code_80370C33;
        sp44->button &= ~U_CBUTTONS;
        break;
      case 0x100:
      case 0x4:
        if ((!g_gamePaused) || ((g_currentGameState == 0x2000))) {
          func_hd_code_8025BBE8(sp44->button & ~START_BUTTON, sp44->stick_x, sp44->stick_y);
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

    D_hd_code_80370C34 = 0;
    if ((g_currentGameState & 0x2000100000002546)) {
      D_hd_code_803ED40A = 0;
      D_hd_code_803F7C34 = 0;
      if (g_currentGameState & 0x440) {
        sp3C = D_hd_code_80370C40;
      } else if (players[playerNumber].unkF0 & (1 << g_currentVehicleType)) {
        sp3C = 1;
      } else {
        sp3C = 0;
      }
      if (((g_currentGameState == 2)) || ((g_currentGameState == 0x100000000000))) {
        sp3C = 0;
      }
      D_hd_code_80370C35 = (u8)sp3C;
      if (g_gamePaused != 0) {
        func_hd_code_8028ADF0(1, 0, sp44, &sp44->stick_x, &sp44->stick_y);
      } else {
        switch (sp3C) {
          case 0:
            switch (g_currentVehicleType) {
              case VEHICLE_J_BOMB:
                if (D_hd_code_803F7C3F != 0) {
                  D_hd_code_80370C34 = 1;
                }
              case VEHICLE_UNKNOWN_0:
              case VEHICLE_THUNDERFIST:
              case VEHICLE_CYCLONE_SUIT:
                func_hd_code_8028B734(&sp44->stick_x, &sp44->stick_y, g_currentVehicleType);
                func_hd_code_8028B190(&sp44->stick_x, &sp44->stick_y);
                break;
              default:
                D_hd_code_80370C75 = 0;
                func_hd_code_8028ADF0(0, 0, sp44, &sp44->stick_x, &sp44->stick_y);
                break;
            }
            break;
          case 1:
            if (g_currentVehicleType == VEHICLE_J_BOMB) {
              D_hd_code_80370C75 = 0;
              func_hd_code_8028ADF0(1, 1, sp44, &sp44->stick_x, &sp44->stick_y);
            } else {
              D_hd_code_80370C75 = 0;
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

  if (sp44->button & L_JPAD) {
    g_leftButtonPressed = 1;
  } else {
    g_leftButtonPressed = 0;
  }
  if (sp44->button & R_JPAD) {
    g_rightButtonPressed = 1;
  } else {
    g_rightButtonPressed = 0;
  }
  if (sp44->button & U_JPAD) {
    g_upButtonPressed = 1;
  } else {
    g_upButtonPressed = 0;
  }
  if (sp44->button & D_JPAD) {
    g_downButtonPressed = 1;
  } else {
    g_downButtonPressed = 0;
  }
  if (sp44->button & START_BUTTON) {
    g_startButtonPressed = 1;
  } else {
    g_startButtonPressed = 0;
  }
  if (sp44->button & L_TRIG) {
    g_lButtonPressed = 1;
  } else {
    g_lButtonPressed = 0;
  }
  if (sp44->button & R_TRIG) {
    g_rButtonPressed = 1;
  } else {
    g_rButtonPressed = 0;
  }
  if (sp44->button & A_BUTTON) {
    g_aButtonPressed = 1;
  } else {
    g_aButtonPressed = 0;
  }
  if (sp44->button & B_BUTTON) {
    g_bButtonPressed = 1;
  } else {
    g_bButtonPressed = 0;
  }
  if (sp44->button & L_CBUTTONS) {
    g_cLeftButtonPressed = 1;
  } else {
    g_cLeftButtonPressed = 0;
  }
  if (sp44->button & D_CBUTTONS) {
    g_cDownButtonPressed = 1;
  } else {
    g_cDownButtonPressed = 0;
  }
  if (sp44->button & U_CBUTTONS) {
    g_cUpButtonPressed = 1;
  } else {
    g_cUpButtonPressed = 0;
  }
  if (sp44->button & R_CBUTTONS) {
    g_cRightButtonPressed = 1;
  } else {
    g_cRightButtonPressed = 0;
  }
  if (sp44->button & Z_TRIG) {
    g_zButtonPressed = 1;
  } else {
    g_zButtonPressed = 0;
  }

  D_hd_code_80370C23 = g_bButtonPressed != 0 || g_zButtonPressed != 0;
  D_hd_code_80370C2E = g_stickX;
  D_hd_code_80370C2F = g_stickY;
  g_stickX = sp44->stick_x;
  g_stickY = sp44->stick_y;
}

void func_hd_code_8028ADF0(u8 arg0, u8 arg1, OSContPad* pController, s8* pStickX, s8* pStickY) {
  if (!arg0 && !g_gamePaused) {
    *pStickY = 0;
  }
  if (!arg1) {
    func_hd_code_8028AFA4(pController->button, pStickX, pStickY);
  }
  func_hd_code_8028B190(pStickX, pStickY);
  if (!arg1) {
    func_hd_code_8028B0E8(pController, *pStickX, *pStickY);
  }
}

void controllerInit(void) {
  D_hd_code_80370C27 = 0;
  D_hd_code_80370C26 = 0;
  D_hd_code_80370C25 = 0;
  D_hd_code_80370C24 = 0;
  g_stickY = 0;
  g_stickX = 0;
  D_hd_code_80370C23 = 0;
  g_zButtonPressed = 0;
  g_cRightButtonPressed = 0;
  g_cUpButtonPressed = 0;
  g_cDownButtonPressed = 0;
  g_cLeftButtonPressed = g_cDownButtonPressed;
  g_bButtonPressed = g_cLeftButtonPressed;
  g_aButtonPressed = g_bButtonPressed;
  g_rButtonPressed = g_aButtonPressed;
  g_lButtonPressed = g_rButtonPressed;
  g_startButtonPressed = g_lButtonPressed;
  g_downButtonPressed = g_startButtonPressed;
  g_upButtonPressed = g_downButtonPressed;
  g_rightButtonPressed = g_upButtonPressed;
  g_leftButtonPressed = g_rightButtonPressed;
  g_previousButtons = 0;
  g_currentButtons = 0;
  D_hd_code_80370BC0 = 0;
  D_hd_code_80370C38 = 0;
}

void func_hd_code_8028AFA4(u16 button, s8* pStickX, s8* pStickY) {
  if (button & L_JPAD) {
    *pStickX = -0x50;
  }
  if (button & R_JPAD) {
    *pStickX = 0x50;
  }
  if (button & B_BUTTON) {
    *pStickY = -0x50;
  }
  if (button & A_BUTTON) {
    *pStickY = 0x50;
  }
}

void func_hd_code_8028B000(s8* arg0, s8* arg1) {
  switch (g_currentVehicleType) {
    case VEHICLE_SIDESWIPE:
    case VEHICLE_SKYFALL:
    case VEHICLE_RAMDOZER:
    case VEHICLE_BACKLASH:
    case VEHICLE_UNKNOWN_6:
      if (*arg0 < 0x33 && *arg0 >= -0x32) {
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

void func_hd_code_8028B0E8(OSContPad* pController, s8 stickX, s8 stickY) {
  if (!(pController->button & L_JPAD) && (stickX < -0x32)) {
    pController->button |= L_JPAD;
  }
  if (!(pController->button & R_JPAD) && (stickX >= 0x33)) {
    pController->button |= R_JPAD;
  }
  if (!(pController->button & A_BUTTON) && (stickY >= 0x33)) {
    pController->button |= A_BUTTON;
  }
  if (!(pController->button & B_BUTTON) && (stickY < -0x32)) {
    pController->button |= B_BUTTON;
  }
}

void func_hd_code_8028B190(s8* pStickX, s8* pStickY) {
  if ((*pStickX < 0xA) && (*pStickX >= -9)) {
    *pStickX = 0;
  }
  if (*pStickX >= 0x51) {
    *pStickX = 0x50;
  }
  if (*pStickX < -0x50) {
    *pStickX = -0x50;
  }
  if ((*pStickY < 0xA) && (*pStickY >= -9)) {
    *pStickY = 0;
  }
  if (*pStickY >= 0x51) {
    *pStickY = 0x50;
  }
  if (*pStickY < -0x50) {
    *pStickY = -0x50;
  }
}

// Location needed here for matching:
char* D_hd_code_802FDB18[3] = { "SPEED ON 3D STICK?", "360 DEGREE MODE?", "AIRBORNE 360' MODE?" };
u32 D_hd_code_802FDB24[3] = { 0x0000EDBA, 0x00010005, 0x00000200 };

void func_hd_code_8028B240(void) {
  INIT_FROM_ARRAY(char* sp24[3], sp24, D_hd_code_802FDB18);
  char* sp20 = "CONTROL METHOD:";
  s32 found = 0;
  s32 sp18 = 0;

  while (sp18 < 3 && !found) {
    if (D_hd_code_802FDB24[sp18] & (1 << g_currentVehicleType)) {
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
  if ((players[playerNumber].unkF0 ^ 0x10205) & (1 << g_currentVehicleType)) {
    D_hd_code_802F8BDC[0x58].unk18 = 0x1A8;
  } else {
    D_hd_code_802F8BDC[0x58].unk18 = 0x1A7;
  }
  yoshiShow(0x8058U);
}
