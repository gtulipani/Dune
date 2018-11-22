#ifndef __ESPECIA_H__
#define __ESPECIA_H__

#include <Picturable.h>

struct Point;

class Especia : public Picturable {
    private:
    unsigned int counter = 0;
    bool haveIChanged = true;

    public:
    Especia(int id, const Point& tilePosition);

    Point getPosition() const;

    bool haveYouChanged() const;

    bool runOut() const;

    void tryToGetSome(unsigned int& especia);

    void reset();
};

#endif
