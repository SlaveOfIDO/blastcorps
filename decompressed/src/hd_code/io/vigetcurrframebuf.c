#include "viint.h"
#include <PR/os_internal.h>

void *osViGetCurrentFramebuffer(void)
{
    register u32 saveMask;
    void *framep;
    saveMask = __osDisableInt();
    framep = __osViCurr->framep;
    __osRestoreInt(saveMask);
    return framep;
}
