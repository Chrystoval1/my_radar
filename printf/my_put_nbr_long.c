/*
** EPITECH PROJECT, 2024
** my_put_nbr
** File description:
** put a number
*/

#include "my.h"
long my_put_nbr_long(long nb)
{
    long i;

    if (nb < 0){
        my_putchar('-');
        nb = nb * (-1);
    }
    if (nb == 0){
        my_putchar('0');
        return (0);
    }
    if (nb >= 10) {
        i = nb % 10;
        nb = nb / 10;
        my_put_nbr_long(nb);
        my_putchar(i + 48);
    } else {
        my_putchar(nb + 48);
        }
    return (0);
}
