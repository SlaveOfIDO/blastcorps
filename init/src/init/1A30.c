#include "common.h"

#if NON_MATCHING
#include <PR/os.h>
#include <PR/rcp.h>
#include "inflate.h"

void func_init_80220360(u8** arg0, u8** arg1, struct huft* arg2);
void MainJump();

extern u8 rzip_HD_CODE_TEXT_START[];
extern u8 rzip_HD_FRONT_END_TEXT_START[];
extern u8 rzip_LAYOUT_END[];
extern u8 hd_code_VRAM[];
extern u8 hd_front_end_VRAM[];
extern u8 hd_code_BSS_END[];

// <bss>
u8* D_init_80224A30;
u8* D_init_80224A34;
// </bss>


void func_init_80220730() {
  s32 i=0;
  s32* p;
  u8 *tmp = (u8*)BOOT_ADDRESS_ULTRA;
  u8 *dst = hd_code_VRAM;
  struct huft* tbl = (struct huft*)hd_front_end_VRAM;

  osInitialize();
  osPiRawStartDma(OS_READ, rzip_HD_CODE_TEXT_START, tmp, rzip_HD_FRONT_END_TEXT_START - rzip_HD_CODE_TEXT_START);
  while(osPiGetStatus() & PI_STATUS_DMA_BUSY);

  func_init_80220360(&tmp, &dst, tbl);
  func_init_80220360(&tmp, &dst, tbl);

  for(p = (s32*)dst;p != (s32*)hd_code_BSS_END; p++) {
    *p = 0;
  }

  // Mailbox for src/hd_code/46C20.c (D_hd_code_802FDB30/34): the last two
  // words of hd_code's just-zeroed bss, so their address has to track
  // hd_code_BSS_END, not a hardcoded constant - it moves as hd_code's own
  // compiled size does.
  *((s32*)(hd_code_BSS_END - 8)) = rzip_HD_FRONT_END_TEXT_START;
  *((s32*)(hd_code_BSS_END - 4)) = rzip_LAYOUT_END;

  osSyncPrintf("got here 2\n");

  MainJump();
}

#else

char D_init_80222850[] = "got here 2\n";

#pragma GLOBAL_ASM("asm/nonmatchings/init/1A30/func_init_80220730.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init/1A30/func_init_80220900.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init/1A30/func_init_80220998.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init/1A30/func_init_80220A50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/init/1A30/func_init_80220B5C.s")

#endif
