#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>

struct Point {
    std::size_t row;
    std::size_t col;

    Point();

    Point(std::size_t row, std::size_t col);

    std::string getStr() const;

    bool operator==(const Point& other) const;

    bool operator!=(const Point& other) const;

    std::size_t hDistanceTo(const Point& other) const;
};

class Matrix {
    std::vector<int> vec;
    std::size_t n;
    std::size_t m;

    public:
    Matrix(std::size_t rows, std::size_t cols);

    Matrix(std::string fName);

    std::size_t rows() const noexcept;

    std::size_t cols() const noexcept;

    int& at(std::size_t row, std::size_t col);

    int& at(Point a);

    const int& at(std::size_t row, std::size_t col) const;

    const int& at(Point a) const;

    private:
    void range_check(std::size_t row, std::size_t col) const;
};

#endif
