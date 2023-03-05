#pragma once
#include "ECS/Component.h"

namespace CLIENT
{
    class IDestructible : public GAUSS::Component
    {
        friend class GAUSS::EntityComponentLookup;
    protected:
        IDestructible() = default;
        ~IDestructible() override = default;
    public:
        virtual void Update(GAUSS::EntityComponentLookup& lookup) = 0;
    };

}