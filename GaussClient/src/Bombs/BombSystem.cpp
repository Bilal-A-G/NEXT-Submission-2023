#include "BombSystem.h"

#include "Bomb.h"
#include "ECS/Entity.h"
#include "ECS/Components/Transform/Transform.h"
#include "ECS/Systems/Physics/Physics.h"
#include "Math/Math.h"

constexpr float explosionRange = 3.0f * 0.8f * 1.3f;

void BombSystem::Update(const float& deltaTime, GAUSS::EntityComponentLookup& lookup)
{
    std::vector<GAUSS::Component*> bombComponents = lookup.GetComponents(ClientEnums::Bomb);
    std::vector<GAUSS::Component*> transformComponents = lookup.GetComponents(GAUSS_ENUMS::Transform);

    for (int i = 0; i < bombComponents.size(); i++)
    {
        if(!bombComponents[i] || i > transformComponents.size())
            continue;

        Client::Bomb* bomb = static_cast<Client::Bomb*>(bombComponents[i]);
        GAUSS::Transform* transform = static_cast<GAUSS::Transform*>(transformComponents[i]);

        if(!transform || !transform->active || !bomb->active) continue;

        if(bomb->fuse > 0)
        {
            bomb->fuse -= bomb->fuseDrainSpeed * deltaTime;
            continue;
        }

         for(int v = 0; v < 4; v++)
         {
             GAUSS::Vector3 rayDirection;
             
             switch (v)
             {
             case 0:
                 rayDirection = GAUSS::Vector3(0, 1, 0);
                 break;
             case 1:
                 rayDirection = GAUSS::Vector3(0, -1, 0);
                 break;
             case 2:
                 rayDirection = GAUSS::Vector3(1, 0, 0);
                 break;
             case 3:
                 rayDirection = GAUSS::Vector3(-1, 0, 0);
                 break;
             default:
                 break;
             }
        
             GAUSS::Physics::Raycast(transform->GetPosition(), rayDirection, explosionRange, 1.5f,
                 [](GAUSS::Entity& a, GAUSS::Entity& b)
             {
                 std::string name = b.name;
             });
        }
        lookup.DestroyEntity(bomb->entityId);
    }
}
