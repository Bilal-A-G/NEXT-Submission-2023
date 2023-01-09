#pragma once
#include "../../../ECS/Component.h"

namespace TESLA
{
    struct Collider : public TESLA::Component
    {
        virtual std::vector<TESLA::Vector> GetEdges(TESLA::Vector position, TESLA::Vector rotation) = 0;
    };    
}

