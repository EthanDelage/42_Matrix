//  Copyright (c) 2024 Ethan Delage

#include <cassert>

#include "./vector.h"
#include "./tests.h"

void vector_norm_tests() {
    Vector<float> v1({0., 0., 0.});
    assert(0. == v1.taxicab_norm());
    assert(0. == v1.euclidean_norm());
    assert(0. == v1.uniform_norm());

    v1 = {1., 2., 3.};
    assert(6. == v1.taxicab_norm());
    assert_float(3.74165738, v1.euclidean_norm());
    assert(3. == v1.uniform_norm());

    Vector<float> v2({-1., -2.});
    assert(3. == v2.taxicab_norm());
    assert_float(2.236067977, v2.euclidean_norm());
    assert(2. == v2.uniform_norm());
}