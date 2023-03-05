#pragma once
#include "ClientECS/Components/ClientEnums.h"
#include "ClientECS/Components/IMovable.h"

namespace CLIENT
{
    class KeyboardMovement final : public IMovable
    {
        friend class GAUSS::EntityComponentLookup;
    protected:
        KeyboardMovement() {}
        ~KeyboardMovement() override = default;
    public:
        void Update(GAUSS::EntityComponentLookup& lookup, const float& deltaTime) override;
        std::vector<int> GetEnum() override {return {CLIENT_ENUMS::KeyboardMovement, CLIENT_ENUMS::Movable};}
    };    
}

