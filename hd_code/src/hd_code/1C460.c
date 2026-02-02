#include "common.h"
#include "functions.h"
#include "gu/guint.h"
#include "snd.h"
#include "structs.h"
#include "variables.h"

s32 func_hd_code_802D8260(ALSeqPlayer*);            /* extern */
void func_hd_code_802D76C0(ALSeqPlayer*);        /* extern */
void func_hd_code_802D7C4C(void*, void*);              /* extern */
void func_hd_code_802D81B0(ALSeqPlayer*, void*); /* extern */
void func_hd_code_802D81F0(ALSeqPlayer*);        /* extern */
void func_hd_code_802D8220(ALSeqPlayer*, s32);   /* extern */
void func_hd_code_802D76F0(void*, u32*);                 /* extern */
void func_hd_code_802676A0(s32*, u8);                   /* extern */
void func_hd_code_80267A74();                          /* extern */
void func_hd_code_802D8320(ALHeap*, void*, u32);            /* extern */
void func_hd_code_802D9670(ALSeqPlayer*, s32*);  /* extern */
void func_hd_code_802D97E0(ALSeqPlayer*, ALBank*); /* extern */
void sndNewPlayerInit(ALSeqpSfxConfig *sfxSeqpConfig);
void func_hd_code_80260A30(s32);                         /* extern */
s32 func_hd_code_80264BA4(s32);                     /* extern */
void sndDeactivateAllSfxByFlag_11();                   /* extern */
void sndDeactivateAllSfxByFlag_3();                    /* extern */
void func_hd_code_80260C20(u8, f32);                   /* extern */
void func_hd_code_802D7790(struct S_80367518*, u8*);   /* extern */
void func_hd_code_802D82A0(ALSeqPlayer*, s32);   /* extern */
s32 func_hd_code_802D8310(ALSeqPlayer*);            /* extern */
extern s32 D_8036772C;

extern s32 D_8036772C;
extern u8 D_hd_code_802E8E04[];
extern u8 D_350950;
extern u8 D_3539A0;
extern u8 D_3A1920;
extern u8 D_3A48C0;
extern u8 D_44F5C0;
extern f32 D_80367710;
extern ALHeap D_80367718;
extern s32 D_8036771C;
extern s32 D_80367720;
extern ALBank* D_8036773C;
extern void* D_80370C80;
extern s32 D_80367408[];
extern ALBank* D_80367738;
extern s32 D_80367408[];
extern void* D_80367510;
extern ALSeqFile *D_80367514;
extern u8 D_hd_code_802E8DC8[];
extern u8 D_hd_code_802E8E40[];

struct S_80367518 {
  u8 unk0[0xF8];
};

struct S_802E8EB4 {
  u32 unk0[0x18 / 4];
};
extern struct S_802E8EB4 D_hd_code_802E8EB4[];

extern struct S_80367518 D_80367518[];
struct S_80367400 {
  u32 unk0[0x1EC / 4];
  /* 0x1EC */ s32 unk1EC;
  /* 0x1F0 */ u8  unk1F0;
  u8 pad[3];
};
extern u8 D_hd_code_802E8D8C[];
extern u8 D_80367708;
extern f32 D_8036770C;
extern u8 D_8036772A;
extern s16 D_hd_code_802E8D00[];
extern u16 D_hd_code_802E8E7C[];
extern u8 D_hd_code_802E8D84;
extern f32 D_hd_code_802E8D88;
extern struct S_80367400* D_80367400;
extern u8 D_80367708;
extern u8 D_80367728;
extern u8 D_80367729;
extern s8 D_80367730;
extern struct S_80367400 D_80366C30;
extern struct S_80367400 *D_80367400;
extern u8 D_80367708;
extern f32 D_80367714;
extern s8 D_80367730;

void func_hd_code_80260C20(u8 arg0, f32 arg1) {
  void* sp24;

  D_hd_code_802E8D84 ^= 1;
  func_hd_code_802D76C0(D_80367734);

  D_8036772A = 0;
  D_8036770C = arg1;
  D_80367708 = arg0;
  sp24 = D_80367514->seqArray[arg0].offset;


  InitiateDma(sp24, D_80367510, &D_80367408[arg0], 0U, 0, 0);
  func_hd_code_802D7C4C(&D_80367518[D_hd_code_802E8D84], D_80367510);
  func_hd_code_802D81B0(D_80367734, &D_80367518[D_hd_code_802E8D84]);
  func_hd_code_802D81F0(D_80367734);
  func_hd_code_802D8220(D_80367734, D_hd_code_802E8D00[D_80367708] * D_8036770C * D_hd_code_802E8D88);
}

void func_hd_code_80260D7C(f32 arg0) {
  D_hd_code_802E8D88 = arg0;
  func_hd_code_802D8220((struct ALSeqPlayer* ) D_80367734, (s32) ((f32) D_hd_code_802E8D00[D_80367708] * D_8036770C * arg0));
}

