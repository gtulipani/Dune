#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <vector>
#include <string>
#include "Point.h"

class Matrix {
    std::vector<int> vec;
    int rows_quantity;
    int columns_quantity;

    void range_check(int row, int col) const;

public:
    Matrix(int rows, int cols);

    explicit Matrix(std::string fName);

    int rows() const;

    int cols() const;

    int& at(int row, int col);

    int& at(Point a);

    const int& at(int row, int col) const;

    const int& at(Point a) const;

};

#endif
