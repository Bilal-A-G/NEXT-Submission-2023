#pragma once
#include <vector>
#include "array"
#include "../Math/Math.h"
#include "../Renderer/RenderQueue.h"

namespace TESLA
{
    struct Triangle
    {
    public:
        Triangle(std::initializer_list<Vector> vertices):vertices()
        {
            this->vertices[0] = data(vertices)[0];
            this->vertices[1] = data(vertices)[1];
            this->vertices[2] = data(vertices)[2];
        }

        Triangle(){}
    public:
        std::array<Vector, 3> vertices;
    };
    
    struct Mesh
    {
        Mesh(std::vector<Triangle>& triangles):
        triangles(triangles),
        scaleMatrix(TESLA::Matrix4x4::Identity()), rotationMatrix(TESLA::Matrix4x4::Identity()),
        translationMatrix(TESLA::Matrix4x4::Identity()),
        view(view), projection(TESLA::Matrix4x4::Identity())
        {
            RenderQueue::AddToQueue(this);
        }

        Mesh()
        {
            RenderQueue::AddToQueue(this);
        }

        ~Mesh()
        {
            RenderQueue::RemoveFromQueue(this);
        }
        
        void Translate(TESLA::Vector translation)
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

        void Rotate(float angle, TESLA::Vector axis)
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

        void Scale(float scale, TESLA::Vector axis)
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

        std::vector<Triangle> GetProjectedTriangles()
        {
            std::vector<Triangle> projectedTriangles;
            
            for(auto triangle : triangles)
            {
                TESLA::Triangle projTri;
                
                projTri.vertices[0] = triangle.vertices[0] * (translationMatrix * scaleMatrix * rotationMatrix) * view * projection;
                projTri.vertices[1] = triangle.vertices[1] * (translationMatrix * scaleMatrix * rotationMatrix) * view * projection;
                projTri.vertices[2] = triangle.vertices[2] * (translationMatrix * scaleMatrix * rotationMatrix) * view * projection;

                projectedTriangles.push_back(projTri);
            }

            return projectedTriangles;
        }
    private:
        std::vector<Triangle> triangles;
        Matrix4x4 scaleMatrix;
        Matrix4x4 rotationMatrix;
        Matrix4x4 translationMatrix;
    public:
        Vector position;
        Vector rotation;
        Vector size;
        
        Matrix4x4 view;
        Matrix4x4 projection;
    };
}
