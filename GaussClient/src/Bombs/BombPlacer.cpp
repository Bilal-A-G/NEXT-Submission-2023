﻿#include "BombPlacer.h"

#include <chrono>

#include "ECS/Entity.h"
#include "ECS/EntityComponentLookup.h"
#include "ECS/Components/Colliders/SphereCollider.h"
#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Transform/Transform.h"
#include "IO/ResourceLoader.h"
#include "Math/Math.h"
#include "../Components/Bomb.h"

constexpr float bombSize = 0.8f;
constexpr float timeBetweenBombs = 3.0f;
constexpr float blockSize = 0.8f;
constexpr float spacing = 1.3f;
const GAUSS::Colour bombColour = GAUSS::Colour::Red();

std::chrono::time_point<std::chrono::steady_clock> lastPlacedBombTime;
bool firstTime = true;

void BombPlacer::PlaceBomb(GAUSS::EntityComponentLookup* lookup, GAUSS::Vector3 position)
{
    std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
    
    if(std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastPlacedBombTime).count() < timeBetweenBombs && !firstTime)
        return;

    firstTime = false;
    lastPlacedBombTime = currentTime;
    
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


