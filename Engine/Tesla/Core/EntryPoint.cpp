#include "TSpch.h"
#include "EntryPoint.h"
#include "Scenes/SceneManager.h"

void Init()
{
    SetUp(scenes);
    
    for(TESLA::Scene* scene : scenes)
    {
        TESLA::SceneManager::AddScene(scene);
    }

    TESLA::SceneManager::Init();
    TESLA::SceneManager::InitSystems();
}

void Update(float deltaTime)
{
    TESLA::SceneManager::UpdateSystems(1/deltaTime);
    TESLA::SceneManager::Update(1/deltaTime);
}

void Render()
{
    TESLA::SceneManager::RenderSystems();
    TESLA::SceneManager::Render();
}

void Shutdown()
{
    TESLA::SceneManager::DisableSystems();
    TESLA::SceneManager::Disable();
}




