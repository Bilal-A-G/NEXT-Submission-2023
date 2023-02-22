#pragma once
#include "ECS/Component.h"

namespace GAUSS
{
    struct Rigidbody : public Component
    {
    public:
        std::vector<int> GetEnum() override
        {
            return {GAUSS_ENUMS::RigidBody};
        }
    public:
        float mass;
        float friction;
        float restitution;
        bool hasGravity;
        Vector3 velocity;
        Vector3 acceleration;
    };   
}
