#pragma once
#include "ParticleSystemProperties.h"
#include "ECS/System.h"
#include "ECS/Entity.h"

namespace GAUSS
{
    class Particles : public System
    {
    public:
        void Update(float deltaTime, EntityComponentLookup& lookup) override;
        void Disable() override;
        void Awake() override;
        static void Play(const ParticleSystemProperties& particleSystem, EntityComponentLookup& lookup);
    private:
        static std::vector<Entity*> m_particles;
    };   
}
