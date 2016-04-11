#pragma once

#include "math_types.h"

namespace kphys {

    struct Body;

    struct Shape {
        enum Enum {
            Polygon,
            Count
        };

        Body* m_body;
        Mat2x2 m_u;
    };

    struct MassData {
        float m_mass;
        float m_invMass;
        float m_inertia;
        float m_invInertia;
    };

    struct Body {
        Shape* m_shape;
        Vec2 m_position;
        Vec2 m_linearVelocity;
    };
}