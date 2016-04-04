#pragma once

namespace kphys {

    struct Shape {

    };

    struct Transform {

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