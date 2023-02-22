#pragma once
#include "ECS/Component.h"
#include "Math/Geometry.h"

namespace GAUSS
{
    struct ParticleProperties : public Component
    {
    public:
        std::vector<int> GetEnum() override {return {GAUSS_ENUMS::Particle};}
    public:
        Vector3 rotationAxis = Vector3::Zero();
        Colour endColour = Colour::White();
        float alphaFadeSpeed = 0.0f;
        float colourChangeSpeed = 0.0f;
        float rotationSpeed = 0.0f;
        float lifeTime = 0.0f;
        bool fadeOut = false;
    };   
}
