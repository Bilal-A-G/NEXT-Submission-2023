#include "GSPch.h"
#include "Transform.h"

namespace GAUSS
{
    Matrix4x4 GetRotationMatrix(const Vector3& axis, const float& angle)
    {
        const float cosTheta = cos(angle);
        const float sinTheta = sin(angle);

        Matrix4x4 rotationY = Matrix4x4();
        Matrix4x4 rotationX = Matrix4x4();
        Matrix4x4 rotationZ = Matrix4x4();
            
        if(axis.y != 0)
        {
            rotationY = Matrix4x4
            (
                {cosTheta, 0.0f, -sinTheta, 0.0f},
                {0.0f, 1.0f, 0.0f, 0.0f},
                {sinTheta, 0.0f, cosTheta, 0.0f},
                {0.0f, 0.0f, 0.0f, 1.0f}
            );
        }

        if(axis.x != 0)
        {
            rotationX = Matrix4x4
            (
                {1.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, cosTheta, sinTheta, 0.0f},
                {0.0f, -sinTheta, cosTheta, 0.0f},
                {0.0f, 0.0f, 0.0f, 1.0f}
            );
        }
            
        if(axis.z != 0)
        {
            rotationZ = Matrix4x4
            (
                {cosTheta, sinTheta, 0.0f, 0.0f},
                {-sinTheta, cosTheta, 0.0f, 0.0f},
                {0.0f, 0.0f, 1.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 1.0f}
            );
        }

        return (rotationY * rotationX * rotationZ);
    }

    Vector3 Transform::GetTransformedToChildVector(const Vector3& childPosition, const Matrix4x4& finalMatrix) const
    {
        const Vector3 vectorToChild = childPosition - position;
        const Vector4 transformedVectorToChild = Vector4(vectorToChild.x, vectorToChild.y, vectorToChild.z, 1) * finalMatrix;
        return Vector3(transformedVectorToChild.x, transformedVectorToChild.y, transformedVectorToChild.z) - vectorToChild;
    }

    void Transform::Rotate(const Vector3& axis, const float& angle, const bool& set)
    {
        PerformGramSchmidtProcess();
        
        Matrix4x4 finalMatrix = GetRotationMatrix(axis, angle);
        if(parent != nullptr) finalMatrix = parent->rotationMatrix * finalMatrix;
    
        rotationMatrix = set ? finalMatrix : rotationMatrix * finalMatrix;
        rotation = axis * angle;

        for (int i = 0; i < m_children.size(); i++)
        {
            m_children[i]->Translate(GetTransformedToChildVector(m_children[i]->position, finalMatrix));
            m_children[i]->SetRotation(axis, -angle);
        }
    }

    void Transform::Scale(const Vector3& axis, const float& size, const bool& set)
    {
        const Vector3 normalizedAxis = axis.Normalize();
        const Matrix4x4 newScaleMatrix = Matrix4x4
        {
            {normalizedAxis.x * size, 0.0f, 0.0f, 0.0f},
            {0.0f, normalizedAxis.y * size, 0.0f, 0.0f},
            {0.0f, 0.0f, normalizedAxis.z * size, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        
        scaleMatrix = set ? newScaleMatrix : scaleMatrix * newScaleMatrix;
    
        scale = set ? (axis * size) : (scale + axis * size);
    }

    void Transform::Translate(const Vector3& translation, const bool& set)
    {
        const Matrix4x4 newPositionMatrix = Matrix4x4
        {
            {1.0f, 0.0f, 0.0f, translation.x},
            {0.0f, 1.0f, 0.0f, translation.y},
            {0.0f, 0.0f, 1.0f, translation.z},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };

        positionMatrix = set ? newPositionMatrix : positionMatrix * newPositionMatrix;

        position = set ? translation : position + translation;
        if(parent != nullptr)
        {
            positionMatrix = parent->positionMatrix * positionMatrix;
        }
    
        for (int i = 0; i < m_children.size(); i++)
        {
            m_children[i]->Translate(translation, set);
        }
    }

    void Transform::SetChild(Transform* child)
    {
        m_children.push_back(child);
        child->parent = this;
    }

    void Transform::RemoveChild(Transform* child)
    {
        for (int i = 0; i < m_children.size(); i++)
        {
            if(m_children[i]->m_entityId == child->m_entityId)
            {
                m_children.erase(m_children.begin() + i);
                return;
            }
        }

        child->parent = nullptr;
    }

    void Transform::PerformGramSchmidtProcess()
    {
        const Vector4 rotatedTarget = Vector4(0, 0, 1, 1) * rotationMatrix;
        const Vector3 vec3RotatedTarget = Vector3(rotatedTarget.x, rotatedTarget.y, rotatedTarget.z);
    
        forward = vec3RotatedTarget.Normalize();
        right = Vector3::Cross(forward, Vector3(0, 1, 0)).Normalize();
        up = Vector3::Cross(right, forward).Normalize();
    }
}





