#include "math_types.h"

namespace kphys {


    Mat2x2 operator*(const Mat2x2& a, const Mat2x2& b) {
        return Mat2x2{
            a[0][0] * b[0][0] + a[0][1] * b[1][0],
            a[0][0] * b[0][1] + a[0][1] * b[1][1],
            a[1][0] * b[0][0] + a[1][1] * b[1][0],
            a[1][0] * b[0][1] + a[1][1] * b[1][1]
        };
    }
}