#include "TSPch.h"
#include "ParticlePool.h"

#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Particles/ParticleProperties.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Transform/Transform.h"

std::vector<TESLA::Entity*> TESLA::ParticlePool::m_pool;

void TESLA::ParticlePool::Return(TESLA::Entity* particle)
{
    particle->GetComponent<Mesh>(TESLA_ENUMS::Mesh)->colour = TESLA::Colour::Black();
    particle->GetComponent<Transform>(TESLA_ENUMS::Transform)->position = TESLA::Vector3::Zero();
    particle->GetComponent<ParticleProperties>(TESLA_ENUMS::Particle)->fadeOut = false;

    m_pool.push_back(particle);
}

TESLA::Entity* TESLA::ParticlePool::Query(TESLA::EntityComponentLookup& entityComponentLookup)
{
    TESLA::Entity* returnParticle;
    
    if(m_pool.size() > 0)
    {
        returnParticle = m_pool[0];
        m_pool.erase(m_pool.begin());
        return returnParticle;
    }
    
    returnParticle = entityComponentLookup.CreateEntity();
    returnParticle->AddComponent<Rigidbody>();
    returnParticle->AddComponent<Mesh>();
    returnParticle->AddComponent<Transform>();
    returnParticle->AddComponent<ParticleProperties>();

    return returnParticle;
}
