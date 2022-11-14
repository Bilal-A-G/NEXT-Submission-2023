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

std::vector<TESLA::Face> TESLA::Mesh::GetProjectedFaces(Matrix4x4 view, Matrix4x4 projection)
{
    std::vector<Face> passedFaces;
    TESLA::Matrix4x4 model = translationMatrix * rotationMatrix * scaleMatrix;
    
    for(Face face : m_faces)
    {
        TESLA::Face projFace(face.triangle, face.colour);
        
        for(int i = 0; i < 3; i++)
        {
            projFace.triangle.vertices[i] = (projFace.triangle.vertices[i] * model);
        }

        projFace.RecalculateNormal();
        
        //Backface culling!
        if(TESLA::Vector::Dot(projFace.normal, (mainCamera->position - projFace.triangle.vertices[0]).Normalize()) < 0.0f)
        {
            for (int j = 0; j < 3; j++)
            {
                //View
                projFace.triangle.vertices[j] = view * projFace.triangle.vertices[j];
            }

            //Depth clipping!!
            TESLA::ClipAgainstPlane({0.0f, 0.0f, 0.1f}, {0.0f, 0.0f, 1.0f}, projFace, passedFaces);
        }
    }

    for (Face& face : passedFaces)
    {
        face.RecalculateNormal();
        
        for (int k = 0; k < 3; k++)
        {
            //Projection
            face.triangle.vertices[k] = projection * face.triangle.vertices[k];
                
            //Doing the perspective divide
            face.triangle.vertices[k] = face.triangle.vertices[k].PerspectiveDivide();

            //Translating to normalized device space
            face.triangle.vertices[k] += Vector(1.0f, 1.0f, 0.0f, 0.0f);
            face.triangle.vertices[k] = Vector(face.triangle.vertices[k].x * (float)APP_VIRTUAL_WIDTH, face.triangle.vertices[k].y * (float)APP_VIRTUAL_HEIGHT, 0.0f)/2;
        }
    }
    
    return passedFaces;
}

void TESLA::Mesh::RecalculateLighting(std::vector<Face>& projectedFaces, Vector lightPosition, float lightIntensity)
{
    for (Face& face : projectedFaces)
    {
        TESLA::Vector ambient = TESLA::Vector(1,1,1) * 0.2;
        TESLA::Vector lightDirection = (lightPosition - (face.triangle.vertices[0] + face.triangle.vertices[1] + face.triangle.vertices[2])/3).Normalize();
        float incidentAngle = std::max(TESLA::Vector::Dot(face.normal, lightDirection), 0.0f);
        
        TESLA::Vector diffuse = TESLA::Vector(1,1,1) * incidentAngle * lightIntensity;

        TESLA::Vector totalColour = ambient + diffuse;
        face.colour = Vector(totalColour.x * colour.x, totalColour.y * colour.y, totalColour.z * colour.z);
    }
}