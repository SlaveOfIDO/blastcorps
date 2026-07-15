#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/hd.h"
#include "../hd_code/yoshi.h"
#include "../hd_code/functions.h"
#include "../hd_code/variables.h"
#include "../hd_code/io/controller.h"
#include "structs.h"

// <data>
/*struct LevelData D_hd_front_end_8020D810[] = {
};*/
// </data>

s32 func_hd_front_end_801F1568(void);               /* extern */
s32 func_hd_front_end_801F2000(void);               /* extern */
s32 func_hd_front_end_801F2428(void);               /* extern */
Gfx* func_hd_front_end_801F2E20(void);               /* extern */
void func_hd_front_end_801F885C(s32);               /* extern */
f32 func_hd_front_end_801FD6B8(f32, f32, f32);      /* extern */
void func_hd_front_end_801FDE50(void);              /* extern */
void func_hd_front_end_801FD484(f32 *, f32 *, f32 *, f32 *, f32 *, f32);  /* extern */
u64 func_hd_code_80299FE8(s32);                     /* extern */
void func_hd_front_end_801ECB18(void);              /* extern */
Gfx* func_hd_front_end_801F9258(Gfx*, struct Model1*, s32*); /* extern */
Gfx* func_hd_front_end_801F9820(Gfx*, struct Model1*, s32*); /* extern */
Gfx* func_hd_front_end_801F9B84(Gfx*, struct Model1*, s32*); /* extern */
void func_hd_front_end_801FD748(void);              /* extern */
void func_hd_code_80275390(u64);                      /* extern */
f32 func_hd_code_8028BBF4(s16, s16, s16, s16);
Gfx* func_hd_code_80274868(Gfx*);                     /* extern */
s32 func_hd_code_80272ED8(s32, s32, u8, s32, s32, s32, f32); /* extern */
s32 func_hd_code_80274AA4(s32);                     /* extern */
Gfx* func_hd_front_end_801FA180(Gfx*, struct Model1*, f32, s8*); /* extern */
Gfx* func_hd_front_end_801FC5B8(struct Model1*, Gfx*, u8, u8); /* extern */
void func_hd_front_end_801FDE98();                     /* extern */
Gfx* func_hd_front_end_801F3450(Gfx*, struct Model1*); /* extern */
Gfx* func_hd_front_end_801FE5D0(Gfx*, struct Model1*); /* extern */
Gfx* func_hd_front_end_801FA74C(struct Model1* arg0, Gfx* gfx, u8 arg2, u8 arg3, s8* arg4, f32* arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 arg10, u8 arg11, u8 arg12);
void func_hd_front_end_801FCF38(Vtx arg0[4], f32, f32, f32, u8, u8, f32, u8); /* extern */
s32 func_hd_front_end_801FE760(u8);
void func_hd_front_end_801FDCA4(Vtx *, s32, s32);

extern Lights1 D_hd_front_end_8020E3A8[2];

extern u16 D_hd_front_end_8020E350[];
extern s8 D_hd_code_80370C2D;
extern f32 D_hd_front_end_8020E3D8;
extern u8 D_hd_front_end_8021A905;
extern f32 D_hd_front_end_8021A90C;
extern f32 D_hd_front_end_8021A910;
extern f32 D_hd_front_end_8021A914;
extern u16 D_hd_front_end_8021A924;
extern f32 D_hd_front_end_8021A934;
extern f32 D_hd_front_end_8021A938;
extern u32 D_hd_front_end_8021AB24;
extern s32 D_hd_front_end_8021AB58;
extern s32 D_hd_front_end_8021AB5C;
extern f32 D_hd_front_end_8021AB60;
extern f32 D_hd_front_end_8021AB64;
extern Gfx* D_hd_front_end_8021AB68;
extern Gfx* D_hd_front_end_8021AB6C;
extern u8 D_hd_front_end_8021AB2E;
extern u16 D_hd_front_end_8021A926;
extern u8 D_hd_front_end_8021A930;
extern u8 D_hd_front_end_8021AB21;
extern u16 D_hd_front_end_8020E39C[];
extern s32 D_hd_front_end_80217B6C;
extern s32 D_hd_front_end_8021A8F4;
extern s32 D_hd_front_end_8021A8FC;
extern s32 D_hd_front_end_8021A900;
extern s8 D_hd_front_end_8021A906;
extern s8 D_hd_front_end_8021A907;
extern u8 D_hd_front_end_8021A908;
extern u16 D_hd_front_end_8021A926;
extern u8 D_hd_front_end_8021A930;
extern s8 D_hd_front_end_8021AB20;
extern u8 D_hd_front_end_8021AB21;
extern f32 D_hd_front_end_8021AB28;
extern s16 D_hd_front_end_8021AB2C;
extern u8 D_hd_front_end_8021AB2E;
extern f32 D_hd_front_end_8021A918;
extern UnknownData8024C414* D_hd_front_end_8021AB30;
extern struct S_80367C04* D_hd_front_end_8021AB34;
extern s32 D_hd_front_end_8021AB38;
extern f32 D_hd_front_end_8021AB40;
extern f32 D_hd_front_end_8021AB44;
extern f32 D_hd_front_end_8021AB48;
extern f32 D_hd_front_end_8021A91C;
extern f32 D_hd_front_end_8021A920;
extern u8 D_hd_front_end_8021A905;
extern u16 D_hd_front_end_8021A924;
extern s32 D_hd_code_80358078; // current top-level display list length; proposed name: topLevelDlLen
extern OSMesgQueue D_hd_code_80315180;
extern void* D_hd_code_8035806C; // static data segment pointer (segment 1); proposed name: staticSegment
extern Mtx D_hd_front_end_80217B70[7][2][2]; // Size: 0x700 / 0x100
extern u8 D_hd_front_end_8021A904;
extern s32 D_hd_code_802FA264;
extern u8 D_hd_code_8035805C;
extern u8 *D_hd_front_end_80215A70[];
extern u8 D_hd_front_end_802159F0[];


// TODO: put this macro into every function and do not use gu_int for that.
#define	ABS(d)		(((d) > 0) ? (d) : -(d))
#define SGN(x)    ((x) >= 0 ? 1 : -1)

// <bss>
Vtx D_hd_front_end_8021A840[2][4];
s32 D_hd_front_end_8021A8C0;
f32 D_hd_front_end_8021A8C4;
f32 D_hd_front_end_8021A8C8;
f32 D_hd_front_end_8021A8CC;
f32 D_hd_front_end_8021A8D0;
f32 D_hd_front_end_8021A8D4;
f32 D_hd_front_end_8021A8D8;
f32 D_hd_front_end_8021A8DC;
f32 D_hd_front_end_8021A8E0;
f32 D_hd_front_end_8021A8E4;
f32 D_hd_front_end_8021A8E8;
f32 D_hd_front_end_8021A8EC;
u8 D_hd_front_end_8021A8F0;
s32 D_hd_front_end_8021A8F4;
Gfx* D_hd_front_end_8021A8F8;
s32 D_hd_front_end_8021A8FC;
s32 D_hd_front_end_8021A900;
u8 D_hd_front_end_8021A904;
u8 D_hd_front_end_8021A905;
s8 D_hd_front_end_8021A906;
s8 D_hd_front_end_8021A907;
u8 D_hd_front_end_8021A908;
u8 D_hd_front_end_8021A909;
f32 D_hd_front_end_8021A90C;
f32 D_hd_front_end_8021A910;
f32 D_hd_front_end_8021A914;
f32 D_hd_front_end_8021A918;
f32 D_hd_front_end_8021A91C;
f32 D_hd_front_end_8021A920;
u16 D_hd_front_end_8021A924;
u16 D_hd_front_end_8021A926;
u8* D_hd_front_end_8021A928[2];
u8 D_hd_front_end_8021A930;
f32 D_hd_front_end_8021A934;
f32 D_hd_front_end_8021A938;
s64 D_hd_front_end_8021A940[0x3C];
s8 D_hd_front_end_8021AB20;
u8 D_hd_front_end_8021AB21;
u32 D_hd_front_end_8021AB24;
f32 D_hd_front_end_8021AB28;
s16 D_hd_front_end_8021AB2C;
u8 D_hd_front_end_8021AB2E;
UnknownData8024C414* D_hd_front_end_8021AB30;
struct S_80367C04* D_hd_front_end_8021AB34;
s32 D_hd_front_end_8021AB38;

