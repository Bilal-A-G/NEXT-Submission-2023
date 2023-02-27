#pragma once
#include "complex"

namespace GAUSS
{
    struct Matrix4x4;

    struct Vector3 final
    {
    public:
        Vector3(const float& x, const float& y, const float& z): x(x), y(y), z(z){}
        Vector3(): x(0), y(0), z(0){}
        
        float Magnitude() const {return std::sqrt(x*x + y*y + z*z);}
        Vector3 Abs() const {return Vector3(abs(x), abs(y), abs(z));}

        Vector3 Normalize() const
        {
            if(this->Magnitude() == 0)
            {
                return Vector3(0,0,0);
            }
            return *this/this->Magnitude();
        }
        
        static float Dot(const Vector3& a, const Vector3& b) {return a.x * b.x + a.y * b.y + a.z * b.z;}
        static Vector3 Cross(const Vector3& a, const Vector3& b) {return Vector3((a.y * b.z - a.z * b.y), (a.z * b.x - b.z * a.x), (a.x * b.y - b.x * a.y));}

        static Vector3 Zero() {return Vector3(0, 0, 0);}

        bool operator ==(const Vector3& other) const {return x == other.x && y == other.y && z == other.z;}
        bool operator !=(const Vector3& other) const {return x != other.x || y != other.y || z != other.z;}

        Vector3 operator /(const float& other) const {return Vector3(x/other, y/other, z/other);}
        void operator /= (const float& other)
        {
            x = x / other;
            y = y / other;
            z = z / other;
        } 

        Vector3 operator *(const float& other) const {return Vector3(x * other, y * other, z * other);}
        void operator *= (const float& other)
        {
            x = x * other;
            y = y * other;
            z = z * other;
        }

        Vector3 operator +(const Vector3& other) const {return Vector3(x + other.x, y + other.y, z + other.z);}
        void operator +=(const Vector3& other)
        {
            x = x + other.x;
            y = y + other.y;
            z = z + other.z;
        }

        Vector3 operator -(const Vector3& other) const {return Vector3(x - other.x, y - other.y, z - other.z);}
        void operator -=(const Vector3& other)
        {
            x = x - other.x;
            y = y - other.y;
            z = z - other.z;
        }
    public:
        float x;
        float y;
        float z; 
    };
    
    struct Vector4 final
    {
    public:
        Vector4(const float& x, const float& y, const float& z, const float& w): x(x), y(y), z(z), w(w) {}
        Vector4() :x(0), y(0), z(0), w(0) {}

        Vector3 PerspectiveDivide() const
        {
            Vector3 returnVector = Vector3(x, y, z);
        
            if(w != 0) returnVector/= -w;

            return returnVector;
        }

        static Vector4 Zero() {return Vector4(0, 0, 0, 0);}

        Vector4 operator *(const float& other) const {return Vector4(x * other, y * other, z * other, w * other);}
        void operator *= (const float& other)
        {
            x = x * other;
            y = y * other;
            z = z * other;
            w = w * other;
        }

        Vector4 operator /(const float& other) const {return Vector4(x/other, y/other, z/other, w/other);}
        void operator /= (const float& other)
        {
            x = x / other;
            y = y / other;
            z = z / other;
            w = w / other;
        } 

        Vector4 operator +(const Vector4& other) const {return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);}
        void operator +=(const Vector4& other)
        {
            x = x + other.x;
            y = y + other.y;
            z = z + other.z;
            w = w + other.w;
        }

