#pragma once
#include "../Math/Geometry.h"

namespace TESLA
{
    class ResourceLoader
    {
    public:
        ResourceLoader() = delete;
        static std::vector<TESLA::Face> LoadObjFile(std::string fileName);
        static std::string GetWavLocation(std::string fileName);
    };
}
