//  Copyright (c) 2024 Ethan Delage

#include <cassert>

#include "./matrix.h"

void matrix_multiplication_tests() {
    Matrix<float> m1({{1., 0.}, {0., 1.}});
    Matrix<float> m2(m1);

    assert(m1 == (m1 * m2));

    m2 = {{2., 1.}, {4., 2.}};
    assert(Matrix<float>({{2., 1.}, {4., 2.}}) == (m1 * m2));

    m1 = {{3., -5.}, {6., 8.}};
    assert(Matrix<float>({{-14., -7.}, {44., 22.}}) == (m1 * m2));
}
