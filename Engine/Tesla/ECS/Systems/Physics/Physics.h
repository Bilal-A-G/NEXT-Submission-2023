#pragma once
#include "ECS/Component.h"
#include "ECS/System.h"
#include "ECS/Components/Colliders/Collider.h"

namespace TESLA
{
    struct Ray
    {
    public:
        Ray(TESLA::Vector position, TESLA::Vector direction, float step, float distance, CollisionFunction callback):
        position(position), direction(direction), step(step), distance(distance), callback(callback)
        {}
        ~Ray() = default;
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
        void Update(float deltaTime, TESLA::EntityComponentLookup& lookup) override;
        void Disable() override;
        static void Raycast(TESLA::Vector position, TESLA::Vector direction, float distance, float step, TESLA::CollisionFunction callback)
        {
            m_rays.push_back(new Ray(position, direction, step, distance, callback));
        }
    private:
        TESLA::Vector PerformSAT(std::vector<TESLA::Vector>& verticesA, std::vector<TESLA::Vector>& verticesB, std::vector<TESLA::Vector>& axes);
    private:
        static std::vector<TESLA::Ray*> m_rays;
    public:
        inline static float gravity = -9.8f;
    };   
}
