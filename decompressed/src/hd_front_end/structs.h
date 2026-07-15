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
  /* 0x00 */ f32 unk0;
  /* 0x04 */ u8 pad4[0x4];
  /* 0x08 */ f32 unk8;
  /* 0x0C */ f32 unkC;
  /* 0x10 */ struct S_8020BD30 *unk10;   /* next sibling */
  /* 0x14 */ struct S_8020BD30 *unk14;   /* first child  */
  /* 0x18 */ u8 unk18;                  /* prim color r */
  /* 0x19 */ u8 unk19;                  /* prim color g */
  /* 0x1A */ u8 unk1A;                  /* prim color b */
  /* 0x1B */ u8 pad1B;
  /* 0x1C */ f32 unk1C;                 /* rotation/angle, [0x1C..0x28) is a vec3 */
  /* 0x20 */ f32 unk20;
  /* 0x24 */ f32 unk24;
  /* 0x28 */ f32 unk28;
  /* 0x2C */ f32 unk2C;
  /* 0x30 */ f32 unk30;
  /* 0x34 */ f32 unk34;
  f32 unk38;
};  /* stride 0x3C */
extern struct S_8020BD30 D_hd_front_end_8020BD30[];

#endif