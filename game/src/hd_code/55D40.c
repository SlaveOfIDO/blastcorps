#include "common.h"
#include "functions.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"
#include "yoshi.h"

struct S_80304A90 {
  s32 unk0;
  u8 unk4;
  u8 unk5;
  char unk6[42];
}; // Size: 0x30

// <bss>
s32 D_hd_code_803A6B20;
s32 D_hd_code_803A6B24;
s32 D_hd_code_803A6B28;
s32 D_hd_code_803A6B2C;
// </bss>

// <data>
struct S_80304A90 D_hd_code_80304A90[82] = {
    { 0x00000011, 0x04, 0x14, "EXECUTIVE PRODUCER" },
    { 0x00000061, 0x07, 0x10, "HIROSHI YAMAUCHI" },
    { 0x00000011, 0x04, 0x14, "NINTENDO PRODUCERS" },
    { 0x00000041, 0x07, 0x10, "MIKE FUKUDA" },
    { 0x00000061, 0x07, 0x10, "KENJI MIKI" },
    { 0x00000011, 0x04, 0x14, "GAME DESIGN" },
    { 0x00000061, 0x07, 0x10, "MARTIN WAKELEY" },
    { 0x00000011, 0x04, 0x14, "LEAD PROGRAMMER" },
    { 0x00000061, 0x07, 0x10, "RICHARD WILSON" },
    { 0x00000011, 0x04, 0x12, "ADDITIONAL PROGRAMMING" },
    { 0x00000061, 0x07, 0x10, "GRAHAM SMITH" },
    { 0x00000011, 0x04, 0x14, "LEAD ARTIST" },
    { 0x00000061, 0x07, 0x10, "RICHARD BERWICK" },
    { 0x00000011, 0x04, 0x14, "ADDITIONAL ARTISTS" },
    { 0x00000041, 0x07, 0x10, "PAUL CUNNINGHAM" },
    { 0x00000061, 0x07, 0x10, "KEITH RABBETTE" },
    { 0x00000011, 0x04, 0x14, "MUSIC AND SFX" },
    { 0x00000061, 0x07, 0x10, "GRAEME NORGATE" },
    { 0x00000011, 0x04, 0x14, "STORY AND TEXT" },
    { 0x00000061, 0x07, 0x10, "LEIGH LOVEDAY" },
    { 0x00000011, 0x04, 0x14, "PRODUCT MANAGER" },
    { 0x00000061, 0x07, 0x10, "SIMON FARMER" },
    { 0x00000011, 0x04, 0x12, "PRODUCT TEST" },
    { 0x00000011, 0x04, 0x12, "AND ADDITIONAL DESIGN" },
    { 0x00000041, 0x07, 0x10, "HUW WARD" },
    { 0x00000041, 0x07, 0x10, "GARY RICHARDS" },
    { 0x00000041, 0x07, 0x10, "GEORGE ANDREAS" },
    { 0x00000041, 0x07, 0x10, "GAVIN HOOD" },
    { 0x00000041, 0x07, 0x10, "GARETH JONES" },
    { 0x00000041, 0x07, 0x10, "MARTIN PENNY" },
    { 0x00000041, 0x07, 0x10, "DAVID WONG" },
    { 0x00000061, 0x07, 0x10, "JAMIE WILLIAMS" },
    { 0x00000011, 0x04, 0x14, "ORIGINAL CONCEPT" },
    { 0x00000061, 0x07, 0x10, "CHRIS STAMPER" },
    { 0x00000011, 0x04, 0x12, "EMULATOR PROGRAMMING" },
    { 0x00000061, 0x07, 0x10, "ROBERT HARRISON" },
    { 0x00000011, 0x04, 0x12, "ADDITIONAL COMPRESSION" },
    { 0x00000061, 0x07, 0x10, "MIKE CURRINGTON" },
    { 0x00000011, 0x04, 0x12, "ADDITIONAL ARTWORK" },
    { 0x00000041, 0x07, 0x10, "KEVIN BAYLISS" },
    { 0x00000061, 0x07, 0x10, "DON MURPHY" },
    { 0x00000011, 0x04, 0x14, "NOA STAFF" },
    { 0x00000041, 0x07, 0x10, "KEN LOBB" },
    { 0x00000041, 0x07, 0x10, "ERICH WAAS" },
    { 0x00000041, 0x07, 0x10, "ARMOND WILLIAMS" },
    { 0x00000041, 0x07, 0x10, "ISAAC MARSHALL" },
    { 0x00000041, 0x07, 0x10, "HENRY STERCHI" },
    { 0x00000061, 0x07, 0x10, "RICH RICHARDSON" },
    { 0x00000011, 0x04, 0x14, "VOICES" },
    { 0x00000041, 0x07, 0x10, "ROBIN KROUSE" },
    { 0x00000041, 0x07, 0x10, "ERICH WAAS" },
    { 0x00000041, 0x07, 0x10, "ISAAC MARSHALL" },
    { 0x00000041, 0x07, 0x10, "MICHAEL KELBAUGH" },
    { 0x00000041, 0x07, 0x10, "LEE RAY" },
    { 0x00000061, 0x07, 0x10, "HELEN COOMBS" },
    { 0x00000011, 0x04, 0x14, "LIVE GUITAR" },
    { 0x00000061, 0x07, 0x10, "GRANT KIRKHOPE" },
    { 0x00000011, 0x04, 0x12, "NOA PRODUCT TESTING" },
    { 0x00000041, 0x07, 0x10, "MICHAEL KELBAUGH" },
    { 0x00000041, 0x07, 0x10, "TIM BECHTEL" },
    { 0x00000041, 0x07, 0x10, "CHRIS NEEDHAM" },
    { 0x00000041, 0x07, 0x10, "BEN SMITH" },
    { 0x00000041, 0x07, 0x10, "ROBERT JOHNSON" },
    { 0x00000041, 0x07, 0x10, "THOMAS HERTZOG" },
    { 0x00000041, 0x07, 0x10, "DAVID BRIDGHAM" },
    { 0x00000061, 0x07, 0x10, "NOA TESTING TEAM" },
    { 0x00000011, 0x04, 0x14, "RARE US STAFF" },
    { 0x00000041, 0x07, 0x10, "EILEEN HOCHBERG" },
    { 0x00000041, 0x07, 0x10, "SCOTT HOCHBERG" },
    { 0x00000041, 0x07, 0x10, "JERRY ROGOWSKI" },
    { 0x00000061, 0x07, 0x10, "MATTHEW BERGER" },
    { 0x00000011, 0x04, 0x14, "NCL STAFF" },
    { 0x00000041, 0x07, 0x10, "KEISUKE TERASAKI" },
    { 0x00000041, 0x07, 0x10, "EIJI ONOZUKA" },
    { 0x00000041, 0x07, 0x10, "KIMIKO NAKAMICHI" },
    { 0x00000061, 0x07, 0x10, "MASASHI GOTO" },
    { 0x00000011, 0x04, 0x14, "SPECIAL THANKS TO" },
    { 0x00000041, 0x07, 0x10, "NCL, EAD. ARTWORK TEAM" },
    { 0x00000041, 0x07, 0x10, "NCL MARIO CLUB" },
    { 0x00000041, 0x07, 0x10, "JOEL HOCHBERG" },
    { 0x00000041, 0x07, 0x10, "MR. ARAKAWA" },
    { 0x00000061, 0x07, 0x10, "HOWARD LINCOLN" }
};
// </data>

