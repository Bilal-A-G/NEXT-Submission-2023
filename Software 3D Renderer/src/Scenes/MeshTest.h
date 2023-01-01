#pragma once
#include <iostream>

#include "NextAPI/app.h"
#include "Tesla/Camera/Camera.h"
#include "Tesla/Mesh/Mesh.h"
#include "Tesla/Scenes/Scene.h"
#include "Tesla/Scenes/SceneManager.h"
#include "Tesla/Mesh/ObjLoader.h"
#include "Tesla/ECS/Entity.h"

struct MyComponent : TESLA::ComponentBase
{
    TESLA::ComponentEnum GetEnum() override{return TESLA::ComponentEnum::Test;}

    void PrintHelloWorld()
    {
        std::cout << "Hello world \n";
    }
};

class MeshTest : public TESLA::Scene
{
public:
    MeshTest(TESLA::Camera* camera, std::string name):
    Scene(name), m_mainCamera(camera), m_mesh(nullptr), m_mesh1(nullptr){}

    void Awake() override
    {
        m_mesh = new TESLA::Mesh(TESLA::ObjLoader::LoadFromOBJFile("Sphere"), TESLA::Vector(1.0f, 0.0f, 0.0f));
        m_mesh->Scale(m_meshSize, TESLA::Vector(1,1,1));
        m_mesh->Translate(TESLA::Vector(0, 0, 2));

        m_mesh1 = new TESLA::Mesh(TESLA::ObjLoader::LoadFromOBJFile("Sphere"), TESLA::Vector(1.0f, 0.0f, 0.0f));
        m_mesh1->Scale(m_meshSize, TESLA::Vector(1,1,1));
        m_mesh1->Translate(TESLA::Vector(0, 1, 7));

        TESLA::Entity myEntity;
        myEntity.AddComponent<MyComponent>();
        std::cout << myEntity.GetComponent(TESLA::Test)->GetEnum();
    }

    void Render() override
    {
        App::Print(APP_VIRTUAL_WIDTH/2, APP_VIRTUAL_HEIGHT - 20, "Mesh Test, press L To Lose", 1, 1, 1, GLUT_BITMAP_HELVETICA_10);
    }
    
    void Update(float deltaTime) override
    {
        m_mesh->Rotate(0.01, TESLA::Vector(0, 1, 0));
        m_mesh1->Rotate(0.01, TESLA::Vector(0, 1, 0));
	
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
        delete(m_mesh);
        delete(m_mesh1);
    }
private:
    TESLA::Camera* m_mainCamera;
    TESLA::Mesh* m_mesh;
    TESLA::Mesh* m_mesh1;
    
    float m_meshSize = 1.0f;
    float m_camSpeed = 0.02f;
};
