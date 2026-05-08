#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"

extern s32 D_80207090;
extern s32 D_80210690;
extern void* D_8036E660[];
extern void* D_8036E678[];
extern s32 D_hd_code_802E53F0;
extern s32 D_hd_code_8030E390;
extern struct Model1 D_hd_code_803156F8[];
extern OSScTask D_8036E698[][2];
extern u64 D_hd_code_80367750;
extern u64 D_hd_code_8036AFB0;

void func_hd_code_80284DB0(void) {
  D_8036E660[0] = &D_80207090; // func_hd_front_end_80207090
  D_8036E678[0] = &D_80210690; // some rodata in hd_front_end
  D_8036E660[1] = &D_hd_code_802E53F0;
  D_8036E678[1] = &D_hd_code_8030E390;
  D_8036E660[2] = &D_hd_code_802E53F0;
  D_8036E678[2] = &D_hd_code_8030E390;
  D_8036E660[3] = &D_hd_code_802E53F0;
  D_8036E678[3] = &D_hd_code_8030E390;
}

void func_hd_code_80284E54(Gfx* arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4, s32 arg5) {
  OSScTask* sp1C;
  s32 sp18;

  sp18 = arg1 * 8;
  sp1C = &D_8036E698[arg2][D_hd_code_8035805C];
  D_8036E68C[(u8) arg2] = 1;
  sp1C->list.t.type = 1;
  if ((u8) arg2 == 4) {
    sp1C->list.t.flags = 2;
  } else {
    sp1C->list.t.flags = 0;
  }
  sp1C->list.t.ucode_boot = (u64* ) rspbootTextStart;
  sp1C->list.t.ucode_boot_size = (u32)aspMainTextStart - (u32)rspbootTextStart;
  sp1C->list.t.ucode = (u64* ) D_8036E660[(u8) arg2];
  sp1C->list.t.ucode_data = (u64* ) D_8036E678[(u8) arg2];
  sp1C->list.t.ucode_size = 0x1000;
  sp1C->list.t.ucode_data_size = 0x800;
  sp1C->list.t.dram_stack = &D_hd_code_80367750;
  sp1C->list.t.dram_stack_size = 0x400;
  sp1C->list.t.output_buff = (u64* ) D_8036E694;
  sp1C->list.t.output_buff_size = (u64* ) (D_8036E694 + 0x1400);
  sp1C->list.t.data_ptr = (u64* ) arg0;
  sp1C->list.t.data_size = (u32) sp18;
  sp1C->list.t.yield_data_ptr = &D_hd_code_8036AFB0;
  sp1C->list.t.yield_data_size = 0x900;
  sp1C->next = NULL;
  sp1C->msg = &D_hd_code_803153D8;
  sp1C->unk58 = ((u8) arg2 << 0x10) | arg4;
  sp1C->flags = 3;
  if ((u8) arg3 != 0) {
    sp1C->flags |= 0x40;
  }
  sp1C->framebuffer = D_80000400[D_hd_code_8035805C];
  sp1C->msgQ = &D_hd_code_803156D8;
  if ((u8) arg5 != 0) {
    osWritebackDCacheAll();
  } else {
    osWritebackDCache(sp1C, 0x60);
    osWritebackDCache(arg0, sp18);
    osWritebackDCache(&D_hd_code_803156F8[D_hd_code_8035805C], 0x21498);
  }
  osSendMesg(&sc.interruptQ, sp1C, 1);
}

void func_hd_code_80285110(s32 arg0) {
  u32 sp1C;

  do {
    osRecvMesg((OSMesgQueue* ) &D_hd_code_803153D8, (OSMesg)&sp1C, 1);
    D_8036E68C[sp1C >> 0x10] = 0;
    sp1C &= 0xFFFF;
    if ((u32)sp1C != arg0) {
      rmonPrintf("Task %d received message %d\n", arg0, sp1C);
    }
  } while ((u32)sp1C != arg0);
}
