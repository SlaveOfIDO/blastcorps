#include "common.h"
#include "functions.h"
#include "variables.h"

void func_hd_code_8025C230(s32* arg0, s32* arg1, s32 arg2) {
  D_803669C0 = *arg0;
  D_803669C4 = *arg1;
  D_8039CAE0 = arg2;
  func_hd_code_8025C5A0();
  if (D_803669C0[D_803669EC] != 0x1F) {
    D_803669EC += 1;
  }
  D_hd_code_802E8CC0 = func_hd_code_8025C30C();
  if (D_hd_code_802E8CC0 >= 0) {
    func_hd_code_802994F8();
    *arg0 += D_803669EC;
    *arg1 += D_803669F0;
  }
}

s32 func_hd_code_8025C30C(void) {
  u8 flags;
  s32 sp28;

  D_803669EC += 2; // Skip gzip magic number 0x1F 0x8B
  D_hd_code_802E8CC0 = -1;
  D_803669CC = 0;
  D_hd_code_802E8CC0 = D_803669C0[D_803669EC++];

  if (D_hd_code_802E8CC0 != 8) { // Compression mode != DEFLATE?
    func_hd_code_8029A7E4("kiunzip: unknown method %d -- get newer version of gzip\n", D_hd_code_802E8CC0);
    D_hd_code_802E8CC4 = 1;
    return -1;
  }

  flags = D_803669C0[D_803669EC++];
  D_803669EC+=6;

  if (flags & 2) {
    D_803669EC += 2;
  }
  if (flags & 4) {
    // read length of additional information
    sp28 = (D_803669C0[D_803669EC++]);
    sp28 |= (D_803669C0[D_803669EC++] << 8);

    // skip additional information
    D_803669EC += sp28;
  }

  if (flags & 8) { // has original filename?
    while(D_803669C0[D_803669EC++] != 0); // skip filename
  }

  if (flags & 16) { // has additional comment?
    while(D_803669C0[D_803669EC++] != 0); // skip comment
  }
  // Skip crc32 checksum (4 byte) and size of original file (4 byte)
  D_803669CC = D_803669EC + 8;
  return D_hd_code_802E8CC0;
}

u32 func_hd_code_8025C56C(u32 arg0, s32 arg1) {
  register u32 v1 = 0;
  do {
    v1 |= (arg0 & 1);
  } while (arg0 >>= 1, v1 <<= 1, --arg1 > 0);
  return v1 >> 1;
}

void func_hd_code_8025C5A0(void) {
  D_803669F0 = 0;
  D_803669EC = 0;
  D_803669E8 = 0;
  D_803669DC = 0;
  D_803669D8 = 0;
}

