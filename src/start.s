#include <asm.h>
.align 2


@ TODO
ARM_FUNC start
    msr cpsr_c, #(SR_SVC | SR_NOIRQ | SR_NOFIQ)
    ldr sp, =_stack_top

    ldr r0, =_vectors_s
    ldr r1, =_vectors_lma
    ldr r2, =_vectors_l
    bl memcpy

    ldr r0, =_bss_s
    ldr r1, =0x00000000
    ldr r2, =_bss_l
    bl memset

    ldr pc, =kernel_main
