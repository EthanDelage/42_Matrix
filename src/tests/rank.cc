//  Copyright (c) 2024 Ethan Delage

#include <cassert>

#include "./tests.h"

void rank_tests() {
    Matrix<float> m1({{1., 0., 0.}, {0., 1., 0.}, {0., 0., 1.}});
    assert(3 == m1.rank());

    Matrix<float> m2({{1., 2., 0., 0.}, {2., 4., 0., 0.}, {-1., 2., 1., 1.}});
    assert(2 == m2.rank());

    Matrix<float> m3({{8., 5., -2.},
                      {4., 7., 20.},
                      {7., 6., 1.},
                      {21., 18., 7.}});
    assert(3 == m3.rank());
}
