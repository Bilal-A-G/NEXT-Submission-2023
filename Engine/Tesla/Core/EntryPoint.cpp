#include "TSpch.h"
#include "EntryPoint.h"

#include "Input/Input.h"
#include "Renderer/Renderer.h"
#include "Scenes/SceneManager.h"

void Init()
{
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
    TESLA::Renderer::Update(mainCamera);
    TESLA::SceneManager::Render();
}

void Shutdown()
{
    TESLA::SceneManager::Disable();
    delete(mainCamera);
}




