/*
 * Building movement animation.
 *
 * Called from the building draw loop (func_hd_code_802BD1F8 in 00000.c, the
 * hand-written asm block at 0x802BD2FC): for each building whose header has a
 * nonzero u16 "movement type" at offset 0xE, func_hd_code_802933A0 is called
 * with the building's positions, its per-building state struct (building+0x38),
 * its "counter" parameter (building+0x34), a Mtx from a pool, and the two
 * display lists. The resulting world position is written to D_803F7664/68/6C
 * and stored back by the caller as the building's current position.
 *
 * Movement types (switch in func_hd_code_802933A0):
 *   1 = bob vertically (sine)            -> func_hd_code_80294C50
 *   2 = tumble/spin about a tilted axis  -> func_hd_code_80294D24
 *   3 = follow a cardinal-spline path    -> func_hd_code_80293F84
 *   4 = drive along roads, chase player  -> func_hd_code_802936AC
 *   5 = one-shot rotate (up to 90 deg)   -> func_hd_code_80294B64
 */
#include "common.h"
#include "functions.h"
#include "gu/guint.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"

/* Proposed name: BuildingMoveState
 * Per-building animation state, located at building+0x38.
 * Field meaning depends on the movement type:
 *   type 1: unk0 = sine phase counter
 *   type 2: unk0 = rotation angle (degrees)
 *   type 3: unk0 = current waypoint index, unk4 = segment progress (0..999)
 *   type 4: unk0 = direction bits (1=+z 2=-z 4=+x 8=-x), unk4 = heading
 *           (degrees), unk8 = index of last visited road junction
 *   type 5: unk0 = start frame (armed on first call), unk4 = angle (degrees) */
struct S_802936AC {
  s32 unk0;
  s32 unk4;
  s32 unk8;
};

void func_hd_code_802936AC(f32 (*arg0)[4], s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16* arg5, s16* arg6, s16* arg7, struct S_802936AC* arg8, s32 arg9);
void func_hd_code_80293F84(f32 (*arg0)[4], s16 arg1, s16 arg2, s16* arg3, s16* arg4, s16* arg5, struct S_802936AC* arg6, s32 arg7);
void func_hd_code_80294B64(f32 (*arg0)[4], s32 arg1, s16* arg2, s16* arg3, s16* arg4, struct S_802936AC* arg5, s32 arg6);
void func_hd_code_80294C50(f32 (*arg0)[4], s16* arg1, s16* arg2, s16* arg3, struct S_802936AC* arg4, s32 arg5);
void func_hd_code_80294D24(f32 (*arg0)[4], s16* arg1, s16* arg2, s16* arg3, struct S_802936AC* arg4, s32 arg5);
extern f32 D_8039CA10[4][4]; /* proposed: gSplineBasisMtx — cardinal-spline basis matrix */
extern s32 D_803F7664; /* proposed: gMovedBuildingX — output world position, read back by the draw loop */
extern s32 D_803F7668; /* proposed: gMovedBuildingY */
extern s32 D_803F766C; /* proposed: gMovedBuildingZ */
extern f32 D_hd_code_8030CD50;

/* Proposed name: RoadJunction
 * Road junction table entry for movement type 4 (drive along roads). */
struct S_802FEDA0 {
  u8 unk0;  /* level number (compared against levelno) */
  u8 pad1;
  s16 unk2; /* grid x (world x >> 5) */
  s16 unk4; /* grid z (world z >> 5) */
  u8 unk6;  /* allowed exit directions: 1=+z 2=-z 4=+x 8=-x */
  u8 pad7;
}; // Size: 0x8


f32 func_hd_code_80294840(f32, f32, f32, f32);      /* extern */
void func_hd_code_802949B0(s32);                       /* extern */
extern f32 D_8039CA50; /* proposed: gSplineT  — interpolation parameter t */
extern f32 D_8039CA54; /* proposed: gSplineT2 — t^2 */
extern f32 D_8039CA58; /* proposed: gSplineT3 — t^3 */

/* Proposed name: BuildingPathNode — one waypoint of a movement type 3 path. */
struct S_802FE980_sub {
  s16 unk0; /* x */
  s16 unk2; /* y */
  s16 unk4; /* z */
  s16 unk6; /* x rotation (degrees) */
  s16 unk8; /* y rotation (degrees) */
  s16 unkA; /* z rotation (degrees) */
}; // Size: 0xC

/* Proposed name: BuildingPath — spline path for movement type 3,
 * indexed by the building's "counter" parameter. */
struct S_802FE980 {
  struct S_802FE980_sub unk0[10];
  s32 unk78; /* node count */
  f32 unk7C; /* spline tension (0.5 = Catmull-Rom) */
  u8 unk80;  /* speed (segment progress per frame, out of 1000) */
  u8 unk81; // D_hd_code_802FEA01 /* y mode: 0 = spline y, 1 = clamp to terrain height */
  u8 pad82;
  u8 pad83;
}; // Size: 0x84

