#pragma once
#include "ParticleSystemProperties.h"
#include "ECS/System.h"
#include "ECS/Entity.h"

namespace TESLA
{
    class Particles : public TESLA::System
    {
    public:
        void Update(float deltaTime, TESLA::EntityComponentLookup& lookup) override;
        void Disable() override;
        void Awake() override;
        static void Play(const TESLA::ParticleSystemProperties& particleSystem, EntityComponentLookup& lookup);
    private:
        static std::vector<Entity*> m_particles;
    };   
}
