#include "common.h"
#include "variables.h"

// <bss>
// assumed types
u8 D_hd_code_803FC9A0[0x3A8];
s32 D_hd_code_803FCD48;
s32 D_hd_code_803FCD4C;
s32 D_hd_code_803FCD50;
s32 D_hd_code_803FCD54;
s32 D_hd_code_803FCD58;
s32 D_hd_code_803FCD5C;
s32 D_hd_code_803FCD60;
s32 D_hd_code_803FCD64;
s16 D_hd_code_803FCD68;
s16 D_hd_code_803FCD6A;
s16 D_hd_code_803FCD6C;
s16 D_hd_code_803FCD6E;
u8 D_hd_code_803FCD70;
u8 D_hd_code_803FCD71;
u8 D_hd_code_803FCD72;
u8 D_hd_code_803FCD73;
u8 D_hd_code_803FCD74;
u8 D_hd_code_803FCD75;
u8 D_hd_code_803FCD76;
u8 D_hd_code_803FCD77;
u8 D_hd_code_803FCD78;
u8 D_hd_code_803FCD79;
u16 D_hd_code_803FCD7A;
s32 D_hd_code_803FCD7C;

// libultra: game/src/hd_code/os/initialize.c and game/src/hd_code/io/pimgr.c
// declare these extern; this file provides the real storage.
u32 __osFinalrom;
s32 D_hd_code_803FCD84;
s32 D_hd_code_803FCD88;
s32 D_hd_code_803FCD8C;
OSThread piThread;
char piThreadStack[OS_PIM_STACKSIZE];
OSMesgQueue piEventQueue;
OSMesg piEventBuf[2];
// </bss>

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/8DDB0/func_hd_code_802D2570.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/8DDB0/func_hd_code_802D291C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/8DDB0/func_hd_code_802D2A40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/8DDB0/func_hd_code_802D2A74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/8DDB0/func_hd_code_802D2C20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/8DDB0/func_hd_code_802D2FA4.s")
