#pragma once
#include "../Math/Geometry.h"

namespace TESLA
{
    class ObjLoader
    {
    public:
        ObjLoader() = delete;
        static std::vector<TESLA::Face> LoadFromOBJFile(std::string fileName);
    };
}
