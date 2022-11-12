#include "TSpch.h"
#include "Camera.h"
#include "NextAPI/AppSettings.h"

TESLA::Matrix4x4 TESLA::Camera::GetProjection()
{
    float aspectRatio = (float)APP_VIRTUAL_HEIGHT/(float)APP_VIRTUAL_WIDTH;
    float fovRad = 1.0f / tanf(m_fov * 0.5f / 180.0f * 3.14159f);
    
    return TESLA::Matrix4x4
    {
        {aspectRatio * fovRad, 0.0f, 0.f, 0.0f},
        {0.0f, fovRad, 0.0f, 0.0f},
        {0.0f, 0.0f, m_farPlane/(m_farPlane - m_nearPlane), 1.0f},
        {0.0f, 0.0f, (-m_farPlane * m_nearPlane)/(m_farPlane - m_nearPlane), 0.0f}
    };
}

TESLA::Matrix4x4 TESLA::Camera::GetView()
{
    Vector rotatedTarget =  TESLA::Vector(0, 0, 1) * m_rotationMatrix;
    forward = rotatedTarget.Normalize();
    right = TESLA::Vector::Cross(forward, up);
    
    TESLA::Matrix4x4 pointAtMatrix = TESLA::Matrix4x4::PointAt(position, position + rotatedTarget, up);
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

    m_rotationMatrix = m_rotationMatrix * (rotationY * rotationX * rotationZ);
    rotation = rotation + axis * angle;
}

void TESLA::Camera::Translate(TESLA::Vector translation)
{
    position += translation;
}


