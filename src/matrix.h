//  Copyright (c) 2024 Ethan Delage
#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <exception>
#include <iostream>
#include <string>
#include <utility>

#include "./vector.h"

#define MATRIX_SHAPE_MISMATCH       "Matrix shape mismatch"
#define MATRIX_VECTOR_SIZE_MISMATCH "Size mismatch for matrix-vector multiplication"
#define MATRIX_NOT_SQUARE           "Matrix is not square. Matrix multiplication requires both matrices to be square"
#define MATRIX_NOT_INVERTIBLE       "Matrix is not invertible"

template <class K>
class Vector;

template <class K>
class Matrix {
    typedef struct shape_s {
        size_t row;
        size_t column;

        bool operator==(const shape_s& rhs) const {
            return (row == rhs.row && column == rhs.column);
        }
    } shape_t;

 private:
    shape_t shape_;
    K**     data_;

    void validate_shape(const Matrix<K>& other) const {
        shape_t other_shape;

        other_shape = other.get_shape();
        if (shape_ != other_shape) {
            throw MatrixException(MATRIX_SHAPE_MISMATCH);
        }
    }

    void validate_size(const Vector<K>& other) const {
        if (shape_.column != other.get_size()) {
            throw MatrixException(MATRIX_VECTOR_SIZE_MISMATCH);
        }
    }

    void validate_multiplication(const Matrix<K>& other) const {
        if (shape_.column != other.get_shape().row) {
            throw MatrixException(MATRIX_VECTOR_SIZE_MISMATCH);
        }
    }

    void swap_row(size_t first, size_t second) {
        std::swap(data_[first], data_[second]);
    }

    K det2() const {
        return data_[0][0] * data_[1][1] - data_[0][1] * data_[1][0];
    }

 public:
    explicit Matrix(size_t row, size_t column) {
        shape_.row = row;
        shape_.column = column;
        data_ = new K*[row];
        for (size_t i = 0; i < row; ++i) {
            data_[i] = new K[column];
            for (size_t j = 0; j < column; ++j) {
                data_[i][j] = K();
            }
        }
    }

    explicit Matrix(shape_t shape) : Matrix(shape.row, shape.column) {}

    Matrix(const Matrix<K>& other) {
        data_ = nullptr;
        *this = other;
    }

