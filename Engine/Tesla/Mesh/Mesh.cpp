#include "TSPch.h"
#include "Mesh.h"
#include "NextAPI/AppSettings.h"

void TESLA::Mesh::Translate(TESLA::Vector translation)
{
    this->translationMatrix = this->translationMatrix * Matrix4x4
    {       
        {1.0f, 0.0f, 0.0f, translation.x},
        {0.0f, 1.0f, 0.0f, translation.y},
        {0.0f, 0.0f, 1.0f, translation.z},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };

    this->position = this->position * translation;
}

void TESLA::Mesh::Rotate(float angle, TESLA::Vector axis)
{
    float cosTheta = cos(angle);
    float sinTheta = sin(angle);

    TESLA::Matrix4x4 rotationY;
    TESLA::Matrix4x4 rotationX;
    TESLA::Matrix4x4 rotationZ;
            
    if(axis.y == 0)
    {
        rotationY = TESLA::Matrix4x4::Identity();
    }
    else
    {
        rotationY = 
        {
            {cosTheta, 0.0f, -sinTheta, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {sinTheta, 0.0f, cosTheta, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
    }

    if(axis.x == 0)
    {
        rotationX = TESLA::Matrix4x4::Identity();
    }
    else
    {
        rotationX = TESLA::Matrix4x4
        {
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, cosTheta, sinTheta, 0.0f},
            {0.0f, -sinTheta, cosTheta, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
    }
            
    if(axis.z == 0)
    {
        rotationZ = TESLA::Matrix4x4::Identity();
    }
    else
    {
        rotationZ = 
        {
            {cosTheta, sinTheta, 0.0f, 0.0f},
            {-sinTheta, cosTheta, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };
    }

    this->rotationMatrix = this->rotationMatrix * (rotationY * rotationX * rotationZ);
    this->rotation = this->rotation + axis * angle;
}

void TESLA::Mesh::Scale(float scale, TESLA::Vector axis)
{
    Vector normalizedAxis = axis.Normalize();
    this->scaleMatrix = this->scaleMatrix * TESLA::Matrix4x4
    {
        {normalizedAxis.x * scale, 0.0f, 0.0f, 0.0f},
        {0.0f, normalizedAxis.y * scale, 0.0f, 0.0f},
        {0.0f, 0.0f, normalizedAxis.z * scale, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };

    this->size = this->size + normalizedAxis * scale;
}

std::vector<TESLA::Triangle> TESLA::Mesh::GetProjectedTriangles()
{
    std::vector<Triangle> projectedTriangles;
    const TESLA::Matrix4x4 model = translationMatrix * scaleMatrix * rotationMatrix;
            
    for(auto triangle : triangles)
    {
        TESLA::Triangle projTri = triangle;

        for (int i = 0; i < 3; i++)
        {
            //Mvp stuff
            projTri.vertices[i] = projection * view * model * triangle.vertices[i];

            //Doing the perspective divide
            projTri.vertices[i] = projTri.vertices[i].PerspectiveDivide();

            //Translating to normalized device space
            projTri.vertices[i] += Vector(1.0f, 1.0f, 0.0f);
            projTri.vertices[i] *= Vector(APP_VIRTUAL_WIDTH, APP_VIRTUAL_HEIGHT * 2.0f, 0.0f) * 0.5f;
        }

        projectedTriangles.push_back(projTri);
    }

    return projectedTriangles;
}



