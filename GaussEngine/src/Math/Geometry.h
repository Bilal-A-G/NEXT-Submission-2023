#pragma once
#include "Math/Math.h"
#include "array"
#include "API/AppSettings.h"

namespace GAUSS
{
    struct Triangle
    {
    public:
        Triangle(std::initializer_list<Vector3> vertices):vertices()
        {
            this->vertices[0] = data(vertices)[0];
            this->vertices[1] = data(vertices)[1];
            this->vertices[2] = data(vertices)[2];
        }

        Triangle(){}
    public:
        std::array<Vector3, 3> vertices;
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

        static bool RoughlyEquals(Colour a, Colour b, float tolerance)
        {
            return (a.r == b.r || a.r >= b.r - tolerance && a.r <= b.r + tolerance) &&
                (a.g == b.g || a.g >= b.g - tolerance && a.g <= b.g + tolerance) &&
                    (a.b == b.b || a.b >= b.b - tolerance && a.b <= b.b + tolerance);
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
            Vector3 edge1 = Vector3(triangle.vertices[2].x, triangle.vertices[2].y, triangle.vertices[2].z) -
                Vector3(triangle.vertices[0].x, triangle.vertices[0].y, triangle.vertices[0].z);

            Vector3 edge2 = Vector3(triangle.vertices[1].x, triangle.vertices[1].y, triangle.vertices[1].z) -
                Vector3(triangle.vertices[0].x, triangle.vertices[0].y, triangle.vertices[0].z);
            
            normal = Vector3::Cross(edge1, edge2).Normalize();
        }
    public:
        Triangle triangle;
        Vector3 normal;
        Colour colour;
    };

    inline void ClipAgainstPlane(Vector3 planePos, Vector3 planeNormal, Face in, std::vector<Face>& faceQueue)
    {
        Vector3 normal = planeNormal.Normalize();
        auto dist = [&](Vector3 point)
        {
            return(normal.x * point.x + normal.y * point.y + normal.z * point.z - Vector3::Dot(normal, planePos));
        };
        
        static std::vector<Vector3> insidePoints;
        insidePoints.clear();
        if(insidePoints.capacity() != 3)
        {
            insidePoints.reserve(3);
        }
        int insideSize = 0;
        
        static std::vector<Vector3> outsidePoints;
        outsidePoints.clear();
        if(outsidePoints.capacity() != 3)
        {
            outsidePoints.reserve(3);
        }

        for (int i = 0; i < 3; i++)
        {
            Vector3 currentVertex = in.triangle.vertices[i];
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
        Vector3 p0;
        Vector3 p1;
        Vector3 p2;
        
        switch (insideSize)
        {
        case 1:
            outFace.colour = in.colour;
            
            p0 = insidePoints[0];
            p1 = IntersectPlane(planePos, normal, insidePoints[0], outsidePoints[0]);
            p2 = IntersectPlane(planePos, normal, insidePoints[0], outsidePoints[1]);
            
            outFace.triangle = {p0, p1, p2};
            faceQueue.push_back(outFace);
            break;
        case 2:
            for (int i = 0; i < 2; i++)
            {
                outFace.colour = in.colour;
            
                p0 = insidePoints[i];
                p1 = i == 1 ? IntersectPlane(planePos, normal, insidePoints[0], outsidePoints[0]) : insidePoints[1];
                p2 = IntersectPlane(planePos, normal, insidePoints[i], outsidePoints[0]);
            
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

    inline void CalculateLighting(std::vector<Face>& projectedFaces, Vector3 lightPosition, float lightIntensity, Colour baseColour)
    {
        for (Face& face : projectedFaces)
        {
            Colour ambient = Colour(1,1,1) * 0.5;
            Vector3 lightDirection = (lightPosition - (face.triangle.vertices[0] + face.triangle.vertices[1] + face.triangle.vertices[2])/3).Normalize();
            float incidentAngle = Vector3::Dot(face.normal, lightDirection);
            if(incidentAngle < 0)
            {
                incidentAngle = 0;
            }
        
            Colour diffuse = Colour(1,1,1) * incidentAngle * lightIntensity;

            Colour totalColour = ambient + diffuse;
            face.colour = totalColour * baseColour;
        }
    }

    inline std::vector<Face> ProjectToWorld(Matrix4x4 model, std::vector<Face>& faces)
    {
        std::vector<Face> projectedFaces;
    
        for(Face face : faces)
        {
            Face projFace(face.triangle, face.colour);
        
            for(int i = 0; i < 3; i++)
            {
                Vector4 vec4Vertex = Vector4(projFace.triangle.vertices[i].x, projFace.triangle.vertices[i].y, projFace.triangle.vertices[i].z, 1);
                Vector4 modelSpaceVertex = model * vec4Vertex;
                projFace.triangle.vertices[i] = Vector3(modelSpaceVertex.x, modelSpaceVertex.y, modelSpaceVertex.z);
            }

            projFace.CalculateNormal();
            projectedFaces.push_back(projFace);
        }

        return projectedFaces;
    }

    inline std::vector<Face> ProjectToView(std::vector<Face>& worldFaces, Vector3 cameraPosition, Matrix4x4 view)
    {
        std::vector<Face> passedFaces;
        
        for (Face projFace : worldFaces)
        {
            //Backface culling!
            if(Vector3::Dot(projFace.normal, (cameraPosition - projFace.triangle.vertices[0]).Normalize()) < 0.0f)
            {
                for (int j = 0; j < 3; j++)
                {
                    //View
                    Vector4 vec4Vertex = Vector4(projFace.triangle.vertices[j].x, projFace.triangle.vertices[j].y, projFace.triangle.vertices[j].z, 1);
                    Vector4 viewSpaceVertex = view * vec4Vertex;
                    projFace.triangle.vertices[j] = Vector3(viewSpaceVertex.x, viewSpaceVertex.y, viewSpaceVertex.z);
                }
        
                //Depth clipping!!
                ClipAgainstPlane({0.0f, 0.0f, 0.1f}, {0.0f, 0.0f, 1.0f}, projFace, passedFaces);
            }
        }

        return passedFaces;
    }

    inline std::vector<Face> ProjectToScreen(std::vector<Face>& viewFaces, Matrix4x4 projection)
    {
        std::vector<Face> screenFaces = viewFaces;
        
        for (Face& face : screenFaces)
        {
            face.CalculateNormal();
        
            for (int k = 0; k < 3; k++)
            {
                //Projection
                Vector4 vec4Vertex = Vector4(face.triangle.vertices[k].x, face.triangle.vertices[k].y, face.triangle.vertices[k].z, 1);
                Vector4 projectedVertex = projection * vec4Vertex;
                
                //Doing the perspective divide
                face.triangle.vertices[k] = projectedVertex.PerspectiveDivide();
        
                //Translating to normalized device space
                face.triangle.vertices[k] += Vector3(1.0f, 1.0f, 0.0f);
                face.triangle.vertices[k] = Vector3(face.triangle.vertices[k].x * (float)APP_VIRTUAL_WIDTH, face.triangle.vertices[k].y * (float)APP_VIRTUAL_HEIGHT, 0.0f)/2;
            }
        }

        return screenFaces;
    }

    inline Matrix4x4 CalculateView(Vector3 position, Vector3 forward, Vector3 up)
    {
        Matrix4x4 pointAtMatrix = Matrix4x4::PointAt(position, position + forward, up);
        return Matrix4x4::LookAt(pointAtMatrix);
    }
}
