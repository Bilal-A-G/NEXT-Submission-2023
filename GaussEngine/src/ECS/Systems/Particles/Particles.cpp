#include "GSPch.h"
#include "Particles.h"

#include "ParticlePool.h"
#include "ECS/Components/Transform/Transform.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Particles/ParticleProperties.h"
#include "ECS/Systems/Particles/ParticleSystemProperties.h"

#define NEW_SEED ((rand() / static_cast<float>(RAND_MAX) - 0.5f) * 2.0f)

namespace GAUSS
{
    std::vector<Entity*> Particles::m_particles;

    void Particles::Play(const ParticleSystemProperties& systemProperties, EntityComponentLookup& lookup)
    {
        for (int i = 0; i < systemProperties.amount; i++)
        {
            Entity* particle = ParticlePool::Query(lookup);
            
            ParticleProperties* properties = particle->GetComponent<ParticleProperties>(GAUSS_ENUMS::Particle);
            Transform* transform = particle->GetComponent<Transform>(GAUSS_ENUMS::Transform);
            Rigidbody* rb = particle->GetComponent<Rigidbody>(GAUSS_ENUMS::RigidBody);
            rb->hasGravity = false;
            Mesh* mesh = particle->GetComponent<Mesh>(GAUSS_ENUMS::Mesh);
        
            mesh->faces = systemProperties.faces;
            mesh->colour = systemProperties.initialColour + Colour(NEW_SEED, NEW_SEED, NEW_SEED) * systemProperties.colourVariation;
        
            transform->SetTranslation(systemProperties.position);
            transform->SetScale(Vector3(1, 1, 1), systemProperties.averageSize + NEW_SEED * systemProperties.sizeVariation);
        
            rb->acceleration = Vector3(NEW_SEED, NEW_SEED, NEW_SEED) * (systemProperties.averageSpeed + NEW_SEED * systemProperties.speedVariation);

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

    void Particles::Update(const float& deltaTime, EntityComponentLookup& lookup)
    {
        for (int i = 0; i < m_particles.size(); i++)
        {
            Entity* particle = m_particles[i];
            Transform* transform = particle->GetComponent<Transform>(GAUSS_ENUMS::Transform);
            Mesh* mesh = particle->GetComponent<Mesh>(GAUSS_ENUMS::Mesh);
            ParticleProperties* properties = particle->GetComponent<ParticleProperties>(GAUSS_ENUMS::Particle);
        
            if(properties->lifeTime <= 0)
            {
                ParticlePool::Return(particle);
                m_particles.erase(m_particles.begin() + i);
                continue;
            }

            properties->lifeTime -= deltaTime;
            transform->Rotate(properties->rotationAxis, properties->rotationSpeed);
        
            if(Colour::RoughlyEquals(mesh->colour,properties->endColour, 0.1f))
                properties->fadeOut = true;

            if(properties->fadeOut)
            {
                mesh->colour = Lerp<Colour>(mesh->colour, Colour::Black(), properties->alphaFadeSpeed * deltaTime);
                continue;
            }
        
            mesh->colour = Lerp<Colour>(mesh->colour, properties->endColour, properties->colourChangeSpeed * deltaTime);
        }
    }

    void Particles::Disable()
    {
        m_particles.clear();
        ParticlePool::CleanUp();
    }
}

