#pragma once
#include "Math/Math.h"
#include "array"
#include "API/AppSettings.h"

namespace GAUSS
{
    struct Triangle
    {
    public:
        Triangle(const std::array<Vector3, 3>& vertices) : vertices(vertices){}
        Triangle() : vertices(std::array<Vector3, 3>()){}
    public:
        std::array<Vector3, 3> vertices;
    };

    struct Colour
    {
    public:
        Colour(const float& r, const float& g, const float& b) : r(r), g(g), b(b){}
        Colour() : r(0), g(0), b(0){}
        
        static Colour Red() {return {1, 0, 0};}
        static Colour Green() {return {0, 1, 0};}
        static Colour Blue() {return {0, 0, 1};}
        static Colour White() {return {1, 1, 1};}
        static Colour Black() {return {0, 0, 0};}

        static Colour Lerp(const Colour& from, const Colour& to, const float& interpolation)
        {
            return from * (1 - interpolation) + to * interpolation;
        }

        static bool RoughlyEquals(const Colour& a, const Colour& b, const float& tolerance)
        {
            return (a.r >= b.r - tolerance && a.r <= b.r + tolerance) &&
                (a.g >= b.g - tolerance && a.g <= b.g + tolerance) &&
                    (a.b >= b.b - tolerance && a.b <= b.b + tolerance);
        }

        Colour operator *(const float& other) const {return Colour(r * other, g * other, b * other);}
        Colour operator *(const Colour& other) const {return Colour(r * other.r, g * other.g, b * other.b);}
        Colour operator +(const Colour& other) const {return Colour(r + other.r, g + other.g, b + other.b);}
    public:
        float r;
        float g;
        float b;
    };

    struct Face
    {
    public:
        Face(const Triangle& triangle, const Colour& colour) : triangle(triangle), colour(colour){}
        Face() : triangle(Triangle()), colour(Colour::White()){}
        
        void CalculateNormal()
        {
            const Vector3 edge1 = Vector3(triangle.vertices[2].x, triangle.vertices[2].y, triangle.vertices[2].z) -
                Vector3(triangle.vertices[0].x, triangle.vertices[0].y, triangle.vertices[0].z);

            const Vector3 edge2 = Vector3(triangle.vertices[1].x, triangle.vertices[1].y, triangle.vertices[1].z) -
                Vector3(triangle.vertices[0].x, triangle.vertices[0].y, triangle.vertices[0].z);
            
            normal = Vector3::Cross(edge1, edge2).Normalize();
        }
    public:
        Triangle triangle;
        Vector3 normal;
        Colour colour;
    };

