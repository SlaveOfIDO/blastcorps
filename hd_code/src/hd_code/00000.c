#include <PR/gu.h>
#include <ultra64.h>

#include "common.h"
#include "structs.h"
#include "variables.h"
#include "macros.h"
#include "functions.h"

// BSS begin
u8 D_hd_code_8030F660;
s32 D_hd_code_8030F664;
struct UnknownStruct8030F668 D_hd_code_8030F668;
u8 bss_pad_1[0x80310820 - 0x8030F66C];
OSThread D_80310820; // bss
void* D_803109D0; // bss
OSThread D_80310BD0; // bss
s64 D_80310D80[0x200]; // bss
OSMesgQueue D_80314D80; // bss
OSMesg D_80314D98; // bss


s16 D_8036BB18;
u64 D_80364A88;
u64 D_80364AA0;
u64 D_hd_code_80364A90;
u64 D_80364A98;
u64 D_80364AD0;
u64 D_80364A98;
u64 D_80364A98;
u64 D_80364A98; // bss or data?
u8 D_8039CA60;
s32 D_80000300;
struct Model1 D_2000000;
u64 D_hd_code_803649D8;



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
  func_hd_code_80270AE0(sp28);
  osCreateThread(&D_80310820, 1, Thread1, NULL, &D_803109D0 + 0x80, 0xA);
  osStartThread(&D_80310820);
}

void Thread1(void* arg0) {
  u8 pad[2];
  osDpSetStatus(4U);
  osCreatePiManager(0x96, &D_80314D80, &D_80314D98, 0xC2);
  osCreateThread(&D_80310BD0, 3, Thread3, arg0, D_80310D80 + 0x400, 0xA);
  osStartThread(&D_80310BD0);
  if (D_hd_code_802FA254 == 0) {
    osStartThread(&D_80310BD0);
  }
  osSetThreadPri(0, 0);
  while(1);
}

void Thread3(void* arg0) {
    s32 sp64;
    s32 sp60;
    s32 sp5C;
    u8 sp5B;
    s32 sp54;

    func_hd_code_80255AD0();
    while (1)
    {
      D_80364A70 = 0;
      do {
        func_hd_code_8029A7E4("game mode switch from %d to %d\n", func_hd_code_8026F92C(D_hd_code_80364A90), func_hd_code_8026F92C(D_80364A98));

        D_80364AA0 = 0ULL;

        // MASTER SWITCH BEGIN
        switch (D_80364A98)
        {
          case 0x0000000000000020:
          {
            func_hd_code_80255DC8();
            func_801EF380(2);
            break;
          }
          case 0x0000000000000010:
          {
            func_hd_code_80255DC8();
            func_801EF380(1);
            sp60 = D_803156C4;
            if ((u32) (D_803156C4 - D_803156C4) < 0xFU) {
              do {

              } while ((u32) (D_803156C4 - sp60) < 0xFU);
            }
            break;
          }
          case 0x0000000100000000:
          {
            func_801F6F18();
            func_hd_code_8026AF6C(0x8012);
            D_80364A70 = func_hd_code_80261A44(D_80364A98);
            break;
          }
          case 0x0000080000000000:
          {
            func_hd_code_80255DC8();
            func_hd_code_8025D184();
            func_80200714(1);
            osSendMesg(&D_80219EF8, 0x01000001, 1);
            func_hd_code_8026AF6C(0x8011);
            break;
          }
          case 0x0000000000010000:
          {
            D_80364A70 = func_hd_code_80261A44(D_80364A98);
            func_hd_code_8025D184();
            func_801EA4B8();
            func_801E8DCC(playerNumber);
            func_hd_code_8026AF6C(0x800A);
            break;
          }
          case 0x0000000010000000:
          {
            osSendMesg(&D_80219EF8, 0x01000001, 1);
            func_801E8DCC(4U);
            func_hd_code_8026AF6C(0x8011);
            break;
          }
          case 0x0020000000000000:
          {
            func_hd_code_802609D0();
            func_hd_code_80255DC8();
            func_hd_code_802A0700();
            func_hd_code_8025D184();
            func_80200714(1);
            osSendMesg(&D_80219EF8, 0x0100000F, 1);
            osRecvMesg(&D_80219F50, &sp5C, 1);
            if ((sp5C != 0) || (D_8039C541 != 0))
            {
              D_hd_code_802E8BF8 = 1;
            }
            else
            {
              D_hd_code_802E8BF8 = 0;
            }
            D_8039C541 = 0;
            if (D_hd_code_802E8BF8 == 0)
            {
              func_801E8C40(4U);
              D_80364AA0 = 0x10000000;
            }
            else
            {
              playerNumber = 0U;
              D_80364AE9 = 0U;
              D_80364AEA = 0,
              osSendMesg(&D_80219EF8, 0x01000010, 1);
              osRecvMesg(&D_80219F50, &D_8039C4B4, 1);
              if (D_8039C4B4 == 0)
              {
                func_hd_code_8029A7E4("NO EE PRESENT! - USING DUMMY EE\n");
              }
              osSendMesg(&D_80219EF8, 0x01000006, 1);
              osRecvMesg(&D_80219F50, &sp5C, 1);
              if (sp5C == 0)
              {
                sp5C = func_80201E80();
              }
              if (sp5C != 0)
              {
                func_801EA108(playerNumber, 1, 1);
                D_80364AA0 = 0x40000;
              }
              else
              {
                D_80365060[playerNumber] = 1;
                D_80364AA0 = 0x4000;
              }
            }
            break;
          }
          case 0x0004000000000000:
          {
            func_hd_code_80255DC8();
            func_hd_code_802A0700();
            func_hd_code_8025D184();
            func_80200714(4);
            func_801E8C40(4U);
            func_hd_code_8026AF6C(0x8038);
            break;
          }
          case 0x0400000000000000:
          {
            D_hd_code_802E8BEC = -1;
            D_hd_code_802E8BF0 = 1;
            D_80365065 = 0;
            D_80364AA0 = 0x2;
            D_8039C541 = 0;
            func_801ECE9C();
            break;
          }
          case 0x0000000000000002:
          {
              switch(D_hd_code_802E8BEC) {
                  case 1:
                  case 3:
                  case 4:
                  case 6:
                  if(D_hd_code_80364A90 == 0x2) {
                      D_80364A98 = 0x1000000000000;
                      func_hd_code_80255DC8();
                      func_80200714(7);
                      func_80201240(D_80364AC4 & 3);
                      func_hd_code_8026AF6C(0x8035);
                      func_801E8C40(D_80364AC4 & 3);
                      D_80364AC4 += 1;
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
                      D_8039CAA0 = 0;
                      func_hd_code_80255DC8();
                      func_hd_code_8025D184();
                      func_hd_code_80295E50();
                      func_hd_code_8025B9D0(D_hd_code_802E8BEC, &levelno);
                      if (D_hd_code_802E8BEC == 0) {
                        func_hd_code_8029A130();
                      }
                      func_hd_code_80256A34(NULL);
                      break;
                  }
              }
            break;
          }
          case 0x0000000000004000:
          {
            if (playerNumber != D_80364AEA) {
              D_80364AE9 = (u8) D_80364AEA;
              playerNumber = (u8) D_80364AEA;
            }
            func_hd_code_8028B3E0();
            func_hd_code_8029A7E4("World screen centred on level %d\n", levelno);
            playerNumber = (u8) D_80364AEA;
            func_801ECE9C();
            if (D_80365065 == 0) {
              D_80365065 = 1;
              D_80364A87 = 0;
              D_803643D5 = 0;
              func_801FE018(8);
              levelno = D_80364AF0[playerNumber].unk8;
              func_hd_code_8029A7E4("going to level %d\n", levelno);
            }

            if (D_8039CA60 = 0, ((D_80364AF0[playerNumber].unk18[levelno] > 0 && D_80364AF0[playerNumber].unk18[levelno] < 6)?1:0)) {
                if(levelno > 0x2A && levelno < 0x2E) {
                    if(!((D_80364AF0[playerNumber].unk18[levelno+1] > 0 && D_80364AF0[playerNumber].unk18[levelno+1] < 6)?1:0)) {
                        levelno++;
                    }
                }
            }
            func_hd_code_80255DC8();
            func_801ECC8C();
            osViBlack(1);
            func_hd_code_802A0700();
            func_801F8530(levelno);
            break;
          }
          case 0x0000800000000000:
          {
            D_80364A70 = func_hd_code_80261A44(D_80364A98);
            break;
          }
          case 0x0000000400000000:
          {
            func_hd_code_8026AF6C(0x8013);
            break;
          }
          case 0x0800000000000000:
          {
            func_hd_code_80255DC8();
            func_80200714(1);
            func_hd_code_8025D184();
            func_hd_code_8026AF6C(0x8059);
            break;
          }
          case 0x0000040000000000:
          {
            func_hd_code_80255DC8();
            func_80200714(3);
            func_801E8C40(playerNumber);
            func_hd_code_8025D184();
            D_8021A830 = D_hd_code_80364A90;
            func_hd_code_8026AF6C(0x8016);
            break;
          }
          case 0x0200000000000000:
          {
            func_801E8EB8(playerNumber, 1);
            func_801F8228();
            func_hd_code_8026AF6C(0x8016);
            D_80364A98 = 0x40000000000;
            break;
          }
          case 0x0000000000002000:
          {
            func_hd_code_80255DC8();
            if (D_hd_code_802E8F94[levelno].unk0 != 1) {
              func_hd_code_80256A34(NULL);
              func_hd_code_80285A78(&D_8036EA70, &D_8036EA60);
              func_hd_code_80285A78(&D_8036EA70, &D_8036EA80);
              D_hd_code_802E8BD8 = 1;
            } else {
              if (((D_80364AF0[playerNumber].unk18[levelno] > 0 && D_80364AF0[playerNumber].unk18[levelno] < 6)?1:0)) {
                func_hd_code_80256A34(&pakBuffer);
              } else {
                func_hd_code_80256A34(NULL);
              }
              func_hd_code_80285A78(&D_8036EA70, &D_8036EA60);
              func_hd_code_80285A78(&D_8036EA70, &D_8036EA80);
              D_80364AA0 = 4;
            }
            break;
          }
          case 0x0000000000000004:
          {
            switch (D_hd_code_80364A90)
            {
              case 0x1000000000:
                func_hd_code_8026101C();
                func_hd_code_80261E9C(D_80364A98);
                D_hd_code_802E8BD4 = 1;
                break;
              case 0x100:
                D_hd_code_80364412 = 1;
                break;
              case 0x2000:
              {
                if (D_hd_code_802E8F94[levelno].unk0 != 1) {
                  D_80364A70 = func_hd_code_80261A44(D_80364A98);
                }

                D_hd_code_802E8BD4 = 1;\
                D_hd_code_802E8BD4 &= !func_hd_code_8026AD30(0x52);\
                D_hd_code_802E8BD4 &= !func_hd_code_8026AD30(0x56);\
                if (((D_80364AF0[playerNumber].unk18[levelno] > 0 && D_80364AF0[playerNumber].unk18[levelno] < 6)?1:0) && D_hd_code_802E8F94[levelno].unk0 == 1) \
                  D_hd_code_802E8BD4 &= !func_hd_code_8026AD30(0x55);\
                else \
                  D_hd_code_802E8BD4 &= !func_hd_code_8026AD30(0x57);

                D_hd_code_802E8BD8 = !D_hd_code_802E8BD4;
                func_hd_code_8029A7E4("Unpause at start = %d\n", D_hd_code_802E8BD4);
                D_80364A58 = D_803156C0;
                D_80358064 = 0;
                func_hd_code_8025BB38();
                func_hd_code_8029A7E4("snew ip=%8d : tc=%5d : bd=%2d : cr=%2d : rt=%3d : coin=%1d : bdn=%1d\n", D_8036EA70, D_8036EA74, D_8036EA78, (s32) D_8036EA79, (s32) D_8036EA7C, (s32) D_8036EA7A, (s32) D_8036EA7B);
                func_hd_code_8029A7E4("sold ip=%8d : tc=%5d : bd=%2d : cr=%2d : rt=%3d : coin=%1d : bdn=%1d\n", D_8036EA60, D_8036EA64, D_8036EA68, (s32) D_8036EA69, (s32) D_8036EA6C, (s32) D_8036EA6A, (s32) D_8036EA6B);
                func_hd_code_8029A7E4("sres ip=%8d : tc=%5d : bd=%2d : cr=%2d : rt=%3d : coin=%1d : bdn=%1d\n", D_8036EA80, D_8036EA84, D_8036EA88, (s32) D_8036EA89, (s32) D_8036EA8C, (s32) D_8036EA8A, (s32) D_8036EA8B);
                func_hd_code_8029A7E4("srs2 ip=%8d : tc=%5d : bd=%2d : cr=%2d : rt=%3d : coin=%1d : bdn=%1d\n", D_8036EA90,  D_8036EA94, D_8036EA98, (s32) D_8036EA99, (s32) D_8036EA9C, (s32) D_8036EA9A, (s32) D_8036EA9B);
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
          case 0x0000000000000080:
          {
            sp5B = 0;
            switch (D_hd_code_80364A90)
            {
              case 0x100000000000:
                func_hd_code_8028B3E0();
                D_80364A70 = func_hd_code_80261A44(D_80364A98);
              case 0x4000:
                sp5B = func_hd_code_80285814();
                break;

              case 0x40000000000:
              case 0x80000000000000:
              case 0x0100000000000000:
              {
                if (playerNumber != D_80364AE9) {
                  D_80364AE9 = playerNumber,
                  func_hd_code_8029A7E4("switching to new player ...........\n");
                  func_hd_code_80285814();
                }
                break;
              }

            }
            func_hd_code_80255DC8();
            if (sp5B != 0) {
              osSendMesg(&D_80219EF8, (levelno << 8) | 0xD | (playerNumber << 0x10), 1);
            }

            D_8020C070[D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)]].unkE + D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)]].unk10 - 2].unk0 &= ~1;
            D_8020C070[D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)]].unkE + D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)]].unk10 - 2].unk0 |= 0x800;

            func_hd_code_8026B8F8();
            func_hd_code_8026AF6C(D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)] | 0x8000);

            D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)]].unk18 =
              D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)]].unkE + D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)]].unk10 - 3;

            D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)]].unk8 &= ~8;

            func_hd_code_80285A78(&D_8036EA70, &D_8036EA60);
            D_80315438 = func_801EE800(&D_80364A60, 1, 0),
            func_801E8C40(playerNumber);
            func_801EC30C(D_80315438);
            func_801EC288(D_80315438);
            func_80200714(1);
            D_80364A71 = func_801EF1E0();
            if (D_80364A71 != -1) {
              func_801F55D8();
            }
            break;
          }
          case 0x0000000000000800:
          {
            func_hd_code_80255DC8();
            if (D_hd_code_80364A90 == 0x4000) {
              osRecvMesg(&D_80219F50, NULL, 1);
            }
            osViBlack(1);
            func_hd_code_80256A34(NULL);
            func_hd_code_802661EC();
            if (levelno == 0x32) {
              func_hd_code_8026AF6C(0x8024);
            }
            break;
          }
          case 0x0000000040000000:
          {
            func_hd_code_80255DC8();
            sp54 = D_803156C4;
            if ((u32)(D_803156C4 - D_803156C4) < 0xFU)
            {
              do
              {

              } while ((u32)(D_803156C4 - sp54) < 0xFU);
            }
            func_801ED790();
            func_80200714(3);
            D_80364A71 = func_801EF1E0();
            if (D_80364A71 != -1)
            {
              func_801F55D8();
            }
            func_801E8C40(playerNumber);
            func_801EC30C(D_80315438);
            break;
          }
          case 0x0000000008000000:{
            switch (D_hd_code_80364A90)
            {
              case 0x40:
              case 0x400:
              case 0x20000000:
              {
                func_hd_code_80255DC8();
                func_80200714(1);
                D_80364A71 = func_801EF1E0();
                if (D_80364A71 != -1)
                {
                  func_801F55D8();
                }
                func_801E8C40(playerNumber);
                func_hd_code_80285A78(&D_8036EA90, &D_8036EA70);
                D_80315438 = func_801EE800(&D_80364A60, 1, 0);
                func_801EC30C(D_80315438);
                func_801EC288(D_80315438);
                break;
              }
              case 0x40000000:
                D_80364A70 = func_hd_code_80261A44(D_80364A98);
                break;

              case 0x40000000000:
              case 0x80000000000000:
              case 0x0100000000000000:
              {
                if (playerNumber != D_80364AE9)
                {
                  func_hd_code_8029A7E4(
                    "switching to new player ...........\n");
                  D_80364AE9 = (u8)playerNumber;
                  D_803643D5 = 0;
                  func_hd_code_80285814();
                }
                func_hd_code_80255DC8();
                D_80364A71 = func_801EF1E0();
                if (D_80364A71 != -1)
                {
                  func_801F55D8();
                }
                func_801E8C40(playerNumber);
                D_80315438 = func_801EE800(&D_80364A60, 1, 0);
                func_80200714(1);
                func_801EC30C(D_80315438);
                func_801EC288(D_80315438);
                break;
              }

              default:
              {
                if (saveIt[playerNumber] && saveIt[playerNumber] != levelno + 1)
                {
                  func_hd_code_8029A7E4("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "!saveIt[playerNumber] || saveIt[playerNumber]==levelno+1", "./master_switch.c", 0x1E8U);
                }
                saveIt[playerNumber] = levelno + 1;
                if (D_hd_code_803643D7 != 0)
                {
                  func_hd_code_802C1DD0(D_hd_code_802E8F94[levelno].unk0 == 0x20 || D_hd_code_802E8F94[levelno].unk0 == 0x80);
                }

                D_803643D5 = !((D_80364AF0[playerNumber].unk18[levelno] > 0 && D_80364AF0[playerNumber].unk18[levelno] < 6)?1:0);

                if (playerNumber == D_80364AEA) D_80364A87 |= D_803643D5;


                if ((D_80364AA8 == 1) && (D_803643D5 == 0))
                {
                  for (sp64 = 0; sp64 < 0x40; sp64++)
                  {
                    D_8039C4F8[sp64] = pakBuffer[sp64];
                  }
                }
                func_hd_code_802CF5B0();
                func_hd_code_80297960();
                if (D_80364AA8 == 1)
                {
                  if (recordStatus(&pakBuffer) >= 0x3D)
                  {
                    func_hd_code_8029A7E4(
                      "\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n",
                      "record_status(pakBuffer)<=LEVEL_SAVE_SIZE-4",
                      "./master_switch.c",
                      0x201U);
                  }
                  if ((saveLevel != 0) &&
                      (saveLevel != (levelno + 1)))
                  {
                    func_hd_code_8029A7E4(
                      "\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n",
                      "!saveLevel || saveLevel==levelno+1",
                      "./master_switch.c",
                      0x203U);
                  }
                  saveLevel = levelno + 1;
                  if ((u32)(func_hd_code_8028604C(D_80364A5C) +
                            D_8036EA74) >= 0xEA60U)
                  {
                    D_8036EA74 = 0xEA5F;
                  }
                  else
                  {
                    D_8036EA74 = D_8036EA74 + func_hd_code_8028604C(D_80364A5C);
                  }
                }
                else if (D_hd_code_803643D7 != 0)
                {
                  func_hd_code_80264AEC();
                  D_8036EA74 = D_hd_code_802E8FCA[levelno].unk0 - D_80367BF6;
                }
                else
                {
                  D_8036EA74 = 0xFFFF;
                }
                if (D_8036EA74 == 0)
                {
                  func_hd_code_8029A7E4("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n",
                                        "nss.tc",
                                        "./master_switch.c",
                                        0x212U);
                }
                if (D_8036EA74 == 0)
                {
                  D_8036EA74 = 1;
                }
                func_hd_code_80255DC8();
                if (D_80365066 != 0)
                {
                  D_8036EA78 = D_8036EB92;
                  D_80365066 = 0;
                }
                if (D_803643D5 != 0)
                {
                  func_hd_code_80285A78(&D_8036EA70, &D_8036EA60);
                }
                else
                {
                  func_hd_code_80285A78(&D_8036EA80, &D_8036EA60);
                }
                D_80315438 = func_801EE800(&D_80364A60, 1, 1),
                func_hd_code_80285A78(&D_8036EA70, &D_8036EA90);

                if (D_80364A60 != 0)
                {
                  D_80364AA0 = 0x40000000;
                  D_80364A64 = 0xDC;
                  D_80364A70 = 0;
                }
                else
                {
                  func_801EC30C(D_80315438);
                  func_80200714(1);
                  D_80364A71 = func_801EF1E0();
                  if (D_80364A71 != -1)
                  {
                    func_801F55D8();
                  }
                  func_801E8C40(playerNumber);
                }

                D_8020C070[D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)]].unkE + D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)]].unk10 - 2].unk0 |= 1;
                D_8020C070[D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)]].unkE + D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)]].unk10 - 2].unk0 &= ~0x800;
                break;
              }
            }

            if ((D_803643D5 != 0) && (playerNumber == D_80364AEA))
            {
              D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)]].unk18 = D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)]].unkE + D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)]].unk10 - 1;
            }
            else
            {
              D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)]].unk18 = D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)]].unkE + D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)]].unk10 - 3;
            }

            D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)]].unk8 |= 8;

            func_hd_code_8026B8F8();
            if (D_hd_code_802E8BF8 != 0)
            {
              D_8020C070[0x1D].unk0 &= ~1;
            }
            func_hd_code_8026AF6C(D_hd_code_802F4868[func_hd_code_8026F92C(D_80364AA8)] | 0x8000);
            break;
          }
          case 0x0000000000000040:
          {
            if (D_hd_code_80364A90 & 0x04000200) {
              func_hd_code_8028B3E0();
              D_8036EA74 = func_hd_code_8028604C(D_80364A5C),
              func_hd_code_80285A78(&D_8036EA70, &D_8036EA60);
              func_801EE800(&D_80364A60, 0, 1);
            }
            D_hd_code_802F5804[0x18].unk0 = D_hd_code_802F5804[0x18].unk0 | 1;
            D_hd_code_802F5804[0x18].unk0 = D_hd_code_802F5804[0x18].unk0 & ~0x800;
            D_hd_code_802F5804[0x17].unk0 = D_hd_code_802F5804[0x17].unk0 | 1;
            D_hd_code_802F5804[0x17].unk0 = D_hd_code_802F5804[0x17].unk0 & ~0x800;
            D_hd_code_802F5804[0x11].unk0 = D_hd_code_802F5804[0x11].unk0 & ~1;
            D_hd_code_802F5804[0x11].unk0 = D_hd_code_802F5804[0x11].unk0 | 0x800;

            if (((D_80364AF0[playerNumber].unk18[levelno] > 0 && D_80364AF0[playerNumber].unk18[levelno] < 6)?1:0)) {
              D_hd_code_802F8BDC[6].unk18 = 0x18,
              D_hd_code_802F8BDC[7].unk18 = 0x22;
            } else {
              D_hd_code_802F8BDC[6].unk18 = 0x17,
              D_hd_code_802F8BDC[7].unk18 = 0x21;
            }
            D_80364A50 = 0;
            D_80364A54 = D_803156C4;
            func_hd_code_80255DC8();
            if (D_hd_code_802E8F94[levelno].unk0 == 1 && ((D_80364AF0[playerNumber].unk18[levelno] > 0 && D_80364AF0[playerNumber].unk18[levelno] < 6)?1:0) && (D_803643D5 == 0)) {
              func_hd_code_80256A34(&D_8039C4F8);
            } else {
              func_hd_code_80256A34(NULL);
            }
            func_hd_code_8026B8F8();
            func_hd_code_8025BB50();
            break;
          }
          case 0x0000000020000000:
          {
            func_hd_code_80255DC8();
            if (D_hd_code_80364A90 == 0x4000)
            {
              osRecvMesg(&D_80219F50, NULL, 1);
            }
            osViBlack(1);
            func_hd_code_802A0700();
            if (func_801E7000() != 0)
            {
              func_80200714(2);
            }
            else
            {
              D_80364AA0 = 0x2000;
            }
            break;
          }
          case 0x0000000000040000:
          {
            osSendMesg(&D_80219EF8, (playerNumber << 0x10) | 0x14 | 0x01000000, 1);
            osRecvMesg(&D_80219F50, NULL, 1);
            func_801EA93C("ENTER NAME!", &D_hd_code_803047A0, 7, 0x1E, &D_80364AF0[playerNumber]);
            func_hd_code_8026AF6C(0x800B);
            func_hd_code_8025D184();
            D_80364A70 = func_hd_code_80261A44(D_80364A98);
            break;
          }
          case 0x4000000000000000:
          {
            func_hd_code_80255DC8();
            func_80200714(1);
            D_8020C070[0x09].unkA = "QUIT GAME!",
            D_8020C070[0x09].unkE = &D_hd_code_803047CC,
            D_8020C070[0x09].unk8 = 0x16U,
            D_8020C070[0x09].unk6 = D_8020C070[0x09].unk8;
            func_hd_code_8026AF6C(0x800C);
            break;
          }
          case 0x0000001000000000:
          {
            func_hd_code_80260EE0(0x18);
            func_hd_code_80260B40(0, 0);
            func_hd_code_80297ECC();
            func_hd_code_8026AF6C(0x8015);
            D_hd_code_802E8BD8 = 1;
            break;
          }
          case 0x0000100000000000:
          {
            func_hd_code_80299C0C();
            D_80364A70 = func_hd_code_80261A44(D_80364A98);
            func_hd_code_80255DC8();
            func_hd_code_80299C20();
            if (D_hd_code_80364A90 == 0x4000 || levelno == 0x2F) {
              osRecvMesg(&D_80219F50, NULL, 1);
            }
            osViBlack(1);
            func_hd_code_80256A34(NULL);
            break;
          }
          case 0x0040000000000000:
          {
            func_hd_code_80255DC8();
            osSendMesg(&D_80219EF8, 0x01000010, 1);
            osRecvMesg(&D_80219F50, &D_8039C4B4, 1);
            if (D_8039C4B4 != 0)
            {
              func_hd_code_8025D184();
              func_80200714(1);
              D_8020C070[0x09].unkA = "ERASE SAVED GAME!",
              D_8020C070[0x09].unkE = &D_hd_code_803047B4,
              D_8020C070[0x09].unk8 = 0x14U,
              D_8020C070[0x09].unk6 = D_8020C070[0x09].unk8;
              func_hd_code_8026AF6C(0x800C);
            }
            else
            {
              D_80364AA0 = 0x10;
            }
            break;
          }
          case 0x0100000000000000:
          {
            D_8020C070[0x09].unkA = "BECOME GUEST PLAYER:",
            D_8020C070[0x09].unkE = &D_hd_code_803047DC,
            D_8020C070[0x09].unk8 = 0x14U,
            D_8020C070[0x09].unk6 = D_8020C070[0x09].unk8;
            func_hd_code_8026AF6C(0x800C);
            break;
          }
          case 0x0000000000400000:
          {
            func_801EA6E8();
            func_hd_code_8026AF6C(0x800A);
            break;
          }
          case 0x0000000000000008:
          {
            D_hd_code_802E8BD8 = 1;
            func_hd_code_80260E80();
            break;
          }

        }

        D_80364A88 = D_hd_code_80364A90;
        D_hd_code_80364A90 = D_80364A98;
        D_80364A98 = D_80364AA0;
      } while (D_80364A98 != 0);

      if (D_80364A70) {
        func_hd_code_80261FB0(D_80364A70);
      }
      while (D_80364A98 == 0) {
        D_80364AD0 = osGetTime();
        func_hd_code_8025B2B8();
        if (D_hd_code_80364A90 & 0x4000) {
          D_80364ACC = (osGetTime() - D_8036BF38) / 0x1E91U;
          func_801F8980();
          D_80364AC8 = (osGetTime() - D_80364AD0) / 0x1E91U;

          if (D_8036E68C[2] != 0) {
            func_hd_code_80285110(0x4D2);
          }
          if (D_8036E68C[0] != 0) {
            func_hd_code_80285110(0x4D2);
          }
          func_hd_code_80285110(0x4D2);
        } else if (D_hd_code_80364A90 & 0xC9FD8FE7DBFF8080) {
          D_80364ACC = (osGetTime() - D_8036BF38) / 0x1E91U;
          func_801FE990();
          D_80364AC8 = (osGetTime() - D_80364AD0) / 0x1E91U;
          func_hd_code_80285110(0x4D2);
        } else if (D_hd_code_80364A90 & 0x20000000) {
          func_801E7598();
          func_hd_code_80285110(0x4D2);
        } else if (D_hd_code_80364A90 & 0x30) {
          func_801EF4AC();
          func_hd_code_80285110(0x4D2);
        } else {
          D_80364ACC = (osGetTime() - D_8036BF38) / 0x1E91U;
          func_hd_code_802475D8();
          D_80364AC8 = (osGetTime() - D_80364AD0) / 0x1E91U;
          if (D_8036E68C[1] != 0) {
            func_hd_code_80285110(0x61F);
          }
          if (D_8036E68C[2] != 0) {
            func_hd_code_80285110(0x54D);
          }
          func_hd_code_80285110(0x4D2);
        }
        func_hd_code_80255D34();
        D_hd_code_80358060 += 1;
        D_80358064 += 1;
        if (D_hd_code_802E8BD0 == 0) {
          D_80358068 += 1;
        }
      }
      if (D_hd_code_80364A90 & 0x104 && ((D_hd_code_803643D6 != 0) || (D_hd_code_803643D7 != 0))) {
        func_hd_code_8025BBE8(0, 0, 0);
      }
      if (areWeFading()) {
        func_hd_code_8029A7E4("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n",
          "!areWeFading()", "hd.c", 0x273U);
      }
      switch (D_80364A98)
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
      if (playerNumber != D_80364AEA) {
        continue;
      }
      if (D_80364A98 != 0x4000) {
        continue;
      }
      if (func_hd_code_8028653C() == 0) {
        continue;
      }
      func_hd_code_802860F0();
    }
}

