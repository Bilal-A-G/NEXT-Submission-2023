#pragma once

namespace TESLA
{
    enum ComponentEnum
    {
        Null = 0,
        Test = 1
    };

    struct ComponentBase
    {
    public:
        virtual ~ComponentBase() = default;
        virtual ComponentEnum GetEnum() = 0;
    public:
        int m_entityId;
    };

    struct NullComponent : ComponentBase
    {
        ComponentEnum GetEnum() override {return ComponentEnum::Null;}
    };
}
