.include "macro.inc"

.set noat
.set noreorder
.set gp=64


.rdata

#define REDISPATCH 0x00
#define SW1 0x04
#define SW2 0x08
#define RCP 0x0c
#define CART 0x10
#define PRENMI 0x14
#define IP6_HDLR 0x18
#define IP7_HDLR 0x1c
#define COUNTER 0x20

__osIntOffTable:
    .byte REDISPATCH
    .byte PRENMI
    .byte IP6_HDLR
    .byte IP6_HDLR
    .byte IP7_HDLR
    .byte IP7_HDLR
    .byte IP7_HDLR
    .byte IP7_HDLR
    .byte COUNTER
    .byte COUNTER
    .byte COUNTER
    .byte COUNTER
    .byte COUNTER
    .byte COUNTER
    .byte COUNTER
    .byte COUNTER
    .byte REDISPATCH
    .byte SW1
    .byte SW2
    .byte SW2
    .byte RCP
    .byte RCP
    .byte RCP
    .byte RCP
    .byte CART
    .byte CART
    .byte CART
    .byte CART
    .byte CART
    .byte CART
    .byte CART
    .byte CART

__osIntTable:
    .word redispatch, sw1, sw2, rcp, cart, prenmi, panic, panic, counter

.data

__osHwIntTable:
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0

__os_Kdebug_Pkt:
    .word 0

__osRdb_Mesg:
    .word 0


.text

glabel __osExceptionPreamble
    la $k0, __osException
    jr $k0
    nop
endlabel __osExceptionPreamble

glabel __osException
   lui        $k0, %hi(__osThreadSave)
   addiu      $k0, $k0, %lo(__osThreadSave)
   sd         $at, 0x20($k0)
   mfc0       $k1, $12
   sw         $k1, 0x118($k0)
   addiu      $at, $zero, -0x4
   and        $k1, $k1, $at
   mtc0       $k1, $12
   sd         $t0, 0x58($k0)
   sd         $t1, 0x60($k0)
   sd         $t2, 0x68($k0)
   sw         $zero, 0x18($k0)
   mfc0       $t0, $13
   andi       $t1, $t0, 0x7C
   addiu      $t2, $zero, 0x0
   bne        $t1, $t2, .Linit_802210C0
   nop
   and        $t1, $k1, $t0
   andi       $t2, $t1, 0x4000
   beqz       $t2, .Linit_802210A4
   nop
   addiu      $t1, $zero, 0x1
   lui        $at, %hi(__os_Kdebug_Pkt)
   b        .Linit_80221104
   sw        $t1, %lo(__os_Kdebug_Pkt)($at)
.Linit_802210A4:
   andi       $t2, $t1, 0x2000
   beqz       $t2, .Linit_802210C0
   nop
   addiu      $t1, $zero, 0x1
   lui        $at, %hi(__osRdb_Mesg)
   b        .Linit_80221104
   sw        $t1, %lo(__osRdb_Mesg)($at)
.Linit_802210C0:
   lui        $at, %hi(__os_Kdebug_Pkt)
   sw         $zero, %lo(__os_Kdebug_Pkt)($at)
   lui        $at, %hi(__osRdb_Mesg)
   or         $t0, $k0, $zero
   sw         $zero, %lo(__osRdb_Mesg)($at)
   lui        $k0, %hi(__osRunningThread)
   lw         $k0, %lo(__osRunningThread)($k0)
   ld         $t1, 0x20($t0)
   sd         $t1, 0x20($k0)
   ld         $t1, 0x118($t0)
   sd         $t1, 0x118($k0)
   ld         $t1, 0x58($t0)
   sd         $t1, 0x58($k0)
   ld         $t1, 0x60($t0)
   sd         $t1, 0x60($k0)
   ld         $t1, 0x68($t0)
   sd         $t1, 0x68($k0)
