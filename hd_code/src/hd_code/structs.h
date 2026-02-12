#ifndef __STRUCTS_H
#define __STRUCTS_H

#include <PR/gbi.h>


// Perhaps some kind of Scene struct?
typedef struct UnknownData8024C414_s {
  /* 0x00 */ struct UnknownData8024C414_s* unk0; // parent?
  /* 0x04 */ u32 pad1;
  /* 0x08 */ u8 unk8;
  /* 0x09 */ u8 unk9;
  /* 0x0A */ u16 unkA;
  /* 0x0C */ u32 pad2;
  /* 0x10 */ s32 unk10;
  /* 0x14 */ s32 pad3;
  /* 0x18 */ u8 unk18[0x4A - 0x18]; // flags? often check >0 and <6
  /* 0x4A */ u8 unk4A;
  /* 0x4B */ u8 pad4B[0x91 - 0x4B]; // -1 byte alignment
  /* 0x91 */ u8 unk91;
  /* 0x92 */ u8 pad92[0xF0 - 0x92];
  /* 0xF0 */ s32 unkF0;
  /* 0xF4 */ u8 padF4[0xFF - 0xF4];
} UnknownData8024C414;

struct S_802F8BDC {
  /* 0x00 */ s32 unk0;  // maybe u16
  /* 0x04 */ s16 unk4; // safe type
  /* 0x06 */ u16 unk6;
  /* 0x08 */ s32 unk8;
  /* 0x0C */ s16 unkC;
  /* 0x0E */ u16 unkE; // safe type
  /* 0x10 */ u16 unk10; // safe type
  /* 0x12 */ s16 unk12;
  /* 0x14 */ s32 unk14;
  /* 0x18 */ u16 unk18; // safe type
  /* 0x1A */ s16 unk1A;

}; // size: 0x1C / 28

#define TOPLEVEL_DL_SIZE (0xB5E)

struct Model1 {
  // size: 0x21498
  /* 0x00000 */ u32 unk00000;
  /* 0x00004 */ u8 unk00004[0x80 - 0x4];
  /* 0x00080 */ Mtx projection;
  /* 0x000C0 */ Mtx mtx1;
  /* 0x00100 */ Mtx mtx2;
  /* 0x00140 */ Mtx projection2;
  /* 0x00180 */ void* unk180;
  /* 0x00184 */ u8 pad184[0x001C0 - 0x00184];
  /* 0x001C0 */ Mtx modelview;
  /* 0x00200 */ Mtx unk200;
  /* 0x00240 */ Mtx unk240;
  /* 0x00280 */ Mtx unk280;
  /* 0x002C0 */ Mtx unk2C0[(0xE00 - 0x2C0) / 0x40]; // length could be smaller
  /* 0x00E00 */ s32 unkE00;
  /* 0x00E04 */ u8 pad[0x11C0 - 0xE04];
  /* 0x011C0 */ s32 unk11C0;
  /* 0x011C4 */ u8 pad11C4[0x1500 - 0x11C4];
  /* 0x01500 */ Mtx unk1500; // another modelview
  /* 0x01540 */ Mtx unk1540; // another modelview
  /* 0x01580 */ Vtx unk1580[(0x18C0 - 0x1580)/0x10]; // length could be smaller, possibly only 0x4?
  /* 0x018C0 */ Vtx unk18C0[4];
  /* 0x01900 */ Vtx unk1900[(0x38C0 - 0x1900)/0x10];
  /* 0x038C0 */ Vtx unk38C0[0x40 / 0x10];
  /* 0x03900 */ Vtx unk3900[(0x03C00 - 0x03900)/0x10];
  /* 0x03C00 */ LookAt lookAt;
  /* 0x03C20 */ u8 pad3C20[0x48B0 - 0x3C20];
  /* 0x048B0 */ Gfx dp[0xA3A0 / 8 - 0x48B0 / 8];
  /* 0x0A3A0 */ s32 unkA3A0;
  /* 0x0A3A4 */ u8 padA3A4[0x0A4E0 - 0x0A3A4];
  /* 0x0A4E0 */ s32 unkA4E0;
  /* 0x0A4E4 */ u8 padA4E4[0x0A580 - 0x0A4E4];
  /* 0x0A580 */ s32 unkA580;
  /* 0x0A584 */ u8 padA584[0x0A918 - 0x0A584];
  /* 0x0A918 */ s32 unkA918;
  /* 0x0A91C */ u8 padA91C[0x0ACB0 - 0x0A91C];
  /* 0x0ACB0 */ s32 unkACB0;
  /* 0x0ACB4 */ u8 padACB4[0x1B650 - 0x0ACB4];
  /* 0x1B650 */ s32 unk1B650;
  /* 0x1B654 */ u8 pad1B654[0x21410 - 0x1B654];
  /* 0x21410 */ s32 unk21410;
  /* 0x21414 */ u8 pad21414[0x21478 - 0x21414];
  /* 0x21478 */ s32 unk21478;
  /* 0x2147C */ u8 pad2147C[0x21498 - 0x2147C];
};


