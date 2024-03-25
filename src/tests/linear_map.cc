//  Copyright (c) 2024 Ethan Delage

#include <cassert>

#include "./matrix.h"
#include "./vector.h"

void linear_map_tests() {
    Matrix<float> m1({{1., 0.}, {0., 1.}});
    Vector<float> v1({4., 2.});

    assert(Vector<float>({4., 2.}) == (m1 * v1));

    m1 = {{2., 0.}, {0., 2.}};
    assert(Vector<float>({8., 4.}) == (m1 * v1));

    m1 = {{2., -2.}, {-2., 2.}};
    assert(Vector<float>({4., -4.}) == (m1 * v1));
}
