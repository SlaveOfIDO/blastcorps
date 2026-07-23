#ifndef HD_FRONT_END_STRUCTS_H
#define HD_FRONT_END_STRUCTS_H

#include <PR/ultratypes.h>

struct LevelData {
  /* 0x00 */ s32 unk0;
  /* 0x04 */ char *name;
  /* 0x08 */ s32 unk8;
  /* 0x0C */ s32 padC;
  /* 0x10 */ f32 unk10;
  /* 0x14 */ f32 unk14;
  /* 0x18 */ s8 unk18[0x1C - 0x18];
  /* 0x1C */ s8 unk1C[0x24 - 0x1C];
  /* 0x24 */ f32 unk24;
  /* 0x28 */ f32 unk28;
  /* 0x2C */ f32 unk2C;
};  /* Size: 0x30 */

extern struct LevelData D_hd_front_end_8020D810[];

struct S_8020BD30 {
  f32 unk0;
  s32 pad4;
  f32 unk8;
  f32 unkC;
  struct S_8020BD30 *unk10;
  struct S_8020BD30 *unk14;
  u8 unk18;
  u8 unk19;
  u8 unk1A;
  u8 pad1B;
  f32 unk1C;
  f32 unk20;
  f32 unk24;
  f32 unk28;
  f32 unk2C;
  f32 unk30;
  f32 unk34;
  f32 unk38;
};
extern struct S_8020BD30 D_hd_front_end_8020BD30;

#endif