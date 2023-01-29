#pragma once
#include "../../../ECS/System.h"
#include "../../../ECS/Components/Rigidbody/Rigidbody.h"
#include "../../../ECS/Components/Transform/Transform.h"
#include "../../../Math/Geometry.h"
#include "../../../ECS/Components/Mesh/Mesh.h"

namespace TESLA
{
    struct ParticleProperties
    {
    public:
        ParticleProperties(std::vector<TESLA::Face> faces):faces(faces)
        {}
    public:
        TESLA::Vector position = TESLA::Vector::Zero();
        TESLA::Vector rotationAxis = TESLA::Vector::Zero();
        TESLA::Colour initialColour = TESLA::Colour::Black();
        TESLA::Colour endColour = TESLA::Colour::White();
        float alphaFadeSpeed = 0.0f;
        float averageSpeed = 0.0f;
        float minSpeed = 0.0f;
        float averageRotationSpeed = 0.0f;
        float averageSize = 0.0f;
        float averageLifetime = 0.0f;
        float colourVariation = 0.0f;
        int amount = 0;
        std::vector<TESLA::Face> faces;
    };
    
    struct Particle
    {
    public:
        Particle(TESLA::Rigidbody* rb, TESLA::Transform* transform, TESLA::Mesh* mesh, float lifetime, TESLA::Vector rotationAxis, float rotationSpeed, float fadeSpeed, TESLA::Colour endColour):
        rb(rb), transform(transform),lifetime(lifetime), rotationAxis(rotationAxis), rotationSpeed(rotationSpeed), mesh(mesh), fadeSpeed(fadeSpeed), endColour(endColour)
        {}
    public:
        TESLA::Rigidbody* rb;
        TESLA::Transform* transform;
        TESLA::Mesh* mesh;
        float lifetime;
        TESLA::Vector rotationAxis;
        float rotationSpeed;
        float fadeSpeed;
        TESLA::Colour endColour;
    };
    
    class Particles : public TESLA::System
    {
    public:
        void Update(float deltaTime) override;
        void Disable() override;
        static void Play(ParticleProperties properties);
    private:
       static std::vector<Particle*> m_particles;
    };   
}
