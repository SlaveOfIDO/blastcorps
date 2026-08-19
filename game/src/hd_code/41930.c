#include "common.h"
#include "functions.h"
#include "hd.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"
#include "yoshi.h"
#include "../hd_front_end/structs.h"
#include "../levels.h"

// Proposed file name: academy.c (the original name - the asserts in
// func_hd_code_80286330 reference "academy.c")
//
// This file drives the single-player campaign progression. Each player's
// progress is a stage counter (players[playerNumber].unk91); completing the
// requirements of a stage (enough levels cleared in a rank, the academy,
// score milestones, etc.) advances it, which in turn unlocks the next
// cutscene, the vehicle academy, the bonus levels, or the ending. unk90 is a
// bitmask of academy tests passed, unkA is the player's overall rank/score.

void func_hd_code_80260C20(u8, f32);                     /* extern */
void func_801F8354(u8);                                /* extern */
void func_hd_code_802995F0(s32);                         /* extern */
void func_801ECF5C();                                  /* extern */
void func_801ED4B8();                                  /* extern */

extern u8 D_hd_code_802FDA70[];
extern u8 D_hd_code_8036EBA0[];
extern u8 D_hd_code_802FDA60[];
extern u8 frontEndPresent;
extern struct S_80367C04 D_hd_code_802E8F94[];
extern s32 D_hd_code_802FA26C;
extern struct LevelData D_hd_front_end_8020D810[];

// <bss>
u8 D_hd_code_8036EBA0[96];
// </bss>