s32 pad_8021AB38; // Potentially a boundary

f32 D_hd_front_end_8021AB40;
f32 D_hd_front_end_8021AB44;
f32 D_hd_front_end_8021AB48;
f32 D_hd_front_end_8021AB4C;
f32 D_hd_front_end_8021AB50;
f32 D_hd_front_end_8021AB54;
s32 D_hd_front_end_8021AB58;
s32 D_hd_front_end_8021AB5C;
f32 D_hd_front_end_8021AB60;
f32 D_hd_front_end_8021AB64;
Gfx* D_hd_front_end_8021AB68;
Gfx* D_hd_front_end_8021AB6C;
// </bss>

void func_hd_front_end_801F8530(s32 arg0) {
    struct Model1* sp3C;
    u32 sp38;
    struct LevelData* sp34;
    f32 sp30;
    f32 sp2C;

    D_hd_front_end_8021AB30 = &players[playerNumber];
    D_hd_front_end_8021AB34 = &D_hd_code_802E8F94[arg0];
    D_hd_front_end_8021A91C = func_hd_front_end_801FD6B8(90.0f, D_hd_front_end_8020D810[arg0].unk14, 180.0f);
    D_hd_front_end_8021A920 = func_hd_front_end_801FD6B8(90.0f, D_hd_front_end_8020D810[arg0].unk10, 180.0f);
    D_hd_front_end_8021A8F4 = func_hd_front_end_801F1568();
    D_hd_front_end_8021A8FC = func_hd_front_end_801F2428();
    D_hd_front_end_8021A900 = func_hd_front_end_801F2000();

    for (sp38 = 0; sp38 < 2; sp38++) {
        D_hd_front_end_8021A928[sp38] = D_hd_code_80358070;
        D_hd_code_80358070 += 0x17000;
    }

    D_hd_front_end_8021A8F8 = func_hd_front_end_801F2E20();

    for (sp38 = 0; sp38 < 2; sp38++) {
        sp3C = &D_hd_code_803156F8[sp38];
        guPerspective(&sp3C->projection, &D_hd_code_8035807C, 45.0f, 1.3333334f, 100.0f, 20000.0f, 1.0f);
        guTranslate(&sp3C->unk1280, 0.0f, -50.0f, 0.0f);
    }

    D_hd_front_end_80217B6C = 6;
    func_hd_front_end_801F885C(arg0);
    D_hd_front_end_8021A904 = arg0;
    D_hd_front_end_8021A908 = arg0;
    D_hd_front_end_8021A926 = 1;
    D_hd_front_end_8021A930 = 0;
    D_hd_front_end_8021A907 = -1;
    D_hd_front_end_8021AB21 = 0;
    D_hd_front_end_8021A906 = arg0;
    D_hd_front_end_8021AB28 = 0.0f;
    D_hd_front_end_8021AB38 = 0;
    D_hd_front_end_8021AB2C = 0;
    D_hd_front_end_8021AB40 = 0.915f;
    D_hd_front_end_8021AB44 = 0.009f;
    D_hd_front_end_8021AB48 = 26100.0f;
    func_hd_front_end_801FDE50();
    D_hd_front_end_8021AB20 = func_hd_code_80272C5C(D_hd_front_end_8020E39C, 0, 4, 1, 1, 1.0f);

    for (sp38 = 0; sp38 < 0x3C; sp38++) {
        sp34 = &D_hd_front_end_8020D810[sp38];
        sp30 = sp34->unk10;
        sp2C = sp34->unk14;
        func_hd_front_end_801FD484(&sp30, &sp2C, &sp34->unk24, &sp34->unk28, &sp34->unk2C, 250.0f);
    }

    D_hd_front_end_8021AB2E = 0;
}

void func_hd_front_end_801F885C(s32 arg0) {
  u8 sp1F;

  sp1F = func_hd_code_80264BA4(arg0);
  D_hd_front_end_8021A905 = (u8) arg0;
  if (sp1F != D_hd_front_end_80217B6C) {
    D_hd_front_end_8021A924 = 0;
    D_hd_front_end_8021A918 = 6250.0f;
    if (D_hd_front_end_80217B6C != 6) {
      if (D_hd_front_end_80217B6C == 3) {
        func_hd_code_80261FB0(0x13U);
      } else if (sp1F == 3) {
        func_hd_code_80261FB0(0xCU);
      }
    }
  }
  if (D_hd_front_end_80217B6C != 6) {
    if ((sp1F == 3) && (D_hd_front_end_80217B6C == 3)) {
      sndPlaySfx((struct ALBankAlt_s* ) D_hd_code_80367738, 0x1D, NULL);
    } else {
      sndPlaySfx((struct ALBankAlt_s* ) D_hd_code_80367738, 0x3F, NULL);
    }
  }
  D_hd_front_end_80217B6C = (s32) sp1F;
  D_hd_front_end_8021AB34 = &D_hd_code_802E8F94[D_hd_front_end_8021A905];
}

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8020FF80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8020FF90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8020FF9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8020FFAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8020FFC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8020FFD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8020FFE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8020FFF0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8020FFF8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8021000C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8021001C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8021002C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210038.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210048.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210054.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210064.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210074.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210084.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210094.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_802100A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_802100AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_802100BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_802100CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_802100DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_802100EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_802100FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8021010C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8021011C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8021012C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210138.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210148.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210158.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210168.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210174.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210184.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210190.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_802101A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_802101AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_802101BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_802101CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_802101D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_802101E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_802101F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210200.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210208.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210210.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210218.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210220.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8021022C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8021023C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8021024C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8021025C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_8021026C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210278.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210284.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_80210294.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_802102A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_802102AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_802102BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_front_end/DC3D0/D_hd_front_end_802102CC.s")

