//  Copyright (c) 2024 Ethan Delage
#ifndef SRC_VECTOR_H_
#define SRC_VECTOR_H_

#include <algorithm>
#include <exception>
#include <iostream>
#include <string>
#include <utility>

#include "./matrix.h"

#define VECTOR_SIZE_MISMATCH_ERROR  "Vector size mismatch"
#define VECTOR_SIZE_NOT_3_ERROR     "Input vectors must be of size 3"

template <class K>
class Matrix;

template <class K>
class Vector {
 private:
    size_t  size_;
    K*      data_;

 public:
    explicit Vector(size_t size) : size_(size) {
        data_ = new K[size];
        foreach([](K& elem) {
            elem = K();
        });
    }

    Vector(const Vector<K>& other) {
        data_ = nullptr;
        *this = other;
    }

    Vector(std::initializer_list<K> entries)
    : size_(entries.size()), data_(new K[size_]) {
        std::copy(entries.begin(), entries.end(), data_);
    }

    ~Vector() {
        delete[] data_;
    }

    Vector<K>& operator=(const Vector<K>& other) {
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        size_ = other.size_;
        data_ = new K[size_];
        foreach([&other](K& elem, size_t i) {
            elem = other[i];
        });
        return *this;
    }

    Vector<K>& operator=(std::initializer_list<K> entries) {
        if (size_ != entries.size()) {
            throw VectorException(VECTOR_SIZE_MISMATCH_ERROR);
        }
        std::copy(entries.begin(), entries.end(), data_);
        return *this;
    }

    bool operator==(const Vector<K>& rhs) const {
        for (size_t i = 0; i < size_; ++i) {
            if (data_[i] != rhs[i]) {
                return false;
            }
        }
        return true;
    }

    const K& operator[](size_t index) const {
        return data_[index];
    }

    K& operator[](size_t index) {
        return data_[index];
    }

    Vector<K> operator+(const Vector<K>& rhs) const {
        validate_size(rhs);
        Vector<K> result(size_);

        result.foreach([this, rhs](K& elem, size_t i) {
            elem = (*this)[i] + rhs[i];
        });
        return result;
    }

    Vector<K>& operator+=(const Vector<K>& rhs) {
        validate_size(rhs);
        foreach([rhs](K& elem, size_t i) {
            elem += rhs[i];
        });
        return *this;
    }

    Vector<K> operator-(const Vector<K>& rhs) const {
        validate_size(rhs);
        Vector<K> result(size_);

        result.foreach([this, rhs](K& elem, size_t i) {
            elem = (*this)[i] - rhs[i];
        });
        return result;
    }

    Vector<K>& operator-=(const Vector<K>& rhs) {
        validate_size(rhs);
        foreach([rhs](K& elem, size_t i) {
            elem -= rhs[i];
        });
        return *this;
    }

    Vector<K> operator*(K scalar) const {
        Vector<K> result(size_);

        result.foreach([this, scalar](K& elem, size_t i) {
            elem = scalar * (*this)[i];
        });
        return result;
    }

    Vector<K>& operator*=(K scalar) {
        foreach([&scalar](K& elem) {
            elem *= scalar;
        });
        return *this;
    }

    K operator*(const Vector<K>& rhs) const {
        return this->dot(rhs);
    }

    size_t get_size() const {
        return size_;
    }

    Matrix<K> to_matrix() {
        Matrix<K> matrix(size_, 1);

        foreach([&matrix](K& elem, size_t i) {
            matrix[i][0] = elem;
        });
        return matrix;
    }

    Vector<K>& add(const Vector<K>& vector) {
        *this += vector;
        return *this;
    }

    Vector<K>& sub(const Vector<K>& vector) {
        *this -= vector;
        return *this;
    }

    Vector<K>& scale(K scalar) {
        *this *= scalar;
        return *this;
    }

    K dot(const Vector<K>& vector) const {
        validate_size(vector);
        K result = K();

        for (size_t i = 0; i < size_; ++i) {
            result = std::fma(data_[i], vector[i], result);
        }
        return result;
    }

    K taxicab_norm() const {
        K result = K();

        foreach([&result](K& elem) {
            if (elem < 0)
                result -= elem;
            else
                result += elem;
        });
        return result;
    }

    K euclidean_norm() const {
        K result = K();

        foreach([&result](K& elem) {
            result = std::fma(elem, elem, result);
        });
        result = std::sqrt(result);
        return result;
    }

    K uniform_norm() const {
        K maximum;

        maximum = std::max(data_[0], -data_[0]);
        foreach([&maximum](K& elem) {
            maximum = std::max(maximum, elem);
            maximum = std::max(maximum, -elem);
        });
        return maximum;
    }

    float angle_cos(const Vector<K>& other) const {
        return this->dot(other) / (this->euclidean_norm() * other.euclidean_norm());
    }

    Vector<K> cross_product(const Vector<K>& other) {
        if (size_ != 3 || other.get_size() != 3) {
            throw VectorException(VECTOR_SIZE_NOT_3_ERROR);
        }
        Vector<K> result(3);

        result[0] = data_[1] * other[2] - data_[2] * other[1];
        result[1] = data_[2] * other[0] - data_[0] * other[2];
        result[2] = data_[0] * other[1] - data_[1] * other[0];
        return result;
    }

    void validate_size(const Vector<K>& other) const {
        if (size_ != other.get_size()) {
            throw VectorException(VECTOR_SIZE_MISMATCH_ERROR);
        }
    }

    template <typename Function>
    auto foreach(Function f)
            -> std::enable_if_t<std::is_invocable_v<Function, K&>> {
        for (size_t i = 0; i < size_; ++i) {
            f(data_[i]);
        }
    }

    template <typename Function>
    auto foreach(Function f)
            -> std::enable_if_t<std::is_invocable_v<Function, K&, size_t>> {
        for (size_t i = 0; i < size_; ++i) {
            f(data_[i], i);
        }
    }

    template <typename Function>
    auto foreach(Function f) const
    -> std::enable_if_t<std::is_invocable_v<Function, K&>> {
        for (size_t i = 0; i < size_; ++i) {
            f(data_[i]);
        }
    }

    template <typename Function>
    auto foreach(Function f) const
    -> std::enable_if_t<std::is_invocable_v<Function, K&, size_t>> {
        for (size_t i = 0; i < size_; ++i) {
            f(data_[i], i);
        }
    }

    class VectorException : public std::exception {
     private:
        std::string error_message_;
     public:
        explicit VectorException(std::string  error_message)
                : error_message_(std::move(error_message)) {}

        const char* what() const _NOEXCEPT {
            return error_message_.c_str();
        }
    };
};

template <typename K>
std::ostream& operator<<(std::ostream& os, const Vector<K>& vector) {
    for (size_t i = 0; i < vector.get_size(); ++i) {
        os << '[' << vector[i]<< ']' << std::endl;
    }
    return os;
}

template <typename K>
Vector<K> operator*(K scalar, const Vector<K>& vector) {
    return vector * scalar;
}

#endif  //  SRC_VECTOR_H_
