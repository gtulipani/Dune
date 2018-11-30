#include "StatusController.h"

// STL Libraries
#include <iostream>

// Commons Libraries
#include <events/GameStatusEvent.h>

// Client Libraries
#include "../../sdl/SdlText.h"

#define STATUS_BAR_ORIGIN_WIDTH 1250
#define STATUS_BAR_ORIGIN_HEIGHT 50

#define FONTS_PATH std::string("resources/fonts/")
#define DEFAULT_FONT std::string("open_sans_bold.ttf")

TTF_Font *StatusController::buildFont() {
    TTF_Init();
    if (!TTF_WasInit()) {
        std::cout << "Error initiating ttf" << std::endl;
    }
    TTF_Font *font = TTF_OpenFont((FONTS_PATH + DEFAULT_FONT).c_str(), 40);
    if (font == nullptr) {
        std::cout << "Font not found!" << std::endl;
    }
    return font;
}

StatusController::StatusController(SdlWindow *window, ClientSpritesSupplier &client_sprites_supplier, TTF_Font* font) :
        window(window),
        client_sprites_supplier(client_sprites_supplier),
        font(font),
        color({255, 255, 255, 0}),
        energy(0),
        especia(0),
        pending_changes(true) {}

StatusController::StatusController(SdlWindow *window, ClientSpritesSupplier &client_sprites_supplier) : StatusController(
        window,
        client_sprites_supplier,
        buildFont()) {}

void StatusController::configure(int screen_width, int screen_height) {
    this->screen_width = screen_width;
    this->screen_height = screen_height;

    // White text
    energy_text = new SdlText(window->getRenderer(), font, &color, energy);
    especia_text = new SdlText(window->getRenderer(), font, &color, especia);
}

void StatusController::render() {
    // Render the main texture containing the status bar
    Area srcArea(0, 0, STATUS_BAR_ORIGIN_WIDTH, STATUS_BAR_ORIGIN_HEIGHT);
    Area destArea(0, 0, screen_width, screen_height);
    client_sprites_supplier[STATUS_BAR]->render(srcArea, destArea);

    // Expected width and height for each digit
    int expected_digit_width = static_cast<int>(static_cast<float>(screen_width) / 60);
    int expected_digit_height = static_cast<int>(static_cast<float>(screen_height) / 2);


    // Render the energy text
    int energy_expected_col = static_cast<int>(static_cast<float>(screen_width) * 0.545);
    int energy_expected_row = static_cast<int>(static_cast<float>(screen_height) / 5);
    energy_text->render(energy_expected_col, energy_expected_row, expected_digit_width, expected_digit_height);

    // Render the especia text
    int especia_expected_col = static_cast<int>(static_cast<float>(screen_width) * 0.815);
    int especia_expected_row = static_cast<int>(static_cast<float>(screen_height) / 5);
    especia_text->render(especia_expected_col, especia_expected_row, expected_digit_width, expected_digit_height);

    window->render();
    pending_changes = false;
}

void StatusController::refresh() {
    if (pending_changes) {
        render();
    }
}

void StatusController::update(const GameStatusEvent &event) {
    if (energy != event.energy) {
        energy = event.energy;
        // Re-render the text
        delete energy_text;
        energy_text = new SdlText(window->getRenderer(), font, &color, energy);
        pending_changes = true;
    }

    if (especia != event.especia) {
        especia = event.especia;
        // Re-render the text
        delete especia_text;
        especia_text = new SdlText(window->getRenderer(), font, &color, especia);
        pending_changes = true;
    }
}

StatusController::~StatusController() {
    delete energy_text;
    delete especia_text;
    // Quit TTF
    TTF_Quit();
}