.Linit_80221104:
   mflo       $t0
   sd         $t0, 0x108($k0)
   mfhi       $t0
   sd         $v0, 0x28($k0)
   sd         $v1, 0x30($k0)
   sd         $a0, 0x38($k0)
   sd         $a1, 0x40($k0)
   sd         $a2, 0x48($k0)
   sd         $a3, 0x50($k0)
   sd         $t3, 0x70($k0)
   sd         $t4, 0x78($k0)
   sd         $t5, 0x80($k0)
   sd         $t6, 0x88($k0)
   sd         $t7, 0x90($k0)
   sd         $s0, 0x98($k0)
   sd         $s1, 0xA0($k0)
   sd         $s2, 0xA8($k0)
   sd         $s3, 0xB0($k0)
   sd         $s4, 0xB8($k0)
   sd         $s5, 0xC0($k0)
   sd         $s6, 0xC8($k0)
   sd         $s7, 0xD0($k0)
   sd         $t8, 0xD8($k0)
   sd         $t9, 0xE0($k0)
   sd         $gp, 0xE8($k0)
   sd         $sp, 0xF0($k0)
   sd         $fp, 0xF8($k0)
   sd         $ra, 0x100($k0)
   sd         $t0, 0x110($k0)
   mfc0       $t0, $14
   sw         $t0, 0x11C($k0)
   lw         $t0, 0x18($k0)
   beqz       $t0, .Linit_802211D8
   nop
   cfc1       $t0, $31
   nop
   sw         $t0, 0x12C($k0)
   sdc1       $f0, 0x130($k0)
   sdc1       $f2, 0x138($k0)
   sdc1       $f4, 0x140($k0)
   sdc1       $f6, 0x148($k0)
   sdc1       $f8, 0x150($k0)
   sdc1       $f10, 0x158($k0)
   sdc1       $f12, 0x160($k0)
   sdc1       $f14, 0x168($k0)
   sdc1       $f16, 0x170($k0)
   sdc1       $f18, 0x178($k0)
   sdc1       $f20, 0x180($k0)
   sdc1       $f22, 0x188($k0)
   sdc1       $f24, 0x190($k0)
   sdc1       $f26, 0x198($k0)
   sdc1       $f28, 0x1A0($k0)
   sdc1       $f30, 0x1A8($k0)
.Linit_802211D8:
   mfc0       $t0, $13
   sw         $t0, 0x120($k0)
   lui        $t1, %hi(0xA430000C) /* MI_INTR_MASK_REG */
   lw         $t1, %lo(0xA430000C)($t1)
   sw         $t1, 0x128($k0)
   addiu      $t1, $zero, 0x2
   sh         $t1, 0x10($k0)
   lui        $t1, %hi(__os_Kdebug_Pkt)
   lw         $t1, %lo(__os_Kdebug_Pkt)($t1)
   beqz       $t1, .Linit_80221224
   nop
   lui        $t2, (0xC0000008 >> 16)
   sw         $zero, (0xC0000008 & 0xFFFF)($t2)
   lui        $a0, (0xC0000000 >> 16)
   addiu      $t2, $t2, %lo(0xC0000008) /* RDB_WRITE_INTR_REG */
   jal        kdebugserver
   lw        $a0, (0xC0000000 & 0xFFFF)($a0)
   b        .Linit_80221778
   nop
.Linit_80221224:
   lui        $t1, %hi(__osRdb_Mesg)
   lw         $t1, %lo(__osRdb_Mesg)($t1)
   beqz       $t1, .Linit_80221270
   nop
   lui        $t2, (0xC000000C >> 16)
   sw         $zero, (0xC000000C & 0xFFFF)($t2)
   lui        $t1, %hi(__osRdbSendMessage)
   lw         $t1, %lo(__osRdbSendMessage)($t1)
   addiu      $t2, $t2, %lo(0xC000000C) /* RDB_READ_INTR_REG */
   beqz       $t1, .Linit_80221258
   nop
   jal        send_mesg
   addiu     $a0, $zero, 0x78
.Linit_80221258:
   lui        $t1, %hi(__osRdbWriteOK)
   lw         $t1, %lo(__osRdbWriteOK)($t1)
   lui        $at, %hi(__osRdbWriteOK)
   addi       $t1, $t1, 0x1
   b        .Linit_80221778
   sw        $t1, %lo(__osRdbWriteOK)($at)
.Linit_80221270:
   andi       $t1, $t0, 0x7C
   addiu      $t2, $zero, 0x24
   beq        $t1, $t2, .Linit_802214F4
   nop
   addiu      $t2, $zero, 0x2C
   beq        $t1, $t2, .Linit_8022163C
   nop
   addiu      $t2, $zero, 0x0
   bne        $t1, $t2, panic
   nop
   and        $s0, $k1, $t0
