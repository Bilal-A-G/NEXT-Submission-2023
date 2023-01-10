#include "TSPch.h"
#include "SphereCollider.h"

std::vector<TESLA::Vector> TESLA::SphereCollider::GetAxes(TESLA::Vector position, TESLA::Vector rotation, TESLA::Vector otherPosition)
{
    return {
        TESLA::Vector(otherPosition - position).Normalize()
    };
}

std::vector<TESLA::Vector> TESLA::SphereCollider::GetVertices(TESLA::Vector position, TESLA::Vector rotation, TESLA::Vector otherPosition)
{
    TESLA::Vector directionToOther = (otherPosition - position).Normalize();
    
    return {
        position + directionToOther * radius,
        position + directionToOther * -radius
    };
}

