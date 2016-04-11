#pragma once

#include "math_types.h"

namespace kphys {

    struct Body;

    struct Shape {
        enum Enum {
            Polygon,
            Count
        };

        virtual void draw(sf::RenderWindow&) = 0;

        Body* m_body;
        Mat2x2 m_u;
    };

    struct MassData {
        float m_mass;
        float m_invMass;
        float m_inertia;
        float m_invInertia;
    };

    struct Body {
        Shape* m_shape;
        Vec2 m_position;
        Vec2 m_velocity;

        Body(Shape* s, float x, float y)
            : m_shape(s) {
            m_position = Vec2{ x, y };
            m_velocity = Vec2{ 0.f, 0.f };
            m_shape->m_body = this;
        }
    };
}