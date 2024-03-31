//  Copyright (c) 2024 Ethan Delage

#include <cassert>

#include "./tests.h"

void inverse_tests() {
    Matrix<float> m1({{1., 0., 0.}, {0., 1., 0.}, {0., 0., 1.}});

    assert(m1 == m1.inverse());

    m1 *= 2.;
    assert(Matrix<float>({{0.5, 0., 0.},
                          {0., 0.5, 0.},
                          {0., 0., 0.5}})
                          == m1.inverse());

    m1 = {{8., 5., -2.},
          {4., 7., 20.},
          {7., 6., 1.}};
    assert_float_matrix(Matrix<float>({{0.649425287, 0.097701149, -0.655172414},
                                       {-0.781609195, -0.126436782, 0.965517241},
                                       {0.143678161, 0.074712644, -0.206896552}}),
                                       m1.inverse());
}
