/*
** EPITECH PROJECT, 2024
** my_put_nbr.c
** File description:
** printing the value inserted as parameter
** using my_putchart
*/
#include "my.h"

int calc(int nb, int f)
{
    int i = 0;
    int mem = 0;

    while (f != 0){
        mem = (nb / f) % 10;
        my_putchar(mem + '0');
        f = f / 10;
        i++;
    }
    return i;
}

int my_put_nbr(int nb)
{
    int f = 1;

    if (nb < 0) {
        my_putchar('-');
        nb = nb * (-1);
    }
    if (nb == 0) {
        my_putchar('0');
        return 0;
    }
    while (nb / f >= 10) {
        f = f * 10;
    }
    calc(nb, f);
}
