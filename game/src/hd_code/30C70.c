#include "common.h"
#include "functions.h"
#include "structs.h"
#include "variables.h"

// Proposed file name: target_markers.c
//
// This file draws the pulsing corner-bracket markers around the current
// target building and contains the world-to-screen projection helper used
// throughout the HUD. Key variables (declared elsewhere): D_hd_code_8036C790 = the
// current target's 4 corner points (fed by the building system),
// D_hd_code_8036C794/D_hd_code_8036C798 = the locked-on target and its id, D_hd_code_8036C7A0[10] =
// recently marked targets (not re-marked until they leave the screen),
// D_hd_code_8036C7C8 = distance to the locked target (drives the green-to-red
// color), D_hd_code_802FAD40/44/48 = the bracket pulse animation, and
// D_hd_code_8036C7CC = how many marker points were on screen this frame.

// <bss>
struct vec3s* D_hd_code_8036C790;
struct vec3s* D_hd_code_8036C794;
s32 D_hd_code_8036C798;
s32 D_hd_code_8036C79C;
struct vec3s* D_hd_code_8036C7A0[10];
s32 D_hd_code_8036C7C8;
u8 D_hd_code_8036C7CC;
u8 D_hd_code_8036C7CD;
u16 D_hd_code_8036C7CE;
Vtx D_hd_code_8036C7D0[2][4];
Mtx D_hd_code_8036C850[2];
// </bss>

// <data>
u8 D_hd_code_802FA940[32*32] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x99, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x99, 0xAA, 0xAA, 0xAA, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDD, 0xAA, 0xAA, 0xAA, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x99, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0xEE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEE, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0xFF, 0xFF, 0xFF, 0xFF, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDD, 0xFF, 0xFF, 0xCC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0xFF, 0xFF, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x99, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
s32 D_hd_code_802FAD40 = 0;
s32 D_hd_code_802FAD44 = 0;
u8 D_hd_code_802FAD48 = 0;
// </data>

// Reset the marked-target list at level init
// Proposed name: ResetTargetMarkers
void func_hd_code_80275430(void)
{
  s32 sp4;

  for (sp4 = 0; sp4 < 10; sp4++)
  {
    D_hd_code_8036C7A0[sp4] = 0;
  }
  D_hd_code_8036C794 = NULL;
  D_hd_code_8036C7CC = 0;
}

