#pragma once
#include "ECS/Component.h"
#include "ECS/System.h"
#include "ECS/Components/Colliders/Collider.h"

namespace GAUSS
{
    struct Ray
    {
    public:
        Ray(Vector3 position, Vector3 direction, float step, float distance, CollisionFunction callback):
        position(position), direction(direction), step(step), distance(distance), callback(callback)
        {}
        ~Ray() = default;
    public:
        Vector3 position;
        Vector3 direction;
        float step;
        float distance;
        CollisionFunction callback;
    };
    
    class Physics : public System
    {
    public:
        void Update(float deltaTime, EntityComponentLookup& lookup) override;
        void Disable() override;
        static void Raycast(Vector3 position, Vector3 direction, float distance, float step, CollisionFunction callback)
        {
            m_rays.push_back(new Ray(position, direction, step, distance, callback));
        }
    private:
        Vector3 PerformSAT(std::vector<Vector3>& verticesA, std::vector<Vector3>& verticesB, std::vector<Vector3>& axes);
    private:
        static std::vector<Ray*> m_rays;
    public:
        inline static float gravity = -9.8f;
    };   
}
