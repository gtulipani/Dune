#include "Matrix.h"

#include <fstream>
#include <cstdlib>
#include "BadFileException.h"

Matrix::Matrix(std::size_t rows, std::size_t cols) : n(rows), m(cols) {
    vec.resize(this->n * this->m);
}

Matrix::Matrix(std::string fName) {
    std::ifstream file(fName.c_str());
    file >> this->n >> this->m;
    vec.resize(this->n * this->m);
    std::size_t i, j;
    for (i = 0; i < this->n && !file.eof(); i++) {
        for (j = 0; j < this->m && !file.eof(); j++) {
            file >> this->at(i, j);
        }
    }
    if (i != this->n || j != this->m) {
        throw BadFileException();
    }
}

int& Matrix::at(std::size_t row, std::size_t col) {
    range_check(row, col);
    return vec.at(row * n + col);
}

int& Matrix::at(Point a) {
    return at(a.row, a.col);
}

const int& Matrix::at(std::size_t row, std::size_t col) const {
    range_check(row, col);
    return vec.at(row * n + col);
}

const int& Matrix::at(Point a) const {
    return at(a.row, a.col);
}

void Matrix::range_check(std::size_t row, std::size_t col) const {
    if (row >= this->n) {
        throw std::out_of_range("Matrix::range_check: row (which is " +
                                std::to_string(row) + ") >= this->rows()" +
                                "(which is " + std::to_string(this->n) + ")");
    }
    if (col >= this->m) {
        throw std::out_of_range("Matrix::range_check: col (which is " +
                                std::to_string(col) + ") >= this->cols()" +
                                "(which is " + std::to_string(this->m) + ")");
    }
}

std::size_t Matrix::rows() const {
    return this->n;
}

std::size_t Matrix::cols() const {
    return this->m;
}
