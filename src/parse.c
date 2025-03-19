/*
** EPITECH PROJECT, 2024
** src/parse
** File description:
** file where the parsing of the file occurs
*/

#include "../include/my.h"
#include "SFML/System/Clock.h"

static void skip_spaces(parser_t *parser)
{
    while (parser->line[parser->pos] == ' ')
        parser->pos++;
}

static int get_next_number(parser_t *parser)
{
    int number;

    skip_spaces(parser);
    number = my_getnbr(&parser->line[parser->pos]);
    while (parser->line[parser->pos] != ' ' && parser->line[parser->pos])
        parser->pos++;
    return number;
}

static void parse_aircraft_position(parser_t *parser, aircraft_t *aircraft)
{
    parser->pos = 1;
    aircraft->start.x = get_next_number(parser);
    aircraft->start.y = get_next_number(parser);
    aircraft->end.x = get_next_number(parser);
    aircraft->end.y = get_next_number(parser);
}

static void parse_aircraft_properties(parser_t *parser, aircraft_t *aircraft)
{
    aircraft->speed = get_next_number(parser);
    aircraft->delay = get_next_number(parser);
    aircraft->current = aircraft->start;
    aircraft->safe = 1;
    aircraft->destroyed = 1;
    aircraft->counted = 0;
    aircraft->completed = 0;
}

void parse_aircraft(char *line, entities_t *entities)
{
    aircraft_t *aircraft;
    parser_t parser = {line, 0};

    aircraft = malloc(sizeof(aircraft_t));
    if (!aircraft)
        return;
    parse_aircraft_position(&parser, aircraft);
    parse_aircraft_properties(&parser, aircraft);
    if (aircraft->start.x >= 0 && aircraft->start.x <= 1920 &&
        aircraft->start.y >= 0 && aircraft->start.y <= 1080) {
        entities->aircrafts[entities->num_aircrafts] = aircraft;
        entities->num_aircrafts++;
    } else {
        free(aircraft);
    }
}

static void init_struct(entities_t *entities)
{
    entities->count = 0;
    entities->final_count = 0;
    entities->num_aircrafts = 0;
    entities->hitboxes = 0;
    entities->num_towers = 0;
    entities->clock = sfClock_create();
}

void parse_tower(char *line, entities_t *entities)
{
    parser_t parser = {line, 1};
    control_tower_t tower;

    tower.position.x = get_next_number(&parser);
    tower.position.y = get_next_number(&parser);
    tower.radius = get_next_number(&parser);
    if (tower.position.x >= 0 && tower.position.x <= 1920 &&
        tower.position.y >= 0 && tower.position.y <= 1080) {
        entities->towers[entities->num_towers] = tower;
        entities->num_towers++;
    }
}

void checklen(const char *filepath, entities_t *entities)
{
    int fd = 0;
    struct stat info;
    char *buff;

    init_struct(entities);
    stat(filepath, &info);
    buff = malloc(info.st_size);
    fd = open(filepath, O_RDONLY);
    read(fd, buff, info.st_size);
    for (int i = 0; buff[i] != '\0'; i++) {
        if (buff[i] == 'A')
            entities->final_count++;
    }
    entities->aircrafts = malloc(sizeof(aircraft_t) * entities->final_count);
}

int load_script(const char *filepath, entities_t *entities)
{
    char *line = NULL;
    size_t len = 0;
    FILE *file = fopen(filepath, "r");

    if (!file) {
        sfRenderWindow_destroy(entities->window);
        return -1;
    }
    checklen(filepath, entities);
    while (getline(&line, &len, file) != -1) {
        if (line[0] != 'A' && line[0] != 'T')
            return -1;
        if (line[0] == 'A')
            parse_aircraft(line, entities);
        if (line[0] == 'T')
            parse_tower(line, entities);
    }
    free(line);
    fclose(file);
    return 0;
}
