/* Proposed file name: cell_visibility.s
 *
 * RSP-assisted hierarchical visibility culling of grid-partitioned level
 * geometry, plus the display-list builder that consumes its results.
 *
 * The level is partitioned into a grid of cells (dimensions in
 * D_hd_code_803BE714/6, per-cell min/max heights in a table referenced by
 * the grid header). Each culling pass subdivides the grid quadtree-style:
 * rects are popped off a stack (D_hd_code_803C2B88/90), their axis-aligned
 * bounding box (from the rect extents and the min/max height table) is
 * rendered by an RSP microcode task through the scheduler, and the output
 * buffer tells whether anything would have been drawn. Visible rects are
 * split into four quadrants and re-pushed; visible 1x1 rects record their
 * cell index into a pending list (D_hd_code_803C3178/3170), which is merged
 * into the sorted visible-cell list (D_hd_code_803C30A8, -1 terminated) at
 * the start of the next pass. One rect is tested per call, paced by a
 * countdown (D_hd_code_803C3248), so a full pass is spread across frames.
 *
 * The builder half walks the level geometry's cell records against the
 * sorted visible list and emits F3D display lists for the visible cells
 * (four layer buffers plus static always-visible geometry), patching
 * G_SETTIMG addresses and G_SETPRIMCOLOR alpha at copy time to implement
 * animated, crossfading textures.
 *
 * All functions are handwritten: they pass arguments in s/t registers
 * across calls rather than following the standard ABI.
 */

.include "macro.inc"

.set noat
.set noreorder
.set gp=64

.section .text, "ax"

/* Proposed name: cellVisInitAll
 * Marks every grid cell as visible/pending. Zeroes the re-test countdown
 * (D_hd_code_803C3248), resets the quadtree rect stack (D_hd_code_803C2B88 =
 * stack base D_hd_code_803C2B90), then fills both the pending cell list
 * (D_hd_code_803C3178) and the sorted visible-cell list (D_hd_code_803C30A8)
 * with all indices 0..(cols*rows)-1 (cols/rows from D_hd_code_803BE714/6),
 * terminating the sorted list with -1 and storing the pending-list end
 * pointer in D_hd_code_803C3170. No-arg variant of func_hd_code_802A45D4.
 */
glabel func_hd_code_802A4510
  addiu      $sp, $sp, -0x28
  sd         $t0, 0x8($sp)
  lui        $t0, %hi(D_hd_code_803C3248)
  sd         $ra, 0x0($sp)
  sd         $t1, 0x10($sp)
  sd         $t2, 0x18($sp)
  sd         $t3, 0x20($sp)
  addiu      $t0, $t0, %lo(D_hd_code_803C3248)
  sh         $zero, 0x0($t0)
  lui        $t0, %hi(D_hd_code_803C2B90)
  lui        $t1, %hi(D_hd_code_803C2B88)
  addiu      $t0, $t0, %lo(D_hd_code_803C2B90)
  addiu      $t1, $t1, %lo(D_hd_code_803C2B88)
  sw         $t0, 0x0($t1)
  lui        $t0, %hi(D_hd_code_803BE714)
  lui        $t1, %hi(D_hd_code_803BE716)
  addiu      $t0, $t0, %lo(D_hd_code_803BE714)
  addiu      $t1, $t1, %lo(D_hd_code_803BE716)
  lhu        $t0, 0x0($t0)
  lhu        $t1, 0x0($t1)
  lui        $t3, %hi(D_hd_code_803C30A8)
  addiu      $t3, $t3, %lo(D_hd_code_803C30A8)
  multu      $t0, $t1
  lui        $t1, %hi(D_hd_code_803C3178)
  addiu      $t1, $t1, %lo(D_hd_code_803C3178)
  addiu      $t2, $zero, 0x0
  mflo       $t0
  nop
  nop
  .Lhd_code_802A4584:
  beq        $t0, $t2, .Lhd_code_802A45A4
   nop
  sh         $t2, 0x0($t1)
  sh         $t2, 0x0($t3)
  addi       $t1, $t1, 0x2 /* handwritten instruction */
  addi       $t3, $t3, 0x2 /* handwritten instruction */
  b          .Lhd_code_802A4584
   addi      $t2, $t2, 0x1 /* handwritten instruction */
  .Lhd_code_802A45A4:
  lui        $t2, %hi(D_hd_code_803C3170)
  addiu      $t2, $t2, %lo(D_hd_code_803C3170)
  sw         $t1, 0x0($t2)
  addiu      $t2, $zero, -0x1
  sh         $t2, 0x0($t3)
  ld         $ra, 0x0($sp)
  ld         $t3, 0x20($sp)
  ld         $t2, 0x18($sp)
  ld         $t1, 0x10($sp)
  ld         $t0, 0x8($sp)
  jr         $ra
   addiu     $sp, $sp, 0x28
endlabel func_hd_code_802A4510

/* Proposed name: cellVisInitAllDelayed
 * Identical to func_hd_code_802A4510 (mark all cells visible, reset stack and
 * lists) except the re-test countdown D_hd_code_803C3248 is set to the a0
 * argument instead of 0, postponing the next culling pass by a0 calls to
 * func_hd_code_802A467C.
 */
glabel func_hd_code_802A45D4
  addiu      $sp, $sp, -0x8
  lui        $t0, %hi(D_hd_code_803C3248)
  sd         $ra, 0x0($sp)
  addiu      $t0, $t0, %lo(D_hd_code_803C3248)
  sh         $a0, 0x0($t0)
  lui        $t0, %hi(D_hd_code_803C2B90)
  lui        $t1, %hi(D_hd_code_803C2B88)
  addiu      $t0, $t0, %lo(D_hd_code_803C2B90)
  addiu      $t1, $t1, %lo(D_hd_code_803C2B88)
  sw         $t0, 0x0($t1)
  lui        $t0, %hi(D_hd_code_803BE714)
  lui        $t1, %hi(D_hd_code_803BE716)
  addiu      $t0, $t0, %lo(D_hd_code_803BE714)
  addiu      $t1, $t1, %lo(D_hd_code_803BE716)
  lhu        $t0, 0x0($t0)
  lhu        $t1, 0x0($t1)
  lui        $t3, %hi(D_hd_code_803C30A8)
  addiu      $t3, $t3, %lo(D_hd_code_803C30A8)
  multu      $t0, $t1
  lui        $t1, %hi(D_hd_code_803C3178)
  addiu      $t1, $t1, %lo(D_hd_code_803C3178)
  addiu      $t2, $zero, 0x0
  mflo       $t0
  nop
  nop
  .Lhd_code_802A4638:
  beq        $t0, $t2, .Lhd_code_802A4658
   nop
  sh         $t2, 0x0($t1)
  sh         $t2, 0x0($t3)
  addi       $t1, $t1, 0x2 /* handwritten instruction */
  addi       $t3, $t3, 0x2 /* handwritten instruction */
  b          .Lhd_code_802A4638
   addi      $t2, $t2, 0x1 /* handwritten instruction */
  .Lhd_code_802A4658:
  lui        $t2, %hi(D_hd_code_803C3170)
  addiu      $t2, $t2, %lo(D_hd_code_803C3170)
  sw         $t1, 0x0($t2)
  addiu      $t2, $zero, -0x1
  sh         $t2, 0x0($t3)
  ld         $ra, 0x0($sp)
  addiu      $sp, $sp, 0x8
  jr         $ra
   nop
endlabel func_hd_code_802A45D4

/* Proposed name: cellVisUpdate
 * Per-frame tick of the cell visibility system. If the countdown
 * D_hd_code_803C3248 is nonzero it just decrements it; otherwise it runs one
 * culling pass via func_hd_code_802A470C. Saves/restores all callee-saved
 * registers because the pass functions pass parameters in s-registers.
 */