// <data>
/* proposed: gBuildingPaths */
struct S_802FE980 D_hd_code_802FE980[8] = {
    { { { 0xFEFC, 0x0000, 0x0154, 0x0000, 0x0000, 0x0000 }, { 0xFE70, 0x0000, 0xFE70, 0x0000, 0x0000, 0x0000 }, { 0x012C, 0x0000, 0xFE34, 0x0000, 0x0000, 0x0000 }, { 0x0258, 0x0000, 0xFFD8, 0x0000, 0x0000, 0x0000 }, { 0x0118, 0x0000, 0x01B8, 0x0000, 0x0000, 0x0000 }, { 0xFEFC, 0x0000, 0x0154, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 } }, 0x00000006, 0.5f, 0x14, 0x01, 0x00, 0x00 },
    { { { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0xFE70, 0x0000, 0xFD44, 0x0000, 0x0000, 0x0000 }, { 0x012C, 0x0000, 0xFD08, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0xFE70, 0x0000, 0x02BC, 0x0000, 0x0000, 0x0000 }, { 0x012C, 0x0000, 0x02BC, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 } }, 0x00000007, 0.5f, 0x14, 0x01, 0x00, 0x00 },
    { { { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0xFF9C, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0258, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 } }, 0x00000005, 0.5f, 0x32, 0x00, 0x00, 0x00 },
    { { { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0064, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0xFDA8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 } }, 0x00000005, 0.5f, 0x32, 0x00, 0x00, 0x00 },
    { { { 0x0000, 0xFFF9, 0x0000, 0x0000, 0x0000, 0x0003 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0xFFF9, 0x0000, 0x0000, 0x0000, 0xFFFD }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0xFFF9, 0x0000, 0x0000, 0x0000, 0x0003 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 } }, 0x00000005, 0.5f, 0x1E, 0x00, 0x00, 0x00 },
    { { { 0x0000, 0xFFF9, 0x0000, 0x0003, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0xFFF9, 0x0000, 0xFFFD, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0xFFF9, 0x0000, 0x0003, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 } }, 0x00000005, 0.5f, 0x1E, 0x00, 0x00, 0x00 },
    { { { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x005A, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x00B4, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x010E, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 } }, 0x00000005, 0.5f, 0x1E, 0x00, 0x00, 0x00 },
    { { { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x012C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x012C, 0x0000, 0x0000, 0x0000, 0x00B4, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x00B4, 0x0000 }, { 0xFED4, 0x0000, 0x0000, 0x0000, 0x00B4, 0x0000 }, { 0xFED4, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 } }, 0x00000005, 0.5f, 0x32, 0x00, 0x00, 0x00 }
};

