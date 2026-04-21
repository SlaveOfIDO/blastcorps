#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"

s32 func_hd_code_8027BCF0(s16 arg0, s16 arg1, s16 arg2);
void func_hd_code_8027D350(s16 x1, s16 y1, s16 z1, s16 x2, s16 y2, s16 z2, Vtx* arg6, s32 arg7);
void func_hd_code_8027D5AC();                          /* extern */

struct S_802FC368_sub {
  s16 unk0;
  s16 unk2;
  s16 unk4;
  s16 unk6;
  s16 unk8;
  s16 unkA;
  s16 unkC;
  s16 unkE;
}; // size: 0x10

struct S_802FC368 {
  struct S_802FC368_sub *unk0; // first
  struct S_802FC368_sub *unk4; // last
  u8 unk8;
}; // Size: 0xC

struct S_8036D3D0 {
  s16 unk0;
  s16 unk2;
  s16 unk4;
  s16 unk6;
  s16 unk8;
  s16 unkA;
  s16 unkC;
  s16 unkE;
  s16 unk10;
  s16 unk12;
  s16 unk14;
  s16 unk16;
  u8 unk18;
  u8 unk19;
  u8 unk1A;
  u8 unk1B;
}; // Size: 0x1C


extern struct S_802FC368 D_hd_code_802FC360[11];
extern struct S_8036D3D0 D_8036D3D0[0x50];

extern u8 D_8036DC90;
extern u8 D_8036DC91;
extern u8 D_8036DC92;
extern u32 D_8036DC94;

s32 func_hd_code_8027BCF0(s16 arg0, s16 arg1, s16 arg2) {
  s32 index = 0;
  u8 found = 0;

  while(index <= 10 && !found) {
    if (D_hd_code_802FC360[index].unk8 == levelno) {
      found = 1;
    } else {
      index++;
    }
  }

  if (!found) {
    return 0;
  } else {
    struct S_802FC368_sub *current = D_hd_code_802FC360[index].unk0;
    struct S_802FC368_sub *last = D_hd_code_802FC360[index].unk4;

    while (current != last) {
      if (arg1 >= current->unkC &&
          arg1 <= current->unkE &&
          func_hd_code_802AC4C4(arg0, arg2, current->unk0, current->unk2, current->unk4, current->unk6, current->unk8, current->unkA)) {
        return 1;
          }
      current++;
    }
  }
  return 0;
}

void func_hd_code_8027BE4C(void) {
  s32 pad;

  D_8036DC90 = 0;
  D_8036DC91 = 0;
  D_8036DC92 = 0;
  D_8036DC94 = -1;
}