glabel func_hd_code_802A467C
  addiu      $sp, $sp, -0x58
  lui        $t0, %hi(D_hd_code_803C3248)
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
  addiu      $t0, $t0, %lo(D_hd_code_803C3248)
  lhu        $t1, 0x0($t0)
  bnez       $t1, .Lhd_code_802A46D0
   nop
  jal        func_hd_code_802A470C
   nop
  b          .Lhd_code_802A46D8
   nop
  .Lhd_code_802A46D0:
  addiu      $t1, $t1, -0x1
  sh         $t1, 0x0($t0)
  .Lhd_code_802A46D8:
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
endlabel func_hd_code_802A467C

/* Proposed name: cellVisCullPass
 * Runs one incremental step of the hierarchical culling pass. a0 points to a
 * grid header (0x0: cols s16, 0x2: rows s16, 0x4/0x6: cell world size x/z,
 * 0x48: offset to per-cell min/max height data). If the rect stack is empty,
 * a new pass is started: the root rect {0,0,cols,rows} is pushed and the
 * pending list (D_hd_code_803C3178..D_hd_code_803C3170) is insertion-merged
 * into the sorted visible list D_hd_code_803C30A8 (-1 terminated). Then the
 * top rect is popped and handed to func_hd_code_802A484C in s0-s3 (x,y,w,h)
 * with grid params in s4/s6/s7/t8, after which the stack pointer
 * D_hd_code_803C2B88 and pending-list pointer D_hd_code_803C3170 are saved.
 */
glabel func_hd_code_802A470C
  addiu      $sp, $sp, -0x8
  lui        $t0, %hi(D_hd_code_803C2B88)
  sd         $ra, 0x0($sp)
  addiu      $t0, $t0, %lo(D_hd_code_803C2B88)
  lw         $t3, 0x0($t0)
  lui        $t2, %hi(D_hd_code_803C2B90)
  addiu      $t2, $t2, %lo(D_hd_code_803C2B90)
  bne        $t2, $t3, .Lhd_code_802A47EC
   nop
  lh         $s2, 0x0($a0)
  lh         $s3, 0x2($a0)
  lui        $t1, %hi(D_hd_code_803C3170)
  sh         $zero, 0x0($t3)
  sh         $zero, 0x2($t3)
  addiu      $t1, $t1, %lo(D_hd_code_803C3170)
  lui        $t5, %hi(D_hd_code_803C3178)
  lui        $t6, %hi(D_hd_code_803C30A8)
  sh         $s2, 0x4($t3)
  sh         $s3, 0x6($t3)
  addi       $t3, $t3, 0x8 /* handwritten instruction */
  lw         $t4, 0x0($t1)
  addiu      $t5, $t5, %lo(D_hd_code_803C3178)
  addiu      $t6, $t6, %lo(D_hd_code_803C30A8)
  .Lhd_code_802A4768:
  beq        $t4, $t5, .Lhd_code_802A47D0
   nop
  lui        $t0, %hi(D_hd_code_803C30A8)
  lh         $t7, 0x0($t5)
  addiu      $t0, $t0, %lo(D_hd_code_803C30A8)
  .Lhd_code_802A477C:
  beq        $t0, $t6, .Lhd_code_802A47C0
   nop
  lh         $t1, 0x0($t0)
  slt        $at, $t7, $t1
  bnez       $at, .Lhd_code_802A479C
   nop
  b          .Lhd_code_802A477C
   addi      $t0, $t0, 0x2 /* handwritten instruction */
  .Lhd_code_802A479C:
  sh         $t7, 0x0($t0)
  .Lhd_code_802A47A0:
  lh         $t7, 0x2($t0)
  sh         $t1, 0x2($t0)
  addi       $t0, $t0, 0x2 /* handwritten instruction */
  bnel       $t0, $t6, .Lhd_code_802A47A0
   or        $t1, $t7, $zero
  addi       $t5, $t5, 0x2 /* handwritten instruction */
  b          .Lhd_code_802A4768
   addi      $t6, $t6, 0x2 /* handwritten instruction */
  .Lhd_code_802A47C0:
  sh         $t7, 0x0($t6)
  addi       $t5, $t5, 0x2 /* handwritten instruction */
  b          .Lhd_code_802A4768
   addi      $t6, $t6, 0x2 /* handwritten instruction */
  .Lhd_code_802A47D0:
  addiu      $t7, $zero, -0x1
  lui        $t0, %hi(D_hd_code_803C3178)
  lui        $t1, %hi(D_hd_code_803C3170)
  sh         $t7, 0x0($t6)
  addiu      $t0, $t0, %lo(D_hd_code_803C3178)
  addiu      $t1, $t1, %lo(D_hd_code_803C3170)
  sw         $t0, 0x0($t1)
  .Lhd_code_802A47EC:
  lw         $s6, 0x48($a0)
  lui        $s5, %hi(D_hd_code_803C3170)
  addiu      $s5, $s5, %lo(D_hd_code_803C3170)
  addi       $t3, $t3, -0x8 /* handwritten instruction */
  lh         $s0, 0x0($t3)
  lh         $s1, 0x2($t3)
  lh         $s2, 0x4($t3)
  lh         $s3, 0x6($t3)
  lh         $s4, 0x0($a0)
  lw         $s5, 0x0($s5)
  lh         $s7, 0x4($a0)
  lh         $t8, 0x6($a0)
  jal        func_hd_code_802A484C
   add       $s6, $s6, $a0 /* handwritten instruction */
  lui        $s4, %hi(D_hd_code_803C3170)
  addiu      $s4, $s4, %lo(D_hd_code_803C3170)
  sw         $s5, 0x0($s4)
  lui        $s4, %hi(D_hd_code_803C2B88)
  addiu      $s4, $s4, %lo(D_hd_code_803C2B88)
  sw         $t3, 0x0($s4)
  ld         $ra, 0x0($sp)
  addiu      $sp, $sp, 0x8
  jr         $ra
   nop
endlabel func_hd_code_802A470C

/* Proposed name: cellVisTestRect
 * Tests one grid rect (s0=x, s1=y, s2=w, s3=h) and subdivides it. Calls
 * func_hd_code_802A49A8 (min/max height of the rect), func_hd_code_802A4A50
 * (build the 8 bounding-box vertices) and func_hd_code_802A4B0C (run the RSP
 * visibility test, result in t6). If the box is visible: a 1x1 rect records
 * its cell index (y*cols+x) into the pending list at s5; a larger rect is
 * split into up to four quadrants (w/2 x h/2) which are pushed onto the rect
 * stack at t3 for later passes. Register-based calling convention throughout.
 */
