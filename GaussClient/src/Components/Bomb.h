#pragma once
#include "ClientEnums.h"
#include "ECS/Component.h"

namespace CLIENT
{
    class Bomb final : public GAUSS::Component
    {
        friend class GAUSS::EntityComponentLookup;
    protected:
        Bomb() : fuse(1.0f), fuseDrainSpeed(1.0f) {}
        ~Bomb() override = default;
    public:
        std::vector<int> GetEnum() override {return {CLIENT_ENUMS::Bomb};}
    public:
        float fuse;
        float fuseDrainSpeed;
        float explosionRange;
    };    
}

