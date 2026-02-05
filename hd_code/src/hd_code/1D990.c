#include "common.h"
#include "variables.h"
#include "functions.h"
#include "structs.h"

Gfx* func_hd_code_80264264(s32 arg0, Gfx* arg1);
s32 func_hd_code_80272ED8(s32, s32, u8, s32, s32, s32, f32); /* extern */
s32 func_hd_code_80274868(s32);                     /* extern */
s32 func_hd_code_80274AA4(s32);                     /* extern */
extern u8 D_80367BB0[];
struct S_80367BCC {
  u8 pad0[0x1A];
  u8 unk1A;
  u8 unk1B[0x26 - 0x1B];
  u8 unk26;
};
extern struct S_80367BCC* D_80367BCC;
extern struct S_80367BCC* D_80367BD0;
extern u8 D_80367BD4;
extern u8 D_80367BD5;
extern s16 D_80367BD8;
extern u16 D_80367BF4;

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1D990/func_hd_code_80262150.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1D990/func_hd_code_802621DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1D990/func_hd_code_80262238.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1D990/func_hd_code_80262320.s")

void func_hd_code_80262840(void) {
    s32 sp34;
    u16 sp32;
    u16 sp30;

    sp34 = (D_803156C4 - D_80367BC0) / 60U;
    if (sp34 != D_80367BC4) {
        switch (sp34) {                             /* switch 1 */
        case 0:                                     /* switch 1 */
            D_80367C68[0] = 0xFFF;
            D_80367CB8[0] = 0xFFF;
            switch ((u32) D_80364AA8) {             /* switch 2; irregular */
            case 0x2:                               /* switch 2 */
                proutSprintf(&D_80367C18, "FINISH %d LAPS IN", D_80367C04->unk18);
                break;
            case 0x4:                               /* switch 2 */
            case 0x20:                              /* switch 2 */
                if (levelno == 0x34) {
                    proutSprintf(&D_80367C18, "DESTROY TARGETS IN");
                } else {
                    proutSprintf(&D_80367C18, "DESTROY %s IN", D_80367C08);
                }
                break;
            case 0x80:                              /* switch 2 */
                if (levelno == 0x32) {
                    proutSprintf(&D_80367C18, "CLEAR SHUTTLE PATH");
                } else {
                    proutSprintf(&D_80367C18, "CLEAR CARRIER PATH");
                }
                break;
            case 0x8:                               /* switch 2 */
                proutSprintf(&D_80367C18, "CAUSE $%d DAMAGE", D_80367C04->unk18);
                break;
            case 0x10:                              /* switch 2 */
            case 0x40:                              /* switch 2 */
                proutSprintf(&D_80367C18, "FIND %d RDUS IN", D_80367C04->unk18);
                break;
            }
            sp32 = D_80367C04->unk36 / 600;
            sp30 = ((s32) D_80367C04->unk36 / 10) % 60;
            proutSprintf(&D_80367C40, "%d MINUTE%c %d SECONDS", sp32, D_hd_code_802E9FA0[sp32 != 1], sp30);
            D_hd_code_802F5804[0x24].unkC = &D_80367C18;
            D_hd_code_802F5804[0x25].unkC = &D_80367C40;
            D_hd_code_802F5804[0x24].unk10 = &D_80367C68;
            D_hd_code_802F5804[0x25].unk10 = &D_80367CB8;
            func_hd_code_8026AF6C(0x8009U);
            sndPlaySfx(D_80367738, func_hd_code_8026205C(0), 0);
            break;
        case 1:                                     /* switch 1 */
            sndPlaySfx(D_80367738, 0x96, 0);
            break;
        case 2:                                     /* switch 1 */
            sndPlaySfx(D_80367738, 0x96, 0);
            break;
        case 3:                                     /* switch 1 */
            sndPlaySfx(D_80367738, 0x96, 0);
            break;
        case 4:                                     /* switch 1 */
            sndPlaySfx(D_80367738, 0x99, 0);
            break;
        }
    }
    D_80367BC4 = sp34;
    if ((sp34 == 4) && (D_8035805C == D_803156F4)) {
        D_80364A98 = 4;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1D990/func_hd_code_80262BF4.s")

void func_hd_code_80262FD0(void) {
  if ((u16) D_8036EA7C >= (u32) D_80367C04->unk18) {
    D_803643DA = 1;
  }
  proutSprintf(D_80367B60[0], "%d/%d", D_8036EA7C, D_80367C04->unk18);
}

void func_hd_code_8026303C(void) {
  s16 sp1E;

  func_hd_code_802C1DD0(0);
  if (D_8036EA78 >= D_80367C04->unk18) {
    D_803643DA = 1;
  }
  if (D_8036DCD4 != 0) {
    func_hd_code_8027EED8(D_hd_code_803643E0 >> 5, D_hd_code_803643E8 >> 5, &sp1E);
    if (sp1E > (D_hd_code_803643E4 >> 5)) {
      D_803643D9 = 1;
    }
  } else if (D_80367C04->unk24 > (D_hd_code_803643E4 >> 5)) {
    D_803643D9 = 1;
  }
  proutSprintf(D_80367B60[0], "%d/%d", D_8036EA78, D_8036EB92);
}

void func_hd_code_80263140(void) {
  s16 sp2E;

  func_hd_code_802C1DD0(1);
  switch (D_80364AA8) {                           /* switch 1; irregular */
    case 0x20:                                      /* switch 1 */
      if (D_8036EA78 >= D_8036EB92) {
        D_803643DA = 1;
      }
      break;
    case 0x80:                                      /* switch 1 */
      if ((D_803F7806 != 0) || (levelno == 0x32 && D_8036EA78 >= D_8036EB92)) {
        D_803643DA = 1;
      }
      break;
  }
  if (D_8036DCD4 != 0) {
    func_hd_code_8027EED8(D_hd_code_803643E0 >> 5, D_hd_code_803643E8 >> 5, &sp2E);
    if (sp2E > D_hd_code_803643E4 >> 5) {
      D_803643D9 = 1;
    }
  } else if (D_80367C04->unk24 > D_hd_code_803643E4 >> 5) {
    D_803643D9 = 1;
  }
  switch (D_80364AA8) {                           /* switch 2; irregular */
    case 0x20:                                      /* switch 2 */
      proutSprintf(D_80367B60[0], "%d/%d", D_8036EA78, D_8036EB92);
      return;
    case 0x80:                                      /* switch 2 */
      if (levelno == 0x32) {
        proutSprintf(D_80367B60[0], "%d/%d", D_8036EA78, D_8036EB92);
        return;
      }
      proutSprintf(D_80367B60[0], "%d/%d", func_hd_code_802C1B1C() , D_8036EB92);
      return;
  }
}


void func_hd_code_80263358(void) {
  s32 sp1C;
  s32 temp_t3;

  func_hd_code_802C1DD0(0);
  if ((u32) D_8036EA70 >= (u32) D_80367C04->unk18) {
    D_803643DA = 1;
  }
  sp1C = (s32)D_80367C04->unk18 - (s32)D_8036EA70;
  if (sp1C < 0) {
    sp1C = 0;
  }
  proutSprintf(D_80367B60[0], "$%d LEFT", sp1C);
}

void func_hd_code_802633E0(void) {
    s32 sp34;
    u8 sp33;

    if (D_80367B54 == 0) {
        if (func_hd_code_8026394C((s32) D_hd_code_803643E0 >> 5, (s32) D_hd_code_803643E8 >> 5, D_80367C04->unkA, D_80367C04->unkC, (s32) D_80367C04->unkE, (s32) D_80367C04->unk10) != 0) {
            D_80367B54 = 1;
            D_80367BF8.unk0 = 0U;
            D_80367BF8.unk1 = D_80367C04->unk12[0];
            D_80367BBC = D_803156C0;
            D_80367BFB = 1;
            D_80367BFC = 0xFFFF;
        }
    } else {
        D_80367BFA = ((D_hd_code_803643E8 >> 5) - D_80367C04->unk4) / ((D_80367C04->unk8 - D_80367C04->unk4) >> 1);
        D_80367BFA *= 2;
        D_80367BFA = D_80367BFA + ((s32) (((s32) D_hd_code_803643E0 >> 5) - D_80367C04->unk2) / (s32) ((s32) (D_80367C04->unk6 - D_80367C04->unk2) >> 1));
        D_80367B56[D_80367B54] = func_hd_code_8028604C(D_803156C0 - D_80364A58);
        for(sp34 = D_80367B54 - 2; sp34 >= 0; sp34--) {
                D_80367B58[D_80367B54-1] = D_80367B58[D_80367B54-1] - D_80367B58[sp34];

        }
        if (D_80370C28 & 0x2000) {
            func_hd_code_8029A7E4("box number=%d\n", D_80367BFA);
        }
        if (D_80367BF8.unk0 == 4) {
            if (func_hd_code_8026394C((s32) D_hd_code_803643E0 >> 5, (s32) D_hd_code_803643E8 >> 5, D_80367C04->unkA, D_80367C04->unkC, (s32) D_80367C04->unkE, (s32) D_80367C04->unk10) != 0) {
                if ((s32) D_80367B56[D_80367B54] < (s32) D_80367BFC) {
                    func_hd_code_8029A7E4("new best lap %d %d\n", D_80367BFC, D_80367B56[D_80367B54]);
                    D_80367BFB = D_80367B54;
                    D_80367BFC = D_80367B56[D_80367B54];
                }
                if ((u32) (D_80367C04->unk18 - 1) < (u8) D_80367B54) {
                    D_803643DA = 1;
                } else {
                    sp33 = D_80367C04->unk18 - D_80367B54;
                    if (D_hd_code_802E8BD0 == 0) {
                        func_hd_code_8026AF6C(0x8008U);
                    }
                    if (sp33 == 1) {
                        proutSprintf(&D_80367D10, "1 LAP LEFT!");
                    } else {
                        proutSprintf(&D_80367D10, "%d LAPS LEFT!", sp33);
                    }
                    D_hd_code_802F5804[0x23].unkC  = &D_80367D10;
                    D_hd_code_802F5804[0x23].unk10 = &D_80367D28;
                    func_hd_code_802D82A0(D_80367734, (s32) ((f64) func_hd_code_802D8260(D_80367734) * 0.95));
                }
                D_80367B54 += 1;
                D_80367BF8.unk0 = 0U;
            }
        } else if (D_80367C04->unk12[D_80367BF8.unk0] == D_80367BF8.unk1 && D_80367C04->unk12[(D_80367BF8.unk0 + 1) % 4] == D_80367BFA) {
            func_hd_code_8029A7E4("box cross: %d to %d\n", D_80367BF8.unk1, D_80367BFA);
            D_80367BF8.unk0 = (u8) (D_80367BF8.unk0 + 1);
        }
        D_80367BF8.unk1 = (u8) D_80367BFA;
    }
    for(sp34 = 0; sp34 < D_80367B54 && sp34 < D_80367C04->unk18; sp34++) {
        func_hd_code_80264A34(D_80367B60[sp34], D_80367B58[sp34], D_80367B54 == (sp34 + 1));
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1D990/func_hd_code_8026394C.s")


Gfx* func_hd_code_802639B4(Gfx* arg0, void* arg1, Gfx** arg2) {
    Gfx* entry; // sp64
    u32 sp60;
    u8 sp5F;
    u8 sp5E;
    u8 sp5D;
    u8 sp5C;
    s16 sp5A;
    s16 pad58;
    s32 pad54;
    s32 sp50;


    entry = arg0;
    if (((D_hd_code_80364A90 & 0x04000200)) && (D_8036BB18 != 0x1E)) {
        sp5A = 0xFF;
    } else {
        sp5A = D_80367BD6;
    }
    switch ((u32) D_80364AA8) {                     /* irregular */
    case 0x2:
        for(sp50 = 0; (sp50 < (D_80367B54 - ((D_hd_code_80364A90 & 0x440)?1:0))) && ((u32) sp50 < (u32) D_80367C04->unk18); sp50++) {
            if ((sp50 + 1 == D_80367BFB) && (sp50 + 1 != D_80367B54)) {
                func_hd_code_80259CCC(arg1, D_80367B60[sp50], NULL, 1U, 0, 0x18, (sp50 * 0x12) + 0x12, 0x14, 0x14, 1, 0xFF, 0, 0, (s32) D_80367BD6);
            } else if ((sp50 + 1) == D_80367B54) {
                func_hd_code_80259CCC(arg1, D_80367B60[sp50], NULL, 1U, 0, 0x18, (sp50 * 0x12) + 0x12, 0x14, 0x14, 1, 0xFF, 0xFF, 0xFF, (s32) D_80367BD6);
            } else {
                func_hd_code_80259CCC(arg1, D_80367B60[sp50], NULL, 1U, 0, 0x18, (sp50 * 0x12) + 0x12, 0x14, 0x14, 1, 0xA0, 0xA0, 0xA0, (s32) D_80367BD6);
            }
        }
        break;
    case 0x4:
    case 0x20:
    case 0x80:
        func_hd_code_80259CCC(arg1, D_80367B60[0], NULL, 1U, 0, 0x38, 0x14, 0x14, 0x14, 1, 0xFF, 0xFF, 0xFF, (s32) sp5A);
        break;
    case 0x8:
        func_hd_code_80259CCC(arg1, D_80367B60[0], NULL, 1U, 0, 0x1C, 0x12, 0x14, 0x14, 1, 0xFF, 0xFF, 0xFF, (s32) sp5A);
        break;
    case 0x10:
    case 0x40:
        func_hd_code_80259CCC(arg1, D_80367B60[0], NULL, 1U, 0, 0x38, 0x12, 0x14, 0x14, 1, 0xFF, 0xFF, 0xFF, (s32) sp5A);
        break;
    }
    sp5E = 0xFF;
    sp5F = 0;
    if ((D_hd_code_80364A90 & 0x04000104)) {
        sp5D = (s32) D_80367BF4 < 0xA;
        if (!sp5D) {
            sp5F = 0xFF;
        }
    } else {
        sp5D = 0;
        sp5F = 0xFF;
        sp5E = 0;
    }
    if (D_80367BF4 == 0) {
        sp5D = 0;
    }
    if ((sp5D == 0) || ((u32) ((u32) D_803156C4 % 20U) < 0x10U)) {
        if (D_80364AA8 == 2) {
            func_hd_code_80259CCC(arg1, D_80367BB0, NULL, 1U, 0, 0x18, (sp50 * 0x12) + 0x14, 0x10, 0x10, 1, (s32) sp5E, (s32) sp5F, 0, (s32) D_80367BD6);
        } else {
            func_hd_code_80259CCC(arg1, D_80367BB0, NULL, 1U, 0, 0x1C, D_80367BD8 + 0x2A, 0x10, 0x10, 1, (s32) sp5E, (s32) sp5F, 0, (s32) sp5A);
        }
    }
    if ((D_hd_code_803643D7 != 0) && (D_hd_code_80364A90 == 0x04000000)) {
        func_hd_code_8025E2CC(&entry, arg1, D_8035805C);
    }
    if (D_80367BC8 != 0) {
        entry = func_hd_code_80264264(arg1, entry);
    }
    entry = func_hd_code_80274868(entry);
    if (D_80367BCC != NULL) {
        entry = func_hd_code_80272ED8(entry, D_80367BCC->unk1B[(D_803156C4 / D_80367BCC->unk26) % D_80367BCC->unk1A] + D_80367BD4 - 1, 0x18, D_80367BD8 + 0xC, (s32) sp5A, 1, 1.0f);
    }
    if (D_80367BD0 != NULL) {
        entry = func_hd_code_80272ED8(entry, D_80367BD0->unk1B[(D_803156C4 / D_80367BD0->unk26) % D_80367BD0->unk1A] + D_80367BD5 - 1, 0x18, D_80367BD8 + 0xC, (s32) sp5A, 1, 1.0f);
    }
    entry = func_hd_code_80274AA4(entry);
    arg2 += entry - arg0;
    return entry;
}

void func_hd_code_8026420C(void) {
  if ((D_80367BFE != 0) && (D_80358064 == D_80367B50)) {
    func_hd_code_8029A7E4("Replay turbo ....\n");
    D_80367BFF = 1;
  }
}

Gfx* func_hd_code_80264264(s32 arg0, Gfx* arg1) {
    Gfx* entry;
    s32 sp78;
    s32 sp74;

    entry = arg1;
    switch (D_80367BC8) {
    case 1:
        D_80367D52.unk0 = 3U;
        D_80367BC8 = 2;
        break;
    case 2:
        D_80367D50 = ((u32) ((D_803156C4 - D_80367BC0) * 0x3C) / 60U) - 0x40;
        D_80367D52.unk0 = (u8) (3 - MAX(0, (s32) (D_80367D50 * 2) / 10));
        if (D_80367D50 >= 0xA) {
            D_80367D52.unk0 = 1U;
            D_80367D50 = 0xA;
            D_80367BC8 = 3;
        }
        break;
    case 3:
        if (D_hd_code_802E8BD0 == 0) {
            D_80367BC8 = 4;
        }
        if (D_80370C1C != 0) {
            D_80367C01 = 1;
        }
        break;
    case 4:
        D_80367D52.unk1 = (u8) D_80367D52.unk0;
        if ((u32) (D_803156C0 - D_80364A58) >= 7U) {
            D_80367D52.unk0 = 5U;
        } else {
            D_80367D52.unk0 = 4U;
        }
        if ((u32) (D_803156C0 - D_80364A58) >= 0x15U) {
            D_80367BC8 = 5;
            D_80367BFF = (s8) D_80367BFE;
            D_80367B50 = D_80358064;
        }
        if ((D_80367D52.unk1 == 1) && (D_80370C1C == 0)) {
            D_80367BFE = !D_80367C01;
        }
        if ((D_80367D52.unk1 == 4) && (D_80367D52.unk0 == 5) && (D_80370C1C == 0)) {
            D_80367BFE = 0;
        }
        break;
    case 5:
        D_80367D50 = 0xA - ((u32) ((((D_803156C0 - D_80364A58) << 1) * 0x3C ) - 0x960) / 60U);
        if (D_80367D50 < -0x3F) {
            D_80367BC8 = 0,
            func_hd_code_8029A7E4("turbo %d\n", D_80367BFE);
        }
        break;
    }
    if (D_80364AA8 != 0x80) {
        gDPPipeSync(entry++);
        gSPTexture(entry++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
        gDPSetTexturePersp(entry++, G_TP_NONE);
        gDPSetCycleType(entry++, G_CYC_1CYCLE);
        gDPSetRenderMode(entry++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
        gDPSetCombineLERP(entry++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor(entry++, 0, 0, 0x00, 0x00, 0x00, 0xFF);

        sp74 = 0x20;
        for(sp78 = 0; sp78 < 0x100; sp78+=0x20) {
            gDPSetTextureImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 256, D_80367BDC[D_80367D52.unk0]);
            gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, (((sp78 - sp78) * 2) + 0x47) >> 3, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
            gDPLoadSync(entry++);
            gDPLoadTile(entry++, G_TX_LOADTILE, sp78 * 4, 0, ((sp78 + 0x1F) << 2), qu102(63)); // qu102(63) = 0xFC?
            gDPPipeSync(entry++);
            gDPSetTile(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, (((sp78 - sp78) * 2) + 0x47) >> 3, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOLOD);
            gDPSetTileSize(entry++, G_TX_RENDERTILE, sp78 * 4, 0, (sp78 + 0x1F) << 2, qu102(63));

            gSPTextureRectangle(entry++, MAX((sp78 + sp74) << 2, 0), 0, MAX((sp78 + sp74 + 0x20) << 2, 0), MAX((D_80367D50 + 0x3F) << 2, 0), 0, ((sp78 << 5) - MIN((((sp78 + sp74) * 4) << 10) >> 7, 0)), -(D_80367D50 << 5), qs510(1), qs510(1))
        }
        gDPPipeSync(entry++);
        gDPSetTexturePersp(entry++, G_TP_PERSP);
    }
    return entry;
}


#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1D990/func_hd_code_80264A34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1D990/func_hd_code_80264AEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1D990/func_hd_code_80264BA4.s")
