#pragma once

namespace TESLA_ENUMS
{
    enum ComponentEnum : uint8_t
    {
        Null = 0,
        Mesh = 1,
        Transform = 2,
        Camera = 3
    };
}


namespace TESLA
{
    struct Component
    {
    public:
        virtual ~Component() = default;
        virtual TESLA_ENUMS::ComponentEnum GetEnum() = 0;
    public:
        uint32_t m_entityId;
    };

    struct NullComponent : Component
    {
        TESLA_ENUMS::ComponentEnum GetEnum() override {return TESLA_ENUMS::ComponentEnum::Null;}
    };
}
