#include "MazeGenerator.h"

#include "../Components/Bomb.h"
#include "../Components/Destructible.h"
#include "ECS/Entity.h"
#include "ECS/EntityComponentLookup.h"
#include "ECS/Components/Colliders/BoxCollider.h"
#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Transform/Transform.h"
#include "IO/ResourceLoader.h"
#include "Math/Geometry.h"

constexpr int mazeWidth = 4;
constexpr int mazeHeight = 3;
const GAUSS::Colour blockColour = GAUSS::Colour::White();
const GAUSS::Colour breakableBlockColour = GAUSS::Colour(0.7f, 0.5f, 0.5f);
constexpr float blockSize = 0.8f;
constexpr float spacing = 1.3f;
constexpr float cameraDistance = -10;

std::vector<GAUSS::Entity*> MazeGenerator::destructibleBlocks;

void MazeGenerator::GenerateMaze(GAUSS::EntityComponentLookup* lookup)
{
    //Generate bounding box
    for (int i = 0; i < 4; i++)
    {
        GAUSS::Vector3 translation;
        GAUSS::Vector3 scaleAxis;
        float scaleAmount;
        
        constexpr float offsetFromCenter = -1.2f;
        constexpr float totalSpacing = blockSize * spacing;
        constexpr float boundaryDistanceFromMaze = 1.2f;
        constexpr float mazeHeightScaleAmount = mazeHeight % 2 != 0 ? (mazeHeight - 2) * 2 : mazeHeight * 2;
        constexpr float mazeWidthScaleAmount = mazeWidth % 2 != 0 ? (mazeWidth - 2) * 2 : mazeWidth * 2;
        
        switch (i)
        {
        case 0:
            translation = GAUSS::Vector3((-mazeWidth - boundaryDistanceFromMaze) * totalSpacing, offsetFromCenter, -cameraDistance);
            scaleAxis = GAUSS::Vector3(0, 1, 0);
            scaleAmount = mazeHeightScaleAmount;
            break;
        case 1:
            translation = GAUSS::Vector3((mazeWidth - 2 + boundaryDistanceFromMaze) * totalSpacing, offsetFromCenter, -cameraDistance);
            scaleAxis = GAUSS::Vector3(0, 1, 0);
            scaleAmount = mazeHeightScaleAmount;
            break;
        case 2:
            translation = GAUSS::Vector3(offsetFromCenter, (mazeHeight - 2 + boundaryDistanceFromMaze) * totalSpacing, -cameraDistance);
            scaleAxis = GAUSS::Vector3(1, 0, 0);
            scaleAmount = mazeWidthScaleAmount;
            break;
        case 3:
            translation = GAUSS::Vector3(offsetFromCenter, (-mazeHeight - boundaryDistanceFromMaze) * totalSpacing, -cameraDistance);
            scaleAxis = GAUSS::Vector3(1, 0, 0);
            scaleAmount = mazeWidthScaleAmount;
            break;
        default:
            break;
        }
        
        GAUSS::Entity* mazeBoundary = lookup->CreateEntity();
        mazeBoundary->name = "Boundary";
        GAUSS::Transform* mazeBoundaryTransform = mazeBoundary->AddComponent<GAUSS::Transform>();
        mazeBoundaryTransform->SetTranslation(translation);
        mazeBoundaryTransform->Scale(scaleAxis, scaleAmount);
        
        constexpr float colliderPadding = 1.9f;
        GAUSS::BoxCollider* mazeBoundaryCollider = mazeBoundary->AddComponent<GAUSS::BoxCollider>();
        mazeBoundaryCollider->height = mazeBoundaryTransform->GetScale().y * colliderPadding;
        mazeBoundaryCollider->width = mazeBoundaryTransform->GetScale().x * colliderPadding;
        mazeBoundaryCollider->depth = mazeBoundaryTransform->GetScale().z * colliderPadding;
        mazeBoundaryCollider->stiffness = 200;
        
        GAUSS::Rigidbody* mazeBoundaryRigidBody = mazeBoundary->AddComponent<GAUSS::Rigidbody>();
        mazeBoundaryRigidBody->isStatic = true;
        mazeBoundaryRigidBody->hasGravity = false;
    }

    constexpr float destructibleBlockSpawnChance = 0.2f;
    
    for (int i = 0; i < mazeWidth * 2; i++)
    {
        for (int j = 0; j < mazeHeight * 2; j++)
        {
            //Generate destructible blocks
            if(i % 2 != 0 || j % 2 != 0)
            {
                if(i >= mazeWidth * 2 - 2 || j >= mazeHeight * 2 - 2)
                    continue;
                
                float random = rand() / static_cast<float>(RAND_MAX);
                if(random >= destructibleBlockSpawnChance)
                    continue;
                
                GAUSS::Entity* destructibleBlock = CreateMazeBlock(lookup, i, j);
                GAUSS::Mesh* mesh = destructibleBlock->GetComponent<GAUSS::Mesh>(GAUSS_ENUMS::Mesh);
                mesh->colour = breakableBlockColour;

                CLIENT::Destructible* destructible = destructibleBlock->AddComponent<CLIENT::Destructible>();
                GAUSS::ParticleSystemProperties properties;

                properties.amount = 5;
                properties.faces = GAUSS::ResourceLoader::LoadObjFile("Cube");
                properties.position = destructibleBlock->GetComponent<GAUSS::Transform>(GAUSS_ENUMS::Transform)->GetPosition();
                properties.averageLifetime = 3.0f;
                properties.averageSize = 0.3f;
                properties.averageSpeed = 5.0f;
                properties.colourVariation = 0.01f;
                properties.endColour = GAUSS::Colour::Black();
                properties.initialColour = GAUSS::Colour(0.5f, 0.3f, 0.3f);
                properties.lifetimeVariation = 0.1f;
                properties.rotationAxis = GAUSS::Vector3(1, 1, 1);
                properties.sizeVariation = 0.0f;
                properties.speedVariation = 0.1f;
                properties.averageRotationSpeed = 0.01f;
                properties.rotationSpeedVariation = 0.001f;
                properties.colourChangeSpeed = 0.3f;

                destructible->explosionParticleProperties = properties;
                destructibleBlocks.push_back(destructibleBlock);
                continue;
            }

            //Generate non destructible blocks
            CreateMazeBlock(lookup, i, j);
        }
    }
}

