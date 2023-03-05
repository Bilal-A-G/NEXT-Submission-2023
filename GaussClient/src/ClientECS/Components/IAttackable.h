#pragma once
#include "ECS/Component.h"

namespace CLIENT
{
    class IAttackable : public GAUSS::Component
    {
        friend class GAUSS::EntityComponentLookup;
    protected:
        IAttackable() = default;
        ~IAttackable() override = default;
    public:
        virtual void Update(GAUSS::EntityComponentLookup& lookup) = 0;
    };

}