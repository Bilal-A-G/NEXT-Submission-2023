#include "GSPch.h"
#include "Transform.h"

namespace GAUSS
{
    Vector3 Transform::GetTransformedToChildVector(const Vector3& childPosition, const Matrix4x4& finalMatrix) const
    {
        const Vector3 vectorToChild = childPosition - m_position;
        const Vector4 transformedVectorToChild = Vector4(vectorToChild.x, vectorToChild.y, vectorToChild.z, 1) * finalMatrix;
        return Vector3(transformedVectorToChild.x, transformedVectorToChild.y, transformedVectorToChild.z) - vectorToChild;
    }

    void Transform::Rotate(const Vector3& axis, const float& angle, const bool& set)
    {
        PerformGramSchmidtProcess();
        
        Matrix4x4 finalMatrix = GetRotationMatrixFromAxisAngle(axis, angle);
        if(m_parent != nullptr) finalMatrix = m_parent->GetRotationMatrix() * finalMatrix;
    
        m_rotationMatrix = set ? finalMatrix : m_rotationMatrix * finalMatrix;
        m_rotation = axis * angle;

        for (int i = 0; i < m_children.size(); i++)
        {
            m_children[i]->Translate(GetTransformedToChildVector(m_children[i]->GetPosition(), finalMatrix));
            m_children[i]->SetRotation(axis, -angle);
        }
    }

    void Transform::Scale(const Vector3& axis, const float& size, const bool& set)
    {
        const Vector3 normalizedAxis = axis.Normalize();
        const Matrix4x4 newScaleMatrix = Matrix4x4
        {
            { normalizedAxis.x == 0 ? 1 :normalizedAxis.x * size, 0.0f, 0.0f, 0.0f},
            {0.0f, normalizedAxis.y == 0 ? 1 : normalizedAxis.y * size, 0.0f, 0.0f},
            {0.0f, 0.0f, normalizedAxis.z == 0 ? 1 : normalizedAxis.z * size, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
        
        m_scaleMatrix = set ? newScaleMatrix : m_scaleMatrix * newScaleMatrix;
    
        m_scale = set ? (axis * size) : (m_scale + axis * size);
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

        m_positionMatrix = set ? newPositionMatrix : m_positionMatrix * newPositionMatrix;

        m_position = set ? translation : m_position + translation;
        if(m_parent != nullptr)
        {
            m_positionMatrix = m_parent->GetPositionMatrix() * m_positionMatrix;
        }
    
        for (int i = 0; i < m_children.size(); i++)
        {
            m_children[i]->Translate(translation, set);
        }
    }

    void Transform::SetChild(Transform* child)
    {
        m_children.push_back(child);
        child->SetParent(this);
    }

    void Transform::RemoveChild(Transform* child)
    {
        for (int i = 0; i < m_children.size(); i++)
        {
            if(m_children[i]->entityId == child->entityId)
            {
                m_children.erase(m_children.begin() + i);
                return;
            }
        }

        child->SetParent(nullptr);
    }

    void Transform::PerformGramSchmidtProcess()
    {
        const Vector4 rotatedTarget = Vector4(0, 0, 1, 1) * m_rotationMatrix;
        const Vector3 vec3RotatedTarget = Vector3(rotatedTarget.x, rotatedTarget.y, rotatedTarget.z);
    
        forward = vec3RotatedTarget.Normalize();
        right = Vector3::Cross(forward, Vector3(0, 1, 0)).Normalize();
        up = Vector3::Cross(right, forward).Normalize();
    }

    Matrix4x4 Transform::GetRotationMatrixFromAxisAngle(const Vector3& axis, const float& angle) const
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
}





