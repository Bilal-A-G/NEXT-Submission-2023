#pragma once
#include "Collider.h"

namespace GAUSS
{
    struct BoxCollider final : public Collider
    {
        friend class EntityComponentLookup;
    protected:
        BoxCollider() : width(0), height(0), depth(0) {}
        ~BoxCollider() override = default;
    public:
        std::vector<int> GetEnum() override {return {GAUSS_ENUMS::BoxCollider, GAUSS_ENUMS::Collider};}
        
        std::vector<Vector3> GetAxes(const Vector3& position, const Matrix4x4& rotation, const Vector3& otherPosition) const override;
        std::vector<Vector3> GetVertices(const Vector3& position, const Matrix4x4& rotation, const Vector3& otherPosition) const override;
    public:
        float width;
        float height;
        float depth;
    };    
}

