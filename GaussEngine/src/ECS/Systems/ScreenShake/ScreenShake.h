#pragma once
#include "ECS/System.h"

namespace GAUSS
{
    class ScreenShake final : public System
    {
        friend class Scene;
    protected:
        ScreenShake() = default;
        ~ScreenShake() override = default;
    public:
        void Update(const float& deltaTime, EntityComponentLookup& lookup) override;
        void Disable() override {m_trauma = 0.0f;}

        static void ShakeScreen(const float& trauma) {m_trauma += trauma;}
    public:
        static float traumaDecreaseRate;
    private:
        static float m_trauma;
    };   
}
