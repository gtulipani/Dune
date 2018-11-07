#ifndef __SDL_PICTURABLE_H__
#define __SDL_PICTURABLE_H__

// Commons Libraries
#include <Picturable.h>

// Client Libraries
#include "SdlTexture.h"

class SdlPicturable {
private:
    Picturable picturable;
    SdlTexture sdlTexture;
public:
    SdlPicturable(Picturable picturable, SdlTexture sdlTexture);

    SdlPicturable(const SdlPicturable &other);

    SdlPicturable(SdlPicturable &&other) noexcept;

    // Overloading the assignment by copy
    SdlPicturable &operator=(const SdlPicturable &other);

    // Overloading the assignment by movement
    SdlPicturable &operator=(SdlPicturable &&other) noexcept;

    void render();
};


#endif //__SDL_PICTURABLE_H__
