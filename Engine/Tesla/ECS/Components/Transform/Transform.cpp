#include "TSPch.h"
#include "Transform.h"

TESLA::Matrix4x4 GetRotationMatrix(TESLA::Vector3 axis, float angle)
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

    return (rotationY * rotationX * rotationZ);
}

TESLA::Vector3 TESLA::Transform::GetTransformedToChildVector(Vector3 childPosition, Matrix4x4 finalMatrix)
{
    TESLA::Vector3 vectorToChild = childPosition - position;
    Vector4 transformedVectorToChild = Vector4(vectorToChild.x, vectorToChild.y, vectorToChild.z, 1) * finalMatrix;
    return Vector3(transformedVectorToChild.x, transformedVectorToChild.y, transformedVectorToChild.z) - vectorToChild;
}


void TESLA::Transform::Rotate(Vector3 axis, float angle)
{
    Vector4 rotatedTarget =  TESLA::Vector4(0, 0, 1, 1) * rotationMatrix;
    Vector3 vec3Target = Vector3(rotatedTarget.x, rotatedTarget.y, rotatedTarget.z);
    
    forward = vec3Target.Normalize();
    right = TESLA::Vector3::Cross(forward, TESLA::Vector3(0, 1, 0)).Normalize();
    up = TESLA::Vector3::Cross(right, forward).Normalize();

    Matrix4x4 finalMatrix = GetRotationMatrix(axis, angle);
    if(parent != nullptr)
    {
        finalMatrix = parent->rotationMatrix * finalMatrix;
    }
    
    rotationMatrix = rotationMatrix * finalMatrix;
    rotation += axis * angle;

    for (int i = 0; i < m_children.size(); i++)
    {
        m_children[i]->Translate(GetTransformedToChildVector(m_children[i]->position, finalMatrix));
        m_children[i]->SetRotation(axis, 0);
    }
}

void TESLA::Transform::SetRotation(Vector3 axis, float angle)
{
    Vector4 rotatedTarget =  TESLA::Vector4(0, 0, 1, 1) * rotationMatrix;
    Vector3 vec3RotatedTarget = Vector3(rotatedTarget.x, rotatedTarget.y, rotatedTarget.z);
    
    forward = vec3RotatedTarget.Normalize();
    right = TESLA::Vector3::Cross(forward, TESLA::Vector3(0, 1, 0)).Normalize();
    up = TESLA::Vector3::Cross(right, forward).Normalize();

    Matrix4x4 finalMatrix = GetRotationMatrix(axis, angle);
    if(parent != nullptr)
    {
        finalMatrix = parent->rotationMatrix * finalMatrix;
    }
    
    rotationMatrix = finalMatrix;
    rotation = axis * angle;

    for (int i = 0; i < m_children.size(); i++)
    {
        m_children[i]->Translate(GetTransformedToChildVector(m_children[i]->position, finalMatrix));
        m_children[i]->SetRotation(axis, -angle);
    }
}

void TESLA::Transform::Scale(Vector3 axis, float size)
{
    Vector3 normalizedAxis = axis.Normalize();
    scaleMatrix = scaleMatrix * TESLA::Matrix4x4
    {
            {normalizedAxis.x * size, 0.0f, 0.0f, 0.0f},
            {0.0f, normalizedAxis.y * size, 0.0f, 0.0f},
            {0.0f, 0.0f, normalizedAxis.z * size, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
    };
    
    scale += axis * size;
}

void TESLA::Transform::SetScale(Vector3 axis, float size)
{
    Vector3 normalizedAxis = axis.Normalize();
    scaleMatrix = TESLA::Matrix4x4
    {
                {normalizedAxis.x * size, 0.0f, 0.0f, 0.0f},
                {0.0f, normalizedAxis.y * size, 0.0f, 0.0f},
                {0.0f, 0.0f, normalizedAxis.z * size, 0.0f},
                {0.0f, 0.0f, 0.0f, 1.0f}
    };
    
    scale = axis * size;
}


void TESLA::Transform::Translate(Vector3 translation)
{
    positionMatrix = positionMatrix * Matrix4x4
    {
        {1.0f, 0.0f, 0.0f, translation.x},
        {0.0f, 1.0f, 0.0f, translation.y},
        {0.0f, 0.0f, 1.0f, translation.z},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };

    position += translation;
    if(parent != nullptr)
    {
        positionMatrix = parent->positionMatrix * positionMatrix;
    }
    
    for (int i = 0; i < m_children.size(); i++)
    {
        m_children[i]->Translate(translation);
    }
}

void TESLA::Transform::SetTranslation(Vector3 translation)
{
    positionMatrix = Matrix4x4
    {
        {1.0f, 0.0f, 0.0f, translation.x},
        {0.0f, 1.0f, 0.0f, translation.y},
        {0.0f, 0.0f, 1.0f, translation.z},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };

    position = translation;
    if(parent != nullptr)
    {
        positionMatrix = parent->positionMatrix * positionMatrix;
    }
    
    for (int i = 0; i < m_children.size(); i++)
    {
        m_children[i]->SetTranslation(translation);
    }
}





