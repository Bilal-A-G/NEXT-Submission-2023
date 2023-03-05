#pragma once
#include "ClientECS/Components/ClientEnums.h"
#include "ClientECS/Components/IDestructible.h"

namespace CLIENT
{
    class PlayerDestruction final : public IDestructible
    {
        friend class GAUSS::EntityComponentLookup;
    protected:
        PlayerDestruction() = default;
        ~PlayerDestruction() override = default;
    public:
        void Update(GAUSS::EntityComponentLookup& lookup) override;
        std::vector<int> GetEnum() override {return {CLIENT_ENUMS::Destructible, CLIENT_ENUMS::PlayerDestruction};}
    };    
}

