#pragma once
#include <iostream>

#include "NextAPI/app.h"
#include "Tesla/ECS/Components/Camera/Camera.h"
#include "Tesla/ECS/Components/Mesh/Mesh.h"
#include "Tesla/ECS/Components/Transform//Transform.h"
#include "Tesla/IO/ObjLoader.h"
#include "Tesla/Scenes/SceneManager.h"

class MeshTest : public TESLA::Scene
{
public:
    MeshTest(std::string name):
    Scene(name), m_entity(nullptr){}

    void Awake() override
    {
        mainCamera = new TESLA::Entity();
        mainCamera->AddComponent<TESLA::Transform>();
        mainCamera->AddComponent<TESLA::Camera>();
        TESLA::Camera* camera =  mainCamera->GetComponent<TESLA::Camera>(TESLA_ENUMS::Camera);
        camera->fov = 70.0f;
        camera->farPlane = 1000.0f;
        camera->nearPlane = 0.1f;
        
        m_entity = new TESLA::Entity();
        m_entity->AddComponent<TESLA::Mesh>();
        m_entity->AddComponent<TESLA::Transform>();
        
        m_mesh = m_entity->GetComponent<TESLA::Mesh>(TESLA_ENUMS::Mesh);
        m_transform = m_entity->GetComponent<TESLA::Transform>(TESLA_ENUMS::Transform);
        
        m_mesh->faces = TESLA::ObjLoader::LoadFromOBJFile("Sphere");
        m_mesh->colour = TESLA::Colour::Green();
        m_transform->Scale(TESLA::Vector(1,1,1), m_meshSize);
        m_transform->Translate(TESLA::Vector(0, 0, 2));

        m_cameraTransform = mainCamera->GetComponent<TESLA::Transform>(TESLA_ENUMS::Transform);

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
        
        m_transform->Rotate(TESLA::Vector(0, 1, 0), 0.01);
	
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
        if(App::IsKeyPressed('L'))
        {
            TESLA::SceneManager::SwitchScene("EndScene");
        }
        if(App::IsKeyPressed(VK_CONTROL))
        {
            m_cameraTransform->Translate(m_cameraTransform->up * -m_camSpeed);
        }
        if(App::IsKeyPressed(VK_SPACE))
        {
            m_cameraTransform->Translate(m_cameraTransform->up * m_camSpeed);
        }
    }

    void Disable() override
    {
        Scene::Disable();
        
        delete(m_entity);
        delete(m_mesh);
    }
    
private:
    TESLA::Entity* m_entity;
    TESLA::Mesh* m_mesh;
    TESLA::Transform* m_transform;
    TESLA::Transform* m_cameraTransform;
    
    float m_meshSize = 1.0f;
    float m_camSpeed = 0.02f;
};