void func_hd_code_8027BE7C(u8 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s32 arg6, s32 arg7, s16 arg8, u8 arg9, u8 arg10, u8 arg11, u8 arg12) {
    f32 sp50[4][4];
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    s16 sp32;
    s16 sp30;
    s16 sp2E;
    s16 sp2C;

    if (func_hd_code_8027BCF0(arg6 >> 5, arg1 >> 5, arg7 >> 5) == 0) {
        guAlignF(sp50, ((f32) arg8 / 4095.0) * 360.0, 0.0f, 1.0f, 0.0f);
        guMtxXFMF(sp50, arg2, 0.0f, arg3, &sp4C, &sp3C, &sp48);
        guMtxXFMF(sp50, arg4, 0.0f, arg5, &sp44, &sp3C, &sp40);

        sp32 = (s32) (sp4C + arg6) >> 5;
        sp30 = (s32) (sp48 + arg7) >> 5;
        sp2E = (s32) (sp44 + arg6) >> 5;
        sp2C = (s32) (sp40 + arg7) >> 5;
        arg1 >>= 5;

        guMtxXFMF(sp50, arg9, 0.0f, 0.0f, &sp38, &sp3C, &sp34);
        if (((D_8036DC94 + 1) != D_hd_code_80358060) || (D_8036DC94 == -1U)) {
            D_8036D3D0[D_8036DC91].unk1A = 1;

            D_8036DC91++;
            if (D_8036DC91 == 0x50) {
                D_8036DC91 = 0;
            }
            if (D_8036DC91 == D_8036DC90) {
                D_8036DC90++;
                if (D_8036DC90 == 0x50) {
                    D_8036DC90 = 0;
                }
            }
        }

        D_8036D3D0[D_8036DC91].unk1B = arg12;

        D_8036D3D0[D_8036DC91].unk0 = sp32 + (s16)sp38;
        D_8036D3D0[D_8036DC91].unk2 = arg1;
        D_8036D3D0[D_8036DC91].unk4 = sp30 + (s16)sp34;
        D_8036D3D0[D_8036DC91].unk6 = sp32 - (s16)sp38;
        D_8036D3D0[D_8036DC91].unk8 = arg1;
        D_8036D3D0[D_8036DC91].unkA = sp30 - (s16)sp34;
        D_8036D3D0[D_8036DC91].unkC = sp2E + (s16)sp38;
        D_8036D3D0[D_8036DC91].unkE = arg1;
        D_8036D3D0[D_8036DC91].unk10 = sp2C + (s16)sp34;
        D_8036D3D0[D_8036DC91].unk12 = sp2E - (s16)sp38;
        D_8036D3D0[D_8036DC91].unk14 = arg1;
        D_8036D3D0[D_8036DC91].unk16 = sp2C - (s16)sp34;
        D_8036D3D0[D_8036DC91].unk18 = arg10;
        D_8036D3D0[D_8036DC91].unk19 = arg11;

        D_8036DC92++;
        if (D_8036DC92 >= arg0) {
            D_8036DC92 = 0;
            D_8036D3D0[D_8036DC91].unk1A = 0;
            D_8036DC91++;
            if (D_8036DC91 == 0x50) {
                D_8036DC91 = 0;
            }
            if (D_8036DC91 == D_8036DC90) {
                D_8036DC90++;
                if (D_8036DC90 == 0x50) {
                    D_8036DC90 = 0;
                }
            }
        }
        D_8036DC94 = D_hd_code_80358060;
    }
}

