//  Copyright (c) 2024 Ethan Delage

#include <cassert>

#include "./vector.h"

void cross_product_tests() {
    Vector<float> v1({0., 0., 1.});
    Vector<float> v2({1., 0., 0.});
    Vector<float> vec4({0., 0., 0., 0.});

    assert(Vector<float>({0., 1., 0.}) == v1.cross_product(v2));
    try {
        v1.cross_product(vec4);
        assert(false);
    } catch (const Vector<float>::VectorException& e) {
        assert(e.what() == std::string(VECTOR_SIZE_NOT_3_ERROR));
    }
    try {
        vec4.cross_product(v2);
        assert(false);
    } catch (const Vector<float>::VectorException& e) {
        assert(e.what() == std::string(VECTOR_SIZE_NOT_3_ERROR));
    }
    v1 = {1., 2., 3.};
    v2 = {4., 5., 6.};
    assert(Vector<float>({-3., 6., -3.}) == v1.cross_product(v2));
    v1 = {4., 2., -3.};
    v2 = {-2., -5., 16.};
    assert(Vector<float>({17., -58., -16.}) == v1.cross_product(v2));
}
