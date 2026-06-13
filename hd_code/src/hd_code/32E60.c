#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"

// Proposed file name: comms.c
//
// This file is the "communications window" - the animated talking-head
// portrait that appears in a screen corner with a voice line and TV-static
// effects - plus the driving-skill monitor that decides when the advisor
// praises or criticizes the player. Skill samples ({speed ok, control ok,
// vehicle, time}) are recorded into a 50-entry ring buffer
// (D_8036C8D0, head/tail D_8036CB29/28, entries expire after 1000 frames);
// tallies of good/bad samples trigger "DOING REALLY WELL", "USING WRONG
// DIGGER" and "USING DIGGER INCORRECTLY" comms. The window plays 40x40
// RGBA16 face frames (id lists D_hd_code_802FBDD0..) streamed into the
// double buffer D_8036CB48, with radio-crackle static bursts via the NOISE
// combiner.

// Per-frame update (arg0 = frame counter): expire old skill samples, record
// a new one when the vehicle code flagged it (D_8036CB2F, with metrics in
// D_8036CB2A/2C/2E), retally and run the praise/criticism checks; at frame
// 50 play the mission-start advisor clip; and in carrier levels fire the
// scripted one-shot comms from the level data (D_803BE6FC list) as the
// carrier passes each z threshold.
// Proposed name: UpdateCommsAdvisor
void func_hd_code_80277620(s32 arg0) {
    u8 sp2F;
    struct S_803BE6FC* sp28;
    s16 sp26;

    sp2F = 0;
    sp28 = D_803BE6FC;
    while ((sp2F == 0) && ((u8) D_8036CB28 != (u8) D_8036CB29)) {
        if ((arg0 - D_8036C8D0[D_8036CB28].unk8) >= 0x3E9) {
            D_8036CB28++;
            if (D_8036CB28 == 0x32) {
                D_8036CB28 = 0;
            }
        } else {
            sp2F = 1;
        }
    }

    if ((D_8036CB2F != 0) && (((u8) D_8036CB29 + 1) != (u8) D_8036CB28) && (((u8) D_8036CB29 != 0x31) || ((u8) D_8036CB28 != 0))) {
        D_8036C8D0[D_8036CB29].unk0 = func_hd_code_80277D34();
        D_8036C8D0[D_8036CB29].unk2 = func_hd_code_80277E08();
        D_8036C8D0[D_8036CB29].unk4 = D_8036CB2E;
        D_8036C8D0[D_8036CB29].unk8 = arg0;

        D_8036CB29++;
        if (D_8036CB29 == 0x32) {
            D_8036CB29 = 0;
        }
    }
    if (D_8036CB2F != 0) {
        func_hd_code_80277C20();
        func_hd_code_802778FC();
        func_hd_code_80277AE0();
        func_hd_code_80277B84();
    }
    if ((arg0 == 0x32) && (D_hd_code_803643D6 == 0)) {
        func_hd_code_80277EDC(2, 1, 2, func_hd_code_8026205C(1));
    }
    if (D_hd_code_803643DB != 0) {
        sp26 = (s16) ((s32) D_803EF6E4 >> 5);
        while ((u32)sp28 < (u32) D_803BE700) {
            if ((sp28->unk6 == 0) && (sp26 > sp28->unk0)) {
                func_hd_code_80277EDC((s32) sp28->unk2, (s32) sp28->unk3, (s32) sp28->unk4, (s32) sp28->unk5);
                sp28->unk6 = 1U;
            }
            sp28++;
        }
    }
    D_8036CB2F = 0;
}

// Praise check: per-vehicle thresholds of consecutive good samples trigger
// the "doing really well" comms and reset the ring
// Proposed name: CheckPraise
void func_hd_code_802778FC(void) {
  switch (D_hd_code_80364456) {                   /* irregular */
    case 5:
      if (((s32) D_8036CB31 >= 0x10) && ((s32) D_8036CB30 >= 0x10)) {
        func_hd_code_80277EDC(3, 1, 1, 0x63);
        D_8036CB28 = 0;
        D_8036CB29 = 0;
        rmonPrintf("DOING REALLY WELL\n");
        return;
      }
      return;
    case 4:
      if (((s32) D_8036CB31 >= 0x29) && ((s32) D_8036CB30 >= 0x29)) {
        func_hd_code_80277EDC(4, 1, 1, func_hd_code_8026205C(4));
        D_8036CB28 = 0;
        D_8036CB29 = 0;
        rmonPrintf("DOING REALLY WELL\n");
        return;
      }
      break;
    case 3:
      if (((s32) D_8036CB31 >= 0xB) && ((s32) D_8036CB30 >= 0xB)) {
        func_hd_code_80277EDC(0, 1, 3, 0xB2);
        D_8036CB28 = 0;
        D_8036CB29 = 0;
        rmonPrintf("DOING REALLY WELL\n");
        return;
      }
      break;
    case 9:
      if (((s32) D_8036CB31 >= 0x1A) && ((s32) D_8036CB30 >= 0x1A)) {
        func_hd_code_80277EDC(4, 1, 1, func_hd_code_8026205C(4));
        D_8036CB28 = 0;
        D_8036CB29 = 0;
        rmonPrintf("DOING REALLY WELL\n");
      }
      break;
  }
}

