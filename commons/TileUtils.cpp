#include "TileUtils.h"

namespace tile_utils {
    Point getTileFromPixel(Point &pixel, int tile_size) {
        return {pixel.row / tile_size, pixel.col / tile_size};
    }

    Point getPixelFromTile(Point &tile, int tile_size) {
        return {tile.row * tile_size, tile.col * tile_size};
    }

}
