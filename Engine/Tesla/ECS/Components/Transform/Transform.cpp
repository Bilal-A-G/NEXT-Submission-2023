#include "TSPch.h"
#include "Transform.h"

void TESLA::Transform::Rotate(Vector axis, float angle)
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

    Vector rotatedTarget =  TESLA::Vector(0, 0, 1) * rotationMatrix;
    forward = rotatedTarget.Normalize();
    right = TESLA::Vector::Cross(forward, TESLA::Vector(0, 1, 0)).Normalize();
    up = TESLA::Vector::Cross(right, forward).Normalize();

    rotationMatrix = rotationMatrix * (rotationY * rotationX * rotationZ);
    rotation += axis * angle;

    for (int i = 0; i < m_children.size(); i++)
    {
        TESLA::Vector vectorToChild = m_children[i]->position - position;
        m_children[i]->Translate(vectorToChild * (rotationY * rotationX * rotationZ) - vectorToChild);
        m_children[i]->Rotate(axis, -angle);
    }
}

void TESLA::Transform::Scale(Vector axis, float size)
{
    Vector normalizedAxis = axis.Normalize();
    scaleMatrix = scaleMatrix * TESLA::Matrix4x4
    {
            {normalizedAxis.x * size, 0.0f, 0.0f, 0.0f},
            {0.0f, normalizedAxis.y * size, 0.0f, 0.0f},
            {0.0f, 0.0f, normalizedAxis.z * size, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
    };
    
    scale += axis * size;

    for (int i = 0; i < m_children.size(); i++)
    {
        m_children[i]->Scale(axis, size);
    }
}

void TESLA::Transform::Translate(Vector translation)
{
    positionMatrix = positionMatrix * Matrix4x4
    {
        {1.0f, 0.0f, 0.0f, translation.x},
        {0.0f, 1.0f, 0.0f, translation.y},
        {0.0f, 0.0f, 1.0f, translation.z},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };

    position += translation;
    
    for (int i = 0; i < m_children.size(); i++)
    {
        m_children[i]->Translate(translation);
    }
}




