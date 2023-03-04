#pragma once
#include "ECS/Component.h"

enum ClientEnums
{
    Bomb = GAUSS_ENUMS::Last + 1
};

namespace Client
{
    class Bomb final : public GAUSS::Component
    {
        friend class GAUSS::EntityComponentLookup;
    protected:
        Bomb() : fuse(1.0f), fuseDrainSpeed(1.0f) {}
        ~Bomb() override = default;
    public:
        std::vector<int> GetEnum() override {return {ClientEnums::Bomb};}
    public:
        float fuse;
        float fuseDrainSpeed;
    };    
}

