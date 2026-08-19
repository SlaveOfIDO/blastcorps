#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/hd.h"
#include "../hd_code/yoshi.h"
#include "../hd_code/functions.h"
#include "../hd_code/variables.h"


extern s16 D_hd_code_8036BB18;
extern s32 D_hd_code_80358078; // current top-level display list length; proposed name: topLevelDlLen
extern void* D_hd_code_8035806C; // static data segment pointer (segment 1); proposed name: staticSegment
extern OSMesgQueue D_hd_code_80315180;

// <bss>
s32 D_hd_front_end_802159C0;
s32 D_hd_front_end_802159C4;
s32 D_hd_front_end_802159C8;
s32 D_hd_front_end_802159CC;
// </bss>

void func_hd_front_end_801EE390(void) {
}

void func_hd_front_end_801EE398(s32 arg0) {
  struct Model1* sp5C = &D_hd_code_803156F8[D_hd_code_8035805C ^ 1];
  Gfx* entry;
  s32 sp54;

  nextdma = 0;
  no_palette_dmas = 0;
  entry = sp5C->dp;
  func_hd_code_802A5720();
  func_hd_code_8025B2B8();
  if (D_hd_code_8036BB18 != arg0) {
    func_hd_code_8026AF6C(arg0 | 0x8000 | 0x2000);
    sndDeactivateAllSfxByFlag_3();
    D_hd_front_end_802159C0 = 0;
  }
  if (D_hd_front_end_802159C0 == 2) {
    osViBlack(0U);
  }
  func_hd_code_80259450();
  func_hd_code_80284E54(D_hd_code_803156F8[D_hd_code_8035805C].dp, D_hd_code_80358078, 1U, 1, 0x4D2, 0);
  D_hd_code_8035805C ^= 1;

  gSPSegment(entry++, 0x00, 0x00000000);
  gSPSegment(entry++, 0x02, osVirtualToPhysical(sp5C));
  gSPSegment(entry++, 0x01, osVirtualToPhysical(D_hd_code_8035806C));
  gSPDisplayList(entry++, (u32) D_1000038);
  gSPDisplayList(entry++, (u32) D_1000010);
  gDPSetCycleType(entry++, G_CYC_FILL);
  gDPSetColorImage(entry++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, D_hd_code_80358050[D_hd_code_8035805C]);
  gDPPipeSync(entry++);
  gDPSetFillColor(entry++, 0x00010001);
  gDPFillRectangle(entry++, 0, 0, 319, 239);
  gDPSetCycleType(entry++, G_CYC_1CYCLE);

  entry = func_hd_code_8026BBD0(entry, &D_hd_code_803156F8[D_hd_code_8035805C], &D_hd_code_80358078);
  gDPFullSync(entry++);
  gSPEndDisplayList(entry++);

  D_hd_code_80358078 = (s32) (((u32)entry - (u32)sp5C) - 0x48B0) >> 3;

  for(sp54 = 0; sp54 < nextdma; sp54++) {
    osRecvMesg(&D_hd_code_80315180, NULL, 1);
  }
  for(sp54 = 0; sp54 < (nextdma - no_palette_dmas); sp54++) {
    func_hd_code_802A57AC();
  }
  func_hd_code_80285110(0x4D2);
  D_hd_front_end_802159C0 += 1;
}

