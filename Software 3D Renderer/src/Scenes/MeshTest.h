#pragma once
#include <iostream>

#include "NextAPI/app.h"
#include "Tesla/ECS/Components/Camera/Camera.h"
#include "Tesla/ECS/Components/Colliders/BoxCollider.h"
#include "Tesla/ECS/Components/Colliders/SphereCollider.h"
#include "Tesla/ECS/Components/Mesh/Mesh.h"
#include "Tesla/ECS/Components/Rigidbody/Rigidbody.h"
#include "Tesla/ECS/Components/Transform//Transform.h"
#include "Tesla/IO/ObjLoader.h"
#include "Tesla/Scenes/SceneManager.h"
#include "Tesla/ECS/Systems/Physics/Physics.h"
#include "Tesla/ECS/Systems/Particles/Particles.h"

bool firstTime = true;

class MeshTest : public TESLA::Scene
{
public:
    MeshTest(std::string name):
    Scene(name), m_entity(nullptr){}

    void Awake() override
    {
        TESLA::ParticleProperties cubeParticles = TESLA::ParticleProperties(TESLA::ObjLoader::LoadFromOBJFile("Cube"));
        cubeParticles.amount = 40;
        cubeParticles.averageLifetime = 1000.0f;
        cubeParticles.rotationAxis = TESLA::Vector(1, 1, 1);
        cubeParticles.averageRotationSpeed = 0.01f;
        cubeParticles.averageSpeed = 1.0f;
        cubeParticles.averageSize = 0.1f;
        cubeParticles.colourVariation = 0.5f;
        cubeParticles.alphaFadeSpeed = 0.1f;
        cubeParticles.minSpeed = 2.0f;
        cubeParticles.initialColour = TESLA::Colour::White();
        cubeParticles.endColour = TESLA::Colour::Red();
        
        TESLA::Particles::Play(cubeParticles);
        
        //Init camera
        mainCamera = new TESLA::Entity();
        m_cameraTransform = mainCamera->AddComponent<TESLA::Transform>();
        auto camera =  mainCamera->AddComponent<TESLA::Camera>();
        camera->fov = 50.0f;
        camera->farPlane = 1000.0f;
        camera->nearPlane = 0.1f;
        m_cameraTransform->right = TESLA::Vector(-1, 0, 0, 1);

        //Init first entity
        m_entity = new TESLA::Entity();
        m_entity->m_name = "Box";
        m_mesh = m_entity->AddComponent<TESLA::Mesh>();
        m_transform = m_entity->AddComponent<TESLA::Transform>();
        m_rb = m_entity->AddComponent<TESLA::Rigidbody>();
        auto collider = m_entity->AddComponent<TESLA::BoxCollider>();
        
        m_mesh->faces = TESLA::ObjLoader::LoadFromOBJFile("Cube");
        m_mesh->colour = TESLA::Colour::Green();
        m_transform->Scale(TESLA::Vector(1,1,1), m_meshSize/2);
        m_transform->Translate(TESLA::Vector(0, 0, 2));
        m_rb->mass = 20;
        m_rb->hasGravity = false;
        m_rb->friction = 1;
        
        collider->width = 0.6f;
        collider->height = 0.6f;
        collider->depth = 0.6f;

        TESLA::Physics::Raycast(TESLA::Vector::Zero(), TESLA::Vector(0, 0, 1, 0), 10, 4.0f,
            [](TESLA::Entity* other)
        {
            std::cout << "Hit: " << other->m_name << "\n";
        });

        collider->OnCollisionStay([](TESLA::Entity* other)
        {
            if(!firstTime)
                return;

            firstTime = false;
            std::cout << "Entered collision! \n";
        });

        collider->OnCollisionResolved([]()
        {
            firstTime = true;
            std::cout << "Exited collision! \n";
        });

        //Init second entity
        TESLA::Entity* entity2 = new TESLA::Entity();
        entity2->m_name = "Sphere";
        TESLA::Mesh* entity2Mesh = entity2->AddComponent<TESLA::Mesh>();
        TESLA::Transform* entity2Transform = entity2->AddComponent<TESLA::Transform>();
        TESLA::Rigidbody* entity2Rb = entity2->AddComponent<TESLA::Rigidbody>();
        auto entity2Collider = entity2->AddComponent<TESLA::SphereCollider>();

        entity2Mesh->faces = TESLA::ObjLoader::LoadFromOBJFile("Sphere");
        entity2Mesh->colour = TESLA::Colour::Blue();
        entity2Transform->Scale(TESLA::Vector(1, 1, 1), m_meshSize);
        entity2Transform->Translate(TESLA::Vector(0, 0, 4));
        entity2Rb->mass = 20;
        entity2Rb->hasGravity = false;
        entity2Rb->friction = 1;
        
        entity2Collider->radius = 0.6f;
        // entity2Collider->height = 0.6f;
        // entity2Collider->depth = 0.6f;
        
        Scene::Awake();
    }

