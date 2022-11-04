#pragma once
#include "complex"

namespace TESLA
{
    struct Matrix4x4;
    
    struct Vector
    {
        Vector(float x, float y, float z, float w):
        x(x), y(y), z(z), w(w){}
        
        Vector(float x, float y, float z):
        x(x), y(y), z(z), w(1){}

        Vector(){}

        Vector PerspectiveDivide() const
        {
            Vector returnVector{x, y, z};
        
            if(w != 0)
            {
                returnVector.x/=w;
                returnVector.y/=w;
                returnVector.z/=w;
            }

            return returnVector;
        }

        float Magnitude()
        {
            return std::sqrt(x*x + y*y + z*z);
        }

        Vector Normalize()
        {
            if(this->Magnitude() == 0)
            {
                return Vector{0,0,0,w};
            }
            return *this/this->Magnitude();
        }

        Vector Abs()
        {
            return {abs(x), abs(y), abs(z), w};
        }

        Vector operator *(const Vector& other) const
        {
            return {other.x * x, other.y * y, other.z * z, other.w * w};
        }

        Vector operator *(const float& other) const
        {
            return  {x * other, y * other, z * other, w * other};
        }

        Vector operator /(const Vector& other) const
        {
            return {x/other.x, y/other.y, z/other.z, w};
        }

        Vector operator /(const float& other) const
        {
            return {x/other, y/other, z/other, w};
        }

        Vector operator +(const Vector& other) const
        {
            return {x + other.x, y + other.y, z + other.z, w};    
        }

        void operator+=(const Vector& other)
        {
            x = x + other.x;
            y = y + other.y;
            z = z + other.z;
        }

        void operator*=(const Vector& other)
        {
            x = x * other.x;
            y = y * other.y;
            z = z * other.z;
        }
    public:
        float x,y,z,w;
    };

    struct Matrix4x4
    {
        Matrix4x4(Vector r1, Vector r2, Vector r3, Vector r4):
        r1(r1), r2(r2), r3(r3), r4(r4){}

        Matrix4x4(){}

        static Matrix4x4 Identity()
        {
            return Matrix4x4{
                {1.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 1.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 1.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 1.0f}
            };
        }

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

        Vector operator*(const Vector& b) const
        {
            Vector returnVector;

            returnVector.x = r1.x * b.x + r1.y * b.y + r1.z * b.z + r1.w * b.w;
            returnVector.y = r2.x * b.x + r2.y * b.y + r2.z * b.z + r2.w * b.w;
            returnVector.z = r3.x * b.x + r3.y * b.y + r3.z * b.z + r3.w * b.w;
            returnVector.w = r4.x * b.x + r4.y * b.y + r4.z * b.z + r4.w * b.w;

            return  returnVector;
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
    public:
        Vector r1, r2, r3, r4;
    };
}