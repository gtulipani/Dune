#ifndef __SDL_PICTURABLE_H__
#define __SDL_PICTURABLE_H__

// Commons Libraries
#include <Picturable.h>

// Client Libraries
#include "../sdl/SdlTexture.h"

class SdlPicturable {
private:
    Picturable picturable;
    SdlTexture &sdlTexture;
    int width;
    int height;

public:
    SdlPicturable(Picturable picturable, SdlTexture &sdlTexture, int width, int height);

    SdlPicturable(const SdlPicturable &other) = delete;

    SdlPicturable(SdlPicturable &&other) noexcept;

    // Overloading the assignment by copy
    SdlPicturable &operator=(const SdlPicturable &other) = delete;

    // Overloading the assignment by movement
    SdlPicturable &operator=(SdlPicturable &&other) noexcept;

    bool operator==(const Picturable& other) const;

    void render(int offset_x, int offset_y);
};


#endif //__SDL_PICTURABLE_H__
