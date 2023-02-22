#pragma once
#include "ECS/Component.h"
#include "ECS/Entity.h"
#include "Math/Math.h"

namespace GAUSS
{
    using CollisionFunction = void(*)(Entity& other);
    using CollisionResolvedFunction = void(*)();
    
    struct Collider : public Component
    {
    public:
        virtual std::vector<Vector3> GetAxes(Vector3 position, Matrix4x4 rotation, Vector3 otherPosition) = 0;
        virtual std::vector<Vector3> GetVertices(Vector3 position, Matrix4x4 rotation, Vector3 otherPosition) = 0;
        virtual float GetStiffness() = 0;
        
        void OnCollisionStay(CollisionFunction listener)
        {
            _collisionListeners.push_back(listener);
        }
        void OnCollisionResolved(CollisionResolvedFunction listener)
        {
            _resolvedListeners.push_back(listener);
        }
        void InvokeCollision(Entity& other)
        {
            _resolvedCollision = false;
            
            for (int i = 0; i < _collisionListeners.size(); i++)
            {
                _collisionListeners[i](other);
            }
        }
        void InvokeResolved()
        {
            if(_resolvedCollision)
                return;

            _resolvedCollision = true;
            for (int i = 0; i < _resolvedListeners.size(); i++)
            {
                _resolvedListeners[i]();
            }
        }
    private:
        std::vector<CollisionFunction> _collisionListeners;
        std::vector<CollisionResolvedFunction> _resolvedListeners;
        bool _resolvedCollision = false;
    };    
}

