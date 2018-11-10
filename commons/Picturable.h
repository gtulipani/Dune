#ifndef __PICTURABLE_H__
#define __PICTURABLE_H__

#include <string>
#include "Point.h"

struct Picturable {
public:
    int id{};
    int sprite;
    bool selected{};
    Point position;
    int health{};

    Picturable() = default;

    Picturable(int id, int sprite, bool selected, Point position, int health);

    Picturable(const Picturable &other);

    Picturable(Picturable &&other) noexcept;

    // Overloading the assignment by copy
    Picturable &operator=(const Picturable &other);

    // Overloading the assignment by movement
    Picturable &operator=(Picturable &&other) noexcept;
};


#endif //__PICTURABLE_H__
