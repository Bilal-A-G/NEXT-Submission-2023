﻿#pragma once
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
        m_triangles(triangles), scaleMatrix(TESLA::Matrix4x4::Identity()), rotationMatrix(TESLA::Matrix4x4::Identity()),
        translationMatrix(TESLA::Matrix4x4::Identity()), view(view), projection(TESLA::Matrix4x4::Identity())
        {
            CalculateModelTriangles();
            CalculateNormals();
            RenderQueue::AddToQueue(this);
        }

        ~Mesh()
        {
            RenderQueue::RemoveFromQueue(this);
        }
        
        void Translate(TESLA::Vector translation);
        void Rotate(float angle, TESLA::Vector axis);
        void Scale(float scale, TESLA::Vector axis);

        std::vector<Triangle> GetProjectedTriangles();
        std::vector<Vector> GetNormals() {return  m_normals;};
        std::vector<Triangle> GetModelTriangles(){return  m_modelTriangles;}
        void CalculateNormals();
        void CalculateModelTriangles();
    private:
        std::vector<Triangle> m_triangles;
        std::vector<Triangle> m_modelTriangles;
        std::vector<Vector> m_normals;
        
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
