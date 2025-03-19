/*
** EPITECH PROJECT, 2025
** src/movement
** File description:
** file where the movement of the planes and collisions occurs
*/

#include "../include/my.h"
#include "SFML/System/Clock.h"
#include "SFML/System/Time.h"

static float get_distance(sfVector2f pos1, sfVector2f pos2)
{
    float dx = pos1.x - pos2.x;
    float dy = pos1.y - pos2.y;

    return sqrt((dx * dx) + (dy * dy));
}

static int is_in_tower_range(aircraft_t *aircraft, control_tower_t *tower)
{
    sfVector2f aircraft_pos = aircraft->current;
    float distance = get_distance(aircraft_pos, tower->position);

    return distance <= tower->radius;
}

static void check_tower_protection(entities_t *entities, int plane_index)
{
    aircraft_t *aircraft = entities->aircrafts[plane_index];

    aircraft->safe = 0;
    for (int i = 0; i < entities->num_towers; i++) {
        if (is_in_tower_range(aircraft, &entities->towers[i])) {
            aircraft->safe = 1;
            break;
        }
    }
}

static void handle_collision(entities_t *entities, int i, int j)
{
    float distance = get_distance(entities->aircrafts[i]->current,
        entities->aircrafts[j]->current);

    if (distance < 20 && !entities->aircrafts[i]->safe &&
        !entities->aircrafts[j]->safe &&
        !entities->aircrafts[i]->destroyed &&
        !entities->aircrafts[j]->destroyed) {
        if (!entities->aircrafts[i]->counted) {
            entities->count++;
            entities->aircrafts[i]->counted = 1;
        }
        if (!entities->aircrafts[j]->counted) {
            entities->count++;
            entities->aircrafts[j]->counted = 1;
        }
        entities->aircrafts[i]->destroyed = 1;
        entities->aircrafts[j]->destroyed = 1;
    }
}

static void check(entities_t *entities, int i)
{
    for (int j = i + 1; j < entities->num_aircrafts; j++) {
        if (!entities->aircrafts[j]->destroyed &&
            entities->aircrafts[j]->delay <= 0)
            handle_collision(entities, i, j);
    }
}

void update_collisions(entities_t *entities)
{
    for (int i = 0; i < entities->num_aircrafts; i++) {
        if (entities->aircrafts[i]->delay > 0 ||
            entities->aircrafts[i]->destroyed)
            continue;
        check_tower_protection(entities, i);
        if (!entities->aircrafts[i]->safe &&
            entities->aircrafts[i]->destroyed == 0) {
            check(entities, i);
        }
    }
}

static void update_aircraft_position(aircraft_t *aircraft, float elapsed_time,
    entities_t *entities)
{
    float dx = aircraft->end.x - aircraft->current.x;
    float dy = aircraft->end.y - aircraft->current.y;
    float d_end = sqrt(dx * dx + dy * dy);
    float movement;

    if (d_end < aircraft->speed * elapsed_time) {
        if (!aircraft->completed && !aircraft->counted) {
            aircraft->completed = 1;
            aircraft->counted = 1;
            entities->count++;
        }
        aircraft->current = aircraft->end;
        return;
    }
    if (d_end > 0) {
        movement = aircraft->speed * elapsed_time;
        aircraft->current.x += (dx / d_end) * movement;
        aircraft->current.y += (dy / d_end) * movement;
    }
}

void delay(entities_t *entities, int i, float elapsed_time)
{
    if (entities->aircrafts[i]->safe == 1)
        entities->aircrafts[i]->destroyed = 0;
    if (!entities->aircrafts[i]->destroyed &&
        !entities->aircrafts[i]->completed) {
        update_aircraft_position(entities->aircrafts[i], elapsed_time,
            entities);
    }
}

void update_entities(entities_t *entities, float elapsed_time)
{
    sfTime time = sfClock_getElapsedTime(entities->clock);

    for (int i = 0; i < entities->num_aircrafts; i++) {
        if (entities->aircrafts[i]->delay == -1) {
            delay(entities, i, elapsed_time);
        }
        if (entities->aircrafts[i]->delay ==
            (int)(time.microseconds / 1000000.0)) {
            entities->aircrafts[i]->delay = -1;
            continue;
        }
    }
}
