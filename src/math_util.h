#pragma once

#include <math.h>

namespace kphys {
    const float PI = 3.14159265358979323846f;
    const float TwoPI = 6.28318530717958647693f;
    const float HalfPI = 1.57079632679489661923f;
    const float FloatEpsilon = 1.0e-7f;

    inline bool fequal(float a, float b, float epsilon = FloatEpsilon) {
        return b <= (a + epsilon) && b >= (a - epsilon);
    }

    inline float radians(float degrees) {
        return degrees * static_cast<float>(0.01745329251994329576923690768489);
    }
}