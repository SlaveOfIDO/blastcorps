#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/hd.h"
#include "../hd_code/yoshi.h"
#include "../hd_code/functions.h"
#include "../hd_code/variables.h"
#include "../hd_code/io/controller.h"
#include "structs.h"

s32 func_hd_front_end_8020480C(void*, s32, s32, s32, s32, u64*); /* extern */
void func_hd_front_end_80204C10(void*, s32, u64*);          /* extern */
void func_hd_front_end_801F58E8();              /* extern */
void func_hd_front_end_801F74B0(u8*);                /* extern */
s32 func_hd_code_8028FCD4(OSMesgQueue*, u8*);       /* extern */
s32 func_hd_code_8028FCD4(OSMesgQueue*, u8*);       /* extern */
void func_hd_front_end_801EE390(void);              /* extern */
void func_hd_front_end_801EE398(s32);               /* extern */
s32 func_hd_front_end_801F5FE4(void);               /* extern */
s32 func_hd_front_end_801F60C8(void);               /* extern */
s32 func_hd_front_end_801F6160(u8);                 /* extern */
s32 func_hd_front_end_801F61C8(u8);                 /* extern */
s32 func_hd_front_end_801F6210(u8);                 /* extern */
s32 func_hd_front_end_801F6264(u8, u8);             /* extern */
s32 func_hd_front_end_801F76E4(u8*, s32);  /* extern */
s32 func_hd_front_end_801F65C4(u8, u8, u8);         /* extern */
s32 func_hd_front_end_801F67E4(u8, u8, s32);         /* extern */
s32 func_hd_front_end_801F6AF4(u8, u64);                 /* extern */
s32 func_hd_front_end_801F6CA4(u8, u8, u8);         /* extern */
s32 func_hd_front_end_801F6ED4(u8);                 /* extern */
s32 func_hd_front_end_801F6BD0(u8, u64*);           /* extern */
s32 func_hd_front_end_801F75A4(u8*, s32); /* extern */
void func_hd_front_end_801F7410(u8*);

extern u8 D_hd_code_80365060[];
extern struct S_8020C070* D_hd_code_8036BB24; // 21 elements
extern u8 D_hd_front_end_8020C01C[];
extern u16 D_80301080[];
extern u8 D_hd_front_end_8020C488[];
extern u16 D_hd_code_80364F70[];
extern s32 D_hd_code_802FA264;
extern OSMesg D_hd_code_8039C4B4;
extern s16 D_hd_code_8036BB18;
extern s32 D_hd_code_8036BF10;
extern OSMesgQueue D_hd_code_80370BF8;
extern s32 D_hd_code_8039B620;
extern s8 D_hd_front_end_8020F19C;
extern s8 D_hd_front_end_8020F1C8;
extern s8 D_hd_front_end_8020F1D0;
extern OSThread g_Thread3;
extern u8 D_hd_front_end_8020C000[]; // "BLASTCORPS GAME"
extern u8 D_hd_front_end_8020C014[];
extern u8 D_hd_front_end_8020F128;
extern u8 D_hd_front_end_8020F140;
extern OSPfs D_hd_code_8039B630;
extern s32 D_hd_code_8039B698[]; // Line no
extern s32 D_hd_code_802FA264;
extern u16 D_hd_code_80364EF0[][16];
extern u8 D_hd_front_end_8020C01C[];

