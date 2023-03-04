#pragma once
#include "ECS/System.h"

class BombSystem final : public GAUSS::System
{
public:
    void Update(const float& deltaTime, GAUSS::EntityComponentLookup& lookup) override;
};
