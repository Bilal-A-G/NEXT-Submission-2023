#include <vector>

#include "Scenes/MeshTest.h"
#include "Scenes/End.h"
#include "Core/EntryPoint.h"
#include "ECS/Systems/Physics/Physics.h"
#include "ECS/Systems/Renderer/Renderer.h"
#include "ECS/Systems/ScreenShake/ScreenShake.h"
#include "App/main.cpp"

void SetUp(std::vector<TESLA::Scene*>& scenes)
{
    TESLA::Scene* meshTestScene = new MeshTest("MainScene");
    meshTestScene->RegisterSystem<TESLA::Renderer>();
    meshTestScene->RegisterSystem<TESLA::Physics>();
    meshTestScene->RegisterSystem<TESLA::Particles>();
    meshTestScene->RegisterSystem<TESLA::ScreenShake>();
    
    TESLA::Scene* endScene = new End("EndScene");

    scenes.push_back(meshTestScene);
    scenes.push_back(endScene);
}
