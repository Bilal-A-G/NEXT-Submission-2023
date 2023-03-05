#pragma once
#include "ClientECS/Components/ClientEnums.h"
#include "ClientECS/Components/IMovable.h"
#include "Math/Math.h"
#include "GameUtils.h"

namespace CLIENT
{
    class SimpleMovement final : public IMovable
    {
        friend class GAUSS::EntityComponentLookup;
    protected:
        SimpleMovement() : m_moveDirection(GetRandomGridDirection()) {}
        ~SimpleMovement() override = default;
    public:
        void Update(GAUSS::EntityComponentLookup& lookup, const float& deltaTime) override;
        std::vector<int> GetEnum() override {return {CLIENT_ENUMS::Movable, CLIENT_ENUMS::SimpleMovement};}
    private:
        GAUSS::Vector3 m_moveDirection;
    };   
}
