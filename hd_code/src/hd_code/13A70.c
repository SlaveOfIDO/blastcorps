#include <ultra64.h>
#include "common.h"
#include "structs.h"
#include "functions.h"
#include "variables.h"

Vp D_hd_code_802E8C60 = {
  {
    {0x0080, 0x0080, 0x01FF, 0x0000},
    {0x0080, 0x0080, 0x01FF, 0x0000}
  }
};

void func_hd_code_80258230(u8 arg0, s32 arg1, s16 arg2, s16 arg3) {
  D_803643C8.end->unk1022 = arg0;
  D_803643C8.end->unk1023 = 0;
  D_803643C8.end->unk1000 = (f32) arg1;
  D_803643C8.end->unk1018 = arg2;
  D_803643C8.end->unk101A = arg3;
  D_803643C8.end->unk101C = 0;
  D_803643C8.end->unk101E = 0;
  D_803643C8.end->unk1020 = 0;
  D_803643C8.end++;
}

void func_hd_code_802582C4(u8 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
  u8 sp37;
  struct Texture* sp30;
  u8 sp2F;
  u8 sp2E;
  u8 sp2D;
  s16 sp2A;
  s32 sp24;
  s32 sp20;
  s32 sp1C;

  sp37 = 0;
  sp2F = 0;
  sp2E = 0;
  if (arg0 == 9) {
    sp2F = func_hd_code_802ABEDC(arg1, arg4, arg3);
    if (sp2F != 0) {
      sp2E = 1;
    }
    sp2D = func_hd_code_8027EED8(arg1 >> 5, arg3 >> 5, &sp2A);
    if (sp2D != 0) {
      sp24 = arg4 - (sp2A << 5);
      sp1C = arg4 - arg2;
      if (sp2F != 0) {
        sp20 = arg4 - D_803EBBF8;
      } else {
        sp20 = 0x98967F;
      }
      if ((sp24 > 0) && (sp24 < sp20) && (sp24 < sp1C)) {
        D_803EBBF8 = sp2A << 5;
        sp2E = 2;
      }
    }
  }
  sp30 = D_803643C8.textures;
  if (sp37 == 0) {
    do {
      if (sp30->unk1022 == arg0) {
        sp30->unk1004 = arg1;
        if (sp2E != 0) {
          sp30->unk1008 = D_803EBBF8;
        } else {
          sp30->unk1008 = arg2;
        }
        sp30->unk100C = arg3;
        sp30->unk1014 = arg2;
        sp30->unk101C = (s16) arg5;
        sp30->unk101E = (s16) arg7;
        sp30->unk1020 = (s16) arg6;
        sp30->unk1010 = arg4;
        sp30->unk1023 = sp2E;
        sp37 = 1;
      } else {
        sp30++;
      }
    } while (sp37 == 0);
  }
}

s32 func_hd_code_802584BC(u8 arg0) {
  struct Texture* sp4;

  sp4 = D_803643C8.textures;
  while(1) { // ... internship?
    if(sp4->unk1022 == arg0) {
      return sp4->unk1008;
    }
    sp4++;
  }
  return 0;
}

s32 func_hd_code_80258500(u8 arg0) {
  struct Texture* sp4;

  sp4 = D_803643C8.textures;
  while(1) { // ... internship?
    if(sp4->unk1022 == arg0) {
      return sp4->unk1014;
    }
    sp4++;
  }
  return 0;
}
# define gSPPerspNormalize_old(pkt, s)					\
{									\
Gfx *_g = (Gfx *)(pkt);						\
\
_g->words.w0 = _SHIFTL(G_RDPHALF_1, 24, 8);			\
_g->words.w1 = (s);						\
}
# define gsSPPerspNormalize_old(s)						\
{{									\
_SHIFTL(G_RDPHALF_1, 24, 8),					\
(s)								\
}}

