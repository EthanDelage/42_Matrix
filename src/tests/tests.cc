//  Copyright (c) 2024 Ethan Delage

#include <cassert>
#include <cmath>

#include "./tests.h"

void assert_float(float a, float b, float epsilon) {
    assert(std::abs(a - b) < epsilon);
}

void assert_float_matrix(const Matrix<float>& a,
                         const Matrix<float>& b,
                         float epsilon) {
    a.foreach([b, epsilon](float& elem, size_t row, size_t column) {
        assert_float(elem, b[row][column], epsilon);
    });
}
