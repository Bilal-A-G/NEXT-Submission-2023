#pragma once
#include "Math/Geometry.h"

namespace TESLA
{
    struct ParticleSystemProperties
    {
    public:
        TESLA::Vector3 position = TESLA::Vector3::Zero();
        TESLA::Vector3 rotationAxis = TESLA::Vector3::Zero();
        TESLA::Colour initialColour = TESLA::Colour::Black();
        TESLA::Colour endColour = TESLA::Colour::White();
        float alphaFadeSpeed = 0.0f;
        float colourChangeSpeed = 0.0f;
        float averageSpeed = 0.0f;
        float averageRotationSpeed = 0.0f;
        float averageSize = 0.0f;
        float averageLifetime = 0.0f;
        float colourVariation = 0.0f;
        float lifetimeVariation = 0.0f;
        float sizeVariation = 0.0f;
        float speedVariation = 0.0f;
        float rotationSpeedVariation = 0.0f;
        int amount = 0;
        std::vector<TESLA::Face> faces;
    };
}