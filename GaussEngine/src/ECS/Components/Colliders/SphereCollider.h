#pragma once
#include "Collider.h"

namespace GAUSS
{
    struct SphereCollider : public Collider
    {
    public:
        SphereCollider() : radius(0){}
    
        std::vector<int> GetEnum() override
        {
            return {GAUSS_ENUMS::SphereCollider, GAUSS_ENUMS::Collider};
        }
        std::vector<Vector3> GetAxes(Vector3 position, Matrix4x4 rotation, Vector3 otherPosition) override;
        std::vector<Vector3> GetVertices(Vector3 position, Matrix4x4 rotation, Vector3 otherPosition) override;
        float GetStiffness() override
        {
            return 20.0f;
        }
    public:
        float radius;
    };   
}
