.include "macro.inc"

.set noat
.set noreorder
.set gp=64

.text

glabel func_init_80220730
    addiu      $sp, $sp, -0x40
    jal        osInitialize
     or        $gp, $a0, $zero
    lui        $a1, %hi(D_787FD0)
    lui        $a3, %hi(D_7E3AD0)
    addiu      $a1, $a1, %lo(D_787FD0)
    lui        $a2, (0x80000400 >> 16)
    addiu      $a3, $a3, %lo(D_7E3AD0)
    addiu      $a0, $zero, 0x0
    ori        $a2, $a2, (0x80000400 & 0xFFFF)
    jal        osPiRawStartDma
     sub       $a3, $a3, $a1
1:
    jal        osPiGetStatus
     nop
    andi       $v0, $v0, 0x1
    bnez       $v0, 1b
     nop
    lui        $a0, (0x80000400 >> 16)
    lui        $a1, (0x802447C0 >> 16)
    lui        $a2, (0x801E7000 >> 16)
    ori        $a0, $a0, (0x80000400 & 0xFFFF)
    ori        $a1, $a1, (0x802447C0 & 0xFFFF)
    ori        $a2, $a2, (0x801E7000 & 0xFFFF)
    jal        func_init_80220998
     addiu     $a3, $zero, 0xD
    jal        func_init_80220998
     addiu     $a3, $zero, 0xA
    or         $a0, $a1, $zero
    lui        $a1, (0x80400000 >> 16)
    addiu      $a2, $zero, 0x4
1:
    sw         $zero, 0x0($a0)
    add        $a0, $a0, $a2
    bne        $a0, $a1, 1b
     nop
    lui        $a0, (0x803FFFF8 >> 16)
    lui        $a1, %hi(D_7E3AD0)
    ori        $a0, $a0, (0x803FFFF8 & 0xFFFF)
    addiu      $a1, $a1, %lo(D_7E3AD0)
    sw         $a1, 0x0($a0)
    lui        $a0, (0x803FFFFC >> 16)
    lui        $a1, %hi(D_7F9BE0)
    ori        $a0, $a0, (0x803FFFFC & 0xFFFF)
    addiu      $a1, $a1, %lo(D_7F9BE0)
    sw         $a1, 0x0($a0)
    addiu      $sp, $sp, -0xF8
    sd         $a0, 0x20($sp)
    lui        $a0, %hi(D_init_80222850)
    sd         $ra, 0x0($sp)
    addiu      $a0, $a0, %lo(D_init_80222850)
    sd         $at, 0x8($sp)
    sd         $v0, 0x10($sp)
    sd         $v1, 0x18($sp)
    sd         $a1, 0x28($sp)
    sd         $a2, 0x30($sp)
    sd         $a3, 0x38($sp)
    sd         $t0, 0x40($sp)
    sd         $t1, 0x48($sp)
    sd         $t2, 0x50($sp)
    sd         $t3, 0x58($sp)
    sd         $t4, 0x60($sp)
    sd         $t5, 0x68($sp)
    sd         $t6, 0x70($sp)
    sd         $t7, 0x78($sp)
    sd         $s0, 0x80($sp)
    sd         $s1, 0x88($sp)
    sd         $s2, 0x90($sp)
    sd         $s3, 0x98($sp)
    sd         $s4, 0xA0($sp)
    sd         $s5, 0xA8($sp)
    sd         $s6, 0xB0($sp)
    sd         $s7, 0xB8($sp)
    sd         $t8, 0xC0($sp)
    sd         $t9, 0xC8($sp)
    sd         $k0, 0xD0($sp)
    sd         $k1, 0xD8($sp)
    sd         $gp, 0xE0($sp)
    sd         $sp, 0xE8($sp)
    jal        osSyncPrintf
     sd        $fp, 0xF0($sp)
    ld         $gp, 0xE0($sp)
    ld         $ra, 0x0($sp)
    ld         $at, 0x8($sp)
    ld         $v0, 0x10($sp)
    ld         $v1, 0x18($sp)
    ld         $a0, 0x20($sp)
    ld         $a1, 0x28($sp)
    ld         $a2, 0x30($sp)
    ld         $a3, 0x38($sp)
    ld         $t0, 0x40($sp)
    ld         $t1, 0x48($sp)
    ld         $t2, 0x50($sp)
    ld         $t3, 0x58($sp)
    ld         $t4, 0x60($sp)
    ld         $t5, 0x68($sp)
    ld         $t6, 0x70($sp)
    ld         $t7, 0x78($sp)
    ld         $s0, 0x80($sp)
    ld         $s1, 0x88($sp)
    ld         $s2, 0x90($sp)
    ld         $s3, 0x98($sp)
    ld         $s4, 0xA0($sp)
    ld         $s5, 0xA8($sp)
    ld         $s6, 0xB0($sp)
    ld         $s7, 0xB8($sp)
    ld         $t8, 0xC0($sp)
    ld         $t9, 0xC8($sp)
    ld         $k0, 0xD0($sp)
    ld         $k1, 0xD8($sp)
    ld         $sp, 0xE8($sp)
    or         $a0, $gp, $zero
    ld         $fp, 0xF0($sp)
    addiu      $sp, $sp, 0xF8
    j          func_802447C0
     addi      $sp, $sp, 0x40
