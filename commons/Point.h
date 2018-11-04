#ifndef __POINT_H__
#define __POINT_H__

#include <string>
#include "json.hpp"

using nlohmann::json;

struct Point {
    int row;
    int col;

    Point();

    Point(const std::string& point);

    Point(int row, int col);

    bool operator==(const Point& other) const;

    bool operator!=(const Point& other) const;

    unsigned int hDistanceTo(const Point& other) const;

    Point(const Point &other);

    Point(Point &&other) noexcept;

    // Overloading the assignment by copy
    Point &operator=(const Point &other);

    // Overloading the assignment by movement
    Point &operator=(Point &&other) noexcept;

    // Overloading the std::string casting to transform the point to string
    explicit operator std::string() const;

    // Friend methods for JSON
    friend void to_json(json &j, const Point &p);
    friend void from_json(const json &j, Point &p);
};

#endif