glabel func_hd_code_802A484C
  addiu      $sp, $sp, -0x48
  sd         $ra, 0x0($sp)
  sd         $a0, 0x8($sp)
  sd         $t0, 0x10($sp)
  sd         $t1, 0x18($sp)
  sd         $t2, 0x20($sp)
  sd         $s0, 0x28($sp)
  sd         $s1, 0x30($sp)
  sd         $s2, 0x38($sp)
  jal        func_hd_code_802A49A8
   sd        $s3, 0x40($sp)
  jal        func_hd_code_802A4A50
   nop
  jal        func_hd_code_802A4B0C
   nop
  beqz       $t6, .Lhd_code_802A497C
   nop
  addiu      $v0, $zero, 0x1
  bne        $s2, $v0, .Lhd_code_802A48BC
   nop
  bne        $s3, $v0, .Lhd_code_802A48BC
   nop
  mult       $s1, $s4
  addi       $s5, $s5, 0x2 /* handwritten instruction */
  mflo       $v1
  add        $v1, $v1, $s0 /* handwritten instruction */
  b          .Lhd_code_802A497C
   sh        $v1, -0x2($s5)
  .Lhd_code_802A48BC:
  or         $t1, $s2, $zero
  or         $t2, $s3, $zero
  srl        $s2, $s2, 1
  or         $a0, $s0, $zero
  or         $t0, $s1, $zero
  beqz       $s2, .Lhd_code_802A48F4
   srl       $s3, $s3, 1
  beqz       $s3, .Lhd_code_802A48F4
   nop
  sh         $s0, 0x0($t3)
  sh         $s1, 0x2($t3)
  sh         $s2, 0x4($t3)
  sh         $s3, 0x6($t3)
  addi       $t3, $t3, 0x8 /* handwritten instruction */
  .Lhd_code_802A48F4:
  add        $s0, $s0, $s2 /* handwritten instruction */
  sub        $s2, $t1, $s2 /* handwritten instruction */
  beqz       $s2, .Lhd_code_802A4920
   nop
  beqz       $s3, .Lhd_code_802A4920
   nop
  sh         $s0, 0x0($t3)
  sh         $s1, 0x2($t3)
  sh         $s2, 0x4($t3)
  sh         $s3, 0x6($t3)
  addi       $t3, $t3, 0x8 /* handwritten instruction */
  .Lhd_code_802A4920:
  add        $s1, $s1, $s3 /* handwritten instruction */
  srl        $s2, $t1, 1
  or         $s0, $a0, $zero
  beqz       $s2, .Lhd_code_802A4950
   sub       $s3, $t2, $s3 /* handwritten instruction */
  beqz       $s3, .Lhd_code_802A4950
   nop
  sh         $s0, 0x0($t3)
  sh         $s1, 0x2($t3)
  sh         $s2, 0x4($t3)
  sh         $s3, 0x6($t3)
  addi       $t3, $t3, 0x8 /* handwritten instruction */
  .Lhd_code_802A4950:
  add        $s0, $s0, $s2 /* handwritten instruction */
  sub        $s2, $t1, $s2 /* handwritten instruction */
  beqz       $s2, .Lhd_code_802A497C
   nop
  beqz       $s3, .Lhd_code_802A497C
   nop
  sh         $s0, 0x0($t3)
  sh         $s1, 0x2($t3)
  sh         $s2, 0x4($t3)
  sh         $s3, 0x6($t3)
  addi       $t3, $t3, 0x8 /* handwritten instruction */
  .Lhd_code_802A497C:
  ld         $ra, 0x0($sp)
  ld         $a0, 0x8($sp)
  ld         $t0, 0x10($sp)
  ld         $t1, 0x18($sp)
  ld         $t2, 0x20($sp)
  ld         $s0, 0x28($sp)
  ld         $s1, 0x30($sp)
  ld         $s2, 0x38($sp)
  ld         $s3, 0x40($sp)
  jr         $ra
   addiu     $sp, $sp, 0x48
endlabel func_hd_code_802A484C

/* Proposed name: cellVisGetRectHeightBounds
 * Scans the per-cell height data for rect (s0=x, s1=y, s2=w, s3=h) in a grid
 * s4 cells wide whose data (two s16 per cell: min,max) starts at s6.
 * Iterates w*h entries starting at &s6[(s1*s4+s0)*4] and returns the lowest
 * min in v1 and the highest max in a0 (initialized to 0x7FFF/-0x8000), i.e.
 * the vertical extent of the rect used to build its bounding box.
 */
glabel func_hd_code_802A49A8
  mult       $s1, $s4
  addiu      $sp, $sp, -0x30
  sd         $a1, 0x8($sp)
  sd         $s4, 0x28($sp)
  sd         $ra, 0x0($sp)
  sd         $a2, 0x10($sp)
  sd         $a3, 0x18($sp)
  sd         $s3, 0x20($sp)
  sll        $s4, $s4, 2
  addiu      $v1, $zero, 0x7FFF
  mflo       $v0
  add        $v0, $v0, $s0 /* handwritten instruction */
  sll        $v0, $v0, 2
  add        $v0, $v0, $s6 /* handwritten instruction */
  addiu      $a0, $zero, -0x8000
  or         $a1, $v0, $zero
  .Lhd_code_802A49E8:
  or         $a2, $s2, $zero
  .Lhd_code_802A49EC:
  lh         $a3, 0x0($v0)
  lh         $t0, 0x2($v0)
  slt        $at, $a3, $v1
  beqz       $at, .Lhd_code_802A4A04
   nop
  or         $v1, $a3, $zero
  .Lhd_code_802A4A04:
  slt        $at, $a0, $t0
  beqz       $at, .Lhd_code_802A4A14
   nop
  or         $a0, $t0, $zero
  .Lhd_code_802A4A14:
  addi       $a2, $a2, -0x1 /* handwritten instruction */
  bnez       $a2, .Lhd_code_802A49EC
   addi      $v0, $v0, 0x4 /* handwritten instruction */
  add        $a1, $a1, $s4 /* handwritten instruction */
  addi       $s3, $s3, -0x1 /* handwritten instruction */
  bnez       $s3, .Lhd_code_802A49E8
   or        $v0, $a1, $zero
  ld         $ra, 0x0($sp)
  ld         $a1, 0x8($sp)
  ld         $a2, 0x10($sp)
  ld         $a3, 0x18($sp)
  ld         $s3, 0x20($sp)
  ld         $s4, 0x28($sp)
  jr         $ra
   addiu     $sp, $sp, 0x30
endlabel func_hd_code_802A49A8

/* Proposed name: cellVisBuildBoxVertices
 * Writes the 8 corner vertices of the rect's axis-aligned bounding box into
 * the Vtx buffer at a2 (8 entries, 0x10 bytes each). X coords are s0*s7 and
 * (s0+s2)*s7, Z coords are s1*t8 and (s1+s3)*t8 (cell coords scaled by the
 * cell world size), and Y is the min height (v1) for the lower four corners
 * and the max height (a0) for the upper four, as computed by
 * func_hd_code_802A49A8. This box is what func_hd_code_802A4B0C feeds to the
 * RSP visibility test.
 */
glabel func_hd_code_802A4A50
  multu      $s0, $s7
  addiu      $sp, $sp, -0x28
  sd         $t1, 0x8($sp)
  sd         $t2, 0x10($sp)
  addu       $t6, $s0, $s2
  sd         $t3, 0x18($sp)
  sd         $t4, 0x20($sp)
  sd         $ra, 0x0($sp)
  sh         $v1, 0x2($a2)
  sh         $v1, 0x12($a2)
  mflo       $t1
  sh         $t1, 0x0($a2)
  sh         $v1, 0x22($a2)
  multu      $s1, $t8
  sh         $t1, 0x30($a2)
  sh         $v1, 0x32($a2)
  sh         $t1, 0x40($a2)
  sh         $a0, 0x42($a2)
  sh         $a0, 0x52($a2)
  sh         $a0, 0x62($a2)
  sh         $t1, 0x70($a2)
  sh         $a0, 0x72($a2)
  mflo       $t2
  sh         $t2, 0x4($a2)
  sh         $t2, 0x14($a2)
  multu      $t6, $s7
  addu       $t6, $s1, $s3
  sh         $t2, 0x44($a2)
  sh         $t2, 0x54($a2)
  mflo       $t3
  sh         $t3, 0x10($a2)
  sh         $t3, 0x20($a2)
  multu      $t6, $t8
  sh         $t3, 0x50($a2)
  sh         $t3, 0x60($a2)
  mflo       $t4
  sh         $t4, 0x24($a2)
  sh         $t4, 0x34($a2)
  sh         $t4, 0x64($a2)
  sh         $t4, 0x74($a2)
  ld         $ra, 0x0($sp)
  ld         $t4, 0x20($sp)
  ld         $t3, 0x18($sp)
  ld         $t2, 0x10($sp)
  ld         $t1, 0x8($sp)
  jr         $ra
   addiu     $sp, $sp, 0x28
