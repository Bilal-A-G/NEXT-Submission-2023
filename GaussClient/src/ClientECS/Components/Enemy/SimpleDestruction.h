#pragma once
#include "ClientECS/Components/ClientEnums.h"
#include "ClientECS/Components/IDestructible.h"
#include "ECS/Systems/Particles/ParticleSystemProperties.h"

namespace CLIENT
{
    class SimpleDestruction final : public IDestructible
   {
       friend class GAUSS::EntityComponentLookup;
    protected:
        SimpleDestruction() : particleProperties(GAUSS::ParticleSystemProperties()), collisionTags(std::vector<std::string>()), useParticles(true) {}
        ~SimpleDestruction() override = default;
    public:
        void Update(GAUSS::EntityComponentLookup& lookup) override;
        std::vector<int> GetEnum() override {return {CLIENT_ENUMS::Destructible, CLIENT_ENUMS::SimpleDestruction};}
    public:
        GAUSS::ParticleSystemProperties particleProperties;
        std::vector<std::string> collisionTags;
        bool useParticles;
   };   
}
