#include "common.h"
#include "functions.h"
#include "gu/guint.h"
#include "macros.h"
#include "structs.h"
#include "variables.h"

f32 func_hd_code_8028BD88(f32, f32);
u16 func_hd_code_8028BA1C(s16, s16, s8*, u8);
f32 func_hd_code_8028BBF4(s16, s16, s16, s16);
extern u16 D_hd_code_80370C70;
extern s16 D_hd_code_80370C72;
extern s8 D_hd_code_80370C74;
extern s16 D_hd_code_80370C76;
extern s16 D_hd_code_803ED408;
extern s8 D_hd_code_80370C75;
extern s8 D_hd_code_803ED40A;
extern s16 D_hd_code_803ED400;
extern s16 D_hd_code_803F7C34;

// Proposed file name: steering.c
//
// This file converts the camera-relative analog stick into a vehicle's
// turn/accelerate inputs for the "steer toward where you push" control
// schemes (on foot and similar vehicles). It computes the world heading the
// stick is pointing at (stick direction plus camera yaw), compares it to the
// vehicle's current heading (D_hd_code_80370C70), and emits turn-left / turn-right
// (button bits 0x200 / 0x100) plus forward speed, with a lock-on window so a
// chosen direction sticks until roughly reached. Angles are in the 0..65535
// turn unit.

// Reset the steering lock-on state
// Proposed name: ResetSteering
void func_hd_code_8028B720(void) {
  D_hd_code_80370C75 = 0;
  D_hd_code_803ED40A = 0;
}

// Camera-relative steering for vehicle type arg2: from the stick (*arg0 x,
// *arg1 y) compute the target world heading and magnitude, then decide
// turn direction (func_hd_code_8028BA1C) - or hold the locked-in heading -
// returning the result as a synthetic left/right press in *arg0 and the
// forward speed in *arg1
// Proposed name: SteerTowardStick
void func_hd_code_8028B734(s8* arg0, s8* arg1, u8 arg2) {
  s8 sp37;
  s8 sp36;
  s16 sp34;
  s16 sp32;
  s16 sp30;
  u16 sp2E;
  s16 sp2C;

  sp30 = (-D_hd_code_80370C70 * 16) + 0x7FF0;
  sp37 = *arg0;
  sp36 = *arg1;
  sp34 = (s16) (s32) ((((f64) func_hd_code_8028BBF4(0, 0, sp37, -sp36) * 65536.0) / 360.0) + 32768.0 + (f64) (s16) (s32) (((360.0 - ((f64) D_hd_code_80364414 + 180.0)) / 360.0) * 65536.0));
  sp32 = (s16) (s32) sqrtf((f32) ((sp37 * sp37) + (sp36 * sp36)));
  *arg1 = (s8) sp32;
  D_hd_code_80370C74 = 0;
  sp2E = 0;
  if ((u8) D_hd_code_80370C75 == 1) {
    sp2C = D_hd_code_80370C76 - sp30;
    if ((ABS(sp2C)) <= (ABS(D_hd_code_80370C72 * 0x10))) {
      D_hd_code_80370C75 = 0;
    }
    sp2E = 0x200;
  } else {
    if (*arg1 >= 0xB) {
      sp2E = func_hd_code_8028BA1C(sp30, sp34, &D_hd_code_80370C74, arg2);
    }
    if ((D_hd_code_80370C74 != 0) && (D_hd_code_8036443C < 0x28)) {
      D_hd_code_80370C76 = sp34;
      D_hd_code_80370C75 = 1;
    }
    else if ((u8) D_hd_code_803ED40A != 0) {
      D_hd_code_803ED408 = 0x7FF - (sp34 / 16);
      *arg0 = 0;
      return;
    }
  }
  *arg0 = 0;
  if (sp2E == 0x200) {
    *arg0 = -0x50;
  }
  if (sp2E == 0x100) {
    *arg0 = 0x50;
  }
}

// Decide which way to turn from current heading arg0 to target arg1: if the
// difference exceeds a speed-dependent threshold flip the "turn the long way"
// state (*arg2) and coast, otherwise return 0x100 (right) or 0x200 (left)
// for the shorter turn; sets the "aligned" flag when within the deadband
// Proposed name: ChooseTurnDirection
u16 func_hd_code_8028BA1C(s16 arg0, s16 arg1, s8* arg2, u8 arg3) {
  s16 spE;
  u16 spC;
  s16 spA;
  u16 sp8;

  sp8 = 0x5A;
  spA = 0x78 - (ABS(D_hd_code_803ED400)) * (0x78 - sp8) / 200;
  spC = 0x8000 - ((spA < sp8 ? sp8 : spA) << 16) / 720;
  if (*arg2 != 0) {
    arg0 += 0x8000;
  }
  spE = arg1 - arg0;
  D_hd_code_803F7C34 = spE;

  if ((ABS(spE)) <= (ABS(D_hd_code_80370C72 * 0x10))) {
    D_hd_code_803ED40A = 1;
  }

  if ((spC < (ABS(spE))) && D_hd_code_8036443C < 0x28) {
    *arg2 ^= -1;
    return 0U;
  }

  if (((D_hd_code_80370C72 >= 0 ? 1 : -1) * spE) > 0) {
    return 0x100U;
  }
  return 0x200U;
}

