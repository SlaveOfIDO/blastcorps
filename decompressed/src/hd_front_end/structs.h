#ifndef HD_FRONT_END_STRUCTS_H
#define HD_FRONT_END_STRUCTS_H

#include <PR/ultratypes.h>

struct LevelData {
  /* 0x00 */ s32 unk0;
  /* 0x04 */ char *name;
  /* 0x08 */ u8 pad8[0x18 - 0x8];
  /* 0x18 */ s8 unk18[0x1C - 0x18];
  /* 0x1C */ s8 unk1C[0x30 - 0x1C];
};  /* Size: 0x30 */

extern struct LevelData D_hd_front_end_8020D810[];

#endif