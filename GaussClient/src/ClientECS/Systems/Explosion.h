#pragma once
#include "ECS/System.h"

namespace CLIENT
{
    class Explosion final : public GAUSS::System
    {
        friend class GAUSS::Scene;
    protected:
        Explosion() = default;
        ~Explosion() override = default;
    public:
        void Update(const float& deltaTime, GAUSS::EntityComponentLookup& lookup) override;
        void Disable() override {m_bombParticles.clear();}
    private:
        std::vector<GAUSS::Entity*> m_bombParticles;
    };    
}

