#include <stdio.h>
#include <string.h>
#include "myprint.h"
#include <stdarg.h>

int myprint(const char *str, ...) {
    va_list args;
    va_start(args, str);
    int num = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '&') {
            num++;
        }
    }
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (c != '&') {
            fputc(c, stdout);
        }
        else if (c == '&') {
            printf("%d", va_arg(args, int));
        }
    }
    va_end(args);
    return num;
}