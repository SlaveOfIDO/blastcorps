#include <PR/gu.h>
#include <ultra64.h>

#include "common.h"
#include "functions.h"
#include "gfx.h"
#include "game_states.h"
#include "hd.h"
#include "macros.h"
#include "music.h"
#include "structs.h"
#include "variables.h"
#include "yoshi.h"
#include "stats_perm.h"
#include "../vram.h"
#include "../hd_front_end/intro.h"
#include "../levels.h"

// size: 0x4
struct UnknownStruct8030F668 {
  /* 0x01 */ u8 flag1;
  /* 0x02 */ u8 flag2;
  /* 0x03 */ u8 flag3;
};

typedef struct {
  s32 unk0;
  s16 unk4;
  s16 unk6;
  u8 unk8;
  u8 unk9;
  s16 pad;
} UnknownStruct_80364A00;

// <bss>
u8 D_hd_code_8030F660;
s32 D_hd_code_8030F664;
struct UnknownStruct8030F668 D_hd_code_8030F668;
u8 bss_pad_1[0x11AC];
OSThread g_Thread1;
u8 g_Thread1Stack[0x200];
OSThread g_Thread3;
s64 g_Thread3Stack[0x400]; // size 0x2000
s32 g_SchedulerStack[0x800]; // bss, size 0x2000
OSMesgQueue D_hd_code_80314D80; // bss
OSMesg D_hd_code_80314D98[0xC2]; // bss
OSMesgQueue D_hd_code_803150A0; // bss
OSMesg D_hd_code_803150B8[0x32]; // bss
OSMesgQueue D_hd_code_80315180; // bss
OSMesg D_hd_code_80315198[0x90]; // bss
OSMesgQueue D_hd_code_803153D8;
u8 D_hd_code_803153F0;
OSMesg D_hd_code_803153F8[0x10];
u8 D_hd_code_80315438;
OSSched sc; // 0x80315440
OSScClient g_gfxClient;
s32 D_hd_code_803156E8;
s32 D_hd_code_803156EC;
s32 D_hd_code_803156F0;
u8 D_hd_code_803156F4;
u8 D_hd_code_803156F5;
struct FrameContext D_hd_code_803156F8[2];
s32 pad_80358028;
s32 pad_8035802C;
Gfx* D_hd_code_80358030[2];
Gfx* D_hd_code_80358038[2];
Gfx* D_hd_code_80358040[2];
Gfx* D_hd_code_80358048[2];
u16 *D_hd_code_80358050[2];
u32 D_hd_code_80358058;
u8 D_hd_code_8035805C;
u32 g_frameCount; // frames since the state started
s32 D_hd_code_80358064;
s32 D_hd_code_80358068;
void* D_hd_code_8035806C;
u8* g_heap;
Gfx* D_hd_code_80358074;
s32 D_hd_code_80358078;
u16 D_hd_code_8035807C;
s32 nextdma; // 0x80358080
s32 no_palette_dmas; // 0x80358084
u8 D_hd_code_80358088[0xC340];
struct Shadows g_shadows;
s32 bss_pad_5;
u8 D_hd_code_803643D4;
u8 D_hd_code_803643D5;
u8 D_hd_code_803643D6;
u8 D_hd_code_803643D7;
u8 D_hd_code_803643D8;
u8 D_hd_code_803643D9;
u8 D_hd_code_803643DA;
u8 D_hd_code_803643DB;
u8 D_hd_code_803643DC;
s32 D_hd_code_803643E0;
s32 D_hd_code_803643E4;
s32 D_hd_code_803643E8;
s32 D_hd_code_803643EC;
s32 D_hd_code_803643F0;
s32 D_hd_code_803643F4;
s32 D_hd_code_803643F8;
s32 D_hd_code_803643FC;
s32 D_hd_code_80364400;
s32 D_hd_code_80364404;
s32 D_hd_code_80364408;
s32 D_hd_code_8036440C;
u8 D_hd_code_80364410;
u8 D_hd_code_80364411;
u8 D_hd_code_80364412;
f32 D_hd_code_80364414;
f32 D_hd_code_80364418;
u8 D_hd_code_8036441C;
u8 D_hd_code_8036441D;
u32 D_hd_code_80364420;
u8 D_hd_code_80364424;
u32 D_hd_code_80364428;
u16 D_hd_code_8036442C;
s32 D_hd_code_80364430;
u8 D_hd_code_80364434;
f32 g_levelFOV;
s16 D_hd_code_8036443C;
s16 D_hd_code_8036443E;
s16 D_hd_code_80364440;
f32 D_hd_code_80364444;
f32 D_hd_code_80364448;
s16 D_hd_code_8036444C;
s16 D_hd_code_8036444E;
s16 D_hd_code_80364450;
s16 D_hd_code_80364452;
s16 D_hd_code_80364454;
u8 D_hd_code_80364456;
s32 D_hd_code_80364458;
s32 pad_8036445C;
struct VehicleSlot g_vehicles[12];
struct VehicleSlot *g_vehiclesEnd;
u64 D_hd_code_803649D8;
s16 D_hd_code_803649E0;
s16 D_hd_code_803649E2;
s16 D_hd_code_803649E4;
s32 D_hd_code_803649E8;
u8 D_hd_code_803649EC;
u8 D_hd_code_803649ED;
s8 D_hd_code_803649EE;
u32 D_hd_code_803649F0;
u32 D_hd_code_803649F4;
f32 D_hd_code_803649F8;
UnknownStruct_80364A00 D_hd_code_80364A00[5];
u8 D_hd_code_80364A3C;
u8 D_hd_code_80364A3D;
s32 D_hd_code_80364A40;
s32 D_hd_code_80364A44;
u8 D_hd_code_80364A48;
s16 D_hd_code_80364A4A;
s16 D_hd_code_80364A4C;
u8 D_hd_code_80364A4E;
u8 pad_80364A4F;
s8 D_hd_code_80364A50;
s32 D_hd_code_80364A54;
s32 D_hd_code_80364A58;
s32 D_hd_code_80364A5C;
u8 D_hd_code_80364A60;
s32 D_hd_code_80364A64;
u8 D_hd_code_80364A68;
u8 D_hd_code_80364A69;
u8 D_hd_code_80364A6A;
u8 D_hd_code_80364A6B;
u8 D_hd_code_80364A6C;
u8 D_hd_code_80364A6D;
u8 pad_80364A6E;
u8 D_hd_code_80364A6F;
u8 D_hd_code_80364A70;
s8 D_hd_code_80364A71;
s16 D_hd_code_80364A72;
s16 D_hd_code_80364A74;
s32 D_hd_code_80364A78;
u8 D_hd_code_80364A7C;
s32 D_hd_code_80364A80;
u8 D_hd_code_80364A84;
u8 D_hd_code_80364A85;
u8 D_hd_code_80364A86;
u8 D_hd_code_80364A87;
u64 D_hd_code_80364A88;
u64 g_currentGameState;
u64 g_nextGameState;
u64 D_hd_code_80364AA0;
u32 D_hd_code_80364AA8;
u32 pad_80364AAC;
u32 D_hd_code_80364AB0;
f32 D_hd_code_80364AB4;
f32 D_hd_code_80364AB8;
f32 D_hd_code_80364ABC;
u8 D_hd_code_80364AC0;
u8 D_hd_code_80364AC1;
s32 D_hd_code_80364AC4;
u32 D_hd_code_80364AC8;
u32 D_hd_code_80364ACC;
u64 D_hd_code_80364AD0;
s32 pad_80364AD8;
s32 pad_80364ADC;
s32 pad_80364AE0;
s32 pad_80364AE4;
u8 playerNumber; // 0x80364AE8
u8 D_hd_code_80364AE9; // nextPlayerNumber?
u8 D_hd_code_80364AEA;
UnknownData8024C414 players[5]; // size 0xFF
u8 bss_pad[0x70];
u8 D_hd_code_80365060[5];
u8 D_hd_code_80365065;
u8 D_hd_code_80365066;
s32 pad_80365068;
s32 D_hd_code_8036506C; // This is a vertex index
s32 pad_80365070;
s32 pad_80365074;
f32 D_hd_code_80365078;
f32 D_hd_code_8036507C;
f32 D_hd_code_80365080;
f32 D_hd_code_80365084;
f32 D_hd_code_80365088;
f32 D_hd_code_8036508C;
struct vec3 D_hd_code_80365090; // some 3d vec
u16 D_hd_code_8036509C;
s16 D_hd_code_8036509E;
s16 D_hd_code_803650A0;
// </bss>

// <data>
u8 D_hd_code_802E8BD0 = 0;
u8 D_hd_code_802E8BD4 = 0;
u8 D_hd_code_802E8BD8 = 0;
s32 g_currentLevel = 0;
f32 D_hd_code_802E8BE0 = 1.3f;
u8 D_hd_code_802E8BE4 = 0;
s32 D_hd_code_802E8BE8 = 0;
s32 D_hd_code_802E8BEC = -1;
u8 D_hd_code_802E8BF0 = 0;
s32 D_hd_code_802E8BF4 = 0x0A1D0000;
u8 D_hd_code_802E8BF8 = 0;
s32 D_hd_code_802E8BFC[18] = {
  0x000007D0, 0x0000092E, 0x00000578,
  0x000006A4, 0x00000640, 0x00000406, 0x00000406,
  0x000007D0, 0x00000640, 0x00000672, 0x00000064,
  0x00000000, 0x000007D0, 0x0000073A, 0x000005AA,
  0x000003E8, 0x00000064, 0x00000064
};
u8 D_hd_code_802E8C44[28] = {
  0x00, 0x01, 0x02, 0x03,
  0x04, 0x05, 0x0E, 0x07,
  0x08, 0x09, 0x0A, 0x0B,
  0x0F, 0x0D, 0x06, 0x0C,
  0x0A, 0x1B, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};
// </data>

void hdGameFrame(void);

void MainJump() {
  u32 sp74;
  s32 pad[2];
  u32* sp68;
  u32 sp28[0x10];
  s32 pad2[0x2];

  osInitialize();
  for (sp68 = (u32*)0xFFB000, sp74 = 0; sp74 < 0x10; sp74++, sp68++) {
    osPiRawReadIo((u32)sp68, &sp28[sp74]);
  }
  func_hd_code_80270AE0((u8*)sp28);
  osCreateThread(&g_Thread1, 1, Thread1, NULL, g_Thread1Stack + 0x200, 0xA);
  osStartThread(&g_Thread1);
}

void Thread1(void* arg0) {
  u8 pad[2];
  osDpSetStatus(DPC_CLR_FREEZE);
  osCreatePiManager(150, &D_hd_code_80314D80, D_hd_code_80314D98, 0xC2);
  osCreateThread(&g_Thread3, 3, Thread3, arg0, g_Thread3Stack + 0x400, 0xA);
  osStartThread(&g_Thread3);
  if (!debugFlagD) {
    osStartThread(&g_Thread3);
  }
  osSetThreadPri(0, 0);
  while(1);
}

void Thread3(void* arg0) {
    s32 sp64;
    s32 sp60;
    OSMesg sp5C;
    u8 sp5B;
    s32 sp54;

    func_hd_code_80255AD0();
    while (1)
    {
      D_hd_code_80364A70 = 0;
      do {
        rmonPrintf("game mode switch from %d to %d\n", yoshiFFS(g_currentGameState), yoshiFFS(g_nextGameState));

        D_hd_code_80364AA0 = 0ULL;

        // MASTER SWITCH BEGIN
        switch (g_nextGameState)
        {
          case INTRO_RARE_LOGO:
          {
            hdPrepareStateTransition();
            introInitialize(INTRO_MODE_RARE);
            break;
          }
          case INTRO_NINTENDO_LOGO:
          {
            hdPrepareStateTransition();
            introInitialize(INTRO_MODE_NINTENDO);
            sp60 = sc.retraceCount;
            if ((u32) (sc.retraceCount - sc.retraceCount) < 0xFU) {
              do {
              } while ((u32) (sc.retraceCount - sp60) < 0xFU);
            }
            break;
          }
          case 0x0000000100000000:
          {
            func_hd_front_end_801F6F18();
            yoshiShow(0x8012);
            D_hd_code_80364A70 = func_hd_code_80261A44(g_nextGameState);
            break;
          }
          case 0x0000080000000000:
          {
            hdPrepareStateTransition();
            func_hd_code_8025D184();
            func_hd_front_end_80200714(1);
            osSendMesg(&D_hd_front_end_80219EF8, (OSMesg)0x01000001, OS_MESG_BLOCK);
            yoshiShow(0x8011);
            break;
          }
          case 0x0000000000010000:
          {
            D_hd_code_80364A70 = func_hd_code_80261A44(g_nextGameState);
            func_hd_code_8025D184();
            func_hd_front_end_801EA4B8();
            func_hd_front_end_801E8DCC(playerNumber);
            yoshiShow(0x800A);
            break;
          }
          case 0x0000000010000000:
          {
            osSendMesg(&D_hd_front_end_80219EF8, (OSMesg)0x01000001, OS_MESG_BLOCK);
            func_hd_front_end_801E8DCC(4U);
            yoshiShow(0x8011);
            break;
          }
          case 0x0020000000000000:
          {
            sndDeactivateAllSfxByFlag_1();
            hdPrepareStateTransition();
            func_hd_code_802A0700();
            func_hd_code_8025D184();
            func_hd_front_end_80200714(1);
            osSendMesg(&D_hd_front_end_80219EF8, (OSMesg)0x0100000F, OS_MESG_BLOCK);
            osRecvMesg(&D_hd_front_end_80219F50, &sp5C, OS_MESG_BLOCK);
            if (sp5C != 0 || D_hd_code_8039C541 != 0) {
              D_hd_code_802E8BF8 = 1;
            }
            else {
              D_hd_code_802E8BF8 = 0;
            }
            D_hd_code_8039C541 = 0;
            if (D_hd_code_802E8BF8 == 0) {
              func_hd_front_end_801E8C40(4U);
              D_hd_code_80364AA0 = 0x10000000;
            }
            else {
              playerNumber = 0U;
              D_hd_code_80364AE9 = 0U;
              D_hd_code_80364AEA = 0,
              osSendMesg(&D_hd_front_end_80219EF8, (OSMesg)0x01000010, OS_MESG_BLOCK);
              osRecvMesg(&D_hd_front_end_80219F50, &D_hd_code_8039C4B4, OS_MESG_BLOCK);
              if (D_hd_code_8039C4B4 == 0)
              {
                rmonPrintf("NO EE PRESENT! - USING DUMMY EE\n");
              }
              osSendMesg(&D_hd_front_end_80219EF8, (OSMesg)0x01000006, OS_MESG_BLOCK);
              osRecvMesg(&D_hd_front_end_80219F50, &sp5C, OS_MESG_BLOCK);
              if (sp5C == 0)
              {
                sp5C = func_hd_front_end_80201E80();
              }
              if (sp5C != 0)
              {
                func_hd_front_end_801EA108(playerNumber, 1, 1);
                D_hd_code_80364AA0 = 0x40000;
              }
              else
              {
                D_hd_code_80365060[playerNumber] = 1;
                D_hd_code_80364AA0 = 0x4000;
              }
            }
            break;
          }
          case 0x0004000000000000:
          {
            hdPrepareStateTransition();
            func_hd_code_802A0700();
            func_hd_code_8025D184();
            func_hd_front_end_80200714(4);
            func_hd_front_end_801E8C40(4U);
            yoshiShow(0x8038);
            break;
          }
          case 0x0400000000000000:
          {
            D_hd_code_802E8BEC = -1;
            D_hd_code_802E8BF0 = 1;
            D_hd_code_80365065 = 0;
            D_hd_code_80364AA0 = 0x2;
            D_hd_code_8039C541 = 0;
            func_hd_front_end_801ECE9C();
            break;
          }
          case 0x0000000000000002:
          {
              switch(D_hd_code_802E8BEC) {
                  case 1:
                  case 3:
                  case 4:
                  case 6:
                  if(g_currentGameState == 0x2) {
                      g_nextGameState = 0x1000000000000;
                      hdPrepareStateTransition();
                      func_hd_front_end_80200714(7);
                      func_hd_front_end_80201240(D_hd_code_80364AC4 & 3);
                      yoshiShow(0x8035);
                      func_hd_front_end_801E8C40(D_hd_code_80364AC4 & 3);
                      D_hd_code_80364AC4 += 1;
                      break;
                  }
                  default: {
                      D_hd_code_802E8BEC++;
                      if (D_hd_code_802E8BEC == 9) {
                        D_hd_code_802E8BEC = 0;
                        D_hd_code_802E8BF0 = 0;
                      } else {
                        D_hd_code_802E8BF0 ^= 1;
                      }
                      D_hd_code_8039CAA0 = 0;
                      hdPrepareStateTransition();
                      func_hd_code_8025D184();
                      func_hd_code_80295E50();
                      func_hd_code_8025B9D0(D_hd_code_802E8BEC, &g_currentLevel);
                      if (D_hd_code_802E8BEC == 0) {
                        func_hd_code_8029A130();
                      }
                      hdInitLevel(NULL);
                      break;
                  }
              }
            break;
          }
          case WORLD_VIEW_GAME_STATE:
          {
            if (playerNumber != D_hd_code_80364AEA) {
              D_hd_code_80364AE9 = (u8) D_hd_code_80364AEA;
              playerNumber = (u8) D_hd_code_80364AEA;
            }
            func_hd_code_8028B3E0();
            rmonPrintf("World screen centred on level %d\n", g_currentLevel);
            playerNumber = (u8) D_hd_code_80364AEA;
            func_hd_front_end_801ECE9C();
            if (D_hd_code_80365065 == 0) {
              D_hd_code_80365065 = 1;
              D_hd_code_80364A87 = 0;
              D_hd_code_803643D5 = 0;
              func_hd_front_end_801FE018(8);
              g_currentLevel = players[playerNumber].levelno;
              rmonPrintf("going to level %d\n", g_currentLevel);
            }

            if (D_hd_code_8039CA60 = 0, (LEVEL_FINISHED(g_currentLevel))) {
                if(g_currentLevel > 0x2A && g_currentLevel < 0x2E) {
                    if(!(LEVEL_FINISHED(g_currentLevel+1))) {
                        g_currentLevel++;
                    }
                }
            }
            hdPrepareStateTransition();
            func_hd_front_end_801ECC8C();
            osViBlack(TRUE);
            func_hd_code_802A0700();
            func_hd_front_end_801F8530(g_currentLevel);
            break;
          }
          case LEVELS_COMPLETED:
          {
            D_hd_code_80364A70 = func_hd_code_80261A44(g_nextGameState);
            break;
          }
          case 0x0000000400000000:
          {
            yoshiShow(0x8013);
            break;
          }
          case 0x0800000000000000:
          {
            hdPrepareStateTransition();
            func_hd_front_end_80200714(1);
            func_hd_code_8025D184();
            yoshiShow(0x8059);
            break;
          }
          case 0x0000040000000000:
          {
            hdPrepareStateTransition();
            func_hd_front_end_80200714(3);
            func_hd_front_end_801E8C40(playerNumber);
            func_hd_code_8025D184();
            D_hd_front_end_8021A830 = g_currentGameState;
            yoshiShow(0x8016);
            break;
          }
          case 0x0200000000000000:
          {
            func_hd_front_end_801E8EB8(playerNumber, 1);
            func_hd_front_end_801F8228();
            yoshiShow(0x8016);
            g_nextGameState = 0x40000000000;
            break;
          }
          case 0x0000000000002000:
          {
            hdPrepareStateTransition();
            if (D_hd_code_802E8F94[g_currentLevel].unk0 != 1) {
              hdInitLevel(NULL);
              statsCopyTo(&g_statsNew, &g_statsOld);
              statsCopyTo(&g_statsNew, &g_statsRes);
              D_hd_code_802E8BD8 = 1;
            } else {
              if ((LEVEL_FINISHED(g_currentLevel))) {
                hdInitLevel(&pakBuffer);
              } else {
                hdInitLevel(NULL);
              }
              statsCopyTo(&g_statsNew, &g_statsOld);
              statsCopyTo(&g_statsNew, &g_statsRes);
              D_hd_code_80364AA0 = 4;
            }
            break;
          }
          case 0x0000000000000004:
          {
            switch (g_currentGameState)
            {
              case 0x1000000000:
                func_hd_code_8026101C();
                func_hd_code_80261E9C(g_nextGameState);
                D_hd_code_802E8BD4 = 1;
                break;
              case 0x100:
                D_hd_code_80364412 = 1;
                break;
              case 0x2000:
              {
                if (D_hd_code_802E8F94[g_currentLevel].unk0 != 1) {
                  D_hd_code_80364A70 = func_hd_code_80261A44(g_nextGameState);
                }

                D_hd_code_802E8BD4 = 1;\
                D_hd_code_802E8BD4 &= !func_hd_code_8026AD30(0x52);\
                D_hd_code_802E8BD4 &= !func_hd_code_8026AD30(0x56);\
                if ((LEVEL_FINISHED(g_currentLevel)) && D_hd_code_802E8F94[g_currentLevel].unk0 == 1) \
                  D_hd_code_802E8BD4 &= !func_hd_code_8026AD30(0x55);\
                else \
                  D_hd_code_802E8BD4 &= !func_hd_code_8026AD30(0x57);

                D_hd_code_802E8BD8 = !D_hd_code_802E8BD4;
                rmonPrintf("Unpause at start = %d\n", D_hd_code_802E8BD4);
                D_hd_code_80364A58 = sc.unk803156C0;
                D_hd_code_80358064 = 0;
                func_hd_code_8025BB38();
                rmonPrintf("snew ip=%8d : tc=%5d : bd=%2d : cr=%2d : rt=%3d : coin=%1d : bdn=%1d\n", g_statsNew.money, g_statsNew.timeCode, g_statsNew.buildingsDestroyed, (s32) g_statsNew.civiliansRescued, (s32) g_statsNew.rdusFound, (s32) g_statsNew.coin, (s32) g_statsNew.bdn);
                rmonPrintf("sold ip=%8d : tc=%5d : bd=%2d : cr=%2d : rt=%3d : coin=%1d : bdn=%1d\n", g_statsOld.money, g_statsOld.timeCode, g_statsOld.buildingsDestroyed, (s32) g_statsOld.civiliansRescued, (s32) g_statsOld.rdusFound, (s32) g_statsOld.coin, (s32) g_statsOld.bdn);
                rmonPrintf("sres ip=%8d : tc=%5d : bd=%2d : cr=%2d : rt=%3d : coin=%1d : bdn=%1d\n", g_statsRes.money, g_statsRes.timeCode, g_statsRes.buildingsDestroyed, (s32) g_statsRes.civiliansRescued, (s32) g_statsRes.rdusFound, (s32) g_statsRes.coin, (s32) g_statsRes.bdn);
                rmonPrintf("srs2 ip=%8d : tc=%5d : bd=%2d : cr=%2d : rt=%3d : coin=%1d : bdn=%1d\n", g_statsRes2.money,  g_statsRes2.timeCode, g_statsRes2.buildingsDestroyed, (s32) g_statsRes2.civiliansRescued, (s32) g_statsRes2.rdusFound, (s32) g_statsRes2.coin, (s32) g_statsRes2.bdn);
                break;
              }
            }
            break;
          }
          case 0x0000000000000100:
          {
            D_hd_code_80364412 = 1;
            break;
          }
          case BEFORE_LEVEL_STATS:
          {
            sp5B = 0;
            switch (g_currentGameState)
            {
              case 0x100000000000:
                func_hd_code_8028B3E0();
                D_hd_code_80364A70 = func_hd_code_80261A44(g_nextGameState);
              case 0x4000:
                sp5B = func_hd_code_80285814();
                break;

              case 0x40000000000:
              case 0x80000000000000:
              case 0x0100000000000000:
              {
                if (playerNumber != D_hd_code_80364AE9) {
                  D_hd_code_80364AE9 = playerNumber,
                  rmonPrintf("switching to new player ...........\n");
                  func_hd_code_80285814();
                }
                break;
              }

            }
            hdPrepareStateTransition();
            if (sp5B != 0) {
              osSendMesg(&D_hd_front_end_80219EF8, (OSMesg)((g_currentLevel << 8) | 0xD | (playerNumber << 0x10)), OS_MESG_BLOCK);
            }

            D_hd_front_end_8020C070[D_hd_code_802F8BDC[D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)]].unkE + D_hd_code_802F8BDC[D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)]].unk10 - 2].unk0 &= ~1;
            D_hd_front_end_8020C070[D_hd_code_802F8BDC[D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)]].unkE + D_hd_code_802F8BDC[D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)]].unk10 - 2].unk0 |= 0x800;

            func_hd_code_8026B8F8();
            yoshiShow(D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)] | 0x8000);

            D_hd_code_802F8BDC[D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)]].unk18 =
              D_hd_code_802F8BDC[D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)]].unkE + D_hd_code_802F8BDC[D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)]].unk10 - 3;

            D_hd_code_802F8BDC[D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)]].unk8 &= ~8;

            statsCopyTo(&g_statsNew, &g_statsOld);
            D_hd_code_80315438 = func_hd_front_end_801EE800(&D_hd_code_80364A60, 1, 0),
            func_hd_front_end_801E8C40(playerNumber);
            func_hd_front_end_801EC30C(D_hd_code_80315438);
            func_hd_front_end_801EC288(D_hd_code_80315438);
            func_hd_front_end_80200714(1);
            D_hd_code_80364A71 = func_hd_front_end_801EF1E0();
            if (D_hd_code_80364A71 != -1) {
              func_hd_front_end_801F55D8();
            }
            break;
          }
          case IN_LEVEL_GAME_STATE:
          {
            hdPrepareStateTransition();
            if (g_currentGameState == 0x4000) {
              osRecvMesg(&D_hd_front_end_80219F50, NULL, OS_MESG_BLOCK);
            }
            osViBlack(TRUE);
            hdInitLevel(NULL);
            func_hd_code_802661EC();
            if (g_currentLevel == LEVEL_SHUTTLE_CLEAR) {
              yoshiShow(0x8024);
            }
            break;
          }
          case PROMOTION_SCREEN:
          {
            hdPrepareStateTransition();
            sp54 = sc.retraceCount;
            if ((u32)(sc.retraceCount - sc.retraceCount) < 0xFU)
            {
              do
              {
              } while ((u32)(sc.retraceCount - sp54) < 0xFU);
            }
            func_hd_front_end_801ED790();
            func_hd_front_end_80200714(3);
            D_hd_code_80364A71 = func_hd_front_end_801EF1E0();
            if (D_hd_code_80364A71 != -1)
            {
              func_hd_front_end_801F55D8();
            }
            func_hd_front_end_801E8C40(playerNumber);
            func_hd_front_end_801EC30C(D_hd_code_80315438);
            break;
          }
          case 0x0000000008000000:{
            switch (g_currentGameState)
            {
              case 0x40:
              case 0x400:
              case 0x20000000:
              {
                hdPrepareStateTransition();
                func_hd_front_end_80200714(1);
                D_hd_code_80364A71 = func_hd_front_end_801EF1E0();
                if (D_hd_code_80364A71 != -1)
                {
                  func_hd_front_end_801F55D8();
                }
                func_hd_front_end_801E8C40(playerNumber);
                statsCopyTo(&g_statsRes2, &g_statsNew);
                D_hd_code_80315438 = func_hd_front_end_801EE800(&D_hd_code_80364A60, 1, 0);
                func_hd_front_end_801EC30C(D_hd_code_80315438);
                func_hd_front_end_801EC288(D_hd_code_80315438);
                break;
              }
              case 0x40000000:
                D_hd_code_80364A70 = func_hd_code_80261A44(g_nextGameState);
                break;

              case 0x40000000000:
              case 0x80000000000000:
              case 0x0100000000000000:
              {
                if (playerNumber != D_hd_code_80364AE9)
                {
                  rmonPrintf(
                    "switching to new player ...........\n");
                  D_hd_code_80364AE9 = (u8)playerNumber;
                  D_hd_code_803643D5 = 0;
                  func_hd_code_80285814();
                }
                hdPrepareStateTransition();
                D_hd_code_80364A71 = func_hd_front_end_801EF1E0();
                if (D_hd_code_80364A71 != -1)
                {
                  func_hd_front_end_801F55D8();
                }
                func_hd_front_end_801E8C40(playerNumber);
                D_hd_code_80315438 = func_hd_front_end_801EE800(&D_hd_code_80364A60, 1, 0);
                func_hd_front_end_80200714(1);
                func_hd_front_end_801EC30C(D_hd_code_80315438);
                func_hd_front_end_801EC288(D_hd_code_80315438);
                break;
              }

              default:
              {
                if (saveIt[playerNumber] && saveIt[playerNumber] != g_currentLevel + 1)
                {
                  rmonPrintf(ASSERT_MESSAGE, "!saveIt[playerNumber] || saveIt[playerNumber]==levelno+1", "./master_switch.c", 0x1E8U);
                }
                saveIt[playerNumber] = g_currentLevel + 1;
                if (D_hd_code_803643D7 != 0)
                {
                  func_hd_code_802C1DD0(D_hd_code_802E8F94[g_currentLevel].unk0 == 0x20 || D_hd_code_802E8F94[g_currentLevel].unk0 == 0x80);
                }

                D_hd_code_803643D5 = !(LEVEL_FINISHED(g_currentLevel));

                if (playerNumber == D_hd_code_80364AEA) D_hd_code_80364A87 |= D_hd_code_803643D5;


                if ((D_hd_code_80364AA8 == 1) && (D_hd_code_803643D5 == 0))
                {
                  for (sp64 = 0; sp64 < 0x40; sp64++)
                  {
                    D_hd_code_8039C4F8.data[sp64] = pakBuffer[sp64];
                  }
                }
                func_hd_code_802CF5B0();
                func_hd_code_80297960();
                if (D_hd_code_80364AA8 == 1)
                {
                  if (recordStatus(&pakBuffer) >= 0x3D)
                  {
                    rmonPrintf(
                      ASSERT_MESSAGE,
                      "record_status(pakBuffer)<=LEVEL_SAVE_SIZE-4",
                      "./master_switch.c",
                      0x201U);
                  }
                  if ((saveLevel != 0) &&
                      (saveLevel != (g_currentLevel + 1)))
                  {
                    rmonPrintf(
                      ASSERT_MESSAGE,
                      "!saveLevel || saveLevel==levelno+1",
                      "./master_switch.c",
                      0x203U);
                  }
                  saveLevel = g_currentLevel + 1;
                  if ((u32)(func_hd_code_8028604C(D_hd_code_80364A5C) +
                            g_statsNew.timeCode) >= 0xEA60U)
                  {
                    g_statsNew.timeCode = 0xEA5F;
                  }
                  else
                  {
                    g_statsNew.timeCode = g_statsNew.timeCode + func_hd_code_8028604C(D_hd_code_80364A5C);
                  }
                }
                else if (D_hd_code_803643D7 != 0)
                {
                  func_hd_code_80264AEC();
                  g_statsNew.timeCode = D_hd_code_802E8FCA[g_currentLevel].unk0 - D_hd_code_80367BF6;
                }
                else
                {
                  g_statsNew.timeCode = 0xFFFF;
                }
                if (g_statsNew.timeCode == 0)
                {
                  rmonPrintf(ASSERT_MESSAGE,
                                        "nss.tc",
                                        "./master_switch.c",
                                        0x212U);
                }
                if (g_statsNew.timeCode == 0)
                {
                  g_statsNew.timeCode = 1;
                }
                hdPrepareStateTransition();
                if (D_hd_code_80365066 != 0)
                {
                  g_statsNew.buildingsDestroyed = D_hd_code_8036EB92;
                  D_hd_code_80365066 = 0;
                }
                if (D_hd_code_803643D5 != 0)
                {
                  statsCopyTo(&g_statsNew, &g_statsOld);
                }
                else
                {
                  statsCopyTo(&g_statsRes, &g_statsOld);
                }
                D_hd_code_80315438 = func_hd_front_end_801EE800(&D_hd_code_80364A60, 1, 1),
                statsCopyTo(&g_statsNew, &g_statsRes2);

                if (D_hd_code_80364A60 != 0)
                {
                  D_hd_code_80364AA0 = 0x40000000;
                  D_hd_code_80364A64 = 0xDC;
                  D_hd_code_80364A70 = 0;
                }
                else
                {
                  func_hd_front_end_801EC30C(D_hd_code_80315438);
                  func_hd_front_end_80200714(1);
                  D_hd_code_80364A71 = func_hd_front_end_801EF1E0();
                  if (D_hd_code_80364A71 != -1)
                  {
                    func_hd_front_end_801F55D8();
                  }
                  func_hd_front_end_801E8C40(playerNumber);
                }

                D_hd_front_end_8020C070[D_hd_code_802F8BDC[D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)]].unkE + D_hd_code_802F8BDC[D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)]].unk10 - 2].unk0 |= 1;
                D_hd_front_end_8020C070[D_hd_code_802F8BDC[D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)]].unkE + D_hd_code_802F8BDC[D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)]].unk10 - 2].unk0 &= ~0x800;
                break;
              }
            }

            if ((D_hd_code_803643D5 != 0) && (playerNumber == D_hd_code_80364AEA))
            {
              D_hd_code_802F8BDC[D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)]].unk18 = D_hd_code_802F8BDC[D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)]].unkE + D_hd_code_802F8BDC[D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)]].unk10 - 1;
            }
            else
            {
              D_hd_code_802F8BDC[D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)]].unk18 = D_hd_code_802F8BDC[D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)]].unkE + D_hd_code_802F8BDC[D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)]].unk10 - 3;
            }

            D_hd_code_802F8BDC[D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)]].unk8 |= 8;

            func_hd_code_8026B8F8();
            if (D_hd_code_802E8BF8 != 0)
            {
              D_hd_front_end_8020C070[0x1D].unk0 &= ~1;
            }
            yoshiShow(D_hd_code_802F4868[yoshiFFS(D_hd_code_80364AA8)] | 0x8000);
            break;
          }
          case 0x0000000000000040:
          {
            if (g_currentGameState & 0x04000200) {
              func_hd_code_8028B3E0();
              g_statsNew.timeCode = func_hd_code_8028604C(D_hd_code_80364A5C),
              statsCopyTo(&g_statsNew, &g_statsOld);
              func_hd_front_end_801EE800(&D_hd_code_80364A60, 0, 1);
            }
            D_hd_code_802F5804[0x18].unk0 = D_hd_code_802F5804[0x18].unk0 | 1;
            D_hd_code_802F5804[0x18].unk0 = D_hd_code_802F5804[0x18].unk0 & ~0x800;
            D_hd_code_802F5804[0x17].unk0 = D_hd_code_802F5804[0x17].unk0 | 1;
            D_hd_code_802F5804[0x17].unk0 = D_hd_code_802F5804[0x17].unk0 & ~0x800;
            D_hd_code_802F5804[0x11].unk0 = D_hd_code_802F5804[0x11].unk0 & ~1;
            D_hd_code_802F5804[0x11].unk0 = D_hd_code_802F5804[0x11].unk0 | 0x800;

            if ((LEVEL_FINISHED(g_currentLevel))) {
              D_hd_code_802F8BDC[6].unk18 = 0x18,
              D_hd_code_802F8BDC[7].unk18 = 0x22;
            } else {
              D_hd_code_802F8BDC[6].unk18 = 0x17,
              D_hd_code_802F8BDC[7].unk18 = 0x21;
            }
            D_hd_code_80364A50 = 0;
            D_hd_code_80364A54 = sc.retraceCount;
            hdPrepareStateTransition();
            if (D_hd_code_802E8F94[g_currentLevel].unk0 == 1 && (LEVEL_FINISHED(g_currentLevel)) && (D_hd_code_803643D5 == 0)) {
              hdInitLevel(&D_hd_code_8039C4F8);
            } else {
              hdInitLevel(NULL);
            }
            func_hd_code_8026B8F8();
            func_hd_code_8025BB50();
            break;
          }
          case 0x0000000020000000:
          {
            hdPrepareStateTransition();
            if (g_currentGameState == 0x4000)
            {
              osRecvMesg(&D_hd_front_end_80219F50, NULL, OS_MESG_BLOCK);
            }
            osViBlack(TRUE);
            func_hd_code_802A0700();
            if (func_hd_front_end_801E7000() != 0)
            {
              func_hd_front_end_80200714(2);
            }
            else
            {
              D_hd_code_80364AA0 = 0x2000;
            }
            break;
          }
          case ENTER_NAME_GAME_STATE:
          {
            osSendMesg(&D_hd_front_end_80219EF8, (OSMesg)((playerNumber << 0x10) | 0x14 | 0x01000000), OS_MESG_BLOCK);
            osRecvMesg(&D_hd_front_end_80219F50, NULL, OS_MESG_BLOCK);
            func_hd_front_end_801EA93C("ENTER NAME!", D_hd_code_803047A0, 7, 0x1E, &players[playerNumber]);
            yoshiShow(0x800B);
            func_hd_code_8025D184();
            D_hd_code_80364A70 = func_hd_code_80261A44(g_nextGameState);
            break;
          }
          case 0x4000000000000000:
          {
            hdPrepareStateTransition();
            func_hd_front_end_80200714(1);
            D_hd_front_end_8020C070[0x09].unkC = "QUIT GAME!",
            D_hd_front_end_8020C070[0x09].unk10 = D_hd_code_803047CC,
            D_hd_front_end_8020C070[0x09].unk8 = 0x16U,
            D_hd_front_end_8020C070[0x09].unk6 = D_hd_front_end_8020C070[0x09].unk8;
            yoshiShow(0x800C);
            break;
          }
          case 0x0000001000000000:
          {
            func_hd_code_80260EE0(0x18);
            sndSetSfxSlotVolume(0, 0);
            func_hd_code_80297ECC();
            yoshiShow(0x8015);
            D_hd_code_802E8BD8 = 1;
            break;
          }
          case TUTORIAL_GAME_STATE:
          {
            func_hd_code_80299C0C();
            D_hd_code_80364A70 = func_hd_code_80261A44(g_nextGameState);
            hdPrepareStateTransition();
            func_hd_code_80299C20();
            if (g_currentGameState == 0x4000 || g_currentLevel == LEVEL_CMO_INTRO) {
              osRecvMesg(&D_hd_front_end_80219F50, NULL, OS_MESG_BLOCK);
            }
            osViBlack(TRUE);
            hdInitLevel(NULL);
            break;
          }
          case 0x0040000000000000:
          {
            hdPrepareStateTransition();
            osSendMesg(&D_hd_front_end_80219EF8, (OSMesg)0x01000010, OS_MESG_BLOCK);
            osRecvMesg(&D_hd_front_end_80219F50, &D_hd_code_8039C4B4, OS_MESG_BLOCK);
            if (D_hd_code_8039C4B4 != 0)
            {
              func_hd_code_8025D184();
              func_hd_front_end_80200714(1);
              D_hd_front_end_8020C070[0x09].unkC = "ERASE SAVED GAME!",
              D_hd_front_end_8020C070[0x09].unk10 = D_hd_code_803047B4,
              D_hd_front_end_8020C070[0x09].unk8 = 0x14U,
              D_hd_front_end_8020C070[0x09].unk6 = D_hd_front_end_8020C070[0x09].unk8;
              yoshiShow(0x800C);
            }
            else
            {
              D_hd_code_80364AA0 = 0x10;
            }
            break;
          }
          case 0x0100000000000000:
          {
            D_hd_front_end_8020C070[0x09].unkC = "BECOME GUEST PLAYER:",
            D_hd_front_end_8020C070[0x09].unk10 = D_hd_code_803047DC,
            D_hd_front_end_8020C070[0x09].unk8 = 0x14U,
            D_hd_front_end_8020C070[0x09].unk6 = D_hd_front_end_8020C070[0x09].unk8;
            yoshiShow(0x800C);
            break;
          }
          case 0x0000000000400000:
          {
            func_hd_front_end_801EA6E8();
            yoshiShow(0x800A);
            break;
          }
          case 0x0000000000000008:
          {
            D_hd_code_802E8BD8 = 1;
            func_hd_code_80260E80();
            break;
          }

        }

        D_hd_code_80364A88 = g_currentGameState;
        g_currentGameState = g_nextGameState;
        g_nextGameState = D_hd_code_80364AA0;
      } while (g_nextGameState != 0);

      if (D_hd_code_80364A70) {
        func_hd_code_80261FB0(D_hd_code_80364A70);
      }
      while (g_nextGameState == 0) {
        D_hd_code_80364AD0 = osGetTime();
        func_hd_code_8025B2B8();
        if (g_currentGameState & 0x4000) {
          D_hd_code_80364ACC = (osGetTime() - D_hd_code_8036BF38) / 0x1E91U;
          func_hd_front_end_801F8980();
          D_hd_code_80364AC8 = (osGetTime() - D_hd_code_80364AD0) / 0x1E91U;

          if (g_gfxTaskSlotUsed[2]) {
            gfxWaitForTask(GFX_TASK_ID_MAIN);
          }
          if (g_gfxTaskSlotUsed[0]) {
            gfxWaitForTask(GFX_TASK_ID_MAIN);
          }
          gfxWaitForTask(GFX_TASK_ID_MAIN);
        } else if (g_currentGameState & 0xC9FD8FE7DBFF8080) {
          D_hd_code_80364ACC = (osGetTime() - D_hd_code_8036BF38) / 0x1E91U;
          func_hd_front_end_801FE990();
          D_hd_code_80364AC8 = (osGetTime() - D_hd_code_80364AD0) / 0x1E91U;
          gfxWaitForTask(GFX_TASK_ID_MAIN);
        } else if (g_currentGameState & 0x20000000) {
          func_hd_front_end_801E7598();
          gfxWaitForTask(GFX_TASK_ID_MAIN);
        } else if (g_currentGameState & 0x30) {
          introRender();
          gfxWaitForTask(GFX_TASK_ID_MAIN);
        } else {
          D_hd_code_80364ACC = (osGetTime() - D_hd_code_8036BF38) / 0x1E91U;
          hdGameFrame();
          D_hd_code_80364AC8 = (osGetTime() - D_hd_code_80364AD0) / 0x1E91U;
          if (g_gfxTaskSlotUsed[1]) {
            gfxWaitForTask(GFX_TASK_ID_SHADOW);
          }
          if (g_gfxTaskSlotUsed[2]) {
            gfxWaitForTask(GFX_TASK_ID_BLUR);
          }
          gfxWaitForTask(GFX_TASK_ID_MAIN);
        }
        func_hd_code_80255D34();
        g_frameCount += 1;
        D_hd_code_80358064 += 1;
        if (D_hd_code_802E8BD0 == 0) {
          D_hd_code_80358068 += 1;
        }
      }
      if (g_currentGameState & 0x104 && ((D_hd_code_803643D6 != 0) || (D_hd_code_803643D7 != 0))) {
        func_hd_code_8025BBE8(0, 0, 0);
      }
      if (areWeFading()) {
        rmonPrintf(ASSERT_MESSAGE,
          "!areWeFading()", "hd.c", 0x273U);
      }
      switch (g_nextGameState)
      {
        case 0x400000000000:
          func_hd_code_80299E10(1);
          break;
        case 0x200000000000:
          func_hd_code_80299E10(0);
          break;
        case 0x2000000000000:
          func_hd_code_80286330();
          break;
      }
      if (playerNumber != D_hd_code_80364AEA) {
        continue;
      }
      if (g_nextGameState != 0x4000) {
        continue;
      }
      if (func_hd_code_8028653C() == 0) {
        continue;
      }
      func_hd_code_802860F0();
    }
}

