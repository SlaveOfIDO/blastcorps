#ifndef HD_CODE_GFX_H
#define HD_CODE_GFX_H

#include <ultra64.h>

#define GFX_TASK_ID_MAIN 1234
#define GFX_TASK_ID_BLUR 1357
#define GFX_TASK_ID_SHADOW 1567

void gfxInitMicrocode(void);
void gfxSubmitTask(Gfx* displayList, s32 displayListEntries, u8 taskSlot, u8 lastTask, s32 gfxTaskId, u8 fullFlush);
void gfxWaitForTask(u32 taskSlot);

extern u8 g_gfxTaskSlotUsed[5];

#endif
