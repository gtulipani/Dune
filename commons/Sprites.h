#ifndef __SPRITES_H__
#define __SPRITES_H__

typedef enum SpriteType {
    // Buildings sprites
    SPRITE_CONSTRUCTION_CENTER = 0,
    SPRITE_WIND_TRAPS = 1,
    SPRITE_REFINERY = 2,
    SPRITE_BARRACKS = 3,
    SPRITE_LIGHT_FACTORY = 4,
    SPRITE_HEAVY_FACTORY = 5,
    SPRITE_SILO = 6,

    // Vehicles
    SPRITE_TRIKE = 7,
    SPRITE_HARVESTER = 8,
    SPRITE_RAIDER = 9,
    SPRITE_TANK = 10,

    // Units
    SPRITE_LIGHT_INFANTRY = 11,
    SPRITE_HEAVY_INFANTRY = 12,

    // Others
    SPRITE_ESPECIA = 13
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
