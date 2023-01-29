#pragma once

namespace TESLA_ENUMS
{
    enum ComponentEnum : uint8_t
    {
        Mesh = 1,
        Transform = 2,
        Camera = 3,
        RigidBody = 4,
        Collider = 5,
        SphereCollider = 6,
        BoxCollider = 7,
        Light = 8,
    };
}


namespace TESLA
{
    struct Component
    {
    public:
        virtual ~Component() = default;
        virtual std::vector<TESLA_ENUMS::ComponentEnum> GetEnum() = 0;
    public:
        uint32_t m_entityId;
    };
}
