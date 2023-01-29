#pragma once
#include "../Math/Math.h"
#include "array"
#include "NextAPI/AppSettings.h"

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

    struct Colour
    {
        Colour(float r, float g, float b) : r(r), g(g), b(b){}
        
        static Colour Red(){return {1, 0, 0};}
        static Colour Green(){return {0, 1, 0};}
        static Colour Blue(){return {0, 0, 1};}
        static Colour White(){return {1, 1, 1};}
        static Colour Black(){return {0, 0, 0};}

        static Colour Lerp(Colour from, Colour to, float interpolation)
        {
            return from * (1 - interpolation) + to * interpolation;
        }
        
        Colour(){}

        Colour operator *(const float& other) const
        {
            return  {r * other, g * other, b * other};
        }

        Colour operator *(const Colour& other) const
        {
            return {r * other.r, g * other.g, b * other.b};
        }
        
        Colour operator +(const Colour& other) const
        {
            return {r + other.r, g + other.g, b + other.b};
        }
    public:
        float r;
        float g;
        float b;
    };

    struct Face
    {
    public:
        Face(Triangle triangle, Colour colour):
            triangle(triangle), colour(colour){}

        Face(){}
        void CalculateNormal()
        {
            normal = TESLA::Vector::Cross(triangle.vertices[2] - triangle.vertices[0],
            triangle.vertices[1] - triangle.vertices[0]).Normalize();
        }
    public:
        Triangle triangle;
        Vector normal;
        Colour colour;
    };

    inline void ClipAgainstPlane(Vector planePos, Vector planeNormal, TESLA::Face in, std::vector<TESLA::Face>& faceQueue)
    {
        Vector normal = planeNormal.Normalize();
        auto dist = [&](Vector point)
        {
            return(normal.x * point.x + normal.y * point.y + normal.z * point.z - TESLA::Vector::Dot(normal, planePos));
        };
        
        static std::vector<Vector> insidePoints;
        insidePoints.clear();
        if(insidePoints.capacity() != 3)
        {
            insidePoints.reserve(3);
        }
        int insideSize = 0;
        
        static std::vector<Vector> outsidePoints;
        outsidePoints.clear();
        if(outsidePoints.capacity() != 3)
        {
            outsidePoints.reserve(3);
        }

        for (int i = 0; i < 3; i++)
        {
            Vector currentVertex = in.triangle.vertices[i];
            float distance = dist(currentVertex);
            if (distance >= 0)
            {
                insidePoints.emplace_back(currentVertex);
                insideSize++;
            }
            else
            {
                outsidePoints.emplace_back(currentVertex);
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
            p1 = TESLA::IntersectPlane(planePos, normal, insidePoints[0], outsidePoints[0]);
            p2 = TESLA::IntersectPlane(planePos, normal, insidePoints[0], outsidePoints[1]);
            
            outFace.triangle = {p0, p1, p2};
            faceQueue.push_back(outFace);
            break;
        case 2:
            for (int i = 0; i < 2; i++)
            {
                outFace.colour = in.colour;
            
                p0 = insidePoints[i];
                p1 = i == 1 ? TESLA::IntersectPlane(planePos, normal, insidePoints[0], outsidePoints[0]) : insidePoints[1];
                p2 = TESLA::IntersectPlane(planePos, normal, insidePoints[i], outsidePoints[0]);
            
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

    inline void CalculateLighting(std::vector<Face>& projectedFaces, Vector lightPosition, float lightIntensity, Colour baseColour)
    {
        for (Face& face : projectedFaces)
        {
            TESLA::Colour ambient = TESLA::Colour(1,1,1) * 0.5;
            TESLA::Vector lightDirection = (lightPosition - (face.triangle.vertices[0] + face.triangle.vertices[1] + face.triangle.vertices[2])/3).Normalize();
            float incidentAngle = TESLA::Vector::Dot(face.normal, lightDirection);
            if(incidentAngle < 0)
            {
                incidentAngle = 0;
            }
        
            TESLA::Colour diffuse = TESLA::Colour(1,1,1) * incidentAngle * lightIntensity;

            TESLA::Colour totalColour = ambient + diffuse;
            face.colour = totalColour * baseColour;
        }
    }

    inline std::vector<TESLA::Face> ProjectToWorld(Matrix4x4 model, std::vector<Face>& faces)
    {
        std::vector<Face> projectedFaces;
    
        for(Face face : faces)
        {
            TESLA::Face projFace(face.triangle, face.colour);
        
            for(int i = 0; i < 3; i++)
            {
                projFace.triangle.vertices[i] = model * projFace.triangle.vertices[i];
            }

            projFace.CalculateNormal();
            projectedFaces.push_back(projFace);
        }

        return projectedFaces;
    }

    inline std::vector<TESLA::Face> ProjectToView(std::vector<Face>& worldFaces, Vector cameraPosition, Matrix4x4 view)
    {
        std::vector<Face> passedFaces;
        
        for (Face projFace : worldFaces)
        {
            //Backface culling!
            if(TESLA::Vector::Dot(projFace.normal, (cameraPosition - projFace.triangle.vertices[0]).Normalize()) < 0.0f)
            {
                for (int j = 0; j < 3; j++)
                {
                    //View
                    projFace.triangle.vertices[j] = projFace.triangle.vertices[j] * view;
                }
        
                //Depth clipping!!
                TESLA::ClipAgainstPlane({0.0f, 0.0f, 0.1f}, {0.0f, 0.0f, 1.0f}, projFace, passedFaces);
            }
        }

        return passedFaces;
    }

    inline std::vector<TESLA::Face> ProjectToScreen(std::vector<Face>& viewFaces, Matrix4x4 projection)
    {
        std::vector<Face> screenFaces = viewFaces;
        
        for (Face& face : screenFaces)
        {
            face.CalculateNormal();
        
            for (int k = 0; k < 3; k++)
            {
                //Projection
                face.triangle.vertices[k] = face.triangle.vertices[k] * projection;
                
                //Doing the perspective divide
                face.triangle.vertices[k] = face.triangle.vertices[k].PerspectiveDivide();
        
                //Translating to normalized device space
                face.triangle.vertices[k] += Vector(1.0f, 1.0f, 0.0f, 0.0f);
                face.triangle.vertices[k] = Vector(face.triangle.vertices[k].x * (float)APP_VIRTUAL_WIDTH, face.triangle.vertices[k].y * (float)APP_VIRTUAL_HEIGHT, 0.0f)/2;
            }
        }

        return screenFaces;
    }

    inline Matrix4x4 CalculateView(Vector position, Vector forward, Vector up)
    {
        TESLA::Matrix4x4 pointAtMatrix = TESLA::Matrix4x4::PointAt(position, position + forward, up);
        return Matrix4x4::LookAt(pointAtMatrix);
    }
}
