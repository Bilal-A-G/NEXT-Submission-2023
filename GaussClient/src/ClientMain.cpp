#include <vector>

#include "Scenes/MeshTest.h"
#include "Scenes/End.h"
#include "ECS/Systems/Physics/Physics.h"
#include "ECS/Systems/Renderer/Renderer.h"
#include "ECS/Systems/ScreenShake/ScreenShake.h"
#include "API/main.cpp"

void SetUp(std::vector<GAUSS::Scene*>& scenes)
{
    GAUSS::Scene* meshTestScene = new MeshTest("MainScene");
    meshTestScene->RegisterSystem<GAUSS::Renderer>();
    meshTestScene->RegisterSystem<GAUSS::Physics>();
    meshTestScene->RegisterSystem<GAUSS::Particles>();
    meshTestScene->RegisterSystem<GAUSS::ScreenShake>();
    
    GAUSS::Scene* endScene = new End("EndScene");

    scenes.push_back(meshTestScene);
    scenes.push_back(endScene);
}
