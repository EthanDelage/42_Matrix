//  Copyright (c) 2024 Ethan Delage

#ifndef SRC_ALGEBRA_H_
#define SRC_ALGEBRA_H_

#include <cmath>
#include <exception>
#include <string>

#include "./vector.h"

template <typename K>
Vector<K> linear_combination(
        const Vector<K>* vectors,
        const K* scalars,
        size_t nb_elems) {
    size_t size;
    size = vectors[0].get_size();
    Vector<K> result(size);

    for (size_t i = 0; i < nb_elems; ++i) {
        for (size_t j = 0; j < size; ++j) {
            result[j] = std::fma(vectors[i][j], scalars[i], result[j]);
        }
    }
    return result;
}

template <typename K>
K linear_interpolation(const K& u, const K& v, float t) {
    return u * (1 - t) + v * t;
}

#endif  //  SRC_ALGEBRA_H_
