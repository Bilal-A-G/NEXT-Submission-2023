#pragma once
#include "ECS/Component.h"
#include "Math/Math.h"

namespace GAUSS
{
    struct Rigidbody final : public Component
    {
        friend class EntityComponentLookup;
    protected:
        Rigidbody() : mass(0), friction(0), hasGravity(true),
        velocity(Vector3::Zero()), acceleration(Vector3::Zero()), isStatic(false) {}
        ~Rigidbody() override = default;
    public:
        std::vector<int> GetEnum() override {return {GAUSS_ENUMS::RigidBody};}
    public:
        float mass;
        float friction;
        bool isStatic;
        bool hasGravity;
        Vector3 velocity;
        Vector3 acceleration;
    };   
}
