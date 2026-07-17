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


void func_hd_code_80271E88(OSSched*);                  /* extern */
void func_hd_code_802712B4(OSSched*, void*);       /* extern */
void func_hd_code_802712FC(OSSched*);              /* extern */
void func_hd_code_80271358(OSSched*);              /* extern */
void func_hd_code_802715DC(OSSched*);              /* extern */
void func_hd_code_80271904(OSSched*);              /* extern */
s32 func_hd_code_802A1320();                        /* extern */
void __scMain(void*);                               /* extern */
void func_hd_code_80271C24(OSSched*, OSScTask*);           /* extern */
void func_hd_code_80271CE4(OSSched*, s32);               /* extern */
s32 func_hd_code_80271F48(OSMesgQueue* arg0, OSMesg arg1, s32 arg2);               /* extern */
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
s32 D_hd_code_8036BF14;
s32 D_hd_code_8036BF18;
OSScTask* D_hd_code_8036BF1C;
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
  D_hd_code_8036BF1C = 0;
  osCreateMesgQueue(&s->interruptQ, s->intBuf, 0x10);
  osCreateMesgQueue(&s->cmdQ, s->cmdMsgBuf, 0x10);
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

void __scMain(void* arg0) {
    OSMesg sp34;
    OSSched* sp30;
    OSScClient* sp2C;

    sp30 = arg0;
    while(1) {
        osRecvMesg(&sp30->interruptQ, &sp34, OS_MESG_BLOCK);
        if (!(func_hd_code_802A1320() & 0x1000)) {

            for (sp2C = sp30->clientList; sp2C != NULL; sp2C = sp2C->next) {
                osSendMesg(sp2C->msgQ, (void* )0x29D, 0);
            }
            D_hd_code_8036BF10 = 1;
            osViBlack(1U);
            rmonPrintf("GO %x\n", osDpGetStatus());
            osDpSetStatus(4U);
            RCP_STAT_PRINT;
            rmonPrintf("GO %x\n", osDpGetStatus());
            while(1);
        }
        switch ((s32)sp34 - 0x29A) {
        case VIDEO_MSG:
            D_hd_code_8036BFB8++;
            if ((D_hd_code_8036BFB8 % 480U) == 0) {
                D_hd_code_8036BEF8 = D_hd_code_8036BF00;
                D_hd_code_8036BF08 = D_hd_code_8036BF0C;
            }
            func_hd_code_80271358(sp30);
            break;
        case 4:
            func_hd_code_802712FC(sp30);
            break;
        case RSP_DONE_MSG:
            func_hd_code_802715DC(sp30);
            break;
        case RDP_DONE_MSG:
            func_hd_code_80271904(sp30);
            break;
        case 5:
            osSendMesg(D_hd_code_8036BF78.mq, D_hd_code_8036BF78.msg, 1);
            break;
        case PRE_NMI_MSG:
            for (sp2C = sp30->clientList; sp2C != NULL; sp2C = sp2C->next) {
                osSendMesg(sp2C->msgQ, (void* )0x29D, 0);
            }
            D_hd_code_8036BF10 = 1;
            osViBlack(TRUE);
            rmonPrintf("%x\n", osDpGetStatus());
            osDpSetStatus(4U);
            RCP_STAT_PRINT;
            rmonPrintf("%x\n", osDpGetStatus());
            while(1);
        case 6:
            rmonPrintf(" *** CPU FAULT *** - UNFREEZING RDP?\n");
            while (osViGetCurrentFramebuffer() != osViGetNextFramebuffer()) {

            }
            osDpSetStatus(4U);
            while(1);
        default:
            func_hd_code_802712B4(sp30, sp34);
            break;
        }
    }
}

void func_hd_code_802712B4(OSSched* arg0, void* arg1) {
  func_hd_code_80271C24(arg0, arg1);
  if (arg0->curRSPTask == NULL) {
    func_hd_code_80271CE4(arg0, 1);
  }
}

void func_hd_code_802712FC(OSSched* arg0) {
  if (arg0->curRSPTask != NULL) {
    func_hd_code_80271E88(arg0);
    return;
  }
  D_hd_code_8036BF00 = 0;
  func_hd_code_80271CE4(arg0, 0);
}

