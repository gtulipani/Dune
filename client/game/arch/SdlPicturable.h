#ifndef __SDL_PICTURABLE_H__
#define __SDL_PICTURABLE_H__

// Commons Libraries
#include <Picturable.h>

// Client Libraries
#include "../sdl/SdlTexture.h"
#include "ClientSpritesSupplier.h"

class SdlPicturable {
private:
    Picturable picturable;
    SdlTexture *main_texture;
    ClientSpritesSupplier &sprites_supplier;

    // Recalculates the width to render from the image, based on a rate between the original width and the destiny
    int recalculateWidth(int destinyWidth, int originalWidth);
public:
    SdlPicturable(Picturable picturable, SdlTexture *sdlTexture, ClientSpritesSupplier &sprites_supplier);

    SdlPicturable(const SdlPicturable &other) = delete;

    SdlPicturable(SdlPicturable &&other) noexcept;

    // Overloading the assignment by copy
    SdlPicturable &operator=(const SdlPicturable &other) = delete;

    // Overloading the assignment by movement
    SdlPicturable &operator=(SdlPicturable &&other) noexcept;

    bool operator==(const Picturable& other) const;

    // Renders itself if it's under the limits
    void render(int offset_x, int offset_y, int width_limit);

    void update(Picturable picturable, SdlTexture *sdlTexture);

    bool hasPriority() const;

    SdlTexture* getHealthBarTexture();
};


#endif //__SDL_PICTURABLE_H__
