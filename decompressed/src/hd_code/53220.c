#include "common.h"
#include "functions.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"
#include "yoshi.h"

u8 func_hd_code_80297F74();                         /* extern */
extern u8 D_hd_code_8039CAD0;
extern u8 D_hd_code_802FF180[6];
extern char* D_hd_code_802FF188[][20][2];
extern u8 D_hd_code_802FF5E8[];
struct S_8036BB24 {
    u16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u8* unkC;
    char* unk10;
    u8 unk14;
    u8 pad15;
    s16 unk16;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
}; // Size: 0x1C
extern struct S_8036BB24* D_hd_code_8036BB24; // 21 elements

// Later data for text
extern u16 D_hd_code_80303B9C[];
extern u16 D_hd_code_80303BB4[];
extern u16 D_hd_code_80303BC8[];
extern u16 D_hd_code_80303BCC[];
extern u16 D_hd_code_80303BD0[];
extern u16 D_hd_code_80303BE4[];
extern u16 D_hd_code_80303BF8[];
extern u16 D_hd_code_80303C14[];
extern u16 D_hd_code_80303C18[];
extern u16 D_hd_code_80303C2C[];
extern u16 D_hd_code_80303C48[];
extern u16 D_hd_code_80303C4C[];
extern u16 D_hd_code_80303C50[];
extern u16 D_hd_code_80303C5C[];
extern u16 D_hd_code_80303C70[];
extern u16 D_hd_code_80303C74[];
extern u16 D_hd_code_80303C78[];
extern u16 D_hd_code_80303C88[];
extern u16 D_hd_code_80303C98[];
extern u16 D_hd_code_80303CAC[];
extern u16 D_hd_code_80303CB0[];
extern u16 D_hd_code_80303CC0[];
extern u16 D_hd_code_80303CD8[];
extern u16 D_hd_code_80303CF0[];
extern u16 D_hd_code_80303CF4[];
extern u16 D_hd_code_80303D0C[];
extern u16 D_hd_code_80303D28[];
extern u16 D_hd_code_80303D40[];
extern u16 D_hd_code_80303D44[];
extern u16 D_hd_code_80303D58[];
extern u16 D_hd_code_80303D70[];
extern u16 D_hd_code_80303D80[];
extern u16 D_hd_code_80303D98[];
extern u16 D_hd_code_80303DA4[];
extern u16 D_hd_code_80303DA8[];
extern u16 D_hd_code_80303DAC[];
extern u16 D_hd_code_80303DC0[];
extern u16 D_hd_code_80303DDC[];
extern u16 D_hd_code_80303DE0[];
extern u16 D_hd_code_80303DE4[];
extern u16 D_hd_code_80303DFC[];
extern u16 D_hd_code_80303E14[];
extern u16 D_hd_code_80303E18[];
extern u16 D_hd_code_80303E30[];
extern u16 D_hd_code_80303E48[];
extern u16 D_hd_code_80303E60[];
extern u16 D_hd_code_80303E70[];
extern u16 D_hd_code_80303E84[];
extern u16 D_hd_code_80303E88[];
extern u16 D_hd_code_80303E8C[];
extern u16 D_hd_code_80303EA0[];
extern u16 D_hd_code_80303EB8[];
extern u16 D_hd_code_80303EBC[];
extern u16 D_hd_code_80303ED0[];
extern u16 D_hd_code_80303EE4[];
extern u16 D_hd_code_80303EF4[];
extern u16 D_hd_code_80303EF8[];
extern u16 D_hd_code_80303F14[];
extern u16 D_hd_code_80303F18[];
extern u16 D_hd_code_80303F1C[];
extern u16 D_hd_code_80303F20[];
extern u16 D_hd_code_80303F24[];
extern u16 D_hd_code_80303F28[];
extern u16 D_hd_code_80303F34[];
extern u16 D_hd_code_80303F4C[];
extern u16 D_hd_code_80303F50[];
extern u16 D_hd_code_80303F54[];
extern u16 D_hd_code_80303F6C[];
extern u16 D_hd_code_80303F84[];
extern u16 D_hd_code_80303F88[];
extern u16 D_hd_code_80303F8C[];
extern u16 D_hd_code_80303F9C[];
extern u16 D_hd_code_80303FB0[];
extern u16 D_hd_code_80303FB4[];
extern u16 D_hd_code_80303FB8[];
extern u16 D_hd_code_80303FD4[];
extern u16 D_hd_code_80303FF0[];
extern u16 D_hd_code_80303FF4[];
extern u16 D_hd_code_80303FF8[];
extern u16 D_hd_code_80303FFC[];
extern u16 D_hd_code_80304000[];
extern u16 D_hd_code_80304004[];
extern u16 D_hd_code_8030401C[];
extern u16 D_hd_code_8030402C[];
extern u16 D_hd_code_80304030[];
extern u16 D_hd_code_80304034[];
extern u16 D_hd_code_8030404C[];
extern u16 D_hd_code_80304064[];
extern u16 D_hd_code_80304080[];
extern u16 D_hd_code_80304084[];
extern u16 D_hd_code_80304094[];
extern u16 D_hd_code_803040A4[];
extern u16 D_hd_code_803040A8[];
extern u16 D_hd_code_803040AC[];
extern u16 D_hd_code_803040B0[];
extern u16 D_hd_code_803040B4[];
extern u16 D_hd_code_803040CC[];
extern u16 D_hd_code_803040DC[];
extern u16 D_hd_code_803040E0[];
extern u16 D_hd_code_803040E4[];
extern u16 D_hd_code_803040F4[];
extern u16 D_hd_code_80304108[];
extern u16 D_hd_code_80304118[];
extern u16 D_hd_code_8030411C[];
extern u16 D_hd_code_80304138[];
extern u16 D_hd_code_80304154[];
extern u16 D_hd_code_80304164[];
extern u16 D_hd_code_80304168[];
extern u16 D_hd_code_8030417C[];
extern u16 D_hd_code_80304190[];
extern u16 D_hd_code_803041A8[];
extern u16 D_hd_code_803041AC[];
extern u16 D_hd_code_803041B0[];
extern u16 D_hd_code_803041B4[];

