#pragma once

namespace kphys {
    struct Vec2 {
        float x, y;
    };

    struct Vec3 {
        float x, y, z;
    };

    struct Rotation {

    };

    struct Transform {
        Vec2 position;
        Rotation rotation;
    };
}