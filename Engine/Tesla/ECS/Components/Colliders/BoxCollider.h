#pragma once
#include "Collider.h"

namespace TESLA
{
    struct BoxCollider : public TESLA::Collider
    {
    public:
        std::vector<TESLA_ENUMS::ComponentEnum> GetEnum() override
        {
            return {TESLA_ENUMS::BoxCollider, TESLA_ENUMS::Collider};
        }
        std::vector<TESLA::Vector> GetAxes(TESLA::Vector position, TESLA::Vector rotation, TESLA::Vector otherPosition) override;
        std::vector<TESLA::Vector> GetVertices(TESLA::Vector position, TESLA::Vector rotation,  TESLA::Vector otherPosition) override;
    public:
        float width;
        float height;
    };    
}

