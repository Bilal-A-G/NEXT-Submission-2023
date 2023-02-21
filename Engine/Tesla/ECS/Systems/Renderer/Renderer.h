#pragma once
#include "ECS/ComponentEnums.h"
#include "ECS/System.h"

namespace TESLA
{
    class Renderer : public TESLA::System
    {
    public:
        void Render(TESLA::EntityComponentLookup& lookup) override;
    };   
}
