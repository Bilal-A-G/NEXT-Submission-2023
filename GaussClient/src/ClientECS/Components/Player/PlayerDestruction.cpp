#include "PlayerDestruction.h"

#include "GameUtils.h"
#include "ECS/Entity.h"
#include "ECS/Components/Colliders/Collider.h"
#include "Scenes/SceneManager.h"

namespace CLIENT
{
    void PlayerDestruction::Update(GAUSS::EntityComponentLookup& lookup)
    {
        GAUSS::Entity* entity = lookup.GetEntity(entityId);
        if(!entity || !entity->GetActive()) return;

        GAUSS::Collider* collider = entity->GetComponent<GAUSS::Collider>(GAUSS_ENUMS::Collider);
        if(!collider || !collider->GetActive()) return;

        collider->OnCollisionStay([](GAUSS::Entity& a, GAUSS::Entity& b)
        {
            if(b.name == enemyTag || b.name == explosionTag)
                GAUSS::SceneManager::SwitchScene(gameOverSceneName);
        });
    }
}
