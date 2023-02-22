#pragma once
#include "ECS/Component.h"

namespace GAUSS
{
    struct Light : public Component
    {
        std::vector<int> GetEnum() override
        {
            return {GAUSS_ENUMS::Light};
        }
    public:
        float intensity;
    }; 
}
