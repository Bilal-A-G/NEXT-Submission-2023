#pragma once
#include "Camera/PerspectiveCamera.h"

namespace TESLA
{
    class Renderer
    {
    public:
        static void Update(TESLA::PerspectiveCamera* camera);
    };   
}