void hdGameFrame(void) {
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    u8 sp63;
    Gfx *entry;
    u8 sp5B;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s16 sp4A;
    s16 pad48;

    if (D_hd_code_802FA268 != 0 && ((g_currentButtons & R_CBUTTONS) && !(g_previousButtons & R_CBUTTONS)) && (g_currentGameState & 0x104)) {
        D_hd_code_803643DA = 1;
        D_hd_code_803643D9 = 0;
        if (g_currentButtons & U_CBUTTONS) {
            if (D_hd_code_80364AA8 != 1 || !LEVEL_FINISHED(g_currentLevel)) {
                D_hd_code_803643DA = 0;
                D_hd_code_803643D9 = 1;
            }
        }
        if ((g_currentButtons & Z_TRIG) && D_hd_code_803643DA != 0) {
            D_hd_code_803F7688 = 1;
            g_statsNew.rdusFound = D_hd_code_8036EB90;
            g_statsNew.civiliansRescued = D_hd_code_8036EB93;
            D_hd_code_80365066 = 1;
            func_hd_code_80285AB0(2);
            func_hd_code_80285AB0(1);
        }
        if (LEVEL_FINISHED(g_currentLevel) && D_hd_code_80364AA8 == 1 && D_hd_code_803643DA != 0) {
            D_hd_code_802E8BD8 = 1;
            fadeToFast(0x08000000);
        }
    }

    nextdma = 0;
    no_palette_dmas = 0;
    D_hd_code_803A7426 = 0;
    if (g_frameCount != 0) {
        if (D_hd_code_8035805C == 0) {
            if (g_frameCount >= 6U) {
                func_hd_code_8024B8F4(&D_hd_code_803156F8[D_hd_code_8035805C].projection, &D_hd_code_803156F8[D_hd_code_8035805C].unk180);
            }
        } else {
            sp68 = 0;
            sp63 = 0;
            while (!sp63) {
                if (g_vehicles[sp68].unk5C == D_hd_code_80364456) {
                    sp63 = 1;
                } else {
                    sp68 += 1;
                }
            }

            sp64 = 0;
            sp63 = 0;
            while (!sp63) {
                if (g_shadows.shadows[sp64].unk1022 == D_hd_code_80364456) {
                    sp63 = 1;
                } else {
                    sp64 += 1;
                }
            }

            func_hd_code_80258544(g_shadows.shadows[sp64].data, g_shadows.shadows[sp64].unk1004, g_shadows.shadows[sp64].unk1010, g_shadows.shadows[sp64].unk100C, g_shadows.shadows[sp64].unk1000, g_vehicles[sp68].unk54, g_vehicles[sp68].unk0, g_vehicles[sp68].unk4);
        }
    }

    sp68 = 0;
    sp63 = 0;
    while (!sp63) {
        if (g_vehicles[sp68].unk5C == D_hd_code_80364456) {
            sp63 = 1;
        } else {
            sp68 += 1;
        }
    }
    if (D_hd_code_8035805C == 0) {
        func_hd_code_80279778(D_hd_code_803643E0, D_hd_code_803643E4, D_hd_code_803643E8, D_hd_code_803643F8, D_hd_code_803643FC, D_hd_code_80364400, g_vehicles[sp68].unk58, g_vehicles[sp68].unk0, g_vehicles[sp68].unk8, g_vehicles[sp68].unk60);
    } else {
        func_hd_code_80279778(D_hd_code_803643E0, D_hd_code_803643E4, D_hd_code_803643E8, D_hd_code_803643F8, D_hd_code_803643FC, D_hd_code_80364400, g_vehicles[sp68].unk58, g_vehicles[sp68].unk0, g_vehicles[sp68].unk4, g_vehicles[sp68].unk60);
    }
    D_hd_code_803649D8 = osGetTime();
    func_hd_code_8028A3E4();
    gfxSubmitTask(D_hd_code_803156F8[D_hd_code_8035805C].dp, D_hd_code_80358078, 3, 1, GFX_TASK_ID_MAIN, 1);
    func_hd_code_802A5720();
    D_hd_code_8035805C ^= 1;
    switch (D_hd_code_802E8BD0) {
    case 0: {
        if (((u8) D_hd_code_802E8BD8 != 0) && ((D_hd_code_802E8BD0 = 1, D_hd_code_802E8BD4 = 0, D_hd_code_802E8BD8 = 0, D_hd_code_803156F4 = D_hd_code_8035805C ^ 1, (0 != 0)) || (g_currentGameState & 0x104))) {
            if (D_hd_code_8036EB99 == 0) {
                sndSetSfxSlotVolume(0, 0);
            }
            func_hd_code_80261570(0.5f);
            if (g_currentGameState == 4 && ((D_hd_code_803643DB != 0) || (D_hd_code_80364AC1 != 0)) && (D_hd_code_8036BB18 == 0)) {
                g_nextGameState = 0x100;
                func_hd_code_802A45D4(0xA);
                D_hd_code_80364A78 = 0;
            }
        }
        break;
    }
    case 1: {

        if (D_hd_code_802E8BD4 != 0 && D_hd_code_8035805C != D_hd_code_803156F4) {
            D_hd_code_802E8BD8 = 0, D_hd_code_802E8BD4 = 0, D_hd_code_802E8BD0 = 0;
            if(g_currentGameState & 0x104) {
                if (D_hd_code_80358064 != 0) {
                    rmonPrintf("LOCKING KEYS!\n");
                    D_hd_code_80370C38 = 1;
                }
                func_hd_code_80261E9C(g_currentGameState);
                func_hd_code_80261570(1.0f);
                if (g_currentGameState == 0x100 && ((D_hd_code_803643DB != 0) || (D_hd_code_80364AC1 != 0))) {
                    g_nextGameState = 4;
                    func_hd_code_802A45D4(0xA);
                }
                if (D_hd_code_80358068 == 0) {
                    D_hd_code_80358064 = 0;
                }
            }
        }
        break;
    }
    }
    if (D_hd_code_802E8BD0 != 0) {
        D_hd_code_803156F5 = D_hd_code_803156F4;
    } else {
        D_hd_code_803156F5 = D_hd_code_8035805C;
    }
    if (D_hd_code_803643DB != 0 && g_currentGameState & 0x104) {
        func_hd_code_802BA148();
    }
    if (D_hd_code_803643DC != 0 && g_currentGameState & 0x1905) {
        func_hd_code_802B8794();
    }
    func_hd_code_802683E0();
    D_hd_code_803649EE = 0;
    if (D_hd_code_80364456 == 0 && !(g_currentGameState & 0x1801)) {
        func_hd_code_8024AE2C();
    }
    controllerUpdateInput();
    if (g_currentGameState & 0x104) {
        sp5B = 0;
        if (g_currentButtons & D_CBUTTONS && !(g_currentButtons & U_CBUTTONS)) {
            if (((f64) D_hd_code_802E8BE0 < 1.5) && (g_currentGameState == 4)) {
                sp5B = 2;
                if (!(g_previousButtons & D_CBUTTONS)) {
                    sndPlaySfx(D_hd_code_80367738, 0xDCU, NULL);
                }
            } else if (!(g_previousButtons & D_CBUTTONS) && (g_currentGameState != 0x100)) {
                sp5B = 3;
            }
        }
        if (sp5B == 0) {
            if ((g_currentButtons & U_CBUTTONS) && !(g_currentButtons & D_CBUTTONS)) {
                if (((f64) D_hd_code_802E8BE0 > 1.0) && g_currentGameState == 4 && (D_hd_code_80364A7C == 0)) {
                    sp5B = 1;
                    if (!(g_previousButtons & U_CBUTTONS)) {
                        sndPlaySfx(D_hd_code_80367738, 0xDDU, NULL);
                    }
                } else if (!(g_previousButtons & U_CBUTTONS) && g_currentGameState == 0x100) {
                    sp5B = 4;
                }
            } else {
                D_hd_code_80364A7C = 0;
            }
        }
        switch (sp5B) {
        case 0:
            break;
        case 2:
            D_hd_code_802E8BE0 = D_hd_code_802E8BE0 + 0.05;
            if (D_hd_code_802E8BE0 > 1.5) {
                D_hd_code_802E8BE0 = 1.5f;
            }
            break;
        case 1:
            D_hd_code_802E8BE0 = D_hd_code_802E8BE0 - 0.05;
            if (D_hd_code_802E8BE0 < 1.0) {
                D_hd_code_802E8BE0 = 1.0f;
            }
            break;
        case 3:
            if ((D_hd_code_803643DB != 0) || (D_hd_code_80364AC1 != 0)) {
                func_hd_code_802A45D4(0xA);
                g_nextGameState = 0x100;
                D_hd_code_80364A78 = 0;
                sndPlaySfx(D_hd_code_80367738, 0xDFU, NULL);
            }
            break;
        case 4:
            D_hd_code_80364A7C = 1;
            if ((D_hd_code_803643DB != 0) || (D_hd_code_80364AC1 != 0)) {
                func_hd_code_802A45D4(0xA);
                g_nextGameState = 4;
                sndPlaySfx(D_hd_code_80367738, 0xDFU, NULL);
            }
            break;
        }
    }
    if (g_currentGameState == 0x100 && (D_hd_code_802E8BD0 != 0) && (D_hd_code_8036BB1C == 2) && (D_hd_code_803643DB != 0) && (D_hd_code_8036BB18 == 0)) {
        if (!(g_currentButtons & Z_TRIG) && !(g_currentButtons & R_TRIG)) {
            D_hd_code_80364A80 = 0;
        } else {
            D_hd_code_80364A80 = D_hd_code_80364A80 + 0x64;
            if (D_hd_code_80364A80 >= 0x321) {
                D_hd_code_80364A80 = 0x320;
            }
            if (g_currentButtons & Z_TRIG) {
                D_hd_code_80364A78 += D_hd_code_80364A80;
            }
            if (g_currentButtons & R_TRIG) {
                D_hd_code_80364A78 -= D_hd_code_80364A80;
            }
        }
        sp54 = D_hd_code_803EF6E4 + D_hd_code_80364A78;
        sp50 = D_hd_code_803EF6F8 - 0x190;
        sp4C = D_hd_code_803EF6F8 + D_hd_code_803EF6F0;
        if (sp4C < sp54) {
            D_hd_code_80364A78 = sp4C - D_hd_code_803EF6E4;
        }
        if (sp54 < sp50) {
            D_hd_code_80364A78 = sp50 - D_hd_code_803EF6E4;
        }
        if (g_currentButtons & (Z_TRIG | R_TRIG)) {
            if ((D_hd_code_802F8BDC->unk4 - 0x18) < -0x100) {
                D_hd_code_802F8BDC->unk4 = -0x100;
            } else {
                D_hd_code_802F8BDC->unk4 = (s16) (D_hd_code_802F8BDC->unk4 - 0x18);
            }
            D_hd_code_8036BB34 = (D_hd_code_8036BB34 * 0.8 > 0.1)?(D_hd_code_8036BB34 * 0.8):(0.1);
            D_hd_code_802F8BDC->unk8 &= ~0x20;
        } else {
            if ((D_hd_code_802F8BDC->unk4 + 0x20) >= 0x21) {
                D_hd_code_802F8BDC->unk4 = 0x20;
            } else {
                D_hd_code_802F8BDC->unk4 = (s16) (D_hd_code_802F8BDC->unk4 + 0x20);
            }

            D_hd_code_8036BB34 = (D_hd_code_8036BB34 / 0.8 < 1.) ? (D_hd_code_8036BB34 / 0.8) : 1.0;
            if (D_hd_code_8036BB34 == 1.0) {
                D_hd_code_802F8BDC->unk8 |= 0x20;
            }
        }
    } else {
        D_hd_code_80364A80 = 0;
        if ((D_hd_code_802F8BDC->unk4 + 0x20) >= 0x21) {
            D_hd_code_802F8BDC->unk4 = 0x20;
        } else {
            D_hd_code_802F8BDC->unk4 = (s16) (D_hd_code_802F8BDC->unk4 + 0x20);
        }

        D_hd_code_8036BB34 = D_hd_code_8036BB34 / 0.8 < 1.0 ? D_hd_code_8036BB34 / 0.8 : 1.0;
        if (D_hd_code_8036BB34 == 1.0) {
            D_hd_code_802F8BDC->unk8 |= 0x20;
        }
    }
    if ((D_hd_code_80370C22 != 0) && (D_hd_code_802E8BD0 == 0) && (D_hd_code_80364456 != 0) && (D_hd_code_8036443C == 0) && ((D_hd_code_80364AA8 == 1) || (D_hd_code_80364AA8 == 0x80))) {
        func_hd_code_8024B188();
    }
    func_hd_code_8024B618();
    if ((g_currentButtons & B_BUTTON) && !(g_previousButtons & B_BUTTON) && (areWeFading() == 0) && g_nextGameState == 0) {
        switch(g_currentGameState) {
            case 0x100000000000:
                if((g_currentLevel != 0x2F) && (g_currentLevel != 0x31) && ((g_currentLevel != 0x26) || (D_hd_code_80364A88 == 0x4000))) {
                    sndPlaySfx(D_hd_code_80367738, 0xDEU, NULL);
                    g_nextGameState = 0x4000;
                }
                break;
            case 0x40:
            case 0x400:
                sndPlaySfx(D_hd_code_80367738, 0xDEU, NULL);
                if ((LEVEL_FINISHED(g_currentLevel)) != 0) {
                    g_nextGameState = 0x08000000;
                } else {
                    g_nextGameState = 0x4000;
                }
                break;
            case 0x800:
            case 0x1000:
                if ((g_currentLevel != 0x32) || ((D_hd_code_80364A88 == 0x4000))) {
                    sndPlaySfx(D_hd_code_80367738, 0xDEU, NULL);
                    g_nextGameState = 0x4000;
                }
                break;

        }
    }
    if ((D_hd_code_803643DC != 0) && ((D_hd_code_802E8BD0 == 0) || (g_currentGameState & 0x1801))) {
        func_hd_code_802B899C();
        if ((g_currentGameState & 0x1801)) {
            if (areWeFading() == 0) {
                if (((g_nextGameState == 0)) || (g_nextGameState & 0x1801)) {
                    func_hd_code_802AEEC8();
                }
                func_hd_code_802B8AE4();
            }
        } else {
            func_hd_code_8026510C();
        }
    }
    if ((D_hd_code_802E8BD0 == 0) && (D_hd_code_80364A84 == 0)) {
        func_hd_code_8024B7AC();
    }
    if ((D_hd_code_8039CA62 != 0) && (D_hd_code_802E8BD0 == 0)) {
        func_hd_code_80294F00();
    }
    if ((D_hd_code_803643DB != 0) && (D_hd_code_80364AA8 & 0x81)) {
        if (!(g_currentGameState & 0x1801)) {
            func_hd_code_802BA354();
        }
        if (((g_currentGameState & 0x104)) && (func_hd_code_8026B10C() == 0) && (D_hd_code_802E8BD0 == 0) && (D_hd_code_803643D7 == 0) && (D_hd_code_803643D6 == 0)) {
            func_hd_code_8024A92C(sp6C = func_hd_code_802C1B9C());
        }
    }
    if ((D_hd_code_80364AC1 != 0) && (D_hd_code_802E8BD0 == 0)) {
        func_hd_code_802D291C();
        if ((g_currentLevel == LEVEL_SHUTTLE_CLEAR) && (D_hd_code_8036BB1C == 1) && ((u32) g_frameCount >= 0x33U) && ((0 != 0) || (g_currentGameState & 0x1801)) && (areWeFading() == 0)) {
            fadeToFast(0x2000);
        }
    }
    func_hd_code_8029DDC8();
    if (D_hd_code_802E8BD0 == 0) {
        D_hd_code_803ED40C = 0;
        D_hd_code_803F7806 = func_hd_code_802C1AA0();
        func_hd_code_802BC5E0();
        func_hd_code_8024B5E8();
        func_hd_code_8028F794(D_hd_code_80364456);
        func_hd_code_80291FAC(D_hd_code_80364456);
        func_hd_code_802688C4(g_currentLevel);
        if (!(g_currentGameState & 0x1801)) {
            func_hd_code_8026FEC4();
        }
        func_hd_code_80281CE4();
        if (g_currentGameState & 0x104) {
            func_hd_code_80297804(D_hd_code_803643E0, D_hd_code_803643E4, D_hd_code_803643E8);
        }
        func_hd_code_8029E0AC();
        if (((g_currentGameState & 0x104)) && (D_hd_code_80364AA8 & 1)) {
            func_hd_code_8024A348();
            func_hd_code_8024ADD8();
        }
        if ((D_hd_code_80364AA8 != 1) && (D_hd_code_80367C00 != 0) && ((u32) (sc.unk803156C0 - D_hd_code_80364A58) >= 0x5BU)) {
            D_hd_code_80367C00 = 0;
            func_hd_code_802794A4();
        }
    }
    if ((D_hd_code_803643D6 == 0) && (D_hd_code_803643D7 == 0)) {
        if ((g_currentLevel == LEVEL_SHUTTLE_CLEAR) && (D_hd_code_8036EB98 != 0)) {
            if ((LEVEL_FINISHED(LEVEL_SHUTTLE_CLEAR)) == 0) {
                goto block_275;
            }
        }
    } else {
      // TODO: block label
block_275:
        if ((D_hd_code_80364AA8 == 1) && (D_hd_code_80364A5C == 0)) {
            rmonPrintf("TIME IN LEVEL=%d\n", D_hd_code_80364A5C = sc.unk803156C0 - D_hd_code_80364A58);
        }
    }
    LoadLevelTodo40(D_hd_code_80358074);
    if (g_currentGameState & 0x1801) {
        func_hd_code_802A45D4(2);
    }
    if ((D_hd_code_8036BB18 == 0x58) && (D_hd_code_8036BB1C != 8) && (D_hd_code_80364410 == 0)) {
        if (D_hd_code_80364A85 == 0) {
            func_hd_code_802A45D4(0xA);
        }
    } else if (D_hd_code_80364A85 != 0) {
        func_hd_code_802A45D4(0xA);
    }
    func_hd_code_802BD1F8(&D_hd_code_803156F8[D_hd_code_8035805C].unkA580,
                          &D_hd_code_803156F8[D_hd_code_8035805C].unkA918,
                          D_hd_code_803156F8[D_hd_code_8035805C].unkACB0,
                          &D_hd_code_803156F8[D_hd_code_8035805C].unk1B650,
                          &D_hd_code_803156F8[D_hd_code_8035805C].unk00000,
                          &D_hd_code_803156F8[D_hd_code_8035805C].unkE00,
                          &D_hd_code_803156F8[D_hd_code_8035805C].unk21410,
                          &D_hd_code_803156F8[D_hd_code_8035805C].unk21478);
    if (g_currentGameState == 4) {
        func_hd_code_80295C70(g_currentLevel, D_hd_code_803643E0, D_hd_code_803643E8);
    }
    func_hd_code_802A4CDC(D_hd_code_80358030[D_hd_code_8035805C],
                          D_hd_code_80358038[D_hd_code_8035805C],
                          D_hd_code_80358040[D_hd_code_8035805C],
                          D_hd_code_80358048[D_hd_code_8035805C],
                          &D_hd_code_803156F8[D_hd_code_8035805C].unkA4E0);
    func_hd_code_8027E9B8(D_hd_code_8035805C);
    if ((D_hd_code_802E8BD0 == 0) || ((D_hd_code_803643DB != 0) && (D_hd_code_803643D6 != 0)) || (D_hd_code_8036EB99 != 0)) {
        func_hd_code_802C0574();
        func_hd_code_802BCA2C();
    }
    if (D_hd_code_802E8BD0 == 0) {
        func_hd_code_8028DF14(D_hd_code_80364456);
        func_hd_code_802906C0(D_hd_code_80364456);
        func_hd_code_80292830();
        func_hd_code_8028C874(D_hd_code_80364456);
    }
    if (D_hd_code_80364AA8 != 1) {
        if (g_currentGameState & 0x40) {
            func_hd_code_8026420C();
        }
        if (g_currentGameState & 0x04002104) {
            func_hd_code_80262BF4();
        }
    } else if (D_hd_code_803BE738 != 0) {
        if ((LEVEL_FINISHED(g_currentLevel)) == 0) {
            D_hd_code_803643D9 = 1;
        } else if (areWeFading() == 0) {
            D_hd_code_803643DA = 1;
            sndPlaySfx(D_hd_code_80367738, 0x2BU, NULL);
            if ((g_currentGameState == 0x40)) {
                fadeToFast(0x40);
            } else {
                fadeToFast(0x08000000);
            }
        }
    }
    func_hd_code_802A64A4();
    func_hd_code_802886A0();
    if (D_hd_code_802E8BD0 == 0) {
        func_hd_code_802CF1A4();
    }
    func_hd_code_80279514(D_hd_code_803643E0, D_hd_code_803643E4, D_hd_code_803643E8, D_hd_code_803643F8, D_hd_code_803643FC, D_hd_code_80364400);
    func_hd_code_80277620(g_frameCount);
    func_hd_code_8027D810(g_currentLevel);
    func_hd_code_802C2054();
    if (D_hd_code_802E8BD0 == 0) {
        func_hd_code_8026A9B4();
    }
    entry = func_hd_code_8024C414(&D_hd_code_803156F8[D_hd_code_8035805C], &D_hd_code_80358078);
    if (g_currentGameState & 0x04002444 && D_hd_code_80364AA8 != 1) {
        entry = func_hd_code_802639B4(entry, &D_hd_code_803156F8[D_hd_code_8035805C], &D_hd_code_80358078);
    }
    if ((g_currentGameState & 0x100000000002)) {
        if((g_currentGameState == 0x2)) {
            entry = func_hd_code_8025C878(entry, &D_hd_code_803156F8[D_hd_code_8035805C], D_hd_code_8035805C, &D_hd_code_80358078);
        }
        if ((D_hd_code_802E8BF0 != 0) || (D_hd_code_80366A12 == 3) || (D_hd_code_802E8BEC >= 9)) {
            if (((D_hd_code_8036BB1C == 1) || (D_hd_code_8036BB1C == 8) || (D_hd_code_802E8BEC >= 9)) && ((D_hd_code_802E8BF0 == 0) || (g_frameCount <= D_hd_code_80366A04))) {
                if ((D_hd_code_8039CAA0 + 0x14) >= 0x100) {
                    D_hd_code_8039CAA0 = 0xFF;
                } else {
                    D_hd_code_8039CAA0 += 0x14;
                }
            } else if ((D_hd_code_8039CAA0 - 0x14) < 0) {
                D_hd_code_8039CAA0 = 0;
            } else {
                D_hd_code_8039CAA0 -= 0x14;
            }
        }
        if ((D_hd_code_8039CAA0 != 0) && (D_hd_code_802E8BEC != 0) && (D_hd_code_8039CAA2 != 0)) {
            entry = func_hd_code_80295EFC(&D_hd_code_803156F8[D_hd_code_8035805C],
                                         entry,
                                         (D_hd_code_8039CAA0 / 2) - 0x67,
                                         0x55 - ((g_currentGameState == 0x100000000000) << 5),
                                         (s32) D_hd_code_8039CAA0);
        }
        if ((D_hd_code_802E8BEC == 0) && (D_hd_code_80366A12 == 3) && (g_currentGameState == 2)) {
            entry = func_hd_code_8029A1A8(&D_hd_code_803156F8, entry);
        }
        if (g_currentGameState == 2 || g_currentLevel == LEVEL_CMO_INTRO) {
            func_hd_code_8025C5D0();
        }
    }
    if ((g_currentGameState & 0x1801)) {
        if ((g_frameCount == 0x96) && (g_currentLevel != 0x32)) {
            yoshiShow(0x8040);
        }
        if (players[playerNumber].unk91 == 0 && (g_frameCount == 0xA)) {
            yoshiShow(0x803F);
        }
    }
    entry = func_hd_code_8024C404(entry, &D_hd_code_803156F8[D_hd_code_8035805C], &D_hd_code_80358078);
    if ((g_currentGameState & 0x440) && ((u32) (sc.retraceCount - D_hd_code_80364A54) >= 0xA1U) && ((u8) D_hd_code_80364A50 == 0)) {
        D_hd_code_80364A50 = 1;
        if (D_hd_code_8036BB1C == 1) {
            if (((LEVEL_FINISHED(g_currentLevel)) == 0) || (D_hd_code_80364AA8 == 1)) {
                yoshiShow(
                     D_hd_code_802F4870[yoshiFFS(D_hd_code_80364AA8)] | 0x8000
                );
            }
        }
    }
    if (g_currentGameState == 8 && (areWeFading() == 0) && ((alCSPGetState(g_musicPlayer) == 0) || ((u32) (sc.retraceCount - D_hd_code_80367740) >= 0x12DU))) {
        fadeToFast(0x08000000);
    }
    if ((g_currentLevel == LEVEL_END_SEQUENCE) && (D_hd_code_8036BB1C == 1)) {
        entry = func_hd_code_8029A518(&D_hd_code_803156F8[D_hd_code_8035805C], entry);
    }
    drawTextOrtho(&entry, &D_hd_code_803156F8[D_hd_code_8035805C]);
    if (g_currentGameState != 2) {
        entry = func_hd_code_80274BF0(&D_hd_code_803156F8[D_hd_code_8035805C], entry);
    }
    if (g_currentGameState == 0x2000000000000000) {
        if ((g_currentButtons & R_TRIG) && !(g_previousButtons & R_TRIG)) {
            if ((D_hd_code_8036BB18 < 0x6B) && (D_hd_code_8036BB1C != 8) && (D_hd_code_8036BB1C != 1)) {
                yoshiShow((D_hd_code_8036BB18 + 1) | 0x8000);
                sndPlaySfx(D_hd_code_80367738, 0x1DU, NULL);
            } else {
                sndPlaySfx(D_hd_code_80367738, 0xD0U, NULL);
            }
        }
        if ((g_currentButtons & Z_TRIG) && !(g_previousButtons & Z_TRIG)) {
            if ((D_hd_code_8036BB18 >= 0x5F) && (D_hd_code_8036BB1C != 8) && (D_hd_code_8036BB1C != 1)) {
                yoshiShow((D_hd_code_8036BB18 - 1) | 0x8000);
                sndPlaySfx(D_hd_code_80367738, 0x1DU, NULL);
            } else {
                sndPlaySfx(D_hd_code_80367738, 0xD0U, NULL);
            }
        }
    }
    if ((((g_currentButtons & START_BUTTON) && !(g_previousButtons & START_BUTTON)) ||
         ((g_currentButtons & A_BUTTON) && !(g_previousButtons & A_BUTTON))) &&
        (areWeFading() == 0) &&
        (D_hd_code_8036BB1A == -1) &&
        (g_nextGameState == 0) && (D_hd_code_803643D9 == 0) && (D_hd_code_803643DA == 0) && (D_hd_code_8036BB18 != 0)) {
        if ((func_hd_code_8026B10C() & 0x8000) && (func_hd_code_8026B10C() & 1)) {
            func_hd_code_8026B10C();
        }
        switch(g_currentGameState) {
            case 0x800:
            case 0x1000:
            case 0x1:
                if (g_currentLevel != 0x32 || D_hd_code_80364A88 == 0x4000) {
                    g_nextGameState = 0x2000;
                    sndPlaySfx(D_hd_code_80367738, 0x1EU, NULL);
                }
                break;
            case 0x400:
            case 0x40:
                if ((LEVEL_FINISHED(g_currentLevel)) && (D_hd_code_80364AA8 != 1)) {
                    g_nextGameState = 0x08000000;
                    sndPlaySfx(D_hd_code_80367738, 0x1EU, NULL);
                } else if (D_hd_code_8036BB1C == 1) {
                    yoshiShow(D_hd_code_802F4870[yoshiFFS(D_hd_code_80364AA8)] | 0x8000);
                }
                break;
            case 0x2:
                if (D_hd_code_80366A18 != 0) {
                    sndPlaySfx(D_hd_code_80367738, 0x1EU, NULL);
                    sndSetSfxSlotVolume(0, 0);
                    sndSetSfxSlotVolume(5, 0);
                    fadeToFast(0x20000000000000);
                }
                break;
            case 0x100000000000:
                if (D_hd_code_803A6B04 != 0) {
                    g_nextGameState = 0x400000000000;
                }
                break;
            case 0x100:
            case 0x4:
                if ((g_currentButtons & START_BUTTON) && (D_hd_code_802E8BD0 == 0)) {
                    if ((LEVEL_FINISHED(g_currentLevel)) && (D_hd_code_80364AA8 == 1)) {
                        D_hd_code_802F5804[2].unk0 |= 1;
                        D_hd_code_802F5804[2].unk18 = 7;
                    } else {
                        D_hd_code_802F5804[2].unk0 &= ~1;
                        D_hd_code_802F5804[2].unk18 = 8;
                    }
                    yoshiShow(0x8000);
                }
                break;
        }
    }
    entry = func_hd_code_8026BBD0(entry, &D_hd_code_803156F8[D_hd_code_8035805C], &D_hd_code_80358078);
    if ((D_hd_code_8036BB16 != 0) && (D_hd_code_803643D9 == 0) && (D_hd_code_803643DA == 0)) {
        func_hd_code_8024BDA4(&D_hd_code_8036BB16);
    }
    if (g_currentGameState & 0x444 && D_hd_code_8036BB1A == -1 && D_hd_code_80367BC8 == 0 && (((D_hd_code_8036BB18 != -1)?(D_hd_code_802F8BDC[D_hd_code_8036BB18].unk8 & 0x01000000):0) == 0)) {
            if (g_currentGameState & 0x440) {
                sp4A = 0xB4;
            } else {
                sp4A = 0xFF;
            }
            D_hd_code_80367BD0.unk6 = (D_hd_code_80367BD0.unk6 < sp4A) ? ((sp4A < D_hd_code_80367BD0.unk6 + 0x10) ? sp4A : (D_hd_code_80367BD0.unk6 + 0x10)) : sp4A;

    } else {
        D_hd_code_80367BD0.unk6 = (D_hd_code_80367BD0.unk6 >= 0) ? (((D_hd_code_80367BD0.unk6 - 0x10) < 0) ? (0) : (D_hd_code_80367BD0.unk6 - 0x10)) : (0);
    }
    if (g_currentGameState == 2) {
        entry = func_hd_code_80274BF0(&D_hd_code_803156F8[D_hd_code_8035805C], entry);
    }
    func_hd_code_802559F8(entry, &D_hd_code_80358078);
    for(sp68 = 0; sp68 < nextdma; sp68++) {
        osRecvMesg(&D_hd_code_80315180, NULL, OS_MESG_BLOCK);
    }

    if (!MQ_IS_EMPTY(&D_hd_code_80315180)) {
        rmonPrintf(ASSERT_MESSAGE, "MQ_IS_EMPTY(&textureDmaMessageQ)", "hd.c", 0x5E5);
    }
    if (!(nextdma - no_palette_dmas < 0x90)) {
        rmonPrintf(ASSERT_MESSAGE, "nextdma-no_palette_dmas<NUM_TEXTURE_DMAS", "hd.c", 0x5E6);
    }
    for(sp68 = 0; sp68 < (nextdma - no_palette_dmas); sp68++) {
        func_hd_code_802A57AC();
    }

    D_hd_code_803649E0 = (D_hd_code_803649D8 % 0x28) - 0x14;
    D_hd_code_803649E2 = ((D_hd_code_803649D8 / 0x64) % 0x28) - 0x14;
    D_hd_code_803649E4 = ((D_hd_code_803649D8 / 0x2710) % 0x28) - 0x14;
    D_hd_code_803643D8 = D_hd_code_803643D6;
    if ((D_hd_code_803643D7 == 0) && (D_hd_code_803643D6 == 0)) {
        if (D_hd_code_803643DA != 0) {
            if (D_hd_code_803643D9 != 0) {
                rmonPrintf(ASSERT_MESSAGE, "!cmo_hit_request", "hd.c", 0x5F9);
            }
            D_hd_code_803643D7 = 1;
        } else if (D_hd_code_803643D9 != 0) {
            D_hd_code_803643D6 = 1;
        }
        D_hd_code_803643DA = 0;
        D_hd_code_803643D9 = 0;
    }
}

