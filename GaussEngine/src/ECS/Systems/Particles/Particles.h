#pragma once
#include "ParticlePool.h"
#include "ParticleSystemProperties.h"
#include "ECS/System.h"
#include "ECS/Entity.h"

namespace GAUSS
{
    class Particles final : public System
    {
        friend class Scene;
    protected:
        Particles() = default;
        ~Particles() override = default;
    public:
        void Update(const float& deltaTime, EntityComponentLookup& lookup) override;
        void Disable() override;
        void Awake() override {ParticlePool::Init();}
        
        static void Play(const ParticleSystemProperties& systemProperties, EntityComponentLookup& lookup);
    private:
        static std::vector<Entity*> m_particles;
    };   
}
