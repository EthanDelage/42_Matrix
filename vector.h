//  Copyright (c) 2024 Ethan Delage
#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>

#include "./matrix.h"

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

    const K& operator[](size_t index) const {
        return data_[index];
    }

    K& operator[](size_t index) {
        return data_[index];
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
};

template <typename K>
std::ostream& operator<<(std::ostream& os, const Vector<K>& vector) {
    for (size_t i = 0; i < vector.get_size(); ++i) {
        os << '[' << vector[i]<< ']' << std::endl;
    }
    return os;
}

#endif  //  VECTOR_H_
