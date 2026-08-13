.include "macro.inc"

.set noat
.set noreorder
.set gp=64

.section .text, "ax"

glabel func_init_8021ED00
    /* 1000 8021ED00 3C088022 */  lui        $t0, %hi(D_init_802229E0)
    /* 1004 8021ED04 250829E0 */  addiu      $t0, $t0, %lo(D_init_802229E0)
    /* 1008 8021ED08 240923A0 */  addiu      $t1, $zero, 0x23A0
  .Linit_8021ED0C:
    /* 100C 8021ED0C 2129FFF8 */  addi       $t1, $t1, -0x8
    /* 1010 8021ED10 AD000000 */  sw         $zero, 0x0($t0)
    /* 1014 8021ED14 AD000004 */  sw         $zero, 0x4($t0)
    /* 1018 8021ED18 1520FFFC */  bnez       $t1, .Linit_8021ED0C
    /* 101C 8021ED1C 21080008 */   addi      $t0, $t0, 0x8
    /* 1020 8021ED20 3C0A8022 */  lui        $t2, %hi(func_init_80220730)
    /* 1024 8021ED24 3C1D8022 */  lui        $sp, %hi(D_init_80224A30)
    /* 1028 8021ED28 254A0730 */  addiu      $t2, $t2, %lo(func_init_80220730)
    /* 102C 8021ED2C 01400008 */  jr         $t2
    /* 1030 8021ED30 27BD4A30 */   addiu     $sp, $sp, %lo(D_init_80224A30)
endlabel func_init_8021ED00
    /* 1034 8021ED34 00000000 */  nop
    /* 1038 8021ED38 00000000 */  nop
    /* 103C 8021ED3C 00000000 */  nop
    /* 1040 8021ED40 00000000 */  nop
    /* 1044 8021ED44 00000000 */  nop
    /* 1048 8021ED48 00000000 */  nop
    /* 104C 8021ED4C 00000000 */  nop