void func_hd_front_end_801F8980(void) {
    s16 sp46;
    s16 sp44;
    s32 sp40;
    u32 sp3C;
    struct Model1* sp38;

    nextdma = 0;
    no_palette_dmas = 0;
    func_hd_code_802A5720();
    func_hd_code_8028A3E4();
    if (D_hd_code_80358060 != 0) {
        func_hd_code_80284E54(D_hd_code_803156F8[D_hd_code_8035805C].dp, D_hd_code_80358078, 2, 0, 0x4D2, 0);
        func_hd_code_80284E54(D_hd_front_end_8021AB68, D_hd_front_end_8021AB58, 0, 0, 0x4D2, 0);
        func_hd_code_80284E54(D_hd_front_end_8021AB6C, D_hd_front_end_8021AB5C, 1, 1, 0x4D2, 0);
    } else {
        func_hd_code_80284E54(D_hd_code_803156F8[D_hd_code_8035805C].dp, D_hd_code_80358078, 1, 1, 0x4D2, 0);
    }
    D_hd_code_8035805C ^= 1;
    sp38 = &D_hd_code_803156F8[D_hd_code_8035805C];
    func_hd_code_8028A470();
    if ((D_hd_front_end_8021AB2E != 0) ||
        ((areWeFading() == 0) && (D_hd_front_end_8021A924 == 1) &&
         (D_hd_code_80370C28 & 0x9000) && !(D_hd_code_80370C2A & 0x9000))) {
        if (D_hd_front_end_8021A926 == 0) {
            sndDeactivateAllSfxByFlag_3();
            sndPlaySfx((struct ALBankAlt_s*) D_hd_code_80367738, 0x1E, NULL);
            D_hd_front_end_8021A924 = 2;
            rmonPrintf("selected level %d\n", D_hd_front_end_8021A905);
            levelno = D_hd_front_end_8021A905;
            func_hd_front_end_801ECB18();
            D_hd_front_end_8021AB2E = 0;
        } else {
            D_hd_front_end_8021AB2E = 1;
        }
    }
    if ((D_hd_code_80370C28 & 0x4000) && !(D_hd_code_80370C2A & 0x4000) &&
        (areWeFading() == 0) && (D_hd_front_end_8021A924 == 1)) {
        D_hd_code_80364A87 = 0;
        sndPlaySfx((struct ALBankAlt_s*) D_hd_code_80367738, 0xDE, NULL);
        func_hd_code_80275390(0x4000000000000000);
        levelno = D_hd_front_end_8021A905;
    }
    sp3C = (D_hd_code_80370C2C * D_hd_code_80370C2C) + (D_hd_code_80370C2D * D_hd_code_80370C2D);
    if (sp3C < 0x5DC) {
        D_hd_front_end_8021A930 = 1;
    }
    if (sp3C != 0) {
        D_hd_front_end_8020E3D8 = func_hd_code_8028BBF4(0, 0, D_hd_code_80370C2C, -D_hd_code_80370C2D);
    }
    if ((sp3C >= 0x5DD) && (D_hd_front_end_8021A930 != 0) && (D_hd_front_end_8021A907 >= 0) &&
        (D_hd_front_end_8021AB2C == 0xFF) && (D_hd_front_end_8021A924 == 1) &&
        (D_hd_code_8036BB1C == 1)) {
        D_hd_front_end_8021A930 = 0;
        D_hd_front_end_8021A904 = D_hd_front_end_8021A905;
        func_hd_front_end_801F885C(D_hd_front_end_8021A907);
        D_hd_front_end_8021A926 = 1;
        D_hd_front_end_8021AB28 = 1.0f;
        if (D_hd_front_end_8021AB38 != 0) {
            sndDeactivate(D_hd_front_end_8021AB38);
        }
    }
    switch (D_hd_front_end_8021A924) {              /* irregular */
    case 0:
        if ((D_hd_front_end_8021AB21 + 0xA) >= 0x100) {
            D_hd_front_end_8021AB21 = -1;
        } else {
            D_hd_front_end_8021AB21 = D_hd_front_end_8021AB21 + 0xA;
        }
        D_hd_front_end_8021A918 -= 200.0f;
        if (D_hd_front_end_8021A918 <= 925.0) {
            D_hd_front_end_8021A924 = 1;
            D_hd_front_end_8021A918 = 925.0f;
            D_hd_front_end_8021AB24 = D_hd_code_803156C4;
        }
        break;
    case 2:
        D_hd_front_end_8021A918 -= 50.0f;
        if ((D_hd_front_end_8021AB21 - 0x19) < 0) {
            D_hd_front_end_8021AB21 = 0;
        } else {
            D_hd_front_end_8021AB21 = D_hd_front_end_8021AB21 - 0x19;
        }
        if ((D_hd_front_end_8021AB2C - 0x40) < 0) {
            D_hd_front_end_8021AB2C = 0;
        } else {
            D_hd_front_end_8021AB2C -= 0x40;
        }
        if (D_hd_front_end_8021A918 <= 300.0) {
            D_hd_code_80364A98 = func_hd_code_80299FE8(levelno);
        }
        break;
    default:
        D_hd_front_end_8021AB21 = 0xFF;
        if (D_hd_front_end_8021A926 == 0) {
            if ((D_hd_front_end_8021AB2C + 0x20) >= 0x100) {
                D_hd_front_end_8021AB2C = 0xFF;
            } else {
                D_hd_front_end_8021AB2C += 0x20;
            }
        }
        break;
    }
    if (D_hd_front_end_80217B6C != 3) {
        D_hd_front_end_8021AB21 = 0;
    }
    sp46 = (s16) (s32) D_hd_front_end_8021A90C;
    sp44 = (s16) (s32) D_hd_front_end_8021A910;
    func_hd_front_end_801FD484(&D_hd_front_end_8021A920, &D_hd_front_end_8021A91C,
                              &D_hd_front_end_8021A90C, &D_hd_front_end_8021A910,
                              &D_hd_front_end_8021A914, 925.0f);
    D_hd_front_end_8021A934 = D_hd_front_end_8021A90C - (f32) sp46;
    D_hd_front_end_8021A938 = D_hd_front_end_8021A910 - (f32) sp44;
    D_hd_front_end_8021AB60 = D_hd_front_end_8020D810[D_hd_front_end_8021A905].unk14;
    D_hd_front_end_8021AB64 = D_hd_front_end_8020D810[D_hd_front_end_8021A905].unk10;
    D_hd_front_end_8021A934 = (func_hd_front_end_801FD6B8(D_hd_front_end_8021AB60, D_hd_front_end_8021A91C, 180.0f) * MAX(0x1F4U, (sp3C >> 2))) / 10000.0f;
    D_hd_front_end_8021A938 = (func_hd_front_end_801FD6B8(D_hd_front_end_8021AB64, D_hd_front_end_8021A920, 180.0f) * MAX(0x1F4U, (sp3C >> 2))) / 10000.0f;
    D_hd_front_end_8021A91C -= D_hd_front_end_8021A934;
    D_hd_front_end_8021A920 -= D_hd_front_end_8021A938;
    D_hd_front_end_8021AB68 = func_hd_front_end_801F9258(sp38->dp, sp38, &D_hd_code_80358078);
    D_hd_front_end_8021AB6C = func_hd_front_end_801F9820(D_hd_front_end_8021AB68, sp38, &D_hd_front_end_8021AB58);
    func_hd_front_end_801F9B84(D_hd_front_end_8021AB6C, sp38, &D_hd_front_end_8021AB5C);
    func_hd_front_end_801FD748();

    for (sp40 = 0; sp40 < nextdma; sp40++) {
        osRecvMesg(&D_hd_code_80315180, NULL, 1);
    }
    for (sp40 = 0; sp40 < (nextdma - no_palette_dmas); sp40++) {
        func_hd_code_802A57AC();
    }
}

Gfx* func_hd_front_end_801F9258(Gfx* gfx, struct Model1* arg1, s32* arg2) {
    Gfx* entry;                                      /* compiler-managed */
    s32 padC0;
    s32 spBC;
    s32 spB8;
    s32 spB4;
    s32 padB0;
    s32 padAC;
    s32 padA8;
    s32 padA4;
    s32 padA0;
    s32 sp9C;

    entry = gfx;
    gSPSegment(entry++, 0, 0x00000000);
    gSPSegment(entry++, 2, osVirtualToPhysical(arg1));
    gSPSegment(entry++, 1, osVirtualToPhysical(D_hd_code_8035806C));
    gSPDisplayList(entry++, D_1000038);
    gSPDisplayList(entry++, D_1000010);
    gDPSetColorImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, D_hd_code_80358050[D_hd_code_8035805C]);
    gDPSetCycleType(entry++, G_CYC_FILL);
    gDPSetFillColor(entry++, 0x00010001);
    gDPFillRectangle(entry++, 0, 0, 319, 239);
    gDPPipeSync(entry++);
    gDPPipelineMode(entry++, G_PM_1PRIMITIVE);
    gDPSetColorDither(entry++, G_CD_NOISE);
    entry = func_hd_front_end_801FE5D0(entry, arg1);
    entry = func_hd_front_end_801F3450(entry, arg1);
    func_hd_code_80259450();

    sp9C = 0x18;
    {
        s32 sp68;
        s32 sp64;
        struct S_80367C04* sp60;
        s32 sp5C;
        s32 sp58;
        sp68 = D_hd_front_end_8021AB2C / 9;
        func_hd_code_80259DC8(arg1, (s32) D_hd_front_end_8020D810[D_hd_front_end_8021A908].name,
                              D_hd_front_end_8020D810[D_hd_front_end_8021A908].unk8, 0, 0xA0, 0,
                              ((u32) (0x1C - (D_hd_front_end_8021AB2C / 9)) >> 1) + 0x12, 0x18,
                              D_hd_front_end_8021AB2C / 9, 1, 0xFF, 0xFF, 0xFF,
                              D_hd_front_end_8021AB2C, 0, 0, 0xFF, D_hd_front_end_8021AB2C);

        entry = func_hd_code_8024C404(entry, arg1, &sp64);
        func_hd_code_80259C24(&entry, arg1);
        sp60 = &D_hd_code_802E8F94[D_hd_front_end_8021A908];
        entry = func_hd_code_80274868(entry);


        for (spBC = 0, spB8 = 0,spB4 = 0xDA; (spBC < 0x13) && (spB4 >= 0x29); spBC++) {
            if ((sp60->unk2C & (1 << spBC)) && ((sp60->unk0 == 1) || (D_hd_front_end_8021AB30->unk10 & (1 << spBC))) && (D_hd_front_end_8020E350[spBC * 2] != 0)) {
                if (spB8 != 0) {
                    entry = func_hd_code_80272ED8(entry, spBC + D_hd_front_end_8021A8F0,
                                0x16 - ((0xFF - D_hd_front_end_8021AB2C) / 6), spB4,
                                D_hd_front_end_8021AB2C, 0, 0.8125f);
                } else {
                    entry = func_hd_code_80272ED8(entry, spBC + D_hd_front_end_8021A8F0,
                                ((0xFF - D_hd_front_end_8021AB2C) / 6) + 0xF6, spB4 -= 0x2C,
                                D_hd_front_end_8021AB2C, 0, 0.8125f);
                }
                spB8 ^= 1;
            }
        }

        sp5C = func_hd_code_8025B498(0xA0U, sp9C,
                   D_hd_front_end_8020D810[D_hd_front_end_8021A908].name,
                   D_hd_front_end_8020D810[D_hd_front_end_8021A908].unk8);
        sp58 = (s32)(sp9C * D_hd_code_802E8C84[0]) * func_hd_code_8025B300(D_hd_front_end_8020D810[D_hd_front_end_8021A908].name);
        entry = func_hd_code_80274AA4(entry);
        gSPEndDisplayList(entry++);
        *arg2 = ((s32)entry - (s32)gfx) >> 3;
    }
    return entry;
}