void func_hd_code_80258544(struct Texture* arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 *arg5, s32 *arg6, s32 *arg7) {
    Gfx *entry;
    u16 sp9A;
    u32 pad;

    entry = &D_803650B0[0];

    gSPViewport(entry++, VIRTUAL_TO_PHYSICAL(&D_hd_code_802E8C60));
    gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
    gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_OFF);
    gSPSegment(entry++, 0x00, 0x00000000);
    gSPSegment(entry++, 0x06, VIRTUAL_TO_PHYSICAL(arg6));
    gSPSegment(entry++, 0x07, VIRTUAL_TO_PHYSICAL(arg7));
    gDPPipeSync(entry++);
    gDPSetScissor(entry++, G_SC_NON_INTERLACE, 0, 0, 63, 63);
    gDPSetPrimColor(entry++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    gDPSetColorDither(entry++, G_CD_DISABLE);
    gDPSetCycleType(entry++, G_CYC_FILL);
    gDPSetColorImage(entry++, G_IM_FMT_CI, G_IM_SIZ_8b, 64, VIRTUAL_TO_PHYSICAL(arg0));
    gDPSetFillColor(entry++, 0x00010001);
    gDPFillRectangle(entry++, 0, 0, 63, 63);
    gDPPipeSync(entry++);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    gDPSetRenderMode(entry++, G_RM_OPA_CI, G_RM_OPA_CI2);
    gDPSetCombineMode(entry++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);

    guPerspective(&D_803651F0, &sp9A, 45.0f, 1.0f, 1.0f, 1000.0f, 1.0f);
    gSPMatrix(entry++, VIRTUAL_TO_PHYSICAL(&D_803651F0), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPPerspNormalize_old(entry++, sp9A);

    func_hd_code_802D4F68(&D_803652F0, 0.0f, 0.0f, -arg4);
    gSPMatrix(entry++, VIRTUAL_TO_PHYSICAL(&D_803652F0), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    guAlign(&D_80365270, -90.0f, 1.0f, 0.0f, 0.0f);
    gSPMatrix(entry++, VIRTUAL_TO_PHYSICAL(&D_80365270), G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);

    guAlign(&D_803652B0, 180.0f, 0.0f, 1.0f, 0.0f);
    gSPMatrix(entry++, VIRTUAL_TO_PHYSICAL(&D_803652B0), G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);

    func_hd_code_802D4F68(&D_80365230, -(arg1 / 32.0f), -(arg2 / 32.0f), -(arg3 / 32.0f));
    gSPMatrix(entry++, VIRTUAL_TO_PHYSICAL(&D_80365230), G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPDisplayList(entry++, VIRTUAL_TO_PHYSICAL(arg5));
    gSPEndDisplayList(entry++);

    osWritebackDCache(&D_803651F0, 0x140);
    func_hd_code_80284E54(&D_803650B0, entry - D_803650B0, 1, 0, 0x61F, 0);
}

void func_hd_code_80258B78(Gfx** arg0, struct Model1* arg1) {
    Gfx* entry;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    s16 sp66;
    s16 sp64;
    s16 sp62;
    s16 sp60;

    entry = *arg0;
    sp70 = 0;
    sp6C = 0;
    sp60 = 0;

    gDPPipeSync(entry++);
    gDPSetCycleType(entry++, G_CYC_1CYCLE);
    gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
    gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
    gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(entry++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(entry++, 0, 0, 0xC8, 0xC8, 0xC8, 0xC8);


    while (&D_803F4030[sp70] != D_803F7654) {
        if (!D_803F4030[sp70].unkEA) {

            switch (D_803F4030[sp70].unk30) {
                case 0xBA:
                case 0xBB:
                case 0xBC:
                    sp68 = 0x3C - ((s32) (D_803F4030[sp70].unk14 - D_803F4030[sp70].unk44) / 800);
                    if (sp68 < 0) {
                        sp68 = 0;
                    }
                    sp66 = (s16)((s32) D_803F4030[sp70].unk10 >> 5);
                    sp64 = (s16) ((s32) D_803F4030[sp70].unk44 >> 5);
                    sp62 = (s16) ((s32) D_803F4030[sp70].unk18 >> 5);

                    arg1->unk3900[sp6C].v.ob[0] = sp66 - sp68;
                    arg1->unk3900[sp6C].v.ob[1] = sp64;
                    arg1->unk3900[sp6C].v.ob[2] = sp62 - sp68;
                    arg1->unk3900[sp6C].v.tc[0] = 0;
                    arg1->unk3900[sp6C].v.tc[1] = 0;
                    sp6C++;

                    arg1->unk3900[sp6C].v.ob[0] = sp66 + sp68;
                    arg1->unk3900[sp6C].v.ob[1] = sp64;
                    arg1->unk3900[sp6C].v.ob[2] = sp62 - sp68;
                    arg1->unk3900[sp6C].v.tc[0] = 0x7E0;
                    arg1->unk3900[sp6C].v.tc[1] = 0;
                    sp6C++;

                    arg1->unk3900[sp6C].v.ob[0] = sp66 + sp68;
                    arg1->unk3900[sp6C].v.ob[1] = sp64;
                    arg1->unk3900[sp6C].v.ob[2] = sp62 + sp68;
                    arg1->unk3900[sp6C].v.tc[0] = 0x7E0;
                    arg1->unk3900[sp6C].v.tc[1] = 0x7E0;
                    sp6C++;

                    arg1->unk3900[sp6C].v.ob[0] = sp66 - sp68;
                    arg1->unk3900[sp6C].v.ob[1] = sp64;
                    arg1->unk3900[sp6C].v.ob[2] = sp62 + sp68;
                    arg1->unk3900[sp6C].v.tc[0] = 0;
                    arg1->unk3900[sp6C].v.tc[1] = 0x7E0;
                    sp6C++;

                    if (sp60 == 0) {
                        gDPLoadTextureBlock(entry++, D_80365330 + 0x80000000, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                        sp60 = 1;
                    }

                    gDPPipeSync(entry++);
                    if ((levelno == 0x10) && (sp66 == 0x19B7) && (sp62 == 0xF99)) {
                        gSPSetGeometryMode(entry++, G_ZBUFFER);
                        gDPSetRenderMode(entry++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
                    } else {
                        gSPClearGeometryMode(entry++, G_ZBUFFER);
                        gDPSetRenderMode(entry++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
                    }
                    gSPVertex(entry++, &D_2000000.unk38C0[sp6C], 4, 0);
                    gSP1Triangle(entry++, 0, 1, 3, 0);
                    gSP1Triangle(entry++, 1, 2, 3, 0);
                    break;
                default:
                    break;
            }
        }
        sp70 += 1;
    }
    gDPPipeSync(entry++);
    *arg0 = entry;
}
