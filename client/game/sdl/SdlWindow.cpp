#include <SDL.h>
#include <SDL_video.h>
#include <SDL_render.h>
#include "SdlException.h"
#include "SdlWindow.h"
#include <iostream>


SdlWindow::SdlWindow(int width, int height, int resolution_width, int resolution_height) :
        width(width), height(height) {
    int errCode = SDL_Init(SDL_INIT_VIDEO);
    if (errCode) {
        throw SdlException("Error en la inicialización", SDL_GetError());
    }
    errCode = SDL_CreateWindowAndRenderer(
        width, height, SDL_RENDERER_ACCELERATED,
        &this->window, &this->renderer);
    if (errCode) {
        throw SdlException("Error al crear ventana", SDL_GetError());
    }
    //SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_RenderSetLogicalSize(this->renderer, resolution_width, resolution_height);
}

SdlWindow::SdlWindow(SdlWindow &&other) noexcept {
    // Copy values
    this->width = other.width;
    this->height = other.height;
    this->window = other.window;
    this->renderer = other.renderer;

    other.width = 0;
    other.height = 0;
    other.window = nullptr;
    other.renderer = nullptr;
}

SdlWindow &SdlWindow::operator=(SdlWindow &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->width = other.width;
    this->height = other.height;
    this->window = other.window;
    this->renderer = other.renderer;

    other.width = 0;
    other.height = 0;
    other.window = nullptr;
    other.renderer = nullptr;

    return *this;
}


SdlWindow::~SdlWindow() {
    std::cout << "Destruyendo SdlWindow()" << std::endl;
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
    }

    if (this->window) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }
}

void SdlWindow::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(this->renderer,
                           r, g, b, alpha);
    SDL_RenderClear(this->renderer);
}

void SdlWindow::fill() {
    this->fill(0x33,0x33,0x33,0xFF);
}

void SdlWindow::render() {
    SDL_RenderPresent(this->renderer);
}

void SdlWindow::setAsTarget() const {
    SDL_SetRenderTarget(this->renderer, nullptr);
}


SDL_Renderer* SdlWindow::getRenderer() const {
    return this->renderer;
}
