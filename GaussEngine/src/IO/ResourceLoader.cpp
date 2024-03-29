﻿#include "GSPch.h"
#include "ResourceLoader.h"
#include <cassert>

namespace GAUSS
{
    std::vector<Face> ResourceLoader::LoadObjFile(const std::string& fileName)
    {
        std::vector<Triangle> triangles;
        std::vector<Face> faces;
    
        std::ifstream fileStream(resourcesPath + "/" + fileName + ".obj");
        assert(fileStream.is_open());

        std::vector<Vector3> vertices;
        while (!fileStream.eof())
        {
            char line[128];
            fileStream.getline(line, 128);

            std::stringstream fileStringStream;
            fileStringStream << line;

            char out;
            if(line[0] == 'v')
            {
                Vector3 v;
                fileStringStream >> out >> v.x >> v.y >> v.z;
                vertices.push_back(v);
            }
            else if(line[0] == 'f')
            {
                int f[3];
                fileStringStream >> out >> f[0] >> f[1] >> f[2];
                triangles.push_back(Triangle({vertices[f[0] -1], vertices[f[1] - 1], vertices[f[2] - 1]}));
            }
        }

        for (const Triangle& triangle : triangles)
        {
            faces.push_back(Face(triangle, Colour::Black()));
        }

        return faces;
    }
}


