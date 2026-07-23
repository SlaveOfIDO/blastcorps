#include "asm_helper.h"

.set noat
.set noreorder

.text

.globl bcopy
bcopy:
    beqz       a2, ret
     or        a3, a1, zero
    beq        a0, a1, ret
     slt       $at, a1, a0
    bnel       $at, zero, goforwards
     slti      $at, a2, 0x10
    add        v0, a0, a2
    slt        $at, a1, v0
    beql       $at, zero, goforwards
     slti      $at, a2, 0x10
    b          .Lhd_code_802E24D8
     slti      $at, a2, 0x10
    slti       $at, a2, 0x10
goforwards:
    bnez       $at, forwards_bytecopy
     nop
    andi       v0, a0, 0x3
    andi       v1, a1, 0x3
    beq        v0, v1, .Lhd_code_802E23B4
     nop
forwards_bytecopy:
    beqz       a2, ret
     nop
    addu       v1, a0, a2
.Lhd_code_802E2398:
    lb         v0, 0x0(a0)
    addiu      a0, a0, 0x1
    addiu      a1, a1, 0x1
    bne        a0, v1, .Lhd_code_802E2398
     sb        v0, -0x1(a1)
ret:
    jr         ra
     or        v0, a3, zero
.Lhd_code_802E23B4:
    beqz       v0, .Lhd_code_802E2418
     addiu     $at, zero, 0x1
    beq        v0, $at, .Lhd_code_802E23FC
     addiu     $at, zero, 0x2
    beql       v0, $at, .Lhd_code_802E23E8
     lh        v0, 0x0(a0)
    lb         v0, 0x0(a0)
    addiu      a0, a0, 0x1
    addiu      a1, a1, 0x1
    addiu      a2, a2, -0x1
    b          .Lhd_code_802E2418
     sb        v0, -0x1(a1)
    lh         v0, 0x0(a0)
.Lhd_code_802E23E8:
    addiu      a0, a0, 0x2
    addiu      a1, a1, 0x2
    addiu      a2, a2, -0x2
    b          .Lhd_code_802E2418
     sh        v0, -0x2(a1)
.Lhd_code_802E23FC:
    lb         v0, 0x0(a0)
    lh         v1, 0x1(a0)
    addiu      a0, a0, 0x3
    addiu      a1, a1, 0x3
    addiu      a2, a2, -0x3
    sb         v0, -0x3(a1)
    sh         v1, -0x2(a1)
.Lhd_code_802E2418:
    slti       $at, a2, 0x20
    bnel       $at, zero, .Lhd_code_802E2478
     slti      $at, a2, 0x10
    lw         v0, 0x0(a0)
    lw         v1, 0x4(a0)
    lw         t0, 0x8(a0)
    lw         t1, 0xC(a0)
    lw         t2, 0x10(a0)
    lw         t3, 0x14(a0)
    lw         t4, 0x18(a0)
    lw         t5, 0x1C(a0)
    addiu      a0, a0, 0x20
    addiu      a1, a1, 0x20
    addiu      a2, a2, -0x20
    sw         v0, -0x20(a1)
    sw         v1, -0x1C(a1)
    sw         t0, -0x18(a1)
    sw         t1, -0x14(a1)
    sw         t2, -0x10(a1)
    sw         t3, -0xC(a1)
    sw         t4, -0x8(a1)
    b          .Lhd_code_802E2418
     sw        t5, -0x4(a1)
.Lhd_code_802E2474:
    slti       $at, a2, 0x10
.Lhd_code_802E2478:
    bnel       $at, zero, .Lhd_code_802E24B4
     slti      $at, a2, 0x4
    lw         v0, 0x0(a0)
    lw         v1, 0x4(a0)
    lw         t0, 0x8(a0)
    lw         t1, 0xC(a0)
    addiu      a0, a0, 0x10
    addiu      a1, a1, 0x10
    addiu      a2, a2, -0x10
    sw         v0, -0x10(a1)
    sw         v1, -0xC(a1)
    sw         t0, -0x8(a1)
    b          .Lhd_code_802E2474
     sw        t1, -0x4(a1)
.Lhd_code_802E24B0:
    slti       $at, a2, 0x4
