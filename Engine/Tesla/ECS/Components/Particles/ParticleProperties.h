﻿#pragma once
#include "ECS/Component.h"
#include "Math/Geometry.h"

namespace TESLA
{
    struct ParticleProperties : public TESLA::Component
    {
    public:
        std::vector<int> GetEnum() override {return {TESLA_ENUMS::Particle};}
    public:
        TESLA::Vector3 rotationAxis = TESLA::Vector3::Zero();
        TESLA::Colour endColour = TESLA::Colour::White();
        float alphaFadeSpeed = 0.0f;
        float colourChangeSpeed = 0.0f;
        float rotationSpeed = 0.0f;
        float lifeTime = 0.0f;
        bool fadeOut = false;
    };   
}