void func_hd_code_8027C4C8(Gfx** gfx, struct Model1* arg1) {
    Gfx* entry;
    u8 sp9B;
    u8 sp9A;
    u8 sp99;
    u8 sp98;
    u8 sp97;
    Gfx* sp90;
    s32 sp8C;
    s32 sp88;
    s32 sp84;
    s16 sp82;
    s16 sp80;
    s16 sp7E;
    s16 sp7C;
    s16 sp7A;
    s16 sp78;
    u8 sp77;
    u8 sp76;
    s32 sp70;
    s32 sp6C;
    u8 sp6B;


    entry = *gfx;
    sp97 = 0;
    sp9B = D_8036DC90;
    sp90 = arg1->unk3C30;
    sp8C = 0;
    sp88 = 0;

    func_hd_code_8027D5AC();
    gDPPipeSync(entry++);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    gDPSetRenderMode(entry++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
    gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
    gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_OFF);
    gDPSetCombineLERP(entry++, 0, 0, 0, PRIMITIVE, 0, 0, 0, SHADE, 0, 0, 0, PRIMITIVE, 0, 0, 0, SHADE);
    gDPSetPrimColor(entry++, 0, 0, 0x00, 0x00, 0x00, 0x00);

    while (sp97 == 0) {
        sp9A = sp9B;
        sp6B = D_8036D3D0[sp9B].unk1B;
        if ((sp9B != D_8036DC91) && (D_8036D3D0[sp9B].unk1A == 0)) {
loop_3:
            sp9B++;
            if (sp9B == 0x50) {
                sp9B = 0;
            }
            if ((sp9B != D_8036DC91) && D_8036D3D0[sp9B].unk1A == 0) {
                goto loop_3;
            }
        }
        sp99 = sp9B;
        if (sp9B == D_8036DC91) {
            sp97 = 1;
        }
        if (sp9A != sp99) {
            gSPDisplayList(entry++, &D_2000000.unk3C30[sp8C]);

            sp82 = 0x7FFF,
            sp80 = 0x7FFF,
            sp7E = 0x7FFF;
            sp7C = -0x8000,
            sp7A = -0x8000,
            sp78 = -0x8000;

            sp84 = sp88;
            sp98 = sp9A;
            if (sp9A != sp99) {
                do {
                    arg1->unk2000[sp84].n.ob[0] = (s16) D_8036D3D0[sp98].unk0;
                    arg1->unk2000[sp84].n.ob[1] = (s16) D_8036D3D0[sp98].unk2;
                    arg1->unk2000[sp84].n.ob[2] = (s16) D_8036D3D0[sp98].unk4;
                    arg1->unk2000[sp84].n.a = (u8) D_8036D3D0[sp98].unk18;
                    sp84++;

                    arg1->unk2000[sp84].n.ob[0] = (s16) D_8036D3D0[sp98].unk6;
                    arg1->unk2000[sp84].n.ob[1] = (s16) D_8036D3D0[sp98].unk8;
                    arg1->unk2000[sp84].n.ob[2] = (s16) D_8036D3D0[sp98].unkA;
                    arg1->unk2000[sp84].n.a = (u8) D_8036D3D0[sp98].unk18;
                    sp84++;

                    if (D_8036D3D0[sp98].unk0 < sp82) {
                        sp82 = D_8036D3D0[sp98].unk0;
                    }

                    if (D_8036D3D0[sp98].unk2 < sp80) {
                        sp80 = D_8036D3D0[sp98].unk2;
                    }

                    if (D_8036D3D0[sp98].unk4 < sp7E) {
                        sp7E = D_8036D3D0[sp98].unk4;
                    }

                    if (D_8036D3D0[sp98].unk0 > sp7C) {
                        sp7C = D_8036D3D0[sp98].unk0;
                    }

                    if (D_8036D3D0[sp98].unk2 > sp7A) {
                        sp7A = D_8036D3D0[sp98].unk2;
                    }

                    if (D_8036D3D0[sp98].unk4 > sp78) {
                        sp78 = D_8036D3D0[sp98].unk4;
                    }

                    if (D_8036D3D0[sp98].unk6 < sp82) {
                        sp82 = D_8036D3D0[sp98].unk6;
                    }

                    if (D_8036D3D0[sp98].unk8 < sp80) {
                        sp80 = D_8036D3D0[sp98].unk8;
                    }

                    if (D_8036D3D0[sp98].unkA < sp7E) {
                        sp7E = D_8036D3D0[sp98].unkA;
                    }

                    if (D_8036D3D0[sp98].unk6 > sp7C) {
                        sp7C = D_8036D3D0[sp98].unk6;
                    }

                    if (D_8036D3D0[sp98].unk8 > sp7A) {
                        sp7A = D_8036D3D0[sp98].unk8;
                    }

                    if (D_8036D3D0[sp98].unkA > sp78) {
                        sp78 = D_8036D3D0[sp98].unkA;
                    }

                    sp98++;
                    if (sp98 == 0x50) {
                        sp98 = 0;
                    }
                } while (sp98 != sp99);
            }
            if (sp6B == 0) {
                sp98 = sp9A;
                if (sp9A != sp99) {
                    do {
                        arg1->unk2000[sp84].n.ob[0] = (s16) D_8036D3D0[sp98].unkC;
                        arg1->unk2000[sp84].n.ob[1] = (s16) D_8036D3D0[sp98].unkE;
                        arg1->unk2000[sp84].n.ob[2] = (s16) D_8036D3D0[sp98].unk10;
                        arg1->unk2000[sp84].n.a = (u8) D_8036D3D0[sp98].unk19;
                        sp84++;

                        arg1->unk2000[sp84].n.ob[0] = (s16) D_8036D3D0[sp98].unk12;
                        arg1->unk2000[sp84].n.ob[1] = (s16) D_8036D3D0[sp98].unk14;
                        arg1->unk2000[sp84].n.ob[2] = (s16) D_8036D3D0[sp98].unk16;
                        arg1->unk2000[sp84].n.a = (u8) D_8036D3D0[sp98].unk19;
                        sp84++;
                        if (D_8036D3D0[sp98].unkC < sp82) {
                            sp82 = D_8036D3D0[sp98].unkC;
                        }

                        if (D_8036D3D0[sp98].unkE < sp80) {
                            sp80 = D_8036D3D0[sp98].unkE;
                        }

                        if (D_8036D3D0[sp98].unk10 < sp7E) {
                            sp7E = D_8036D3D0[sp98].unk10;
                        }

                        if (D_8036D3D0[sp98].unk12 > sp7C) {
                            sp7C = D_8036D3D0[sp98].unk12;
                        }

                        if (D_8036D3D0[sp98].unk14 > sp7A) {
                            sp7A = D_8036D3D0[sp98].unk14;
                        }

                        if (D_8036D3D0[sp98].unk16 > sp78) {
                            sp78 = D_8036D3D0[sp98].unk16;
                        }

                        if (D_8036D3D0[sp98].unkC < sp82) {
                            sp82 = D_8036D3D0[sp98].unkC;
                        }

                        if (D_8036D3D0[sp98].unkE < sp80) {
                            sp80 = D_8036D3D0[sp98].unkE;
                        }

                        if (D_8036D3D0[sp98].unk10 < sp7E) {
                            sp7E = D_8036D3D0[sp98].unk10;
                        }

                        if (D_8036D3D0[sp98].unk12 > sp7C) {
                            sp7C = D_8036D3D0[sp98].unk12;
                        }

                        if (D_8036D3D0[sp98].unk14 > sp7A) {
                            sp7A = D_8036D3D0[sp98].unk14;
                        }

                        if (D_8036D3D0[sp98].unk16 > sp78) {
                            sp78 = D_8036D3D0[sp98].unk16;
                        }
                        sp98++;
                        if (sp98 == 0x50) {
                            sp98 = 0;
                        }
                    } while (sp98 != sp99);
                }
            }
            sp70 = sp84 - sp88;
            if (sp6B != 0) {
                sp6C = 0;
            } else {
                sp6C = sp70 >> 1;
            }
            if (sp70 >= 0x29) {
                func_hd_code_8027D350(sp82, sp80, sp7E, sp7C, sp7A, sp78, arg1->unk2000, sp84);

                gSPVertex(sp90++,&D_2000000.unk2000[sp84], 8, 0);
                gSPCullDisplayList(sp90++, 0, 7);

                sp8C += 2;
                sp84 += 8;
            }
            while (sp70 >= 3) {
                if (sp70 > 16) {
                    sp76 = 16;
                } else {
                    sp76 = (u8) sp70;
                }

                gSPVertex(sp90++, &D_2000000.unk2000[sp88], sp76, 0);
//                sp38->unk0 = (s32) (((((sp76 - 1) * 0x10) & 0xFF) << 0x10) | 0x04000000 | ((sp76 * 0x10) & 0xFFFF));
                //sp38->unk4 = (void* ) ((sp88 * 0x10) + 0x2000 + &D_2000000);

                sp77 = 0;
                sp88 = sp88 - 2 + sp76;
                sp8C++;
                while ((sp76 - 2) > sp77) {
                    if (sp6C != 2) {
                        gSP1Triangle(sp90++, sp77, sp77 + 1, sp77 + 2, 0);
                        gSP1Triangle(sp90++, sp77 + 1, sp77 + 2, sp77 + 3, 0);

                        sp8C += 2;
                        sp6C -= 2;
                        sp77 += 2;
                    } else {
                        sp6C = 0;
                        sp77 += 4;
                    }
                }
                sp70 = (sp70 - sp76) + 2;
            }
            sp88 = sp84;
            gSPEndDisplayList(sp90++);
            sp8C += 1;
        }
        sp9B++;
        if (sp9B == 0x50) {
            sp9B = 0;
        }
    }
    gDPPipeSync(entry++);

    *gfx = entry;
}