GAUSS::Entity* MazeGenerator::CreateMazeBlock(GAUSS::EntityComponentLookup* lookup, int widthIndex, int heightIndex)
{
    GAUSS::Entity* block = lookup->CreateEntity();
    block->name = "Wall";
            
    GAUSS::Transform* transform = block->AddComponent<GAUSS::Transform>();
    transform->SetTranslation(GAUSS::Vector3((widthIndex - mazeWidth) * blockSize * spacing, (heightIndex - mazeHeight) * blockSize * spacing, -cameraDistance));
    transform->SetScale(GAUSS::Vector3(1, 1, 1), blockSize);
            
    GAUSS::Rigidbody* rigidbody = block->AddComponent<GAUSS::Rigidbody>();
    rigidbody->mass = 20;
    rigidbody->hasGravity = false;
    rigidbody->friction = 1;
    rigidbody->isStatic = true;

    constexpr float colliderPadding = 1.25f;
    
    GAUSS::BoxCollider* collider = block->AddComponent<GAUSS::BoxCollider>();
    collider->depth = blockSize * colliderPadding;
    collider->width = blockSize * colliderPadding;
    collider->height = blockSize * colliderPadding;
    collider->stiffness = 200.0f;
            
    GAUSS::Mesh* mesh = block->AddComponent<GAUSS::Mesh>();
    mesh->faces = GAUSS::ResourceLoader::LoadObjFile("Cube");

    return block;
}