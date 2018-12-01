#ifndef __ESPECIA_H__
#define __ESPECIA_H__

#include <Picturable.h>

struct Point;

class Especia : public Picturable {
    private:
    int especia_per_sprite_change;
    int counter = 1;
    bool haveIChanged = true;

    public:
    Especia(int id, const Point& tilePosition);

    Point getPosition() const;

    bool haveYouChanged() const;

    bool runOut() const;

    void tryToGetSome(int& especia);

    void reset();
};

#endif