endlabel func_hd_code_802A4A50

/* Proposed name: cellVisRunRspTest
 * Runs the RSP visibility-test microcode on the bounding-box vertices (a2)
 * and returns visible/not-visible in t6. If the grid is only 1x1 cell the
 * test is skipped and t6=1. Otherwise it fills in the OSScTask at
 * D_hd_code_803BE740 (type 1 gfx task; boot ucode rspbootTextStart, ucode
 * D_hd_code_802E77B0 / data D_hd_code_8030EE60, output buffer
 * D_hd_code_803BEB80, data_ptr=a1, data_size=a3, yield buffer
 * D_hd_code_8036AFB0, msg id 0x4D3), flushes caches, sends the task to the
 * scheduler queue `sc` via osSendMesg, waits for completion via
 * func_hd_code_80285110(0x4D3), then checks the output buffer: if its first
 * word is 0xE8000000 (G_RDPTILESYNC, i.e. nothing drawn) the box is not
 * visible (t6=0), otherwise t6=1.
 */
glabel func_hd_code_802A4B0C
  addiu      $sp, $sp, -0x50
  lui        $t0, %hi(D_hd_code_803BE714)
  lh         $t0, %lo(D_hd_code_803BE714)($t0)
  addiu      $at, $zero, 0x1
  sd         $ra, 0x0($sp)
  sd         $a1, 0x8($sp)
  sd         $a2, 0x10($sp)
  sd         $a3, 0x18($sp)
  sd         $t1, 0x20($sp)
  sd         $t3, 0x28($sp)
  sd         $s4, 0x30($sp)
  sd         $s5, 0x38($sp)
  sd         $t8, 0x40($sp)
  bne        $t0, $at, .Lhd_code_802A4B5C
   sd        $fp, 0x48($sp)
  lui        $t0, %hi(D_hd_code_803BE716)
  lh         $t0, %lo(D_hd_code_803BE716)($t0)
  addiu      $at, $zero, 0x1
  beq        $t0, $at, .Lhd_code_802A4CA0
   nop
  .Lhd_code_802A4B5C:
  lui        $t0, %hi(D_hd_code_803BE740)
  addiu      $t0, $t0, %lo(D_hd_code_803BE740)
  addiu      $t1, $zero, 0x1
  sw         $t1, 0x10($t0)
  addiu      $t1, $zero, 0x0
  sw         $t1, 0x14($t0)
  lui        $t1, %hi(rspbootTextStart)
  addiu      $t1, $t1, %lo(rspbootTextStart)
  lui        $t2, %hi(aspMainTextStart)
  addiu      $t2, $t2, %lo(aspMainTextStart)
  sw         $t1, 0x18($t0)
  subu       $t2, $t2, $t1
  lui        $t1, %hi(D_hd_code_802E77B0)
  addiu      $t1, $t1, %lo(D_hd_code_802E77B0)
  sw         $t1, 0x20($t0)
  addiu      $t1, $zero, 0x1000
  sw         $t1, 0x24($t0)
  lui        $t1, %hi(D_hd_code_8030EE60)
  addiu      $t1, $t1, %lo(D_hd_code_8030EE60)
  sw         $t1, 0x28($t0)
  addiu      $t1, $zero, 0x800
  sw         $t1, 0x2C($t0)
  lui        $t1, %hi(D_hd_code_803BE780)
  addiu      $t1, $t1, %lo(D_hd_code_803BE780)
  sw         $t1, 0x30($t0)
  addiu      $t1, $zero, 0x400
  sw         $t1, 0x34($t0)
  lui        $t1, %hi(D_hd_code_803BEB80)
  addiu      $t1, $t1, %lo(D_hd_code_803BEB80)
  sw         $t1, 0x38($t0)
  lui        $t1, %hi(D_hd_code_803C2B80)
  addiu      $t1, $t1, %lo(D_hd_code_803C2B80)
  sw         $t1, 0x3C($t0)
  lui        $t1, %hi(D_hd_code_8036AFB0)
  addiu      $t1, $t1, %lo(D_hd_code_8036AFB0)
  sw         $t1, 0x48($t0)
  addiu      $t1, $zero, 0x900
  sw         $t1, 0x4C($t0)
  addiu      $t1, $zero, 0x1
  sw         $t1, 0x8($t0)
  lui        $t1, %hi(D_hd_code_803153D8)
  addiu      $t1, $t1, %lo(D_hd_code_803153D8)
  sw         $t1, 0x54($t0)
  addiu      $t1, $zero, 0x4D3
  sw         $t1, 0x58($t0)
  addiu      $t1, $zero, 0x0
  sw         $t1, 0xC($t0)
  lui        $t1, %hi(D_hd_code_803156D8)
  sw         $a1, 0x40($t0)
  addiu      $t1, $t1, %lo(D_hd_code_803156D8)
  sw         $t2, 0x1C($t0)
  sw         $a3, 0x44($t0)
  sw         $t1, 0x50($t0)
  or         $s4, $t0, $zero
  addi       $sp, $sp, -0x20 /* handwritten instruction */
  or         $a0, $a2, $zero
  jal        osWritebackDCache
   addiu     $a1, $zero, 0x80
  or         $a0, $s4, $zero
  jal        osWritebackDCache
   addiu     $a1, $zero, 0x40
  lui        $a0, %hi(D_hd_code_803BEB80)
  addiu      $a0, $a0, %lo(D_hd_code_803BEB80)
  jal        osInvalDCache
   addiu     $a1, $zero, 0x20
  lui        $a2, %hi(sc)
  addiu      $a2, $a2, %lo(sc)
  addiu      $a0, $a2, 0x0
  lui        $a1, %hi(D_hd_code_803BE740)
  addiu      $a1, $a1, %lo(D_hd_code_803BE740)
  jal        osSendMesg
   addiu     $a2, $zero, 0x1
  jal        func_hd_code_80285110
   addiu     $a0, $zero, 0x4D3
  lui        $a1, %hi(D_hd_code_803BEB80)
  addiu      $a1, $a1, %lo(D_hd_code_803BEB80)
  lw         $a2, 0x0($a1)
  lui        $at, (0xE8000000 >> 16)
  addiu      $sp, $sp, 0x20
  beq        $a2, $at, .Lhd_code_802A4CA8
   nop
  .Lhd_code_802A4CA0:
  b          .Lhd_code_802A4CAC
   addiu     $t6, $zero, 0x1
  .Lhd_code_802A4CA8:
  addiu      $t6, $zero, 0x0
  .Lhd_code_802A4CAC:
  ld         $ra, 0x0($sp)
  ld         $a1, 0x8($sp)
  ld         $a2, 0x10($sp)
  ld         $a3, 0x18($sp)
  ld         $t1, 0x20($sp)
  ld         $t3, 0x28($sp)
  ld         $s4, 0x30($sp)
  ld         $s5, 0x38($sp)
  ld         $t8, 0x40($sp)
  ld         $fp, 0x48($sp)
  jr         $ra
   addiu     $sp, $sp, 0x50
endlabel func_hd_code_802A4B0C

