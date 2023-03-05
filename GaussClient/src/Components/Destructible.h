#pragma once
#include "ClientEnums.h"
#include "ECS/Component.h"
#include "ECS/Systems/Particles/ParticleSystemProperties.h"

namespace CLIENT
{
    class Destructible : public GAUSS::Component
    {
        friend class GAUSS::EntityComponentLookup;
    protected:
        Destructible() : explosionParticleProperties(GAUSS::ParticleSystemProperties()) {}
        ~Destructible() override = default;
    public:
        std::vector<int> GetEnum() override {return {CLIENT_ENUMS::Destructible};}
        virtual void OnDestroy() {return;}
    public:
        GAUSS::ParticleSystemProperties explosionParticleProperties;
    };

}