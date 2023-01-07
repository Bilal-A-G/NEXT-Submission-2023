#pragma once
#include "../../../ECS/Component.h"
#include "../../../ECS/System.h"
#include "../../../ECS/Entity.h"
#include "../../../ECS/Components/Camera/Camera.h"
#include "../../../ECS/Components/Transform/Transform.h"

namespace TESLA
{
    class Renderer : public TESLA::System
    {
    public:
        void Awake() override;
        void Disable() override;
        void Render() override;
    private:
        std::vector<TESLA::Component*> m_meshComponents;
        std::vector<TESLA::Component*> m_transformComponents;
        TESLA::Camera* m_camera;
        TESLA::Transform* m_cameraTransform;
    };   
}