/* Proposed name: cellVisBuildDisplayLists
 * Builds the frame's display lists from the visible-cell list. Loads the
 * level geometry header from D_hd_code_80358074 and, for each of the four
 * DL output buffers passed in a0-a3, calls func_hd_code_802A4E4C with one of
 * four consecutive cell-record ranges (header offsets 0xA0-0xC0 hold the
 * range table, likely one range per geometry layer/pass). Then emits the
 * always-visible static sub-DLs (offsets 0x7C/0x80) into a fifth buffer (5th
 * stack argument) via func_hd_code_802A4DE8, and finally advances the
 * texture animations via func_hd_code_802A5020.
 */
glabel func_hd_code_802A4CDC
  addiu      $sp, $sp, -0x28
  or         $t2, $a1, $zero
  or         $a1, $a0, $zero
  lui        $a0, %hi(D_hd_code_80358074)
  sd         $ra, 0x0($sp)
  sd         $s0, 0x8($sp)
  sd         $s1, 0x10($sp)
  sd         $s2, 0x18($sp)
  sd         $gp, 0x20($sp)
  addiu      $a0, $a0, %lo(D_hd_code_80358074)
  lw         $a0, 0x0($a0)
  or         $t0, $a2, $zero
  or         $t1, $a3, $zero
  lw         $a2, 0xA0($a0)
  lw         $a3, 0xA4($a0)
  lw         $t8, 0xB0($a0)
  lw         $t9, 0xB4($a0)
  add        $a2, $a2, $a0 /* handwritten instruction */
  add        $a3, $a3, $a0 /* handwritten instruction */
  add        $t8, $t8, $a0 /* handwritten instruction */
  jal        func_hd_code_802A4E4C
   add       $t9, $t9, $a0 /* handwritten instruction */
  lw         $a2, 0xA4($a0)
  lw         $a3, 0xA8($a0)
  lw         $t8, 0xB4($a0)
  lw         $t9, 0xB8($a0)
  or         $a1, $t2, $zero
  add        $a2, $a2, $a0 /* handwritten instruction */
  add        $a3, $a3, $a0 /* handwritten instruction */
  add        $t8, $t8, $a0 /* handwritten instruction */
  jal        func_hd_code_802A4E4C
   add       $t9, $t9, $a0 /* handwritten instruction */
  lw         $a2, 0xA8($a0)
  lw         $a3, 0xAC($a0)
  lw         $t8, 0xB8($a0)
  lw         $t9, 0xBC($a0)
  or         $a1, $t0, $zero
  add        $a2, $a2, $a0 /* handwritten instruction */
  add        $a3, $a3, $a0 /* handwritten instruction */
  add        $t8, $t8, $a0 /* handwritten instruction */
  jal        func_hd_code_802A4E4C
   add       $t9, $t9, $a0 /* handwritten instruction */
  lw         $a2, 0xAC($a0)
  lw         $a3, 0xB0($a0)
  lw         $t8, 0xBC($a0)
  lw         $t9, 0xC0($a0)
  or         $a1, $t1, $zero
  add        $a2, $a2, $a0 /* handwritten instruction */
  add        $a3, $a3, $a0 /* handwritten instruction */
  add        $t8, $t8, $a0 /* handwritten instruction */
  jal        func_hd_code_802A4E4C
   add       $t9, $t9, $a0 /* handwritten instruction */
  lw         $a2, 0x7C($a0)
  lw         $a3, 0x80($a0)
  lw         $a1, 0x38($sp)
  addu       $a2, $a2, $a0
  jal        func_hd_code_802A4DE8
   addu      $a3, $a3, $a0
  jal        func_hd_code_802A5020
   nop
  ld         $ra, 0x0($sp)
  ld         $s0, 0x8($sp)
  ld         $s1, 0x10($sp)
  ld         $s2, 0x18($sp)
  ld         $gp, 0x20($sp)
  jr         $ra
   addiu     $sp, $sp, 0x28
endlabel func_hd_code_802A4CDC

/* Proposed name: appendStaticSubDLs
 * Walks the static geometry commands from a2 to a3 and, for each sub-list,
 * writes a gsSPDisplayList command (0x06000000, address converted from
 * KSEG0 to physical by subtracting 0x80000000) into the output DL at a1,
 * skipping forward in the source past each G_ENDDL (0xB8000000) to find the
 * next sub-list. Terminates the output with its own G_ENDDL.
 */
glabel func_hd_code_802A4DE8
  addiu      $sp, $sp, -0x8
  sd         $ra, 0x0($sp)
  lui        $t2, (0x80000000 >> 16)
  lui        $t1, (0xB8000000 >> 16)
  .Lhd_code_802A4DF8:
  beq        $a2, $a3, .Lhd_code_802A4E2C
   nop
  subu       $t3, $a2, $t2
  lui        $at, (0x6000000 >> 16)
  sw         $at, 0x0($a1)
  sw         $t3, 0x4($a1)
  addi       $a1, $a1, 0x8 /* handwritten instruction */
  .Lhd_code_802A4E14:
  lw         $t0, 0x0($a2)
  addi       $a2, $a2, 0x8 /* handwritten instruction */
  bne        $t0, $t1, .Lhd_code_802A4E14
   nop
  b          .Lhd_code_802A4DF8
   nop
  .Lhd_code_802A4E2C:
  lui        $at, (0xB8000000 >> 16)
  sw         $at, 0x0($a1)
  sw         $zero, 0x4($a1)
  ld         $ra, 0x0($sp)
  addi       $a1, $a1, 0x8 /* handwritten instruction */
  addiu      $sp, $sp, 0x8
  jr         $ra
   nop
endlabel func_hd_code_802A4DE8

/* Proposed name: emitVisibleCellDLs
 * Emits the geometry display lists for all visible cells of one layer.
 * a0=geometry header, a1=output DL, a2/a3=cell record range (0x14-byte
 * records: 0x0/0x4=DL offsets, 0x8=DL end, 0xC=material/anim id, 0x10=cell
 * index), t8/t9=multi-cell record range (variable length: 0x10=cell count,
 * followed by a sorted cell index array). First copies the layer's header
 * commands (offsets 0x88/0x8C) into the output. Then for each record whose
 * cell index appears in the sorted visible list D_hd_code_803C30A8: records
 * its material id into the drawn-id list D_hd_code_803C2EB0, sets up its
 * texture animation via func_hd_code_802A50DC, and copies/patches its DL via
 * func_hd_code_802A51FC (consecutive records sharing the same id reuse the
 * setup). Multi-cell records are emitted if any of their cells is visible.
 * Finishes via func_hd_code_802A5334 and terminates the DL with G_ENDDL.
 */