    void Render() override
    {
        Scene::Render();
        
        App::Print(APP_VIRTUAL_WIDTH/2, APP_VIRTUAL_HEIGHT - 20, "Mesh Test, press L To Lose", 1, 1, 1, GLUT_BITMAP_HELVETICA_10);
    }
    
    void Update(float deltaTime) override
    {
        Scene::Update(deltaTime);

        TESLA::Vector moveVector = TESLA::Vector::Zero();
        
        //Entity controls
        if(App::IsKeyPressed(VK_UP))
        {
            moveVector += m_transform->forward;
        }
        if(App::IsKeyPressed(VK_DOWN))
        {
            moveVector -= m_transform->forward;
        }
        if(App::IsKeyPressed(VK_LEFT))
        {
            moveVector -= m_transform->right;
        }
        if(App::IsKeyPressed(VK_RIGHT))
        {
            moveVector += m_transform->right;
        }
        if(App::IsKeyPressed(VK_OEM_PERIOD))
        {
            moveVector += m_transform->up;
        }
        if(App::IsKeyPressed(VK_OEM_COMMA))
        {
            moveVector -= m_transform->up;
        }

        m_rb->acceleration += moveVector.Normalize() * 0.3f;

        //Camera controls
        if(App::IsKeyPressed('A'))
        {
            m_cameraTransform->Translate(m_cameraTransform->right * m_camSpeed);
        }
        if(App::IsKeyPressed('D'))
        {
            m_cameraTransform->Translate(m_cameraTransform->right * -m_camSpeed);
        }
        if(App::IsKeyPressed('W'))
        {
            m_cameraTransform->Translate(m_cameraTransform->forward * m_camSpeed);
        }
        if(App::IsKeyPressed('S'))
        {
            m_cameraTransform->Translate(m_cameraTransform->forward * -m_camSpeed);
        }
        if(App::IsKeyPressed('Q'))
        {
            m_cameraTransform->Rotate(m_cameraTransform->up, -m_camSpeed);
            
        }
        if(App::IsKeyPressed('E'))
        {
            m_cameraTransform->Rotate(m_cameraTransform->up, m_camSpeed);
        }
        if(App::IsKeyPressed(VK_CONTROL))
        {
            m_cameraTransform->Translate(m_cameraTransform->up * -m_camSpeed);
        }
        if(App::IsKeyPressed(VK_SPACE))
        {
            m_cameraTransform->Translate(m_cameraTransform->up * m_camSpeed);
        }

        //Scene switching
        if(App::IsKeyPressed('L'))
        {
            TESLA::SceneManager::SwitchScene("EndScene");
        }
    }

    void Disable() override
    {
        Scene::Disable();
    }
    
private:
    TESLA::Entity* m_entity;
    TESLA::Mesh* m_mesh;
    TESLA::Transform* m_transform;
    TESLA::Rigidbody* m_rb;
    TESLA::Transform* m_cameraTransform;
    
    float m_meshSize = 1.0f;
    float m_camSpeed = 0.02f;
};
