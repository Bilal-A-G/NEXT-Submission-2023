#pragma once
#include "ECS/Entity.h"

namespace GAUSS
{
    class ParticlePool final
    {
    public:
        ParticlePool() = delete;
        ~ParticlePool() = delete;
        
        static void Init() {m_pool = std::vector<Entity*>();}
        static void CleanUp() {m_pool.clear();}
        static void Return(Entity* particle);
        static Entity* Query(EntityComponentLookup& entityComponentLookup);
    private:
        static std::vector<Entity*> m_pool;
    };   
}
