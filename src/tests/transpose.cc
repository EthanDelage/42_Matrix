//  Copyright (c) 2024 Ethan Delage

#include <cassert>

#include "./matrix.h"

void transpose_tests() {
    Matrix<float> m1({{1., 2.}, {3., 4.}});

    assert(Matrix<float>({{1., 3.}, {2., 4.}}) == m1.transpose());

    Matrix<float> m2({{1., 2., 3.}, {4., 5., 6.}});

    assert(Matrix<float>({{1., 4.}, {2., 5.}, {3., 6.}}) == m2.transpose());
}
