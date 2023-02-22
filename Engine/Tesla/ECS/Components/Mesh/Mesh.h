#pragma once
#include "ECS/Component.h"
#include "Math/Geometry.h"

namespace TESLA
{
    struct Mesh : public TESLA::Component
    {
        std::vector<int> GetEnum() override
        {
            return {TESLA_ENUMS::ComponentEnum::Mesh};
        }
    public:
        std::vector<Face> faces;
        Colour colour;
    };
}
