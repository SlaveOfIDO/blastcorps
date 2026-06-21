#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/hd.h"
#include "../hd_code/functions.h"

// <data>
char *D_hd_front_end_80208040 = "SELECT VEHICLE!";
s16 D_hd_front_end_80208044[4] = {
  0x8030, 0x4954, 0xFFFF, 0x0000
};
u8 D_hd_front_end_8020804C[20] = {
  0x00, 0x01, 0x00, 0x00,
  0x01, 0x00, 0x01, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};

struct S_80208060
{
  u8 unk0;
  f32 unk4;
};

struct S_80208060 D_hd_front_end_80208060[19] = {
  { 0, 0.0f }, { 0, 0.0f }, { 1, 0.5f }, { 0, 0.0f },
  { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f },
  { 0, 0.0f }, { 1, 0.5f }, { 0, 0.0f }, { 0, 0.0f },
  { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f },
  { 1, 0.5f }, { 0, 0.0f }, { 0, 0.0f }
};

u8 D_hd_front_end_802080F8[19] = {
  0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x02, 0x01,
  0x01, 0x06, 0x01, 0x01,
  0x00, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01
};
u8 D_hd_front_end_8020810C[19] = {
  0x03, 0x03, 0x03, 0x03,
  0x03, 0x03, 0x03, 0x03,
  0x03, 0x03, 0x0C, 0x03,
  0x03, 0x03, 0x03, 0x03,
  0x03, 0x03, 0x03
};
f32 D_hd_front_end_80208120[19] = {
  220.0f,
  400.0f,
  800.0f,
  320.0f,
  400.0f,
  460.0f,
  400.0f,
  400.0f,
  320.0f,
  550.0f,
  320.0f,
  320.0f,
  500.0f,
  320.0f,
  320.0f,
  320.0f,
  320.0f,
  320.0f,
  320.0f
};
s16 D_hd_front_end_8020816C[19] = {
  -75, -75, -250, -50,
  -80, -93, -75, -75,
  -53, -180, -50, -75,
  -75, -50, -65, -50,
  -65, -75, -75
};
u8 D_hd_front_end_80208194[19] = {
  0x00, 0x36, 0x50, 0x8C,
  0x0B, 0x05, 0x00, 0x20,
  0xCE, 0x02, 0x94, 0x72,
  0x00, 0xCE, 0x7B, 0xCE,
  0x50, 0x72, 0x72
};
u16 D_hd_front_end_802081A8 = 0x1DD0;
s32 D_hd_front_end_802081AC = 1;
s16 D_hd_front_end_802081B0 = 0;
s8 D_hd_front_end_802081B4 = 1;
// </data>

void func_hd_code_8029DEA0();                                  /* extern */
void func_hd_front_end_801E74E8(u8);                  /* extern */
void func_hd_front_end_80202100(s32, void*, void*, void*); /* extern */
void func_hd_front_end_80202270(s32, void*, void*);    /* extern */
void func_hd_front_end_802022EC(void*, u8, u8, u8, f32, s32, s32); /* extern */
void func_hd_front_end_80202380(s32);                  /* extern */

extern u8 D_hd_code_802E8C44[28];
extern ALBank* D_hd_code_80367738;
extern s16 D_hd_front_end_80211A68;
extern f32 D_hd_front_end_802153D4;
extern f32 D_hd_front_end_802153DC;
extern struct S_80367C04 D_hd_code_802E8F94[];

extern f32 D_hd_code_802FDAC0[20];
extern u8 D_hd_code_803643D4;
// players = 0x80364AF0
extern u16 D_hd_code_80364EF0[][0x10];

extern s32 D_hd_front_end_80210E90[0x50 / 0x4];

struct S_80210EE0 {
    s32 unk0;
    s32 unk4;
}; // Size: 0x8
extern struct S_80210EE0 D_hd_front_end_80210EE0[0x98 / 0x8];
struct S_80210F78 {
    s32 unk0[4];
}; // Size: 0x10
extern struct S_80210F78 D_hd_front_end_80210F78[];
extern Mtx D_hd_front_end_802110A8[19];
extern Mtx D_hd_front_end_80211568[19];
extern Mtx D_hd_front_end_80211A28;
extern s16 D_hd_front_end_80211A68;
extern s16 D_hd_front_end_80211A6A;
extern f32 D_hd_front_end_80211A70[0x50/4];
struct S_80211AC0 {
    u8 pad0[0x300];
}; // Size: 0x300
extern struct S_80211AC0 D_hd_front_end_80211AC0[0x3900/0x300];
extern u8 D_hd_front_end_802153C0[19];
extern f32 D_hd_front_end_802153D4;
extern f32 D_hd_front_end_802153D8;
extern f32 D_hd_front_end_802153DC;
extern f32 D_hd_front_end_802153E0;
extern s16 D_hd_front_end_802153E4;
extern s16 D_hd_front_end_802153E6;
extern s32 D_hd_front_end_802153E8;

