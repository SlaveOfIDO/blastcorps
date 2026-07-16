#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/hd.h"
#include "../hd_code/yoshi.h"
#include "../hd_code/functions.h"
#include "../hd_code/variables.h"

void func_hd_code_80259BD4(Gfx**, struct Model1*);     /* extern */
Gfx* func_hd_code_80274AA4(Gfx*);                     /* extern */
s32 func_hd_code_8025B558(u16*);                    /* extern */
Gfx* func_hd_code_80274868(Gfx*);                     /* extern */
void func_hd_front_end_801F8354(u8);  /* extern */
void func_hd_front_end_801FE018(s32);  /* extern */
void func_hd_front_end_801E8DCC(u8);                   /* extern */
void func_hd_front_end_801E8EB8(u8, s32);                /* extern */
s16 func_hd_code_8025B370(s32);                     /* extern */
void func_hd_front_end_801E93DC(u8);                /* extern */
void func_hd_front_end_801EA268(UnknownData8024C414 *);  /* extern */
Gfx* func_hd_code_80272ED8(Gfx* arg0, u8 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, f32 arg6);
s32 func_hd_code_8025B3F0(UnknownData8024C414 *, char *);  /* extern */
Gfx* func_hd_code_80274868(Gfx*);
void func_hd_front_end_801EA108(u8, u8, u8);               /* extern */
extern u8 D_hd_front_end_80215520[];
extern u8 D_hd_code_80365060[];
void func_hd_front_end_801EA278(void);  /* extern */
extern u8 D_803046F8;
extern u8 D_80304710;
extern struct S_8020C070 D_hd_front_end_8020C070[];
extern u8 D_hd_front_end_80215520[];
extern u8 D_hd_front_end_802154B0;
extern u8 D_hd_code_80365060[];
extern OSMesgQueue D_hd_front_end_80219EF8;
extern OSMesgQueue D_hd_front_end_80219F50;
extern u8 D_hd_code_80365060[];
extern u8 D_hd_front_end_80215915;
extern u8 D_hd_front_end_80215916;
extern u16 D_hd_front_end_8021591C;
extern s16 D_hd_front_end_8021593C;
extern s32 D_hd_front_end_802154D8;
extern f32 D_hd_front_end_802154E4;
extern s32 D_hd_front_end_802154E8;
extern s32 D_hd_front_end_802154F0[];
extern u8 D_hd_front_end_8021592E;
extern u16 D_hd_code_802E8C98[];
extern s16 D_hd_front_end_802154D2;
extern s16 D_hd_front_end_802154D4;
extern s32 D_hd_front_end_802154DC;
extern f32 D_hd_front_end_802154E0;
extern f32 D_hd_front_end_802154E4;
extern s32 D_hd_front_end_802154E8;
extern s32 D_hd_front_end_802154EC;
extern s32 D_hd_front_end_802154F0[];
extern s32 D_hd_front_end_80215508[];
extern u16 *D_hd_front_end_802158A0;
extern u8 D_hd_front_end_802155A0;
extern u16 D_hd_front_end_80215930[];
extern u16 D_hd_code_80364EF0[][16];
extern u8  D_hd_code_802E8C44[];
extern struct S_80367C04 D_hd_code_802E8F94[];
void func_hd_front_end_801EA278(void);  /* extern */
extern u8 D_80304730;
extern struct S_8020C070 D_hd_front_end_8020C070[];
extern u8 D_hd_front_end_80215520[];
extern u8 D_hd_code_80365060[];
extern s16 D_hd_front_end_802154B2;
extern s16 D_hd_front_end_802154B4;
extern s16 D_hd_front_end_802154B6;
extern s16 D_hd_front_end_802154B8;
extern s16 D_hd_front_end_802154BA;
extern s16 D_hd_front_end_802154BE;
extern s16 D_hd_front_end_802154C0;
extern s32 D_hd_front_end_802154C4;
extern s32 D_hd_front_end_802154C8;
extern s32 D_hd_front_end_802154CC;
extern s16 D_hd_front_end_80215918;
extern s16 D_hd_front_end_8021591A;
extern s32 D_hd_front_end_80215920;
extern s8 *D_hd_front_end_80215928;
extern s16 D_hd_front_end_8021592C;

extern s32 D_hd_front_end_80215908[];
extern s16 D_hd_front_end_80215910[];
extern u8  D_hd_front_end_80215914;
typedef struct {
  char *unk0;
  s32 unk4;
} UnknownData802081C0;

extern u8 D_hd_code_80364AEA;
extern u8 D_hd_code_80365060[];
extern UnknownData802081C0 D_hd_front_end_802081C0[];
extern char* D_hd_front_end_80208358[4];
extern s32 D_hd_front_end_80208368[4];
extern char *D_hd_front_end_80208378[];
extern s8 D_hd_front_end_8020EB00;
extern s8 D_hd_front_end_8020EB2C;
extern s32 D_hd_front_end_80215458;
extern s16 D_hd_front_end_802154D2;
extern s16 D_hd_front_end_802154D4;
extern s32 D_hd_front_end_802154DC;
extern f32 D_hd_front_end_802154E0;
extern s32 D_hd_front_end_802154EC;
extern s32 D_hd_front_end_80215508[];
extern u8 D_hd_front_end_802155A0;
extern u16 D_hd_front_end_80215930[];
extern s16 D_hd_code_8036BB1C;
extern u8  D_hd_front_end_80215900[];
extern u8  D_hd_front_end_80215902[];
extern s32 D_hd_front_end_80215908[];
extern s16 D_hd_front_end_80215910[];
extern s32 D_hd_front_end_80215908[];
extern s16 D_hd_front_end_80215910[];
void func_hd_front_end_801ED480(u8 *, u8 *);      /* extern */
u8 func_hd_front_end_801EF2BC(u16, u8, u8);         /* extern */
Gfx *func_hd_front_end_801EC49C(Gfx *, s32, s32, u8);  /* extern */
extern u16 D_802E8FCC[][0x44 / 2];
extern char D_hd_front_end_80215470[];
extern u8 D_hd_front_end_8020849C[5];
extern s8  D_hd_front_end_8020EBDC;
extern u8  D_hd_front_end_80215480[];
extern u16 D_hd_code_80364EF0[][16];
extern struct S_80367C04 D_hd_code_802E8F94[];
extern u8  saveIt[];
u16 func_hd_front_end_801E9528(void);               /* extern */
extern Vtx  D_hd_front_end_80208380[];
extern u16 D_hd_front_end_802158A8[];
extern s16 D_hd_front_end_802158AA[];

extern s16 D_hd_code_8036BB1C;
extern s16 D_hd_code_8036BB20;
extern u8  D_hd_front_end_80208314[];
extern u32 D_hd_front_end_80208350[];
extern u8  D_hd_front_end_80208498[];
extern f32 D_hd_front_end_80215440;
extern f32 D_hd_front_end_80215444;
extern f32 D_hd_front_end_80215448;
extern f32 D_hd_front_end_8021544C;
extern f32 D_hd_front_end_80215450;
extern f32 D_hd_front_end_80215454;
extern f32 D_hd_front_end_8021545C;
extern f32 D_hd_front_end_80215460;
extern f32 D_hd_front_end_80215464;
extern f32 D_hd_front_end_80215468;
extern s16 D_hd_front_end_8021546C;
extern s16 D_hd_front_end_802154B2;
extern s16 D_hd_front_end_802154B4;
extern s16 D_hd_front_end_802154B6;
extern s16 D_hd_front_end_802154B8;
extern s16 D_hd_front_end_802154BA;
extern u8  D_hd_front_end_802154BC;
extern s16 D_hd_front_end_802154BE;
extern s16 D_hd_front_end_802154C0;
extern s32 D_hd_front_end_802154C4;
extern s32 D_hd_front_end_802154C8;
extern s32 D_hd_front_end_802154CC;
extern u8  D_hd_front_end_802154D0;
extern s16 D_hd_front_end_80215918;
extern s16 D_hd_front_end_8021591A;
extern s32 D_hd_front_end_80215920;
extern u8  D_hd_front_end_80215924;
extern s16 D_hd_front_end_8021592C;
extern s32 D_hd_front_end_80215940;
extern f32 D_hd_front_end_80215944;
extern f32 D_hd_front_end_80215948;
extern f32 D_hd_front_end_8021594C;
extern f32 D_hd_front_end_80215950;

