#include "TSPch.h"
#include "Particles.h"

#include "ECS/Entity.h"
#include "ECS/Components/Transform/Transform.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Mesh/Mesh.h"

#define NEW_SEED ((rand() / static_cast<double>(RAND_MAX) - 0.5f) * 2.0f)

std::vector<TESLA::Particle*> TESLA::Particles::m_particles;

void TESLA::Particles::Play(ParticleProperties properties)
{
    for (int i = 0; i < properties.amount; i++)
    {
        TESLA::Entity* entity = new TESLA::Entity();
        TESLA::Transform* transform = entity->AddComponent<Transform>();
        TESLA::Rigidbody* rb = entity->AddComponent<Rigidbody>();
        rb->hasGravity = false;
        TESLA::Mesh* mesh = entity->AddComponent<Mesh>();
        
        mesh->faces = properties.faces;
        mesh->colour = properties.initialColour + TESLA::Colour(NEW_SEED, NEW_SEED, NEW_SEED) * properties.colourVariation;
        
        transform->Translate(properties.position);
        transform->Scale(TESLA::Vector(1, 1, 1), properties.averageSize + properties.averageSize * NEW_SEED);
        
        float speed = properties.averageSpeed + properties.averageSpeed * NEW_SEED;
        if(speed < properties.minSpeed)
            speed = properties.minSpeed;
        
        rb->acceleration = TESLA::Vector(NEW_SEED, NEW_SEED, NEW_SEED) * speed;

        const float randomizedRotationSpeed = properties.averageRotationSpeed + properties.averageRotationSpeed * NEW_SEED;
        const float randomizedLifetime = properties.averageLifetime + properties.averageLifetime * NEW_SEED;

        ParticleProperties* propertiesForParticle = new ParticleProperties(properties);
        propertiesForParticle->averageRotationSpeed = randomizedRotationSpeed;
        propertiesForParticle->averageLifetime = randomizedLifetime;
        
        m_particles.push_back(new Particle(entity, propertiesForParticle));
    }
}

void TESLA::Particles::Update(float deltaTime)
{
    for (int i = 0; i < m_particles.size(); i++)
    {
        TESLA::Particle* particle = m_particles[i];
        TESLA::Transform* transform = particle->entity->GetComponent<Transform>(TESLA_ENUMS::Transform);
        TESLA::Mesh* mesh = particle->entity->GetComponent<Mesh>(TESLA_ENUMS::Mesh);
        TESLA::ParticleProperties* properties = particle->properties;
        
        if(properties->averageLifetime <= 0)
            continue;

        properties->averageLifetime -= deltaTime;
        transform->Rotate(properties->rotationAxis, properties->averageRotationSpeed);
        
        if(TESLA::Colour::RoughlyEquals(mesh->colour,properties->endColour, 0.1f))
            properties->fadeOut = true;

        if(properties->fadeOut)
        {
            mesh->colour = Colour::Lerp(mesh->colour, TESLA::Colour::Black(), properties->alphaFadeSpeed * deltaTime);
        }
        else
        {
            mesh->colour = Colour::Lerp(mesh->colour, properties->endColour, properties->colourChangeSpeed * deltaTime);
        }
    }
}

void TESLA::Particles::Disable()
{
    m_particles.clear();
}

