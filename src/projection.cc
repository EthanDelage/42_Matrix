//  Copyright (c) 2024 Ethan Delage

#include <cmath>

#include "./matrix.h"

Matrix<float> perspective_matrix(float fov,
                                float aspect_ratio,
                                float near,
                                float far) {
    Matrix<float> projection(4, 4);

    projection[0][0] = 1 / (aspect_ratio * std::tan(fov / 2));
    projection[1][1] = 1 / std::tan(fov / 2);
    projection[2][2] = - (far + near) / (far - near);
    projection[2][3] = (-2 * far * near) / (far - near);
    projection[3][2] = -1;
    return projection;
}
