#include "SimpleDestruction.h"
#include "ECS/Entity.h"
#include "ECS/Components/Colliders/Collider.h"
#include "GameUtils.h"
#include "ECS/Systems/Particles/Particles.h"

namespace CLIENT
{
    void SimpleDestruction::Update(GAUSS::EntityComponentLookup& lookup)
    {
        GAUSS::Entity* entity = lookup.GetEntity(entityId);
        if(!entity || !entity->GetActive()) return;

        GAUSS::Collider* collider = entity->GetComponent<GAUSS::Collider>(GAUSS_ENUMS::Collider);
        if(!collider || !collider->GetActive()) return;
        
        collider->OnCollisionStay([&](GAUSS::Entity& a, GAUSS::Entity& b)
        {
            bool foundMatch = false;
            
            for (int i = 0; i < collisionTags.size(); i++)
            {
                if(b.name == collisionTags[i])
                {
                    foundMatch = true;
                    break;
                }
            }
            
            if(!foundMatch || !a.GetActive()) return;
            if(useParticles) {GAUSS::Particles::Play(particleProperties, lookup);}
            
            a.SetActive(false);
        });
    }
}
