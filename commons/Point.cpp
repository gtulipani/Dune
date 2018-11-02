#include <cstdlib>
#include <sstream>

#include "Point.h"

#define ROW_COL_SEPARATOR ','

Point::Point() {
    this->row = 0;
    this->col = 0;
}

Point::Point(unsigned int _row, unsigned int _col) {
    this->row = _row;
    this->col = _col;
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
