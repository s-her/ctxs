/*
 Definiciones de plataforma
*/

#pragma once

#include <common.h>

uint32_t _enter_critical(void);
void _leave_critical(uint32_t cs);