glabel func_hd_code_802A4E4C
  addiu      $sp, $sp, -0x20
  sd         $ra, 0x0($sp)
  sd         $t0, 0x8($sp)
  sd         $t1, 0x10($sp)
  sd         $t2, 0x18($sp)
  lw         $t0, 0x88($a0)
  lw         $t1, 0x8C($a0)
  add        $t0, $t0, $a0 /* handwritten instruction */
  add        $t1, $t1, $a0 /* handwritten instruction */
  .Lhd_code_802A4E70:
  beq        $t0, $t1, .Lhd_code_802A4E8C
   nop
  ld         $t2, 0x0($t0)
  addi       $t0, $t0, 0x8 /* handwritten instruction */
  addi       $a1, $a1, 0x8 /* handwritten instruction */
  b          .Lhd_code_802A4E70
   sd        $t2, -0x8($a1)
  .Lhd_code_802A4E8C:
  lui        $v1, %hi(D_hd_code_803C2EB0)
  addiu      $v1, $v1, %lo(D_hd_code_803C2EB0)
  .Lhd_code_802A4E94:
  beq        $a2, $a3, .Lhd_code_802A4FF0
   nop
  lui        $t0, %hi(D_hd_code_803C30A8)
  lw         $t4, 0x10($a2)
  addiu      $t0, $t0, %lo(D_hd_code_803C30A8)
  .Lhd_code_802A4EA8:
  lh         $t1, 0x0($t0)
  addiu      $at, $zero, -0x1
  addi       $t0, $t0, 0x2 /* handwritten instruction */
  beq        $t1, $at, .Lhd_code_802A4FE8
   slt       $at, $t1, $t4
  bnez       $at, .Lhd_code_802A4EA8
   nop
  bne        $t1, $t4, .Lhd_code_802A4FE8
   nop
  lw         $t4, 0xC($a2)
  addi       $v1, $v1, 0x2 /* handwritten instruction */
  jal        func_hd_code_802A50DC
   sh        $t4, -0x2($v1)
  lw         $t5, 0x0($a2)
  jal        func_hd_code_802A51FC
   lw        $t6, 0x8($a2)
  .Lhd_code_802A4EE8:
  addi       $a2, $a2, 0x14 /* handwritten instruction */
  beq        $a2, $a3, .Lhd_code_802A4F4C
   nop
  lw         $t7, 0xC($a2)
  bne        $t4, $t7, .Lhd_code_802A4F4C
   nop
  lui        $t0, %hi(D_hd_code_803C30A8)
  lw         $t7, 0x10($a2)
  addiu      $t0, $t0, %lo(D_hd_code_803C30A8)
  .Lhd_code_802A4F0C:
  lh         $t2, 0x0($t0)
  addiu      $at, $zero, -0x1
  addi       $t0, $t0, 0x2 /* handwritten instruction */
  beq        $t2, $at, .Lhd_code_802A4EE8
   nop
  slt        $at, $t2, $t7
  bnez       $at, .Lhd_code_802A4F0C
   nop
  bne        $t2, $t7, .Lhd_code_802A4EE8
   nop
  addiu      $gp, $zero, 0x0
  lw         $t5, 0x4($a2)
  jal        func_hd_code_802A51FC
   lw        $t6, 0x8($a2)
  b          .Lhd_code_802A4EE8
   nop
  .Lhd_code_802A4F4C:
  or         $t7, $t8, $zero
  .Lhd_code_802A4F50:
  beq        $t7, $t9, .Lhd_code_802A4E94
   nop
  lw         $t1, 0xC($t7)
  slt        $at, $t4, $t1
  bnez       $at, .Lhd_code_802A4E94
   nop
  bne        $t4, $t1, .Lhd_code_802A4FD4
   nop
  lui        $t3, %hi(D_hd_code_803C30A8)
  lw         $t1, 0x10($t7)
  addi       $t2, $t7, 0x14 /* handwritten instruction */
  addiu      $t3, $t3, %lo(D_hd_code_803C30A8)
  .Lhd_code_802A4F80:
  lh         $v0, 0x0($t3)
  addiu      $at, $zero, -0x1
  beq        $v0, $at, .Lhd_code_802A4FD4
   nop
  addi       $t3, $t3, 0x2 /* handwritten instruction */
  or         $s0, $t2, $zero
  or         $s1, $t1, $zero
  .Lhd_code_802A4F9C:
  beqz       $s1, .Lhd_code_802A4F80
   nop
  lw         $s2, 0x0($s0)
  beq        $s2, $v0, .Lhd_code_802A4FC4
   slt       $at, $v0, $s2
  bnez       $at, .Lhd_code_802A4F80
   nop
  addi       $s0, $s0, 0x4 /* handwritten instruction */
  b          .Lhd_code_802A4F9C
   addi      $s1, $s1, -0x1 /* handwritten instruction */
  .Lhd_code_802A4FC4:
  addiu      $gp, $zero, 0x0
  lw         $t5, 0x4($t7)
  jal        func_hd_code_802A51FC
   lw        $t6, 0x8($t7)
  .Lhd_code_802A4FD4:
  lw         $t1, 0x10($t7)
  sll        $t1, $t1, 2
  addi       $t1, $t1, 0x14 /* handwritten instruction */
  b          .Lhd_code_802A4F50
   addu      $t7, $t7, $t1
  .Lhd_code_802A4FE8:
  b          .Lhd_code_802A4E94
   addi      $a2, $a2, 0x14 /* handwritten instruction */
  .Lhd_code_802A4FF0:
  jal        func_hd_code_802A5334
   nop
  lui        $at, (0xB8000000 >> 16)
  sw         $at, 0x0($a1)
  sw         $zero, 0x4($a1)
  ld         $ra, 0x0($sp)
  ld         $t2, 0x18($sp)
  ld         $t1, 0x10($sp)
  ld         $t0, 0x8($sp)
  addi       $a1, $a1, 0x8 /* handwritten instruction */
  jr         $ra
   addiu     $sp, $sp, 0x20
endlabel func_hd_code_802A4E4C

/* Proposed name: updateTextureAnims
 * Advances all texture animation records of the geometry header a0 (record
 * range at offsets 0x2C/0x30; variable-size records: 0x4=frame count,
 * 0x5=current frame, 0x6=blend flag, 0x7=blend factor out, 0x8=frame period,
 * 0xA=tick counter, then a table of per-frame DL/texture pointers). Each
 * tick increments the counter; when it reaches the period the current frame
 * advances (wrapping at frame count) and the counter resets. If blending is
 * enabled, computes the crossfade factor 255*counter/period into byte 0x7.
 */
glabel func_hd_code_802A5020
  addiu      $sp, $sp, -0x8
  sd         $ra, 0x0($sp)
  lw         $v0, 0x2C($a0)
  lw         $v1, 0x30($a0)
  addu       $v0, $v0, $a0
  addu       $v1, $v1, $a0
  .Lhd_code_802A5038:
  beq        $v0, $v1, .Lhd_code_802A50CC
   nop
  lhu        $a2, 0xA($v0)
  lhu        $a1, 0x8($v0)
  addi       $a2, $a2, 0x1 /* handwritten instruction */
  bne        $a1, $a2, .Lhd_code_802A5074
   nop
  lbu        $a2, 0x5($v0)
  lbu        $a1, 0x4($v0)
  addi       $a2, $a2, 0x1 /* handwritten instruction */
  bne        $a1, $a2, .Lhd_code_802A506C
   nop
  addiu      $a2, $zero, 0x0
  .Lhd_code_802A506C:
  sb         $a2, 0x5($v0)
  addiu      $a2, $zero, 0x0
  .Lhd_code_802A5074:
  lbu        $a1, 0x6($v0)
  beqz       $a1, .Lhd_code_802A50B4
   nop
  addiu      $a1, $zero, 0xFF
  multu      $a1, $a2
  lhu        $a3, 0x8($v0)
  mflo       $a1
  nop
  nop
  divu       $zero, $a1, $a3
  mflo       $a1
  mflo       $a1
  sb         $a1, 0x7($v0)
  bnez       $a3, .Lhd_code_802A50B4
   nop
  break      7
  .Lhd_code_802A50B4:
  lbu        $a1, 0x4($v0)
  sh         $a2, 0xA($v0)
  sll        $a1, $a1, 2
  addu       $v0, $v0, $a1
  b          .Lhd_code_802A5038
   addi      $v0, $v0, 0x8 /* handwritten instruction */
  .Lhd_code_802A50CC:
  ld         $ra, 0x0($sp)
  addiu      $sp, $sp, 0x8
  jr         $ra
   nop
endlabel func_hd_code_802A5020

/* Proposed name: setupCellTextureAnim
 * Looks up the texture animation record (header a0, record range at offsets
 * 0x2C/0x30) whose id (word 0x0) matches the cell record's material id in
 * t4, and stages its state into globals for the DL patcher: current frame's
 * texture pointer into D_hd_code_803C3240, next frame's texture pointer into
 * D_hd_code_803C3244, blend flag into D_hd_code_803C324A and blend factor
 * into D_hd_code_803C324B. Returns 1 in gp if the DL needs animation
 * patching, 0 if not animated (no match, frame 0 without blending).
 */
