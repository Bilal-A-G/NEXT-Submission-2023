#include "TSpch.h"
#include "BoxCollider.h"

std::vector<TESLA::Vector> TESLA::BoxCollider::GetAxes(TESLA::Vector position, TESLA::Matrix4x4 rotation, TESLA::Vector otherPosition)
{
    std::vector<TESLA::Vector> axis
    {
        TESLA::Vector(1, 0, 0) * rotation,
        TESLA::Vector(-1, 0, 0) * rotation,
        
        TESLA::Vector(0, 1, 0) * rotation,
        TESLA::Vector(0, -1, 0) * rotation,
        
        TESLA::Vector(0, 0, 1) * rotation,
        TESLA::Vector(0, 0, -1) * rotation,
    };
    return axis;
}

std::vector<TESLA::Vector> TESLA::BoxCollider::GetVertices(TESLA::Vector position, TESLA::Matrix4x4 rotation, TESLA::Vector otherPosition)
{
    std::vector<TESLA::Vector> vertices
    {
        (position + TESLA::Vector(width/2, -height/2, depth/2) * rotation),
        (position + TESLA::Vector(-width/2, -height/2, depth/2) * rotation),
        
        (position + TESLA::Vector(width/2, height/2, depth/2) * rotation),
        (position + TESLA::Vector(-width/2, height/2, depth/2) * rotation),
        
        (position + TESLA::Vector(width/2, -height/2, -depth/2) * rotation),
        (position + TESLA::Vector(-width/2, -height/2, -depth/2) * rotation),
        
        (position + TESLA::Vector(width/2, height/2, -depth/2) * rotation),
        (position + TESLA::Vector(-width/2, height/2, -depth/2) * rotation),
    };
    return vertices;
}

