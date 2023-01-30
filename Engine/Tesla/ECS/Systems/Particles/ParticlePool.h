#pragma once
#include "Particles.h"

namespace TESLA
{
    class ParticlePool
    {
    public:
        static void Init(){m_pool = std::vector<TESLA::Particle*>();}
        static void CleanUp(){m_pool.clear();}
        static void Return(TESLA::Particle* particle);
        static TESLA::Particle* Query();
    private:
        static std::vector<TESLA::Particle*> m_pool;
    };   
}
