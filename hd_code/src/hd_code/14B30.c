#include <ultra64.h>
#include "common.h"
#include "structs.h"
#include "functions.h"
#include "variables.h"

// Data
s32 D_hd_code_802E8C70 = 0;
s32 characterIndex = 0;
s32 D_hd_code_802E8C78 = 0;
s32 pad1 = 0; // unused struct data?
s32 pad2 = 0x20200000; // unused struct data?
f32 D_hd_code_802E8C84[2] = { 0.6f, 0.95f };
s16 D_hd_code_802E8C8C[2] = { 0x002A, 0x1000 };
s16 D_hd_code_802E8C90[2] = { 0x0026, 0x1005 };
u16 D_hd_code_802E8C94[2] = { 0x0020, 0x1002 };
u16 D_hd_code_802E8C98[2] = { 0x0000, 0x0FFE };
u16 D_hd_code_802E8C9C[4] = { 0x0023, 0x1001, 0x1003, 0x0FFE };

s32 D_80364A9C;
Vtx* D_80365348[2];
s32 D_80365350;
s32 D_80364A9C;

void func_hd_code_802592F0() {
  s32 sp1C;

  if (D_80364A98 & 0xC9FD8FE7DBFF8080 ||
      D_80364A98 == 0x100000000000 ||
      D_80364A98 == 2 ||
      levelno == 0x28 ||
      levelno == 0x32) {
    maxCharacters = 0x200;
      } else if (D_80364A98 == 0x40) {
        maxCharacters = 0x9C;
      } else {
        maxCharacters = 0xAC;
      }

  for(sp1C = 0; sp1C < 2; sp1C++) {
    D_80365348[sp1C] = D_80358070;
    D_80358070 += (maxCharacters << 4) * sizeof(Gfx*);
  }

  D_80365340 = D_80358070;
  D_80358070 += maxCharacters * 12;

  func_hd_code_8025B070();
}

void func_hd_code_80259450(void) {
  D_hd_code_802E8C70 = 0;
  characterIndex = 0;
  D_hd_code_802E8C78 = 0;
}

void func_hd_code_8025946C(Gfx** arg0, struct Model1* arg1) {
  Gfx *entry;

  entry = *arg0;

  gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
  gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
  gDPPipeSync(entry++);
  gDPSetCycleType(entry++, G_CYC_1CYCLE);
  gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
  gDPSetCombineMode(entry++, G_CC_MODULATEIA, G_CC_MODULATEIA);
  gDPSetTextureFilter(entry++, G_TF_BILERP);
  gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);

  *arg0 = entry;
}

// probably shell sort
void func_hd_code_802595E0(u8* base, s32 elements, s32 size, s32 (*cmp)(u16*, u16*)) {
  s32 sp124;
  s32 sp120;
  s32 gap;
  u8* sp118;
  u8 buffer[256];

  sp118 = base;
  for (gap = 1; gap <= (elements / 9); gap = (gap * 3) + 1) {

  }
  for (;gap > 0;gap /= 3) {
    for(sp124 = gap; sp124 < elements; sp124++) {
      func_hd_code_802597D8(buffer, &sp118[size * sp124], size);

      sp120 = sp124;
      while (sp120 >= gap && cmp((u16*)(sp118 + (sp120 - gap) * size), (u16*)buffer) > 0) {
        func_hd_code_802597D8(size * sp120 + &sp118[0],
                             size * (sp120 - gap) + &sp118[0] ,
                              size);
        sp120 -= gap;
      }

      func_hd_code_802597D8(&sp118[size * sp120], buffer, size);
    }
  }
}

void func_hd_code_802597D8(u8* arg0, u8* arg1, s32 arg2) {
  s32 sp4;
  for(sp4 = 0; sp4 < arg2; sp4++) {
    arg0[sp4] = arg1[sp4];
  }
}

s32 func_hd_code_80259814(u16* arg0, u16* arg1) {
  return *arg0 - *arg1;
}

