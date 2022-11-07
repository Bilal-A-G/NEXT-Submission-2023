#include "TSpch.h"
#include "Camera.h"
#include "NextAPI/AppSettings.h"

TESLA::Matrix4x4 TESLA::Camera::GetProjection()
{
    float aspectRatio = APP_VIRTUAL_HEIGHT * 2/APP_VIRTUAL_WIDTH;
    float fovRad = 1.0f / tan(m_fov / 3.1415 * 180 /2);
    
    return TESLA::Matrix4x4
    {
        {aspectRatio * fovRad, 0.0f, 0.f, 0.0f},
        {0.0f, fovRad, 0.0f, 0.0f},
        {0.0f, 0.0f, m_farPlane/(m_nearPlane - m_farPlane), -m_farPlane * m_nearPlane/(m_nearPlane - m_farPlane)},
        {0.0f, 0.0f, 1.0f, 0.0f}
    };
}

TESLA::Matrix4x4 TESLA::Camera::GetView()
{
    Vector target = Vector(0, 0, 1);
    Vector rotatedTarget =  m_rotationMatrix * target;
    target = position + rotatedTarget;
    
    TESLA::Matrix4x4 pointAtMatrix = TESLA::Matrix4x4::PointAt(position, target, up);
    return Matrix4x4::LookAt(pointAtMatrix);
}

void TESLA::Camera::Rotate(float angle, TESLA::Vector axis)
{
    float cosTheta = cos(angle);
    float sinTheta = sin(angle);

    TESLA::Matrix4x4 rotationY;
    TESLA::Matrix4x4 rotationX;
    TESLA::Matrix4x4 rotationZ;
            
    if(axis.y == 0)
    {
        rotationY = TESLA::Matrix4x4::Identity();
    }
    else
    {
        rotationY = 
        {
            {cosTheta, 0.0f, -sinTheta, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {sinTheta, 0.0f, cosTheta, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
    }

    if(axis.x == 0)
    {
        rotationX = TESLA::Matrix4x4::Identity();
    }
    else
    {
        rotationX = TESLA::Matrix4x4
        {
                {1.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, cosTheta, sinTheta, 0.0f},
                {0.0f, -sinTheta, cosTheta, 0.0f},
                {0.0f, 0.0f, 0.0f, 1.0f}
        };
    }
            
    if(axis.z == 0)
    {
        rotationZ = TESLA::Matrix4x4::Identity();
    }
    else
    {
        rotationZ = 
        {
            {cosTheta, sinTheta, 0.0f, 0.0f},
            {-sinTheta, cosTheta, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
    }

    this->m_rotationMatrix = this->m_rotationMatrix * (rotationY * rotationX * rotationZ);
    rotation += axis * angle;
}

void TESLA::Camera::Translate(TESLA::Vector translation)
{
    position += translation;
}