// <data>
UnknownData802081C0 D_hd_front_end_802081C0[31] = {
  { "ROOKIE WRECKER", 0x803041DC },
  { "TRAINED CRUSHER", 0x803041EC },
  { "EXPERIENCED RAVAGER", 0x803041FC },
  { "DECORATED DAMAGER", 0x8030420C },
  { "PROFESSIONAL RAZER", 0x8030421C },
  { "EXPERT DESTROYER", 0x8030422C },
  { "GIFTED RUINER", 0x8030423C },
  { "ACCOMPLISHED CONQUEROR", 0x8030424C },
  { "MASTER DESPOILER", 0x8030425C },
  { "DEMOLITION FANATIC", 0x8030426C },
  { "GRAND ERADICATOR", 0x8030427C },
  { "HEAVY DUTY WASTER", 0x80304288 },
  { "TOTAL PULVERISER", 0x8030429C },
  { "CHAMPION RANSACKER", 0x803042AC },
  { "MECHANICAL MAESTRO", 0x803042B8 },
  { "CHIEF OBLITERATOR", 0x803042CC },
  { "COMMANDING DESOLATOR", 0x803042E0 },
  { "SUPREME DEVASTATOR", 0x803042F0 },
  { "ULTIMATE ANNIHILATOR", 0x80304304 },
  { "LEVELING LEGEND", 0x8030430C },
  { "DESTRUCTIVE PSYCHOPATH", 0x80304318 },
  { "MINDLESS DESECRATOR", 0x80304328 },
  { "HYSTERICAL CLAUSTROPHOBE", 0x80304334 },
  { "UNCONTROLLABLE MADMAN", 0x80304344 },
  { "WORLD CLASS MEGALOMANIAC", 0x80304358 },
  { "CAPTAIN OF CARNAGE", 0x80304364 },
  { "SINGLE MINDED CHAOSMONGER", 0x80304370 },
  { "GRAND HIGH SLAUGHTERMASTER", 0x8030437C },
  { "LUNATIC LORD OF HAVOC", 0x80304388 },
  { "ARMAGEDDON ADEPT", 0x80304394 },
  { "YOU CAN STOP NOW.", 0x8030439C }
};
u8 D_hd_front_end_802082B8[32] = {
  0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x02,
  0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01,
  0x02, 0x01, 0x02, 0x02,
  0x02, 0x01, 0x01, 0x00
};
u16 D_hd_front_end_802082D8[] = {
  0x0777, 0x0777, 0x0776, 0x0773,
  0x0000, 0x0000
};

u16 D_hd_front_end_802082E4[] = { // +6
  0x0774, 0x0775,
};

u16 D_hd_front_end_802082E8[] = { // +8
  0x0576, 0x0575,
};

u16 D_hd_front_end_802082EC[] = { // +10
  0x091B, 0x091B,
  0x091C, 0x091D, 0x0572, 0x0000
};

u16 D_hd_front_end_802082F8[] = { // + 16
  0x091F, 0x0000
};

u8 D_hd_front_end_802082FC[24] = {
  0x31, 0x32, 0x33, 0x34,
  0x2F, 0x2E, 0x7F, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x30, 0x31, 0x32, 0x33,
  0x34, 0x35, 0x36, 0x37,
  0x38, 0x39, 0x2F, 0x7F
};

u8 D_hd_front_end_80208314[60] = {
  'A', 0x42, 0x43, 0x44,
  0x45, 0x46, 0x47, 0x48,
  0x49, 0x4A, 0x4B, 0x4C,
  0x4D, 0x4E, 0x4F, 0x50,
  0x51, 0x52, 0x53, 0x54,
  0x55, 0x56, 0x57, 0x58,
  0x59, 0x5A, 0x42, 0x43,
  0x44, 0x46, 0x47, 0x48,
  0x4A, 0x4B, 0x4C, 0x4D,
  0x4E, 0x50, 0x51, 0x52,
  0x53, 0x54, 0x56, 0x57,
  0x58, 0x59, 0x5A, 0x00,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x07,
  0x00, 0x00, 0x00, 0x0C
};
u32 D_hd_front_end_80208350[2] = {
  0x0000001A, 0x00000015
};
// </data>

void func_hd_front_end_801E8C40(u8 arg0) {
  struct Model1* sp34;
  s32 sp30;

  playerNumber = arg0;
  D_hd_front_end_80215915 = func_hd_code_80272C5C(D_hd_front_end_802082F8, 0, 1U, 1U, 1, 1.0f);
  D_hd_front_end_80215916 = func_hd_code_80272C5C(D_hd_front_end_802082EC, 0, 5U, 1U, 0, 1.0f);
  for(sp30 = 0; sp30 < 2; sp30++) {
    sp34 = &D_hd_code_803156F8[sp30];
    guPerspective(&sp34->projection, &D_hd_front_end_8021591C, 45.0f, 1.3333334f, 10.0f, 10000.0f, 1.0f);
    guLookAt((Mtx* ) &sp34->unk180, 0.0f, 277.0f, 480.0f, 0.0f, 189.0f, 200.0f, 0.0f, 0.0f, 1.0f);
    guTranslate(&sp34->unk2C0[0xC], 0.0f, 88.0f, 0.0f);
  }
  D_hd_front_end_8021593C = 0;
  func_hd_front_end_801E8DCC(playerNumber);
}

void func_hd_front_end_801E8DCC(u8 arg0) {
  s32 sp1C;

  func_hd_front_end_801E8EB8(arg0, 0);
  for(sp1C = 0; sp1C < 0x1B; sp1C++) {
    D_hd_front_end_802158A8[sp1C] = D_hd_code_802E8C94[D_hd_front_end_8021592E];
  }

  D_hd_front_end_802158A8[sp1C] = D_hd_code_802E8C98[D_hd_front_end_8021592E];
  D_hd_front_end_802154D8 = 0;
  D_hd_front_end_802154E8 = 0x270F;
  for(sp1C = 1; sp1C < 5; sp1C++) {
    D_hd_front_end_802154F0[sp1C] = 0x270F;
  }
  D_hd_front_end_802154E4 = 3.0f;
}

static const char D_hd_front_end_8020E764[] = "";
static const char D_hd_front_end_8020E768[] = "GUEST: ";

void func_hd_front_end_801E8EB8(u8 arg0, s32 arg1) {
    s32 sp4C;
    UnknownData8024C414 *sp48 = &players[arg0];
    u8 sp47 = 0;
    char* sp34[4] = {
      ".................... LEADER OF THE ARMY BASE WALKOUT YEARS AGO. AMBER'S SHARP MIND AND BRIGHT, SELFLESS OUTLOOK MAKE HER THE NEAREST THING BLAST CORPS HAS TO A LEADER ....................",
      ".................... A GENIUS IN HEAVY VEHICLE DESIGN. WHILE SOMETIMES OVERLY POSSESSIVE OF HIS CREATIONS, CLARK HAS TALENTS VITAL TO BLAST CORPS' SURVIVAL AND SUCCESS ....................",
      ".................... HEAD MECHANIC OF THE BLAST CORPS TEAM. WITH YEARS OF EXPERIENCE AND A GRUFF PRIDE IN HIS WORK, SPIKE ENSURES THAT THE DOZERS ARE BUILT TO PERFECTION ..................",
      ".................... A FEARLESS ARMY DAREDEVIL UNTIL HIS DISABLING ACCIDENT. WESLEY'S REJECTION BY HIS SUPERIORS TRIGGERED THE REBELLION THAT LED TO THE RISE OF BLAST CORPS ..............."
    };
    s32 sp24[4] = {
      0x803043B8, 0x80304474, 0x80304544, 0x80304614
    };

    if (!(D_hd_code_80364A90 & 0x10E18000) && (arg0 != D_hd_code_80364AEA)) {
        sp47 = 1;
    }
    D_hd_front_end_802154EC = -1;
    for(sp4C = 1; (sp4C < 5); sp4C++) {
        D_hd_front_end_80215508[sp4C] = -1;
    }
    if ((s32) arg0 < 4) {
        func_hd_front_end_801E93DC(arg0);
    }
    if ((D_hd_code_80364A98 == 0x1000000000000)) {
        D_hd_front_end_802158A0 = 0;
        sprintf(&D_hd_front_end_802155A0, "%s", sp34[arg0]);
    } else {
        D_hd_front_end_802158A0 = 0;
        if ((s32) arg0 < 4) {
            if (D_hd_code_80365060[arg0] == 1) {
                sprintf(&D_hd_front_end_802155A0, " ..... %s%s (%s) ... ", D_hd_front_end_80208378[sp47], sp48, D_hd_front_end_802081C0[sp48->unkC].unk0);
                if ((s32) players[arg0].unk91 >= 0xC) {
                    sp4C = 4;
                } else {
                    sp4C = 3;
                }
                for (;sp4C > 0; sp4C--) {
                    D_hd_front_end_80215508[sp4C] = func_hd_code_8025B300(&D_hd_front_end_802155A0);
                    if (sp4C != 1) {
                        sprintf(&D_hd_front_end_802155A0, "%s  %d .. ", &D_hd_front_end_802155A0, D_hd_front_end_80215930[sp4C]);
                    }
                }
                sprintf(&D_hd_front_end_802155A0, "%s  %d ... ", &D_hd_front_end_802155A0, D_hd_front_end_80215930[1]);
                if (D_hd_code_802E8BF8 == 0) {
                    sprintf(&D_hd_front_end_802155A0, "%s$%d ... ", &D_hd_front_end_802155A0, sp48->unk14);
                }
                D_hd_front_end_802154EC = func_hd_code_8025B300(&D_hd_front_end_802155A0);
                sprintf(&D_hd_front_end_802155A0, "%s  %d", &D_hd_front_end_802155A0, sp48->unkC);
                if ((D_hd_code_80364A98 & 0x0200040000000000) || D_hd_code_80364A90 & 0x0100000000000000) {
                    sprintf(&D_hd_front_end_802155A0, "%s ..... %s", &D_hd_front_end_802155A0, "USE Z/R TO CHANGE PLAYER, THEN A TO SELECT!");
                }
            } else {
                sprintf(&D_hd_front_end_802155A0, " ... NEW GAME");
            }
        } else {
            sprintf(&D_hd_front_end_802155A0, " ");
        }
    }
    if (D_hd_front_end_802158A0 != 0) {
        D_hd_front_end_802154D2 = func_hd_code_8025B370(D_hd_front_end_802158A0);
        D_hd_front_end_8021592E = 1;
        D_hd_front_end_80215458 = 0x13;
        if (arg0 == 4) {
            D_hd_front_end_802154D4 = 0x16;
        } else {
            D_hd_front_end_802154D4 = 0xE;
        }
    } else {
        D_hd_front_end_802154D2 = func_hd_code_8025B300(&D_hd_front_end_802155A0);
        D_hd_front_end_8021592E = 0;
        D_hd_front_end_80215458 = 0xC;
        if (arg0 == 4) {
            D_hd_front_end_802154D4 = 0x24;
        } else {
            D_hd_front_end_802154D4 = 0x16;
        }
    }
    if (D_hd_front_end_802154D2 >= 0x100) {
        rmonPrintf(ASSERT_MESSAGE, "sslen<TOTAL_SCROLL_LENGTH", "player.c", 0x190);
    }
    D_hd_front_end_802154DC = -1;
    if (((u8) arg1 != 0) || (arg0 == 4)) {
        D_hd_front_end_802154E0 = 12.0f;
        return;
    }
    D_hd_front_end_802154E0 = 8.0f;
}

