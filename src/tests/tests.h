//  Copyright (c) 2024 Ethan Delage

#ifndef SRC_TESTS_TESTS_H_
#define SRC_TESTS_TESTS_H_

#include "./matrix.h"

void assert_float(float a, float b, float epsilon = 1e-5);
void assert_float_matrix(const Matrix<float>& a,
                         const Matrix<float>& b,
                         float epsilon = 1e-5);

void vector_code_constraints_tests();
void matrix_code_constraints_tests();
void vector_ex00_tests();
void matrix_ex00_tests();
void linear_combination_tests();
void linear_interpolation_tests();
void dot_product_tests();
void vector_norm_tests();
void angle_cos_tests();
void cross_product_tests();
void linear_map_tests();
void matrix_multiplication_tests();
void trace_tests();
void transpose_tests();
void row_echelon_tests();
void determinant_tests();
void inverse_tests();

#endif  //  SRC_TESTS_TESTS_H_
