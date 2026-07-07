#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/hd.h"
#include "../hd_code/yoshi.h"
#include "../hd_code/functions.h"
#include "../hd_code/variables.h"
#include "structs.h"

void func_hd_front_end_801F58E8();              /* extern */
void func_hd_front_end_801F74B0(u8*);                /* extern */
s32 func_hd_code_8028FCD4(OSMesgQueue*, u8*);       /* extern */
s32 func_hd_code_8028FCD4(OSMesgQueue*, u8*);       /* extern */

extern u8 D_hd_front_end_8020C000[]; // "BLASTCORPS GAME"
extern u8 D_hd_front_end_8020C014[];
extern u8 D_hd_front_end_8020F128;
extern u8 D_hd_front_end_8020F140;
extern OSThread D_hd_front_end_80218D30;
extern u8 D_hd_front_end_80218EF8;
extern void* D_hd_front_end_80219F10;
extern OSMesgQueue D_hd_front_end_80219F30;
extern void* D_hd_front_end_80219F48;
extern void* D_hd_front_end_80219F68;
extern OSPfs D_hd_code_8039B630;
extern s32 D_hd_code_8039B698[]; // Line no
extern OSPfsState D_hd_front_end_80218B20[];

void func_hd_front_end_801F57B0(void) {
  s32 sp24 = 0xDE0;
  osCreateThread(&D_hd_front_end_80218D30, 2, func_hd_front_end_801F58E8, NULL, &D_hd_front_end_80218EF8 + 0x1000, 0xB);
  osCreateMesgQueue(&D_hd_front_end_80219EF8, &D_hd_front_end_80219F10, 8);
  osCreateMesgQueue(&D_hd_front_end_80219F30, &D_hd_front_end_80219F48, 1);
  osCreateMesgQueue(&D_hd_front_end_80219F50, &D_hd_front_end_80219F68, 8);
  func_hd_front_end_801F74B0(D_hd_front_end_8020C000);
  func_hd_front_end_801F74B0(D_hd_front_end_8020C014);
  rmonPrintf("current pak file size is %d bytes\n", sp24);
  rmonPrintf("current playerInfo size is %d bytes\n", 0x100);
  osScAddClient(&sc, &D_hd_front_end_80218EE0, &D_hd_front_end_80219F30, 1, 3);
  if (sp24 >= 0xE00) {
    rmonPrintf(ASSERT_MESSAGE, "filesize<PFS_FILE_SIZE", "pfsHandler.c", 0x68);
  }
  osStartThread(&D_hd_front_end_80218D30);
}

// Scratch: https://decomp.me/scratch/qRQ8h - useless branch
#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F58E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/D_hd_front_end_8020F19C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/D_hd_front_end_8020F1C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/D_hd_front_end_8020F1D0.s")

s32 func_hd_front_end_801F5FE4(void) {
  s32 sp24;
  u8 sp23;
  void* sp1C;

  sp1C = NULL;
  if (D_hd_code_80370BF8.validCount != 0) {
    rmonPrintf(ASSERT_MESSAGE, "1==0", "pfsHandler.c", 0x190);
    osRecvMesg(&D_hd_code_80370BF8, &sp1C, 0);
  }
  if (func_hd_code_8028FCD4(&D_hd_code_80370BF8, &sp23) != 0) {
    sp24 = 1;
  } else if (!(sp23 & 1)) {
    sp24 = 1;
  } else {
    sp24 = 0;
  }
  if (sp1C != NULL) {
    rmonPrintf(ASSERT_MESSAGE, "1==0", "pfsHandler.c", 0x19E);
    osSendMesg(&D_hd_code_80370BF8, sp1C, 0);
  }
  return sp24;
}

s32 func_hd_front_end_801F60C8(void) {
  u8 sp1F;
  s32 sp18;

  sp18 = 0;
  D_hd_code_8039C4F8.unk40 = 4;
  if (func_hd_code_8028FCD4(&D_hd_code_80370BF8, &sp1F) != 0) {
    sp18 = 1;
  } else if (!(sp1F & 1)) {
    sp18 = 1;
  }
  if (sp18 == 0) {
    sp18 = osPfsInit(&D_hd_code_80370BF8, &D_hd_code_8039B630, 0);
  }
  func_hd_code_8028A370();
  return sp18;
}

s32 func_hd_front_end_801F6160(u8 arg0) {
  return osPfsAllocateFile(
      &D_hd_code_8039B630,
      0x3031U, // "01"
      0x4E424345U, // "NBCE"
      D_hd_front_end_8020C000, // "BLASTCORPS GAME"
      D_hd_front_end_8020C014,
      0xE00,
      &D_hd_code_8039B698[arg0]
  );
}

s32 func_hd_front_end_801F61C8(u8 arg0) {
  return osPfsDeleteFile(&D_hd_code_8039B630, 0x3031U, 0x4E424345U, D_hd_front_end_8020C000, D_hd_front_end_8020C014);
}

s32 func_hd_front_end_801F6210(u8 arg0) {
  s32 sp24;

  sp24 = osPfsDeleteFile(
      &D_hd_code_8039B630,
      D_hd_front_end_80218B20[arg0 - 37].company_code,
      D_hd_front_end_80218B20[arg0 - 37].game_code,
      D_hd_front_end_80218B20[arg0 - 37].game_name,
      D_hd_front_end_80218B20[arg0 - 37].ext_name);
  return sp24;
}

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F6264.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F65C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/D_hd_front_end_8020F2DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F67E4.s")

// Scratch: https://decomp.me/scratch/zAitn
#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F6AF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F6BD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F6CA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F6ED4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F6F18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F73FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F7410.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F74B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F75A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F76E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F7850.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F7F74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F7FF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F803C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F81B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F8228.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F8354.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/D9650/func_hd_front_end_801F8440.s")
