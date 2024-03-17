//  Copyright (c) 2024 Ethan Delage

#include <cassert>

#include "./vector.h"
#include "./matrix.h"

void vector_ex00_tests() {
    Vector<int> vec3(3);
    Vector<int> vec3_bis(3);
    Vector<int> result(3);
    Vector<int> vec4(4);

    try {
        (void) (vec3 + vec4);
        assert(false);
    } catch (Vector<int>::VectorException& e) {
        assert("Vector size mismatch" == std::string(e.what()));
    }
    try {
        (void) (vec3 - vec4);
        assert(false);
    } catch (Vector<int>::VectorException& e) {
        assert("Vector size mismatch" == std::string(e.what()));
    }
    try {
        vec3 -= vec4;
        assert(false);
    } catch (Vector<int>::VectorException& e) {
        assert("Vector size mismatch" == std::string(e.what()));
    }

    for (size_t i = 0; i < vec3.get_size(); ++i) {
        vec3[i] = static_cast<int>(i) + 1;
        assert(vec3[i] == static_cast<int>(i) + 1);
        vec3_bis[i] = static_cast<int>(i) * 2 + 1;
        assert(vec3_bis[i] == static_cast<int>(i) * 2 + 1);
    }

    result = vec3 + vec3_bis;
    for (size_t i = 0; i < vec3.get_size(); ++i) {
        assert(result[i] == vec3[i] + vec3_bis[i]);
    }

    result = vec3 - vec3_bis;
    for (size_t i = 0; i < vec3.get_size(); ++i) {
        assert(result[i] == (vec3[i] - vec3_bis[i]));
    }

    result = 4 * vec3;
    for (size_t i = 0; i < vec3.get_size(); ++i) {
        assert(result[i] == 4 * vec3[i]);
    }

    result = vec3 * 2;
    for (size_t i = 0; i < vec3.get_size(); ++i) {
        assert(result[i] == 2 * vec3[i]);
    }

    result = vec3_bis;
    result += vec3;
    for (size_t i = 0; i < vec3.get_size(); ++i) {
        assert(result[i] == vec3[i] + vec3_bis[i]);
    }
    result = vec3_bis;
    result -= vec3;
    for (size_t i = 0; i < vec3.get_size(); ++i) {
        assert(result[i] == -vec3[i] + vec3_bis[i]);
    }
    result = vec3;
    result *= 2;
    for (size_t i = 0; i < vec3.get_size(); ++i) {
        assert(result[i] == 2 * vec3[i]);
    }

    result = vec3_bis;
    result.add(vec3);
    for (size_t i = 0; i < vec3.get_size(); ++i) {
        assert(result[i] == vec3[i] + vec3_bis[i]);
    }
    result = vec3_bis;
    result.sub(vec3);
    for (size_t i = 0; i < vec3.get_size(); ++i) {
        assert(result[i] == -vec3[i] + vec3_bis[i]);
    }
    result = vec3;
    result.scale(2);
    for (size_t i = 0; i < vec3.get_size(); ++i) {
        assert(result[i] == 2 * vec3[i]);
    }
}

void matrix_ex00_tests() {
    Matrix<float>   mat3x3(3, 3);
    Matrix<float>   mat3x3_bis(3, 3);
    Matrix<float>   result(3, 3);
    Matrix<float>   mat4x3(4, 3);

    try {
        (void) (mat3x3 + mat4x3);
        assert(false);
    } catch (Matrix<float>::MatrixException& e) {
        assert("Matrix shape mismatch" == std::string(e.what()));
    }
    try {
        (void) (mat4x3 - mat3x3_bis);
        assert(false);
    } catch (Matrix<float>::MatrixException& e) {
        assert("Matrix shape mismatch" == std::string(e.what()));
    }


    for (size_t i = 0; i < mat3x3.get_shape().row; ++i) {
        for (size_t j = 0; j < mat3x3.get_shape().column; ++j) {
            mat3x3[i][j] = i * mat3x3.get_shape().column + j + 1.5;
            assert(mat3x3[i][j] == i * mat3x3.get_shape().column + j + 1.5);
            mat3x3_bis[i][j] = i * mat3x3.get_shape().row + j + 2.5;
            assert(mat3x3_bis[i][j] == i * mat3x3.get_shape().row + j + 2.5);
        }
    }


    result = mat3x3 + mat3x3_bis;
    for (size_t i = 0; i < mat3x3.get_shape().row; ++i) {
        for (size_t j = 0; j < mat3x3.get_shape().column; ++j) {
            assert(result[i][j] == mat3x3[i][j] + mat3x3_bis[i][j]);
        }
    }

    result = mat3x3 - mat3x3_bis;
    for (size_t i = 0; i < mat3x3.get_shape().row; ++i) {
        for (size_t j = 0; j < mat3x3.get_shape().column; ++j) {
            assert(result[i][j] == mat3x3[i][j] - mat3x3_bis[i][j]);
        }
    }

    result = 2.f * mat3x3;
    for (size_t i = 0; i < mat3x3.get_shape().row; ++i) {
        for (size_t j = 0; j < mat3x3.get_shape().column; ++j) {
            assert(result[i][j] == 2.f * mat3x3[i][j]);
        }
    }
    result = mat3x3 * 4.;
    for (size_t i = 0; i < mat3x3.get_shape().row; ++i) {
        for (size_t j = 0; j < mat3x3.get_shape().column; ++j) {
            assert(result[i][j] == 4. * mat3x3[i][j]);
        }
    }

    result = mat3x3;
    result += mat3x3_bis;
    for (size_t i = 0; i < mat3x3.get_shape().row; ++i) {
        for (size_t j = 0; j < mat3x3.get_shape().column; ++j) {
            assert(result[i][j] == mat3x3[i][j] + mat3x3_bis[i][j]);
        }
    }
    result = mat3x3;
    result -= mat3x3_bis;
    for (size_t i = 0; i < mat3x3.get_shape().row; ++i) {
        for (size_t j = 0; j < mat3x3.get_shape().column; ++j) {
            assert(result[i][j] == mat3x3[i][j] - mat3x3_bis[i][j]);
        }
    }
    result = mat3x3;
    result *= 2;
    for (size_t i = 0; i < mat3x3.get_shape().row; ++i) {
        for (size_t j = 0; j < mat3x3.get_shape().column; ++j) {
            assert(result[i][j] == 2. * mat3x3[i][j]);
        }
    }
    result = mat3x3;
    result.add(mat3x3_bis);
    for (size_t i = 0; i < mat3x3.get_shape().row; ++i) {
        for (size_t j = 0; j < mat3x3.get_shape().column; ++j) {
            assert(result[i][j] == mat3x3[i][j] + mat3x3_bis[i][j]);
        }
    }
    result = mat3x3;
    result.sub(mat3x3_bis);
    for (size_t i = 0; i < mat3x3.get_shape().row; ++i) {
        for (size_t j = 0; j < mat3x3.get_shape().column; ++j) {
            assert(result[i][j] == mat3x3[i][j] - mat3x3_bis[i][j]);
        }
    }
    result = mat3x3;
    result.scale(2.);
    for (size_t i = 0; i < mat3x3.get_shape().row; ++i) {
        for (size_t j = 0; j < mat3x3.get_shape().column; ++j) {
            assert(result[i][j] == 2. * mat3x3[i][j]);
        }
    }
}