        Vector4 operator -(const Vector4& other) const {return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);}
        void operator -=(const Vector4& other)
        {
            x = x - other.x;
            y = y - other.y;
            z = z - other.z;
            w = w - other.w;
        }

        bool operator ==(const Vector4& other) const {return x == other.x && y == other.y && z == other.z && w == other.w;}
        bool operator !=(const Vector4& other) const {return x != other.x || y != other.y || z != other.z || w != other.w;}

        //Defined later on
        Vector4 operator *(const Matrix4x4& b) const;
    public:
        float x;
        float y;
        float z;
        float w;
    };

    struct Matrix4x4 final
    {
        Matrix4x4(const Vector4& r0, const Vector4& r1, const Vector4& r2, const Vector4& r3): r0(r0), r1(r1), r2(r2), r3(r3){}
        Matrix4x4() : r0(Vector4(1, 0, 0, 0)), r1(Vector4(0, 1, 0, 0)),
        r2(Vector4(0, 0, 1, 0)), r3(Vector4(0, 0, 0, 1)){}

        static Matrix4x4 PointAt(const Vector3& position, const Vector3& target, const Vector3& up)
        {
            const Vector3 forward = (target - position).Normalize();
            const Vector3 localUp = (up - forward * Vector3::Dot(up, forward)).Normalize();
            const Vector3 right = Vector3::Cross(localUp, forward);

            const Matrix4x4 pointAt = Matrix4x4
            {
                {right.x, right.y, right.z, position.x},
                {localUp.x, localUp.y, localUp.z, position.y},
                {forward.x, forward.y, forward.z, position.z},
                {0, 0, 0, 1.0f}
            };

            return pointAt;
        }

        static Matrix4x4 LookAt(const Matrix4x4& pointAt)
        {
            const Vector3 r0Vector = Vector3(pointAt.r0.x, pointAt.r0.y, pointAt.r0.z);
            const Vector3 r1Vector = Vector3(pointAt.r1.x, pointAt.r1.y, pointAt.r1.z);
            const Vector3 r2Vector = Vector3(pointAt.r2.x, pointAt.r2.y, pointAt.r2.z);
            
            const Vector3 r3Vector = Vector3(pointAt.r0.w, pointAt.r1.w, pointAt.r2.w);
            
            const Matrix4x4 lookAt = Matrix4x4
            {
                {pointAt.r0.x, pointAt.r0.y, pointAt.r0.z, -Vector3::Dot(r0Vector, r3Vector)},
                {pointAt.r1.x, pointAt.r1.y, pointAt.r1.z, -Vector3::Dot(r1Vector, r3Vector)},
                {pointAt.r2.x, pointAt.r2.y, pointAt.r2.z, -Vector3::Dot(r2Vector, r3Vector)},
                {0, 0, 0, 1.0f},
            };

            return lookAt;
        }

        Matrix4x4 operator *(const Matrix4x4& b) const
        {
            Matrix4x4 returnMatrix;

            returnMatrix.r0 = Vector4(
                (r0.x * b.r0.x + r0.y * b.r1.x + r0.z * b.r2.x + r0.w * b.r3.x),
                (r0.x * b.r0.y + r0.y * b.r1.y + r0.z * b.r2.y + r0.w * b.r3.y),
                (r0.x * b.r0.z + r0.y * b.r1.z + r0.z * b.r2.z + r0.w * b.r3.z),
                (r0.x * b.r0.w + r0.y * b.r1.w + r0.z * b.r2.w + r0.w * b.r3.w)
            );

            returnMatrix.r1 = Vector4(
                (r1.x * b.r0.x + r1.y * b.r1.x + r1.z * b.r2.x + r1.w * b.r3.x),
                (r1.x * b.r0.y + r1.y * b.r1.y + r1.z * b.r2.y + r1.w * b.r3.y),
                (r1.x * b.r0.z + r1.y * b.r1.z + r1.z * b.r2.z + r1.w * b.r3.z),
                (r1.x * b.r0.w + r1.y * b.r1.w + r1.z * b.r2.w + r1.w * b.r3.w)
            );

            returnMatrix.r2 = Vector4(
                (r2.x * b.r0.x + r2.y * b.r1.x + r2.z * b.r2.x + r2.w * b.r3.x),
                (r2.x * b.r0.y + r2.y * b.r1.y + r2.z * b.r2.y + r2.w * b.r3.y),
                (r2.x * b.r0.z + r2.y * b.r1.z + r2.z * b.r2.z + r2.w * b.r3.z),
                (r2.x * b.r0.w + r2.y * b.r1.w + r2.z * b.r2.w + r2.w * b.r3.w)
            );
            
            returnMatrix.r3 = Vector4(
                (r3.x * b.r0.x + r3.y * b.r1.x + r3.z * b.r2.x + r3.w * b.r3.x),
                (r3.x * b.r0.y + r3.y * b.r1.y + r3.z * b.r2.y + r3.w * b.r3.y),
                (r3.x * b.r0.z + r3.y * b.r1.z + r3.z * b.r2.z + r3.w * b.r3.z),
                (r3.x * b.r0.w + r3.y * b.r1.w + r3.z * b.r2.w + r3.w * b.r3.w)
            );
        
            return returnMatrix;
        }

        Vector4 operator*(const Vector4& b) const
        {
            Vector4 returnVector;

            returnVector.x = r0.x * b.x + r0.y * b.y + r0.z * b.z + r0.w;
            returnVector.y = r1.x * b.x + r1.y * b.y + r1.z * b.z + r1.w;
            returnVector.z = r2.x * b.x + r2.y * b.y + r2.z * b.z + r2.w;
            returnVector.w = r3.x * b.x + r3.y * b.y + r3.z * b.z + r3.w;

            return returnVector;
        }

        Matrix4x4 operator+(const Matrix4x4& b) const
        {
            Matrix4x4 returnMatrix;

            returnMatrix.r0 = Vector4(
                (r0.x + b.r0.x),
                (r0.y + b.r0.y),
                (r0.z + b.r0.z),
                (r0.w + b.r0.w)
            );

            returnMatrix.r1 = Vector4(
                (r1.x + b.r1.x),
                (r1.y + b.r1.y),
                (r1.z + b.r1.z),
                (r1.w + b.r1.w)
            );

            returnMatrix.r2 = Vector4(
                (r2.x + b.r2.x),
                (r2.y + b.r2.y),
                (r2.z + b.r2.z),
                (r2.w + b.r2.w)
            );

            returnMatrix.r3 = Vector4(
                (r3.x + b.r3.x),
                (r3.y + b.r3.y),
                (r3.z + b.r3.z),
                (r3.w + b.r3.w)
            );
        
            return returnMatrix;
        }
    public:
        Vector4 r0;
        Vector4 r1;
        Vector4 r2;
        Vector4 r3;
    };

    inline Vector4 Vector4::operator*(const Matrix4x4& b) const
    {
        Vector4 returnVector;

        returnVector.x = x * b.r0.x + y * b.r1.x + z * b.r2.x + b.r3.x;
        returnVector.y = x * b.r0.y + y * b.r1.y + z * b.r2.y + b.r3.y;
        returnVector.z = x * b.r0.z + y * b.r1.z + z * b.r2.z + b.r3.z;
        returnVector.w = x * b.r0.w + y * b.r1.w + z * b.r2.w + b.r3.w;

        return returnVector;
    }

    inline Vector3 IntersectPlane(const Vector3& planePos, const Vector3& planeNormal, const Vector3& lineStart, const Vector3& lineEnd)
    {
        const Vector3 normal = planeNormal.Normalize();
        const float planeD = -Vector3::Dot(normal, planePos);
        const float aD = Vector3::Dot(lineStart, normal);
        const float bD = Vector3::Dot(lineEnd, normal);
        const float t = (-planeD - aD) / (bD - aD);
        const Vector3 lineVec = lineEnd - lineStart;
        const Vector3 lineIntersection = lineVec * t;
        
        return lineStart + lineIntersection;
    }

    template <typename T>
    inline T Lerp(const T& from, const T& to, const float& interpolator)
    {
        return from * (1 - interpolator) + to * interpolator;
    }
}
