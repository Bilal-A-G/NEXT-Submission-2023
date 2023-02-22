#pragma once
#include "ECS/Component.h"
#include "Math/Geometry.h"

namespace GAUSS
{
    struct Mesh : public Component
    {
        std::vector<int> GetEnum() override
        {
            return {GAUSS_ENUMS::ComponentEnum::Mesh};
        }
    public:
        std::vector<Face> faces;
        Colour colour;
    };
}
