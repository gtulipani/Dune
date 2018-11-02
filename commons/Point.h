#ifndef __POINT_H__
#define __POINT_H__

#include <string>

struct Point {
    unsigned int row;
    unsigned int col;

    Point();

    Point(unsigned int row, unsigned int col);

    bool operator==(const Point& other) const;

    bool operator!=(const Point& other) const;

    unsigned int hDistanceTo(const Point& other) const;

    // Overloading the std::string casting to transform the point to string
    explicit operator std::string() const;
};

#endif
