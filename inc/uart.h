/*
 E/S serial
*/

#pragma once

#include <common.h>

#define UART_BASE (0x16000000)

#define REG_UART_TXRX   ((volatile uint32_t*)(UART_BASE + 0x00))
#define REG_UART_STATUS ((volatile uint32_t*)(UART_BASE + 0x18))

#define UART_TX_FULL  (1 << 5)
#define UART_RX_EMPTY (1 << 4)

void uart_putc(char c);
char uart_getc(void);
void uart_puts(const char *s);
size_t uart_gets(char *s, size_t n);
