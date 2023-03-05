#pragma once
#include "ClientEnums.h"
#include "ECS/Component.h"
#include "Math/Math.h"

namespace CLIENT
{
    class Enemy : public GAUSS::Component
    {
        friend class GAUSS::EntityComponentLookup;
    protected:
        Enemy() : moveDirection(GAUSS::Vector3::Zero()), moveSpeed(0) {}
        ~Enemy() override = default;
    public:
        std::vector<int> GetEnum() override {return {CLIENT_ENUMS::Enemy};}
        virtual void OnHitWall(GAUSS::EntityComponentLookup& lookup) {moveDirection *= -1;}
    public:
        GAUSS::Vector3 moveDirection;
        float moveSpeed;
    };    
}