// "USING WRONG DIGGER" check: enough good speed samples but almost no good
// control samples
// Proposed name: CheckWrongVehicle
void func_hd_code_80277AE0(void) {
  switch(D_hd_code_80364456) {
    case 3:
    case 4:
    case 5:
    case 9:
      if (((s32) D_8036CB31 >= 6) && ((s32) D_8036CB30 < 2)) {
        func_hd_code_80277EDC(1, 1, 3, 0xB3);
        D_8036CB28 = 0;
        D_8036CB29 = 0;
        rmonPrintf("USING WRONG DIGGER\n");
      }
      break;
  }
}

// "USING DIGGER INCORRECTLY" check: many bad speed samples with few good
// control samples
// Proposed name: CheckVehicleMisuse
void func_hd_code_80277B84(void) {
  switch(D_hd_code_80364456) {
    case 3:
    case 4:
    case 5:
      if (((s32) D_8036CB33 >= 0x1F) && ((s32) D_8036CB30 < 6)) {
        func_hd_code_80277EDC(2, 1, 2, 0x58);
        D_8036CB28 = 0;
        D_8036CB29 = 0;
        rmonPrintf("USING DIGGER INCORRECTLY\n");
      }
      break;
  }
}

// Recompute the good/bad sample tallies (D_8036CB30..33) from the ring
// Proposed name: TallySkillSamples
void func_hd_code_80277C20(void) {
  u8 sp7 = D_8036CB28;

  D_8036CB30 = 0;
  D_8036CB31 = 0;
  D_8036CB32 = 0;
  D_8036CB33 = 0;

  while (sp7 != D_8036CB29) {
    if (D_8036C8D0[sp7].unk2 == 0) {
      D_8036CB30 += 1;
    } else {
      D_8036CB32 += 1;
    }
    if (D_8036C8D0[sp7].unk0 == 0) {
      D_8036CB31 += 1;
    } else {
      D_8036CB33 += 1;
    }
    sp7++;
    if (sp7 == 0x32) {
      sp7 = 0;
    }
  }
}

// Grade the current speed sample against the vehicle's threshold
// (0 = good, 1 = bad)
// Proposed name: GradeSpeedSample
s16 func_hd_code_80277D34(void) {
  switch (D_8036CB2E) {                           /* irregular */
    case 5:
      if (D_8036CB2A >= 0x191) {
        return 0;
      }
      return 1;
    case 4:
      if (D_8036CB2A >= 0x191) {
        return 0;
      }
      return 1;
    case 9:
      if (D_8036CB2A >= 0x64) {
        return 0;
      }
      return 1;
    case 3:
      if (D_8036CB2A >= 0x64) {
        return 0;
      }
      return 1;
  }
  return 1;
}

// Grade the current control/handling sample against the vehicle's threshold
// (0 = good, 1 = bad)
// Proposed name: GradeControlSample
s16 func_hd_code_80277E08(void) {
  switch (D_8036CB2E) {                           /* irregular */
    case 5:
      if (D_8036CB2C >= 0x51) {
        return 0;
      }
      return 1;
    case 4:
      if (D_8036CB2C >= 0x51) {
        return 0;
      }
      return 1;
    case 9:
      if (D_8036CB2C >= 0x64) {
        return 0;
      }
      return 1;
    case 3:
      if (D_8036CB2C >= 0x64) {
        return 0;
      }
      return 1;
  }
  return 1;
}