f32 func_hd_code_80260DF0(void) {
  return D_hd_code_802E8D88;
}

void func_hd_code_80260DFC(void) {
  func_hd_code_80260EE0(D_hd_code_802E8DC8[levelno]);
}

void func_hd_code_80260E2C(void) {
  D_80367740 = (s32) D_803156C4;
  D_8036772C = func_hd_code_802D8260(D_80367734);
  func_hd_code_80261FB0(D_hd_code_802E8E04[levelno]);
}

void func_hd_code_80260E80(void) {
  D_80367740 = (s32) D_803156C4;
  func_hd_code_80261FB0(D_hd_code_802E8E40[levelno]);
}

void func_hd_code_80260EC0(void) {
  func_hd_code_80260DFC();
}

void func_hd_code_80260EE0(u8 arg0) {
  if (D_80367728 != 0) {
    func_hd_code_8029A7E4("OH DEAR - pushing tune but we're still popping!\n");
    return;
  }
  func_hd_code_8029A7E4("push tune %d\n", (u8) arg0);
  D_80367400->unk1F0 = D_80367708;
  D_80367708 = arg0;
  D_80367730 = 0;
  D_80367729 = 1;
}

void func_hd_code_80260F60(f32 arg0) {
  func_hd_code_8029A7E4("1 pop tune");
  if (&D_80366C30 == D_80367400) {
    return;
  }

  D_80367400 = D_80367400 - 1;
  if (&D_80366C30 == D_80367400) {
    D_80367730 = 1;
  }
  func_hd_code_8029A7E4("2 pop tune %d\n", D_80367400->unk1F0);
  D_80367708 = D_80367400->unk1F0;
  func_hd_code_802D76C0(D_80367734);
  D_80367728 = 2;
  D_80367714 = arg0;
}

void func_hd_code_8026101C(void) {
  func_hd_code_80260F60(0);
}

void func_hd_code_80261040(void) {
  func_hd_code_80260F60(1.0f);
}

void func_hd_code_80261068(void) {
  u32 sp114;
  u8 pad30[0x114-0x30];
  u32 sp2C;
  u32 sp28;

  switch(D_80367728) {
    case 2:
      if (func_hd_code_802D4E10(D_80367734) == 0) {
        func_hd_code_80260C20(D_80367708, D_80367714);
        D_80367728 = 1;
      }
      break;

    case 1:
      func_hd_code_802D76F0(&D_80367518[D_hd_code_802E8D84], &sp28);
      if ((func_hd_code_802D4E10(D_80367734) == 1) && (sp2C != 0)) {
        func_hd_code_802D7790(&D_80367518[D_hd_code_802E8D84], &D_80367400->unk0[0x40]);
        func_hd_code_802D82A0(D_80367734, D_80367400->unk1EC);
        // Reads 4 channels 4 * 0x10
        for(sp114 = 0; sp114 < 0x40U; sp114++) {
          // Raw data transfer
          *(((u32*)D_80367734->chanState) + sp114) = D_80367400->unk0[sp114];
        }
        D_80367728 = 0;
        if ((f64) D_80367714 != 1.0) {
          func_hd_code_80261570(1.0f);
        }
      }
      break;

  }
}

void func_hd_code_802611F0(void) {
  u8 pad[0x3B * 4 - 0x8];
  u32 sp20;
  u32 sp1C;

  func_hd_code_802D76F0(&D_80367518[D_hd_code_802E8D84], &sp1C);
  if ((D_80367729 == 0) && (D_80367728 == 0) && (func_hd_code_802D4E10(D_80367734) == 0) && (sp20 != 0)) {
    func_hd_code_8029A7E4("auto popping\n");
    func_hd_code_8026101C();
  }
}

void func_hd_code_80261284(void) {
  u32 sp24;

  switch (D_80367729) {                           /* irregular */
    case 1:
      if (func_hd_code_802D4E10((struct ALSeqPlayer* ) D_80367734) == 1) {
        func_hd_code_802D76F0(&D_80367518[D_hd_code_802E8D84], &D_80367400->unk0[0x40]);
        D_80367400->unk1EC = func_hd_code_802D8260(D_80367734);
        for(sp24 = 0; sp24 < 0x40U; sp24++) {
          D_80367400->unk0[sp24] = *(((u32*)D_80367734->chanState)+sp24);

        }
        func_hd_code_802D76C0((struct ALSeqPlayer* ) D_80367734);
        D_80367400++;
        D_80367729 = 2;
        return;
      }
      return;
    case 2:
      if (func_hd_code_802D4E10((struct ALSeqPlayer* ) D_80367734) == 0) {
        func_hd_code_80260C20(D_80367708, 1.0f);
        D_80367729 = 0;
      }
      break;
  }
}

