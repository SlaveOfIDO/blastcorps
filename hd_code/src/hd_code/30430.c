#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"

extern u16 D_8036C770;
extern f32 D_8036C774;
u64 D_8036C778;
extern s32 D_8036C780;
extern u8 D_8036C784;
extern f32 D_hd_code_802FA930;
extern u32 D_hd_code_803156C4;
extern u8 D_hd_code_8035805C;
extern u32 D_hd_code_80358060;
extern u64 D_hd_code_80364A90;
extern u64 D_hd_code_80364A98;
extern s32 levelno;

Gfx* func_hd_code_80274BF0(void* arg0, Gfx* gfx) {
    Gfx* entry;

    entry = gfx;
    if (D_hd_code_80358060 == 0) {
        if ((D_hd_code_80364A90 & 0x4055800100040000) || (((D_hd_code_80364A90 & 0x1801)) && (levelno == 0x32))) {
            D_8036C784 = 0xFF;
            if ((D_hd_code_80364A90 & 0x51800100040000)) {
                D_8036C770 = func_hd_code_8026B10C();
                func_hd_code_8026AF6C(0U);
            }
            D_8036C780 = D_hd_code_803156C4;
        } else {
            D_8036C784 = 0;
        }
    }
    if ((D_8036C778 != 0)) {
        D_8036C784 = MIN(255.0f, ((D_hd_code_803156C4 - D_8036C780) * D_8036C774));
        if (D_8036C784 == 0xFF) {
            D_hd_code_80364A98 = D_8036C778;
            D_8036C778 = 0;
        }
    } else if (D_8036C784 != 0) {
        D_8036C784 = MAX(0.0f, 255.0f - ((D_hd_code_803156C4 - D_8036C780) * D_hd_code_802FA930));
        if (D_8036C784 == 0) {
            func_hd_code_8026AF6C(D_8036C770);
            D_8036C770 = 0;
        }
    }
    if (D_8036C784 != 0) {
        gDPPipeSync(entry++);
        gDPSetRenderMode(entry++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
        gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_OFF);
        gDPSetPrimColor(entry++, 0, 0, 0, 0, 0, D_8036C784);
        gDPSetCycleType(entry++, G_CYC_1CYCLE);
        gDPSetCombineMode(entry++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPFillRectangle(entry++, 0, 0, 319, 239);

        osWritebackDCache(&D_hd_code_802FA8B0[D_hd_code_8035805C], 0x40);
    }
    return entry;
}

void func_hd_code_80275270(u64 arg0, f32 arg2) {
  if ((D_8036C778 != 0)) {
    rmonPrintf("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "!postFadeLoop_done", "fade.c", 0x64);
  }
  if ((D_8036C778 == 0)) {
    D_8036C778 = arg0;
    D_8036C774 = 4.25 / arg2;
    D_8036C780 = D_hd_code_803156C4;
    if (!(arg0 & 0x40000000080004C2) && !(D_hd_code_80364A90 & 0x4000000000040000)) {
      func_hd_code_80261570(0.0f);
    }
  }
}

void func_hd_code_80275390(u64 arg0) {
  func_hd_code_80275270(arg0, 0.25f);
}

s32 areWeFading(void) {
  return D_8036C778 != 0 ? 1 : 0;
}

s32 func_hd_code_802753F8(void) {
  return D_8036C770 != 0 ? 1 : 0;
}