// Open the comms window: arg0 = face animation (0..4, selecting the frame
// id list, frame count and rate), arg1 = play mode (0 = loop forward,
// 1 = ping-pong), arg2 = number of loops, arg3 = voice clip to play.
// Positions the face + border quads top-left or bottom-right (always
// bottom-right outside demolition mode). Ignored if a window is already up.
// Proposed name: ShowCommsWindow
void func_hd_code_80277EDC(u8 arg0, u8 arg1, s32 arg2, s32 arg3) {
    u8 sp27;

    if (((D_hd_code_80364A90 & 0x200000000400220C)) && ((u8) D_8036CB34 == 0)) {
        if ((u8) arg3 != 0) {
            sndPlaySfx(D_hd_code_80367738, (s16) (u8) arg3, NULL);
        }
        D_8036CB34 = 1;
        D_8036CB35 = arg2;
        D_8036CB36 = 0;
        D_8036CB37 = 0;
        D_8036CB39 = 0;
        D_8036CB3A = 0;
        D_8036CB38 = (u8) arg1;
        D_8036CB44 = (u8) arg0;
        D_8036CB50 = 0;
        switch (arg0) {                        /* switch 1 */
        case 0:                                     /* switch 1 */
            sp27 = 0;
            D_8036CB3C = 0xD;
            D_8036CB40 = D_hd_code_802FBDD0;
            D_8036CB3B = 1;
            break;
        case 1:                                     /* switch 1 */
            sp27 = 1;
            D_8036CB3C = 0x15;
            D_8036CB40 = D_hd_code_802FBDEC;
            D_8036CB3B = 1;
            break;
        case 2:                                     /* switch 1 */
            sp27 = 0;
            D_8036CB3C = 0x15;
            D_8036CB40 = D_hd_code_802FBE18;
            D_8036CB3B = 2;
            break;
        case 3:                                     /* switch 1 */
            sp27 = 1;
            D_8036CB3C = 0x1E;
            D_8036CB40 = D_hd_code_802FBE44;
            D_8036CB3B = 1;
            break;
        case 4:                                     /* switch 1 */
            sp27 = 0;
            D_8036CB3C = 0x22;
            D_8036CB40 = D_hd_code_802FBE80;
            D_8036CB3B = 1;
            break;
        }
        if (D_hd_code_80364AA8 != 1) {
            sp27 = 1;
        }
        switch (sp27) {
        case 0:
            D_hd_code_802FBD50[0].v.ob[0] = 0x20;
            D_hd_code_802FBD50[0].v.ob[1] = 0x44;

            D_hd_code_802FBD50[1].v.ob[0] = 0x4E,
            D_hd_code_802FBD50[1].v.ob[1] = 0x44;

            D_hd_code_802FBD50[2].v.ob[0] = 0x4E,
            D_hd_code_802FBD50[2].v.ob[1] = 0x17;

            D_hd_code_802FBD50[3].v.ob[0] = 0x20,
            D_hd_code_802FBD50[3].v.ob[1] = 0x17;

            D_hd_code_802FBD50[4].v.ob[0] = 0x1A,
            D_hd_code_802FBD50[4].v.ob[1] = 0x49;

            D_hd_code_802FBD50[5].v.ob[0] = 0x54,
            D_hd_code_802FBD50[5].v.ob[1] = 0x49;

            D_hd_code_802FBD50[6].v.ob[0] = 0x54,
            D_hd_code_802FBD50[6].v.ob[1] = 0xD;

            D_hd_code_802FBD50[7].v.ob[0] = 0x1A,
            D_hd_code_802FBD50[7].v.ob[1] = 0xD;
            return;
        case 1:
            D_hd_code_802FBD50[0].v.ob[0] = 0xEE,
            D_hd_code_802FBD50[0].v.ob[1] = 0xDE;

            D_hd_code_802FBD50[1].v.ob[0] = 0x11C,
            D_hd_code_802FBD50[1].v.ob[1] = 0xDE;

            D_hd_code_802FBD50[2].v.ob[0] = 0x11C,
            D_hd_code_802FBD50[2].v.ob[1] = 0xB1;

            D_hd_code_802FBD50[3].v.ob[0] = 0xEE,
            D_hd_code_802FBD50[3].v.ob[1] = 0xB1;

            D_hd_code_802FBD50[4].v.ob[0] = 0xE8,
            D_hd_code_802FBD50[4].v.ob[1] = 0xE3;

            D_hd_code_802FBD50[5].v.ob[0] = 0x122,
            D_hd_code_802FBD50[5].v.ob[1] = 0xE3;

            D_hd_code_802FBD50[6].v.ob[0] = 0x122,
            D_hd_code_802FBD50[6].v.ob[1] = 0xA7;

            D_hd_code_802FBD50[7].v.ob[0] = 0xE8,
            D_hd_code_802FBD50[7].v.ob[1] = 0xA7;
            break;
        }
    }
}

