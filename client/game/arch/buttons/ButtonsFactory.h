#ifndef __BUTTONS_FACTORY_H__
#define __BUTTONS_FACTORY_H__

// Client Libraries
#include "PanelButton.h"

class ButtonsFactory {
private:
    static PanelButton* createUnitButton(const std::string& name, int icon, int action, ClientSpritesSupplier &client_sprites_supplier);

    static PanelButton* createBuildingButton(const std::string& name, int icon, int action, ClientSpritesSupplier &client_sprites_supplier);

public:
    static PanelButton* createButton(const std::string& name, ClientSpritesSupplier &client_sprites_supplier);
};


#endif //__BUTTONS_FACTORY_H__
