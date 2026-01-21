#include <ultra64.h>
#include "common.h"
#include "structs.h"
#include "macros.h"


Gfx* func_hd_code_80257540(Gfx* gfx) {
  gDPPipeSync(gfx++);
  gDPSetCycleType(gfx++, G_CYC_1CYCLE);
  gSPClearGeometryMode(gfx++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
  gSPSetGeometryMode(gfx++, G_SHADE | G_LOD | G_SHADING_SMOOTH);
  gSPTexture(gfx++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);

  return gfx;
}


Gfx* func_hd_code_802575F4(Gfx* gfx, s32 arg1, s32 arg2, s16 arg3, s32 width, s32 height, s32 arg6) {
    s32 spBC;

    gDPPipeSync(gfx++);
    if (arg6) {
        gSPSetGeometryMode(gfx++, G_ZBUFFER);
    } else {
        gSPClearGeometryMode(gfx++, G_ZBUFFER);
    }
    spBC = arg2 & 0x1FFFFFFF;
    gSPVertex(gfx++, arg1 & 0x1FFFFFFF, 4, 0);

    switch ((u8)arg3) {                              /* switch 1; irregular */
    case G_IM_SIZ_4b:                                         /* switch 1 */
        rare_gDPLoadTextureBlock_4b(gfx++, spBC, ((u8)(arg3>>8)), width, height, /* pal = */ 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD)
        //gDPLoadTextureBlock_4bS(gfx++, spBC, ((u8)(arg3>>8)), width, height, /* pal = */ 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD)
        //gDPLoadMultiBlock_4bS(gfx++, spBC, 0, G_TX_RENDERTILE, ((u8)(arg3>>8)), width, height, /* pal = */ 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD)
        //gDPLoadTextureBlock_4b(gfx++, spBC, ((u8)(arg3>>8)), width, height, /* pal = */ 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD)
        //gDPLoadMultiBlock_4b(gfx++, spBC, 0, G_TX_RENDERTILE, ((u8)(arg3>>8)), width, height, /* pal = */ 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD)
        //gDPLoadTextureTile_4b(gfx++, spBC, ((u8)(arg3>>8)), width, height, 1,1,width-1,height-1,/* pal = */ 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD)
        break;
    case G_IM_SIZ_8b:
        gDPLoadTextureBlock(gfx++, spBC, (u8)(arg3>>8), G_IM_SIZ_8b, width, height, /* pal = */ 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case G_IM_SIZ_16b:
        gDPLoadTextureBlock(gfx++, spBC, (u8)(arg3>>8), G_IM_SIZ_16b, width, height, /* pal = */ 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    case G_IM_SIZ_32b:
        gDPLoadTextureBlock(gfx++, spBC, (u8)(arg3>>8), G_IM_SIZ_32b, width, height, /* pal = */ 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        break;
    }
    switch ((arg3 >> 8) & 0xFF) {
    case 0:
        if (arg6 != 0) {
            gDPSetRenderMode(gfx++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
        } else {
            gDPSetRenderMode(gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
        }
        gDPSetCombineMode(gfx++, G_CC_MODULATEIA, G_CC_MODULATEIA);
        break;
    case 3:
        if (arg6 != 0) {
            gDPSetRenderMode(gfx++, G_RM_ZB_CLD_SURF, G_RM_ZB_CLD_SURF2);
        } else {
            gDPSetRenderMode(gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
        }
        gDPSetCombineMode(gfx++, G_CC_MODULATEIA, G_CC_MODULATEIA);
        break;
    case 4:
        if (arg6 != 0) {
            gDPSetRenderMode(gfx++, G_RM_ZB_OPA_SURF, G_RM_ZB_OPA_SURF2);
        } else {
            gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        }
        gDPSetCombineMode(gfx++, G_CC_MODULATEI, G_CC_MODULATEI);
        break;
    }

    gSP1Triangle(gfx++, 0, 1, 3, 0);
    gSP1Triangle(gfx++, 0, 2, 3, 0);

    return gfx;
}
