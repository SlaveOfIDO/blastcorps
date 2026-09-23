#include "common.h"
#include "functions.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"

#define VIDEO_MSG       0
#define RSP_DONE_MSG    1
#define RDP_DONE_MSG    2
#define PRE_NMI_MSG     3


#define RSP_STATE_SUSPENDED 3

#define EXEC_IS_AUDIO 0
#define EXEC_IS_GFX 1

void __scYield(OSSched*);                  /* extern */
void __scHandleGfxTask(OSSched*, OSScTask*);       /* extern */
void __scExecAudioIfIdle(OSSched*);              /* extern */
void __scRetraceDone(OSSched*);              /* extern */
void __scRspDone(OSSched*);              /* extern */
void __scRdpDone(OSSched*);              /* extern */
s32 func_hd_code_802A1320();                        /* extern */
void __scMain(void*);                               /* extern */
void __scAppendList(OSSched*, OSScTask*);           /* extern */
void __scExec(OSSched*, s32);               /* extern */
s32 __scSendMesg(OSMesgQueue* messageQueue, OSMesg message, s32 flags);               /* extern */
s32 func_hd_code_80271A84(OSSched*, OSScTask*);     /* extern */

extern OSViMode D_hd_code_80306E70[];
extern s8 D_hd_code_8030C0C0;

// Data begin
s8 D_hd_code_802FA270 = 1;
// Data end

// BSS begin
OSTime D_hd_code_8036BEF0;
OSTime D_hd_code_8036BEF8;
OSTime D_hd_code_8036BF00;
s32 D_hd_code_8036BF08;
s32 D_hd_code_8036BF0C;
s32 D_hd_code_8036BF10;
s32 g_nextRetrace;
s32 D_hd_code_8036BF18;
OSScTask* g_currentRdpTask;
u32 D_hd_code_8036BF20;
u32 D_hd_code_8036BF24;
u32 bss_pad_8036BF28;
u32 D_hd_code_8036BF2C;
u32 pad_8036BF30;
u32 pad_8036BF34;
OSTime D_hd_code_8036BF38;
u64 D_hd_code_8036BF40;
OSTime D_hd_code_8036BF48;
u64 D_hd_code_8036BF50;
u8 bss_pad_8036BF58[0x8036BF78 - 0x8036BF58];
OSTimer D_hd_code_8036BF78;
u8 bss_pad_8036BF98[0x8036BFB8 - 0x8036BF98];
u32 D_hd_code_8036BFB8;
s32 D_hd_code_8036BFBC;
// BSS end

void osCreateScheduler(OSSched* s, void* stack, s32 priority, u8 mode, u8 numFields) {
  s->audioListTail = (OSScTask* ) &s->audioListHead;
  s->gfxListTail = (OSScTask* ) &s->gfxListHead;
  D_hd_code_8036BF10 = 0;
  g_currentRdpTask = 0;

  osCreateMesgQueue(&s->interruptQ, s->intBuf, OS_SC_MAX_MESGS);
  osCreateMesgQueue(&s->cmdQ, s->cmdMsgBuf, OS_SC_MAX_MESGS);
  osCreateViManager(0xFE);
  osViSetMode(&osViModeTable[mode]);
  osViBlack(1);
  osSetEventMesg(OS_EVENT_SP, &s->interruptQ, (void* )0x29B);
  osSetEventMesg(OS_EVENT_DP, &s->interruptQ, (void* )0x29C);
  osSetEventMesg(OS_EVENT_PRENMI, &s->interruptQ, (void* )0x29D);
  osSetEventMesg(OS_EVENT_FAULT, &s->interruptQ, (void* )0x2A0);
  osViSetEvent(s, 0x29A, numFields);
  osCreateThread(&s->thread, 5, __scMain, s, stack, priority);
  osStartThread(&s->thread);
}

