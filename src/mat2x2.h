#include "math_types.h"
#include <math.h>

namespace kphys {


    Mat2x2 operator*(const Mat2x2& a, const Mat2x2& b) {
        return Mat2x2 {
            a[0][0] * b[0][0] + a[0][1] * b[1][0],
            a[0][0] * b[0][1] + a[0][1] * b[1][1],
            a[1][0] * b[0][0] + a[1][1] * b[1][0],
            a[1][0] * b[0][1] + a[1][1] * b[1][1]
        };
    }

    Vec2 operator*(const Mat2x2& m, const Vec2& v) {
        return Vec2{
            m[0][0] * v[0] + m[0][1] * v[1],
            m[1][0] * v[0] + m[1][1] * v[1]
        };
    }


    void setRotation(Mat2x2& m, float radians) {
        float c = cos(radians);
        float s = sin(radians);
        m[0][0] = c;
        m[0][1] = -s;
        m[1][0] = s;
        m[1][1] = c;
    }
}