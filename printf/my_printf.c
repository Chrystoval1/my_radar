/*
** EPITECH PROJECT, 2024
** my_printf.c
** File description:
** main function of the project printf
*/
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include "flags.h"
#include "my.h"
#include <unistd.h>
#include <stdio.h>

int my_printf(const char *format, ...)
{
    va_list list;
    int res = 0;
    int i = 0;

    if (format == NULL)
        return 0;
    va_start(list, format);
    while (format[i] != '\0') {
        if (format[i] == '%') {
            i++;
            res = res + handle_format(format, list, &i);
        } else {
            my_putchar(format[i]);
            i++;
        }
    }
    va_end(list);
    return res;
}

static format_flag_t *init_flags(void)
{
    format_flag_t *flags = malloc(sizeof(format_flag_t));

    flags->flag = 0;
    flags->width = 0;
    flags->lenght = 0;
    flags->precision = -1;
    return flags;
}

int precision_width(char const *format, int *i, format_flag_t *flags)
{
    while (format[*i] <= '9' && format[*i] >= '0') {
        flags->width = flags->width * 10 + (format[*i] - '0');
        *i += 1;
    }
    if (format[*i] == '.') {
        flags->precision = 0;
        *i += 1;
    }
    if (format[*i] == '-')
        return 0;
    while (format[*i] >= '0' && format[*i] <= '9') {
        flags->precision = flags->precision * 10 + (format[*i] - '0');
        *i += 1;
    }
}

int handle_format(const char *format, va_list list, int *i)
{
    format_flag_t *flags = init_flags();
    int res = 0;

    if (char_in_str(format[*i], "#0- +") == 1) {
            flags->flag = format[*i];
            *i += 1;
    }
    precision_width(format, i, flags);
    if (char_in_str(format[*i], "lh") == 1) {
            flags->flag = format[*i];
            *i += 1;
    }
    res = res + handle_convert(format[*i], list, flags);
    *i += 1;
    free(flags);
    return res;
}
