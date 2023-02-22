#include "GSPch.h"
#include "Camera.h"
#include "API/AppSettings.h"

namespace GAUSS
{
    Matrix4x4 Camera::GetProjection()
    {
        float aspectRatio = (float)APP_VIRTUAL_HEIGHT/(float)APP_VIRTUAL_WIDTH;
        float fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);
    
        return Matrix4x4
        {
            {aspectRatio * fovRad, 0.0f, 0.f, 0.0f},
            {0.0f, fovRad, 0.0f, 0.0f},
            {0.0f, 0.0f, farPlane/(farPlane - nearPlane), 1.0f},
            {0.0f, 0.0f, (-farPlane * nearPlane)/(farPlane - nearPlane), 0.0f}
        };
    }
}


