#include "TSpch.h"
#include "EntryPoint.h"

#include "Input/Input.h"
#include "Scenes/SceneManager.h"

void Init()
{
    SetUp(scenes);
    
    for(TESLA::Scene* scene : scenes)
    {
        TESLA::SceneManager::AddScene(scene);
    }

    TESLA::SceneManager::Init();
}

void Update(float deltaTime)
{
    TESLA::Input::Update();
    TESLA::SceneManager::Update(deltaTime);
}

void Render()
{
    TESLA::SceneManager::Render();
}

void Shutdown()
{
    TESLA::SceneManager::Disable();
    delete(mainCamera);
}




