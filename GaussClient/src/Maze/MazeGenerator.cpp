#include "MazeGenerator.h"

#include "ECS/Entity.h"
#include "ECS/EntityComponentLookup.h"
#include "ECS/Components/Colliders/BoxCollider.h"
#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Transform/Transform.h"
#include "IO/ResourceLoader.h"
#include "Math/Geometry.h"

constexpr int mazeWidth = 5;
constexpr int mazeHeight = 5;
const GAUSS::Colour blockColour = GAUSS::Colour::White();
constexpr float blockSize = 0.8f;
constexpr float spacing = 2.5f;
constexpr float cameraDistance = -10;

void MazeGenerator::GenerateMaze(GAUSS::EntityComponentLookup* lookup)
{
    //Generate bounding box
    GAUSS::Entity* mazeBoundaryLeft = lookup->CreateEntity();
    GAUSS::Transform* mazeBoundaryLeftTransform = mazeBoundaryLeft->AddComponent<GAUSS::Transform>();
    mazeBoundaryLeftTransform->SetTranslation(GAUSS::Vector3(-(mazeWidth + 0.72f) * blockSize * spacing, -blockSize  - blockSize/4, -cameraDistance));
    mazeBoundaryLeftTransform->Scale(GAUSS::Vector3(0.1f, 1, 0.1f), mazeHeight * 2.02f);
    GAUSS::BoxCollider* mazeBoundaryLeftCollider = mazeBoundaryLeft->AddComponent<GAUSS::BoxCollider>();
    mazeBoundaryLeftCollider->depth = mazeHeight * 3.8f;
    mazeBoundaryLeftCollider->width = mazeHeight * 3.8f * 0.1f;
    mazeBoundaryLeftCollider->height = mazeHeight * 3.8f;
    GAUSS::Rigidbody* mazeBoundaryLeftRigidBody = mazeBoundaryLeft->AddComponent<GAUSS::Rigidbody>();
    mazeBoundaryLeftRigidBody->isStatic = true;
    mazeBoundaryLeftRigidBody->hasGravity = false;

    GAUSS::Entity* mazeBoundaryRight = lookup->CreateEntity();
    GAUSS::Transform* mazeBoundaryRightTransform = mazeBoundaryRight->AddComponent<GAUSS::Transform>();
    mazeBoundaryRightTransform->SetTranslation(GAUSS::Vector3(mazeWidth + 2.27f * blockSize * spacing, -blockSize  - blockSize/4, -cameraDistance));
    mazeBoundaryRightTransform->SetScale(GAUSS::Vector3(0.1f, 1, 0.1f), mazeHeight * 2.02f);
    GAUSS::BoxCollider* mazeBoundaryRightCollider = mazeBoundaryRight->AddComponent<GAUSS::BoxCollider>();
    mazeBoundaryRightCollider->depth = mazeHeight * 3.8f;
    mazeBoundaryRightCollider->width = mazeHeight * 3.8f  * 0.1f;
    mazeBoundaryRightCollider->height = mazeHeight * 3.8f;
    GAUSS::Rigidbody* mazeBoundaryRightRigidBody = mazeBoundaryRight->AddComponent<GAUSS::Rigidbody>();
    mazeBoundaryRightRigidBody->isStatic = true;
    mazeBoundaryRightRigidBody->hasGravity = false;
    
    GAUSS::Entity* mazeBoundaryUp = lookup->CreateEntity();
    GAUSS::Transform* mazeBoundaryUpTransform = mazeBoundaryUp->AddComponent<GAUSS::Transform>();
    mazeBoundaryUpTransform->SetTranslation(GAUSS::Vector3(-blockSize - blockSize/4, mazeHeight + 2.27f * blockSize * spacing, -cameraDistance));
    mazeBoundaryUpTransform->SetScale(GAUSS::Vector3(1, 0.1f, 0.1f), mazeWidth * 2.02f);
    GAUSS::BoxCollider* mazeBoundaryUpCollider = mazeBoundaryUp->AddComponent<GAUSS::BoxCollider>();
    mazeBoundaryUpCollider->depth = mazeHeight * 3.8f;
    mazeBoundaryUpCollider->width = mazeHeight * 3.8f;
    mazeBoundaryUpCollider->height = mazeHeight * 3.8f * 0.1f;
    GAUSS::Rigidbody* mazeBoundaryUpRigidBody = mazeBoundaryUp->AddComponent<GAUSS::Rigidbody>();
    mazeBoundaryUpRigidBody->isStatic = true;
    mazeBoundaryUpRigidBody->hasGravity = false;
    
    GAUSS::Entity* mazeBoundaryDown = lookup->CreateEntity();
    GAUSS::Transform* mazeBoundaryDownTransform = mazeBoundaryDown->AddComponent<GAUSS::Transform>();
    mazeBoundaryDownTransform->SetTranslation(GAUSS::Vector3(-blockSize - blockSize/4, -(mazeHeight + 0.72f) * blockSize * spacing, -cameraDistance));
    mazeBoundaryDownTransform->SetScale(GAUSS::Vector3(1, 0.1f, 0.1f), mazeWidth * 2.02f);
    GAUSS::BoxCollider* mazeBoundaryDownCollider = mazeBoundaryDown->AddComponent<GAUSS::BoxCollider>();
    mazeBoundaryDownCollider->depth = mazeHeight * 3.8f;
    mazeBoundaryDownCollider->width = mazeHeight * 3.8f;
    mazeBoundaryDownCollider->height = mazeHeight * 3.8f * 0.1f;
    GAUSS::Rigidbody* mazeBoundaryDownRigidBody = mazeBoundaryDown->AddComponent<GAUSS::Rigidbody>();
    mazeBoundaryDownRigidBody->isStatic = true;
    mazeBoundaryDownRigidBody->hasGravity = false;
    
    for (int i = 0; i < mazeWidth * 2; i++)
    {
        for (int j = 0; j < mazeHeight * 2; j++)
        {
            GAUSS::Entity* block = lookup->CreateEntity();
            
            GAUSS::Transform* transform = block->AddComponent<GAUSS::Transform>();
            transform->SetTranslation(GAUSS::Vector3((i - mazeWidth) * blockSize * spacing, (j - mazeHeight) * blockSize * spacing, -cameraDistance));
            transform->SetScale(GAUSS::Vector3(1, 1, 1), blockSize);
            
            GAUSS::Rigidbody* rigidbody = block->AddComponent<GAUSS::Rigidbody>();
            rigidbody->mass = 20;
            rigidbody->hasGravity = false;
            rigidbody->friction = 1;
            rigidbody->isStatic = true;

            GAUSS::BoxCollider* collider = block->AddComponent<GAUSS::BoxCollider>();
            collider->depth = blockSize;
            collider->width = blockSize;
            collider->height = blockSize;
            
            GAUSS::Mesh* mesh = block->AddComponent<GAUSS::Mesh>();
            mesh->faces = GAUSS::ResourceLoader::LoadObjFile("Cube");
            mesh->colour = blockColour;
        }
    }
}

