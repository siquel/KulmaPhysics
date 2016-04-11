#pragma once
#include <stdint.h>

namespace kphys {
    struct Vec2 {
        float x, y;
        float& operator[](uint32_t i) { return *(&x + i); }
        const float& operator[](uint32_t i) const { return *(&x + i); }
    };

    struct Vec3 {
        float x, y, z;
    };

    struct Rotation {

    };

    struct Mat2x2 {
        union {
            struct {
                float m11, m12;
                float m21, m22;
            };
            struct {
                Vec2 x;
                Vec2 y;
            };

            Vec2 v[2];
        };

        Vec2& operator[](uint32_t i) { return v[i]; }
        const Vec2& operator[](uint32_t i) const { return v[i]; }
    };

    struct Transform {
        Vec2 position;
        Rotation rotation;
    };
}