#include "TSPch.h"
#include "Particles.h"

#include "ParticlePool.h"
#include "ECS/Components/Transform/Transform.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Particles/ParticleProperties.h"
#include "ECS/Systems/Particles/ParticleSystemProperties.h"

#define NEW_SEED ((rand() / static_cast<double>(RAND_MAX) - 0.5f) * 2.0f)

std::vector<TESLA::Entity*> TESLA::Particles::m_particles;

void TESLA::Particles::Play(const TESLA::ParticleSystemProperties& systemProperties, EntityComponentLookup& lookup)
{
    for (int i = 0; i < systemProperties.amount; i++)
    {
        TESLA::Entity* particle = TESLA::ParticlePool::Query(lookup);
        TESLA::ParticleProperties* properties = particle->GetComponent<TESLA::ParticleProperties>(TESLA_ENUMS::Particle);
        
        TESLA::Transform* transform = particle->GetComponent<Transform>(TESLA_ENUMS::Transform);
        TESLA::Rigidbody* rb = particle->GetComponent<Rigidbody>(TESLA_ENUMS::RigidBody);
        rb->hasGravity = false;
        TESLA::Mesh* mesh = particle->GetComponent<Mesh>(TESLA_ENUMS::Mesh);
        
        mesh->faces = systemProperties.faces;
        mesh->colour = systemProperties.initialColour + TESLA::Colour(NEW_SEED, NEW_SEED, NEW_SEED) * systemProperties.colourVariation;
        
        transform->Translate(systemProperties.position);
        transform->Scale(TESLA::Vector(1, 1, 1), systemProperties.averageSize + NEW_SEED * systemProperties.sizeVariation);
        
        rb->acceleration = TESLA::Vector(NEW_SEED, NEW_SEED, NEW_SEED) * (systemProperties.averageSpeed + NEW_SEED * systemProperties.speedVariation);

        const float randomizedRotationSpeed = systemProperties.averageRotationSpeed + NEW_SEED * systemProperties.rotationSpeedVariation;
        const float randomizedLifetime = systemProperties.averageLifetime + NEW_SEED * systemProperties.lifetimeVariation;

        properties->rotationSpeed = randomizedRotationSpeed;
        properties->lifeTime = randomizedLifetime;
        properties->endColour = systemProperties.endColour;
        properties->rotationAxis = systemProperties.rotationAxis;
        properties->alphaFadeSpeed = systemProperties.alphaFadeSpeed;
        properties->colourChangeSpeed = systemProperties.colourChangeSpeed;
        
        m_particles.push_back(particle);
    }
}

void TESLA::Particles::Update(float deltaTime, TESLA::EntityComponentLookup& lookup)
{
    for (int i = 0; i < m_particles.size(); i++)
    {
        TESLA::Entity* particle = m_particles[i];
        TESLA::Transform* transform = particle->GetComponent<Transform>(TESLA_ENUMS::Transform);
        TESLA::Mesh* mesh = particle->GetComponent<Mesh>(TESLA_ENUMS::Mesh);
        TESLA::ParticleProperties* properties = particle->GetComponent<TESLA::ParticleProperties>(TESLA_ENUMS::Particle);
        
        if(properties->lifeTime <= 0)
        {
            TESLA::ParticlePool::Return(particle);
            m_particles.erase(m_particles.begin() + i);
            continue;
        }

        properties->lifeTime -= deltaTime;
        transform->Rotate(properties->rotationAxis, properties->rotationSpeed);
        
        if(TESLA::Colour::RoughlyEquals(mesh->colour,properties->endColour, 0.1f))
            properties->fadeOut = true;

        if(properties->fadeOut)
        {
            mesh->colour = Colour::Lerp(mesh->colour, TESLA::Colour::Black(), properties->alphaFadeSpeed * deltaTime);
            continue;
        }
        
        mesh->colour = Colour::Lerp(mesh->colour, properties->endColour, properties->colourChangeSpeed * deltaTime);
    }
}

void TESLA::Particles::Awake()
{
    TESLA::ParticlePool::Init();
}

void TESLA::Particles::Disable()
{
    m_particles.clear();
    TESLA::ParticlePool::CleanUp();
}

