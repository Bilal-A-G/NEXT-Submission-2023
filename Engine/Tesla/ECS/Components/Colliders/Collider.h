#pragma once
#include "ECS/Component.h"
#include "ECS/Entity.h"
#include "Math/Math.h"

namespace TESLA
{
    using CollisionFunction = void(*)(TESLA::Entity& other);
    using CollisionResolvedFunction = void(*)();
    
    struct Collider : public TESLA::Component
    {
    public:
        virtual std::vector<TESLA::Vector3> GetAxes(TESLA::Vector3 position, TESLA::Matrix4x4 rotation, TESLA::Vector3 otherPosition) = 0;
        virtual std::vector<TESLA::Vector3> GetVertices(TESLA::Vector3 position, TESLA::Matrix4x4 rotation, TESLA::Vector3 otherPosition) = 0;
        virtual float GetStiffness() = 0;
        
        void OnCollisionStay(CollisionFunction listener)
        {
            _collisionListeners.push_back(listener);
        }
        void OnCollisionResolved(CollisionResolvedFunction listener)
        {
            _resolvedListeners.push_back(listener);
        }
        void InvokeCollision(TESLA::Entity& other)
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

