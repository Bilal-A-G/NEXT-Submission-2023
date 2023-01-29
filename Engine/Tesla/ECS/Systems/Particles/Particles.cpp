#include "TSPch.h"
#include "Particles.h"

#include "ECS/Entity.h"

std::vector<TESLA::Particle*> TESLA::Particles::m_particles;

void TESLA::Particles::Play(ParticleProperties properties)
{
    for (int i = 0; i < properties.amount; i++)
    {
        float seed0 = (rand() / static_cast<double>(RAND_MAX) - 0.5f) * 2.0f;
        float seed1 = (rand() / static_cast<double>(RAND_MAX) - 0.5f) * 2.0f;
        float seed2 = (rand() / static_cast<double>(RAND_MAX) - 0.5f) * 2.0f;

        float seed3 = (rand() / static_cast<double>(RAND_MAX) - 0.5f) * 2.0f;
        float seed4 = (rand() / static_cast<double>(RAND_MAX) - 0.5f) * 2.0f;
        float seed5 = (rand() / static_cast<double>(RAND_MAX) - 0.5f) * 2.0f;
        
        float seed6 = (rand() / static_cast<double>(RAND_MAX) - 0.5f) * 2.0f;
        float seed7 = (rand() / static_cast<double>(RAND_MAX) - 0.5f) * 2.0f;
        float seed8 = (rand() / static_cast<double>(RAND_MAX) - 0.5f) * 2.0f;
        float seed9 = (rand() / static_cast<double>(RAND_MAX) - 0.5f) * 2.0f;
        
        TESLA::Entity* entity = new TESLA::Entity();
        TESLA::Transform* transform = entity->AddComponent<Transform>();
        TESLA::Rigidbody* rb = entity->AddComponent<Rigidbody>();
        rb->hasGravity = false;
        TESLA::Mesh* mesh = entity->AddComponent<Mesh>();
        
        mesh->faces = properties.faces;
        mesh->colour = properties.initialColour + TESLA::Colour(seed3, seed4, seed5) * properties.colourVariation;
        
        transform->Translate(properties.position);
        transform->Scale(TESLA::Vector(1, 1, 1), properties.averageSize + properties.averageSize * seed6);
        
        float speed = properties.averageSpeed + properties.averageSpeed * seed7;
        if(speed < properties.minSpeed)
            speed = properties.minSpeed;
        
        rb->acceleration = TESLA::Vector(seed0, seed1, seed2) * speed;

        const float rotationSpeed = properties.averageRotationSpeed + properties.averageRotationSpeed * seed9;
        const float lifetime = properties.averageLifetime + properties.averageLifetime * seed8;
        
        m_particles.push_back(new Particle(rb, transform, mesh, lifetime, properties.rotationAxis,
            rotationSpeed, properties.alphaFadeSpeed, properties.endColour));
    }
}

void TESLA::Particles::Update(float deltaTime)
{
    for (int i = 0; i < m_particles.size(); i++)
    {
        if(m_particles[i]->lifetime <= 0)
            continue;

        m_particles[i]->lifetime -= deltaTime;
        m_particles[i]->transform->Rotate(m_particles[i]->rotationAxis, m_particles[i]->rotationSpeed);
        m_particles[i]->mesh->colour = Colour::Lerp(m_particles[i]->mesh->colour, m_particles[i]->endColour, m_particles[i]->fadeSpeed * deltaTime);
        m_particles[i]->mesh->colour = Colour::Lerp(m_particles[i]->mesh->colour, TESLA::Colour::Black(), m_particles[i]->fadeSpeed * deltaTime);
    }
}

void TESLA::Particles::Disable()
{
    m_particles.clear();
}