// <data>
char* D_hd_front_end_80208378[2] = {
  (char*) D_hd_front_end_8020E764, (char*) D_hd_front_end_8020E768
};

Vtx D_hd_front_end_80208380[8] = {
  { { { 0xFF60, 0x00AE, 0x00B4 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x81, 0x00, 0x28 } } },
  { { { 0x00A0, 0x00AE, 0x00B4 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x81, 0x00, 0x28 } } },
  { { { 0x00A0, 0x00CC, 0x00B4 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x7F, 0x1E, 0x28 } } },
  { { { 0xFF60, 0x00CC, 0x00B4 }, 0x0000, { 0x0000, 0x0000 }, { 0x00, 0x7F, 0x1E, 0x28 } } },
  { { { 0xFF60, 0x00C6, 0x00C8 }, 0x0000, { 0x0000, 0x0000 }, { 0x5A, 0x5A, 0x00, 0xB4 } } },
  { { { 0xFF60, 0x00B4, 0x00C8 }, 0x0000, { 0x0000, 0x0000 }, { 0x5A, 0xA6, 0x00, 0xB4 } } },
  { { { 0x00A0, 0x00B4, 0x00C8 }, 0x0000, { 0x0000, 0x0000 }, { 0x5A, 0xA6, 0x00, 0xB4 } } },
  { { { 0x00A0, 0x00C6, 0x00C8 }, 0x0000, { 0x0000, 0x0000 }, { 0x5A, 0x5A, 0x00, 0xB4 } } }
};

Gfx D_hd_front_end_80208400[9] = {
  gsSPVertex(D_hd_front_end_80208380, 8, 0),
  gsDPPipeSync(),
  gsSP1Triangle(0, 5, 1, 0),
  gsSP1Triangle(5, 1, 6, 0),
  gsSP1Triangle(4, 5, 6, 0),
  gsSP1Triangle(4, 6, 7, 0),
  gsSP1Triangle(4, 3, 7, 0),
  gsSP1Triangle(3, 7, 2, 0),
  gsSPEndDisplayList(),
};

Lights2 D_hd_front_end_80208448[2] = {
  gdSPDefLights2(0x28, 0x0A, 0x0A, 0xF0, 0xC8, 0x14, 0x45, 0xBB, 0x45, 0xF0, 0x6E, 0x14, 0xBB, 0x45, 0x45),
  gdSPDefLights2(0x28, 0x02, 0x21, 0x5A, 0x02, 0xDC, 0x45, 0xBB, 0x45, 0x5A, 0x02, 0xDC, 0xBB, 0x45, 0x45)
};

u8 D_hd_front_end_80208498[4] = {' '};
u8 D_hd_front_end_8020849C[5] = {0};
// </data>

void func_hd_front_end_801E93DC(u8 arg0) {
  s32 spC;
  UnknownData8024C414 *sp8;

  sp8 = &players[arg0];
  for (spC = 0; spC < 6; spC++) {
    D_hd_front_end_80215930[spC] = 0;
  }
  for (spC = 0; spC < 0x3C; spC++) {
    if ((sp8->unk18[spC] > 0) && (sp8->unk18[spC] < 5)) {
      D_hd_front_end_80215930[sp8->unk18[spC]] += 1;
    }
    if (((players[arg0].unk18[spC] > 0) && (players[arg0].unk18[spC] < 6)?1:0) && (D_hd_code_802E8F94[spC].unk0 & 0x81) && (spC != 0x31) && (spC != 0x2F) && (spC != 0x26)) {
      D_hd_front_end_80215930[3]++;
    }
  }
}

u16 func_hd_front_end_801E9528(void) {
  s32 sp4;

  D_hd_front_end_802154DC = (D_hd_front_end_802154DC + 1) % D_hd_front_end_802154D2;
  if (D_hd_front_end_802154DC == D_hd_front_end_802154EC) {
    D_hd_front_end_802154E8 = 0;
  }
  for (sp4 = 1; ((s32) players[playerNumber].unk91 >= 0xC ? 4 : 3) >= sp4; sp4++) {
    if (D_hd_front_end_80215508[sp4] == D_hd_front_end_802154DC) {
      D_hd_front_end_802154F0[sp4] = 0;
    }
  }
  if (D_hd_front_end_802154D4 != 0) {
    D_hd_front_end_802154D4--;
    if (D_hd_front_end_802154D4 == 0) {
      D_hd_front_end_802154E0 = 3.0f;
    }
  }
  D_hd_front_end_802154E4 = (f32) (((f64) (D_hd_front_end_802154E0 - D_hd_front_end_802154E4) * 0.2) + (f64) D_hd_front_end_802154E4);
  if (D_hd_front_end_802158A0 != 0) {
    return D_hd_front_end_802158A0[D_hd_front_end_802154DC];
  }
  return (u16) (&D_hd_front_end_802155A0)[D_hd_front_end_802154DC];
}

s32 func_hd_front_end_801E96F8(void) {
  return D_hd_front_end_802154D2 == (D_hd_front_end_802154DC + 8);
}