void func_hd_code_80271358(OSSched* arg0) {
  OSScTask* sp44;
  OSScClient* sp40;
  s32 sp3C;
  s32 sp38;

  arg0->unk803156C4 += 1;
  if (D_hd_code_802E8BD0 == 0) {
    arg0->unk803156C0 += 1;
  }
  D_hd_code_8036BF38 = osGetTime();
  if (D_hd_code_8036BF1C != NULL) {
    osViSwapBuffer(D_hd_code_8036BF1C->framebuffer);
    D_hd_code_8036BF18 = D_hd_code_8036BF14;
    D_hd_code_8036BF14 = arg0->unk803156C4 + 1;
    osDpSetStatus(8U);
    if (D_hd_code_8036BF1C->msg != NULL) {
      func_hd_code_80271F48(D_hd_code_8036BF1C->msg, D_hd_code_8036BF1C->unk58, 0);
    }
    D_hd_code_8036BF1C = NULL;
  } else {
    if ((osViGetCurrentFramebuffer() == osViGetNextFramebuffer()) && (osDpGetStatus() & 2)) {
      arg0->unk803156C8 = osGetTime();
      osDpSetStatus(4U);
    }
  }
  for(sp38 = arg0->cmdQ.validCount, sp3C = 0; sp3C < sp38; sp3C++) {
    if (osRecvMesg(&arg0->cmdQ, (OSMesg*)&sp44, 0) == -1) {
      rmonPrintf(ASSERT_MESSAGE, "osRecvMesg(&sc->cmdQ, (OSMesg *)&rspTask, OS_MESG_NOBLOCK) != -1", "sched.c", 0x1BD);
    }
    if (((u32) arg0->unk803156C4 % (u32) sp44->msgQ->validCount) == 0) {
      func_hd_code_80271C24(arg0, sp44);
    } else {
      osSendMesg(&arg0->cmdQ, (OSMesg*)sp44, 0);
    }
  }
  if ((arg0->audioListHead != NULL) && !(arg0->unk803156C4 & 1)) {
    osSetTimer(&D_hd_code_8036BF78, 0x445C0, 0, (OSMesgQueue* ) arg0->audioListHead->msgQ->fullqueue, (void* )5);
  }
  for(sp40 = arg0->clientList; sp40 != NULL; sp40 = sp40->next) {
    if (sp40->unkC == 3) {
      osSendMesg(sp40->msgQ, (void* )0x29A, 0);
    }
  }
}

void func_hd_code_802715DC(OSSched* arg0) {
    OSScTask* sp2C;
    OSTime sp20;

    if (arg0->curRSPTask == NULL) {
        rmonPrintf(ASSERT_MESSAGE, "sc->curRSPTask", "sched.c", 0x1F2);
    }
    sp2C = arg0->curRSPTask;
    arg0->curRSPTask = NULL;
    if (sp2C->state == 3) {
        D_hd_code_8036BF00 = osGetTime() - D_hd_code_8036BEF0;
        if (D_hd_code_8036BF00 >= 0x86471U) {
            rmonPrintf("Silly yield time of %llu ticks\n", D_hd_code_8036BF00);
        }
        if (D_hd_code_8036BF00 > D_hd_code_8036BEF8) {
            D_hd_code_8036BEF8 = D_hd_code_8036BF00;
        }
        if (osSpTaskYielded(&sp2C->list) == 0) {
            sp2C->state = 2;
            sp2C->flags |= 4;
            func_hd_code_80271A84(arg0, sp2C);
        }
        if (arg0->audioListHead == NULL) {
            rmonPrintf(ASSERT_MESSAGE, "sc->audioListHead", "sched.c", 0x21A);
        }
        if (arg0->audioListHead == NULL) {
            rmonPrintf("Yield took %llu, max %llu\n", D_hd_code_8036BF00, D_hd_code_8036BEF8);
        }
        func_hd_code_80271CE4(arg0, 0);
        return;
    }
    if (sp2C->flags & 0x40) {
        sp20 = osGetTime();
        D_hd_code_8036BF24 = (sp20 - arg0->unk803156D0) / 0x1E91;
        D_hd_code_802FA270 = 1;
    } else if (sp2C->list.t.type == 2) {
        D_hd_code_8036BF50 = osGetTime();
        D_hd_code_8036BF40 = D_hd_code_8036BF48;
    }
    sp2C->state = 2;
    sp2C->flags |= 4;
    if (arg0->curRSPTask != NULL) {
        rmonPrintf(ASSERT_MESSAGE, "sc->curRSPTask==0", "sched.c", 0x230);
    }
    if (func_hd_code_80271A84(arg0, sp2C) != 0) {
        if ((arg0->gfxListHead != NULL) && (arg0->gfxListHead->flags != 0x47)) {
            func_hd_code_80271CE4(arg0, 1);
        }
    }
}

void func_hd_code_80271904(OSSched* arg0) {
  OSScTask* sp24;
  OSTime sp18;

  if (arg0->curRDPTask == NULL) {
    rmonPrintf(ASSERT_MESSAGE, "sc->curRDPTask", "sched.c", 0x24A);
  }
  sp24 = arg0->curRDPTask;
  arg0->curRDPTask = NULL;
  sp24->flags |= 8;
  if ((arg0->unk803156C4 != D_hd_code_8036BF14) || (D_hd_code_80364A90 & 0xC9FD0FE79BFF80B0)) {
    D_hd_code_8036BF1C = NULL;
    osViSwapBuffer(sp24->framebuffer);
    D_hd_code_8036BF18 = D_hd_code_8036BF14;
    D_hd_code_8036BF14 = arg0->unk803156C4 + 1;
    osDpSetStatus(8U);
  } else {
    D_hd_code_8036BF1C = sp24;
  }
  sp18 = osGetTime();
  D_hd_code_8036BF20 = (sp18 - arg0->unk803156C8) / 0x1E91;
  if (D_hd_code_80358060 == 3) {
    osViBlack(0U);
  }
  func_hd_code_80271A84(arg0, sp24);
}

