#include <stdarg.h>
#include <rmon.h>
#include <os.h>

char D_init_80222A30[0x2000]; // assumed unused buffer

void func_init_80220700(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {

}

void osSyncPrintf(const char *fmt, ...) {
    // these functions intentionally left blank.  ifdeffed out in rom release
}
