/*
** EPITECH PROJECT, 2024
** my_compute_power_rec
** File description:
** my_compute_power_rec
*/

#include "my.h"

long my_compute_power_rec_long(long nb, long power)
{
    if (power == 0) {
        return (1);
    }
    if (power < 0){
        return (0);
    }
    return (nb * my_compute_power_rec_long(nb, power - 1));
}
