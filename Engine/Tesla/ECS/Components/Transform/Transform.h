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
        void Rotate(Vector axis, float angle);
        void Scale(Vector axis, float scale);
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
    };   
}
