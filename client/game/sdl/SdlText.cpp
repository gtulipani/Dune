#include "SdlText.h"

// Client Libraries
#include "SdlTexture.h"
#include "../arch/Area.h"

// SDL Libraries
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>

SdlTexture* SdlText::buildTexture(SDL_Renderer* renderer, TTF_Font* font, SDL_Color* text_color, const std::string& text) {
    SDL_Surface *surface;
    surface = TTF_RenderText_Solid(font, text.c_str(), *text_color);
    auto *texture = new SdlTexture(renderer, SDL_CreateTextureFromSurface(renderer, surface));

    width = surface->w;
    height = surface->h;
    return texture;
}

SdlText::SdlText(const std::string& text, SdlTexture* texture) :
        text(text),
        texture(texture) {}

SdlText::SdlText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color* text_color, const std::string& text) :
        SdlText(text, buildTexture(renderer, font, text_color, text)) {}

SdlText::SdlText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color* color, int value) : SdlText(
        renderer,
        font,
        color,
        std::to_string(value)) {}

void SdlText::render(int col, int row, int char_expected_width, int char_expected_height) const {
    // The size depends on the quantity of chars
    int chars_quantity = static_cast<int>(text.length());

    Area src(0, 0, width, height);
    Area dest(col, row, char_expected_width * chars_quantity, char_expected_height);
    texture->render(src, dest);
}

SdlText::~SdlText() {
    delete texture;
}
