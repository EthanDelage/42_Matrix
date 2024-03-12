//  Copyright (c) 2024 Ethan Delage
#ifndef VECTOR_H_
#define VECTOR_H_

#include <exception>
#include <iostream>
#include <string>
#include <utility>

#include "./matrix.h"

template <class K>
class Matrix;

template <class K>
class Vector {
 private:
    size_t  size_;
    K*      data_;

    void validate_size(const Vector<K>& other) const {
        if (size_ != other.get_size()) {
            throw VectorException("Vector size mismatch");
        }
    }

 public:
    explicit Vector(size_t size) : size_(size) {
        data_ = new K[size];
        for (size_t i = 0; i < size; ++i) {
            data_[i] = 0;
        }
    }

    Vector(const Vector<K>& other) {
        data_ = nullptr;
        *this = other;
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
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other[i];
        }
        return *this;
    }

    Vector<K>& operator=(K* values) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = values[i];
        }
        return *this;
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

        for (size_t i = 0; i < size_; ++i) {
            result[i] = data_[i] + rhs[i];
        }
        return result;
    }

    Vector<K>& operator+=(const Vector<K>& rhs) {
        validate_size(rhs);
        for (size_t i = 0; i < size_; ++i) {
            data_[i] += rhs[i];
        }
        return *this;
    }

    Vector<K> operator-(const Vector<K>& rhs) const {
        validate_size(rhs);
        Vector<K> result(size_);

        for (size_t i = 0; i < size_; ++i) {
            result[i] = data_[i] - rhs[i];
        }
        return result;
    }

    Vector<K>& operator-=(const Vector<K>& rhs) {
        validate_size(rhs);
        for (size_t i = 0; i < size_; ++i) {
            data_[i] -= rhs[i];
        }
        return *this;
    }

    Vector<K> operator*(K scalar) const {
        Vector<K> result(size_);

        for (size_t i = 0; i < size_; ++i) {
            result[i] = scalar * data_[i];
        }
        return result;
    }

    Vector<K>& operator*=(K scalar) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] *= scalar;
        }
        return *this;
    }

    size_t get_size() const {
        return size_;
    }

    Matrix<K> to_matrix() {
        Matrix<K> matrix(size_, 1);

        for (size_t i = 0; i < size_; ++i) {
            matrix[i][0] = data_[i];
        }
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

template <typename K>
Vector<K> linear_combination(Vector<K>* vectors, K* scalars, size_t nb_elems) {
    Vector<K> result(vectors[0].get_size());

    for (size_t i = 0; i < nb_elems; ++i) {
        result += (vectors[i] * scalars[i]);
    }
    return result;
}

#endif  //  VECTOR_H_
