#ifndef __PICTURABLE_H__
#define __PICTURABLE_H__

#include <string>
#include "Point.h"

struct Picturable {
public:
    int id{};
    std::string type;
    bool selected{};
    Point position;
    int life{};
    int motion{};

    Picturable() = default;

    Picturable(int id, std::string type, bool selected, Point position, int life, int motion);

    Picturable(const Picturable &other);

    Picturable(Picturable &&other) noexcept;

    // Overloading the assignment by copy
    Picturable &operator=(const Picturable &other);

    // Overloading the assignment by movement
    Picturable &operator=(Picturable &&other) noexcept;
};


#endif //__PICTURABLE_H__
