/*
** EPITECH PROJECT, 2024
** include/my
** File description:
** include fie for function definition
*/

#ifndef MY_H_
    #define MY_H_

    #include <SFML/Graphics.h>
    #include <SFML/Window.h>
    #include <stdlib.h>
    #include <string.h>
    #include "struct.h"
    #include "SFML/Config.h"
    #include <SFML/System.h>
    #include <math.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

int my_getnbr(char const *str);
void main_loop(sfRenderWindow *window, entities_t *entities);
int load_script(const char *filepath, entities_t *entities);
int my_strcmp(char const *s1, char const *s2);
int my_printf(char const *format, ...);
void update_collisions(entities_t *entities);
void update_entities(entities_t *entities, float elapsed_time);

#endif
