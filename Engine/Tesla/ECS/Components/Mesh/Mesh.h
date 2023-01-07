#pragma once
#include "../../../ECS/Component.h"
#include "../../../Math/Geometry.h"

namespace TESLA
{
    struct Mesh : public TESLA::Component
    {
        Mesh();
        TESLA_ENUMS::ComponentEnum GetEnum() override
        {
            return TESLA_ENUMS::ComponentEnum::Mesh;
        }

        //Temp
        void Translate(TESLA::Vector translation);
        void Rotate(float angle, TESLA::Vector axis);
        void Scale(float scale, TESLA::Vector axis);

        Vector GetPosition(){return m_position;}
        Vector GetRotation(){return m_rotation;}
        Vector GetScale(){return m_scale;}
    public:
        std::vector<Face> faces;
        Colour colour;

        //Temp
        Matrix4x4 m_scaleMatrix;
        Matrix4x4 m_rotationMatrix;
        Matrix4x4 m_translationMatrix;
        
        Vector m_position;
        Vector m_rotation;
        Vector m_scale;
    };
}
