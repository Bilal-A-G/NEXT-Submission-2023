#pragma once
#include "Math/Geometry.h"

namespace GAUSS
{
    class ResourceLoader
    {
    public:
        ResourceLoader() = delete;
        static std::vector<Face> LoadObjFile(std::string fileName);
        static std::string GetWavLocation(std::string fileName);
    };
}
