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
            Vector returnVector{x, y, z, w};
        
            if(w != 0)
            {
                returnVector.x/=w;
                returnVector.y/=w;
                returnVector.z/=w;
                returnVector.w = 0.0f;
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

        static float Dot(Vector a, Vector b)
        {
            return a.x * b.x + a.y * b.y + a.z * b.z;
        }

        static Vector Cross(Vector a, Vector b)
        {
            return {(a.y * b.z - a.z * b.y), (a.z * b.x - b.z * a.x), (a.x * b.y - b.x * a.y)};
        }

        Vector operator *(const float& other) const
        {
            return  {x * other, y * other, z * other, w * other};
        }

        void operator *= (const float& other)
        {
            x = x * other;
            y = y * other;
            z = z * other;
            w = w * other;
        }

        Vector operator /(const float& other) const
        {
            return {x/other, y/other, z/other, w/other};
        }

        void operator /= (const float& other)
        {
            x = x / other;
            y = y / other;
            z = z / other;
            w = w / other;
        } 

        Vector operator +(const Vector& other) const
        {
            return {x + other.x, y + other.y, z + other.z, w + other.w};    
        }

        void operator +=(const Vector& other)
        {
            x = x + other.x;
            y = y + other.y;
            z = z + other.z;
            w = w + other.w;
        }

        Vector operator -(const Vector& other) const
        {
            return {x - other.x, y - other.y, z - other.z, w - other.w};
        }

        void operator -=(const Vector& other)
        {
            x = x - other.x;
            y = y - other.y;
            z = z - other.z;
            w = w - other.w;
        }

        //Defined later on
        Vector operator *(const Matrix4x4& other);
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

        static Matrix4x4 PointAt(Vector position, Vector target, Vector up)
        {
            Vector forward = (target - position).Normalize();
            Vector localUp = (up - forward * TESLA::Vector::Dot(up, forward)).Normalize();
            Vector right = TESLA::Vector::Cross(localUp, forward);

            Matrix4x4 pointAt = TESLA::Matrix4x4
            {
                {right.x, right.y, right.z, 0.0f},
                {localUp.x, localUp.y, localUp.z, 0.0f},
                {forward.x, forward.y, forward.z, 0.0f},
                {position.x, position.y, position.z, 1.0f}
            };

            return pointAt;
        }

        static Matrix4x4 LookAt(Matrix4x4 pointAt)
        {
            Matrix4x4 lookAt = TESLA::Matrix4x4
            {
                {pointAt.r1.x, pointAt.r2.x, pointAt.r3.x, 0.0f},
                {pointAt.r1.y, pointAt.r2.y, pointAt.r3.y, 0.0f},
                {pointAt.r1.z, pointAt.r2.z, pointAt.r3.z, 0.0f},
                {-TESLA::Vector::Dot(pointAt.r1, pointAt.r4),
                    -TESLA::Vector::Dot(pointAt.r2, pointAt.r4),
                    -TESLA::Vector::Dot(pointAt.r3, pointAt.r4), 1.0f},
            };

            return lookAt;
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

            returnVector.x = b.x * r1.x + b.y * r2.x + b.z * r3.x + r4.x;
            returnVector.y = b.x * r1.y + b.y * r2.y + b.z * r3.y + r4.y;
            returnVector.z = b.x * r1.z + b.y * r2.z + b.z * r3.z + r4.z;
            returnVector.w = b.x * r1.w + b.y * r2.w + b.z * r3.w + r4.w;

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

    inline Vector Vector::operator*(const Matrix4x4& other)
    {
        Vector returnVector;

        returnVector.x = other.r1.x * x + other.r1.y * y + other.r1.z * z + other.r1.w;
        returnVector.y = other.r2.x * x + other.r2.y * y + other.r2.z * z + other.r2.w;
        returnVector.z = other.r3.x * x + other.r3.y * y + other.r3.z * z + other.r3.w;
        returnVector.w = other.r4.x * x + other.r4.y * y + other.r4.z * z + other.r4.w;

        return  returnVector;
    }

}