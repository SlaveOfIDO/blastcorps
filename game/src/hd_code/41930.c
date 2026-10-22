#include "../hd_front_end/structs.h"
#include "../levels.h"
#include "common.h"
#include "functions.h"
#include "game_states.h"
#include "hd.h"
#include "macros.h"
#include "music.h"
#include "structs.h"
#include "variables.h"
#include "yoshi.h"

void func_hd_front_end_801F8354(u8);
void func_hd_code_802995F0(s32);
void func_hd_front_end_801ECF5C();
void func_hd_front_end_801ED4B8();

extern u8 D_hd_code_802FDA70[];
extern u8 D_hd_code_8036EBA0[];
extern u8 D_hd_code_802FDA60[];
extern s32 D_hd_code_802FA26C;

// <bss>
u8 D_hd_code_8036EBA0[96];
// </bss>

void func_hd_code_802860F0(void) {
  u8 sp37;
  s32 sp30;
  s32 sp2C;
  s32 sp28;

  if (players[playerNumber].unk91 != 0xD && (players[playerNumber].unk91 != 8) && (players[playerNumber].unk91 != 1)) {
    g_nextGameState = STATE_LEVELS_COMPLETED;
    hdPrepareStateTransition();
    func_hd_front_end_80200714(D_hd_code_802FDA60[players[playerNumber].unk91]);
    switch (players[playerNumber].unk91) { /* irregular */
      case 4:
        for (sp37 = 0, sp30 = 0; (sp30 < LEVEL_MAX) && (sp37 == 0); sp30++) {
          for (sp2C = 0, sp28 = 0; (sp2C < 6) && (sp28 == 0); sp2C++) {
            if (D_hd_code_802E8F38[sp2C].unk0 == sp30) {
              sp28 = 1;
              if (!(players[playerNumber].unk90 & (1 << sp2C))) {
                sp37 = 1;
              }
            }
          }
        }
        sprintf(D_hd_code_8036EBA0, "IN %s.", D_hd_front_end_8020D810[sp30 - 1].name);
        D_hd_front_end_8020C070[0x52].unkC = &D_hd_code_8036EBA0;
        break;
      case 6:
        func_hd_front_end_801ECC8C();
        break;
    }
    yoshiShow((players[playerNumber].unk91 + 0x16) | 0x8000);
  }
}

void func_hd_code_802862DC(void) {
  if (g_frameCount == 0) {
    musicPlayTune(D_hd_code_802FDA70[players[playerNumber].unk91], 1.0f);
  }
}

void func_hd_code_80286330(void) {
  switch (players[playerNumber].unk91) {
    case 2:
    case 3:
    case 4:
      g_nextGameState = 0x4000;
    default:
      break;
    case 5:
      func_hd_code_802995F0(0);
      g_nextGameState = 0x100000000000;
      break;
    case 6:
      if (g_currentLevel != LEVEL_SHUTTLE_CLEAR) {
        rmonPrintf(ASSERT_MESSAGE, "levelno==50", "academy.c", 0x8C);
      }
      if (players[playerNumber].levelno != LEVEL_SHUTTLE_CLEAR) {
        rmonPrintf(ASSERT_MESSAGE, "players[playerNumber].levelno==50", "academy.c", 0x8D);
      }
      if (!frontEndPresent) {
        rmonPrintf(ASSERT_MESSAGE, "frontEndPresent", "academy.c", 0x8E);
      }
      g_nextGameState = 0x800;
      D_hd_code_803643D5 = 0;
      func_hd_front_end_801F8354(playerNumber);
      break;
    case 7:
      func_hd_code_802995F0(1);
      g_nextGameState = 0x100000000000;
      break;
    case 9:
      func_hd_code_802995F0(3);
      g_nextGameState = 0x100000000000;
      break;
    case 10:
      g_nextGameState = 0x4000000000000;
      break;
    case 11:
      g_nextGameState = 0x4000;
      break;
    case 12:
      g_nextGameState = 0x4000;
      break;
  }
}

s32 func_hd_code_8028653C(void) {
  s32 sp34;
  UnknownData8024C414* sp30 = &players[playerNumber];
  u8 sp2F = 1;
  u8 sp2E = 0;
  u8 sp2D = sp30->unk91;
  u8 pad2C;

  u8 sp2B;

  do {
    sp2F = 1;
    switch (players[playerNumber].unk91) {
      case 0:
        if (g_currentGameState == 0x100000000000) {
          sp2F = 0;
        }
        break;
      case 1:
      case 2:
      case 3:
        for (sp34 = 0; sp34 < LEVEL_MAX && sp2F != 0; sp34++) {
          if (D_hd_code_802E8F94[sp34].unk1 == players[playerNumber].unk91) {
            if (((LEVEL_FINISHED(sp34)) == 0) &&
                (D_hd_code_802E8F94[sp34].unk0 == 1)) {
              sp2F = 0;
            }
          }
        }
        break;
      case 4:
        if (sp30->unk90 != 0x3F) {
          sp2F = 0;
        }
        break;
      case 5:
        if (!LEVEL_FINISHED(LEVEL_END_SEQUENCE)) {
          sp2F = 0;
        }
        break;
      case 6:
        if (!LEVEL_FINISHED(LEVEL_SHUTTLE_CLEAR)) {
          sp2F = 0;
        }
        break;
      case 7:
        if (!LEVEL_FINISHED(LEVEL_MOON)) {
          sp2F = 0;
        }
        break;
      case 8:
        if ((s32)sp30->unkA < 0xDE) {
          sp2F = 0;
        }
        break;
      case 9:
        if (((s32)sp30->unkA >= 0xEA) || (D_hd_code_802FA26C != 0)) {
          func_hd_code_80261570(0.0f);
          func_hd_code_8028B3E0();
          func_hd_front_end_801ECF5C();
          sp2E = 1;
        } else {
          sp2F = 0;
        }
        break;
      case 10:
        break;
      case 11:
        if (((s32)sp30->unkA < 0x129) || (D_hd_code_802FA26C != 0)) {
          sp2F = 0;
        } else {
          func_hd_code_80261570(0.0f);
          func_hd_code_8028B3E0();
          func_hd_front_end_801ED4B8();
        }
        break;
      case 12:
        if (((s32)sp30->unkA >= 0x162) || (D_hd_code_802FA26C != 0)) {
          sp30->unkA = 0x168;
          sp30->rankLevel = 0x1E;
          rmonPrintf(" ***** YOU CAN STOP NOW!! ***** \n");
        } else {
          sp2F = 0;
        }
        break;
      case 13:
        sp2F = 0;
        break;
      default:
        rmonPrintf("Undefined gameState case !!!!\n");
    }
    if ((D_hd_code_802FA26C != 0) && ((players[playerNumber].unk91 != 0xD))) {
      if (saveIt[playerNumber] != 0) {
        players[playerNumber].unk91 += 1;
      }
    } else {
      if (sp2F != 0) {
        players[playerNumber].unk91 += 1;
      }
      rmonPrintf("going to game state %d\n", players[playerNumber].unk91);
    }
  } while ((sp2F != 0) && (sp2E == 0) && (D_hd_code_802FA26C == 0));

  sp2B = players[playerNumber].unk91 != sp2D;
  rmonPrintf("game state %d to %d\n", sp2D, players[playerNumber].unk91);
  return (s32)sp2B;
}
