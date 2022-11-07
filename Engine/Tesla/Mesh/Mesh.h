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

    struct Face
    {
    public:
        Face(Triangle triangle, Vector colour):
            triangle(triangle), colour(colour){}

        Face(){}
        void RecalculateNormal()
        {
            normal = TESLA::Vector::Cross(triangle.vertices[1] - triangle.vertices[0],
            triangle.vertices[2] - triangle.vertices[1]).Normalize();
        }
    public:
        Triangle triangle;
        Vector normal;
        Vector colour;
    };
    
    struct Mesh
    {
        Mesh(std::vector<Triangle> triangles, Vector colour = TESLA::Vector(1.0f, 1.0f, 1.0f)):
        scaleMatrix(TESLA::Matrix4x4::Identity()), rotationMatrix(TESLA::Matrix4x4::Identity()), translationMatrix(TESLA::Matrix4x4::Identity()),
        colour(colour)
        {
            for (int i = 0; i < triangles.size(); i++)
            {
                m_faces.push_back(Face(triangles[i], this->colour));
            }
            RenderQueue::AddToQueue(this);
        }

        ~Mesh()
        {
            RenderQueue::RemoveFromQueue(this);
        }
        
        void Translate(TESLA::Vector translation);
        void Rotate(float angle, TESLA::Vector axis);
        void Scale(float scale, TESLA::Vector axis);

        std::vector<Face> GetProjectedFaces(Matrix4x4 view, Matrix4x4 projection);
        void RecalculateLighting(std::vector<Face>& projectedFaces, Vector lightPosition, float lightIntensity);
    private:
        std::vector<Face> m_faces;
        
        Matrix4x4 scaleMatrix;
        Matrix4x4 rotationMatrix;
        Matrix4x4 translationMatrix;
    public:
        Vector colour;
        Vector position;
        Vector rotation;
        Vector size;
    };
}