Gfx* func_hd_front_end_801F9820(Gfx* gfx, struct Model1* arg1, s32* arg2) {
  Gfx* entry = gfx;
  gSPSegment(entry++, 0, 0x00000000);
  gSPSegment(entry++, 2, osVirtualToPhysical(arg1));
  gSPSegment(entry++, 1, osVirtualToPhysical(D_hd_code_8035806C));
  gSPDisplayList(entry++, D_1000010);
  gSPDisplayList(entry++, D_1000038);
  gDPSetColorImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, D_hd_code_80358050[D_hd_code_8035805C]);
  gDPSetDepthImage(entry++, D_hd_code_80358058);
  gDPPipeSync(entry++);
  gDPSetRenderMode(entry++, G_RM_AA_XLU_LINE, G_RM_AA_XLU_LINE2);
  gSPPerspNormalize(entry++, D_hd_code_8035807C);
  gSPMatrix(entry++, &arg1->projection, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
  gSPMatrix(entry++, &arg1->projection2, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
  gSPMatrix(entry++, &D_hd_front_end_80217B70[3][0][D_hd_code_8035805C], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
  gSPMatrix(entry++, &D_hd_front_end_80217B70[3][1][D_hd_code_8035805C], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
  gSPMatrix(entry++, &arg1->unk1280, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
  entry = func_hd_front_end_801FA180(entry, arg1, D_hd_front_end_8020E3D8, &D_hd_front_end_8021A907);
  gSPEndDisplayList(entry++);
  *arg2 = (s32) ((s32)entry - (s32)gfx) >> 3;
  return entry;
}

Gfx* func_hd_front_end_801F9B84(Gfx* gfx, struct Model1* arg1, s32* arg2) {
    Gfx* entry = gfx;
    gSPSegment(entry++, 0, 0x00000000);
    gSPSegment(entry++, 2, osVirtualToPhysical(arg1));
    gSPSegment(entry++, 1, osVirtualToPhysical(D_hd_code_8035806C));
    gSPDisplayList(entry++, D_1000010);
    gSPDisplayList(entry++, D_1000038);
    gDPSetColorImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, D_hd_code_80358050[D_hd_code_8035805C]);
    gDPSetDepthImage(entry++, D_hd_code_80358058);
    gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPTexture(entry++, 0x8000, 0x8000, 0, 0, G_ON);
    gDPSetPrimColor(entry++, 0, 0, 0, 0, 0, D_hd_front_end_8021AB21);
    gDPSetCombineLERP(entry++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    gSPPerspNormalize(entry++, D_hd_code_8035807C);
    gSPMatrix(entry++, &arg1->projection, G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(entry++, &arg1->projection2, G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(entry++, &D_hd_front_end_80217B70[3][0][D_hd_code_8035805C], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(entry++, &D_hd_front_end_80217B70[3][1][D_hd_code_8035805C], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(entry++, &arg1->unk1280, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    entry = func_hd_front_end_801FC5B8(arg1, entry, (u8) D_hd_front_end_8021A904, D_hd_front_end_8021A905);
    func_hd_front_end_801FDE98();
    entry = func_hd_code_80274BF0(&arg1[D_hd_code_8035805C], entry);
    gDPFullSync(entry++);
    gSPEndDisplayList(entry++);
    if (D_hd_code_802FA264 != 0) {
        if (D_hd_code_80370C28 & 0x800) {
            D_hd_front_end_8021AB40 = (f32) ((f64) D_hd_front_end_8021AB40 + 0.01);
        }
        if (D_hd_code_80370C28 & 0x400) {
            D_hd_front_end_8021AB40 = (f32) ((f64) D_hd_front_end_8021AB40 - 0.01);
        }
        if (D_hd_code_80370C28 & 0xC00) {
            rmonPrintf("angd %f\n", D_hd_front_end_8021AB40);
        }
        if (D_hd_code_80370C28 & 0x100) {
            D_hd_front_end_8021AB44 = (f32) ((f64) D_hd_front_end_8021AB44 + 0.001);
        }
        if (D_hd_code_80370C28 & 0x200) {
            D_hd_front_end_8021AB44 = (f32) ((f64) D_hd_front_end_8021AB44 - 0.001);
        }
        if (D_hd_code_80370C28 & 0x300) {
            rmonPrintf("dmm %f\n", D_hd_front_end_8021AB44);
        }
        if (D_hd_code_80370C28 & 0x10) {
            D_hd_front_end_8021AB48 += 100.0f;
        }
        if (D_hd_code_80370C28 & 0x20) {
            D_hd_front_end_8021AB48 -= 100.0f;
        }
        if (D_hd_code_80370C28 & 0x30) {
            rmonPrintf("mmm %f\n", D_hd_front_end_8021AB48);
        }
    }
    *arg2 = (s32) ((s32)entry - (s32)gfx) >> 3;
    return entry;
}

Gfx* func_hd_front_end_801FA180(Gfx* arg0, struct Model1* arg1, f32 arg2, s8* arg3) {
    struct LevelData* sp74;
    Gfx* entry;
    f32 sp6C;
    f32 sp68;
    s32 sp64;
    s32 sp60;
    s8 sp5F;
    s8 sp5E;



    entry = arg0;
    sp68 = 180.0f;
    D_hd_front_end_8021A909 = 0;
    gDPPipeSync(entry++);

    for (sp64 = 0; sp64 < 0x3C; sp64++) {
        D_hd_front_end_8021A940[sp64] = 0;
    }

    for (sp64 = 0; sp64 < 0x3C; sp64++) {
        sp74 = &D_hd_front_end_8020D810[sp64];
        if ((players[playerNumber].unk18[sp64] > 0) && (players[playerNumber].unk18[sp64] < 6)?1:0) {
            for (sp60 = 0; sp60 < 8 && sp74->unk1C[sp60] != -1; sp60++) {
                entry = func_hd_front_end_801FA74C(arg1, entry, sp64, sp74->unk1C[sp60], &sp5F, &sp6C, 0, 0, 0, 0, 0, 0, 0);
            }
        }
    }

    for (sp64 = 0; sp64 < 0x3C; sp64++) {
        D_hd_front_end_8021A940[sp64] = 0;
    }

    for (sp64 = 0; sp64 < 0x3C; sp64++) {
        sp74 = &D_hd_front_end_8020D810[sp64];
        if ((players[playerNumber].unk18[sp64] > 0) && (players[playerNumber].unk18[sp64] < 6)?1:0) {
            for (sp60 = 0; sp60 < 4 && sp74->unk18[sp60] != -1; sp60++) {
                if (players[playerNumber].unk54[sp64] & (1 << sp60)) {
                    entry = func_hd_front_end_801FA74C(arg1, entry, sp64, sp74->unk18[sp60], &sp5F, &sp6C, 1, 0, 0xFF, 0, 0xFF, 0xFF, 0);
                    if (sp5F != -1) {
                        f32 sp54 = func_hd_front_end_801FD6B8(arg2, sp6C, 180.0f);
                        sp54 = (ABS(sp54));
                        if (sp54 < sp68) {
                            sp68 = sp54;
                            sp5E = sp5F;
                        }
                    }
                }
            }
        }
    }

    for (sp64 = 0; sp64 < 0x3C; sp64++) {
        sp74 = &D_hd_front_end_8020D810[sp64];
        if ((players[playerNumber].unk18[sp64] > 0) && (players[playerNumber].unk18[sp64] < 6)?1:0) {
            for (sp60 = 0; sp60 < 8 && sp74->unk1C[sp60] != -1; sp60++) {
                entry = func_hd_front_end_801FA74C(arg1, entry, sp64, sp74->unk1C[sp60], &sp5F, &sp6C, 1, 0xFF, 0, 0, 0xFF, 0x80, 0x80);
                if (sp5F != -1) {
                    f32 sp50 = func_hd_front_end_801FD6B8(arg2, sp6C, 180.0f);
                    sp50 = (ABS(sp50));
                    if (sp50 < sp68) {
                        sp68 = sp50;
                        sp5E = sp5F;
                    }
                }
            }
        }
    }

    osWritebackDCache(D_hd_front_end_8021A928[D_hd_code_8035805C], 0x17000);
    if (sp68 < 45.0f) {
        *arg3 = sp5E;
    } else {
        *arg3 = -1;
    }
    return entry;
}

Gfx* func_hd_front_end_801FA74C(struct Model1* arg0, Gfx* gfx, u8 arg2, u8 arg3, s8* arg4, f32* arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 arg10, u8 arg11, u8 arg12) {
    Vtx* sp12C;
    Vtx* sp128;
    Gfx* entry;
    s32 sp120;
    s32 sp11C;
    s32 sp118;
    s8 sp117;
    u8 sp116;
    f32 sp110;
    struct LevelData* sp10C;
    struct LevelData* sp108;
    f32 sp104;
    f32 sp100;
    f32 spFC;
    f32 spF8;
    s16 spF6;
    s16 spF4;
    s16 spF2;
    s16 spF0;
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    u8 spBB;
    u8 spBA;
    u32 spB4;

    entry = gfx;
    sp117 = 1;
    spC0 = 1.0f;
    spBA = 0;

    if ((arg3 == D_hd_front_end_8021A905) || !players[playerNumber].unk18[arg2]) {
        u8 tmp = arg3;
        arg3 = arg2;
        arg2 = tmp;
    }

    if(D_hd_front_end_8021A940[arg2] & (1LL << arg3)) {
        sp116 = 1;
    } else {
        sp116 = 0;
    }

    D_hd_front_end_8021A940[arg2] |= 1LL << arg3;
    D_hd_front_end_8021A940[arg3] |= 1LL << arg2;
    *arg4 = -1;
    if ((sp116 != 0) || (func_hd_front_end_801FE760(arg3) != 0)) {
        return gfx;
    }
    if ((func_hd_code_80264BA4(arg2) == 3) || (func_hd_code_80264BA4(arg3) == 3)) {
        spBA = 1;
    }
    if (arg2 == D_hd_front_end_8021A905) {
        *arg4 = arg3;
    }
    if ((func_hd_code_80264BA4(arg2) == 3) && (func_hd_code_80264BA4(arg3) == 3)) {
        if (
            (D_hd_code_80364A87 != 0 &&
            (
                players[playerNumber].unk18[arg3] == 0 ||
                (((D_hd_code_80364A87 & 1) && arg2 == D_hd_front_end_8021A905) &&
                ((players[playerNumber].unk18[arg3] > 0 && (players[playerNumber].unk18[arg3] < 6)?1:0) == 0))
            ))
        ) {
            if (D_hd_front_end_8021A924 != 0) {
                sp110 = MIN(1.0f, MAX(D_hd_front_end_8021AB28, (((f32)(D_hd_code_803156C4 - D_hd_front_end_8021AB24) * 60.0) / 60U) / 90.0));
                if ((sp110 == 1.0) && (D_hd_front_end_8021AB38 != 0)) {
                    sndDeactivate(D_hd_front_end_8021AB38);
                } else if ((D_hd_front_end_8021AB38 == 0) && (sp110 != 1.0) && (D_hd_front_end_80217B6C == 3)) {
                    sndPlaySfx((struct ALBankAlt_s*) D_hd_code_80367738, 0x7C, (ALSoundState*) &D_hd_front_end_8021AB38);
                }
            } else {
                sp110 = 0.0f;
            }
        } else {
            sp110 = 1.0f;
        }
    } else {
        sp110 = 1.0f;
    }
    sp10C = &D_hd_front_end_8020D810[arg2];
    sp108 = &D_hd_front_end_8020D810[arg3];

    spEC = sp10C->unk24,
    spE4 = sp10C->unk28,
    spDC = sp10C->unk2C;
    spE8 = sp108->unk24;
    spE0 = sp108->unk28;
    spD8 = sp108->unk2C;



    spF8 = sqrtf(((spE8 - spEC) * (spE8 - spEC)) + ((spE0 - spE4) * (spE0 - spE4)) + ((spD8 - spDC) * (spD8 - spDC)));
    sp118 = MAX(3.0, MIN(spF8 / 32.0, 15.0));
    sp11C = sp118 + 1;
    sp128 = &((Vtx*) D_hd_front_end_8021A928[D_hd_code_8035805C])[D_hd_front_end_8021A909 * 0x10];
    sp12C = sp128;
    spCC = ((((spEC * spE8) + (spE4 * spE0) + (spDC * spD8)) / 250.0) / 250.0);
    spC8 = (90.0 - (((((spCC >= 0.0f) ? 1 : -1) * func_hd_code_802AD7D4(((ABS(spCC)) * 65535.0))) / 16.0) / 11.377777));
    if (spC8 >= 180.0) {
        spC8 -= 180.0;
    }
    if (spC8 < -180.0) {
        spC8 += 180.0;
    }
    spBB = 0;
    spC8 *= 0.017453292519943295;
    for (sp120 = 0; sp120 < sp11C; sp120++, sp12C++) {
        spC4 = MIN(sp110, ((1.0 / (sp11C - 1)) * (f32) sp120));
        spD4 = func_hd_code_802574F0((1.0 - spC4) * spC8) / func_hd_code_802574F0(spC8);
        spD0 = func_hd_code_802574F0(spC4 * spC8) / func_hd_code_802574F0(spC8);
        if (arg6 != 0) {
            spC0 = ((func_hd_code_802574F0((spC4 * 3.141592653)) * sp118) / 64.0) + 1.0;
        }

        sp104 = ((spD4 * spEC) + (spD0 * spE8)) * spC0;
        sp100 = ((spD4 * spE4) + (spD0 * spE0)) * spC0;
        spFC = ((spD4 * spDC) + (spD0 * spD8)) * spC0;


        if (*arg4 != -1) {
            if(sp120 < 2) {
                if (D_hd_front_end_80217B6C == 3) {

                    if (sp120 != 0) {
                        if(sp104 == 1.0f && 0) {
                        }
                        func_hd_code_8027690C(
                            arg0,
                            sp104, sp100, spFC,
                            &spF6, &spF4,
                            &D_hd_front_end_80217B70[3][0][D_hd_code_8035805C],
                            &D_hd_front_end_80217B70[3][1][D_hd_code_8035805C],
                            &arg0->unk1280, 1.0f
                        );
                        *arg5 = func_hd_code_8028BBF4(spF2, spF0, spF6, spF4);
                    }  else {
                        func_hd_code_8027690C(
                            arg0,
                            sp104, sp100, spFC,
                            &spF2, &spF0,
                            &D_hd_front_end_80217B70[3][0][D_hd_code_8035805C],
                            &D_hd_front_end_80217B70[3][1][D_hd_code_8035805C],
                            &arg0->unk1280, 1.0f
                        );
                    }
                } else {
                   if (sp120 != 0) {
                     *arg5 = (arg2 < arg3) ? 0 : 180;
                   }
                }

            }
        }
        sp12C->v.ob[0] = sp104;
        sp12C->v.ob[1] = sp100;
        sp12C->v.ob[2] = spFC;
        spBC = MAX(0.0, ((sp104 * D_hd_front_end_8021A90C) + (sp100 * D_hd_front_end_8021A910) + (spFC * D_hd_front_end_8021A914)) / spC0 / 250000.0);
        if (arg6 != 0) {
            spB4 = (1.0 / (MAX(0.001, ABS(spBC - D_hd_front_end_8021AB40)))) * D_hd_front_end_8021AB44 * D_hd_front_end_8021AB44 * D_hd_front_end_8021AB48;
        } else {
            spB4 = 0;
        }
        sp12C->v.cn[0] = MIN(255.0, ((0.5 - ABS(spC4 - 0.5)) * (f32)arg10 + (f32)arg7 * ABS(spC4 - 0.5)) * 2.0 + spB4);
        sp12C->v.cn[1] = MIN(255.0, ((0.5 - ABS(spC4 - 0.5)) * (f32)arg11 + (f32)arg8 * ABS(spC4 - 0.5)) * 2.0 * spBC + spB4);
        sp12C->v.cn[2] = MIN(255.0, ((0.5 - ABS(spC4 - 0.5)) * (f32)arg12 + (f32)arg9 * ABS(spC4 - 0.5)) * 2.0 * (1.0 - spBC) + spB4);
        sp12C->v.cn[3] = ((D_hd_front_end_8021AB21 * spBC) / (2 - arg6));
        if ((sp120 != 0) && (sp116 == 0) && (spBA != 0) && (spBC > 0.0f)) {
            if (spBB == 0) {
                gSPVertex(entry++, sp128, sp11C, 0);
                spBB = 1;
            }

            gSPLineW3D(entry++,
                       sp120 - 1,
                       sp120,
                       2.0 - MIN(2.0, (D_hd_front_end_8021A918 / 1000.0f) / (1.0 + (spBC / 2.0f))),
                       0);
        }


    }
    D_hd_front_end_8021A909 += 1;
    return entry;
}

Gfx* func_hd_front_end_801FC5B8(struct Model1* arg0, Gfx* gfx, u8 arg2, u8 arg3) {
    f32 spAC;
    f32 spA8;
    Gfx* entry = gfx;
    Vtx* spA0 = D_hd_front_end_8021A840[D_hd_code_8035805C];
    struct LevelData* sp9C;
    struct LevelData* sp98;

    switch (D_hd_front_end_8021A926) {
    case 0:
        break;
    case 1:
        sp9C = &D_hd_front_end_8020D810[arg2];
        sp98 = &D_hd_front_end_8020D810[arg3];
        D_hd_front_end_8021A8C4 = sp9C->unk24;
        D_hd_front_end_8021A8CC = sp9C->unk28;
        D_hd_front_end_8021A8D4 = sp9C->unk2C;
        D_hd_front_end_8021A8C8 = sp98->unk24;
        D_hd_front_end_8021A8D0 = sp98->unk28;
        D_hd_front_end_8021A8D8 = sp98->unk2C;
        D_hd_front_end_8021A8DC = sqrtf(
            ((D_hd_front_end_8021A8C8 - D_hd_front_end_8021A8C4) * (D_hd_front_end_8021A8C8 - D_hd_front_end_8021A8C4)) +
            ((D_hd_front_end_8021A8D0 - D_hd_front_end_8021A8CC) * (D_hd_front_end_8021A8D0 - D_hd_front_end_8021A8CC)) +
            ((D_hd_front_end_8021A8D8 - D_hd_front_end_8021A8D4) * (D_hd_front_end_8021A8D8 - D_hd_front_end_8021A8D4)));
        D_hd_front_end_8021A8C0 = MAX(3.0, MIN(D_hd_front_end_8021A8DC / 32.0, 15.0));
        if (arg2 != arg3) {
            D_hd_front_end_8021A926 = 2;
        } else {
            D_hd_front_end_8021A926 = 0;
        }
        D_hd_front_end_8021A8E8 = 0.0f;
        D_hd_front_end_8021A8E0 = ((((D_hd_front_end_8021A8C4 * D_hd_front_end_8021A8C8) + (D_hd_front_end_8021A8CC * D_hd_front_end_8021A8D0) + (D_hd_front_end_8021A8D4 * D_hd_front_end_8021A8D8)) / 250.0) / 250.0);
        D_hd_front_end_8021A8E4 = (90.0 - (((SGN(D_hd_front_end_8021A8E0) * func_hd_code_802AD7D4(ABS(D_hd_front_end_8021A8E0) * 65535.0)) / 16.0) / 11.377777));
        if (D_hd_front_end_8021A8E4 >= 180.0) {
            D_hd_front_end_8021A8E4 -= 180.0;
        }
        if (D_hd_front_end_8021A8E4 < -180.0) {
            D_hd_front_end_8021A8E4 += 180.0;
        }
        D_hd_front_end_8021A8E4 *= 0.017453292519943295;
        break;
    case 2:
        D_hd_front_end_8021A8E8 = (D_hd_front_end_8021A8E8 + (0.4 / D_hd_front_end_8021A8C0));
        if (D_hd_front_end_8021A8E8 > 1.0) {
            D_hd_front_end_8021A926 = 0;
            D_hd_front_end_8021A8E8 = 1.0f;
        }
        D_hd_front_end_8021AB2C = ABS(0.5 - D_hd_front_end_8021A8E8) * 510.0;
        if (D_hd_front_end_8021A8E8 >= 0.5) {
            D_hd_front_end_8021A908 = D_hd_front_end_8021A905;
        }
        break;
    }
    spAC = func_hd_code_802574F0(((1.0 - D_hd_front_end_8021A8E8) * D_hd_front_end_8021A8E4)) / func_hd_code_802574F0(D_hd_front_end_8021A8E4);
    spA8 = func_hd_code_802574F0(D_hd_front_end_8021A8E8 * D_hd_front_end_8021A8E4) / func_hd_code_802574F0(D_hd_front_end_8021A8E4);
    D_hd_front_end_8021A8EC = (((func_hd_code_802574F0((D_hd_front_end_8021A8E8 * 3.141592653)) * D_hd_front_end_8021A8C0) / 64.0) + 1.0);
    D_hd_front_end_8021AB4C = ((spAC * D_hd_front_end_8021A8C4) + (spA8 * D_hd_front_end_8021A8C8)) * D_hd_front_end_8021A8EC;
    D_hd_front_end_8021AB50 = ((spAC * D_hd_front_end_8021A8CC) + (spA8 * D_hd_front_end_8021A8D0)) * D_hd_front_end_8021A8EC;
    D_hd_front_end_8021AB54 = ((spAC * D_hd_front_end_8021A8D4) + (spA8 * D_hd_front_end_8021A8D8)) * D_hd_front_end_8021A8EC;
    func_hd_front_end_801FCF38(spA0, D_hd_front_end_8021AB4C, D_hd_front_end_8021AB50, D_hd_front_end_8021AB54, 0x20, 0x20, 1.75f, 1);
    osWritebackDCache(spA0, 0x40);
    gDPSetTextureImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 1, D_hd_front_end_80215A70[(D_hd_code_803156C4 / 3) % 3]);
    gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0, 0, 7, 0, 2, 0, 0, 2, 0, 0);
    gDPLoadSync(entry++);
    gDPLoadBlock(entry++, 7, 0, 0, 1023, 128);
    gDPPipeSync(entry++);
    gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 8, 0, 0, 0, 2, 0, 0, 2, 0, 0);
    gDPSetTileSize(entry++, 0, 0, 0, 124, 124);
    gSPVertex(entry++, spA0, 4, 0);
    gSP1Triangle(entry++, 0, 1, 2, 0);
    gSP1Triangle(entry++, 2, 3, 0, 0);
    return entry;
}

void func_hd_front_end_801FCE74(Vtx arg0[4], u8 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, f32 arg6, u8 arg7) {
  struct LevelData* sp3C = &D_hd_front_end_8020D810[arg1];
  f32 sp38 = sp3C->unk10 + arg2;
  f32 sp34 = sp3C->unk14 + arg3;
  f32 sp30;
  f32 sp2C;
  f32 sp28;

  func_hd_front_end_801FD484(&sp38, &sp34, &sp30, &sp2C, &sp28, 248.75f);
  func_hd_front_end_801FCF38(arg0, sp30, sp2C, sp28, arg4, arg5, arg6, arg7);
}

void func_hd_front_end_801FCF38(Vtx arg0[4], f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, f32 arg6, u8 arg7) {
    f32 spA0[4][4];
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;

    sp9C = -arg3;
    sp98 = 0.0f;
    sp94 = arg1;

    sp90 = arg1 * arg2;
    sp8C = -((arg1 * arg1) + (arg3 * arg3));
    sp88 = arg2 * arg3;

    sp84 = ((sqrtf((sp9C * sp9C) + (sp98 * sp98) + (sp94 * sp94)) / 50.0) * 2.0) / arg6;
    if (sp84 < 0.1) {
        sp84 = 0.1f;
    }
    sp9C /= sp84;
    sp98 /= sp84;
    sp94 /= sp84;
    sp80 = ((sqrtf((sp90 * sp90) + (sp8C * sp8C) + (sp88 * sp88)) / 50.0) * 2.0) / arg6;
    if (sp80 < 0.1) {
        sp80 = 0.1f;
    }
    sp90 /= sp80;
    sp8C /= sp80;
    sp88 /= sp80;
    guAlignF(spA0, 45.0f, arg1, arg2, arg3);

    sp7C = arg1 + sp9C;
    sp6C = arg2 + sp98;
    sp5C = arg3 + sp94;

    sp78 = arg1 + sp90;
    sp68 = arg2 + sp8C;
    sp58 = arg3 + sp88;

    sp74 = arg1 - sp9C;
    sp64 = arg2 - sp98;
    sp54 = arg3 - sp94;

    sp70 = arg1 - sp90;
    sp60 = arg2 - sp8C;
    sp50 = arg3 - sp88;
    guMtxXFMF(spA0, sp7C, sp6C, sp5C, &sp7C, &sp6C, &sp5C);
    guMtxXFMF(spA0, sp78, sp68, sp58, &sp78, &sp68, &sp58);
    guMtxXFMF(spA0, sp74, sp64, sp54, &sp74, &sp64, &sp54);
    guMtxXFMF(spA0, sp70, sp60, sp50, &sp70, &sp60, &sp50);
    arg0[0].v.tc[0] = 0;
    arg0[0].v.tc[1] = (arg7 != 0 ? 0 : arg5 - 1) << 6;

    arg0[1].v.tc[0] = (arg4 - 1) << 6;
    arg0[1].v.tc[1] = (arg7 != 0 ? 0 : arg5 - 1) << 6;

    arg0[2].v.tc[0] = ((arg4 - 1) << 6);
    arg0[2].v.tc[1] = (arg7 != 0 ? arg5 - 1 : 0) << 6;

    arg0[3].v.tc[0] = 0;
    arg0[3].v.tc[1] = (arg7 != 0 ? arg5 - 1 : 0) << 6;

    arg0[0].v.ob[0] = sp7C;
    arg0[0].v.ob[1] = sp6C;
    arg0[0].v.ob[2] = sp5C;

    arg0[1].v.ob[0] = sp78;
    arg0[1].v.ob[1] = sp68;
    arg0[1].v.ob[2] = sp58;

    arg0[2].v.ob[0] = sp74;
    arg0[2].v.ob[1] = sp64;
    arg0[2].v.ob[2] = sp54;

    arg0[3].v.ob[0] = sp70;
    arg0[3].v.ob[1] = sp60;
    arg0[3].v.ob[2] = sp50;
}

void func_hd_front_end_801FD484(f32* arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32 arg5) {
  if ((*arg0 >= 90.0) || (*arg0 < -90.0)) {
    if (*arg0 >= 90.0) {
      *arg0 = (180.0 - *arg0);
    } else {
      *arg0 = (-180.0 - *arg0);
    }
    *arg1 = (*arg1 + 180.0);
  }
  if (*arg1 >= 180.0) {
    *arg1 = (*arg1 - 360.0);
  } else if (*arg1 < -180.0) {
    *arg1 = (*arg1 + 360.0);
  }
  *arg2 = func_hd_code_80257514(-*arg1 * 0.017453292519943295) * func_hd_code_80257514(*arg0 * 0.017453292519943295) * arg5;
  *arg3 = func_hd_code_802574F0(*arg0 * 0.017453292519943295) * arg5;
  *arg4 = func_hd_code_802574F0(-*arg1 * 0.017453292519943295) * func_hd_code_80257514(*arg0 * 0.017453292519943295) * arg5;
}

f32 func_hd_front_end_801FD6B8(f32 arg0, f32 arg1, f32 arg2) {
  f32 sp4 = arg1 - arg0;

  if ((sp4 >= -arg2) && (arg2 > sp4)) {
    return sp4;
  }

  if (sp4 >= arg2) {
    return (-2.0f * arg2) + sp4;
  }

  return (2.0f * arg2) + sp4;
}

void func_hd_front_end_801FD748(void) {
    s32 sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 pad40;
    s32 pad3C;
    Vtx* sp38 = &D_hd_code_803156F8[D_hd_code_8035805C].unk1580[4];
    Vtx* sp34 = &D_hd_code_803156F8[D_hd_code_8035805C ^ 1].unk1580[4];

    for (sp74 = 0; sp74 < 0x80; sp74++) {
        sp48  = 0x40000000,
        sp4C = 0x40000000;

        for (sp70 = 0, sp50 = 0, sp54 = 0; sp70 < 4; sp70++) {
            sp6C = (sp74 * 4) + sp70;

            sp68 = sp38[sp6C].v.ob[0] = (sp34[sp6C].v.ob[0] - (D_hd_front_end_80217B6C == 3 ? D_hd_front_end_8021A934 * 40.0f : 0.0f));
            sp64 = sp38[sp6C].v.ob[1] = (sp34[sp6C].v.ob[1] + (D_hd_front_end_80217B6C == 3 ? D_hd_front_end_8021A938 * 40.0f : 0.0f));
            sp60 = sp38[sp6C].v.ob[2] = (sp34[sp6C].v.ob[2] - ((D_hd_front_end_802159F0[sp74] * D_hd_front_end_8021A918) / 925.0));
            if (ABS(sp68) >= 0xFA1) {
                sp54 = sp68;
            }
            if (ABS(sp64) >= 0xFA1) {
                sp50 = sp64;
            }
            if (ABS(sp68) < sp4C) {
                sp4C = ABS(sp68);
            }
            if (ABS(sp64) < sp48) {
                sp48 = ABS(sp64);
            }
        }
        sp44 = 0;
        if ((sp54 != 0) || (sp50 != 0)) {
            for (sp70 = 0; sp70 < 4; sp70++) {
                sp6C = (sp74 * 4) + sp70;
                sp5C = sp38[sp6C].v.ob[0];
                sp58 = sp38[sp6C].v.ob[1];
                if (sp54 != 0) {
                    sp68 = sp38[sp6C].v.ob[0] = (s16) (s32) func_hd_front_end_801FD6B8(0.0f, sp38[sp6C].v.ob[0], 3890.0f);
                }
                if (sp50 != 0) {
                    sp64 = sp38[sp6C].v.ob[1] = (s16) (s32) func_hd_front_end_801FD6B8(0.0f, sp38[sp6C].v.ob[1], 3890.0f);
                }
                if ((sp54 != 0) && ((sp5C * sp68) > 0)) {
                    sp44 = 1;
                }
                if ((sp50 != 0) && ((sp58 * sp64) > 0)) {
                    sp44 = 1;
                }
            }
        }
        if ((sp44 != 0) || (sp60 < 0) ||
            ((sp4C < (231250.0 / D_hd_front_end_8021A918)) &&
             (sp48 < (231250.0 / D_hd_front_end_8021A918)))) {
            func_hd_front_end_801FDCA4(sp38, sp74, 0x61A8);
        }
    }
}

void func_hd_front_end_801FDCA4(Vtx* arg0, s32 arg1, s32 arg2) {
  s32 sp24;
  s32 sp20;
  s32 sp1C;

  sp24 = arg1 * 4;
  D_hd_front_end_802159F0[arg1] = func_hd_code_8026A828(0x50, 0xC8);
  sp20 = func_hd_code_8026A828(-0xFA0, 0xFA0);
  sp1C = func_hd_code_8026A828(-0xFA0, 0xFA0);
  arg0[sp24].v.ob[0] = sp20 - 0x37;
  arg0[sp24].v.ob[1] = sp1C - 0x37;
  arg0[sp24].v.ob[2] = arg2;
  arg0[sp24 + 1].v.ob[0] = sp20 - 0x37;
  arg0[sp24 + 1].v.ob[1] = sp1C + 0x36;
  arg0[sp24 + 1].v.ob[2] = arg2;
  arg0[sp24 + 2].v.ob[0] = sp20 + 0x36;
  arg0[sp24 + 2].v.ob[1] = sp1C + 0x36;
  arg0[sp24 + 2].v.ob[2] = arg2;
  arg0[sp24 + 3].v.ob[0] = sp20 + 0x36;
  arg0[sp24 + 3].v.ob[1] = sp1C - 0x37;
  arg0[sp24 + 3].v.ob[2] = arg2;
}

void func_hd_front_end_801FDE50(void) {
  D_hd_front_end_8021A8F0 = func_hd_code_80272C5C(D_hd_front_end_8020E350, 0, 0x13U, 2U, 1, 1.0f);
}

void func_hd_front_end_801FDE98(void) {
  f32 sp24;
  f32 sp20;
  f32 sp1C;
  f32 sp18;

  sp24 = sqrtf((D_hd_front_end_8021AB4C * D_hd_front_end_8021AB4C) +
               (D_hd_front_end_8021AB50 * D_hd_front_end_8021AB50) +
               (D_hd_front_end_8021AB54 * D_hd_front_end_8021AB54));
  if (sp24 < 1.0) {
    sp24 = 1.0f;
  }
  sp20 = (D_hd_front_end_8021AB4C / sp24) * 120.0f;
  sp1C = (D_hd_front_end_8021AB50 / sp24) * 120.0f;
  sp18 = (D_hd_front_end_8021AB54 / sp24) * 120.0f;
  D_hd_front_end_8020E3A8[D_hd_code_8035805C].l[0].l.dir[0] = sp20;
  D_hd_front_end_8020E3A8[D_hd_code_8035805C].l[0].l.dir[1] = sp1C;
  D_hd_front_end_8020E3A8[D_hd_code_8035805C].l[0].l.dir[2] = sp18;
  osWritebackDCache(&D_hd_front_end_8020E3A8[D_hd_code_8035805C], 0x30);
}

void func_hd_front_end_801FE018(u8 arg0) {
  s32 sp34;
  s32 sp30;
  struct LevelData* sp2C;
  struct S_80367C04* sp28;

  D_hd_front_end_8021AB30 = &players[playerNumber];
  for (sp34 = 0; sp34 < 0x3C; sp34++) {
    if ((players[playerNumber].unk18[sp34] > 0) && (players[playerNumber].unk18[sp34] < 6)?1:0) {
      sp2C = &D_hd_front_end_8020D810[sp34];
      sp28 = &D_hd_code_802E8F94[sp34];
      for (sp30 = 0; sp30 < 8 && sp2C->unk1C[sp30] != -1; sp30++) {
        if ((D_hd_front_end_8021AB30->unk18[sp2C->unk1C[sp30]] == 0) &&
            (func_hd_front_end_801FE760(sp2C->unk1C[sp30]) == 0)) {
          D_hd_front_end_8021AB30->unk18[sp2C->unk1C[sp30]] = arg0;
            }
      }
      for (sp30 = 0; sp30 < 4 && sp2C->unk18[sp30] != -1; sp30++) {
        if (D_hd_front_end_8021AB30->unk54[sp34] & (1 << sp30)) {
          if (D_hd_front_end_8021AB30->unk18[sp2C->unk18[sp30]] == 0) {
            D_hd_front_end_8021AB30->unk18[sp2C->unk18[sp30]] = arg0;
          }
        }
      }
    }
  }
}

Gfx* func_hd_front_end_801FE238(Gfx* gfx, struct Model1* arg1) {
  Gfx* entry;

  entry = gfx;
  gDPSetTextureLOD(entry++, G_TL_LOD);
  gDPSetCycleType(entry++, G_CYC_2CYCLE);
  gDPSetRenderMode(entry++, G_RM_PASS, G_RM_AA_OPA_TERR2);
  if (D_hd_front_end_80217B6C == 3) {
    gSPSetLights1(entry++, D_hd_front_end_8020E3A8[D_hd_code_8035805C]);
    gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH | G_CULL_BACK | G_LIGHTING);
    gDPSetCombineMode(entry++, G_CC_TRILERP, G_CC_MODULATERGB);
  } else {
    gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH | G_CULL_BACK | G_LIGHTING);
    gDPSetCombineMode(entry++, G_CC_TRILERP, G_CC_DECALRGB);
  }
  gSPDisplayList(entry++, D_hd_front_end_8021A8F4);
  gDPPipeSync(entry++);
  gSPClearGeometryMode(entry++, G_LIGHTING);
  gDPSetPrimColor(entry++, 0, 0, 0, 0, 0, D_hd_front_end_8021AB21);
  gDPSetEnvColor(entry++, 0, 0, 0, ((s32) (D_hd_front_end_8021AB21 * 2) / 3));
  gSPDisplayList(entry++, D_hd_front_end_8021A8FC);
  gSPDisplayList(entry++, D_hd_front_end_8021A900);
  gSPEndDisplayList(entry++);
  return entry;
}


Gfx* func_hd_front_end_801FE5D0(Gfx* gfx, struct Model1* arg1) {
  Gfx* entry = gfx;
  gDPPipeSync(entry++);
  gDPSetCycleType(entry++, G_CYC_1CYCLE);
  gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
  gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
  gDPSetRenderMode(entry++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
  gDPSetCombineMode(entry++, G_CC_DECALRGBA, G_CC_DECALRGBA);
  gDPSetTextureFilter(entry++, G_TF_BILERP);
  gSPDisplayList(entry++, D_hd_front_end_8021A8F8);
  gDPPipeSync(entry++);
  return entry;
}

s32 func_hd_front_end_801FE760(u8 arg0) {
  u8 sp7 = 0;
  if (D_hd_code_802E8F94[arg0].unk1 > players[playerNumber].unk91 &&
      ((D_hd_code_802E8F94[arg0].unk0 & 0x81) || ((arg0 >= 0x2B) && (arg0 < 0x2F)))) {
    sp7 = 1;
      }
  if (arg0 == 0xA) {
    if (!(((players[playerNumber].unk18[0x37] > 0) && (players[playerNumber].unk18[0x37] < 6))?1:0)) {
      sp7 = 1;
    }
  }
  if (arg0 == 0xF) {
    if (!(((players[playerNumber].unk18[0x1C] > 0) && (players[playerNumber].unk18[0x1C] < 6))?1:0)) {
      sp7 = 1;
    }
  }
  if (arg0 == 0x3A) {
    if (!(((players[playerNumber].unk18[0x35] > 0) && (players[playerNumber].unk18[0x35] < 6))?1:0)) {
      sp7 = 1;
    }
  }
  if (arg0 == 5) {
    if (!(((players[playerNumber].unk18[7] > 0) && (players[playerNumber].unk18[7] < 6))?1:0)) {
      sp7 = 1;
    }
  }
  if (arg0 == 0x10) {
    if (!(((players[playerNumber].unk18[0x13] > 0) && (players[playerNumber].unk18[0x13] < 6))?1:0)) {
      sp7 = 1;
    }
  }
  if (arg0 == 0) {
    sp7 = 0;
  }
  return sp7;
}
