#include "TSpch.h"
#include "EntryPoint.h"
#include "Renderer/Renderer.h"

void Init()
{
    Awake();
}

void Update(float deltaTime)
{
    UpdateLoop(deltaTime);
}

void Render()
{
    TESLA::Renderer::Update(mainCamera);
}

void Shutdown()
{
    CleanUp();
    delete(mainCamera);
}




