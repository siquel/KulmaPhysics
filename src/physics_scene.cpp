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

    }

    void PhysicsScene::render() {
        m_window.clear(sf::Color(135, 128, 114));
        

        m_window.display();
    }
}