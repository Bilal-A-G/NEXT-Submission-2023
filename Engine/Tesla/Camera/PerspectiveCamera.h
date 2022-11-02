#pragma once
#include "../Math/Math.h"

namespace TESLA
{
    class PerspectiveCamera
    {
    public:
        PerspectiveCamera(float fov, float nearPlane, float farPlane):
        m_fov(fov), m_nearPlane(nearPlane), m_farPlane(farPlane){}
    
        void Translate(TESLA::Vector translation);
        void Rotate(float angle, TESLA::Vector axis);
        TESLA::Matrix4x4 GetProjection();
        TESLA::Matrix4x4 GetView();
    public:
        TESLA::Vector position;
        TESLA::Vector rotation;
    private:
        TESLA::Matrix4x4 m_rotationMatrix;
        TESLA::Matrix4x4 m_translationMatrix;

        float m_fov;
        float m_nearPlane;
        float m_farPlane;
    };

}