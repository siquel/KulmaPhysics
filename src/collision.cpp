#include "collision.h"
#include "polygon.h"
#include "manifold.h"


    namespace kphys {
        void polygonToPolygon(Manifold* m, Body* _a, Body* _b)
        {
            PolygonShape* a = static_cast<PolygonShape*>(_a->m_shape);
            PolygonShape* b = static_cast<PolygonShape*>(_b->m_shape);
            m->m_contactCount = 0;
        }
    }
