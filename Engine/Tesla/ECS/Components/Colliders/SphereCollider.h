#pragma once
#include "Collider.h"

namespace TESLA
{
    struct SphereCollider : public TESLA::Collider
    {
    public:
        SphereCollider() : radius(0){}
    
        std::vector<int> GetEnum() override
        {
            return {TESLA_ENUMS::SphereCollider, TESLA_ENUMS::Collider};
        }
        std::vector<TESLA::Vector3> GetAxes(TESLA::Vector3 position, TESLA::Matrix4x4 rotation, TESLA::Vector3 otherPosition) override;
        std::vector<TESLA::Vector3> GetVertices(TESLA::Vector3 position, TESLA::Matrix4x4 rotation, TESLA::Vector3 otherPosition) override;
        float GetStiffness() override
        {
            return 20.0f;
        }
    public:
        float radius;
    };   
}
