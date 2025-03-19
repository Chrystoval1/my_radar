/*
** EPITECH PROJECT, 2024
** my_getnbr
** File description:
** print every number until n
*/
#include "../include/my.h"

void calc_nb(char to_find, int *nbr)
{
    char nb = 48;

    if (to_find == '1') {
        *nbr += 1;
        return;
    }
    while (nb <= to_find - 1) {
        nb++;
        *nbr += 1;
    }
    nb = 48;
}

int my_getnbr(char const *str)
{
    int nbr = 0;
    int i = 0;

    while (str[i] == '-')
        i++;
    while (str[i] >= '0' && str[i] <= '9') {
        if (str[i] >= '0' && str[i] <= '9') {
            calc_nb(str[i], &nbr);
        }
        if (str[i + 1] <= '9' && str[i + 1] >= '0') {
            nbr = nbr * 10;
        }
        i++;
    }
    return nbr;
}
