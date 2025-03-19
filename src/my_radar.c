/*
** EPITECH PROJECT, 2024
** src/my_radar
** File description:
** Main file for the project my_radar
*/


#include "../include/my.h"

aircraft_t *create_plane(sfTexture *texture, sfVector2f pos, sfVector2f dest,
    float speed)
{
    aircraft_t *plane = malloc(sizeof(aircraft_t));

    plane->sprite = sfRectangleShape_create();
    sfRectangleShape_setTexture(plane->sprite, texture, sfTrue);
    sfRectangleShape_setSize(plane->sprite, (sfVector2f){20, 20});
    plane->start = pos;
    plane->end = dest;
    plane->speed = speed;
    plane->safe = 0;
    return plane;
}

control_tower_t *create_tower(sfVector2f pos, float radius)
{
    control_tower_t *tower = malloc(sizeof(control_tower_t));

    tower->shape = sfCircleShape_create();
    sfCircleShape_setPosition(tower->shape, pos);
    sfCircleShape_setRadius(tower->shape, radius);
    return tower;
}

void create_window(entities_t *entities)
{
    sfVideoMode mode = {1920, 1080, 32};

    entities->window = sfRenderWindow_create(mode, "my_radar",
        sfResize | sfClose, NULL);
    sfRenderWindow_setFramerateLimit(entities->window, 60);
}

static int init_background(entities_t *entities)
{
    create_window(entities);
    entities->background_texture =
        sfTexture_createFromFile("./assets/background.png", NULL);
    if (!entities->background_texture)
        return 84;
    entities->background_sprite = sfSprite_create();
    sfSprite_setTexture(entities->background_sprite,
        entities->background_texture, sfTrue);
    return 0;
}

int display_usage(void)
{
    my_printf("Air traffic simulation panel\n"
            "USAGE:\n"
            "./my_radar [OPTIONS] path_to_script\n[ESCAPE] to quit the game"
            "\n[L] to enable/disable hitboxes\n"
              "[S] to enable/disable planes/towers\n"
            "OPTIONS:\n"
            "-h print the usage and quit.\n");
    return 0;
}

int main(int argc, char **argv)
{
    entities_t *entities = malloc(sizeof(entities_t));

    if (argc != 2) {
        my_printf("./my_radar: bad arguments: %d given but 84 is required\n",
            argc - 1);
        return 84;
    }
    if (my_strcmp(argv[1], "-h") == 0)
        return display_usage();
    init_background(entities);
    if (!entities->window)
        return 84;
    if (load_script(argv[1], entities) == -1) {
        my_printf("./my_radar: bad filepath given"
            "or non-valid/corrupted file\n");
        return 84;
    }
    main_loop(entities->window, entities);
    return 0;
}
