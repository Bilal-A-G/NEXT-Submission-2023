#pragma once
#include "Mesh.h"

namespace TESLA
{
    class ObjLoader
    {
    public:
        ObjLoader() = delete;
        static std::vector<TESLA::Triangle> LoadFromOBJFile(std::string fileName);
    };
}