void func_hd_code_8029A500(void) {
  D_hd_code_803A6B20 = -0xEF;
  D_hd_code_803A6B24 = 0;
}

s32 func_hd_code_8029A518(struct Model1* arg0, s32 arg1) {
    s32 sp64;
    struct S_80304A90* sp60;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;

    sp54 = 0;
    sp64 = arg1;
#if NON_MATCHING
    // retail reads uninitialized stack here too (see docs/RELOC_PROBLEMS.md); IDO's layout happens to match, GCC's doesn't
    sp58 = 0;
#endif
    for(sp5C = 0; sp5C < 0x52; sp5C++) {
        sp60 = &D_hd_code_80304A90[sp5C];
        if (sp60->unk0 & 1) {
            sp50 = 0xA0;
        } else if (sp60->unk0 & 4) {
            sp50 = 0x6A;
        } else if (sp60->unk0 & 8) {
            sp50 = 0xD5;
        } else {
            sp50 = 0;
        }
        if ((sp54 - D_hd_code_803A6B20 >= -0x31) && (sp54 - D_hd_code_803A6B20 < 0xF0)) {
            func_hd_code_80259DC8(
                arg0,
                sp60->unk6,
                0,
                0,
                sp50,
                sp58,
                sp54 - D_hd_code_803A6B20,
                sp60->unk5,
                sp60->unk5,
                1,
                D_hd_code_802F47B0[sp60->unk4][0],
                D_hd_code_802F47B0[sp60->unk4][1],
                D_hd_code_802F47B0[sp60->unk4][2],
                D_hd_code_802F47B0[sp60->unk4][3],
                D_hd_code_802F47B0[sp60->unk4][4],
                D_hd_code_802F47B0[sp60->unk4][5],
                D_hd_code_802F47B0[sp60->unk4][6],
                D_hd_code_802F47B0[sp60->unk4][7]
            );
        }
        if (sp60->unk0 & 0x20) {
            sp54 += 0x26;
        }
        if (sp60->unk0 & 0x10) {
            sp54 += 0x16;
        }
        if (sp60->unk0 & 0x40) {
            sp54 += 0x11;
        }
    }
    if (g_frameCount == 0x64) {
        func_hd_code_8026AF6C(0x8036U);
    }
    if ((u32) g_frameCount >= 0x18CU) {
        D_hd_code_803A6B20 += 1;
    }
    if (D_hd_code_803643D6 != 0) {
        D_hd_code_803A6B24 += 1;
    }
    if (D_hd_code_803A6B24 == 0x7D) {
        func_hd_code_8026AF6C(0x8037U);
        func_hd_code_80260EE0(0x25);
    }
    if ((D_hd_code_803A6B24 >= 0x7E) && (D_hd_code_8036BB1C == 1) && (areWeFading() == 0)) {
        func_hd_code_80275270(0x200000000000, 0.75f);
    }
    return sp64;
}