// Close the comms window immediately
// Proposed name: HideCommsWindow
void func_hd_code_80278318(void) {
  D_8036CB34 = 0;
}

// decomped by inspectredc
// Draw the comms window: stream the current 40x40 face frame into the
// double buffer, advance the animation (forward or ping-pong, counting
// loops, closing when done), apply the TV-static effect - full static with
// a radio crackle (sfx 0x69) while tuning in, then random short bursts -
// and draw the face quad (2-cycle NOISE blend by the static alpha) plus the
// translucent 32x32 RGBA32 border frame.
// Proposed name: DrawCommsWindow
void func_hd_code_80278324(Gfx** arg0, s32* arg1, u8 arg2) {
    Gfx* entry;

    entry = *arg0;
    if (D_8036CB34 != 0) {
        func_hd_code_802A1040((u16) D_8036CB40->v.ob[D_8036CB39], D_8036CB48[arg2], 0);
        switch (D_8036CB38) {
            case 1:
                if (D_8036CB37 == 0) {
                    D_8036CB3A++;
                    if (D_8036CB3A == D_8036CB3B) {
                        D_8036CB3A = 0;
                        D_8036CB39++;
                        if ((D_8036CB39 + 1) == D_8036CB3C) {
                            D_8036CB37 = 1;
                            D_8036CB36++;
                        }
                    }
                } else {
                    D_8036CB3A++;
                    if (D_8036CB3A == D_8036CB3B) {
                        D_8036CB3A = 0;
                        D_8036CB39--;
                        if (!D_8036CB39) {
                            D_8036CB37 = 0;
                            D_8036CB36++;
                        }
                    }
                }
                break;
            case 0:
                D_8036CB3A++;
                if (D_8036CB3A == D_8036CB3B) {
                    D_8036CB3A = 0;
                    D_8036CB39++;
                    if (D_8036CB39 == D_8036CB3C) {
                        D_8036CB39 = 0;
                        D_8036CB36++;
                    }
                }
                break;
            default:
                break;
        }
        if (D_8036CB36 == D_8036CB35) {
            D_8036CB34 = 0;
        }
        if ((D_8036CB36 == 0) && (D_8036CB39 < 5)) {
            if (D_8036CB39 == 0) {
                sndPlaySfx(D_hd_code_80367738, 0x69, NULL);
            }
            D_8036CB51 = 0x50;
        } else if (D_8036CB50 != 0) {
            D_8036CB51 -= 0xF;
            D_8036CB50--;
        } else if (func_hd_code_8026A828(0, 0x14) == 0) {
            D_8036CB50 = 5;
            D_8036CB51 = 0x50;
            sndPlaySfx(D_hd_code_80367738, 0x69, NULL);
        } else {
            D_8036CB51 = 0;
        }

        gSPMatrix(entry++, &D_2000000.mtx1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPMatrix(entry++, &D_2000000.modelview, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(entry++);
        gDPSetCycleType(entry++, G_CYC_2CYCLE);
        gDPSetRenderMode(entry++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
        gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
        gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);
        gDPSetCombineLERP(entry++, NOISE, 0, PRIMITIVE_ALPHA, 0, 0, 0, 0, SHADE, TEXEL1, 0, SHADE, COMBINED, 0, 0, 0, SHADE);
        gDPSetPrimColor(entry++, 0, 0, 0, 0, 0, D_8036CB51);
        gDPLoadTextureBlock(entry++, OS_PHYSICAL_TO_K0(D_8036CB48[arg2]), G_IM_FMT_RGBA, G_IM_SIZ_16b, 40, 40, 0, G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPVertex(entry++, OS_PHYSICAL_TO_K0(D_hd_code_802FBD50), 8, 0);
        gSP1Triangle(entry++, 0, 1, 2, 0);
        gSP1Triangle(entry++, 0, 2, 3, 0);
        gDPPipeSync(entry++);
        gDPSetCycleType(entry++, G_CYC_1CYCLE);
        gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(entry++, G_CC_MODULATEIA, G_CC_MODULATEIA);
        gDPLoadTextureBlock(entry++, OS_PHYSICAL_TO_K0(D_hd_code_802FAD50), G_IM_FMT_RGBA, G_IM_SIZ_32b, 32, 32, 0, G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSP1Triangle(entry++, 4, 5, 6, 0);
        gSP1Triangle(entry++, 4, 6, 7, 0);
        gDPPipeSync(entry++);
    }
    *arg0 = entry;
}

