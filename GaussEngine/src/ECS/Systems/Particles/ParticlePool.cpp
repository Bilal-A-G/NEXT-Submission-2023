#include "GSPch.h"
#include "ParticlePool.h"

#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Particles/ParticleProperties.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Transform/Transform.h"

namespace GAUSS
{
    std::vector<Entity*> ParticlePool::m_pool;

    void ParticlePool::Return(Entity* particle)
    {
        particle->GetComponent<Mesh>(GAUSS_ENUMS::Mesh)->colour = Colour::Black();
        particle->GetComponent<Transform>(GAUSS_ENUMS::Transform)->SetTranslation(Vector3::Zero());
        particle->GetComponent<ParticleProperties>(GAUSS_ENUMS::Particle)->fadeOut = false;
        particle->SetActive(false);

        m_pool.push_back(particle);
    }

    Entity* ParticlePool::Query(EntityComponentLookup& entityComponentLookup)
    {
        Entity* returnParticle;
    
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
}
