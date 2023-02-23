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
        friend class EntityComponentLookup;
    protected:
        Collider() : collisionListeners(std::vector<CollisionFunction>()),
        resolvedListeners(std::vector<CollisionResolvedFunction>()), resolvedCollision(false) {}
        ~Collider() override = default;
    public:
        virtual std::vector<Vector3> GetAxes(const Vector3& position, const Matrix4x4& rotation, const Vector3& otherPosition) const = 0;
        virtual std::vector<Vector3> GetVertices(const Vector3& position, const Matrix4x4& rotation, const Vector3& otherPosition) const = 0;
        virtual float GetStiffness() const = 0;
        
        void OnCollisionStay(const CollisionFunction& listener) {collisionListeners.push_back(listener);}
        void OnCollisionResolved(const CollisionResolvedFunction& listener) {resolvedListeners.push_back(listener);}
        
        void InvokeCollision(Entity& other);
        void InvokeResolved();
    private:
        std::vector<CollisionFunction> collisionListeners;
        std::vector<CollisionResolvedFunction> resolvedListeners;
        bool resolvedCollision;
    };    
}

