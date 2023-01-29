#pragma once
#include "../../../ECS/Component.h"
#include "../../../ECS/System.h"
#include "../../../ECS/Components/Camera/Camera.h"
#include "../../../ECS/Components/Transform/Transform.h"
#include "../../../ECS/Components/Light/Light.h"

namespace TESLA
{
    class Renderer : public TESLA::System
    {
    public:
        void Awake() override;
        void Render() override;
    private:
        std::vector<TESLA::Component*> m_meshComponents;
        std::vector<TESLA::Component*> m_transformComponents;
        TESLA::Light* m_light;
        TESLA::Transform* m_lightTransform;
        TESLA::Camera* m_camera;
        TESLA::Transform* m_cameraTransform;
    };   
}
