#include "common.h"
#include "functions.h"
#include "gfx.h"
#include "hd.h"
#include "structs.h"
#include "variables.h"

extern s32 D_hd_code_80207090;
extern s32 D_hd_code_80210690;
extern void* g_gfxMicrocodeText[];
extern void* g_gfxMicrocodeData[];
extern s32 D_hd_code_802E53F0;
extern s32 D_hd_code_8030E390;
extern u64 D_hd_code_80367750;
extern u64 D_hd_code_8036AFB0;
extern s32 __hd_front_end_menu_rsp_databin;
extern s32 __hd_front_end_menu_rsp_textbin;

// <bss>
void* g_gfxMicrocodeText[5];
void* g_gfxMicrocodeData[5];
u8 g_gfxTaskSlotUsed[5];
Gfx* g_gfxTaskOutputBuffer;
OSScTask g_gfxTasks[5][2];
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

void gfxInitMicrocode(void) {
  g_gfxMicrocodeText[0] = &__hd_front_end_menu_rsp_textbin;
  g_gfxMicrocodeData[0] = &__hd_front_end_menu_rsp_databin;
  g_gfxMicrocodeText[1] = &D_hd_code_802E53F0; // f3d
  g_gfxMicrocodeData[1] = &D_hd_code_8030E390; // f3d data
  g_gfxMicrocodeText[2] = &D_hd_code_802E53F0;
  g_gfxMicrocodeData[2] = &D_hd_code_8030E390;
  g_gfxMicrocodeText[3] = &D_hd_code_802E53F0;
  g_gfxMicrocodeData[3] = &D_hd_code_8030E390;
}

void gfxSubmitTask(Gfx* displayList, s32 displayListEntries, u8 taskSlot, u8 lastTask, s32 gfxTaskId, u8 fullFlush) {
  OSScTask* gfxTask;
  s32 displayListSize;

  displayListSize = displayListEntries * sizeof(Gfx);
  gfxTask = &g_gfxTasks[taskSlot][D_hd_code_8035805C];
  g_gfxTaskSlotUsed[taskSlot] = 1;
  gfxTask->list.t.type = M_GFXTASK;
  if (taskSlot == 4) {
    gfxTask->list.t.flags = OS_TASK_DP_WAIT;
  } else {
    gfxTask->list.t.flags = 0;
  }
  gfxTask->list.t.ucode_boot = (u64* ) rspbootTextStart;
  gfxTask->list.t.ucode_boot_size = (u32)aspMainTextStart - (u32)rspbootTextStart;
  gfxTask->list.t.ucode = (u64* ) g_gfxMicrocodeText[taskSlot];
  gfxTask->list.t.ucode_data = (u64* ) g_gfxMicrocodeData[taskSlot];
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
  gfxTask->msg = (OSMesg)((taskSlot << 0x10) | gfxTaskId);
  gfxTask->flags = OS_SC_NEEDS_RDP | OS_SC_NEEDS_RSP;
  if (lastTask) {
    gfxTask->flags |= OS_SC_SWAPBUFFER;
  }
  gfxTask->framebuffer = D_80000400[D_hd_code_8035805C];
  gfxTask->client = &g_gfxClient;
  if (fullFlush) {
    osWritebackDCacheAll();
  } else {
    osWritebackDCache(gfxTask, 0x60);
    osWritebackDCache(displayList, displayListSize);
    osWritebackDCache(&D_hd_code_803156F8[D_hd_code_8035805C], 0x21498);
  }
  osSendMesg(&sc.interruptQ, gfxTask, OS_MESG_BLOCK);
}

void gfxWaitForTask(u32 taskSlot) {
  u32 finishedTaskMessage;

  do {
    osRecvMesg(&D_hd_code_803153D8, (OSMesg)&finishedTaskMessage, OS_MESG_BLOCK);
    g_gfxTaskSlotUsed[finishedTaskMessage >> 16] = 0;
    finishedTaskMessage &= 0xFFFF;
    if (finishedTaskMessage != taskSlot) {
      rmonPrintf("Task %d received message %d\n", taskSlot, finishedTaskMessage);
    }
  } while (finishedTaskMessage != taskSlot);
}
