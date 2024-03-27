//  Copyright (c) 2024 Ethan Delage

#include <cassert>

#include "./matrix.h"

void determinant_tests() {
    Matrix<float> m1({{1.}});
    assert(1. == m1.determinant());

    Matrix<float> m2({{1., 0.}, {0., 1.}});
    assert(1. == m2.determinant());

    m2 = {{1., -1.}, {-1., 1.}};
    assert(0. == m2.determinant());

    Matrix<float> m3({{2., 0., 0.}, {0., 2., 0.}, {0., 0., 2.}});
    assert(8. == m3.determinant());

    m3 = {{8., 5., -2.},
          {4., 7., 20.},
          {7., 6., 1.}};
    assert(-174. == m3.determinant());

    Matrix<float> m4({{8., 5., -2., 4.},
                      {4., 2.5, 20., 4.},
                      {8., 5., 1., 4.},
                      {28., -4., 17., 1.}});
    assert(1032 == m4.determinant());
}