void osScAddClient(OSSched* s, OSScClient* c, OSMesgQueue* msgQ, s32 arg3, s32 arg4) {
  u32 sp1C;

  sp1C = osSetIntMask(1U);
  c->msgQ = msgQ;
  c->next = s->clientList;
  s->clientList = c;
  c->unk8 = arg3;
  c->unkC = arg4;
  osSetIntMask(sp1C);
}

void osScRemoveClient(OSSched* sc, OSScClient* c) {
  OSScClient *client = sc->clientList;
  OSScClient *prev   = 0;
  OSIntMask  mask;

  mask = osSetIntMask(OS_IM_NONE);

  while (client != 0)
  {
    if (client == c)
    {
      if(prev)
        prev->next = c->next;
      else
        sc->clientList = c->next;
      break;
    }
    prev   = client;
    client = client->next;
  }

  osSetIntMask(mask);
}

OSMesgQueue* osScGetCmdQ(OSSched* s) {
  return &s->cmdQ;
}

void __scMain(void* params) {
    OSMesg msg;
    OSSched* scheduler;
    OSScClient* client;

    scheduler = params;
    while(1) {
        osRecvMesg(&scheduler->interruptQ, &msg, OS_MESG_BLOCK);

        if (!(func_hd_code_802A1320() & 0x1000)) {
            for (client = scheduler->clientList; client != NULL; client = client->next) {
                osSendMesg(client->msgQ, (void* )0x29D, 0);
            }
            D_hd_code_8036BF10 = 1;
            osViBlack(1U);
            rmonPrintf("GO %x\n", osDpGetStatus());
            osDpSetStatus(DPC_CLR_FREEZE);
            RCP_STAT_PRINT;
            rmonPrintf("GO %x\n", osDpGetStatus());
            while(1);
        }
        switch ((s32)msg - 0x29A) {
        case VIDEO_MSG:
            D_hd_code_8036BFB8++;
            if ((D_hd_code_8036BFB8 % 480U) == 0) {
                D_hd_code_8036BEF8 = D_hd_code_8036BF00;
                D_hd_code_8036BF08 = D_hd_code_8036BF0C;
            }
            __scRetraceDone(scheduler);
            break;
        case 4:
            __scExecAudioIfIdle(scheduler);
            break;
        case RSP_DONE_MSG:
            __scRspDone(scheduler);
            break;
        case RDP_DONE_MSG:
            __scRdpDone(scheduler);
            break;
        case 5:
            osSendMesg(D_hd_code_8036BF78.mq, D_hd_code_8036BF78.msg, 1);
            break;
        case PRE_NMI_MSG:
            for (client = scheduler->clientList; client != NULL; client = client->next) {
                osSendMesg(client->msgQ, (void* )0x29D, 0);
            }
            D_hd_code_8036BF10 = 1;
            osViBlack(TRUE);
            rmonPrintf("%x\n", osDpGetStatus());
            osDpSetStatus(DPC_CLR_FREEZE);
            RCP_STAT_PRINT;
            rmonPrintf("%x\n", osDpGetStatus());
            while(1);
        case 6:
            rmonPrintf(" *** CPU FAULT *** - UNFREEZING RDP?\n");
            while (osViGetCurrentFramebuffer() != osViGetNextFramebuffer()) {

            }
            osDpSetStatus(DPC_CLR_FREEZE);
            while(1);
        default:
            __scHandleGfxTask(scheduler, (OSScTask*)msg);
            break;
        }
    }
}

void __scHandleGfxTask(OSSched* scheduler, OSScTask* arg1) {
  __scAppendList(scheduler, arg1);
  if (scheduler->curRSPTask == NULL) {
    __scExec(scheduler, EXEC_IS_GFX);
  }
}

void __scExecAudioIfIdle(OSSched* scheduler) {
  if (scheduler->curRSPTask != NULL) {
    __scYield(scheduler);
    return;
  }
  D_hd_code_8036BF00 = 0;
  __scExec(scheduler, EXEC_IS_AUDIO);
}

