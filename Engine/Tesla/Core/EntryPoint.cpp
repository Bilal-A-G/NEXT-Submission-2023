#include "TSpch.h"
#include "EntryPoint.h"

void Init()
{
    SetUp(scenes);
    
    for(TESLA::Scene* scene : scenes)
    {
        TESLA::SceneManager::AddScene(scene);
    }

    TESLA::SceneManager::m_activeScene->Awake();
    TESLA::SceneManager::m_activeScene->AwakeSystems();
}

void Update(float deltaTime)
{
    TESLA::SceneManager::m_activeScene->Update(1/deltaTime);
    TESLA::SceneManager::m_activeScene->UpdateSystems(1/deltaTime);
}

void Render()
{
    TESLA::SceneManager::m_activeScene->RenderSystems();
    TESLA::SceneManager::m_activeScene->Render();
}

void Shutdown()
{
    TESLA::SceneManager::m_activeScene->DisableSystems();
    TESLA::SceneManager::m_activeScene->Disable();
}