void func_hd_code_8027D350(s16 x1, s16 y1, s16 z1, s16 x2, s16 y2, s16 z2, Vtx* arg6, s32 arg7) {
  arg6[arg7].v.ob[0] = x1;
  arg6[arg7].v.ob[1] = y1;
  arg6[arg7].v.ob[2] = z1;
  arg7++;

  arg6[arg7].v.ob[0] = x1;
  arg6[arg7].v.ob[1] = y2;
  arg6[arg7].v.ob[2] = z1;
  arg7++;

  arg6[arg7].v.ob[0] = x2;
  arg6[arg7].v.ob[1] = y1;
  arg6[arg7].v.ob[2] = z1;
  arg7++;

  arg6[arg7].v.ob[0] = x2;
  arg6[arg7].v.ob[1] = y2;
  arg6[arg7].v.ob[2] = z1;
  arg7++;

  arg6[arg7].v.ob[0] = x1;
  arg6[arg7].v.ob[1] = y1;
  arg6[arg7].v.ob[2] = z2;
  arg7++;

  arg6[arg7].v.ob[0] = x1;
  arg6[arg7].v.ob[1] = y2;
  arg6[arg7].v.ob[2] = z2;
  arg7++;

  arg6[arg7].v.ob[0] = x2;
  arg6[arg7].v.ob[1] = y1;
  arg6[arg7].v.ob[2] = z2;
  arg7++;

  arg6[arg7].v.ob[0] = x2;
  arg6[arg7].v.ob[1] = y2;
  arg6[arg7].v.ob[2] = z2;
}