glabel func_hd_code_802A50DC
  addiu      $sp, $sp, -0x28
  sd         $ra, 0x0($sp)
  sd         $v0, 0x8($sp)
  sd         $v1, 0x10($sp)
  sd         $a1, 0x18($sp)
  sd         $a2, 0x20($sp)
  lw         $v0, 0x2C($a0)
  lw         $v1, 0x30($a0)
  addu       $v0, $v0, $a0
  addu       $v1, $v1, $a0
  .Lhd_code_802A5104:
  beq        $v0, $v1, .Lhd_code_802A51DC
   nop
  lw         $a1, 0x0($v0)
  beq        $a1, $t4, .Lhd_code_802A512C
   nop
  lbu        $a2, 0x4($v0)
  sll        $a2, $a2, 2
  addu       $v0, $v0, $a2
  b          .Lhd_code_802A5104
   addi      $v0, $v0, 0x8 /* handwritten instruction */
  .Lhd_code_802A512C:
  lbu        $a2, 0x5($v0)
  beqz       $a2, .Lhd_code_802A5158
   nop
  sll        $a1, $a2, 2
  addu       $a1, $a1, $v0
  addi       $a1, $a1, 0x8 /* handwritten instruction */
  lw         $a1, 0x0($a1)
  lui        $v1, %hi(D_hd_code_803C3240)
  addiu      $v1, $v1, %lo(D_hd_code_803C3240)
  b          .Lhd_code_802A5164
   sw        $a1, 0x0($v1)
  .Lhd_code_802A5158:
  lui        $v1, %hi(D_hd_code_803C3240)
  addiu      $v1, $v1, %lo(D_hd_code_803C3240)
  sw         $zero, 0x0($v1)
  .Lhd_code_802A5164:
  lbu        $v1, 0x6($v0)
  lui        $gp, %hi(D_hd_code_803C324A)
  addiu      $gp, $gp, %lo(D_hd_code_803C324A)
  bnez       $v1, .Lhd_code_802A5188
   sb        $v1, 0($gp)
  beqz       $a2, .Lhd_code_802A51DC
   nop
  b          .Lhd_code_802A51E0
   addiu     $gp, $zero, 0x1
  .Lhd_code_802A5188:
  lbu        $v1, 0x4($v0)
  addi       $a2, $a2, 0x1 /* handwritten instruction */
  bne        $v1, $a2, .Lhd_code_802A51A8
   nop
  lui        $v1, %hi(D_hd_code_803C3244)
  addiu      $v1, $v1, %lo(D_hd_code_803C3244)
  b          .Lhd_code_802A51C4
   sw        $zero, 0x0($v1)
  .Lhd_code_802A51A8:
  sll        $a1, $a2, 2
  addu       $a1, $a1, $v0
  addi       $a1, $a1, 0x8 /* handwritten instruction */
  lw         $a1, 0x0($a1)
  lui        $v1, %hi(D_hd_code_803C3244)
  addiu      $v1, $v1, %lo(D_hd_code_803C3244)
  sw         $a1, 0x0($v1)
  .Lhd_code_802A51C4:
  lbu        $a1, 0x7($v0)
  lui        $v1, %hi(D_hd_code_803C324B)
  addiu      $v1, $v1, %lo(D_hd_code_803C324B)
  addiu      $gp, $zero, 0x1
  b          .Lhd_code_802A51E0
   sb        $a1, 0x0($v1)
  .Lhd_code_802A51DC:
  addiu      $gp, $zero, 0x0
  .Lhd_code_802A51E0:
  ld         $ra, 0x0($sp)
  ld         $v0, 0x8($sp)
  ld         $v1, 0x10($sp)
  ld         $a1, 0x18($sp)
  ld         $a2, 0x20($sp)
  jr         $ra
   addiu     $sp, $sp, 0x28
endlabel func_hd_code_802A50DC

/* Proposed name: copyCellDLPatchTexAnim
 * Copies a cell's display list (t5 to t6, offsets relative to base a0) into
 * the output DL at a1 as raw 8-byte commands. If gp is set (animation staged
 * by func_hd_code_802A50DC), patches the copied commands in place: the first
 * G_SETTIMG (opcode 0xFD) gets the current frame's texture address
 * (D_hd_code_803C3240); if the blend flag D_hd_code_803C324A is set, the
 * second G_SETTIMG gets the next frame's address (D_hd_code_803C3244) and
 * the following G_SETPRIMCOLOR (opcode 0xFA) gets the crossfade factor
 * (D_hd_code_803C324B) OR'd into its alpha for frame blending.
 */
glabel func_hd_code_802A51FC
  addiu      $sp, $sp, -0x18
  sd         $a2, 0x10($sp)
  sd         $ra, 0x0($sp)
  sd         $v0, 0x8($sp)
  or         $a2, $a1, $zero
  add        $t5, $t5, $a0 /* handwritten instruction */
  add        $t6, $t6, $a0 /* handwritten instruction */
  .Lhd_code_802A5218:
  beq        $t5, $t6, .Lhd_code_802A5234
   nop
  ld         $v0, 0x0($t5)
  addi       $t5, $t5, 0x8 /* handwritten instruction */
  addi       $a1, $a1, 0x8 /* handwritten instruction */
  b          .Lhd_code_802A5218
   sd        $v0, -0x8($a1)
  .Lhd_code_802A5234:
  beqz       $gp, .Lhd_code_802A5320
   nop
  lui        $gp, %hi(D_hd_code_803C3240)
  addiu      $gp, $gp, %lo(D_hd_code_803C3240)
  lw         $gp, 0($gp)
  addiu      $sp, $sp, -0x10
  sd         $a3, 0x8($sp)
  sd         $ra, 0x0($sp)
  lui        $a3, (0xFF000000 >> 16)
  .Lhd_code_802A5258:
  lw         $v0, 0x0($a2)
  addiu      $at, $zero, 0xFD
  addi       $a2, $a2, 0x8 /* handwritten instruction */
  and        $v0, $v0, $a3
  srl        $v0, $v0, 24
  bne        $v0, $at, .Lhd_code_802A5258
   nop
  beqz       $gp, .Lhd_code_802A5280
   nop
  sw         $gp, -0x4($a2)
  .Lhd_code_802A5280:
  lui        $gp, %hi(D_hd_code_803C324A)
  addiu      $gp, $gp, %lo(D_hd_code_803C324A)
  lbu        $gp, 0($gp)
  ld         $ra, 0x0($sp)
  ld         $a3, 0x8($sp)
  beqz       $gp, .Lhd_code_802A5320
   addiu     $sp, $sp, 0x10
  lui        $gp, (0xFF000000 >> 16)
  .Lhd_code_802A52A0:
  lw         $v0, 0x0($a2)
  addiu      $at, $zero, 0xFD
  addi       $a2, $a2, 0x8 /* handwritten instruction */
  and        $v0, $v0, $gp
  srl        $v0, $v0, 24
  bne        $v0, $at, .Lhd_code_802A52A0
   nop
  lui        $gp, %hi(D_hd_code_803C3244)
  addiu      $gp, $gp, %lo(D_hd_code_803C3244)
  lw         $gp, 0($gp)
  beqz       $gp, .Lhd_code_802A52D4
   nop
  sw         $gp, -0x4($a2)
  .Lhd_code_802A52D4:
  addiu      $sp, $sp, -0x10
  sd         $ra, 0x0($sp)
  sd         $a3, 0x8($sp)
  lui        $gp, (0xFF000000 >> 16)
  .Lhd_code_802A52E4:
  lw         $v0, 0x0($a2)
  addiu      $at, $zero, 0xFA
  addi       $a2, $a2, 0x8 /* handwritten instruction */
  and        $a3, $v0, $gp
  srl        $a3, $a3, 24
  bne        $a3, $at, .Lhd_code_802A52E4
   nop
  lui        $gp, %hi(D_hd_code_803C324B)
  addiu      $gp, $gp, %lo(D_hd_code_803C324B)
  lbu        $gp, 0($gp)
  or         $v0, $v0, $gp
  sw         $v0, -0x8($a2)
  ld         $a3, 0x8($sp)
  ld         $ra, 0x0($sp)
  addiu      $sp, $sp, 0x10
  .Lhd_code_802A5320:
  ld         $ra, 0x0($sp)
  ld         $v0, 0x8($sp)
  ld         $a2, 0x10($sp)
  jr         $ra
   addiu     $sp, $sp, 0x18