s32 func_hd_front_end_801E7000(void) {
    s32 spA4;
    s32 pad;
    s32 sp9C;
    struct S_80367C04* sp98;
    u16 sp96;
    u16 pad94;
    s32 sp90;
    s32 sp8C;
    s32 sp40[19];

    D_hd_front_end_80211A68 = 0;
    sp9C = 0;
    sp98 = &D_hd_code_802E8F94[levelno];
    D_hd_front_end_80211A6A = 0;
    sp96 = 0xe73c;
    D_hd_front_end_802153E8 = (s32) D_hd_code_803643D4;
    func_hd_code_8029DEA0();
    for(spA4 = 0; spA4 < 19; spA4++) {
        sp40[spA4] = -1;
        if ((players[D_hd_code_80364AEA].unk10 & (1 << spA4) & sp98->unk2C) && ((playerNumber == D_hd_code_80364AEA) || (*(&D_hd_code_80364EF0[D_hd_code_80364AEA][D_hd_code_802E8C44[spA4]]) != 0))) {
            func_hd_front_end_80202100(spA4, &D_hd_front_end_80210E90[D_hd_front_end_80211A6A], &D_hd_front_end_80210EE0[D_hd_front_end_80211A6A], &D_hd_front_end_80210F78[D_hd_front_end_80211A6A]);
            D_hd_front_end_80211A70[spA4] = sp9C;
            sp9C = (s32) ((f64) sp9C + 380.0);
            guTranslate(&D_hd_front_end_802110A8[D_hd_front_end_80211A6A], D_hd_front_end_80211A70[spA4], (f32) D_hd_front_end_8020816C[spA4], 0.0f);
            guScale(&D_hd_front_end_80211568[D_hd_front_end_80211A6A], D_hd_code_802FDAC0[spA4], D_hd_code_802FDAC0[spA4], D_hd_code_802FDAC0[spA4]);
            func_hd_front_end_80202270(D_hd_front_end_80210E90[D_hd_front_end_80211A6A], &D_hd_front_end_80210EE0[D_hd_front_end_80211A6A], &D_hd_front_end_80211AC0[D_hd_front_end_80211A6A]);
            func_hd_front_end_802022EC(&D_hd_front_end_80211AC0[D_hd_front_end_80211A6A], D_hd_front_end_802080F8[spA4], D_hd_front_end_8020804C[spA4], D_hd_front_end_80208060[spA4].unk0, D_hd_front_end_80208060[spA4].unk4, (s32) D_hd_front_end_8020810C[spA4], 0);
            func_hd_front_end_80202380(spA4);
            D_hd_front_end_802153C0[D_hd_front_end_80211A6A] = spA4;
            sp40[spA4] = (s32) D_hd_front_end_80211A6A;
            D_hd_front_end_80211A6A += 1;
        }
    }
    guAlign(&D_hd_front_end_80211A28, 20.0f, 1.0f, 0.0f, 0.0f);
    sp90 = (s32) (D_hd_front_end_80211A6A - 1) / 2;
    sp8C = -1;
    switch(D_hd_code_80364A90) {
        case 0x4000:
            break;
        case 0x80:
            sp8C = sp40[players[playerNumber].unk92[levelno]];
            break;
        case 0x08000000:
        case 0x100:
        case 0x4:
            sp8C = sp40[D_hd_code_803643D4];
            break;
        default:
            rmonPrintf(ASSERT_MESSAGE, "1==0", "digger_loop.c", 0x8B);
            break;
    }
    rmonPrintf("default %d auto %d\n", sp90, sp8C);
    func_hd_front_end_801E74E8(sp8C == -1 ? sp90 : sp8C);
    D_hd_front_end_802153D8 = D_hd_front_end_802153D4;
    D_hd_front_end_802153E0 = (f32) ((f64) D_hd_front_end_802153DC * 4.0);
    D_hd_front_end_802153E6 = 0;
    D_hd_front_end_802153E4 = 0;
    return D_hd_front_end_80211A6A > 1;
}


void func_hd_front_end_801E74E8(u8 arg0) {

  D_hd_front_end_80211A68 = arg0;
  D_hd_code_803643D4 = D_hd_front_end_802153C0[arg0];
  sndDeactivateAllSfxByFlag_3();
  sndPlaySfx(D_hd_code_80367738, D_hd_front_end_80208194[D_hd_front_end_802153C0[arg0]], NULL);
  D_hd_front_end_802153D4 = D_hd_front_end_80211A70[D_hd_front_end_802153C0[arg0]];
  D_hd_front_end_802153DC = D_hd_front_end_80208120[D_hd_front_end_802153C0[arg0]];
}

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/CAEA0/func_hd_front_end_801E7598.s")
