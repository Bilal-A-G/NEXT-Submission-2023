#pragma once
#include "ECS/Component.h"
#include "Math/Geometry.h"

namespace GAUSS
{
    struct Mesh final : public Component
    {
        friend class EntityComponentLookup;
    protected:
        Mesh() : faces(std::vector<Face>()), colour(Colour::White()) {}
        ~Mesh() override = default;
    public:
        std::vector<int> GetEnum() override {return {GAUSS_ENUMS::ComponentEnum::Mesh};}
    public:
        std::vector<Face> faces;
        Colour colour;
    };
}
