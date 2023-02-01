#pragma once
#include "../../../ECS/System.h"
#include "../../../ECS/Components/Transform/Transform.h"

namespace TESLA
{
    class ScreenShake : public TESLA::System
    {
    public:
        static void ShakeScreen(float trauma);
        void Update(float deltaTime) override;
        void Awake() override;
        void Disable() override;
    public:
        static float traumaDecreaseRate;
    private:
        static TESLA::Transform* m_cameraTransform;
        static float m_trauma;
    };   
}