    Matrix(std::initializer_list<std::initializer_list<K>> entries) {
        shape_.row = entries.size();
        shape_.column = entries.begin()->size();
        data_ = new K*[shape_.row];

        for (size_t i = 0; i < shape_.row; ++i) {
            data_[i] = new K[shape_.column];

            std::copy(
                    entries.begin()[i].begin(),
                    entries.begin()[i].end(),
                    data_[i]);
        }
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

    Matrix<K>& operator=(
            std::initializer_list<std::initializer_list<K>> entries) {
        shape_t entries_shape;

        entries_shape.row = entries.size();
        entries_shape.column = entries.begin()->size();
        if (shape_ != entries_shape) {
            throw MatrixException(MATRIX_SHAPE_MISMATCH);
        }
        size_t i = 0;
        for (const auto& row : entries) {
            size_t j = 0;
            for (const auto& elem : row) {
                data_[i][j] = elem;
                ++j;
            }
            ++i;
        }
        return *this;
    }

    bool operator==(const Matrix<K>& rhs) const {
        for (size_t row = 0; row < shape_.row; ++row) {
            for (size_t column = 0; column < shape_.column; ++column) {
                if (data_[row][column] != rhs[row][column]) {
                    return false;
                }
            }
        }
        return true;
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

    Matrix<K>& operator*=(const Matrix<K>& rhs) {
        if (!is_square()) {
            throw MatrixException(MATRIX_NOT_SQUARE);
        }

        Matrix<K> result((*this) * rhs);

        *this = result;
        return *this;
    }

    Matrix<K> operator*(const Matrix<K>& rhs) const {
        validate_multiplication(rhs);
        shape_t rhs_shape = rhs.get_shape();
        Matrix<K> result(shape_.row, rhs_shape.column);


        result.foreach(
                [this, rhs, rhs_shape](K& elem, size_t row, size_t column) {
            for (size_t i = 0; i < rhs_shape.column; ++i) {
                elem = std::fma((*this)[row][i], rhs[i][column], elem);
            }
        });
        return result;
    }

    Vector<K> operator*(const Vector<K>& rhs) const {
        validate_size(rhs);
        Vector<K> result(shape_.row);

        result.foreach([this, rhs](K& elem, size_t row) {
            for (size_t column = 0; column < shape_.column; ++column) {
                elem = std::fma(data_[row][column], rhs[column], elem);
            }
        });
        return result;
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

    K trace() const {
        if (!is_square()) {
            throw MatrixException(MATRIX_NOT_SQUARE);
        }
        K result = K();

        for (size_t i = 0; i < shape_.row; ++i) {
            result += data_[i][i];
        }
        return result;
    }

    Matrix<K> transpose() const {
        Matrix<K> transpose(shape_.column, shape_.row);

        transpose.foreach([this](K& elem, size_t row, size_t column) {
            elem = data_[column][row];
        });
        return transpose;
    }

    Matrix<K> row_echelon() const {
        Matrix<K> result(*this);
        size_t pivot_row = 0;
        K pivot;
        K factor;

        for (size_t column = 0; column < shape_.column && pivot_row < shape_.row; ++column) {
            for (size_t row = pivot_row; row < shape_.row; ++row) {
                if (result[row][column] != 0) {
                    pivot = result[row][column];
                    if (row != pivot_row) {
                        result.swap_row(pivot_row, row);
                    }
                    for (size_t j = 0; j < shape_.column; ++j) {
                        result[pivot_row][j] /= pivot;
                    }
                    for (size_t i = 0; i < shape_.row; ++i) {
                        if (i != pivot_row) {
                            factor = result[i][column];
                            for (size_t j = column; j < shape_.column; ++j) {
                                result[i][j] -= (factor * result[pivot_row][j]);
                            }
                        }
                    }
                    ++pivot_row;
                }
            }
        }
        return result;
    }

    K determinant() const {
        if (!is_square()) {
            throw MatrixException(MATRIX_NOT_SQUARE);
        }
        switch (shape_.row) {
            case 1:
                return data_[0][0];
            case 2:
                return det2();
            default:
                K determinant = K();

                for (size_t i = 0; i < shape_.column; ++i) {
                    Matrix<K> sub_matrix(shape_.row - 1, shape_.column - 1);

                    sub_matrix.foreach([this, i](K& elem,
                            size_t row,
                            size_t column) {
                        elem = data_[row + 1][(column < i) ? column : column + 1];
                    });
                    determinant += (
                            ((i % 2) ? -1 : 1)
                            * data_[0][i]
                            * sub_matrix.determinant());
                }
                return determinant;
        }
    }

    Matrix<K> inverse() const {
        if (determinant() == 0) {
            throw MatrixException(MATRIX_NOT_INVERTIBLE);
        }
        size_t dimension = shape_.row;
        Matrix<K> augmented(dimension, 2 * dimension);
        Matrix<K> result(shape_);

        for (size_t row = 0; row < dimension; ++row) {
            for (size_t column = 0; column < dimension; ++column) {
                augmented[row][column] = data_[row][column];
            }
        }
        for (size_t i = 0; i < dimension; ++i) {
            augmented[i][dimension + i] = 1.;
        }
        augmented = augmented.row_echelon();

        result.foreach([augmented, dimension](K& elem, size_t row, size_t column) {
            elem = augmented[row][dimension + column];
        });
        return result;
    }

    size_t rank() const {
        Matrix row_echelon_matrix(shape_);
        size_t rank = 0;
        bool is_null;

        row_echelon_matrix = this->row_echelon();

        for (size_t row = 0; row < shape_.row; ++row) {
            is_null = true;
            for (size_t column = 0; column < shape_.column; ++column) {
                if (row_echelon_matrix[row][column] != 0) {
                    is_null = false;
                }
            }
            if (!is_null) {
                ++rank;
            }
        }

        return rank;
    }

    template <typename Function>
    auto foreach(Function f)
            -> std::enable_if_t<std::is_invocable_v<Function, K&>> {
        for (size_t i = 0; i < shape_.row; ++i) {
            for (size_t j = 0; j < shape_.column; ++j) {
                f(data_[i][j]);
            }
        }
    }

    template <typename Function>
    auto foreach(Function f)
            -> std::enable_if_t<std::is_invocable_v<Function, K&, size_t>> {
        for (size_t i = 0; i < shape_.row; ++i) {
            f(data_[i]);
        }
    }

    template <typename Function>
    auto foreach(Function f)
            -> std::enable_if_t<std::is_invocable_v<
                    Function,
                    K&,
                    size_t,
                    size_t>> {
        for (size_t i = 0; i < shape_.row; ++i) {
            for (size_t j = 0; j < shape_.column; ++j) {
                f(data_[i][j], i, j);
            }
        }
    }

    template <typename Function>
    auto foreach(Function f) const
    -> std::enable_if_t<std::is_invocable_v<
            Function,
            K&,
            size_t,
            size_t>> {
        for (size_t i = 0; i < shape_.row; ++i) {
            for (size_t j = 0; j < shape_.column; ++j) {
                f(data_[i][j], i, j);
            }
        }
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
        for (
                size_t column = 0;
                column < matrix.get_shape().column - 1;
                ++column) {
            os << matrix[row][column] << ", ";
        }
        os << matrix[row][matrix.get_shape().column - 1] << "]\n";
    }
    os << std::flush;
    return os;
}

template <typename K>
Matrix<K> operator*(K scalar, const Matrix<K>& matrix) {
    return matrix * scalar;
}

#endif  //  SRC_MATRIX_H_