s32 func_hd_code_80271A84(OSSched* arg0, OSScTask* arg1) {
  s32 sp24;
  s32 sp20;
  s32 sp1C;
  u32 sp18;

  sp20 = arg1->flags & 3;
  sp1C = ((u32) arg1->flags >> 2) & 3;
  sp18 = arg1->list.t.type;
  if (!(arg1->flags & 0x40)) {
    sp20 = sp20 & 1;
    sp1C = sp1C & 1;
  }
  if (sp20 == sp1C) {
    if (sp18 == 1) {
      if (arg0->gfxListHead == NULL) {
        rmonPrintf(ASSERT_MESSAGE, "sc->gfxListHead", "sched.c", 0x27C);
      }
      arg0->gfxListHead = arg0->gfxListHead->next;
      if (arg0->gfxListHead == NULL) {
        arg0->gfxListTail = (OSScTask* ) &arg0->gfxListHead;
      }
    }
    if ((arg1->msg != NULL) && ((D_hd_code_8036BF1C == NULL) || (sp18 != 1))) {
      if (arg1->flags & 0x40) {
        sp24 = func_hd_code_80271F48((s32) arg1->msg, arg1->unk58, 0);
      } else {
        sp24 = osSendMesg((OSMesgQueue* ) arg1->msg, (void* ) arg1->unk58, 0);
      }
      if (sp24 == -1) {
        rmonPrintf(ASSERT_MESSAGE, "rv!=-1", "sched.c", 0x289);
      }
    }
    D_hd_code_8036BFBC = 1;
  } else {
    D_hd_code_8036BFBC = 0;
  }
  return D_hd_code_8036BFBC;
}

// __scAppendList
void func_hd_code_80271C24(OSSched* arg0, OSScTask* arg1) {
  s32 sp1C;

  sp1C = arg1->list.t.type;
  if (!(sp1C == M_AUDTASK || sp1C == M_GFXTASK)) {
    rmonPrintf(ASSERT_MESSAGE, "(type == M_AUDTASK) || (type == M_GFXTASK)", "sched.c", 0x29C);
  }
  if (sp1C == M_AUDTASK) {
    arg0->audioListTail->next = arg1;
    arg0->audioListTail = arg1;
  } else {
    arg0->gfxListTail->next = arg1;
    arg0->gfxListTail = arg1;
  }
  arg1->next = NULL;
  arg1->state = 2;
}

// __scExec
void func_hd_code_80271CE4(OSSched* arg0, s32 arg1) {
  OSScTask* sp24;
  OSTime sp18;

  if (arg0->curRSPTask != NULL) {
    rmonPrintf(ASSERT_MESSAGE, "!sc->curRSPTask", "sched.c", 0x2B8);
  }
  if (arg1 == NULL) {
    sp24 = arg0->audioListHead;
    if (!sp24) {
      rmonPrintf(ASSERT_MESSAGE, "t", "sched.c", 0x2BD);
    }
    if (sp24) {
      arg0->audioListHead = arg0->audioListHead->next;
      if (arg0->audioListHead == NULL) {
        arg0->audioListTail = (OSScTask* ) &arg0->audioListHead;
      }
      D_hd_code_8036BF48 = osGetTime();
    } else {
      return;
    }
  } else {
    sp24 = arg0->gfxListHead;
    if ((u8) D_hd_code_802FA270 != 0) {
      arg0->unk803156D0 = osGetTime();
      sp18 = osGetTime();

      D_hd_code_8036BF2C = (sp18 - D_hd_code_8036BF38) / 0x1E91;
      D_hd_code_802FA270 = 0;
    }
  }

  sp24->state = 1;
  osSpTaskLoad(&sp24->list);
  osSpTaskStartGo(&sp24->list);
  arg0->curRSPTask = sp24;
  if (sp24->flags & 0x40) {
    arg0->curRDPTask = sp24;
  }
}

// __scYield
void func_hd_code_80271E88(OSSched* sc) {
  if (!(sc->curRSPTask->list.t.type != M_AUDTASK)) {
    rmonPrintf(ASSERT_MESSAGE, "sc->curRSPTask->list.t.type != M_AUDTASK", "sched.c", 0x2DF);
  }

  if (sc->curRSPTask->list.t.type == M_GFXTASK) {
    if (!(sc->curRSPTask->state != RSP_STATE_SUSPENDED)) {
      rmonPrintf(ASSERT_MESSAGE, "sc->curRSPTask->state != RSP_STATE_SUSPENDED", "sched.c", 0x2E3);
    }
    sc->curRSPTask->state = 3;
    D_hd_code_8036BEF0 = osGetTime();
    osSpTaskYield();
  }
}

s32 func_hd_code_80271F48(OSMesgQueue* arg0, OSMesg arg1, s32 arg2) {
  OSTime sp28;
  OSTime sp20;
  s32 sp1C;

  sp28 = D_hd_code_8036BF38 + 0x5F852 - osGetTime();
  sp20 = osGetTime();
  sp1C = 0;

  return osSendMesg(arg0, arg1, arg2);
}
