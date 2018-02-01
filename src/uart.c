#include <common.h>
#include <uart.h>

void
uart_putc(char c)
{
    while(*REG_UART_STATUS & UART_TX_FULL);
    *REG_UART_TXRX = c;
    if (c == '\r') uart_putc('\n');
    return;
}

char
uart_getc(void)
{
    while(*REG_UART_STATUS & UART_RX_EMPTY);
    return *REG_UART_TXRX;
}

void
uart_puts(const char *s)
{
    while(*s) {
        uart_putc(*s);
        s++;
    }
    return;
}

size_t
uart_gets(char *s, size_t n)
{
    size_t l = 0;
    while(l < n) {
        s[l] = uart_getc();
        if (!s[l]) break;
        l++;
    }
    return l;
}
