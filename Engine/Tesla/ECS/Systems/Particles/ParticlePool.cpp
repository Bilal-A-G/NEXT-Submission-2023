#include "TSPch.h"
#include "ParticlePool.h"

#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Transform/Transform.h"

std::vector<TESLA::Particle*> TESLA::ParticlePool::m_pool;

void TESLA::ParticlePool::Return(TESLA::Particle* particle)
{
    particle->entity->GetComponent<Mesh>(TESLA_ENUMS::Mesh)->colour = TESLA::Colour::Black();
    particle->entity->GetComponent<Transform>(TESLA_ENUMS::Transform)->position = TESLA::Vector::Zero();
    particle->properties->fadeOut = false;

    m_pool.push_back(particle);
}


TESLA::Particle* TESLA::ParticlePool::Query()
{
    TESLA::Particle* returnParticle;
    
    if(m_pool.size() > 0)
    {
        returnParticle = m_pool[0];
        m_pool.erase(m_pool.begin());
        return returnParticle;
    }
    
    TESLA::Entity* entity = new Entity();
    entity->AddComponent<Rigidbody>();
    entity->AddComponent<Mesh>();
    entity->AddComponent<Transform>();
    TESLA::ParticleProperties* properties = new ParticleProperties();
    
    returnParticle = new TESLA::Particle(entity, properties);

    return returnParticle;
}