Gfx *func_hd_front_end_801E9718(Gfx *gfx, struct Model1 *arg1, s32 arg2) {
    Gfx *entry;


    entry = gfx;

    gSPMatrix(entry++, &arg1->projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(entry++, &arg1->unk180, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    gSPMatrix(entry++, &arg1->unk5C0, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPPerspNormalize(entry++, D_hd_front_end_8021591C);

    gDPPipeSync(entry++);
    gSPTexture(entry++, 1984, 1984, 0, G_TX_RENDERTILE, G_OFF);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
    gSPSetGeometryMode(entry++, G_SHADE | G_LIGHTING | G_SHADING_SMOOTH);

    {

        s32 pad[4];
        gSPSetLights2(entry++, D_hd_front_end_80208448[0]);
        gDPSetRenderMode(entry++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
        gDPSetCombineMode(entry++, G_CC_SHADE, G_CC_SHADE);
    }

    {
        s32 sp84;
        s32 sp80;

        if ((D_hd_code_80364A90 & 0x5040008010080)) {
            D_hd_front_end_8021593C += 0x10;
            if (D_hd_front_end_8021593C >= 0x100) {
                D_hd_front_end_8021593C = 0xFF;
            }
        } else if ((D_hd_code_80364A90 & 0x8000202020000)) {
            D_hd_front_end_8021593C -= 0x10;
            if (D_hd_front_end_8021593C <= 0) {
                D_hd_front_end_8021593C = 0;
            }
        }
        for (sp80 = 0; sp80 < 4; sp80++) {
          D_hd_front_end_80208380[sp80].v.cn[3] = D_hd_front_end_8021593C * 0x28 / 255;
        }
        for (sp80 = 4; sp80 < 7; sp80++) {
          D_hd_front_end_80208380[sp80].v.cn[3] = D_hd_front_end_8021593C * 0xB4 / 255;
        }
        osWritebackDCache(&D_hd_front_end_80208380, 0x80);
        if (D_hd_front_end_8021593C != 0) {
            gSPDisplayList(entry++, D_hd_front_end_80208400);
        }
        gDPPipeSync(entry++);
        gSPClearGeometryMode(entry++, G_LIGHTING);

        D_hd_front_end_802154D8 = (f32) D_hd_front_end_802154D8 + D_hd_front_end_802154E4;
        if (D_hd_front_end_802154D8 >= D_hd_front_end_80215458) {
            D_hd_front_end_802154D8 -= D_hd_front_end_80215458;
            for(sp80 = 1; D_hd_front_end_802158A8[sp80] != D_hd_code_802E8C98[D_hd_front_end_8021592E];sp80++) {
                D_hd_front_end_802158A8[sp80 - 1] = D_hd_front_end_802158A8[sp80];
            }
            sp80--;
            D_hd_front_end_802158A8[sp80] = func_hd_front_end_801E9528();
            D_hd_front_end_802158A8[sp80 + 1] = D_hd_code_802E8C98[D_hd_front_end_8021592E];
        }
        entry = func_hd_code_80274868(entry);
        D_hd_front_end_802154E8 = (f32) D_hd_front_end_802154E8 + D_hd_front_end_802154E4;
        sp84 = 0x136 - D_hd_front_end_802154E8;
        if ((sp84 >= -0x1F) && (sp84 < 0x140)) {
            entry = func_hd_code_80272ED8(entry, (u8) D_hd_front_end_80215915, sp84, 0xC2, (u32) D_hd_front_end_8021593C, 1, 1.0f);
        }
        for (sp80 = 1; sp80 < 5; sp80++) {
            D_hd_front_end_802154F0[sp80] = (f32) D_hd_front_end_802154F0[sp80] + D_hd_front_end_802154E4;
            sp84 = 0x136 - D_hd_front_end_802154F0[sp80];
            if ((sp84 >= -0x1F) && (sp84 < 0x140)) {
                entry = func_hd_code_80272ED8(entry, D_hd_front_end_80215916 + sp80, sp84, 0xC2, (u32) D_hd_front_end_8021593C, 1, 1.0f);
            }
        }
        entry = func_hd_code_80274AA4(entry);

        func_hd_code_80259CCC(arg1,
            (s8 *) ((D_hd_front_end_8021592E == 1) ? 0 : func_hd_code_8025B558((u16 *) D_hd_front_end_802158A8)),
            (u16 *) ((D_hd_front_end_8021592E == 1) ? D_hd_front_end_802158A8 : NULL),
            0U, 0,
            ((s32) -D_hd_front_end_802154D8 % (s32) D_hd_front_end_80215458) - 3,
            0xC9, 0x14, 0x14, 1, 0, 0, 0,
            (((s16) D_hd_front_end_8021593C / 2) - 0x1B < 0) ? 0 : ((s16) D_hd_front_end_8021593C / 2) - 0x1B);

        func_hd_code_80259DC8(arg1,
            (D_hd_front_end_8021592E == 1) ? 0 : func_hd_code_8025B558((u16 *) D_hd_front_end_802158A8),
            (s32) ((D_hd_front_end_8021592E == 1) ? D_hd_front_end_802158A8 : NULL),
            0, 0,
            (s32) -D_hd_front_end_802154D8 % (s32) D_hd_front_end_80215458,
            0xC7, 0x14, 0x14, 1, 0xFF, 0xFF, 0xFF, (s32) D_hd_front_end_8021593C,
            0xFF, 0xFF, 0xFF, (s32) D_hd_front_end_8021593C);

        gDPPipeSync(entry++);
    }

    return entry;
}

void func_hd_front_end_801EA108(u8 arg0, u8 arg1, u8 arg2) {
  UnknownData8024C414 *sp2C;
  u32 sp28;

  sp2C = &players[arg0];
  for (sp28 = 0; sp28 < 0x100U; sp28++) {
    ((u8 *) sp2C)[sp28] = 0;
  }
  func_hd_front_end_801EA268(sp2C);
  sprintf((u8 *) sp2C, "%s", "NEW GAME");
  D_hd_code_80365060[arg0] = 2;
  osSendMesg(&D_hd_front_end_80219EF8, (void *) ((arg0 << 0x10) | 7), 1);
  if (arg1 != 0) {
    osSendMesg(&D_hd_front_end_80219EF8, (void *) ((arg2 ? 0x14 : 0x15) | (arg0 << 0x10) | 0x01000000), 1);
    osRecvMesg(&D_hd_front_end_80219F50, NULL, 1);
    return;
  }
  osSendMesg(&D_hd_front_end_80219EF8, (void *) ((arg2 ? 0x14 : 0x15) | (arg0 << 0x10)), 1);
}

void func_hd_front_end_801EA268(UnknownData8024C414* arg0) {
  arg0->unk10 = 0x1063E;
}

void func_hd_front_end_801EA278(void) {
  s32 sp1C;
  void *sp18;

  for (sp1C = 0; sp1C < 4; sp1C++) {
    osSendMesg(&D_hd_front_end_80219EF8, (void *) ((sp1C << 0x10) | 6 | 0x01000000), 1);
    osRecvMesg(&D_hd_front_end_80219F50, &sp18, 1);
    if (sp18 == NULL) {
      if (func_hd_code_8025B3F0(&players[sp1C], "NEW GAME") != 0) {
        D_hd_code_80365060[sp1C] = 1;
      } else {
        D_hd_code_80365060[sp1C] = 2;
      }
    } else if (sp18 != (void *) 0x6E382) {
      if (sp1C < (s32) D_hd_code_8039C4F8.unk40) {
        osSendMesg(&D_hd_front_end_80219EF8, (void *) ((sp1C << 0x10) | 3 | 0x01000000), 1);
        osRecvMesg(&D_hd_front_end_80219F50, &sp18, 1);
      }
      if ((sp18 != NULL) || (sp1C >= (s32) D_hd_code_8039C4F8.unk40)) {
        D_hd_code_80365060[sp1C] = 0;
        sprintf(&D_hd_front_end_80215520[sp1C * 0x19], "%d : %s", sp1C + 1, "PAK FULL");
      } else {
        func_hd_front_end_801EA108(sp1C, 1, 0);
      }
    } else {
      func_hd_front_end_801EA108(sp1C, 1, 0);
    }
    if ((D_hd_code_80365060[sp1C] == 1) || (D_hd_code_80365060[sp1C] == 2)) {
      sprintf(&D_hd_front_end_80215520[sp1C * 0x19], "%d : %s", sp1C + 1, &players[sp1C]);
    }
  }
}

void func_hd_front_end_801EA4B8(void) {
  s32 sp1C;

  func_hd_front_end_801EA278();
  D_hd_front_end_802154B0 = 0;
  for (sp1C = 0; sp1C < 4; sp1C++) {
    D_hd_front_end_8020C070[2 + sp1C].unkC = &D_hd_front_end_80215520[sp1C * 0x19];
    D_hd_front_end_8020C070[2 + sp1C].unk0 |= 0x81;
    D_hd_front_end_8020C070[2 + sp1C].unk0 &= ~0x20;
    D_hd_front_end_8020C070[2 + sp1C].unk18 = 7;
    D_hd_front_end_8020C070[2 + sp1C].unk19 = 4;
    D_hd_front_end_8020C070[2 + sp1C].unk2 = 0x50;
    if (D_hd_code_80365060[sp1C] != 0) {
      continue;
    }
    D_hd_front_end_8020C070[2 + sp1C].unk0 &= ~0x81;
    D_hd_front_end_8020C070[2 + sp1C].unk18 = 8;
    D_hd_front_end_802154B0++;

  }
  if (D_hd_front_end_802154B0 != 4) {
    D_hd_front_end_8020C070[6].unkC = "ERASE GAME";
    D_hd_front_end_8020C070[6].unk10 = &D_803046F8;
  } else {
    D_hd_front_end_8020C070[6].unkC = "IGNORE PAK";
    D_hd_front_end_8020C070[6].unk10 = &D_80304710;
  }
  D_hd_front_end_8020C070[6].unk19 = 2;
  D_hd_code_802F8BDC[0xA].unk8 &= ~0x400;
}

void func_hd_front_end_801EA6E8(void) {
  s32 sp24;

  func_hd_front_end_801EA278();
  for (sp24 = 0; sp24 < 4; sp24++) {
    D_hd_front_end_8020C070[sp24 + 2].unk2 = 0x40;
    switch (D_hd_code_80365060[sp24]) {         /* irregular */
      case 1:
        sprintf(&D_hd_front_end_80215520[sp24 * 0x19], "ERASE %d : %s", sp24 + 1, &players[sp24]);
        D_hd_front_end_8020C070[sp24 + 2].unk0 |= 0x81;
        D_hd_front_end_8020C070[sp24 + 2].unk0 &= ~0x20;
        D_hd_front_end_8020C070[sp24 + 2].unk18 = 7;
        D_hd_front_end_8020C070[sp24 + 2].unk19 = 4;
        break;
      case 0:
      case 2:
        D_hd_front_end_8020C070[sp24 + 2].unk18 = 8;
        D_hd_front_end_8020C070[sp24 + 2].unk0 |= 0x20;
        D_hd_front_end_8020C070[sp24 + 2].unk0 &= ~0x81;
        D_hd_front_end_8020C070[sp24 + 2].unk18 = 8;
        break;
    }
  }
  D_hd_front_end_8020C070[6].unkC = "GO BACK";
  D_hd_front_end_8020C070[6].unk10 = &D_80304730;
  D_hd_front_end_8020C070[6].unk19 = 2;
  D_hd_code_802F8BDC[0xA].unk8 |= 0x400;
  D_hd_code_802F8BDC[0xA].unk18 = 6;
}

void func_hd_front_end_801EA93C(char *arg0, void *arg1, u8 arg2, u8 arg3, s8 *arg4) {
  D_hd_front_end_802154B2 = 0x7FFF;
  D_hd_front_end_802154B4 = 0x7FFF;
  D_hd_front_end_80215918 = 0;
  D_hd_front_end_802154B8 = 0;
  D_hd_front_end_802154B6 = 0;
  D_hd_front_end_802154BA = -1;
  D_hd_front_end_802154BC = 0;
  D_hd_front_end_802154BE = 0;
  D_hd_front_end_802154C0 = 1;
  D_hd_front_end_8020C070[7].unk6 = arg3;
  D_hd_front_end_8020C070[7].unk8 = arg3;
  D_hd_front_end_802154CC = arg3;
  D_hd_front_end_802154C8 = arg3 * 3 / 5;
  D_hd_front_end_80215928 = arg4;
  *arg4 = 0;
  D_hd_front_end_8020C070[7].unkC = (char *) D_hd_front_end_80215928;
  D_hd_front_end_802154C4 = 0xA0 - (D_hd_front_end_802154C8 / 2);
  D_hd_front_end_8020C070[7].unk2 = D_hd_front_end_802154C4;
  D_hd_front_end_8020C070[8].unkC = arg0;
  D_hd_front_end_8020C070[8].unk10 = arg1;
  D_hd_front_end_80215924 = arg2;
  D_hd_front_end_802154D0 = 1;
  D_hd_front_end_8021591A = 0;
  D_hd_front_end_80215920 = 1;
  D_hd_front_end_8021592C = 0;
}

Gfx *func_hd_front_end_801EAA7C(Gfx *gfx, struct Model1 *arg1, s32 *arg2) {
    Gfx *entry = gfx;
    struct S_8020C070 *spF8 = &D_hd_front_end_8020C070[7];
    u8 spF7;
    s32 spF0;
    s32 spEC;
    s16 spEA;
    s32 spE4;
    s32 spE0;
    s32 spDC;
    s32 spD8;
    s32 spD4;
    s32 spD0;
    s32 spCC = 0;
    s32 spC8;
    u8 *spC4;
    u8 *spC0;
    s16 spBE;
    s16 spBC;
    u8 spBB;

    spC8 = func_hd_code_8025B300(D_hd_front_end_80215928);
    spC4 = D_hd_code_802F47B0[16];

    if ((D_hd_code_80370C28 & 0x300) && !(D_hd_code_80370C2A & 0x300)) {
        sndPlaySfx((struct ALBankAlt_s *) D_hd_code_80367738, 0xC, NULL);
    }
    D_hd_front_end_8021546C = D_hd_front_end_8021591A;
    D_hd_front_end_8021591A = D_hd_code_80370C2C;
    if ((D_hd_code_80370C2C > 0 ? D_hd_code_80370C2C : -D_hd_front_end_8021591A) < 0xA) {
        D_hd_front_end_8021591A = 0;
    } else {
        D_hd_front_end_8021591A *= (D_hd_front_end_8021591A > 0) ? D_hd_front_end_8021591A : -D_hd_front_end_8021591A;
    }
    if (D_hd_front_end_8021591A != 0) {
        if (D_hd_front_end_8021546C == 0) {
            D_hd_front_end_80215918 = D_hd_front_end_802154B6;
        }
        D_hd_front_end_802154B4 -= D_hd_front_end_8021591A >> 3;
    } else {
        if ((D_hd_front_end_8021546C != 0) && (D_hd_front_end_802154B6 == D_hd_front_end_80215918)) {
            D_hd_front_end_802154B6 += (D_hd_front_end_8021546C >= 0) ? 1 : -1;
            if (D_hd_front_end_802154B6 < 0) {
                D_hd_front_end_802154B6 += 0x21;
            }
            if (D_hd_front_end_802154B6 >= 0x21) {
                D_hd_front_end_802154B6 -= 0x21;
            }
            D_hd_front_end_802154B2 = 0x7FFF - (D_hd_front_end_802154B6 * 0x7C2);
        }
        spEA = D_hd_front_end_802154B4 - D_hd_front_end_802154B2;
        D_hd_front_end_802154B4 -= spEA >> 4;
    }
    D_hd_front_end_802154B6 = (0x83E0 - D_hd_front_end_802154B4) / 1986;
    if (D_hd_front_end_802154B6 == 0x21) {
        D_hd_front_end_802154B6 = 0;
    }
    if (D_hd_front_end_8021591A != 0) {
        D_hd_front_end_802154B2 = 0x7FFF - (D_hd_front_end_802154B6 * 0x7C2);
    }
    if (D_hd_front_end_802154D0 != 0) {
        D_hd_front_end_802154B8 = D_hd_front_end_802154B6;
        D_hd_front_end_802154D0 = 0;
    }
    if (D_hd_front_end_802154B6 != D_hd_front_end_802154B8) {
        sndPlaySfx((struct ALBankAlt_s *) D_hd_code_80367738, 0x90, NULL);
    }
    D_hd_front_end_802154B8 = D_hd_front_end_802154B6;
    for(spEC = 0; spEC < 2; spEC++) {
        for (spF0 = 0; spF0 < 33; spF0++) {
            spBE = (D_hd_front_end_802154B4 + spF0 * 0x7C2) - 0x6000;
            spBC = spBE - 0x2000;
            spBC += 0x7FFF;
            spBC += 0x2000;
            spBC += 0x7FFF;
            spE4 = (s32) ((((f64) sins(spBC) * 120.0) / 32768.0) - 7.0);
            spE0 = (s32) ((((f64) coss(spBC) * 96.0) / 32768.0) - 10.0);
            if (spF0 < D_hd_front_end_80208350[0]) {
                D_hd_front_end_80208498[0] = D_hd_front_end_80208314[spF0];
            } else {
                D_hd_front_end_80208498[0] = D_hd_front_end_802082FC[spF0 - D_hd_front_end_80208350[0]];
            }
            if ((u8) D_hd_front_end_80208498[0] != D_hd_front_end_802154BA) {
                if (spEC != 0) {
                    if (D_hd_front_end_802154B6 == spF0) {
                        spF7 = D_hd_front_end_80208498[0],
                        spDC = spE4,
                        spD8 = spE0,
                        spD4 = 0x18,
                        spD0 = 0x14;
                    } else {
                        func_hd_code_80259DC8(arg1, D_hd_front_end_80208498, 0, 1, 0, spE4, spE0, 0x18, 0x14, 1, 0xC8, 0xC8, 0xC8, (s32) D_hd_code_8036BB20, 0xFF, 0xFF, 0xFF, (s32) D_hd_code_8036BB20);
                    }
                } else if (D_hd_front_end_802154B6 == spF0) {
                    func_hd_code_80259CCC(arg1, D_hd_front_end_80208498, NULL, 1U, 0, spE4 - 0xB, spE0, 0x30, 0x28, 1, 0, 0, 0, D_hd_code_8036BB20 / 2);
                } else {
                    func_hd_code_80259CCC(arg1, D_hd_front_end_80208498, NULL, 1U, 0, spE4 - 4, spE0 + 3, 0x18, 0x14, 1, 0, 0, 0, D_hd_code_8036BB20 / 2);
                }
            }
        }
    }
    if ((spF7 != D_hd_front_end_802154BA) && (D_hd_front_end_802154BA == -1)) {
        if (D_hd_code_803156C4 % 20U < 0xFU) {
            spBB = D_hd_code_8036BB20;
        } else {
            spBB = D_hd_code_8036BB20 / 3;
        }
        D_hd_front_end_80208498[0] = spF7;
        func_hd_code_80259BD4(&entry, arg1);
        func_hd_code_80259DC8(arg1, (s32) D_hd_front_end_80208498, 0, 1, 0, spDC - 5, spD8 - 5, spD4 * 2, spD0 * 2, 1, spC4[0], spC4[1], spC4[2], spBB, spC4[4], spC4[5], spC4[6], spBB);
    }
    if ((D_hd_code_8036BB1C == 2) && (D_hd_code_80370C28 & 0x1000) && !(D_hd_code_80370C2A & 0x1000) && (areWeFading() == 0)) {
        if (D_hd_front_end_802154BC != 0) {
            D_hd_code_80364A98 = 0x01000000;
            D_hd_code_80365060[playerNumber] = 1;
            func_hd_code_8026AF6C(0x4000U);
        } else {
            sndPlaySfx((struct ALBankAlt_s *) D_hd_code_80367738, 0x2B, NULL);
        }
    }
    switch (D_hd_front_end_802154BE) {              /* switch 1; irregular */
    case 0:
        if ((D_hd_code_8036BB1C == 2) && (D_hd_code_80370C28 & 0xC000) && !(D_hd_code_80370C2A & 0xC000) && (areWeFading() == 0)) {
            if (D_hd_code_80370C28 & 0x4000) {
                spF7 = 0x7F;
            }
            if (spF7 == 0x7F) {
                if (D_hd_front_end_802154BC == 0) {
                    if (D_hd_code_80370C28 & 0x4000) {
                        if (D_hd_code_802E8BF8 != 0) {
                            func_hd_code_80275270(0x0400000000000000, 0.5f);
                        } else {
                            D_hd_code_80364A98 = 0x200000;
                        }
                        sndPlaySfx((struct ALBankAlt_s *) D_hd_code_80367738, 0xDE, NULL);
                        func_hd_code_8026AF6C(0x4000U);
                    } else {
                        sndPlaySfx((struct ALBankAlt_s *) D_hd_code_80367738, 0x2B, NULL);
                    }
                } else {
                    D_hd_front_end_802154BC--;
                    D_hd_front_end_80215928[D_hd_front_end_802154BC] = 0;
                    sndPlaySfx((struct ALBankAlt_s *) D_hd_code_80367738, 0xE4, NULL);
                    D_hd_front_end_802154C0 = 0;
                    D_hd_front_end_80215464 = spF8->unk6;
                    D_hd_front_end_80215468 = D_hd_front_end_802154CC;
                    spF0 = (s32)D_hd_front_end_80215468;
                    spF0 = spF0 * 3 / 5;
                    D_hd_front_end_80215450 = spF8->unk2;
                    D_hd_front_end_80215454 = (-(((spC8 - 1) * (s32) spF0) / 2) - ((s32) spF0 / 2)) + 0xA0;
                    D_hd_front_end_8021545C = D_hd_front_end_802154C4;
                    D_hd_front_end_80215460 = ((((spC8 - 1) * (s32) spF0) / 2) - ((s32) spF0 / 2)) + 0xA0;
                }
            } else if ((s32) D_hd_front_end_802154BC < (s32) D_hd_front_end_80215924) {
                sndPlaySfx((struct ALBankAlt_s *) D_hd_code_80367738, 0x91, NULL);
                D_hd_front_end_802154BE = 1;
                D_hd_front_end_802154C0 = 0;
                D_hd_front_end_802154BA = spF7;
                D_hd_front_end_80215464 = spF8->unk6;
                D_hd_front_end_80215468 = D_hd_front_end_802154CC;
                spF0 = (s32)D_hd_front_end_80215468;
                spF0 = spF0 * 3 / 5;
                D_hd_front_end_80215450 = spF8->unk2;
                D_hd_front_end_80215454 = (-(((spC8 + 1) * (s32) spF0) / 2) - ((s32) spF0 / 2)) + 0xA0;
                D_hd_front_end_8021545C = D_hd_front_end_802154C4;
                D_hd_front_end_80215460 = ((((spC8 + 1) * (s32) spF0) / 2) - ((s32) spF0 / 2)) + 0xA0;
                D_hd_front_end_80215944 = spDC - 5;
                D_hd_front_end_80215948 = spD8 - 5;
                D_hd_front_end_8021594C = (D_hd_front_end_80215460 - 160.0f) - (f32) spF0;
                D_hd_front_end_80215950 = spF8->unk4 - 0x78;
                D_hd_front_end_80215440 = 48.0f;
                D_hd_front_end_80215444 = 40.0f;
                D_hd_front_end_80215448 = D_hd_front_end_802154CC;
                D_hd_front_end_8021544C = D_hd_front_end_802154CC;
            } else {
                sndPlaySfx((struct ALBankAlt_s *) D_hd_code_80367738, 0x2B, NULL);
            }
        }
        break;
    case 1:
        D_hd_front_end_80215944 = (f32) ((f64) D_hd_front_end_80215944 + ((f64) (D_hd_front_end_8021594C - D_hd_front_end_80215944) * 0.2));
        D_hd_front_end_80215948 = (f32) ((f64) D_hd_front_end_80215948 + ((f64) (D_hd_front_end_80215950 - D_hd_front_end_80215948) * 0.2));
        D_hd_front_end_80215440 = (f32) ((f64) D_hd_front_end_80215440 + ((f64) (D_hd_front_end_80215448 - D_hd_front_end_80215440) * 0.2));
        D_hd_front_end_80215444 = (f32) ((f64) D_hd_front_end_80215444 + ((f64) (D_hd_front_end_8021544C - D_hd_front_end_80215444) * 0.2));
        D_hd_front_end_80208498[0] = D_hd_front_end_802154BA;
        func_hd_code_80259CCC(arg1, &D_hd_front_end_80208498, NULL, 0U, 0, (s32) (D_hd_front_end_80215944 - 4.0f), (s32) (D_hd_front_end_80215948 + 4.0f), (s32) D_hd_front_end_80215440, (s32) D_hd_front_end_80215444, 1, 0, 0, 0, D_hd_code_8036BB20 / 2);
        func_hd_code_80259DC8(arg1, (s32) &D_hd_front_end_80208498, 0, 0, 0, (s32) D_hd_front_end_80215944, (s32) D_hd_front_end_80215948, (s32) D_hd_front_end_80215440, (s32) D_hd_front_end_80215444, 1, spC4[0], spC4[1], spC4[2], (s32) D_hd_code_8036BB20, spC4[4], spC4[5], spC4[6], (s32) D_hd_code_8036BB20);
        if ((ABS((D_hd_front_end_80215944 - D_hd_front_end_8021594C))) < 0.15
            && (ABS((D_hd_front_end_80215948 - D_hd_front_end_80215950))) < 0.15) {
            sndPlaySfx((struct ALBankAlt_s *) D_hd_code_80367738, 1, NULL);
            D_hd_front_end_802154BE = 0,
            D_hd_front_end_802154C0 = 0;

            D_hd_front_end_80215928[D_hd_front_end_802154BC] = D_hd_front_end_80208498[0];
            D_hd_front_end_802154BC++;
            D_hd_front_end_80215928[D_hd_front_end_802154BC] = 0;
            D_hd_front_end_802154BA = -1;
        }
        break;
    }
    func_hd_code_80259BD4(&entry, arg1);
    D_hd_front_end_80215940 += D_hd_front_end_80215920;
    if (D_hd_front_end_80215920 < 0) {
        D_hd_front_end_80215940 += D_hd_front_end_80215920 * 2;
    }
    if ((D_hd_front_end_80215940 < 0) || (D_hd_front_end_80215940 >= 0x10)) {
        D_hd_front_end_80215940 -= D_hd_front_end_80215920 * 2;
        D_hd_front_end_80215920 = -D_hd_front_end_80215920;
    }

    D_hd_front_end_8021592C = D_hd_code_8036BB1C == 2 ? MIN(D_hd_front_end_8021592C + 16, 0xFF) : 0;
    spC0 = D_hd_code_802F47B0[0x13];
    spCC = func_hd_code_80276130(arg1, 3U, spCC, D_hd_front_end_802154C4 + D_hd_front_end_802154C8 + D_hd_front_end_80215940, spF8->unk4 + (spF8->unk8 / 2), (spF8->unk6 / 3) + (D_hd_front_end_80215940 / 2), (spF8->unk8 / 2) + 3, D_hd_code_802F47B0[0x13][0], D_hd_code_802F47B0[0x13][1], D_hd_code_802F47B0[0x13][2], (u8) D_hd_front_end_8021592C, D_hd_code_802F47B0[0x13][4], D_hd_code_802F47B0[0x13][5], D_hd_code_802F47B0[0x13][6], (u8) D_hd_front_end_8021592C, D_hd_code_802F47B0[0x13][0], D_hd_code_802F47B0[0x13][1], D_hd_code_802F47B0[0x13][2], (u8) D_hd_front_end_8021592C, D_hd_code_802F47B0[0x13][4], D_hd_code_802F47B0[0x13][5], D_hd_code_802F47B0[0x13][6], (u8) D_hd_front_end_8021592C);
    spCC = func_hd_code_80276080(arg1, 3, spCC, D_hd_front_end_802154C4 + D_hd_front_end_802154C8 + D_hd_front_end_80215940 + 4, spF8->unk4 + (spF8->unk8 / 2) + 3, (spF8->unk6 / 3) + (D_hd_front_end_80215940 / 2), (spF8->unk8 / 2) + 3, 0, 0, 0, D_hd_front_end_8021592C / 2);
    entry = func_hd_code_80275DA4(entry, 0);
    gSPVertex(entry++, (u32) arg1->unk1E00, 8, 0);
    gSP1Triangle(entry++, 4, 5, 6, 0);
    gSP1Triangle(entry++, 4, 6, 7, 0);
    gSP1Triangle(entry++, 0, 1, 2, 0);
    gSP1Triangle(entry++, 0, 2, 3, 0);
    spCC = func_hd_code_80276130(arg1, 2U, spCC, (spF8->unk2 - D_hd_front_end_80215940) - 4, spF8->unk4 + (spF8->unk8 / 2), (spF8->unk6 / 3) + (D_hd_front_end_80215940 / 2), (spF8->unk8 / 2) + 3, spC0[0], spC0[1], spC0[2], D_hd_front_end_8021592C, spC0[4], spC0[5], spC0[6], (u8) D_hd_front_end_8021592C, spC0[0], spC0[1], spC0[2], (u8) D_hd_front_end_8021592C, spC0[4], spC0[5], spC0[6], (u8) D_hd_front_end_8021592C);
    spCC = func_hd_code_80276080(arg1, 2, spCC, (spF8->unk2 - D_hd_front_end_80215940) - 8, spF8->unk4 + (spF8->unk8 / 2) + 3, (spF8->unk6 / 3) + (D_hd_front_end_80215940 / 2), (spF8->unk8 / 2) + 3, 0, 0, 0, D_hd_front_end_8021592C / 2);
    entry = func_hd_code_80275DA4(entry, 0);
    gSPVertex(entry++, &arg1->unk1D80[spCC], 8, 0);
    gSP1Triangle(entry++, 4, 5, 6, 0);
    gSP1Triangle(entry++, 4, 6, 7, 0);
    gSP1Triangle(entry++, 0, 1, 2, 0);
    gSP1Triangle(entry++, 0, 2, 3, 0);

    switch (D_hd_front_end_802154C0) {              /* switch 2; irregular */
    case 1:
        break;
    case 0:
        D_hd_front_end_80215450 = (f32) ((f64) D_hd_front_end_80215450 + ((f64) (D_hd_front_end_80215454 - D_hd_front_end_80215450) * 0.2));
        spF8->unk2 = (s16) (s32) D_hd_front_end_80215450;
        D_hd_front_end_8021545C = (f32) ((f64) D_hd_front_end_8021545C + ((f64) (D_hd_front_end_80215460 - D_hd_front_end_8021545C) * 0.2));
        D_hd_front_end_802154C4 = (s32) D_hd_front_end_8021545C;
        break;
    }
    *arg2 += entry - gfx;
    return entry;
}

void func_hd_front_end_801EC288(u8 arg0) {
  s32 sp4;

  D_hd_front_end_80215902[0] = 3;
  D_hd_front_end_80215902[1] = arg0;
  for (sp4 = 0; sp4 < 2; sp4++) {
    D_hd_front_end_80215900[sp4] = 4;
    D_hd_front_end_80215908[sp4] = 0x32;
    D_hd_front_end_80215910[sp4] = 0;
  }
}

void func_hd_front_end_801EC30C(u8 arg0) {
  s32 sp24;
  s32 sp20;

  D_hd_front_end_80215914 = func_hd_code_80272C5C(D_hd_front_end_802082E4, D_hd_front_end_802082D8, 4U, 2U, 0, 1.0f);
  func_hd_code_80272C5C(D_hd_front_end_802082E8, 0, 1U, 2U, 1, 1.0f);
  D_hd_front_end_80215902[0] = 3;
  D_hd_front_end_80215902[1] = arg0;
  if (D_hd_code_802E8F94[levelno].unk0 == 1) {
    sp24 = 0;
  } else {
    sp24 = 1;
  }

  for (sp20 = 0; sp24 < 2; sp24++, sp20++) {
    D_hd_front_end_80215900[sp24] = 0;
    D_hd_front_end_80215908[sp24] = (sp20 * 0x3C) + 0x28;
    D_hd_front_end_80215910[sp24] = 0;
  }
}

void func_hd_front_end_801EC464(void) {
  s32 sp4;

  for(sp4 = 0; sp4 < 2; sp4++) {
    D_hd_front_end_80215900[sp4] = 3;
  }
}

Gfx* func_hd_front_end_801EC49C(Gfx* arg0, s32 arg1, s32 arg2, u8 arg3) {
  Gfx* sp34;
  s32 pad30;
  s32 sp2C;

  sp34 = arg0;
  if (D_hd_code_8036BB1C == 8) {
    D_hd_front_end_80215900[arg3] = 3;
  }
  switch ((u8) D_hd_front_end_80215900[arg3]) {
    case 2:
      break;
    case 0:
      D_hd_front_end_80215908[arg3] -= 1;
      if (D_hd_front_end_80215908[arg3] == 0) {
        D_hd_front_end_80215900[arg3] = 1;
        if ((u8) D_hd_front_end_80215902[arg3] == 5) {
          sndPlaySfx((struct ALBankAlt_s *) D_hd_code_80367738, 0xEA, NULL);
        } else {
          sndPlaySfx((struct ALBankAlt_s *) D_hd_code_80367738, 0xE6, NULL);
        }
      }
      break;
    case 4:
      D_hd_front_end_80215908[arg3] -= 1;
      if (D_hd_front_end_80215908[arg3] == 0) {
        D_hd_front_end_80215900[arg3] = 1;
      }
      break;
    case 1:
      D_hd_front_end_80215910[arg3] += 0x10;
      if (D_hd_front_end_80215910[arg3] >= 0x100) {
        D_hd_front_end_80215910[arg3] = 0xFF;
        D_hd_front_end_80215900[arg3] = 2;
      }
      break;
    case 3:
      D_hd_front_end_80215910[arg3] -= 0x20;
      if (D_hd_front_end_80215910[arg3] < 0) {
        D_hd_front_end_80215910[arg3] = 0;
      }
      break;
  }
  if (D_hd_front_end_80215900[arg3] == 0) {
    return sp34;
  }
  if (D_hd_front_end_80215902[arg3] == 5) {
    sp2C = 2;
  } else {
    sp2C = 1;
  }
  sp34 = func_hd_code_80272ED8(sp34, ((s32) (u8) D_hd_front_end_80215902[arg3] % 5) + (u8) D_hd_front_end_80215914, arg1, arg2, (u32) D_hd_front_end_80215910[arg3], sp2C, 1.0f);
  return sp34;
}

Gfx *func_hd_front_end_801EC770(Gfx *gfx, struct Model1 *arg1, s32 *arg2) {
  Gfx *entry = gfx;
  u8 sp63;

  entry = func_hd_code_80274868(entry);
  if (D_hd_code_80364AA8 == 1) {
    entry = func_hd_front_end_801EC49C(entry, 0x5C, 0x68, 0);
    if (D_hd_front_end_80215902[1] != 0) {
      entry = func_hd_front_end_801EC49C(entry, 0xA8, 0x68, 1);
    }
  } else {
    if (D_hd_front_end_80215902[1] == 5) {
      sp63 = 1;
    } else {
      sp63 = MIN(((players[playerNumber].unk91 >= 0xC) ? 4 : 3), D_hd_front_end_80215902[1] + 1);
    }
    entry = func_hd_front_end_801EC49C(entry, 0x82, 0x68, 1);
    entry = func_hd_code_80272ED8(entry, sp63 + (u8) D_hd_front_end_80215914, 0x2EU, 0x6C, (u32) ((s32) (D_hd_front_end_80215910[1] * 3) / 4), 0, 0.75f);
  }
  entry = func_hd_code_80274AA4(entry);
  if (D_hd_code_80364AA8 != 1) {
    func_hd_code_80264A34(D_hd_front_end_80215470, D_802E8FCC[levelno][-sp63], 0); // TODO: find correct base
    D_hd_front_end_80215470[5]  = 0;
    func_hd_code_80259DC8(arg1, D_hd_front_end_80215470, 0, 0, 0, 0x29, 0x7D, 0x10, 0x10, 1, 0xFF, 0xB4, 0, D_hd_front_end_80215910[1], 0xFF, 0x78, 0, D_hd_front_end_80215910[1]);
  }
  *arg2 += entry - gfx;
  return entry;
}

u64 func_hd_front_end_801ECA50(u8 arg0) {
  u64 sp8;

  if ((players[playerNumber].unk18[arg0] > 0) && (players[playerNumber].unk18[arg0] < 6)?1:0 != 0) {
    sp8 = 0x80;
  } else if (D_hd_code_802E8F94[arg0].unk0 & 0x81) {
    sp8 = 0x800;
  } else {
    sp8 = 0x20000000;
  }
  return sp8;
}

void func_hd_front_end_801ECB18(void) {
  func_hd_front_end_801FE018(8);
  D_hd_code_80364A87 = 0;
  D_hd_code_803643D5 = 0;
  if (((players[playerNumber].unk18[levelno] > 0) && (players[playerNumber].unk18[levelno] < 6)?1:0) != 0) {
    if (D_hd_code_802E8F94[levelno].unk0 == 1) {
      osSendMesg(&D_hd_front_end_80219EF8, (void *) ((levelno << 8) | 0xC | (playerNumber << 0x10)), 1);
    }
    osSendMesg(&D_hd_front_end_80219EF8, (void *) ((levelno << 8) | 8 | (playerNumber << 0x10) | 0x01000000), 1);
    return;
  }
  osSendMesg(&D_hd_front_end_80219EF8, (void *) ((levelno << 8) | 0x16 | (playerNumber << 0x10) | 0x01000000), 1);
  func_hd_front_end_801F8354(playerNumber);
}

void func_hd_front_end_801ECC8C(void) {
  s32 sp1C;
  s32 sp18;

  sp18 = 0;
  for (sp1C = 0; sp1C < 4; sp1C++) {
    if (saveIt[sp1C] != 0) {
      if (sp18 == 0) {
        func_hd_code_80261570(0.0f);
        sp18 = 1;
      }
      osSendMesg(&D_hd_front_end_80219EF8, (void *) ((sp1C << 0x10) | 0x14), 1);
      rmonPrintf("saving player %d on level %d\n", sp1C, saveIt[sp1C] - 1);
      players[sp1C].levelno = levelno;
      osSendMesg(&D_hd_front_end_80219EF8, (void *) (((saveIt[sp1C] - 1) << 8) | 7 | (sp1C << 0x10)), 1);
      osSendMesg(&D_hd_front_end_80219EF8, (void *) (((saveIt[sp1C] - 1) << 8) | 9 | (sp1C << 0x10)), 1);
      osSendMesg(&D_hd_front_end_80219EF8, (void *) (((saveIt[sp1C] - 1) << 8) | 0xB | (sp1C << 0x10)), 1);
      if ((saveLevel != 0) && (playerNumber == sp1C)) {
        osSendMesg(&D_hd_front_end_80219EF8, (void *) (((saveLevel - 1) << 8) | 0xD | (playerNumber << 0x10)), 1);
        saveLevel = 0;
      }
      osSendMesg(&D_hd_front_end_80219EF8, (void *) ((sp1C << 0x10) | 0x15 | 0x01000000), 1);
      osRecvMesg(&D_hd_front_end_80219F50, NULL, 1);
      saveIt[sp1C] = 0;
    }
  }
}

void func_hd_front_end_801ECE9C(void) {
  s32 sp4;

  for (sp4 = 0; sp4 < 0x3C; sp4++) {
    if (D_hd_code_802E8F94[sp4].unk0 & 0x81) {
      if ((players[playerNumber].unk91 >= 0xB) && (D_hd_code_80364A98 == 0x4000)) {
        D_hd_code_802E8F94[sp4].unk0 = 0x80;
      } else {
        D_hd_code_802E8F94[sp4].unk0 = 1;
      }
    }
  }
}

void func_hd_front_end_801ECF5C(void) {
    UnknownData8024C414 *sp6C  = &players[playerNumber];
    u16 sp4C[16];
    struct S_80367C04 *sp48;
    u8 sp40[5] = D_hd_front_end_8020849C;
    u8 sp3F;
    u16 sp3C;
    s32 sp38;
    s32 sp34;
    u16 sp32;
    u8 sp31;
    u8 sp30;

    sp3C = sp6C->unkA;
    func_hd_front_end_801ED480(D_hd_code_80364EF0[playerNumber], sp4C);
    if (saveIt[playerNumber] == 0) {
        rmonPrintf(ASSERT_MESSAGE, "saveIt[playerNumber]", "player.c", 0x568);
    }
    for (sp30 = 0; sp30 < 0x3C; sp30++) {
        if (((players[playerNumber].unk18[sp30] > 0) && (players[playerNumber].unk18[sp30] < 6)?1:0) != 0) {
            if ((D_hd_code_802E8F94[sp30].unk0 == 1) && (sp30 != 0x31) && (sp30 != 0x2F) && (sp30 != 0x26)) {
                sp48 = &D_hd_code_802E8F94[sp30];
                if (saveIt[playerNumber] != (sp30 + 1)) {
                    osSendMesg(&D_hd_front_end_80219EF8, (void *) ((sp30 << 8) | 8 | (playerNumber << 0x10) | 0x01000000), 1);
                    osRecvMesg(&D_hd_front_end_80219F50, NULL, 1);
                } else {
                    func_hd_front_end_801ED480(sp4C, D_hd_code_80364EF0[playerNumber]);
                }
                sp32 = D_hd_code_80364EF0[playerNumber][D_hd_code_802E8C44[0]];
                rmonPrintf("level %d time is %d\n", sp30, sp32);
                sp31 = func_hd_front_end_801EF2BC(sp32, sp30, players[playerNumber].unk91);
                sp6C->unk18[sp30] = sp31;
                ((u8 *) &sp40)[sp31 - 1]++;
            }
        }
    }
    func_hd_front_end_801ED480(sp4C, D_hd_code_80364EF0[playerNumber]);
    levelno = 0;
    rmonPrintf(" %d %d %d %d %d\n", sp40[2] * 3, sp40[1] * 2, sp40[0], sp6C->unkA, sp3C);
    sp6C->unkA += (sp40[2] * 3) + (sp40[1] * 2) + sp40[0];
    sp3F = (sp6C->unkA / 12) - (sp3C / 12);
    sp6C->unkC += sp3F;
    rmonPrintf("%d stars\n", sp3F);

    sp34 = (0x140 - (sp3F << 5)) / 2 + 0x28;
    for (sp38 = 0; sp38 < sp3F; sp38++, sp34 += 0x20) {
        D_hd_front_end_8020C070[189 + sp38].unk0 |= 0x100;
        D_hd_front_end_8020C070[189 + sp38].unk2 = sp34;
        D_hd_front_end_8020C070[189 + sp38].unk14 = 0x33;

    }
    for (; sp38 < 6; sp38++) {
        D_hd_front_end_8020C070[189 + sp38].unk0 &= ~0x100;
        D_hd_front_end_8020C070[189 + sp38].unk14 = 0;
    }
    for (sp38 = 0; sp38 < 3; sp38++) {
        sprintf(&D_hd_front_end_80215480[sp38 * 0x10], "*******%-2d**", ((u8 *) &sp40)[2 - sp38]);
        D_hd_front_end_8020C070[185 + sp38].unkC = &D_hd_front_end_80215480[sp38 * 0x10];
    }
}

void func_hd_front_end_801ED480(u8* arg0, u8* arg1) {
  u32 sp4;

  for(sp4 = 0; sp4 < 0x20; sp4++) {
    arg1[sp4] = arg0[sp4];
  }
}

void func_hd_front_end_801ED4B8(void) {
  UnknownData8024C414 *sp54;
  u16 sp34[16];
  struct S_80367C04 *sp30;
  u8 sp2F;
  u16 sp2C;
  s32 pad28;
  u8 sp27;
  u8 sp26;

  sp54 = &players[playerNumber];
  sp2C = sp54->unkA;
  func_hd_front_end_801ED480(D_hd_code_80364EF0[playerNumber], sp34);
  if (saveIt[playerNumber] == 0) {
    rmonPrintf(ASSERT_MESSAGE, "saveIt[playerNumber]", "player.c", 0x5C0);
  }
  for (sp26 = 0; sp26 < 0x3C; sp26++) {
    if ((((players[playerNumber].unk18[sp26] > 0) && (players[playerNumber].unk18[sp26] < 6)?1:0) != 0) && (sp26 != 0x31) && (sp26 != 0x2F) && (sp26 != 0x26)) {
      sp30 = &D_hd_code_802E8F94[sp26];
      if (saveIt[playerNumber] != (sp26 + 1)) {
        osSendMesg(&D_hd_front_end_80219EF8, (void *) ((sp26 << 8) | 8 | (playerNumber << 0x10) | 0x01000000), 1);
        osRecvMesg(&D_hd_front_end_80219F50, NULL, 1);
      } else {
        func_hd_front_end_801ED480(sp34, D_hd_code_80364EF0[playerNumber]);
      }
      sp27 = func_hd_front_end_801EF2BC(D_hd_code_80364EF0[playerNumber][D_hd_code_802E8C44[players[playerNumber].unk92[sp26]]], sp26, players[playerNumber].unk91 + 1);
      sp54->unk18[sp26] = sp27;
      if (sp27 == 4) {
        sp54->unkA++;
      }
    }
  }
  func_hd_front_end_801ED480((u8*)sp34, (u8*)D_hd_code_80364EF0[playerNumber]);
  levelno = 0;
  sp2F = (sp54->unkA / 12) - (sp2C / 12);
  sp54->unkC += sp2F;
  rmonPrintf("cmo destroy %d stars\n", sp2F);
}