void func_hd_code_802613C8(void) {
  f32 sp2C;
  f32 sp28;
  s16 sp26;

  sp2C = func_hd_code_802D8310(D_80367734);
  sp28 = D_hd_code_802E8D00[D_80367708] * D_hd_code_802E8D88;
  sp26 = sp2C + (sp28 * D_8036770C - sp2C) * 0.075;
  if ((ABS(sp26 - sp28 * D_8036770C)) < 10.0f) {
    sp26 = sp28 * D_8036770C;
    D_8036772A = 0;
  }
  func_hd_code_802D8220((struct ALSeqPlayer* ) D_80367734, (s32) sp26);
}

void func_hd_code_80261528(void) {
  if (D_80367734->state == 1) {
    func_hd_code_802D82A0(D_80367734, D_8036772C);
    D_8036772C = 0;
  }
}

void func_hd_code_80261570(f32 arg0) {
  D_8036770C = arg0;
  D_8036772A = 1;
}

void func_hd_code_80261588(void) {
    ALSeqpSfxConfig sp84;
    s32 sp80;
    s32 sp7C;
    s32 sp78;
    ALHeap* sp74;
    s8 pad73;
    s8 pad72;
    s8 pad71;
    s8 sp70;
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s8 pad63;
    s8 pad62;
    s8 pad61;
    s8 sp60;
    s32 sp5C;
    ALHeap* sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    ALBankFile* sp40;
    ALBankFile* sp3C;
    s32 sp38;
    s32 sp34;
    u32 sp30;
    s32 pad2C;
    s32 pad28;
    s32 sp24;
    s32 sp20;

    func_hd_code_802D8320(&D_80367718, &D_80370C80, 0x2A280);
    sp38 = sp34 = (s32)&D_3539A0 - (s32)&D_350950;
    InitiateDma(&D_350950, (void* )0x8004B400, &sp38, 0xDU, 0, 2);
    sp3C = alHeapAlloc(&D_80367718, 1, sp38);
    InitiateDma(&D_350950, sp3C, &sp34, 0xDU, 0, 2);
    alBnkfNew(sp3C, &D_3539A0);
    D_8036773C = sp3C->bankArray[0];
    sp38 = sp34 = (s32)&D_3A48C0 - (s32)&D_3A1920;

    InitiateDma(&D_3A1920, (void* )0x8004B400, &sp38, 0xDU, 0, 2);
    sp40 = alHeapAlloc(&D_80367718, 1, sp38);
    InitiateDma(&D_3A1920, sp40, &sp34, 0xDU, 0, 2);
    alBnkfNew(sp40, &D_3A48C0);
    D_80367738 = sp40->bankArray[0];
    D_80367514 = alHeapAlloc(&D_80367718, 1, 4);
    sp20 = 4;
    InitiateDma(&D_44F5C0, D_80367514, &sp20, 0U, 0, 0);
    sp24 = (D_80367514->seqCount * 8) + 4;
    D_80367514 = alHeapAlloc(&D_80367718, 1, 0x214);
    InitiateDma(&D_44F5C0, D_80367514, &sp24, 0U, 0, 0);
    alSeqFileNew(D_80367514, &D_44F5C0);
    D_80367510 = alHeapAlloc(&D_80367718, 1, 0x21AE);
    for(sp30 = 0; sp30 < 0x42U; sp30++) {
        D_80367408[sp30] = D_80367514->seqArray[sp30].len;
        if (D_80367408[sp30] & 1) {
            D_80367408[sp30]++;
        }
    }
    // TODO: find matching struct
    sp44 = 0;
    sp48 = 0x18;
    sp4C = 0x80;
    sp50 = 1;
    sp54 = 0;
    sp60 = 6;
    sp5C = 0;
    sp58 = &D_80367718;
    func_hd_code_802676A0(&sp44, 0xC);
    // TODO: find matching struct
    sp68 = 0x18;
    sp6C = 0x20;
    sp70 = 0x10;
    sp74 = &D_80367718;
    sp78 = 0;
    sp7C = 0;
    sp80 = 0;
    D_80367734 = alHeapAlloc(&D_80367718, 1, 0x7C);
    func_hd_code_802D9670(D_80367734, &sp68);
    func_hd_code_802D97E0(D_80367734, D_8036773C);
    sp84.maxEvents = 0x40;
    sp84.maybeSndStateCount = 0x20;
    sp84.maybeMaxSounds = 8;
    sp84.slotCount = 8;
    sp84.heap = &D_80367718;
    sndNewPlayerInit(&sp84);
    func_hd_code_8029A7E4("%d bytes audio heap left over\n", D_80367720 - ((s32)D_8036771C - (s32)D_80367718.base));
    D_8036772A = 0;
    D_80367728 = 0;
    D_80367710 = D_8036770C = 1.0f;
    D_80367730 = 1;
    D_80367400 = &D_80366C30;
    func_hd_code_80267A74();
}

