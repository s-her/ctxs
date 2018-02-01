#include <common.h>
#include <asm.h>
#include <arm.h>
#include <task.h>
#include <uart.h>

static inline void
yield(void)
{
    __asm__ __volatile__ ("svc #0\n\t" : : : "memory");
    return;
}

void
task(int id, void *arg)
{
    char str[32] = {0};
    sprintf(str, "tarea numero %d!\n", id);

    while(1) {
        uart_puts(str);
        yield();
    }
}

void
kernel_main(void)
{
    static uint32_t _stacks[32 * 1024];
    task_init();

    for (int i = 0; i < 32; i++) {
        task_register(&task, &_stacks[(i+1)*1024], SR_SYS | SR_NOFIQ | SR_NOIRQ, NULL);
    }

    while(1) {
        task_schedule();
    }
}
