#include "common.h"
#include "inflate.h"

s32 func_8022043C();
void func_802206D0(void);

s32 D_80222840 = 8;
s32 D_80222844 = 0;
const char D_802228D0[] = "kiunzip: unknown method %d -- get newer version of gzip\n";
extern struct huft *D_802229E0; // bss?
extern u8 *D_802229F0; // bss?
extern u8 *D_802229F4; // bss? 
extern s32 D_802229FC;
extern s32 D_80222A08;
extern s32 D_80222A0C;
extern s32 D_80222A18;
extern s32 D_80222A1C; // bss?
extern u32 D_80222A20; // bss?

void func_init_80220360(u8** arg0, u8** arg1, struct huft* arg2) {
    D_802229F0 = *arg0;
    D_802229F4 = *arg1;
    D_802229E0 = arg2;
    func_802206D0();
    if (D_802229F0[D_80222A1C] != 0x1F) {
        D_80222A1C += 1;
    }
    D_80222840 = func_8022043C();
    if (D_80222840 >= 0) {
        inflate();
        *arg0 += D_80222A1C;
        *arg1 += D_80222A20;
    }
}

// get_method
s32 func_8022043C(void) {
    u8 flags;
    s32 sp28;

    D_80222A1C += 2; // Skip gzip magic number 0x1F 0x8B
    D_80222840 = -1;
    D_802229FC = 0;
    D_80222840 = D_802229F0[D_80222A1C++];
    if (D_80222840 != 8) { // Compression mode != DEFLATE?
        osSyncPrintf(D_802228D0, D_80222840); /* kiunzip: unknown method %d -- get newer version of gzip\n */
        D_80222844 = 1;
        return -1;
    }
    
    flags = D_802229F0[D_80222A1C++];
    D_80222A1C += 6; // Skip rest of header
    
    if (flags & 2) { // has crc-16 checksum?
        D_80222A1C += 2; // then skip crc-16 checksum
    }

    if (flags & 4) { // has additional information?
        // read length of additional information
        sp28 = (D_802229F0[D_80222A1C++]);
        sp28 |= (D_802229F0[D_80222A1C++] << 8);
        
        // skip additional information
        D_80222A1C += sp28;
    }
  
    if (flags & 8) { // has original filename?
        while(D_802229F0[D_80222A1C++] != 0); // skip filename
    }

    if (flags & 16) { // has additional comment?
        while(D_802229F0[D_80222A1C++] != 0); // skip comment
    }
    // Skip crc32 checksum (4 byte) and size of original file (4 byte)
    D_802229FC = D_80222A1C + 8;
    return D_80222840;
}


u32 func_8022069C(u32 arg0, s32 arg1) {
    register u32 v1 = 0;
    do {
        v1 |= (arg0 & 1);
    } while (arg0 >>= 1, v1 <<= 1, --arg1 > 0);
    return v1 >> 1;
}

void func_802206D0(void) {
    D_80222A20 = 0;
    D_80222A1C = 0;
    D_80222A18 = 0;
    D_80222A0C = 0;
    D_80222A08 = 0;
}
