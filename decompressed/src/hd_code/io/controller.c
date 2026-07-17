#include <PR/os_internal.h>
#include "controller.h"
#include "siint.h"


u32 _osContInitialized = 0;

OSPifRam __osContPifRam;
u8 __osContLastCmd;
u8 __osMaxControllers;
OSTimer __osEepromTimer;
OSMesgQueue __osEepromTimerQ;
OSMesg __osEepromTimerMsg;

s32 osContInit(OSMesgQueue *mq, u8 *bitpattern, OSContStatus *data)
{
  OSMesg dummy;
  s32 ret;
  OSTime t;
  OSTimer mytimer;
  OSMesgQueue timerMesgQueue;

  ret = 0;
  if (_osContInitialized)
    return ret;
  _osContInitialized = TRUE;
  t = osGetTime();
  if (500000 * osClockRate / 1000000 > t)
  {
    osCreateMesgQueue(&timerMesgQueue, &dummy, 1);
    osSetTimer(&mytimer, 500000 * osClockRate / 1000000 - t, 0, &timerMesgQueue, &dummy);
    osRecvMesg(&timerMesgQueue, &dummy, OS_MESG_BLOCK);
  }
  __osMaxControllers = MAXCONTROLLERS;
  __osPackRequestData(CONT_CMD_RESET);

  ret = __osSiRawStartDma(OS_WRITE, &__osContPifRam);
  osRecvMesg(mq, &dummy, OS_MESG_BLOCK);

  ret = __osSiRawStartDma(OS_READ, &__osContPifRam);
  osRecvMesg(mq, &dummy, OS_MESG_BLOCK);
  __osContGetInitData(bitpattern, data);
  __osContLastCmd = CONT_CMD_RESET;
  __osSiCreateAccessQueue();
  osCreateMesgQueue(&__osEepromTimerQ, &__osEepromTimerMsg, 1);
  return ret;
}

void __osContGetInitData(u8 *pattern, OSContStatus *data) {
    u8 *ptr;
    __OSContRequesFormat response;
    s32 i;
    u8 bits;

    bits = 0;
    ptr = (u8 *) __osContPifRam.ramarray;
    for (i = 0; i < __osMaxControllers; i++, ptr += sizeof(response), data++) {
        response = *REQFORMAT(ptr);
        data->errno = CHNL_ERR(response);
        if (data->errno == 0) {
            data->type = response.typel << 8 | response.typeh;
            data->status = response.status;

            bits |= 1 << i;
        }
    }

    *pattern = bits;
}

void __osPackRequestData(u8 cmd) {
    u8 *ptr;
    __OSContRequesFormat requestHeader;
    s32 i;

    for (i = 0; i < 16; i++) {
      __osContPifRam.ramarray[i] = 0;
    }
    __osContPifRam.pifstatus = CONT_CMD_EXE;

    ptr = (u8 *) __osContPifRam.ramarray;
    requestHeader.dummy = CONT_CMD_NOP;
    requestHeader.txsize = CONT_CMD_RESET_TX;
    requestHeader.rxsize = CONT_CMD_RESET_RX;
    requestHeader.cmd = cmd;
    requestHeader.typeh = CONT_CMD_NOP;
    requestHeader.typel = CONT_CMD_NOP;
    requestHeader.status = CONT_CMD_NOP;
    requestHeader.dummy1 = CONT_CMD_NOP;

    for (i = 0; i < __osMaxControllers; i++) {
        *REQFORMAT(ptr) = requestHeader;
        ptr += sizeof(requestHeader);
    }
    *ptr = CONT_CMD_END;
}
