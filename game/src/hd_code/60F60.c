#include "common.h"
#include "variables.h"

extern s32 D_hd_code_802C2954;
extern s32 D_hd_code_802C2984;
extern s32 D_hd_code_802C2A5C;
extern s32 D_hd_code_802C37C0;
extern s32 D_hd_code_802C3804;
extern s32 D_hd_code_802C382C;
extern s32 D_hd_code_802C3848;
extern s32 D_hd_code_802C386C;

// <bss>
// assumed types
u8 D_hd_code_803C3250[0x1000];
u8 D_hd_code_803C4250[0x900];
s32 D_hd_code_803C4B50;
s32 D_hd_code_803C4B54;
u8 D_hd_code_803C4B58[0x18];
u8 D_hd_code_803C4B70[0x3C0];
u8 D_hd_code_803C4F30[0x40];
u8 D_hd_code_803C4F70[0x400];
u8 D_hd_code_803C5370[0x400];
Gfx D_hd_code_803C5770[384];
Gfx D_hd_code_803C6370[384];
Gfx D_hd_code_803C6F70[384];
Gfx D_hd_code_803C7B70[384];
u8 D_hd_code_803C8770[0x1000];
u8 D_hd_code_803C9770[0x1000];
u8 D_hd_code_803CA770[0x10000];
u8 D_hd_code_803DA770[0x10000];
u8 D_hd_code_803EA770[0x1000];
u8 D_hd_code_803EB770[0x10];
s32 D_hd_code_803EB780;
s32 D_hd_code_803EB784;
s32 D_hd_code_803EB788;
s32 D_hd_code_803EB78C;
u16 D_hd_code_803EB790;
u16 D_hd_code_803EB792;
s32 D_hd_code_803EB794;
s32 D_hd_code_803EB798;
s32 D_hd_code_803EB79C;
// </bss>

// <data>
void* D_hd_code_80305C10[9] = {
    &D_hd_code_802C2954, &D_hd_code_802C2984, &D_hd_code_802C2A5C,
    &D_hd_code_802C37C0, &D_hd_code_802C3804, &D_hd_code_802C382C,
    &D_hd_code_802C3848, &D_hd_code_802C386C, 0x00000000
};
char D_hd_code_80305C34[] = "Num texture caches=";
char D_hd_code_80305C48[] = "%d\n";
// </data>

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/func_hd_code_802A5720.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/func_hd_code_802A5764.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/func_hd_code_802A57AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/DecodeTexture.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/DecodeTexture6.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/DecodeTexture3.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/DecodeTexture1.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/DecodeTexture2.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/DecodeTexture4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/DecodeTexture5.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/DecodeTexture0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/func_hd_code_802A5E60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/func_hd_code_802A5ED0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/func_hd_code_802A5F30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/func_hd_code_802A5FA8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/func_hd_code_802A6274.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/func_hd_code_802A64A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/func_hd_code_802A6748.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/func_hd_code_802A67C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/func_hd_code_802A68D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/func_hd_code_802A6C10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/func_hd_code_802A6D34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/func_hd_code_802A6DE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/60F60/func_hd_code_802A6EB8.s")