void func_hd_code_802475D8(void) {
    s32 sp6C;
    s32 sp68; // sp70
    s32 sp64;
    u8 sp63; // sp6B
    u8 pad62;
    u8 pad61;
    u8 pad60;
    Gfx *sp5C;
    u8 sp5B;
    u8 pad5A;
    u8 pad59;
    u8 pad58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s16 sp4A;
    s16 pad48;

    if ((D_hd_code_802FA268 != 0) && (D_80370C28 & 1) && !(D_80370C2A & 1) && (D_hd_code_80364A90 & 0x104)) {
        D_803643DA = 1;
        D_803643D9 = 0;
        if (D_80370C28 & 8) {
            if (D_80364AA8 != 1 || ((D_80364AF0[playerNumber].unk18[levelno] > 0 && D_80364AF0[playerNumber].unk18[levelno] < 6)?1:0) == 0) {
                D_803643DA = 0;
                D_803643D9 = 1;
            }
        }
        if ((D_80370C28 & 0x2000) && (D_803643DA != 0)) {
            D_803F7688 = 1;
            D_8036EA7C = D_8036EB90;
            D_8036EA79 = D_8036EB93;
            D_80365066 = 1;
            func_hd_code_80285AB0(2);
            func_hd_code_80285AB0(1);
        }
        if (((D_80364AF0[playerNumber].unk18[levelno] > 0 && D_80364AF0[playerNumber].unk18[levelno] < 6)?1:0) && (D_80364AA8 == 1) && (D_803643DA != 0)) {
            D_hd_code_802E8BD8 = 1;
            func_hd_code_80275390(0x08000000);
        }
    }
    nextdma = 0;
    no_palette_dmas = 0;
    D_803A7426 = 0;
    if (D_hd_code_80358060 != 0) {
        if (D_8035805C == 0) {
            if (D_hd_code_80358060 >= 6U) {
                func_hd_code_8024B8F4(&D_803156F8[D_8035805C].projection, &D_803156F8[D_8035805C].unk180);
            }
        } else {
            sp68 = 0;
            sp63 = 0;
            do {
                if (D_803644BC[sp68].unk0 == D_hd_code_80364456) {
                    sp63 = 1;
                } else {
                    sp68 += 1;
                }
            } while (sp63 == 0);
            sp64 = 0;
            sp63 = 0;
            do {
                if (D_803643C8.textures[sp64].unk1022 == D_hd_code_80364456) {
                    sp63 = 1;
                } else {
                    sp64 += 1;
                }
            } while (sp63 == 0);

            func_hd_code_80258544(D_803643C8.textures[sp64].data, D_803643C8.textures[sp64].unk1004, D_803643C8.textures[sp64].unk1010, D_803643C8.textures[sp64].unk100C, D_803643C8.textures[sp64].unk1000, D_80364460[sp68].unk54, D_80364460[sp68].unk0, D_80364460[sp68].unk4);
        }
    }
    sp68 = 0;
    sp63 = 0;
    do {
        if (D_803644BC[sp68].unk0 == D_hd_code_80364456) {
            sp63 = 1;
        } else {
            sp68 += 1;
        }
    } while (sp63 == 0);
    if (D_8035805C == 0) {
        func_hd_code_80279778(D_hd_code_803643E0, D_hd_code_803643E4, D_hd_code_803643E8, D_hd_code_803643F8, D_hd_code_803643FC, D_hd_code_80364400, D_80364460[sp68].pad58, D_80364460[sp68].unk0, D_80364460[sp68].unk8, D_80364460[sp68].unk60);
    } else {
        func_hd_code_80279778(D_hd_code_803643E0, D_hd_code_803643E4, D_hd_code_803643E8, D_hd_code_803643F8, D_hd_code_803643FC, D_hd_code_80364400, D_80364460[sp68].pad58, D_80364460[sp68].unk0, D_80364460[sp68].unk4, D_80364460[sp68].unk60);
    }
    D_hd_code_803649D8 = osGetTime();
    func_hd_code_8028A3E4();
    func_hd_code_80284E54(&D_803156F8[D_8035805C].dp, D_80358078, 3, 1, 0x4D2, 1);
    func_hd_code_802A5720();
    D_8035805C ^= 1;
    switch (D_hd_code_802E8BD0) {
    case 0: {
        if (((u8) D_hd_code_802E8BD8 != 0) && ((D_hd_code_802E8BD0 = 1, D_hd_code_802E8BD4 = 0, D_hd_code_802E8BD8 = 0, D_803156F4 = D_8035805C ^ 1, (0 != 0)) || (D_hd_code_80364A90 & 0x104))) {
            if (D_8036EB99 == 0) {
                func_hd_code_80260B40(0, 0);
            }
            func_hd_code_80261570(0.5f);
            if (D_hd_code_80364A90 == 4 && ((D_hd_code_803643DB != 0) || (D_80364AC1 != 0)) && (D_8036BB18 == 0)) {
                D_80364A98 = 0x100;
                func_hd_code_802A45D4(0xA);
                D_hd_code_80364A78 = 0;
            }
        }
        break;
    }
    case 1: {

        if (D_hd_code_802E8BD4 != 0 && D_8035805C != D_803156F4) {
            D_hd_code_802E8BD8 = 0, D_hd_code_802E8BD4 = 0, D_hd_code_802E8BD0 = 0;
            if(D_hd_code_80364A90 & 0x104) {
                if (D_80358064 != 0) {
                    func_hd_code_8029A7E4("LOCKING KEYS!\n");
                    D_80370C38 = 1;
                }
                func_hd_code_80261E9C(D_hd_code_80364A90);
                func_hd_code_80261570(1.0f);
                if (D_hd_code_80364A90 == 0x100 && ((D_hd_code_803643DB != 0) || (D_80364AC1 != 0))) {
                    D_80364A98 = 4;
                    func_hd_code_802A45D4(0xA);
                }
                if (D_80358068 == 0) {
                    D_80358064 = 0;
                }
            }
        }
        break;
    }
    }
    if (D_hd_code_802E8BD0 != 0) {
        D_803156F5 = D_803156F4;
    } else {
        D_803156F5 = D_8035805C;
    }
    if ((D_hd_code_803643DB != 0) && ((D_hd_code_80364A90 & 0x104))) {
        func_hd_code_802BA148();
    }
    if ((D_803643DC != 0) && ((D_hd_code_80364A90 & 0x1905))) {
        func_hd_code_802B8794();
    }
    func_hd_code_802683E0();
    D_803649EE = 0;
    if ((D_hd_code_80364456 == 0) && !(D_hd_code_80364A90 & 0x1801)) {
        func_hd_code_8024AE2C();
    }
    func_hd_code_8028A470();
    if (D_hd_code_80364A90 & 0x104) {
        sp5B = 0;
        if ((D_80370C28 & 4) && !(D_80370C28 & 8)) {
            if (((f64) D_hd_code_802E8BE0 < 1.5) && (D_hd_code_80364A90 == 4)) {
                sp5B = 2;
                if (!(D_80370C2A & 4)) {
                    sndPlaySfx(D_80367738, 0xDCU, NULL);
                }
            } else if (!(D_80370C2A & 4) && (D_hd_code_80364A90 != 0x100)) {
                sp5B = 3;
            }
        }
        if (sp5B == 0) {
            if ((D_80370C28 & 8) && !(D_80370C28 & 4)) {
                if (((f64) D_hd_code_802E8BE0 > 1.0) && D_hd_code_80364A90 == 4 && (D_80364A7C == 0)) {
                    sp5B = 1;
                    if (!(D_80370C2A & 8)) {
                        sndPlaySfx(D_80367738, 0xDDU, NULL);
                    }
                } else if (!(D_80370C2A & 8) && D_hd_code_80364A90 == 0x100) {
                    sp5B = 4;
                }
            } else {
                D_80364A7C = 0;
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
            if ((D_hd_code_803643DB != 0) || (D_80364AC1 != 0)) {
                func_hd_code_802A45D4(0xA);
                D_80364A98 = 0x100;
                D_hd_code_80364A78 = 0;
                sndPlaySfx(D_80367738, 0xDFU, NULL);
            }
            break;
        case 4:
            D_80364A7C = 1;
            if ((D_hd_code_803643DB != 0) || (D_80364AC1 != 0)) {
                func_hd_code_802A45D4(0xA);
                D_80364A98 = 4;
                sndPlaySfx(D_80367738, 0xDFU, NULL);
            }
            break;
        }
    }
    if (D_hd_code_80364A90 == 0x100 && (D_hd_code_802E8BD0 != 0) && (D_8036BB1C == 2) && (D_hd_code_803643DB != 0) && (D_8036BB18 == 0)) {
        if (!(D_80370C28 & 0x2000) && !(D_80370C28 & 0x10)) {
            D_80364A80 = 0;
        } else {
            D_80364A80 = D_80364A80 + 0x64;
            if (D_80364A80 >= 0x321) {
                D_80364A80 = 0x320;
            }
            if (D_80370C28 & 0x2000) {
                D_hd_code_80364A78 += D_80364A80;
            }
            if (D_80370C28 & 0x10) {
                D_hd_code_80364A78 -= D_80364A80;
            }
        }
        sp54 = D_803EF6E4 + D_hd_code_80364A78;
        sp50 = D_803EF6F8 - 0x190;
        sp4C = D_803EF6F8 + D_803EF6F0;
        if (sp4C < sp54) {
            D_hd_code_80364A78 = sp4C - D_803EF6E4;
        }
        if (sp54 < sp50) {
            D_hd_code_80364A78 = sp50 - D_803EF6E4;
        }
        if (D_80370C28 & 0x2010) {
            if ((D_hd_code_802F8BDC->unk4 - 0x18) < -0x100) {
                D_hd_code_802F8BDC->unk4 = -0x100;
            } else {
                D_hd_code_802F8BDC->unk4 = (s16) (D_hd_code_802F8BDC->unk4 - 0x18);
            }
            D_8036BB34 = (D_8036BB34 * 0.8 > 0.1)?(D_8036BB34 * 0.8):(0.1);
            D_hd_code_802F8BDC->unk8 &= ~0x20;
        } else {
            if ((D_hd_code_802F8BDC->unk4 + 0x20) >= 0x21) {
                D_hd_code_802F8BDC->unk4 = 0x20;
            } else {
                D_hd_code_802F8BDC->unk4 = (s16) (D_hd_code_802F8BDC->unk4 + 0x20);
            }

            D_8036BB34 = (D_8036BB34 / 0.8 < 1.) ? (D_8036BB34 / 0.8) : 1.0;
            if (D_8036BB34 == 1.0) {
                D_hd_code_802F8BDC->unk8 |= 0x20;
            }
        }
    } else {
        D_80364A80 = 0;
        if ((D_hd_code_802F8BDC->unk4 + 0x20) >= 0x21) {
            D_hd_code_802F8BDC->unk4 = 0x20;
        } else {
            D_hd_code_802F8BDC->unk4 = (s16) (D_hd_code_802F8BDC->unk4 + 0x20);
        }

        D_8036BB34 = D_8036BB34 / 0.8 < 1.0 ? D_8036BB34 / 0.8 : 1.0;
        if (D_8036BB34 == 1.0) {
            D_hd_code_802F8BDC->unk8 |= 0x20;
        }
    }
    if ((D_80370C22 != 0) && (D_hd_code_802E8BD0 == 0) && (D_hd_code_80364456 != 0) && (D_hd_code_8036443C == 0) && ((D_80364AA8 == 1) || (D_80364AA8 == 0x80))) {
        func_hd_code_8024B188();
    }
    func_hd_code_8024B618();
    if ((D_80370C28 & 0x4000) && !(D_80370C2A & 0x4000) && (areWeFading() == 0) && D_80364A98 == 0) {
        switch(D_hd_code_80364A90) {
            case 0x100000000000:
                if((levelno != 0x2F) && (levelno != 0x31) && ((levelno != 0x26) || (D_80364A88 == 0x4000))) {
                    sndPlaySfx(D_80367738, 0xDEU, NULL);
                    D_80364A98 = 0x4000;
                }
                break;
            case 0x40:
            case 0x400:
                sndPlaySfx(D_80367738, 0xDEU, NULL);
                if (((D_80364AF0[playerNumber].unk18[levelno] > 0 && D_80364AF0[playerNumber].unk18[levelno] < 6)?1:0) != 0) {
                    D_80364A98 = 0x08000000;
                } else {
                    D_80364A98 = 0x4000;
                }
                break;
            case 0x800:
            case 0x1000:
                if ((levelno != 0x32) || ((D_80364A88 == 0x4000))) {
                    sndPlaySfx(D_80367738, 0xDEU, NULL);
                    D_80364A98 = 0x4000;
                }
                break;

        }
    }
    if ((D_803643DC != 0) && ((D_hd_code_802E8BD0 == 0) || (0 != 0) || (D_hd_code_80364A90 & 0x1801))) {
        func_hd_code_802B899C();
        if ((D_hd_code_80364A90 & 0x1801)) {
            if (areWeFading() == 0) {
                if (((D_80364A98 == 0)) || (D_80364A98 & 0x1801)) {
                    func_hd_code_802AEEC8();
                }
                func_hd_code_802B8AE4();
            }
        } else {
            func_hd_code_8026510C();
        }
    }
    if ((D_hd_code_802E8BD0 == 0) && (D_80364A84 == 0)) {
        func_hd_code_8024B7AC();
    }
    if ((D_8039CA62 != 0) && (D_hd_code_802E8BD0 == 0)) {
        func_hd_code_80294F00();
    }
    if ((D_hd_code_803643DB != 0) && (D_80364AA8 & 0x81)) {
        if (!(D_hd_code_80364A90 & 0x1801)) {
            func_hd_code_802BA354();
        }
        if (((D_hd_code_80364A90 & 0x104)) && (func_hd_code_8026B10C() == 0) && (D_hd_code_802E8BD0 == 0) && (D_hd_code_803643D7 == 0) && (D_hd_code_803643D6 == 0)) {
            func_hd_code_8024A92C(sp6C = func_hd_code_802C1B9C());
        }
    }
    if ((D_80364AC1 != 0) && (D_hd_code_802E8BD0 == 0)) {
        func_hd_code_802D291C();
        if ((levelno == 0x32) && (D_8036BB1C == 1) && ((u32) D_hd_code_80358060 >= 0x33U) && ((0 != 0) || (D_hd_code_80364A90 & 0x1801)) && (areWeFading() == 0)) {
            func_hd_code_80275390(0x2000);
        }
    }
    func_hd_code_8029DDC8();
    if (D_hd_code_802E8BD0 == 0) {
        D_803ED40C = 0;
        D_803F7806 = func_hd_code_802C1AA0();
        func_hd_code_802BC5E0();
        func_hd_code_8024B5E8();
        func_hd_code_8028F794(D_hd_code_80364456);
        func_hd_code_80291FAC(D_hd_code_80364456);
        func_hd_code_802688C4(levelno);
        if ((0 == 0) && !(D_hd_code_80364A90 & 0x1801)) {
            func_hd_code_8026FEC4();
        }
        func_hd_code_80281CE4();
        if ((0 != 0) || (D_hd_code_80364A90 & 0x104)) {
            func_hd_code_80297804(D_hd_code_803643E0, D_hd_code_803643E4, D_hd_code_803643E8);
        }
        func_hd_code_8029E0AC();
        if (((0 != 0) || (D_hd_code_80364A90 & 0x104)) && (D_80364AA8 & 1)) {
            func_hd_code_8024A348();
            func_hd_code_8024ADD8();
        }
        if ((D_80364AA8 != 1) && (D_80367C00 != 0) && ((u32) (D_803156C0 - D_80364A58) >= 0x5BU)) {
            D_80367C00 = 0;
            func_hd_code_802794A4();
        }
    }
    if ((D_hd_code_803643D6 == 0) && (D_hd_code_803643D7 == 0)) {
        if ((levelno == 0x32) && (D_8036EB98 != 0)) {
            if (((D_80364AF0[playerNumber].unk18[0x4A - 0x18] > 0 && D_80364AF0[playerNumber].unk18[0x4A - 0x18] < 6)?1:0) == 0) {
                goto block_275;
            }
        }
    } else {
block_275:
        if ((D_80364AA8 == 1) && (D_80364A5C == 0)) {
            func_hd_code_8029A7E4("TIME IN LEVEL=%d\n", D_80364A5C = D_803156C0 - D_80364A58);
        }
    }
    LoadLevelTodo40(D_80358074);
    if ((0 != 0) || (D_hd_code_80364A90 & 0x1801)) {
        func_hd_code_802A45D4(2);
    }
    if ((D_8036BB18 == 0x58) && (D_8036BB1C != 8) && (D_hd_code_80364410 == 0)) {
        if (D_hd_code_80364A85 == 0) {
            func_hd_code_802A45D4(0xA);
        }
    } else if (D_hd_code_80364A85 != 0) {
        func_hd_code_802A45D4(0xA);
    }
    func_hd_code_802BD1F8(&D_803156F8[D_8035805C].unkA580,
                          &D_803156F8[D_8035805C].unkA918,
                          &D_803156F8[D_8035805C].unkACB0,
                          &D_803156F8[D_8035805C].unk1B650,
                          &D_803156F8[D_8035805C].unk00000,
                          &D_803156F8[D_8035805C].unkE00,
                          &D_803156F8[D_8035805C].unk21410,
                          &D_803156F8[D_8035805C].unk21478);
    if (D_hd_code_80364A90 == 4) {
        func_hd_code_80295C70(levelno, D_hd_code_803643E0, D_hd_code_803643E8);
    }
    func_hd_code_802A4CDC(D_80358030[D_8035805C],
                          D_80358038[D_8035805C],
                          D_80358040[D_8035805C],
                          D_80358048[D_8035805C],
                          &D_803156F8[D_8035805C].unkA4E0);
    func_hd_code_8027E9B8(D_8035805C);
    if ((D_hd_code_802E8BD0 == 0) || ((D_hd_code_803643DB != 0) && (D_hd_code_803643D6 != 0)) || (D_8036EB99 != 0)) {
        func_hd_code_802C0574();
        func_hd_code_802BCA2C();
    }
    if (D_hd_code_802E8BD0 == 0) {
        func_hd_code_8028DF14(D_hd_code_80364456);
        func_hd_code_802906C0(D_hd_code_80364456);
        func_hd_code_80292830();
        func_hd_code_8028C874(D_hd_code_80364456);
    }
    if (D_80364AA8 != 1) {
        if ((0 != 0) || (D_hd_code_80364A90 & 0x40)) {
            func_hd_code_8026420C();
        }
        if ((0 != 0) || (D_hd_code_80364A90 & 0x04002104)) {
            func_hd_code_80262BF4();
        }
    } else if (D_803BE738 != 0) {
        if (((D_80364AF0[playerNumber].unk18[levelno] > 0 && D_80364AF0[playerNumber].unk18[levelno] < 6)?1:0) == 0) {
            D_803643D9 = 1;
        } else if (areWeFading() == 0) {
            D_803643DA = 1;
            sndPlaySfx(D_80367738, 0x2BU, NULL);
            if ((D_hd_code_80364A90 == 0x40)) {
                func_hd_code_80275390(0x40);
            } else {
                func_hd_code_80275390(0x08000000);
            }
        }
    }
    func_hd_code_802A64A4();
    func_hd_code_802886A0();
    if (D_hd_code_802E8BD0 == 0) {
        func_hd_code_802CF1A4();
    }
    func_hd_code_80279514(D_hd_code_803643E0, D_hd_code_803643E4, D_hd_code_803643E8, D_hd_code_803643F8, D_hd_code_803643FC, D_hd_code_80364400);
    func_hd_code_80277620(D_hd_code_80358060);
    func_hd_code_8027D810(levelno);
    func_hd_code_802C2054();
    if (D_hd_code_802E8BD0 == 0) {
        func_hd_code_8026A9B4();
    }
    sp5C = func_hd_code_8024C414(&D_803156F8[D_8035805C], &D_80358078);
    if (D_hd_code_80364A90 & 0x04002444 && D_80364AA8 != 1) {
        sp5C = func_hd_code_802639B4(sp5C, &D_803156F8[D_8035805C], &D_80358078);
    }
    if ((D_hd_code_80364A90 & 0x100000000002)) {
        if((D_hd_code_80364A90 == 0x2)) {
            sp5C = func_hd_code_8025C878(sp5C, &D_803156F8[D_8035805C], D_8035805C, &D_80358078);
        }
        if ((D_hd_code_802E8BF0 != 0) || (D_80366A12 == 3) || (D_hd_code_802E8BEC >= 9)) {
            if (((D_8036BB1C == 1) || (D_8036BB1C == 8) || (D_hd_code_802E8BEC >= 9)) && ((D_hd_code_802E8BF0 == 0) || (D_hd_code_80358060 <= D_80366A04))) {
                if ((D_8039CAA0 + 0x14) >= 0x100) {
                    D_8039CAA0 = 0xFF;
                } else {
                    D_8039CAA0 += 0x14;
                }
            } else if ((D_8039CAA0 - 0x14) < 0) {
                D_8039CAA0 = 0;
            } else {
                D_8039CAA0 -= 0x14;
            }
        }
        if ((D_8039CAA0 != 0) && (D_hd_code_802E8BEC != 0) && (D_8039CAA2 != 0)) {
            sp5C = func_hd_code_80295EFC(&D_803156F8[D_8035805C],
                                         sp5C,
                                         (D_8039CAA0 / 2) - 0x67,
                                         0x55 - ((D_hd_code_80364A90 == 0x100000000000) << 5),
                                         (s32) D_8039CAA0);
        }
        if ((D_hd_code_802E8BEC == 0) && (D_80366A12 == 3) && (D_hd_code_80364A90 == 2)) {
            sp5C = func_hd_code_8029A1A8(&D_803156F8, sp5C);
        }
        if (D_hd_code_80364A90 == 2 || levelno == 0x2F) {
            func_hd_code_8025C5D0();
        }
    }
    if ((D_hd_code_80364A90 & 0x1801)) {
        if ((D_hd_code_80358060 == 0x96) && (levelno != 0x32)) {
            func_hd_code_8026AF6C(0x8040);
        }
        if (D_80364AF0[playerNumber].unk91 == 0 && (D_hd_code_80358060 == 0xA)) {
            func_hd_code_8026AF6C(0x803F);
        }
    }
    sp5C = func_hd_code_8024C404(sp5C, &D_803156F8[D_8035805C], &D_80358078);
    if ((D_hd_code_80364A90 & 0x440) && ((u32) (D_803156C4 - D_80364A54) >= 0xA1U) && ((u8) D_80364A50 == 0)) {
        D_80364A50 = 1;
        if (D_8036BB1C == 1) {
            if ((((D_80364AF0[playerNumber].unk18[levelno] > 0 && D_80364AF0[playerNumber].unk18[levelno] < 6)?1:0) == 0) || (D_80364AA8 == 1)) {
                func_hd_code_8026AF6C(
                     D_hd_code_802F4870[func_hd_code_8026F92C(D_80364AA8)] | 0x8000
                );
            }
        }
    }
    if (D_hd_code_80364A90 == 8 && (areWeFading() == 0) && ((func_hd_code_802D4E10(D_80367734) == 0) || ((u32) (D_803156C4 - D_80367740) >= 0x12DU))) {
        func_hd_code_80275390(0x08000000);
    }
    if ((levelno == 0x31) && (D_8036BB1C == 1)) {
        sp5C = func_hd_code_8029A518(&D_803156F8[D_8035805C], sp5C);
    }
    func_hd_code_80259C24(&sp5C, &D_803156F8[D_8035805C]);
    if (D_hd_code_80364A90 != 2) {
        sp5C = func_hd_code_80274BF0(&D_803156F8[D_8035805C], sp5C);
    }
    if ((D_hd_code_80364A90 == 0x2000000000000000)) {
        if ((D_80370C28 & 0x10) && !(D_80370C2A & 0x10)) {
            if ((D_8036BB18 < 0x6B) && (D_8036BB1C != 8) && (D_8036BB1C != 1)) {
                func_hd_code_8026AF6C((D_8036BB18 + 1) | 0x8000);
                sndPlaySfx(D_80367738, 0x1DU, NULL);
            } else {
                sndPlaySfx(D_80367738, 0xD0U, NULL);
            }
        }
        if ((D_80370C28 & 0x2000) && !(D_80370C2A & 0x2000)) {
            if ((D_8036BB18 >= 0x5F) && (D_8036BB1C != 8) && (D_8036BB1C != 1)) {
                func_hd_code_8026AF6C((D_8036BB18 - 1) | 0x8000);
                sndPlaySfx(D_80367738, 0x1DU, NULL);
            } else {
                sndPlaySfx(D_80367738, 0xD0U, NULL);
            }
        }
    }
    if ((((D_80370C28 & 0x1000) && !(D_80370C2A & 0x1000)) ||
         ((D_80370C28 & 0x8000) && !(D_80370C2A & 0x8000))) &&
        (areWeFading() == 0) &&
        (D_8036BB1A == -1) &&
        (D_80364A98 == 0) && (D_803643D9 == 0) && (D_803643DA == 0) && (D_8036BB18 != 0)) {
        if ((func_hd_code_8026B10C() & 0x8000) && (func_hd_code_8026B10C() & 1)) {
            func_hd_code_8026B10C();
        }
        switch(D_hd_code_80364A90) {
            case 0x800:
            case 0x1000:
            case 0x1:
                if (levelno != 0x32 || D_80364A88 == 0x4000) {
                    D_80364A98 = 0x2000;
                    sndPlaySfx(D_80367738, 0x1EU, NULL);
                }
                break;
            case 0x400:
            case 0x40:
                if (((D_80364AF0[playerNumber].unk18[levelno] > 0 && D_80364AF0[playerNumber].unk18[levelno] < 6)?1:0) && (D_80364AA8 != 1)) {
                    D_80364A98 = 0x08000000;
                    sndPlaySfx(D_80367738, 0x1EU, NULL);
                } else if (D_8036BB1C == 1) {
                    func_hd_code_8026AF6C(D_hd_code_802F4870[func_hd_code_8026F92C(D_80364AA8)] | 0x8000);
                }
                break;
            case 0x2:
                if (D_80366A18 != 0) {
                    sndPlaySfx(D_80367738, 0x1EU, NULL);
                    func_hd_code_80260B40(0, 0);
                    func_hd_code_80260B40(5, 0);
                    func_hd_code_80275390(0x20000000000000);
                }
                break;
            case 0x100000000000:
                if (D_803A6B04 != 0) {
                    D_80364A98 = 0x400000000000;
                }
                break;
            case 0x100:
            case 0x4:
                if ((D_80370C28 & 0x1000) && (D_hd_code_802E8BD0 == 0)) {
                    if (((D_80364AF0[playerNumber].unk18[levelno] > 0 && D_80364AF0[playerNumber].unk18[levelno] < 6)?1:0) && (D_80364AA8 == 1)) {
                        D_hd_code_802F5804[2].unk0 |= 1;
                        D_hd_code_802F5804[2].unk18 = 7;
                    } else {
                        D_hd_code_802F5804[2].unk0 &= ~1;
                        D_hd_code_802F5804[2].unk18 = 8;
                    }
                    func_hd_code_8026AF6C(0x8000);
                }
                break;



        }
    }
    sp5C = func_hd_code_8026BBD0(sp5C, &D_803156F8[D_8035805C], &D_80358078);
    if ((D_8036BB16 != 0) && (D_803643D9 == 0) && (D_803643DA == 0)) {
        func_hd_code_8024BDA4(&D_8036BB16);
    }
    if (D_hd_code_80364A90 & 0x444 && D_8036BB1A == -1 && D_80367BC8 == 0 && (((D_8036BB18 != -1)?(D_hd_code_802F8BE4[D_8036BB18].unk0 & 0x01000000):0) == 0)) {

            if (D_hd_code_80364A90 & 0x440) {
                sp4A = 0xB4;
            } else {
                sp4A = 0xFF;
            }
            D_80367BD6 = (D_80367BD6 < sp4A) ? ((sp4A < D_80367BD6 + 0x10) ? sp4A : (D_80367BD6 + 0x10)) : sp4A;

    } else {
        D_80367BD6 = (D_80367BD6 >= 0) ? (((D_80367BD6 - 0x10) < 0) ? (0) : (D_80367BD6 - 0x10)) : (0);
    }
    if (D_hd_code_80364A90 == 2) {
        sp5C = func_hd_code_80274BF0(&D_803156F8[D_8035805C], sp5C);
    }
    func_hd_code_802559F8(sp5C, &D_80358078);
    for(sp68 = 0; sp68 < nextdma; sp68++) {
        osRecvMesg(&D_80315180, NULL, 1);
    }

    if (D_80315188 != 0) {
        func_hd_code_8029A7E4("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "MQ_IS_EMPTY(&textureDmaMessageQ)", "hd.c", 0x5E5);
    }
    if (!(nextdma - no_palette_dmas < 0x90)) {
        func_hd_code_8029A7E4("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "nextdma-no_palette_dmas<NUM_TEXTURE_DMAS", "hd.c", 0x5E6);
    }
    for(sp68 = 0; sp68 < (nextdma - no_palette_dmas); sp68++) {
        func_hd_code_802A57AC();
    }

    D_803649E0 = (D_hd_code_803649D8 % 0x28) - 0x14;
    D_803649E2 = ((D_hd_code_803649D8 / 0x64) % 0x28) - 0x14;
    D_803649E4 = ((D_hd_code_803649D8 / 0x2710) % 0x28) - 0x14;
    D_803643D8 = D_hd_code_803643D6;
    if ((D_hd_code_803643D7 == 0) && (D_hd_code_803643D6 == 0)) {
        if (D_803643DA != 0) {
            if (D_803643D9 != 0) {
                func_hd_code_8029A7E4("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "!cmo_hit_request", "hd.c", 0x5F9);
            }
            D_hd_code_803643D7 = 1;
        } else if (D_803643D9 != 0) {
            D_hd_code_803643D6 = 1;
        }
        D_803643DA = 0;
        D_803643D9 = 0;
    }
}

void func_hd_code_8024A348(void) {
    if (D_80364A40 != 0) {
        if (((D_80364A3D + 1) != D_80364A3C) && ((D_80364A3D != 4) || (D_80364A3C != 0))) {
            D_80364A00[D_80364A3D].unk0 = D_80364A40;
            D_80364A00[D_80364A3D].unk9 = 0x1E;
            if ((D_hd_code_8036443E >= 0xE00) || (D_hd_code_8036443E < 0x200)) {
                if (D_80364AA8 == 8) {
                    D_80364A00[D_80364A3D].unk4 = 0x1E;
                    D_80364A00[D_80364A3D].unk6 = 0x3C;
                    D_80364A00[D_80364A3D].unk8 = 1;
                } else {
                    D_80364A00[D_80364A3D].unk4 = 0x1E;
                    D_80364A00[D_80364A3D].unk6 = 0x1E;
                    D_80364A00[D_80364A3D].unk8 = 1;
                }
            }
            if ((D_hd_code_8036443E >= 0x200) && (D_hd_code_8036443E < 0x600)) {
                D_80364A00[D_80364A3D].unk4 = 0x1E;
                D_80364A00[D_80364A3D].unk6 = 0xA0;
                D_80364A00[D_80364A3D].unk8 = 1;
            }
            if ((D_hd_code_8036443E >= 0x600) && (D_hd_code_8036443E < 0xA00)) {
                D_80364A00[D_80364A3D].unk4 = 0xFA;
                D_80364A00[D_80364A3D].unk6 = 0xA0;
                D_80364A00[D_80364A3D].unk8 = 0;
            }
            if ((D_hd_code_8036443E >= 0xA00) && (D_hd_code_8036443E < 0xE00)) {
                D_80364A00[D_80364A3D].unk4 = 0xFA;
                D_80364A00[D_80364A3D].unk6 = 0x25;
                D_80364A00[D_80364A3D].unk8 = 0;
            }

            if(++D_80364A3D == 5) {
                D_80364A3D = 0;
            }
        }
        D_80364A40 = 0;
    }
    if (D_80364A3C != D_80364A3D) {
        D_80364A44 = D_80364A00[D_80364A3C].unk0;
        D_80364A4A = D_80364A00[D_80364A3C].unk4;
        D_80364A4C = D_80364A00[D_80364A3C].unk6;
        D_80364A4E = D_80364A00[D_80364A3C].unk8;
        if ((s32) D_80364A00[D_80364A3C].unk9 >= 16) {
            D_80364A48 = (u32) (255.0f - (((f32) (D_80364A00[D_80364A3C].unk9 - 0xF) / 15.0f) * 255.0f));
        } else {
            D_80364A48 = (u32) (((f32) D_80364A00[D_80364A3C].unk9 / 15.0f) * 255.0f);
        }
        if (D_80364A00[D_80364A3C].unk9-- == 0) {
            if (++D_80364A3C == 5) {
                D_80364A3C = 0;
            }
        }
    } else {
        D_80364A44 = 0;
    }
}

void func_hd_code_8024A92C(u32 arg0) {
    u32 sp2C;
    u32 sp28;

    switch (levelno) {                              /* irregular */
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
        if (D_803EF6E4 >= 0x2B5C1) {
            sp2C = 0x61A8;
            sp28 = 0x4E20;
        } else if (D_803EF6E4 >= 0x13881) {
            sp2C = 0x55F0;
            sp28 = 0x445C;
        } else {
            sp2C = 0x36B0;
            sp28 = 0x1F40;
        }
        break;
    case 0x9:
        if (D_803EF6E4 >= 0x187E1) {
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
    D_803153F0 = D_80364A6F;
    if (arg0 < sp2C) {
        if (arg0 < sp28) {
            D_80364A6F = 2;
        } else {
            D_80364A6F = 1;
        }
    } else {
        D_80364A6F = 0;
    }
    if (D_80364A6F != D_803153F0) {
        if ((D_803153F0 == 0) && (func_hd_code_8026A610(D_803EF6DC, D_803EF6E4, D_hd_code_803643E0, D_hd_code_803643E8) >= 0x4E21)) {
            func_hd_code_80277EDC(1, 1, 7, 0x6C);
            func_hd_code_8029A7E4("TOO FAR AWAY FROM CMO\n");
        }
        switch (D_80364A6F) {                       /* switch 1; irregular */
        case 1:                                     /* switch 1 */
            switch (D_803153F0) {                   /* switch 2; irregular */
            case 0:                                 /* switch 2 */
                func_hd_code_80260DFC();
                /* fallthrough */
            case 2:                                 /* switch 2 */
                sndDeactivate(D_803156E8);
                break;
            }
            break;
        case 2:                                     /* switch 1 */
            switch (D_803153F0) {                   /* switch 3; irregular */
            case 0:                                 /* switch 3 */
                func_hd_code_80260DFC();
                /* fallthrough */
            case 1:                                 /* switch 3 */
                sndPlaySfx(D_80367738, 0x26U, &D_803156E8);
                break;
            }
            break;
        case 0:                                     /* switch 1 */
            sndDeactivate(D_803156E8);
            if ((D_hd_code_802E8F94[levelno].unk0 != 0x80) || (func_hd_code_802C1AA0() == 0)) {
                func_hd_code_8029A7E4("popTuneImmediate();\n");
                func_hd_code_80261040();
            } else {
                func_hd_code_8029A7E4("WILL THIS FIX IT!!?\n");
            }
            if (D_803153F0 == 2) {
                sndPlaySfx(D_80367738, 0x68U, NULL);
            }
            break;
        }
    }
    switch (D_80364A6F) {                           /* switch 4; irregular */
    case 1:                                         /* switch 4 */
        if ((func_hd_code_8026AD30(0x49) == 0) && (D_8036BB18 != 3)) {
            func_hd_code_8026AF6C(0x8003);
            return;
        }
        return;
    case 2:                                         /* switch 4 */
        if (D_8036BB18 != 2) {
            func_hd_code_8026AF6C(0x8002);
            return;
        }
        break;
    case 0:                                         /* switch 4 */
        if (((D_8036BB1C == 2) || (D_8036BB1C == 4)) && (func_hd_code_8026B10C() == 0) && ((D_8036BB18 == 3) || (D_8036BB18 == 2) || (D_8036BB18 == 0x49))) {
            func_hd_code_8026AF6C(0x4000);
        }
        break;
    }
}

void func_hd_code_8024ADD8(void) {
  u32 sp4;

  sp4 = (u32)D_803649F0 - (u32)D_803649F4;
  D_803649F4 = sp4 / 10U + (u32)D_803649F4;
  D_803649F4 = (u32)D_803649F4 + 0xA;
  if ((u32) D_803649F0 < (u32)D_803649F4) {
    D_803649F4 = D_803649F0;
  }
}

void func_hd_code_8024AE2C(void) {
    UnknownData8024C414* temp_t4;

    if ((D_803649ED != 0) && (D_803649ED != 0xFF)) {
        if (func_hd_code_802AB878(D_803649ED) == 0) {
            func_hd_code_802AB478(D_803649ED);
            func_hd_code_8028F6B4(D_803649ED);
            func_hd_code_80291ED8(D_803649ED);
            func_hd_code_8028B720();
            func_hd_code_802794E4();
            if (func_hd_code_8024AFA8(D_803649ED) != 0) {
                D_hd_code_80364456 = D_803649ED;
                func_hd_code_802AE860();
                if ((D_hd_code_802E8BD0 == 0) && ((u32) D_hd_code_80358060 >= 0xBU) && ((D_hd_code_80364456 == 8) || (D_hd_code_80364456 == 0xF) || (D_hd_code_80364456 == 0xD) || (D_hd_code_80364456 == 0xE))) {
                    func_hd_code_8026AD30(0x4A);
                }
            }
            D_80364AF0[playerNumber].unk10 |= 1 << D_hd_code_80364456;
            D_803649E8 = 1;
            D_hd_code_803649EC = 1;
            D_803649EE = 1;
            return;
        }
        if (sndGetPlayingState(D_803156F0) == 0) {
            sndPlaySfx(D_80367738, 0x2B, &D_803156F0);
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
    case 4:
      func_hd_code_802B448C();
      break;
    case 5:
      func_hd_code_802B5CD8();
      break;
    case 6:
      func_hd_code_802BB054();
      break;
    case 7:
      func_hd_code_802BBDC8();
      break;
    case 8:
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
  if ((sp27 != 0) && ((D_hd_code_80364A90 & 0x104))) {
    func_hd_code_8025BBE8(D_80364AF0[playerNumber].unkF0 & (1 << arg0) ? 0x80 : 0x40, 0, 0);
  }
  if (sp27 != 0) {
    func_hd_code_8029A7E4("changing to digger %d\n", arg0);
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
        sp26 = func_hd_code_802AE888(*(s32*)(&D_hd_code_802E8BF8 + D_hd_code_80364456 * 4));
    }
    if (sp26 != 0) {
        D_803649E8 = 0;
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
        if ((D_hd_code_80364A90 & 0x104)) {
            func_hd_code_8025BBE8(D_80364AF0[playerNumber].unkF0 & 1 ? 0x80 : 0x40, 0, 0);
        }
    }
    if (((sp27 == 0) || ((sp27 != 2) && (sp26 == 0))) && (sndGetPlayingState(D_803156EC) == 0)) {
        sndPlaySfx(D_80367738, 0x2BU, &D_803156EC);
    }
}

s32 func_hd_code_8024B418(u8 arg0) {
  u32 sp4;
  sp4 = 0;
  while(D_803649D0 != &D_80364460[sp4]) {
    if (D_80364460[sp4].unk5C == arg0) {
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
  D_803ED3F5 = 1;
  func_hd_code_802AB670(D_hd_code_80364456);
}

void func_hd_code_8024B618(void) {

    s32 sp1C;
    s32 sp18;

    sp1C = 0;
    if (D_80364460 != D_803649D0) {
        do {
            if (D_80364460[sp1C].unk70 != 0) {
                sp18 = D_80364460[sp1C].unk5C;
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
                        func_hd_code_8029A7E4("MOVEABLE GEOMETRY MOVE ROUTINE NOT WRITTEN YET\n");
                        break;
                    }
                }
            }
            sp1C += 1;
        } while (&D_80364460[sp1C] != D_803649D0);
    }
}

void func_hd_code_8024B7AC(void) {
    D_803ED3F5 = 0;
    switch (D_hd_code_80364456) {
    case 0:
        D_803649ED = 0;
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
  gSPSegment(entry++, 1, osVirtualToPhysical(D_8035806C));
  gSPDisplayList(entry++, D_1000010);
  gSPMatrix(entry++, (s32)arg0 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
  gImmp1(entry++, G_RDPHALF_1, D_8035807C);
  gSPMatrix(entry++, (s32)arg1 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
  gSPVertex(entry++, (s32)vertices & 0x1FFFFFFF, 8, 0);
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
  func_hd_code_802A467C(D_80358074, gfx, vertices, (((s32) entry - (s32)gfx) >> 3) * 8);
}

void func_hd_code_8024BDA4(u16* arg0) {
    switch(D_hd_code_80364A90) {
        case 0x4:
        case 0x100:
            switch (*arg0) {                    /* irregular */
            case 0x1:
                if ((D_hd_code_80364456 == 6) || (D_hd_code_80364456 == 0xB) || (D_hd_code_80364456 == 0x11) || (D_hd_code_80364456 == 0x12)) {
                    D_hd_code_802F5804[0x07].unk0 = (u16) (D_hd_code_802F5804[0x07].unk0 & ~1);
                    D_hd_code_802F5804[0x07].unk18 = 8;
                } else {
                    D_hd_code_802F5804[0x07].unk0 = (u16) (D_hd_code_802F5804[0x07].unk0 | 1);
                    D_hd_code_802F5804[0x07].unk18 = 7;
                }
                func_hd_code_8026AF6C(0x8001);
                D_80364A98 = 0x4;
                break;
            case 0x2:
                func_hd_code_80285EF4(D_80364A58);
                break;
            case 0x7:
                func_hd_code_8028B240();
                break;
            case 0x3:
                if (D_hd_code_802E8F94[levelno].unk0 & 0x81) {
                    func_hd_code_80275270(0x2000, 0x3F000000);
                } else {
                    func_hd_code_80275270(0x20000000, 0x3F000000);
                }
                break;
            case 0x8:
                D_80364A98 = 0x2000000000000000;
                func_hd_code_8026AF6C(0x805E);
                D_hd_code_80364412 = 1;
                break;
            case 0x4:
                func_hd_code_80275270(0x4000, 0x3F000000);
                break;
            case 0x9:
                if ((f64) func_hd_code_80260DF0() == 1.0) {
                    D_hd_code_802F8BDC[0x0d].unk18 = 0x28;
                } else {
                    D_hd_code_802F8BDC[0x0d].unk18 = 0x27;
                }
                func_hd_code_8026AF6C(0x800D);
                break;
            case 0x1A7:
            case 0x1A8:
                if ((((*arg0 - 0x1A7) << D_hd_code_80364456) ^ ((1 << D_hd_code_80364456) & 0x10205)) != 0) {
                    func_hd_code_8029A7E4("selected controller mode yes\n");
                    D_80364AF0[playerNumber].unkF0 = D_80364AF0[playerNumber].unkF0 | (1 << D_hd_code_80364456);
                    func_hd_code_8025BBE8(0x80, 0, 0);
                } else {
                    func_hd_code_8029A7E4("selected controller mode no\n");
                    D_80364AF0[playerNumber].unkF0 = (s32) (D_80364AF0[playerNumber].unkF0 & ~(1 << D_hd_code_80364456));
                    func_hd_code_8025BBE8(0x40, 0, 0);
                }
                break;
            case 0x11:
                D_hd_code_802F8BDC[0x06].unk8 = (s32) (D_hd_code_802F8BDC[0x06].unk8 | 0x80);
                break;
            case 0xFFFF:
                switch (D_8036BB18) {                   /* switch 1; irregular */
                case 0x1:                               /* switch 1 */
                case 0x6:                               /* switch 1 */
                    func_hd_code_8029A7E4("TESTING PAUSE2 %d %d %d\n", D_hd_code_802E8BD0, D_hd_code_802E8BD8, D_hd_code_802E8BD4);
                    func_hd_code_8026AF6C(0x8000);
                    if ((D_hd_code_803643DB != 0) || (D_80364AC1 != 0)) {
                        D_80364A98 = 0x100;
                        func_hd_code_802A45D4(0xA);
                    }
                    break;
                case 0xD:                               /* switch 1 */
                case 0x58:                              /* switch 1 */
                    func_hd_code_8029A7E4("TESTING PAUSE3 %d %d %d\n", D_hd_code_802E8BD0, D_hd_code_802E8BD8, D_hd_code_802E8BD4);
                    func_hd_code_8026AF6C(0x8001);
                    break;
                }
                break;
            case 0x28:
                func_hd_code_80260D7C(1.0f);
                break;
            case 0x27:
                func_hd_code_80260D7C(0.7f);
                break;
            }
            break;
        case 0x1000000000:
            D_80364A98 = 4;
            break;
        case 0x40:
        case 0x400:
            if (((D_80364AF0[playerNumber].unk18[levelno] > 0 && D_80364AF0[playerNumber].unk18[levelno] < 6)?1:0) != 0) {
                if ((*arg0 == 0x18) || (*arg0 == 0x22) || (*arg0 == 0xFFFF)) {
                    D_80364A98 = 0x08000000;
                } else {
                    D_80364A98 = 0x2000;
                }
            } else {
                if ((*arg0 == 0x18) || (*arg0 == 0x22) || (*arg0 == 0xFFFF)) {
                    D_80364A98 = 0x4000;
                } else {
                    D_80364A98 = 0x2000;
                }
            }
            break;
        case 0x2000000000000000:
            if (*arg0 == 0xFFFF) {
                func_hd_code_8029A7E4("TESTING PAUSE %d %d %d\n", D_hd_code_802E8BD0, D_hd_code_802E8BD8, D_hd_code_802E8BD4);
                func_hd_code_8026AF6C(0x8001);
            }
            D_80364A98 = 4;
            break;
        default:
            func_hd_code_8029A7E4("Yoshi selection in illegal game mode\n");
            break;
    }

    *arg0 = 0;
}

Gfx* func_hd_code_8024C404(Gfx* arg0, struct Model1* arg1, s32* arg2) {
  *arg2 = 0;
  return arg0;
}

Gfx* func_hd_code_8024C414(struct Model1* arg0, s32* arg1) {
    Gfx* entry;
    u8 sp194[16];
    u8 sp184[16];
    s32 sp180;

    entry = &arg0->dp[0];
    gSPSegment(entry++, 0x00, 0x00000000);
    gSPSegment(entry++, 0x02, osVirtualToPhysical(arg0));
    gSPSegment(entry++, 0x01, osVirtualToPhysical(D_8035806C));
    gSPDisplayList(entry++, D_1000038);
    gSPDisplayList(entry++, D_1000010);
    gDPPipeSync(entry++);
    gDPSetCycleType(entry++, G_CYC_FILL);
    gSPClearGeometryMode(entry++, G_ZBUFFER);
    gDPSetDepthImage(entry++, (s32) D_80358058);
    gDPSetColorImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, (s32) D_80358058);
    gDPSetFillColor(entry++, 0xFFFCFFFC);
    gDPFillRectangle(entry++, 0, 0, 319, 239);

    func_hd_code_802D4F68(&arg0->modelview, 0.f, 0.f, 0.f);
    guOrtho(&arg0->mtx1, 0, 319.f, 239.f, 0.0f, -20000.0f, 20000.0f, 1.0f);
    guOrtho(&arg0->mtx2, 0, 1279.f, 959.f, 0.0f, -20000.0f, 20000.0f, 1.0f);
    func_hd_code_802507C8(&arg0->projection2, &arg0->lookAt, &arg0->unk180);

    gDPSetColorImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, D_80358050[D_8035805C]);
    entry = func_hd_code_80271FD0(entry, arg0, levelno, D_hd_code_80364452, (s32) D_hd_code_80364454, &sp180);

    gDPPipeSync(entry++);
    gDPSetCycleType(entry++, G_CYC_FILL);

    switch(levelno) {
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
    gImmp1(entry++, G_RDPHALF_1, D_8035807C);

    switch(D_hd_code_80364A90) {
        case 0x40:
        case 0x400:
            guPerspective(&arg0->projection, &D_8035807C, D_80364438, ASPECT_RATIO, 10.0f, 20000.0f, 1.0f);
            break;
        case 0x01:
        case 0x800:
        case 0x1000:
            guPerspective(&arg0->projection, &D_8035807C, D_80364438, ASPECT_RATIO, 10.0f, 10000.0f, 1.0f);
            break;
        default:
            guPerspective(&arg0->projection, &D_8035807C, D_80364438, ASPECT_RATIO, 10.0f, 10000.0f, 1.0f);
            break;
    }


    gDPSetColorDither(entry++, G_CD_MAGICSQ);
    gSPClipRatio(entry++, FRUSTRATIO_3);
    func_hd_code_8027F1F8(&entry, D_8035805C, 0);


    gSPSegment(entry++, 0x08, D_80364458 & 0x1FFFFFFF);
    gSPClearGeometryMode(entry++, 0xFFFFFFFF);

    gSPDisplayList(entry++, osVirtualToPhysical(D_80358030[D_8035805C]));
    gSPDisplayList(entry++, (s32) D_803BE6E0);
    gSPClearGeometryMode(entry++, 0xFFFFFFFF);
    gSPSetGeometryMode(entry++, G_ZBUFFER);
    gSPDisplayList(entry++, osVirtualToPhysical(D_80358038[D_8035805C]));
    gSPDisplayList(entry++, (s32) D_803BE6E4);

    if ((D_hd_code_803643D6 == 0) && (D_hd_code_803643D7 == 0)) {
        gSPClearGeometryMode(entry++, 0xFFFFFFFF);
        gSPSetGeometryMode(entry++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LOD | G_SHADING_SMOOTH);

        gSPDisplayList(entry++, &D_2000000.unk21410);
        gDPPipeSync(entry++);
    }
    switch (D_8035805C) {                           /* irregular */
    case 0:
        gSPSegment(entry++, 0x0A, osVirtualToPhysical(D_803F7820));
        break;
    case 1:
        gSPSegment(entry++, 0x0A, osVirtualToPhysical(D_803F7824));
        break;
    }
    gDPPipeSync(entry++);
    gSPSetGeometryMode(entry++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    gDPSetCombineMode(entry++, G_CC_SHADE, G_CC_SHADE);
    gSPDisplayList(entry++, &D_2000000.unkA4E0);

    if (!(D_hd_code_80364A90 & 0x440)) {
        func_hd_code_8027C4C8(&entry, arg0);
    }
    func_hd_code_802502EC();
    func_hd_code_8024E4F4(&entry, arg0, 0);
    func_hd_code_80258B78(&entry, arg0);
    if ((D_hd_code_802E8BD0 == 0) && (D_80364AA8 != 0x40) && !(D_hd_code_80364A90 & 0x440) && (D_80364A84 == 0)) {
        func_hd_code_80279EE8(&entry, arg0, D_8035805C);
    }
    gSPClearGeometryMode(entry++, 0xFFFFFFFF);
    gSPSetGeometryMode(entry++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LOD | G_SHADING_SMOOTH);
    gSPDisplayList(entry++, &D_2000000.unkA580);

    gDPPipeSync(entry++);

    entry = func_hd_code_802CEEFC(entry, D_8035805C, &arg0->unkA3A0, &arg0->unk11C0);
    func_hd_code_8024E4F4(&entry, arg0, 1);
    if (D_803643DC != 0) {
        func_hd_code_8024F520(&entry, arg0);
    }
    func_hd_code_802701A8(&entry, arg0);
    func_hd_code_80281E44(&entry);
    func_hd_code_8028E9E4(&entry, arg0);
    func_hd_code_802917B0(&entry, arg0);
    func_hd_code_80292EB8(&entry, arg0);
    func_hd_code_8028CB30(&entry, arg0);
    switch (D_8035805C) {                           /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        gSPDisplayList(entry++, osVirtualToPhysical(&D_803C5770));
        break;
    case 1:                                         /* switch 1 */
        gSPDisplayList(entry++, osVirtualToPhysical(&D_803C6370));
        break;
    }
    func_hd_code_80288DF0(&entry, D_8035805C);
    if (!(D_hd_code_80364A90 & 2) || D_hd_code_802E8BF0 == 0) {
        func_hd_code_8024FC2C(&entry, 0);
    }
    func_hd_code_802976E8(&entry);

    gSPClearGeometryMode(entry++, 0xFFFFFFFF);
    gSPSetGeometryMode(entry++, G_ZBUFFER);
    gSPDisplayList(entry++, osVirtualToPhysical(D_80358040[D_8035805C]));
    gSPDisplayList(entry++, (s32) D_803BE6E8);
    if (!(D_hd_code_80364A90 & 2) || D_hd_code_802E8BF0 == 0) {
        func_hd_code_8024FC2C(&entry, 1);
    }

    gSPClearGeometryMode(entry++, 0xFFFFFFFF);
    gSPSetGeometryMode(entry++, G_ZBUFFER);
    gSPDisplayList(entry++, osVirtualToPhysical(D_80358048[D_8035805C]));
    gSPDisplayList(entry++, (s32) D_803BE6EC);

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
    if (( !(D_hd_code_80364A90 & 2)) || (D_hd_code_802E8BF0 == 0)) {
        func_hd_code_8024FC2C(&entry, 2);
    }
    func_hd_code_80295120(&entry, arg0);
    if ((D_hd_code_80364A90 & 0x2000001000003905)) {
        func_hd_code_80280F34(&entry, D_8035805C);
    }
    func_hd_code_8027F1F8(&entry, D_8035805C, 1);
    func_hd_code_8024E4F4(&entry, arg0, 2);
    if (D_803643DC != 0) {
        func_hd_code_80266248(&entry, arg0);
    }
    switch (D_8035805C) {                           /* switch 2; irregular */
    case 0:                                         /* switch 2 */
        gSPDisplayList(entry++, osVirtualToPhysical(&D_803C6F70));
        break;
    case 1:                                         /* switch 2 */
        gSPDisplayList(entry++, osVirtualToPhysical(&D_803C7B70));
        break;
    }
    if (D_hd_code_803643DB != 0) {
        func_hd_code_8028273C(&entry, D_8035805C);
    }
    if ((D_80364A68 != 0) && (D_hd_code_80364A90 & 0x104)) {
        func_hd_code_80286C60(&entry, arg0, D_8035805C, D_hd_code_80364456);
    }
    if ((D_hd_code_80364A90 & 0x200000000400220C)) {
        func_hd_code_80278324(&entry, arg0, D_8035805C);
    }
    if ((D_hd_code_80364A90 == 0x100) && (D_hd_code_803643DB != 0)) {
        func_hd_code_80276E50(&entry, arg0, D_8035805C, D_hd_code_803643E0, D_hd_code_803643E4, D_hd_code_803643E8);
    }
    func_hd_code_80259450();
    if ((D_80364A6A != 0) && ((D_hd_code_80364A90 & 0x104))) {
        func_hd_code_80287530(&entry, arg0, D_8035805C, D_hd_code_80364456);
    }
    if ((D_80364A6C != 0) && ((D_hd_code_80364A90 & 0x104))) {
        func_hd_code_80287C68(&entry, arg0, D_8035805C, D_hd_code_80364456);
    }
    if ((D_hd_code_80364A90 & 0x104)) {
        func_hd_code_80282224(&entry, D_hd_code_80364456);
    }
    if ((D_80364AA8 & 1) && ((D_hd_code_80364A90 & 0x0400030C))) {
        func_hd_code_8026A378(D_803649F4, &sp194[1]);
        sp194[0] = 0x24;
        func_hd_code_80259CCC(arg0, &sp194, NULL, 1, 0, 0x118, 0x12, 0x14, 0x14, 0, 0xFF, 0xFF, 0xFF, (s32) D_80367BD6);
        if ((D_80364A44 != 0) && (D_hd_code_802E8BD0 == 0)) {
            func_hd_code_8026A378(D_80364A44, &sp184[1]);
            sp184[0] = 0x24;
            func_hd_code_80259CCC(arg0, &sp184, NULL, 1, 0, (s32) D_80364A4A, (s32) D_80364A4C, 0x23, 0x23, (s32) D_80364A4E, 0xFF, 0xFF, 0xFF, D_80364A48);
        }
    }
   if ((D_hd_code_80364A90 & 0x2000000000000104) && (!(D_80364AA8 & 0x81) || (D_hd_code_803643DB != 0) || (D_80364AC1 != 0))) {
        func_hd_code_80275478(arg0, &entry, D_hd_code_80364A90 & 0x100 || D_8036BB18 == 0x4D || D_8036BB18 == 0x49);
    }
    if ((D_80364A98 == 0) && (areWeFading() == 0)) {
        if (!(D_hd_code_80364A90 & 0x200000100400230C) && ((u32) ((u32) (((u32) D_803156C4 % 50U) * 0x3C) / 60U) >= 0x15U) && (D_8036BB1C == 1) && ((!(D_hd_code_80364A90 & 2)) || ((D_hd_code_802E8BEC != 0) && ((D_80366A12 == 3) || (D_hd_code_802E8BEC == 1)))) && ((D_hd_code_80364A90 != 0x100000000000) || (D_803A6B04 != 0)) && ((!(D_hd_code_80364A90 & 0x1801)) || (D_80364B81[playerNumber << 8] != 0)) && (levelno != 0x2F)) {
            func_hd_code_80259CCC(arg0, "PRESS START", NULL, 1, 0, 0x5C, 0xC4, 0x1A, 0x1A, 1, 0xFF, 0xFF, 0xFF, 0xFF);
        }
        if ((u32) ((u32) (((u32) D_803156C4 % 40U) * 60) / 60U) >= 16U) {
            if (D_hd_code_802E8BD0 != 0) {
                if ((D_hd_code_80364A90 == 0x2000000000000000) && (D_8036BB1C == 2)) {
                    func_hd_code_80259CCC(arg0, "USE Z/R TO TURN PAGES", &D_hd_code_8030491C, 0, 0, 0x18, 0x14, 0xF, 0xF, 1, 0xFF, 0xFF, 0xFF, 0xFF);
                } else if ((D_hd_code_80364A90 == 0x100) && (D_8036BB18 == 0) && (D_8036BB1C == 2) && (D_hd_code_803643DB != 0) && !(D_80370C28 & 0x2010)) {
                    func_hd_code_80259CCC(arg0, "USE Z/R TO MOVE MAP", &D_hd_code_80304938, 0, 0, 0x18, 0x14, 0xF, 0xF, 1, 0xFF, 0xFF, 0xFF, 0xFF);
                }
            } else if ((D_hd_code_80364A90 == 0x100)) {
                if (D_80364AC1 != 0) {
                    func_hd_code_80259CCC(arg0, "SHUTTLE VIEW", &D_hd_code_80304904, 0, 0, 0x18, 0x14, 0xF, 0xF, 1, 0xFF, 0xFF, 0xFF, 0xFF);
                } else {
                    func_hd_code_80259CCC(arg0, "MISSILE VIEW", &D_hd_code_80304910, 0, 0, 0x18, 0x14, 0xF, 0xF, 1, 0xFF, 0xFF, 0xFF, 0xFF);
                }
            }
        }
    }
    if (( (D_hd_code_80364A90 & 0x440) || (levelno == 0x26)) && (D_8036BB1C == 1) && (areWeFading() == 0)) {
        if (( (D_hd_code_80364A90 & 0x440)) && (D_80364AA8 != 1)) {
            func_hd_code_80274B40(&entry, arg0, D_80365580, 0x108, 0x12);
        } else {
            func_hd_code_80274B40(&entry, arg0, D_80365580, 0x18, 0x12);
        }
    }
    if (( (D_hd_code_80364A90 & 0x104)) && (D_hd_code_80364410 != 0)) {
        func_hd_code_80274B40(&entry, arg0, D_80364A86, 0x108, 0xBE);
    }
    if (( (D_hd_code_80364A90 & 0x104)) && (D_80364AA8 == 1) && (D_hd_code_802E8BD0 == 0)) {
        func_hd_code_80285CC0();
    }
    if ((D_hd_code_803643DB != 0) && (D_hd_code_80364A90 == 4)) {
        func_hd_code_80282C80(&entry, arg0, D_hd_code_803643E0, D_hd_code_803643E4, D_hd_code_803643E8, D_803EF6DC, D_803EF6E0, D_803EF6E4);
    }
    if ((D_hd_code_802E8F94[levelno].unk0 & 0x81) && (D_hd_code_80364A90 == 4) ) {
        if (levelno != 0x32 || ((D_80364AF0[playerNumber].unk4A > 0 && D_80364AF0[playerNumber].unk4A < 6) ? 1 : 0)) {
            func_hd_code_8028376C(&entry, arg0, D_8035805C, D_hd_code_803643E0, D_hd_code_803643E8, D_803EF6DC, D_803EF6E4);
        }
    }
    if ((D_hd_code_803643DB != 0) || (D_80364AC1 != 0)) {
        switch(D_hd_code_80364A90) {
            case 0x4:
            case 0x100000000000:
            case 0x100:
            case 0x200:
                func_hd_code_8025E2CC(&entry, arg0, D_8035805C);
                func_hd_code_8025E67C(&entry, arg0, D_8035805C);
            case 0x400:
            case 0x40:
                if (((D_hd_code_803643D6 != 0) || (D_hd_code_803643D7 != 0) || (D_803643D9 != 0) || (D_803643DA != 0)) && ((D_hd_code_80364A90 & 0x144))) {
                    func_hd_code_802A45D4(0x32);
                    if (D_hd_code_80364A90 == 0x40) {
                        D_80364A98 = 1024;
                    } else {
                        D_80364A98 = 512;
                    }
                }
                break;
        }

    }
    func_hd_code_80259C24(&entry, arg0);
    *arg1 = (s32) (((s32)entry - (s32)arg0) - 0x48B0) >> 3;
    return entry;
}


// arg2 can only be 0,1 and 2
void func_hd_code_8024E4F4(Gfx** arg0, struct Model1 *arg1, u8 arg2) {
    Gfx *entry; // sp144
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
        D_8036506C = 0;
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



    sp133 = !D_803649E8 && (D_hd_code_803649EC || (D_hd_code_80364A90 & 0x1801));
    sp140 = 0;
    while(&D_803643C8.textures[sp140] != D_803643C8.end) {
        if (((D_803643C8.textures[sp140].unk1022 != 0) || (sp133 != 0)) && (D_803643C8.textures[sp140].unk1022 != 0xFE) && (( D_803643C8.textures[sp140].unk1022 != 0xFF) || (D_803EF6FF == 0)) && ((D_803643C8.textures[sp140].unk1022 == 0xFD) || (D_80364A84 == 0) || (D_80364AC1 == 0)) && D_803643C8.textures[sp140].unk1023 == arg2) {
                sp13C = D_803643C8.textures[sp140].unk1004 >> 5;
                sp13A = D_803643C8.textures[sp140].unk1008 >> 5;
                sp138 = D_803643C8.textures[sp140].unk100C >> 5;
                sp136 = D_803643C8.textures[sp140].unk1018; // 2D x
                sp134 = D_803643C8.textures[sp140].unk101A; // 2D y
                spAB = D_803643C8.textures[sp140].unk1022 == D_hd_code_80364456 && D_803ED40D == 0x65;
                if (spAB) {
                    guAlignF(spB0, ((f32) D_80364440 * 360.0) / 4096.0f, 0.0f, 1.0f, 0.0f); // Additional rotation around y axis if spAB
                }
                guAlignF(spF0, ((f32) -D_803643C8.textures[sp140].unk101E * 360.0) / 4096.0f, 0.0f, 1.0f, 0.0f); // rotation around y axis by -unk101E * D_hd_code_803087C0 degrees
                if (spAB) {
                    guMtxCatF(spB0, spF0, spF0); // Apply additional rotation
                }
                guAlignF(spB0, (f32) (((f64) (f32) D_803643C8.textures[sp140].unk101C * 360.0) / 4096.0), 1.0f, 0, 0.0f);
                guMtxCatF(spF0, spB0, spB0);
                guAlignF(spF0, (f32) (((f64) (f32) D_803643C8.textures[sp140].unk1020 * 360.0) / 4096.0), 0, 0, 1.0f);
                guMtxCatF(spB0, spF0, spF0);
                guAlignF(spB0, (f32) (((f64) (f32) D_803643C8.textures[sp140].unk101E * 360.0) / 4096.0), 0, 1.0f, 0.0f);
                guMtxCatF(spF0, spB0, spF0);
                func_hd_code_802D4F20(spB0, (f32) sp13C, (f32) sp13A, (f32) sp138);
                guMtxCatF(spF0, spB0, spF0);
                guMtxF2L(spF0, &arg1->unk2C0[sp140]);

                if (spAB) {
                    gDPLoadTextureBlock(entry++, OS_PHYSICAL_TO_K0(&D_hd_code_802FA940), G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    spAC = spAE = 32;
                } else {
                    gDPLoadTextureBlock(entry++, K0_TO_PHYS((s32)(D_803643C8.textures[sp140].data)), G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                    spAC = spAE = 64;
                }

                SET_COLOR_VERTEX(arg1->unk1580[D_8036506C + 4], (s16) -sp136, 0, sp134, (s16) ((spAE - 1) << 5), (s16) ((spAC - 1) << 5), 0xA, 0xA, 0xA, 0x8C);
                D_8036506C++;
                SET_COLOR_VERTEX(arg1->unk1580[D_8036506C + 4], sp136, 0, sp134, 0, (s16) ((spAC - 1) << 5), 0xA, 0xA, 0xA, 0x8C);
                D_8036506C++;
                SET_COLOR_VERTEX(arg1->unk1580[D_8036506C + 4], sp136, 0, (s16) -sp134, 0, 0, 0xA, 0xA, 0xA, 0x8C);
                D_8036506C++;
                SET_COLOR_VERTEX(arg1->unk1580[D_8036506C + 4], (s16) -sp136, 0, (s16) -sp134, (s16) ((spAE - 1) << 5), 0, 0xA, 0xA, 0xA, 0x8C);
                D_8036506C++;

                if ((D_hd_code_803643D6 != 0) && !(D_80364AA8 & 0x81) && (D_803643C8.textures[sp140].unk1022 == D_hd_code_80364456)) {
                    gSPMatrix(entry++, &D_2000000.unk1540, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
                }
                gSPMatrix(entry++, &D_2000000.unk2C0[sp140], G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
                gSPVertex(entry++, &D_2000000.unk1580[D_8036506C], 4, 0);
                gSP1Triangle(entry++, 0, 1, 2, 0);
                gSP1Triangle(entry++, 0, 2, 3, 0);
                gSPPopMatrix(entry++, G_MTX_MODELVIEW);

                if ((D_hd_code_803643D6 != 0) && !(D_80364AA8 & 0x81) && (D_803643C8.textures[sp140].unk1022 == D_hd_code_80364456)) {
                    gSPPopMatrix(entry++, G_MTX_MODELVIEW);
                }
                gDPPipeSync(entry++);

        }
        sp140++;
    }
    *arg0 = entry;
}

void func_hd_code_8024F520(Gfx** arg0, struct Model1* arg1) {
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
        if (D_803643C8.textures[sp88].unk1022 == 0xFE) {
            sp87 = 1;
        } else {
            sp88 += 1;
        }
    } while (sp87 == 0);
    gDPSetTextureImage(entry++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, K0_TO_PHYS((s32)(D_803643C8.textures[sp88].data)));
    gDPSetTile(entry++, G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
    gDPLoadSync(entry++);
    gDPLoadBlock(entry++, G_TX_LOADTILE, 0, 0, 2047, 256);
    gDPPipeSync(entry++);
    gDPSetTile(entry++, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
    gDPSetTileSize(entry++, G_TX_RENDERTILE, 0, 0, qu102(63), qu102(63));
    sp84 = (s16) ((s32) D_803643C8.textures[sp88].unk1004 >> 5);
    sp82 = (s16) ((s32) D_803643C8.textures[sp88].unk1008 >> 5);
    sp80 = (s16) ((s32) D_803643C8.textures[sp88].unk100C >> 5);
    sp7E = D_803643C8.textures[sp88].unk1018;
    sp7C = D_803643C8.textures[sp88].unk101A;

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

    func_hd_code_802D4F68(&arg1->unk240, (f32) sp84, (f32) sp82, (f32) sp80);
    guAlign(&arg1->unk280, ((f32) D_803EF326 * 360.0) / 4096.0, 0.0f, 1.0f, 0.0f);
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
    s32 sp60;
    u8 pad;
    u8 sp5E;
    u8 sp5D;

    entry = *arg0;
    
    sp5D = D_803649E8 == 0 && (D_hd_code_803649EC != 0 || D_hd_code_80364A90 & 0x1801);
    sp60 = 0;
    while (&D_80364460[sp60] != D_803649D0) {
        if (((D_80364460[sp60].unk5C != 0) || (sp5D != 0)) && ((D_80364460[sp60].unk5C != 0xFF) || (D_803EF6FF == 0)) && ((D_80364460[sp60].unk5C == 0xFD) || (D_80364A84 == 0) || (D_80364AC1 == 0))) {
            gSPSegment(entry++, 0x06, osVirtualToPhysical(D_80364460[sp60].unk0));               
            if (((D_hd_code_80364A90 & 0x1801)) && (((D_80364460[sp60].unk5C == 0xFE)) || (D_80364460[sp60].unk5C == 0))) {
                sp5E = D_8035805C;
            } else {
                sp5E = D_803156F5;
            }
            if (sp5E != 0) {
                gSPSegment(entry++, 0x07, osVirtualToPhysical(D_80364460[sp60].unk4));
            } else {
                gSPSegment(entry++, 0x07, osVirtualToPhysical(D_80364460[sp60].unk8));
            }
            gDPPipeSync(entry++);
            gDPSetEnvColor(entry++, 0x00, 0x00, 0x00, D_80364460[sp60].unk60);
            gSPClearGeometryMode(entry++, 0xFFFFFFFF);
            if ((D_hd_code_803643D6 != 0) && !(D_80364AA8 & 0x81) && (D_80364460[sp60].unk5C == D_hd_code_80364456)) {
                gSPMatrix(entry++, &D_2000000.unk1500, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            }
            if (sp5E != 0) {
                switch (arg1) {                 /* switch 1; irregular */
                case 0:                         /* switch 1 */
                    gSPDisplayList(entry++, osVirtualToPhysical(D_80364460[sp60].unkC));
                    break;
                case 1:                         /* switch 1 */
                    gSPDisplayList(entry++, osVirtualToPhysical(D_80364460[sp60].unk10));
                    break;
                case 2:                         /* switch 1 */
                    gSPDisplayList(entry++, osVirtualToPhysical(D_80364460[sp60].unk14));
                    break;
                }
            } else {
                switch (arg1) {                 /* irregular */
                case 0:
                    gSPDisplayList(entry++, osVirtualToPhysical(D_80364460[sp60].unk30));
                    break;
                case 1:
                    gSPDisplayList(entry++, osVirtualToPhysical(D_80364460[sp60].unk34));
                    break;
                case 2:
                    gSPDisplayList(entry++, osVirtualToPhysical(D_80364460[sp60].unk38));
                    break;
                }
            }
            gSPMatrix(entry++, &D_2000000.modelview, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        }
        sp60++;
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

    if ((D_hd_code_803643D6 != 0) && !(D_80364AA8 & 0x81)) {
        func_hd_code_802D4F20(sp70, (f64) -(f32) D_hd_code_803643E0 / 32.0f, (f64) -(f32) D_hd_code_803643E4 / 32.0, (f64) -(f32) D_hd_code_803643E8 / 32.0);
        guRotateRPYF(sp30, D_80364ABC, D_80364ABC, D_80364ABC);
        guMtxCatF(sp70, sp30, sp70);
        guAlignF(sp30, D_80364AB4, 0, 1.0f, 0.0f);
        guMtxCatF(sp70, sp30, sp70);
        func_hd_code_802D4F20(sp30, (f64) (f32) D_hd_code_803643E0 / 32.0,(f64) (f32) D_hd_code_803643E4 / 32.0, (f64) (f32) D_hd_code_803643E8 / 32.0);
        guMtxCatF(sp70, sp30, sp70);
        guMtxF2L(sp70, &D_803156F8[D_8035805C].unk1500);
        sp2C = 0;
        while (D_803643C8.textures[sp2C].unk1022 != D_hd_code_80364456) {
            sp2C += 1;
        }
        sp2A = D_803643C8.textures[sp2C].unk1004 >> 5;
        sp28 = D_803643C8.textures[sp2C].unk1008 >> 5;
        sp26 = D_803643C8.textures[sp2C].unk100C >> 5;
        func_hd_code_802D4F20(sp70, (f32) -sp2A, (f32) -sp28, (f32) -sp26);
        guRotateRPYF(sp30, D_80364ABC, D_80364ABC, D_80364ABC);
        guMtxCatF(sp70, sp30, sp70);
        guAlignF(sp30, D_80364AB4, 0, 1.0f, 0.0f);
        guMtxCatF(sp70, sp30, sp70);
        func_hd_code_802D4F20(sp30, sp2A, sp28, sp26);
        guMtxCatF(sp70, sp30, sp70);
        guMtxF2L(sp70, &D_803156F8[D_8035805C].unk1540);
        if (D_80364AC0 == 0) {
            D_80364ABC = D_80364ABC - 0.04;
            if (D_80364ABC < 0.0) {
                D_80364ABC = 0.0;
            }
        }
        if ((D_80364ABC == 0.0) && (D_80364AC0 == 0)) {
            func_hd_code_802AC61C(D_hd_code_803643E0, D_hd_code_803643E4, D_hd_code_803643E8, 0x13, 0x61A80);
            D_80364AC0 = 1;
        }
        D_80364AB4 += D_80364AB8;
        D_80364AB8 = (f32) ((f64) D_80364AB8 + 3.0);
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
    s16 sp62; // 0x5e

    sp8B = 0;
    func_hd_code_80255190();
    if ((D_8036B965 != 0) && (D_hd_code_80364A90 & 0x600)) {
        D_8036B965 = 0;
    }

    sp95 = D_80364AC1 && ((D_hd_code_80364A90 & 0x940) || D_8036B965);
    if (((D_hd_code_80364A90 == 8)) || ((D_8036BB18 == 0x4B) && (D_8036BB1C == 2) && D_hd_code_802F8BF4[D_8036BB18].id == 0x14D)) {
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
    if ((D_8036BB18 == 0x49) && (D_8036BB1C == 2) && (D_hd_code_802F8BF4[D_8036BB18].id == 0x130)) {
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
    if ((D_8036BB18 == 0x4D) && (D_8036BB1C == 2) && (D_hd_code_802F8BF4[D_8036BB18].id != 0x164)) {
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
    if ((D_8036BB18 == 0x58) && (D_8036BB1C != 8) && (D_hd_code_80364410 == 0)) {
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

    D_hd_code_80364412 |= sp95 || D_hd_code_80364A90 == 0x100;
    D_hd_code_80364412 |= D_hd_code_80358060 <= 1U;

    if ((D_hd_code_803643D6 != 0) && ((D_hd_code_80364A90 & 0x100000000600))) {
        spFC = 0.2f;
        spF8 = 0.1f;
        spF4 = 0.2f;
    } else {
        if ((D_8036BB1C == 2 && (D_8036BB18 == 0x4D || D_8036BB18 == 0x4B || D_8036BB18 == 0x49)) || ((D_hd_code_803643D7 != 0) && (D_hd_code_80364A90 & 0x100000000600) != 0) || D_hd_code_80364A90 == 8) {
            spFC = 0.08f;
            spF8 = 0.03f;
            spF4 = 0.08f;
        }
        else if ((D_hd_code_80364A90 & 0x1801) != 0) {
            spFC = 0.06f;
            spF8 = 0.03f;
            spF4 = 0.03f;
        } else {
            if (((D_80364AA8 == 0x10) || (D_80364AA8 == 0x40)) && (D_hd_code_80364A90 == 0x40)) {
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
    if ( (D_hd_code_80364A90 == 0x40) && (levelno == 0x3B)) {
        spFC = 1.0f;
        spF8 = 1.0f;
        spF4 = 1.0f;
        spF0 = 1.0f;
        spEC = 1.0f;
        spE8 = 1.0f;
    }

    switch(D_hd_code_80364A90) {

        case 0x100:
        case 0x200:
        case 0x400:
            D_8036509E = D_80364AC1 != 0 ? 0xFD : 0xFF;
            break;
        case 0x1:
        case 0x800:
        case 0x1000:
            D_8036509E = D_80364AC1 != 0 ? 0xFD : 0xFE;
            break;
        default:
            D_8036509E = (s16) D_hd_code_80364456;
            break;
    }
    sp96 = D_hd_code_8036443C;
    if (D_hd_code_803649EC == 0) {
        D_hd_code_8030F664 = func_hd_code_802A56C4();
    }
    if ((((D_hd_code_80364A90 & 0x2)) && (D_hd_code_802E8BF0 != 0)) || (D_hd_code_803649EC == 0)) {
        spCC = 0;
        spC8 = 0.0f;
        spC4 = 0.0f;
    } else {
        switch (D_8036509E) {                       /* switch 3; irregular */
        case 0x7:                                   /* switch 3 */
            spCC = 11;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0xEB;
            D_hd_code_80364A74 = -0xA5;
            break;
        case 0xA:                                   /* switch 3 */
            spCC = 9;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0xF5;
            D_hd_code_80364A74 = -0x87;
            break;
        case 0xB:                                   /* switch 3 */
        case 0x11:                                  /* switch 3 */
        case 0x12:                                  /* switch 3 */
            spCC = 11;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0xEB;
            D_hd_code_80364A74 = -0xA5;
            break;
        case 0x8:                                   /* switch 3 */
            spCC = 7;
            spC8 = 3.0f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0x14F;
            D_hd_code_80364A74 = -0xA5;
            break;
        case 0xF:                                   /* switch 3 */
            spCC = 7;
            spC8 = 3.0f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0x131;
            D_hd_code_80364A74 = -0xA5;
            break;
        case 0xD:                                   /* switch 3 */
            spCC = 7;
            spC8 = 3.0f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0x145;
            D_hd_code_80364A74 = -0xA5;
            break;
        case 0xE:                                   /* switch 3 */
            spCC = 7;
            spC8 = 3.0f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0x13B;
            D_hd_code_80364A74 = -0xA5;
            break;
        case 0x9:                                   /* switch 3 */
            spCC = 11;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0x3E8;
            D_hd_code_80364A72 = 0x87;
            D_hd_code_80364A74 = -0x55;
            break;
        case 0x6:                                   /* switch 3 */
            spCC = 11;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0x1388;
            D_hd_code_80364A72 = 0;
            D_hd_code_80364A74 = 0;
            break;
        case 0x5:                                   /* switch 3 */
            spCC = 9;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0xCD;
            D_hd_code_80364A74 = -0x69;
            break;
        case 0x4:                                   /* switch 3 */
            spCC = 9;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0xEB;
            D_hd_code_80364A74 = -0xA5;
            break;
        case 0x3:                                   /* switch 3 */
            spCC = 7;
            spC8 = 3.0f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0xEB;
            D_hd_code_80364A74 = -0xA5;
            break;
        case 0x2:                                   /* switch 3 */
            spCC = 11;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0x7D0;
            D_hd_code_80364A72 = 0x91;
            D_hd_code_80364A74 = -0x55;
            break;
        case 0x10:                                  /* switch 3 */
            spCC = 2;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0x258;
            D_hd_code_80364A72 = 0x91;
            D_hd_code_80364A74 = -0x55;
            break;
        case 0x1:                                   /* switch 3 */
            spCC = 11;
            spC8 = 0.75f;
            spC4 = 30.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0xCD;
            D_hd_code_80364A74 = -0xA5;
            break;
        case 0x0:                                   /* switch 3 */
            spCC = 0x14;
            spC8 = 0.25f;
            spC4 = 15.0f;
            D_hd_code_8030F664 = 0;
            D_hd_code_80364A72 = 0x55;
            D_hd_code_80364A74 = -0x19;
            break;
        case 0xFF:                                  /* switch 3 */
            spCC = 11;
            spC8 = 0.75f;
            spC4 = 30.0f;
            sp96 = (s16) (sp96 / 2);
            D_hd_code_80364A72 = 0;
            D_hd_code_80364A74 = 0;
            break;
        case 0xFE:                                  /* switch 3 */
            spCC = 11;
            spC8 = 0.75f;
            spC4 = 30.0f;
            sp96 = D_803EF328;
            D_hd_code_8030F664 = 0;
            D_hd_code_8036443E = D_803EF32A;
            D_hd_code_80364A72 = 0;
            D_hd_code_80364A74 = 0;
            break;
        case 0xFD:                                  /* switch 3 */
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
    if ( (D_hd_code_80364A90 == 0x40)) {
        spCC = spCC / 2;
    }
    if (sp96 > D_hd_code_80364A72 ) {
        sp96 = D_hd_code_80364A72;
    }
    if (sp96 < D_hd_code_80364A74) {
        sp96 = D_hd_code_80364A74;
    }
    if (((sp96 > 0) && (D_80370C1C != 0) && (D_hd_code_802E8BD0 == 0) && ((D_hd_code_80364A90 & 0x106))) || ((sp96 < 0) && (D_80370C1D != 0) && (D_hd_code_802E8BD0 == 0) && ((D_hd_code_80364A90 & 0x106)))) {
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
    spDE = (s16) (s32) (func_hd_code_80257514((f32) ((f64) ((f32) (s16) spE2 / 1024.0f) * 1.5708)) * ((f32) spCC * D_hd_code_80364444));
    spE0 = (s16) (s32) (func_hd_code_802574F0((f32) ((f64) ((f32) spE2 / 1024.0f) * 1.5708)) * ((f32) spCC * D_hd_code_80364444));
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

    switch(D_hd_code_80364A90) {
        case 0x100: {
            if (D_80364AC1 != 0) {
                if (D_hd_code_80364412 != 0) {
                    D_8036509C = D_803FCD68 * 0x10;
                } else {
                    D_8036509C = ((s16) (((u16) D_803FCD68 * 0x10) - D_8036509C) / 10) + (s16) D_8036509C;
                }
                D_hd_code_803643EC = (s32) (((f32) D_803FCD48 - (func_hd_code_802574F0((f32) ((f64) ((f32) (s16) D_8036509C / 16384.0f) * 1.5708)) * 8000.0f)) + (f32) spD8) << 11;
                D_hd_code_803643F0 = (D_803FCD4C + 0xDAC) << 11;
                D_hd_code_803643F4 = (s32) (((f32) D_803FCD50 - (func_hd_code_80257514((f32) ((f64) ((f32) (s16) D_8036509C / 16384.0f) * 1.5708)) * 8000.0f)) + (f32) spD4) << 11;
            } else {
                D_hd_code_803643EC = (D_803EF6DC + 0xFA0) << 11;
                D_hd_code_803643F0 = (D_803EF6E0 + 0x61A8) << 11;
                D_hd_code_803643F4 = (D_803EF6E4 + D_hd_code_80364A78 + 0x1B58) << 11;
            }
            break;
        }
        case 0x40: {
            switch ((u32) D_80364AA8) {             /* switch 4; irregular */
            case 0x1:                               /* switch 4 */
            case 0x80:                              /* switch 4 */
                if (D_hd_code_803643DB != 0) {
                    D_hd_code_803643EC = (D_803EF6DC + spD8) << 11;
                    D_hd_code_803643F0 = (D_803EF6E0 + 0x7D0) << 11;
                    D_hd_code_803643F4 = (D_803EF6E4 + spD4) << 11;
                }
                if (D_80364AC1 != 0) {
                    if ((u32) D_hd_code_80358060 < 2U) {
                        D_8036509C = D_803FCD68 * 0x10;
                    } else {
                        D_8036509C = ((s16) (((u16) D_803FCD68 * 0x10) - D_8036509C) / 10) + (s16) D_8036509C;
                    }
                    D_hd_code_803643EC = (s32) (((f32) D_803FCD48 - (func_hd_code_802574F0((f32) ((f64) ((f32) (s16) D_8036509C / 16384.0f) * 1.5708)) * 8000.0f)) + (f32) spD8) << 11;
                    D_hd_code_803643F0 = (D_803FCD4C + 0xDAC) << 11;
                    D_hd_code_803643F4 = (s32) (((f32) D_803FCD50 - (func_hd_code_80257514((f32) ((f64) ((f32) (s16) D_8036509C / 16384.0f) * 1.5708)) * 8000.0f)) + (f32) spD4) << 11;
                }
                if ((D_hd_code_803643DB == 0) && (D_80364AC1 == 0)) {
                case 0x4:                           /* switch 4 */
                case 0x8:                           /* switch 4 */
                    if (D_hd_code_80364412 == 0) {
                        D_8036509C = ((s16) (((u16) D_hd_code_8036443E * 0x10) - D_8036509C) / 10) + (s16) D_8036509C;
                    } else {
                        D_8036509C = D_hd_code_8036443E * 0x10;
                    }
                    D_hd_code_803643EC = (s32) (((f32) D_hd_code_803643E0 - (func_hd_code_802574F0((f32) ((f64) ((f32) (s16) D_8036509C / 16384.0f) * 1.5708)) * ((f32) D_hd_code_8036444C * 2.0f))) + (f32) spD8) << 11;
                    D_hd_code_803643F0 = (D_hd_code_8036444E + D_hd_code_803643E4) << 11;
                    D_hd_code_803643F4 = (s32) (((f32) D_hd_code_803643E8 - (func_hd_code_80257514((f32) ((f64) ((f32) (s16) D_8036509C / 16384.0f) * 1.5708)) * ((f32) D_hd_code_8036444C * 2.0f))) + (f32) spD4) << 11;
                }
                break;
            case 0x2:                               /* switch 4 */
            case 0x20:                              /* switch 4 */
                if (D_hd_code_80364412 == 0) {
                    D_8036509C = ((s16) (((u16) D_hd_code_8036443E * 0x10) - D_8036509C) / 10) + (s16) D_8036509C;
                } else {
                    D_8036509C = D_hd_code_8036443E * 0x10;
                }
                D_hd_code_803643EC = (s32) ((func_hd_code_802574F0((f32) ((f64) ((f32) (s16) D_8036509C / 16384.0f) * 1.5708)) * ((f32) D_hd_code_8036444C * 2.0f)) + (f32) D_hd_code_803643E0 + (f32) spD8) << 11;
                D_hd_code_803643F0 = (D_hd_code_8036444E + D_hd_code_803643E4 + (D_80370C2D * 0x32)) << 11;
                D_hd_code_803643F4 = (s32) ((func_hd_code_80257514((f32) ((f64) ((f32) (s16) D_8036509C / 16384.0f) * 1.5708)) * ((f32) D_hd_code_8036444C * 2.0f)) + (f32) D_hd_code_803643E8 + (f32) spD4) << 11;
                break;
            case 0x10:                              /* switch 4 */
            case 0x40:                              /* switch 4 */
                D_hd_code_803643EC = (((D_8036BED8[D_8036BBB0[D_8036EA7C]].x) << 5) + spD8) << 11;
                D_hd_code_803643F0 = (((D_8036BED8[D_8036BBB0[D_8036EA7C]].y) << 5) + 2000) << 11;
                D_hd_code_803643F4 = (((D_8036BED8[D_8036BBB0[D_8036EA7C]].z) << 5) + spD4) << 11;
                break;
            }
            break;
        }
        case 0x200: {
            if (D_80364AC1 != 0) {
                D_hd_code_803643EC = ((D_803FCD48 + spD8) - 0x1770) << 11;
                D_hd_code_803643F0 = (D_803FCD4C + 0xD48) << 11;
                D_hd_code_803643F4 = (D_803FCD50 + spD4 + 0x1770) << 11;
            } else if (D_hd_code_803643D6 != 0) {
                D_hd_code_803643EC = (D_803EF6DC + spD8 + 0x3E80) << 11;
                D_hd_code_803643F0 = (D_803EF6E0 + 0x3A98) << 11;
                D_hd_code_803643F4 = ((D_803EF6E4 + spD4) - 0xBB8) << 11;
            } else {
                D_hd_code_803643EC = (D_803EF6DC + spD8 + 0xFA0) << 11;
                D_hd_code_803643F0 = (D_803EF6E0 + 0x960) << 11;
                if (levelno == 0) {
                    D_hd_code_803643F0 = D_hd_code_803643F0 + 0x5DC000;
                }
                D_hd_code_803643F4 = ((D_803EF6E4 + spD4) - 0xFA0) << 11;
            }
            break;
        }
        case 0x400: {
            if (D_80364AC1 != 0) {
                D_hd_code_803643EC = (D_803FCD48 + spD8 + 0x1770) << 11;
                D_hd_code_803643F0 = (D_803FCD4C + 0xD48) << 11;
                D_hd_code_803643F4 = ((D_803FCD50 + spD4) - 0x1770) << 11;
            } else if (D_hd_code_803643D6 != 0) {
                D_hd_code_803643EC = ((D_803EF6DC + spD8) - 0x3E80) << 11;
                D_hd_code_803643F0 = (D_803EF6E0 + 0x3A98) << 11;
                D_hd_code_803643F4 = ((D_803EF6E4 - spD4) + 0xBB8) << 11;
            } else {
                D_hd_code_803643EC = ((D_803EF6DC + spD8) - 0xFA0) << 11;
                D_hd_code_803643F0 = (D_803EF6E0 + 0x960) << 11;
                if (levelno == 0) {
                    D_hd_code_803643F0 = D_hd_code_803643F0 + 0x5DC000;
                }
                D_hd_code_803643F4 = (D_803EF6E4 + spD4 + 0xFA0) << 11;
            }
            break;
        }


        case 0x1:
        case 0x800: {
            if (D_80364AC1 != 0) {
                if ((u32) D_hd_code_80358060 < 2U) {
                    D_8036509C = D_803FCD68 * 0x10;
                } else {
                    D_8036509C = ((s16) (((u16) D_803FCD68 * 0x10) - D_8036509C) / 10) + (s16) D_8036509C;
                }
                D_hd_code_803643EC = (s32) (((f32) D_803FCD48 - (func_hd_code_802574F0((f32) ((f64) ((f32) (s16) D_8036509C / 16384.0f) * 1.5708)) * 8000.0f)) + (f32) spD8) << 11;
                D_hd_code_803643F0 = (D_803FCD4C + 0xDAC) << 11;
                D_hd_code_803643F4 = (s32) (((f32) D_803FCD50 - (func_hd_code_80257514((f32) ((f64) ((f32) (s16) D_8036509C / 16384.0f) * 1.5708)) * 8000.0f)) + (f32) spD4) << 11;
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
                if (D_80364AA8 == 0x40) {
                    D_hd_code_8036444C = 0x2328;
                    D_hd_code_8036444E = 0x2AF8;
                    D_hd_code_80364420 = 0x2AF8;
                }
                if ((D_80364AC1 != 0) && (D_8036B8B0 != 0)) {
                    D_hd_code_803643EC = (D_803FCD48 + D_8036B8B4) << 11;
                    D_hd_code_803643F0 = (D_803FCD4C + D_8036B8B8) << 11;
                    D_hd_code_803643F4 = (D_803FCD50 + D_8036B8BC) << 11;
                } else if ((D_hd_code_803643DB != 0) && (D_8036B8B0 != 0)) {
                    D_hd_code_803643EC = (D_803EF6DC + D_8036B8B4) << 11;
                    D_hd_code_803643F0 = (D_803EF6E0 + D_8036B8B8) << 11;
                    D_hd_code_803643F4 = (D_803EF6E4 + D_8036B8BC) << 11;
                } else {
                    if (D_hd_code_8030F668.flag1 != 0) {
                        func_hd_code_80255034(0x9C4, D_hd_code_80364414, &sp90, &sp8C);
                        D_hd_code_803643EC = ((D_803F767C << 5) + sp90) << 11;
                        D_hd_code_803643F0 = ((D_803F767E << 5) + 0x1388) << 11;
                        D_hd_code_803643F4 = ((D_803F7680 << 5) + sp8C) << 11;
                    }
                    else if (D_hd_code_8030F668.flag3 != 0) {
                        func_hd_code_80255034(0x9C4, D_hd_code_80364414, &sp90, &sp8C);
                        D_hd_code_803643EC = (sp90 + D_803F7670) << 11;
                        D_hd_code_803643F0 = (D_803F7674 + 0x1388) << 11;
                        D_hd_code_803643F4 = (sp8C + D_803F7678) << 11;
                    } else if (D_hd_code_8030F668.flag2 != 0) {
                        if (D_8036C794 != NULL) {
                            func_hd_code_80255034(0x9C4, D_hd_code_80364414, &sp90, &sp8C);
                            D_hd_code_803643EC = (((s32) (D_8036C794[0] + D_8036C794[9]) / 2) << 16) + (sp90 << 11);
                            D_hd_code_803643F0 = (((s32) (D_8036C794[1] + D_8036C794[10]) / 2) << 16) + 0x9C4000;
                            D_hd_code_803643F4 = (((s32) (D_8036C794[2] + D_8036C794[11]) / 2) << 16) + (sp8C << 11);
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


    switch(D_hd_code_80364A90) {
        case 0x100:
            {
                if (D_80364AC1 != 0) {
                    D_80365078 = (f32) D_803FCD48 / 32.0f;
                    D_8036507C = (f32) (D_803FCD4C + 0x7D0) / 32.0f;
                    D_80365080 = (f32) D_803FCD50 / 32.0f;
                } else {
                    D_80365078 = (f32) D_803EF6DC / 32.0f;
                    D_8036507C = (f32) D_803EF6E0 / 32.0f;
                    D_80365080 = (f32) (D_803EF6E4 + D_hd_code_80364A78 + 0x2AF8) / 32.0f;
                }
                break;
            }
        case 0x200:
        case 0x400:
            {
                if (D_80364AC1 != 0) {
                    D_80365078 = (f32) (D_803FCD48 + spD8) / 32.0f;
                    D_8036507C = (f32) (D_803FCD4C + 0x7D0) / 32.0f;
                    D_80365080 = (f32) (D_803FCD50 + spD4) / 32.0f;
                } else {
                    D_80365078 = (f32) (D_803EF6DC + spD8) / 32.0f;
                    D_8036507C = (f32) D_803EF6E0 / 32.0f;
                    D_80365080 = (f32) (D_803EF6E4 + spD4) / 32.0f;
                }
                break;
            }
        case 0x1:
        case 0x800:
        case 0x1000:
            {
                if (D_80364AC1 != 0) {
                    D_80365078 = (f32) D_803FCD48 / 32.0f;
                    D_8036507C = (f32) (D_803FCD4C + 0x7D0) / 32.0f;
                    D_80365080 = (f32) D_803FCD50 / 32.0f;
                } else {
                    D_80365078 = (f32) (D_803EF2EC + spD8) / 32.0f;
                    D_8036507C = (f32) D_803EF314 / 32.0f;
                    D_80365080 = (f32) (D_803EF2F4 + spD4) / 32.0f;
                }
                break;
            }
        case 0x40:
            if (D_80364AC1 != 0) {
                D_80365078 = (f32) D_803FCD48 / 32.0f;
                D_8036507C = (f32) (D_803FCD4C + 0x7D0) / 32.0f;
                D_80365080 = (f32) D_803FCD50 / 32.0f;
            }
            else
        default:
            {
                if ((D_80364AC1 != 0) && (D_8036B8B0 != 0)) {
                    D_80365078 = (f32) D_803FCD48 / 32.0f;
                    D_8036507C = (f32) (D_803FCD4C + 0x1770) / 32.0f;
                    D_80365080 = (f32) D_803FCD50 / 32.0f;
                }
                else if ((D_hd_code_803643DB != 0) && (D_8036B8B0 != 0)) {
                    D_80365078 = (f32) D_803EF6DC / 32.0f;
                    D_8036507C = (f32) D_803EF6E0 / 32.0f;
                    D_80365080 = (f32) D_803EF6E4 / 32.0f;
                }
                else if (D_hd_code_8030F668.flag1 != 0) {
                    D_80365078 = (f32) D_803F767C;
                    D_8036507C = (f32) D_803F767E;
                    D_80365080 = (f32) D_803F7680;
                }
                else if (D_hd_code_8030F668.flag3 != 0) {
                    D_80365078 = (f32) D_803F7670 / 32.0f;
                    D_8036507C = (f32) D_803F7674 / 32.0f;
                    D_80365080 = (f32) D_803F7678 / 32.0f;
                }
                else if (D_hd_code_8030F668.flag2 != 0) {
                    if (D_8036C794 != NULL) {
                        D_80365078 = (f32) ((f64) (f32) (D_8036C794[0] + D_8036C794[9]) / 2.0);
                        D_8036507C = (f32) ((f64) (f32) (D_8036C794[1] + D_8036C794[10]) / 2.0);
                        D_80365080 = (f32) ((f64) (f32) (D_8036C794[2] + D_8036C794[11]) / 2.0);
                    }
                } else {
                    D_80365078 = (f32) (D_hd_code_803643E0 + spD8) / 32.0f;
                    D_8036507C = (f32) (D_hd_code_803643E4 + D_hd_code_8030F664) / 32.0f;
                    D_80365080 = (f32) (D_hd_code_803643E8 + spD4) / 32.0f;
                }
            }
            break;
    }


    if ((D_hd_code_803643D6 != 0) && (levelno == 0x31)) {
        D_hd_code_803643EC = (D_803EF6DC + spD8 + 0x3E80) << 11;
        D_hd_code_803643F0 = (D_803EF6E0 + 0x3A98) << 11;
        D_hd_code_803643F4 = ((D_803EF6E4 + spD4) - 0xBB8) << 11;
    }
    if ((D_80364AC1 != 0) && (D_8036B965 != 0)) {
        if (D_hd_code_80364412 != 0) {
            D_8036509C = D_803FCD68 * 0x10;
        } else {
            D_8036509C = ((s16) (((u16) D_803FCD68 * 0x10) - D_8036509C) / 10) + (s16) D_8036509C;
        }
        D_hd_code_803643EC = (s32) (((f32) D_803FCD48 - (func_hd_code_802574F0((f32) ((f64) ((f32) (s16) D_8036509C / 16384.0f) * 1.5708)) * 8000.0f)) + (f32) spD8) << 11;
        D_hd_code_803643F0 = (D_803FCD4C + 0xDAC) << 11;
        D_hd_code_803643F4 = (s32) ((D_803FCD50 - (func_hd_code_80257514((f32) ((f64) ((f32) (s16) D_8036509C / 16384.0f) * 1.5708)) * 8000.0f)) + (f32) spD4) << 11;
        D_80365078 = (f32) D_803FCD48 / 32.0f;
        D_8036507C = (f32) (D_803FCD4C + 0x7D0) / 32.0f;
        D_80365080 = D_803FCD50 / 32.0f;
    }
    if ( (D_hd_code_80364A90 == 0x40) && (levelno == 0x3B)) {
        D_hd_code_803643EC = (D_hd_code_803643E0 + 0x1900) << 11;
        D_hd_code_803643F0 = (D_hd_code_803643E4 + 0x3070) << 11;
        D_hd_code_803643F4 = (D_hd_code_803643E8 - 0x1900) << 11;
        D_80365078 = (f32) D_hd_code_803643E0 / 32.0f;
        D_8036507C = (f32) D_hd_code_803643E4 / 32.0f;
        D_80365080 = (f32) D_hd_code_803643E8 / 32.0f;
    }
    if (((D_hd_code_80364A90 & 0x2000000000002104) ) && (D_8036B8B0 == 0) && (sp95 == 0) && ((D_hd_code_80364A90 != 0x100)) && (levelno != 0x23) && (D_hd_code_80364A85 == 0)) {
        sp70 = (s32) ((f64) D_80365078 * 65536.0);
        sp6C = (s32) ((f64) D_8036507C * 65536.0);
        sp68 = (s32) ((f64) D_80365080 * 65536.0);
        if ((levelno == 0x10) && (8718.0f < D_80365078) && (D_80365078 < 8919.0f) && (9051.0f < D_80365080) && (D_80365080 < 9251.0f)) {
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
        D_803650A0 = !D_8036509E;
    }

    if ((D_hd_code_80364424 != 0) && (((D_hd_code_80364414 < 134.0)) || (D_hd_code_80364414 > 136.0))) {
        func_hd_code_802CE4F0((s32) D_hd_code_803643F8 >> 0xB, (s32) D_hd_code_803643FC >> 0xB, (s32) D_hd_code_80364400 >> 11);
        func_hd_code_802CE5BC((s32) D_hd_code_803643F8 >> 0xB, (s32) D_hd_code_803643FC >> 0xB, (s32) D_hd_code_80364400 >> 0xB, D_hd_code_80364434 ? D_hd_code_80364430 : D_hd_code_80364430 + 0x640, 0xBE, 0);
        if (D_hd_code_80364434 != 0) {
            if (D_803A7424 != 0) {
                D_hd_code_80364420 += D_hd_code_8036442C;
                if ((u32) D_hd_code_80364428 < D_hd_code_80364420) {
                    D_hd_code_80364420 = D_hd_code_80364428;
                }
                D_hd_code_80364434 = 1;
            } else {
                D_hd_code_80364434 = 0;
            }
        } else if (D_803A7424 != 0) {
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
    if ((D_8036509E != D_803650A0) || (sp8B != 0)) {
        D_80365090.x = D_80365084 - D_80365078;
        D_80365090.y = D_80365088 - D_8036507C;
        D_80365090.z = D_8036508C - D_80365080;
        D_803650A0 = D_8036509E;
        D_hd_code_8030F660 = 0;
    }
    if ((D_hd_code_8030F660 == 0) && (D_hd_code_80364412 == 0)) {
        D_80365090.x = D_80365090.x * 0.95;
        D_80365084 = D_80365090.x + D_80365078;

        D_80365090.y = D_80365090.y * 0.97;
        D_80365088 = D_80365090.y + D_8036507C;

        D_80365090.z = D_80365090.z * 0.95;
        D_8036508C = D_80365090.z + D_80365080;

        if (D_80365090.x < 0.1  &&
            D_80365090.x > -0.1 &&
            D_80365090.z < 0.1 &&
            D_80365090.z > -0.1 &&
            D_80365090.y < 0.1 &&
            D_80365090.y > -0.1) {
            D_hd_code_8030F660 = 1;
        }
    } else {
        D_80365084 = D_80365078;
        D_80365088 = D_8036507C;
        D_8036508C = D_80365080;
        D_hd_code_8030F660 = 1;
    }
    if (D_hd_code_802E8BE8 == 0) {
        D_hd_code_802E8BE8 = 1;
    }
    if ((D_hd_code_802E8BE4 != 0) && ((D_hd_code_80364A90 & 0x2000100000000206))) {
        // 802D4B7C = ull_rem
        // 802D4BB8 = ull_div
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
    if ((D_hd_code_80364A90 & 2) &&
        (D_hd_code_802E8BF0 != 0) &&
        (D_hd_code_80358060 > D_80366A04 )) {
        spB4 = ((spB4 - D_80365084) * D_hd_code_803649F8) + D_80365084;
        spB0 = ((spB0 - D_80365088) * D_hd_code_803649F8) + D_80365088;
        spAC = ((spAC - D_8036508C) * D_hd_code_803649F8) + D_8036508C;
        if (D_hd_code_803649F8 > 0.4) {
            D_hd_code_803649F8 = D_hd_code_803649F8 - 0.01;
        }
    }
    sp7C = (f32)((D_80365084 * 32.0f) + spC0) / 32.0f;
    sp78 = (f32)((D_8036508C * 32.0f) + spB8) / 32.0f;
    sp84 = (spB4 - sp7C);

    if (sp84 < 0.0) {
        sp84 = 0.0-sp84;
    }
    sp80 = spAC - sp78;
    if (sp80 < 0.0) {
        sp80 = 0.0-sp80;
    }
    if (((f64) sp84 > 0.5) || ((f64) sp80 > 0.5)) {
        func_hd_code_802D5F60(arg0, arg1, spB4, spB0, spAC, ((D_80365084 * 32.0f) + (f32) spC0) / 32.0f, ((D_80365088 * 32.0f) + (f32) spBC) / 32.0f, ((D_8036508C * 32.0f) + (f32) spB8) / 32.0f, 0.0f, 1.0f, 0.0f);
    } else {
        func_hd_code_802D5F60(arg0, arg1, (f32) ((f64) spB4 + 2.0), spB0, (f32) ((f64) spAC + 2.0), ((D_80365084 * 32.0f) + (f32) spC0) / 32.0f, ((D_80365088 * 32.0f) + (f32) spBC) / 32.0f, ((D_8036508C * 32.0f) + (f32) spB8) / 32.0f, 0.0f, 1.0f, 0.0f);
    }
    sp98 = sqrtf(((spB4 - D_80365084) * (spB4 - D_80365084)) + ((spAC - D_8036508C) * (spAC - D_8036508C)));
    if (sp98 < 1.0) {
        sp98 = 1.0;
    }
    if ((spB4 >= D_80365084) && (spAC >= D_8036508C)) {
        D_hd_code_80364452 = (func_hd_code_802AD7D4((s32) (((f64) (spB4 - D_80365084) * 65535.9) / (f64) sp98)) >> 4),
        sp67 = 0;
    }
    if ((spB4 >= D_80365084) && (spAC < D_8036508C)) {
        D_hd_code_80364452 = 0x400 + (func_hd_code_802AD7D4((s32) (((f64) (D_8036508C - spAC) * 65535.9) / (f64) sp98)) >> 4),
        sp67 = 1;
    }
    if ((spB4 < D_80365084) && (spAC < D_8036508C)) {
        D_hd_code_80364452 = (func_hd_code_802AD7D4((s32) (((f64) (D_80365084 - spB4) * 65535.9) / (f64) sp98)) >> 4) + 0x800,
        sp67 = 2;
    }
    if ((spB4 < D_80365084) && (spAC >= D_8036508C)) {
        D_hd_code_80364452 = (func_hd_code_802AD7D4((s32) (((f64) (spAC - D_8036508C) * 65535.9) / (f64) sp98)) >> 4) + 0xC00,
        sp67 = 3;
    }
    sp98 = sqrtf(((spB4 - D_80365084) * (spB4 - D_80365084)) + ((spAC - D_8036508C) * (spAC - D_8036508C)) + ((spB0 - D_80365088) * (spB0 - D_80365088)));
    if (spB0 >= D_80365088) {
        sp62 = (s16) (func_hd_code_802AD7D4((s32) (((f64) (spB0 - D_80365088) * 65535.9) / (f64) sp98)) >> 3);
    } else {
        sp62 = 0x1000 - (func_hd_code_802AD7D4((s32) (((f64) (D_80365088 - spB0) * 65535.9) / (f64) sp98)) >> 3);
    }
    if (spB0 >= D_80365088) {
        sp64 =          (func_hd_code_802AD7D4((s32) (65535.0 < (((f64) (spB0 - D_80365088) * 65535.9) / 20000.0) ? (65535.0) : (((f64) (spB0 - D_80365088) * 65535.9) / 20000.0))) >> 3);
    } else {
        sp64 = 0x1000 - (func_hd_code_802AD7D4((s32) (65535.0 < (((f64) (D_80365088 - spB0) * 65535.9) / 20000.0) ? (65535.0) : (((f64) (D_80365088 - spB0) * 65535.9) / 20000.0))) >> 3);
    }
    D_hd_code_80364454 = sp62 - sp64;
    sp9C = func_hd_code_80254E54(spB4, spB0, spAC, D_80365084, D_80365088, D_8036508C);
    spA8 = ((spB4 - D_80365084) * sp9C) + D_80365084;
    spA4 = ((spB0 - D_80365088) * sp9C) + D_80365088;
    spA0 = ((spAC - D_8036508C) * sp9C) + D_8036508C;
    if (((f64) sp84 > 0.5) || ((f64) sp80 > 0.5)) {
        func_hd_code_802D62A8(arg2, spA8, spA4, spA0, D_80365084, D_80365088, D_8036508C, 0.0f, 1.0f, 0.0f);
    } else {
        func_hd_code_802D62A8(arg2, (f32) ((f64) spA8 + 2.0), spA4, (f32) ((f64) spA0 + 2.0), D_80365084, D_80365088, D_8036508C, 0.0f, 1.0f, 0.0f);
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
        if ((sp1F != 0) && (((D_80370C21 != 0) && (D_80370C27 == 0)) || ((D_80370C1E != 0) && (D_80370C24 == 0))) && ((D_hd_code_80364A90 & 0x104))) {
            sndPlaySfx(D_80367738, 0xD0U, NULL);
        }
        if ((D_80370C21 != 0) && (D_80370C27 == 0) && (D_8036441C == 0) && (D_8036441D == 0) && (sp1F == 0) && ((D_hd_code_80364A90 != 0x2000))) {
            D_80364418 = (f32) ((f64) D_hd_code_80364414 + 45.0);
            if (D_80364418 >= 360.0) {
                D_80364418 = (f64)D_80364418 - 360.0;
            }
            D_8036441C = 1;
            if (D_hd_code_80364A90 != 0x40) {
                sndPlaySfx(D_80367738, 0xDDU, NULL);
            }
        }
        if (D_8036441C != 0) {
            if (D_hd_code_80364414 < D_80364418) {
                D_hd_code_80364414 = (f32) ((f64) D_hd_code_80364414 + 3.0);
                if (D_80364418 <= D_hd_code_80364414) {
                    D_8036441C = 0;
                    D_hd_code_80364414 = D_80364418;
                }
            } else {
                D_hd_code_80364414 = (f32) ((f64) D_hd_code_80364414 + 3.0);
                if (D_hd_code_80364414 >= 360.0) {
                    D_hd_code_80364414 = (f32) ((f64) D_hd_code_80364414 - 360.0);
                    if (D_80364418 <= D_hd_code_80364414) {
                        D_8036441C = 0;
                        D_hd_code_80364414 = D_80364418;
                    }
                }
            }
        }
        if ((D_80370C1E != 0) && (D_80370C24 == 0) && (D_8036441C == 0) && (D_8036441D == 0) && (sp1F == 0) && (D_hd_code_80364A90 != 0x2000)) {
            D_80364418 = D_hd_code_80364414 - 45.0;
            if (D_80364418 < 0.0) {
                D_80364418 = (f32) (D_80364418 + 360.0);
            }
            D_8036441D = 1;
            if (D_hd_code_80364A90 != 0x40) {
                sndPlaySfx(D_80367738, 0xDCU, NULL);
            }
        }
        if (D_8036441D != 0) {
            if (D_hd_code_80364414 > D_80364418) {
                D_hd_code_80364414 = (f32) ((f64) D_hd_code_80364414 - 3.0);
                if (D_hd_code_80364414 <= D_80364418) {
                    D_8036441D = 0;
                    D_hd_code_80364414 = D_80364418;
                }
            } else {
                D_hd_code_80364414 = D_hd_code_80364414 - 3.0;
                if (D_hd_code_80364414 < 0.0) {
                    D_hd_code_80364414 = (f32) (D_hd_code_80364414 + 360.0);
                    if (D_hd_code_80364414 <= D_80364418) {
                        D_8036441D = 0;
                        D_hd_code_80364414 = D_80364418;
                    }
                }
            }
        }
        if ((D_8036441D != 0) || (D_8036441C != 0)) {
            func_hd_code_802A45D4(2);
        }
    }
}

u8 func_hd_code_80255628(void) {
  u8 sp37;

  sp37 = 0;
  if (((D_hd_code_80364A90 == 0x100000000000) ) || ((D_hd_code_80364A90 == 2) )) {
    sp37 = 1;
  } else {
    switch (levelno) {                   /* irregular */
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
  if (sp37 != 0 && ((D_80364418 < 134.0) || (D_80364418 > 136.0))) {
    D_8036441D = 0;
    D_8036441C = 0;
    D_80364418 = 135.0f;
    if (D_hd_code_80364414 > D_80364418) {
      if ((D_hd_code_80364414 - D_80364418) > 180.0 ) {
        D_8036441C = 1;
      } else {
        D_8036441D = 1;
      }
    } else {
      D_8036441C = 1;
    }
  }
  return sp37;
}

void func_hd_code_802558C8(Gfx* gfx, s32* arg1) {
  Gfx *gfx2 = gfx;
  gDPPipeSync(gfx2++);
  gDPSetCycleType(gfx2++, G_CYC_FILL);
  gDPSetColorImage(gfx2++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, D_80358050[D_8035805C]);
  gDPSetFillColor(gfx2++, 0x00010001);
  gDPPipeSync(gfx2++);
  gDPFillRectangle(gfx2++, 0, 0, 319, 239);

  *arg1 += (s32) (gfx2 - gfx);
}

void func_hd_code_802559F8(Gfx* gfx, s32* length) {
  Gfx *entry = gfx;

  gDPFullSync(entry++);
  gSPEndDisplayList(entry++);

  *length = (s32) (((s32)entry - (s32)&D_803156F8[D_8035805C]) - 0x48B0) >> 3;
  if (*length >= TOPLEVEL_DL_SIZE) {
    func_hd_code_8029A7E4("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "*length<TOPLEVEL_DL_SIZE", "hd.c", 0xE51);
  }
}

void func_hd_code_80255AD0(void) {
    s32 sp44;
    f32 sp40;
    s64 pad1;
    s64 pad2;
    u8 sp2F;

    sp40 = 1.0f;
    D_hd_code_80364A90 = 0x20;
    osCreateMesgQueue(&D_803150A0, &D_803150B8, 0x32);
    osCreateMesgQueue(&D_80315180, &D_80315198, 0x90);
    func_hd_code_80270D20(&D_80315440, &D_80312D80 + 0x800, 0xD, D_80000300 != 1 ? 16 : 2, 1);
    osCreateMesgQueue(&D_803153D8, &D_803153F8, 0x10);
    func_hd_code_80270E50(&D_80315440, &D_803156D8, &D_803153D8, 1, 1);
    sp2F = func_hd_code_8028A370();
    func_hd_code_80261588();
    func_hd_code_8029A7E4("audio inited\n");
    osViSetSpecialFeatures(2);
    osViSetSpecialFeatures(0x40);
    D_80358050[0] = VIRTUAL_TO_PHYSICAL(&D_80000400);
    D_80358050[1] = VIRTUAL_TO_PHYSICAL(&D_80000400 + 0x9600);
    D_80358058 = VIRTUAL_TO_PHYSICAL(&func_init_8021ED00);
    func_hd_code_80284DB0();
    osWriteBackDCacheAll();
    func_hd_code_8028FC10();
    if (!(sp2F & 1)) {
        D_80364A98 = 0x0800000000000000;
    } else if (D_hd_code_802FDBD0 != 0) {
        D_80364A98 = 0x0000080000000000;
    } else if (D_hd_code_802FDBD4 != 0) {
        D_80364A98 = 0x0040000000000000;
    } else {
        D_80364A98 = 0x10;
    }
    for(sp44 = 0x1FF; sp44 >= 0; sp44--) {
        D_80310D80[sp44] = 0x1122334455667788;
    }
}

void func_hd_code_80255D34(void) {
  u8 sp1F;
  s32 sp18;

  sp1F = 0;
  for(sp18 = 0x1FF; sp18 >= 0 && sp1F == 0; sp18--) {
    if (D_80310D80[sp18] != 0x1122334455667788) {
      sp1F = 1;
      func_hd_code_8029A7E4("stack end =%d\n", sp18);
    }
  }
}

void func_hd_code_80255DC8(void) {
    void* sp2C;
    s32 pad;
    s32 sp24;
    Gfx* sp20;

    sp24 = (s32)&D_788000 - (s32)&D_787F40;
    osViBlack(1);
    D_80364A70 = func_hd_code_80261A44(D_80364A98);
    osWriteBackDCacheAll();
    osInvalDCache(0x80000000, 0x400000);
    D_803649F4 = 0;
    D_80358068 = 0;
    D_80358064 = 0;
    D_hd_code_80358060 = 0;
    D_8035805C = 0;
    D_80367BD6 = 0;
    func_hd_code_8026A8BC();
    func_hd_code_8026A974();
    func_hd_code_8028AE88();
    func_hd_code_8028B720();
    D_8035806C = &D_803FF600;
    InitiateDma(&D_787F40, &D_803FF600, &sp24, 0xA, 0, 2);
    sp2C = ((s32)&D_788000 - (s32)&D_787F40) + (s32)&D_803FF600;
    func_hd_code_8029A7E4("Static end = 0x%x, space=0x%x (%d) bytes\n", sp2C, 0x80400000 - (s32)sp2C, 0x80400000 - (s32)sp2C);
    D_80358078 = 0;
    func_hd_code_802558C8(D_803156F8[D_8035805C].dp, &D_80358078);
    func_hd_code_802559F8(D_803156F8[D_8035805C].dp, &D_80358078);
    D_80358070 = (u8*)0x8004B400;
    func_hd_code_80257490((u8**)(&D_80358070), 0x10); // TODO: Crazy convert
    D_8036E694 = D_80358070;
    D_80358070 += 0x1400 * 8;
    if ((D_hd_code_802E8F94[levelno].unk0 == 2) && !(D_80364A98 & 0x0000100000000002)) {
        func_hd_code_8029A7E4("Allocating ghost buffer memory\n");
        D_80358070 += 0x4000 * 8;
    }
    D_803B9888 = 0;
    func_hd_code_802A0700();
    D_803643C8.textures = (struct Texture* ) ((s32) (&D_80358088 + 0x10) & ~0x3F);
    func_hd_code_80278E3C();
    D_803643D9 = 0;
    D_803643DA = 0;
    D_803643D8 = 0;
    D_hd_code_803643D6 = 0;
    D_hd_code_803643D7 = 0;
    D_hd_code_802E8BD8 = 0;
    D_hd_code_802E8BD4 = 0;
    D_hd_code_802E8BD0 = 0;
    D_8036EB99 = 0;
    D_803669B4 = 0;
    if (D_80364A98 & 0xC9FD8FE7FBFFC0B0) {
        func_hd_code_8028B3E0();
    }
    func_hd_code_80297530(levelno);
    func_hd_code_80272C50();
    if ((D_80364A98 == 0x40000000000)) {
        func_801F7850();
    }
    sp20 = D_80358070;
    func_hd_code_8026B118(0);
    func_hd_code_8029A7E4("Yoshi windows allocated %d bytes, %x\n", (u32)D_80358070 - (u32)sp20, D_80358070);
    D_803649D0 = D_80364460;
    func_hd_code_8028A42C();
    func_hd_code_802592F0();
    D_8039CAA2 = 0;
}

//region Level Addresses
extern u8 D_4A5660;
extern u8 D_4ACC10;
extern u8 D_4B8960;
extern u8 D_4BFD60;
extern u8 D_4C3AC0;
extern u8 D_4D5F90;
extern u8 D_4E2F70;
extern u8 D_4E4E80;
extern u8 D_4E7C00;
extern u8 D_4E8F70;
extern u8 D_4F5C10;
extern u8 D_500520;
extern u8 D_507E80;
extern u8 D_511340;
extern u8 D_523080;
extern u8 D_52CD00;
extern u8 D_532700;
extern u8 D_53E9B0;
extern u8 D_54A820;
extern u8 D_552DE0;
extern u8 D_555000;
extern u8 D_560E90;
extern u8 D_5652D0;
extern u8 D_56F3F0;
extern u8 D_5721E0;
extern u8 D_5736E0;
extern u8 D_57A2C0;
extern u8 D_580B60;
extern u8 D_588CE0;
extern u8 D_58BE80;
extern u8 D_597B80;
extern u8 D_59B7D0;
extern u8 D_5A5840;
extern u8 D_5B0B10;
extern u8 D_5B5A30;
extern u8 D_5B8BB0;
extern u8 D_5C4C80;
extern u8 D_5CA9C0;
extern u8 D_5CCF50;
extern u8 D_5D1060;
extern u8 D_5DC830;
extern u8 D_5E6EE0;
extern u8 D_5EC800;
extern u8 D_5F3A80;
extern u8 D_6014B0;
extern u8 D_60A710;
extern u8 D_613AA0;
extern u8 D_61DD70;
extern u8 D_621AF0;
extern u8 D_6269E0;
extern u8 D_630C30;
extern u8 D_635700;
extern u8 D_63CA10;
extern u8 D_641F30;
extern u8 D_644810;
extern u8 D_646080;
extern u8 D_647550;
extern u8 D_654FC0;
extern u8 D_660950;
extern u8 D_665F80;
extern u8 D_66C900;
//endregion

void LoadLevel(u32 arg0, void* arg1, s32* arg2) {
    u8* sp24;

    switch (arg0) {
    case 0x1:
        sp24 = &D_4A5660;
        *arg2 = &D_4ACC10 - &D_4A5660;
        break;
    case 0x0:
        sp24 = &D_4ACC10;
        *arg2 = &D_4B8960 - &D_4ACC10;
        break;
    case 0x2:
        sp24 = &D_4B8960;
        *arg2 = &D_4BFD60 - &D_4B8960;
        break;
    case 0x3:
        sp24 = &D_4BFD60;
        *arg2 = &D_4C3AC0 - &D_4BFD60;
        break;
    case 0x4:
        sp24 = &D_4C3AC0;
        *arg2 = &D_4D5F90 - &D_4C3AC0;
        break;
    case 0x5:
        sp24 = &D_4D5F90;
        *arg2 = &D_4E2F70 - &D_4D5F90;
        break;
    case 0x6:
        sp24 = &D_4E2F70;
        *arg2 = &D_4E4E80 - &D_4E2F70;
        break;
    case 0x7:
        sp24 = &D_4E4E80;
        *arg2 = &D_4E7C00 - &D_4E4E80;
        break;
    case 0x8:
        sp24 = &D_4E7C00;
        *arg2 = &D_4E8F70 - &D_4E7C00;
        break;
    case 0x9:
        sp24 = &D_4E8F70;
        *arg2 = &D_4F5C10 - &D_4E8F70;
        break;
    case 0xA:
        sp24 = &D_4F5C10;
        *arg2 = &D_500520 - &D_4F5C10;
        break;
    case 0xB:
        sp24 = &D_500520;
        *arg2 = &D_507E80 - &D_500520;
        break;
    case 0xC:
        sp24 = &D_507E80;
        *arg2 = &D_511340 - &D_507E80;
        break;
    case 0xD:
        sp24 = &D_511340;
        *arg2 = &D_523080 - &D_511340;
        break;
    case 0xE:
        sp24 = &D_523080;
        *arg2 = &D_52CD00 - &D_523080;
        break;
    case 0xF:
        sp24 = &D_52CD00;
        *arg2 = &D_532700 - &D_52CD00;
        break;
    case 0x10:
        sp24 = &D_532700;
        *arg2 = &D_53E9B0 - &D_532700;
        break;
    case 0x11:
        sp24 = &D_53E9B0;
        *arg2 = &D_54A820 - &D_53E9B0;
        break;
    case 0x12:
        sp24 = &D_54A820;
        *arg2 = &D_552DE0 - &D_54A820;
        break;
    case 0x13:
        sp24 = &D_552DE0;
        *arg2 = &D_555000 - &D_552DE0;
        break;
    case 0x14:
        sp24 = &D_555000;
        *arg2 = &D_560E90 - &D_555000;
        break;
    case 0x15:
        sp24 = &D_560E90;
        *arg2 = &D_5652D0 - &D_560E90;
        break;
    case 0x16:
        sp24 = &D_5652D0;
        *arg2 = &D_56F3F0 - &D_5652D0;
        break;
    case 0x17:
        sp24 = &D_56F3F0;
        *arg2 = &D_5721E0 - &D_56F3F0;
        break;
    case 0x18:
        sp24 = &D_5721E0;
        *arg2 = &D_5736E0 - &D_5721E0;
        break;
    case 0x19:
        sp24 = &D_5736E0;
        *arg2 = &D_57A2C0 - &D_5736E0;
        break;
    case 0x1A:
        sp24 = &D_57A2C0;
        *arg2 = &D_580B60 - &D_57A2C0;
        break;
    case 0x1B:
        sp24 = &D_580B60;
        *arg2 = &D_588CE0 - &D_580B60;
        break;
    case 0x1C:
        sp24 = &D_588CE0;
        *arg2 = &D_58BE80 - &D_588CE0;
        break;
    case 0x1D:
        sp24 = &D_58BE80;
        *arg2 = &D_597B80 - &D_58BE80;
        break;
    case 0x1E:
        sp24 = &D_597B80;
        *arg2 = &D_59B7D0 - &D_597B80;
        break;
    case 0x1F:
        sp24 = &D_59B7D0;
        *arg2 = &D_5A5840 - &D_59B7D0;
        break;
    case 0x20:
        sp24 = &D_5A5840;
        *arg2 = &D_5B0B10 - &D_5A5840;
        break;
    case 0x21:
        sp24 = &D_5B0B10;
        *arg2 = &D_5B5A30 - &D_5B0B10;
        break;
    case 0x22:
        sp24 = &D_5B5A30;
        *arg2 = &D_5B8BB0 - &D_5B5A30;
        break;
    case 0x23:
        sp24 = &D_5B8BB0;
        *arg2 = &D_5C4C80 - &D_5B8BB0;
        break;
    case 0x24:
        sp24 = &D_5C4C80;
        *arg2 = &D_5CA9C0 - &D_5C4C80;
        break;
    case 0x25:
        sp24 = &D_5CA9C0;
        *arg2 = &D_5CCF50 - &D_5CA9C0;
        break;
    case 0x26:
        sp24 = &D_5CCF50;
        *arg2 = &D_5D1060 - &D_5CCF50;
        break;
    case 0x27:
        sp24 = &D_5D1060;
        *arg2 = &D_5DC830 - &D_5D1060;
        break;
    case 0x28:
        sp24 = &D_5DC830;
        *arg2 = &D_5E6EE0 - &D_5DC830;
        break;
    case 0x29:
        sp24 = &D_5E6EE0;
        *arg2 = &D_5EC800 - &D_5E6EE0;
        break;
    case 0x2A:
        sp24 = &D_5EC800;
        *arg2 = &D_5F3A80 - &D_5EC800;
        break;
    case 0x2B:
        sp24 = &D_5F3A80;
        *arg2 = &D_6014B0 - &D_5F3A80;
        break;
    case 0x2C:
        sp24 = &D_6014B0;
        *arg2 = &D_60A710 - &D_6014B0;
        break;
    case 0x2D:
        sp24 = &D_60A710;
        *arg2 = &D_613AA0 - &D_60A710;
        break;
    case 0x2E:
        sp24 = &D_613AA0;
        *arg2 = &D_61DD70 - &D_613AA0;
        break;
    case 0x2F:
        sp24 = &D_61DD70;
        *arg2 = &D_621AF0 - &D_61DD70;
        break;
    case 0x30:
        sp24 = &D_621AF0;
        *arg2 = &D_6269E0 - &D_621AF0;
        break;
    case 0x31:
        sp24 = &D_6269E0;
        *arg2 = &D_630C30 - &D_6269E0;
        break;
    case 0x32:
        sp24 = &D_630C30;
        *arg2 = &D_635700 - &D_630C30;
        break;
    case 0x33:
        sp24 = &D_635700;
        *arg2 = &D_63CA10 - &D_635700;
        break;
    case 0x34:
        sp24 = &D_63CA10;
        *arg2 = &D_641F30 - &D_63CA10;
        break;
    case 0x35:
        sp24 = &D_641F30;
        *arg2 = &D_644810 - &D_641F30;
        break;
    case 0x36:
        sp24 = &D_644810;
        *arg2 = &D_646080 - &D_644810;
        break;
    case 0x37:
        sp24 = &D_646080;
        *arg2 = &D_647550 - &D_646080;
        break;
    case 0x38:
        sp24 = &D_647550;
        *arg2 = &D_654FC0 - &D_647550;
        break;
    case 0x39:
        sp24 = &D_654FC0;
        *arg2 = &D_660950 - &D_654FC0;
        break;
    case 0x3A:
        sp24 = &D_660950;
        *arg2 = &D_665F80 - &D_660950;
        break;
    case 0x3B:
        sp24 = &D_665F80;
        *arg2 = &D_66C900 - &D_665F80;
    }
    InitiateDma(sp24, arg1, arg2, 0xCU, 0xA, 1);
}

void func_hd_code_80256A34(s32* arg0) {
    s32 sp4C;
    s32 sp48;
    struct Texture* sp44;
    u8 sp43;
    Gfx* sp3C;

    D_80364A68 = 0;
    D_80364A69 = 0;
    D_80364A6A = 0;
    D_80364A6B = 0;
    D_80364A6C = 0;
    D_80364A6D = 0;
    D_803649E8 = 0;
    D_hd_code_803649EC = 0;
    D_803643C8.end = D_803643C8.textures;
    D_80364AA8 = (s32)D_hd_code_802E8F94[levelno].unk0;
    D_hd_code_802E8BE4 = 0;
    D_hd_code_802E8BE8 = 0;
    D_hd_code_803643E0 = 0;
    D_hd_code_803643E4 = 0;
    D_hd_code_803643E8 = 0;
    D_hd_code_8036443C = 0;
    D_hd_code_80364414 = 135.0f;
    D_80364418 = 135.0f;
    D_8036441C = 0;
    D_8036441D = 0;
    D_hd_code_80364420 = 0xBB8;
    D_hd_code_80364434 = 1;
    D_803A7430 = 0;
    D_803649EE = 0;
    D_80364A84 = 0;
    D_hd_code_80364456 = 0;
    if (D_80370C50 != 0) {
        if (D_8039C4B0 != 0) {
            func_hd_code_8029A7E4("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "!pakBusy", "hd.c", 0x1042);
        }
        if (D_80219F58 != 0) {
            func_hd_code_8029A7E4("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "MQ_IS_EMPTY(&pakToGameMessageQ)", "hd.c", 0x1043);
        }
        func_hd_code_80270ECC(&D_80315440, &D_80218EE0);
        osDestroyThread(&D_80218D30);
    }
    D_8039CA62 = 0;
    D_8039CA61 = 0;
    if (D_80364AA8 == 2 && (D_80364A98 == 0x2000)) {
        if (D_8039CA60 == 0) {
            func_hd_code_80294E30();
        }
        func_hd_code_80294E88();
        func_hd_code_80294EB8();
    }
    LoadLevel(levelno, D_80358070, &sp48);
    D_80358074 = D_80358070;
    D_80358070 = (Gfx*)((u8*)D_80358070 + sp48);
    func_hd_code_80257490(&D_80358070, 0x10);
    func_hd_code_80285190();
    func_hd_code_80275430();
    func_hd_code_802621DC(levelno);
    func_hd_code_80262238(levelno);
    func_hd_code_80262150(levelno);
    D_80367BFF = 0;
    func_hd_code_802CE840();
    func_hd_code_8029A7E4("enter initlevel game_mode=%d loop_done=%d\n", func_hd_code_8026F92C(D_hd_code_80364A90), func_hd_code_8026F92C(D_80364A98));
    sp3C = D_80358070;
    func_hd_code_802A1674(D_80358074, arg0);
    func_hd_code_8029A7E4("exit initlevel allocated %d bytes, %x\n", (u32)D_80358070 - (u32)sp3C, D_80358070);
    func_hd_code_80257234();
    if (D_80364A98 != 2) {
        if((D_80364AF0[playerNumber].unk18[levelno] > 0 && D_80364AF0[playerNumber].unk18[levelno] < 6)?1:0) {
            func_hd_code_802CF628();
        }
    }
    func_hd_code_802C1DD0(D_80364AA8 == 0x20 || D_80364AA8 == 0x80);
    func_hd_code_80262320(levelno);
    if (D_hd_code_80364410 != 0) {
        D_80364A86 = func_hd_code_80272C5C(&D_hd_code_802E8BF4, 0, 1, 1, 1, 1.0f);
    }
    func_hd_code_802775C0();
    if (D_80364A69 != 0) {
        func_hd_code_80286A00();
    }
    if (D_80364A6B != 0) {
        func_hd_code_802873AC();
    }
    if (D_80364A6D != 0) {
        func_hd_code_80287AE4();
    }
    func_hd_code_802821D0();
    func_hd_code_80282728();
    func_hd_code_80281A70(levelno);
    if (D_hd_code_802E8F94[levelno].unk0 == 1) {
        func_hd_code_80264C20(arg0);
    }
    func_hd_code_80288220();
    func_hd_code_8027BE4C();
    func_hd_code_80292240();
    func_hd_code_8027E344(levelno);
    func_hd_code_802807D8(levelno);
    func_hd_code_80268664(levelno);
    func_hd_code_8026A988();
    sp44 = D_803643C8.textures;
    while (sp44 != D_803643C8.end) {
        sp4C = 0;
        sp43 = 0;
        do {
            if (D_80364460[sp4C].unk5C == sp44->unk1022) {
                sp43 = 1;
            } else {
                sp4C += 1;
            }
        } while (sp43 == 0);
        func_hd_code_80258544(sp44, sp44->unk1004, sp44->unk1010, sp44->unk100C, sp44->unk1000, D_80364460[sp4C].unk54, D_80364460[sp4C].unk0, D_80364460[sp4C].unk4);
        func_hd_code_80285110(0x61F);
        sp44++;
    }
    func_hd_code_802729F0((s32)D_80364A98, levelno);
    D_hd_code_80364452 = 0x2000;
    D_hd_code_80364454 = 0x2000;
    D_hd_code_80364456 = 0;
    D_803649ED = 0;
    D_hd_code_803643F8 = 0;
    D_hd_code_803643FC = 0;
    D_hd_code_80364400 = 0;
    D_hd_code_80364444 = 0.0f;
    D_hd_code_80364448 = 0.0f;
    D_hd_code_803649F8 = 1.0f;
    D_80364A3C = 0;
    D_80364A3D = 0;
    D_80364A40 = 0;
    D_80364A44 = 0;
    D_80364A6F = 0;
    D_80364AB4 = 0.0f;
    D_80364AB8 = 1.0f;
    D_80364ABC = 1.0f;
    D_80364AC0 = 0;
    D_hd_code_803643E0 = D_803ED808;
    D_hd_code_803643E4 = D_803ED80C;
    D_hd_code_803643E8 = D_803ED810;
    D_hd_code_802FDB14 = 0;
    if (D_hd_code_802E8BF8 != 0) {
        D_803649F0 = D_8036EA70;
    } else {
        D_803649F0 = D_80364B04[playerNumber].unk0;
    }
    D_80364A5C = 0;
    D_80364A58 = 0;
    if (D_803669B4 != 0) {
        func_hd_code_8025BD98();
    }
    func_hd_code_8029A7E4("Level %d: mem_pool=0x%x, code seg=0x%x, space=%d bytes\n", (s32* ) levelno, D_80358070, 0x802447C0, 0x8021ED00 - (s32)D_80358070);
    if (D_8039CAB7 != 0) {
        func_hd_code_802979E0(levelno);
    }
    func_hd_code_802A56C4();
    func_hd_code_802A5FA8();
}

void func_hd_code_80257234(void) {
  s32 sp14;
  s32 sp10;
  s32 spC;
  s32 sp8;

  switch (levelno) {
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
      switch (D_803BE739) {                       /* switch 1; irregular */
      case 0:                                     /* switch 1 */
          sp14 = 0x1770;
          sp10 = 0x1388;
          spC = 0x64;
          sp8 = 0x7D0;
          break;
      case 1:                                     /* switch 1 */
          sp14 = 0x3E8;
          sp10 = 0x3E8;
          spC = 0x64;
          sp8 = 0x7D0;
          break;
      }
      break;
  }
  D_80358030[0] = D_80358070;
  D_80358070 += sp14 * 8;
  D_80358038[0] = D_80358070;
  D_80358070 += sp10 * 8;
  D_80358040[0] = D_80358070;
  D_80358070 += spC * 8;
  D_80358048[0] = D_80358070;
  D_80358070 += sp8 * 8;
  D_80358030[1] = D_80358070;
  D_80358070 += sp14 * 8;
  D_80358038[1] = D_80358070;
  D_80358070 += sp10 * 8;
  D_80358040[1] = D_80358070;
  D_80358070 += spC * 8;
  D_80358048[1] = D_80358070;
  D_80358070 += sp8 * 8;
}

void func_hd_code_80257490(u8** arg0, s32 arg1) {
  s32 sp4;

  sp4 = (s32) *arg0 % arg1;
  if (sp4 != 0) {
    sp4 = arg1 - sp4;
  }
  *arg0 += sp4;
}

f32 func_hd_code_802574F0(f32 arg0) {
  return sinf(arg0);
}

f32 func_hd_code_80257514(f32 arg0) {
  return cosf(arg0);
}
