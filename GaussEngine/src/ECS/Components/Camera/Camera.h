#pragma once
#include "Math/Math.h"
#include "ECS/Component.h"

namespace GAUSS
{
    struct Camera : public Component
    {
    public:
        std::vector<int> GetEnum() override
        {
            return {GAUSS_ENUMS::Camera};
        };
        
        Matrix4x4 GetProjection();
    public:
        float fov;
        float nearPlane;
        float farPlane;
    };

}
