#include <common.h>

static const char _ntos_chr[] =
{'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

static char *
ntos(uint32_t n, char *s, int base)
{
    int len;
    if (base < 2 || base > 16)
        return s;
    len = 0;
    do {
        s[len++] = _ntos_chr[n % base];
        n /= base;
    } while(n != 0);
    for (int i = 0; i < len/2; i++) {
        char t = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = t;
    }
    s[len] = 0;
    return s + len;
}

int
sprintf(char *str, const char *fmt, ...)
{
    char p, *s = str;
    va_list va;

    va_start(va, fmt);
    while(*fmt) {
        p = *fmt++;
        if (p != '%') {
            *s++ = p;
        } else {
            p = *fmt++;
            switch(p) {
                case 'b':
                    s = ntos(va_arg(va, uint32_t), s, 2);
                    break;
                case 'd':
                    s = ntos(va_arg(va, uint32_t), s, 10);
                    break;
                case 'x':
                    s = ntos(va_arg(va, uint32_t), s, 16);
                    break;
                case 's':
                    strcpy(s, va_arg(va, const char*));
                    break;
                default:
                    *s++ = '%';
                    break;
            }
        }
        while(*s)
            s++;
    }

    va_end(va);
    return s - str;
}
