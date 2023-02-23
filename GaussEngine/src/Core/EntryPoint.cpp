#include "GSPch.h"
#include "EntryPoint.h"
#include "Scenes/SceneManager.h"

void Init()
{
    SetUp(scenes);
    
    for(GAUSS::Scene* scene : scenes)
    {
        GAUSS::SceneManager::AddScene(scene);
    }

    GAUSS::SceneManager::m_activeScene->Awake();
    GAUSS::SceneManager::m_activeScene->AwakeSystems();
}

void Update(float deltaTime)
{
    GAUSS::SceneManager::m_activeScene->Update(1/deltaTime);
    GAUSS::SceneManager::m_activeScene->UpdateSystems(1/deltaTime);
}

void Render()
{
    GAUSS::SceneManager::m_activeScene->RenderSystems();
    GAUSS::SceneManager::m_activeScene->Render();
}

void Shutdown()
{
    GAUSS::SceneManager::m_activeScene->DisableSystems();
    GAUSS::SceneManager::m_activeScene->Disable();
}




