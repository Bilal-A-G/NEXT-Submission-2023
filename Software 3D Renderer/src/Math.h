#pragma once

namespace TESLA
{
    struct Matrix4x4;
    
    struct Vector
    {
        float x,y,z,w;
    public:
        Vector(float x, float y, float z, float w):
        x(x), y(y), z(z), w(w){}
        
        Vector(float x, float y, float z):
        x(x), y(y), z(z), w(1){}

        Vector(){}

        Vector operator *(const Vector& other) const
        {
            return {other.x * x, other.y * y, other.z * z, other.w * w};
        }

        Vector operator *(const float& other) const
        {
            return  {x * other, y * other, z * other, w};
        }

        //Defined later on because matrix's body isn't here yet
        Vector operator *(const Matrix4x4& b) const;
    };

    struct Matrix4x4
    {
        Vector r1, r2, r3, r4;
    public:
        Matrix4x4(Vector r1, Vector r2, Vector r3, Vector r4):
        r1(r1), r2(r2), r3(r3), r4(r4){}

        Matrix4x4(){}

        Matrix4x4 operator *(const Matrix4x4& b) const
        {
            Matrix4x4 returnMatrix;

            returnMatrix.r1 = Vector(
                (r1.x * b.r1.x + r1.y * b.r2.x + r1.z * b.r3.x + r1.w * b.r4.x),
                (r1.x * b.r1.y + r1.y * b.r2.y + r1.z * b.r3.y + r1.w * b.r4.y),
                (r1.x * b.r1.z + r1.y * b.r2.z + r1.z * b.r3.z + r1.w * b.r4.z),
                (r1.x * b.r1.w + r1.y * b.r2.w + r1.z * b.r3.w + r1.w * b.r4.w)
            );

            returnMatrix.r2 = Vector(
                (r2.x * b.r1.x + r2.y * b.r2.x + r2.z * b.r3.x + r2.w * b.r4.x),
                (r2.x * b.r1.y + r2.y * b.r2.y + r2.z * b.r3.y + r2.w * b.r4.y),
                (r2.x * b.r1.z + r2.y * b.r2.z + r2.z * b.r3.z + r2.w * b.r4.z),
                (r2.x * b.r1.w + r2.y * b.r2.w + r2.z * b.r3.w + r2.w * b.r4.w)
            );

            returnMatrix.r3 = Vector(
                (r3.x * b.r1.x + r3.y * b.r2.x + r3.z * b.r3.x + r3.w * b.r4.x),
                (r3.x * b.r1.y + r3.y * b.r2.y + r3.z * b.r3.y + r3.w * b.r4.y),
                (r3.x * b.r1.z + r3.y * b.r2.z + r3.z * b.r3.z + r3.w * b.r4.z),
                (r3.x * b.r1.w + r3.y * b.r2.w + r3.z * b.r3.w + r3.w * b.r4.w)
            );
            returnMatrix.r4 = Vector(
                (r4.x * b.r1.x + r4.y * b.r2.x + r4.z * b.r3.x + r4.w * b.r4.x),
                (r4.x * b.r1.y + r4.y * b.r2.y + r4.z * b.r3.y + r4.w * b.r4.y),
                (r4.x * b.r1.z + r4.y * b.r2.z + r4.z * b.r3.z + r4.w * b.r4.z),
                (r4.x * b.r1.w + r4.y * b.r2.w + r4.z * b.r3.w + r4.w * b.r4.w)
            );
        
            return returnMatrix;
        }

        Matrix4x4 operator+(const Matrix4x4& b) const
        {
            Matrix4x4 returnMatrix;

            returnMatrix.r1 = Vector(
                (r1.x + b.r1.x),
                (r1.y + b.r1.y),
                (r1.z + b.r1.z),
                (r1.w + b.r1.w)
            );

            returnMatrix.r2 = Vector(
                (r2.x + b.r2.x),
                (r2.y + b.r2.y),
                (r2.z + b.r2.z),
                (r2.w + b.r2.w)
            );

            returnMatrix.r3 = Vector(
                (r3.x + b.r3.x),
                (r3.y + b.r3.y),
                (r3.z + b.r3.z),
                (r3.w + b.r3.w)
            );

            returnMatrix.r4 = Vector(
                (r4.x + b.r4.x),
                (r4.y + b.r4.y),
                (r4.z + b.r4.z),
                (r4.w + b.r4.w)
            );
        
            return returnMatrix;
        }
    };

    inline Vector Vector::operator*(const Matrix4x4& b) const
    {
        Vector returnVector;

        returnVector.x = x * b.r1.x + y * b.r2.x + z * b.r3.x + b.r4.x;
        returnVector.y = x * b.r1.y + y * b.r2.y + z * b.r3.y + b.r4.y;
        returnVector.z = x * b.r1.z + y * b.r2.z + z * b.r3.z + b.r4.z;
        returnVector.w = x * b.r1.w + y * b.r2.w + z * b.r3.w + b.r4.w;
        
        return returnVector;
    }


    class Triangle
    {
    public:
        std::array<Vector, 3> vertices;
    public:
        Triangle(std::initializer_list<Vector> vertices):vertices()
        {
            this->vertices[0] = data(vertices)[0];
            this->vertices[1] = data(vertices)[1];
            this->vertices[2] = data(vertices)[2];
        }

        Triangle(){}
    };

    struct Mesh
    {
        std::vector<Triangle> triangles;
    public:
        Mesh(std::vector<Triangle> triangles):
        triangles(triangles){}

        Mesh(){}
    };

    static Vector PerspectiveDivide(Vector a)
    {
        Vector returnVector{a.x, a.y, a.z};
        
        if(a.w != 0)
        {
            returnVector.x/=a.w;
            returnVector.y/=a.w;
            returnVector.z/=a.w;
        }

        return returnVector;
    }
    
}