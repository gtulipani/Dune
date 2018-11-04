#include <cstdlib>
#include <sstream>
#include <fstream>

#include "Point.h"

#define ROW_COL_SEPARATOR ' '

Point::Point() {
    this->row = 0;
    this->col = 0;
}

Point::Point(const std::string& point) {
    std::ifstream stream(point.c_str());
    stream >> this->row >> this->col;
}

Point::Point(int _row, int _col) {
    this->row = _row;
    this->col = _col;
}

Point::Point(const Point &other) : Point(
        other.row,
        other.col) {}

Point::Point(Point &&other) noexcept : Point(
        other.row,
        other.col) {
    other.row= 0;
    other.col = 0;
}

Point &Point::operator=(const Point &other) {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->row = other.row;
    this->col = other.col;

    return *this;
}

Point &Point::operator=(Point &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->row = other.row;
    this->col= other.col;

    other.row = 0;
    other.col= 0;

    return *this;
}

bool Point::operator==(const Point& other) const {
    return other.row == this->row && other.col == this->col;
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

unsigned int Point::hDistanceTo(const Point& other) const {
   return static_cast<unsigned int>(std::abs((long)(this->row - other.row)) +
        std::abs((long)(this->col - other.col)));
}

Point::operator std::string() const {
    std::stringstream stream;
    stream << row << ROW_COL_SEPARATOR << col;
    return stream.str();
}
