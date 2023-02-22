#include "GSPch.h"
#include "Physics.h"

#include "ECS/Components/Colliders/Collider.h"
#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Transform/Transform.h"

namespace GAUSS
{
    std::vector<Ray*> Physics::m_rays;

    void Physics::Update(float deltaTime, EntityComponentLookup& lookup)
    {
        std::vector<Component*>& colliders = lookup.GetComponents(GAUSS_ENUMS::Collider);
        std::vector<Component*>& rigidBodies = lookup.GetComponents(GAUSS_ENUMS::RigidBody);
        std::vector<Component*>& transforms = lookup.GetComponents(GAUSS_ENUMS::Transform);
    
        //Collision detection + resolution
        for(int i = 0; i < colliders.size() - 1; i++)
        {
            if(!(rigidBodies[i] && transforms[i] && colliders[i]))
                continue;
    
            Rigidbody* rb1 = static_cast<Rigidbody*>(rigidBodies[i]);
            Transform* transform1 = static_cast<Transform*>(transforms[i]);
            Collider* collider1 = static_cast<Collider*>(colliders[i]);
    
            for (int j = i + 1; j < colliders.size(); j++)
            {
                if(!(rigidBodies[i] && transforms[i] && colliders[i]))
                    continue;
    
                Rigidbody* rb2 = static_cast<Rigidbody*>(rigidBodies[j]);
                Transform* transform2 = static_cast<Transform*>(transforms[j]);
                Collider* collider2 = static_cast<Collider*>(colliders[j]);
    
                //Perform SAT and update velocities
                std::vector<Vector3> body1Axes = collider1->GetAxes(transform1->position, transform1->rotationMatrix, transform2->position);
                std::vector<Vector3> body2Axes = collider2->GetAxes(transform2->position, transform2->rotationMatrix, transform1->position);
            
                std::vector<Vector3> body1Vertices = collider1->GetVertices(transform1->position, transform1->rotationMatrix, transform2->position);
                std::vector<Vector3> body2Vertices = collider2->GetVertices(transform2->position, transform2->rotationMatrix, transform1->position);
    
                Vector3 resolution = Vector3::Zero();
    
                resolution = PerformSAT(body1Vertices, body2Vertices,body1Axes);
                resolution = PerformSAT(body1Vertices, body2Vertices,body2Axes);
            
                if(resolution != Vector3::Zero())
                {
                    collider1->InvokeCollision(*lookup.GetEntity(rb2->m_entityId));
                    collider2->InvokeCollision(*lookup.GetEntity(rb1->m_entityId));
                    
                    rb1->velocity += resolution * (collider1->GetStiffness() + collider2->GetStiffness()) * deltaTime;
                    rb2->velocity += resolution * -1.0f * (collider1->GetStiffness() + collider2->GetStiffness()) * deltaTime;
    
                    continue;
                }
    
                collider1->InvokeResolved();
                collider2->InvokeResolved();
            }
        }

        int eraseIndex = m_rays.size() + 1;

        //Raycasting
        for (int i = 0; i < m_rays.size(); i++)
        {
            std::vector<Vector3> rayPosition{m_rays[i]->position};
        
            for (int v = 0; v < colliders.size(); v++)
            {
                if(!(transforms[v] && colliders[v]))
                    continue;
    
                Transform* transform = static_cast<Transform*>(transforms[v]);
                Collider* collider = static_cast<Collider*>(colliders[v]);
    
                std::vector<Vector3> bodyAxes = collider->GetAxes(transform->position, transform->rotationMatrix, m_rays[i]->position);
                std::vector<Vector3> bodyVertices = collider->GetVertices(transform->position, transform->rotationMatrix, m_rays[i]->position);

                if(PerformSAT(bodyVertices, rayPosition, bodyAxes) != Vector3::Zero())
                {
                    m_rays[i]->callback(*lookup.GetEntity(collider->m_entityId));
                    eraseIndex = i;
                }
            }

            if(m_rays[i]->distance <= 0)
            {
                eraseIndex = i;
                continue;
            }
        
            m_rays[i]->position += m_rays[i]->direction.Normalize() * m_rays[i]->step * deltaTime;
            m_rays[i]->distance -= m_rays[i]->step * deltaTime;
        }

        if(eraseIndex < m_rays.size())
        {
            m_rays.erase(m_rays.begin() + eraseIndex);
        }

        //Integration
        for (int i = 0; i < rigidBodies.size(); i++)
        {
            Transform* currentTransform = static_cast<Transform*>(transforms[i]);
            Rigidbody* currentRigidBody = static_cast<Rigidbody*>(rigidBodies[i]);

            if(!currentTransform || !currentRigidBody)
                continue;
        
            currentRigidBody->velocity += currentRigidBody->acceleration * deltaTime;
        
            if(currentRigidBody->acceleration.Magnitude() > 0.1f)
            {
                currentRigidBody->acceleration -= currentRigidBody->acceleration * currentRigidBody->friction * deltaTime;
            }
            else if(currentRigidBody->acceleration.Magnitude() <= 0.1f)
            {
                currentRigidBody->acceleration = Vector3::Zero();
            }

            if(currentRigidBody->hasGravity)
            {
                currentRigidBody->velocity += Vector3(0, gravity, 0) * deltaTime;
            }
        
            currentTransform->Translate(currentRigidBody->velocity * deltaTime);
        
            currentRigidBody->velocity = Vector3::Zero();
        }
    }

    void Physics::Disable()
    {
        m_rays.clear();
    }

    Vector3 Physics::PerformSAT(std::vector<Vector3>& verticesA, std::vector<Vector3>& verticesB, std::vector<Vector3>& axes)
    {
        float minDepth = 0;
        Vector3 minAxis = Vector3::Zero();
    
        for (Vector3 axis : axes)
        {
            float bodyAMin = 0;
            float bodyAMax = 0;
                
            float bodyBMin = 0;
            float bodyBMax = 0;

            for (int i = 0; i < verticesA.size(); i++)
            {
                float dotProduct = Vector3::Dot(verticesA[i], axis);
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
                float dotProduct = Vector3::Dot(verticesB[i], axis);
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
                float depth = abs(bodyBMin - bodyAMax);

                if(depth < minDepth || minAxis == Vector3::Zero())
                {
                    minDepth = depth;
                    minAxis = axis * -1.0f;
                }
            }
            else if(bodyAMin < bodyBMax && bodyAMax > bodyBMax)
            {
                float depth = abs(bodyAMin - bodyBMax);

                if(depth < minDepth || minAxis == Vector3::Zero())
                {
                    minDepth = depth;
                    minAxis = axis;
                }
            }
            else
            {
                return Vector3::Zero();
            }
        }
    
        return minAxis * minDepth/2.0f;
    }
}
