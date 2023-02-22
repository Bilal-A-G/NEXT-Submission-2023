#pragma once
#include "ECS/Component.h"

namespace GAUSS
{
    class Transform : public Component
    {
    public:
        std::vector<int> GetEnum() override
        {
            return {GAUSS_ENUMS::Transform};
        }
        void Translate(Vector3 translation);
        void SetTranslation(Vector3 translation);
        
        void Rotate(Vector3 axis, float angle);
        void SetRotation(Vector3 axis, float angle);
        
        void Scale(Vector3 axis, float size);
        void SetScale(Vector3 axis, float size);
        
        void SetChild(Transform* child)
        {
            m_children.push_back(child);
            child->parent = this;
        }
        
        void RemoveChild(Transform* child)
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

    private:
        Vector3 GetTransformedToChildVector(Vector3 childPosition, Matrix4x4 finalMatrix);
    public:
        Matrix4x4 scaleMatrix = Matrix4x4::Identity();
        Matrix4x4 positionMatrix = Matrix4x4::Identity();
        Matrix4x4 rotationMatrix = Matrix4x4::Identity();
        
        Vector3 position;
        Vector3 rotation;
        Vector3 scale;
        
        Vector3 right = {1.0f, 0.0f, 0.0f};
        Vector3 up = {0.0f, 1.0f, 0.0f};
        Vector3 forward = {0.0f, 0.0f, 1.0f};

        Transform* parent = nullptr;
    private:
        std::vector<Transform*> m_children;
    };   
}
