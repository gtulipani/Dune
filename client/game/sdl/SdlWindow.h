#ifndef __SDL_WINDOW_H__
#define __SDL_WINDOW_H__
#include "../arch/Area.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class SdlWindow {
public:
    SdlWindow() = default;

    SdlWindow(int width, int height);

    SdlWindow(const SdlWindow &other) = delete;

    SdlWindow(SdlWindow &&other) noexcept;

    // Overloading the assignment by copy
    SdlWindow &operator=(const SdlWindow &other) = delete;

    // Overloading the assignment by movement
    SdlWindow &operator=(SdlWindow &&other) noexcept;

    ~SdlWindow();

    void fill();

    void fill(int r, int g, int b, int alpha);

    void render();

    SDL_Renderer* getRenderer() const;
private:
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif
