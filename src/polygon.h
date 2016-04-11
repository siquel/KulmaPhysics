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

        void draw(sf::RenderWindow& window) {
            sf::ConvexShape poly;
            poly.setPointCount(m_vertexCount);
            for (uint32_t i = 0; i < m_vertexCount; ++i) {
                Vec2 v = m_body->m_position + m_u * m_vertices[i];
                poly.setPoint(i, sf::Vector2f(v.x, v.y));
            }
        }
    };

}