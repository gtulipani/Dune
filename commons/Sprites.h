#ifndef __SPRITES_H__
#define __SPRITES_H__

typedef enum Type {
    // Buildings sprites
    CONSTRUCTION_CENTER = 0,
    WIND_TRAPS = 1,
    REFINERY = 2,
    ATREIDES_BARRACKS = 3,
    HARKUNNAN_BARRACKS = 4,
    ORDOS_BARRACKS = 5,
    LIGHT_FACTORY = 6,
    HEAVY_FACTORY = 7,
    SILO = 8,
    PALACE = 9,

    // Trike unit sprites
    TRIKE = 10,

    // Harvester unit sprites
    HARVESTER = 18,

    // Light infantry sprites (TBD)
    LIGHT_INFANTRY = 18,
    ESPECIA = 19
} Sprites;

#define MAX_MOTION 4

typedef enum {
    SPRITE_UP = 0,
    SPRITE_UP_RIGHT = 1,
    SPRITE_RIGHT = 2,
    SPRITE_DOWN_RIGHT = 3,
    SPRITE_DOWN = 4,
    SPRITE_DOWN_LEFT = 5,
    SPRITE_LEFT = 6,
    SPRITE_UP_LEFT = 7
} Direction;

#endif //__SPRITES_H__