    inline void ClipAgainstPlane(const Vector3& planePos, const Vector3& planeNormal, const Face& in, std::vector<Face>& faceQueue)
    {
        const Vector3 normal = planeNormal.Normalize();
        auto dist = [&](const Vector3& point)
        {
            return(normal.x * point.x + normal.y * point.y + normal.z * point.z - Vector3::Dot(normal, planePos));
        };
        
        std::vector<Vector3> insidePoints;
        insidePoints.clear();
        
        if(insidePoints.capacity() != 3)
        {
            insidePoints.reserve(3);
        }
        int insideSize = 0;
        
        std::vector<Vector3> outsidePoints;
        outsidePoints.clear();
        
        if(outsidePoints.capacity() != 3)
        {
            outsidePoints.reserve(3);
        }

        for (int i = 0; i < 3; i++)
        {
            Vector3 currentVertex = in.triangle.vertices[i];
            const float distance = dist(currentVertex);
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
            
            outFace.triangle = Triangle({p0, p1, p2});
            faceQueue.push_back(outFace);
            break;
        case 2:
            for (int i = 0; i < 2; i++)
            {
                outFace.colour = in.colour;
            
                p0 = insidePoints[i];
                p1 = i == 1 ? IntersectPlane(planePos, normal, insidePoints[0], outsidePoints[0]) : insidePoints[1];
                p2 = IntersectPlane(planePos, normal, insidePoints[i], outsidePoints[0]);
            
                outFace.triangle = Triangle({p0, p1, p2});
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

    inline void CalculateLighting(std::vector<Face>& projectedFaces, const Vector3& lightPosition,
        const float& lightIntensity, const Colour& baseColour)
    {
        for (Face& face : projectedFaces)
        {
            const Vector3 lightDirection = (lightPosition -
                (face.triangle.vertices[0] + face.triangle.vertices[1] + face.triangle.vertices[2])/3).Normalize();
            
            float incidentAngle = Vector3::Dot(face.normal, lightDirection);
            if(incidentAngle < 0) incidentAngle = 0;

            Colour ambient = Colour(1,1,1) * 0.5;
            Colour diffuse = Colour(1,1,1) * incidentAngle * lightIntensity;

            Colour totalColour = ambient + diffuse;
            face.colour = totalColour * baseColour;
        }
    }

    inline void ProjectToWorld(const Matrix4x4& model, std::vector<Face>& faces)
    {
        for(Face& face : faces)
        {
            for(int i = 0; i < 3; i++)
            {
                const Vector4 vec4Vertex = Vector4(face.triangle.vertices[i].x, face.triangle.vertices[i].y, face.triangle.vertices[i].z, 1);
                const Vector4 modelSpaceVertex = model * vec4Vertex;
                face.triangle.vertices[i] = Vector3(modelSpaceVertex.x, modelSpaceVertex.y, modelSpaceVertex.z);
            }

            face.CalculateNormal();
        }
    }

    inline std::vector<Face> ProjectToView(const std::vector<Face>& worldFaces,
        const Vector3& cameraPosition, const Matrix4x4& view)
    {
        std::vector<Face> passedFaces;
        
        for (Face projFace : worldFaces)
        {
            if(Vector3::Dot(projFace.normal, (cameraPosition - projFace.triangle.vertices[0]).Normalize()) < 0.0f)
            {
                for (int j = 0; j < 3; j++)
                {
                    const Vector4 vec4Vertex = Vector4(projFace.triangle.vertices[j].x, projFace.triangle.vertices[j].y,
                        projFace.triangle.vertices[j].z, 1);
                    const Vector4 viewSpaceVertex = view * vec4Vertex;
                    projFace.triangle.vertices[j] = Vector3(viewSpaceVertex.x, viewSpaceVertex.y, viewSpaceVertex.z);
                }
        
                ClipAgainstPlane(Vector3(0.0f, 0.0f, 0.1f), Vector3(0.0f, 0.0f, 1.0f), projFace, passedFaces);
            }
        }

        return passedFaces;
    }

    inline void ProjectToScreen(std::vector<Face>& viewFaces, const Matrix4x4& projection)
    {
        for (Face& face : viewFaces)
        {
            face.CalculateNormal();
        
            for (int k = 0; k < 3; k++)
            {
                const Vector4 vec4Vertex = Vector4(face.triangle.vertices[k].x, face.triangle.vertices[k].y,
                    face.triangle.vertices[k].z, 1);
                const Vector4 projectedVertex = projection * vec4Vertex;
                
                face.triangle.vertices[k] = projectedVertex.PerspectiveDivide();
        
                face.triangle.vertices[k] += Vector3(1.0f, 1.0f, 0.0f);
                face.triangle.vertices[k] = Vector3(face.triangle.vertices[k].x * static_cast<float>(APP_VIRTUAL_WIDTH),
                                                    face.triangle.vertices[k].y * static_cast<float>(APP_VIRTUAL_HEIGHT),
                                                    0.0f)/2;
            }
        }
    }

    inline Matrix4x4 CalculateView(const Vector3& position, const Vector3& forward, const Vector3& up)
    {
        const Matrix4x4 pointAtMatrix = Matrix4x4::PointAt(position, position + forward, up);
        return Matrix4x4::LookAt(pointAtMatrix);
    }
}
