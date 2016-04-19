#pragma once

#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "physics_types.h"
#include "manifold.h"

namespace kphys {

    struct PhysicsScene {
        sf::RenderWindow m_window;
        std::vector<Body*> m_bodies;
        std::vector<Manifold> m_contacts;
        float m_dt;
        uint32_t m_iterations;

        PhysicsScene(float delta, uint32_t iterations)
            : m_dt(delta), m_iterations(iterations),
            m_window(sf::VideoMode(1280, 720, 32), "PhysicsShit") {
            m_window.setFramerateLimit(60);
        }
        void run();
        void step();
        void render();
        Body* add(Shape* shape, float x, float y);
    };
}