#include "MazeGenerator.h"

#include "ECS/Entity.h"
#include "ECS/EntityComponentLookup.h"
#include "ECS/Components/Colliders/BoxCollider.h"
#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Transform/Transform.h"
#include "IO/ResourceLoader.h"

#include "GameUtils.h"
#include "ClientECS/Components/Enemy/SimpleDestruction.h"
#include "ClientECS/Components/Enemy/SimpleMovement.h"
#include "ECS/Systems/Particles/ParticleSystemProperties.h"

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
        mazeBoundary->name = wallTag;
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

    GAUSS::ParticleSystemProperties properties;
    
    properties.amount = 5;
    properties.faces = GAUSS::ResourceLoader::LoadObjFile("Cube");
    properties.averageLifetime = 3.0f;
    properties.averageSize = 0.3f;
    properties.averageSpeed = 5.0f;
    properties.colourVariation = 0.01f;
    properties.endColour = GAUSS::Colour::Black();
    properties.lifetimeVariation = 0.1f;
    properties.rotationAxis = GAUSS::Vector3(1, 1, 1);
    properties.sizeVariation = 0.05f;
    properties.speedVariation = 0.1f;
    properties.averageRotationSpeed = 0.01f;
    properties.rotationSpeedVariation = 0.001f;
    properties.colourChangeSpeed = 0.3f;
    
    for (int i = 0; i < mazeWidth * 2; i++)
    {
        for (int j = 0; j < mazeHeight * 2; j++)
        {
            if(i % 2 != 0 || j % 2 != 0)
            {
                if(i >= mazeWidth * 2 - 2 || j >= mazeHeight * 2 - 2)
                    continue;
                
                float breakableBlockRandom = NEW_SEED;
                float enemyRandom = NEW_SEED;
                
                //Generate enemies
                if(breakableBlockRandom >= breakableBlockSpawnChance)
                {
                    if(enemyRandom >= enemySpawnChance) continue;
                    
                    GAUSS::Entity* enemyEntity = lookup->CreateEntity();
                    enemyEntity->name = enemyTag;
                    
                    GAUSS::Mesh* enemyMesh = enemyEntity->AddComponent<GAUSS::Mesh>();
                    enemyMesh->faces = GAUSS::ResourceLoader::LoadObjFile("Cube");
                    enemyMesh->colour = GAUSS::Colour::Red();
                    
                    GAUSS::Transform* enemyTransform = enemyEntity->AddComponent<GAUSS::Transform>();
                    enemyTransform->SetScale(GAUSS::Vector3(1, 1, 1), 0.6f);
                    enemyTransform->SetTranslation(GAUSS::Vector3((i - mazeWidth) * blockSize * spacing, (j - mazeHeight) * blockSize * spacing, -cameraDistance));
                    
                    GAUSS::Rigidbody* enemyRigidBody = enemyEntity->AddComponent<GAUSS::Rigidbody>();
                    enemyRigidBody->hasGravity = false;
                    
                    GAUSS::BoxCollider* enemyCollider = enemyEntity->AddComponent<GAUSS::BoxCollider>();
                    enemyCollider->depth = 0.8f;
                    enemyCollider->height = 0.8f;
                    enemyCollider->width = 0.8f;
                    enemyCollider->stiffness = 200;
                    
                    enemyEntity->AddComponent<CLIENT::SimpleMovement>();

                    CLIENT::SimpleDestruction* enemyDestruction = enemyEntity->AddComponent<CLIENT::SimpleDestruction>();
                    properties.position = enemyTransform->GetPosition();
                    properties.initialColour = GAUSS::Colour(1.0f, 0.4f, 0.1f);
                    enemyDestruction->particleProperties = properties;
                    enemyDestruction->collisionTags = {explosionTag};
                    
                    continue;
                }
                
                //Generate destructible blocks
                GAUSS::Entity* destructibleBlock = CreateMazeBlock(lookup, i, j);
                GAUSS::Mesh* mesh = destructibleBlock->GetComponent<GAUSS::Mesh>(GAUSS_ENUMS::Mesh);
                mesh->colour = breakableBlockColour;
                
                CLIENT::SimpleDestruction* blockDestruction = destructibleBlock->AddComponent<CLIENT::SimpleDestruction>();
                properties.position = destructibleBlock->GetComponent<GAUSS::Transform>(GAUSS_ENUMS::Transform)->GetPosition();
                properties.initialColour = GAUSS::Colour(0.2f, 0.5f, 0.8f);
                blockDestruction->particleProperties = properties;
                blockDestruction->collisionTags = {explosionTag};
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
    block->name = wallTag;
            
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