void func_hd_code_8024A348(void) {
    if (D_hd_code_80364A40 != 0) {
        if (((D_hd_code_80364A3D + 1) != D_hd_code_80364A3C) && ((D_hd_code_80364A3D != 4) || (D_hd_code_80364A3C != 0))) {
            D_hd_code_80364A00[D_hd_code_80364A3D].unk0 = D_hd_code_80364A40;
            D_hd_code_80364A00[D_hd_code_80364A3D].unk9 = 0x1E;
            if ((D_hd_code_8036443E >= 0xE00) || (D_hd_code_8036443E < 0x200)) {
                if (D_hd_code_80364AA8 == 8) {
                    D_hd_code_80364A00[D_hd_code_80364A3D].unk4 = 0x1E;
                    D_hd_code_80364A00[D_hd_code_80364A3D].unk6 = 0x3C;
                    D_hd_code_80364A00[D_hd_code_80364A3D].unk8 = 1;
                } else {
                    D_hd_code_80364A00[D_hd_code_80364A3D].unk4 = 0x1E;
                    D_hd_code_80364A00[D_hd_code_80364A3D].unk6 = 0x1E;
                    D_hd_code_80364A00[D_hd_code_80364A3D].unk8 = 1;
                }
            }
            if ((D_hd_code_8036443E >= 0x200) && (D_hd_code_8036443E < 0x600)) {
                D_hd_code_80364A00[D_hd_code_80364A3D].unk4 = 0x1E;
                D_hd_code_80364A00[D_hd_code_80364A3D].unk6 = 0xA0;
                D_hd_code_80364A00[D_hd_code_80364A3D].unk8 = 1;
            }
            if ((D_hd_code_8036443E >= 0x600) && (D_hd_code_8036443E < 0xA00)) {
                D_hd_code_80364A00[D_hd_code_80364A3D].unk4 = 0xFA;
                D_hd_code_80364A00[D_hd_code_80364A3D].unk6 = 0xA0;
                D_hd_code_80364A00[D_hd_code_80364A3D].unk8 = 0;
            }
            if ((D_hd_code_8036443E >= 0xA00) && (D_hd_code_8036443E < 0xE00)) {
                D_hd_code_80364A00[D_hd_code_80364A3D].unk4 = 0xFA;
                D_hd_code_80364A00[D_hd_code_80364A3D].unk6 = 0x25;
                D_hd_code_80364A00[D_hd_code_80364A3D].unk8 = 0;
            }

            if(++D_hd_code_80364A3D == 5) {
                D_hd_code_80364A3D = 0;
            }
        }
        D_hd_code_80364A40 = 0;
    }
    if (D_hd_code_80364A3C != D_hd_code_80364A3D) {
        D_hd_code_80364A44 = D_hd_code_80364A00[D_hd_code_80364A3C].unk0;
        D_hd_code_80364A4A = D_hd_code_80364A00[D_hd_code_80364A3C].unk4;
        D_hd_code_80364A4C = D_hd_code_80364A00[D_hd_code_80364A3C].unk6;
        D_hd_code_80364A4E = D_hd_code_80364A00[D_hd_code_80364A3C].unk8;
        if ((s32) D_hd_code_80364A00[D_hd_code_80364A3C].unk9 >= 16) {
            D_hd_code_80364A48 = (u32) (255.0f - (((f32) (D_hd_code_80364A00[D_hd_code_80364A3C].unk9 - 0xF) / 15.0f) * 255.0f));
        } else {
            D_hd_code_80364A48 = (u32) (((f32) D_hd_code_80364A00[D_hd_code_80364A3C].unk9 / 15.0f) * 255.0f);
        }
        if (D_hd_code_80364A00[D_hd_code_80364A3C].unk9-- == 0) {
            if (++D_hd_code_80364A3C == 5) {
                D_hd_code_80364A3C = 0;
            }
        }
    } else {
        D_hd_code_80364A44 = 0;
    }
}

void func_hd_code_8024A92C(u32 arg0) {
    u32 sp2C;
    u32 sp28;

    switch (g_currentLevel) {
    case 0x1D:
        sp2C = 0x55F0;
        sp28 = 0x36B0;
        break;
    case 0xC:
        sp2C = 0x6590;
        sp28 = 0x4E20;
        break;
    case 0x3A:
        sp2C = 0x8CA0;
        sp28 = 0x7530;
        break;
    case 0x12:
        sp2C = 0x8CA0;
        sp28 = 0x6D60;
        break;
    case 0x10:
        sp2C = 0x80E8;
        sp28 = 0x59D8;
        break;
    case 0xF:
        sp2C = 0x5DC0;
        sp28 = 0x4650;
        break;
    case 0xD:
        sp2C = 0xD6D8;
        sp28 = 0x88B8;
        break;
    case 0xE:
        if (D_hd_code_803EF6E4 >= 0x2B5C1) {
            sp2C = 0x61A8;
            sp28 = 0x4E20;
        } else if (D_hd_code_803EF6E4 >= 0x13881) {
            sp2C = 0x55F0;
            sp28 = 0x445C;
        } else {
            sp2C = 0x36B0;
            sp28 = 0x1F40;
        }
        break;
    case 0x9:
        if (D_hd_code_803EF6E4 >= 0x187E1) {
            sp2C = 0x8CA0;
            sp28 = 0x4650;
        } else {
            sp2C = 0x2EE0;
            sp28 = 0x1770;
        }
        break;
    default:
        sp2C = 0x2EE0;
        sp28 = 0x1770;
        break;
    }
    D_hd_code_803153F0 = D_hd_code_80364A6F;
    if (arg0 < sp2C) {
        if (arg0 < sp28) {
            D_hd_code_80364A6F = 2;
        } else {
            D_hd_code_80364A6F = 1;
        }
    } else {
        D_hd_code_80364A6F = 0;
    }
    if (D_hd_code_80364A6F != D_hd_code_803153F0) {
        if ((D_hd_code_803153F0 == 0) && (func_hd_code_8026A610(D_hd_code_803EF6DC, D_hd_code_803EF6E4, D_hd_code_803643E0, D_hd_code_803643E8) >= 0x4E21)) {
            func_hd_code_80277EDC(1, 1, 7, 0x6C);
            rmonPrintf("TOO FAR AWAY FROM CMO\n");
        }
        switch (D_hd_code_80364A6F) {
          case 1:
            switch (D_hd_code_803153F0) {
            case 0:
                func_hd_code_80260DFC();
                /* fallthrough */
            case 2:
                sndDeactivate(D_hd_code_803156E8);
                break;
            }
            break;
          case 2:
            switch (D_hd_code_803153F0) {
            case 0:
                func_hd_code_80260DFC();
                /* fallthrough */
            case 1:
                sndPlaySfx(D_hd_code_80367738, 0x26U, &D_hd_code_803156E8);
                break;
            }
            break;
          case 0:
            sndDeactivate(D_hd_code_803156E8);
            if ((D_hd_code_802E8F94[g_currentLevel].unk0 != 0x80) || (func_hd_code_802C1AA0() == 0)) {
                rmonPrintf("popTuneImmediate();\n");
                func_hd_code_80261040();
            } else {
                rmonPrintf("WILL THIS FIX IT!!?\n");
            }
            if (D_hd_code_803153F0 == 2) {
                sndPlaySfx(D_hd_code_80367738, 0x68U, NULL);
            }
            break;
        }
    }
    switch (D_hd_code_80364A6F) {
    case 1:
        if ((func_hd_code_8026AD30(0x49) == 0) && (D_hd_code_8036BB18 != 3)) {
            yoshiShow(0x8003);
            return;
        }
        return;
    case 2:
        if (D_hd_code_8036BB18 != 2) {
            yoshiShow(0x8002);
            return;
        }
        break;
    case 0:
        if (((D_hd_code_8036BB1C == 2) || (D_hd_code_8036BB1C == 4)) && (func_hd_code_8026B10C() == 0) && ((D_hd_code_8036BB18 == 3) || (D_hd_code_8036BB18 == 2) || (D_hd_code_8036BB18 == 0x49))) {
            yoshiShow(0x4000);
        }
        break;
    }
}

