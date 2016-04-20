#pragma once
#include "config.h"
#include "collision.h"

namespace kphys {

    

    struct Manifold {
        
        Manifold(Body* a, Body* b) 
            : m_a(a), m_b(b), m_contactCount(0), m_e(0), m_penetration(0) {

        }

        Body* m_a;
        Body* m_b;
        // depth
        float m_penetration;
        // A => B
        Vec2 m_normal;
        Vec2 m_contacts[2];
        uint32_t m_contactCount;
        // mixed restitution
        float m_e;

        void solve() {
            polygonToPolygon(this, m_a, m_b);
        }

        void initialize() {
            m_e = std::min(m_a->m_restitution, m_b->m_restitution);

            for (uint32_t i = 0; i < m_contactCount; ++i) {
                Vec2 ra = m_contacts[i] - m_a->m_position;
                Vec2 rb = m_contacts[i] - m_b->m_position;

                // calculate relative velocity

                Vec2 rv = m_b->m_velocity + cross(m_b->m_angularVelocity, rb) - m_a->m_velocity - cross(m_a->m_angularVelocity, ra);
                // TODO FIXXXX
                const static float dt = 1 / 60.f;
                const static float epsilon = 0.001f;
                // only gravity is colliding
                if (lengthSquared(rv) < lengthSquared(g_gravity * dt) + epsilon) {
                    m_e = 0.f;
                }
            }
        }
    };
}