#ifndef HD_CODE_HD_H
#define HD_CODE_HD_H

#include <PR/sched.h>
#include <PR/ultratypes.h>
#include "structs.h"

struct VehicleSlot {
  // size: 0x74
  /* 0x00 */ Vtx* unk0; // Vertex data for model
  /* 0x04 */ Mtx** unk4; // Matrix array for even frames
  /* 0x08 */ Mtx** unk8; // Matrix array for uneven frames
  /* 0x0C */ Gfx* unkC; // main Displaylist for even frames
  /* 0x10 */ Gfx* unk10; // D_80364470
  /* 0x14 */ Gfx* unk14; // D_80364474
  /* 0x18 */ s32 unused18; // D_80364478
  /* 0x1C */ s32 unused1C; // D_8036447C
  /* 0x20 */ s32 unused20; // D_80364480
  /* 0x24 */ s32 unused24; // D_80364484
  /* 0x28 */ s32 unused28; // D_80364488
  /* 0x2C */ s32 unused2C; // D_8036448C
  /* 0x30 */ Gfx *unk30; // main Displaylist for uneven frames
  /* 0x34 */ Gfx *unk34; // D_80364494
  /* 0x38 */ Gfx *unk38; // D_80364498
  /* 0x3C */ s32 unused3C; // D_8036449C
  /* 0x40 */ u8 pad40[0x54 - 0x40];
  /* 0x54 */ Gfx *unk54; // used for shadow rendering
  /* 0x58 */ s32 unk58; // used for blur rendering
  /* 0x5C */ s32 type; /// Vehicle Type ID; see vehicles.h
  /* 0x60 */ s32 unk60; // Some kind of env color?
  /* 0x64 */ s32 unk64;
  /* 0x68 */ s32 unk68;
  /* 0x6C */ s32 unk6C;
  /* 0x70 */ s32 unk70;
}; // Size: 0x74

// Perhaps some kind of Scene struct?
typedef struct UnknownData8024C414_s {
  /* 0x00 */ struct UnknownData8024C414_s* unk0; // parent?
  /* 0x04 */ u32 pad1;
  /* 0x08 */ u8 levelno;
  /* 0x09 */ u8 unk9;
  /* 0x0A */ u16 unkA;
  /* 0x0C */ u8 rankLevel; // rank level. e.g. 0 for ROOKIE WRECKER
  /* 0x0D */ u8 padD;
  /* 0x0E */ s16 padE;
  /* 0x10 */ s32 unk10; // TODO: unlocked vehicles? vehicles bitmask
  /* 0x14 */ s32 unk14;
  /* 0x18 */ u8 unk18[0x3C]; // flags? often check >0 and <6
  /* 0x54 */ u8 unk54[0x3C]; // this is a bitfield
  /* 0x90 */ u8 unk90;
  /* 0x91 */ u8 unk91;
  /* 0x92 */ u8 unk92[0xF0 - 0x92]; // indexed by level
  /* 0xF0 */ s32 unkF0;
  /* 0xF4 */ u8 padF4[0xFF - 0xF4];
} UnknownData8024C414;

extern u8 g_gamePaused;
extern u8 D_hd_code_802E8BD4;
extern u8 D_hd_code_802E8BD8;
extern s32 g_currentLevel;
extern u8 D_hd_code_802E8BE4;
extern s32 D_hd_code_802E8BE8;
extern s32 D_hd_code_802E8BEC;
extern u8 D_hd_code_802E8BF0;
extern u8 D_hd_code_802E8BF8;
extern u8 D_hd_code_802E8C44[];
extern OSMesgQueue D_hd_code_803150A0;
extern OSMesgQueue D_hd_code_803153D8;
extern OSSched sc; // 0x80315440
extern OSScClient g_gfxClient;
extern u8 D_hd_code_803156F4;
extern struct FrameContext D_hd_code_803156F8[2];
extern u32 D_hd_code_80358058;
extern u8 D_hd_code_8035805C;
extern u32 g_frameCount;
extern s32 D_hd_code_80358064;
extern u8* g_heap;
extern u16 D_hd_code_8035807C;
extern struct Shadows g_shadows;
extern u8 D_hd_code_803643D4;
extern u8 D_hd_code_803643D5;
extern u8 D_hd_code_803643D6;
extern u8 D_hd_code_803643D7;
extern u8 D_hd_code_803643D8;
extern u8 D_hd_code_803643D9;
extern u8 D_hd_code_803643DA;
extern u8 D_hd_code_803643DB;
extern s32 D_hd_code_803643E0;
extern s32 D_hd_code_803643E4;
extern s32 D_hd_code_803643E8;
extern s32 D_hd_code_803643F8;
extern s32 D_hd_code_803643FC;
extern s32 D_hd_code_80364400;
extern s32 D_hd_code_80364404;
extern s32 D_hd_code_80364408;
extern s32 D_hd_code_8036440C;
extern u8 D_hd_code_80364410;
extern f32 D_hd_code_80364414;
extern u8 D_hd_code_80364424;
extern u32 D_hd_code_80364428;
extern u16 D_hd_code_8036442C;
extern s32 D_hd_code_80364430;
extern f32 g_levelFOV;
extern s16 D_hd_code_8036443C;
extern s16 D_hd_code_8036443E;
extern s16 D_hd_code_80364452;
extern u8 g_currentVehicleType;
extern struct VehicleSlot g_vehicles[12];
extern struct VehicleSlot *g_vehiclesEnd;
extern s32 D_hd_code_803649E8;
extern u8 D_hd_code_803649ED;
extern s8 D_hd_code_80364A50;
extern s32 D_hd_code_80364A58;
extern u8 D_hd_code_80364A68;
extern u8 D_hd_code_80364A6A;
extern u8 D_hd_code_80364A6C;
extern u8 D_hd_code_80364A84;
extern u8 D_hd_code_80364A87;
extern u64 g_currentGameState;
extern u64 g_nextGameState;
extern u32 D_hd_code_80364AA8;
extern u8 playerNumber;
extern u8 g_playerNumberAtStart;
extern UnknownData8024C414 players[];
extern s32 nextdma; // 0x80358080
extern s32 no_palette_dmas; // 0x80358084
extern u64 D_hd_code_80364A88;
extern u16 *D_hd_code_80358050[2];

#define LEVEL_FINISHED(_lvl) ((players[playerNumber].unk18[_lvl] > 0 && players[playerNumber].unk18[_lvl] < 6)?1:0)

#endif
