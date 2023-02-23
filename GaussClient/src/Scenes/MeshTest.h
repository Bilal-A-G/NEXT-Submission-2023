﻿#pragma once
#include <iostream>

#include "API/app.h"
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
#include "Scenes/Scene.h"
#include "ECS/Entity.h"

bool firstTime = true;

class MeshTest : public GAUSS::Scene
{
public:
    MeshTest(std::string name):
    Scene(name){}

    void Awake() override
    {
        //Particles
        GAUSS::ParticleSystemProperties properties;
        
        properties.faces = GAUSS::ResourceLoader::LoadObjFile("Cube");
        properties.amount = 10;
        properties.averageLifetime = 20.0f;
        properties.lifetimeVariation = 5.0f;
        properties.rotationAxis = GAUSS::Vector3(1, 1, 1);
        properties.averageRotationSpeed = 0.01f;
        properties.rotationSpeedVariation = 0.01f;
        properties.averageSpeed = 2.0f;
        properties.speedVariation = 0.5f;
        properties.averageSize = 0.2f;
        properties.sizeVariation = 0.01f;
        properties.colourVariation = 0.5f;
        properties.alphaFadeSpeed = 0.3f;
        properties.colourChangeSpeed = 0.2f;
        properties.initialColour = GAUSS::Colour::White();
        properties.endColour = GAUSS::Colour::Red();
        properties.position = GAUSS::Vector3(0, 0, 2);
        
        GAUSS::Particles::Play(properties, *m_lookup);
        
        //Init camera
        m_mainCamera = m_lookup->CreateEntity();
        auto camera = m_mainCamera->AddComponent<GAUSS::Camera>();
        m_cameraTransform = m_mainCamera->AddComponent<GAUSS::Transform>();
        camera->fov = 155.0f;
        camera->farPlane = 1000.0f;
        camera->nearPlane = 0.1f;

        //Init camera parent
        GAUSS::Entity* cameraParent = m_lookup->CreateEntity();
        m_cameraParentTransform = cameraParent->AddComponent<GAUSS::Transform>();
        m_cameraParentTransform->SetChild(m_cameraTransform);
        m_cameraTransform->right = GAUSS::Vector3(-1, 0, 0);
        
        //Init light
        GAUSS::Entity* light = m_lookup->CreateEntity();
        light->name = "Light";
        GAUSS::Light* lightComponent = light->AddComponent<GAUSS::Light>();
        GAUSS::Transform* lightTransform = light->AddComponent<GAUSS::Transform>();
        lightComponent->intensity = 0.6f;
        lightTransform->Translate(GAUSS::Vector3(-40, 50, 0));

        //Init first entity
        m_entity = m_lookup->CreateEntity();
        m_entity->name = "Box";
        m_mesh = m_entity->AddComponent<GAUSS::Mesh>();
        m_transform = m_entity->AddComponent<GAUSS::Transform>();
        m_rb = m_entity->AddComponent<GAUSS::Rigidbody>();
        auto collider = m_entity->AddComponent<GAUSS::BoxCollider>();
        
        m_mesh->faces = GAUSS::ResourceLoader::LoadObjFile("Cube");
        m_mesh->colour = GAUSS::Colour::Green();
        m_transform->Scale(GAUSS::Vector3(1,1,1), m_meshSize/2);
        m_transform->Translate(GAUSS::Vector3(0, 0, 2));
        m_rb->mass = 20;
        m_rb->hasGravity = false;
        m_rb->friction = 1;
        
        collider->width = 0.6f;
        collider->height = 0.6f;
        collider->depth = 0.6f;

        //Raycasting
        GAUSS::Physics::Raycast(GAUSS::Vector3::Zero(), GAUSS::Vector3(0, 0, 1), 100, 10.0f,
            [](GAUSS::Entity& other)
        {
            std::cout << "Hit: " << other.name << "\n";
        });

        //Collision callbacks
        collider->OnCollisionStay([](GAUSS::Entity& other)
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
        GAUSS::ScreenShake::traumaDecreaseRate = 1.0f;

        //Init second entity
        GAUSS::Entity* entity2 = m_lookup->CreateEntity();
        entity2->name = "Sphere";
        GAUSS::Mesh* entity2Mesh = entity2->AddComponent<GAUSS::Mesh>();
        GAUSS::Transform* entity2Transform = entity2->AddComponent<GAUSS::Transform>();
        GAUSS::Rigidbody* entity2Rb = entity2->AddComponent<GAUSS::Rigidbody>();
        auto entity2Collider = entity2->AddComponent<GAUSS::SphereCollider>();

        entity2Mesh->faces = GAUSS::ResourceLoader::LoadObjFile("Sphere");
        entity2Mesh->colour = GAUSS::Colour::Blue();
        entity2Transform->Scale(GAUSS::Vector3(1, 1, 1), m_meshSize);
        entity2Transform->Translate(GAUSS::Vector3(0, 0, 4));
        entity2Rb->mass = 20;
        entity2Rb->hasGravity = false;
        entity2Rb->friction = 1;
        
        entity2Collider->radius = 0.6f;
    }

    void Render() override
    {
        App::Print(APP_VIRTUAL_WIDTH/2, APP_VIRTUAL_HEIGHT - 20, "Mesh Test, press L To Lose", 1, 1, 1, GLUT_BITMAP_HELVETICA_10);
    }
    
    void Update(const float& deltaTime) override
    {
        GAUSS::Vector3 moveVector = GAUSS::Vector3::Zero();
        
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
            GAUSS::ScreenShake::ShakeScreen(0.1f);
            App::PlaySoundW(GAUSS::ResourceLoader::GetWavLocation("Smash").c_str());
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
            GAUSS::SceneManager::SwitchScene("EndScene");
        }
    }
    
private:
    GAUSS::Entity* m_entity;
    GAUSS::Entity* m_mainCamera;
    GAUSS::Mesh* m_mesh;
    GAUSS::Transform* m_transform;
    GAUSS::Rigidbody* m_rb;
    GAUSS::Transform* m_cameraTransform;
    GAUSS::Transform* m_cameraParentTransform;
    
    float m_meshSize = 1.0f;
    float m_camSpeed = 0.02f;
};