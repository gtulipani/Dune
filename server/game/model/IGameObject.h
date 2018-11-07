#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <string>

class IGameObject {
    public:
    virtual void tick() = 0;

    virtual bool haveYouChanged() = 0;

    virtual std::string getState() = 0;
};

#endif