// <bss>
u8 D_hd_front_end_80218740[16][0x28];
u8 D_hd_front_end_802189C0[16][0x11];
u8 D_hd_front_end_80218AD0[16][0x5];
OSPfsState D_hd_front_end_80218B20[16];
s32 D_hd_front_end_80218B20_pad;
s32 D_hd_front_end_80218D24;
s32 D_hd_front_end_80218D28;
s32 D_hd_front_end_80218D28_pad;
OSThread D_hd_front_end_80218D30;
OSScClient D_hd_front_end_80218EE0;
s32 D_hd_front_end_80218EF0;
s32 D_hd_front_end_80218EF0_pad;
u8 D_hd_front_end_80218EF8[0x1000];
OSMesgQueue D_hd_front_end_80219EF8;
void* D_hd_front_end_80219F10[8];
OSMesgQueue D_hd_front_end_80219F30;
void* D_hd_front_end_80219F48;
s32 D_hd_front_end_80219F48_pad;
OSMesgQueue D_hd_front_end_80219F50;
void* D_hd_front_end_80219F68[8];
s32 D_hd_front_end_80219F88;
s32 D_hd_front_end_80219F88_pad;
u8 D_hd_front_end_80219F90[0x20];
u8 D_hd_front_end_80219FB0[0x20];
// </bss>

