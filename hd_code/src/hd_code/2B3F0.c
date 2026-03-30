#include "common.h"
#include "variables.h"
#include "functions.h"
#include "structs.h"

void func_hd_code_8026A5CC(void*, void*, u32);              /* extern */
s32 func_hd_code_8026AD30(s16);                         /* extern */
void func_hd_code_802AC544(s16, s16, s16);             /* extern */

extern u16 D_8036BBB2[];
extern s32 D_hd_code_802FA200[];
extern s32 D_8036BED4;
extern f32 D_8036BEDC;
extern s8 D_8036BEE0;
extern s32 D_803BE70C;
extern s32 D_803BE710;
extern s16 D_803BE714;
extern s32 D_hd_code_802F99C0;

void LoadLevelRdus(struct vec3s* arg0, struct vec3s* arg1) {
  s32 pad1;

  D_8036EB90 = 0;
  D_8036EA7C = 0;
  if (D_hd_code_80364A90 != 0x40) {
    D_8036BED4 = *D_8036BBB0 = 0;
  }
  D_8036BED8 = D_hd_code_80358070;
  D_8036BEE0 = 0;
  D_8036BEDC = 999999.0f;
  while (arg0 != arg1) {
    D_8036BED8[D_8036EB90].x = arg0->x;
    D_8036BED8[D_8036EB90].y = arg0->y;
    D_8036BED8[D_8036EB90].z = arg0->z;
    D_8036BED8[D_8036EB90].unk6 = 0;
    D_8036BED8[D_8036EB90].unk7 = ((arg0->z / (D_803BE710 >> 5)) * D_803BE714) + (arg0->x / (D_803BE70C >> 5));

    func_hd_code_8026A5CC(D_8036BED8[D_8036EB90].unk8, &D_hd_code_802F99C0, 0x40U);
    func_hd_code_8026A5CC(D_8036BED8[D_8036EB90].unk48, &D_hd_code_802F99C0, 0x40U);
    D_8036EB90++;
    arg0++;
  }
  D_hd_code_80358070 += D_8036EB90 * 0x88;
}

u8 func_hd_code_8026FE6C(s32 arg0) {
  return D_8036BED8[arg0].unk6;
}

void func_hd_code_8026FE8C(s32 arg0) {
  D_8036BED8[arg0].unk6 = 1;
  D_8036EA7C += 1;
}

void func_hd_code_8026FEC4(void) {
  s32 sp34;
  s32 pad30;
  s32 sp2C;
  u8 sp2B;
  u8 sp2A;

  sp2A = 0;
  sp2B = (((s32) D_hd_code_803643E8 / (s32) D_803BE710) * D_803BE714) + ((s32) D_hd_code_803643E0 / (s32) D_803BE70C);

  for(sp34 = 0;sp34 < (s32) D_8036EB90; sp34++) {
    if (((u8) D_8036BED8[sp34].unk7 == sp2B) && ((u8) D_8036BED8[sp34].unk6 == 0)) {
      sp2C = func_hd_code_8026A6F0((s32) D_hd_code_803643E0 >> 5, (s32) D_hd_code_803643E4 >> 5, (s32) D_hd_code_803643E8 >> 5, (s32) D_8036BED8[sp34].x, (s32) D_8036BED8[sp34].y, (s32) D_8036BED8[sp34].z);
      if (sp2C < D_hd_code_802FA200[D_hd_code_80364456]) {
        D_8036EA7C++;
        if ((D_8036EA7C >= 4) && D_hd_code_802E8BD0 == 0) {
          func_hd_code_8026AD30(0x46);
        }
        if (D_hd_code_80364A90 != 0x40) {
          D_8036BBB0[D_8036BED4] = D_8036BBB2[D_8036BED4] = sp34;
          D_8036BED4++;
        }
        func_hd_code_802AC544(D_8036BED8[sp34].x, D_8036BED8[sp34].y + 5, D_8036BED8[sp34].z);
        D_8036BED8[sp34].unk6 = 1;
        if (sp2A == 0) {
          sp2A = 1;
          if (D_hd_code_80364AA8 == 0x40) {
            sndPlaySfx(D_hd_code_80367738, 0x3B, NULL);
          } else {
            sndPlaySfx(D_hd_code_80367738, 0x27, NULL);
          }
        }
      }
    }
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/2B3F0/func_hd_code_802701A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/2B3F0/func_hd_code_80270A54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/2B3F0/func_hd_code_80270AE0.s")
