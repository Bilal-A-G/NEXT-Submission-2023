#include "GSPch.h"
#include "SphereCollider.h"

namespace GAUSS
{
    std::vector<Vector3> SphereCollider::GetAxes(Vector3 position, Matrix4x4 rotation, Vector3 otherPosition)
    {
        Vector3 normalizedDirToOther = (otherPosition - position).Normalize();
    
        return {
            normalizedDirToOther
        };
    }

    std::vector<Vector3> SphereCollider::GetVertices(Vector3 position, Matrix4x4 rotation, Vector3 otherPosition)
    {
        Vector3 directionToOther = (otherPosition - position).Normalize();
        Vector3 r0 = position + directionToOther * radius;
        Vector3 r1 = position + directionToOther * -radius;
    
        return {
            r0,
            r1
        };
    }
}

