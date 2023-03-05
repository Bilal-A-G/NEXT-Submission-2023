#include "BehaviourUpdater.h"

#include "ClientECS/Components/ClientEnums.h"
#include "ClientECS/Components/IAttackable.h"
#include "ClientECS/Components/IDestructible.h"
#include "ClientECS/Components/IMovable.h"

namespace CLIENT
{
    void BehaviourUpdater::Update(const float& deltaTime, GAUSS::EntityComponentLookup& lookup)
    {
        const std::vector<GAUSS::Component*> movables = lookup.GetComponents(CLIENT_ENUMS::Movable);
        const std::vector<GAUSS::Component*> destructibles = lookup.GetComponents(CLIENT_ENUMS::Destructible);
        const std::vector<GAUSS::Component*> attackables = lookup.GetComponents(CLIENT_ENUMS::Attackable);

        for (int i = 0; i < movables.size(); i++)
        {
            CLIENT::IMovable* movable = static_cast<CLIENT::IMovable*>(movables[i]);
            if(!movable || !movable->GetActive()) continue;
            
            movable->Update(lookup, deltaTime);
        }

        for (int i = 0; i < destructibles.size(); i++)
        {
            CLIENT::IDestructible* destructible = static_cast<CLIENT::IDestructible*>(destructibles[i]);
            if(!destructible || !destructible->GetActive()) continue;
            
            destructible->Update(lookup);
        }

        for (int i = 0; i < attackables.size(); i++)
        {
            CLIENT::IAttackable* attackable = static_cast<CLIENT::IAttackable*>(attackables[i]);
            if(!attackable || !attackable->GetActive()) continue;
            
            attackable->Update(lookup);
        }
    }
    
}
