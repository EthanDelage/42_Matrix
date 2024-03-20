//  Copyright (c) 2024 Ethan Delage

#include <cassert>

#include "./vector.h"

void angle_cos_tests() {
    Vector<float> v1({1., 0.});
    Vector<float> v2({0., 1.});

    assert(1. == v1.angle_cos(v1));
    assert(0. == v1.angle_cos(v2));

    v1 = {2., 1.};
    v2 = {4., 2.};
    assert(1. == v1.angle_cos(v2));
}