#ifndef __SPRITES_SUPPLIER_H__
#define __SPRITES_SUPPLIER_H__

// STL Libraries
#include <map>

// Client Libraries
#include "../sdl/SdlTexture.h"

typedef enum ClientSprites {
    CONSTRUCTION_CENTER_ICON = 5,
    WIND_TRAPS_ICON = 6,
    REFINERY_ICON = 7,
    BARRACKS_ICON = 8,
    LIGHT_FACTORY_ICON = 9,
    HEAVY_FACTORY_ICON = 10,
    SILO_ICON = 11,
    LIGHT_INFANTRY_ICON = 12,
    HEAVY_INFANTRY_ICON = 13,
    TRIKE_ICON = 14,
    RAIDER_ICON = 15,
    TANK_ICON = 16,
    HARVESTER_ICON = 17,
    PANEL_BACKGROUND = 18,
    PANEL_BUTTONS_BACKGROUND = 19,
    HEALTH_10 = 20,
    HEALTH_20 = 21,
    HEALTH_30 = 22,
    HEALTH_40 = 23,
    HEALTH_50 = 24,
    HEALTH_60 = 25,
    HEALTH_70 = 26,
    HEALTH_80 = 27,
    HEALTH_90 = 28,
    HEALTH_100 = 29,
    SELECTION_SQUARE = 30,
    CONSTRUCTION_PERCENTAGE_0 = 31,
    CONSTRUCTION_PERCENTAGE_12 = 32,
    CONSTRUCTION_PERCENTAGE_25 = 33,
    CONSTRUCTION_PERCENTAGE_37 = 34,
    CONSTRUCTION_PERCENTAGE_50 = 35,
    CONSTRUCTION_PERCENTAGE_62 = 36,
    CONSTRUCTION_PERCENTAGE_75 = 37,
    CONSTRUCTION_PERCENTAGE_87 = 38,
    CONSTRUCTION_PERCENTAGE_100 = 39,
    EAGLE_EYE_SQUARE = 40,
    STATUS_BAR = 41
} ClientSprites;

class ClientSpritesSupplier {
private:
    std::map<int, SdlTexture*> sprites;

    SdlTexture *createTexture(const std::string& subpath, const std::string& file_path, SdlWindow *window);

    SdlTexture *createPanelTexture(const std::string& file_path, SdlWindow *window);
    SdlTexture *createTerrainTexture(const std::string& file_path, SdlWindow *window);
    SdlTexture *createStatusTexture(const std::string& file_path, SdlWindow *window);

public:
    explicit ClientSpritesSupplier(SdlWindow *window);

    // Overloading the assignment by copy
    ClientSpritesSupplier &operator=(const ClientSpritesSupplier &other) = delete;

    // Overloading the assignment by movement
    ClientSpritesSupplier &operator=(ClientSpritesSupplier &&other) noexcept;

    SdlTexture* operator[](enum ClientSprites sprite) const;
    SdlTexture* operator[](int sprite) const;

    ~ClientSpritesSupplier();
};


#endif //__SPRITES_SUPPLIER_H__
