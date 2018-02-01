#include <asm.h>
.align 2


@ TODO
ARM_FUNC _svc
    @ Guardo el estado del usuario
    msr cpsr_c, #(SR_SYS | SR_NOIRQ | SR_NOFIQ)
    push {r0-r12, lr}
    mov r0, sp
    msr cpsr_c, #(SR_SVC | SR_NOIRQ | SR_NOFIQ)

    mrs r12, spsr
    stmfd r0!, {r12, lr}

    @ Cargo el estado del kernel
    pop {r4-r12, lr}
    mov sp, r12

    bx lr


@ uint32_t *task_run(uint32_t *task_stack)
ARM_FUNC task_run
    @ Guardo el estado del kernel
    mov r12, sp
    push {r4-r12, lr}

    @ Cargo el estado del usuario
    ldmfd r0!, {r12, lr}
    msr spsr, r12

    msr cpsr_c, #(SR_SYS | SR_NOIRQ | SR_NOFIQ)
    mov sp, r0
    pop {r0-r12, lr}
    msr cpsr_c, #(SR_SVC | SR_NOIRQ | SR_NOFIQ)

    movs pc, lr