endlabel func_init_80220730
    nop
    nop

glabel func_init_80220900
    addiu      $sp, $sp, -0x58
    sd         $ra, 0x0($sp)
    sd         $s0, 0x8($sp)
    sd         $s1, 0x10($sp)
    sd         $s2, 0x18($sp)
    sd         $s3, 0x20($sp)
    sd         $s4, 0x28($sp)
    sd         $s5, 0x30($sp)
    sd         $s6, 0x38($sp)
    sd         $s7, 0x40($sp)
    sd         $gp, 0x48($sp)
    sd         $fp, 0x50($sp)
    addiu      $sp, $sp, -0x18
    sd         $ra, 0x0($sp)
    sd         $a0, 0x8($sp)
    sd         $a1, 0x10($sp)
    lw         $a0, 0x0($a0)
    jal        func_init_80220A50
     lw        $a1, 0x0($a1)
    ld         $t6, 0x8($sp)
    ld         $t7, 0x10($sp)
    ld         $ra, 0x0($sp)
    sw         $a0, 0x0($t6)
    addiu      $sp, $sp, 0x18
    sw         $a1, 0x0($t7)
    ld         $ra, 0x0($sp)
    ld         $fp, 0x50($sp)
    ld         $gp, 0x48($sp)
    ld         $s7, 0x40($sp)
    ld         $s6, 0x38($sp)
    ld         $s5, 0x30($sp)
    ld         $s4, 0x28($sp)
    ld         $s3, 0x20($sp)
    ld         $s2, 0x18($sp)
    ld         $s1, 0x10($sp)
    ld         $s0, 0x8($sp)
    jr         $ra
     addiu     $sp, $sp, 0x58
endlabel func_init_80220900

glabel func_init_80220998
    addiu      $sp, $sp, -0x58
    lui        $at, %hi(D_init_80224A30)
    sd         $ra, 0x0($sp)
    sd         $s0, 0x8($sp)
    sd         $s1, 0x10($sp)
    sd         $s2, 0x18($sp)
    sd         $s3, 0x20($sp)
    sd         $s4, 0x28($sp)
    sd         $s5, 0x30($sp)
    sd         $s6, 0x38($sp)
    sd         $s7, 0x40($sp)
    sd         $gp, 0x48($sp)
    sd         $fp, 0x50($sp)
    sw         $a0, %lo(D_init_80224A30)($at)
    addi       $sp, $sp, -0x80
    lui        $at, %hi(D_init_80224A34)
    sw         $a1, %lo(D_init_80224A34)($at)
    addiu      $sp, $sp, -0x10
    lui        $a0, %hi(D_init_80224A30)
    lui        $a1, %hi(D_init_80224A34)
    sd         $ra, 0x0($sp)
    addiu      $a0, $a0, %lo(D_init_80224A30)
    addiu      $a1, $a1, %lo(D_init_80224A34)
    jal        func_init_80220360
     sd        $a2, 0x8($sp)
    ld         $ra, 0x0($sp)
    ld         $a2, 0x8($sp)
    lui        $a0, %hi(D_init_80224A30)
    lui        $a1, %hi(D_init_80224A34)
    addiu      $sp, $sp, 0x10
    lw         $a0, %lo(D_init_80224A30)($a0)
    lw         $a1, %lo(D_init_80224A34)($a1)
    addi       $sp, $sp, 0x80
    ld         $ra, 0x0($sp)
    ld         $s0, 0x8($sp)
    ld         $s1, 0x10($sp)
    ld         $s2, 0x18($sp)
    ld         $s3, 0x20($sp)
    ld         $s4, 0x28($sp)
    ld         $s5, 0x30($sp)
    ld         $s6, 0x38($sp)
    ld         $s7, 0x40($sp)
    ld         $gp, 0x48($sp)
    ld         $fp, 0x50($sp)
    jr         $ra
     addiu     $sp, $sp, 0x58
