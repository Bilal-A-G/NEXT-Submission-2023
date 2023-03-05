#pragma once
#include "ECS/System.h"

namespace CLIENT
{
    class BehaviourUpdater final : public GAUSS::System
    {
        friend class GAUSS::Scene;
    protected:
        BehaviourUpdater() = default;
        ~BehaviourUpdater() override = default;
    public:
        void Update(const float& deltaTime, GAUSS::EntityComponentLookup& lookup) override;
    };   
}