// Show the cutscene / congratulations message for the player's current
// campaign stage (skipping the few stages that have no message): set the
// state to the cutscene state, load the matching tune, and for the
// "new rank" stage build the "IN <place>." text from the next uncompleted
// region
// Proposed name: ShowStageCutscene
void func_hd_code_802860F0(void) {
  u8 sp37;
  s32 sp30;
  s32 sp2C;
  s32 sp28;

  if ((players[playerNumber].unk91 != 0xD) && (players[playerNumber].unk91 != 8) && (players[playerNumber].unk91 != 1)) {
    D_hd_code_80364A98 = 0x800000000000;
    func_hd_code_80255DC8();
    func_80200714(D_hd_code_802FDA60[players[playerNumber].unk91]);
    switch (players[playerNumber].unk91) {                          /* irregular */
      case 4:
        for(sp37 = 0, sp30 = 0; (sp30 < LEVEL_MAX) && (sp37 == 0); sp30++) {
          for(sp2C = 0, sp28 = 0; (sp2C < 6) && (sp28 == 0); sp2C++) {
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
        func_801ECC8C();
        break;
    }
    func_hd_code_8026AF6C((players[playerNumber].unk91 + 0x16) | 0x8000);
  }
}

// Start the cutscene's tune on its first frame (per-stage tune table
// D_hd_code_802FDA70)
// Proposed name: StartStageCutsceneMusic
void func_hd_code_802862DC(void) {
  if (D_hd_code_80358060 == 0) {
    func_hd_code_80260C20(D_hd_code_802FDA70[players[playerNumber].unk91], 1.0f);
  }
}

// Transition out of a cutscene to whatever follows the current campaign
// stage: the world map, the credits, the academy (stage 6, level 50), a
// bonus/special level, or the ending sequence
// Proposed name: ExitStageCutscene
void func_hd_code_80286330(void) {
  switch (players[playerNumber].unk91) {
    case 2:
    case 3:
    case 4:
      D_hd_code_80364A98 = 0x4000;
    default:
      break;
    case 5:
      func_hd_code_802995F0(0);
      D_hd_code_80364A98 = 0x100000000000;
      break;
    case 6:
      if (levelno != 0x32) {
        rmonPrintf(ASSERT_MESSAGE, "levelno==50", "academy.c", 0x8C);
      }
      if (players[playerNumber].levelno != LEVEL_SHUTTLE_CLEAR) {
        rmonPrintf(ASSERT_MESSAGE, "players[playerNumber].levelno==50", "academy.c", 0x8D);
      }
      if (!frontEndPresent) {
        rmonPrintf(ASSERT_MESSAGE, "frontEndPresent", "academy.c", 0x8E);
      }
      D_hd_code_80364A98 = 0x800;
      D_hd_code_803643D5 = 0;
      func_801F8354(playerNumber);
      break;
    case 7:
      func_hd_code_802995F0(1);
      D_hd_code_80364A98 = 0x100000000000;
      break;
    case 9:
      func_hd_code_802995F0(3);
      D_hd_code_80364A98 = 0x100000000000;
      break;
    case 10:
      D_hd_code_80364A98 = 0x4000000000000;
      break;
    case 11:
      D_hd_code_80364A98 = 0x4000;
      break;
    case 12:
      D_hd_code_80364A98 = 0x4000;
      break;
  }
}

// Advance the player's campaign stage as far as its requirements allow:
// repeatedly checks the current stage's unlock condition (all levels of a
// rank cleared, all academy tests passed, a specific level cleared, a score
// threshold reached...) and bumps the stage until one isn't met. The "give
// every coin" debug flag (D_hd_code_802FA26C) forces advancement. Returns 1
// if the stage changed (so a new cutscene should play).
// Proposed name: AdvanceCampaignStage
s32 func_hd_code_8028653C(void) {
    s32 sp34;
    UnknownData8024C414* sp30;
    u8 sp2F;
    u8 sp2E;
    u8 sp2D;
    u8 pad2C;

    u8 sp2B;

    sp30 = &players[playerNumber];
    sp2F = 1;
    sp2E = 0;
    sp2D = sp30->unk91;
    do {
        sp2F = 1;
        switch (players[playerNumber].unk91) {
        case 0:
            if (D_hd_code_80364A90 == 0x100000000000) {
                sp2F = 0;
            }
            break;
        case 1:
        case 2:
        case 3:
            for(sp34 = 0; sp34 < LEVEL_MAX && sp2F != 0; sp34++) {
                if (D_hd_code_802E8F94[sp34].unk1 == players[playerNumber].unk91) {
                    if ((((players[playerNumber].unk18[sp34] > 0) && (players[playerNumber].unk18[sp34] < 6)?1:0) == 0) && (D_hd_code_802E8F94[sp34].unk0 == 1)) {
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
            if (((players[playerNumber].unk18[0x31] > 0) && (players[playerNumber].unk18[0x31] < 6)?1:0) == 0) {
                sp2F = 0;
            }
            break;
        case 6:
            if (((players[playerNumber].unk18[0x32] > 0) && (players[playerNumber].unk18[0x32] < 6)?1:0) == 0) {
                sp2F = 0;
            }
            break;
        case 7:
            if (((players[playerNumber].unk18[0x28] > 0) && (players[playerNumber].unk18[0x28] < 6)?1:0) == 0) {
                sp2F = 0;
            }
            break;
        case 8:
            if ((s32) sp30->unkA < 0xDE) {
                sp2F = 0;
            }
            break;
        case 9:
            if (((s32) sp30->unkA >= 0xEA) || (D_hd_code_802FA26C != 0)) {
                func_hd_code_80261570(0.0f);
                func_hd_code_8028B3E0();
                func_801ECF5C();
                sp2E = 1;
            } else {
                sp2F = 0;
            }
            break;
        case 10:
            break;
        case 11:
            if (((s32) sp30->unkA < 0x129) || (D_hd_code_802FA26C != 0)) {
                sp2F = 0;
            } else {
                func_hd_code_80261570(0.0f);
                func_hd_code_8028B3E0();
                func_801ED4B8();
            }
            break;
        case 12:
            if (((s32) sp30->unkA >= 0x162) || (D_hd_code_802FA26C != 0)) {
                sp30->unkA = 0x168;
                sp30->unkC = 0x1E;
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
    } while((sp2F != 0) && (sp2E == 0) && (D_hd_code_802FA26C == 0));


    sp2B = players[playerNumber].unk91 != sp2D;
    rmonPrintf("game state %d to %d\n", sp2D, players[playerNumber].unk91);
    return (s32) sp2B;
}

