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
        std::vector<TESLA::Vector> GetEdges(TESLA::Vector position, TESLA::Vector rotation) override;
    public:
        float width;
        float height;
    };    
}

