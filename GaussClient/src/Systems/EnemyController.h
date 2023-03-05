#pragma once
#include "ECS/System.h"

class EnemyController final : public GAUSS::System
{
public:
    void Update(const float& deltaTime, GAUSS::EntityComponentLookup& lookup) override;
    void Disable() override {m_lookup = nullptr;}
private:
    static GAUSS::EntityComponentLookup* m_lookup;
};
