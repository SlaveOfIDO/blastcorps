#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/symbol_data.h"
#include "../hd_code/hd.h"
#include "../hd_code/yoshi.h"
#include "../hd_code/functions.h"
#include "../hd_code/variables.h"

struct S_80208044 {
  s32 unk0;
  s16 unk4[2];
};
extern struct S_80208044 D_hd_front_end_80208044;

// <data>
char *D_hd_front_end_80208040 = "SELECT VEHICLE!";
struct S_80208044 D_hd_front_end_80208044 = {
  (s32) D_hd_code_80304954, { 0xFFFF,  0x0000 }
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


Gfx* func_hd_code_8026BBD0(Gfx*, struct Model1*, s32*); /* extern */
Gfx* func_hd_front_end_80200BE0(Gfx*, struct Model1*, s32*); /* extern */
void func_hd_front_end_802021FC(struct S_80211AC0*, s32, s32); /* extern */
void func_hd_front_end_802025D0(u8, u32);              /* extern */
extern OSMesgQueue D_hd_code_80315180;
extern void* D_hd_code_8035806C;
extern s32 D_hd_code_80358078;
extern u16 D_hd_code_80370C28;
extern u16 D_hd_code_80370C2A;
extern s8 D_hd_code_80370C2C;
extern s8 D_hd_code_80370C2E;
extern Gfx* D_hd_front_end_80210F80[][4]; // Size: about 0x128
extern s32 D_hd_front_end_802153EC;
extern u32 D_hd_front_end_802153F0[0x50/0x4]; // Size: 0x50
extern u32 D_hd_front_end_80210EE0[19][2];

// The four observed fields are u32 byte-offsets from the blob's own base.
typedef struct ModelFile {
  /* 0x00 */ u8  unk00[0x14];   // header, not yet observed
  /* 0x14 */ u32 unk14;     // -> gfxOffset? display list / gfx data   (segment 6 source)
  /* 0x18 */ u32 unk18; // -> MtxSect (see below)
  /* 0x1C */ u32 sect1COffset;  // -> data section (resolved in ctor 80202100)
  /* 0x20 */ u8  unk20[0x0C];
  /* 0x2C */ u32 sect2COffset;  // -> data section (resolved in ctor 80202100)
  /* 0x30 */ // remainder = model data, interpreted by RSP not CPU
} ModelFile;

typedef struct MtxSect {
  /* 0x00 */ u32 unk0;
  /* 0x04 */ u32 unk4; // added to a matrix-table base -> guAlign target
} MtxSect;

// corrected array decl (was: s32 D_hd_front_end_80210E90[0x50/4])
extern ModelFile* D_hd_front_end_80210E90[20];   // up to 19 entries used


extern u8 D_hd_code_802E8C44[28];
extern ALBank* D_hd_code_80367738;
extern s16 D_hd_front_end_80211A68;
extern f32 D_hd_front_end_802153D4;
extern f32 D_hd_front_end_802153DC;
extern struct S_80367C04 D_hd_code_802E8F94[];

extern f32 D_hd_code_802FDAC0[20];
extern u8 D_hd_code_803643D4;
extern u16 D_hd_code_80364EF0[][0x10];

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
            func_hd_front_end_80202100(spA4, &D_hd_front_end_80210E90[D_hd_front_end_80211A6A], D_hd_front_end_80210EE0[D_hd_front_end_80211A6A], &D_hd_front_end_80210F78[D_hd_front_end_80211A6A]);
            D_hd_front_end_80211A70[spA4] = sp9C;
            sp9C = (s32) ((f64) sp9C + 380.0);
            guTranslate(&D_hd_front_end_802110A8[D_hd_front_end_80211A6A], D_hd_front_end_80211A70[spA4], (f32) D_hd_front_end_8020816C[spA4], 0.0f);
            guScale(&D_hd_front_end_80211568[D_hd_front_end_80211A6A], D_hd_code_802FDAC0[spA4], D_hd_code_802FDAC0[spA4], D_hd_code_802FDAC0[spA4]);
            func_hd_front_end_80202270(D_hd_front_end_80210E90[D_hd_front_end_80211A6A], D_hd_front_end_80210EE0[D_hd_front_end_80211A6A], &D_hd_front_end_80211AC0[D_hd_front_end_80211A6A]);
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

void func_hd_front_end_801E7598(void) {
    union {
        s16 hw;
        u8 bytes[2];
    } sp14C;
    s32 sp148;
    s32 sp144;
    struct Model1* sp140;
    Gfx* entry;

    sp144 = 0;
    sp14C.hw = D_hd_front_end_802081A8;
    sp140 = &D_hd_code_803156F8[D_hd_code_8035805C ^ 1];
    entry = sp140->dp;
    func_hd_code_8028A3E4();
    nextdma = 0;
    no_palette_dmas = 0;
    func_hd_code_802A5720();
    func_hd_code_8029E0AC();
    func_hd_code_8028A470();
    if (((u32) D_hd_code_80358060 >= 0xBU) && (areWeFading() == 0)) {
        if ((D_hd_code_80370C28 & 0x9000) && !(D_hd_code_80370C2A & 0x9000)) {
            func_hd_code_80275390(0x2000);
            sndPlaySfx((struct ALBankAlt_s* ) D_hd_code_80367738, 0x1E, NULL);
        } else if ((D_hd_code_80370C28 & 0x4000) && !(D_hd_code_80370C2A & 0x4000)) {
            sndPlaySfx((struct ALBankAlt_s* ) D_hd_code_80367738, 0xDE, NULL);
            D_hd_code_803643D4 = (u8) D_hd_front_end_802153E8;
            switch(D_hd_code_80364A88) {
                case 0x80:
                case 0x08000000:
                    D_hd_code_80364A98 = D_hd_code_80364A88;
                    break;
                default:
                    D_hd_code_80364A98 = 0x4000;
                break;
            }
        }
    }
    if ((D_hd_code_80370C2C < -0xA) && (areWeFading() == 0)) {
        if (D_hd_code_80370C2E < -0xA) {
            if (D_hd_front_end_80211A68 > 0) {
                D_hd_front_end_802153E4 = (u16) D_hd_front_end_802153E4 - D_hd_code_80370C2C;
            }
        } else {
            D_hd_front_end_802153E4 = 0x2EE;
        }
    }
    if ((D_hd_code_80370C28 & 0x200) && !(D_hd_code_80370C2A & 0x200) && (areWeFading() == 0)) {
        D_hd_front_end_802153E4 = 0x2EE;
    }
    if ((D_hd_code_80370C2C >= 0xB) && (areWeFading() == 0)) {
        if (D_hd_code_80370C2E >= 0xB) {
            if (D_hd_front_end_80211A68 < (D_hd_front_end_80211A6A - 1)) {
                D_hd_front_end_802153E6 = (u16) D_hd_front_end_802153E6 + D_hd_code_80370C2C;
            }
        } else {
            D_hd_front_end_802153E6 = 0x2EE;
        }
    }
    if ((D_hd_code_80370C28 & 0x100) && !(D_hd_code_80370C2A & 0x100) && (areWeFading() == 0)) {
        D_hd_front_end_802153E6 = 0x2EE;
    }
    if ((D_hd_code_8035805C == 0) && ((s32) (u16) D_hd_front_end_802153E4 >= 0x2EE)) {
        sndPlaySfx((struct ALBankAlt_s* ) D_hd_code_80367738, (s16) sp14C.bytes[D_hd_front_end_80211A68 == 0], NULL);
        if (D_hd_front_end_80211A68 != 0) {
            func_hd_front_end_801E74E8(D_hd_front_end_80211A68 - 1);
        }
        D_hd_front_end_802153E4 = (u16) D_hd_front_end_802153E4 - 0x2EE;
    }
    if ((D_hd_code_8035805C == 0) && ((s32) (u16) D_hd_front_end_802153E6 >= 0x2EE)) {
        sndPlaySfx((struct ALBankAlt_s* ) D_hd_code_80367738, (s16) sp14C.bytes[(D_hd_front_end_80211A68 + 1) == D_hd_front_end_80211A6A], NULL);
        if (D_hd_front_end_80211A68 + 1 != D_hd_front_end_80211A6A) {
            func_hd_front_end_801E74E8(D_hd_front_end_80211A68 + 1);
        }
        D_hd_front_end_802153E6 = (u16) D_hd_front_end_802153E6 - 0x2EE;
    }
    func_hd_code_80284E54(D_hd_code_803156F8[D_hd_code_8035805C].dp, D_hd_code_80358078, 1U, 1, 0x4D2, 0);

    D_hd_code_8035805C ^= 1;

    gSPSegment(entry++, 0x00, 0x00000000);
    gSPSegment(entry++, 0x02, osVirtualToPhysical(sp140));
    gSPSegment(entry++, 0x01, osVirtualToPhysical(D_hd_code_8035806C));
    gSPDisplayList(entry++, D_1000038);
    gSPDisplayList(entry++, D_1000010);
    gDPSetCycleType(entry++, G_CYC_FILL);
    gDPSetDepthImage(entry++, D_hd_code_80358058);
    gDPSetColorImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, D_hd_code_80358058);
    gDPSetFillColor(entry++, 0xFFFCFFFC);
    gDPFillRectangle(entry++, 0, 0, 319, 239);
    gDPSetColorImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, (u32) D_hd_code_80358050[D_hd_code_8035805C]);


    func_hd_code_80259450();
    entry = func_hd_front_end_80200BE0(entry, sp140, &D_hd_code_80358078);
    gDPPipeSync(entry++);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);

    func_hd_code_80259CCC(sp140, D_hd_front_end_80208040, D_hd_front_end_80208044.unk0, 0U, 0xA0, 0x50, 0x18, 0x15, 0x15, 1, 0, 0, 0, 0xA0);
    if ((u32) ((u32) (((u32) D_hd_code_803156C0 % 20U) * 0x3C) / 60U) < 0x10U) {
        D_hd_front_end_802081B0 = D_hd_front_end_802081B0 + (D_hd_front_end_802081B4 * 0x1E);
        if (D_hd_front_end_802081B0 >= 0x100) {
            D_hd_front_end_802081B0 = D_hd_front_end_802081B0 - 0x3C;
            D_hd_front_end_802081B4 = -D_hd_front_end_802081B4;
        }
        if (D_hd_front_end_802081B0 < 0) {
            D_hd_front_end_802081B0 += 0x3C;
            D_hd_front_end_802081B4 = -D_hd_front_end_802081B4;
        }
        func_hd_code_80259DC8(sp140, (s32) D_hd_front_end_80208040, D_hd_front_end_80208044.unk0, 0, 0xA0, 0x54, 0x15, 0x15, 0x15, 1, 0xFF, 0xFF - D_hd_front_end_802081B0, 0, 0xFF, 0xFF, (s32) D_hd_front_end_802081B0, 0, 0xFF);
    }
    func_hd_code_80259C24(&entry, sp140);
    if ((u32) D_hd_code_80358060 < 2U) {
        guPerspective(&sp140->unk1240, &D_hd_code_8035807C, 45.0f, 1.3333334f, 40.0f, 4000.0f, 1.0f);
    }

    D_hd_front_end_802153D8 = (f32) ((f64) D_hd_front_end_802153D8 + (((f64) (D_hd_front_end_802153D4 - D_hd_front_end_802153D8) * 0.1 * 60.0) / 60.0));
    D_hd_front_end_802153E0 = (f32) ((f64) D_hd_front_end_802153E0 + (((f64) (D_hd_front_end_802153DC - D_hd_front_end_802153E0) * 0.1 * 60.0) / 60.0));
    guLookAtReflect(&sp140->projection2, &sp140->lookAt, D_hd_front_end_802153D8, 1.0f, D_hd_front_end_802153E0, D_hd_front_end_802153D8, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);



    gSPPerspNormalize(entry++, D_hd_code_8035807C);
    gSPLookAtX(entry++, (u32) &sp140->lookAt);
    gSPLookAtY(entry++, (u32) &sp140->lookAt.l[1]);
    gSPMatrix(entry++, &sp140->unk1240, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(entry++, &sp140->projection2, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    gDPSetEnvColor(entry++, 0x00, 0x00, 0x00, 0xFF);


    for(sp148 = 0; sp148 < D_hd_front_end_80211A6A; sp148++) {
        u8 spEF = D_hd_code_8035805C & (sp148 == D_hd_front_end_80211A68);
        if ((ABS(D_hd_front_end_802153D8 - D_hd_front_end_80211A70[D_hd_front_end_802153C0[sp148]])) < 570.0) {
            u8* spE8 = D_hd_front_end_80210E90[sp148]->unk14 + (u8*)D_hd_front_end_80210E90[sp148];
            if (D_hd_front_end_80211A68 == sp148) {
                s32 spE4 = ((MtxSect*)(D_hd_front_end_80210E90[sp148]->unk18 + (u8*)D_hd_front_end_80210E90[sp148]))->unk4;
                Mtx* spE0 = (Mtx*)(D_hd_front_end_80210EE0[sp148][spEF] + (u8*)spE4);

                func_hd_front_end_802021FC(&D_hd_front_end_80211AC0[sp148], D_hd_front_end_80210EE0[sp148][D_hd_code_8035805C], D_hd_front_end_80210EE0[sp148][D_hd_code_8035805C ^ 1]);
                guAlign(spE0,
                        (f32)((D_hd_front_end_802153F0[sp148] += 4) % 360), 0.0f, 1.0f, 0.0f);
                osWritebackDCache(spE0, 0x40);
                func_hd_front_end_802025D0(
                    D_hd_front_end_802153C0[sp148],
                    (f32) ((D_hd_front_end_802153F0[sp148] + 0xB4) % 360U) * 11.37778);
            }
            gSPSegment(entry++, 0x06, spE8);
            gSPSegment(entry++, 0x07, D_hd_front_end_80210EE0[sp148][spEF]);


            gSPMatrix(entry++, &D_hd_front_end_80211A28, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPMatrix(entry++, &D_hd_front_end_802110A8[sp148], G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            gSPMatrix(entry++, &D_hd_front_end_80211568[sp148], G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);

            gSPDisplayList(entry++, D_hd_front_end_80210F78[sp148].unk0[D_hd_code_8035805C]);

            gSPMatrix(entry++, &D_hd_front_end_80211A28, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            gSPMatrix(entry++, &D_hd_front_end_802110A8[sp148], G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            gSPMatrix(entry++, &D_hd_front_end_80211568[sp148], G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
            gSPDisplayList(entry++, D_hd_front_end_80210F80[sp148][D_hd_code_8035805C]);
        }
    }

    D_hd_front_end_802153EC = D_hd_front_end_802153EC + D_hd_front_end_802081AC;
    if (D_hd_front_end_802081AC < 0) {
        D_hd_front_end_802153EC += D_hd_front_end_802081AC * 2;
    }
    if ((D_hd_front_end_802153EC < 0) || (D_hd_front_end_802153EC >= 0x10)) {
        D_hd_front_end_802153EC -= D_hd_front_end_802081AC * 2;
        D_hd_front_end_802081AC = -D_hd_front_end_802081AC;
    }
    if (D_hd_front_end_80211A68 + 1 != D_hd_front_end_80211A6A) {
        u8* spB4 = D_hd_code_802F47B0[0x13];
        sp144 = func_hd_code_80276130(sp140, 2U, sp144, D_hd_front_end_802153EC + 0x108, 0x20, ((s32) D_hd_front_end_802153EC / 4) + 0xC, 0x10, (u8) (s32) spB4[0], (u8) (s32) spB4[1], (u8) (s32) spB4[2], (u8) (s32) spB4[3], (u8) (s32) spB4[4], (u8) (s32) spB4[5], (u8) (s32) spB4[6], (u8) (s32) spB4[7], (u8) (s32) spB4[0], (u8) (s32) spB4[1], (u8) (s32) spB4[2], (u8) (s32) spB4[3], (u8) (s32) spB4[4], (u8) (s32) spB4[5], (u8) (s32) spB4[6], (u8) (s32) spB4[7]);
        sp144 = func_hd_code_80276080(sp140, 2, sp144, D_hd_front_end_802153EC + 0x10C, 0x23, ((s32) D_hd_front_end_802153EC / 4) + 0xC, 0x10, 0, 0, 0, 0xA0);
        entry = func_hd_code_80275DA4(entry, 0);
        gSPVertex(entry++, (u32) sp140->unk1E00, 8, 0);
        gSP1Triangle(entry++, 4, 5, 6, 0);
        gSP1Triangle(entry++, 4, 6, 7, 0);
        gSP1Triangle(entry++, 0, 1, 2, 0);
        gSP1Triangle(entry++, 0, 2, 3, 0);
    }
    if (D_hd_front_end_80211A68 > 0) {
        u8* sp9C = D_hd_code_802F47B0[0x13]; // TODO use sp9C
        sp144 = func_hd_code_80276130(sp140, 3U, sp144, 0x34 - D_hd_front_end_802153EC, 0x20, ((s32) D_hd_front_end_802153EC / 4) + 0xC, 0x10, (u8) (s32) D_hd_code_802F47B0[0x13][0], (u8) (s32) D_hd_code_802F47B0[0x13][1], (u8) (s32) D_hd_code_802F47B0[0x13][2], (u8) (s32) D_hd_code_802F47B0[0x13][3], (u8) (s32) D_hd_code_802F47B0[0x13][4], (u8) (s32) D_hd_code_802F47B0[0x13][5], (u8) (s32) D_hd_code_802F47B0[0x13][6], (u8) (s32) D_hd_code_802F47B0[0x13][7], (u8) (s32) D_hd_code_802F47B0[0x13][0], (u8) (s32) D_hd_code_802F47B0[0x13][1], (u8) (s32) D_hd_code_802F47B0[0x13][2], (u8) (s32) D_hd_code_802F47B0[0x13][3], (u8) (s32) D_hd_code_802F47B0[0x13][4], (u8) (s32) D_hd_code_802F47B0[0x13][5], (u8) (s32) D_hd_code_802F47B0[0x13][6], (u8) (s32) D_hd_code_802F47B0[0x13][7]);
        sp144 = func_hd_code_80276080(sp140, 3, sp144, 0x30 - D_hd_front_end_802153EC, 0x23, ((s32) D_hd_front_end_802153EC / 4) + 0xC, 0x10, 0, 0, 0, 0xA0);
        entry = func_hd_code_80275DA4(entry, 0);
        gSPVertex(entry++, (u32) &sp140->unk1D80[sp144], 8, 0);
        gSP1Triangle(entry++, 4, 5, 6, 0);
        gSP1Triangle(entry++, 4, 6, 7, 0);
        gSP1Triangle(entry++, 0, 1, 2, 0);
        gSP1Triangle(entry++, 0, 2, 3, 0);
    }
    entry = func_hd_code_8026BBD0(entry, &D_hd_code_803156F8[D_hd_code_8035805C], &D_hd_code_80358078);
    entry = func_hd_code_80274BF0(sp140, entry);
    gDPFullSync(entry++);
    gSPEndDisplayList(entry++);
    D_hd_code_80358078 = (s32) (((u32)entry - (u32)sp140) - 0x48B0) >> 3;
    for(sp148 = 0; sp148 < nextdma; sp148++) {
        osRecvMesg(&D_hd_code_80315180, NULL, 1);
    }
    for(sp148 = 0; sp148 < (nextdma - no_palette_dmas); sp148++) {
        func_hd_code_802A57AC();
    }
}