void __scRetraceDone(OSSched* scheduler) {
  OSScTask* rspTask;
  OSScClient* client;
  s32 sp3C;
  s32 sp38;

  scheduler->retraceCount += 1;
  if (D_hd_code_802E8BD0 == 0) {
    scheduler->unk803156C0 += 1;
  }
  D_hd_code_8036BF38 = osGetTime();
  if (g_currentRdpTask != NULL) {
    osViSwapBuffer(g_currentRdpTask->framebuffer);
    D_hd_code_8036BF18 = g_nextRetrace;
    g_nextRetrace = scheduler->retraceCount + 1;
    osDpSetStatus(DPC_SET_FREEZE);
    if (g_currentRdpTask->msgQ != NULL) {
      __scSendMesg(g_currentRdpTask->msgQ, g_currentRdpTask->msg, OS_MESG_NOBLOCK);
    }
    g_currentRdpTask = NULL;
  } else {
    if (osViGetCurrentFramebuffer() == osViGetNextFramebuffer() && (osDpGetStatus() & 2)) {
      scheduler->unk803156C8 = osGetTime();
      osDpSetStatus(DPC_CLR_FREEZE);
    }
  }
  for(sp38 = scheduler->cmdQ.validCount, sp3C = 0; sp3C < sp38; sp3C++) {
    if (osRecvMesg(&scheduler->cmdQ, (OSMesg*)&rspTask, OS_MESG_NOBLOCK) == -1) {
      rmonPrintf(ASSERT_MESSAGE, "osRecvMesg(&sc->cmdQ, (OSMesg *)&rspTask, OS_MESG_NOBLOCK) != -1", "sched.c", 0x1BD);
    }
    if (((u32) scheduler->retraceCount % (u32) rspTask->client->unk8) == 0) {
      __scAppendList(scheduler, rspTask);
    } else {
      osSendMesg(&scheduler->cmdQ, (OSMesg*)rspTask, OS_MESG_NOBLOCK);
    }
  }
  if ((scheduler->audioListHead != NULL) && !(scheduler->retraceCount & 1)) {
    osSetTimer(&D_hd_code_8036BF78, 0x445C0, 0, (OSMesgQueue* ) scheduler->audioListHead->client->msgQ, (void* )5);
  }
  for(client = scheduler->clientList; client != NULL; client = client->next) {
    if (client->unkC == 3) {
      osSendMesg(client->msgQ, (void* )0x29A, OS_MESG_NOBLOCK);
    }
  }
}

void __scRspDone(OSSched* scheduler) {
    OSScTask* rspTask;
    OSTime sp20;

    if (scheduler->curRSPTask == NULL) {
        rmonPrintf(ASSERT_MESSAGE, "sc->curRSPTask", "sched.c", 0x1F2);
    }
    rspTask = scheduler->curRSPTask;
    scheduler->curRSPTask = NULL;
    if (rspTask->state == RSP_STATE_SUSPENDED) {
        D_hd_code_8036BF00 = osGetTime() - D_hd_code_8036BEF0;
        if (D_hd_code_8036BF00 >= 0x86471U) {
            rmonPrintf("Silly yield time of %llu ticks\n", D_hd_code_8036BF00);
        }
        if (D_hd_code_8036BF00 > D_hd_code_8036BEF8) {
            D_hd_code_8036BEF8 = D_hd_code_8036BF00;
        }
        if (osSpTaskYielded(&rspTask->list) == 0) {
            rspTask->state = 2;
            rspTask->flags |= OS_SC_NEEDS_RDP << 2;
            func_hd_code_80271A84(scheduler, rspTask);
        }
        if (scheduler->audioListHead == NULL) {
            rmonPrintf(ASSERT_MESSAGE, "sc->audioListHead", "sched.c", 0x21A);
        }
        if (scheduler->audioListHead == NULL) {
            rmonPrintf("Yield took %llu, max %llu\n", D_hd_code_8036BF00, D_hd_code_8036BEF8);
        }
        __scExec(scheduler, EXEC_IS_AUDIO);
        return;
    }
    if (rspTask->flags & OS_SC_SWAPBUFFER) {
        sp20 = osGetTime();
        D_hd_code_8036BF24 = (sp20 - scheduler->unk803156D0) / 0x1E91;
        D_hd_code_802FA270 = 1;
    } else if (rspTask->list.t.type == M_AUDTASK) {
        D_hd_code_8036BF50 = osGetTime();
        D_hd_code_8036BF40 = D_hd_code_8036BF48;
    }
    rspTask->state = 2;
    rspTask->flags |= OS_SC_DRAM_DLIST;
    if (scheduler->curRSPTask != NULL) {
        rmonPrintf(ASSERT_MESSAGE, "sc->curRSPTask==0", "sched.c", 0x230);
    }
    if (func_hd_code_80271A84(scheduler, rspTask) != 0) {
        if (scheduler->gfxListHead != NULL && (scheduler->gfxListHead->flags != 0x47)) {
            __scExec(scheduler, EXEC_IS_GFX);
        }
    }
}