/* proposed: gRoadJunctions — 0x66 entries */
struct S_802FEDA0 D_hd_code_802FEDA0[102] = {
    { 0x17, 0x00, 0x04E2, 0x02EE, 0x0D, 0x00 },
    { 0x17, 0x00, 0x03B6, 0x02EE, 0x05, 0x00 },
    { 0x17, 0x00, 0x06D6, 0x02EE, 0x0D, 0x00 },
    { 0x17, 0x00, 0x0802, 0x02EE, 0x09, 0x00 },
    { 0x17, 0x00, 0x0226, 0x03B6, 0x05, 0x00 },
    { 0x17, 0x00, 0x0352, 0x03B6, 0x0D, 0x00 },
    { 0x17, 0x00, 0x03B6, 0x03B6, 0x0B, 0x00 },
    { 0x17, 0x00, 0x04E2, 0x03B6, 0x07, 0x00 },
    { 0x17, 0x00, 0x05DC, 0x03B6, 0x0D, 0x00 },
    { 0x17, 0x00, 0x06D6, 0x03B6, 0x0B, 0x00 },
    { 0x17, 0x00, 0x0802, 0x03B6, 0x07, 0x00 },
    { 0x17, 0x00, 0x0866, 0x03B6, 0x0D, 0x00 },
    { 0x17, 0x00, 0x0992, 0x03B6, 0x09, 0x00 },
    { 0x17, 0x00, 0x0352, 0x041A, 0x07, 0x00 },
    { 0x17, 0x00, 0x03B6, 0x041A, 0x0E, 0x00 },
    { 0x17, 0x00, 0x04E2, 0x041A, 0x0B, 0x00 },
    { 0x17, 0x00, 0x06D6, 0x041A, 0x07, 0x00 },
    { 0x17, 0x00, 0x0802, 0x041A, 0x0E, 0x00 },
    { 0x17, 0x00, 0x0866, 0x041A, 0x0B, 0x00 },
    { 0x17, 0x00, 0x0226, 0x047E, 0x06, 0x00 },
    { 0x17, 0x00, 0x0352, 0x047E, 0x0B, 0x00 },
    { 0x17, 0x00, 0x0866, 0x047E, 0x07, 0x00 },
    { 0x17, 0x00, 0x0992, 0x047E, 0x0A, 0x00 },
    { 0x17, 0x00, 0x0352, 0x04E2, 0x07, 0x00 },
    { 0x17, 0x00, 0x041A, 0x04E2, 0x0D, 0x00 },
    { 0x17, 0x00, 0x04E2, 0x04E2, 0x0F, 0x00 },
    { 0x17, 0x00, 0x05DC, 0x04E2, 0x0E, 0x00 },
    { 0x17, 0x00, 0x06D6, 0x04E2, 0x0F, 0x00 },
    { 0x17, 0x00, 0x079E, 0x04E2, 0x0D, 0x00 },
    { 0x17, 0x00, 0x0866, 0x04E2, 0x0B, 0x00 },
    { 0x17, 0x00, 0x0226, 0x0546, 0x05, 0x00 },
    { 0x17, 0x00, 0x0352, 0x0546, 0x0B, 0x00 },
    { 0x17, 0x00, 0x0866, 0x0546, 0x07, 0x00 },
    { 0x17, 0x00, 0x0992, 0x0546, 0x09, 0x00 },
    { 0x17, 0x00, 0x0352, 0x05DC, 0x07, 0x00 },
    { 0x17, 0x00, 0x041A, 0x05DC, 0x0B, 0x00 },
    { 0x17, 0x00, 0x079E, 0x05DC, 0x07, 0x00 },
    { 0x17, 0x00, 0x0866, 0x05DC, 0x0B, 0x00 },
    { 0x17, 0x00, 0x0226, 0x0672, 0x06, 0x00 },
    { 0x17, 0x00, 0x0352, 0x0672, 0x0B, 0x00 },
    { 0x17, 0x00, 0x0866, 0x0672, 0x07, 0x00 },
    { 0x17, 0x00, 0x0992, 0x0672, 0x0A, 0x00 },
    { 0x17, 0x00, 0x0352, 0x06D6, 0x07, 0x00 },
    { 0x17, 0x00, 0x041A, 0x06D6, 0x0E, 0x00 },
    { 0x17, 0x00, 0x04E2, 0x06D6, 0x0F, 0x00 },
    { 0x17, 0x00, 0x05DC, 0x06D6, 0x0D, 0x00 },
    { 0x17, 0x00, 0x06D6, 0x06D6, 0x0F, 0x00 },
    { 0x17, 0x00, 0x079E, 0x06D6, 0x0E, 0x00 },
    { 0x17, 0x00, 0x0866, 0x06D6, 0x0B, 0x00 },
    { 0x17, 0x00, 0x0226, 0x073A, 0x05, 0x00 },
    { 0x17, 0x00, 0x0352, 0x073A, 0x0B, 0x00 },
    { 0x17, 0x00, 0x0866, 0x073A, 0x07, 0x00 },
    { 0x17, 0x00, 0x0992, 0x073A, 0x09, 0x00 },
    { 0x17, 0x00, 0x0352, 0x079E, 0x07, 0x00 },
    { 0x17, 0x00, 0x03B6, 0x079E, 0x0D, 0x00 },
    { 0x17, 0x00, 0x04E2, 0x079E, 0x0B, 0x00 },
    { 0x17, 0x00, 0x06D6, 0x079E, 0x07, 0x00 },
    { 0x17, 0x00, 0x0802, 0x079E, 0x0D, 0x00 },
    { 0x17, 0x00, 0x0866, 0x079E, 0x0B, 0x00 },
    { 0x17, 0x00, 0x0226, 0x0802, 0x06, 0x00 },
    { 0x17, 0x00, 0x0352, 0x0802, 0x0E, 0x00 },
    { 0x17, 0x00, 0x03B6, 0x0802, 0x0B, 0x00 },
    { 0x17, 0x00, 0x04E2, 0x0802, 0x07, 0x00 },
    { 0x17, 0x00, 0x05DC, 0x0802, 0x0E, 0x00 },
    { 0x17, 0x00, 0x06D6, 0x0802, 0x0B, 0x00 },
    { 0x17, 0x00, 0x0802, 0x0802, 0x07, 0x00 },
    { 0x17, 0x00, 0x0866, 0x0802, 0x0E, 0x00 },
    { 0x17, 0x00, 0x0992, 0x0802, 0x0A, 0x00 },
    { 0x17, 0x00, 0x03B6, 0x08CA, 0x06, 0x00 },
    { 0x17, 0x00, 0x04E2, 0x08CA, 0x0E, 0x00 },
    { 0x17, 0x00, 0x06D6, 0x08CA, 0x0E, 0x00 },
    { 0x17, 0x00, 0x0802, 0x08CA, 0x0A, 0x00 },
    { 0x18, 0x00, 0x041A, 0x0096, 0x05, 0x00 },
    { 0x18, 0x00, 0x06A4, 0x0096, 0x0D, 0x00 },
    { 0x18, 0x00, 0x092E, 0x0096, 0x09, 0x00 },
    { 0x18, 0x00, 0x03B6, 0x015E, 0x05, 0x00 },
    { 0x18, 0x00, 0x041A, 0x015E, 0x0E, 0x00 },
    { 0x18, 0x00, 0x04E2, 0x015E, 0x0D, 0x00 },
    { 0x18, 0x00, 0x05AA, 0x015E, 0x0D, 0x00 },
    { 0x18, 0x00, 0x06A4, 0x015E, 0x0E, 0x00 },
    { 0x18, 0x00, 0x079E, 0x015E, 0x0D, 0x00 },
    { 0x18, 0x00, 0x0866, 0x015E, 0x0D, 0x00 },
    { 0x18, 0x00, 0x092E, 0x015E, 0x0E, 0x00 },
    { 0x18, 0x00, 0x0992, 0x015E, 0x09, 0x00 },
    { 0x18, 0x00, 0x03B6, 0x028A, 0x07, 0x00 },
    { 0x18, 0x00, 0x04E2, 0x028A, 0x0B, 0x00 },
    { 0x18, 0x00, 0x05AA, 0x0258, 0x07, 0x00 },
    { 0x18, 0x00, 0x079E, 0x0258, 0x0B, 0x00 },
    { 0x18, 0x00, 0x0866, 0x028A, 0x07, 0x00 },
    { 0x18, 0x00, 0x0992, 0x028A, 0x0B, 0x00 },
    { 0x18, 0x00, 0x03B6, 0x03B6, 0x06, 0x00 },
    { 0x18, 0x00, 0x041A, 0x03B6, 0x0D, 0x00 },
    { 0x18, 0x00, 0x04E2, 0x03B6, 0x0E, 0x00 },
    { 0x18, 0x00, 0x05AA, 0x03B6, 0x0E, 0x00 },
    { 0x18, 0x00, 0x06A4, 0x03B6, 0x0D, 0x00 },
    { 0x18, 0x00, 0x079E, 0x03B6, 0x0E, 0x00 },
    { 0x18, 0x00, 0x0866, 0x03B6, 0x0E, 0x00 },
    { 0x18, 0x00, 0x092E, 0x03B6, 0x0D, 0x00 },
    { 0x18, 0x00, 0x0992, 0x03B6, 0x0A, 0x00 },
    { 0x18, 0x00, 0x041A, 0x047E, 0x06, 0x00 },
    { 0x18, 0x00, 0x06A4, 0x047E, 0x0E, 0x00 },
    { 0x18, 0x00, 0x092E, 0x047E, 0x0A, 0x00 }
};
// </data>

