#pragma once
#include "ECS/System.h"

namespace GAUSS
{
    class ScreenShake : public System
    {
    public:
        static void ShakeScreen(float trauma);
        void Update(float deltaTime, EntityComponentLookup& lookup) override;
        void Disable() override;
    public:
        static float traumaDecreaseRate;
    private:
        static float m_trauma;
    };   
}
