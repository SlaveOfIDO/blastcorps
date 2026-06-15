#include "common.h"
#include "functions.h"
#include "variables.h"

// Proposed file name: kiunzip.c (after the "kiunzip:" debug message)
//
// This file is the gzip decompression front-end: it parses the gzip header
// and sets up the state for the DEFLATE decoder (func_hd_code_802994F8,
// in another file). Most game assets are stored gzip-compressed in ROM.

// BSS Begin
u8* D_hd_code_803669C0; // compressed input data pointer; proposed name: gzInput
u8* D_hd_code_803669C4; // decompressed output pointer; proposed name: gzOutput
s32 pad_803669C8;
s32 D_hd_code_803669CC; // offset recorded past the header (+8); proposed name: gzDataStart
s32 pad_803669D0;
s32 pad_803669D4;
s32 D_hd_code_803669D8; // inflate bit buffer; proposed name: gzBitBuf
s32 D_hd_code_803669DC; // inflate bit count; proposed name: gzBitCount
s32 pad_803669E0;
s32 pad_803669E4;
s32 D_hd_code_803669E8;
s32 D_hd_code_803669EC; // input read offset; proposed name: gzReadOfs
u32 D_hd_code_803669F0; // output write offset; proposed name: gzWriteOfs
// BSS End

// Decompress a gzip stream: *arg0 = source, *arg1 = destination, arg2 = a
// mode passed through to the decoder. Parses the header, runs the DEFLATE
// decoder, then advances *arg0 by the bytes consumed and *arg1 by the bytes
// written.
// Proposed name: DecompressGzip
void func_hd_code_8025C230(s32* arg0, s32* arg1, s32 arg2) {
  D_hd_code_803669C0 = *arg0;
  D_hd_code_803669C4 = *arg1;
  D_hd_code_8039CAE0 = arg2;
  func_hd_code_8025C5A0();
  if (D_hd_code_803669C0[D_hd_code_803669EC] != 0x1F) {
    D_hd_code_803669EC += 1;
  }
  D_hd_code_802E8CC0 = func_hd_code_8025C30C();
  if (D_hd_code_802E8CC0 >= 0) {
    inflate();
    *arg0 += D_hd_code_803669EC;
    *arg1 += D_hd_code_803669F0;
  }
}

// Parse the gzip header: check the DEFLATE method byte, then skip the
// optional extra/name/comment fields per the flags. Returns the method or
// -1 on error.
// Proposed name: ParseGzipHeader
s32 func_hd_code_8025C30C(void) {
  u8 flags;
  s32 sp28;

  D_hd_code_803669EC += 2; // Skip gzip magic number 0x1F 0x8B
  D_hd_code_802E8CC0 = -1;
  D_hd_code_803669CC = 0;
  D_hd_code_802E8CC0 = D_hd_code_803669C0[D_hd_code_803669EC++];

  if (D_hd_code_802E8CC0 != 8) { // Compression mode != DEFLATE?
    rmonPrintf("kiunzip: unknown method %d -- get newer version of gzip\n", D_hd_code_802E8CC0);
    D_hd_code_802E8CC4 = 1;
    return -1;
  }

  flags = D_hd_code_803669C0[D_hd_code_803669EC++];
  D_hd_code_803669EC+=6;

  if (flags & 2) {
    D_hd_code_803669EC += 2;
  }
  if (flags & 4) {
    // read length of additional information
    sp28 = (D_hd_code_803669C0[D_hd_code_803669EC++]);
    sp28 |= (D_hd_code_803669C0[D_hd_code_803669EC++] << 8);

    // skip additional information
    D_hd_code_803669EC += sp28;
  }

  if (flags & 8) { // has original filename?
    while(D_hd_code_803669C0[D_hd_code_803669EC++] != 0); // skip filename
  }

  if (flags & 16) { // has additional comment?
    while(D_hd_code_803669C0[D_hd_code_803669EC++] != 0); // skip comment
  }
  // Skip crc32 checksum (4 byte) and size of original file (4 byte)
  D_hd_code_803669CC = D_hd_code_803669EC + 8;
  return D_hd_code_802E8CC0;
}

// Reverse the low arg1 bits of arg0 (Huffman code bit reversal)
// Proposed name: ReverseBits
u32 func_hd_code_8025C56C(u32 arg0, s32 arg1) {
  register u32 v1 = 0;
  do {
    v1 |= (arg0 & 1);
  } while (arg0 >>= 1, v1 <<= 1, --arg1 > 0);
  return v1 >> 1;
}

// Reset the decompressor state (offsets and bit buffer)
// Proposed name: ResetInflateState
void func_hd_code_8025C5A0(void) {
  D_hd_code_803669F0 = 0;
  D_hd_code_803669EC = 0;
  D_hd_code_803669E8 = 0;
  D_hd_code_803669DC = 0;
  D_hd_code_803669D8 = 0;
}

