#include "GSPch.h"
#include "Physics.h"

#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Transform/Transform.h"

namespace GAUSS
{
    std::vector<Ray*> Physics::rays;

    void Physics::Update(const float& deltaTime, EntityComponentLookup& lookup)
    {
        std::vector<Component*>& colliders = lookup.GetComponents(GAUSS_ENUMS::Collider);
        std::vector<Component*>& rigidBodies = lookup.GetComponents(GAUSS_ENUMS::RigidBody);
        std::vector<Component*>& transforms = lookup.GetComponents(GAUSS_ENUMS::Transform);

        if(rigidBodies.size() == 0 || transforms.size() == 0)
            return;

        //For some reason, colliders.size() - 1 as the condition in the loop breaks it, but putting it in a variable works fine
        const int colliderSizeMinusOne = colliders.size() - 1;

        //Collision detection and resolution
        for(int i = 0; i < colliderSizeMinusOne; i++)
        {
            if(!(rigidBodies[i] && transforms[i] && colliders[i]))
                continue;
    
            Rigidbody* rb1 = static_cast<Rigidbody*>(rigidBodies[i]);
            Transform* transform1 = static_cast<Transform*>(transforms[i]);
            Collider* collider1 = static_cast<Collider*>(colliders[i]);
    
            for (int j = i + 1; j < colliders.size(); j++)
            {
                if(!(rigidBodies[j] && transforms[j] && colliders[j]))
                    continue;
    
                Rigidbody* rb2 = static_cast<Rigidbody*>(rigidBodies[j]);
                Transform* transform2 = static_cast<Transform*>(transforms[j]);
                Collider* collider2 = static_cast<Collider*>(colliders[j]);
    
                std::vector<Vector3> body1Axes = collider1->GetAxes(transform1->GetPosition(),
                    transform1->GetRotationMatrix(), transform2->GetPosition());
                std::vector<Vector3> body2Axes = collider2->GetAxes(transform2->GetPosition(),
                    transform2->GetRotationMatrix(), transform1->GetPosition());
            
                std::vector<Vector3> body1Vertices = collider1->GetVertices(transform1->GetPosition(),
                    transform1->GetRotationMatrix(), transform2->GetPosition());
                std::vector<Vector3> body2Vertices = collider2->GetVertices(transform2->GetPosition(),
                    transform2->GetRotationMatrix(), transform1->GetPosition());
    
                Vector3 resolution = Vector3::Zero();
    
                resolution = PerformSAT(body1Vertices, body2Vertices, body1Axes);
                resolution = PerformSAT(body1Vertices, body2Vertices, body2Axes);
            
                if(resolution != Vector3::Zero())
                {
                    collider1->InvokeCollision(*lookup.GetEntity(rb2->m_entityId));
                    collider2->InvokeCollision(*lookup.GetEntity(rb1->m_entityId));

                    if(!rb1->isStatic && !rb2->isStatic)
                    {
                        rb1->velocity += resolution * (collider1->GetStiffness() + collider2->GetStiffness()) * deltaTime;
                        rb2->velocity += resolution * -1.0f * (collider1->GetStiffness() + collider2->GetStiffness()) * deltaTime;  
                    }
                    else if(!rb1->isStatic)
                    {
                        rb1->velocity += resolution * 2 * (collider1->GetStiffness() + collider2->GetStiffness()) * deltaTime;
                    }
                    else if(!rb2->isStatic)
                    {
                        rb2->velocity += resolution * -2.0f * (collider1->GetStiffness() + collider2->GetStiffness()) * deltaTime;  
                    }
                    
                    continue;
                }
    
                collider1->InvokeResolved();
                collider2->InvokeResolved();
            }
        }

        //Raycasting
        int eraseIndex = rays.size() + 1;

        for (int i = 0; i < rays.size(); i++)
        {
            std::vector<Vector3> rayPosition = std::vector<Vector3>{rays[i]->position};
        
            for (int v = 0; v < colliders.size(); v++)
            {
                if(!(transforms[v] && colliders[v]))
                    continue;
    
                const Transform* transform = static_cast<Transform*>(transforms[v]);
                const Collider* collider = static_cast<Collider*>(colliders[v]);
    
                std::vector<Vector3> bodyAxes = collider->GetAxes(transform->GetPosition(),
                    transform->GetRotationMatrix(), rays[i]->position);
                std::vector<Vector3> bodyVertices = collider->GetVertices(transform->GetPosition(),
                    transform->GetRotationMatrix(), rays[i]->position);

                if(PerformSAT(bodyVertices, rayPosition, bodyAxes) != Vector3::Zero())
                {
                    rays[i]->callback(*lookup.GetEntity(collider->m_entityId));
                    eraseIndex = i;
                }
            }

            if(rays[i]->distance <= 0)
            {
                eraseIndex = i;
                continue;
            }
        
            rays[i]->position += rays[i]->direction.Normalize() * rays[i]->step * deltaTime;
            rays[i]->distance -= rays[i]->step * deltaTime;
        }

        if(eraseIndex < rays.size()) rays.erase(rays.begin() + eraseIndex);

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

    void Physics::Raycast(const Vector3& position, const Vector3& direction, const float& distance, const float& step, const CollisionFunction& callback)
    {
        rays.push_back(new Ray(position, direction, step, distance, callback));
    }

    Vector3 Physics::PerformSAT(const std::vector<Vector3>& verticesA, const std::vector<Vector3>& verticesB, const std::vector<Vector3>& axes) const
    {
        float minDepth = 0;
        Vector3 minAxis;
    
        for (Vector3 axis : axes)
        {
            float bodyAMin = 0;
            float bodyAMax = 0;
                
            float bodyBMin = 0;
            float bodyBMax = 0;

            for (int i = 0; i < verticesA.size(); i++)
            {
                const float dotProduct = Vector3::Dot(verticesA[i], axis);
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
                const float dotProduct = Vector3::Dot(verticesB[i], axis);
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
                const float depth = abs(bodyBMin - bodyAMax);

                if(depth < minDepth || minAxis == Vector3::Zero())
                {
                    minDepth = depth;
                    minAxis = axis * -1.0f;
                }
            }
            else if(bodyAMin < bodyBMax && bodyAMax > bodyBMax)
            {
                const float depth = abs(bodyAMin - bodyBMax);

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
