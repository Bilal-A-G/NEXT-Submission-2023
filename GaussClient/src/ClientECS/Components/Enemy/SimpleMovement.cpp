#include "SimpleMovement.h"

#include "ECS/Entity.h"
#include "ECS/Components/Colliders/Collider.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"

namespace CLIENT
{
    void SimpleMovement::Update(GAUSS::EntityComponentLookup& lookup, const float& deltaTime)
    {
        GAUSS::Entity* entity = lookup.GetEntity(entityId);
        if(!entity || !entity->GetActive()) return;

        GAUSS::Rigidbody* rigidBody = entity->GetComponent<GAUSS::Rigidbody>(GAUSS_ENUMS::RigidBody);
        if(!rigidBody || !rigidBody->GetActive()) return;

        GAUSS::Collider* collider = entity->GetComponent<GAUSS::Collider>(GAUSS_ENUMS::Collider);
        if(!collider || !collider->GetActive()) return;

        collider->OnCollisionStay([&](GAUSS::Entity& a, GAUSS::Entity& b)
        {
            if(b.name != wallTag && b.name != enemyTag && b.name != bombTag) return;
            m_moveDirection *= -1;
        });
        

        rigidBody->acceleration = m_moveDirection * enemySpeed * deltaTime;
    }
    
}
