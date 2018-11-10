#ifndef __SDL_PICTURABLE_H__
#define __SDL_PICTURABLE_H__

// Commons Libraries
#include <Picturable.h>

// Client Libraries
#include "../sdl/SdlTexture.h"

#define SIZE 10

class SdlPicturable {
private:
    Picturable picturable;
    SdlTexture sdlTexture;
public:
    SdlPicturable(Picturable picturable, SdlTexture sdlTexture);

    SdlPicturable(const SdlPicturable &other) = delete;

    SdlPicturable(SdlPicturable &&other) noexcept;

    // Overloading the assignment by copy
    SdlPicturable &operator=(const SdlPicturable &other) = delete;

    // Overloading the assignment by movement
    SdlPicturable &operator=(SdlPicturable &&other) noexcept;

    void render(int offset_x, int offset_y);
};


#endif //__SDL_PICTURABLE_H__