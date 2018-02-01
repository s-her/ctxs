/*
 Definiciones comunes al kernel
*/

#pragma once

#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <stdint.h>

void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
char *strcpy(char *dest, const char *src);
int  sprintf(char *str, const char *fmt, ...);

#define POWER_OF_TWO(x)  (((x) & ((x)-1)) == 0)

#define BIT(x)           (1 << (x))