// <data>
u8 D_hd_code_802FF180[6] = {
  0x04, 0x0A, 0x0D, 0x21, 0x0E, 0x11
};

char* D_hd_code_802FF188[7][20][2] = {
  {
    { "WELL, IT'S ABOUT TIME!", D_hd_code_80303B9C },
    { "DOES IT LOOK LIKE I'M", D_hd_code_80303BB4 },
    { "ENJOYING MYSELF HERE?", D_hd_code_80303BC8 },
    { " ", D_hd_code_80303BCC },
    { "AND YOU'VE STILL GOT", D_hd_code_80303BD0 },
    { "0 OF THE OTHERS", D_hd_code_80303BE4 },
    { "LEFT TO TRACK DOWN.", D_hd_code_80303BF8 },
    { " ", D_hd_code_80303C14 },
    { "VISIT GLORY CROSSING -", D_hd_code_80303C18 },
    { "THERE'S BOUND TO BE", D_hd_code_80303C2C },
    { "ONE HOLED UP THERE.", D_hd_code_80303C48 },
    { " ", D_hd_code_80303C4C },
    { "IT SHOULDN'T TAKE YOU", D_hd_code_80303C50 },
    { "TOO LONG TO FIND HIM.", D_hd_code_80303C5C },
    { " ", D_hd_code_80303C70 },
    { " ", D_hd_code_80303C74 },
    }, {
    { "THIS IS IT, I TELL YOU!", D_hd_code_80303C78 },
    { "THE END! WE'RE ALL", D_hd_code_80303C88 },
    { "GOING TO ... OH.", D_hd_code_80303C98 },
    { " ", D_hd_code_80303CAC },
    { "WHAT ABOUT THE REST", D_hd_code_80303CB0 },
    { "OF MY FRIENDS?", D_hd_code_80303CC0 },
    { "ONLY 0 MORE LEFT ...", D_hd_code_80303CD8 },
    { " ", D_hd_code_80303CF0 },
    { "WANT TO MAKE AN", D_hd_code_80303CF4 },
    { "EXTRA SUBWAY STOP", D_hd_code_80303D0C },
    { "AT ARGENT TOWERS?", D_hd_code_80303D28 },
    { " ", D_hd_code_80303D40 },
    { "JUST KEEP YOUR EYE", D_hd_code_80303D44 },
    { "ON THE MARKER.", D_hd_code_80303D58 },
    { "I HOPE THAT HELPS!", D_hd_code_80303D70 },
      }, {
    { "YOU'VE MANAGED TO KEEP", D_hd_code_80303D80 },
    { "THE CARRIER SAFE? THAT'S", D_hd_code_80303D98 },
    { "PRETTY GOOD GOING!", D_hd_code_80303DA4 },
    { " ", D_hd_code_80303DA8 },
    { "ALL WE HAVE TO DO NOW IS", D_hd_code_80303DAC },
    { "TRACK DOWN THE OTHER 0.", D_hd_code_80303DC0 },
    { " ", D_hd_code_80303DDC },
    { "I'M SURE I REMEMBER", D_hd_code_80303DE0 },
    { "HEARING ONE HAD MOVED", D_hd_code_80303DE4 },
    { "TO THE EBONY COAST...", D_hd_code_80303DFC },
    { " ", D_hd_code_80303E14 },
    { "YOU'LL HAVE TO STRIKE", D_hd_code_80303E18 },
    { "OUT AHEAD AND GET ", D_hd_code_80303E30 },
    { "AIRBORNE TO FIND HIM.", D_hd_code_80303E48 },
        }, {
    { "WHERE'S EVERYONE GONE?", D_hd_code_80303E60 },
    { "THERE WAS A LOT OF FUSS", D_hd_code_80303E70 },
    { "OUT THERE A WHILE BACK.", D_hd_code_80303E84 },
    { " ", D_hd_code_80303E88 },
    { "WHAT'S THAT? YOU'VE", D_hd_code_80303E8C },
    { "GOT 0 OF MY FRIENDS", D_hd_code_80303EA0 },
    { "LEFT TO FIND?", D_hd_code_80303EB8 },
    { " ", D_hd_code_80303EBC },
    { "I KNOW ONE OF THEM", D_hd_code_80303ED0 },
    { "LIVES AT TEMPEST CITY,", D_hd_code_80303EE4 },
    { " ", D_hd_code_80303EF4 },
    { "BUT THE NOISE IS TOO", D_hd_code_80303EF8 },
    { "MUCH FOR HIM.", D_hd_code_80303F14 },
    { " ", D_hd_code_80303F18 },
    { "HE LIKES TO GET ABOVE", D_hd_code_80303F1C },
    { "IT ALL AND SHUT", D_hd_code_80303F20 },
    { "HIMSELF AWAY.", D_hd_code_80303F24 },
    },{
    { "HELP? OF COURSE I'LL", D_hd_code_80303F28 },
    { "HELP. FINALLY, SOMEONE'S", D_hd_code_80303F34 },
    { "MAKING A STAND!", D_hd_code_80303F4C },
    { " ", D_hd_code_80303F50 },
    { "THIS IS GOING TO TAKE", D_hd_code_80303F54 },
    { "ALL SIX OF US, SO", D_hd_code_80303F6C },
    { "YOU'LL NEED 0 MORE.", D_hd_code_80303F84 },
    { " ", D_hd_code_80303F88 },
    { " ", D_hd_code_80303F8C },
    { "TRY OYSTER HARBOR.", D_hd_code_80303F9C },
    { " ", D_hd_code_80303FB0 },
    { " ", D_hd_code_80303FB4 },
    { "THIS UPROAR HAS LEFT", D_hd_code_80303FB8 },
    { "MY COLLEAGUE THERE", D_hd_code_80303FD4 },
    { "ALL OUT AT SEA,", D_hd_code_80303FF0 },
    { " ", D_hd_code_80303FF4 },
    { "BUT YOU MUSTN'T LET", D_hd_code_80303FF8 },
    { "ANYTHING STAND IN", D_hd_code_80303FFC },
    { "YOUR WAY!", D_hd_code_80304000 }
    }, {
    { "WELL, IT'S GOOD TO SEE", D_hd_code_80304004 },
    { "SOME NEW FACES! DON'T", D_hd_code_8030401C },
    { "MIND ME, LET'S MOVE OUT.", D_hd_code_8030402C },
    { " ", D_hd_code_80304030 },
    { "0 OF THE OTHER CHAPS", D_hd_code_80304034 },
    { "LEFT TO FIND, AFTER ALL.", D_hd_code_8030404C },
    { " ", D_hd_code_80304064 },
    { " ", D_hd_code_80304080 },
    { "I EXPECT THEY'VE DUCKED", D_hd_code_80304084 },
    { "FOR COVER UNDERGROUND", D_hd_code_80304094 },
    { "AT IRONSTONE MINE...", D_hd_code_803040A4 },
    { " ", D_hd_code_803040A8 },
    { "YOU MIGHT NEED", D_hd_code_803040AC },
    { "TO BLAST YOUR WAY DOWN.", D_hd_code_803040B0 }
    }, {
    { "I CAN HARDLY BELIEVE", D_hd_code_803040B4 },
    { "THE WORLD'S STILL IN", D_hd_code_803040CC },
    { "ONE PIECE!", D_hd_code_803040DC },
    { " ", D_hd_code_803040E0 },
    { "STILL, AT LEAST NOW", D_hd_code_803040E4 },
    { "WE'RE ALL BACK", D_hd_code_803040F4 },
    { "TOGETHER ...", D_hd_code_80304108 },
    { " ", D_hd_code_80304118 },
    { "MAYBE WE FINALLY", D_hd_code_8030411C },
    { "STAND A CHANCE OF", D_hd_code_80304138 },
    { "CLEARING UP THIS MESS.", D_hd_code_80304154 },
    { " ", D_hd_code_80304164 },
    { "NO TIME TO LOSE. LET'S", D_hd_code_80304168 },
    { "HEAD FOR THE DETONATION ", D_hd_code_8030417C },
    { "SITE AND GET SET UP.", D_hd_code_80304190 },
    { " ", D_hd_code_803041A8 },
    { "WHEN IT COMES TO THE", D_hd_code_803041AC },
    { "CRUNCH, EVERYTHING'S", D_hd_code_803041B0 },
    { "GOING TO DEPEND ON US.", D_hd_code_803041B4 }
  }
};
u8 D_hd_code_802FF5E8[72] = {
  0x01, 0x05, 0x09, 0x0D, 0x00, 0x01, 0x05, 0x09,
  0x0E, 0x00, 0x01, 0x05, 0x08, 0x0C, 0x00, 0x01,
  0x05, 0x09, 0x0C, 0x0F, 0x01, 0x05, 0x09, 0x0D,
  0x11, 0x01, 0x05, 0x09, 0x0D, 0x00, 0x01, 0x05,
  0x09, 0x0D, 0x11, 0x00, 0x01, 0x05, 0x09, 0x0D,
  0x00, 0x01, 0x05, 0x09, 0x0D, 0x00, 0x01, 0x05,
  0x09, 0x0C, 0x00, 0x01, 0x05, 0x08, 0x0B, 0x0E,
  0x01, 0x05, 0x09, 0x0D, 0x11, 0x01, 0x05, 0x09,
  0x00, 0x00, 0x01, 0x05, 0x09, 0x0D, 0x00, 0x00
};
// </data>

