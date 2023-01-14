#pragma once
#include "../../../ECS/Component.h"
#include "../../../ECS/System.h"
#include "../../../ECS/Components/Colliders/Collider.h"

namespace TESLA
{
    struct Ray
    {
    public:
        Ray(TESLA::Vector position, TESLA::Vector direction, float step, float distance, CollisionFunction callback):
        position(position), direction(direction), step(step), distance(distance), callback(callback)
        {}
    public:
        TESLA::Vector position;
        TESLA::Vector direction;
        float step;
        float distance;
        TESLA::CollisionFunction callback;
    };
    
    class Physics : public TESLA::System
    {
    public:
        void Update(float deltaTime) override;
        void Awake() override;
        void Disable() override;
        static void Raycast(TESLA::Vector position, TESLA::Vector direction, float distance, float step, TESLA::CollisionFunction callback)
        {
            m_rays.push_back(new Ray(position, direction, step, distance, callback));
        }
    private:
        bool CheckValidCollider(int colliderIndex);
        TESLA::Vector PerformSAT(std::vector<TESLA::Vector>& verticesA, std::vector<TESLA::Vector>& verticesB, std::vector<TESLA::Vector>& axes);
    private:
        std::vector<TESLA::Component*> m_colliders;
        std::vector<TESLA::Component*> m_rigidBodies;
        std::vector<TESLA::Component*> m_transforms;
        static std::vector<TESLA::Ray*> m_rays;
    public:
        inline static float gravity = -9.8f;
    };   
}
