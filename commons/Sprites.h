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

    // Vehicles
    TRIKE = 10,
    HARVESTER = 11,
    RAIDER = 12,
    TANK = 13,

    // Units
    LIGHT_INFANTRY = 14,
    HEAVY_INFANTRY = 15,

    // Others
    ESPECIA = 16
} Sprites;

#define MAX_MOTION 4

typedef enum Direction {
    SPRITE_UP = 0,
    SPRITE_UP_RIGHT = 1,
    SPRITE_RIGHT = 2,
    SPRITE_DOWN_RIGHT = 3,
    SPRITE_DOWN = 4,
    SPRITE_DOWN_LEFT = 5,
    SPRITE_LEFT = 6,
    SPRITE_UP_LEFT = 7
} Direction;

#define DEFAULT_SPRITE_DIRECTION SPRITE_DOWN
#define DEFAULT_SPRITE_MOTION 0

#endif //__SPRITES_H__
