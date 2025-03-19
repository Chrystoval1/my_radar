/*
** EPITECH PROJECT, 2024
** src/diplay
** File description:
** file where i dsplay teverything
*/

#include "../include/my.h"
#include "SFML/Graphics/RectangleShape.h"
#include "SFML/Graphics/Types.h"
#include "SFML/Window/Event.h"

static void hitbox(sfRectangleShape *plane, sfRenderWindow *window,
    entities_t *entities)
{
    if (entities->hitboxes != 0) {
        sfRectangleShape_setRotation(plane, 0);
        sfRectangleShape_setOutlineColor(plane, sfGreen);
        sfRectangleShape_setOutlineThickness(plane, 2);
        sfRectangleShape_setTexture(plane, NULL, sfTrue);
        sfRectangleShape_setFillColor(plane, sfTransparent);
        sfRenderWindow_drawRectangleShape(window, plane, NULL);
    }
    sfRectangleShape_setOutlineColor(plane, sfTransparent);
    sfRectangleShape_setOutlineThickness(plane, 0);
}

void rotate(entities_t *entities, sfRectangleShape *plane, int i,
    sfTexture *texture)
{
    float rotation;

    sfRectangleShape_setPosition(plane, (sfVector2f){
            entities->aircrafts[i]->current.x,
            entities->aircrafts[i]->current.y});
    rotation = atan2(entities->aircrafts[i]->end.y -
            entities->aircrafts[i]->start.y, entities->aircrafts[i]->end.x -
            entities->aircrafts[i]->start.x) * 180 / M_PI;
    sfRectangleShape_setRotation(plane, rotation);
    sfRectangleShape_setFillColor(plane, sfWhite);
    if (entities->show != 0)
        sfRectangleShape_setFillColor(plane, sfTransparent);
    sfRectangleShape_setTexture(plane, texture, sfTrue);
    sfRenderWindow_drawRectangleShape(entities->window, plane, NULL);
}

static void draw_aircrafts(sfRenderWindow *window, entities_t *entities)
{
    sfRectangleShape *plane = sfRectangleShape_create();
    sfTexture *texture = sfTexture_createFromFile("assets/plane.png", NULL);
    float scale = 0.05f;

    if (!plane || !texture)
        return;
    sfRectangleShape_setTexture(plane, texture, sfTrue);
    sfRectangleShape_setSize(plane, (sfVector2f){20, 20});
    sfRectangleShape_setOrigin(plane, (sfVector2f) {10, 10});
    for (int i = 0; i < entities->num_aircrafts; i++) {
        if (entities->aircrafts[i]->destroyed == 1 ||
            entities->aircrafts[i]->completed)
            continue;
        rotate(entities, plane, i, texture);
        hitbox(plane, window, entities);
    }
    sfRectangleShape_destroy(plane);
    sfTexture_destroy(texture);
}

static void draw_tower(entities_t *entities, sfRectangleShape *tower,
    sfCircleShape *radius, int i)
{
    sfRectangleShape_setOrigin(tower, (sfVector2f) {20, 20});
    sfRectangleShape_setPosition(tower, (sfVector2f){
        entities->towers[i].position.x,
        entities->towers[i].position.y});
    sfRenderWindow_drawRectangleShape(entities->window, tower, NULL);
    sfCircleShape_setRadius(radius, entities->towers[i].radius);
    sfCircleShape_setOrigin(radius, (sfVector2f){
        entities->towers[i].radius, entities->towers[i].radius});
    sfCircleShape_setPosition(radius, (sfVector2f){
        entities->towers[i].position.x,
        entities->towers[i].position.y});
    sfCircleShape_setFillColor(radius, sfTransparent);
    if (entities->hitboxes != 0) {
        sfCircleShape_setOutlineThickness(radius, 2);
        sfCircleShape_setOutlineColor(radius, sfBlue);
        sfRenderWindow_drawCircleShape(entities->window, radius, NULL);
    }
    sfCircleShape_setOutlineColor(radius, sfTransparent);
    sfCircleShape_setOutlineThickness(radius, 0);
}

static void draw_towers(sfRenderWindow *window, entities_t *entities)
{
    sfRectangleShape *tower = sfRectangleShape_create();
    sfTexture *texture = sfTexture_createFromFile("assets/tower.png", NULL);
    sfCircleShape *radius = sfCircleShape_create();

    if (!tower || !texture)
        return;
    sfRectangleShape_setTexture(tower, texture, sfTrue);
    sfRectangleShape_setSize(tower, (sfVector2f) {40, 40});
    if (entities->show != 0)
        sfRectangleShape_setFillColor(tower, sfTransparent);
    for (int i = 0; i < entities->num_towers; i++) {
        if (entities->towers[i].position.x >= 0 &&
            entities->towers[i].position.x <= 1920 &&
            entities->towers[i].position.y >= 0 &&
            entities->towers[i].position.y <= 1080)
        draw_tower(entities, tower, radius, i);
    }
    sfRectangleShape_destroy(tower);
    sfTexture_destroy(texture);
    sfCircleShape_destroy(radius);
}

void draw_background(sfRenderWindow *window)
{
    sfSprite *background = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile("assets/background.png",
        NULL);

    if (!background || !texture)
        return;
    sfSprite_setTexture(background, texture, sfTrue);
    sfRenderWindow_drawSprite(window, background, NULL);
    sfSprite_destroy(background);
    sfTexture_destroy(texture);
}

void draw_all(sfRenderWindow *window, entities_t *entities, sfClock *clock)
{
    sfTime time = sfClock_getElapsedTime(clock);
    float elapsed = sfTime_asSeconds(time);

    sfClock_restart(clock);
    sfRenderWindow_clear(window, sfBlack);
    draw_background(window);
    draw_towers(window, entities);
    draw_aircrafts(window, entities);
    update_entities(entities, elapsed);
    update_collisions(entities);
    sfRenderWindow_display(window);
}

static int check_end(entities_t *entities)
{
    static int last_count = -1;

    if (last_count != entities->count) {
        my_printf("Progress: %d/%d planes finished/crashed\n",
            entities->count, entities->final_count);
        last_count = entities->count;
    }
    return entities->count >= entities->final_count;
}

void keybinds(sfEvent event, entities_t *entities, int *temp, int *temp2)
{
    if (event.type == sfEvtClosed || (event.key.code == sfKeyEscape &&
        event.type == sfEvtKeyPressed))
        sfRenderWindow_close(entities->window);
    if (event.key.code == sfKeyL && event.type == sfEvtKeyPressed) {
        *temp += 1;
        entities->hitboxes = *temp % 2;
    }
    if (event.key.code == sfKeyS && event.type == sfEvtKeyPressed) {
        *temp2 += 1;
        entities->show = *temp2 % 2;
    }
}

void main_loop(sfRenderWindow *window, entities_t *entities)
{
    sfClock *clock = sfClock_create();
    sfEvent event;
    int temp = 0;
    int temp2 = 0;

    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            keybinds(event, entities, &temp, &temp2);
        }
        draw_all(window, entities, clock);
        if (check_end(entities)) {
            sfClock_destroy(clock);
            return;
        }
    }
    sfClock_destroy(clock);
    sfRenderWindow_destroy(entities->window);
}
