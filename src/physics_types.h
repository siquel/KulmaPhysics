#pragma once

#include "math_types.h"

namespace kphys {

    struct Shape {

    };

    struct MassData {
        float mass;
        float invMass;
        float inertia;
        float invInertia;
    };

    struct Body {
        Shape* shape;

    };
}