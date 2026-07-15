#ifndef _YOSHI_H
#define _YOSHI_H

#include <PR/gbi.h>
#include <PR/ultratypes.h>

#include "structs.h"

extern u8 D_hd_code_802F47B0[23][8];
extern char D_hd_code_8036B980[0x28];
extern char D_hd_code_8036B9A8[0x20];
extern char D_hd_code_8036B9C8[0x20];
extern char D_hd_code_8036B9E8[0x20];
extern char D_hd_code_8036BA08[0x20];
extern char D_hd_code_8036BA28[0x20];

void func_hd_code_8026AF6C(u16 yd);
s32 func_hd_code_8026AD30(s16);
u16 func_hd_code_8026B10C();
void func_hd_code_8026B118(s32 arg0);
void func_hd_code_8026B8F8();
Gfx* func_hd_code_8026BBD0(Gfx*, struct Model1*, s32*);
s32 func_hd_code_8026F92C(u64);
u8 func_hd_code_8026FA38(char** arg0, s32* arg1);

#endif