.Lhd_code_802E24B4:
    bnez       $at, forwards_bytecopy
     nop
    lw         v0, 0x0(a0)
    addiu      a0, a0, 0x4
    addiu      a1, a1, 0x4
    addiu      a2, a2, -0x4
    b          .Lhd_code_802E24B0
     sw        v0, -0x4(a1)
    slti       $at, a2, 0x10
.Lhd_code_802E24D8:
    add        a0, a0, a2
    bnez       $at, .Lhd_code_802E24F4
     add       a1, a1, a2
    andi       v0, a0, 0x3
    andi       v1, a1, 0x3
    beq        v0, v1, .Lhd_code_802E2524
     nop
.Lhd_code_802E24F4:
    beqz       a2, ret
     nop
    addiu      a0, a0, -0x1
    addiu      a1, a1, -0x1
    subu       v1, a0, a2
.Lhd_code_802E2508:
    lb         v0, 0x0(a0)
    addiu      a0, a0, -0x1
    addiu      a1, a1, -0x1
    bne        a0, v1, .Lhd_code_802E2508
     sb        v0, 0x1(a1)
    jr         ra
     or        v0, a3, zero
.Lhd_code_802E2524:
    beqz       v0, .Lhd_code_802E2588
     addiu     $at, zero, 0x3
    beq        v0, $at, .Lhd_code_802E256C
     addiu     $at, zero, 0x2
    beql       v0, $at, .Lhd_code_802E2558
     lh        v0, -0x2(a0)
    lb         v0, -0x1(a0)
    addiu      a0, a0, -0x1
    addiu      a1, a1, -0x1
    addiu      a2, a2, -0x1
    b          .Lhd_code_802E2588
     sb        v0, 0x0(a1)
    lh         v0, -0x2(a0)
.Lhd_code_802E2558:
    addiu      a0, a0, -0x2
    addiu      a1, a1, -0x2
    addiu      a2, a2, -0x2
    b          .Lhd_code_802E2588
     sh        v0, 0x0(a1)
.Lhd_code_802E256C:
    lb         v0, -0x1(a0)
    lh         v1, -0x3(a0)
    addiu      a0, a0, -0x3
    addiu      a1, a1, -0x3
    addiu      a2, a2, -0x3
    sb         v0, 0x2(a1)
    sh         v1, 0x0(a1)
.Lhd_code_802E2588:
    slti       $at, a2, 0x20
    bnel       $at, zero, .Lhd_code_802E25E8
     slti      $at, a2, 0x10
    lw         v0, -0x4(a0)
    lw         v1, -0x8(a0)
    lw         t0, -0xC(a0)
    lw         t1, -0x10(a0)
    lw         t2, -0x14(a0)
    lw         t3, -0x18(a0)
    lw         t4, -0x1C(a0)
    lw         t5, -0x20(a0)
    addiu      a0, a0, -0x20
    addiu      a1, a1, -0x20
    addiu      a2, a2, -0x20
    sw         v0, 0x1C(a1)
    sw         v1, 0x18(a1)
    sw         t0, 0x14(a1)
    sw         t1, 0x10(a1)
    sw         t2, 0xC(a1)
    sw         t3, 0x8(a1)
    sw         t4, 0x4(a1)
    b          .Lhd_code_802E2588
     sw        t5, 0x0(a1)
.Lhd_code_802E25E4:
    slti       $at, a2, 0x10
.Lhd_code_802E25E8:
    bnel       $at, zero, .Lhd_code_802E2624
     slti      $at, a2, 0x4
    lw         v0, -0x4(a0)
    lw         v1, -0x8(a0)
    lw         t0, -0xC(a0)
    lw         t1, -0x10(a0)
    addiu      a0, a0, -0x10
    addiu      a1, a1, -0x10
    addiu      a2, a2, -0x10
    sw         v0, 0xC(a1)
    sw         v1, 0x8(a1)
    sw         t0, 0x4(a1)
    b          .Lhd_code_802E25E4
     sw        t1, 0x0(a1)
.Lhd_code_802E2620:
    slti       $at, a2, 0x4
.Lhd_code_802E2624:
    bnez       $at, .Lhd_code_802E24F4
     nop
    lw         v0, -0x4(a0)
    addiu      a0, a0, -0x4
    addiu      a1, a1, -0x4
    addiu      a2, a2, -0x4
    b          .Lhd_code_802E2620
     sw        v0, 0x0(a1)