void __scRdpDone(OSSched* scheduler) {
  OSScTask* rdpTask;
  OSTime currentTime;

  if (scheduler->curRDPTask == NULL) {
    rmonPrintf(ASSERT_MESSAGE, "sc->curRDPTask", "sched.c", 0x24A);
  }
  rdpTask = scheduler->curRDPTask;
  scheduler->curRDPTask = NULL;
  rdpTask->flags |= OS_SC_NEEDS_RSP << 2;
  // N64 logo is:  D_hd_code_80364A90 = 0x0000000000000010 is true
  // Rare logo is: D_hd_code_80364A90 = 0x0000000000000020 is true
  if (scheduler->retraceCount != g_nextRetrace || g_currentGameState & 0xC9FD0FE79BFF80B0) {
    g_currentRdpTask = NULL;
    osViSwapBuffer(rdpTask->framebuffer);
    D_hd_code_8036BF18 = g_nextRetrace;
    g_nextRetrace = scheduler->retraceCount + 1;
    osDpSetStatus(DPC_SET_FREEZE);
  } else {
    g_currentRdpTask = rdpTask;
  }
  currentTime = osGetTime();
  D_hd_code_8036BF20 = (currentTime - scheduler->unk803156C8) / 0x1E91;
  if (g_frameCount == 3) {
    osViBlack(0U);
  }
  func_hd_code_80271A84(scheduler, rdpTask);
}

s32 func_hd_code_80271A84(OSSched* scheduler, OSScTask* rspOrRdpTask) {
  s32 rv;
  s32 sp20;
  s32 sp1C;
  u32 taskType;

  sp20 = rspOrRdpTask->flags & OS_SC_RCP_MASK;
  sp1C = ((u32) rspOrRdpTask->flags >> 2) & OS_SC_RCP_MASK;
  taskType = rspOrRdpTask->list.t.type;
  if (!(rspOrRdpTask->flags & OS_SC_SWAPBUFFER)) {
    sp20 = sp20 & OS_SC_NEEDS_RDP;
    sp1C = sp1C & OS_SC_NEEDS_RDP;
  }
  if (sp20 == sp1C) {
    if (taskType == M_GFXTASK) {
      if (scheduler->gfxListHead == NULL) {
        rmonPrintf(ASSERT_MESSAGE, "sc->gfxListHead", "sched.c", 0x27C);
      }
      scheduler->gfxListHead = scheduler->gfxListHead->next;
      if (scheduler->gfxListHead == NULL) {
        scheduler->gfxListTail = (OSScTask* ) &scheduler->gfxListHead;
      }
    }
    if (rspOrRdpTask->msgQ != NULL && (g_currentRdpTask == NULL || taskType != M_GFXTASK)) {
      if (rspOrRdpTask->flags & OS_SC_SWAPBUFFER) {
        rv = __scSendMesg(rspOrRdpTask->msgQ, rspOrRdpTask->msg, OS_MESG_NOBLOCK);
      } else {
        rv = osSendMesg(rspOrRdpTask->msgQ, rspOrRdpTask->msg, OS_MESG_NOBLOCK);
      }
      if (rv == -1) {
        rmonPrintf(ASSERT_MESSAGE, "rv!=-1", "sched.c", 0x289);
      }
    }
    D_hd_code_8036BFBC = 1;
  } else {
    D_hd_code_8036BFBC = 0;
  }
  return D_hd_code_8036BFBC;
}

