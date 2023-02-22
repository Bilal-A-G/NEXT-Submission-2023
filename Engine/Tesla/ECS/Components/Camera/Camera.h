#pragma once
#include "Math/Math.h"
#include "ECS/Component.h"

namespace TESLA
{
    struct Camera : public TESLA::Component
    {
    public:
        std::vector<int>  GetEnum() override
        {
            return {TESLA_ENUMS::Camera};
        };
        
        TESLA::Matrix4x4 GetProjection();
    public:
        float fov;
        float nearPlane;
        float farPlane;
    };

}
