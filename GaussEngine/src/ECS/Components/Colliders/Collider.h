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
        friend class Physics;
    protected:
        Collider() : m_collisionListeners(std::vector<CollisionFunction>()),
        m_resolvedListeners(std::vector<CollisionResolvedFunction>()), m_resolvedCollision(false) {}
        ~Collider() override = default;
    public:
        virtual std::vector<Vector3> GetAxes(const Vector3& position, const Matrix4x4& rotation, const Vector3& otherPosition) const = 0;
        virtual std::vector<Vector3> GetVertices(const Vector3& position, const Matrix4x4& rotation, const Vector3& otherPosition) const = 0;
        virtual float GetStiffness() const = 0;
        
        void OnCollisionStay(const CollisionFunction& listener) {m_collisionListeners.push_back(listener);}
        void OnCollisionResolved(const CollisionResolvedFunction& listener) {m_resolvedListeners.push_back(listener);}
    protected:
        void InvokeCollision(Entity& other);
        void InvokeResolved();
        std::vector<CollisionFunction> m_collisionListeners;
        std::vector<CollisionResolvedFunction> m_resolvedListeners;
        bool m_resolvedCollision;
    };    
}

