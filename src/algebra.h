//  Copyright (c) 2024 Ethan Delage

#ifndef SRC_ALGEBRA_H_
#define SRC_ALGEBRA_H_

#include <exception>
#include <string>

#include "./vector.h"

template <typename K>
Vector<K> linear_combination(
        const Vector<K>* vectors,
        const K* scalars,
        size_t nb_elems) {
    Vector<K> result(vectors[0].get_size());

    for (size_t i = 0; i < nb_elems; ++i) {
        result += (vectors[i] * scalars[i]);
    }
    return result;
}

template <typename K>
K linear_interpolation(const K& u, const K& v, float t) {
    return u * (1 - t) + v * t;
}

#endif  //  SRC_ALGEBRA_H_
