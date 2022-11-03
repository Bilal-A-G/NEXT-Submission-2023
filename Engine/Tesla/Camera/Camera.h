#pragma once
#include "../Math/Math.h"

namespace TESLA
{
    class Camera
    {
    public:
        Camera(float fov, float nearPlane, float farPlane):
        m_fov(fov), m_nearPlane(nearPlane), m_farPlane(farPlane){}
    
        void Translate(TESLA::Vector translation);
        void Rotate(float angle, TESLA::Vector axis);
        TESLA::Matrix4x4 GetProjection();
        TESLA::Matrix4x4 GetView();
    public:
        TESLA::Vector position = {0.0f, 0.0f, 0.0f, 0.0f};
        TESLA::Vector rotation = {0.0f, 0.0f, 0.0f, 0.0f};
    private:
        TESLA::Matrix4x4 m_rotationMatrix = TESLA::Matrix4x4::Identity();
        TESLA::Matrix4x4 m_translationMatrix = TESLA::Matrix4x4::Identity();

        float m_fov;
        float m_nearPlane;
        float m_farPlane;
    };

}