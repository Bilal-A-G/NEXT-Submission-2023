#pragma once
#include "../../../ECS/Component.h"
#include "../../../Math/Geometry.h"

namespace TESLA
{
    struct Mesh : public TESLA::Component
    {
        Mesh()
        {
            colour = Colour::White();
        }
        
        std::vector<TESLA_ENUMS::ComponentEnum>  GetEnum() override
        {
            return {TESLA_ENUMS::ComponentEnum::Mesh};
        }
    public:
        std::vector<Face> faces;
        Colour colour;
    };
}
