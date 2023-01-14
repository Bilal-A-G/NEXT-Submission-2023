#pragma once
#include "../../../ECS/Component.h"

namespace TESLA
{
    struct Collider : public TESLA::Component
    {
        virtual std::vector<TESLA::Vector> GetAxes(TESLA::Vector position, TESLA::Matrix4x4 rotation, TESLA::Vector otherPosition) = 0;
        virtual std::vector<TESLA::Vector> GetVertices(TESLA::Vector position, TESLA::Matrix4x4 rotation, TESLA::Vector otherPosition) = 0;
    };    
}

