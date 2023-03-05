#include "BombAttack.h"

#include "API/app.h"
#include "ECS/Entity.h"
#include "ECS/Components/Colliders/SphereCollider.h"
#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Transform/Transform.h"
#include "IO/ResourceLoader.h"

#include "ClientECS/Components/Bomb.h"
#include "GameUtils.h"

namespace CLIENT
{
    void BombAttack::Update(GAUSS::EntityComponentLookup& lookup)
    {
        if(App::IsKeyPressed(bombKey))
        {
            std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
    
            if(std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_lastPlacedBombTime).count() < timeBetweenBombs && !m_firstTime)
                return;

            m_firstTime = false;
            m_lastPlacedBombTime = currentTime;

            GAUSS::Entity* entity = lookup.GetEntity(entityId);
            GAUSS::Transform* entityTransform = entity->GetComponent<GAUSS::Transform>(GAUSS_ENUMS::Transform);
    
            GAUSS::Entity* bombEntity = lookup.CreateEntity();
            bombEntity->name = bombTag;

            GAUSS::Transform* transform =  bombEntity->AddComponent<GAUSS::Transform>();
            transform->SetTranslation(WorldToGridPosition(entityTransform->GetPosition()));
            transform->SetScale(GAUSS::Vector3(1, 1, 1), bombSize);
    
            GAUSS::Mesh* mesh = bombEntity->AddComponent<GAUSS::Mesh>();
            mesh->faces = GAUSS::ResourceLoader::LoadObjFile("Sphere");
            mesh->colour = bombColour;
    
            GAUSS::Rigidbody* rigidBody = bombEntity->AddComponent<GAUSS::Rigidbody>();
            rigidBody->hasGravity = false;
            rigidBody->isStatic = true;
    
            GAUSS::SphereCollider*  collider = bombEntity->AddComponent<GAUSS::SphereCollider>();
            collider->radius = bombSize * 0.65f;
    
            CLIENT::Bomb* bomb = bombEntity->AddComponent<CLIENT::Bomb>();
            bomb->fuse = fuse;
            bomb->fuseDrainSpeed = fuseDrainSpeed;
        }
    }
    
}
