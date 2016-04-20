#include "collision.h"
#include "polygon.h"
#include "manifold.h"
#include <assert.h>


    namespace kphys {

        float findAxisLeastPenetration(uint32_t* faceIndex, PolygonShape* a, PolygonShape* b) {
            float bestDistance = -FLT_MAX;
            uint32_t bestIndex;

            for (uint32_t i = 0; i < a->m_vertexCount; ++i) {
                Vec2 n = a->m_normals[i];
                Vec2 nw = a->m_u * n;

                // transpose
                Mat2x2 transpose = Mat2x2{ b->m_u[0][0], b->m_u[1][0], b->m_u[0][1], b->m_u[1][1] };
                // transform to b model space
                n = transpose * nw;

                Vec2 s = b->getSupport(-n);

                Vec2 v = a->m_vertices[i];
                v = a->m_u * v + a->m_body->m_position;
                v -= b->m_body->m_position;
                v = transpose * v;

                // compute penetration distnace
                float d = dot(n, s - v);
                if (d > bestDistance) {
                    bestDistance = d;
                    bestIndex = i;
                }
            }
            *faceIndex = bestIndex;
            return bestDistance;
        }

        bool biasGT(float a, float b) {
            float relative = 0.95f;
            float absolute = 0.01f;
            return a >= b * relative + a * absolute;
        }

        void findIncidentFace(Vec2* v, PolygonShape* refPoly, PolygonShape* incPoly, uint32_t refindex) {
            Vec2 refn = refPoly->m_normals[refindex];

            refn = refPoly->m_u * refn; // world space
            Mat2x2 transpose = Mat2x2{ incPoly->m_u[0][0], incPoly->m_u[1][0], incPoly->m_u[0][1], incPoly->m_u[1][1] };
            refn = transpose * refn; // model space

            uint32_t incface = 0;
            float mindot = FLT_MAX;
            for (uint32_t i = 0; i < incPoly->m_vertexCount; ++i) {
                float d = dot(refn, incPoly->m_normals[i]);
                if (d < mindot) {
                    mindot = d;
                    incface = i;
                }
            }

            v[0] = incPoly->m_u * incPoly->m_vertices[incface] + incPoly->m_body->m_position;
            incface = incface + 1 >= incPoly->m_vertexCount ? 0 : incface + 1;
            v[1] = incPoly->m_u * incPoly->m_vertices[incface] + incPoly->m_body->m_position;
        }

        int32_t clip(Vec2 n, float c, Vec2* face) {
            uint32_t sp = 0;
            Vec2 out[2] = {
                face[0], face[1]
            };

            float d1 = dot(n, face[0]) - c;
            float d2 = dot(n, face[1]) - c;

            if (d1 <= 0.f) out[sp++] = face[0];
            if (d2 <= 0.f) out[sp++] = face[1];
            // If the points are on different sides of the plane
            if (d1 * d2 < 0.f) {
                float a = d1 / (d1 - d2);
                out[sp] = face[0] + a * (face[1] - face[0]);
                ++sp;
            }

            face[0] = out[0];
            face[1] = out[1];

            assert(sp != 3);
            return sp;
        }

        void polygonToPolygon(Manifold* m, Body* _a, Body* _b)
        {
            PolygonShape* a = static_cast<PolygonShape*>(_a->m_shape);
            PolygonShape* b = static_cast<PolygonShape*>(_b->m_shape);
            m->m_contactCount = 0;

            uint32_t faceA{ 0 };
            float penetrationA = findAxisLeastPenetration(&faceA, a, b);
            if (penetrationA >= 0.f) return;

            uint32_t faceB{ 0 };
            float penetrationB = findAxisLeastPenetration(&faceB, b, a);
            if (penetrationB >= 0.f) return;

            uint32_t refIndex; // which index
            bool flip = false; // should we flip the result
            PolygonShape* refPoly = nullptr; // 
            PolygonShape* incPoly = nullptr; //

            if (biasGT(penetrationA, penetrationB)) {
                refPoly = a;
                incPoly = b;
                refIndex = faceA;
                flip = false;
            }
            else {
                refPoly = b;
                incPoly = a;
                refIndex = faceB;
                flip = true;
            }

            Vec2 incidentFace[2];
            findIncidentFace(incidentFace, refPoly, incPoly, refIndex);

            Vec2 v1 = refPoly->m_vertices[refIndex];
            refIndex = refIndex + 1 == refPoly->m_vertexCount ? 0 : refIndex + 1;
            Vec2 v2 = refPoly->m_vertices[refIndex];


            // transform to world space
            v1 = refPoly->m_u * v1 + refPoly->m_body->m_position;
            v2 = refPoly->m_u * v2 + refPoly->m_body->m_position;

            Vec2 sideplaneNormal = v2 - v1;
            sideplaneNormal = normalize(sideplaneNormal);

            Vec2 refFaceNormal = { sideplaneNormal[1], -sideplaneNormal[0] };


            float refC = dot(refFaceNormal, v1);
            float negSide = -dot(sideplaneNormal, v1);
            float posside = dot(sideplaneNormal, v2);


            if (clip(-sideplaneNormal, negSide, incidentFace) < 2) return;
            if (clip(sideplaneNormal, posside, incidentFace) < 2) return;

            m->m_normal = flip ? -refFaceNormal : refFaceNormal;

            uint32_t cp = 0;
            float separation = dot(refFaceNormal, incidentFace[0]) - refC;
            if (separation <= 0.f) {
                m->m_contacts[cp] = incidentFace[0];
                m->m_penetration = -separation;
                ++cp;
            }
            else {
                m->m_penetration = 0;
            }

            separation = dot(refFaceNormal, incidentFace[1]) - refC;
            if (separation <= 0.f) {
                m->m_contacts[cp] = incidentFace[1];
                m->m_penetration += -separation;
                ++cp;
                // avg
                m->m_penetration /= float(cp);
            }
            m->m_contactCount = cp;
        }
    }
