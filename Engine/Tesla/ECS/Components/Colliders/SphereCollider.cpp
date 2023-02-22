#include "TSPch.h"
#include "SphereCollider.h"

std::vector<TESLA::Vector3> TESLA::SphereCollider::GetAxes(TESLA::Vector3 position, TESLA::Matrix4x4 rotation, TESLA::Vector3 otherPosition)
{
    Vector3 normalizedDirToOther = (otherPosition - position).Normalize();
    
    return {
        normalizedDirToOther
    };
}

std::vector<TESLA::Vector3> TESLA::SphereCollider::GetVertices(TESLA::Vector3 position, TESLA::Matrix4x4 rotation, TESLA::Vector3 otherPosition)
{
    TESLA::Vector3 directionToOther = (otherPosition - position).Normalize();
    TESLA::Vector3 r0 = position + directionToOther * radius;
    TESLA::Vector3 r1 = position + directionToOther * -radius;
    
    return {
        r0,
        r1
    };
}

