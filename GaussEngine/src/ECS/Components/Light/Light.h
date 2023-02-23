#pragma once
#include "ECS/Component.h"

namespace GAUSS
{
    struct Light final : public Component
    {
        friend class EntityComponentLookup;
    protected:
        Light() : intensity(0) {}
        ~Light() override = default;
    public: 
        std::vector<int> GetEnum() override {return {GAUSS_ENUMS::Light};}
    public:
        float intensity;
    }; 
}
