//  Copyright (c) 2024 Ethan Delage
#ifndef MATRIX_H_
#define MATRIX_H_

#include <exception>
#include <iostream>
#include <string>
#include <utility>

#include "./vector.h"

template <class K>
class Vector;

template <class K>
class Matrix {
    typedef struct shape_s {
        size_t row;
        size_t column;
    } shape_t;

 private:
    shape_t shape_;
    K**     data_;

    void validate_shape(const Matrix<K>& other) const {
        shape_t other_shape;

        other_shape = other.get_shape();
        if (shape_.row != other_shape.row
            || shape_.column != other_shape.column) {
            throw MatrixException("Matrix shape mismatch");
        }
    }

 public:
    explicit Matrix(size_t row, size_t column) {
        shape_.row = row;
        shape_.column = column;
        data_ = new K*[row];
        for (size_t i = 0; i < row; ++i) {
            data_[i] = new K[column];
            for (size_t j = 0; j < column; ++j) {
                data_[i][j] = 0;
            }
        }
    }

    explicit Matrix(shape_t shape) : Matrix(shape.row, shape.column) {}

    Matrix(const Matrix<K>& other) {
        data_ = nullptr;
        *this = other;
    }

    ~Matrix() {
        for (size_t row = 0; row < shape_.row; ++row) {
            delete[] data_[row];
        }
        delete[] data_;
    }

    Matrix<K>& operator=(const Matrix<K>& other) {
        if (this == &other) {
            return *this;
        }
        if (data_ != nullptr) {
            for (size_t row = 0; row < shape_.row; ++row) {
                delete[] data_[row];
            }
            delete[] data_;
        }
        shape_ = other.shape_;
        data_ = new K*[shape_.row];
        for (size_t row = 0; row < shape_.row; ++row) {
            data_[row] = new K[shape_.column];
            for (size_t column = 0; column < shape_.column; ++column) {
                data_[row][column] = other[row][column];
            }
        }
        return *this;
    }

    const K* operator[](size_t index) const {
        return data_[index];
    }

    K* operator[](size_t index) {
        return data_[index];
    }

    Matrix<K> operator+(const Matrix<K>& rhs) const {
        validate_shape(rhs);
        Matrix<K> result(shape_.row, shape_.column);

        for (size_t row = 0; row < shape_.row; ++row) {
            for (size_t column = 0; column < shape_.column; ++column) {
                result[row][column] = data_[row][column] + rhs[row][column];
            }
        }
        return result;
    }

    Matrix<K>& operator+=(const Matrix<K>& rhs) {
        validate_shape(rhs);
        for (size_t row = 0; row < shape_.row; ++row) {
            for (size_t column = 0; column < shape_.column; ++column) {
                data_[row][column] += rhs[row][column];
            }
        }
        return *this;
    }

    Matrix<K> operator-(const Matrix<K>& rhs) const {
        validate_shape(rhs);
        Matrix<K> result(shape_.row, shape_.column);

        for (size_t row = 0; row < shape_.row; ++row) {
            for (size_t column = 0; column < shape_.column; ++column) {
                result[row][column] = data_[row][column] - rhs[row][column];
            }
        }
        return result;
    }

    Matrix<K>& operator-=(const Matrix<K>& rhs) {
        validate_shape(rhs);
        for (size_t row = 0; row < shape_.row; ++row) {
            for (size_t column = 0; column < shape_.column; ++column) {
                data_[row][column] -= rhs[row][column];
            }
        }
        return *this;
    }

    Matrix<K> operator*(K scalar) const {
        Matrix<K> result(shape_.row, shape_.column);

        for (size_t row = 0; row < shape_.row; ++row) {
            for (size_t column = 0; column < shape_.column; ++column) {
                result[row][column] = scalar * data_[row][column];
            }
        }
        return result;
    }

    Matrix<K>& operator*=(K scalar) {
        for (size_t row = 0; row < shape_.row; ++row) {
            for (size_t column = 0; column < shape_.column; ++column) {
                data_[row][column] *= scalar;
            }
        }
        return *this;
    }

    shape_t get_shape() const {
        return shape_;
    }

    bool is_square() const {
        return shape_.row == shape_.column;
    }

    Vector<K> to_vector() {
        if (shape_.column != 1) {
            throw MatrixException("Matrix cannot be converted to vector");
        }
        Vector<K> vector(shape_.row);

        for (size_t row = 0; row < shape_.row; ++row) {
            vector[row] = data_[row][0];
        }
        return vector;
    }

    Matrix<K>& add(const Matrix<K>& matrix) {
        *this += matrix;
        return *this;
    }

    Matrix<K>& sub(const Matrix<K>& matrix) {
        *this -= matrix;
        return *this;
    }

    Matrix<K>& scale(K scalar) {
        *this *= scalar;
        return *this;
    }

    class MatrixException : public std::exception {
     private:
        std::string error_message_;
     public:
        explicit MatrixException(std::string  error_message)
            : error_message_(std::move(error_message)) {}

        const char* what() const _NOEXCEPT {
            return error_message_.c_str();
        }
    };
};

template <typename K>
std::ostream& operator<<(std::ostream& os, const Matrix<K>& matrix) {
    for (size_t row = 0; row < matrix.get_shape().row; ++row) {
        os << '[';
        for (size_t column = 0; column < matrix.get_shape().column; ++column) {
            os << matrix[column][row] << ", ";
        }
        os << "]\n";
    }
    os << std::flush;
    return os;
}

template <typename K>
Matrix<K> operator*(K scalar, const Matrix<K>& matrix) {
    return matrix * scalar;
}

#endif  //   MATRIX_H_
