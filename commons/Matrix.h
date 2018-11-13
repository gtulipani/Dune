#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <vector>
#include <string>
#include "Point.h"

struct Matrix {
public:
    std::vector<char> vec;
    int rows_quantity{};
    int columns_quantity{};

    void range_check(int row, int col) const;

    Matrix() = default;

    Matrix(int rows, int cols);

    explicit Matrix(std::string fName);

    Matrix(const Matrix &other);

    Matrix(Matrix &&other) noexcept;

    // Overloading the assignment by copy
    Matrix &operator=(const Matrix &other);

    // Overloading the assignment by movement
    Matrix &operator=(Matrix &&other) noexcept;

    int rows() const;

    int cols() const;

    char& at(int row, int col);

    char& at(Point a);

    const char& at(int row, int col) const;

    const char& at(Point a) const;

};

#endif