void func_hd_code_8024ADD8(void) {
  u32 sp4;

  sp4 = (u32)D_hd_code_803649F0 - (u32)D_hd_code_803649F4;
  D_hd_code_803649F4 = sp4 / 10U + (u32)D_hd_code_803649F4;
  D_hd_code_803649F4 = (u32)D_hd_code_803649F4 + 0xA;
  if ((u32) D_hd_code_803649F0 < (u32)D_hd_code_803649F4) {
    D_hd_code_803649F4 = D_hd_code_803649F0;
  }
}

void func_hd_code_8024AE2C(void) {
    UnknownData8024C414* temp_t4;

    if ((D_hd_code_803649ED != 0) && (D_hd_code_803649ED != 0xFF)) {
        if (func_hd_code_802AB878(D_hd_code_803649ED) == 0) {
            func_hd_code_802AB478(D_hd_code_803649ED);
            func_hd_code_8028F6B4(D_hd_code_803649ED);
            func_hd_code_80291ED8(D_hd_code_803649ED);
            func_hd_code_8028B720();
            func_hd_code_802794E4();
            if (func_hd_code_8024AFA8(D_hd_code_803649ED) != 0) {
                D_hd_code_80364456 = D_hd_code_803649ED;
                func_hd_code_802AE860();
                if ((D_hd_code_802E8BD0 == 0) && ((u32) g_frameCount >= 0xBU) && ((D_hd_code_80364456 == 8) || (D_hd_code_80364456 == 0xF) || (D_hd_code_80364456 == 0xD) || (D_hd_code_80364456 == 0xE))) {
                    func_hd_code_8026AD30(0x4A);
                }
            }
            players[playerNumber].unk10 |= 1 << D_hd_code_80364456;
            D_hd_code_803649E8 = 1;
            D_hd_code_803649EC = 1;
            D_hd_code_803649EE = 1;
            return;
        }
        if (sndGetPlayingState(D_hd_code_803156F0) == 0) {
            sndPlaySfx(D_hd_code_80367738, 0x2B, &D_hd_code_803156F0);
        }
    }
}

u8 func_hd_code_8024AFA8(s32 arg0) {
  u8 sp27;

  sp27 = 1;
  switch (arg0) {
    case 1:
      func_hd_code_802AFFD4();
      break;
    case 2:
      func_hd_code_802B1228();
      break;
    case 3:
      func_hd_code_802B2D7C();
      break;
    case 4: // BULLDOZER
      func_hd_code_802B448C();
      break;
    case 5:
      func_hd_code_802B5CD8();
      break;
    case 6:
      func_hd_code_802BB054();
      break;
    case 7: // TRAIN
      func_hd_code_802BBDC8();
      break;
    case 8: // AMERICAN MUSCLE CAR - BONUS VEHICLE
      func_hd_code_802B76AC();
      break;
    case 9:
      func_hd_code_802C5714();
      break;
    case 10:
      func_hd_code_802C9F54();
      break;
    case 11:
    case 17:
    case 18:
      func_hd_code_802C8AB0();
      break;
    case 13:
      func_hd_code_802CBA94();
      break;
    case 14:
      func_hd_code_802CCC8C();
      break;
    case 15:
      func_hd_code_802CFA0C();
      break;
    case 16:
      func_hd_code_802D0C68();
      break;
    default:
      sp27 = 0;
      break;
  }
  if ((sp27 != 0) && ((g_currentGameState & 0x104))) {
    func_hd_code_8025BBE8(players[playerNumber].unkF0 & (1 << arg0) ? 0x80 : 0x40, 0, 0);
  }
  if (sp27 != 0) {
    rmonPrintf("changing to digger %d\n", arg0);
  }
  return sp27;
}

void func_hd_code_8024B188(void) {
    u8 sp27;
    u8 sp26;
    u8 var_s0;

    sp27 = 0;
    sp26 = 0;
    sp27 = func_hd_code_8024B4B8();
    if (sp27 == 1) {
        sp26 = func_hd_code_802AE888(D_hd_code_802E8BFC[D_hd_code_80364456 - 1]);
    }
    if (sp26 != 0) {
        D_hd_code_803649E8 = 0;
        func_hd_code_802794E4();
        func_hd_code_8028F93C();
        func_hd_code_80292084();
        func_hd_code_8028B720();
        switch (D_hd_code_80364456) {
        case 4:
            func_hd_code_802B4658();
            break;
        case 3:
            func_hd_code_802B2F54();
            break;
        case 5:
            func_hd_code_802B5F60();
            break;
        case 2:
            func_hd_code_802B11B8();
            break;
        case 1:
            func_hd_code_802B0254();
            break;
        case 7:
            func_hd_code_802BBE2C();
            break;
        case 8:
            func_hd_code_802B7754();
            break;
        case 9:
            func_hd_code_802C5688();
            break;
        case 10:
            func_hd_code_802CA1AC();
            break;
        case 11:
        case 17:
        case 18:
            func_hd_code_802C8B0C(D_hd_code_80364456);
            break;
        case 13:
            func_hd_code_802CBBBC();
            break;
        case 14:
            func_hd_code_802CCD34();
            break;
        case 6:
            func_hd_code_802BB1A0();
            if (func_hd_code_8024B418(4) != 0) {
                func_hd_code_802B4658();
            }
            if (func_hd_code_8024B418(0xD) != 0) {
                func_hd_code_802CBBBC();
            }
            break;
        case 15:
            func_hd_code_802CFAB4();
            break;
        case 16:
            func_hd_code_802D0BF8();
            break;
        }
        D_hd_code_80364456 = 0;
        if ((g_currentGameState & 0x104)) {
            func_hd_code_8025BBE8(players[playerNumber].unkF0 & 1 ? 0x80 : 0x40, 0, 0);
        }
    }
    if (((sp27 == 0) || ((sp27 != 2) && (sp26 == 0))) && (sndGetPlayingState(D_hd_code_803156EC) == 0)) {
        sndPlaySfx(D_hd_code_80367738, 0x2BU, &D_hd_code_803156EC);
    }
}

s32 func_hd_code_8024B418(u8 arg0) {
  u32 sp4;
  sp4 = 0;
  while(g_vehiclesEnd != &g_vehicles[sp4]) {
    if (g_vehicles[sp4].unk5C == arg0) {
      return 1;
    }
    sp4++;
  }
  return 0;
}

u8 func_hd_code_8024B4B8(void) {
  switch (D_hd_code_80364456) {
    case 4:
      return func_hd_code_802B45FC();
    case 3:
      return func_hd_code_802B2EF8();
    case 5:
      return func_hd_code_802B5F04();
    case 2:
      return func_hd_code_802B1150();
    case 1:
      return func_hd_code_802B01DC();
    case 6:
      return func_hd_code_802BB170();
    case 7:
      return func_hd_code_802BBE10();
    case 8:
      return func_hd_code_802B76F8();
    case 9:
      return func_hd_code_802C5508();
    case 10:
      return func_hd_code_802CA140();
    case 11:
    case 17:
    case 18:
      return func_hd_code_802C8AF0();
    case 13:
      return func_hd_code_802CBB60();
    case 14:
      return func_hd_code_802CCCD8();
    case 15:
      return func_hd_code_802CFA58();
    case 16:
      return func_hd_code_802D0B90();
  }
}

void func_hd_code_8024B5E8() {
  D_hd_code_803ED3F5 = 1;
  func_hd_code_802AB670(D_hd_code_80364456);
}

void func_hd_code_8024B618(void) {

    s32 sp1C;
    s32 sp18;

    sp1C = 0;
    if (g_vehicles != g_vehiclesEnd) {
        do {
            if (g_vehicles[sp1C].unk70 != 0) {
                sp18 = g_vehicles[sp1C].unk5C;
                if ((sp18 != D_hd_code_80364456) && (sp18 != 0xFF) && (sp18 != 0xFE) && (sp18 != 0)) {
                    switch (sp18) {
                    case 5:
                        func_hd_code_802B5FAC();
                        break;
                    case 1:
                        func_hd_code_802B02A0();
                        break;
                    case 4:
                        func_hd_code_802B46C4();
                        break;
                    case 8:
                        func_hd_code_802B77A0();
                        break;
                    case 13:
                        func_hd_code_802CBC08();
                        break;
                    case 14:
                        func_hd_code_802CCD80();
                        break;
                    case 15:
                        func_hd_code_802CFB00();
                        break;
                    case 9:
                        func_hd_code_802C5860();
                        break;
                    case 3:
                        func_hd_code_802B2FA0();
                        break;
                    default:
                        rmonPrintf("MOVEABLE GEOMETRY MOVE ROUTINE NOT WRITTEN YET\n");
                        break;
                    }
                }
            }
            sp1C += 1;
        } while (&g_vehicles[sp1C] != g_vehiclesEnd);
    }
}

void func_hd_code_8024B7AC(void) {
    D_hd_code_803ED3F5 = 0;
    switch (D_hd_code_80364456) {
    case 0:
        D_hd_code_803649ED = 0;
        func_hd_code_802AEEC8();
        return;
    case 1:
        func_hd_code_802B03F4();
        return;
    case 2:
        func_hd_code_802B152C();
        return;
    case 3:
        func_hd_code_802B327C();
        return;
    case 4:
        func_hd_code_802B49AC();
        return;
    case 5:
        func_hd_code_802B6294();
        return;
    case 6:
        func_hd_code_802BB274();
        return;
    case 7:
        func_hd_code_802BBEB8();
        return;
    case 8:
        func_hd_code_802B7A88();
        return;
    case 9:
        func_hd_code_802C5AFC();
        return;
    case 10:
        func_hd_code_802CA4E0();
        return;
    case 11:
    case 17:
    case 18:
        func_hd_code_802C8BB8(D_hd_code_80364456);
        return;
    case 13:
        func_hd_code_802CBEF0();
        return;
    case 14:
        func_hd_code_802CD068();
        return;
    case 15:
        func_hd_code_802CFDE8();
        return;
    case 16:
        func_hd_code_802D0F98();
        /* fallthrough */
    default:
        return;
    }
}

