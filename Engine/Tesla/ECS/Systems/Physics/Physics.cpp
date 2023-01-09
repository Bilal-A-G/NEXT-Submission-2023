#include "TSPch.h"
#include "Physics.h"

#include "ECS/Components/Colliders/Collider.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Transform/Transform.h"
#include "Scenes/SceneManager.h"

void TESLA::Physics::Awake()
{
    m_colliders = TESLA::SceneManager::m_activeScene->GetComponents(TESLA_ENUMS::Collider);
    m_rigidBodies = TESLA::SceneManager::m_activeScene->GetComponents(TESLA_ENUMS::RigidBody);
    m_transforms = TESLA::SceneManager::m_activeScene->GetComponents(TESLA_ENUMS::Transform);
}

void TESLA::Physics::Update(float deltaTime)
{
    //Collision detection + resolution
    for(int i = 0; i < m_colliders.size() - 1; i++)
    {
        if(!CheckValidCollider(i))
            continue;

        TESLA::Rigidbody* rb1 = static_cast<TESLA::Rigidbody*>(m_rigidBodies[i]);
        TESLA::Transform* transform1 = static_cast<TESLA::Transform*>(m_transforms[i]);
        TESLA::Collider* collider1 = static_cast<TESLA::Collider*>(m_colliders[i]);

        for (int j = i + 1; j < m_colliders.size(); j++)
        {
            if(!CheckValidCollider(j))
                continue;

            TESLA::Rigidbody* rb2 = static_cast<TESLA::Rigidbody*>(m_rigidBodies[j]);
            TESLA::Transform* transform2 = static_cast<TESLA::Transform*>(m_transforms[j]);
            TESLA::Collider* collider2 = static_cast<TESLA::Collider*>(m_colliders[j]);

            //Perform SAT and update velocities
        }
    }

    //Integration
    for (int i = 0; i < m_rigidBodies.size(); i++)
    {
        TESLA::Transform* currentTransform = static_cast<TESLA::Transform*>(m_transforms[i]);
        TESLA::Rigidbody* currentRigidBody = static_cast<TESLA::Rigidbody*>(m_rigidBodies[i]);

        if(!currentTransform || !currentRigidBody)
            continue;
        
        currentRigidBody->velocity = currentRigidBody->acceleration * deltaTime;
        currentTransform->Translate(currentRigidBody->velocity * deltaTime);
        if(currentRigidBody->acceleration.Magnitude() > 0.1f)
        {
            currentRigidBody->acceleration -= currentRigidBody->acceleration.Normalize() * currentRigidBody->friction * deltaTime;
        }
        else if(currentRigidBody->acceleration.Magnitude() <= 0.1f)
        {
            currentRigidBody->acceleration = TESLA::Vector::Zero();
        }

        if(currentRigidBody->hasGravity)
        {
            currentRigidBody->velocity += TESLA::Vector(0, gravity, 0) * deltaTime;
        }
    }
}

bool TESLA::Physics::CheckValidCollider(int colliderIndex)
{
    return m_transforms[colliderIndex] && m_rigidBodies[colliderIndex];
}



