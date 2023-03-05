#pragma once
#include <chrono>

#include "ClientECS/Components/ClientEnums.h"
#include "ClientECS/Components/IAttackable.h"

namespace CLIENT
{
    class BombAttack final : public IAttackable
    {
        friend class GAUSS::EntityComponentLookup;
    protected:
        BombAttack() : m_firstTime(true) {}
        ~BombAttack() override = default;
    public:
        void Update(GAUSS::EntityComponentLookup& lookup) override;
        std::vector<int> GetEnum() override {return {CLIENT_ENUMS::Attackable, CLIENT_ENUMS::BombAttack};}
    private:
        bool m_firstTime;
        std::chrono::time_point<std::chrono::steady_clock> m_lastPlacedBombTime;
    };    
}

