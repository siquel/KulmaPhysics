#include "physics_types.h"
#include "vec2.h"
#include <stdint.h>
#include <float.h>
#include <SFML/Graphics.hpp>
#include "mat2x2.h"

namespace kphys {
    
    static const uint32_t MaxVertexCount = 4;

    struct PolygonShape : public Shape {
        uint32_t m_vertexCount;
        Vec2 m_vertices[MaxVertexCount];
        Vec2 m_normals[MaxVertexCount];

        PolygonShape() {
            m_u = { 1.f, 0.f, 0.f, 1.f };
        }

        void setAsBox(float halfWidth, float halfHeight) {
            m_vertexCount = 4;
            m_vertices[0] = vec2(-halfWidth, -halfHeight);
            m_vertices[1] = vec2(halfWidth, -halfHeight);
            m_vertices[2] = vec2(halfWidth, halfHeight);
            m_vertices[3] = vec2(-halfWidth, halfHeight);
            m_normals[0] = vec2(0.0f, -1.f);
            m_normals[1] = vec2(1.0f, 0.f);
            m_normals[2] = vec2(0.0f, 1.f);
            m_normals[3] = vec2(-1.0f, 0.f);
        }

        Vec2 getSupport(const Vec2& dir) {
            float bestProjection = -FLT_MAX;
            Vec2 bestVertex{ 0, 0 };

            for (uint32_t i = 0; i < m_vertexCount; ++i) {
                Vec2& v = m_vertices[i];
                float projection = dot(v, dir);
                if (projection > bestProjection) {
                    bestVertex = v;
                    bestProjection = projection;
                }
            }
            return bestVertex;
        }

        void draw(sf::RenderWindow& window) override {
            sf::ConvexShape poly;
            poly.setPointCount(m_vertexCount);
            for (uint32_t i = 0; i < m_vertexCount; ++i) {
                Vec2 v = m_body->m_position + m_u * m_vertices[i];
                poly.setPoint(i, sf::Vector2f(v.x, v.y));
            }
            poly.setFillColor(sf::Color::Red);
            window.draw(poly);
        }

        void setOrient(float radians) override {
            setRotation(m_u, radians);
        }

        void computeMass(float density) override
        {
            // Calculate centroid and moment of interia
            Vec2 c{ 0.0f, 0.0f }; // centroid
            float area = 0.0f;
            float I = 0.0f;
            const float k_inv3 = 1.0f / 3.0f;

            for (uint32_t i1 = 0; i1 < m_vertexCount; ++i1)
            {
                // Triangle vertices, third vertex implied as (0, 0)
                Vec2 p1(m_vertices[i1]);
                uint32_t i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
                Vec2 p2(m_vertices[i2]);

                float D = cross(p1, p2);
                float triangleArea = 0.5f * D;

                area += triangleArea;

                // Use area to weight the centroid average, not just vertex position
                c += triangleArea * k_inv3 * (p1 + p2);

                float intx2 = p1.x * p1.x + p2.x * p1.x + p2.x * p2.x;
                float inty2 = p1.y * p1.y + p2.y * p1.y + p2.y * p2.y;
                I += (0.25f * k_inv3 * D) * (intx2 + inty2);
            }

            c *= 1.0f / area;

            // Translate vertices to centroid (make the centroid (0, 0)
            // for the polygon in model space)
            // Not floatly necessary, but I like doing this anyway
            for (uint32_t i = 0; i < m_vertexCount; ++i)
                m_vertices[i] -= c;

            m_body->m_mass = density * area;
            m_body->m_invMass = (m_body->m_mass) ? 1.0f / m_body->m_mass : 0.0f;
            m_body->m_inertia = I * density;
            m_body->m_inverseInertia = m_body->m_inertia ? 1.0f / m_body->m_inertia : 0.0f;
        }
    };

}