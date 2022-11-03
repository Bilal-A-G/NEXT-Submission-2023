#include "TSpch.h"
#include "Camera.h"
#include "glut/include/GL/freeglut_std.h"

TESLA::Matrix4x4 TESLA::Camera::GetProjection()
{
    float aspectRatio = GLUT_SCREEN_HEIGHT/GLUT_SCREEN_WIDTH;
    float fovRad = 1.0f / tan(m_fov/2 / 3.1415 * 180);
    
    return TESLA::Matrix4x4
    {
        {aspectRatio * fovRad, 0.0f, 0.f, 0.0f},
        {0.0f, fovRad, 0.0f, 0.0f},
        {0.0f, 0.0f, m_farPlane/(m_farPlane - m_nearPlane), 1.0f},
        {0.0f, 0.0f, -m_farPlane * m_nearPlane/(m_farPlane - m_nearPlane), 0.0f}
    };
}

TESLA::Matrix4x4 TESLA::Camera::GetView()
{
    return TESLA::Matrix4x4
    {
            {1.0f, 0.0f, 0.0f, position.x},
            {0.0f, 1.0f, 0.0f, position.y},
            {0.0f, 0.0f, 1.0f, position.z},
            {0.0f, 0.0f, 0.0f, 1.0f}
    };
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
    this->rotation = this->rotation + axis * angle;
}

void TESLA::Camera::Translate(TESLA::Vector translation)
{
    m_translationMatrix = m_translationMatrix * Matrix4x4
    {
        {1.0f, 0.0f, 0.0f, translation.x},
        {0.0f, 1.0f, 0.0f, translation.y},
        {0.0f, 0.0f, 1.0f, translation.z},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };

    position = position + translation;
}


