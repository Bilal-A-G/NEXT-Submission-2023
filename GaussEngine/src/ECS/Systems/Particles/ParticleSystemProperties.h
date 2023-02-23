#pragma once
#include "Math/Geometry.h"

namespace GAUSS
{
    struct ParticleSystemProperties final
    {
    public:
        ParticleSystemProperties() : position(Vector3()), rotationAxis(Vector3()),
        initialColour(Colour::White()), endColour(Colour::White()), alphaFadeSpeed(0.0f), colourChangeSpeed(0.0f), averageSpeed(0.0f),
        averageRotationSpeed(0.0f), averageSize(0.0f), averageLifetime(0.0f), colourVariation(0.0f), lifetimeVariation(0.0f),
        sizeVariation(0.0f), speedVariation(0.0f), rotationSpeedVariation(0.0f), amount(0), faces(std::vector<Face>()) {}
        ~ParticleSystemProperties() = default;
    public:
        Vector3 position;
        Vector3 rotationAxis;
        Colour initialColour;
        Colour endColour;
        float alphaFadeSpeed;
        float colourChangeSpeed;
        float averageSpeed;
        float averageRotationSpeed;
        float averageSize;
        float averageLifetime;
        float colourVariation;
        float lifetimeVariation;
        float sizeVariation;
        float speedVariation;
        float rotationSpeedVariation;
        int amount;
        std::vector<Face> faces;
    };
}