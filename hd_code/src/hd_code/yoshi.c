#include "common.h"
#include "functions.h"
#include "gu/guint.h"
#include "structs.h"
#include "variables.h"
#include "yoshi.h"

struct S_802F9934 {
  u8 unk0;
  char unk1[15];
  s32 unk10;
};

struct S_802F48D0 {
  u8 unk0;
  u8 pad1;
  s16 unk2[0x10];
};
struct S_802F4A22 {
  s8 unk0; // safe type
  u8 pad1;
  u8 pad4[0x30 - 0x2];
};

Gfx* func_hd_code_80274AA4(s32);                     /* extern */
s32 func_hd_code_80272ED8(s32, s32, u8, s32, u32, s32, f32); /* extern */
void func_hd_code_80259BD4(Gfx**, struct Model1*);     /* extern */
void func_hd_code_80259DC8(struct Model1*, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
void func_hd_code_8026EF70(struct S_802F8BDC*);        /* extern */
u8* func_hd_code_8026F004(struct S_802F8BDC*, u16, s32); /* extern */
u8 func_hd_code_8026F644(struct S_802F8BDC*, struct S_8020C070*, s16); /* extern */
u16 func_hd_code_8026F82C(u16, u16, u16);             /* extern */
u16 func_hd_code_8026F8A8(u16, u16, u16, u16);        /* extern */
void func_hd_code_8026FB50(struct S_802F8BDC*);        /* extern */
Gfx* func_hd_code_80274998(Gfx*);                   /* extern */
Gfx* func_hd_code_80274B08(Gfx*);                   /* extern */
Gfx* func_hd_code_80275DA4(Gfx*, u8);                /* extern */
Gfx* func_hd_code_80274868(Gfx*);                     /* extern */
s32 func_hd_code_8025B558(u16*);                    /* extern */
void func_hd_code_8026BA7C(struct S_802F8BDC*);        /* extern */
s32 func_hd_code_80297EF8(s32);                     /* extern */
Gfx* func_hd_code_8026BCE0(Gfx* gfx, struct Model1* arg1, s32* arg2);

extern u16 D_hd_code_802E8C98[];
extern u16 D_hd_code_802E8C9C[];
extern u8 D_hd_code_802F4878[];
extern struct S_802F48D0 D_hd_code_802F48D0[];
extern struct S_802F4A22 D_hd_code_802F4A22[];
extern struct S_802F9934 D_hd_code_802F9934[7]; // Buildings data?
extern s32 D_hd_code_8030BE64;
extern s32 D_hd_code_8030BE90;
extern s32 D_hd_code_8030BE94;
extern u64 D_hd_code_80364A98;
extern u32 D_hd_code_80364AA8;

u8 bss_pad_8036B980[0x8036B9A8 - 0x8036B980];
char D_hd_code_8036B9A8[0x8036BA48 - 0x8036B9A8];
u8 D_8036BA48[0x50];
u8 D_8036BA98[0x8];
u8 D_8036BAA0[0x48];
u8 D_8036BAE8[0x14];
u32 D_8036BAFC;
u32 D_8036BB00;
u16 D_8036BB04;
u16 D_8036BB06;
f32 D_8036BB08;
s16 D_8036BB0C;
s8 D_8036BB0E;
s8 bss_pad_8036BB0F;
struct S_8020C070* D_8036BB10;
u16 D_8036BB14;
u16 D_8036BB16;
s16 D_8036BB18;
s16 D_8036BB1A;
s16 D_hd_code_8036BB1C;
s16 D_8036BB1E;
s16 D_8036BB20;
s16 bss_pad_8036BB22;
struct S_8020C070* D_hd_code_8036BB24;
f32 D_8036BB28;
f32 D_8036BB2C;
s32 D_8036BB30;
f32 D_8036BB34; // safe type
f32 D_8036BB38;
u16 D_8036BB3C;
u16 D_8036BB3E;
s32 D_8036BB40;
s32 D_8036BB44;
u16 D_8036BB48[0x34];

extern s8 D_80370C11;
extern s8 D_80370C12;
extern s8 D_80370C13;
extern s8 D_80370C14;

extern s32 D_803F7684;

/*
u64 D_hd_code_802F46C0[] = {

};

Gfx D_hd_code_802F4780[] = {
  gsSPClearGeometryMode(G_CULL_BOTH),
  gsSPVertex(0x0B000000, 4, 0),
  gsDPSetRenderMode(Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP | ZMODE_OPA | GBL_c1(G_BL_CLR_MEM, G_BL_A_SHADE, G_BL_CLR_MEM, G_BL_1), Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP | ZMODE_OPA | GBL_c2(G_BL_CLR_MEM, G_BL_A_SHADE, G_BL_CLR_MEM, G_BL_1)),
  gsSP1Triangle(0, 1, 3, 0),
  gsSP1Triangle(0, 2, 3, 0),
  gsDPPipeSync(),
};*/

extern u8 D_hd_code_802F47B0[0x100/8][8];
extern Gfx D_hd_code_802F98B0[];
extern s32 D_hd_code_802F9930;
extern u32 D_hd_code_803156C4;
extern u8 D_hd_code_8035805C;
extern u8 D_8036BAA2[];
extern u8 D_hd_code_802F499A[];

s32 func_hd_code_8026AD30(s16 arg0) {
  struct S_802F48D0* sp2C;
  u8 sp2B;
  s32 sp24;
  s32 sp20;
  s32 sp1C;
  s32 sp18;

  sp2B = 0;
  if (!(D_hd_code_80364A90 & 0x2104)) {
    return 0;
  }
  if (D_hd_code_80364AF0[playerNumber].unk91 >= 0xB) {
    return 0;
  }
  for(sp24 = 0; sp24 < 8 && sp2B == 0; sp24++) {
    sp2C = &D_hd_code_802F48D0[sp24];
    if (sp2C->unk0 == levelno) {
      for(sp20 = 0; sp20 < 16 && (sp2B == 0) && (sp2C->unk2[sp20] != -1); sp20++) {
        if (sp2C->unk2[sp20] == arg0) {
          sp1C = D_hd_code_80364AF0[playerNumber].unk88[arg0] < (s32) D_hd_code_802F499A[arg0];
          sp18 = levelno == 0;
          if (!D_8036BAA0[arg0+2] && ((sp18 != 0) || (sp1C != 0))) {
            if ((sp1C != 0) && (sp18 == 0)) {
              D_hd_code_80364AF0[playerNumber].unk88[arg0] += 1;
            }
            D_8036BAA0[arg0+2] = 1;
            func_hd_code_8026AF6C((s16) arg0 | 0x8000 | 0x2000);
            sp2B = 1;
          }
        }
      }
    }
  }

  return (s32) sp2B;
}

void func_hd_code_8026AF6C(u16 yd) {
  u16 sp1E;
  u16 sp1C;

  sp1E = D_8036BB14 & 0xFF;
  sp1C = yd & 0xFF;
  if (D_8036BB14) {
    if (D_8036BB14) {
      rmonPrintf("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "!yoshiDemandV", "yoshi.c", 0x520);
    }
    rmonPrintf("NEW: %x OLD:%x\n", yd, D_8036BB14);
  }
  if ((yd & 0x4000)) {
    if (!(yd == 0x4000)) {
      rmonPrintf("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "yd==YOSHI_DEMAND_OFF", "yoshi.c", 0x525);
    }
  }
  if ((sp1C == 0x1E) || (sp1C == 0x23) || (sp1C == 5) || (sp1C == 0xE)) {
    D_8036BB1A = -1;
  }
  if ((sp1E == 0x1E) || (sp1E == 0x23) || (sp1E == 5) || (sp1E == 0xE)) {
    rmonPrintf("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "1==0", "yoshi.c", 0x52C);
    rmonPrintf("OH MY GOD!\n");
    return;
  }
  if (D_8036BB14) {
    if (D_8036BB14 != 0) {
      rmonPrintf("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "!yoshiDemandV", "yoshi.c", 0x533);
    }
    rmonPrintf("GOING FOR NEW: %x OLD:%x\n", yd, D_8036BB14);
  }
  D_8036BB14 = yd;
}

u16 func_hd_code_8026B10C() {
  return D_8036BB14;
}

void func_hd_code_8026B118(s32 arg0) {
    struct S_802F8BDC* sp44;
    struct S_802F48D0* sp40;
    u8 sp3F;
    s32 sp38;
    s32 sp34;

    D_hd_code_8036BB1C = 1;
    D_8036BB16 = 0;
    D_8036BB14 = 0;
    D_8036BB1A = -1;
    D_8036BB18 = -1;
    D_8036BB0C = 0;
    sp44 = NULL;
    D_8036BB0E = 1;
    if ((u8) arg0 == 0) {
        for(sp38 = 0;sp38 < 0x6C;sp38++) {
            sp44 = &D_hd_code_802F8BDC[sp38];
            if (sp44->unk8 & 0x100) {
                sp44->unk8 = sp44->unk8 | 0x80;
            }
        }
    }
    D_hd_code_802F8BDC[6].unkC = 3;

    for(sp38 = 0; sp38 < 0x12; sp38++) {
        D_8036BAE8[sp38] = 0;
    }

    for(sp38 = 0; sp38 < 0x4B; sp38++) {
        D_hd_code_802F4A22[sp38].unk0 = -1;
    }

    switch(D_hd_code_80364A98) {
                case 0x8000000:
        case 0x80:
            D_8020C070[0x19].unk14 = 0;
        case 0x40000000:
            sp44 = &D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_hd_code_802E8F94[levelno].unk0)]];
            if (D_hd_code_802E8BF8 != 0) {
                D_8020C070[0x1D].unk0 &= ~1;
                D_8020C070[0x1D].unk14 = 0xB;
            }
            if (D_hd_code_802E8F94[levelno].unk0 == 1) {
                if (func_hd_code_80297EF8(levelno) != 0) {
                    D_8020C070[0x12].unk14 = 0x18;
                } else {
                    D_8020C070[0x12].unk14 = 0;
                }
            } else if (D_hd_code_802E8F94[levelno].unk0 == 0x20) {
                D_8020C070[0x17].unk0 &= ~0x400;
                D_8020C070[0x1A].unk0 &= ~0x400;

                D_8020C070[0x1B].unk14 = 0;
                D_8020C070[0x1C].unk14 = 0;
            } else {
                D_8020C070[0x17].unk14 = D_hd_code_802F4878[func_hd_code_8026F92C(D_hd_code_802E8F94[levelno].unk0)];
                D_8020C070[0x1A].unk14 = D_hd_code_802F4878[func_hd_code_8026F92C(D_hd_code_802E8F94[levelno].unk0)];

                D_8020C070[0x1B].unk14 = 0;
                D_8020C070[0x1C].unk14 = 0;
            }
            break;
         case 0x40000000000:
            sp44 = &D_hd_code_802F8BDC[0x16];
            break;
        case 0x4000000000000:
            sp44 = &D_hd_code_802F8BDC[0x38];
            break;



        case 0x40:
            sp44 = &D_hd_code_802F8BDC[D_hd_code_802F4870[func_hd_code_8026F92C(D_hd_code_802E8F94[levelno].unk0)]];
            if (D_hd_code_802E8F94[levelno].unk0 == 0x20) {
                D_hd_code_802F5804[0x1B].unk0 &= ~0x400;
                D_hd_code_802F5804[0x1C].unk0 &= ~0x400;
                D_hd_code_802F5804[0x1D].unk14 = 0;
                D_hd_code_802F5804[0x1E].unk14 = 0;
            } else {
                D_hd_code_802F5804[0x1B].unk14 = D_hd_code_802F4878[func_hd_code_8026F92C(D_hd_code_802E8F94[levelno].unk0)];
                D_hd_code_802F5804[0x1C].unk14 = D_hd_code_802F4878[func_hd_code_8026F92C(D_hd_code_802E8F94[levelno].unk0)];
                D_hd_code_802F5804[0x1D].unk14 = 0;
                D_hd_code_802F5804[0x1E].unk14 = 0;
            }
            break;

        case 0x2000:
            if ((((D_hd_code_80364AF0[playerNumber].unk18[levelno] > 0 && D_hd_code_80364AF0[playerNumber].unk18[levelno] < 6)?1:0) != 0) && (D_hd_code_802E8F94[levelno].unk0 == 1)) {
                sp44 = &D_hd_code_802F8BDC[6];
            } else {
                sp44 = NULL;
            }
            break;

        case 0x100000000000: {
            switch (levelno) {
            case 0x37:
                sp44 = &D_hd_code_802F8BDC[0x41];
                break;
            case 0x1C:
                sp44 = &D_hd_code_802F8BDC[0x42];
                break;
            case 0x35:
                sp44 = &D_hd_code_802F8BDC[0x43];
                break;
            case 0x7:
                sp44 = &D_hd_code_802F8BDC[0x44];
                break;
            case 0x13:
                sp44 = &D_hd_code_802F8BDC[0x45];
                break;
            default:
                sp44 = NULL;
            }
            break;
        }

        default:
            sp44 = NULL;
            break;
    }

    if (sp44 != NULL) {
        func_hd_code_8026BA7C(sp44);
    }
    if (D_hd_code_80364A98 & 0x2004) {
        for(sp38 = 0, sp3F = 0; sp38 < 8 && sp3F == 0; sp38++) {
            sp40 = &D_hd_code_802F48D0[sp38];
            if (sp40->unk0 == levelno) {
                for(sp34 = 0; sp34 < 0x10 && sp40->unk2[sp34] != -1;sp34++) {
                    func_hd_code_8026BA7C(&D_hd_code_802F8BDC[sp40->unk2[sp34]]);
                }
            }
        }
    }
}

void func_hd_code_8026B8F8(void) {
  if (D_hd_code_80364AA8 & 0x20) {
    D_8020C070[0x17].unk0 |= 0x400;
    D_8020C070[0x1A].unk0 |= 0x400;
    D_hd_code_802F5804[0x1B].unk0 |= 0x400;
    D_hd_code_802F5804[0x1C].unk0 |= 0x400;
    D_8020C070[0x17].unk14 = D_8020C070[0x1A].unk14 = D_hd_code_802F5804[0x1B].unk14 = D_hd_code_802F5804[0x1C].unk14 = func_hd_code_8026FA38(0, 0);

    if ((D_hd_code_80364A98 == 0x40)) {
      func_hd_code_8026BA7C(&D_hd_code_802F8BDC[D_hd_code_802F4870[func_hd_code_8026F92C( D_hd_code_80364AA8)]]);
      return;
    }

    func_hd_code_8026BA7C(&D_hd_code_802F8BDC[D_hd_code_802F4868[func_hd_code_8026F92C(D_hd_code_80364AA8)]]);
  }
}

// @internal
void func_hd_code_8026BA7C(struct S_802F8BDC* arg0) {
  struct S_80367BCC* sp2C;
  s32 sp28;
  u8 sp27;
  struct S_8020C070* sp20;

  sp27 = 4;
  func_hd_code_8026FB50(arg0);
  if (arg0->unk8 & 0x20000) {
    sp27 = 0;
  }
  for(sp28 = arg0->unkE; sp28 < (arg0->unkE + arg0->unk10); sp28++) {
    sp20 = &D_8036BB10[sp28];
    if (sp20->unk0 & 0x400) {
      sp2C = &D_hd_code_802F49F4[sp20->unk14];
      if (sp2C->unk2E == -1) {
        sp20->unk1A = func_hd_code_80272C5C((s32* ) sp2C->unk6, 0, sp2C->unk4, sp2C->unk2C, sp2C->unk2D | sp27, 1.0f);
        D_8036BA98[sp20->unk14] = 0;
      } else {
        sp20->unk1A = sp2C->unk2E;
      }
    }

  }
}

Gfx* func_hd_code_8026BBD0(Gfx* arg0, struct Model1* arg1, s32* arg2) {
  Gfx* entry;                                       /* compiler-managed */

  entry = arg0;
  if ((D_hd_code_8036BB1C == 1) && (D_8036BB18 != -1)) {
    rmonPrintf("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "!(yoshiState==YOSHI_OFF && currentYoshiWindow!=NO_YOSHI_WINDOW)", "yoshi.c", 0x61F);
  }
  entry = func_hd_code_8026BCE0(entry, arg1, arg2);
  if ((D_hd_code_8036BB1C == 1) && (D_8036BB18 != -1)) {
    rmonPrintf("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "!(yoshiState==YOSHI_OFF && currentYoshiWindow!=NO_YOSHI_WINDOW)", "yoshi.c", 0x623);
  }
  gDPPipeSync(entry++);
  *arg2 += entry - arg0;
  // This does not return any value... UB... needed for match
}

// @internal
Gfx* func_hd_code_8026BCE0(Gfx* gfx, struct Model1* arg1, s32* arg2) {
    struct S_802F8BDC* sp14C;
    struct S_8020C070* sp148;
    s32 sp144;
    s32 sp140;
    Gfx* entry;
    u16 sp13A;
    u16 sp138;
    u16 sp136;
    u16 sp134;
    u16 sp132;
    u16 sp130;
    u8* sp12C;
    f32 sp128;
    u16 sp126;
    u16 sp124;
    s32 sp120;
    u8 sp11F; // correct


    entry = gfx;
    sp128 = 1.0f;
    sp130 = 0;
    sp132 = (D_hd_code_803156C4 - D_8036BB40) * 15;
    D_8036BB40 = D_hd_code_803156C4;
    D_8036BB0C = D_8036BB0C + (D_8036BB0E * sp132);
    if (D_8036BB0C >= 0x100) {
        D_8036BB0C = 0xFF;
        D_8036BB0E = -D_8036BB0E;
    }
    if (D_8036BB0C < 0) {
        D_8036BB0C = 0;
        D_8036BB0E = -D_8036BB0E;
    }
    sp12C = D_hd_code_802F47B0[0x10];
    sp12C[1] = 0xFF - D_8036BB0C;
    sp12C[5] = D_8036BB0C;

    sp12C = D_hd_code_802F47B0[0x11];
    sp12C[1] = 0xAA - (D_8036BB0C * 2) / 3;
    sp12C[5] =  (D_8036BB0C * 2) / 3;

    sp12C = D_hd_code_802F47B0[0x12];
    sp12C[0] = sp12C[1] = (0xFF - D_8036BB0C);
    sp12C[4] = sp12C[5] = (0x00 + (u8)D_8036BB0C);


    sp12C = D_hd_code_802F47B0[0x13];
    sp12C[2] = sp12C[1] = (0xFF - D_8036BB0C);
    sp12C[6] = sp12C[5] = (0x00 + (u8)D_8036BB0C);


    sp12C = D_hd_code_802F47B0[0x14];
    sp12C[2] = (0xFF - D_8036BB0C);
    sp12C[6] = (D_8036BB0C);

    if ((D_hd_code_80364A90 == 0x200) && (D_hd_code_803643DB != 0) && (D_hd_code_803643D6 != 0) && ((D_8036BB1A = -1, (D_hd_code_8036BB1C == 4)) || (D_hd_code_8036BB1C == 2))) {
        rmonPrintf("putting off!\n");
        func_hd_code_8026AF6C(0x4000U);
    }
    if ((D_8036BB18 == -1) && (D_8036BB14 & 0x4000)) {
        rmonPrintf("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "1==0", "yoshi.c", 0x65B);
        D_8036BB14 = 0;
        return gfx;
    }
    if (D_8036BB14 != 0) {
        sp126 = D_8036BB14 & 0xFF;
        sp124 = D_8036BB14 & 0x2000;
        sp120 = 0;
        rmonPrintf("yoshiDemand=%x\n", D_8036BB14);
        if (D_8036BB14 & 0x8000) {
            D_8036BB1A = -1;
            if (D_8036BB18 != -1) {
                sp120 = D_hd_code_802F8BE4[D_8036BB18].unk0 & 0x08000000;
            }
            if ((D_hd_code_8036BB1C == 1) || (sp124 != 0) || (sp120 != 0)) {
                D_8036BB18 = (s16) sp126;
                D_hd_code_8036BB1C = 1;
            } else {
                D_8036BB1A = (s16) sp126;
            }
        }
        if (D_hd_code_8036BB1C != 8) {
            sp130 = 1;
        }
        D_8036BB14 = 0;
    }
    if (D_8036BB18 == -1) {
        D_8036BB18 = D_8036BB1A;
        D_8036BB1A = -1;
        if (D_8036BB18 == -1) {
            return gfx;
        }
        sp130 = 1;
    }
    sp14C = &D_hd_code_802F8BDC[D_8036BB18];
    func_hd_code_8026FB50(sp14C);
    if ((sp14C->unk8 & 0x20) && (D_hd_code_8036BB1C == 2)) {
        if ((((D_80370C28 & 0x8000) && !(D_80370C2A & 0x8000)) || ((sp14C->unk8 & 0x80000000) && (D_80370C28 & 0x1000) && !(D_80370C2A & 0x1000))) && (sp14C->unk1A != 0)) {
            sp13A = D_8036BB10[sp14C->unk18].unk16;
            if (sp13A != 0) {
                sndPlaySfx(D_hd_code_80367738, (s16) sp13A, NULL);
            }
            if (D_8036BB10[sp14C->unk18].unk0 & 0x10) {
                D_hd_code_802E8BD4 = 1;
            }
            D_8036BB16 = sp14C->unk18;
            sp130 = 1;
        }
        if ((D_80370C28 & 0x4000) && !(D_80370C2A & 0x4000)) {
            if ((sp14C->unk8 & 0x20000000) && (sp14C->unk1A != 0)) {
                sndPlaySfx(D_hd_code_80367738, 0xDE, NULL);
                D_8036BB16 = 0xFFFF;
                sp130 = 1;
                if (sp14C->unk8 & 0x40000000) {
                    D_hd_code_802E8BD4 = 1;
                }
            } else {
                sndPlaySfx(D_hd_code_80367738, 0xD0, NULL);
            }
        }
    }
    if (sp130 != 0) {
        D_8036BAFC = D_hd_code_803156C4;
        switch(D_hd_code_8036BB1C) {
            case 8:
                D_8036BAFC = D_hd_code_803156C4 - D_8036BB08 * D_8036BB38 * D_8036BB34;
            case 1:
                D_hd_code_8036BB1C = 4;
                D_8036BB34 = 1.0f;
                if (sp14C->unk8 & 0x18) {
                    D_8036BB08 = 40.0f;
                } else {
                    D_8036BB08 = 13.333333f;
                }
                func_hd_code_8026EF70(sp14C);
                sp13A = sp14C->unk12;
                if (sp13A != 0) {
                    sndPlaySfx(D_hd_code_80367738, (s16) sp13A, NULL);
                }
                if (!(sp14C->unk8 & 0x400)) {

                    for(sp138 = sp14C->unkE;(!(D_8036BB10[sp138].unk0 & 1) && sp138 < (sp14C->unkE + sp14C->unk10)); sp138++) {}
                    sp14C->unk18 = sp138;
                }
                for(sp138 = sp14C->unkE; sp138 < (sp14C->unkE + sp14C->unk10); sp138++) {
                    sp148 = sp138 + D_8036BB10;
                    if (sp148->unk0 & 0x20) {
                        if (sp14C->unk8 & 0x80000) {
                            sp148->unk2 = func_hd_code_8025B498(sp14C->unk0 / 2, sp148->unk6, sp148->unkC, sp148->unk10);
                        } else {
                            sp148->unk2 = func_hd_code_8025B498((u16) ((s32) sp14C->unk0 / 2), sp148->unk6, sp148->unkC, sp148->unk10);
                        }
                    }
                }
                if (sp14C->unk8 & 1) {
                    D_hd_code_802E8BD8 = 1;
                }
                if (sp14C->unk8 & 2) {
                    func_hd_code_80261570(0.0f);
                }
                if (sp14C->unk8 & 0x100000) {
                    D_8036BB28 = (f32) sp14C->unk2;
                } else {
                    D_8036BB28 = (f32) (((s32) sp14C->unk2 / 2) - D_8036BB10[sp14C->unk18].unk4);
                    if (sp14C->unk8 & 0x40000) {
                        D_8036BB28 = D_8036BB28 - (f32) ((s32) D_8036BB10[sp14C->unk18].unk8 / 2);
                    }
                }
                D_8036BB2C = D_8036BB28;
                break;
            case 4:
                D_8036BAFC = (D_8036BB38 - sp128) * D_8036BB08 + D_hd_code_803156C4;
            case 2:
                D_hd_code_8036BB1C = 8;
                sp13A = sp14C->unk14;
                if (sp13A != 0) {
                    sndPlaySfx(D_hd_code_80367738, (s16) sp13A, NULL);
                }
                if (sp14C->unk8 & 0x200000) {
                    D_hd_code_802E8BD4 = 1;
                }
                if (sp14C->unk8 & 4) {
                    func_hd_code_80261570(1.0f);
                }
                break;
        }
    }
    switch (D_hd_code_8036BB1C) {
    case 2:
        if (sp14C->unk8 & 0x100000) {
            sp11F = D_8036BB2C < (sp14C->unk2 / 8 - D_8036BB10[sp14C->unkE + sp14C->unk10 - 1].unk4);
        } else {
            sp11F = sp14C->unkC
                && (D_hd_code_803156C4 - D_8036BAFC) / 60.0f > sp14C->unkC
                && (!(sp14C->unk8 & 0x400000) || !(D_8036BB1E != 0))
                ;
        }
        if (sp11F) {
            sp13A = sp14C->unk14;
            if (sp13A != 0) {
                sndPlaySfx(D_hd_code_80367738, (s16) sp13A, NULL);
            }
            if (sp14C->unk8 & 0x2000) {
                func_hd_code_80261570(0.0f);
            }
            D_hd_code_8036BB1C = 8;
            D_8036BAFC = D_hd_code_803156C4;
        }
        break;
    case 4:

        {
            D_8036BB38 = (f32)(D_hd_code_803156C4 - D_8036BAFC) / D_8036BB08;
            if (sp128 < D_8036BB38) {
                D_8036BAFC = D_hd_code_803156C4;
                D_hd_code_8036BB1C = 2;
                D_8036BB38 = sp128;

                if (sp14C->unk8 & 0x40) {
                    D_8036BB3C = 0x200U;
                    D_8036BB3E = 0x100U;
                } else {
                    D_8036BB3C = 0x800U;
                    D_8036BB3E = 0x400U;
                }
                if (sp14C->unk8 & 0x10000000) {
                    sp14C->unk1A = 1U;
                } else {
                    sp14C->unk1A = 0U;
                }
                if (func_hd_code_8026F8A8(sp14C->unkE, sp14C->unk10, sp14C->unk18, 1) == sp14C->unk18) {
                    sp14C->unk1A = 1U;
                }
            }
            break;
        }
    case 8:
        {
            D_8036BB38 = sp128 - (D_hd_code_803156C4 - D_8036BAFC) / D_8036BB08;
            if (D_8036BB38 < 0.001) {
                D_8036BB38 = 0;
                D_hd_code_8036BB1C = 1;
                if (sp14C->unk8 & 0x02000000) {
                    D_hd_code_802E8BD4 = 1;
                }

                if (sp14C->unk8 & 0x100) {
                    sp14C->unk8 = sp14C->unk8 & ~0x80;
                }
                D_8036BB18 = -1;
                return gfx;
            }
            break;
        }
    }

    if (D_hd_code_8036BB1C != 1) {
        D_8036BB20 = (func_hd_code_802574F0(4.71 + ((D_8036BB38 * D_8036BB34) / sp128) * 1.57) + 1.0) * 255.0;
    }
    if (D_hd_code_8036BB1C != 1 && D_8036BB38 * D_8036BB34 > 0.1) {
        sp136 = (u16) sp14C->unk0 / 2;
        sp134 = (u16) sp14C->unk2 / 2;
        guOrtho(&arg1->unk1240, (f32) (-sp14C->unk4 - (sp136)), (f32) ((-sp14C->unk4 - (sp136)) + 0x13F), (f32) ((-(s16) sp14C->unk6 - (sp134)) + 0xEF), (f32) (-(s16) sp14C->unk6 - (sp134)), -256.0f, 256.0f, 256.0f);
        gSPMatrix(entry++, OS_PHYSICAL_TO_K0(&arg1->unk1240), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        if (sp14C->unk8 & 0x10) {
            guAlign(&arg1->unk12C0, 180.0 - 180.0 * ((D_8036BB38 * D_8036BB34) / sp128), 2.0f, 0.0f, 1.0f);
            gSPMatrix(entry++, OS_PHYSICAL_TO_K0(&arg1->unk12C0), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        } else {
            guTranslate(&arg1->unk12C0, 0.0f, 0.0f, 0.0f);
            gSPMatrix(entry++,  OS_PHYSICAL_TO_K0(&arg1->unk12C0), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        }
        gSPMatrix(entry++, OS_PHYSICAL_TO_K0(&arg1->unk1300), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
        gSPPopMatrix(entry++, G_MTX_MODELVIEW);
        if (sp14C->unk8 & 8) {
            guScale(&arg1->unk1300, (sp136 * D_8036BB38 * D_8036BB34) / 1000.0f, (sp134 * D_8036BB38 * D_8036BB34) / 1000.0f, 1.0f);
            gSPMatrix(entry++, OS_PHYSICAL_TO_K0(&arg1->unk1300), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
        } else {
            guScale(&arg1->unk1300, sp136 / 1000.0f, sp134 / 1000.0f, 1.0f);
            gSPMatrix(entry++, OS_PHYSICAL_TO_K0(&arg1->unk1300), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
        }
        gDPPipeSync(entry++);
        gDPSetRenderMode(entry++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
        gDPSetCombineMode(entry++, G_CC_SHADE, G_CC_SHADE);
        gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
        gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
        gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_OFF);

        if (!(sp14C->unk8 & 0x200)) {
            gSPDisplayList(entry++, &D_hd_code_802F98B0);
        }
        gSPPopMatrix(entry++, G_MTX_MODELVIEW);

        if (sp14C->unk8 & 8) {
            guScale(&arg1->unk1280, D_8036BB38, D_8036BB38, 1.0f);
            gSPMatrix(entry++, OS_PHYSICAL_TO_K0(&arg1->unk1280), G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
        }
        if ((sp14C->unk8 & 0x20) && (D_hd_code_8036BB1C == 2)) {
            s32 spD8 = 0;
            s32 spD4 = 0;

            if (D_8036BB3C == 0x800) {
                if ((D_80370C12 >= 0x1F) && (D_80370C14 < 0x1F)) {
                    spD8 = 1;
                } else {
                    spD8 = 0;
                }
            } else if ((D_80370C11 < -0x1E) && (D_80370C13 >= -0x1E)) {
                spD8 = 1;
            } else {
                spD8 = 0;
            }
            if (D_8036BB3E == 0x400) {
                if ((D_80370C12 < -0x1E) && (D_80370C14 >= -0x1E)) {
                    spD4 = 1;
                } else {
                    spD4 = 0;
                }
            } else if ((D_80370C11 >= 0x1F) && (D_80370C13 < 0x1F)) {
                spD4 = 1;
            } else {
                spD4 = 0;
            }
            if (((D_80370C28 & D_8036BB3C) && !(D_80370C2A & D_8036BB3C)) || (spD8 != 0)) {
                u16 spD2 = func_hd_code_8026F82C(sp14C->unkE, sp14C->unk18, 1);
                sp13A = sp14C->unk16;
                if (sp13A != 0) {
                    if (spD2 != sp14C->unk18) {
                        sndPlaySfx(D_hd_code_80367738, (s16) sp13A, NULL);
                    } else {
                        sndPlaySfx(D_hd_code_80367738, 0xD0, NULL);
                    }
                }
                D_8036BB28 += D_8036BB10[sp14C->unk18].unk4 - D_8036BB10[spD2].unk4;
                sp14C->unk18 = spD2;
            } else if (((((sp14C->unk1A ? 0 : 0x8000) | D_8036BB3E) & D_80370C28) && !(((sp14C->unk1A ? 0 : 0x8000) | D_8036BB3E) & D_80370C2A)) || spD4) {
                u16 spD0 = func_hd_code_8026F8A8(sp14C->unkE, sp14C->unk10, sp14C->unk18, 1);
                if (func_hd_code_8026F8A8(sp14C->unkE, sp14C->unk10, spD0, 1) == spD0) {
                    sp14C->unk1A = 1U;
                }
                sp13A = sp14C->unk16;
                if (sp13A != 0) {
                    if (spD0 != sp14C->unk18) {
                        sndPlaySfx(D_hd_code_80367738, (s16) sp13A, NULL);
                    } else {
                        sndPlaySfx(D_hd_code_80367738, 0xD0, NULL);
                    }
                }
                D_8036BB28 += D_8036BB10[sp14C->unk18].unk4 - D_8036BB10[spD0].unk4;
                sp14C->unk18 = spD0;
                D_8036BAFC = D_hd_code_803156C4;
            }
        }
        if (sp14C->unk8 & 0x4000) {
            if (sp14C->unk8 & 0x100000) {
                if (!(sp14C->unkC && (D_hd_code_803156C4 - D_8036BAFC) / 60.0f < sp14C->unkC)) {
                    if (sp14C->unk8 & 0x800000) {
                        D_8036BB2C -= 0.5;
                    } else {
                        D_8036BB2C -= 1.0;
                    }
                }
            } else {
                D_8036BB2C += (D_8036BB28 - D_8036BB2C) * 0.1;
            }
            if (sp14C->unk8 & 0x10000) {
                s32 spCC = 0;
                s16 spCA;

                if (sp14C->unk8 & 0x40000) {
                    spCA = 0x12;
                } else {
                    spCA = 0x1C;
                }
                if ((!(D_hd_code_80364A90 & 0xC9FD0FE79BFF80B0)) || (D_hd_code_8035805C != 0)) {
                    D_8036BB44 += D_hd_code_802F9930;
                }
                if (D_hd_code_802F9930 < 0) {
                    D_8036BB44 += D_hd_code_802F9930 * 2;
                }
                if ((D_8036BB44 < 0) || (D_8036BB44 >= 8)) {
                    D_8036BB44 -= D_hd_code_802F9930 * 2;
                    D_hd_code_802F9930 = -D_hd_code_802F9930;
                }
                if (func_hd_code_8026F8A8(sp14C->unkE, sp14C->unk10, sp14C->unk18, 1) != sp14C->unk18) {
                    u8* spC4 = D_hd_code_802F47B0[0x12];
                    spCC = func_hd_code_80276130(arg1, 0, spCC, -sp136, (sp134 - D_8036BB44) - spCA, 0x10, ((s32) D_8036BB44 / 2) + 0xA, (s32) spC4[0], (s32) spC4[1], (s32) spC4[2], (s32) D_8036BB20, (s32) spC4[4], (s32) spC4[5], (s32) spC4[6], (s32) D_8036BB20, (s32) spC4[0], (s32) spC4[1], (s32) spC4[2], (s32) D_8036BB20, (s32) spC4[4], (s32) spC4[5], (s32) spC4[6], (s32) D_8036BB20);
                    spCC = func_hd_code_80276080(arg1, 0, spCC, -sp136 - 3, ((sp134 - D_8036BB44) - spCA) + 3, 0x10, ((s32) D_8036BB44 / 2) + 0xA, 0, 0, 0, (s16) D_8036BB20 / 2);
                    entry = func_hd_code_80275DA4(entry, 1);
                    gSPVertex(entry++, (u32) &arg1->unk1E00, 8, 0);
                    gSP1Triangle(entry++, 4, 5, 6, 0);
                    gSP1Triangle(entry++, 4, 6, 7, 0);
                    gSP1Triangle(entry++, 0, 1, 2, 0);
                    gSP1Triangle(entry++, 0, 2, 3, 0);
                }
                if (func_hd_code_8026F82C(sp14C->unkE, sp14C->unk18, 1) != sp14C->unk18) {
                    u8 *spAC = D_hd_code_802F47B0[0x12];
                    spCC = func_hd_code_80276130(arg1, 1, spCC, -sp136, (D_8036BB44 - sp134) + spCA, 0x10, D_8036BB44/2 + 10, spAC[0], spAC[1], spAC[2], D_8036BB20, spAC[4], spAC[5], spAC[6], D_8036BB20, *((volatile u8*)spAC), spAC[1], spAC[2], D_8036BB20, spAC[4], spAC[5], spAC[6], D_8036BB20);
                    spCC = func_hd_code_80276080(arg1, 1, spCC, -sp136 - 3, ((D_8036BB44 - sp134) + spCA) - 3, 0x10, ((s32) D_8036BB44 / 2) + 0xA, 0, 0, 0, (s16) D_8036BB20 / 2);
                    entry = func_hd_code_80275DA4(entry, 1);
                    gSPVertex(entry++, (u32) (&arg1->unk1D80[spCC]), 8, 0);
                    gSP1Triangle(entry++, 4, 5, 6, 0);
                    gSP1Triangle(entry++, 4, 6, 7, 0);
                    gSP1Triangle(entry++, 0, 1, 2, 0);
                    gSP1Triangle(entry++, 0, 2, 3, 0);
                }
            }
        } else {
            D_8036BB2C = 0.0f;
        }
        D_8036BB30 = (s32) D_8036BB2C;
        if (sp14C->unk8 & 0x1000) {
            entry = (sp14C->unk8 & 0x20000) ? func_hd_code_80274868(entry) : func_hd_code_80274998(entry);
            for(sp138 = sp14C->unkE; sp138 < sp14C->unkE + sp14C->unk10; sp138++) {
                sp148 = &D_8036BB10[sp138];
                if ((sp148->unk0 & 0x800) || !(sp148->unk0 & 0x400) || (sp148->unk0 & 0x300 && !(sp138 <= D_8036BB04))) {
                    continue;
                }

                {
                    struct S_80367BCC* sp94;
                    s16 sp92;
                    s16 sp90;
                    u8 sp8F;
                    u8 sp8E;
                    u8 sp8D;
                    u8 sp8C;
                    u8 sp8B;

                    sp94 = &D_hd_code_802F49F4[sp148->unk14];
                    sp92 = (sp14C->unk8 & 0x20000)!=0 ? sp14C->unk4 : -sp136;
                    sp90 = (sp14C->unk8 & 0x20000)!=0 ? sp14C->unk6 : -sp134;
                    sp8F = 1;
                    sp8E = sp94->unk1B[0xA];
                    if ((sp148->unk0 & 1) && (sp138 != sp14C->unk18)) {
                        sp8F = 0;
                    }
                    sp8D = D_8036BA48[sp148->unk14];
                    sp8C = D_8036BA48[sp148->unk14] = ((u32) ((u32) ((u32) (D_hd_code_803156C4 * 0x3C) / 60U) / (u8) sp94->unk26) % (u8) sp94->unk1A);
                    if ((sp8C != sp8D) && ((sp8F != 0) || (D_8036BA98[sp148->unk14] != 0))) {
                        D_8036BA98[sp148->unk14] = (u8) ((s32) (D_8036BA98[sp148->unk14] + 1) % (s32) sp94->unk1A);
                    }
                    sp8B = sp94->unk1B[D_8036BA98[sp148->unk14]];
                    if (sp8B != 0) {
                        if (sp8F != 0) {
                            if ((sp138 == sp14C->unk18) && (sp148->unk0 & 0x40)) {
                                sp8E |= 8;
                            }

                            entry = func_hd_code_80272ED8(entry, (sp148->unk1A + sp8B) - 1, sp94->unk0 + sp148->unk2 + sp92, ((sp148->unk0 & 0x1000) ? D_8036BB30 : 0) + (sp94->unk2 + sp148->unk4 + sp90), func_hd_code_8026F644(sp14C, sp148, ((sp148->unk4 + sp94->unk2) - sp134) + D_8036BB30 + 8) * D_8036BB38 * D_8036BB34, sp8E, sp94->unk28);
                        } else {
                            entry = func_hd_code_80272ED8(entry, (sp148->unk1A + sp8B) - 1, sp94->unk0 + sp148->unk2 + sp92, ((sp148->unk0 & 0x1000) ? D_8036BB30 : 0) + (sp94->unk2 + sp148->unk4 + sp90), func_hd_code_8026F644(sp14C, sp148, ((sp148->unk4 + sp94->unk2) - sp134) + D_8036BB30 + 8) * D_8036BB38 * D_8036BB34 * 0.7, sp8E & ~1, sp94->unk28);
                        }
                    }
                }




            }

            entry = (sp14C->unk8 & 0x20000) ? func_hd_code_80274AA4(entry) : func_hd_code_80274B08(entry);
        }
        if ((D_8036BB18 < 0x62) || (D_8036BB18 >= 0x6C) || ((D_hd_code_80364A90 == 2))) {
            for(sp138 = sp14C->unkE; ((sp138) < (sp14C->unkE + sp14C->unk10)); sp138++) {
                sp148 = &D_8036BB10[sp138];
                sp140 = 0;
                sp144 = func_hd_code_8026F004(sp14C, sp138, 0);

                if ((sp148->unk0 & 0x80) && !(sp148->unk0 & 0x800)) {
                    if (sp138 == sp14C->unk18) {
                        func_hd_code_80259DC8(arg1, sp144, sp140, sp148->unk0 & 8, 0, (sp148->unk2 - sp136) - 3, ((sp148->unk0 & 0x1000) ? D_8036BB30 : 0) + (sp148->unk4 - sp134) + 3, sp148->unk6, sp148->unk8, 1, 0, 0, 0, D_8036BB20 * D_hd_code_802F47B0[sp148->unk19][3] * func_hd_code_8026F644(sp14C, sp148, (sp148->unk4 - sp134) + D_8036BB30) / 65025 / 2, 0, 0, 0, D_8036BB20 * D_hd_code_802F47B0[sp148->unk19][3] * func_hd_code_8026F644(sp14C, sp148, (sp148->unk4 - sp134) + D_8036BB30 + sp148->unk8) / 65025 / 2);
                    } else if (!(sp148->unk0 & 4) || (((D_hd_code_803156C4 % 23U) * 0x3C) / 60U) < 0x10U) {
                        func_hd_code_80259DC8(arg1, sp144, sp140, sp148->unk0 & 8, 0, (sp148->unk2 - sp136) - 3, ((sp148->unk0 & 0x1000) ? D_8036BB30 : 0) + (sp148->unk4 - sp134) + 3, sp148->unk6, sp148->unk8, 1, 0, 0, 0, D_8036BB20 * D_hd_code_802F47B0[sp148->unk18][3] * func_hd_code_8026F644(sp14C, sp148, (sp148->unk4 - sp134) + D_8036BB30) / 65025 / 2, 0, 0, 0, D_8036BB20 * D_hd_code_802F47B0[sp148->unk18][3] * func_hd_code_8026F644(sp14C, sp148, (sp148->unk4 - sp134) + D_8036BB30 + sp148->unk8) / 65025 / 2);
                    }
                }
            }
        }
        for(sp138 = sp14C->unkE; (sp138 < (sp14C->unkE + sp14C->unk10)); sp138++) {
                            sp148 = &D_8036BB10[sp138];
                sp140 = 0;
                sp144 = func_hd_code_8026F004(sp14C, sp138, 0);
                if (!(sp148->unk0 & 0x800)) {
                    if (sp138 == sp14C->unk18) {
                        if ((!(sp148->unk0 & 4) || ((u32) ((u32) (((u32) D_hd_code_803156C4 % 23U) * 0x3C) / 60U) < 0x10U)) && (!(sp148->unk0 & 0x40) || ((u32) ((u32) (((u32) D_hd_code_803156C4 % 15U) * 0x3C) / 60U) < 0xBU))) {
                            func_hd_code_80259DC8(arg1, sp144, sp140, sp148->unk0 & 8, 0, sp148->unk2 - sp136, (sp148->unk0 & 0x1000 ? D_8036BB30 : 0) + (sp148->unk4 - sp134), (s32) sp148->unk6, (s32) sp148->unk8, 1,
                                                  D_hd_code_802F47B0[sp148->unk19][0],
                                                  D_hd_code_802F47B0[sp148->unk19][1],
                                                  D_hd_code_802F47B0[sp148->unk19][2],
                                                  D_8036BB20 * D_hd_code_802F47B0[sp148->unk19 ][ 3] * func_hd_code_8026F644(sp14C, sp148, (sp148->unk4 - sp134) + D_8036BB30) / 65025,
                                                  D_hd_code_802F47B0[sp148->unk19][4],
                                                  D_hd_code_802F47B0[sp148->unk19][5],
                                                  D_hd_code_802F47B0[sp148->unk19][6],
                                                  D_8036BB20 * D_hd_code_802F47B0[sp148->unk19 ][ 7] * func_hd_code_8026F644(sp14C, sp148, (sp148->unk4 - sp134) + D_8036BB30 + sp148->unk8) / 65025);
                        }
                    } else if (!(sp148->unk0 & 4) || ((u32) ((u32) (((u32) D_hd_code_803156C4 % 23U) * 0x3C) / 60U) < 0x10U)) {
                        func_hd_code_80259DC8(arg1, sp144, sp140, sp148->unk0 & 8, 0, sp148->unk2 - sp136, (sp148->unk0 & 0x1000 ? D_8036BB30 : 0) + (sp148->unk4 - sp134), (s32) sp148->unk6, (s32) sp148->unk8, 1,
                                              D_hd_code_802F47B0[sp148->unk18  ][ 0],
                                              D_hd_code_802F47B0[sp148->unk18  ][ 1],
                                              D_hd_code_802F47B0[sp148->unk18  ][ 2],
                                              D_8036BB20 * D_hd_code_802F47B0[sp148->unk18 ][ 3] * func_hd_code_8026F644(sp14C, sp148, (sp148->unk4 - sp134) + D_8036BB30) / 65025,
                                              D_hd_code_802F47B0[sp148->unk18  ][ 4],
                                              D_hd_code_802F47B0[sp148->unk18  ][ 5],
                                              D_hd_code_802F47B0[sp148->unk18  ][ 6],
                                              D_8036BB20 * D_hd_code_802F47B0[sp148->unk18 ][ 7] * func_hd_code_8026F644(sp14C, sp148, (sp148->unk4 - sp134) + D_8036BB30 + sp148->unk8) / 65025);
                    }
                }
        }

        func_hd_code_80259BD4((Gfx** ) &entry, arg1);
    }
    return (Gfx* ) entry;
}

// @internal
void func_hd_code_8026EF70(struct S_802F8BDC* arg0) {
  if (arg0->unk8 & 0x80) {
    D_8036BB04 = func_hd_code_8026F8A8(arg0->unkE, arg0->unk10, arg0->unkE - 1, 0x100);
    D_8036BB06 = 0;
    if ((D_8036BB04 + 1) == arg0->unkE) {
      D_8036BB1E = 0;
      return;
    }
    D_8036BB1E = 1;
    return;
  }
  D_8036BB1E = 0;
}

// @internal
u8* func_hd_code_8026F004(struct S_802F8BDC* arg0, u16 arg1, s32 arg2) {
    struct S_8020C070* sp3C;
    u8 sp3B;
    u8* sp34;
    u16* sp30;
    u16 sp2E;
    s32 sp28;
    u16 sp26;

    sp3C = &D_8036BB10[arg1];
    if ((u8) arg2 != 0) {
        sp3B = 1;
    } else {
        sp3B = 0;
    }
    sp34 = sp3C->unkC;
    sp30 = sp3C->unk10;
    D_8036BB48[0] = D_hd_code_802E8C98[sp3B];

    switch (D_8036BB1E) {                           /* irregular */
    case 0:
        if ((u8) arg2 != 0) {
            return sp30;
        }
        return sp34;
    case 1:
        if (D_hd_code_8036BB1C == 2) {
            D_8036BB1E = 2;
            D_8036BB00 = D_hd_code_803156C4;
        }
        break;

    case 2:
        if ((s32) arg1 < (s32) D_8036BB04) {
            if ((u8) arg2 != 0) {
                return sp30;
            }
            return sp34;
        }
        if (arg1 <= D_8036BB04) {
            if ((u32) (D_hd_code_803156C4 - D_8036BB00) >= 5U) {
                D_8036BB00 = D_hd_code_803156C4;
                D_8036BB06++;
                if ((u8) arg2 != 0) {
                    sp2E = sp30[D_8036BB06];
                } else {
                    sp2E = sp34[D_8036BB06];
                }
                if ((u16) D_hd_code_802E8C90[sp3B] == sp2E) {
                    sndPlaySfx(D_hd_code_80367738, 0x91, NULL);
                } else if ((D_hd_code_802E8C94[sp3B] != sp2E) && (D_hd_code_802E8C98[sp3B] != sp2E) && ((u16) D_hd_code_802E8C8C[sp3B] != sp2E)) {
                    sndPlaySfx(D_hd_code_80367738, 0x22, NULL);
                }
            }
            if ((u8) arg2 != 0) {
                if (sp30 == 0) {
                    rmonPrintf("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "jtext", "./vidiPrint.h", 0x46);
                }
            } else {
                if (sp34 == 0) {
                    rmonPrintf("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "text", "./vidiPrint.h", 0x46);
                }
            }
            sp28 = 0;
            if ((u8) arg2 != 0) {
                while (sp30[sp28] != D_hd_code_802E8C98[sp3B]) {
                    D_8036BB48[sp28] = sp30[sp28];
                    sp28++;
                }
            } else {
                while (sp34[sp28] != D_hd_code_802E8C98[sp3B]) {
                    D_8036BB48[sp28] = sp34[sp28];
                    sp28++;
                }
            }
            D_8036BB48[sp28] = D_hd_code_802E8C98[sp3B];
            if (D_8036BB48[D_8036BB06] == D_hd_code_802E8C98[sp3B]) {
                sp26 = func_hd_code_8026F8A8(arg0->unkE, arg0->unk10, D_8036BB04, 0x100);
                if (sp26 == D_8036BB04) {
                    D_8036BB1E = 0;
                    if ((arg0->unk8 & 0x400000) && (D_hd_code_8036BB1C == 2)) {
                        D_8036BAFC = D_hd_code_803156C4;
                    }
                } else {
                    sndPlaySfx(D_hd_code_80367738, 0x23, NULL);
                    D_8036BB04 = sp26;
                }
                D_8036BB06 = 0;
            } else {
                (D_8036BB48)[D_8036BB06] = D_hd_code_802E8C98[sp3B];
                if (!(sp3C->unk0 & 0x4000) && ((u32) ((u32) D_hd_code_803156C4 % 10U) >= 6U)) {
                    D_8036BB48[D_8036BB06] = D_hd_code_802E8C9C[sp3B];
                    D_8036BB48[D_8036BB06+1] = D_hd_code_802E8C98[sp3B];
                }
            }
            if ((u8) arg2 != 0) {
                return D_8036BB48;
            }
            return func_hd_code_8025B558(D_8036BB48);
        }
        break;
    }
    if ((sp3C->unk0 & 0x100) || (sp3C->unk0 & 0x200)) {
        if ((u8) arg2 != 0) {
            return (s32) &D_8036BB48;
        }
        return func_hd_code_8025B558(D_8036BB48);
    }
    if ((u8) arg2 != 0) {
        return sp30;
    }
    return sp34;

}

// @internal
u8 func_hd_code_8026F644(struct S_802F8BDC* arg0, struct S_8020C070* arg1, s16 arg2) {
  if (arg1->unk0 & 0x1000) {
    return MAX(0x00, MIN(0xFF, 0x200 - (((ABS(arg2)) << 9) / (arg0->unk2 / 3))));
  }
  return 0xFF;
}

// @internal
u16 func_hd_code_8026F82C(u16 arg0, u16 arg1, u16 arg2) {
  s32 sp4;

  for(sp4 = arg1 - 1; sp4 >= arg0; sp4--) {
    if (D_8036BB10[sp4].unk0 & (arg2)) {
      return sp4;
    }
  }
  return arg1;
}

// @internal
u16 func_hd_code_8026F8A8(u16 arg0, u16 arg1, u16 arg2, u16 arg3) {
  s32 sp4;

  for(sp4 = arg2 + 1; sp4 < arg0 + arg1; sp4++) {
    if (D_8036BB10[sp4].unk0 & (arg3)) {
      return sp4;
    }
  }
  return arg2;
}

s32 func_hd_code_8026F92C(u64 arg) {
  s64 sp1C;

  if ((arg == 0)) {
    rmonPrintf("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "in", "yoshi.c", 0x8DE);
  }
  if ((arg == 0)) {
    return -1;
  }

  for(sp1C = 0; !((1LL << sp1C) & arg); sp1C++) {

  }

  return sp1C;
}

u8 func_hd_code_8026FA38(char** arg0, s32* arg1) {
  s32 sp1C;
  s32 sp18;

  sp18 = 0;
  rmonPrintf("path builing=%d\n", D_803F7684);
  sp1C = 0;
  if (sp18 == 0) {
    loop_1:
            if (D_hd_code_802F9934[sp1C].unk0 == D_803F7684) {
              sp18 = sp1C + 0x1A;
            }
    sp1C++;
    if ((sp1C < 7) && (sp18 == 0)) {
      goto loop_1;
    }
  }
  if (sp18 == 0) {
    sp18 = 0x1A;
    sp1C = 1;
  }
  if (arg0 != NULL) {
    *arg0 = D_hd_code_802F9934[sp1C-1].unk1;
  }
  if (arg1 != NULL) {
    *arg1 = D_hd_code_802F9934[sp1C-1].unk10;
  }
  return sp18;
}

// @internal
void func_hd_code_8026FB50(struct S_802F8BDC* arg0) {
  if (arg0->unk8 & 0x8000) {
    D_8036BB10 = D_hd_code_8036BB24;
    return;
  }
  if (arg0->unk8 & 0x800) {
    D_8036BB10 = &D_8020C070[0];
    return;
  }
  D_8036BB10 = &D_hd_code_802F5804[0];
}

