#pragma once
#include "../../../Camera/Camera.h"
#include "../../../ECS/Component.h"
#include "../../../ECS/System.h"

namespace TESLA
{
    class Renderer : public TESLA::System
    {
    public:
        Renderer(TESLA::Camera* camera) : m_camera(camera){}
        void Awake() override;
        void Disable() override;
        void Render() override;
    private:
        TESLA::Camera* m_camera;
        std::vector<TESLA::Component*> m_components;
    };   
}
