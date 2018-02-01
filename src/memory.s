#include <asm.h>
.align 2


THUMB_FUNC memset
    .memset_byte:
        lsl r3, r2, #30
        lsr r3, r3, #30
        beq .memset_native
        sub r2, r2, #1
        strb r1, [r0, r2]
        b .memset_byte
    .memset_native:
        sub r2, r2, #4
        bmi 1f
        str r1, [r0, r2]
        b .memset_native
    1: bx lr


THUMB_FUNC memcpy
    .memcpy_byte:
        lsl r3, r2, #30
        lsr r3, r3, #30
        beq .memcpy_native
        sub r2, r2, #1
        ldrb r3, [r1, r2]
        strb r3, [r0, r2]
        b .memcpy_byte
    .memcpy_native:
        sub r2, r2, #4
        bmi 1f
        ldr r3, [r1, r2]
        str r3, [r0, r2]
        b .memcpy_native
    1: bx lr


THUMB_FUNC strcpy
    mov r2, #0
    1:
        ldrb r3, [r1, r2]
        strb r3, [r0, r2]
        add r2, r2, #1
        cmp r3, #0
        bne 1b
    bx lr
