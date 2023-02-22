#pragma once
#include "Math/Geometry.h"

namespace GAUSS
{
    struct ParticleSystemProperties
    {
    public:
        Vector3 position = Vector3::Zero();
        Vector3 rotationAxis = Vector3::Zero();
        Colour initialColour = Colour::Black();
        Colour endColour = Colour::White();
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
        std::vector<Face> faces;
    };
}