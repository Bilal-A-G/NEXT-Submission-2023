#pragma once
#include "ECS/System.h"

class Explosion final : public GAUSS::System
{
public:
    void Update(const float& deltaTime, GAUSS::EntityComponentLookup& lookup) override;
    void Disable() override {m_bombParticles.clear();}
private:
    std::vector<GAUSS::Entity*> m_bombParticles;
};
