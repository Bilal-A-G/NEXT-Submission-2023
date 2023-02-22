#pragma once

namespace TESLA_ENUMS
{
    enum ComponentEnum : uint8_t
    {
        Mesh = 1,
        Transform,
        Camera,
        RigidBody,
        Collider,
        SphereCollider,
        BoxCollider,
        Light,
        Particle,
        ParticleSystem,
        Last
    };

#define LAST_COMPONENT (TESLA_ENUMS::ComponentEnum::Last  - 1)
}
