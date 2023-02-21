#pragma once
#include "ECS/Component.h"

namespace TESLA
{
    struct Rigidbody : public TESLA::Component
    {
    public:
        std::vector<TESLA_ENUMS::ComponentEnum>  GetEnum() override
        {
            return {TESLA_ENUMS::RigidBody};
        }
    public:
        float mass;
        float friction;
        float restitution;
        bool hasGravity;
        TESLA::Vector velocity;
        TESLA::Vector acceleration;
    };   
}
