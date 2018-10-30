#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <vector>
#include <string>
#include "Point.h"

class Matrix {
    std::vector<int> vec;
    std::size_t n;
    std::size_t m;

    public:
    Matrix(std::size_t rows, std::size_t cols);

    Matrix(std::string fName);

    std::size_t rows() const;

    std::size_t cols() const;

    int& at(std::size_t row, std::size_t col);

    int& at(Point a);

    const int& at(std::size_t row, std::size_t col) const;

    const int& at(Point a) const;

    private:
    void range_check(std::size_t row, std::size_t col) const;
};

#endif