.Linit_8022129C:
   andi       $t1, $s0, 0xFF00
   srl        $t2, $t1, 12
   bnez       $t2, .Linit_802212B4
   nop
   srl        $t2, $t1, 8
   addi       $t2, $t2, 0x10
.Linit_802212B4:
   lui        $at, %hi(__osIntOffTable)
   addu       $at, $at, $t2
   lbu        $t2, %lo(__osIntOffTable)($at)
   lui        $at, %hi(__osIntTable)
   addu       $at, $at, $t2
   lw         $t2, %lo(__osIntTable)($at)
   jr         $t2
   nop
counter:
   mfc0       $t1, $11
   mtc0       $t1, $11
   jal        send_mesg
   addiu     $a0, $zero, 0x18
   lui        $at, (0xFFFF7FFF >> 16)
   ori        $at, $at, (0xFFFF7FFF & 0xFFFF)
   b        .Linit_8022129C
   and       $s0, $s0, $at
cart:
   addiu      $t2, $zero, 0x4
   lui        $at, %hi(__osHwIntTable)
   addu       $at, $at, $t2
   lw         $t2, %lo(__osHwIntTable)($at)
   beqz       $t2, .Linit_80221314
   nop
   jalr       $t2
   nop
.Linit_80221314:
   jal        send_mesg
   addiu     $a0, $zero, 0x10
   addiu      $at, $zero, -0x801
   b        .Linit_8022129C
   and       $s0, $s0, $at
rcp:
   lui        $s1, %hi(0xA4300008) /* MI_INTR_REG */
   lw         $s1, %lo(0xA4300008)($s1)
   andi       $s1, $s1, 0x3F
   andi       $t1, $s1, 0x1
   beqz       $t1, .Linit_80221388
   nop
   lui        $t4, %hi(0xA4040010) /* SP_STATUS_REG */
   lw         $t4, %lo(0xA4040010)($t4)
   addiu      $t1, $zero, 0x8
   lui        $at, %hi(0xA4040010) /* SP_STATUS_REG */
   andi       $t4, $t4, 0x300
   andi       $s1, $s1, 0x3E
   beqz       $t4, .Linit_80221378
   sw        $t1, %lo(0xA4040010)($at)
   jal        send_mesg
   addiu     $a0, $zero, 0x20
   beqz       $s1, .Linit_8022144C
   nop
   b        .Linit_80221388
   nop
.Linit_80221378:
   jal        send_mesg
   addiu     $a0, $zero, 0x58
   beqz       $s1, .Linit_8022144C
   nop
.Linit_80221388:
   andi       $t1, $s1, 0x8
   beqz       $t1, .Linit_802213AC
   lui       $at, %hi(0xA4400010) /* VI_CURRENT_REG */
   andi       $s1, $s1, 0x37
   sw         $zero, %lo(0xA4400010)($at)
   jal        send_mesg
   addiu     $a0, $zero, 0x38
   beqz       $s1, .Linit_8022144C
   nop
.Linit_802213AC:
   andi       $t1, $s1, 0x4
   beqz       $t1, .Linit_802213D8
   nop
   addiu      $t1, $zero, 0x1
   lui        $at, %hi(0xA450000C) /* AI_STATUS_REG */
   andi       $s1, $s1, 0x3B
   sw         $t1, %lo(0xA450000C)($at)
   jal        send_mesg
   addiu     $a0, $zero, 0x30
   beqz       $s1, .Linit_8022144C
   nop
.Linit_802213D8:
   andi       $t1, $s1, 0x2
   beqz       $t1, .Linit_802213FC
   lui       $at, %hi(0xA4800018) /* SI_STATUS_REG */
   andi       $s1, $s1, 0x3D
   sw         $zero, %lo(0xA4800018)($at)
   jal        send_mesg
   addiu     $a0, $zero, 0x28
   beqz       $s1, .Linit_8022144C
   nop
.Linit_802213FC:
   andi       $t1, $s1, 0x10
   beqz       $t1, .Linit_80221428
   nop
   addiu      $t1, $zero, 0x2
   lui        $at, %hi(0xA4600010) /* PI_STATUS_REG */
   andi       $s1, $s1, 0x2F
   sw         $t1, %lo(0xA4600010)($at)
   jal        send_mesg
   addiu     $a0, $zero, 0x40
   beqz       $s1, .Linit_8022144C
   nop
