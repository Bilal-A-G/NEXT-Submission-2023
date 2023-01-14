#pragma once
#include "Collider.h"

namespace TESLA
{
    struct SphereCollider : public TESLA::Collider
    {
    public:
        SphereCollider() : radius(0){}
    
        std::vector<TESLA_ENUMS::ComponentEnum>  GetEnum() override
        {
            return {TESLA_ENUMS::SphereCollider, TESLA_ENUMS::Collider};
        }
        std::vector<TESLA::Vector> GetAxes(TESLA::Vector position, TESLA::Matrix4x4 rotation, TESLA::Vector otherPosition) override;
        std::vector<TESLA::Vector> GetVertices(TESLA::Vector position, TESLA::Matrix4x4 rotation, TESLA::Vector otherPosition) override;
        float GetStiffness() override
        {
            return 10.0f;
        }
    public:
        float radius;
    };   
}
