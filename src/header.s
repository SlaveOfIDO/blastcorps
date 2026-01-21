.section .data

.word 0x80371240       /* PI BSB Domain 1 register */
.word 0x0000000F       /* Clockrate setting */
.word 0x8021ED00       /* Entrypoint address */
.word 0x00001444       /* Revision */
.word 0x7C647E65       /* Checksum 1 */
.word 0x1948D305       /* Checksum 2 */
.word 0x00000000       /* Unknown 1 */
.word 0x00000000       /* Unknown 2 */
.ascii "Blast Corps         " /* Internal name */
.word 0x00000000       /* Unknown 3 */
.word 0x0000004E       /* Cartridge */
.ascii "BC"            /* Cartridge ID */
.ascii "E"             /* Country code */
.byte 0x01             /* Version */