void func_hd_code_80259824(Gfx** arg0, struct Model1* arg1) {
  s32 sp54;
  Gfx* entry;
  s32 sp4C;

  sp54 = 0;
  entry = *arg0;
  func_hd_code_802595E0((u8* ) &D_80365340[D_hd_code_802E8C70], characterIndex - D_hd_code_802E8C70, 0xC, func_hd_code_80259814);
  for(sp4C = D_hd_code_802E8C70; sp4C < characterIndex; sp4C++) {
    if (D_80365340[sp4C].unk8 != sp54) {
      sp54 = D_80365340[sp4C].unk8;
      if (sp4C == D_hd_code_802E8C70) {
        gDPLoadTextureBlock_4b(entry++, sp54 + 0x80000000, G_IM_FMT_I, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
      } else {
        gDPSetTextureImage(entry++, G_IM_FMT_I, G_IM_SIZ_16b, 1, sp54 + 0x80000000);
        gDPLoadSync(entry++);
        gDPLoadBlock(entry++, G_TX_LOADTILE, 0, 0, 255, 1024);
      }
    }
    gSPVertex(entry++, &D_80365348[D_8035805C][D_80365340[sp4C].unk4 * 4], 4, 0);
    gSP1Triangle(entry++, 0, 1, 2, 0);
    gSP1Triangle(entry++, 0, 2, 3, 0);
  }

  osWritebackDCache(&D_80365348[D_8035805C][D_hd_code_802E8C70 * 4], (characterIndex - D_hd_code_802E8C70) << 6);
  D_hd_code_802E8C70 = characterIndex;
  *arg0 = entry;
}

void func_hd_code_80259BD4(Gfx** arg0, struct Model1* arg1) {
  Gfx* sp1C;

  sp1C = *arg0;
  func_hd_code_8025946C(&sp1C, arg1);
  func_hd_code_80259824(&sp1C, arg1);
  *arg0 = sp1C;
}

void func_hd_code_80259C24(Gfx** arg0, struct Model1* arg1) {
  Gfx* entry;

  entry = *arg0;
  gSPMatrix(entry++, (u32) &arg1->mtx1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
  gSPMatrix(entry++, (u32) &arg1->modelview, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

  func_hd_code_8025946C(&entry, arg1);
  func_hd_code_80259824(&entry, arg1);
  *arg0 = entry;
}


void func_hd_code_80259CCC(struct Model1* arg0, const char* arg1, u16* arg2, u8 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13) {
  func_hd_code_80259EC4(arg0, arg1, arg2, arg3, arg4, (f32) arg5, arg6, (f32) arg7, arg8, (s32) (u8) arg9, (s32) (u8) arg10, (s32) (u8) arg11, (s32) (u8) arg12, (s32) (u8) arg13, (s32) (u8) arg10, (s32) (u8) arg11, (s32) (u8) arg12, (s32) (u8) arg13, (s32) (u8) arg10, (s32) (u8) arg11, (s32) (u8) arg12, (s32) (u8) arg13, (s32) (u8) arg10, (s32) (u8) arg11, (s32) (u8) arg12, (s32) (u8) arg13);
}

void func_hd_code_80259DC8(s32 arg0, u8* arg1, u16* arg2, u8 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, u8 arg9, u8 arg10, u8 arg11, u8 arg12, u8 arg13, u8 arg14, u8 arg15, u8 arg16, u8 arg17) {
  func_hd_code_80259EC4(arg0, arg1, arg2, arg3, arg4, (f32) arg5, arg6, (f32) arg7, arg8, (s32) arg9, (s32) arg10, (s32) arg11, (s32) arg12, (s32) arg13, (s32) arg10, (s32) arg11, (s32) arg12, (s32) arg13, (s32) arg14, (s32) arg15, (s32) arg16, (s32) arg17, (s32) arg14, (s32) arg15, (s32) arg16, (s32) arg17);
}

void func_hd_code_80259EC4(s32 arg0, u8* sp44_a1, u16* sp48_a2, u8 arg3, s32 arg4, f32 arg5, s32 arg6, f32 arg7, s32 arg8, u8 sp67, u8 sp44_a10, u8 sp44_a11, u8 sp44_a12, u8 sp44_a13, u8 sp44_a14, u8 sp44_a15, u8 sp44_a16, u8 sp44_a17, u8 sp44_a18, u8 sp44_a19, u8 sp48_a20, u8 sp48_a21, u8 sp48_a22, u8 sp48_a23, u8 sp48_a24, u8 sp48_a25) {
    u16 sp3E;
    u8* sp38;
    u16* sp34;
    u8 sp33;
    f32 sp2C;
    u8 sp2B;
    u8 sp2A;
    u8 sp29;
    u8 sp28;
    s32 sp24;

    sp33 = 0;
    sp2B = 0;
    sp2A = 0;
    if ((sp44_a1 == NULL) || (*sp44_a1 == 0)) {
        return;
    }

    sp38 = sp44_a1;
    sp34 = sp48_a2;
    if (!sp67) {
        if (sp2B) {
            while (*sp34 != 0x0FFE) {
                sp34++;
            }
            sp34--;
        } else {
            while (*sp38 != 0) {
                sp38++;
            }
            sp38--;
        }
    }
    if (arg4 != 0) {
        arg5 = (f32) func_hd_code_8025B498(arg4, (u32) arg7, sp44_a1, sp48_a2);
    }
    if (sp33 == 0) {
        do {
            switch (sp2A) {                     /* switch 1; irregular */
            case 0:                             /* switch 1 */
                sp2C = 0.21f;
                switch (sp38[0]) {              /* switch 2 */
                case 0x30:                      /* switch 2 */
                    sp3E = 0;
                    sp2C = 0.25f;
                    break;
                case 0x31:                      /* switch 2 */
                    sp3E = 1;
                    sp2C = 0.25f;
                    break;
                case 0x32:                      /* switch 2 */
                    sp3E = 2;
                    sp2C = 0.25f;
                    break;
                case 0x33:                      /* switch 2 */
                    sp3E = 3;
                    sp2C = 0.25f;
                    break;
                case 0x34:                      /* switch 2 */
                    sp3E = 4;
                    sp2C = 0.25f;
                    break;
                case 0x35:                      /* switch 2 */
                    sp3E = 5;
                    sp2C = 0.25f;
                    break;
                case 0x36:                      /* switch 2 */
                    sp3E = 6;
                    sp2C = 0.25f;
                    break;
                case 0x37:                      /* switch 2 */
                    sp3E = 7;
                    sp2C = 0.25f;
                    break;
                case 0x38:                      /* switch 2 */
                    sp3E = 8;
                    sp2C = 0.25f;
                    break;
                case 0x39:                      /* switch 2 */
                    sp3E = 9;
                    sp2C = 0.25f;
                    break;
                case 0x41:                      /* switch 2 */
                    sp3E = 0xA;
                    break;
                case 0x42:                      /* switch 2 */
                    sp3E = 0xB;
                    break;
                case 0x43:                      /* switch 2 */
                    sp3E = 0xC;
                    break;
                case 0x44:                      /* switch 2 */
                    sp3E = 0xD;
                    break;
                case 0x7F:                      /* switch 2 */
                    sp3E = 0xE;
                    sp2C = 0.05f;
                    break;
                case 0x45:                      /* switch 2 */
                    sp3E = 0xF;
                    break;
                case 0x46:                      /* switch 2 */
                    sp3E = 0x10;
                    break;
                case 0x47:                      /* switch 2 */
                    sp3E = 0x11;
                    break;
                case 0x48:                      /* switch 2 */
                    sp3E = 0x12;
                    break;
                case 0x49:                      /* switch 2 */
                    sp3E = 0x13;
                    sp2C = 0.27f;
                    break;
                case 0x4A:                      /* switch 2 */
                    sp3E = 0x14;
                    break;
                case 0x4B:                      /* switch 2 */
                    sp3E = 0x15;
                    break;
                case 0x4C:                      /* switch 2 */
                    sp3E = 0x16;
                    break;
                case 0x4D:                      /* switch 2 */
                    sp3E = 0x17;
                    sp2C = 0.05f;
                    break;
                case 0x4E:                      /* switch 2 */
                    sp3E = 0x18;
                    break;
                case 0x4F:                      /* switch 2 */
                    sp3E = 0x19;
                    break;
                case 0x50:                      /* switch 2 */
                    sp3E = 0x1A;
                    break;
                case 0x51:                      /* switch 2 */
                    sp3E = 0x1B;
                    break;
                case 0x52:                      /* switch 2 */
                    sp3E = 0x1C;
                    break;
                case 0x53:                      /* switch 2 */
                    sp3E = 0x1D;
                    break;
                case 0x54:                      /* switch 2 */
                    sp3E = 0x1E;
                    break;
                case 0x55:                      /* switch 2 */
                    sp3E = 0x1F;
                    break;
                case 0x56:                      /* switch 2 */
                    sp3E = 0x20;
                    break;
                case 0x57:                      /* switch 2 */
                    sp3E = 0x21;
                    sp2C = 0.05f;
                    break;
                case 0x58:                      /* switch 2 */
                    sp3E = 0x22;
                    break;
                case 0x59:                      /* switch 2 */
                    sp3E = 0x23;
                    break;
                case 0x5A:                      /* switch 2 */
                    sp3E = 0x24;
                    break;
                case 0x27:                      /* switch 2 */
                    sp3E = 0x26;
                    sp2C = 0.25f;
                    break;
                case 0x29:                      /* switch 2 */
                    sp3E = 0x27;
                    sp2C = 0.25f;
                    break;
                case 0x3A:                      /* switch 2 */
                    sp3E = 0x28;
                    sp2C = 0.36f;
                    break;
                case 0x2C:                      /* switch 2 */
                    sp3E = 0x29;
                    sp2C = 0.25f;
                    break;
                case 0x24:                      /* switch 2 */
                    sp3E = 0x2A;
                    break;
                case 0x21:                      /* switch 2 */
                    sp3E = 0x2B;
                    sp2C = 0.25f;
                    break;
                case 0x2E:                      /* switch 2 */
                    sp3E = 0x2C;
                    sp2C = 0.3f;
                    break;
                case 0x2D:                      /* switch 2 */
                    sp3E = 0x2D;
                    sp2C = 0.25f;
                    break;
                case 0x28:                      /* switch 2 */
                    sp3E = 0x2E;
                    sp2C = 0.25f;
                    break;
                case 0x25:                      /* switch 2 */
                    sp3E = 0x2F;
                    break;
                case 0x3F:                      /* switch 2 */
                    sp3E = 0x30;
                    break;
                case 0x23:                      /* switch 2 */
                    sp3E = 0x31;
                    break;
                case 0x2F:                      /* switch 2 */
                    sp3E = 0x32;
                    break;
                case 0x20:                      /* switch 2 */
                case 0x26:                      /* switch 2 */
                    sp3E = 0;
                    sp2C = 0.3f;
                    break;
                case 0x61:                      /* switch 2 */
                case 0x62:                      /* switch 2 */
                case 0x64:                      /* switch 2 */
                case 0x65:                      /* switch 2 */
                case 0x6B:                      /* switch 2 */
                case 0x6D:                      /* switch 2 */
                    sp3E = sp38[0] - 0x22C;
                    break;
                default:                        /* switch 2 */
                    sp3E = 0;
                    sp2C = 0.0f;
                    break;
                }
                sp3E += 0xF4C;
                break;
            case 1:                             /* switch 1 */
                sp2C = 1.0f;
                if ((s32) sp34[0] < 0x200) {
                    sp3E = sp34[0] + 0xD4C;
                } else if (sp34[0] == 0x1001) {
                    sp3E = 0xF7D;
                } else {
                    sp3E = 0xD4C;
                }
                break;
            }
            if (arg3 == 1) {
                if (sp67 != 0) {
                    arg5 -= sp2C * arg7;
                } else {
                    arg5 += sp2C * arg7;
                }
            }
            if (sp2B != 0) {
                sp24 = (s32) sp34[0];
            } else {
                sp24 = (s32) sp38[0];
            }
            if ((D_hd_code_802E8C94[sp2A] != sp24) && ((u16) D_hd_code_802E8C90[sp2A] != sp24) && ((u16) D_hd_code_802E8C8C[sp2A] != sp24) && ((sp44_a13 != 0) || (sp44_a17 != 0) || (sp48_a21 != 0) || (sp48_a25 != 0))) {
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.ob[0] = arg5;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.ob[1] = arg6;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.ob[2] = -0xA;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.flag = 0;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.tc[0] = 0;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.tc[1] = 0x3E0;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.cn[0] = sp44_a10;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.cn[1] = sp44_a11;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.cn[2] = sp44_a12;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.cn[3] = sp44_a13;
                D_hd_code_802E8C78++;

                D_80365348[D_8035805C][D_hd_code_802E8C78].v.ob[0] = arg5 + arg7;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.ob[1] = arg6;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.ob[2] = -0xA;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.flag = 0;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.tc[0] = 0x3E0;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.tc[1] = 0x3E0;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.cn[0] = sp44_a14;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.cn[1] = sp44_a15;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.cn[2] = sp44_a16;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.cn[3] = sp44_a17;
                D_hd_code_802E8C78++;

                D_80365348[D_8035805C][D_hd_code_802E8C78].v.ob[0] = (s16) (s32) (arg5 + arg7);
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.ob[1] = (s16) (arg6 + arg8);
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.ob[2] = -0xA;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.flag = 0;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.tc[0] = 0x3E0;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.tc[1] = 0;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.cn[0] = sp44_a18;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.cn[1] = sp44_a19;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.cn[2] = sp48_a20;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.cn[3] = sp48_a21;
                D_hd_code_802E8C78++;

                D_80365348[D_8035805C][D_hd_code_802E8C78].v.ob[0] = (s16) (s32) arg5;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.ob[1] = (s16) (arg6 + arg8);
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.ob[2] = -0xA;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.flag = 0;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.tc[0] = 0;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.tc[1] = 0;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.cn[0] = sp48_a22;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.cn[1] = sp48_a23;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.cn[2] = sp48_a24;
                D_80365348[D_8035805C][D_hd_code_802E8C78].v.cn[3] = sp48_a25;
                D_hd_code_802E8C78++;

                D_80365340[characterIndex].unk0 = sp24;
                if ((sp44_a10 != 0) || (sp44_a12 != 0) || (sp44_a11 != 0)) {
                    D_80365340[characterIndex].unk0 += 0x8000;
                }
                D_80365340[characterIndex].unk4 = (s32) characterIndex;
                D_80365340[characterIndex].unk8 = func_hd_code_8025B0B8(sp3E);
                characterIndex++;
                if (characterIndex >= maxCharacters) {
                    func_hd_code_8029A7E4("\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n", "index<maxCharacters", "drawtext.c", 0x1B3);
                }
                if (characterIndex >= maxCharacters) {
                    func_hd_code_8029A7E4("%d %d\n", characterIndex, maxCharacters);
                }
            }
            if (arg3 == 1) {
                if (sp67 != 0) {
                    arg5 += arg7 - (sp2C * arg7);
                } else {
                    arg5 -= arg7 - (sp2C * arg7);
                }
            } else if ((u16) D_hd_code_802E8C8C[sp2A] != sp24) {
                if (sp67 != 0) {
                    arg5 += arg7 * D_hd_code_802E8C84[sp2A];
                }
                if (sp67 == 0) {
                    arg5 -= arg7 * D_hd_code_802E8C84[sp2A];
                }
            }
            if (sp67 != 0) {
                if (sp2B != 0) {
                    sp34++;
                    if (sp34[0] == 0xFFE) {
                        sp33 = 1;
                    }
                } else {
                    sp38 += 1;
                    if (sp38[0] == 0) {
                        sp33 = 1;
                    }
                }
            } else if (sp2B != 0) {
                if (sp34 == sp48_a2) {
                    sp33 = 1;
                }
                sp34--;
            } else {
                if (sp38 == sp44_a1) {
                    sp33 = 1;
                }
                sp38 -= 1;
            }
        } while (sp33 == 0);
    }

}