// <data>
u8 D_hd_front_end_8020BEE0[256] = {
  'P', 'L', 'A', 'Y', 'E', 'R', '1', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x06, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x11, 0x44, 0x33, 0x66, 0x55, 0x88, 0x77,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
u8 pad_8020BFE0[32] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
u8 D_hd_front_end_8020C000[0x14] = "BLASTCORPS GAME";
u8 D_hd_front_end_8020C014[8] = "";
u8 D_hd_front_end_8020C01C[69] = {
  0x00, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x20,
  0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46,
  0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56,
  0x57, 0x58, 0x59, 0x5A, 0x21, 0x61, 0x62, 0x27, 0x64, 0x65, 0x2C, 0x2D, 0x2E, 0x2F, 0x3A, 0x6B,
  0x3F, 0x6D, 0x2D, 0x2D, 0x2D
};
// </data>

void func_hd_front_end_801F57B0(void) {
  s32 sp24 = 0xDE0;
  osCreateThread(&D_hd_front_end_80218D30, 2, func_hd_front_end_801F58E8, NULL, &D_hd_front_end_80218EF8[0x1000], 0xB);
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

void func_hd_front_end_801F58E8() {
    u32 sp3C;
    s32 sp38;
    s32 sp34;
    u8 pad33;
    u8 sp32;
    u8 sp31;
    u8 sp30;
    u8 sp2F;
    u8 sp2E;
    u8 sp2D;
    u8 pad2C;
    s32 sp28;
    u32 sp24;

    while(1) {
        D_hd_code_8039C4B0 = 0;
        sp24 = 0;
        osSetEventMesg(OS_EVENT_SI, &D_hd_code_80370BF8, NULL);
        osRecvMesg(&D_hd_front_end_80219EF8, (OSMesg*)&sp3C, 1);
        osSetEventMesg(OS_EVENT_SI, &D_hd_code_80370BF8, NULL);
        while (D_hd_code_8036BF10 != 0) {
        }

        sp2F = (sp3C >> 0) & 0xFF;
        sp31 = (sp3C >> 8) & 0xFF;
        sp32 = (sp3C >> 0x10) & 0xFF;
        sp30 = (sp3C >> 0x18) & 0xFF;
        D_hd_front_end_8020C014[0] = sp32 + 0x11;
        D_hd_code_8039C4B0 = 1;
        func_hd_code_8028A42C();
        func_hd_front_end_801EE390();
        D_hd_front_end_80218D24 = 0;
        do {
            sp2D = 0;
            sp2E = 0;
            sp28 = 0x5B;
            sp34 = 0;
            switch (sp2F) {                             /* switch 1 */
            case 1:                                     /* switch 1 */
            case 2:                                     /* switch 1 */
                sp38 = func_hd_front_end_801F60C8();
                break;
            case 3:                                     /* switch 1 */
                sp38 = func_hd_front_end_801F6160(sp32);
                break;
            case 4:                                     /* switch 1 */
                sp38 = func_hd_front_end_801F61C8(sp32);
                break;
            case 5:                                     /* switch 1 */
                sp38 = func_hd_front_end_801F6210(sp32);
                break;
            case 6:                                     /* switch 1 */
                sp38 = func_hd_front_end_801F6264(sp32, 0);
                break;
            case 7:                                     /* switch 1 */
                sp38 = func_hd_front_end_801F6264(sp32, 1);
                break;
            case 8:                                     /* switch 1 */
                sp38 = func_hd_front_end_801F65C4(sp32, sp31, 0);
                break;
            case 9:                                     /* switch 1 */
                sp38 = func_hd_front_end_801F65C4(sp32, sp31, 1);
                break;
            case 10:                                    /* switch 1 */
                sp38 = func_hd_front_end_801F67E4(sp32, sp31, 0);
                break;
            case 11:                                    /* switch 1 */
                sp38 = func_hd_front_end_801F67E4(sp32, sp31, 1);
                break;
            case 12:                                    /* switch 1 */
                sp38 = func_hd_front_end_801F6CA4(sp32, sp31, 0);
                break;
            case 13:                                    /* switch 1 */
                sp38 = func_hd_front_end_801F6CA4(sp32, sp31, 1);
                break;
            case 14:                                    /* switch 1 */
                sp38 = osPfsFreeBlocks(&D_hd_code_8039B630, &D_hd_front_end_80218EF0);
                break;
            case 15:                                    /* switch 1 */
                sp38 = func_hd_front_end_801F5FE4();
                break;
            case 16:                                    /* switch 1 */
                sp2D = 1;
                sp38 = osEepromProbe(&D_hd_code_80370BF8);
                break;
            case 17:                                    /* switch 1 */
                sp38 = func_hd_front_end_801F6ED4(sp32);
                break;
            case 18:                                    /* switch 1 */
                sp38 = osPfsChecker(&D_hd_code_8039B630);
                break;
            case 19:                                    /* switch 1 */
                sp38 = 0xA;
                break;
            case 20:                                    /* switch 1 */
                sp38 = func_hd_front_end_801F6AF4(sp32, 0x2704197125121981);
                break;
            case 21:                                    /* switch 1 */
                sp38 = func_hd_front_end_801F6AF4(sp32, 0x87569ab6cd076aec);
                break;
            case 22:                                    /* switch 1 */
                sp38 = 0;
                break;
            default:                                    /* switch 1 */
                rmonPrintf("Nonsense pak message\n");
                break;
            }
            rmonPrintf("pak command %d returned %d\n", sp2F, sp38);
            switch (sp38) {
            case 0x6E382:
                if (D_hd_code_80364A90 & 0x10E18000 || (D_hd_code_80364A98 & 0x20000000000000)) {
                    sp2D = 1;
                    break;
                }
            case 0x6:
            case 0xA:
            case 0xB:
                if (sp24 >= 4U) {
                    if (sp2F != 0x13) {
                        if (sp38 == 0x6E382) {
                            D_hd_front_end_80219F88 = 0x5D;
                        } else {
                            D_hd_front_end_80219F88 = 0x5C;
                        }
                        func_hd_front_end_801F6AF4(sp32, 0x2704197125121981);
                        sp2E = 0x13;
                    }
                    sp28 = D_hd_front_end_80219F88;
                } else {
                    sp28 = 0;
                    sp24 += 1;
                }
                break;
            case 0x0:                                   /* switch 2 */
            case 0x5:                                   /* switch 2 */
            case 0x9:                                   /* switch 2 */
                sp2D = 1;
                break;
            case 0x8:                                   /* switch 2 */
                if (!((D_hd_code_80364A90 & 0x10E18000)) || (func_hd_front_end_801F5FE4() != 0)) {
                    break;
                }
            case 0x7:                               /* switch 2 */
                D_hd_code_8039C4F8.unk40 = MIN(sp32, D_hd_code_8039C4F8.unk40);
                sp2D = 1;
                break;
            case 0x3:                                   /* switch 2 */
                if (sp24 >= 4U) {
                    if (sp2F != 0x13) {
                        func_hd_front_end_801F6AF4(sp32, 0x2704197125121981);
                        sp2E = 0x13;
                    }
                    sp28 = 0x5C;
                } else {
                    rmonPrintf("trying to fix pak ...\n");
                    if (sp2F != 0x12) {
                        osSendMesg(&D_hd_front_end_80219EF8, (void* ) (sp2F | (sp31 << 8) | (sp32 << 0x10) | (sp30 << 0x18)), 0);
                    }
                    sp2E = 0x12;
                    sp30 = 0;
                    sp24 += 1;
                }
                break;
            case 0x2:                                   /* switch 2 */
                if ((sp34 == 8) && !(D_hd_code_80364A90 & 0x10E18000)) {
                    rmonPrintf(ASSERT_MESSAGE, "1==0", "pfsHandler.c", 0x156);
                    sp2D = 1;
                }
                break;
            case 0x1:
                if ((D_hd_code_80364A98 & 0x20000000000000) != 0) {
                    sp2D = 1;
                }
                break;
            case 0x4:
                if (sp2F && sp2F) {}
                // can't have break here
            }
            sp34 = sp38;
            if ((D_hd_code_8036BF10 == 0) && (sp28 != 0) && (sp2D == 0) && (sp2E == 0) && (&g_Thread3 == D_hd_front_end_80219F50.mtqueue)) {
                func_hd_front_end_801EE398(sp28);
                D_hd_front_end_80218D24 = 1;
            }
            if (sp2E) {
                sp2F = sp2E;
                sp2E = 0;
            }
            osRecvMesg(&D_hd_front_end_80219F30, NULL, 1);
        } while (!sp2D);

        if (D_hd_front_end_80218D24 != 0) {
            D_hd_code_8036BB1C = 1;
            D_hd_code_8036BB18 = -1;
        }
        if (sp30) {
            osSendMesg(&D_hd_front_end_80219F50, (OSMesg) sp38, 1);
        }

    }
}

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

s32 func_hd_front_end_801F6264(u8 arg0, u8 arg1) {
    s32 sp3C = 0;
    s32 pad38;
    u32 sp34;
    s32 pad30;
    s32 sp2C;
    UnknownData8024C414* sp28;
    u64 sp20;

    sp28 = &players[arg0];

    for (sp34 = 0; (sp34 < 0x100) && ((u8) arg1 == 1); sp34++) {
        rmonPrintf("0x%x, ", ((u8*) sp28)[sp34]);
    }
    rmonPrintf("\n");

    if (0)
    {
      rmonPrintf(ASSERT_MESSAGE, "sizeof(playerInfo)<=512", "pfsHandler.c", 0x123);
    }

    if (arg1 == 1) {
        func_hd_front_end_801F75A4(sp28, 0x100);
    }

    if ((D_hd_code_802E8BF8 != 0) || (D_hd_code_80364A90 == 0x0040000000000000)) {
        if ((D_hd_code_8039C4B4 == 0) || (D_hd_code_802FA264 != 0)) {
            for (sp34 = 0; sp34 < 0x100; sp34++) {
                if ((u8) arg1 == 1) {
                    ((u8*) D_hd_code_8039B698)[0x18 + sp34] = ((u8*) sp28)[sp34];
                    D_hd_front_end_8020BEE0[sp34] = ((u8*) sp28)[sp34];
                } else {
                    ((u8*) D_hd_code_8039B698)[0x18 + sp34] = D_hd_front_end_8020BEE0[sp34];
                    ((u8*) sp28)[sp34] = ((u8*) D_hd_code_8039B698)[0x18 + sp34];
                }
            }
        } else if ((u8) arg1 == 1) {
            osEepromLongWrite(&D_hd_code_80370BF8, 0U, (u8*) sp28, 0x100);
        } else {
            osEepromLongRead(&D_hd_code_80370BF8, 0U, (u8*) sp28, 0x100);
        }
    } else {
        sp2C = 0;
        do {
            sp3C = osPfsFindFile(&D_hd_code_8039B630, 0x3031U, 0x4E424345U, D_hd_front_end_8020C000, D_hd_front_end_8020C014, &D_hd_code_8039B698[arg0]);
            sp2C++;
        } while ((sp3C != 0) && (sp2C < 3));

        if (sp3C == 0) {
            sp2C = 0;
            do {
                sp3C = osPfsReadWriteFile(&D_hd_code_8039B630, D_hd_code_8039B698[arg0], arg1, 0, 0x100, (u8*) sp28);
                sp2C++;
            } while ((sp3C != 0) && (sp2C < 3));
        }
    }

    if ((sp3C == 0) && ((u8) arg1 == 0)) {
        sp3C = func_hd_front_end_801F76E4(sp28, 0x100);
    }

    if ((sp3C == 0) && ((u8) arg1 == 0) && ((func_hd_front_end_801F6BD0(arg0, &sp20), (sp20 != 0x87569AB6CD076AEC)))) {
        sp3C = 0x6E382;
    }

    return sp3C;
}

s32 func_hd_front_end_801F65C4(u8 arg0, u8 arg1, u8 arg2) {
  s32 sp34;
  s32 sp30;
  s32 pad2C;
  u32 sp28;
  u8* sp24;

  sp34 = 0;
  sp24 = (u8*)D_hd_code_80364EF0[arg0];
  sp28 = (arg1 << 5) + 0x100;

  if (arg2 == 1) {
    func_hd_front_end_801F75A4(sp24, 0x20);
  }

  if (D_hd_code_802E8BF8 != 0) {
    for (sp30 = sp28; sp30 < sp28 + 0x20; sp30++) {
      if ((u8) arg2 == 1) {
        ((u8*) D_hd_code_8039B698)[0x18 + sp30] = sp24[sp30 - sp28];
      } else {
        sp24[sp30 - sp28] = ((u8*) D_hd_code_8039B698)[0x18 + sp30];
      }
    }
  } else {
    sp34 = osPfsFindFile(&D_hd_code_8039B630, 0x3031U, 0x4E424345U, D_hd_front_end_8020C000, D_hd_front_end_8020C014, &D_hd_code_8039B698[arg0]);
    if (sp34 == 0) {
      sp34 = osPfsReadWriteFile(&D_hd_code_8039B630, D_hd_code_8039B698[arg0], (u8) arg2, (s32) sp28, 0x20, (u8*) sp24);
    }
    for (sp30 = 0; sp30 < 0xE; sp30++) {
      rmonPrintf("%d TIME %d = %d\n", (u8) arg2, sp30, D_hd_code_80364EF0[arg0][D_hd_code_802E8C44[sp30]]);
    }
  }

  if ((sp34 == 0) && (arg2 == 0)) {
    sp34 = func_hd_front_end_801F76E4((UnknownData8024C414*) sp24, 0x20);
  }

  return sp34;
}

s32 func_hd_front_end_801F67E4(u8 arg0, u8 arg1, s32 arg2) {
  s32 sp3C = 0;
  s32 sp38;
  u8 sp37;
  u16* sp30;

  sp37 = arg1 * 2;
  sp30 = &D_hd_code_80364F70[sp37 & ~3];

  if (D_hd_code_802E8BF8 != 0) {
    if (arg0 != D_hd_code_80364AEA) {
      rmonPrintf(ASSERT_MESSAGE, "pn==playerNumberAtStart", "pfsHandler.c", 0x25C);
    }
    if ((u8) arg2 == 1) {
      D_hd_code_80364F70[sp37] = D_hd_code_80364EF0[arg0][D_hd_code_802E8C44[players[arg0].unk92[arg1]]];
      D_hd_code_80364F70[sp37 + 1] = D_hd_code_80364F70[sp37] ^ 0x55AA;
      rmonPrintf("%d %d EEWRITE %x %x\n", arg1, D_hd_code_80364F70[sp37], (u32) ((sp37 * 2) + 0x100) >> 3, sp30);
      osEepromWrite(&D_hd_code_80370BF8, (u8) ((u32) ((sp37 * 2) + 0x100) >> 3), (u8*) sp30);
    } else {
      osEepromRead(&D_hd_code_80370BF8, (u8) ((u32) ((sp37 * 2) + 0x100) >> 3), (u8*) sp30);
      for (sp38 = 0; sp38 < 2; sp38++, arg1++) {
        if (((players[arg0].unk18[arg1] > 0) && (players[arg0].unk18[arg1] < 6)?1:0) != 0 &&
            (arg1 != 0x31) && (arg1 != 0x2F) && (arg1 != 0x26)) {
          D_hd_code_80364EF0[arg0][D_hd_code_802E8C44[players[arg0].unk92[arg1]]] = D_hd_code_80364F70[arg1 * 2];
          rmonPrintf("%d EETIMES: %d %d\n", arg1, D_hd_code_80364F70[arg1 * 2], D_hd_code_80364F70[arg1 * 2 + 1] ^ 0x55AA);
          if (D_hd_code_80364F70[arg1 * 2] != (D_hd_code_80364F70[arg1 * 2 + 1] ^ 0x55AA)) {
            sp3C = 0x6E382;
          }
            }
      }
    }
  }
  return sp3C;
}

s32 func_hd_front_end_801F6AF4(u8 arg0, u64 arg2) {
  s32 sp24;
  UnknownData8024C414* sp20;

  sp24 = 0;
  sp20 = &players[arg0];
  if ((D_hd_code_802E8BF8 != 0) || D_hd_code_80364A90 == 0x40000000000000) {
    osEepromWrite(&D_hd_code_80370BF8, 0x3F, (u8*)&arg2);
  } else {
    rmonPrintf("PUTTING SEMAPHORE %llu\n", arg2);
    sp24 = osPfsReadWriteFile(&D_hd_code_8039B630, D_hd_code_8039B698[arg0], 1, 0xDE0, 0x20, (u8*)&arg2);
  }
  return sp24;
}

s32 func_hd_front_end_801F6BD0(u8 arg0, u64* arg1) {
  s32 sp44 = 0;
  UnknownData8024C414* sp40 = &players[arg0];
  u64 sp20[4];

  if (D_hd_code_802E8BF8 != 0) {
    osEepromRead(&D_hd_code_80370BF8, 0x3FU, (u8* ) arg1);
  } else {
    sp44 = osPfsReadWriteFile(&D_hd_code_8039B630, D_hd_code_8039B698[arg0], 0U, 0xDE0, 0x20, &sp20);
    *arg1 = sp20[0];
    rmonPrintf("Getting SEMAPHORE %llu\n", *arg1);
  }
  return sp44;
}

s32 func_hd_front_end_801F6CA4(u8 arg0, u8 arg1, u8 arg2) {
  s32 sp34;
  s32 sp30;
  s32 sp2C;
  s32 sp28;
  s32 sp24;

  sp34 = 0;
  sp28 = 0;

  for (sp2C = 0; sp2C < arg1; sp2C++) {
    if ((D_hd_code_802E8F94[sp2C].unk0 == 1) && (sp2C != 0x31) && (sp2C != 0x2F) && (sp2C != 0x26)) {
      sp28++;
    }
  }

  sp24 = (sp28 << 6) + 0x880;

  if ((u8) arg2 == 1) {
    func_hd_front_end_801F75A4((UnknownData8024C414*) pakBuffer, 0x40);
  }

  if (D_hd_code_802E8BF8 != 0) {
    for (sp2C = sp24; sp2C < sp24 + 0x40; sp2C++) {
      if ((u8) arg2 == 1) {
        ((u8*) D_hd_code_8039B698)[0x18 + sp2C] = pakBuffer[sp2C - sp24];
      } else {
        pakBuffer[sp2C - sp24] = ((u8*) D_hd_code_8039B698)[0x18 + sp2C];
      }
    }
  } else {
    sp30 = osPfsFindFile(&D_hd_code_8039B630, 0x3031U, 0x4E424345U, D_hd_front_end_8020C000, D_hd_front_end_8020C014, &D_hd_code_8039B698[arg0]);
    sp34 = sp30;
    if (sp30 == 0) {
      sp34 = osPfsReadWriteFile(&D_hd_code_8039B630, D_hd_code_8039B698[arg0], (u8) arg2, sp24, 0x40, pakBuffer);
    }
  }

  if ((sp34 == 0) && ((u8) arg2 == 0)) {
    sp34 = func_hd_front_end_801F76E4((UnknownData8024C414*) pakBuffer, 0x40);
  }

  return sp34;
}

s32 func_hd_front_end_801F6ED4(u8 arg0) {
  return osPfsFileState(&D_hd_code_8039B630, (s32) arg0, &D_hd_front_end_80218B20[D_hd_front_end_80218D28]);
}

s32 func_hd_front_end_801F6F18(void) {
    s32 sp44;
    s32 pad40;
    s32 pad3C;
    OSMesg sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;

    D_hd_front_end_80218D28 = 0;

    for (sp44 = 0; sp44 < 0x10; sp44++) {
        do {
            osSendMesg(&D_hd_front_end_80219EF8, (void*) ((sp44 << 0x10) | 0x11 | 0x01000000), 1);
            osRecvMesg(&D_hd_front_end_80219F50, &sp38, 1);
            if (sp38 != NULL) {
                sp44 += 1;
            }
        } while ((sp38 != NULL) && (sp44 < 0x10));

        if (sp44 < 0x10) {
            bcopy(D_hd_front_end_80218B20[D_hd_front_end_80218D28].game_name, D_hd_front_end_802189C0[D_hd_front_end_80218D28], 0x11);
            bcopy(D_hd_front_end_80218B20[D_hd_front_end_80218D28].ext_name, D_hd_front_end_80218AD0[D_hd_front_end_80218D28], 5);
            D_hd_front_end_802189C0[D_hd_front_end_80218D28][0x10] = 0;
            D_hd_front_end_80218AD0[D_hd_front_end_80218D28][4] = 0;

            sp34 = (D_hd_front_end_80218B20[D_hd_front_end_80218D28].file_size >> 5) >> 3;
            sp30 = D_hd_front_end_80218AD0[D_hd_front_end_80218D28][0];

            func_hd_front_end_801F7410(D_hd_front_end_802189C0[D_hd_front_end_80218D28]);
            func_hd_front_end_801F7410(D_hd_front_end_80218AD0[D_hd_front_end_80218D28]);
            sprintf(D_hd_front_end_80218740[sp44], "%16s%c%-4s (%d)",
                D_hd_front_end_802189C0[D_hd_front_end_80218D28],
                (sp30 != 0 ? '.' : ' '),
                D_hd_front_end_80218AD0[D_hd_front_end_80218D28],
                sp34);
            rmonPrintf("%s\n", D_hd_front_end_80218740[sp44]);
            if (sp34 < 0x63) {
                sprintf(D_hd_front_end_80218740[sp44], "%s ", D_hd_front_end_80218740[sp44]);
            }
            if (sp34 < 9) {
                sprintf(D_hd_front_end_80218740[sp44], "%s ", D_hd_front_end_80218740[sp44]);
            }
            D_hd_front_end_8020C070[37 + D_hd_front_end_80218D28].unkC = D_hd_front_end_80218740[sp44];
            D_hd_front_end_80218D28 += 1;
        }
    }

    if (D_hd_front_end_80218D28 == 0) {
        sprintf(D_hd_front_end_80218740[0], "%s", "PAK EMPTY!");
        D_hd_front_end_8020C070[37].unkC = D_hd_front_end_80218740[0];
        sp2C = 1;
    } else {
        sp2C = 0;
    }

    D_hd_code_802F8BDC[0x12].unk18 = ((s32) (D_hd_front_end_80218D28 + sp2C + 1) / 2) + 0x24;
    D_hd_code_802F8BDC[0x12].unk10 = D_hd_front_end_80218D28 + sp2C + 4;
    osSendMesg(&D_hd_front_end_80219EF8, (void*) 0x0100000E, 1);
    osRecvMesg(&D_hd_front_end_80219F50, NULL, 1);
    sprintf(D_hd_front_end_80219F90, "%d PAGES FREE", (D_hd_front_end_80218EF0 / 32) / 8);
    D_hd_front_end_8020C070[35].unkC = D_hd_front_end_80219F90;
    sprintf(D_hd_front_end_80219FB0, "%d NEEDED PER PLAYER", 0xE);
    D_hd_front_end_8020C070[36].unkC = D_hd_front_end_80219FB0;
    D_hd_front_end_8020C070[10].unkC = "DELETE THIS FILE?";
    D_hd_front_end_8020C070[10].unk10 = D_80301080;
    return D_hd_front_end_80218D28 != 0;
}

s32 func_hd_front_end_801F73FC(void) {
  return D_hd_front_end_80218D28 != 0;
}

void func_hd_front_end_801F7410(u8* arg0) {
  s32 sp1C;

  for (sp1C = 0; sp1C < func_hd_code_8025B300(arg0); sp1C++) {
    if (arg0[sp1C] < 0x45) {
      arg0[sp1C] = D_hd_front_end_8020C01C[arg0[sp1C]];
    } else {
      arg0[sp1C] = 0x2D;
    }
  }
}

void func_hd_front_end_801F74B0(u8* arg0) {
  s32 sp1C;
  s32 sp18;

  for (sp1C = 0; sp1C < func_hd_code_8025B300(arg0); sp1C++) {
    for (sp18 = 0; sp18 < 0x45 && D_hd_front_end_8020C01C[sp18] != arg0[sp1C];sp18++) {

    }
    if (sp18 != 0x45) {
      arg0[sp1C] = sp18;
    } else {
      arg0[sp1C] = 0xF;
    }
  }
}

s32 func_hd_front_end_801F75A4(u8* arg0, s32 arg1) {
  s32 sp34;
  s32 sp30;
  s32 sp2C;
  u8 sp28[4];
  s32 sp24;

  sp2C = (arg1 + 0x7F) >> 7;

  for (sp34 = 0; sp34 < 4; sp34++) {
    sp28[sp34] = 0;
    arg0[arg1 + sp34 - 4] = sp28[sp34];
  }

  for (sp34 = 0; sp34 < sp2C; sp34++) {
    for (sp30 = 0; sp30 < 4; sp30++) {
      sp24 = (sp34 << 7) + (sp30 << 5);
      if (sp24 < arg1) {
        sp28[sp30] += __osContDataCrc(&arg0[sp24]);
      }
    }
  }

  for (sp34 = 0; sp34 < 4; sp34++) {
    arg0[arg1 + sp34 - 4] = sp28[sp34];
  }
  return 0;
}

s32 func_hd_front_end_801F76E4(u8* arg0, s32 arg1) {
  s32 sp3C;
  s32 sp38;
  s32 sp34;
  u8 sp30[4];
  u8 sp2C[4];
  s32 sp28;

  sp34 = (arg1 + 0x7F) >> 7;

  for (sp3C = 0; sp3C < 4; sp3C++) {
    sp30[sp3C] = arg0[arg1 + sp3C - 4];
    sp2C[sp3C] = 0;
    arg0[arg1 + sp3C - 4] = sp2C[sp3C];
  }

  for (sp3C = 0; sp3C < sp34; sp3C++) {
    for (sp38 = 0; sp38 < 4; sp38++) {
      sp28 = (sp3C << 7) + (sp38 << 5);
      if (sp28 < arg1) {
        sp2C[sp38] += __osContDataCrc(&arg0[sp28]);
      }
    }
  }

  for (sp3C = 0; sp3C < 4; sp3C++) {
    if (sp2C[sp3C] != sp30[sp3C]) {
      return 0x6E382;
    }
  }

  return 0;
}
