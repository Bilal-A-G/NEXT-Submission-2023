#include "EnemyController.h"

#include "../Components/ClientEnums.h"
#include "../Components/Enemy.h"
#include "ECS/Component.h"
#include "ECS/Components/Colliders/Collider.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "Scenes/SceneManager.h"

GAUSS::EntityComponentLookup* EnemyController::m_lookup;

void EnemyController::Update(const float& deltaTime, GAUSS::EntityComponentLookup& lookup)
{
    m_lookup = &lookup;
    
    std::vector<GAUSS::Component*> enemies = lookup.GetComponents(CLIENT_ENUMS::Enemy);
    std::vector<GAUSS::Component*> rigidBodies = lookup.GetComponents(GAUSS_ENUMS::RigidBody);
    std::vector<GAUSS::Component*> colliders = lookup.GetComponents(GAUSS_ENUMS::Collider);

    for (int i = 0; i < enemies.size(); i++)
    {
        if(enemies.size() == 0 || rigidBodies.size() == 0 || colliders.size() == 0) return;
        if(!enemies[i] || !rigidBodies[i] || !colliders[i]) continue;
        if(!enemies[i]->GetActive() || !rigidBodies[i]->GetActive() || !colliders[i]->GetActive()) continue;

        CLIENT::Enemy* enemy = static_cast<CLIENT::Enemy*>(enemies[i]);
        GAUSS::Rigidbody* rigidBody = static_cast<GAUSS::Rigidbody*>(rigidBodies[i]);
        GAUSS::Collider* collider = static_cast<GAUSS::Collider*>(colliders[i]);

        collider->OnCollisionStay([](GAUSS::Entity& a, GAUSS::Entity& b)
        {
            if(b.name == "Player")
            {
                b.SetActive(false);
                GAUSS::SceneManager::SwitchScene("GameOver");
            }
            if(b.name != "Wall" && b.name != "Boundary" && b.name != "Bomb") return;
            a.GetComponent<CLIENT::Enemy>(CLIENT_ENUMS::Enemy)->OnHitWall(*m_lookup);
        });

        rigidBody->acceleration = enemy->moveDirection * enemy->moveSpeed * deltaTime;
    }
}

