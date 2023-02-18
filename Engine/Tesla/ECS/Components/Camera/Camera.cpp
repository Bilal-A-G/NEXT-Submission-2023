#include "TSpch.h"
#include "Camera.h"
#include "App/AppSettings.h"

TESLA::Camera::Camera()
{
    fov = 0;
    nearPlane = 0;
    farPlane = 0;
}

TESLA::Matrix4x4 TESLA::Camera::GetProjection()
{
    float aspectRatio = (float)APP_VIRTUAL_HEIGHT/(float)APP_VIRTUAL_WIDTH;
    float fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);
    
    return TESLA::Matrix4x4
    {
        {aspectRatio * fovRad, 0.0f, 0.f, 0.0f},
        {0.0f, fovRad, 0.0f, 0.0f},
        {0.0f, 0.0f, farPlane/(farPlane - nearPlane), 1.0f},
        {0.0f, 0.0f, (-farPlane * nearPlane)/(farPlane - nearPlane), 0.0f}
    };
}