/* Proposed name: UpdateBuildingMovement
 * Dispatcher: builds the movement matrix for the building's movement type
 * (arg3), concatenates the translation to the building origin (arg0..arg2,
 * fixed-point world coords; /32 = float world, >>5 = grid), converts it with
 * guMtxF2L and pushes it onto both display lists (arg6/arg7). Writes the
 * resulting world position to D_803F7664/68/6C for the caller to store back.
 * arg5 = per-building state (building+0x38), arg8 = building "counter" param
 * (meaning depends on type: amplitude / speed / path index / delay),
 * arg9..arg11 = current position (building+0x10..0x18) used by type 4. */
void func_hd_code_802933A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Mtx* arg4, s32 arg5, Gfx* arg6, Gfx* arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11) {
    s16 spBE;
    s16 spBC;
    s16 spBA;
    f32 sp78[4][4];
    f32 sp38[4][4];

    spBE = 0;
    spBC = 0;
    spBA = 0;
    switch (arg3) {
    case 1:
        func_hd_code_80294C50(sp78, &spBE, &spBC, &spBA, arg5, arg8);
        break;
    case 2:
        func_hd_code_80294D24(sp78, &spBE, &spBC, &spBA, arg5, arg8);
        break;
    case 3:
        func_hd_code_80293F84(sp78, arg0 >> 5, arg2 >> 5, &spBE, &spBC, &spBA, arg5, arg8);
        break;
    case 4:
        func_hd_code_802936AC(sp78, arg0 >> 5, arg2 >> 5, arg9 >> 5, arg11 >> 5, &spBE, &spBC, &spBA, arg5, arg8);
        break;
    case 5:
        func_hd_code_80294B64(sp78, 0x5A, &spBE, &spBC, &spBA, arg5, arg8);
        break;
    default:
        guTranslateF(sp78, 0.0f, 0.0f, 0.0f);
        break;
    }
    if ((arg3 == 3) && (D_hd_code_802FE980[arg8].unk81 == 1)) {
        arg1 = 0;
    }
    guTranslateF(sp38, arg0 / 32.0f, arg1 / 32.0f, arg2 / 32.0f);
    guMtxCatF(sp78, sp38, sp78);
    guMtxF2L(sp78, arg4);
    D_803F7664 = (spBE << 5) + arg0;
    D_803F7668 = (spBC << 5) + arg1;
    D_803F766C = (spBA << 5) + arg2;

    gSPMatrix(arg6++, osVirtualToPhysical(arg4), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPMatrix(arg7++, osVirtualToPhysical(arg4), G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
}

/* Proposed name: BuildingMovementDriveRoads (movement type 4)
 * Drives a building along a 32-unit road grid toward the player
 * (D_hd_code_803643E0/E8 = player x/z) — or away from it at 1.5x speed when
 * D_8036E4C8 is set, in which case it also blinks (parked at y=20000 except
 * when (frame & 0xF) >= 7). At each junction from D_hd_code_802FEDA0 (matched
 * by levelno and grid position +/-5) it picks an allowed exit direction biased
 * toward (or away from) the player; D_8036E4CA reverses the current direction.
 * Heading (arg8->unk4) turns 10 deg/frame toward the cardinal target angle.
 * arg1/arg2 = origin grid x/z, arg3/arg4 = current grid x/z,
 * arg5/arg6/arg7 = out offsets from origin, arg9 = speed (grid units). */
void func_hd_code_802936AC(f32 (*arg0)[4], s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16* arg5, s16* arg6, s16* arg7, struct S_802936AC* arg8, s32 arg9) {
    f32 sp58[4][4];
    s32 sp54;
    u8 sp53;
    s16 sp50;
    s16 sp4E;
    s16 sp4C;
    s16 sp4A;
    s16 sp48;
    s16 sp46;
    s16 sp44;
    u8 sp43;
    u8 sp42;
    s32 sp3C;
    s16 sp3A;
    s16 sp38;
    s16 sp36;
    s32 sp30;

    sp54 = 0;
    sp53 = 0;
    if ((D_8036E4C8 == 0) && (D_8036DCD8.link.next != NULL)) {
        sndDeactivate(D_8036DCD8.link.next);
    }
    if (D_hd_code_802E8BD0 == 0) {
        if (D_8036E4CA != 0) {
            arg8->unk8 = -1;
            switch (arg8->unk0) {                      /* switch 1; irregular */
            case 1:                                 /* switch 1 */
                arg8->unk0 = 2;
                break;
            case 2:                                 /* switch 1 */
                arg8->unk0 = 1;
                break;
            case 4:                                 /* switch 1 */
                arg8->unk0 = 8;
                break;
            case 8:                                 /* switch 1 */
                arg8->unk0 = 4;
                break;
            }
        }
        while ((sp54 < 0x66) && (sp53 == 0)) {
            if (D_hd_code_802FEDA0[sp54].unk0 == levelno
                && (arg3 >= D_hd_code_802FEDA0[sp54].unk2 - 5)
                && (arg4 >= D_hd_code_802FEDA0[sp54].unk4 - 5)
                && (arg3 < D_hd_code_802FEDA0[sp54].unk2 + 5)
                && (arg4 < D_hd_code_802FEDA0[sp54].unk4 + 5)
                && (arg8->unk8 != sp54)) {
                sp53 = 1;
            } else {
                sp54 += 1;
            }
        }
        if (sp53 != 0) {
            arg8->unk8 = sp54;
            sp4E = D_hd_code_803643E0 >> 5,
            sp4C = D_hd_code_803643E8 >> 5;
            if (D_8036E4C8 == 0) {
                sp4A = sp4E - arg3,
                sp48 = sp4C - arg4;
            } else {
                sp4A = arg3 - sp4E,
                sp48 = arg4 - sp4C;
            }
            if (sp4A < 0) {
                sp46 = -sp4A;
            } else {
                sp46 = sp4A;
            }
            if (sp48 < 0) {
                sp44 = -sp48;
            } else {
                sp44 = sp48;
            }
            switch (arg8->unk0) {                    /* switch 2; irregular */
            case 1:                                 /* switch 2 */
                sp3C = 2;
                break;
            case 2:                                 /* switch 2 */
                sp3C = 1;
                break;
            case 4:                                 /* switch 2 */
                sp3C = 8;
                break;
            case 8:                                 /* switch 2 */
                sp3C = 4;
                break;
            default:                                /* switch 2 */
                sp3C = 0;
                break;
            }
            if (D_hd_code_802FEDA0[sp54].unk6 & sp3C) {
                sp43 = D_hd_code_802FEDA0[sp54].unk6 & (sp3C ^ 0xFF);
            } else {
                sp43 = D_hd_code_802FEDA0[sp54].unk6;
            }
            if ((sp48 > 0) && (sp44 >= sp46)) {
                sp42 = 1;
            }
            if ((sp48 <= 0) && (sp44 >= sp46)) {
                sp42 = 2;
            }
            if ((sp4A > 0) && (sp46 >= sp44)) {
                sp42 = 4;
            }
            if ((sp4A <= 0) && (sp46 >= sp44)) {
                sp42 = 8;
            }
            if (sp43 & sp42) {
                arg8->unk0 = sp42;
            } else {
                if (sp42 == 1) {
                    if (sp43 & 4) {
                        arg8->unk0 = 4;
                    } else if (sp43 & 8) {
                        arg8->unk0 = 8;
                    } else {
                        arg8->unk0 = 2;
                    }
                }
                if (sp42 == 2) {
                    if (sp43 & 8) {
                        arg8->unk0 = 8;
                    } else if (sp43 & 4) {
                        arg8->unk0 = 4;
                    } else {
                        arg8->unk0 = 1;
                    }
                }
                if (sp42 == 4) {
                    if (sp43 & 1) {
                        arg8->unk0 = 1;
                    } else if (sp43 & 2) {
                        arg8->unk0 = 2;
                    } else {
                        arg8->unk0 = 8;
                    }
                }
                if (sp42 == 8) {
                    if (sp43 & 2) {
                        arg8->unk0 = 2;
                    } else if (sp43 & 1) {
                        arg8->unk0 = 1;
                    } else {
                        arg8->unk0 = 4;
                    }
                }
            }
        }
        if (D_8036E4C8 == 0) {
            sp30 = arg9;
        } else {
            sp30 = (arg9 * 3) / 2;
        }
        switch (arg8->unk0) {                        /* switch 3; irregular */
        case 1:                                     /* switch 3 */
            *arg5 = arg3 - arg1;
            *arg7 = (arg4 - arg2) + sp30;
            sp50 = 0x10E;
            break;
        case 2:                                     /* switch 3 */
            *arg5 = arg3 - arg1;
            *arg7 = (arg4 - arg2) - sp30;
            sp50 = 0x5A;
            break;
        case 4:                                     /* switch 3 */
            *arg5 = (arg3 - arg1) + sp30;
            *arg7 = arg4 - arg2;
            sp50 = 0;
            break;
        case 8:                                     /* switch 3 */
            *arg5 = (arg3 - arg1) - sp30;
            *arg7 = arg4 - arg2;
            sp50 = 0xB4;
            break;
        }
        *arg6 = 0;
        sp3A = (arg8->unk4 << 16) / 360;
        sp38 = (sp50 << 16) / 360;
        sp36 = sp38 - sp3A;

        if ((ABS(sp36)) < 0x7D0) {
            arg8->unk4 = sp50;
        } else {
            if (sp36 > 0) {
                arg8->unk4 = (arg8->unk4 + 0xA);
            } else {
                arg8->unk4 = (arg8->unk4 - 0xA);
            }
            if (arg8->unk4 >= 0x168) {
                arg8->unk4 = (arg8->unk4 - 0x168);
            }
            if (arg8->unk4 < 0) {
                arg8->unk4 = (arg8->unk4 + 0x168);
            }
        }
    } else {
        *arg5 = arg3 - arg1;
        *arg6 = 0;
        *arg7 = arg4 - arg2;
    }
    guAlignF(arg0, (f32) arg8->unk4, 0.0f, 1.0f, 0.0f);
    if ((D_8036E4C8 == 0) || ((D_hd_code_803156C4 & 0xF) >= 7U)) {
        guTranslateF(sp58, *arg5, *arg6, *arg7);
    } else {
        guTranslateF(sp58, 0.0f, 20000.0f, 0.0f);
    }
    guMtxCatF(arg0, sp58, arg0);
}

/* Proposed name: BuildingMovementFollowPath (movement type 3)
 * Moves the building along the cardinal-spline path D_hd_code_802FE980[arg7].
 * Advances segment progress (arg6->unk4) by the path speed each frame and
 * wraps the waypoint index (arg6->unk0). Interpolates position (out
 * arg3/arg4/arg5) and x/y/z rotation through the 4 surrounding waypoints;
 * rotations are unwrapped pairwise with func_hd_code_8026A2E8 (angle-unwrap
 * helper) before interpolation. If the path's y mode is 1, y comes from
 * func_hd_code_8027EED8 (terrain height lookup at world x/z) instead.
 * arg1/arg2 = building origin grid x/z. */
void func_hd_code_80293F84(f32 (*arg0)[4], s16 arg1, s16 arg2, s16* arg3, s16* arg4, s16* arg5, struct S_802936AC* arg6, s32 arg7) {
    s32 sp94;
    s32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp44[4][4];
    u8 sp40[4];
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;

    func_hd_code_802949B0(arg7);
    if (D_hd_code_802E8BD0 == 0) {
        arg6->unk4 += D_hd_code_802FE980[arg7].unk80;
        if (arg6->unk4 >= 0x3E8) {
            arg6->unk4 = 0;
            arg6->unk0 = (arg6->unk0 + 1);
            if (arg6->unk0 >= D_hd_code_802FE980[arg7].unk78 - 1) {
                arg6->unk0 = 0;
            }
        }
    }
    sp94 = arg6->unk0;
    sp90 = D_hd_code_802FE980[arg7].unk78 - 1;
    if (sp94 <= 0) {
        sp40[0] = ((sp90 + sp94) - 1);
    } else {
        sp40[0] = (sp94 - 1);
    }
    sp40[1] = sp94;
    if ((sp94 + 1) >= sp90) {
        sp40[2] = ((sp94 - sp90) + 1);
    } else {
        sp40[2] = (sp94 + 1);
    }
    if ((sp94 + 2) >= sp90) {
        sp40[3] = ((sp94 - sp90) + 2);
    } else {
        sp40[3] = (sp94 + 2);
    }
    D_8039CA50 = ((f32) arg6->unk4 / 1000.0);
    D_8039CA54 = D_8039CA50 * D_8039CA50;
    D_8039CA58 = D_8039CA54 * D_8039CA50;

    sp3C = D_hd_code_802FE980[arg7].unk0[sp40[0]].unk6;
    sp38 = D_hd_code_802FE980[arg7].unk0[sp40[1]].unk6;
    sp34 = D_hd_code_802FE980[arg7].unk0[sp40[2]].unk6;
    sp30 = D_hd_code_802FE980[arg7].unk0[sp40[3]].unk6;
    func_hd_code_8026A2E8(sp3C, &sp38);
    func_hd_code_8026A2E8(sp38, &sp34);
    func_hd_code_8026A2E8(sp34, &sp30);
    sp8C = func_hd_code_80294840(sp3C, sp38, sp34, sp30);

    sp3C = D_hd_code_802FE980[arg7].unk0[sp40[0]].unk8;
    sp38 = D_hd_code_802FE980[arg7].unk0[sp40[1]].unk8;
    sp34 = D_hd_code_802FE980[arg7].unk0[sp40[2]].unk8;
    sp30 = D_hd_code_802FE980[arg7].unk0[sp40[3]].unk8;
    func_hd_code_8026A2E8(sp3C, &sp38);
    func_hd_code_8026A2E8(sp38, &sp34);
    func_hd_code_8026A2E8(sp34, &sp30);
    sp88 = func_hd_code_80294840(sp3C, sp38, sp34, sp30);

    sp3C = D_hd_code_802FE980[arg7].unk0[sp40[0]].unkA;
    sp38 = D_hd_code_802FE980[arg7].unk0[sp40[1]].unkA;
    sp34 = D_hd_code_802FE980[arg7].unk0[sp40[2]].unkA;
    sp30 = D_hd_code_802FE980[arg7].unk0[sp40[3]].unkA;

    func_hd_code_8026A2E8(sp3C, &sp38);
    func_hd_code_8026A2E8(sp38, &sp34);
    func_hd_code_8026A2E8(sp34, &sp30);
    sp84 = func_hd_code_80294840(sp3C, sp38, sp34, sp30);
    *arg3 = func_hd_code_80294840(
        D_hd_code_802FE980[arg7].unk0[sp40[0]].unk0,
        D_hd_code_802FE980[arg7].unk0[sp40[1]].unk0,
        D_hd_code_802FE980[arg7].unk0[sp40[2]].unk0,
        D_hd_code_802FE980[arg7].unk0[sp40[3]].unk0
    );

    *arg5 = func_hd_code_80294840(
        D_hd_code_802FE980[arg7].unk0[sp40[0]].unk4,
        D_hd_code_802FE980[arg7].unk0[sp40[1]].unk4,
        D_hd_code_802FE980[arg7].unk0[sp40[2]].unk4,
        D_hd_code_802FE980[arg7].unk0[sp40[3]].unk4
    );

    switch (D_hd_code_802FE980[arg7].unk81) {
    case 0:
        *arg4 = func_hd_code_80294840(
            D_hd_code_802FE980[arg7].unk0[sp40[0]].unk2,
            D_hd_code_802FE980[arg7].unk0[sp40[1]].unk2,
            D_hd_code_802FE980[arg7].unk0[sp40[2]].unk2,
            D_hd_code_802FE980[arg7].unk0[sp40[3]].unk2
        );
        break;
    case 1:
        func_hd_code_8027EED8(*arg3 + arg1, *arg5 + arg2, arg4);
        break;
    }

    guAlignF(sp44, sp8C, 1.0f, 0.0f, 0.0f);
    guAlignF(arg0, sp88, 0.0f, 1.0f, 0.0f);
    guMtxCatF(sp44, arg0, sp44);
    guAlignF(arg0, sp84, 0.0f, 0.0f, 1.0f);
    guMtxCatF(sp44, arg0, sp44);
    guTranslateF(arg0, *arg3, *arg4, *arg5);
    guMtxCatF(sp44, arg0, arg0);
}

/* Proposed name: EvalCardinalSpline
 * Evaluates the cardinal spline through control points arg0..arg3 at the
 * parameter whose powers were precomputed in D_8039CA50/54/58 (t, t^2, t^3),
 * using the basis matrix D_8039CA10 set up by func_hd_code_802949B0:
 * result = [t^3 t^2 t 1] . B^T . [p0 p1 p2 p3]. */
f32 func_hd_code_80294840(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
  s32 spC;
  s32 sp8;
  s32 sp4;
  s32 sp0;

  spC = D_8039CA10[0][0] * arg0 + D_8039CA10[1][0] * arg1 + D_8039CA10[2][0] * arg2 + D_8039CA10[3][0] * arg3;
  sp8 = D_8039CA10[0][1] * arg0 + D_8039CA10[1][1] * arg1 + D_8039CA10[2][1] * arg2 + D_8039CA10[3][1] * arg3;
  sp4 = D_8039CA10[0][2] * arg0 + D_8039CA10[1][2] * arg1 + D_8039CA10[2][2] * arg2 + D_8039CA10[3][2] * arg3;
  sp0 = D_8039CA10[0][3] * arg0 + D_8039CA10[1][3] * arg1 + D_8039CA10[2][3] * arg2 + D_8039CA10[3][3] * arg3;

  return spC * D_8039CA58 + D_8039CA54 * sp8 + D_8039CA50 * sp4 + sp0;
}

/* Proposed name: InitCardinalSplineBasis
 * Fills D_8039CA10 with the cardinal-spline basis matrix for path arg0,
 * using the path's tension parameter (0.5 would give a Catmull-Rom spline). */
void func_hd_code_802949B0(s32 arg0) {
  f32 sp4 = D_hd_code_802FE980[arg0].unk7C;

  D_8039CA10[0][0] = -sp4;
  D_8039CA10[0][1] = sp4 * 2.0;
  D_8039CA10[0][2] = -sp4;
  D_8039CA10[0][3] = 0.0f;
  D_8039CA10[1][0] = 2.0 - sp4;
  D_8039CA10[1][1] = sp4 - 3.0;
  D_8039CA10[1][2] = 0.0f;
  D_8039CA10[1][3] = 1.0f;
  D_8039CA10[2][0] = sp4 - 2.0;
  D_8039CA10[2][1] = 3.0 - sp4 * 2.0;
  D_8039CA10[2][2] = sp4;
  D_8039CA10[2][3] = 0.0f;
  D_8039CA10[3][0] = sp4;
  D_8039CA10[3][1] = -sp4;
  D_8039CA10[3][2] = 0.0f;
  D_8039CA10[3][3] = 0.0f;
}


/* Proposed name: BuildingMovementRotateOnce (movement type 5)
 * One-shot rotation, e.g. a swing/gate opening: on the first call arms a
 * start frame (current frame D_hd_code_803156C4 + delay arg6, the building's
 * "counter" param), then rotates about Y at 1 deg/frame, clamped to arg1
 * (90 deg from the dispatcher). */
void func_hd_code_80294B64(f32 (*arg0)[4], s32 arg1, s16* arg2, s16* arg3, s16* arg4, struct S_802936AC* arg5, s32 arg6) {
  if (arg5->unk0 == 0) {
    arg5->unk0 = arg6 + D_hd_code_803156C4;
  }
  if (D_hd_code_803156C4 > arg5->unk0 && D_hd_code_802E8BD0 == 0) {
    arg5->unk4++;
    if (arg5->unk4 > arg1) {
      arg5->unk4 = arg1;
    }
  }
  guAlignF(arg0, -arg5->unk4, 0.0f, 1.0f, 0.0f);
  *arg2 = 0;
  *arg3 = 0;
  *arg4 = 0;
}

/* Proposed name: BuildingMovementBob (movement type 1)
 * Bobs the building vertically: y = arg5 * sinf(phase / 5), where arg5 is the
 * building's "counter" param (amplitude) and the phase advances 1/frame. */
void func_hd_code_80294C50(f32 (*arg0)[4], s16* arg1, s16* arg2, s16* arg3, struct S_802936AC* arg4, s32 arg5) {
  f32 sp1C;

  if (D_hd_code_802E8BD0 == 0) {
    arg4->unk0++;
  }
  sp1C = sinf(arg4->unk0 / 5.0f);
  *arg1 = 0;
  *arg3 = 0;
  *arg2 = arg5 * sp1C;
  guTranslateF(arg0, 0.0f, *arg2, 0.0f);
}

/* Proposed name: BuildingMovementTumble (movement type 2)
 * Spins the building about the fixed tilted axis (0.2, 0.7,
 * D_hd_code_8030CD50), advancing the angle by arg5 (the building's "counter"
 * param) per frame, and orbits the offset point (90, 0, 0) through that
 * rotation — a wobbling spin. */
void func_hd_code_80294D24(f32 (*arg0)[4], s16* arg1, s16* arg2, s16* arg3, struct S_802936AC* arg4, s32 arg5) {
  f32 sp38[4][4];
  f32 sp34;
  f32 sp30;
  f32 sp2C;

  if (D_hd_code_802E8BD0 == 0) {
    arg4->unk0 += arg5;
  }
  guAlignF(sp38, arg4->unk0, 0.2f, 0.7f, 0.1f);
  guMtxXFMF(sp38, 90.0f, 0.0f, 0.0f, &sp34, &sp30, &sp2C);
  *arg1 = sp34;
  *arg2 = sp30;
  *arg3 = sp2C;
  guTranslateF(arg0, sp34, sp30, sp2C);
}

