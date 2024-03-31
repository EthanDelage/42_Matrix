//  Copyright (c) 2024 Ethan Delage

#include "tests/tests.h"
#include "./algebra.h"

int main() {
    vector_code_constraints_tests();
    matrix_code_constraints_tests();
    vector_ex00_tests();
    matrix_ex00_tests();
    linear_combination_tests();
    linear_interpolation_tests();
    dot_product_tests();
    vector_norm_tests();
    angle_cos_tests();
    cross_product_tests();
    linear_map_tests();
    matrix_multiplication_tests();
    trace_tests();
    transpose_tests();
    row_echelon_tests();
    determinant_tests();
    inverse_tests();
    rank_tests();

    std::cout << perspective_matrix(90, 1, 0, 10).transpose() << std::endl;
    return 0;
}
