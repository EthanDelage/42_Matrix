//  Copyright (c) 2024 Ethan Delage

#include <cassert>

#include "./matrix.h"

void row_echelon_tests() {
    Matrix<float> m1({{1., 0., 0.}, {0., 1., 0.}, {0., 0., 1.}});

    assert(m1 == m1.row_echelon());

    Matrix<float> m2({{1., 2.}, {3., 4.}});
    assert(Matrix<float>({{1., 0.}, {0., 1.}}) == m2.row_echelon());

    Matrix<float> m3({{8., 5., -2., 4., 28.},
                      {4., 2.5, 20., 4., -4},
                      {8., 5., 1., 4., 17.}});
    assert(Matrix<float>({{1.0, 0.625, 0.0, 0.0, -12.1666667},
                          {0.0, 0.0, 1.0, 0.0, -3.6666667},
                          {0.0, 0.0, 0.0, 1.0, 29.5}})
                          == m3.row_echelon());
}
