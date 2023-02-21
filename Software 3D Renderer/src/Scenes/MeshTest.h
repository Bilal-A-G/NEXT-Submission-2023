#pragma once
#include <iostream>

#include "App/app.h"
#include "ECS/Components/Camera/Camera.h"
#include "ECS/Components/Colliders/BoxCollider.h"
#include "ECS/Components/Colliders/SphereCollider.h"
#include "ECS/Components/Light/Light.h"
#include "ECS/Components/Mesh/Mesh.h"
#include "ECS/Components/Particles/ParticleProperties.h"
#include "ECS/Components/Rigidbody/Rigidbody.h"
#include "ECS/Components/Transform//Transform.h"
#include "IO/ResourceLoader.h"
#include "Scenes/SceneManager.h"
#include "ECS/Systems/Physics/Physics.h"
#include "ECS/Systems/Particles/Particles.h"
#include "ECS/Systems/ScreenShake/ScreenShake.h"

bool firstTime = true;

class MeshTest : public TESLA::Scene
{
public:
    MeshTest(std::string name):
    Scene(name){}

    void Awake() override
    {
        //Particles
        TESLA::ParticleSystemProperties system;
        
        system.faces = TESLA::ResourceLoader::LoadObjFile("Cube");
        system.amount = 10;
        system.averageLifetime = 20.0f;
        system.lifetimeVariation = 5.0f;
        system.rotationAxis = TESLA::Vector(1, 1, 1);
        system.averageRotationSpeed = 0.01f;
        system.rotationSpeedVariation = 0.01f;
        system.averageSpeed = 2.0f;
        system.speedVariation = 0.5f;
        system.averageSize = 0.2f;
        system.sizeVariation = 0.01f;
        system.colourVariation = 0.5f;
        system.alphaFadeSpeed = 0.3f;
        system.colourChangeSpeed = 0.2f;
        system.initialColour = TESLA::Colour::White();
        system.endColour = TESLA::Colour::Red();
        system.position = TESLA::Vector(0, 0, 2);
        
        TESLA::Particles::Play(system, *m_lookup);
        
        //Init camera
        m_mainCamera = m_lookup->CreateEntity();
        auto camera = m_mainCamera->AddComponent<TESLA::Camera>();
        m_cameraTransform = m_mainCamera->AddComponent<TESLA::Transform>();
        camera->fov = 50.0f;
        camera->farPlane = 1000.0f;
        camera->nearPlane = 0.1f;

        //Init camera parent
        TESLA::Entity* cameraParent = m_lookup->CreateEntity();
        m_cameraParentTransform = cameraParent->AddComponent<TESLA::Transform>();
        m_cameraParentTransform->SetChild(m_cameraTransform);
        m_cameraTransform->right = TESLA::Vector(-1, 0, 0, 1);
        
        //Init light
        TESLA::Entity* light = m_lookup->CreateEntity();
        light->name = "Light";
        TESLA::Light* lightComponent = light->AddComponent<TESLA::Light>();
        TESLA::Transform* lightTransform = light->AddComponent<TESLA::Transform>();
        lightComponent->intensity = 0.6f;
        lightTransform->Translate(TESLA::Vector(-40, 50, 0));

        //Init first entity
        m_entity = m_lookup->CreateEntity();
        m_entity->name = "Box";
        m_mesh = m_entity->AddComponent<TESLA::Mesh>();
        m_transform = m_entity->AddComponent<TESLA::Transform>();
        m_rb = m_entity->AddComponent<TESLA::Rigidbody>();
        auto collider = m_entity->AddComponent<TESLA::BoxCollider>();
        
        m_mesh->faces = TESLA::ResourceLoader::LoadObjFile("Cube");
        m_mesh->colour = TESLA::Colour::Green();
        m_transform->Scale(TESLA::Vector(1,1,1), m_meshSize/2);
        m_transform->Translate(TESLA::Vector(0, 0, 2));
        m_rb->mass = 20;
        m_rb->hasGravity = false;
        m_rb->friction = 1;
        
        collider->width = 0.6f;
        collider->height = 0.6f;
        collider->depth = 0.6f;

        //Raycasting
        TESLA::Physics::Raycast(TESLA::Vector::Zero(), TESLA::Vector(0, 0, 1, 0), 10, 4.0f,
            [](TESLA::Entity& other)
        {
            std::cout << "Hit: " << other.name << "\n";
        });

        //Collision callbacks
        collider->OnCollisionStay([](TESLA::Entity& other)
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

        //Screenshake
        TESLA::ScreenShake::traumaDecreaseRate = 1.0f;

        //Init second entity
        TESLA::Entity* entity2 = m_lookup->CreateEntity();
        entity2->name = "Sphere";
        TESLA::Mesh* entity2Mesh = entity2->AddComponent<TESLA::Mesh>();
        TESLA::Transform* entity2Transform = entity2->AddComponent<TESLA::Transform>();
        TESLA::Rigidbody* entity2Rb = entity2->AddComponent<TESLA::Rigidbody>();
        auto entity2Collider = entity2->AddComponent<TESLA::SphereCollider>();

        entity2Mesh->faces = TESLA::ResourceLoader::LoadObjFile("Sphere");
        entity2Mesh->colour = TESLA::Colour::Blue();
        entity2Transform->Scale(TESLA::Vector(1, 1, 1), m_meshSize);
        entity2Transform->Translate(TESLA::Vector(0, 0, 4));
        entity2Rb->mass = 20;
        entity2Rb->hasGravity = false;
        entity2Rb->friction = 1;
        
        entity2Collider->radius = 0.6f;
    }

    void Render() override
    {
        App::Print(APP_VIRTUAL_WIDTH/2, APP_VIRTUAL_HEIGHT - 20, "Mesh Test, press L To Lose", 1, 1, 1, GLUT_BITMAP_HELVETICA_10);
    }
    
    void Update(float deltaTime) override
    {
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
        if(App::IsKeyPressed(VK_SHIFT))
        {
            TESLA::ScreenShake::ShakeScreen(0.1f);
            App::PlaySoundW(TESLA::ResourceLoader::GetWavLocation("Smash").c_str());
        }

        m_rb->acceleration += moveVector.Normalize() * 0.3f;

        //Camera controls
        if(App::IsKeyPressed('A'))
        {
            m_cameraParentTransform->Translate(m_cameraTransform->right * m_camSpeed);
        }
        if(App::IsKeyPressed('D'))
        {
            m_cameraParentTransform->Translate(m_cameraTransform->right * -m_camSpeed);
        }
        if(App::IsKeyPressed('W'))
        {
            m_cameraParentTransform->Translate(m_cameraTransform->forward * m_camSpeed);
        }
        if(App::IsKeyPressed('S'))
        {
            m_cameraParentTransform->Translate(m_cameraTransform->forward * -m_camSpeed);
        }
        if(App::IsKeyPressed('Q'))
        {
            m_cameraParentTransform->Rotate(m_cameraParentTransform->up, -m_camSpeed);
            
        }
        if(App::IsKeyPressed('E'))
        {
            m_cameraParentTransform->Rotate(m_cameraParentTransform->up, m_camSpeed);
        }
        if(App::IsKeyPressed(VK_CONTROL))
        {
            m_cameraParentTransform->Translate(m_cameraTransform->up * -m_camSpeed);
        }
        if(App::IsKeyPressed(VK_SPACE))
        {
            m_cameraParentTransform->Translate(m_cameraTransform->up * m_camSpeed);
        }

        //Scene switching
        if(App::IsKeyPressed('L'))
        {
            TESLA::SceneManager::SwitchScene("EndScene");
        }
    }
    
private:
    TESLA::Entity* m_entity;
    TESLA::Entity* m_mainCamera;
    TESLA::Mesh* m_mesh;
    TESLA::Transform* m_transform;
    TESLA::Rigidbody* m_rb;
    TESLA::Transform* m_cameraTransform;
    TESLA::Transform* m_cameraParentTransform;
    
    float m_meshSize = 1.0f;
    float m_camSpeed = 0.02f;
};