struct S_802F5804 {
  u16 unk0;  // maybe u16
  u16 unk2;
  s32 unk4;
  s32 unk8;
  u8* unkC;
  void* unk10;  // some kind of address
  s32 unk14;
  u8 unk18; // safe type
  u8 pad19;
  u8 pad1A;
  u8 pad1B;
}; // size: 0x1C / 28

struct Texture {
  u8 data[0x1000];
  f32 unk1000;
  s32 unk1004;
  s32 unk1008;
  s32 unk100C;
  s32 unk1010;
  s32 unk1014;
  s16 unk1018;
  s16 unk101A;
  s16 unk101C;
  s16 unk101E;
  s16 unk1020;
  u8 unk1022;
  u8 unk1023; // can only be 0,1,2
  u8 pad2[0x1040-0x1024];
  // size: 0x1040
};

struct Textures {
  struct Texture *textures;
  struct Texture *end; // D_803643CC
};




struct UnknownStruct_803644BC {
  // size: 0x74
  /* 0x00 */ s32 unk0;
  /* 0x04 */ s32 unk4; // D_80364464
  /* 0x08 */ s32 unk8; // D_80364468
  /* 0x0C */ s32 unkC; // D_8036446C
  /* 0x10 */ s32 unk10; // D_80364470
  /* 0x14 */ s32 unk14; // D_80364474
  /* 0x18 */ s32 unused18; // D_80364478
  /* 0x1C */ s32 unused1C; // D_8036447C
  /* 0x20 */ s32 unused20; // D_80364480
  /* 0x24 */ s32 unused24; // D_80364484
  /* 0x28 */ s32 unused28; // D_80364488
  /* 0x2C */ s32 unused2C; // D_8036448C
  /* 0x30 */ s32 unk30; // D_80364490
  /* 0x34 */ s32 unk34; // D_80364494
  /* 0x38 */ s32 unk38; // D_80364498
  /* 0x3C */ s32 unused3C; // D_8036449C
  /* 0x40 */ u8 pad40[0x54 - 0x40];
  /* 0x54 */ s32 unk54;
  /* 0x58 */ s32 pad58;
  /* 0x5C */ s32 unk5C; // Texture Index?
  /* 0x60 */ s32 unk60; // Some kind of env color?
  /* 0x64 */ s32 pad64;
  /* 0x68 */ s32 pad68;
  /* 0x6C */ s32 pad6C;
  /* 0x70 */ s32 unk70;
};

// size: 0x4
struct UnknownStruct8030F668 {
  /* 0x01 */ u8 flag1;
  /* 0x02 */ u8 flag2;
  /* 0x03 */ u8 flag3;
};

struct vec3 {
  f32 x;
  f32 y;
  f32 z;
};

struct vec3d {
  f64 x;
  f64 y;
  f64 z;
};

struct BoundingBox {
  struct vec3d min;
  struct vec3d max;
};

struct Struct802F8BF4 {
  u16 id; // Safe type
  char data[0x1A];
};

struct Struct8036BED8 {
  s16 x;
  s16 y;
  s16 z;
  char unk[0x82];
};

struct S_802E8FCA {
  u16 unk0;
  u8 pad[0x42];
};

