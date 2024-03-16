//  Copyright (c) 2024 Ethan Delage

#include <cassert>

#include "./algebra.h"
#include "./vector.h"
#include "./matrix.h"

void linear_interpolation_tests() {
    assert(0.0 == linear_interpolation(0., 1., 0.));
    assert(1.0 == linear_interpolation(0., 1., 1.));
    assert(0.5 == linear_interpolation(0., 1., 0.5));
    assert(
            Vector<float>({2.6, 1.3}) ==
            linear_interpolation(
                   Vector<float>({2., 1.}),
                   Vector<float>({4., 2.}),
                   0.3));
    assert(
            Matrix<float>({{11., 5.5}, {16.5, 22.}}) ==
            linear_interpolation(
                   Matrix<float>({{2., 1.}, {3., 4.}}),
                   Matrix<float>({{20., 10.}, {30., 40.}}),
                   0.5));
}
