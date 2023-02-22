#pragma once
#include "ECS/ComponentEnums.h"
#include "ECS/System.h"

namespace GAUSS
{
    class Renderer : public System
    {
    public:
        void Render(EntityComponentLookup& lookup) override;
    };   
}
