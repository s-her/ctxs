#include <asm.h>
#include <common.h>
#include <task.h>


#define MAX_TASKS (32)
static struct task_t {
    int id;
    int state;
    uint32_t *regs;
    char name[20];
} tasks[MAX_TASKS];
static int current_tid, task_count;

uint32_t *task_run(uint32_t *task_stack);

static inline int
task_find(int id, int state)
{
    id %= MAX_TASKS;
    while(tasks[id].state != state) {
        id++;
        id %= MAX_TASKS;
    }
    return id;
}

void
task_init(void)
{
    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].id = -1;
        tasks[i].regs = NULL;
        tasks[i].state = TASK_INACTIVE;
    }
    current_tid = -1;
    task_count = 0;
    return;
}

int
task_kill(int id)
{
    if (id >= MAX_TASKS)
        return -1;

    tasks[id].id = -1;
    tasks[id].regs = NULL;
    tasks[id].state = TASK_INACTIVE;
    task_count--;
    return id;
}

void
task_schedule(void)
{
    current_tid = task_find(current_tid + 1, TASK_ACTIVE);
    tasks[current_tid].regs = task_run(tasks[current_tid].regs);
}

int
task_register(task_f entry, uint32_t *stack_top, uint32_t psr, void *arg)
{
    int id;
    if (task_count >= MAX_TASKS)
        return -1;

    id = task_find(task_count, TASK_INACTIVE);

    // Thumb hack
    if ((uintptr_t)entry & 1)
        psr |= SR_THUMB;

    stack_top -= 16;
    stack_top[0] = psr;
    stack_top[1] = (uint32_t)entry;
    stack_top[2] = (uint32_t)id;
    stack_top[3] = (uint32_t)arg;

    tasks[id].id = id;
    tasks[id].regs = stack_top;
    tasks[id].state = TASK_ACTIVE;
    task_count++;
    return id;
}