void __scAppendList(OSSched* scheduler, OSScTask* task) {
  s32 taskType;

  taskType = task->list.t.type;
  if (!(taskType == M_AUDTASK || taskType == M_GFXTASK)) {
    rmonPrintf(ASSERT_MESSAGE, "(type == M_AUDTASK) || (type == M_GFXTASK)", "sched.c", 0x29C);
  }
  if (taskType == M_AUDTASK) {
    scheduler->audioListTail->next = task;
    scheduler->audioListTail = task;
  } else {
    scheduler->gfxListTail->next = task;
    scheduler->gfxListTail = task;
  }
  task->next = NULL;
  task->state = 2;
}

void __scExec(OSSched* scheduler, s32 type) {
  OSScTask* task;
  OSTime sp18;

  if (scheduler->curRSPTask != NULL) {
    rmonPrintf(ASSERT_MESSAGE, "!sc->curRSPTask", "sched.c", 0x2B8);
  }
  if (type == EXEC_IS_AUDIO) {
    task = scheduler->audioListHead;
    if (!task) {
      rmonPrintf(ASSERT_MESSAGE, "t", "sched.c", 0x2BD);
    }
    if (task) {
      scheduler->audioListHead = scheduler->audioListHead->next;
      if (scheduler->audioListHead == NULL) {
        scheduler->audioListTail = (OSScTask* ) &scheduler->audioListHead;
      }
      D_hd_code_8036BF48 = osGetTime();
    } else {
      return;
    }
  } else {
    task = scheduler->gfxListHead;
    if ((u8) D_hd_code_802FA270 != 0) {
      scheduler->unk803156D0 = osGetTime();
      sp18 = osGetTime();

      D_hd_code_8036BF2C = (sp18 - D_hd_code_8036BF38) / 0x1E91;
      D_hd_code_802FA270 = 0;
    }
  }

  task->state = 1;
  osSpTaskLoad(&task->list);
  osSpTaskStartGo(&task->list);
  scheduler->curRSPTask = task;
  if (task->flags & OS_SC_SWAPBUFFER) {
    scheduler->curRDPTask = task;
  }
}

void __scYield(OSSched* scheduler) {
  if (!(scheduler->curRSPTask->list.t.type != M_AUDTASK)) {
    rmonPrintf(ASSERT_MESSAGE, "sc->curRSPTask->list.t.type != M_AUDTASK", "sched.c", 0x2DF);
  }

  if (scheduler->curRSPTask->list.t.type == M_GFXTASK) {
    if (!(scheduler->curRSPTask->state != RSP_STATE_SUSPENDED)) {
      rmonPrintf(ASSERT_MESSAGE, "sc->curRSPTask->state != RSP_STATE_SUSPENDED", "sched.c", 0x2E3);
    }
    scheduler->curRSPTask->state = RSP_STATE_SUSPENDED;
    D_hd_code_8036BEF0 = osGetTime();
    osSpTaskYield();
  }
}

s32 __scSendMesg(OSMesgQueue* messageQueue, OSMesg message, s32 flags) {
  OSTime sp28;
  OSTime sp20;
  s32 sp1C;

  sp28 = D_hd_code_8036BF38 + 0x5F852 - osGetTime();
  sp20 = osGetTime();
  sp1C = 0;

  return osSendMesg(messageQueue, message, flags);
}
