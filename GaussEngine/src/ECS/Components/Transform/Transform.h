#pragma once
#include "ECS/Component.h"

namespace GAUSS
{
    class Transform final : public Component
    {
        friend class EntityComponentLookup;
    protected:
        Transform() : scaleMatrix(Matrix4x4()), positionMatrix(Matrix4x4()), rotationMatrix(Matrix4x4()),
        position(Vector3()), rotation(Vector3()), scale(Vector3()), right(Vector3(1, 0, 0)), up(Vector3(0, 1, 0)),
        forward(0, 0, 1), parent(nullptr) {}
        ~Transform() override {m_children.clear();}
    public:
        std::vector<int> GetEnum() override {return {GAUSS_ENUMS::Transform};}
        
        void Translate(const Vector3& translation) {Translate(translation, false);}
        void SetTranslation(const Vector3& translation) {Translate(translation, true);}
        
        void Rotate(const Vector3& axis, const float& angle) {Rotate(axis, angle, false);}
        void SetRotation(const Vector3& axis, const float& angle)  {Rotate(axis, angle, true);}
        
        void Scale(const Vector3& axis, const float& size) {Scale(axis, size, false);}
        void SetScale(const Vector3& axis, const float& size) {Scale(axis, size, true);}
        
        void SetChild(Transform* child);
        void RemoveChild(Transform* child);
    private:
        Vector3 GetTransformedToChildVector(const Vector3& childPosition, const Matrix4x4& finalMatrix) const;
        
        void PerformGramSchmidtProcess();
        
        void Rotate(const Vector3& axis, const float& angle, const bool& set);
        void Scale(const Vector3& axis, const float& size, const bool& set);
        void Translate(const Vector3& translation, const bool& set);
    public:
        Matrix4x4 scaleMatrix;
        Matrix4x4 positionMatrix;
        Matrix4x4 rotationMatrix;
        
        Vector3 position;
        Vector3 rotation;
        Vector3 scale;
        
        Vector3 right;
        Vector3 up;
        Vector3 forward;

        Transform* parent;
    private:
        std::vector<Transform*> m_children;
    };   
}
