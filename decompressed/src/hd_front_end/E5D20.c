#include "common.h"
#include "../hd_code/macros.h"
#include "../hd_code/structs.h"
#include "../hd_code/hd.h"
#include "../hd_code/yoshi.h"
#include "../hd_code/functions.h"
#include "../hd_code/variables.h"
#include "../hd_code/io/controller.h"
#include "structs.h"

extern u16 D_hd_code_80364EF0[][0x10];
extern u16 D_hd_code_80364F70[];

void func_hd_front_end_801F8354(u8);                /* extern */

void* func_hd_front_end_80201E80(void) {
  u8 sp2F;
  void* sp28;

  sp28 = NULL;
  rmonPrintf("restoring from EE memory\n");
  for (sp2F = 0; (sp2F < 0x3C) && (sp28 == NULL); sp2F++) {
    if (!(sp2F & 1)) {
      osSendMesg(&D_hd_front_end_80219EF8, (void*) ((sp2F << 8) | 0xA | (playerNumber << 0x10) | 0x01000000), 1);
      osRecvMesg(&D_hd_front_end_80219F50, &sp28, 1);
    }
    if (((players[playerNumber].unk18[sp2F] > 0) && (players[playerNumber].unk18[sp2F] < 6)?1:0) &&
        (sp2F != 0x31) && (sp2F != 0x2F) && (sp2F != 0x26) && (sp28 == NULL)) {
      if (D_hd_code_802E8F94[sp2F].unk0 == 1) {
        *((u64*)pakBuffer) = 0x1234567887654321;
        osSendMesg(&D_hd_front_end_80219EF8, (void*) ((sp2F << 8) | 0xD | (playerNumber << 0x10) | 0x01000000), 1);
        osRecvMesg(&D_hd_front_end_80219F50, NULL, 1);
      }
      func_hd_front_end_801F8354(playerNumber);
      D_hd_code_80364EF0[playerNumber][D_hd_code_802E8C44[players[playerNumber].unk92[sp2F]]] = D_hd_code_80364F70[sp2F * 2];
      osSendMesg(&D_hd_front_end_80219EF8, (void*) ((sp2F << 8) | 9 | (playerNumber << 0x10) | 0x01000000), 1);
      osRecvMesg(&D_hd_front_end_80219F50, NULL, 1);
        }
  }
  return sp28;
}

