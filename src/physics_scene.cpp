#include "physics_scene.h"
#include "config.h"
namespace kphys {

    Vec2 g_gravity{ 0.f, 9.81f * 4 };

    void integrateForces(Body* body, float dt) {
        // static obj
        if (body->m_invMass == 0.f) return;

        body->m_velocity += (body->m_force * body->m_invMass + g_gravity) * (0.5f * dt);
    }

    void integrateVelocity(Body* b, float dt) {
        if (b->m_invMass == 0.f) return;

        b->m_position += b->m_velocity * dt;
        b->m_orientRadians += b->m_angularVelocity * dt;
        b->setOrient(b->m_orientRadians);
        integrateForces(b, dt);
    }

    void PhysicsScene::step() {
        m_contacts.clear();

        for (size_t i = 0; i < m_bodies.size(); ++i) {
            Body* a = m_bodies[i];
            for (size_t j = i + 1; j < m_bodies.size(); ++j) {
                Body* b = m_bodies[j];
                // static objs
                if (a->m_invMass == 0 && b->m_invMass == 0) continue;

                // todo manifolds
                Manifold m(a, b);
                m.solve();
                // if objects collided
                if (m.m_contactCount) {
                    m_contacts.emplace_back(m);
                }
            }
        }

        for (auto b : m_bodies) {
            integrateForces(b, m_dt);
        }

        for (uint32_t i = 0; i < m_contacts.size(); ++i) {
            m_contacts[i].initialize();
        }

        for (uint32_t j = 0; j < m_iterations; ++j) {
            for (auto& contact : m_contacts) {
                contact.applyImpulse();
            }
        }

        for (auto* b : m_bodies) {
            integrateVelocity(b, m_dt);
        }

        for (auto& contact : m_contacts) {
            contact.positionalCorrection();
        }
        
        // clear forces
        for (auto b : m_bodies) {
            b->m_force = { 0.f, 0.f };
            //b->torque = 0;
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