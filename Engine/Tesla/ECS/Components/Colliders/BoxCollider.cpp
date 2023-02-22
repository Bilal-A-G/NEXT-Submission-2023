#include "TSpch.h"
#include "BoxCollider.h"

std::vector<TESLA::Vector3> TESLA::BoxCollider::GetAxes(TESLA::Vector3 position, TESLA::Matrix4x4 rotation, TESLA::Vector3 otherPosition)
{
    Vector4 r0 = TESLA::Vector4(1, 0, 0, 1) * rotation;
    Vector4 r1 = TESLA::Vector4(-1, 0, 0, 1) * rotation;

    Vector4 r2 = TESLA::Vector4(0, 1, 0, 1) * rotation;
    Vector4 r3 = TESLA::Vector4(0, -1, 0, 1) * rotation;
        
    Vector4 r4 = TESLA::Vector4(0, 0, 1, 1) * rotation;
    Vector4 r5 = TESLA::Vector4(0, 0, -1, 1) * rotation;
    
    std::vector<TESLA::Vector3> axis
    {
        TESLA::Vector3(r0.x, r0.y, r0.z),
        TESLA::Vector3(r1.x, r1.y, r1.z),
        
        TESLA::Vector3(r2.x, r2.y, r2.z),
        TESLA::Vector3(r3.x, r3.y, r3.z),
        
        TESLA::Vector3(r4.x, r4.y, r4.z),
        TESLA::Vector3(r5.x, r5.y, r5.z)
    };
    
    return axis;
}

std::vector<TESLA::Vector3> TESLA::BoxCollider::GetVertices(TESLA::Vector3 position, TESLA::Matrix4x4 rotation, TESLA::Vector3 otherPosition)
{
    Vector4 vec4Position = Vector4(position.x, position.y, position.z, 1);

    Vector4 r0 = vec4Position + TESLA::Vector4(width/2, -height/2, depth/2, 1) * rotation;
    Vector4 r1 = vec4Position + TESLA::Vector4(-width/2, -height/2, depth/2, 1) * rotation;
    Vector4 r2 = vec4Position + TESLA::Vector4(width/2, height/2, depth/2, 1) * rotation;
    Vector4 r3 = vec4Position + TESLA::Vector4(-width/2, height/2, depth/2, 1) * rotation;
    Vector4 r4 = vec4Position + TESLA::Vector4(width/2, -height/2, -depth/2, 1) * rotation;
    Vector4 r5 = vec4Position + TESLA::Vector4(-width/2, -height/2, -depth/2, 1) * rotation;
    Vector4 r6 = vec4Position + TESLA::Vector4(width/2, height/2, -depth/2, 1) * rotation;
    Vector4 r7 = vec4Position + TESLA::Vector4(-width/2, height/2, -depth/2, 1) * rotation;
    
    std::vector<TESLA::Vector3> vertices
    {
        Vector3(r0.x, r0.y, r0.z),
        Vector3(r1.x, r1.y, r1.z),
        
        Vector3(r2.x, r2.y, r2.z),
        Vector3(r3.x, r3.y, r3.z),
        
        Vector3(r4.x, r4.y, r4.z),
        Vector3(r5.x, r5.y, r5.z),
        
        Vector3(r6.x, r6.y, r6.z),
        Vector3(r7.x, r7.y, r7.z),
    };
    return vertices;
}

