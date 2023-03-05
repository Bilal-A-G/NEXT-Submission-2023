#pragma once
#include "ECS/Component.h"

namespace CLIENT
{
    class IMovable : public GAUSS::Component
    {
        friend class GAUSS::EntityComponentLookup;
    protected:
        IMovable() = default;
        ~IMovable() override = default;
    public:
        virtual void Update(GAUSS::EntityComponentLookup& lookup, const float& deltaTime) = 0;
    };
}
