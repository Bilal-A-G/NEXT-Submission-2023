#pragma once

namespace GAUSS_ENUMS
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
}
