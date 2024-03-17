//  Copyright (c) 2024 Ethan Delage

#include <cassert>

#include "./vector.h"

void dot_product_tests() {
    Vector<float> v1({0., 0.});
    Vector<float> v2({1., 1.});

    assert(0. == v1.dot(v2));
    assert(0. == v2.dot(v1));

    v1 = {1., 1.};
    assert(2. == v1.dot(v2));
    assert(2. == v2.dot(v1));

    v1 = {-1., 6.};
    v2 = {3., 2.};
    assert(9. == v1.dot(v2));
    assert(9. == v2.dot(v1));

    Vector<int> v3({1, 3, -5});
    Vector<int> v4({4, -2, -1});
    assert(3 == v3.dot(v4));
    assert(35 == v3.dot(v3));
}