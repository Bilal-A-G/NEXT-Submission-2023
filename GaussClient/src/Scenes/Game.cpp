#include "Game.h"

#include "ECS/Entity.h"
#include "ECS/Components/Camera/Camera.h"
#include "ECS/Components/Colliders/BoxCollider.h"
#include "ECS/Components/Colliders/SphereCollider.h"
#include "ECS/Components/Light/Light.h"
#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Transform/Transform.h"
#include "IO/ResourceLoader.h"

#include "Maze/MazeGenerator.h"
#include "GameUtils.h"
#include "ClientECS/Components/Player/BombAttack.h"
#include "ClientECS/Components/Player/KeyboardMovement.h"
#include "ClientECS/Components/Player/PlayerDestruction.h"
#include "ECS/Systems/ScreenShake/ScreenShake.h"
#include "Scenes/SceneManager.h"

GAUSS::Entity* player;
GAUSS::Entity* cameraParent;

void Game::InitPlayer()
{
    player = m_lookup->CreateEntity();
    player->name = "Player";
    GAUSS::Transform* transform = player->AddComponent<GAUSS::Transform>();
    transform->Scale(GAUSS::Vector3(1,1,1), 0.6f);
    transform->Translate(GAUSS::Vector3(0, 0, -cameraDistance));
    
    GAUSS::Mesh* mesh = player->AddComponent<GAUSS::Mesh>();
    mesh->faces = GAUSS::ResourceLoader::LoadObjFile("Cube");
    mesh->colour = GAUSS::Colour::Green();

    GAUSS::Rigidbody* rigidBody = player->AddComponent<GAUSS::Rigidbody>();
    rigidBody->hasGravity = false;
    rigidBody->mass = 20;
    rigidBody->friction = 1;

    GAUSS::BoxCollider* collider = player->AddComponent<GAUSS::BoxCollider>();
    collider->depth = 0.7f;
    collider->height = 0.7f;
    collider->width = 0.7f;
    collider->stiffness = 1.0f;
    collider->OnCollisionResolved([](GAUSS::Entity& a, GAUSS::Entity& b)
    {
       if(b.name == bombTag)
       {
           GAUSS::SphereCollider* collider = b.GetComponent<GAUSS::SphereCollider>(GAUSS_ENUMS::SphereCollider);
           collider->stiffness = 150;
       }
    });

    player->AddComponent<CLIENT::KeyboardMovement>();
    player->AddComponent<CLIENT::BombAttack>();
    player->AddComponent<CLIENT::PlayerDestruction>();
}

void Game::Awake()
{
    GAUSS::Entity* mainCamera = m_lookup->CreateEntity();
    GAUSS::Transform* cameraTransform = mainCamera->AddComponent<GAUSS::Transform>();
    GAUSS::Camera* camera = mainCamera->AddComponent<GAUSS::Camera>();
    camera->fov = 120;
    camera->nearPlane = 0.1f;
    camera->farPlane = 1000.0f;

    cameraParent = m_lookup->CreateEntity();
    GAUSS::Transform* parentTransform = cameraParent->AddComponent<GAUSS::Transform>();
    parentTransform->SetChild(cameraTransform);

    GAUSS::Entity* light = m_lookup->CreateEntity();
    GAUSS::Light* lightComponent = light->AddComponent<GAUSS::Light>();
    GAUSS::Transform* lightTransform = light->AddComponent<GAUSS::Transform>();
    lightComponent->intensity = 0.6f;
    lightTransform->Translate(GAUSS::Vector3(-40, 50, 0));

    InitPlayer();
    MazeGenerator::GenerateMaze(m_lookup);

    GAUSS::ScreenShake::traumaDecreaseRate = 1.0f;
}

void Game::Update(const float& deltaTime)
{
    GAUSS::Transform* playerTransform = player->GetComponent<GAUSS::Transform>(GAUSS_ENUMS::Transform);
    GAUSS::Transform* cameraTransform = cameraParent->GetComponent<GAUSS::Transform>(GAUSS_ENUMS::Transform);
    
    GAUSS::Vector3 playerPosition = playerTransform->GetPosition();
    GAUSS::Vector3 cameraPosition = cameraTransform->GetPosition();

    GAUSS::Vector3 adjustedPlayerPosition = GAUSS::Vector3(playerPosition.x, playerPosition.y, cameraDistance);
    cameraTransform->SetTranslation(GAUSS::Lerp<GAUSS::Vector3>(cameraPosition, adjustedPlayerPosition, deltaTime * cameraCatchUpSpeed));

    int inactiveBlocks = 0;
    for (int i = 0; i < MazeGenerator::destructibleBlocks.size(); i++)
    {
        if(!MazeGenerator::destructibleBlocks[i]->GetActive())
        {
            inactiveBlocks++;
        }
    }
    
    if(inactiveBlocks == MazeGenerator::destructibleBlocks.size())
    {
        GAUSS::SceneManager::SwitchScene("End");
    }
}

void Game::Disable()
{
    MazeGenerator::CleanUp();
}