// Target marker update + draw: shows the one-time "path blocked" hint, then
// locks onto the current target building when its projected bounding box
// comes on screen (and it hasn't been marked recently). While locked,
// projects the 4 corners each frame, colors the brackets by distance (green
// far, red near, like the carrier arrow), draws 4 corner quads pulsing in
// and out (5 half-cycles, then the marker is dismissed), and finally prunes
// off-screen entries from the marked list.
// Proposed name: UpdateDrawTargetMarkers
void func_hd_code_80275478(struct Model1* arg0, Gfx** arg1, s32 arg2) {
    s16 sp76;
    s16 sp74;
    s16 sp72;
    Gfx* entry;
    s16 sp6A;
    s16 sp68;
    s16 sp66;
    s16 sp64;
    s16 sp62;
    s16 sp60;
    s16 sp5E;
    s16 sp5C;
    u8 sp5B;
    u8 sp5A;
    s16 sp58;
    s16* sp54;
    s32 sp50;

    sp72 = 0x10;
    entry = *arg1;
    sp62 = 0x7FFF,
    sp60 = -0x8000,
    sp5E = 0x7FFF,
    sp5C = -0x8000;
    sp50 = func_hd_code_802BCE40();
    D_hd_code_8036C7CC = 0;
    sp54 = D_hd_code_8036C790;
    if ((D_hd_code_8036EB98 == 0) && (sp50 == 0) && (D_hd_code_80364AA8 == 1) && (D_hd_code_802E8BD0 == 0)) {
        if (func_hd_code_8026AD30(0x4B) == 0) {
            func_hd_code_8026AF6C(0x803DU);
            func_hd_code_80277EDC(3, 1, 2, 0x82);
        }
        D_hd_code_8036EB98 = 1;
    }
    if ((D_hd_code_8036C790 != NULL) && ((func_hd_code_802768A8() == 0) || ((u8) arg2 != 0)) && (D_hd_code_8036C794 == NULL)) {
        for(sp76 = 0; sp76 < 4; sp76++) {
            func_hd_code_8027690C(arg0, D_hd_code_8036C790->x, D_hd_code_8036C790->y, D_hd_code_8036C790->z, &sp6A, &sp68, 0, 0, 0, 1.0f);
            D_hd_code_8036C790++;
            if (sp6A < sp62) {
                sp62 = sp6A;
            }
            if (sp6A > sp60) {
                sp60 = sp6A;
            }
            if (sp68 < sp5E) {
                sp5E = sp68;
            }
            if (sp68 > sp5C) {
                sp5C = sp68;
            }

        }
        D_hd_code_8036C7CC = 0;
        for(sp74 = 0; sp74 < 4; sp74++) {
            switch (sp74) {                         /* switch 1; irregular */
            case 0:                                 /* switch 1 */
                sp66 = ((sp60 - sp62) / 2) + sp62;
                sp64 = sp5E;
                break;
            case 1:                                 /* switch 1 */
                sp66 = ((sp60 - sp62) / 2) + sp62;
                sp64 = sp5C;
                break;
            case 2:                                 /* switch 1 */
                sp66 = sp62;
                sp64 = ((sp5C - sp5E) / 2) + sp5E;
                break;
            case 3:                                 /* switch 1 */
                sp66 = sp60;
                sp64 = ((sp5C - sp5E) / 2) + sp5E;
                break;
            }
            if ((sp66 < 0x136) && (sp66 >= 0xB) && (sp64 < 0xE6) && (sp64 >= 0xB)) {
                D_hd_code_8036C794 = sp54;
                D_hd_code_8036C798 = sp50;
                D_hd_code_803F7809 = D_hd_code_803F7808;
                D_hd_code_802FAD44 = 0;
            }

        }
    }
    if (D_hd_code_8036C794 != NULL) {
        func_hd_code_802BD10C(D_hd_code_8036C798);
        if ((D_hd_code_8036C7C8 >= 0x5DD) || (D_hd_code_803643DB == 0)) {
            sp5A = 0xFF;
            sp5B = 0;
        } else if (D_hd_code_8036C7C8 < 0x1F4) {
            sp5B = 0xFF;
            sp5A = 0;
        } else {
            sp58 = (((D_hd_code_8036C7C8 - 0x1F4) / 1000.0f) * 511.0f);
            if (sp58 < 0x100) {
                sp5A = sp58,
                sp5B = 0xFF;
            } else {
                sp5A = 0xFF,
                sp5B = 0x1FE - sp58;
            }
        }
        sp54 = D_hd_code_8036C794;
        for(sp76 = 0; sp76 < 4; sp76++) {
            func_hd_code_8027690C(arg0, sp54[0], sp54[1], sp54[2], &sp6A, &sp68, 0, 0, 0, 1.0f);
            sp54 += 3;
            if (sp6A < sp62) {
                sp62 = sp6A;
            }
            if (sp6A > sp60) {
                sp60 = sp6A;
            }
            if (sp68 < sp5E) {
                sp5E = sp68;
            }
            if (sp68 > sp5C) {
                sp5C = sp68;
            }
        }

        for(sp74 = 0; sp74 < 4; sp74++) {
            switch (sp74) {
            case 0:
                sp66 = ((sp60 - sp62) / 2) + sp62,
                sp64 = sp5E - D_hd_code_802FAD40;
                break;
            case 1:
                sp66 = ((sp60 - sp62) / 2) + sp62,
                sp64 = sp5C + D_hd_code_802FAD40;
                break;
            case 2:
                sp66 = sp62 - D_hd_code_802FAD40,
                sp64 = ((sp5C - sp5E) / 2) + sp5E;
                break;
            case 3:
                sp66 = sp60 + D_hd_code_802FAD40,
                sp64 = ((sp5C - sp5E) / 2) + sp5E;
                break;
            }
            if ((sp66 < 0x136) && (sp66 >= 0xB) && (sp64 < 0xE6) && (sp64 >= 0xB)) {
                D_hd_code_8036C7CC += 1;
            }
            sp72 = func_hd_code_80276080(arg0, sp74, sp72, sp66, sp64, 8, 8, sp5B, sp5A, 0, 0xFF);
        }

        if (D_hd_code_802FAD48 == 0) {
            D_hd_code_802FAD40++;
            if (D_hd_code_802FAD40 == 0xA) {
                D_hd_code_802FAD48 = 1;
                D_hd_code_802FAD44 += 1;
            }
        } else {
            D_hd_code_802FAD40--;
            if (D_hd_code_802FAD40 == 0) {
                D_hd_code_802FAD48 = 0;
                D_hd_code_802FAD44 += 1;
            }
        }
        if (D_hd_code_802FAD44 == 5) {
            D_hd_code_8036C794 = NULL;
        }
        entry = func_hd_code_80275DA4(entry, 0);
        gSPVertex(entry++, &D_2000000.unk1F00, 16, 0);

        sp72 = 0;
        for(sp74 = 0; sp74 < 4; sp74++) {
            gSP1Triangle(entry++, sp72, sp72 + 1, sp72 + 2, 0);
            gSP1Triangle(entry++, sp72, sp72 + 2, sp72 + 3, 0);

            sp72 += 4;
        }
    }
    func_hd_code_8027656C(arg0);
    *arg1 = entry;
}