struct S_803F4030 {
  /* 0x00 */ s32 unk0;
  /* 0x04 */ u8 pad4[0x10 - 0x04];
  /* 0x10 */ s32 unk10;
  /* 0x14 */ s32 unk14;
  /* 0x18 */ s32 unk18;
  /* 0x1C */ u8 pad1C[0x30 - 0x1C];
  /* 0x30 */ u32 unk30;
  /* 0x34 */ u8 pad34[0x44 - 0x34];
  /* 0x44 */ u32 unk44;
  /* 0x48 */ u8 pad48[0xEA - 0x48];
  /* 0xEA */ u8 unkEA;
  /* 0xEC */ u8 padEC[0xFC - 0xEC];
};

typedef struct {
  s32 unk0;
  s16 unk4;
  s16 unk6;
  u8 unk8;
  u8 unk9;
  s16 pad;
} UnknownStruct_80364A00;


struct S_802F8BE4 {
  u32 unk0;
  u8 pad4[0x1C - 0x04];
};

struct S_803669AC {
  /* 0x00 */ u8 unk0;
  /* 0x01 */ u8 unk1;
  /* 0x02 */ u8 unk2;
  /* 0x03 */ s8 unk3;
  /* 0x04 */ s8 unk4;
};

struct S_80366BC4 {
  u8 unk0;
  u8 unk1;
};
struct S_802FA8B0 {
  Vtx v[4];
};


struct S_8020C070 {
  /* 0x00 */ u16 unk0;
  /* 0x02 */ u16 unk2;
  /* 0x04 */ u16 unk4;
  /* 0x06 */ u16 unk6;
  /* 0x08 */ u16 unk8;
  /* 0x0A */ char* unkA; // e.g. "QUIT GAME!"
  /* 0x0E */ s32* unkE;
  /* 0x10 */ s32* unk10;
  /* 0x14 */ u32 unk14;
  ///* 0x18 */ u8 unk18;
}; // Size unsure

struct S_80365340 {
  u16 unk0;
  u16 unk2;
  s32 unk4;
  s32 unk8;
};

struct S_80366BC0 {
  u8 unk0;
  u8 pad1;
  u16 unk2;
};



struct S_80367C04
{
  u8 unk0;
  u8 pad1;
  u16 unk2;
  u16 unk4;
  u16 unk6;
  u16 unk8;
  u16 unkA;
  u16 unkC;
  u16 unkE;
  u16 unk10;
  u8 unk12[4];
  u8 pad16[2];
  u32 unk18;
  s16 unk1C;
  s16 unk1E;
  u32 pad20;
  s16 unk24;
  s16 unk26;
  s16 unk28;
  s16 unk2A;
  u8 pad2C[0x36 - 0x2C];
  u16 unk36;
  u8 unk38;
  u8 pad39;
  u8 pad3A;
  u8 pad3B;
  u32 unk3C;
  u16 unk40;
  u16 unk42;
};

struct S_80367BF8 {
  u8 unk0;
  u8 unk1;
};

struct S_80367D52
{
  u8 unk0;
  u8 unk1;
};

struct S_802E8F74 {
  u8 unk0;
  u8 pad1;
  s16 unk2;
  s16 unk4;
  s16 unk6;
};

struct S_80367BCC {
  s32 pad0;
  u8 unk4;
  u8 pad5;
  char unk6[0x1A - 0x6];
  u8 unk1A;
  u8 unk1B[0x26 - 0x1B];
  u8 unk26;
  u8 pad27;
  float unk28;
  u8 unk2C;
  u8 unk2D;
  u8 pad2E;
  u8 pad2F;
};

struct S_802E8F68 {
  u8 unk0;
  u8 pad1;
  s16 unk2;
  s16 unk4;
  s16 unk6;
  s16 unk8;
};


struct S_80367518 {
  u8 unk0[0xF8];
};

struct S_802E8EB4 {
  u32 unk0[0x18 / 4];
};
struct S_80367400 {
  u32 unk0[0x1EC / 4];
  /* 0x1EC */ s32 unk1EC;
  /* 0x1F0 */ u8  unk1F0;
  u8 pad[3];
};

#endif
