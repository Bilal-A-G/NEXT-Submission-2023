#include "TSPch.h"
#include "Physics.h"

#include "ECS/Components/Colliders/Collider.h"
#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Transform/Transform.h"
#include "Scenes/SceneManager.h"

std::vector<TESLA::Component*> meshes;

void TESLA::Physics::Awake()
{
    m_colliders = TESLA::SceneManager::m_activeScene->GetComponents(TESLA_ENUMS::Collider);
    m_rigidBodies = TESLA::SceneManager::m_activeScene->GetComponents(TESLA_ENUMS::RigidBody);
    m_transforms = TESLA::SceneManager::m_activeScene->GetComponents(TESLA_ENUMS::Transform);
    meshes = TESLA::SceneManager::m_activeScene->GetComponents(TESLA_ENUMS::Mesh);
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
            static_cast<TESLA::Mesh*>(meshes[i])->colour = TESLA::Colour::Green();
            static_cast<TESLA::Mesh*>(meshes[j])->colour = TESLA::Colour::Blue();
            
            if(!CheckValidCollider(j))
                continue;

            TESLA::Rigidbody* rb2 = static_cast<TESLA::Rigidbody*>(m_rigidBodies[j]);
            TESLA::Transform* transform2 = static_cast<TESLA::Transform*>(m_transforms[j]);
            TESLA::Collider* collider2 = static_cast<TESLA::Collider*>(m_colliders[j]);

            //Perform SAT and update velocities
            std::vector<TESLA::Vector> body1Axes = collider1->GetAxes(transform1->position, transform1->rotationMatrix, transform2->position);
            std::vector<TESLA::Vector> body2Axes = collider2->GetAxes(transform2->position, transform2->rotationMatrix, transform1->position);
            
            std::vector<TESLA::Vector> body1Vertices = collider1->GetVertices(transform1->position, transform1->rotationMatrix, transform2->position);
            std::vector<TESLA::Vector> body2Vertices = collider2->GetVertices(transform2->position, transform2->rotationMatrix, transform1->position);

            TESLA::Vector body1Resolution = TESLA::Vector::Zero();
            TESLA::Vector body2Resolution = TESLA::Vector::Zero();

            if(PerformSAT(body1Vertices, body2Vertices,body1Axes, body1Resolution, body2Resolution))
            {
                if(PerformSAT(body1Vertices, body2Vertices,body2Axes, body1Resolution, body2Resolution))
                {
                    rb1->velocity += body1Resolution * deltaTime * 1.5f;
                    rb2->velocity += body2Resolution * deltaTime * 1.5f;
                }
            }
        }
    }

    //Integration
    for (int i = 0; i < m_rigidBodies.size(); i++)
    {
        TESLA::Transform* currentTransform = static_cast<TESLA::Transform*>(m_transforms[i]);
        TESLA::Rigidbody* currentRigidBody = static_cast<TESLA::Rigidbody*>(m_rigidBodies[i]);

        if(!currentTransform || !currentRigidBody)
            continue;
        
        currentRigidBody->velocity += currentRigidBody->acceleration * deltaTime;
        
        if(currentRigidBody->acceleration.Magnitude() > 0.1f)
        {
            currentRigidBody->acceleration -= currentRigidBody->acceleration * currentRigidBody->friction * deltaTime;
        }
        else if(currentRigidBody->acceleration.Magnitude() <= 0.1f)
        {
            currentRigidBody->acceleration = TESLA::Vector::Zero();
        }

        if(currentRigidBody->hasGravity)
        {
            currentRigidBody->velocity += TESLA::Vector(0, gravity, 0) * deltaTime;
        }
        
        currentTransform->Translate(currentRigidBody->velocity * deltaTime);
        
        currentRigidBody->velocity = TESLA::Vector::Zero();
    }
}

bool TESLA::Physics::CheckValidCollider(int colliderIndex)
{
    return m_transforms[colliderIndex] && m_rigidBodies[colliderIndex];
}

bool TESLA::Physics::PerformSAT(std::vector<Vector>& verticesA, std::vector<Vector>& verticesB,
    std::vector<Vector>& axes, Vector& resolutionA, Vector& resolutionB)
{
    
    for (TESLA::Vector axis : axes)
    {
        float bodyAMin = 0;
        float bodyAMax = 0;
                
        float bodyBMin = 0;
        float bodyBMax = 0;

        for (int i = 0; i < verticesA.size(); i++)
        {
            float dotProduct = TESLA::Vector::Dot(verticesA[i], axis);
            if(i == 0)
            {
                bodyAMax = dotProduct;
                bodyAMin = dotProduct;
            }
                    
            if(dotProduct > bodyAMax)
            {
                bodyAMax = dotProduct;
            }
            else if(dotProduct < bodyAMin)
            {
                bodyAMin = dotProduct;
            }
        }

        for (int i = 0; i < verticesB.size(); i++)
        {
            float dotProduct = TESLA::Vector::Dot(verticesB[i], axis);
            if(i == 0)
            {
                bodyBMax = dotProduct;
                bodyBMin = dotProduct;
            }
                    
            if(dotProduct > bodyBMax)
            {
                bodyBMax = dotProduct;
            }
            else if(dotProduct < bodyBMin)
            {
                bodyBMin = dotProduct;
            }
        }
        
        if(bodyBMin < bodyAMax && bodyBMax > bodyAMax)
        {
            resolutionA += axis * (bodyBMin - bodyAMax)/2.0f;
            resolutionB += axis * -(bodyBMin - bodyAMax)/2.0f;
        }
        else if(bodyAMin < bodyBMax && bodyAMax > bodyBMax)
        {
            resolutionA += axis * (bodyAMax - bodyBMin)/2.0f;
            resolutionB += axis * -(bodyAMax - bodyBMin)/2.0f;
        }
        else if(bodyAMax == bodyBMax || bodyBMin == bodyAMin)
        {
            continue;
        }
        else
        {
            return false;
        }
    }

    return true;
}