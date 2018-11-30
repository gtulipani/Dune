#ifndef __SDL_TEXT_H__
#define __SDL_TEXT_H__

// STL Libraries
#include <string>

// SDL Libraries
#include <SDL2/SDL_ttf.h>

struct SDL_Renderer;
struct SDL_Color;

class SdlTexture;
class SdlWindow;
class Area;

class SdlText {
private:
    std::string text;
    SdlTexture* texture;
    int width;
    int height;

    SdlTexture* buildTexture(SDL_Renderer* renderer, TTF_Font* font, SDL_Color* text_color, const std::string& text);
public:
    SdlText(const std::string& text, SdlTexture* texture);

    SdlText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color* text_color, const std::string& text);

    SdlText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color* color, int value);

    void render(int col, int row, int char_expected_width, int char_expected_height) const;

    ~SdlText();
};


#endif //__SDL_TEXT_H__