.Linit_80221428:
   andi       $t1, $s1, 0x20
   beqz       $t1, .Linit_8022144C
   nop
   addiu      $t1, $zero, 0x800
   lui        $at, %hi(0xA4300000) /* MI_MODE_REG */
   andi       $s1, $s1, 0x1F
   sw         $t1, %lo(0xA4300000)($at)
   jal        send_mesg
   addiu     $a0, $zero, 0x48
.Linit_8022144C:
   addiu      $at, $zero, -0x401
   b        .Linit_8022129C
   and       $s0, $s0, $at
prenmi:
   lw         $k1, 0x118($k0)
   addiu      $at, $zero, -0x1001
   lui        $t1, %hi(__osShutdown)
   and        $k1, $k1, $at
   sw         $k1, 0x118($k0)
   addiu      $t1, $t1, %lo(__osShutdown)
   lw         $t2, 0x0($t1)
   beqz       $t2, .Linit_80221484
   addiu     $at, $zero, -0x1001
   b          redispatch
   and       $s0, $s0, $at
.Linit_80221484:
   addiu      $t2, $zero, 0x1
   sw         $t2, 0x0($t1)
   jal        send_mesg
   addiu     $a0, $zero, 0x70
   lui        $t2, %hi(__osRunQueue)
   lw         $t2, %lo(__osRunQueue)($t2)
   addiu      $at, $zero, -0x1001
   and        $s0, $s0, $at
   lw         $k1, 0x118($t2)
   and        $k1, $k1, $at
   b          redispatch
   sw        $k1, 0x118($t2)
sw2:
   addiu      $at, $zero, -0x201
   and        $t0, $t0, $at
   mtc0       $t0, $13
   jal        send_mesg
   addiu     $a0, $zero, 0x8
   addiu      $at, $zero, -0x201
   b        .Linit_8022129C
   and       $s0, $s0, $at
sw1:
   addiu      $at, $zero, -0x101
   and        $t0, $t0, $at
   mtc0       $t0, $13
   jal        send_mesg
   addiu     $a0, $zero, 0x0
   addiu      $at, $zero, -0x101
   b        .Linit_8022129C
   and       $s0, $s0, $at
.Linit_802214F4:
   addiu      $t1, $zero, 0x1
   sh         $t1, 0x12($k0)
   jal        send_mesg
   addiu     $a0, $zero, 0x50
   b          redispatch
   nop
redispatch:
   lui        $t2, %hi(__osRunQueue)
   lw         $t2, %lo(__osRunQueue)($t2)
   lw         $t1, 0x4($k0)
   lw         $t3, 0x4($t2)
   slt        $at, $t1, $t3
   beqz       $at, .Linit_80221540
   nop
   lui        $a0, %hi(__osRunQueue)
   or         $a1, $k0, $zero
   jal        __osEnqueueThread
   addiu     $a0, $a0, %lo(__osRunQueue)
   j          __osDispatchThread
   nop
.Linit_80221540:
   lui        $t1, %hi(__osRunQueue)
   addiu      $t1, $t1, %lo(__osRunQueue)
   lw         $t2, 0x0($t1)
   sw         $t2, 0x0($k0)
   j          __osDispatchThread
   sw        $k0, 0x0($t1)
panic:
   lui        $at, %hi(__osFaultedThread)
   sw         $k0, %lo(__osFaultedThread)($at)
   addiu      $t1, $zero, 0x1
   sh         $t1, 0x10($k0)
   addiu      $t1, $zero, 0x2
   sh         $t1, 0x12($k0)
   mfc0       $t2, $8
   sw         $t2, 0x124($k0)
   jal        send_mesg
   addiu     $a0, $zero, 0x60
   j          __osDispatchThread
   nop
endlabel __osException

