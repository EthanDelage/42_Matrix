//  Copyright (c) 2024 Ethan Delage

#include <cassert>

#include "./vector.h"
#include "./tests.h"

void angle_cos_tests() {
    Vector<float> v1({1., 0.});
    Vector<float> v2({0., 1.});

    assert(1. == v1.angle_cos(v1));
    assert(0. == v1.angle_cos(v2));

    v1 = {2., 1.};
    v2 = {4., 2.};
    assert(1. == v1.angle_cos(v2));

    Vector<float> v3({1., 2., 3.});
    Vector<float> v4({4., 5., 6.});
    assert_float(0.974631846, v3.angle_cos(v4));
}