#include "Matrix.h"

#include <string>
#include <fstream>
//#include <BadFiLeException.h>

Point::Point() {
    this->row = 0;
    this->col = 0;
}

Point::Point(std::size_t _row, std::size_t _col) {
    this->row = _row;
    this->col = _col;
}

Point::Point(std::string str) {
    std::size_t n = str.find(',');
    this->row = stoul(str.substr(1, n - 1));
    std::size_t m = str.find(')');
    this->col = stoul(str.substr(n + 2, m - n - 2));
}

std::string Point::getStr() const {
    return "(" + std::to_string(this->row) + ", " +
            std::to_string(this->col) + ")";
}

bool Point::operator==(const Point& other) const {
    return other.row == this->row && other.col == this->col;
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

std::size_t Point::hDistanceTo(const Point& other) const {
   return ::abs(this->row - other.row) + ::abs(this->col - other.col);
}

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
        throw "Error"/*BadFileException()*/;
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
