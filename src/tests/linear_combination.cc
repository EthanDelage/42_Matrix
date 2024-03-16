//  Copyright (c) 2024 Ethan Delage

#include <cassert>

#include "./algebra.h"

void linear_combination_tests() {
    Vector<float> v1(3);
    v1[0] = 1.;
    Vector<float> v2(3);
    v2[1] = 1.;
    Vector<float> v3(3);
    v3[2] = 1.;
    Vector<float> vectors_list[] = {v1, v2, v3};
    float scalars_value[] = {10., -2., 0.5};

    float e1_values[] = {1., 2., 3.};
    Vector<float> e1(3);
    e1 = e1_values;
    float e2_values[]= {0., 10., -100.};
    Vector<float> e2(3);
    e2 = e2_values;
    Vector<float> vectors_list_bis[] = {e1, e2};

    Vector<float> result = linear_combination(vectors_list, scalars_value, 3);

    assert(result[0] == 10.);
    assert(result[1] == -2.);
    assert(result[2] == 0.5);

    result = linear_combination(vectors_list_bis, scalars_value, 2);

    assert(result[0] == 10.);
    assert(result[1] == 0.);
    assert(result[2] == 230.);
}
