#include "Game.h"

#include "API/app.h"
#include "ECS/Entity.h"
#include "ECS/Components/Camera/Camera.h"
#include "ECS/Components/Colliders/BoxCollider.h"
#include "ECS/Components/Light/Light.h"
#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Transform/Transform.h"
#include "IO/ResourceLoader.h"

GAUSS::Entity* player;
GAUSS::Entity* cameraParent;

constexpr int cameraDistanceFromPlayer = -5;
constexpr float cameraCatchUpSpeed = 1;

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
    
    player = m_lookup->CreateEntity();
    GAUSS::Transform* transform = player->AddComponent<GAUSS::Transform>();
    transform->Scale(GAUSS::Vector3(1,1,1), 0.4f);
    transform->Translate(GAUSS::Vector3(0, 0, -cameraDistanceFromPlayer));
    
    GAUSS::Mesh* mesh = player->AddComponent<GAUSS::Mesh>();
    mesh->faces = GAUSS::ResourceLoader::LoadObjFile("Cube");
    mesh->colour = GAUSS::Colour::Green();

    GAUSS::Rigidbody* rigidBody = player->AddComponent<GAUSS::Rigidbody>();
    rigidBody->hasGravity = false;
    rigidBody->mass = 20;
    rigidBody->friction = 1;
}

void Game::Update(const float& deltaTime)
{
    GAUSS::Rigidbody* rigidBody = player->GetComponent<GAUSS::Rigidbody>(GAUSS_ENUMS::RigidBody);
    GAUSS::Transform* playerTransform = player->GetComponent<GAUSS::Transform>(GAUSS_ENUMS::Transform);
    GAUSS::Transform* cameraTransform = cameraParent->GetComponent<GAUSS::Transform>(GAUSS_ENUMS::Transform);
    
    GAUSS::Vector3 direction;

    if(App::IsKeyPressed(VK_UP))
    {
        direction.y = 1;
    }
    if(App::IsKeyPressed(VK_DOWN))
    {
        direction.y = -1;
    }
    if(App::IsKeyPressed(VK_LEFT))
    {
        direction.x = -1;
    }
    if(App::IsKeyPressed(VK_RIGHT))
    {
        direction.x = 1;
    }

    rigidBody->acceleration += direction.Normalize() * 15 * deltaTime;

    direction = GAUSS::Vector3::Zero();

    GAUSS::Vector3 playerPosition = playerTransform->GetPosition();
    GAUSS::Vector3 cameraPosition = cameraTransform->GetPosition();

    GAUSS::Vector3 adjustedPlayerPosition = GAUSS::Vector3(playerPosition.x, playerPosition.y, cameraDistanceFromPlayer);
    cameraTransform->SetTranslation(GAUSS::Lerp<GAUSS::Vector3>(cameraPosition, adjustedPlayerPosition, deltaTime * cameraCatchUpSpeed));
}

