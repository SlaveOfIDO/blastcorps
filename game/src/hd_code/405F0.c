#include "common.h"
#include "functions.h"
#include "hd.h"
#include "structs.h"
#include "variables.h"

extern s32 D_hd_code_80207090;
extern s32 D_hd_code_80210690;
extern void* D_hd_code_8036E660[];
extern void* D_hd_code_8036E678[];
extern s32 D_hd_code_802E53F0;
extern s32 D_hd_code_8030E390;
extern OSScTask D_hd_code_8036E698[][2];
extern u64 D_hd_code_80367750;
extern u64 D_hd_code_8036AFB0;
extern s32 __hd_front_end_menu_rsp_databin;
extern s32 __hd_front_end_menu_rsp_textbin;

// Proposed file name: rsp_task.c
//
// This file submits graphics display lists to the RSP as scheduler tasks and
// waits for them to complete. It holds a small table of microcode entry
// points (D_hd_code_8036E660 = text, D_hd_code_8036E678 = data) for the different render
// passes - slot 0 is the front-end menu microcode, slots 1-3 the in-game
// microcode. Up to 5 concurrent task slots are tracked, each double-buffered
// per frame, with the in-flight flags in D_hd_code_8036E68C.

// <bss>
void* D_hd_code_8036E660[6];
void* D_hd_code_8036E678[5];
u8 D_hd_code_8036E68C[4];
s32 D_hd_code_8036E690;
Gfx* g_gfxTaskOutputBuffer;
OSScTask D_hd_code_8036E698[5][2];
s32 D_hd_code_8036EA58;
s32 D_hd_code_8036EA5C;
// </bss>

// <data>
u8 D_hd_code_802FDA60[16] = {
  0x00, 0x00, 0x05, 0x05,
  0x05, 0x04, 0x06, 0x04,
  0x00, 0x05, 0x05, 0x09,
  0x06, 0x00, 0x00, 0x00
};

u8 D_hd_code_802FDA70[16] = {
  0x00, 0x00, 0x28, 0x28,
  0x25, 0x28, 0x1B, 0x27,
  0x00, 0x25, 0x25, 0x1A,
  0x1A, 0x00, 0x00, 0x00
};

Vtx D_hd_code_802FDA80[4] = {
  { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
  { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
  { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0xFF } } },
  { { { 0x0000, 0x0000, 0x0000 }, 0x0000, { 0x0000, 0x0000 }, { 0xFF, 0xFF, 0xFF, 0xFF } } }
};

// This is only used by hd_front_end
f32 D_hd_code_802FDAC0[20] = {
  2.0f, 0.800000012f, 1.39999998f, 0.899999976f,
  0.600000024f, 1.20000005f, 0.075000003f, 0.400000006f,
  0.899999976f, 1.0f, 0.850000024f, 1.0f,
  1.20000005f, 1.0f, 1.0f, 1.0f,
  1.0f, 1.0f, 1.0f, 0.0f
};
// </data>

// Populate the microcode entry-point table: slot 0 points at the front-end
// menu's microcode (in the separate hd_front_end overlay), slots 1-3 at the
// shared in-game microcode
void gfxInitMicrocode(void) {
  D_hd_code_8036E660[0] = &__hd_front_end_menu_rsp_textbin;
  D_hd_code_8036E678[0] = &__hd_front_end_menu_rsp_databin;
  D_hd_code_8036E660[1] = &D_hd_code_802E53F0; // f3d
  D_hd_code_8036E678[1] = &D_hd_code_8030E390; // f3d data
  D_hd_code_8036E660[2] = &D_hd_code_802E53F0;
  D_hd_code_8036E678[2] = &D_hd_code_8030E390;
  D_hd_code_8036E660[3] = &D_hd_code_802E53F0;
  D_hd_code_8036E678[3] = &D_hd_code_8030E390;
}

// Submit display list arg0 (arg1 commands) to the RSP on task slot arg2,
// using that slot's microcode. Fills in an OSScTask (boot/main microcode,
// DRAM stack, output buffer, yield buffer, target framebuffer), marks the
// slot in-flight, writes back the data cache (the whole cache if arg5,
// otherwise just the task/list/graphics-context), and queues it to the
// scheduler. arg3 enables a task flag (0x40), gfxTaskId is a tag returned in the
// completion message.
void gfxSubmitTask(Gfx* displayList, s32 displayListEntries, u8 arg2, s32 arg3, s32 gfxTaskId, s32 arg5) {
  OSScTask* gfxTask;
  s32 displayListSize;

  displayListSize = displayListEntries * sizeof(Gfx);
  gfxTask = &D_hd_code_8036E698[arg2][D_hd_code_8035805C];
  D_hd_code_8036E68C[(u8) arg2] = 1;
  gfxTask->list.t.type = M_GFXTASK;
  if ((u8) arg2 == 4) {
    gfxTask->list.t.flags = OS_TASK_DP_WAIT;
  } else {
    gfxTask->list.t.flags = 0;
  }
  gfxTask->list.t.ucode_boot = (u64* ) rspbootTextStart;
  gfxTask->list.t.ucode_boot_size = (u32)aspMainTextStart - (u32)rspbootTextStart;
  gfxTask->list.t.ucode = (u64* ) D_hd_code_8036E660[(u8) arg2];
  gfxTask->list.t.ucode_data = (u64* ) D_hd_code_8036E678[(u8) arg2];
  gfxTask->list.t.ucode_size = 0x1000;
  gfxTask->list.t.ucode_data_size = 0x800;
  gfxTask->list.t.dram_stack = &D_hd_code_80367750;
  gfxTask->list.t.dram_stack_size = 0x400;
  gfxTask->list.t.output_buff = (u64* ) g_gfxTaskOutputBuffer;
  gfxTask->list.t.output_buff_size = (u64* ) (g_gfxTaskOutputBuffer + 0x1400);
  gfxTask->list.t.data_ptr = (u64* ) displayList;
  gfxTask->list.t.data_size = (u32) displayListSize;
  gfxTask->list.t.yield_data_ptr = &D_hd_code_8036AFB0;
  gfxTask->list.t.yield_data_size = 0x900;
  gfxTask->next = NULL;
  gfxTask->msgQ = &D_hd_code_803153D8;
  gfxTask->msg = (OSMesg)((arg2 << 0x10) | gfxTaskId);
  gfxTask->flags = OS_SC_NEEDS_RDP | OS_SC_NEEDS_RSP;
  if ((u8) arg3 != 0) {
    gfxTask->flags |= OS_SC_SWAPBUFFER;
  }
  gfxTask->framebuffer = D_80000400[D_hd_code_8035805C];
  gfxTask->client = &g_gfxClient;
  if ((u8) arg5 != 0) {
    osWritebackDCacheAll();
  } else {
    osWritebackDCache(gfxTask, 0x60);
    osWritebackDCache(displayList, displayListSize);
    osWritebackDCache(&D_hd_code_803156F8[D_hd_code_8035805C], 0x21498);
  }
  osSendMesg(&sc.interruptQ, gfxTask, OS_MESG_BLOCK);
}

// Block until the task tagged arg0 reports completion, clearing each
// finished slot's in-flight flag along the way (warns on unexpected tags)
void gfxWaitForTask(u32 arg0) {
  u32 sp1C;

  do {
    osRecvMesg(&D_hd_code_803153D8, (OSMesg)&sp1C, 1);
    D_hd_code_8036E68C[sp1C >> 16] = 0;
    sp1C &= 0xFFFF;
    if (sp1C != arg0) {
      rmonPrintf("Task %d received message %d\n", arg0, sp1C);
    }
  } while (sp1C != arg0);
}
