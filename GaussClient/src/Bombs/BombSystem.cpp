#include "BombSystem.h"

#include "Bomb.h"
#include "ECS/Entity.h"

void BombSystem::Update(const float& deltaTime, GAUSS::EntityComponentLookup& lookup)
{
    std::vector<GAUSS::Component*> bombComponents = lookup.GetComponents(ClientEnums::Bomb);

    for (int i = 0; i < bombComponents.size(); i++)
    {
        if(!bombComponents[i])
            continue;

        Client::Bomb* bomb = static_cast<Client::Bomb*>(bombComponents[i]);

        if(bomb->fuse > 0)
        {
            bomb->fuse -= bomb->fuseDrainSpeed * deltaTime;
            continue;
        }

        lookup.DestroyEntity(bomb->entityId);
    }
}
