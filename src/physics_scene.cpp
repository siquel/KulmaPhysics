#include "physics_scene.h"

namespace kphys {

    void PhysicsScene::run() {
        while (m_window.isOpen()) {
            sf::Event Event;
            while (m_window.pollEvent(Event))
            {
                if (Event.type == sf::Event::Closed)
                    m_window.close();
            }
            step();
            render();
        }
    }

    void PhysicsScene::step() {
        m_contacts.clear();

        for (size_t i = 0; i < m_bodies.size(); ++i) {
            Body* a = m_bodies[i];
            for (size_t j = i + i; j < m_bodies.size(); ++j) {
                Body* b = m_bodies[j];
                // static objs
                if (a->m_invMass == 0 && b->m_invMass == 0) continue;

                // todo manifolds
            }
        }
    }

    void PhysicsScene::render() {
        m_window.clear(sf::Color(135, 128, 114));
        
        for (auto body : m_bodies) {
            body->m_shape->draw(m_window);
        }

        m_window.display();
    }

    Body* PhysicsScene::add(Shape* shape, float x, float y) {
        m_bodies.push_back(new Body(shape, x, y));
        return m_bodies.back();
    }
}