glabel send_mesg
   lui        $t2, %hi(__osEventStateTab)
   addiu      $t2, $t2, %lo(__osEventStateTab)
   addu       $t2, $t2, $a0
   lw         $t1, 0x0($t2)
   or         $s2, $ra, $zero
   beqz       $t1, .Linit_80221634
   nop
   lw         $t3, 0x8($t1)
   lw         $t4, 0x10($t1)
   slt        $at, $t3, $t4
   beqz       $at, .Linit_80221634
   nop
   lw         $t5, 0xC($t1)
   addu       $t5, $t5, $t3
   div        $zero, $t5, $t4
   bnez       $t4, .Linit_802215D0
   nop
   break      7
.Linit_802215D0:
   addiu      $at, $zero, -0x1
   bne        $t4, $at, .Linit_802215E8
   lui       $at, (0x80000000 >> 16)
   bne        $t5, $at, .Linit_802215E8
   nop
   break      6
.Linit_802215E8:
   lw         $t4, 0x14($t1)
   mfhi       $t5
   sll        $t5, $t5, 2
   addu       $t4, $t4, $t5
   lw         $t5, 0x4($t2)
   addiu      $t2, $t3, 0x1
   sw         $t5, 0x0($t4)
   sw         $t2, 0x8($t1)
   lw         $t2, 0x0($t1)
   lw         $t3, 0x0($t2)
   beqz       $t3, .Linit_80221634
   nop
   jal        __osPopThread
   or        $a0, $t1, $zero
   or         $t2, $v0, $zero
   lui        $a0, %hi(__osRunQueue)
   or         $a1, $t2, $zero
   jal        __osEnqueueThread
   addiu     $a0, $a0, %lo(__osRunQueue)
.Linit_80221634:
   jr         $s2
   nop
.Linit_8022163C:
   lui        $at, (0x30000000 >> 16)
   and        $t1, $t0, $at
   srl        $t1, $t1, 28
   addiu      $t2, $zero, 0x1
   bne        $t1, $t2, panic
   nop
   lw         $k1, 0x118($k0)
   lui        $at, (0x20000000 >> 16)
   addiu      $t1, $zero, 0x1
   or         $k1, $k1, $at
   sw         $t1, 0x18($k0)
   b        .Linit_80221540
   sw        $k1, 0x118($k0)

.globl __osEnqueueAndYield
.type __osEnqueueAndYield, @function
__osEnqueueAndYield:
   lui        $a1, %hi(__osRunningThread)
   lw         $a1, %lo(__osRunningThread)($a1)
   mfc0       $t0, $12
   lw         $k1, 0x18($a1)
   ori        $t0, $t0, 0x2
   sw         $t0, 0x118($a1)
   sd         $s0, 0x98($a1)
   sd         $s1, 0xA0($a1)
   sd         $s2, 0xA8($a1)
   sd         $s3, 0xB0($a1)
   sd         $s4, 0xB8($a1)
   sd         $s5, 0xC0($a1)
   sd         $s6, 0xC8($a1)
   sd         $s7, 0xD0($a1)
   sd         $gp, 0xE8($a1)
   sd         $sp, 0xF0($a1)
   sd         $fp, 0xF8($a1)
   sd         $ra, 0x100($a1)
   beqz       $k1, .Linit_802216E0
   sw        $ra, 0x11C($a1)
   cfc1       $k1, $31
   sdc1       $f20, 0x180($a1)
   sdc1       $f22, 0x188($a1)
   sdc1       $f24, 0x190($a1)
   sdc1       $f26, 0x198($a1)
   sdc1       $f28, 0x1A0($a1)
   sdc1       $f30, 0x1A8($a1)
   sw         $k1, 0x12C($a1)
.Linit_802216E0:
   lui        $k1, %hi(0xA430000C) /* MI_INTR_MASK_REG */
   lw         $k1, %lo(0xA430000C)($k1)
   beqz       $a0, .Linit_802216F8
   sw        $k1, 0x128($a1)
   jal        __osEnqueueThread
   nop
.Linit_802216F8:
   j          __osDispatchThread
   nop
endlabel send_mesg

glabel __osEnqueueThread
   lw         $t8, 0x0($a0)
   lw         $t7, 0x4($a1)
   or         $t9, $a0, $zero
   lw         $t6, 0x4($t8)
   slt        $at, $t6, $t7
   bnez       $at, .Linit_80221734
   nop
