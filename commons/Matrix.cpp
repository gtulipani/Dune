#include "Matrix.h"

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include "BadFileException.h"

Matrix::Matrix(int rows, int cols) : rows_quantity(rows), columns_quantity(cols) {
    vec.resize(this->rows_quantity * this->columns_quantity);
}

Matrix::Matrix(const Matrix &other) : Matrix(
        other.rows_quantity,
        other.columns_quantity) {
    this->vec = other.vec;
}

Matrix::Matrix(Matrix &&other) noexcept : Matrix(
        other.rows_quantity,
        other.columns_quantity) {
    this->vec = std::move(other.vec);
}

Matrix &Matrix::operator=(const Matrix &other) {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->vec = other.vec;
    this->rows_quantity = other.rows_quantity;
    this->columns_quantity = other.columns_quantity;

    return *this;
}

Matrix &Matrix::operator=(Matrix &&other) noexcept {
    if (this == &other) {
        return *this; // other is myself!
    }

    // Copy values
    this->vec = std::move(other.vec);
    this->rows_quantity = other.rows_quantity;
    this->columns_quantity = other.columns_quantity;

    return *this;
}

char& Matrix::at(int row, int col) {
    range_check(row, col);
    return vec.at((row * columns_quantity) + col);
}

char& Matrix::at(Point a) {
    return at(a.row, a.col);
}

const char& Matrix::at(int row, int col) const {
    range_check(row, col);
    return vec.at((row * columns_quantity + col));
}

const char& Matrix::at(Point a) const {
    return at(a.row, a.col);
}

void Matrix::range_check(int row, int col) const {
    if (row >= this->rows_quantity) {
        throw std::out_of_range("Matrix::range_check: row (which is " +
                                std::to_string(row) + ") >= this->rows()" +
                                "(which is " + std::to_string(this->rows_quantity) + ")");
    }
    if (col >= this->columns_quantity) {
        throw std::out_of_range("Matrix::range_check: col (which is " +
                                std::to_string(col) + ") >= this->cols()" +
                                "(which is " + std::to_string(this->columns_quantity) + ")");
    }
}

int Matrix::rows() const {
    return this->rows_quantity;
}

int Matrix::cols() const {
    return this->columns_quantity;
}
