//  Copyright (c) 2024 Ethan Delage

#include <cassert>

#include "./matrix.h"

void trace_tests() {
    Matrix<float> m1({{1., 0.}, {0., 1.}});
    assert(2.0 == m1.trace());

    Matrix<float> m2({{2., -5., 0.}, {4., 3., 7.}, {-2., 3., 4.}});
    assert(9.0 == m2.trace());

    m2 = {{-2., -8., 4.}, {1., -23., 4.}, {0., 6., 4.}};
    assert(-21.0 == m2.trace());
}