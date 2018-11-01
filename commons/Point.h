#ifndef __POINT_H__
#define __POINT_H__

struct Point {
    unsigned int row;
    unsigned int col;

    Point();

    Point(unsigned int row, unsigned int col);

    bool operator==(const Point& other) const;

    bool operator!=(const Point& other) const;

    unsigned int hDistanceTo(const Point& other) const;
};

#endif
