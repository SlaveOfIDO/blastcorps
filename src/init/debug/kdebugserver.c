#include "common.h"
#include <ultra64.h>
#include <PR/rdb.h>

// TODO: This file is perhaps this https://github.com/ExcellentGamer/sm64ds-remastered/blob/bf7e2acf57b36518b5927a3e9a11b8d30a59e49e/lib/ultra/debug/kdebugserver.c#L36

static s32 debugState = 0;
static s32 numChars = 0;
static s32 numCharsToReceive = 0;

// .bss
extern u8 debugBuffer[0x100];

extern OSThread __osThreadSave;

void func_80221E10(u32 arg0, u8* arg1) {
    arg1[0] = ((arg0 >> 24) & 0xFF);
    arg1[1] = ((arg0 >> 16) & 0xFF);
    arg1[2] = ((arg0 >> 8) & 0xFF);
    arg1[3] = (arg0 & 0xFF);
}

u32 func_80221E40(u8 *arg0) {
    u32 sp4;

    sp4 = ((arg0[0] & 0xFF) << 24);
    sp4 |= ((arg0[1] & 0xFF) << 16);
    sp4 |= ((arg0[2] & 0xFF) << 8);
    sp4 |= (arg0[3] & 0xFF);
    
    return sp4;
}

void func_80221E98(u8 buf[], s32 length) {
    rdbPacket packet;
    int i;

    packet.type = 2;
    packet.length = length;
    for(i = 0; i < length; i++) {
            packet.buf[i] = buf[i];        
    }
    *(u32* )RDB_BASE_REG = *(u32*)&packet;
    while (!(__osGetCause() & CAUSE_IP6))
      ;
    *(u32* )RDB_READ_INTR_REG = 0;
}

void func_80221F58(u8 buf[], s32 length) {
    s32 i;
    s32 sp20;
    s32 sp1C;

    if (__osRdbWriteOK == 0) {
        while (!(__osGetCause() & CAUSE_IP6));
        *(u32* )RDB_READ_INTR_REG = 0;
        
        __osRdbWriteOK = 1;
    }
    sp1C = length % 3;
    sp20 = length - sp1C;
    for(i = 0; i < sp20; i += 3) {
        func_80221E98(&buf[i], 3);
    }
    if (sp1C > 0) {
        func_80221E98(&buf[sp20], sp1C);
    }
}
    
void func_80222030(void) {
    u32 data;
    s32 length;

    data = func_80221E40(&debugBuffer[1]);
    length = func_80221E40(&debugBuffer[5]);
    func_80221F58(data, length);
}

void func_8022207C(void) {
    func_80221F58((u8*)(&__osThreadSave.context), 0x190);
}

void func_init_802220A8(u32 packet) {
    u32 i;
    rdbPacket sp28;
    
    *(u32 *) &sp28 = packet;

    for(i = 0; i < sp28.length; i++) {
        debugBuffer[numChars++] = sp28.buf[i];
    }
    numCharsToReceive -= sp28.length;
    switch (debugState) {                           /* irregular */
    case 0:
        switch (sp28.buf[0]) {                          /* switch 1; irregular */
        case 1:                                     /* switch 1 */
            debugState = 1;
            numCharsToReceive = 9 - (sp28.length);
            return;
        case 2:                                     /* switch 1 */
            func_8022207C();
            debugState = 0;
            numChars = 0;
            numCharsToReceive = 0;
            return;
        default:                                    /* switch 1 */
            debugState = 0;
            numChars = 0;
            numCharsToReceive = 0;
            return;
        }
        break;
    case 1:
        if (numCharsToReceive <= 0) {
            if (debugBuffer[0] == 1) {
                func_80222030();
                debugState = 0;
                numChars = 0;
                numCharsToReceive = 0;
                return;
            } else {
                debugState = 0;
                numChars = 0;
                numCharsToReceive = 0;
                return;
            }
            return;
        }
        break;
    default:
        debugState = 0;
        numChars = 0;
        numCharsToReceive = 0;
    }
 
}

