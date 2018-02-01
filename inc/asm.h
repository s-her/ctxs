/*
 Definiciones de plataforma, para ser incluidas por el ensamblador
*/

#pragma once

// Bits del Status Register
#define SR_PMASK (0x0F)
#define SR_USR   (0x10)
#define SR_FIQ   (0x11)
#define SR_IRQ   (0x12)
#define SR_SVC   (0x13)
#define SR_ABT   (0x17)
#define SR_UND   (0x1B)
#define SR_SYS   (0x1F)

#define SR_THUMB (1 << 5)
#define SR_NOFIQ (1 << 6)
#define SR_NOIRQ (1 << 7)

#ifdef __ASSEMBLER__
.macro ARM_FUNC f
    .arm
    .align 2
    .section .text.\f, "ax", %progbits

    .global \f
    .type \f, %function
\f:
.endm

.macro THUMB_FUNC f
    .thumb
    .align 1
    .section .text.\f, "ax", %progbits

    .global \f
    .type \f, %function
\f:
.endm

.macro NOP_SLED c
    .rept \c
    mov r0, r0
    .endr
.endm
#endif
