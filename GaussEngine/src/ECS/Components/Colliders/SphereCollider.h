#pragma once
#include "Collider.h"

namespace GAUSS
{
    struct SphereCollider final : public Collider
    {
        friend class EntityComponentLookup;
    protected:
        SphereCollider() : radius(0) {}
        ~SphereCollider() override = default;
    public:
        std::vector<int> GetEnum() override {return {GAUSS_ENUMS::SphereCollider, GAUSS_ENUMS::Collider};}
        
        std::vector<Vector3> GetAxes(const Vector3& position, const Matrix4x4& rotation, const Vector3& otherPosition) const override;
        std::vector<Vector3> GetVertices(const Vector3& position, const Matrix4x4& rotation, const Vector3& otherPosition) const override;
        
        float GetStiffness() const override {return 20.0f;}
    public:
        float radius;
    };   
}
