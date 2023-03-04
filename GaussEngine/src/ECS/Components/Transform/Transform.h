#pragma once
#include "ECS/Component.h"
#include "Math/Math.h"

namespace GAUSS
{
    class Transform final : public Component
    {
        friend class EntityComponentLookup;
    protected:
        Transform() : m_scaleMatrix(Matrix4x4::Identity()), m_positionMatrix(Matrix4x4::Identity()), m_rotationMatrix(Matrix4x4::Identity()),
        m_position(Vector3::Zero()), m_rotation(Vector3::Zero()), m_scale(Vector3(1, 1, 1)), right(Vector3(1, 0, 0)),
        up(Vector3(0, 1, 0)), forward(0, 0, 1), m_parent(nullptr) {}
        ~Transform() override {m_children.clear();}
    public:
        std::vector<int> GetEnum() override {return {GAUSS_ENUMS::Transform};}
        
        void Translate(const Vector3& translation) {Translate(translation, false);}
        void SetTranslation(const Vector3& translation) {Translate(translation, true);}
        
        void Rotate(const Vector3& axis, const float& angle) {Rotate(axis, angle, false);}
        void SetRotation(const Vector3& axis, const float& angle)  {Rotate(axis, angle, true);}
        
        void Scale(const Vector3& axis, const float& size) {Scale(axis, size, false);}
        void SetScale(const Vector3& axis, const float& size) {Scale(axis, size, true);}

        const Vector3& GetPosition() const {return m_position;}
        const Vector3& GetRotation() const {return m_rotation;}
        const Vector3& GetScale() const {return m_scale;}

        const Matrix4x4& GetPositionMatrix() const {return m_positionMatrix;}
        const Matrix4x4& GetRotationMatrix() const {return m_rotationMatrix;}
        const Matrix4x4& GetScaleMatrix() const {return m_scaleMatrix;}

        const Transform* GetParent() const {return m_parent;}

        void SetChild(Transform* child);
        void RemoveChild(Transform* child);
    private:
        void SetParent(Transform* newParent) {m_parent = newParent;}
        Vector3 GetTransformedToChildVector(const Vector3& childPosition, const Matrix4x4& finalMatrix) const;
        
        void PerformGramSchmidtProcess();
        
        void Rotate(const Vector3& axis, const float& angle, const bool& set);
        void Scale(const Vector3& axis, const float& size, const bool& set);
        void Translate(const Vector3& translation, const bool& set);

        Matrix4x4 GetRotationMatrixFromAxisAngle(const Vector3& axis, const float& angle) const;
    public:
        Vector3 right;
        Vector3 up;
        Vector3 forward;
    private:
        Vector3 m_position;
        Vector3 m_rotation;
        Vector3 m_scale;

        Matrix4x4 m_scaleMatrix;
        Matrix4x4 m_positionMatrix;
        Matrix4x4 m_rotationMatrix;

        Transform* m_parent;
        std::vector<Transform*> m_children;
    };   
}
