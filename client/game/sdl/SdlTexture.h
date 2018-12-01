#ifndef __SDL_TEXTURE_H__
#define __SDL_TEXTURE_H__

#include <string>

struct SDL_Texture;
struct SDL_Renderer;
class SdlWindow;
class SdlColor;
class Area;

class SdlTexture {
public:
    SdlTexture() = default;

    SdlTexture(SDL_Renderer *renderer, SDL_Texture *texture);

    SdlTexture(int width, int height, SDL_Renderer* renderer);

    SdlTexture(const std::string &filename, const SdlWindow* window);

    SdlTexture(const SdlTexture &other);

    SdlTexture(SdlTexture &&other) noexcept;

    // Overloading the assignment by copy
    SdlTexture &operator=(const SdlTexture &other);

    // Overloading the assignment by movement
    SdlTexture &operator=(SdlTexture &&other) noexcept;

    ~SdlTexture();

    int render(const Area& src, const Area& dest) const;

    void setColor(SdlColor *color);

    void setAsTarget() const;
private:
    SDL_Texture* loadTexture(const std::string &filename);
    SDL_Texture* createTexture(int width, int height);
    SDL_Renderer* renderer;
    SDL_Texture* texture;
};

#endif
