/*
** EPITECH PROJECT, 2024
** include/struct
** File description:
** file containing definition of structures
*/

#include "SFML/Graphics/CircleShape.h"
#include "SFML/Graphics/Types.h"
#include "SFML/System/Types.h"
#include "SFML/System/Vector2.h"
#include "SFML/Window/Types.h"
#include <SFML/Graphics.h>

#ifndef STRUCT_H_
    #define STRUCT_H_

typedef struct {
    char *line;
    int pos;
} parser_t;

typedef struct {
    sfRectangleShape *sprite;
    sfVector2f start;
    sfVector2f end;
    sfVector2f current;
    float speed;
    int delay;
    int safe;
    int counted;
    int completed;
    int destroyed;
} aircraft_t;

typedef struct {
    sfCircleShape *shape;
    sfVector2f position;
    int radius;
} control_tower_t;

typedef struct {
    aircraft_t **aircrafts;
    control_tower_t towers[100];
    int num_aircrafts;
    int num_towers;
    sfTexture* background_texture;
    sfSprite* background_sprite;
    sfRenderWindow *window;
    int count;
    int final_count;
    int hitboxes;
    sfClock *clock;
    int show;
} entities_t;

#endif
