#include "Matrix.h"

#include <fstream>
#include <cstdlib>
#include <iostream>
#include "BadFileException.h"

Matrix::Matrix(int rows, int cols) : rows_quantity(rows), columns_quantity(cols) {
    vec.resize(this->rows_quantity * this->columns_quantity);
}

Matrix::Matrix(std::string fName) {
    std::ifstream file(fName.c_str());
    file >> this->rows_quantity >> this->columns_quantity;
    vec.resize(this->rows_quantity * this->columns_quantity);
    std::size_t i, j;
    for (i = 0; i < this->rows_quantity && !file.eof(); i++) {
        for (j = 0; j < this->columns_quantity && !file.eof(); j++) {
            file >> this->at(i, j);
        }
    }
    if (i != this->rows_quantity || j != this->columns_quantity) {
        throw BadFileException();
    }
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

    other.rows_quantity = 0;
    other.columns_quantity = 0;
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

    other.rows_quantity = 0;
    other.columns_quantity= 0;

    return *this;
}

int& Matrix::at(int row, int col) {
    range_check(row, col);
    return vec.at((row * columns_quantity) + col);
}

int& Matrix::at(Point a) {
    return at(a.row, a.col);
}

const int& Matrix::at(int row, int col) const {
    range_check(row, col);
    return vec.at((row * columns_quantity + col));
}

const int& Matrix::at(Point a) const {
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
