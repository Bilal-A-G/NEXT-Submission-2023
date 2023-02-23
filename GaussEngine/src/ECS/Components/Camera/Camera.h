#pragma once
#include "Math/Math.h"
#include "ECS/Component.h"

namespace GAUSS
{
    struct Camera final : public Component
    {
        friend class EntityComponentLookup;
    protected:
        Camera() : fov(0), nearPlane(0), farPlane(0) {}
        ~Camera() override = default;
    public:
        std::vector<int> GetEnum() override {return {GAUSS_ENUMS::Camera};}
        
        Matrix4x4 GetProjection() const;
    public:
        float fov;
        float nearPlane;
        float farPlane;
    };

}