endlabel func_init_80220998

glabel func_init_80220A50
    addiu      $s5, $zero, 0x1
    addiu      $t6, $zero, 0xF
    subu       $t6, $t6, $a3
    sllv       $s0, $s5, $a3
    addiu      $sp, $sp, -0x8
    addiu      $s4, $zero, 0x80
    subu       $a3, $a3, $s5
    sd         $ra, 0x0($sp)
    addiu      $s6, $zero, 0x2
    or         $t3, $zero, $zero
    or         $t4, $s4, $zero
    or         $t1, $s5, $zero
    sllv       $t6, $s5, $t6
    subu       $s0, $s0, $s5
    sllv       $t5, $s5, $a3
  .Linit_80220A8C:
    bne        $t4, $s4, .Linit_80220A9C
     nop
    lbu        $t3, 0x0($a0)
    addu       $a0, $a0, $s5
  .Linit_80220A9C:
    and        $s7, $t3, $t4
    srlv       $t4, $t4, $s5
    bnez       $t4, .Linit_80220AB0
     nop
    or         $t4, $s4, $zero
  .Linit_80220AB0:
    beqz       $s7, .Linit_80220ADC
     nop
    jal        func_init_80220B5C
     or        $a3, $s4, $zero
    addu       $s7, $a2, $t1
    sb         $v0, 0x0($a1)
    addu       $t1, $t1, $s5
    addu       $a1, $a1, $s5
    sb         $v0, 0x0($s7)
    b          .Linit_80220A8C
     and       $t1, $t1, $s0
  .Linit_80220ADC:
    jal        func_init_80220B5C
     or        $a3, $t5, $zero
    beqz       $v0, .Linit_80220B3C
     nop
    or         $t0, $v0, $zero
    jal        func_init_80220B5C
     or        $a3, $t6, $zero
    addu       $t9, $v0, $s6
    or         $s7, $zero, $zero
  .Linit_80220B00:
    addu       $t8, $t0, $s7
    and        $t8, $t8, $s0
    addu       $t8, $a2, $t8
    lbu        $t8, 0x0($t8)
    addu       $t2, $a2, $t1
    addu       $s7, $s7, $s5
    addu       $t1, $t1, $s5
    slt        $at, $t9, $s7
    sb         $t8, 0x0($a1)
    addu       $a1, $a1, $s5
    and        $t1, $t1, $s0
    beqz       $at, .Linit_80220B00
     sb        $t8, 0x0($t2)
    b          .Linit_80220A8C
     nop
  .Linit_80220B3C:
    and        $s7, $a0, $s5
    beqz       $s7, .Linit_80220B4C
     nop
    add        $a0, $a0, $s5
  .Linit_80220B4C:
    ld         $ra, 0x0($sp)
    addiu      $sp, $sp, 0x8
    jr         $ra
     nop
endlabel func_init_80220A50

glabel func_init_80220B5C
    or         $v0, $zero, $zero
  .Linit_80220B60:
    bne        $t4, $s4, .Linit_80220B70
     nop
    lbu        $t3, 0x0($a0)
    addu       $a0, $a0, $s5
  .Linit_80220B70:
    and        $s7, $t3, $t4
    beqz       $s7, .Linit_80220B80
     nop
    or         $v0, $v0, $a3
  .Linit_80220B80:
    srl        $t4, $t4, 1
    bnez       $t4, .Linit_80220B90
     srl       $a3, $a3, 1
    or         $t4, $s4, $zero
  .Linit_80220B90:
    bnez       $a3, .Linit_80220B60
     nop
    jr         $ra
     nop
endlabel func_init_80220B5C

.data

.align 2

dlabel D_init_80222850
    .asciz "got here 2\n"
.align 2
.align 2
    .asciz ""
.align 2
enddlabel D_init_80222850

.section .bss, "wa"

.align 2

dlabel D_init_80224A30
    .space 0x4
enddlabel D_init_80224A30

dlabel D_init_80224A34
    .space 0x4
enddlabel D_init_80224A34
