/*
** EPITECH PROJECT, 2024
** my_put_float
** File description:
** put a decimal number
*/

#include "my.h"
#include <stdio.h>

double round_number(double nb, int precision)
{
    double i = 5;
    int a = 10;
    int count = 0;

    while (count != (precision + 1)) {
        i = i / a;
        count++;
        }
    nb = nb + i;
    return (nb);
}

long my_put_float(double nb, int precision)
{
    int p = 6;
    long a = 10;

    nb = round_number(nb, precision);
    my_put_nbr_long((long)nb);
    if (precision > 0 || precision == (-1)){
        my_putchar('.');
    }
    if (nb < 0) {
        nb = -nb;
    }
    if (precision == (-1)) {
        precision = p;
    }
    if (precision > 0) {
        nb = nb - (long)nb;
        nb = nb * my_compute_power_rec_long(a, precision);
    }
    if (precision > 0)
    my_put_nbr_long((long)nb);
}
