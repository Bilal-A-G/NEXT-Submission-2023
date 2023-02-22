#pragma once
#include "ECS/Component.h"

namespace TESLA
{
    struct Rigidbody : public TESLA::Component
    {
    public:
        std::vector<int> GetEnum() override
        {
            return {TESLA_ENUMS::RigidBody};
        }
    public:
        float mass;
        float friction;
        float restitution;
        bool hasGravity;
        TESLA::Vector3 velocity;
        TESLA::Vector3 acceleration;
    };   
}
