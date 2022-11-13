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
            normal = TESLA::Vector::Cross(triangle.vertices[2] - triangle.vertices[0],
            triangle.vertices[1] - triangle.vertices[0]).Normalize();
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

    inline void ClipAgainstPlane(Vector planePos, Vector planeNormal, TESLA::Face in, std::vector<TESLA::Face>& faceQueue)
    {
        Vector normal = planeNormal.Normalize();
        auto dist = [&](Vector point)
        {
            return(normal.x * point.x + normal.y * point.y + normal.z * point.z - TESLA::Vector::Dot(normal, planePos));
        };
        
        std::array<Vector, 3> insidePoints;
        int insideSize = 0;
        
        std::array<Vector, 3> outsidePoints;

        for (int i = 0; i < 3; i++)
        {
            Vector currentVertex = in.triangle.vertices[i];
            float distance = dist(currentVertex);
            if (distance >= 0)
            {
                insidePoints[i] = currentVertex;
                insideSize++;
            }
            else
            {
                outsidePoints[i] = currentVertex;
            }
        }

        Face outFace;
        Vector p0;
        Vector p1;
        Vector p2;
        
        switch (insideSize)
        {
        case 1:
            outFace.colour = in.colour;
            
            p0 = insidePoints[0];
            p1 = TESLA::IntersectPlane(planePos, normal, insidePoints[0], outsidePoints[1]);
            p2 = TESLA::IntersectPlane(planePos, normal, insidePoints[0], outsidePoints[2]);
            
            outFace.triangle = {p0, p1, p2};
            faceQueue.push_back(outFace);
            break;
        case 2:
            for (int i = 0; i < 2; i++)
            {
                outFace.colour = in.colour;
            
                p0 = insidePoints[i];
                p1 = i == 1 ? TESLA::IntersectPlane(planePos, normal, insidePoints[0], outsidePoints[2]) : insidePoints[1];
                p2 = TESLA::IntersectPlane(planePos, normal, insidePoints[i], outsidePoints[2]);
            
                outFace.triangle = {p0, p1, p2};
                faceQueue.push_back(outFace);
            }
            break;
        case 3:
            faceQueue.push_back(in);
            break;
        default:
            break;
        }
    }
}
