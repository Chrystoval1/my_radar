/*
** EPITECH PROJECT, 2024
** my_strlen
** File description:
** give the lenght of a character string
*/
int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        i += 1;
    }
    return i;
}