void func_hd_code_8024B8F4(void* arg0, void* arg1) {
  Gfx gfx[50];
  Gfx* entry;
  s32 unused;
  Vtx vertices[8];
  s32 i;

  entry = gfx;
  for(i = 0; i < 8; i++) {
    vertices[i].v.flag = 0;
    vertices[i].v.tc[0] = 0;
    vertices[i].v.tc[1] = 0;
    vertices[i].v.cn[0] = 0;
    vertices[i].v.cn[1] = 0;
    vertices[i].v.cn[2] = 0;
    vertices[i].v.cn[3] = 0;
  }

  gSPSegment(entry++, 0, 0);
  gSPSegment(entry++, 1, osVirtualToPhysical(D_hd_code_8035806C));
  gSPDisplayList(entry++, D_1000010);
  gSPMatrix(entry++, VIRTUAL_TO_PHYSICAL(arg0), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
  gSPPerspNormalize(entry++, D_hd_code_8035807C);
  gSPMatrix(entry++, VIRTUAL_TO_PHYSICAL(arg1), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
  gSPVertex(entry++, VIRTUAL_TO_PHYSICAL(vertices), 8, 0);
  gSP1Triangle(entry++, 0, 1, 4, 0);
  gSP1Triangle(entry++, 1, 4, 5, 0);
  gSP1Triangle(entry++, 0, 3, 4, 0);
  gSP1Triangle(entry++, 3, 4, 7, 0);
  gSP1Triangle(entry++, 2, 3, 7, 0);
  gSP1Triangle(entry++, 2, 6, 7, 0);
  gSP1Triangle(entry++, 1, 2, 5, 0);
  gSP1Triangle(entry++, 2, 5, 6, 0);
  gSP1Triangle(entry++, 4, 5, 6, 0);
  gSP1Triangle(entry++, 4, 6, 7, 0);
  gSP1Triangle(entry++, 0,1,2, 0);
  gSP1Triangle(entry++, 0,2,3, 0);
  gDPTileSync(entry++);
  gSPEndDisplayList(entry++);

  osWritebackDCache(gfx, (((s32) entry - (s32)gfx) >> 3) * 8);
  osWritebackDCache(arg0, 0x40);
  osWritebackDCache(arg1, 0x40);
  func_hd_code_802A467C(D_hd_code_80358074, gfx, vertices, (((s32) entry - (s32)gfx) >> 3) * 8);
}

void func_hd_code_8024BDA4(u16* arg0) {
    switch(g_currentGameState) {
        case 0x4:
        case 0x100:
            switch (*arg0) {
            case 0x1:
                if ((D_hd_code_80364456 == 6) || (D_hd_code_80364456 == 0xB) || (D_hd_code_80364456 == 0x11) || (D_hd_code_80364456 == 0x12)) {
                    D_hd_code_802F5804[0x07].unk0 = (u16) (D_hd_code_802F5804[0x07].unk0 & ~1);
                    D_hd_code_802F5804[0x07].unk18 = 8;
                } else {
                    D_hd_code_802F5804[0x07].unk0 = (u16) (D_hd_code_802F5804[0x07].unk0 | 1);
                    D_hd_code_802F5804[0x07].unk18 = 7;
                }
                yoshiShow(0x8001);
                g_nextGameState = 0x4;
                break;
            case 0x2:
                func_hd_code_80285EF4(D_hd_code_80364A58);
                break;
            case 0x7:
                func_hd_code_8028B240();
                break;
            case 0x3:
                if (D_hd_code_802E8F94[g_currentLevel].unk0 & 0x81) {
                    fadeTo(0x2000, 0.5f);
                } else {
                    fadeTo(0x20000000, 0.5f);
                }
                break;
            case 0x8:
                g_nextGameState = 0x2000000000000000;
                yoshiShow(0x805E);
                D_hd_code_80364412 = 1;
                break;
            case 0x4:
                fadeTo(0x4000, 0.5f);
                break;
            case 0x9:
                if ((f64) func_hd_code_80260DF0() == 1.0) {
                    D_hd_code_802F8BDC[0x0d].unk18 = 0x28;
                } else {
                    D_hd_code_802F8BDC[0x0d].unk18 = 0x27;
                }
                yoshiShow(0x800D);
                break;
            case 0x1A7:
            case 0x1A8:
                if ((((*arg0 - 0x1A7) << D_hd_code_80364456) ^ ((1 << D_hd_code_80364456) & 0x10205)) != 0) {
                    rmonPrintf("selected controller mode yes\n");
                    players[playerNumber].unkF0 = players[playerNumber].unkF0 | (1 << D_hd_code_80364456);
                    func_hd_code_8025BBE8(0x80, 0, 0);
                } else {
                    rmonPrintf("selected controller mode no\n");
                    players[playerNumber].unkF0 = (s32) (players[playerNumber].unkF0 & ~(1 << D_hd_code_80364456));
                    func_hd_code_8025BBE8(0x40, 0, 0);
                }
                break;
            case 0x11:
                D_hd_code_802F8BDC[0x06].unk8 = (s32) (D_hd_code_802F8BDC[0x06].unk8 | 0x80);
                break;
            case 0xFFFF:
                switch (D_hd_code_8036BB18) {
                case 0x1:
                case 0x6:
                    rmonPrintf("TESTING PAUSE2 %d %d %d\n", D_hd_code_802E8BD0, D_hd_code_802E8BD8, D_hd_code_802E8BD4);
                    yoshiShow(0x8000);
                    if ((D_hd_code_803643DB != 0) || (D_hd_code_80364AC1 != 0)) {
                        g_nextGameState = 0x100;
                        func_hd_code_802A45D4(0xA);
                    }
                    break;
                case 0xD:
                case 0x58:
                    rmonPrintf("TESTING PAUSE3 %d %d %d\n", D_hd_code_802E8BD0, D_hd_code_802E8BD8, D_hd_code_802E8BD4);
                    yoshiShow(0x8001);
                    break;
                }
                break;
            case 0x28:
                musicSetMasterVolume(1.0f);
                break;
            case 0x27:
                musicSetMasterVolume(0.7f);
                break;
            }
            break;
        case 0x1000000000:
            g_nextGameState = 4;
            break;
        case 0x40:
        case 0x400:
            if ((LEVEL_FINISHED(g_currentLevel)) != 0) {
                if ((*arg0 == 0x18) || (*arg0 == 0x22) || (*arg0 == 0xFFFF)) {
                    g_nextGameState = 0x08000000;
                } else {
                    g_nextGameState = 0x2000;
                }
            } else {
                if ((*arg0 == 0x18) || (*arg0 == 0x22) || (*arg0 == 0xFFFF)) {
                    g_nextGameState = 0x4000;
                } else {
                    g_nextGameState = 0x2000;
                }
            }
            break;
        case 0x2000000000000000:
            if (*arg0 == 0xFFFF) {
                rmonPrintf("TESTING PAUSE %d %d %d\n", D_hd_code_802E8BD0, D_hd_code_802E8BD8, D_hd_code_802E8BD4);
                yoshiShow(0x8001);
            }
            g_nextGameState = 4;
            break;
        default:
            rmonPrintf("Yoshi selection in illegal game mode\n");
            break;
    }

    *arg0 = 0;
}

Gfx* func_hd_code_8024C404(Gfx* arg0, struct FrameContext* arg1, s32* arg2) {
  *arg2 = 0;
  return arg0;
}

Gfx* func_hd_code_8024C414(struct FrameContext* arg0, s32* arg1) {
    Gfx* entry;
    u8 sp194[16];
    u8 sp184[16];
    s32 sp180;

    entry = &arg0->dp[0];
    gSPSegment(entry++, 0x00, 0x00000000);
    gSPSegment(entry++, 0x02, osVirtualToPhysical(arg0));
    gSPSegment(entry++, 0x01, osVirtualToPhysical(D_hd_code_8035806C));
    gSPDisplayList(entry++, D_1000038);
    gSPDisplayList(entry++, D_1000010);
    gDPPipeSync(entry++);
    gDPSetCycleType(entry++, G_CYC_FILL);
    gSPClearGeometryMode(entry++, G_ZBUFFER);
    gDPSetDepthImage(entry++, (s32) D_hd_code_80358058);
    gDPSetColorImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, (s32) D_hd_code_80358058);
    gDPSetFillColor(entry++, 0xFFFCFFFC);
    gDPFillRectangle(entry++, 0, 0, 319, 239);

    guTranslate(&arg0->modelview, 0.f, 0.f, 0.f);
    guOrtho(&arg0->mtxOrtho, 0, 319.f, 239.f, 0.0f, -20000.0f, 20000.0f, 1.0f);
    guOrtho(&arg0->mtxOrthoLarge, 0, 1279.f, 959.f, 0.0f, -20000.0f, 20000.0f, 1.0f);
    func_hd_code_802507C8(&arg0->projection2, &arg0->lookAt, &arg0->unk180);

    gDPSetColorImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, D_hd_code_80358050[D_hd_code_8035805C]);
    entry = func_hd_code_80271FD0(entry, arg0, g_currentLevel, D_hd_code_80364452, (s32) D_hd_code_80364454, &sp180);

    gDPPipeSync(entry++);
    gDPSetCycleType(entry++, G_CYC_FILL);

    switch(g_currentLevel) {
        case 0xD:
        case 0xE:
        case 0x10:
        case 0x34:
            gDPSetFillColor(entry++, 0xD55FD55F);
            break;
        case 0xF:
            gDPSetFillColor(entry++, 0x10511051);
            break;
        default:
            gDPSetFillColor(entry++, 0x00010001);
            break;
    }
    gDPPipeSync(entry++);

    gDPFillRectangle(entry++, 0, (sp180 < 1 ? 0 : (sp180 - 1)), 319, 239);
    gDPPipeSync(entry++);

    gSPLookAt(entry++, &D_2000000.lookAt);
    gSPMatrix(entry++, &D_2000000.projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(entry++, &D_2000000.projection2, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    gSPMatrix(entry++, &D_2000000.modelview, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPPerspNormalize(entry++, D_hd_code_8035807C);

    switch(g_currentGameState) {
        case 0x40:
        case 0x400:
            guPerspective(&arg0->projection, &D_hd_code_8035807C, g_levelFOV, ASPECT_RATIO, 10.0f, 20000.0f, 1.0f);
            break;
        case 0x01:
        case 0x800:
        case 0x1000:
            guPerspective(&arg0->projection, &D_hd_code_8035807C, g_levelFOV, ASPECT_RATIO, 10.0f, 10000.0f, 1.0f);
            break;
        default:
            guPerspective(&arg0->projection, &D_hd_code_8035807C, g_levelFOV, ASPECT_RATIO, 10.0f, 10000.0f, 1.0f);
            break;
    }


    gDPSetColorDither(entry++, G_CD_MAGICSQ);
    gSPClipRatio(entry++, FRUSTRATIO_3);
    func_hd_code_8027F1F8(&entry, D_hd_code_8035805C, 0);


    gSPSegment(entry++, 0x08, VIRTUAL_TO_PHYSICAL(D_hd_code_80364458));
    gSPClearGeometryMode(entry++, 0xFFFFFFFF);

    gSPDisplayList(entry++, osVirtualToPhysical(D_hd_code_80358030[D_hd_code_8035805C]));
    gSPDisplayList(entry++, (s32) D_hd_code_803BE6E0);
    gSPClearGeometryMode(entry++, 0xFFFFFFFF);
    gSPSetGeometryMode(entry++, G_ZBUFFER);
    gSPDisplayList(entry++, osVirtualToPhysical(D_hd_code_80358038[D_hd_code_8035805C]));
    gSPDisplayList(entry++, (s32) D_hd_code_803BE6E4);

    if ((D_hd_code_803643D6 == 0) && (D_hd_code_803643D7 == 0)) {
        gSPClearGeometryMode(entry++, 0xFFFFFFFF);
        gSPSetGeometryMode(entry++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LOD | G_SHADING_SMOOTH);

        gSPDisplayList(entry++, &D_2000000.unk21410);
        gDPPipeSync(entry++);
    }
    switch (D_hd_code_8035805C) {
    case 0:
        gSPSegment(entry++, 0x0A, osVirtualToPhysical(D_hd_code_803F7820));
        break;
    case 1:
        gSPSegment(entry++, 0x0A, osVirtualToPhysical(D_hd_code_803F7824));
        break;
    }
    gDPPipeSync(entry++);
    gSPSetGeometryMode(entry++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    gDPSetCombineMode(entry++, G_CC_SHADE, G_CC_SHADE);
    gSPDisplayList(entry++, &D_2000000.unkA4E0);

    if (!(g_currentGameState & 0x440)) {
        func_hd_code_8027C4C8(&entry, arg0);
    }
    func_hd_code_802502EC();
    func_hd_code_8024E4F4(&entry, arg0, 0);
    func_hd_code_80258B78(&entry, arg0);
    if ((D_hd_code_802E8BD0 == 0) && (D_hd_code_80364AA8 != 0x40) && !(g_currentGameState & 0x440) && (D_hd_code_80364A84 == 0)) {
        func_hd_code_80279EE8(&entry, arg0, D_hd_code_8035805C);
    }
    gSPClearGeometryMode(entry++, 0xFFFFFFFF);
    gSPSetGeometryMode(entry++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LOD | G_SHADING_SMOOTH);
    gSPDisplayList(entry++, &D_2000000.unkA580);

    gDPPipeSync(entry++);

    entry = func_hd_code_802CEEFC(entry, D_hd_code_8035805C, &arg0->unkA3A0, &arg0->unk11C0);
    func_hd_code_8024E4F4(&entry, arg0, 1);
    if (D_hd_code_803643DC != 0) {
        func_hd_code_8024F520(&entry, arg0);
    }
    func_hd_code_802701A8(&entry, arg0);
    func_hd_code_80281E44(&entry);
    func_hd_code_8028E9E4(&entry, arg0);
    func_hd_code_802917B0(&entry, arg0);
    func_hd_code_80292EB8(&entry, arg0);
    func_hd_code_8028CB30(&entry, arg0);
    switch (D_hd_code_8035805C) {
    case 0:
        gSPDisplayList(entry++, osVirtualToPhysical(&D_hd_code_803C5770));
        break;
    case 1:
        gSPDisplayList(entry++, osVirtualToPhysical(&D_hd_code_803C6370));
        break;
    }
    func_hd_code_80288DF0(&entry, D_hd_code_8035805C);
    if (!(g_currentGameState & 2) || D_hd_code_802E8BF0 == 0) {
        func_hd_code_8024FC2C(&entry, 0);
    }
    func_hd_code_802976E8(&entry);

    gSPClearGeometryMode(entry++, 0xFFFFFFFF);
    gSPSetGeometryMode(entry++, G_ZBUFFER);
    gSPDisplayList(entry++, osVirtualToPhysical(D_hd_code_80358040[D_hd_code_8035805C]));
    gSPDisplayList(entry++, (s32) D_hd_code_803BE6E8);
    if (!(g_currentGameState & 2) || D_hd_code_802E8BF0 == 0) {
        func_hd_code_8024FC2C(&entry, 1);
    }

    gSPClearGeometryMode(entry++, 0xFFFFFFFF);
    gSPSetGeometryMode(entry++, G_ZBUFFER);
    gSPDisplayList(entry++, osVirtualToPhysical(D_hd_code_80358048[D_hd_code_8035805C]));
    gSPDisplayList(entry++, (s32) D_hd_code_803BE6EC);

    gSPClearGeometryMode(entry++, 0xFFFFFFFF);
    gSPSetGeometryMode(entry++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LOD | G_SHADING_SMOOTH);
    gSPDisplayList(entry++, &D_2000000.unkA918);
    gDPPipeSync(entry++);

    if ((D_hd_code_803643D6 == 0) && (D_hd_code_803643D7 == 0)) {
        gSPClearGeometryMode(entry++, 0xFFFFFFFF);
        gSPSetGeometryMode(entry++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LOD | G_SHADING_SMOOTH);
        gSPDisplayList(entry++, &D_2000000.unk21478);
        gDPPipeSync(entry++);
    }
    if (( !(g_currentGameState & 2)) || (D_hd_code_802E8BF0 == 0)) {
        func_hd_code_8024FC2C(&entry, 2);
    }
    func_hd_code_80295120(&entry, arg0);
    if ((g_currentGameState & 0x2000001000003905)) {
        func_hd_code_80280F34(&entry, D_hd_code_8035805C);
    }
    func_hd_code_8027F1F8(&entry, D_hd_code_8035805C, 1);
    func_hd_code_8024E4F4(&entry, arg0, 2);
    if (D_hd_code_803643DC != 0) {
        func_hd_code_80266248(&entry, arg0);
    }
    switch (D_hd_code_8035805C) {
    case 0:
        gSPDisplayList(entry++, osVirtualToPhysical(&D_hd_code_803C6F70));
        break;
    case 1:
        gSPDisplayList(entry++, osVirtualToPhysical(&D_hd_code_803C7B70));
        break;
    }
    if (D_hd_code_803643DB != 0) {
        func_hd_code_8028273C(&entry, D_hd_code_8035805C);
    }
    if ((D_hd_code_80364A68 != 0) && (g_currentGameState & 0x104)) {
        func_hd_code_80286C60(&entry, arg0, D_hd_code_8035805C, D_hd_code_80364456);
    }
    if ((g_currentGameState & 0x200000000400220C)) {
        func_hd_code_80278324(&entry, arg0, D_hd_code_8035805C);
    }
    if ((g_currentGameState == 0x100) && (D_hd_code_803643DB != 0)) {
        func_hd_code_80276E50(&entry, arg0, D_hd_code_8035805C, D_hd_code_803643E0, D_hd_code_803643E4, D_hd_code_803643E8);
    }
    func_hd_code_80259450();
    if ((D_hd_code_80364A6A != 0) && ((g_currentGameState & 0x104))) {
        func_hd_code_80287530(&entry, arg0, D_hd_code_8035805C, D_hd_code_80364456);
    }
    if ((D_hd_code_80364A6C != 0) && ((g_currentGameState & 0x104))) {
        func_hd_code_80287C68(&entry, arg0, D_hd_code_8035805C, D_hd_code_80364456);
    }
    if ((g_currentGameState & 0x104)) {
        func_hd_code_80282224(&entry, D_hd_code_80364456);
    }
    if ((D_hd_code_80364AA8 & 1) && ((g_currentGameState & 0x0400030C))) {
        func_hd_code_8026A378(D_hd_code_803649F4, &sp194[1]);
        sp194[0] = 0x24;
        drawTextSimple(arg0, &sp194, NULL, 1, 0, 0x118, 0x12, 0x14, 0x14, 0, 0xFF, 0xFF, 0xFF, (s32) D_hd_code_80367BD0.unk6);
        if ((D_hd_code_80364A44 != 0) && (D_hd_code_802E8BD0 == 0)) {
            func_hd_code_8026A378(D_hd_code_80364A44, &sp184[1]);
            sp184[0] = 0x24;
            drawTextSimple(arg0, &sp184, NULL, 1, 0, (s32) D_hd_code_80364A4A, (s32) D_hd_code_80364A4C, 0x23, 0x23, (s32) D_hd_code_80364A4E, 0xFF, 0xFF, 0xFF, D_hd_code_80364A48);
        }
    }
   if ((g_currentGameState & 0x2000000000000104) && (!(D_hd_code_80364AA8 & 0x81) || (D_hd_code_803643DB != 0) || (D_hd_code_80364AC1 != 0))) {
        func_hd_code_80275478(arg0, &entry, g_currentGameState & 0x100 || D_hd_code_8036BB18 == 0x4D || D_hd_code_8036BB18 == 0x49);
    }
    if ((g_nextGameState == 0) && (areWeFading() == 0)) {
        if (!(g_currentGameState & 0x200000100400230C) && ((u32) ((u32) (((u32) sc.retraceCount % 50U) * 0x3C) / 60U) >= 0x15U) && (D_hd_code_8036BB1C == 1) && ((!(g_currentGameState & 2)) || ((D_hd_code_802E8BEC != 0) && ((D_hd_code_80366A12 == 3) || (D_hd_code_802E8BEC == 1)))) && ((g_currentGameState != 0x100000000000) || (D_hd_code_803A6B04 != 0)) && ((!(g_currentGameState & 0x1801)) || (players[playerNumber].unk91 != 0)) && (g_currentLevel != 0x2F)) {
            drawTextSimple(arg0, "PRESS START", NULL, 1, 0, 0x5C, 0xC4, 0x1A, 0x1A, 1, 0xFF, 0xFF, 0xFF, 0xFF);
        }
        if ((u32) ((u32) (((u32) sc.retraceCount % 40U) * 60) / 60U) >= 16U) {
            if (D_hd_code_802E8BD0 != 0) {
                if ((g_currentGameState == 0x2000000000000000) && (D_hd_code_8036BB1C == 2)) {
                    drawTextSimple(arg0, "USE Z/R TO TURN PAGES", D_hd_code_8030491C, 0, 0, 0x18, 0x14, 0xF, 0xF, 1, 0xFF, 0xFF, 0xFF, 0xFF);
                } else if ((g_currentGameState == 0x100) && (D_hd_code_8036BB18 == 0) && (D_hd_code_8036BB1C == 2) && (D_hd_code_803643DB != 0) && !(g_currentButtons & (Z_TRIG | R_TRIG))) {
                    drawTextSimple(arg0, "USE Z/R TO MOVE MAP", D_hd_code_80304938, 0, 0, 0x18, 0x14, 0xF, 0xF, 1, 0xFF, 0xFF, 0xFF, 0xFF);
                }
            } else if ((g_currentGameState == 0x100)) {
                if (D_hd_code_80364AC1 != 0) {
                    drawTextSimple(arg0, "SHUTTLE VIEW", D_hd_code_80304904, 0, 0, 0x18, 0x14, 0xF, 0xF, 1, 0xFF, 0xFF, 0xFF, 0xFF);
                } else {
                    drawTextSimple(arg0, "MISSILE VIEW", D_hd_code_80304910, 0, 0, 0x18, 0x14, 0xF, 0xF, 1, 0xFF, 0xFF, 0xFF, 0xFF);
                }
            }
        }
    }
    if (( (g_currentGameState & 0x440) || (g_currentLevel == LEVEL_SHUTTLE_ISLAND)) && (D_hd_code_8036BB1C == 1) && (areWeFading() == 0)) {
        if (( (g_currentGameState & 0x440)) && (D_hd_code_80364AA8 != 1)) {
            func_hd_code_80274B40(&entry, arg0, D_hd_code_80365580, 0x108, 0x12);
        } else {
            func_hd_code_80274B40(&entry, arg0, D_hd_code_80365580, 0x18, 0x12);
        }
    }
    if (( (g_currentGameState & 0x104)) && (D_hd_code_80364410 != 0)) {
        func_hd_code_80274B40(&entry, arg0, D_hd_code_80364A86, 0x108, 0xBE);
    }
    if (( (g_currentGameState & 0x104)) && (D_hd_code_80364AA8 == 1) && (D_hd_code_802E8BD0 == 0)) {
        func_hd_code_80285CC0();
    }
    if ((D_hd_code_803643DB != 0) && (g_currentGameState == 4)) {
        func_hd_code_80282C80(&entry, arg0, D_hd_code_803643E0, D_hd_code_803643E4, D_hd_code_803643E8, D_hd_code_803EF6DC, D_hd_code_803EF6E0, D_hd_code_803EF6E4);
    }
    if ((D_hd_code_802E8F94[g_currentLevel].unk0 & 0x81) && (g_currentGameState == 4) ) {
        if (g_currentLevel != 0x32 || (LEVEL_FINISHED(LEVEL_SHUTTLE_CLEAR))) {
            func_hd_code_8028376C(&entry, arg0, D_hd_code_8035805C, D_hd_code_803643E0, D_hd_code_803643E8, D_hd_code_803EF6DC, D_hd_code_803EF6E4);
        }
    }
    if ((D_hd_code_803643DB != 0) || (D_hd_code_80364AC1 != 0)) {
        switch(g_currentGameState) {
            case 0x4:
            case 0x100000000000:
            case 0x100:
            case 0x200:
                func_hd_code_8025E2CC(&entry, arg0, D_hd_code_8035805C);
                func_hd_code_8025E67C(&entry, arg0, D_hd_code_8035805C);
            case 0x400:
            case 0x40:
                if (((D_hd_code_803643D6 != 0) || (D_hd_code_803643D7 != 0) || (D_hd_code_803643D9 != 0) || (D_hd_code_803643DA != 0)) && ((g_currentGameState & 0x144))) {
                    func_hd_code_802A45D4(0x32);
                    if (g_currentGameState == 0x40) {
                        g_nextGameState = 1024;
                    } else {
                        g_nextGameState = 512;
                    }
                }
                break;
        }

    }
    drawTextOrtho(&entry, arg0);
    *arg1 = (s32) (((s32)entry - (s32)arg0) - 0x48B0) >> 3;
    return entry;
}


void func_hd_code_8024E4F4(Gfx** arg0, struct FrameContext *arg1, u8 arg2) {
    Gfx *entry;
    s32 sp140;
    s16 pad;
    s16 sp13C;
    s16 sp13A;
    s16 sp138;
    s16 sp136;
    s16 sp134;
    u8 sp133;
    f32 spF0[4][4];
    f32 spB0[4][4];
    s16 spAE;
    s16 spAC;
    u8 spAB;


    entry = *arg0;
    if (arg2 == 0) {
        D_hd_code_8036506C = 0;
    }
    gDPPipeSync(entry++);
    gDPSetTexturePersp(entry++, G_TP_PERSP);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    gSPClearGeometryMode(entry++, 0xFFFFFFFF);
    gSPSetGeometryMode(entry++, G_SHADE | G_CULL_BACK | G_LOD | G_SHADING_SMOOTH);
    gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(entry++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetTextureFilter(entry++, G_TF_BILERP);
    gDPSetRenderMode(entry++, G_RM_CLD_SURF, G_RM_CLD_SURF2);



    sp133 = !D_hd_code_803649E8 && (D_hd_code_803649EC || (g_currentGameState & 0x1801));
    sp140 = 0;
    while(&g_shadows.shadows[sp140] != g_shadows.firstFree) {
        if (((g_shadows.shadows[sp140].unk1022 != 0) || (sp133 != 0)) && (g_shadows.shadows[sp140].unk1022 != 0xFE) && (( g_shadows.shadows[sp140].unk1022 != 0xFF) || (D_hd_code_803EF6FF == 0)) && ((g_shadows.shadows[sp140].unk1022 == 0xFD) || (D_hd_code_80364A84 == 0) || (D_hd_code_80364AC1 == 0)) && g_shadows.shadows[sp140].unk1023 == arg2) {
                sp13C = g_shadows.shadows[sp140].unk1004 >> 5;
                sp13A = g_shadows.shadows[sp140].unk1008 >> 5;
                sp138 = g_shadows.shadows[sp140].unk100C >> 5;
                sp136 = g_shadows.shadows[sp140].unk1018; // 2D x
                sp134 = g_shadows.shadows[sp140].unk101A; // 2D y
                spAB = g_shadows.shadows[sp140].unk1022 == D_hd_code_80364456 && D_hd_code_803ED40D == 0x65;
                if (spAB) {
                    guAlignF(spB0, ((f32) D_hd_code_80364440 * 360.0) / 4096.0f, 0.0f, 1.0f, 0.0f); // Additional rotation around y axis if spAB
                }
                guAlignF(spF0, ((f32) -g_shadows.shadows[sp140].unk101E * 360.0) / 4096.0f, 0.0f, 1.0f, 0.0f); // rotation around y axis by -unk101E * D_hd_code_803087C0 degrees
                if (spAB) {
                    guMtxCatF(spB0, spF0, spF0); // Apply additional rotation
                }
                guAlignF(spB0, (f32) (((f64) (f32) g_shadows.shadows[sp140].unk101C * 360.0) / 4096.0), 1.0f, 0, 0.0f);
                guMtxCatF(spF0, spB0, spB0);
                guAlignF(spF0, (f32) (((f64) (f32) g_shadows.shadows[sp140].unk1020 * 360.0) / 4096.0), 0, 0, 1.0f);
                guMtxCatF(spB0, spF0, spF0);
                guAlignF(spB0, (f32) (((f64) (f32) g_shadows.shadows[sp140].unk101E * 360.0) / 4096.0), 0, 1.0f, 0.0f);
                guMtxCatF(spF0, spB0, spF0);
                guTranslateF(spB0, (f32) sp13C, (f32) sp13A, (f32) sp138);
                guMtxCatF(spF0, spB0, spF0);
                guMtxF2L(spF0, &arg1->unk2C0[sp140]);

                if (spAB) {
                    gDPLoadTextureBlock(entry++, OS_PHYSICAL_TO_K0(D_hd_code_802FA940), G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    spAC = spAE = 32;
                } else {
                    gDPLoadTextureBlock(entry++, K0_TO_PHYS((s32)(g_shadows.shadows[sp140].data)), G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    spAC = spAE = 64;
                }

                SET_COLOR_VERTEX(arg1->unk1580[D_hd_code_8036506C + 4], (s16) -sp136, 0, sp134, (s16) ((spAE - 1) << 5), (s16) ((spAC - 1) << 5), 0xA, 0xA, 0xA, 0x8C);
                D_hd_code_8036506C++;
                SET_COLOR_VERTEX(arg1->unk1580[D_hd_code_8036506C + 4], sp136, 0, sp134, 0, (s16) ((spAC - 1) << 5), 0xA, 0xA, 0xA, 0x8C);
                D_hd_code_8036506C++;
                SET_COLOR_VERTEX(arg1->unk1580[D_hd_code_8036506C + 4], sp136, 0, (s16) -sp134, 0, 0, 0xA, 0xA, 0xA, 0x8C);
                D_hd_code_8036506C++;
                SET_COLOR_VERTEX(arg1->unk1580[D_hd_code_8036506C + 4], (s16) -sp136, 0, (s16) -sp134, (s16) ((spAE - 1) << 5), 0, 0xA, 0xA, 0xA, 0x8C);
                D_hd_code_8036506C++;

                if ((D_hd_code_803643D6 != 0) && !(D_hd_code_80364AA8 & 0x81) && (g_shadows.shadows[sp140].unk1022 == D_hd_code_80364456)) {
                    gSPMatrix(entry++, &D_2000000.unk1540, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
                }
                gSPMatrix(entry++, &D_2000000.unk2C0[sp140], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
                gSPVertex(entry++, &D_2000000.unk1580[D_hd_code_8036506C], 4, 0);
                gSP1Triangle(entry++, 0, 1, 2, 0);
                gSP1Triangle(entry++, 0, 2, 3, 0);
                gSPPopMatrix(entry++, G_MTX_MODELVIEW);

                if ((D_hd_code_803643D6 != 0) && !(D_hd_code_80364AA8 & 0x81) && (g_shadows.shadows[sp140].unk1022 == D_hd_code_80364456)) {
                    gSPPopMatrix(entry++, G_MTX_MODELVIEW);
                }
                gDPPipeSync(entry++);

        }
        sp140++;
    }
    *arg0 = entry;
}

void func_hd_code_8024F520(Gfx** arg0, struct FrameContext* arg1) {
    Gfx* entry;

    s32 sp88;
    u8 sp87;
    s16 sp84;
    s16 sp82;
    s16 sp80;
    s16 sp7E;
    s16 sp7C;

    entry = *arg0;
    gDPPipeSync(entry++);
    gDPSetTexturePersp(entry++, G_TP_PERSP);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    gSPClearGeometryMode(entry++, 0xFFFFFFFF);
    gSPSetGeometryMode(entry++, G_SHADE | G_CULL_BACK | G_LOD | G_SHADING_SMOOTH);
    gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(entry++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetTextureFilter(entry++, G_TF_BILERP);
    gDPSetRenderMode(entry++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
    sp87 = 0;
    sp88 = 0;
    do {
        if (g_shadows.shadows[sp88].unk1022 == 0xFE) {
            sp87 = 1;
        } else {
            sp88 += 1;
        }
    } while (sp87 == 0);
    gDPSetTextureImage(entry++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, K0_TO_PHYS((s32)(g_shadows.shadows[sp88].data)));
    gDPSetTile(entry++, G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
    gDPLoadSync(entry++);
    gDPLoadBlock(entry++, G_TX_LOADTILE, 0, 0, 2047, 256);
    gDPPipeSync(entry++);
    gDPSetTile(entry++, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
    gDPSetTileSize(entry++, G_TX_RENDERTILE, 0, 0, qu102(63), qu102(63));
    sp84 = (s16) ((s32) g_shadows.shadows[sp88].unk1004 >> 5);
    sp82 = (s16) ((s32) g_shadows.shadows[sp88].unk1008 >> 5);
    sp80 = (s16) ((s32) g_shadows.shadows[sp88].unk100C >> 5);
    sp7E = g_shadows.shadows[sp88].unk1018;
    sp7C = g_shadows.shadows[sp88].unk101A;

    arg1->unk18C0[0].v.ob[0] = -sp7E;
    arg1->unk18C0[0].v.ob[1] = 0;
    arg1->unk18C0[0].v.ob[2] = sp7C;
    arg1->unk18C0[0].v.flag = 0;
    arg1->unk18C0[0].v.tc[0] = 0x7E0;
    arg1->unk18C0[0].v.tc[1] = 0x7E0;
    arg1->unk18C0[0].v.cn[0] = 0xA;
    arg1->unk18C0[0].v.cn[1] = 0xA;
    arg1->unk18C0[0].v.cn[2] = 0xA;
    arg1->unk18C0[0].v.cn[3] = 0x8C;

    arg1->unk18C0[1].v.ob[0] = sp7E;
    arg1->unk18C0[1].v.ob[1] = 0;
    arg1->unk18C0[1].v.ob[2] = sp7C;
    arg1->unk18C0[1].v.flag = 0;
    arg1->unk18C0[1].v.tc[0] = 0;
    arg1->unk18C0[1].v.tc[1] = 0x7E0;
    arg1->unk18C0[1].v.cn[0] = 0xA;
    arg1->unk18C0[1].v.cn[1] = 0xA;
    arg1->unk18C0[1].v.cn[2] = 0xA;
    arg1->unk18C0[1].v.cn[3] = 0x8C;

    arg1->unk18C0[2].v.ob[0] = sp7E;
    arg1->unk18C0[2].v.ob[1] = 0;
    arg1->unk18C0[2].v.ob[2] = -sp7C;
    arg1->unk18C0[2].v.flag = 0;
    arg1->unk18C0[2].v.tc[0] = 0;
    arg1->unk18C0[2].v.tc[1] = 0;
    arg1->unk18C0[2].v.cn[0] = 0xA;
    arg1->unk18C0[2].v.cn[1] = 0xA;
    arg1->unk18C0[2].v.cn[2] = 0xA;
    arg1->unk18C0[2].v.cn[3] = 0x8C;

    arg1->unk18C0[3].v.ob[0] = -sp7E;
    arg1->unk18C0[3].v.ob[1] = 0;
    arg1->unk18C0[3].v.ob[2] = -sp7C;
    arg1->unk18C0[3].v.flag = 0;
    arg1->unk18C0[3].v.tc[0] = 0x7E0;
    arg1->unk18C0[3].v.tc[1] = 0;
    arg1->unk18C0[3].v.cn[0] = 0xA;
    arg1->unk18C0[3].v.cn[1] = 0xA;
    arg1->unk18C0[3].v.cn[2] = 0xA;
    arg1->unk18C0[3].v.cn[3] = 0x8C;

    guTranslate(&arg1->unk240, (f32) sp84, (f32) sp82, (f32) sp80);
    guAlign(&arg1->unk280, ((f32) D_hd_code_803EF326 * 360.0) / 4096.0, 0.0f, 1.0f, 0.0f);
    gSPMatrix(entry++, &D_2000000.unk240, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPMatrix(entry++, &D_2000000.unk280, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPVertex(entry++, &D_2000000.unk18C0, 4, 0);
    gSP1Triangle(entry++, 0, 1, 2, 0);
    gSP1Triangle(entry++, 0, 2, 3, 0);
    gSPPopMatrix(entry++, G_MTX_MODELVIEW)

    *arg0 = entry;
}

void func_hd_code_8024FC2C(Gfx** arg0, u8 arg1) {
    Gfx* entry;
    s32 i;
    u8 pad;
    u8 sp5E;
    u8 sp5D;

    entry = *arg0;

    sp5D = D_hd_code_803649E8 == 0 && (D_hd_code_803649EC != 0 || g_currentGameState & 0x1801);
    i = 0;
    while (&g_vehicles[i] != g_vehiclesEnd) {
        if (((g_vehicles[i].unk5C != 0) || (sp5D != 0)) && ((g_vehicles[i].unk5C != 0xFF) || (D_hd_code_803EF6FF == 0)) && ((g_vehicles[i].unk5C == 0xFD) || (D_hd_code_80364A84 == 0) || (D_hd_code_80364AC1 == 0))) {
            gSPSegment(entry++, 0x06, osVirtualToPhysical(g_vehicles[i].unk0));
            if (((g_currentGameState & 0x1801)) && (((g_vehicles[i].unk5C == 0xFE)) || (g_vehicles[i].unk5C == 0))) {
                sp5E = D_hd_code_8035805C;
            } else {
                sp5E = D_hd_code_803156F5;
            }
            if (sp5E != 0) {
                gSPSegment(entry++, 0x07, osVirtualToPhysical(g_vehicles[i].unk4));
            } else {
                gSPSegment(entry++, 0x07, osVirtualToPhysical(g_vehicles[i].unk8));
            }
            gDPPipeSync(entry++);
            gDPSetEnvColor(entry++, 0x00, 0x00, 0x00, g_vehicles[i].unk60);
            gSPClearGeometryMode(entry++, 0xFFFFFFFF);
            if ((D_hd_code_803643D6 != 0) && !(D_hd_code_80364AA8 & 0x81) && (g_vehicles[i].unk5C == D_hd_code_80364456)) {
                gSPMatrix(entry++, &D_2000000.unk1500, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            }
            if (sp5E != 0) {
                switch (arg1) {
                case 0:
                    gSPDisplayList(entry++, osVirtualToPhysical(g_vehicles[i].unkC));
                    break;
                case 1:
                    gSPDisplayList(entry++, osVirtualToPhysical(g_vehicles[i].unk10));
                    break;
                case 2:
                    gSPDisplayList(entry++, osVirtualToPhysical(g_vehicles[i].unk14));
                    break;
                }
            } else {
                switch (arg1) {
                case 0:
                    gSPDisplayList(entry++, osVirtualToPhysical(g_vehicles[i].unk30));
                    break;
                case 1:
                    gSPDisplayList(entry++, osVirtualToPhysical(g_vehicles[i].unk34));
                    break;
                case 2:
                    gSPDisplayList(entry++, osVirtualToPhysical(g_vehicles[i].unk38));
                    break;
                }
            }
            gSPMatrix(entry++, &D_2000000.modelview, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        }
        i++;
    }
    *arg0 = entry;
}

void func_hd_code_802502EC(void) {
    f32 sp70[4][4];
    f32 sp30[4][4];
    s32 sp2C;
    s16 sp2A;
    s16 sp28;
    s16 sp26;

    if ((D_hd_code_803643D6 != 0) && !(D_hd_code_80364AA8 & 0x81)) {
        guTranslateF(sp70, (f64) -(f32) D_hd_code_803643E0 / 32.0f, (f64) -(f32) D_hd_code_803643E4 / 32.0, (f64) -(f32) D_hd_code_803643E8 / 32.0);
        guScaleF(sp30, D_hd_code_80364ABC, D_hd_code_80364ABC, D_hd_code_80364ABC);
        guMtxCatF(sp70, sp30, sp70);
        guAlignF(sp30, D_hd_code_80364AB4, 0, 1.0f, 0.0f);
        guMtxCatF(sp70, sp30, sp70);
        guTranslateF(sp30, (f64) (f32) D_hd_code_803643E0 / 32.0,(f64) (f32) D_hd_code_803643E4 / 32.0, (f64) (f32) D_hd_code_803643E8 / 32.0);
        guMtxCatF(sp70, sp30, sp70);
        guMtxF2L(sp70, &D_hd_code_803156F8[D_hd_code_8035805C].unk1500);
        sp2C = 0;
        while (g_shadows.shadows[sp2C].unk1022 != D_hd_code_80364456) {
            sp2C += 1;
        }
        sp2A = g_shadows.shadows[sp2C].unk1004 >> 5;
        sp28 = g_shadows.shadows[sp2C].unk1008 >> 5;
        sp26 = g_shadows.shadows[sp2C].unk100C >> 5;
        guTranslateF(sp70, (f32) -sp2A, (f32) -sp28, (f32) -sp26);
        guScaleF(sp30, D_hd_code_80364ABC, D_hd_code_80364ABC, D_hd_code_80364ABC);
        guMtxCatF(sp70, sp30, sp70);
        guAlignF(sp30, D_hd_code_80364AB4, 0, 1.0f, 0.0f);
        guMtxCatF(sp70, sp30, sp70);
        guTranslateF(sp30, sp2A, sp28, sp26);
        guMtxCatF(sp70, sp30, sp70);
        guMtxF2L(sp70, &D_hd_code_803156F8[D_hd_code_8035805C].unk1540);
        if (D_hd_code_80364AC0 == 0) {
            D_hd_code_80364ABC = D_hd_code_80364ABC - 0.04;
            if (D_hd_code_80364ABC < 0.0) {
                D_hd_code_80364ABC = 0.0;
            }
        }
        if ((D_hd_code_80364ABC == 0.0) && (D_hd_code_80364AC0 == 0)) {
            func_hd_code_802AC61C(D_hd_code_803643E0, D_hd_code_803643E4, D_hd_code_803643E8, 0x13, 0x61A80);
            D_hd_code_80364AC0 = 1;
        }
        D_hd_code_80364AB4 += D_hd_code_80364AB8;
        D_hd_code_80364AB8 = (f32) ((f64) D_hd_code_80364AB8 + 3.0);
    }
}

void func_hd_code_802507C8(Mtx* arg0, LookAt *arg1, void *arg2) {
    f32 spFC;
    f32 spF8;
    f32 spF4;
    f32 spF0;
    f32 spEC;
    f32 spE8;
    s32 _spE4;
    s16 spE2;
    s16 spE0;
    s16 spDE;
    s16 _spDC;
    s32 spD8;
    s32 spD4;
    f32 spD0;
    s32 spCC;
    f32 spC8;
    f32 spC4;
    s32 spC0;
    s32 spBC;
    s32 spB8;
    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    s16 sp96;
    u8 sp95;
    u8 _sp94;
    s32 sp90;
    s32 sp8C;
    u8 sp8B;
    u8 _sp8A;
    u16 _sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    s16 sp76;
    s16 _sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    s8 sp67;
    s8 _sp66;
    s16 sp64;
    s16 sp62;

    sp8B = 0;
    func_hd_code_80255190();
    if ((D_hd_code_8036B965 != 0) && (g_currentGameState & 0x600)) {
        D_hd_code_8036B965 = 0;
    }

    sp95 = D_hd_code_80364AC1 && ((g_currentGameState & 0x940) || D_hd_code_8036B965);
    if (((g_currentGameState == 8)) || ((D_hd_code_8036BB18 == 0x4B) && (D_hd_code_8036BB1C == 2) && D_hd_code_802F8BDC[D_hd_code_8036BB18].unk18 == 0x14D)) {
        if (D_hd_code_8030F668.flag1 == 0) {
            sp8B = 1;
        }
        D_hd_code_8030F668.flag1 = 1;
    } else {
        if (D_hd_code_8030F668.flag1 != 0) {
            sp8B = 1;
        }
        D_hd_code_8030F668.flag1 = 0;
    }
    if ((D_hd_code_8036BB18 == 0x49) && (D_hd_code_8036BB1C == 2) && (D_hd_code_802F8BDC[D_hd_code_8036BB18].unk18 == 0x130)) {
        if (D_hd_code_8030F668.flag3 == 0) {
            sp8B = 1;
        }
        D_hd_code_8030F668.flag3 = 1;
    } else {
        if (D_hd_code_8030F668.flag3 != 0) {
            sp8B = 1;
        }
        D_hd_code_8030F668.flag3 = 0;
    }
    if ((D_hd_code_8036BB18 == 0x4D) && (D_hd_code_8036BB1C == 2) && (D_hd_code_802F8BDC[D_hd_code_8036BB18].unk18 != 0x164)) {
        if (D_hd_code_8030F668.flag2 == 0) {
            sp8B = 1;
        }
        D_hd_code_8030F668.flag2 = 1;
    } else {
        if (D_hd_code_8030F668.flag2 != 0) {
            sp8B = 1;
        }
        D_hd_code_8030F668.flag2 = 0;
    }
    if ((D_hd_code_8036BB18 == 0x58) && (D_hd_code_8036BB1C != 8) && (D_hd_code_80364410 == 0)) {
        if (D_hd_code_80364A85 == 0) {
            D_hd_code_80364412 = sp8B = 1;
        }
        D_hd_code_80364A85 = 1;
    } else {
        if (D_hd_code_80364A85 != 0) {
            D_hd_code_80364412 = sp8B = 1;
        }
        D_hd_code_80364A85 = 0;
    }

    D_hd_code_80364412 |= sp95 || g_currentGameState == 0x100;
    D_hd_code_80364412 |= g_frameCount <= 1U;

    if ((D_hd_code_803643D6 != 0) && ((g_currentGameState & 0x100000000600))) {
        spFC = 0.2f;
        spF8 = 0.1f;
        spF4 = 0.2f;
    } else {
        if ((D_hd_code_8036BB1C == 2 && (D_hd_code_8036BB18 == 0x4D || D_hd_code_8036BB18 == 0x4B || D_hd_code_8036BB18 == 0x49)) || ((D_hd_code_803643D7 != 0) && (g_currentGameState & 0x100000000600) != 0) || g_currentGameState == 8) {
            spFC = 0.08f;
            spF8 = 0.03f;
            spF4 = 0.08f;
        }
        else if ((g_currentGameState & 0x1801) != 0) {
            spFC = 0.06f;
            spF8 = 0.03f;
            spF4 = 0.03f;
        } else {
            if (((D_hd_code_80364AA8 == 0x10) || (D_hd_code_80364AA8 == 0x40)) && (g_currentGameState == 0x40)) {
                spFC = 0.1f;
                spF8 = 0.03f;
                spF4 = 0.1f;
            }
            else if (D_hd_code_80364456 == 9) {
                spFC = 0.5f;
                spF8 = 0.06f;
                spF4 = 0.5f;
            } else {
                spFC = 0.5f;
                spF8 = 0.03f;
                spF4 = 0.5f;
            }
        }
    }
    spF0 = 0.95f;
    spEC = 0.97f;
    spE8 = 0.95f;
    if ( (g_currentGameState == 0x40) && (g_currentLevel == LEVEL_LIZARD_ISLAND)) {
        spFC = 1.0f;
        spF8 = 1.0f;
        spF4 = 1.0f;
        spF0 = 1.0f;
        spEC = 1.0f;
        spE8 = 1.0f;
    }

    switch(g_currentGameState) {

        case 0x100:
        case 0x200:
        case 0x400:
            D_hd_code_8036509E = D_hd_code_80364AC1 != 0 ? 0xFD : 0xFF;
            break;
        case 0x1:
        case 0x800:
        case 0x1000:
            D_hd_code_8036509E = D_hd_code_80364AC1 != 0 ? 0xFD : 0xFE;
            break;
        default:
            D_hd_code_8036509E = (s16) D_hd_code_80364456;
            break;
    }
    sp96 = D_hd_code_8036443C;
    if (D_hd_code_803649EC == 0) {
        D_hd_code_8030F664 = func_hd_code_802A56C4();
    }
    if ((((g_currentGameState & 0x2)) && (D_hd_code_802E8BF0 != 0)) || (D_hd_code_803649EC == 0)) {
        spCC = 0;
        spC8 = 0.0f;
        spC4 = 0.0f;
    } else {
        switch (D_hd_code_8036509E) {
        case 0x7:
            spCC = 11;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0xEB;
            D_hd_code_80364A74 = -0xA5;
            break;
        case 0xA:
            spCC = 9;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0xF5;
            D_hd_code_80364A74 = -0x87;
            break;
        case 0xB:
        case 0x11:
        case 0x12:
            spCC = 11;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0xEB;
            D_hd_code_80364A74 = -0xA5;
            break;
        case 0x8:
            spCC = 7;
            spC8 = 3.0f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0x14F;
            D_hd_code_80364A74 = -0xA5;
            break;
        case 0xF:
            spCC = 7;
            spC8 = 3.0f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0x131;
            D_hd_code_80364A74 = -0xA5;
            break;
        case 0xD:
            spCC = 7;
            spC8 = 3.0f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0x145;
            D_hd_code_80364A74 = -0xA5;
            break;
        case 0xE:
            spCC = 7;
            spC8 = 3.0f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0x13B;
            D_hd_code_80364A74 = -0xA5;
            break;
        case 0x9:
            spCC = 11;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0x3E8;
            D_hd_code_80364A72 = 0x87;
            D_hd_code_80364A74 = -0x55;
            break;
        case 0x6:
            spCC = 11;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0x1388;
            D_hd_code_80364A72 = 0;
            D_hd_code_80364A74 = 0;
            break;
        case 0x5:
            spCC = 9;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0xCD;
            D_hd_code_80364A74 = -0x69;
            break;
        case 0x4:
            spCC = 9;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0xEB;
            D_hd_code_80364A74 = -0xA5;
            break;
        case 0x3:
            spCC = 7;
            spC8 = 3.0f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0xEB;
            D_hd_code_80364A74 = -0xA5;
            break;
        case 0x2:
            spCC = 11;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0x7D0;
            D_hd_code_80364A72 = 0x91;
            D_hd_code_80364A74 = -0x55;
            break;
        case 0x10:
            spCC = 2;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0x258;
            D_hd_code_80364A72 = 0x91;
            D_hd_code_80364A74 = -0x55;
            break;
        case 0x1:
            spCC = 11;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0xCD;
            D_hd_code_80364A74 = -0xA5;
            break;
        case 0x0:
            spCC = 0x14;
            spC8 = 0.25f;
            spC4 = 15.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0x55;
            D_hd_code_80364A74 = -0x19;
            break;
        case 0xFF:
            spCC = 11;
            spC8 = 0.75f;
            spC4 = 30.0f;
            sp96 = (s16) (sp96 / 2);
            D_hd_code_80364A72 = 0;
            D_hd_code_80364A74 = 0;
            break;
        case 0xFE:
            spCC = 11;
            spC8 = 0.75f;
            spC4 = 30.0f;
            sp96 = D_hd_code_803EF328;
            D_hd_code_8030F664 = 0;
            D_hd_code_8036443E = D_hd_code_803EF32A;
            D_hd_code_80364A72 = 0;
            D_hd_code_80364A74 = 0;
            break;
        case 0xFD:
            spCC = 11;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            sp96 = (s16) (sp96 / 2);
            D_hd_code_8036443E = (s16) ((s16) D_hd_code_8036443E / 2);
            D_hd_code_80364A72 = 0;
            D_hd_code_80364A74 = 0;
            break;
        }
    }
    if (g_currentGameState == 0x40) {
        spCC = spCC / 2;
    }
    if (sp96 > D_hd_code_80364A72 ) {
        sp96 = D_hd_code_80364A72;
    }
    if (sp96 < D_hd_code_80364A74) {
        sp96 = D_hd_code_80364A74;
    }
    if (((sp96 > 0) && (D_hd_code_80370C1C != 0) && (D_hd_code_802E8BD0 == 0) && ((g_currentGameState & 0x106))) || ((sp96 < 0) && (D_hd_code_80370C1D != 0) && (D_hd_code_802E8BD0 == 0) && ((g_currentGameState & 0x106)))) {
        if (D_hd_code_80364444 < (f32) sp96) {
            D_hd_code_80364444 += spC8;
        }
        if (D_hd_code_80364444 > (f32) sp96) {
            D_hd_code_80364444 -= spC8;
        }
    } else {
        if ((D_hd_code_80364444 < (f32) sp96) && (sp96 <= 0)) {
            D_hd_code_80364444 += (spC8 * 10.0f);
            if ((f32) sp96 < D_hd_code_80364444) {
                D_hd_code_80364444 = (f32) sp96;
            }
        }
        if ((D_hd_code_80364444 > (f32) sp96) && (sp96 >= 0)) {
            D_hd_code_80364444 = D_hd_code_80364444 - (spC8 * 10.0f);
            if (D_hd_code_80364444 <  (f32) sp96) {
                D_hd_code_80364444 =  (f32) sp96;
            }
        }
    }
    spD0 = (f32) D_hd_code_8036443E - D_hd_code_80364448;
    if (spD0 < 0.0) {
        spD0 = (f32) (0.0 - spD0);
    }
    if ((f64) spD0 > 2048.0) {
        if (D_hd_code_80364448 > (f32) D_hd_code_8036443E) {
            D_hd_code_80364448 = D_hd_code_80364448 + spC4;
            if (D_hd_code_80364448 > 4095.0) {
                D_hd_code_80364448 = (f32) (D_hd_code_80364448 - 4095.0);
                if ((f32) D_hd_code_8036443E < D_hd_code_80364448) {
                    D_hd_code_80364448 = (f32) D_hd_code_8036443E;
                }
            }
        } else {
            D_hd_code_80364448 = D_hd_code_80364448 - spC4;
            if (D_hd_code_80364448 < 0.0) {
                D_hd_code_80364448 = (f32) (D_hd_code_80364448 + 4095.0);
                if (D_hd_code_80364448 < (f32) D_hd_code_8036443E) {
                    D_hd_code_80364448 = (f32) D_hd_code_8036443E;
                }
            }
        }
    } else {
        if (D_hd_code_80364448 > (f32) D_hd_code_8036443E) {
            D_hd_code_80364448 =  D_hd_code_80364448 - spC4;
            if (D_hd_code_80364448 < (f32) D_hd_code_8036443E) {
                D_hd_code_80364448 = (f32) D_hd_code_8036443E;
            }
        }
        if (D_hd_code_80364448 < (f32) D_hd_code_8036443E) {
            D_hd_code_80364448 = D_hd_code_80364448 + spC4;
            if ((f32) D_hd_code_8036443E < D_hd_code_80364448) {
                D_hd_code_80364448 = (f32) D_hd_code_8036443E;
            }
        }
    }
    spE2 = (s16) (s16) (s32) D_hd_code_80364448 % 1024;
    spDE = (s16) (s32) (hdCos((f32) ((f64) ((f32) (s16) spE2 / 1024.0f) * 1.5708)) * ((f32) spCC * D_hd_code_80364444));
    spE0 = (s16) (s32) (hdSin((f32) ((f64) ((f32) spE2 / 1024.0f) * 1.5708)) * ((f32) spCC * D_hd_code_80364444));
    if ((D_hd_code_80364448 >= 0.0f) && (D_hd_code_80364448 < 1024.0f)) {
        spD8 = (s32) (s16) spE0;
        spD4 = (s32) spDE;
    }
    if ((D_hd_code_80364448 >= 1024.0f) && (D_hd_code_80364448 < 2048.0f)) {
        spD8 = (s32) spDE;
        spD4 = (s32) -spE0;
    }
    if ((D_hd_code_80364448 >= 2048.0f) && (D_hd_code_80364448 < 3072.0f)) {
        spD8 = (s32) -spE0, // LATER: Perhaps struct copy?
        spD4 = (s32) -spDE;
    }
    if ((D_hd_code_80364448 >= 3072.0f) && (D_hd_code_80364448 < 4096.0f)) {
        spD8 = (s32) -spDE;
        spD4 = (s32) spE0;
    }

    switch(g_currentGameState) {
        case 0x100: {
            if (D_hd_code_80364AC1 != 0) {
                if (D_hd_code_80364412 != 0) {
                    D_hd_code_8036509C = D_hd_code_803FCD68 * 0x10;
                } else {
                    D_hd_code_8036509C = ((s16) (((u16) D_hd_code_803FCD68 * 0x10) - D_hd_code_8036509C) / 10) + (s16) D_hd_code_8036509C;
                }
                D_hd_code_803643EC = (s32) (((f32) D_hd_code_803FCD48 - (hdSin((f32) ((f64) ((f32) (s16) D_hd_code_8036509C / 16384.0f) * 1.5708)) * 8000.0f)) + (f32) spD8) << 11;
                D_hd_code_803643F0 = (D_hd_code_803FCD4C + 0xDAC) << 11;
                D_hd_code_803643F4 = (s32) (((f32) D_hd_code_803FCD50 - (hdCos((f32) ((f64) ((f32) (s16) D_hd_code_8036509C / 16384.0f) * 1.5708)) * 8000.0f)) + (f32) spD4) << 11;
            } else {
                D_hd_code_803643EC = (D_hd_code_803EF6DC + 0xFA0) << 11;
                D_hd_code_803643F0 = (D_hd_code_803EF6E0 + 0x61A8) << 11;
                D_hd_code_803643F4 = (D_hd_code_803EF6E4 + D_hd_code_80364A78 + 0x1B58) << 11;
            }
            break;
        }
        case 0x40: {
            switch ((u32) D_hd_code_80364AA8) {             /* switch 4; irregular */
            case 0x1:                               /* switch 4 */
            case 0x80:                              /* switch 4 */
                if (D_hd_code_803643DB != 0) {
                    D_hd_code_803643EC = (D_hd_code_803EF6DC + spD8) << 11;
                    D_hd_code_803643F0 = (D_hd_code_803EF6E0 + 0x7D0) << 11;
                    D_hd_code_803643F4 = (D_hd_code_803EF6E4 + spD4) << 11;
                }
                if (D_hd_code_80364AC1 != 0) {
                    if ((u32) g_frameCount < 2U) {
                        D_hd_code_8036509C = D_hd_code_803FCD68 * 0x10;
                    } else {
                        D_hd_code_8036509C = ((s16) (((u16) D_hd_code_803FCD68 * 0x10) - D_hd_code_8036509C) / 10) + (s16) D_hd_code_8036509C;
                    }
                    D_hd_code_803643EC = (s32) (((f32) D_hd_code_803FCD48 - (hdSin((f32) ((f64) ((f32) (s16) D_hd_code_8036509C / 16384.0f) * 1.5708)) * 8000.0f)) + (f32) spD8) << 11;
                    D_hd_code_803643F0 = (D_hd_code_803FCD4C + 0xDAC) << 11;
                    D_hd_code_803643F4 = (s32) (((f32) D_hd_code_803FCD50 - (hdCos((f32) ((f64) ((f32) (s16) D_hd_code_8036509C / 16384.0f) * 1.5708)) * 8000.0f)) + (f32) spD4) << 11;
                }
                if ((D_hd_code_803643DB == 0) && (D_hd_code_80364AC1 == 0)) {
                case 0x4:                           /* switch 4 */
                case 0x8:                           /* switch 4 */
                    if (D_hd_code_80364412 == 0) {
                        D_hd_code_8036509C = ((s16) (((u16) D_hd_code_8036443E * 0x10) - D_hd_code_8036509C) / 10) + (s16) D_hd_code_8036509C;
                    } else {
                        D_hd_code_8036509C = D_hd_code_8036443E * 0x10;
                    }
                    D_hd_code_803643EC = (s32) (((f32) D_hd_code_803643E0 - (hdSin((f32) ((f64) ((f32) (s16) D_hd_code_8036509C / 16384.0f) * 1.5708)) * ((f32) D_hd_code_8036444C * 2.0f))) + (f32) spD8) << 11;
                    D_hd_code_803643F0 = (D_hd_code_8036444E + D_hd_code_803643E4) << 11;
                    D_hd_code_803643F4 = (s32) (((f32) D_hd_code_803643E8 - (hdCos((f32) ((f64) ((f32) (s16) D_hd_code_8036509C / 16384.0f) * 1.5708)) * ((f32) D_hd_code_8036444C * 2.0f))) + (f32) spD4) << 11;
                }
                break;
            case 0x2:                               /* switch 4 */
            case 0x20:                              /* switch 4 */
                if (D_hd_code_80364412 == 0) {
                    D_hd_code_8036509C = ((s16) (((u16) D_hd_code_8036443E * 0x10) - D_hd_code_8036509C) / 10) + (s16) D_hd_code_8036509C;
                } else {
                    D_hd_code_8036509C = D_hd_code_8036443E * 0x10;
                }
                D_hd_code_803643EC = (s32) ((hdSin((f32) ((f64) ((f32) (s16) D_hd_code_8036509C / 16384.0f) * 1.5708)) * ((f32) D_hd_code_8036444C * 2.0f)) + (f32) D_hd_code_803643E0 + (f32) spD8) << 11;
                D_hd_code_803643F0 = (D_hd_code_8036444E + D_hd_code_803643E4 + (D_hd_code_80370C2D * 0x32)) << 11;
                D_hd_code_803643F4 = (s32) ((hdCos((f32) ((f64) ((f32) (s16) D_hd_code_8036509C / 16384.0f) * 1.5708)) * ((f32) D_hd_code_8036444C * 2.0f)) + (f32) D_hd_code_803643E8 + (f32) spD4) << 11;
                break;
            case 0x10:                              /* switch 4 */
            case 0x40:                              /* switch 4 */
                D_hd_code_803643EC = (((D_hd_code_8036BED8[D_hd_code_8036BBB0[g_statsNew.rdusFound]].x) << 5) + spD8) << 11;
                D_hd_code_803643F0 = (((D_hd_code_8036BED8[D_hd_code_8036BBB0[g_statsNew.rdusFound]].y) << 5) + 2000) << 11;
                D_hd_code_803643F4 = (((D_hd_code_8036BED8[D_hd_code_8036BBB0[g_statsNew.rdusFound]].z) << 5) + spD4) << 11;
                break;
            }
            break;
        }
        case 0x200: {
            if (D_hd_code_80364AC1 != 0) {
                D_hd_code_803643EC = ((D_hd_code_803FCD48 + spD8) - 0x1770) << 11;
                D_hd_code_803643F0 = (D_hd_code_803FCD4C + 0xD48) << 11;
                D_hd_code_803643F4 = (D_hd_code_803FCD50 + spD4 + 0x1770) << 11;
            } else if (D_hd_code_803643D6 != 0) {
                D_hd_code_803643EC = (D_hd_code_803EF6DC + spD8 + 0x3E80) << 11;
                D_hd_code_803643F0 = (D_hd_code_803EF6E0 + 0x3A98) << 11;
                D_hd_code_803643F4 = ((D_hd_code_803EF6E4 + spD4) - 0xBB8) << 11;
            } else {
                D_hd_code_803643EC = (D_hd_code_803EF6DC + spD8 + 0xFA0) << 11;
                D_hd_code_803643F0 = (D_hd_code_803EF6E0 + 0x960) << 11;
                if (g_currentLevel == LEVEL_SIMIAN_ACRES) {
                    D_hd_code_803643F0 = D_hd_code_803643F0 + 0x5DC000;
                }
                D_hd_code_803643F4 = ((D_hd_code_803EF6E4 + spD4) - 0xFA0) << 11;
            }
            break;
        }
        case 0x400: {
            if (D_hd_code_80364AC1 != 0) {
                D_hd_code_803643EC = (D_hd_code_803FCD48 + spD8 + 0x1770) << 11;
                D_hd_code_803643F0 = (D_hd_code_803FCD4C + 0xD48) << 11;
                D_hd_code_803643F4 = ((D_hd_code_803FCD50 + spD4) - 0x1770) << 11;
            } else if (D_hd_code_803643D6 != 0) {
                D_hd_code_803643EC = ((D_hd_code_803EF6DC + spD8) - 0x3E80) << 11;
                D_hd_code_803643F0 = (D_hd_code_803EF6E0 + 0x3A98) << 11;
                D_hd_code_803643F4 = ((D_hd_code_803EF6E4 - spD4) + 0xBB8) << 11;
            } else {
                D_hd_code_803643EC = ((D_hd_code_803EF6DC + spD8) - 0xFA0) << 11;
                D_hd_code_803643F0 = (D_hd_code_803EF6E0 + 0x960) << 11;
                if (g_currentLevel == LEVEL_SIMIAN_ACRES) {
                    D_hd_code_803643F0 = D_hd_code_803643F0 + 0x5DC000;
                }
                D_hd_code_803643F4 = (D_hd_code_803EF6E4 + spD4 + 0xFA0) << 11;
            }
            break;
        }


        case 0x1:
        case 0x800: {
            if (D_hd_code_80364AC1 != 0) {
                if ((u32) g_frameCount < 2U) {
                    D_hd_code_8036509C = D_hd_code_803FCD68 * 0x10;
                } else {
                    D_hd_code_8036509C = ((s16) (((u16) D_hd_code_803FCD68 * 0x10) - D_hd_code_8036509C) / 10) + (s16) D_hd_code_8036509C;
                }
                D_hd_code_803643EC = (s32) (((f32) D_hd_code_803FCD48 - (hdSin((f32) ((f64) ((f32) (s16) D_hd_code_8036509C / 16384.0f) * 1.5708)) * 8000.0f)) + (f32) spD8) << 11;
                D_hd_code_803643F0 = (D_hd_code_803FCD4C + 0xDAC) << 11;
                D_hd_code_803643F4 = (s32) (((f32) D_hd_code_803FCD50 - (hdCos((f32) ((f64) ((f32) (s16) D_hd_code_8036509C / 16384.0f) * 1.5708)) * 8000.0f)) + (f32) spD4) << 11;
            } else {
                D_hd_code_803643EC = ((D_hd_code_803643E0 + spD8) - 0x1F4) << 11;
                D_hd_code_803643F0 = (D_hd_code_803643E4 + 0x1770) << 11;
                D_hd_code_803643F4 = (D_hd_code_803643E8 + spD4 + 0x1F4) << 11;
            }
            break;
        }
        case 0x1000: {
            D_hd_code_803643EC = ((D_hd_code_803643E0 + spD8) - 0xFA0) << 11;
            D_hd_code_803643F0 = (D_hd_code_803643E4 + 0x1388) << 11;
            D_hd_code_803643F4 = (D_hd_code_803643E8 + spD4 + 0xFA0) << 11;
            break;
        }
        default: {
            if (D_hd_code_80364410 != 0) {
                D_hd_code_803643EC = D_hd_code_80364404;
                D_hd_code_803643F0 = D_hd_code_80364408;
                D_hd_code_803643F4 = D_hd_code_8036440C;
            } else {
                if (D_hd_code_80364AA8 == 0x40) {
                    D_hd_code_8036444C = 0x2328;
                    D_hd_code_8036444E = 0x2AF8;
                    D_hd_code_80364420 = 0x2AF8;
                }
                if ((D_hd_code_80364AC1 != 0) && (D_hd_code_8036B8B0 != 0)) {
                    D_hd_code_803643EC = (D_hd_code_803FCD48 + D_hd_code_8036B8B4) << 11;
                    D_hd_code_803643F0 = (D_hd_code_803FCD4C + D_hd_code_8036B8B8) << 11;
                    D_hd_code_803643F4 = (D_hd_code_803FCD50 + D_hd_code_8036B8BC) << 11;
                } else if ((D_hd_code_803643DB != 0) && (D_hd_code_8036B8B0 != 0)) {
                    D_hd_code_803643EC = (D_hd_code_803EF6DC + D_hd_code_8036B8B4) << 11;
                    D_hd_code_803643F0 = (D_hd_code_803EF6E0 + D_hd_code_8036B8B8) << 11;
                    D_hd_code_803643F4 = (D_hd_code_803EF6E4 + D_hd_code_8036B8BC) << 11;
                } else {
                    if (D_hd_code_8030F668.flag1 != 0) {
                        func_hd_code_80255034(0x9C4, D_hd_code_80364414, &sp90, &sp8C);
                        D_hd_code_803643EC = ((D_hd_code_803F767C << 5) + sp90) << 11;
                        D_hd_code_803643F0 = ((D_hd_code_803F767E << 5) + 0x1388) << 11;
                        D_hd_code_803643F4 = ((D_hd_code_803F7680 << 5) + sp8C) << 11;
                    }
                    else if (D_hd_code_8030F668.flag3 != 0) {
                        func_hd_code_80255034(0x9C4, D_hd_code_80364414, &sp90, &sp8C);
                        D_hd_code_803643EC = (sp90 + D_hd_code_803F7670) << 11;
                        D_hd_code_803643F0 = (D_hd_code_803F7674 + 0x1388) << 11;
                        D_hd_code_803643F4 = (sp8C + D_hd_code_803F7678) << 11;
                    } else if (D_hd_code_8030F668.flag2 != 0) {
                        if (D_hd_code_8036C794 != NULL) {
                            func_hd_code_80255034(0x9C4, D_hd_code_80364414, &sp90, &sp8C);
                            D_hd_code_803643EC = (((s32) (D_hd_code_8036C794[0].x + D_hd_code_8036C794[3].x) / 2) << 16) + (sp90 << 11);
                            D_hd_code_803643F0 = (((s32) (D_hd_code_8036C794[0].y + D_hd_code_8036C794[3].y) / 2) << 16) + 0x9C4000;
                            D_hd_code_803643F4 = (((s32) (D_hd_code_8036C794[0].z + D_hd_code_8036C794[3].z) / 2) << 16) + (sp8C << 11);
                        }
                    } else {
                        if (D_hd_code_80364A85 != 0) {
                            sp76 = (s16) (s32) (((f32) ((s32) (D_hd_code_8036443E * 0x168) / 4096) - D_hd_code_80364414) + 180.0f);
                            if ((s16) sp76 < 0) {
                                sp76 = (s16) sp76 + 0x168;
                            }
                            if (sp76 >= 0x168) {
                                sp76 = (s16) (sp76 % 360);
                            }
                            if ((D_hd_code_80364456 == 2) || (D_hd_code_80364456 == 9)) {
                                func_hd_code_80255034((s32) D_hd_code_8036444C, (f32) sp76, &sp90, &sp8C);
                            } else {
                                func_hd_code_80255034((s16) D_hd_code_8036444C / 2, (f32) sp76, &sp90, &sp8C);
                            }
                            D_hd_code_803643F0 = (((s32) (D_hd_code_80364420 * 3) / 5) + D_hd_code_803643E4) << 11;
                            spD8 = 0;
                            spD4 = 0;
                        } else {
                            func_hd_code_80255034((s32) D_hd_code_8036444C, D_hd_code_80364414, &sp90, &sp8C);
                            if ((D_hd_code_80364411 != 0) && D_hd_code_80364414 >= 134.0 && D_hd_code_80364414 <= 136.0) {
                                D_hd_code_803643F0 = (D_hd_code_803643E4 + 0x3908) << 11;
                            } else {
                                D_hd_code_803643F0 = (D_hd_code_803643E4 + D_hd_code_80364420) << 11;
                            }
                        }
                        D_hd_code_803643EC = (D_hd_code_803643E0 + sp90 + spD8) << 11;
                        D_hd_code_803643F4 = (D_hd_code_803643E8 + sp8C + spD4) << 11;
                    }
                }
            }
            break;
        }
    }


    switch(g_currentGameState) {
        case 0x100:
            {
                if (D_hd_code_80364AC1 != 0) {
                    D_hd_code_80365078 = (f32) D_hd_code_803FCD48 / 32.0f;
                    D_hd_code_8036507C = (f32) (D_hd_code_803FCD4C + 0x7D0) / 32.0f;
                    D_hd_code_80365080 = (f32) D_hd_code_803FCD50 / 32.0f;
                } else {
                    D_hd_code_80365078 = (f32) D_hd_code_803EF6DC / 32.0f;
                    D_hd_code_8036507C = (f32) D_hd_code_803EF6E0 / 32.0f;
                    D_hd_code_80365080 = (f32) (D_hd_code_803EF6E4 + D_hd_code_80364A78 + 0x2AF8) / 32.0f;
                }
                break;
            }
        case 0x200:
        case 0x400:
            {
                if (D_hd_code_80364AC1 != 0) {
                    D_hd_code_80365078 = (f32) (D_hd_code_803FCD48 + spD8) / 32.0f;
                    D_hd_code_8036507C = (f32) (D_hd_code_803FCD4C + 0x7D0) / 32.0f;
                    D_hd_code_80365080 = (f32) (D_hd_code_803FCD50 + spD4) / 32.0f;
                } else {
                    D_hd_code_80365078 = (f32) (D_hd_code_803EF6DC + spD8) / 32.0f;
                    D_hd_code_8036507C = (f32) D_hd_code_803EF6E0 / 32.0f;
                    D_hd_code_80365080 = (f32) (D_hd_code_803EF6E4 + spD4) / 32.0f;
                }
                break;
            }
        case 0x1:
        case 0x800:
        case 0x1000:
            {
                if (D_hd_code_80364AC1 != 0) {
                    D_hd_code_80365078 = (f32) D_hd_code_803FCD48 / 32.0f;
                    D_hd_code_8036507C = (f32) (D_hd_code_803FCD4C + 0x7D0) / 32.0f;
                    D_hd_code_80365080 = (f32) D_hd_code_803FCD50 / 32.0f;
                } else {
                    D_hd_code_80365078 = (f32) (D_hd_code_803EF2EC + spD8) / 32.0f;
                    D_hd_code_8036507C = (f32) D_hd_code_803EF314 / 32.0f;
                    D_hd_code_80365080 = (f32) (D_hd_code_803EF2F4 + spD4) / 32.0f;
                }
                break;
            }
        case 0x40:
            if (D_hd_code_80364AC1 != 0) {
                D_hd_code_80365078 = (f32) D_hd_code_803FCD48 / 32.0f;
                D_hd_code_8036507C = (f32) (D_hd_code_803FCD4C + 0x7D0) / 32.0f;
                D_hd_code_80365080 = (f32) D_hd_code_803FCD50 / 32.0f;
            }
            else
        default:
            {
                if ((D_hd_code_80364AC1 != 0) && (D_hd_code_8036B8B0 != 0)) {
                    D_hd_code_80365078 = (f32) D_hd_code_803FCD48 / 32.0f;
                    D_hd_code_8036507C = (f32) (D_hd_code_803FCD4C + 0x1770) / 32.0f;
                    D_hd_code_80365080 = (f32) D_hd_code_803FCD50 / 32.0f;
                }
                else if ((D_hd_code_803643DB != 0) && (D_hd_code_8036B8B0 != 0)) {
                    D_hd_code_80365078 = (f32) D_hd_code_803EF6DC / 32.0f;
                    D_hd_code_8036507C = (f32) D_hd_code_803EF6E0 / 32.0f;
                    D_hd_code_80365080 = (f32) D_hd_code_803EF6E4 / 32.0f;
                }
                else if (D_hd_code_8030F668.flag1 != 0) {
                    D_hd_code_80365078 = (f32) D_hd_code_803F767C;
                    D_hd_code_8036507C = (f32) D_hd_code_803F767E;
                    D_hd_code_80365080 = (f32) D_hd_code_803F7680;
                }
                else if (D_hd_code_8030F668.flag3 != 0) {
                    D_hd_code_80365078 = (f32) D_hd_code_803F7670 / 32.0f;
                    D_hd_code_8036507C = (f32) D_hd_code_803F7674 / 32.0f;
                    D_hd_code_80365080 = (f32) D_hd_code_803F7678 / 32.0f;
                }
                else if (D_hd_code_8030F668.flag2 != 0) {
                    if (D_hd_code_8036C794 != NULL) {
                        D_hd_code_80365078 = (f32) ((f64) (f32) (D_hd_code_8036C794[0].x + D_hd_code_8036C794[3].x) / 2.0);
                        D_hd_code_8036507C = (f32) ((f64) (f32) (D_hd_code_8036C794[0].y + D_hd_code_8036C794[3].y) / 2.0);
                        D_hd_code_80365080 = (f32) ((f64) (f32) (D_hd_code_8036C794[0].z + D_hd_code_8036C794[3].z) / 2.0);
                    }
                } else {
                    D_hd_code_80365078 = (f32) (D_hd_code_803643E0 + spD8) / 32.0f;
                    D_hd_code_8036507C = (f32) (D_hd_code_803643E4 + D_hd_code_8030F664) / 32.0f;
                    D_hd_code_80365080 = (f32) (D_hd_code_803643E8 + spD4) / 32.0f;
                }
            }
            break;
    }


    if ((D_hd_code_803643D6 != 0) && (g_currentLevel == LEVEL_END_SEQUENCE)) {
        D_hd_code_803643EC = (D_hd_code_803EF6DC + spD8 + 0x3E80) << 11;
        D_hd_code_803643F0 = (D_hd_code_803EF6E0 + 0x3A98) << 11;
        D_hd_code_803643F4 = ((D_hd_code_803EF6E4 + spD4) - 0xBB8) << 11;
    }
    if ((D_hd_code_80364AC1 != 0) && (D_hd_code_8036B965 != 0)) {
        if (D_hd_code_80364412 != 0) {
            D_hd_code_8036509C = D_hd_code_803FCD68 * 0x10;
        } else {
            D_hd_code_8036509C = ((s16) (((u16) D_hd_code_803FCD68 * 0x10) - D_hd_code_8036509C) / 10) + (s16) D_hd_code_8036509C;
        }
        D_hd_code_803643EC = (s32) (((f32) D_hd_code_803FCD48 - (hdSin((f32) ((f64) ((f32) (s16) D_hd_code_8036509C / 16384.0f) * 1.5708)) * 8000.0f)) + (f32) spD8) << 11;
        D_hd_code_803643F0 = (D_hd_code_803FCD4C + 0xDAC) << 11;
        D_hd_code_803643F4 = (s32) ((D_hd_code_803FCD50 - (hdCos((f32) ((f64) ((f32) (s16) D_hd_code_8036509C / 16384.0f) * 1.5708)) * 8000.0f)) + (f32) spD4) << 11;
        D_hd_code_80365078 = (f32) D_hd_code_803FCD48 / 32.0f;
        D_hd_code_8036507C = (f32) (D_hd_code_803FCD4C + 0x7D0) / 32.0f;
        D_hd_code_80365080 = D_hd_code_803FCD50 / 32.0f;
    }
    if ( (g_currentGameState == 0x40) && (g_currentLevel == LEVEL_LIZARD_ISLAND)) {
        D_hd_code_803643EC = (D_hd_code_803643E0 + 0x1900) << 11;
        D_hd_code_803643F0 = (D_hd_code_803643E4 + 0x3070) << 11;
        D_hd_code_803643F4 = (D_hd_code_803643E8 - 0x1900) << 11;
        D_hd_code_80365078 = (f32) D_hd_code_803643E0 / 32.0f;
        D_hd_code_8036507C = (f32) D_hd_code_803643E4 / 32.0f;
        D_hd_code_80365080 = (f32) D_hd_code_803643E8 / 32.0f;
    }
    if (((g_currentGameState & 0x2000000000002104) ) && (D_hd_code_8036B8B0 == 0) && (sp95 == 0) && ((g_currentGameState != 0x100)) && (g_currentLevel != 0x23) && (D_hd_code_80364A85 == 0)) {
        sp70 = (s32) ((f64) D_hd_code_80365078 * 65536.0);
        sp6C = (s32) ((f64) D_hd_code_8036507C * 65536.0);
        sp68 = (s32) ((f64) D_hd_code_80365080 * 65536.0);
        if ((g_currentLevel == LEVEL_HAVOC_DISTRICT) && (8718.0f < D_hd_code_80365078) && (D_hd_code_80365078 < 8919.0f) && (9051.0f < D_hd_code_80365080) && (D_hd_code_80365080 < 9251.0f)) {
            D_hd_code_802E8BE0 = 1.5f;
            spF8 = 0.1f;
        }
        D_hd_code_803643EC = (s32) (((f32) (D_hd_code_803643EC - sp70) * D_hd_code_802E8BE0) + (f32) sp70);
        D_hd_code_803643F0 = (s32) (((f32) (D_hd_code_803643F0 - sp6C) * D_hd_code_802E8BE0) + (f32) sp6C);
        D_hd_code_803643F4 = (s32) (((f32) (D_hd_code_803643F4 - sp68) * D_hd_code_802E8BE0) + (f32) sp68);
    }
    if (D_hd_code_80364412 == 0) {
        D_hd_code_803643F8 = (s32) (((f32) (D_hd_code_803643EC - D_hd_code_803643F8) * spFC) + (f32) D_hd_code_803643F8);
        D_hd_code_803643FC = (s32) (((f32) (D_hd_code_803643F0 - D_hd_code_803643FC) * spF8) + (f32) D_hd_code_803643FC);
        D_hd_code_80364400 = (s32) (((f32) (D_hd_code_803643F4 - D_hd_code_80364400) * spF4) + (f32) D_hd_code_80364400);
    } else {
        D_hd_code_803643F8 = D_hd_code_803643EC;
        D_hd_code_803643FC = D_hd_code_803643F0;
        D_hd_code_80364400 = D_hd_code_803643F4;
        D_hd_code_803650A0 = !D_hd_code_8036509E;
    }

    if ((D_hd_code_80364424 != 0) && (((D_hd_code_80364414 < 134.0)) || (D_hd_code_80364414 > 136.0))) {
        func_hd_code_802CE4F0((s32) D_hd_code_803643F8 >> 0xB, (s32) D_hd_code_803643FC >> 0xB, (s32) D_hd_code_80364400 >> 11);
        func_hd_code_802CE5BC((s32) D_hd_code_803643F8 >> 0xB, (s32) D_hd_code_803643FC >> 0xB, (s32) D_hd_code_80364400 >> 0xB, D_hd_code_80364434 ? D_hd_code_80364430 : D_hd_code_80364430 + 0x640, 0xBE, 0);
        if (D_hd_code_80364434 != 0) {
            if (D_hd_code_803A7424 != 0) {
                D_hd_code_80364420 += D_hd_code_8036442C;
                if ((u32) D_hd_code_80364428 < D_hd_code_80364420) {
                    D_hd_code_80364420 = D_hd_code_80364428;
                }
                D_hd_code_80364434 = 1;
            } else {
                D_hd_code_80364434 = 0;
            }
        } else if (D_hd_code_803A7424 != 0) {
            D_hd_code_80364434 = 1;
        } else {
            D_hd_code_80364420 = D_hd_code_80364420 - D_hd_code_8036442C;
            if ((s32) D_hd_code_80364420 < D_hd_code_8036444E) {
                D_hd_code_80364420 = (u32) D_hd_code_8036444E;
            }
            D_hd_code_80364434 = 0;
        }
    }
    if (D_hd_code_80364424 == 0) {
        D_hd_code_80364420 = (u32) D_hd_code_8036444E;
    } else {
        if ((D_hd_code_80364414 >= 134.0) && (D_hd_code_80364414 <= 136.0)) {
            D_hd_code_80364420 = D_hd_code_80364420 - D_hd_code_8036442C;
            if ((s32) D_hd_code_80364420 < D_hd_code_8036444E) {
                D_hd_code_80364420 = (u32) D_hd_code_8036444E;
            }
        }
    }
    if ((D_hd_code_8036509E != D_hd_code_803650A0) || (sp8B != 0)) {
        D_hd_code_80365090.x = D_hd_code_80365084 - D_hd_code_80365078;
        D_hd_code_80365090.y = D_hd_code_80365088 - D_hd_code_8036507C;
        D_hd_code_80365090.z = D_hd_code_8036508C - D_hd_code_80365080;
        D_hd_code_803650A0 = D_hd_code_8036509E;
        D_hd_code_8030F660 = 0;
    }
    if ((D_hd_code_8030F660 == 0) && (D_hd_code_80364412 == 0)) {
        D_hd_code_80365090.x = D_hd_code_80365090.x * 0.95;
        D_hd_code_80365084 = D_hd_code_80365090.x + D_hd_code_80365078;

        D_hd_code_80365090.y = D_hd_code_80365090.y * 0.97;
        D_hd_code_80365088 = D_hd_code_80365090.y + D_hd_code_8036507C;

        D_hd_code_80365090.z = D_hd_code_80365090.z * 0.95;
        D_hd_code_8036508C = D_hd_code_80365090.z + D_hd_code_80365080;

        if (D_hd_code_80365090.x < 0.1  &&
            D_hd_code_80365090.x > -0.1 &&
            D_hd_code_80365090.z < 0.1 &&
            D_hd_code_80365090.z > -0.1 &&
            D_hd_code_80365090.y < 0.1 &&
            D_hd_code_80365090.y > -0.1) {
            D_hd_code_8030F660 = 1;
        }
    } else {
        D_hd_code_80365084 = D_hd_code_80365078;
        D_hd_code_80365088 = D_hd_code_8036507C;
        D_hd_code_8036508C = D_hd_code_80365080;
        D_hd_code_8030F660 = 1;
    }
    if (D_hd_code_802E8BE8 == 0) {
        D_hd_code_802E8BE8 = 1;
    }
    if ((D_hd_code_802E8BE4 != 0) && ((g_currentGameState & 0x2000100000000206))) {
        spC0 = (D_hd_code_803649D8 % D_hd_code_802E8BE8) - (D_hd_code_802E8BE8 >> 1);
        spBC = (D_hd_code_803649D8 / 100) % D_hd_code_802E8BE8 - (D_hd_code_802E8BE8 >> 1);
        spB8 = (D_hd_code_803649D8 / 10000) % D_hd_code_802E8BE8 - (D_hd_code_802E8BE8 >> 1);
    } else {
        spC0 = 0;
        spBC = 0;
        spB8 = 0;
    }
    if (D_hd_code_802E8BE4 != 0) {
        D_hd_code_802E8BE4 -= 1;
        D_hd_code_802E8BE8 -= ((s32) D_hd_code_802E8BE8 / 6);
        D_hd_code_802E8BE8++;
    }
    spB4 = (f32) ((f64) (f32) D_hd_code_803643F8 / 65536.0);
    spB0 = (f32) ((f64) (f32) D_hd_code_803643FC / 65536.0);
    spAC = (f32) ((f64) (f32) D_hd_code_80364400 / 65536.0);
    if ((g_currentGameState & 2) &&
        (D_hd_code_802E8BF0 != 0) &&
        (g_frameCount > D_hd_code_80366A04 )) {
        spB4 = ((spB4 - D_hd_code_80365084) * D_hd_code_803649F8) + D_hd_code_80365084;
        spB0 = ((spB0 - D_hd_code_80365088) * D_hd_code_803649F8) + D_hd_code_80365088;
        spAC = ((spAC - D_hd_code_8036508C) * D_hd_code_803649F8) + D_hd_code_8036508C;
        if (D_hd_code_803649F8 > 0.4) {
            D_hd_code_803649F8 = D_hd_code_803649F8 - 0.01;
        }
    }
    sp7C = (f32)((D_hd_code_80365084 * 32.0f) + spC0) / 32.0f;
    sp78 = (f32)((D_hd_code_8036508C * 32.0f) + spB8) / 32.0f;
    sp84 = (spB4 - sp7C);

    if (sp84 < 0.0) {
        sp84 = 0.0-sp84;
    }
    sp80 = spAC - sp78;
    if (sp80 < 0.0) {
        sp80 = 0.0-sp80;
    }
    if (((f64) sp84 > 0.5) || ((f64) sp80 > 0.5)) {
        guLookAtReflect(arg0, arg1, spB4, spB0, spAC, ((D_hd_code_80365084 * 32.0f) + (f32) spC0) / 32.0f, ((D_hd_code_80365088 * 32.0f) + (f32) spBC) / 32.0f, ((D_hd_code_8036508C * 32.0f) + (f32) spB8) / 32.0f, 0.0f, 1.0f, 0.0f);
    } else {
        guLookAtReflect(arg0, arg1, (f32) ((f64) spB4 + 2.0), spB0, (f32) ((f64) spAC + 2.0), ((D_hd_code_80365084 * 32.0f) + (f32) spC0) / 32.0f, ((D_hd_code_80365088 * 32.0f) + (f32) spBC) / 32.0f, ((D_hd_code_8036508C * 32.0f) + (f32) spB8) / 32.0f, 0.0f, 1.0f, 0.0f);
    }
    sp98 = sqrtf(((spB4 - D_hd_code_80365084) * (spB4 - D_hd_code_80365084)) + ((spAC - D_hd_code_8036508C) * (spAC - D_hd_code_8036508C)));
    if (sp98 < 1.0) {
        sp98 = 1.0;
    }
    if ((spB4 >= D_hd_code_80365084) && (spAC >= D_hd_code_8036508C)) {
        D_hd_code_80364452 = (func_hd_code_802AD7D4((s32) (((f64) (spB4 - D_hd_code_80365084) * 65535.9) / (f64) sp98)) >> 4),
        sp67 = 0;
    }
    if ((spB4 >= D_hd_code_80365084) && (spAC < D_hd_code_8036508C)) {
        D_hd_code_80364452 = 0x400 + (func_hd_code_802AD7D4((s32) (((f64) (D_hd_code_8036508C - spAC) * 65535.9) / (f64) sp98)) >> 4),
        sp67 = 1;
    }
    if ((spB4 < D_hd_code_80365084) && (spAC < D_hd_code_8036508C)) {
        D_hd_code_80364452 = (func_hd_code_802AD7D4((s32) (((f64) (D_hd_code_80365084 - spB4) * 65535.9) / (f64) sp98)) >> 4) + 0x800,
        sp67 = 2;
    }
    if ((spB4 < D_hd_code_80365084) && (spAC >= D_hd_code_8036508C)) {
        D_hd_code_80364452 = (func_hd_code_802AD7D4((s32) (((f64) (spAC - D_hd_code_8036508C) * 65535.9) / (f64) sp98)) >> 4) + 0xC00,
        sp67 = 3;
    }
    sp98 = sqrtf(((spB4 - D_hd_code_80365084) * (spB4 - D_hd_code_80365084)) + ((spAC - D_hd_code_8036508C) * (spAC - D_hd_code_8036508C)) + ((spB0 - D_hd_code_80365088) * (spB0 - D_hd_code_80365088)));
    if (spB0 >= D_hd_code_80365088) {
        sp62 = (s16) (func_hd_code_802AD7D4((s32) (((f64) (spB0 - D_hd_code_80365088) * 65535.9) / (f64) sp98)) >> 3);
    } else {
        sp62 = 0x1000 - (func_hd_code_802AD7D4((s32) (((f64) (D_hd_code_80365088 - spB0) * 65535.9) / (f64) sp98)) >> 3);
    }
    if (spB0 >= D_hd_code_80365088) {
        sp64 =          (func_hd_code_802AD7D4((s32) (65535.0 < (((f64) (spB0 - D_hd_code_80365088) * 65535.9) / 20000.0) ? (65535.0) : (((f64) (spB0 - D_hd_code_80365088) * 65535.9) / 20000.0))) >> 3);
    } else {
        sp64 = 0x1000 - (func_hd_code_802AD7D4((s32) (65535.0 < (((f64) (D_hd_code_80365088 - spB0) * 65535.9) / 20000.0) ? (65535.0) : (((f64) (D_hd_code_80365088 - spB0) * 65535.9) / 20000.0))) >> 3);
    }
    D_hd_code_80364454 = sp62 - sp64;
    sp9C = func_hd_code_80254E54(spB4, spB0, spAC, D_hd_code_80365084, D_hd_code_80365088, D_hd_code_8036508C);
    spA8 = ((spB4 - D_hd_code_80365084) * sp9C) + D_hd_code_80365084;
    spA4 = ((spB0 - D_hd_code_80365088) * sp9C) + D_hd_code_80365088;
    spA0 = ((spAC - D_hd_code_8036508C) * sp9C) + D_hd_code_8036508C;
    if (((f64) sp84 > 0.5) || ((f64) sp80 > 0.5)) {
        guLookAt(arg2, spA8, spA4, spA0, D_hd_code_80365084, D_hd_code_80365088, D_hd_code_8036508C, 0.0f, 1.0f, 0.0f);
    } else {
        guLookAt(arg2, (f32) ((f64) spA8 + 2.0), spA4, (f32) ((f64) spA0 + 2.0), D_hd_code_80365084, D_hd_code_80365088, D_hd_code_8036508C, 0.0f, 1.0f, 0.0f);
    }
    D_hd_code_80364412 = 0;
}

f32 func_hd_code_80254E54(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
  f32 sp2C;
  f32 sp28;
  f32 sp24;
  f32 sp20;
  f32 sp1C;

  switch (D_hd_code_80364456) {
    case 0:
      sp2C = 3.5f;
      break;
    case 1:
      sp2C = 1.4f;
      break;
    case 2:
      sp2C = 1.6f;
      break;
    case 3:
      sp2C = 4.8f;
      break;
    case 4:
      sp2C = 5.0f;
      break;
    case 5:
      sp2C = 5.0f;
      break;
    case 6:
      sp2C = 1.6f;
      break;
    case 7:
      sp2C = 1.6f;
      break;
    case 8:
      sp2C = 4.8f;
      break;
    case 9:
      sp2C = 1.6f;
      break;
    case 10:
      sp2C = 5.0f;
      break;
    case 11:
    case 17:
    case 18:
      sp2C = 1.6f;
      break;
    case 13:
      sp2C = 4.8f;
      break;
    case 14:
      sp2C = 4.8f;
      break;
    case 15:
      sp2C = 4.8f;
      break;
    case 16:
      sp2C = 1.6f;
      break;
  }

  sp28 = arg0 - arg3;
  sp28 = sp28 * sp28;

  sp24 = arg1 - arg4;
  sp24 = sp24 * sp24;

  sp20 = arg2 - arg5;
  sp20 = sp20 * sp20;

  sp1C = sqrtf(sp28 + sp24 + sp20);
  if (sp1C * sp2C > 10000.0f) {
    sp2C -= (sp1C * sp2C - 10000.0f) / sp1C;
  }
  return sp2C;
}

void func_hd_code_80255034(s32 arg0, f32 arg1, s32* arg2, s32* arg3) {
  f32 sp2C;
  f32 sp28;
  s32 sp24;
  s32 sp20;
  f32 sp1C;

  sp28 = arg0 * arg0;
  sp2C = sqrtf(sp28 + sp28);
  sp1C = arg1;
  sp1C = sp1C / 360.0;
  sp1C = sp1C * 6.28318;
  sp24 = (s32) (sinf(sp1C) * sp2C);
  sp20 = (s32) sqrtf((sp2C * sp2C) - (sp24 * sp24));
  if ((arg1 >= 90.0) && (arg1 < 270.0)) {
    sp20 = (s32) (0.0 - (f64) sp20);
  }
  if ((sp20 >= -0x64) && (sp20 < 0x65)) {
    sp20 = 0;
  }
  *arg2 = sp24;
  *arg3 = sp20;
}

void func_hd_code_80255190(void) {
    u8 sp1F;

    if (D_hd_code_802E8BD0 == 0) {
        sp1F = func_hd_code_80255628();
        if ((sp1F != 0) && (((D_hd_code_80370C21 != 0) && (D_hd_code_80370C27 == 0)) || ((D_hd_code_80370C1E != 0) && (D_hd_code_80370C24 == 0))) && ((g_currentGameState & 0x104))) {
            sndPlaySfx(D_hd_code_80367738, 0xD0U, NULL);
        }
        if ((D_hd_code_80370C21 != 0) && (D_hd_code_80370C27 == 0) && (D_hd_code_8036441C == 0) && (D_hd_code_8036441D == 0) && (sp1F == 0) && ((g_currentGameState != 0x2000))) {
            D_hd_code_80364418 = (f32) ((f64) D_hd_code_80364414 + 45.0);
            if (D_hd_code_80364418 >= 360.0) {
                D_hd_code_80364418 = (f64)D_hd_code_80364418 - 360.0;
            }
            D_hd_code_8036441C = 1;
            if (g_currentGameState != 0x40) {
                sndPlaySfx(D_hd_code_80367738, 0xDDU, NULL);
            }
        }
        if (D_hd_code_8036441C != 0) {
            if (D_hd_code_80364414 < D_hd_code_80364418) {
                D_hd_code_80364414 = (f32) ((f64) D_hd_code_80364414 + 3.0);
                if (D_hd_code_80364418 <= D_hd_code_80364414) {
                    D_hd_code_8036441C = 0;
                    D_hd_code_80364414 = D_hd_code_80364418;
                }
            } else {
                D_hd_code_80364414 = (f32) ((f64) D_hd_code_80364414 + 3.0);
                if (D_hd_code_80364414 >= 360.0) {
                    D_hd_code_80364414 = (f32) ((f64) D_hd_code_80364414 - 360.0);
                    if (D_hd_code_80364418 <= D_hd_code_80364414) {
                        D_hd_code_8036441C = 0;
                        D_hd_code_80364414 = D_hd_code_80364418;
                    }
                }
            }
        }
        if ((D_hd_code_80370C1E != 0) && (D_hd_code_80370C24 == 0) && (D_hd_code_8036441C == 0) && (D_hd_code_8036441D == 0) && (sp1F == 0) && (g_currentGameState != 0x2000)) {
            D_hd_code_80364418 = D_hd_code_80364414 - 45.0;
            if (D_hd_code_80364418 < 0.0) {
                D_hd_code_80364418 = (f32) (D_hd_code_80364418 + 360.0);
            }
            D_hd_code_8036441D = 1;
            if (g_currentGameState != 0x40) {
                sndPlaySfx(D_hd_code_80367738, 0xDCU, NULL);
            }
        }
        if (D_hd_code_8036441D != 0) {
            if (D_hd_code_80364414 > D_hd_code_80364418) {
                D_hd_code_80364414 = (f32) ((f64) D_hd_code_80364414 - 3.0);
                if (D_hd_code_80364414 <= D_hd_code_80364418) {
                    D_hd_code_8036441D = 0;
                    D_hd_code_80364414 = D_hd_code_80364418;
                }
            } else {
                D_hd_code_80364414 = D_hd_code_80364414 - 3.0;
                if (D_hd_code_80364414 < 0.0) {
                    D_hd_code_80364414 = (f32) (D_hd_code_80364414 + 360.0);
                    if (D_hd_code_80364414 <= D_hd_code_80364418) {
                        D_hd_code_8036441D = 0;
                        D_hd_code_80364414 = D_hd_code_80364418;
                    }
                }
            }
        }
        if ((D_hd_code_8036441D != 0) || (D_hd_code_8036441C != 0)) {
            func_hd_code_802A45D4(2);
        }
    }
}

u8 func_hd_code_80255628(void) {
  u8 sp37;

  sp37 = 0;
  if (((g_currentGameState == 0x100000000000) ) || ((g_currentGameState == 2) )) {
    sp37 = 1;
  } else {
    switch (g_currentLevel) {
      case 0x4:
        if ((func_hd_code_802AC4C4((s32) D_hd_code_803643E0 >> 5, (s32) D_hd_code_803643E8 >> 5, 0xE56, 0x8EC, 0xBB8, 0x6A4, 0x1068, 0x1F4) != 0) || (func_hd_code_802AC4C4((s32) D_hd_code_803643E0 >> 5, (s32) D_hd_code_803643E8 >> 5, 0xE56, 0x8EC, 0x1068, 0x1F4, 0x1324, 0x4B0) != 0)) {
          sp37 = 1;
        }
        break;
      case 0x10:
        if ((D_hd_code_803643E0 >= 0x46501) && (D_hd_code_803643E8 >= 0x3E801)) {
          sp37 = 1;
        }
        break;
      case 0xD:
        if ((D_hd_code_803643E0 >= 0x42681) && (D_hd_code_803643E8 >= 0x46501)) {
          sp37 = 1;
        }
        break;
      case 0x3B:
        sp37 = 1;
        break;
    }

  }
  if (sp37 != 0 && ((D_hd_code_80364418 < 134.0) || (D_hd_code_80364418 > 136.0))) {
    D_hd_code_8036441D = 0;
    D_hd_code_8036441C = 0;
    D_hd_code_80364418 = 135.0f;
    if (D_hd_code_80364414 > D_hd_code_80364418) {
      if ((D_hd_code_80364414 - D_hd_code_80364418) > 180.0 ) {
        D_hd_code_8036441C = 1;
      } else {
        D_hd_code_8036441D = 1;
      }
    } else {
      D_hd_code_8036441C = 1;
    }
  }
  return sp37;
}

void func_hd_code_802558C8(Gfx* gfx, s32* arg1) {
  Gfx *entry = gfx;

  gDPPipeSync(entry++);
  gDPSetCycleType(entry++, G_CYC_FILL);
  gDPSetColorImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, D_hd_code_80358050[D_hd_code_8035805C]);
  gDPSetFillColor(entry++, 0x00010001);
  gDPPipeSync(entry++);
  gDPFillRectangle(entry++, 0, 0, 319, 239);

  *arg1 += entry - gfx;
}

void func_hd_code_802559F8(Gfx* gfx, s32* length) {
  Gfx *entry = gfx;

  gDPFullSync(entry++);
  gSPEndDisplayList(entry++);

  *length = (s32) (((s32)entry - (s32)&D_hd_code_803156F8[D_hd_code_8035805C]) - 0x48B0) >> 3;
  if (*length >= TOPLEVEL_DL_SIZE) {
    rmonPrintf(ASSERT_MESSAGE, "*length<TOPLEVEL_DL_SIZE", "hd.c", 0xE51);
  }
}

void func_hd_code_80255AD0(void) {
    s32 sp44;
    f32 sp40;
    s64 pad1;
    s64 pad2;
    u8 sp2F;

    sp40 = 1.0f;
    g_currentGameState = 0x20;
    osCreateMesgQueue(&D_hd_code_803150A0, D_hd_code_803150B8, 0x32);
    osCreateMesgQueue(&D_hd_code_80315180, D_hd_code_80315198, 0x90);
    osCreateScheduler(&sc, g_SchedulerStack + 0x800, 0xD, osTvType != OS_TV_NTSC ? OS_VI_PAL_LAN1 : OS_VI_NTSC_LAN1, 1);
    osCreateMesgQueue(&D_hd_code_803153D8, D_hd_code_803153F8, 0x10);
    osScAddClient(&sc, &g_gfxClient, &D_hd_code_803153D8, 1, 1);
    sp2F = func_hd_code_8028A370();
    func_hd_code_80261588();
    rmonPrintf("audio inited\n");
    osViSetSpecialFeatures(2);
    osViSetSpecialFeatures(0x40);
    D_hd_code_80358050[0] = VIRTUAL_TO_PHYSICAL(D_80000400[0]);
    D_hd_code_80358050[1] = VIRTUAL_TO_PHYSICAL(D_80000400[1]);
    D_hd_code_80358058 = VIRTUAL_TO_PHYSICAL(&func_init_8021ED00);
    gfxInitMicrocode();
    osWritebackDCacheAll();
    func_hd_code_8028FC10();
    if (!(sp2F & 1)) {
        g_nextGameState = 0x0800000000000000;
    } else if (D_hd_code_802FDBD0 != 0) {
        g_nextGameState = 0x0000080000000000;
    } else if (D_hd_code_802FDBD4 != 0) {
        g_nextGameState = 0x0040000000000000;
    } else {
        g_nextGameState = 0x10;
    }
    for(sp44 = 0x1FF; sp44 >= 0; sp44--) {
        g_Thread3Stack[sp44] = 0x1122334455667788;
    }
}

void func_hd_code_80255D34(void) {
  u8 sp1F;
  s32 sp18;

  sp1F = 0;
  for(sp18 = 0x1FF; sp18 >= 0 && sp1F == 0; sp18--) {
    if (g_Thread3Stack[sp18] != 0x1122334455667788) {
      sp1F = 1;
      rmonPrintf("stack end =%d\n", sp18);
    }
  }
}

void hdPrepareStateTransition(void) {
    s32 sp2C;
    s32 pad;
    s32 sp24;
    Gfx* sp20;

    sp24 = (s32)&D_788000 - (s32)&D_787F40;
    osViBlack(TRUE);
    D_hd_code_80364A70 = func_hd_code_80261A44(g_nextGameState);
    osWritebackDCacheAll();
    osInvalDCache(0x80000000, 0x400000);
    D_hd_code_803649F4 = 0;
    D_hd_code_80358068 = 0;
    D_hd_code_80358064 = 0;
    g_frameCount = 0;
    D_hd_code_8035805C = 0;
    D_hd_code_80367BD0.unk6 = 0;
    func_hd_code_8026A8BC();
    func_hd_code_8026A974();
    func_hd_code_8028AE88();
    func_hd_code_8028B720();
    D_hd_code_8035806C = &D_hd_code_803FF600;
    INITIATE_DMA(&D_787F40, &D_hd_code_803FF600, &sp24, 0xA, 0, 2);
    sp2C = ((s32)&D_788000 - (s32)&D_787F40) + (s32)&D_hd_code_803FF600;
    rmonPrintf("Static end = 0x%x, space=0x%x (%d) bytes\n", sp2C, 0x80400000 - (s32)sp2C, 0x80400000 - (s32)sp2C);
    D_hd_code_80358078 = 0;
    func_hd_code_802558C8(D_hd_code_803156F8[D_hd_code_8035805C].dp, &D_hd_code_80358078);
    func_hd_code_802559F8(D_hd_code_803156F8[D_hd_code_8035805C].dp, &D_hd_code_80358078);
    g_heap = (u8*)VRAM_HEAP_START;
    hdAlignPointer(&g_heap, 0x10);
    g_gfxTaskOutputBuffer = (Gfx*)g_heap;
    g_heap += 0x1400 * 8;
    if ((D_hd_code_802E8F94[g_currentLevel].unk0 == 2) && !(g_nextGameState & 0x0000100000000002)) {
        rmonPrintf("Allocating ghost buffer memory\n");
        g_heap += 0x4000 * 8;
    }
    D_hd_code_803B9888 = 0;
    func_hd_code_802A0700();
    g_shadows.shadows = (struct Shadow* ) ((s32) (D_hd_code_80358088 + 0x40) & ~0x3F);
    func_hd_code_80278E3C();
    D_hd_code_803643D9 = 0;
    D_hd_code_803643DA = 0;
    D_hd_code_803643D8 = 0;
    D_hd_code_803643D6 = 0;
    D_hd_code_803643D7 = 0;
    D_hd_code_802E8BD8 = 0;
    D_hd_code_802E8BD4 = 0;
    D_hd_code_802E8BD0 = 0;
    D_hd_code_8036EB99 = 0;
    D_hd_code_803669B4 = 0;
    if (g_nextGameState & 0xC9FD8FE7FBFFC0B0) {
        func_hd_code_8028B3E0();
    }
    func_hd_code_80297530(g_currentLevel);
    func_hd_code_80272C50();
    if (g_nextGameState == 0x40000000000) {
        func_hd_front_end_801F7850();
    }
    sp20 = g_heap;
    func_hd_code_8026B118(0);
    rmonPrintf("Yoshi windows allocated %d bytes, %x\n", (u32)g_heap - (u32)sp20, g_heap);
    g_vehiclesEnd = g_vehicles;
    func_hd_code_8028A42C();
    func_hd_code_802592F0();
    D_hd_code_8039CAA2 = 0;
}

//region Level Addresses
extern u8 lagp_ROM_START;
extern u8 chimp_ROM_START;
extern u8 valley_ROM_START;
extern u8 fact_ROM_START;
extern u8 dip_ROM_START;
extern u8 beetle_ROM_START;
extern u8 bonus1_ROM_START;
extern u8 bonus2_ROM_START;
extern u8 bonus3_ROM_START;
extern u8 level9_ROM_START;
extern u8 level10_ROM_START;
extern u8 level11_ROM_START;
extern u8 level12_ROM_START;
extern u8 level13_ROM_START;
extern u8 level14_ROM_START;
extern u8 level15_ROM_START;
extern u8 level16_ROM_START;
extern u8 level17_ROM_START;
extern u8 level18_ROM_START;
extern u8 level19_ROM_START;
extern u8 level20_ROM_START;
extern u8 level21_ROM_START;
extern u8 level22_ROM_START;
extern u8 level23_ROM_START;
extern u8 level24_ROM_START;
extern u8 level25_ROM_START;
extern u8 level26_ROM_START;
extern u8 level27_ROM_START;
extern u8 level28_ROM_START;
extern u8 level29_ROM_START;
extern u8 level30_ROM_START;
extern u8 level31_ROM_START;
extern u8 level32_ROM_START;
extern u8 level33_ROM_START;
extern u8 level34_ROM_START;
extern u8 level35_ROM_START;
extern u8 level36_ROM_START;
extern u8 level37_ROM_START;
extern u8 level38_ROM_START;
extern u8 level39_ROM_START;
extern u8 level40_ROM_START;
extern u8 level41_ROM_START;
extern u8 level42_ROM_START;
extern u8 level43_ROM_START;
extern u8 level44_ROM_START;
extern u8 level45_ROM_START;
extern u8 level46_ROM_START;
extern u8 level47_ROM_START;
extern u8 level48_ROM_START;
extern u8 level49_ROM_START;
extern u8 level50_ROM_START;
extern u8 level51_ROM_START;
extern u8 level52_ROM_START;
extern u8 level53_ROM_START;
extern u8 level54_ROM_START;
extern u8 level55_ROM_START;
extern u8 level56_ROM_START;
extern u8 level57_ROM_START;
extern u8 level58_ROM_START;
extern u8 level59_ROM_START;
extern u8 worldtextures_ROM_START;
//endregion

void LoadLevel(u32 level, void* arg1, s32* arg2) {
    u8* levelRomPosition;

    switch (level) {
    case 0x1:
        levelRomPosition = &lagp_ROM_START;
        *arg2 = &chimp_ROM_START - &lagp_ROM_START;
        break;
    case 0x0:
        levelRomPosition = &chimp_ROM_START;
        *arg2 = &valley_ROM_START - &chimp_ROM_START;
        break;
    case 0x2:
        levelRomPosition = &valley_ROM_START;
        *arg2 = &fact_ROM_START - &valley_ROM_START;
        break;
    case 0x3:
        levelRomPosition = &fact_ROM_START;
        *arg2 = &dip_ROM_START - &fact_ROM_START;
        break;
    case 0x4:
        levelRomPosition = &dip_ROM_START;
        *arg2 = &beetle_ROM_START - &dip_ROM_START;
        break;
    case 0x5:
        levelRomPosition = &beetle_ROM_START;
        *arg2 = &bonus1_ROM_START - &beetle_ROM_START;
        break;
    case 0x6:
        levelRomPosition = &bonus1_ROM_START;
        *arg2 = &bonus2_ROM_START - &bonus1_ROM_START;
        break;
    case 0x7:
        levelRomPosition = &bonus2_ROM_START;
        *arg2 = &bonus3_ROM_START - &bonus2_ROM_START;
        break;
    case 0x8:
        levelRomPosition = &bonus3_ROM_START;
        *arg2 = &level9_ROM_START - &bonus3_ROM_START;
        break;
    case 0x9:
        levelRomPosition = &level9_ROM_START;
        *arg2 = &level10_ROM_START - &level9_ROM_START;
        break;
    case 0xA:
        levelRomPosition = &level10_ROM_START;
        *arg2 = &level11_ROM_START - &level10_ROM_START;
        break;
    case 0xB:
        levelRomPosition = &level11_ROM_START;
        *arg2 = &level12_ROM_START - &level11_ROM_START;
        break;
    case 0xC:
        levelRomPosition = &level12_ROM_START;
        *arg2 = &level13_ROM_START - &level12_ROM_START;
        break;
    case 0xD:
        levelRomPosition = &level13_ROM_START;
        *arg2 = &level14_ROM_START - &level13_ROM_START;
        break;
    case 0xE:
        levelRomPosition = &level14_ROM_START;
        *arg2 = &level15_ROM_START - &level14_ROM_START;
        break;
    case 0xF:
        levelRomPosition = &level15_ROM_START;
        *arg2 = &level16_ROM_START - &level15_ROM_START;
        break;
    case 0x10:
        levelRomPosition = &level16_ROM_START;
        *arg2 = &level17_ROM_START - &level16_ROM_START;
        break;
    case 0x11:
        levelRomPosition = &level17_ROM_START;
        *arg2 = &level18_ROM_START - &level17_ROM_START;
        break;
    case 0x12:
        levelRomPosition = &level18_ROM_START;
        *arg2 = &level19_ROM_START - &level18_ROM_START;
        break;
    case 0x13:
        levelRomPosition = &level19_ROM_START;
        *arg2 = &level20_ROM_START - &level19_ROM_START;
        break;
    case 0x14:
        levelRomPosition = &level20_ROM_START;
        *arg2 = &level21_ROM_START - &level20_ROM_START;
        break;
    case 0x15:
        levelRomPosition = &level21_ROM_START;
        *arg2 = &level22_ROM_START - &level21_ROM_START;
        break;
    case 0x16:
        levelRomPosition = &level22_ROM_START;
        *arg2 = &level23_ROM_START - &level22_ROM_START;
        break;
    case 0x17:
        levelRomPosition = &level23_ROM_START;
        *arg2 = &level24_ROM_START - &level23_ROM_START;
        break;
    case 0x18:
        levelRomPosition = &level24_ROM_START;
        *arg2 = &level25_ROM_START - &level24_ROM_START;
        break;
    case 0x19:
        levelRomPosition = &level25_ROM_START;
        *arg2 = &level26_ROM_START - &level25_ROM_START;
        break;
    case 0x1A:
        levelRomPosition = &level26_ROM_START;
        *arg2 = &level27_ROM_START - &level26_ROM_START;
        break;
    case 0x1B:
        levelRomPosition = &level27_ROM_START;
        *arg2 = &level28_ROM_START - &level27_ROM_START;
        break;
    case 0x1C:
        levelRomPosition = &level28_ROM_START;
        *arg2 = &level29_ROM_START - &level28_ROM_START;
        break;
    case 0x1D:
        levelRomPosition = &level29_ROM_START;
        *arg2 = &level30_ROM_START - &level29_ROM_START;
        break;
    case 0x1E:
        levelRomPosition = &level30_ROM_START;
        *arg2 = &level31_ROM_START - &level30_ROM_START;
        break;
    case 0x1F:
        levelRomPosition = &level31_ROM_START;
        *arg2 = &level32_ROM_START - &level31_ROM_START;
        break;
    case 0x20:
        levelRomPosition = &level32_ROM_START;
        *arg2 = &level33_ROM_START - &level32_ROM_START;
        break;
    case 0x21:
        levelRomPosition = &level33_ROM_START;
        *arg2 = &level34_ROM_START - &level33_ROM_START;
        break;
    case 0x22:
        levelRomPosition = &level34_ROM_START;
        *arg2 = &level35_ROM_START - &level34_ROM_START;
        break;
    case 0x23:
        levelRomPosition = &level35_ROM_START;
        *arg2 = &level36_ROM_START - &level35_ROM_START;
        break;
    case 0x24:
        levelRomPosition = &level36_ROM_START;
        *arg2 = &level37_ROM_START - &level36_ROM_START;
        break;
    case 0x25:
        levelRomPosition = &level37_ROM_START;
        *arg2 = &level38_ROM_START - &level37_ROM_START;
        break;
    case 0x26:
        levelRomPosition = &level38_ROM_START;
        *arg2 = &level39_ROM_START - &level38_ROM_START;
        break;
    case 0x27:
        levelRomPosition = &level39_ROM_START;
        *arg2 = &level40_ROM_START - &level39_ROM_START;
        break;
    case 0x28:
        levelRomPosition = &level40_ROM_START;
        *arg2 = &level41_ROM_START - &level40_ROM_START;
        break;
    case 0x29:
        levelRomPosition = &level41_ROM_START;
        *arg2 = &level42_ROM_START - &level41_ROM_START;
        break;
    case 0x2A:
        levelRomPosition = &level42_ROM_START;
        *arg2 = &level43_ROM_START - &level42_ROM_START;
        break;
    case 0x2B:
        levelRomPosition = &level43_ROM_START;
        *arg2 = &level44_ROM_START - &level43_ROM_START;
        break;
    case 0x2C:
        levelRomPosition = &level44_ROM_START;
        *arg2 = &level45_ROM_START - &level44_ROM_START;
        break;
    case 0x2D:
        levelRomPosition = &level45_ROM_START;
        *arg2 = &level46_ROM_START - &level45_ROM_START;
        break;
    case 0x2E:
        levelRomPosition = &level46_ROM_START;
        *arg2 = &level47_ROM_START - &level46_ROM_START;
        break;
    case 0x2F:
        levelRomPosition = &level47_ROM_START;
        *arg2 = &level48_ROM_START - &level47_ROM_START;
        break;
    case 0x30:
        levelRomPosition = &level48_ROM_START;
        *arg2 = &level49_ROM_START - &level48_ROM_START;
        break;
    case 0x31:
        levelRomPosition = &level49_ROM_START;
        *arg2 = &level50_ROM_START - &level49_ROM_START;
        break;
    case 0x32:
        levelRomPosition = &level50_ROM_START;
        *arg2 = &level51_ROM_START - &level50_ROM_START;
        break;
    case 0x33:
        levelRomPosition = &level51_ROM_START;
        *arg2 = &level52_ROM_START - &level51_ROM_START;
        break;
    case 0x34:
        levelRomPosition = &level52_ROM_START;
        *arg2 = &level53_ROM_START - &level52_ROM_START;
        break;
    case 0x35:
        levelRomPosition = &level53_ROM_START;
        *arg2 = &level54_ROM_START - &level53_ROM_START;
        break;
    case 0x36:
        levelRomPosition = &level54_ROM_START;
        *arg2 = &level55_ROM_START - &level54_ROM_START;
        break;
    case 0x37:
        levelRomPosition = &level55_ROM_START;
        *arg2 = &level56_ROM_START - &level55_ROM_START;
        break;
    case 0x38:
        levelRomPosition = &level56_ROM_START;
        *arg2 = &level57_ROM_START - &level56_ROM_START;
        break;
    case 0x39:
        levelRomPosition = &level57_ROM_START;
        *arg2 = &level58_ROM_START - &level57_ROM_START;
        break;
    case 0x3A:
        levelRomPosition = &level58_ROM_START;
        *arg2 = &level59_ROM_START - &level58_ROM_START;
        break;
    case 0x3B:
        levelRomPosition = &level59_ROM_START;
        *arg2 = &worldtextures_ROM_START - &level59_ROM_START;
    }
    INITIATE_DMA(levelRomPosition, arg1, arg2, 0xCU, 0xA, 1);
}

void hdInitLevel(s32* pakBuffer) {
    s32 sp4C;
    s32 sp48;
    struct Shadow* sp44;
    u8 sp43;
    Gfx* sp3C;

    D_hd_code_80364A68 = 0;
    D_hd_code_80364A69 = 0;
    D_hd_code_80364A6A = 0;
    D_hd_code_80364A6B = 0;
    D_hd_code_80364A6C = 0;
    D_hd_code_80364A6D = 0;
    D_hd_code_803649E8 = 0;
    D_hd_code_803649EC = 0;
    g_shadows.firstFree = g_shadows.shadows;
    D_hd_code_80364AA8 = (s32)D_hd_code_802E8F94[g_currentLevel].unk0;
    D_hd_code_802E8BE4 = 0;
    D_hd_code_802E8BE8 = 0;
    D_hd_code_803643E0 = 0;
    D_hd_code_803643E4 = 0;
    D_hd_code_803643E8 = 0;
    D_hd_code_8036443C = 0;
    D_hd_code_80364414 = 135.0f;
    D_hd_code_80364418 = 135.0f;
    D_hd_code_8036441C = 0;
    D_hd_code_8036441D = 0;
    D_hd_code_80364420 = 0xBB8;
    D_hd_code_80364434 = 1;
    D_hd_code_803A7430 = 0;
    D_hd_code_803649EE = 0;
    D_hd_code_80364A84 = 0;
    D_hd_code_80364456 = 0;

    if (frontEndPresent) {
        if (g_pakBusy != 0) {
            rmonPrintf(ASSERT_MESSAGE, "!pakBusy", "hd.c", 0x1042);
        }
        if (D_hd_front_end_80219F58 != 0) {
            rmonPrintf(ASSERT_MESSAGE, "MQ_IS_EMPTY(&pakToGameMessageQ)", "hd.c", 0x1043);
        }
        osScRemoveClient(&sc, &D_hd_front_end_80218EE0);
        osDestroyThread(&D_hd_front_end_80218D30);
    }

    D_hd_code_8039CA62 = 0;
    D_hd_code_8039CA61 = 0;
    if (D_hd_code_80364AA8 == 2 && (g_nextGameState == 0x2000)) {
        if (D_hd_code_8039CA60 == 0) {
            func_hd_code_80294E30();
        }
        func_hd_code_80294E88();
        func_hd_code_80294EB8();
    }
    LoadLevel(g_currentLevel, g_heap, &sp48);
    D_hd_code_80358074 = (Gfx*)g_heap;
    g_heap += sp48;
    hdAlignPointer(&g_heap, 0x10);

    statsLoadLevelStats();
    targetMarkersReset();
    func_hd_code_802621DC(g_currentLevel);
    func_hd_code_80262238(g_currentLevel);
    missionsSetLevelFOV(g_currentLevel);
    D_hd_code_80367BFF = 0;
    func_hd_code_802CE840();
    rmonPrintf("enter initlevel game_mode=%d loop_done=%d\n", yoshiFFS(g_currentGameState), yoshiFFS(g_nextGameState));
    sp3C = g_heap;
    func_hd_code_802A1674(D_hd_code_80358074, pakBuffer);
    rmonPrintf("exit initlevel allocated %d bytes, %x\n", (u32)g_heap - (u32)sp3C, g_heap);
    hdAllocDlBuffers();
    if (g_nextGameState != 2) {
        if(LEVEL_FINISHED(g_currentLevel)) {
            func_hd_code_802CF628();
        }
    }
    func_hd_code_802C1DD0(D_hd_code_80364AA8 == 0x20 || D_hd_code_80364AA8 == 0x80);
    func_hd_code_80262320(g_currentLevel);
    if (D_hd_code_80364410 != 0) {
        D_hd_code_80364A86 = func_hd_code_80272C5C(&D_hd_code_802E8BF4, 0, 1, 1, 1, 1.0f);
    }
    func_hd_code_802775C0();
    if (D_hd_code_80364A69 != 0) {
        func_hd_code_80286A00();
    }
    if (D_hd_code_80364A6B != 0) {
        func_hd_code_802873AC();
    }
    if (D_hd_code_80364A6D != 0) {
        func_hd_code_80287AE4();
    }
    func_hd_code_802821D0();
    func_hd_code_80282728();
    func_hd_code_80281A70(g_currentLevel);
    if (D_hd_code_802E8F94[g_currentLevel].unk0 == 1) {
        func_hd_code_80264C20(pakBuffer);
    }
    func_hd_code_80288220();
    func_hd_code_8027BE4C();
    func_hd_code_80292240();
    func_hd_code_8027E344(g_currentLevel);
    func_hd_code_802807D8(g_currentLevel);
    func_hd_code_80268664(g_currentLevel);
    func_hd_code_8026A988();
    sp44 = g_shadows.shadows;
    while (sp44 != g_shadows.firstFree) {
        sp4C = 0;
        sp43 = 0;
        while (sp43 == 0) {
            if (g_vehicles[sp4C].unk5C == sp44->unk1022) {
                sp43 = 1;
            } else {
                sp4C += 1;
            }
        }
        func_hd_code_80258544(sp44, sp44->unk1004, sp44->unk1010, sp44->unk100C, sp44->unk1000, g_vehicles[sp4C].unk54, g_vehicles[sp4C].unk0, g_vehicles[sp4C].unk4);
        gfxWaitForTask(GFX_TASK_ID_SHADOW);
        sp44++;
    }
    func_hd_code_802729F0((s32)g_nextGameState, g_currentLevel);
    D_hd_code_80364452 = 0x2000;
    D_hd_code_80364454 = 0x2000;
    D_hd_code_80364456 = 0;
    D_hd_code_803649ED = 0;
    D_hd_code_803643F8 = 0;
    D_hd_code_803643FC = 0;
    D_hd_code_80364400 = 0;
    D_hd_code_80364444 = 0.0f;
    D_hd_code_80364448 = 0.0f;
    D_hd_code_803649F8 = 1.0f;
    D_hd_code_80364A3C = 0;
    D_hd_code_80364A3D = 0;
    D_hd_code_80364A40 = 0;
    D_hd_code_80364A44 = 0;
    D_hd_code_80364A6F = 0;
    D_hd_code_80364AB4 = 0.0f;
    D_hd_code_80364AB8 = 1.0f;
    D_hd_code_80364ABC = 1.0f;
    D_hd_code_80364AC0 = 0;
    D_hd_code_803643E0 = D_hd_code_803ED808;
    D_hd_code_803643E4 = D_hd_code_803ED80C;
    D_hd_code_803643E8 = D_hd_code_803ED810;
    D_hd_code_802FDB14 = 0;
    if (D_hd_code_802E8BF8 != 0) {
        D_hd_code_803649F0 = g_statsNew.money;
    } else {
        D_hd_code_803649F0 = players[playerNumber].unk14;
    }
    D_hd_code_80364A5C = 0;
    D_hd_code_80364A58 = 0;
    if (D_hd_code_803669B4 != 0) {
        func_hd_code_8025BD98();
    }
    rmonPrintf("Level %d: mem_pool=0x%x, code seg=0x%x, space=%d bytes\n", (s32* ) g_currentLevel, g_heap, VRAM_HD_CODE, 0x8021ED00 - (s32)g_heap);
    if (D_hd_code_8039CAB7 != 0) {
        func_hd_code_802979E0(g_currentLevel);
    }
    func_hd_code_802A56C4();
    func_hd_code_802A5FA8();
}

void hdAllocDlBuffers(void) {
  s32 sp14;
  s32 sp10;
  s32 spC;
  s32 sp8;

  switch (g_currentLevel) {
    case 16:
    case 29:
      sp14 = 0x32;
      sp10 = 0x32;
      spC = 0x32;
      sp8 = 0xC8;
      break;
    case 17:
      sp14 = 0x32;
      sp10 = 0x32;
      spC = 0x32;
      sp8 = 0x32;
      break;
    case 11:
      sp14 = 0xBB8;
      sp10 = 0x32;
      spC = 0x32;
      sp8 = 0xC8;
      break;
    case 10:
      sp14 = 0x32;
      sp10 = 0x32;
      spC = 0x32;
      sp8 = 0x7D0;
      break;
    default:
      switch (D_hd_code_803BE739) {
        case 0:
          sp14 = 0x1770;
          sp10 = 0x1388;
          spC = 0x64;
          sp8 = 0x7D0;
          break;
        case 1:
          sp14 = 0x3E8;
          sp10 = 0x3E8;
          spC = 0x64;
          sp8 = 0x7D0;
          break;
      }
      break;
  }
  D_hd_code_80358030[0] = g_heap;
  g_heap += sp14 * 8;
  D_hd_code_80358038[0] = g_heap;
  g_heap += sp10 * 8;
  D_hd_code_80358040[0] = g_heap;
  g_heap += spC * 8;
  D_hd_code_80358048[0] = g_heap;
  g_heap += sp8 * 8;
  D_hd_code_80358030[1] = g_heap;
  g_heap += sp14 * 8;
  D_hd_code_80358038[1] = g_heap;
  g_heap += sp10 * 8;
  D_hd_code_80358040[1] = g_heap;
  g_heap += spC * 8;
  D_hd_code_80358048[1] = g_heap;
  g_heap += sp8 * 8;
}

// Align a bump-allocator pointer up to an arg1-byte boundary
void hdAlignPointer(u8** arg0, s32 arg1) {
  s32 sp4;

  sp4 = (s32) *arg0 % arg1;
  if (sp4 != 0) {
    sp4 = arg1 - sp4;
  }
  *arg0 += sp4;
}

f32 hdSin(f32 value) {
  return sinf(value);
}

f32 hdCos(f32 value) {
  return cosf(value);
}
