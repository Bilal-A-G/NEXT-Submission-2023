#include "TSPch.h"
#include "SphereCollider.h"

std::vector<TESLA::Vector> TESLA::SphereCollider::GetEdges(TESLA::Vector position, TESLA::Vector rotation)
{
    return {
        position + TESLA::Vector(radius, 0, 0),
        position + TESLA::Vector(0, radius, 0),
        position + TESLA::Vector(0, 0, radius),
    };
}
