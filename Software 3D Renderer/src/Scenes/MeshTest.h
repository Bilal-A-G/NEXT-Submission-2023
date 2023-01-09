#pragma once
#include <iostream>

#include "NextAPI/app.h"
#include "Tesla/ECS/Components/Camera/Camera.h"
#include "Tesla/ECS/Components/Colliders/SphereCollider.h"
#include "Tesla/ECS/Components/Mesh/Mesh.h"
#include "Tesla/ECS/Components/Rigidbody/Rigidbody.h"
#include "Tesla/ECS/Components/Transform//Transform.h"
#include "Tesla/ECS/Systems/Physics/Physics.h"
#include "Tesla/IO/ObjLoader.h"
#include "Tesla/Scenes/SceneManager.h"

class MeshTest : public TESLA::Scene
{
public:
    MeshTest(std::string name):
    Scene(name), m_entity(nullptr){}

    void Awake() override
    {
        //Init camera
        mainCamera = new TESLA::Entity();
        m_cameraTransform = mainCamera->AddComponent<TESLA::Transform>();
        auto camera =  mainCamera->AddComponent<TESLA::Camera>();
        camera->fov = 50.0f;
        camera->farPlane = 1000.0f;
        camera->nearPlane = 0.1f;
        m_cameraTransform->right = TESLA::Vector(-1, 0, 0, 1);

        //Init first sphere
        m_entity = new TESLA::Entity();
        m_mesh = m_entity->AddComponent<TESLA::Mesh>();
        m_transform = m_entity->AddComponent<TESLA::Transform>();
        m_rb = m_entity->AddComponent<TESLA::Rigidbody>();
        auto collider = m_entity->AddComponent<TESLA::SphereCollider>();
        
        m_mesh->faces = TESLA::ObjLoader::LoadFromOBJFile("Sphere");
        m_mesh->colour = TESLA::Colour::Green();
        m_transform->Scale(TESLA::Vector(1,1,1), m_meshSize);
        m_transform->Translate(TESLA::Vector(0, 0, 2));
        m_rb->mass = 20;
        m_rb->hasGravity = false;
        m_rb->friction = 1;
        collider->radius = m_meshSize;

        //Init second sphere
        TESLA::Entity* entity2 = new TESLA::Entity();
        TESLA::Mesh* entity2Mesh = entity2->AddComponent<TESLA::Mesh>();
        TESLA::Transform* entity2Transform = entity2->AddComponent<TESLA::Transform>();
        //TESLA::Rigidbody* entity2Rb = entity2->AddComponent<TESLA::Rigidbody>();
        //TESLA::SphereCollider* entity2Collider = entity2->AddComponent<TESLA::SphereCollider>();

        entity2Mesh->faces = TESLA::ObjLoader::LoadFromOBJFile("Sphere");
        entity2Mesh->colour = TESLA::Colour::Blue();
        entity2Transform->Scale(TESLA::Vector(1, 1, 1), m_meshSize);
        entity2Transform->Translate(TESLA::Vector(0, 0, 4));
        //entity2Rb->mass = 20;
        //entity2Collider->radius = m_meshSize;
        
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

        //Panic
        if(App::IsKeyPressed('P'))
        {
            std::cout << "Hi there";
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
