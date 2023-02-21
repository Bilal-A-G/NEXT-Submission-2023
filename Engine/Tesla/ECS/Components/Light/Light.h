#pragma once
#include "ECS/Component.h"

namespace TESLA
{
    struct Light : public TESLA::Component
    {
        std::vector<TESLA_ENUMS::ComponentEnum> GetEnum() override
        {
            return {TESLA_ENUMS::Light};
        }
    public:
        float intensity;
    }; 
}
