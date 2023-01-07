#pragma once
#include <iostream>

#include "NextAPI/app.h"
#include "Tesla/Camera/Camera.h"
#include "Tesla/ECS/Components/Mesh/Mesh.h"
#include "Tesla/IO/ObjLoader.h"
#include "Tesla/Scenes/SceneManager.h"

class MeshTest : public TESLA::Scene
{
public:
    MeshTest(TESLA::Camera* camera, std::string name):
    Scene(name), m_mainCamera(camera), m_entity(nullptr){}

    void Awake() override
    {
        m_entity = new TESLA::Entity();
        m_entity->AddComponent<TESLA::Mesh>();
        m_mesh = m_entity->GetComponent<TESLA::Mesh>(TESLA_ENUMS::Mesh);
        
        m_mesh->faces = TESLA::ObjLoader::LoadFromOBJFile("Sphere");
        m_mesh->colour = TESLA::Colour::Green();
        m_mesh->Scale(m_meshSize, TESLA::Vector(1,1,1));
        m_mesh->Translate(TESLA::Vector(0, 0, 2));

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
        
        m_mesh->Rotate(0.01, TESLA::Vector(0, 1, 0));
	
        if(App::IsKeyPressed('A'))
        {
            m_mainCamera->position += m_mainCamera->right * m_camSpeed;
        }
        if(App::IsKeyPressed('D'))
        {
            m_mainCamera->position += m_mainCamera->right * -m_camSpeed;
        }
        if(App::IsKeyPressed('W'))
        {
            m_mainCamera->Translate(m_mainCamera->forward * m_camSpeed);
        }
        if(App::IsKeyPressed('S'))
        {
            m_mainCamera->Translate(m_mainCamera->forward * -m_camSpeed);
        }
        if(App::IsKeyPressed('Q'))
        {
            m_mainCamera->Rotate(-m_camSpeed, m_mainCamera->up);
        }
        if(App::IsKeyPressed('E'))
        {
            m_mainCamera->Rotate(m_camSpeed, m_mainCamera->up);	
        }
        if(App::IsKeyPressed('L'))
        {
            TESLA::SceneManager::SwitchScene("EndScene");
        }
        if(App::IsKeyPressed(VK_CONTROL))
        {
            m_mainCamera->Translate(m_mainCamera->up * -m_camSpeed);
        }
        if(App::IsKeyPressed(VK_SPACE))
        {
            m_mainCamera->Translate(m_mainCamera->up * m_camSpeed);
        }
    }

    void Disable() override
    {
        Scene::Disable();
        
        delete(m_entity);
        delete(m_mesh);
    }
    
private:
    TESLA::Camera* m_mainCamera;
    TESLA::Entity* m_entity;
    TESLA::Mesh* m_mesh;
    
    float m_meshSize = 1.0f;
    float m_camSpeed = 0.02f;
};