.Linit_8022171C:
   or         $t9, $t8, $zero
   lw         $t8, 0x0($t8)
   lw         $t6, 0x4($t8)
   slt        $at, $t6, $t7
   beqz       $at, .Linit_8022171C
   nop
.Linit_80221734:
   lw         $t8, 0x0($t9)
   sw         $t8, 0x0($a1)
   sw         $a1, 0x0($t9)
   jr         $ra
   sw        $a0, 0x8($a1)
endlabel __osEnqueueThread

glabel __osPopThread
   lw         $v0, 0x0($a0)
   lw         $t9, 0x0($v0)
   jr         $ra
   sw        $t9, 0x0($a0)
endlabel __osPopThread

glabel __osDispatchThread
   lui        $a0, %hi(__osRunQueue)
   jal        __osPopThread
   addiu     $a0, $a0, %lo(__osRunQueue)
   lui        $at, %hi(__osRunningThread)
   sw         $v0, %lo(__osRunningThread)($at)
   addiu      $t0, $zero, 0x4
   sh         $t0, 0x10($v0)
   or         $k0, $v0, $zero
.Linit_80221778:
   ld         $k1, 0x108($k0)
   ld         $at, 0x20($k0)
   ld         $v0, 0x28($k0)
   mtlo       $k1
   ld         $k1, 0x110($k0)
   ld         $v1, 0x30($k0)
   ld         $a0, 0x38($k0)
   ld         $a1, 0x40($k0)
   ld         $a2, 0x48($k0)
   ld         $a3, 0x50($k0)
   ld         $t0, 0x58($k0)
   ld         $t1, 0x60($k0)
   ld         $t2, 0x68($k0)
   ld         $t3, 0x70($k0)
   ld         $t4, 0x78($k0)
   ld         $t5, 0x80($k0)
   ld         $t6, 0x88($k0)
   ld         $t7, 0x90($k0)
   ld         $s0, 0x98($k0)
   ld         $s1, 0xA0($k0)
   ld         $s2, 0xA8($k0)
   ld         $s3, 0xB0($k0)
   ld         $s4, 0xB8($k0)
   ld         $s5, 0xC0($k0)
   ld         $s6, 0xC8($k0)
   ld         $s7, 0xD0($k0)
   ld         $t8, 0xD8($k0)
   ld         $t9, 0xE0($k0)
   ld         $gp, 0xE8($k0)
   mthi       $k1
   ld         $sp, 0xF0($k0)
   ld         $fp, 0xF8($k0)
   ld         $ra, 0x100($k0)
   lw         $k1, 0x11C($k0)
   mtc0       $k1, $14
   lw         $k1, 0x118($k0)
   mtc0       $k1, $12
   lw         $k1, 0x18($k0)
   beqz       $k1, .Linit_80221860
   nop
   lw         $k1, 0x12C($k0)
   ctc1       $k1, $31
   ldc1       $f0, 0x130($k0)
   ldc1       $f2, 0x138($k0)
   ldc1       $f4, 0x140($k0)
   ldc1       $f6, 0x148($k0)
   ldc1       $f8, 0x150($k0)
   ldc1       $f10, 0x158($k0)
   ldc1       $f12, 0x160($k0)
   ldc1       $f14, 0x168($k0)
   ldc1       $f16, 0x170($k0)
   ldc1       $f18, 0x178($k0)
   ldc1       $f20, 0x180($k0)
   ldc1       $f22, 0x188($k0)
   ldc1       $f24, 0x190($k0)
   ldc1       $f26, 0x198($k0)
   ldc1       $f28, 0x1A0($k0)
   ldc1       $f30, 0x1A8($k0)
.Linit_80221860:
   lw         $k1, 0x128($k0)
   sll        $k1, $k1, 1
   lui        $k0, %hi(__osRcpImTable)
   addiu      $k0, $k0, %lo(__osRcpImTable)
   addu       $k1, $k1, $k0
   lhu        $k1, 0x0($k1)
   lui        $k0, %hi(0xA430000C) /* MI_INTR_MASK_REG */
   addiu      $k0, $k0, %lo(0xA430000C)
   sw         $k1, 0x0($k0)
   nop
   nop
   nop
   nop
   eret
endlabel __osDispatchThread

glabel __osCleanupThread
   jal        osDestroyThread
   or         $a0, $zero, $zero
endlabel __osCleanupThread
