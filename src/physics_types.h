#pragma once

#include "math_types.h"
#include "vec2.h"

namespace kphys {

    struct Body;

    struct Shape {
        enum Enum {
            Polygon,
            Count
        };

        virtual void draw(sf::RenderWindow&) = 0;
        virtual void setOrient(float radians) = 0;
        Body* m_body;
        Mat2x2 m_u;
    };

    struct Body {
        Shape* m_shape;
        Vec2 m_position;
        Vec2 m_velocity;

        Vec2 m_force;

        float m_mass;
        float m_invMass;
        float m_inertia;
        float m_inverseInertia;

        float m_angularVelocity;

        float m_staticFriction;
        float m_dynamicFriction;
        float m_restitution;

        float m_orientRadians;

        Body(Shape* s, float x, float y)
            : m_shape(s), m_angularVelocity(0), 
            m_orientRadians(0), m_staticFriction(0.5f), m_dynamicFriction(0.3f),
            m_restitution(0.2f) {
            m_position = Vec2{ x, y };
            m_force = Vec2{ 0.f, 0.f };
            m_velocity = Vec2{ 0.f, 0.f };
            m_shape->m_body = this;
        }

        void applyForce(const Vec2& force) {
            m_force += force;
        }

        void applyImpulse(const Vec2& impulse, const Vec2& contact) {
            m_velocity += m_invMass * impulse;
            m_angularVelocity += m_inverseInertia * cross(contact, impulse);
            
        }

        void setOrient(float radians) {
            m_orientRadians = radians;
            m_shape->setOrient(radians);
        }

        void setStatic() {
            m_inertia = m_inverseInertia = m_mass = m_invMass = 0.f;
        }
    };
}