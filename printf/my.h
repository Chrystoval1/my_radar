/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** includes every definitions of functions to avoid useless warnings
*/
#include <stdarg.h>
#include "flags.h"
#ifndef MY_H_
    #define MY_H_

void my_putchar(char c);
int my_isneg(int nb);
int my_put_nbr(int nb);
void my_swap(int *a, int *b);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_getnbr(char const *str);
void my_sort_int_array(int *tab, int size);
int my_compute_power_rec(int nb, int power);
int my_compute_square_root(int nb);
int my_is_prime(int nb);
int my_find_prime_sup(int nb);
char *my_strcpy(char *dest, char const *str);
char *my_strncpy(char *dest, char const *str, int n);
char *my_revstr(char *str);
char *my_strstr(char *str, char const *to_find);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strlowcase(char *str);
char *my_strupcase(char *str);
char *my_strcapitalize(char *str);
int my_isalpha(char const *str);
int my_isnum(char const *str);
int my_islower(char const *str);
int my_isprintable(char const *str);
int my_isupper(char const *str);
int my_showstr(char const *str);
int my_showmem(char const *str, int size);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int nb);
char *my_strdup(char const *src);
char *concat_params(int argc, char **argv);
int my_show_word_array(char *const *tab);
int my_printf(const char *format, ...);
int handle_format(const char *format, va_list list, int *i);
int handle_convert(char flag, va_list list, format_flag_t *flags);
static int nb_len(long long nb, int initial_len);
int my_putnbr_base(long nbr, char const *base);
long my_put_float(double nb, int precision);
int char_in_str(char flag, char *str);
long my_compute_power_rec_long(long nb, long power);
int handle_basic(char flag, va_list, format_flag_t *flags);
int put_number(long long nb, char *base, format_flag_t *flags, char flag);
long my_put_nbr_long(long nb);

#endif
