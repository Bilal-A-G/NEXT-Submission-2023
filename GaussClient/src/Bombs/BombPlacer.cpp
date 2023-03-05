#include "BombPlacer.h"
#include "ECS/Entity.h"
#include "ECS/EntityComponentLookup.h"
#include "ECS/Components/Colliders/SphereCollider.h"
#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Transform/Transform.h"
#include "IO/ResourceLoader.h"
#include "../Components/Bomb.h"
#include "../GameSettings.h"

bool BombPlacer::m_firstTime;
std::chrono::time_point<std::chrono::steady_clock> BombPlacer::m_lastPlacedBombTime;

void BombPlacer::PlaceBomb(GAUSS::EntityComponentLookup* lookup, GAUSS::Vector3 position)
{
    std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
    
    if(std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_lastPlacedBombTime).count() < timeBetweenBombs && !m_firstTime)
        return;

    m_firstTime = false;
    m_lastPlacedBombTime = currentTime;
    
    GAUSS::Entity* bombEntity = lookup->CreateEntity();
    GAUSS::Transform* transform =  bombEntity->AddComponent<GAUSS::Transform>();
    transform->SetTranslation(GAUSS::Vector3(round(position.x) * blockSize * spacing, round(position.y) * blockSize * spacing, position.z));
    transform->SetScale(GAUSS::Vector3(1, 1, 1), bombSize);
    GAUSS::Mesh* mesh = bombEntity->AddComponent<GAUSS::Mesh>();
    mesh->faces = GAUSS::ResourceLoader::LoadObjFile("Sphere");
    mesh->colour = bombColour;
    GAUSS::Rigidbody* rigidBody = bombEntity->AddComponent<GAUSS::Rigidbody>();
    rigidBody->hasGravity = false;
    rigidBody->isStatic = true;
    GAUSS::SphereCollider*  collider = bombEntity->AddComponent<GAUSS::SphereCollider>();
    collider->radius = bombSize * 0.65f;
    collider->stiffness = 0.0f;
    bombEntity->name = "Bomb";
    
    CLIENT::Bomb* bomb = bombEntity->AddComponent<CLIENT::Bomb>();
    bomb->fuse = 10.0f;
    bomb->fuseDrainSpeed = 1.0f;
    bomb->explosionRange = 100.0f;
}