void func_hd_code_802619D0(u32 effectId) {
  if (effectId >= 0x1CU) {
    func_hd_code_8029A7E4("effect id %d out of range!\n", effectId);
    return;
  }

  if (D_hd_code_802E8E7C[effectId] != 0) {
    sndPlaySfx(D_80367738, D_hd_code_802E8E7C[effectId], 0);
  }
}

u8 func_hd_code_80261A44(u64 arg0) {
    u8 sp27;
    u8 sp26;

    sp26 = 0;
    sp27 = D_80367708;
    if (arg0 != 4) {
        sndDeactivateAllSfxByFlag_3();
    }
    sndDeactivateAllSfxByFlag_11();
    func_hd_code_80261E9C(arg0);
    if ((D_hd_code_80364A90 & 0xC9FD8FE7FBFFC0B0)) {
        func_hd_code_80260A30(0);
        func_hd_code_80260A30(5);
    }
    D_80367710 = 1.0f;

    switch(arg0) {
        case 0x2:
            sp27 = 0x11;
            break;
        case 0x40:
            sp27 = 0xA;
            break;
        case 0x800:
        case 0x1000:
            sp27 = 3;
            break;
        case 0x10000:
            sp27 = 0x21;
            break;
        case 0x40000000000000:
        case 0x100000000:
        case 0x200000000:
        case 0x20000:
        case 0x40000:
            sp27 = 0x21;
            break;
        case 0x80000000:
            func_hd_code_80261570(0.0f);
            break;
        case 0x08000000:
            sp27 = 0xE;
            break;

        case 0x4000: // correct
        case 0x80: // correct
            if (func_hd_code_80264BA4(levelno) == 3) {
                sp27 = 0xC;
            } else {
                sp27 = 0x13;
            }
            break;
        case 0x40000000:
            sp27 = 0xF;
            break;
        case 0x2000:
            if (D_hd_code_802E8F94[levelno].unk0 != 1) {
                func_hd_code_80261570(0.0f);
                break;
            }
        case 0x4:
            sp27 = D_hd_code_802E8D8C[levelno];
            sp26 = 1;
            break;
        case 0x20000000:
            sp27 = 0x1D;
            break;
        case 0x100000000000:
            sp27 = D_hd_code_802E8D8C[levelno];
            sp26 = 1;
            if (levelno == 0x26) {
                D_80367710 = 0.7f;
            }
            break;
        case 0x4000000000000:
            func_hd_code_80261570(0.0f);
            break;

        case 0x10000000000000:
            sp27 = 0x28;
            break;

        case 0x4000000000000000:
            break;
        case 0x800000000000:
            func_hd_code_80261570(0.0f);
            break;
    }

    if ((sp27 != D_80367708) || (sp26 != 0)) {
        func_hd_code_80261570(0.0f);
        return sp27;
    }
    return 0U;
}

void func_hd_code_80261E9C(u64 arg0) {
  switch(arg0) {
    case 0x2:
      sndSetSfxSlotVolume(0, 0x5DC0);
      sndSetSfxSlotVolume(5, 0x5DC0);
      break;
    case 0x20000000:
      sndSetSfxSlotVolume(0, 0x61A8);
      break;
    case 0x40:
      sndSetSfxSlotVolume(0, 0x4E20);
      sndSetSfxSlotVolume(5, 0x4E20);
      break;
    case 0x800:
    case 0x1000:
      sndSetSfxSlotVolume(0, 0x6D60);
      sndSetSfxSlotVolume(5, 0x6D60);
      break;
    default:
      sndSetSfxSlotVolume(0, 0x7FFF);
      sndSetSfxSlotVolume(5, 0x7FFF);
      break;
  }
}

void func_hd_code_80261FB0(u8 arg0) {
  D_80367728 = 0;
  D_80367729 = 0;
  D_80367400 = &D_80366C30;
  D_80367730 = 1;
  func_hd_code_80260C20(arg0, D_80367710);
}

void func_hd_code_80262008(u8 arg0, f32 arg1) {
  D_80367400 = &D_80366C30;
  D_80367730 = 1;
  func_hd_code_80260C20(arg0, arg1);
}

u8 func_hd_code_80262050()
{
  return D_80367708;
}

s32 func_hd_code_8026205C(s32 arg0) {
  u32 sp2C;
  s32 sp28;

  for(sp2C = 0, sp28 = 0;sp28 < 5 && D_hd_code_802E8EB4[arg0].unk0[sp28] != -1; sp28++, sp2C++);

  return D_hd_code_802E8EB4[arg0].unk0[osGetCount() % sp2C];
}