endlabel func_hd_code_802A51FC

/* Proposed name: emitMultiCellDLs
 * Second pass over the multi-cell geometry records (t8 to t9, variable-size
 * records with a sorted cell index array), called from
 * func_hd_code_802A4E4C. For each record spanning at least one visible cell
 * (intersection test of its index array against the sorted visible list
 * D_hd_code_803C30A8) whose material id (0xC) was NOT already emitted (not
 * present in the drawn-id list ending at v1, D_hd_code_803C2EB0): stages its
 * texture animation, copies its DL (offset 0x0, or the alternate DL at 0x4
 * for id -2) into the output at a1, and applies the same G_SETTIMG /
 * G_SETPRIMCOLOR animation patching as func_hd_code_802A51FC.
 */
glabel func_hd_code_802A5334
  addiu      $sp, $sp, -0x8
  sd         $ra, 0x0($sp)
  addiu      $t0, $zero, -0x2
  .Lhd_code_802A5340:
  beq        $t8, $t9, .Lhd_code_802A54F4
   nop
  lui        $t2, %hi(D_hd_code_803C30A8)
  lw         $t1, 0x10($t8)
  addi       $t4, $t8, 0x14 /* handwritten instruction */
  addiu      $t2, $t2, %lo(D_hd_code_803C30A8)
  .Lhd_code_802A5358:
  lh         $t3, 0x0($t2)
  addiu      $at, $zero, -0x1
  beq        $t3, $at, .Lhd_code_802A54E4
   nop
  addi       $t2, $t2, 0x2 /* handwritten instruction */
  or         $t5, $t4, $zero
  or         $t6, $t1, $zero
  .Lhd_code_802A5374:
  beqz       $t6, .Lhd_code_802A5358
   nop
  lw         $t7, 0x0($t5)
  beq        $t7, $t3, .Lhd_code_802A539C
   slt       $at, $t3, $t7
  bnez       $at, .Lhd_code_802A5358
   nop
  addi       $t5, $t5, 0x4 /* handwritten instruction */
  b          .Lhd_code_802A5374
   addi      $t6, $t6, -0x1 /* handwritten instruction */
  .Lhd_code_802A539C:
  lui        $t3, %hi(D_hd_code_803C2EB0)
  lw         $t2, 0xC($t8)
  addiu      $t3, $t3, %lo(D_hd_code_803C2EB0)
  .Lhd_code_802A53A8:
  beq        $t3, $v1, .Lhd_code_802A53D0
   nop
  lh         $t4, 0x0($t3)
  slt        $at, $t2, $t4
  bnez       $at, .Lhd_code_802A53D0
   nop
  beq        $t4, $t2, .Lhd_code_802A54E4
   addi      $t3, $t3, 0x2 /* handwritten instruction */
  b          .Lhd_code_802A53A8
   nop
  .Lhd_code_802A53D0:
  bne        $t2, $t0, .Lhd_code_802A53E8
   nop
  lw         $t3, 0x4($t8)
  addiu      $v0, $zero, 0x0
  b          .Lhd_code_802A53F4
   addu      $t3, $t3, $a0
  .Lhd_code_802A53E8:
  lw         $t3, 0x0($t8)
  or         $v0, $a1, $zero
  addu       $t3, $t3, $a0
  .Lhd_code_802A53F4:
  or         $t0, $t2, $zero
  jal        func_hd_code_802A50DC
   or        $t4, $t0, $zero
  lw         $t4, 0x8($t8)
  addu       $t4, $t4, $a0
  .Lhd_code_802A5408:
  beq        $t3, $t4, .Lhd_code_802A5424
   nop
  ld         $t5, 0x0($t3)
  addi       $t3, $t3, 0x8 /* handwritten instruction */
  addi       $a1, $a1, 0x8 /* handwritten instruction */
  b          .Lhd_code_802A5408
   sd        $t5, -0x8($a1)
  .Lhd_code_802A5424:
  beqz       $gp, .Lhd_code_802A54E4
   nop
  beqz       $v0, .Lhd_code_802A54E4
   nop
  lui        $gp, %hi(D_hd_code_803C3240)
  addiu      $gp, $gp, %lo(D_hd_code_803C3240)
  lw         $gp, 0($gp)
  lui        $t5, (0xFF000000 >> 16)
  .Lhd_code_802A5444:
  lw         $a2, 0x0($v0)
  addiu      $at, $zero, 0xFD
  addi       $v0, $v0, 0x8 /* handwritten instruction */
  and        $a2, $a2, $t5
  srl        $a2, $a2, 24
  bne        $a2, $at, .Lhd_code_802A5444
   nop
  beqz       $gp, .Lhd_code_802A546C
   nop
  sw         $gp, -0x4($v0)
  .Lhd_code_802A546C:
  lui        $gp, %hi(D_hd_code_803C324A)
  addiu      $gp, $gp, %lo(D_hd_code_803C324A)
  lbu        $gp, 0($gp)
  beqz       $gp, .Lhd_code_802A54E4
   nop
  .Lhd_code_802A5480:
  lw         $a2, 0x0($v0)
  addiu      $at, $zero, 0xFD
  addi       $v0, $v0, 0x8 /* handwritten instruction */
  and        $a2, $a2, $t5
  srl        $a2, $a2, 24
  bne        $a2, $at, .Lhd_code_802A5480
   nop
  lui        $gp, %hi(D_hd_code_803C3244)
  addiu      $gp, $gp, %lo(D_hd_code_803C3244)
  lw         $gp, 0($gp)
  beqz       $gp, .Lhd_code_802A54B4
   nop
  sw         $gp, -0x4($v0)
  .Lhd_code_802A54B4:
  lw         $a2, 0x0($v0)
  addiu      $at, $zero, 0xFA
  addi       $v0, $v0, 0x8 /* handwritten instruction */
  and        $gp, $a2, $t5
  srl        $gp, $gp, 24
  bne        $gp, $at, .Lhd_code_802A54B4
   nop
  lui        $gp, %hi(D_hd_code_803C324B)
  addiu      $gp, $gp, %lo(D_hd_code_803C324B)
  lbu        $gp, 0($gp)
  or         $a2, $a2, $gp
  sw         $a2, -0x8($v0)
  .Lhd_code_802A54E4:
  sll        $t1, $t1, 2
  addi       $t1, $t1, 0x14 /* handwritten instruction */
  b          .Lhd_code_802A5340
   addu      $t8, $t8, $t1
  .Lhd_code_802A54F4:
  ld         $ra, 0x0($sp)
  addiu      $sp, $sp, 0x8
  jr         $ra
   nop
endlabel func_hd_code_802A5334
  nop
  nop
  nop
