#include "GSPch.h"
#include "SphereCollider.h"

namespace GAUSS
{
    std::vector<Vector3> SphereCollider::GetAxes(const Vector3& position, const Matrix4x4& rotation, const Vector3& otherPosition) const
    {
        return std::vector<Vector3>{(otherPosition - position).Normalize()};
    }

    std::vector<Vector3> SphereCollider::GetVertices(const Vector3& position, const Matrix4x4& rotation, const Vector3& otherPosition) const
    {
        const Vector3 directionToOther = (otherPosition - position).Normalize();
        const Vector3 r0 = position + directionToOther * radius;
        const Vector3 r1 = position + directionToOther * -radius;
    
        return std::vector<Vector3>{r0, r1};
    }
}

