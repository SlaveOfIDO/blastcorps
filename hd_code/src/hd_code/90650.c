#include "common.h"

// TODO: This is 99% a library function

struct S_802D4E10 {
  u8 pad0[0x2C];
  s32 unk2C;
};

s32 func_hd_code_802D4E10(struct S_802D4E10* arg0) {
  return arg0->unk2C;
}