// Set up the RDP for marker drawing and load the 32x32 IA8 marker texture
// (D_hd_code_802FA940); arg1 != 0 skips the ortho matrix load
// Proposed name: BeginMarkerDraw
Gfx* func_hd_code_80275DA4(Gfx* gfx, u8 arg1) {
  Gfx* entry;

  entry = gfx;
  if (!arg1) {
    gSPMatrix(entry++, &D_2000000.mtx1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(entry++, &D_2000000.modelview, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
  }
  gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
  gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
  gDPPipeSync(entry++);
  gDPSetCycleType(entry++, G_CYC_1CYCLE);
  gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
  gDPSetCombineMode(entry++, G_CC_MODULATEIA, G_CC_MODULATEIA);
  gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);
  gDPLoadTextureBlock(entry++, OS_PHYSICAL_TO_K0(D_hd_code_802FA940), G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

  return entry;
}

// Append a flat-colored marker quad (single color for all corners)
// Proposed name: AddMarkerQuad
Gfx *func_hd_code_80276080(struct Model1* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10) {
  return func_hd_code_80276130(arg0, (s32) (u8) arg1, arg2, arg3, arg4, arg5, arg6, (s32) (u8) arg7, (s32) (u8) arg8, (s32) (u8) arg9, (s32) (u8) arg10, (s32) (u8) arg7, (s32) (u8) arg8, (s32) (u8) arg9, (s32) (u8) arg10, (s32) (u8) arg7, (s32) (u8) arg8, (s32) (u8) arg9, (s32) (u8) arg10, (s32) (u8) arg7, (s32) (u8) arg8, (s32) (u8) arg9, (s32) (u8) arg10);
}

// Fill a 4-vertex screen-space quad at (arg3, arg4) +- (arg5, arg6) with
// per-corner colors; arg1 (0..3) selects one of four texcoord orientations
// so the same texture faces each screen edge. Returns the next vertex index.
// Proposed name: FillMarkerQuad
s32 func_hd_code_80276130(struct Model1* arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, u8 arg8, u8 arg9, u8 arg10, u8 arg11, u8 arg12, u8 arg13, u8 arg14, u8 arg15, u8 arg16, u8 arg17, u8 arg18, u8 arg19, u8 arg20, u8 arg21, u8 arg22) {

    switch (arg1) {                              /* irregular */
    case 0:
        arg0->unk1E00[arg2].v.tc[0] = 0,
        arg0->unk1E00[arg2].v.tc[1] = 0;

        arg0->unk1E00[arg2+1].v.tc[0] = 0x3E0,
        arg0->unk1E00[arg2+1].v.tc[1] = 0;

        arg0->unk1E00[arg2+2].v.tc[0] = 0x3E0,
        arg0->unk1E00[arg2+2].v.tc[1] = 0x3E0;

        arg0->unk1E00[arg2+3].v.tc[0] = 0,
        arg0->unk1E00[arg2+3].v.tc[1] = 0x3E0;
        break;
    case 1:
        arg0->unk1E00[arg2].v.tc[0] = 0,
        arg0->unk1E00[arg2].v.tc[1] = 0x3E0;

        arg0->unk1E00[arg2+1].v.tc[0] = 0x3E0,
        arg0->unk1E00[arg2+1].v.tc[1] = 0x3E0;

        arg0->unk1E00[arg2+2].v.tc[0] = 0x3E0,
        arg0->unk1E00[arg2+2].v.tc[1] = 0;

        arg0->unk1E00[arg2+3].v.tc[0] = 0,
        arg0->unk1E00[arg2+3].v.tc[1] = 0;
        break;
    case 2:
        arg0->unk1E00[arg2].v.tc[0] = 0,
        arg0->unk1E00[arg2].v.tc[1] = 0;

        arg0->unk1E00[arg2+1].v.tc[0] = 0,
        arg0->unk1E00[arg2+1].v.tc[1] = 0x3E0;

        arg0->unk1E00[arg2+2].v.tc[0] = 0x3E0,
        arg0->unk1E00[arg2+2].v.tc[1] = 0x3E0;

        arg0->unk1E00[arg2+3].v.tc[0] = 0x3E0,
        arg0->unk1E00[arg2+3].v.tc[1] = 0;
        break;
    case 3:
        arg0->unk1E00[arg2].v.tc[0] = 0,
        arg0->unk1E00[arg2].v.tc[1] = 0x3E0;

        arg0->unk1E00[arg2+1].v.tc[0] = 0,
        arg0->unk1E00[arg2+1].v.tc[1] = 0;

        arg0->unk1E00[arg2+2].v.tc[0] = 0x3E0,
        arg0->unk1E00[arg2+2].v.tc[1] = 0;

        arg0->unk1E00[arg2+3].v.tc[0] = 0x3E0,
        arg0->unk1E00[arg2+3].v.tc[1] = 0x3E0;
        break;
    }

    arg0->unk1E00[arg2].v.ob[0] = (s16) (arg3 - arg5);
    arg0->unk1E00[arg2].v.ob[1] = arg4 - arg6;
    arg0->unk1E00[arg2].v.ob[2] = -0xA;
    arg0->unk1E00[arg2].v.flag = 0;
    arg0->unk1E00[arg2].v.cn[0] = (u8) arg7;
    arg0->unk1E00[arg2].v.cn[1] = (u8) arg8;
    arg0->unk1E00[arg2].v.cn[2] = (u8) arg9;
    arg0->unk1E00[arg2].v.cn[3] = (u8) arg10;
    arg2++;

    arg0->unk1E00[arg2].v.ob[0] = (s16) (arg3 + arg5);
    arg0->unk1E00[arg2].v.ob[1] = arg4 - arg6;
    arg0->unk1E00[arg2].v.ob[2] = -0xA;
    arg0->unk1E00[arg2].v.flag = 0;
    arg0->unk1E00[arg2].v.cn[0] = (u8) arg11;
    arg0->unk1E00[arg2].v.cn[1] = (u8) arg12;
    arg0->unk1E00[arg2].v.cn[2] = (u8) arg13;
    arg0->unk1E00[arg2].v.cn[3] = (u8) arg14;
    arg2++;

    arg0->unk1E00[arg2].v.ob[0] = (s16) (arg3 + arg5);
    arg0->unk1E00[arg2].v.ob[1] = arg4 + arg6;
    arg0->unk1E00[arg2].v.ob[2] = -0xA;
    arg0->unk1E00[arg2].v.flag = 0;
    arg0->unk1E00[arg2].v.cn[0] = (u8) arg15;
    arg0->unk1E00[arg2].v.cn[1] = (u8) arg16;
    arg0->unk1E00[arg2].v.cn[2] = (u8) arg17;
    arg0->unk1E00[arg2].v.cn[3] = (u8) arg18;
    arg2++;

    arg0->unk1E00[arg2].v.ob[0] = (s16) (arg3 - arg5);
    arg0->unk1E00[arg2].v.ob[1] = arg4 + arg6;
    arg0->unk1E00[arg2].v.ob[2] = -0xA;
    arg0->unk1E00[arg2].v.flag = 0;
    arg0->unk1E00[arg2].v.cn[0] = (u8) arg19;
    arg0->unk1E00[arg2].v.cn[1] = (u8) arg20;
    arg0->unk1E00[arg2].v.cn[2] = (u8) arg21;
    arg0->unk1E00[arg2].v.cn[3] = (u8) arg22;
    arg2++;

    return arg2;
}

// Drop entries from the marked-target list once their box is fully off
// screen, allowing them to be marked again later
// Proposed name: PruneMarkedTargets
void func_hd_code_8027656C(struct Model1* arg0) {
    s32 sp5C;
    s32 sp58;
    struct vec3s* sp54;
    s16 sp52;
    s16 sp50;
    s16 sp4E;
    s16 sp4C;
    s16 sp4A;
    s16 sp48;
    s16 sp46;
    s16 sp44;
    u8 sp43;

    for(sp5C = 0; sp5C < 10; sp5C++) {
        if (D_hd_code_8036C7A0[sp5C] != NULL) {
            sp4A = 0x7FFF,
            sp48 = -0x8000;

            sp46 = 0x7FFF,
            sp44 = -0x8000;

            sp54 = D_hd_code_8036C7A0[sp5C];
            for(sp58 = 0; sp58 < 4; sp58++) {
                func_hd_code_8027690C(arg0, (f32) sp54->x, (f32) sp54->y, (f32) sp54->z, &sp52, &sp50, 0, 0, 0, 1.0f);
                sp54++;
                if (sp52 < sp4A) {
                    sp4A = sp52;
                }
                if (sp52 > sp48) {
                    sp48 = sp52;
                }
                if (sp50 < sp46) {
                    sp46 = sp50;
                }
                if (sp50 > sp44) {
                    sp44 = sp50;
                }
            }
            sp58 = 0;
            sp43 = 0;
            while((sp58 < 4) && (sp43 == 0)) {
                switch (sp58) {                         /* irregular */
                case 0:
                    sp4E = ((sp48 - sp4A) / 2) + sp4A;
                    sp4C = sp46;
                    break;
                case 1:
                    sp4E = ((sp48 - sp4A) / 2) + sp4A;
                    sp4C = sp44;
                    break;
                case 2:
                    sp4E = sp4A;
                    sp4C = ((sp44 - sp46) / 2) + sp46;
                    break;
                case 3:
                    sp4E = sp48;
                    sp4C = ((sp44 - sp46) / 2) + sp46;
                    break;
                }
                if ((sp4E < 0x136) && (sp4E >= 0xB) && (sp4C < 0xE6) && (sp4C >= 0xB)) {
                    sp43 = 1;
                }
                sp58 += 1;
            }

            if (sp43 == 0) {
                D_hd_code_8036C7A0[sp5C] = NULL;
            }
        }
    }
}

// Add the locked target to the marked list
// Proposed name: MarkCurrentTarget
void func_hd_code_8027684C(void) {
    s32 i = 0;

    while(i < 10) {
      if (D_hd_code_8036C7A0[i] == NULL) {
        D_hd_code_8036C7A0[i] = D_hd_code_8036C794;
        return;
      }
      i++;
    }
}

// Is the current target already in the marked list?
// Proposed name: IsTargetMarked
s32 func_hd_code_802768A8(void) {
  s32 i;

  i = 0;
  while(i < 10) {
    if ((D_hd_code_8036C7A0[i] != NULL) && (D_hd_code_8036C7A0[i] == D_hd_code_8036C790)) {
      return 1;
    }
    i++;
  }
  return 0;
}

// Project a world point to screen coordinates: through up to three optional
// extra matrices (arg6..arg8), then the modelview and projection, perspnorm
// scale, w divide and viewport transform (arg9 = resolution scale, normally
// 1.0). Returns (0x4000, 0x4000) for points behind the camera; results are
// clamped to +-16384.
// Proposed name: WorldToScreen
void func_hd_code_8027690C(struct Model1* arg0, f32 arg1, f32 arg2, f32 arg3, s16* arg4, s16* arg5, Mtx* arg6, Mtx* arg7, Mtx* arg8, f32 arg9) {
  f32 sp4C = 1.0f;
  if (arg8 != 0) {
    func_hd_code_80276D1C(arg8, arg1, arg2, arg3, sp4C, &arg1, &arg2, &arg3, &sp4C);
  }
  if (arg7 != 0) {
    func_hd_code_80276D1C(arg7, arg1, arg2, arg3, sp4C, &arg1, &arg2, &arg3, &sp4C);
  }
  if (arg6 != 0) {
    func_hd_code_80276D1C(arg6, arg1, arg2, arg3, sp4C, &arg1, &arg2, &arg3, &sp4C);
  }
  func_hd_code_80276D1C(&arg0->projection2, arg1, arg2, arg3, sp4C, &arg1, &arg2, &arg3, &sp4C);
  if (arg3 >= 0.0) {
    *arg4 = 0x4000;
    *arg5 = 0x4000;
    return;
  }
  func_hd_code_80276D1C(&arg0->projection, arg1, arg2, arg3, sp4C, &arg1, &arg2, &arg3, &sp4C);

  arg1 = (arg1 * (D_hd_code_8035807C / 65535.0));
  arg2 = (arg2 * (D_hd_code_8035807C / 65535.0));
  sp4C = (sp4C * (D_hd_code_8035807C / 65535.0));
  arg1 = arg1 / sp4C;
  arg2 = arg2 / sp4C;

  arg1 = ((320.0f * arg9) / 2.0f) * arg1;
  arg2 = ((240.0f * arg9) / 2.0f) * arg2;
  arg1 = ((320.0f * arg9) / 2.0f) + arg1;
  arg2 = ((240.0f * arg9) / 2.0f) + arg2;
  arg2 = (240.0f * arg9) - arg2;

  if ((arg1 > 0.0f ? arg1 : -arg1) >= 16384.0f) {
    arg1 = ((arg1 >= 0.0f ? 1 : -1) << 0xE);
  }
  if ((arg2 > 0.0f ? arg2 : -arg2) >= 16384.0f) {
    arg2 = ((arg2 >= 0.0f ? 1 : -1) << 0xE);
  }
  *arg4 = arg1;
  *arg5 = arg2;
}

// Multiply the homogeneous point (arg1, arg2, arg3, arg4) by fixed-point
// matrix arg0, returning x/y/z/w
// Proposed name: TransformPoint
void func_hd_code_80276D1C(Mtx* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32* arg5, f32* arg6, f32* arg7, f32* arg8) {
  f32 sp18[4][4];

  guMtxL2F(sp18, arg0);

  *arg5 = sp18[0][0] * arg1 + sp18[1][0] * arg2 + sp18[2][0] * arg3 + sp18[3][0];
  *arg6 = sp18[0][1] * arg1 + sp18[1][1] * arg2 + sp18[2][1] * arg3 + sp18[3][1];
  *arg7 = sp18[0][2] * arg1 + sp18[1][2] * arg2 + sp18[2][2] * arg3 + sp18[3][2];
  *arg8 = sp18[0][3] * arg1 + sp18[1][3] * arg2 + sp18[2][3] * arg3 + sp18[3][3];
}

// Draw a yellow edge-of-screen indicator for the world position
// (arg3, arg4, arg5) when it is off screen: project it, clamp the result to
// the screen border and draw a marker quad rotated by the camera heading
// (used in missile view to point back at the player's vehicle)
// Proposed name: DrawOffscreenIndicator
void func_hd_code_80276E50(Gfx** arg0, struct Model1* arg1, u8 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s16 sp10E;
    s16 sp10C;
    Gfx* entry;
    f32 spC8[4][4];
    f32 sp88[4][4];

    entry = *arg0;
    func_hd_code_8027690C(arg1, (f32) (arg3 >> 5), (f32) (arg4 >> 5), (f32) (arg5 >> 5), &sp10E, &sp10C, 0, 0, 0, 1.0f);
    if ((sp10E < 0x1E) || (sp10E >= 0x123) || (sp10C < 0x19) || (sp10C >= 0xD8)) {
        if (sp10E < 0x1E) {
            sp10E = 0x1E;
        }
        if (sp10C < 0x19) {
            sp10C = 0x19;
        }
        if (sp10E >= 0x123) {
            sp10E = 0x122;
        }
        if (sp10C >= 0xD8) {
            sp10C = 0xD7;
        }
        D_hd_code_8036C7D0[arg2][0].v.ob[0] = -0xF;
        D_hd_code_8036C7D0[arg2][0].v.ob[1] = -0xF;
        D_hd_code_8036C7D0[arg2][0].v.ob[2] = -0xA;
        D_hd_code_8036C7D0[arg2][0].v.tc[0] = 0;
        D_hd_code_8036C7D0[arg2][0].v.tc[1] = 0;

        D_hd_code_8036C7D0[arg2][1].v.ob[0] = 0xF;
        D_hd_code_8036C7D0[arg2][1].v.ob[1] = -0xF;
        D_hd_code_8036C7D0[arg2][1].v.ob[2] = -0xA;
        D_hd_code_8036C7D0[arg2][1].v.tc[0] = 0x3E0;
        D_hd_code_8036C7D0[arg2][1].v.tc[1] = 0;

        D_hd_code_8036C7D0[arg2][2].v.ob[0] = 0xF;
        D_hd_code_8036C7D0[arg2][2].v.ob[1] = 0xF;
        D_hd_code_8036C7D0[arg2][2].v.ob[2] = -0xA;
        D_hd_code_8036C7D0[arg2][2].v.tc[0] = 0x3E0;
        D_hd_code_8036C7D0[arg2][2].v.tc[1] = 0x3E0;

        D_hd_code_8036C7D0[arg2][3].v.ob[0] = -0xF;
        D_hd_code_8036C7D0[arg2][3].v.ob[1] = 0xF;
        D_hd_code_8036C7D0[arg2][3].v.ob[2] = -0xA;
        D_hd_code_8036C7D0[arg2][3].v.tc[0] = 0;
        D_hd_code_8036C7D0[arg2][3].v.tc[1] = 0x3E0;

        guTranslateF(spC8, (f32) sp10E, (f32) sp10C, 0.0f);
        guAlignF(sp88, (f32) (135.0 - (((f64) D_hd_code_8036443E / 4095.0) * 360.0)), 0.0f, 0.0f, 1.0f);
        guMtxCatF(sp88, spC8, spC8);
        guMtxF2L(spC8, &D_hd_code_8036C850[arg2]);

        gSPMatrix(entry++, &D_2000000.mtx1, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPMatrix(entry++, &D_hd_code_8036C850[arg2], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(entry++);
        gDPSetCycleType(entry++, G_CYC_1CYCLE);
        gDPSetRenderMode(entry++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gSPClearGeometryMode(entry++, G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | 0xFFE0CDF8);
        gSPSetGeometryMode(entry++, G_SHADE | G_SHADING_SMOOTH);
        gSPTexture(entry++, qu016(0.999985), qu016(0.999985), 0, G_TX_RENDERTILE, G_ON);
        gDPSetCombineMode(entry++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(entry++, 0, 0, 0xFF, 0xFF, 0x00, 0xFF);
        gDPLoadTextureBlock(entry++, OS_PHYSICAL_TO_K0(D_hd_code_802FA940), G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPVertex(entry++, OS_PHYSICAL_TO_K0(D_hd_code_8036C7D0[arg2]), 4, 0);
        gSP1Triangle(entry++, 0, 1, 2, 0);
        gSP1Triangle(entry++, 0, 2, 3, 0);
        gDPPipeSync(entry++);
    }

    *arg0 = entry;
}

// Allocate two 0xC80-byte double buffers (D_hd_code_8036CB48) for the following
// effect system and reset its counters
// Proposed name: InitEffectBuffers
void func_hd_code_802775C0() {
  D_hd_code_8036CB34 = 0;

  D_hd_code_8036CB48[0] = D_hd_code_80358070;
  D_hd_code_80358070 += 0xC80;

  D_hd_code_8036CB48[1] = D_hd_code_80358070;
  D_hd_code_80358070 += 0xC80;

  D_hd_code_8036CB28 = 0;
  D_hd_code_8036CB29 = 0;
}
