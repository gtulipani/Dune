#include "SdlTexture.h"
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "SdlWindow.h"
#include "SdlException.h"

SdlTexture::SdlTexture(int width, int height, SDL_Renderer* renderer) : renderer(renderer) {
    this->texture = createTexture(width, height);
}

SdlTexture::SdlTexture(const std::string &filename, const SdlWindow* window)
    : renderer(window->getRenderer()) {
    this->texture = loadTexture(filename);
}

SdlTexture::SdlTexture(const SdlTexture &other) {
    this->renderer = other.renderer;
    this->texture = other.texture;
}

SdlTexture::SdlTexture(SdlTexture &&other) noexcept {
    this->renderer = other.renderer;
    this->texture = other.texture;

    other.renderer = nullptr;
    other.texture = nullptr;
}

SdlTexture &SdlTexture::operator=(const SdlTexture &other) {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->renderer = other.renderer;
    this->texture = other.texture;

    return *this;
}

SdlTexture &SdlTexture::operator=(SdlTexture &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->renderer = other.renderer;
    this->texture = other.texture;

    other.renderer = nullptr;
    other.texture = nullptr;

    return *this;
}

SdlTexture::~SdlTexture() {
    if (this->texture != nullptr) {
        SDL_DestroyTexture(this->texture);
    }
}

SDL_Texture* SdlTexture::loadTexture(const std::string &filename) {
    SDL_Texture* texture = IMG_LoadTexture(this->renderer,
                                           filename.c_str());
    if (!texture) {
        throw SdlException("Error al cargar la textura", SDL_GetError());
    }
    return texture;
}

SDL_Texture* SdlTexture::createTexture(int width, int height) {
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, width, height);
    if (!texture) {
        throw SdlException("Error al crear la textura", SDL_GetError());
    }
    return texture;
}

int SdlTexture::render(const Area& src, const Area& dest) const {
    SDL_Rect sdlSrc = {
            src.getX(), src.getY(),
            src.getWidth(), src.getHeight()
    };
    SDL_Rect sdlDest = {
            dest.getX(), dest.getY(),
            dest.getWidth(), dest.getHeight()
    };

    return SDL_RenderCopy(this->renderer, this->texture, &sdlSrc, &sdlDest);
}

void SdlTexture::setAsTarget() const {
    SDL_SetRenderTarget(this->renderer, this->texture);
}
