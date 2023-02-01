#pragma once
#include "../../../ECS/Component.h"

namespace TESLA
{
    class Transform : public TESLA::Component
    {
    public:
        Transform() : scaleMatrix(Matrix4x4::Identity()),
        positionMatrix(Matrix4x4::Identity()), rotationMatrix(Matrix4x4::Identity()),
        position(TESLA::Vector::Zero()), rotation(TESLA::Vector::Zero()), scale(TESLA::Vector::Zero())
        {};
        std::vector<TESLA_ENUMS::ComponentEnum>  GetEnum() override
        {
            return {TESLA_ENUMS::Transform};
        }
        void Translate(Vector translation);
        void SetTranslation(Vector translation);
        
        void Rotate(Vector axis, float angle);
        void SetRotation(Vector axis, float angle);
        
        void Scale(Vector axis, float size);
        void SetScale(Vector axis, float size);
        
        void SetChild(TESLA::Transform* child)
        {
            m_children.push_back(child);
            child->parent = this;
        }
        
        void RemoveChild(TESLA::Transform* child)
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
    public:
        Matrix4x4 scaleMatrix;
        Matrix4x4 positionMatrix;
        Matrix4x4 rotationMatrix;
        
        Vector position;
        Vector rotation;
        Vector scale;
        
        Vector right = {1.0f, 0.0f, 0.0f};
        Vector up = {0.0f, 1.0f, 0.0f};
        Vector forward = {0.0f, 0.0f, 1.0f};

        Transform* parent = nullptr;
    private:
        std::vector<Transform*> m_children;
    };   
}
