#pragma once
#include "Particles.h"

namespace TESLA
{
    class ParticlePool
    {
    public:
        static void Init(){m_pool = std::vector<TESLA::Entity*>();}
        static void CleanUp(){m_pool.clear();}
        static void Return(TESLA::Entity* particle);
        static TESLA::Entity* Query(TESLA::EntityComponentLookup& entityComponentLookup);
    private:
        static std::vector<TESLA::Entity*> m_pool;
    };   
}
