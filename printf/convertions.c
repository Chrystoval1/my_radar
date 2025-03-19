/*
** EPITECH PROJECT, 2024
** convertions.c
** File description:
** file that handles the convertions
*/
#include <stdarg.h>
#include <stdlib.h>
#include "my.h"
#include "flags.h"

static int condition(long nbr)
{
    if (nbr == 0) {
        my_putchar('0');
        return 1;
    }
    if (nbr < 0)
        nbr = - nbr;
    return 0;
}

int my_putnbr_base(long nbr, char const *base)
{
    int i = 0;
    char mem[33];
    int count;

    if (condition(nbr) == 1)
        return 1;
    if (my_strlen(base) < 2 || my_strlen(base) > 16)
        return 0;
    while (nbr != 0) {
        mem[i] = base[nbr % my_strlen(base)];
        nbr = nbr / my_strlen(base);
        i++;
    }
    mem[i] = '\0';
    count = i;
    while (i != 0) {
        i--;
        my_putchar(mem[i]);
    }
    return count;
}

static int nb_len(long long nb, int initial_len)
{
    int len = 1;

    if (nb < 0)
        nb = -nb;
    if (nb == 0)
        return 1;
    while (nb > initial_len) {
        nb = nb / initial_len;
        len++;
    }
    return len - 1;
}

static void padd(char flag, int len, char c, format_flag_t *flags)
{
    if (flags->flag == '#') {
        if (char_in_str(flag, "xXp") == 1)
            len += 2;
        if (flag == 'o')
            len += 1;
    }
    while (flags->width > len) {
        my_putchar(c);
        len++;
    }
    if (flags->flag == '#' && flag == 'o')
        my_putchar('0');
}

int put_number(long long nb, char *base, format_flag_t *flags, char flag)
{
    int len = nb_len(nb, my_strlen(base));
    char c = ' ';

    if (flags->flag == '0')
        c = '0';
    if (flags->width > len && flags->flag != '-')
        padd(flag, len, c, flags);
    if ((flags->flag == '#' && flag == 'x') || flag == 'p')
        my_putstr("0x");
    if (flags->flag == '#' && flag == 'X')
        my_putstr("0X");
    my_putnbr_base(nb, base);
    if (flags->width > len && flags->flag == '-')
        padd(flag, len, ' ', flags);
    if (flags->width > len)
        return flags->width;
    if (flags->width < len)
        return len;
}

int handle_convert(char flag, va_list list, format_flag_t *flags)
{
    if (char_in_str(flag, "diu") == 1)
        return put_number(va_arg(list, int), "0123456789", flags, flag);
    switch (flag){
    case 'x':
        return put_number(va_arg(list, int), "0123456789abcdef", flags, flag);
    case 'X':
        return put_number(va_arg(list, int), "0123456789ABCDEF", flags, flag);
    case 'p':
        return put_number(va_arg(list, long), "0123456789abcdef", flags, flag);
    case 'f':
        return my_put_float(va_arg(list, double), flags->precision);
    default:
        return handle_basic(flag, list, flags);
    }
}
