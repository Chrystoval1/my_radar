/*
** EPITECH PROJECT, 2024
** my_putstr.c
** File description:
** display evey charater one by one
*/
#include "my.h"

int my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        my_putchar(str[i]);
        i += 1;
    }
}
