#pragma once

namespace kphys {
    struct Body;
    struct Manifold;

    void polygonToPolygon(Manifold* m, Body* _a, Body* _b);
}
