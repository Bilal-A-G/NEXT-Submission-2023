#include "TSpch.h"
#include "EntryPoint.h"

#include "Input/Input.h"
#include "Renderer/Renderer.h"

void Init()
{
    Awake();
}

void Update(float deltaTime)
{
    TESLA::Input::Update();
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




