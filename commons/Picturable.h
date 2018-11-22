#ifndef __PICTURABLE_H__
#define __PICTURABLE_H__

#include <string>
#include "Point.h"

struct Picturable {
public:
    int player_id{};
    int id{};
    int sprite{};
    bool selected{};
    Point position;
    Point size;
    int health{};
    int max_health{};
    int porcentage{};

    Picturable() = default;

    Picturable(int player_id, int id, int sprite, bool selected, Point position, Point size, int health, int max_health, int porcentage);

    Picturable(const Picturable &other);

    Picturable(Picturable &&other) noexcept;

    // Overloading the assignment by copy
    Picturable &operator=(const Picturable &other);

    // Overloading the assignment by movement
    Picturable &operator=(Picturable &&other) noexcept;
};


#endif //__PICTURABLE_H__
