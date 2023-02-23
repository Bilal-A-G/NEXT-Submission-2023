#pragma once
#include "ECS/Component.h"
#include "Math/Geometry.h"

namespace GAUSS
{
    struct ParticleProperties final : public Component
    {
        friend class EntityComponentLookup;
    protected:
        ParticleProperties() : rotationAxis(Vector3::Zero()), endColour(Colour::White()), alphaFadeSpeed(0), colourChangeSpeed(0),
        rotationSpeed(0), lifeTime(0), fadeOut(false) {}
        ~ParticleProperties() override = default;
    public:
        std::vector<int> GetEnum() override {return {GAUSS_ENUMS::Particle};}
    public:
        Vector3 rotationAxis;
        Colour endColour;
        float alphaFadeSpeed;
        float colourChangeSpeed;
        float rotationSpeed;
        float lifeTime;
        bool fadeOut;
    };   
}
