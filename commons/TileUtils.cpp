#include "TileUtils.h"

#define TILE_PIXEL_RATE 32

namespace tile_utils {
    Point getTileFromPixel(Point &pixel) {
        return {pixel.row / TILE_PIXEL_RATE, pixel.col / TILE_PIXEL_RATE};
    }

    Point getPixelFromTile(Point &tile) {
        return {tile.row * TILE_PIXEL_RATE, tile.col * TILE_PIXEL_RATE};
    }

}
