#pragma once

#include <stdint.h>

namespace kphys {
    struct PhysicsScene {
        float m_dt;
        uint32_t m_iterations;

        PhysicsScene(float delta, uint32_t iterations)
            : m_dt(delta), m_iterations(iterations) {}

        void step();
        void render();
    };
}