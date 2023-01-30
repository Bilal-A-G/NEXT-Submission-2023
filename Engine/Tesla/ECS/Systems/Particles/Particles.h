#pragma once
#include "../../../ECS/System.h"
#include "../../../Math/Geometry.h"
#include "../../../ECS/Entity.h"

namespace TESLA
{
    struct ParticleProperties
    {
        ParticleProperties(std::vector<TESLA::Face> faces):faces(faces)
        {}
        ParticleProperties()
        {}
    public:
        TESLA::Vector position = TESLA::Vector::Zero();
        TESLA::Vector rotationAxis = TESLA::Vector::Zero();
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

        bool fadeOut = false;
   };
    
    struct Particle
    {
        Particle(TESLA::Entity* entity, ParticleProperties* properties):
        entity(entity), properties(properties)
        {}
    public:
        TESLA::Entity* entity;
        ParticleProperties* properties;
    };
    
    class Particles : public TESLA::System
    {
    public:
        void Update(float deltaTime) override;
        void Disable() override;
        void Awake() override;
        static void Play(ParticleProperties properties);
    private:
       static std::vector<Particle*> m_particles;
    };   
}
