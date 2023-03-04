#pragma once
#include "ECS/System.h"
#include "ECS/Components/Colliders/CollisionFunctions.h"
#include "Math/Math.h"

namespace GAUSS
{
    struct Ray final
    {
    public:
        Ray(const Vector3& position, const Vector3& direction, const float& step, const float& distance,
            const CollisionFunction& callback) :
        position(position), direction(direction), step(step), distance(distance), callback(callback) {}
        ~Ray() = default;
    public:
        Vector3 position;
        Vector3 direction;
        float step;
        float distance;
        CollisionFunction callback;
    };
    
    class Physics final : public System
    {
        friend class Scene;
    protected:
        Physics() = default;
        ~Physics() override = default;
    public:
        void Update(const float& deltaTime, EntityComponentLookup& lookup) override;
        void Disable() override {rays.clear();}
        static void Raycast(const Vector3& position, const Vector3& direction, const float& distance, const float& step, const CollisionFunction& callback);
    private:
        Vector3 PerformSAT(const std::vector<Vector3>& verticesA, const std::vector<Vector3>& verticesB, const std::vector<Vector3>& axes) const;
    public:
        static std::vector<Ray*> rays;
        inline static float gravity = -9.8f;
    };   
}
