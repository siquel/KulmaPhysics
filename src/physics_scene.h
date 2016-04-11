#pragma once

#include <stdint.h>
#include <SFML/Graphics.hpp>

namespace kphys {
    struct PhysicsScene {
        sf::RenderWindow m_window;

        float m_dt;
        uint32_t m_iterations;

        PhysicsScene(float delta, uint32_t iterations)
            : m_dt(delta), m_iterations(iterations),
            m_window(sf::VideoMode(1280, 720, 32), "PhysicsShit") {
            
        }
        void run();
        void step();
        void render();
    };
}