// Bearing in degrees (0..360) from (arg0, arg1) to (arg2, arg3) via the
// quadrant-resolved acos helper below
// Proposed name: BearingDegrees
f32 func_hd_code_8028BBF4(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
  f32 sp1C;

  if (arg2 >= arg0 && arg3 >= arg1) {
    sp1C = func_hd_code_8028BD88(arg3 - arg1, arg2 - arg0) + 90.0f;
  } else if (arg2 >= arg0 && arg3 < arg1) {
    sp1C = 90.0f - func_hd_code_8028BD88(arg1 - arg3, arg2 - arg0);
  } else if (arg2 < arg0 && arg3 < arg1) {
    sp1C = func_hd_code_8028BD88(arg1 - arg3, arg0 - arg2) + 270.0f;
  } else if (arg2 < arg0 && arg3 >= arg1) {
    sp1C = 270.0f - func_hd_code_8028BD88(arg3 - arg1, arg0 - arg2);
  }
  return sp1C;
}

// acos(arg1 / hypot(arg0,arg1)) in degrees, via the fixed-point arccos
// lookup func_hd_code_802AD7D4
// Proposed name: AcosDegrees
f32 func_hd_code_8028BD88(f32 arg0, f32 arg1) {
  s32 sp1C;
  f32 sp18;

  if (arg0 == 0.0 && arg1 == 0.0) {
    return 0.0f;
  }
  sp18 = arg0 / sqrtf(arg0 * arg0 + arg1 * arg1);
  sp1C = func_hd_code_802AD7D4(sp18 * 65536.0);
  return ((f32) sp1C / 65536.0) * 360.0;
}


// Set the directional + L/R button bits in *arg0 from a raw stick position
// (the simple, non-steering control mapping; Z also presses L+R)
// Proposed name: StickToButtonsRaw
void func_hd_code_8028BE70(u16* arg0, s8 arg1, s8 arg2) {
  if (!(*arg0 & 0x200) && (arg1 < -0x32)) {
    *arg0 |= 0x200;
  }
  if (!(*arg0 & 0x100) && (arg1 >= 0x33)) {
    *arg0 |= 0x100;
  }
  if (!(*arg0 & 0x8000) && (arg2 < -0x32)) {
    *arg0 |= 0x8000;
  }
  if (!(*arg0 & 0x4000) && (arg2 >= 0x33)) {
    *arg0 |= 0x4000;
  }
  if (*arg0 & 0x2000) {
    *arg0 |= 0x30;
  }
}

// Steering control for vehicle type arg3 that also drives via button bits:
// from the stick magnitude gate turning/forward thresholds, then OR in the
// turn direction (func_hd_code_8028BA1C) and forward/accelerate bits
// Proposed name: SteerToButtons
void func_hd_code_8028BF34(u16* arg0, s8 arg1, s8 arg2, u8 arg3) {
  s16 sp2E;
  s16 sp2C;
  s16 sp2A;
  u16 sp28;

  sp2E = (((func_hd_code_8028BBF4(0, 0, arg1, -arg2) * 65536.0) / 360.0) + 32768.0);
  sp2C = sqrtf((f32) ((arg1 * arg1) + (arg2 * arg2)));
  sp2A = (-D_hd_code_80370C70 * 0x10) + 0x7FF0;
  sp2A = sp2A - 0x2000;
  sp28 = 0;

  if ((sp2C >= 0x10) && ((sp28 = 1, (arg3 == 0)) || (arg3 == 2) || (arg3 == 0x10))) {
    sp28 |= 2;
  }
  if (sp2C >= 0x2E) {
    sp28 |= 2;
  }
  if ((sp2C >= 0x4C) && ((D_hd_code_80370C74 == 0) || (arg3 != 3))) {
    sp28 |= 4;
  }
  if (sp28 == 0) {
    D_hd_code_80370C74 = 0;
  }
  if (!(*arg0 & 0x300) && (sp28 & 1)) {
    *arg0 |= func_hd_code_8028BA1C(sp2A, sp2E, &D_hd_code_80370C74, arg3);
  }

  if (!(*arg0 & 0xC000) && (sp28 & 2)) {
    if (D_hd_code_80370C74 != 0) {
      *arg0 = *arg0 | 0x8000;
    } else {
      *arg0 |= 0x4000;
    }
  }

  if (*arg0 & 0x2000) {
    *arg0 = *arg0 | 0x30;
  }
}

