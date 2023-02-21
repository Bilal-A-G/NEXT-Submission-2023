#pragma once
#include "ECS/System.h"

namespace TESLA
{
    class ScreenShake : public TESLA::System
    {
    public:
        static void ShakeScreen(float trauma);
        void Update(float deltaTime, TESLA::EntityComponentLookup& lookup) override;
        void Disable() override;
    public:
        static float traumaDecreaseRate;
    private:
        static float m_trauma;
    };   
}