void func_hd_code_802979E0(u8 arg0) {
    struct S_802F8BDC* sp4C;
    struct S_8036BB24* sp48;
    struct S_80367BCC* sp44;
    u8 sp43;
    u8 sp42;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    u8 sp2F;


    sp4C = &D_hd_code_802F8BDC[0x15];
    sp43 = func_hd_code_80297F74();
    sp42 = 0;
    if ((sp43 == 1) && (func_hd_code_80297EF8((s32) (u8) arg0) == 0)) {
        sp43 -= 1;
    }
    if (sp43 == 0) {
        D_hd_code_8039CAD0 = 6;
    } else {
        sp2F = 0;
        sp3C = (s32) D_hd_code_8039CAB6;
        while((sp3C < (D_hd_code_8039CAB6 + 6)) && (sp2F == 0)) {
            if ((func_hd_code_80297EF8(D_hd_code_802FF180[sp3C % 6]) == 0) && (D_hd_code_802FF180[sp3C % 6] != (u8) arg0)) {
                sp2F = 1;
            } else {
                sp3C += 1;
            }
        }
        D_hd_code_8039CAD0 = (u8) (sp3C % 6);
    }
    D_hd_code_8036BB24 = (struct S_8036BB24*)D_hd_code_80358070;
    D_hd_code_80358070 += 0x24C;




    for (sp3C = 0,  sp34 = 0, sp30 = 0, sp2F = 0; (sp3C < 0x14) && (sp2F == 0); sp3C++) {
        char* sp24 = D_hd_code_802FF188[D_hd_code_8039CAD0][sp3C][0];
        char* sp28 = D_hd_code_802FF188[D_hd_code_8039CAD0][sp3C][1];
        sp48 = &D_hd_code_8036BB24[sp3C];
        if (sp24 != NULL) {
            sp30 += 1;
            sp48->unk0 = 0x1020;
            if (D_hd_code_802FF5E8[(D_hd_code_8039CAD0 * 5) + sp34] == sp3C) {
                sp48->unk0 |= 1;
                sp34 += 1;
            }
            sp48->unk4 = (s16) (sp3C * 0x10);
            sp48->unk6 = 0x10;
            sp48->unk8 = 0x10;
            sp48->unkC = sp24;
            sp48->unk10 = sp28;
            sp48->unk14 = 0U;
            sp48->unk16 = 0;
            sp48->unk18 = 7;
            sp48->unk19 = 7;
            sp48->unk1A = 0U;
        } else {
            sp2F = 1;
        }
    }

    sp48 = &D_hd_code_8036BB24[sp30];
    sp48->unkC = 0;
    sp48->unk10 = 0;
    sp48->unk0 = 0x400;
    sp48->unk2 = -0x20;
    sp48->unk4 = 0x26;
    sp48->unk14 = 0x18U;
    sp48->unk1A = 0;
    sp48->unk16 = (s16) sp48->unk1A;
    sp44 = &D_hd_code_802F49F4[sp48->unk14];
    sp48->unk1A = func_hd_code_80272C5C(sp44->unk6, 0, sp44->unk4, sp44->unk2C, sp44->unk2D | 4, 1.0f);
    sp4C->unk10 = sp30 + 1;
    sp4C->unk18 = D_hd_code_802FF5E8[D_hd_code_8039CAD0 * 5];
    if (func_hd_code_80297EF8((s32) (u8) arg0) == 0) {
        sp43 -= 1;
    }
    for(sp3C = 0; sp3C < sp4C->unk10 && sp42 == 0; sp3C++) {
        sp48 = &D_hd_code_8036BB24[sp3C];
        sp38 = 0;
        while ((sp38 < func_hd_code_8025B300(sp48->unkC)) && (sp42 == 0)) {
            // This seem to replace a 0 with sp43 as a stringified number
            if (((s32) sp48->unkC[sp38] >= 0x30) && ((s32) sp48->unkC[sp38] < 0x36)) {
                sp48->unkC[sp38] = sp43 + 0x30;
                sp42 = 1;
            }
            sp38 += 1;
        }
    }
}

void func_hd_code_80297ECC(void) {
  D_hd_code_802F8BDC[0x15].unk18 = D_hd_code_802FF5E8[D_hd_code_8039CAD0 * 5];
}

u8 func_hd_code_80297EF8(u8 arg0) {
  u8 sp27;
  u8 sp26;

  sp26 = func_hd_code_8029766C(arg0, &sp27);
  return sp26 && (players[playerNumber].unk90 & (1 << sp27)) ? 1 : 0;
}

u8 func_hd_code_80297F74(void) {
  s32 sp4;
  s32 sp0 = 6;

  for(sp4 = 0; sp4 < 6; sp4++) {
    if (players[playerNumber].unk90 & (1 << sp4)) {
      sp0--;
    }
  }

  return sp0;
}
