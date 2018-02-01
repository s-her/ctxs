/*
 Definiciones de tarea
*/
#pragma once

#include <common.h>

enum {
    TASK_INACTIVE,
    TASK_ACTIVE
};

typedef void (*task_f)(int, void*);

void task_init(void);
int  task_kill(int id);
void task_schedule(void);

int  task_register(task_f entry, uint32_t *stack_top, uint32_t psr, void *arg);
