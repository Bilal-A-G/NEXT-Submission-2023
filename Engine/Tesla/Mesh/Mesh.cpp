#include "TSPch.h"
#include "Mesh.h"

#include "Core/EntryPoint.h"
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

    this->position = this->position + translation;
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
    CalculateModelTriangles();
    CalculateNormals();
            
    for(int i = 0; i < m_modelTriangles.size(); i++)
    {
        if(TESLA::Vector::Dot(m_normals[i], mainCamera->position - m_modelTriangles[i].vertices[0]) < 0.0f)
        {
            TESLA::Triangle projTri = m_modelTriangles[i];
            
            for (int v = 0; v < 3; v++)
            {
                //Mvp stuff
                projTri.vertices[v] = projection * m_modelTriangles[i].vertices[v];

                //Doing the perspective divide
                projTri.vertices[v] = projTri.vertices[v].PerspectiveDivide();

                //Translating to normalized device space
                projTri.vertices[v] += Vector(1.0f, 1.0f, 0.0f);
                projTri.vertices[v] = Vector(projTri.vertices[v].x * APP_VIRTUAL_WIDTH, projTri.vertices[v].y * APP_VIRTUAL_HEIGHT * 2.0f, 0.0f) * 0.5f;
            }

            projectedTriangles.push_back(projTri);
        }
    }
    
    return projectedTriangles;
}

void TESLA::Mesh::CalculateModelTriangles()
{
    m_modelTriangles.clear();
    
    const TESLA::Matrix4x4 model = translationMatrix * scaleMatrix * rotationMatrix;
    for (Triangle triangle : m_triangles)
    {
        TESLA::Triangle movedTri = triangle;
        
        for (int i = 0; i < 3; i++)
        {
            movedTri.vertices[i] = view * model * triangle.vertices[i];
        }

        m_modelTriangles.push_back(movedTri);
    }
}


void TESLA::Mesh::CalculateNormals()
{
    m_normals.clear();
    
    for (Triangle triangle : m_modelTriangles)
    {
        Vector lineA = triangle.vertices[1] - triangle.vertices[0];
        Vector lineB = triangle.vertices[2] - triangle.vertices[1];
        
        m_normals.push_back(TESLA::Vector::Cross(lineA, lineB).Normalize());
    }
}





