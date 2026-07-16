#include <PR/os_internal.h>
#include <PR/R4300.h>
#include <PR/rcp.h>
#include "viint.h"

__OSViContext vi[2] = { 0 };
__OSViContext *__osViCurr = &vi[0];
__OSViContext *__osViNext = &vi[1];

u32 osIsNtscEnabled = TRUE; // OS_TV_NTSC
u32 osViClock = VI_NTSC_CLOCK;

void __osViInit(void) {
    osIsNtscEnabled = osTvType;

    bzero(vi, sizeof(vi));
    __osViCurr = &vi[0];
    __osViNext = &vi[1];
    __osViNext->retraceCount = 1;
    __osViCurr->retraceCount = 1;

    if (osIsNtscEnabled == TRUE) {
        __osViNext->modep = &osViModeNtscLan1;
        osViClock = VI_NTSC_CLOCK;
    } else {
        __osViNext->modep = &osViModePalLan1;
        osViClock = VI_MPAL_CLOCK;
    }
    __osViNext->state = VI_STATE_BLACK;
    __osViNext->control = __osViNext->modep->comRegs.ctrl;

    while (IO_READ(VI_CURRENT_REG) > 10) { //wait for vsync?
    }

    IO_WRITE(VI_STATUS_REG, 0); //pixel size blank (no data, no sync)
    __osViSwapContext();
}
