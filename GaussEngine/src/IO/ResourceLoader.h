#pragma once
#include "Math/Geometry.h"

const std::string resourcesPath = RES_PATH;

namespace GAUSS
{
    class ResourceLoader final
    {
    public:
        ResourceLoader() = delete;
        ~ResourceLoader() = delete;
        
        static std::vector<Face> LoadObjFile(const std::string& fileName);
        static std::string GetWavLocation(const std::string& fileName) {return resourcesPath + "/" + fileName + ".wav";}
    };
}
