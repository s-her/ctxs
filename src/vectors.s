#include <asm.h>
.align 2
.arm

@ TODO

.section .vectors, "ax"
.global vectors_start
vectors_start:
    ldr pc, =_reset
    ldr pc, =_undef
    ldr pc, =_svc
    ldr pc, =_pabt
    ldr pc, =_dabt
    ldr pc, =_resv
    ldr pc, =_irq
    ldr pc, =_fiq
    .pool

ARM_FUNC _reset
    ldr r0, =_reset_str
    bl uart_puts
    b .

ARM_FUNC _undef
    ldr r0, =_undef_str
    bl uart_puts
    b .

ARM_FUNC _pabt
    ldr r0, =_pabt_str
    bl uart_puts
    b .

ARM_FUNC _dabt
    ldr r0, =_dabt_str
    bl uart_puts
    b .

ARM_FUNC _resv
    ldr r0, =_resv_str
    bl uart_puts
    b .

ARM_FUNC _irq
    ldr r0, =_irq_str
    bl uart_puts
    b .

ARM_FUNC _fiq
    ldr r0, =_fiq_str
    bl uart_puts
    b .

.section .rodata.abort_strings
_reset_str: .asciz "reset"
_undef_str: .asciz "undefined"
_svc_str:   .asciz "svc"
_pabt_str:  .asciz "prefetch"
_dabt_str:  .asciz "data"
_resv_str:  .asciz "reserved"
_irq_str:   .asciz "irq"
_fiq_str:   .asciz "fiq"
