/*
** EPITECH PROJECT, 2024
** handle_flags.c
** File description:
** file that handles every flag case called in the format
*/
#include <stdarg.h>
#include <stdlib.h>
#include "my.h"

int char_in_str(char flag, char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == flag)
            return 1;
    }
    return 0;
}

int print_str(char *src, format_flag_t *flags)
{
    int len = my_strlen(src);

    if (flags->precision >= 0 && flags->precision < len)
        len = flags->precision;
    for (int i = 0; i < len; i++)
        my_putchar(src[i]);
    return len;
}

int handle_basic(char flag, va_list list, format_flag_t *flags)
{
    switch (flag) {
    case 's':
        return print_str(va_arg(list, char *), flags);
    case 'c':
        my_putchar((char)va_arg(list, int));
        return 1;
    case 'o':
        return put_number(va_arg(list, int), "01234567", flags, flag);
    case '%':
        my_putchar('%');
        return 1;
    default:
        return 0;
    }
}

int handle_long_int(va_list list)
{
    long long int nb = va_arg(list, long long int);

    return my_putnbr_base(nb, "0123456789");
}