void func_hd_code_8027D5AC(void) {
  s32 sp4;
  u8 sp3;

  if (D_8036DC91 >= D_8036DC90) {
    sp4 = D_8036DC91 - D_8036DC90;
  } else {
    sp4 = (D_8036DC91 - D_8036DC90) + 0x50;
  }
  if (sp4 >= 0x47) {
    if (D_8036D3D0[D_8036DC90].unk18 <= 0) {
      D_8036D3D0[D_8036DC90].unk18 = 0;
    } else {
      D_8036D3D0[D_8036DC90].unk18 -= 1;
    }

    if (D_8036D3D0[D_8036DC90].unk19 <= 0) {
      D_8036D3D0[D_8036DC90].unk19 = 0;
    } else {
      D_8036D3D0[D_8036DC90].unk19 -= 1;
    }

    if ((D_8036D3D0[D_8036DC90].unk18 == 0) && (D_8036D3D0[D_8036DC90].unk19 == 0)) {
      sp3 = D_8036DC90 + 1;
      if (sp3 == 0x50) {
        sp3 = 0;
      }

      if (D_8036D3D0[sp3].unk18 <= 0) {
        D_8036D3D0[sp3].unk18 = 0;
      } else {
        D_8036D3D0[sp3].unk18 -= 1;
      }

      if (D_8036D3D0[sp3].unk19 <= 0) {
        D_8036D3D0[sp3].unk19 = 0;
      } else {
        D_8036D3D0[sp3].unk19 -= 1;
      }

      if ((D_8036D3D0[sp3].unk18 == 0) && (D_8036D3D0[sp3].unk19 == 0)) {
        D_8036DC90 = sp3;
      }
    }
  }
}
