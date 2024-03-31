//  Copyright (c) 2024 Ethan Delage

#ifndef SRC_ALGEBRA_H_
#define SRC_ALGEBRA_H_

#include <cmath>
#include <exception>
#include <string>

#include "./vector.h"
#include "./matrix.h"

Matrix<float> perspective_matrix(float fov,
                                float aspect_ratio,
                                float near,
                                float far);

template <typename K>
Vector<K> linear_combination(
        const Vector<K>* vectors,
        const K* scalars,
        size_t nb_elems) {
    size_t size;
    size = vectors[0].get_size();
    Vector<K> result(size);

    result.foreach([vectors, scalars, nb_elems](K& elem, size_t j) {
         for (size_t i = 0; i < nb_elems; ++i) {
             elem = std::fma(vectors[i][j], scalars[i], elem);
         }
    });
    return result;
}

template <typename K>
K linear_interpolation(const K& u, const K& v, float t) {
    return (v - u) * t + u;
}

#endif  //  SRC_ALGEBRA_H_
